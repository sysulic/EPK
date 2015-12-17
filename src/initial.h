#ifndef INITIAL_H
#define INITIAL_H

#include "define.h"

//extern vector<OnticAction> ontic_actions;
//extern vector<EpisAction> epis_actions;

class Initial {
public:
	Initial();
	~Initial();

	map<int, string> atomsByIndex;
	map<string, int> atomsByName;

    //EpisDNF init;
    //EpisCNF goal;

public:
	void printAtoms();
};

#endif
