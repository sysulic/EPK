#include "initial.h"
#include "reader.h"

extern Reader reader;

Initial::Initial() {
    atomsGrounding();
    init = getEpisDNFfromTree(reader.init);


    const char* endFile = "output_initial";
    ofstream out_end(endFile);  // 打开要写入的文本文件
    if(!out_end.is_open()) {
        printf("cannot open %s\n", endFile);
        return;
    }
    printAtoms(out_end);
    printInit(out_end);
    //printGoal(out_end);
    //printSenseActions(out_end);
    //printOnticActions(out_end);  // conversion after first printActions()

    out_end.close();
}

void Initial::printInit(ofstream & out) {
    // print init
    out << "----------------init Tree-------------------\n";
    init.show(out);
    out << "----------------  done  -------------------\n\n";

}

void Initial::printGoal(ofstream & out) {
    // print goal
    out << "----------------goal Tree-------------------\n";
    goal.show(out);
    out << "----------------  done  -------------------\n\n";
}
/*
void Initial::printSenseActions(ofstream & out_file) {

    out_file << "-------------- sense actions ----------------\n";
    for(PreSenseActionList::iterator it_action = senseActions.begin();
        it_action != senseActions.end(); ++it_action) {

        if (it_action != senseActions.begin())
            out_file << "******************************************\n";
        out_file << ":action " << (*it_action).name << " --------------\n";

        out_file << "\n:parameters ----------------\n";
        for (MultiTypeSet::iterator it_para = (*it_action).paras.begin();
            it_para != (*it_action).paras.end(); ++it_para) {
            out_file << (*it_para).first << ":";
            for (StringSet::const_iterator it_vrb = (*it_para).second.begin();
                it_vrb != (*it_para).second.end(); ++it_vrb) {
                out_file << " " << *it_vrb;
            }
            out_file << endl;
        }

        out_file << "\n:precondition --------------\n";
        printTree(out_file, (*it_action).preCondition, 0);
        convertToCNFTree((*it_action).preCondition);

        out_file << "\n:observe -------------------\n";
        printTree(out_file, (*it_action).observe, 0);
        convertToCNFTree((*it_action).observe);

    }
    out_file << "----------------  done  -------------------\n\n";

}

void Initial::printOnticActions(ofstream & out_file) {

    out_file << "-------------- ontic actions ----------------\n";
    for(PreOnticActionList::iterator it_action = onticActions.begin();
        it_action != onticActions.end(); ++it_action) {

        if (it_action != onticActions.begin())
            out_file << "******************************************\n";
        out_file << ":action " << (*it_action).name << " --------------\n";

        out_file << "\n:parameters ----------------\n";
        for (MultiTypeSet::iterator it_para = (*it_action).paras.begin();
            it_para != (*it_action).paras.end(); ++it_para) {
            out_file << (*it_para).first << ":";
            for (StringSet::const_iterator it_vrb = (*it_para).second.begin();
                it_vrb != (*it_para).second.end(); ++it_vrb) {
                out_file << " " << *it_vrb;
            }
            out_file << endl;
        }

        out_file << "\n:precondition --------------\n";
        printTree(out_file, (*it_action).preCondition, 0);
        convertToCNFTree((*it_action).preCondition);

        out_file << "\n:effect --------------------\n";
        size_t counter = 0;
        for (EffectList::iterator it_ef = (*it_action).effects.begin();
            it_ef != (*it_action).effects.end(); ++it_ef, ++counter) {
            out_file << "--- effect --- No." << counter << " :\n";
            for (StringSet::iterator str = (*it_ef).condition.begin();
                str != (*it_ef).condition.end(); ++str) {
                out_file << *str << ", ";
            }
            out_file << "\n-----\n";
            for (StringSet::iterator str = (*it_ef).lits.begin();
                str != (*it_ef).lits.end(); ++str) {
                out_file << *str << ", ";
            }
            out_file << "\n";
        }

    }
    out_file << "----------------  done  -------------------\n\n";

}
*/
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
	for (PredicateSet::iterator mul_type_pair = reader.predicates.begin();
			mul_type_pair != reader.predicates.end(); ++mul_type_pair) {
		queue<string> tmp_atoms;
		tmp_atoms.push((*mul_type_pair).first);  // grounding atomic proposition
		for (MultiTypeSet::iterator sig_type_pair = (*mul_type_pair).second.begin();
				sig_type_pair != (*mul_type_pair).second.end(); ++sig_type_pair) {
			// find objects to the specific type
			for (MultiTypeSet::iterator obj = reader.objects.begin();
					obj != reader.objects.end(); ++obj) {
				if((*sig_type_pair).first == (*obj).first) {
					for (size_t i = 0; i < (*sig_type_pair).second.size(); ++i) {
						size_t tmp_atoms_size = tmp_atoms.size();
						for (size_t i = 0; i < tmp_atoms_size; ++i) {
							for (StringSet::iterator ob = (*obj).second.begin();
								ob != (*obj).second.end(); ++ob) {
								if (tmp_atoms.front().find(" "+*ob) != string::npos) {
									continue;  // avoid repeat
								}
								// cout << tmp_atoms.front()+" "+*ob << " //test" << endl;
								tmp_atoms.push(tmp_atoms.front()+" "+*ob);
							}
							tmp_atoms.pop();
						}
					}
				}
			}
		}
		atoms_vector.push_back(tmp_atoms);
	}

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

void Initial::episActionGrounding() {

}

void Initial::onticActionGrounding() {

}

EpisDNF Initial::getEpisDNFfromTree(Formula f) {
	EpisDNF e_dnf;
	Formula* fml = &f;
	stack<Formula*> s;
    do {
        while(fml->label != "NULL") {
            if (fml->label != "|") {//cout << "200 : " << fml->label << endl;
            	e_dnf.epis_terms.push_back(getEpisTermFromTree(*fml));
                fml->label = "NULL";
            } else {
            	s.push(fml);
            	fml = fml->left;
            }
        }
        if(!s.empty()) {
            fml = s.top();
            s.pop();
            fml = fml->right;
        }
    } while(fml->label != "NULL" || !s.empty());
    return e_dnf;
}

EpisTerm Initial::getEpisTermFromTree(Formula & f) {
	EpisTerm e_term;
	Formula* fml = &f;
	stack<Formula*> s;
    do {
        while(fml->label != "NULL") {
            if (fml->label == "K") {
    //cout << "226 : " << fml->label << endl;
            	e_term.pos_propDNF.group(getPropDNFfromTree(*fml));
                fml->label = "NULL";
            } else if (fml->label == "DK") { //cout << "229 : " << fml->label << endl;
                e_term.neg_propDNFs.push_back(getPropDNFfromTree(*fml));
                fml->label = "NULL";
            } else {
            	s.push(fml);
            	fml = fml->left;
            }
        }
        if(!s.empty()) {
            fml = s.top();
            s.pop();
            fml = fml->right;
        }
    } while(fml->label != "NULL" || !s.empty());
    return e_term;
}

PropDNF Initial::getPropDNFfromTree(Formula & f) {
	PropDNF p_dnf;
	Formula* fml = &f;
    //cout << fml->label << endl;
	stack<Formula*> s;
    do {
        while(fml->label != "NULL") {
            if (fml->label != "K" || fml->label != "DK") {
            	p_dnf.prop_terms.push_back(getPropTermFromTree(*fml));
                fml->label = "NULL";
            } else {
            	s.push(fml);
            	fml = fml->left;
            }
        }
        if(s.size() > 1) {
            fml = s.top();
            s.pop();
            fml = fml->right;
        }

    } while(fml->label != "NULL" || s.size() > 1);
    //cout << "270 done" << endl;
    return p_dnf;
}

PropTerm Initial::getPropTermFromTree(Formula & f) {
	PropTerm p_term(atomsByIndex.size()*2);
	Formula* fml = &f;
	stack<Formula*> s;
    do {
        while(fml->label != "NULL") { //cout << "go3" << endl;//cout << fml->label << endl;
            if (fml->label != "&") {//cout << "280 : " << fml->label << endl;
                if (fml->label == "!") {//cout << " 281 : " << fml->label << endl;
                    p_term.literals[atomsByName[fml->left->label]+1] = 1;
                } else {//cout << fml->label << endl;
                    p_term.literals[atomsByName[fml->label]] = 1;
                }
                fml->label = "NULL";
            } else {
            	s.push(fml);
            	fml = fml->left;
            }
        }
        if(!s.empty()) {
            fml = s.top();
            s.pop();
            fml = fml->right;
        }
    } while(fml->label != "NULL" || !s.empty());
    return p_term;
}
