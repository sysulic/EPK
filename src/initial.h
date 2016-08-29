#ifndef INITIAL_H
#define INITIAL_H


#include "define2.h"

extern map<int, string> atomsByIndex;
extern map<string, int> atomsByName;

extern vector<EpisAction> epis_actions;
extern vector<OnticAction> ontic_actions;

class Initial {
public:
    Initial() {}
    void exec(const char* dFile, const char* pFile);
    ~Initial() {}
	
    EpisDNF init;
    EpisCNF goal;

public:
    // for atoms grounding
    void atomsGrounding();
    // for epistemic action grounding
    void episActionsGrounding();
    PreSenseAction episActionParamGrouding(PreSenseAction & senseAction,
        const string param, const string obj);
    void replaceParamWithObj(Formula * f, const string param, const string obj);
    // for ontic action grounding
    void onticActionsGrounding();
    PreOnticAction onticActionParamGrouding(PreOnticAction & onticAction,
        const string param, const string obj);
    StringList getGroundedStr(StringList sl, const string param, const string obj);
    vector<ConEffect> getOnticEffect(EffectList effects);
    
    EpisDNF getEpisDNFfromTree(Formula * f);
    EpisTerm getEpisTermFromTree(Formula * f);
    PropDNF getPropDNFfromTree(Formula * f);
    PropTerm getPropTermFromTree(Formula * f);
    
    EpisCNF getEpisCNFfromTree(Formula * f);
    EpisClause getEpisClauseFromTree(Formula * f);
    PropCNF getPropCNFfromTree(Formula * f);
    PropClause getPropClauseFromTree(Formula * f);

    void checkInitial();

    void printAtoms(ofstream & out);
    void printInit(ofstream & out);
    void printGoal(ofstream & out);
    void printEpisActions(ofstream & out);
    void printOnticActions(ofstream & out);
};

#endif
