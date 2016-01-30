#include "initial.h"
#include "reader.h"

Reader reader;

 void Initial::exec(const char* dFile, const char* pFile) {
    reader.exec(dFile, pFile);
    atomsGrounding();
    episActionsGrounding();
    onticActionsGrounding();

    init = getEpisDNFfromTree(&reader.init);
    goal = getEpisCNFfromTree(&reader.goal);

    string endFile = "../output/";
    endFile += reader.domainName; endFile += "_initial";

    ofstream out_end(endFile);  // 打开要写入的文本文件
    if(!out_end.is_open()) {
        cout << "cannot open " << endFile << endl;
        return;
    }
    printAtoms(out_end);
    printInit(out_end);
    printGoal(out_end);
    printEpisActions(out_end);
    printOnticActions(out_end);  // conversion after first printActions()

    out_end.close();

}

void Initial::printInit(ofstream & out) {
    // print init
    out << "---------------- init -------------------\n";
    init.show(out);
    out << "---------------- done -------------------\n\n";

}

void Initial::printGoal(ofstream & out) {
    // print goal
    out << "---------------- goal -------------------\n";
    goal.show(out);
    out << "---------------- done -------------------\n\n";
}

void Initial::atomsGrounding() {
	/* get atomic propositions from reader */

	// propositions table 
	size_t atomicCounter = 0;
	for (set<string>::iterator it = reader.atomicPropSet.begin();
			it != reader.atomicPropSet.end(); ++it) {
		// cout << *it << endl;
		atomsByName.insert( pair<string, int>(*it, atomicCounter) );
		atomsByIndex.insert( pair<int, string>((atomicCounter++), *it) );
	}

	// predicate grounding
	vector<queue<string> > atoms_vector;
	for (PredicateSet::const_iterator mul_type_pair = reader.predicates.begin();
			mul_type_pair != reader.predicates.end(); ++mul_type_pair) {
		queue<string> tmp_atoms;
		tmp_atoms.push((*mul_type_pair).first);  // grounding atomic proposition
		for (MultiTypeSet::const_iterator sig_type_pair = (*mul_type_pair).second.begin();
				sig_type_pair != (*mul_type_pair).second.end(); ++sig_type_pair) {
			// find objects to the specific type
			for (MultiTypeSet::const_iterator obj = reader.objects.begin();
					obj != reader.objects.end(); ++obj) {
				if((*sig_type_pair).first == (*obj).first) {
					for (size_t i = 0; i < (*sig_type_pair).second.size(); ++i) {
						size_t tmp_atoms_size = tmp_atoms.size();
						for (size_t i = 0; i < tmp_atoms_size; ++i) {
							for (StringList::const_iterator ob = (*obj).second.begin();
								ob != (*obj).second.end(); ++ob) {
                                /*
								if (tmp_atoms.front().find(" "+*ob) != string::npos) {
									continue;  // avoid repeat
								}
                                */
								// cout << tmp_atoms.front()+" "+*ob << " //test" << endl;
								tmp_atoms.push(tmp_atoms.front()+" "+*ob);
							}
							tmp_atoms.pop();
						}
					}
                    break;
				}
			}
		}
		atoms_vector.push_back(tmp_atoms);
	}

    // pass atoms to map
	for (vector<queue<string> > ::iterator atom_queue = atoms_vector.begin();
		atom_queue != atoms_vector.end(); ++atom_queue) {
		while (!(*atom_queue).empty()) {
			atomsByName.insert( pair<string, int>((*atom_queue).front(), atomicCounter) );
			atomsByIndex.insert( pair<int, string>((atomicCounter++), (*atom_queue).front()) );
			(*atom_queue).pop();
		}
	}
    
}

void Initial::printAtoms(ofstream & out) {
	out << "------------ print all atoms ----------------\n";
	for (int i = 0; i < atomsByIndex.size(); ++i)
	{
		out << i << " : " << atomsByIndex[i] << endl;
	}
	out << "-------- end print all atoms ----------------\n\n";
}

void Initial::episActionsGrounding() {
    for (PreSenseActionList::const_iterator senseAction = reader.senseActions.begin();
        senseAction != reader.senseActions.end(); ++senseAction) {

        queue<PreSenseAction> actions;
        actions.push(*senseAction);
        for(MultiTypeSet::const_iterator param = (*senseAction).paras.begin();
            param != (*senseAction).paras.end(); ++param) {

            // find objects to the specific type of a parameter
            for (MultiTypeSet::const_iterator obj = reader.objects.begin();
                    obj != reader.objects.end(); ++obj) {

                if((*param).first == (*obj).first) {
                    size_t tmp_actions_size = actions.size();  // cause size is changing!
                    for (size_t i = 0; i < tmp_actions_size; ++i) {

                        for (StringList::const_iterator ob = (*obj).second.begin();
                            ob != (*obj).second.end(); ++ob) {

                            actions.push(episActionParamGrouding(actions.front(),
                                    *(*param).second.begin(), *ob));
                        }
                        actions.pop();
                    }
                    break;
                }
            }
        }

        // PreSenseActions(reader) to EpisActions(dest structure)
        while (!actions.empty()) {
            EpisAction epis_action;
            epis_action.name = actions.front().name;
            epis_action.pre_con = getEpisCNFfromTree(&(actions.front().preCondition));
            epis_action.pos_res = getPropDNFfromTree(&(actions.front().observe));
            epis_actions.push_back(epis_action);
            actions.pop();
        }

    }
}

PreSenseAction Initial::episActionParamGrouding(PreSenseAction & senseAction,
    const string param, const string obj) {
    PreSenseAction action;
    if (action.name.find_first_of("_") != string::npos)
        action.name.insert(action.name.find_first_of("_"), "_" + obj);
    else
        action.name += "_" + obj;
    action.type = senseAction.type;
    action.paras = senseAction.paras;
    action.preCondition = *copyFormula(&senseAction.preCondition);
    action.observe = *copyFormula(&senseAction.observe);
    // precondition
    replaceParamWithObj(&action.preCondition, param, obj);
    // observe
    replaceParamWithObj(&action.observe, param, obj);
    return action;
}

void Initial::replaceParamWithObj(Formula * f, const string param, const string obj) {
    // cout << param << " " << obj << endl;
    size_t found = f->label.find(param);
    while (found != string::npos) {
        f->label.replace(found, found+param.size(), obj);
        found = f->label.find(param);
    }
    if (f->left != NULL)
    {
        replaceParamWithObj(f->left, param, obj);
    }
    if (f->right != NULL)
    {
        replaceParamWithObj(f->right, param, obj);
    }
}

void Initial::printEpisActions(ofstream & out) {
    out << "---------------- Epis Actions -------------------\n";
    for(vector<EpisAction>::const_iterator epis_action = epis_actions.begin();
        epis_action != epis_actions.end(); ++epis_action) {

        if (epis_action != epis_actions.begin())
            out << "******************************************\n";
        out << ":action " << (*epis_action).name << " --------------\n";

        out << "\n:precondition --------------\n";
        (*epis_action).pre_con.show(out);

        out << ":observe -------------------\n";
        (*epis_action).pos_res.show(out);

    }
    out << "-------------------- done -----------------------\n\n";
}

void Initial::onticActionsGrounding() {
    for (PreOnticActionList::const_iterator onticAction = reader.onticActions.begin();
        onticAction != reader.onticActions.end(); ++onticAction) {

        // action(reader) to action_1 2 3...(reader)
        queue<PreOnticAction> actions;
        actions.push(*onticAction);
        for(MultiTypeSet::const_iterator param = (*onticAction).paras.begin();
            param != (*onticAction).paras.end(); ++param) {

            // find objects to the specific type of a parameter
            for (MultiTypeSet::const_iterator obj = reader.objects.begin();
                    obj != reader.objects.end(); ++obj) {

                if((*param).first == (*obj).first) {
                    size_t tmp_actions_size = actions.size();  // cause size is changing!
                    for (size_t i = 0; i < tmp_actions_size; ++i) {

                        for (StringList::const_iterator ob = (*obj).second.begin();
                            ob != (*obj).second.end(); ++ob) {

                            actions.push(onticActionParamGrouding(actions.front(),
                                    *(*param).second.begin(), *ob));
                        }
                        actions.pop();
                    }
                    break;
                }
            }
        }

        // PreOnticActions(reader) to OnticActions(dest structure)
        while (!actions.empty()) {
            OnticAction ontic_action;
            ontic_action.name = actions.front().name;
            ontic_action.pre_con = getEpisCNFfromTree(&(actions.front().preCondition));
            ontic_action.con_eff = getOnticEffect(actions.front().effects);
            ontic_actions.push_back(ontic_action);
            actions.pop();
        }

    }
}

PreOnticAction Initial::onticActionParamGrouding(PreOnticAction & onticAction,
    const string param, const string obj) {
    PreOnticAction action;
    action.name = onticAction.name;
    if (action.name.find_first_of("_") != string::npos)
        action.name.insert(action.name.find_first_of("_"), "_" + obj);
    else
        action.name += "_" + obj;
    action.type = onticAction.type;
    action.paras = onticAction.paras;
    action.preCondition = *copyFormula(&onticAction.preCondition);
    replaceParamWithObj(&action.preCondition, param, obj);
    for (EffectList::const_iterator eff = onticAction.effects.begin();
        eff != onticAction.effects.end(); ++eff) {
        Effect effect;
        effect.condition = getGroundedStr((*eff).condition, param, obj);
        effect.lits = getGroundedStr((*eff).lits, param, obj);
        action.effects.push_back(effect);
    }
    return action;
}

StringList Initial::getGroundedStr(StringList sl, const string param, const string obj) {
    StringList ss;
    // method replace, so no const_iterator here
    for (StringList::iterator str = sl.begin(); str != sl.end(); ++str) {
        size_t found = str->find(param);
        while (found != string::npos) {
            str->replace(found, found+param.size(), obj);
            found = str->find(param);
        }
        ss.push_back(*str);
    }
    return ss;
}

vector<ConEffect> Initial::getOnticEffect(EffectList effects) {
    vector<ConEffect> con_effs;
    for (EffectList::iterator eff = effects.begin();
        eff != effects.end(); ++eff) {
        ConEffect con_eff;
        // condition
        for (StringList::iterator str = eff->condition.begin();
            str != eff->condition.end(); ++str) {
            if ((*str).substr(0, 3) == "not")
            {
                (*str) = (*str).substr(3, (*str).size()-3);
                size_t start = (*str).find_first_not_of("( ");
                size_t end = (*str).find_last_not_of(") ");
                con_eff.condition.push_back(
                    atomsByName[(*str).substr(start, end-start+1)]*2+1);
            }
            else
                con_eff.condition.push_back(atomsByName[*str]*2);
        }
        // effect
        for (StringList::iterator str = eff->lits.begin();
            str != eff->lits.end(); ++str) {
            if ((*str).substr(0, 3) == "not")
            {
                (*str) = (*str).substr(3, (*str).size()-3);
                size_t start = (*str).find_first_not_of("( ");
                size_t end = (*str).find_last_not_of(") ");
                con_eff.lits.push_back(
                    atomsByName[(*str).substr(start, end-start+1)]*2+1);
            }
            else
                con_eff.lits.push_back(atomsByName[*str]*2);
        }
        con_effs.push_back(con_eff);
    }
    return con_effs;
}

void Initial::printOnticActions(ofstream & out) {
    out << "---------------- Ontic Actions -------------------\n";
    for(vector<OnticAction>::const_iterator ontic_action = ontic_actions.begin();
        ontic_action != ontic_actions.end(); ++ontic_action) {

        if (ontic_action != ontic_actions.begin())
            out << "******************************************\n";
        out << ":action " << (*ontic_action).name << " --------------\n";

        out << "\n:precondition --------------\n";
        (*ontic_action).pre_con.show(out);

        out << ":effects -------------------\n";
        size_t counter = 0;
        for (vector<ConEffect>::const_iterator eff = (*ontic_action).con_eff.begin();
            eff != (*ontic_action).con_eff.end(); ++eff) {
            out << "effect " << counter++ << " --------\n";
            // out condition
            for (vector<int>::const_iterator con = (*eff).condition.begin();
                con != (*eff).condition.end(); ++con) {
                out << *con << " ";
            }
            out << ", ";
            // out lits
            for (vector<int>::const_iterator lit = (*eff).lits.begin();
                lit != (*eff).lits.end(); ++lit) {
                out << *lit << " ";
            }
            out << endl;
        }

    }
    out << "-------------------- done -----------------------\n\n";
}

EpisDNF Initial::getEpisDNFfromTree(Formula * f) {
    EpisDNF e_dnf;
    if (f->label == "True") return e_dnf;  // when true
    stack<Formula*> s;
    do {
        while(f->label != "NULL") {
            if (f->label != "|") {
                e_dnf.epis_terms.push_back(getEpisTermFromTree(f));
                f->label = "NULL";
            } else {
                s.push(f);
                f = f->left;
            }
        }
        if(!s.empty()) {
            f = s.top();
            s.pop();
            f = f->right;
        }
    } while(f->label != "NULL" || !s.empty());
    e_dnf.minimal();
    return e_dnf;
}

EpisTerm Initial::getEpisTermFromTree(Formula * f) {
    EpisTerm e_term;
    stack<Formula*> s;
    do {
        while(f->label != "NULL") {
            if (f->label == "K") {
                e_term.pos_propDNF = e_term.pos_propDNF.group(getPropDNFfromTree(f));
                f->label = "NULL";
            } else if (f->label == "DK") {
                e_term.neg_propDNFs.push_back(getPropDNFfromTree(f));
                f->label = "NULL";
            } else {
                s.push(f);
                f = f->left;
            }
        }
        if(!s.empty()) {
            f = s.top();
            s.pop();
            f = f->right;
        }
    } while(f->label != "NULL" || !s.empty());
    return e_term;
}

PropDNF Initial::getPropDNFfromTree(Formula * f) {
    PropDNF p_dnf;
    stack<Formula*> s;
    do {
        while(f->label != "NULL") {
            if (f->label != "K" && f->label != "DK"
                && f->label != "|") {
                p_dnf.prop_terms.push_back(getPropTermFromTree(f));
                f->label = "NULL";
            } else {
                s.push(f);
                f = f->left;
            }
        }
        if(s.size() > 1) {
            f = s.top();
            s.pop();
            f = f->right;
        }

    } while(f->label != "NULL" || s.size() > 1);
    p_dnf.minimal();
    return p_dnf;
}

PropTerm Initial::getPropTermFromTree(Formula * f) {
    PropTerm p_term(atomsByIndex.size()*2);
    stack<Formula*> s;
    do {
        while(f->label != "NULL") {
            if (f->label != "&") {
                if (f->label == "!") {
                    p_term.literals[atomsByName[f->left->label]*2+1] = 1;
                } else {
                    p_term.literals[atomsByName[f->label]*2] = 1;
                }
                f->label = "NULL";
            } else {
                s.push(f);
                f = f->left;
            }
        }
        if(!s.empty()) {
            f = s.top();
            s.pop();
            f = f->right;
        }
    } while(f->label != "NULL" || !s.empty());
    return p_term;
}

EpisCNF Initial::getEpisCNFfromTree(Formula * f) {
    EpisCNF e_cnf;
    if (f->label == "True") return e_cnf;  // when true
    stack<Formula*> s;
    do {
        while(f->label != "NULL") {
            if (f->label != "&") {
                e_cnf.epis_clauses.push_back(getEpisClauseFromTree(f));
                f->label = "NULL";
            } else {
                s.push(f);
                f = f->left;
            }
        }
        if(!s.empty()) {
            f = s.top();
            s.pop();
            f = f->right;
        }
    } while(f->label != "NULL" || !s.empty());
    e_cnf.minimal();
    return e_cnf;
}

EpisClause Initial::getEpisClauseFromTree(Formula * f) {
    EpisClause e_clause;
    stack<Formula*> s;
    do {
        while(f->label != "NULL") {
            if (f->label == "DK") {
                e_clause.neg_propCNF = e_clause.neg_propCNF.group(getPropCNFfromTree(f));
                f->label = "NULL";
            } else if (f->label == "K") {
                e_clause.pos_propCNFs.push_back(getPropCNFfromTree(f));
                f->label = "NULL";
            } else {
                s.push(f);
                f = f->left;
            }
        }
        if(!s.empty()) {
            f = s.top();
            s.pop();
            f = f->right;
        }
    } while(f->label != "NULL" || !s.empty());
    return e_clause;
}

PropCNF Initial::getPropCNFfromTree(Formula * f) {
    PropCNF p_cnf;
    stack<Formula*> s;
    do {
        while(f->label != "NULL") {
            if (f->label != "K" && f->label != "DK"
                && f->label != "&") {
                p_cnf.prop_clauses.push_back(getPropClauseFromTree(f));
                f->label = "NULL";
            } else {
                s.push(f);
                f = f->left;
            }
        }
        if(s.size() > 1) {
            f = s.top();
            s.pop();
            f = f->right;
        }

    } while(f->label != "NULL" || s.size() > 1);
    p_cnf.minimal();
    return p_cnf;
}

PropClause Initial::getPropClauseFromTree(Formula * f) {
    PropClause p_clause(atomsByIndex.size()*2);
    stack<Formula*> s;
    do {
        while(f->label != "NULL") {
            if (f->label != "|") {
                if (f->label == "!") {
                    p_clause.literals[atomsByName[f->left->label]*2+1] = 1;
                } else {
                    p_clause.literals[atomsByName[f->label]*2] = 1;
                }
                f->label = "NULL";
            } else {
                s.push(f);
                f = f->left;
            }
        }
        if(!s.empty()) {
            f = s.top();
            s.pop();
            f = f->right;
        }
    } while(f->label != "NULL" || !s.empty());
    return p_clause;
}
