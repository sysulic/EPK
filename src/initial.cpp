#include "initial.h"
#include "reader.h"

extern Reader reader;

Initial::Initial() {
    atomsGrounding();
    init = getEpisDNFfromTree(reader.init);
}

Initial::~Initial() {

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
    
    atoms_length = atomsByIndex.size();  // initial atoms_length
}

void Initial::printAtoms() {
	cout << "------------ print all atoms ----------------\n";
	for (int i = 0; i < atomsByIndex.size(); ++i)
	{
		cout << atomsByIndex[i] << endl;
	}
	cout << "-------- end print all atoms ----------------\n";
}


void Initial::episActionGrounding() {

}

void Initial::onticActionGrounding() {

}

EpisDNF Initial::getEpisDNFfromTree(Formula & f) {
	EpisDNF e_dnf;
	Formula* fml = &f;
	stack<Formula*> s;
    while(fml != NULL || !s.empty())
    {
        while(fml != NULL)
        {
            if (fml->label == "&") {
            	e_dnf.epis_terms.push_back(getEpisTermFromTree(*fml));
            	break;
            } else {
            	s.push(fml);
            	fml = fml->left;
            }
        }
        if(!s.empty())
        {
            fml = s.top();
            s.pop();
            fml = fml->right;
        }
    }
    return e_dnf;
}

EpisTerm Initial::getEpisTermFromTree(Formula & f) {
	EpisTerm e_term;
	Formula* fml = &f;
	stack<Formula*> s;
    while(fml != NULL || !s.empty())
    {
        while(fml != NULL)
        {
            if (fml->label == "K") {
            	e_term.pos_propDNF.group(getPropDNFfromTree(*fml));
            	break;
            } else if (fml->label == "DK") {
                e_term.neg_propDNFs.push_back(getPropDNFfromTree(*fml));
                break;
            } else {
            	s.push(fml);
            	fml = fml->left;
            }
        }
        if(!s.empty())
        {
            fml = s.top();
            s.pop();
            fml = fml->right;
        }
    }
    return e_term;
}

PropDNF Initial::getPropDNFfromTree(Formula & f) {
	PropDNF p_dnf;
	Formula* fml = &f;
	stack<Formula*> s;
    while(fml != NULL || !s.empty())
    {
        while(fml != NULL)
        {
            if (fml->label == "&") {
            	p_dnf.prop_terms.push_back(getPropTermFromTree(*fml));
            	break;
            } else {
            	s.push(fml);
            	fml = fml->left;
            }
        }
        if(!s.empty())
        {
            fml = s.top();
            s.pop();
            fml = fml->right;
        }
    }
    return p_dnf;
}

PropTerm Initial::getPropTermFromTree(Formula & f) {
	PropTerm p_term(atomsByIndex.size());
	Formula* fml = &f;
	stack<Formula*> s;
    while(fml != NULL || !s.empty())
    {
        while(fml != NULL)
        {
            if (fml->label != "&") {
                if (fml->label == "!")
                    p_term.literals[atomsByName[fml->left->label]+1] = 1;
                else
                    p_term.literals[atomsByName[fml->label]] = 1;
            } else {
            	s.push(fml);
            	fml = fml->left;
            }
        }
        if(!s.empty())
        {
            fml = s.top();
            s.pop();
            fml = fml->right;
        }
    }
    return p_term;
}

