#ifndef INITIAL_H
#define INITIAL_H

#include "define2.h"

class Initial {
public:
    Initial();
    ~Initial();

    map<int, string> atomsByIndex;
    map<string, int> atomsByName;
    size_t atoms_length;
    
    vector<EpisAction> epis_actions;
    vector<OnticAction> ontic_actions;
	
    EpisDNF init;
    EpisCNF goal;

public:
    void atomsGrounding();
    void episActionGrounding();
    void onticActionGrounding();
    void printAtoms();
    
    EpisDNF getEpisDNFfromTree(Formula & f);
    EpisTerm getEpisTermFromTree(Formula & f);
    PropDNF getPropDNFfromTree(Formula & f);
    PropTerm getPropTermFromTree(Formula & f);
    
    EpisCNF getEpisCNFfromTree(Formula & f);
    EpisTerm getEpisTermFromTree(Formula & f);
    PropCNF getPropCNFfromTree(Formula & f);
    PropTerm getPropTermFromTree(Formula & f);
};

#endif
