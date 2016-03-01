#ifndef DEFINE_H
#define DEFINE_H


#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <list>
#include <map>
#include <queue>
#include <vector>
#include <stack>
#include "EpisCNF.h"
#include "EpisDNF.h"

//#include <algorithm>
//#include <sys/time.h>
//#include <sys/resource.h>
//#include <math.h>
//#include <cstdio>

using namespace std;

struct Formula;
struct PreSenseAction;
struct ConEffect;
struct PreOnticAction;
struct Effect;

typedef list<Effect> EffectList;
typedef set<string> StringSet;
typedef list<string> StringList;
typedef pair<string, StringList> SingleTypePair;
typedef list<SingleTypePair> MultiTypeList;
typedef pair<string, MultiTypeList> MultiTypePair;
typedef set<MultiTypePair> PredicateSet;
typedef list<PreSenseAction> PreSenseActionList;
typedef list<PreOnticAction> PreOnticActionList;

struct Formula
{
	string label;
	Formula* left;
	Formula* right;
    Formula() {
        label = "";
        left = NULL;
        right = NULL;
    }
    Formula(string la) {
        label = la;
        left = NULL;
        right = NULL;
    }
    Formula(string la, Formula* l, Formula* r) {
        label = la;
        left = l;
        right = r;
    }
};

static inline Formula* copyFormula(Formula* f) {
    Formula* tmp = new Formula(*f);
    if (f->left) tmp->left = copyFormula(f->left);
    if (f->right) tmp->right = copyFormula(f->right);
    return tmp;
}

//观察动作的描述 - for preprocessing
struct PreSenseAction
{
    string name; // action name
    string type; // sense or ontic
    MultiTypeList paras; // parameters
    Formula preCondition;
    Formula observe; //需要观察的“公式”
};

//物理动作中的effect（效果二元组）- for preprocessing
struct Effect
{
    StringList condition; //效果中的条件
    StringList lits;  
};

//物理动作的描述 - for preprocessing
struct PreOnticAction
{
    string name; //动作的名称
    string type; // sense or ontic
    MultiTypeList paras;
    Formula preCondition;
    EffectList effects; //效果二元组
};


enum STATE_TYPE {
    TOBEEXPLORED = 0,
    EXPLORED,
    DEAD,
    FINAL_GOAL
};


#endif
