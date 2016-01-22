#ifndef INITIAL_H
#define INITIAL_H


#include "define2.h"


class Initial {
public:
    Initial(const char* dFile, const char* pFile);
    ~Initial() {}
	
    EpisDNF init;
    EpisCNF goal;

public:
    void atomsGrounding();
    void episActionsGrounding();
    PreSenseAction episActionParamGrouding(PreSenseAction & senseAction,
                                        const string param, const string obj);
    void replaceParamWithObj(Formula * f, const string param, const string obj);
    void onticActionsGrounding();
    
    EpisDNF getEpisDNFfromTree(Formula * f);
    EpisTerm getEpisTermFromTree(Formula * f);
    PropDNF getPropDNFfromTree(Formula * f);
    PropTerm getPropTermFromTree(Formula * f);
    
    EpisCNF getEpisCNFfromTree(Formula * f);
    EpisClause getEpisClauseFromTree(Formula * f);
    PropCNF getPropCNFfromTree(Formula * f);
    PropClause getPropClauseFromTree(Formula * f);


    void printAtoms(ofstream & out);
    void printInit(ofstream & out);
    void printGoal(ofstream & out);
    void printEpisActions(ofstream & out);
    void printOnticActions(ofstream & out);
};

#endif
