#ifndef DEFINE_H
#define DEFINE_H


#include <string>
#include <iostream>
#include <set>
#include <list>
#include <map>
#include <vector>
//#include <algorithm>
//#include <sys/time.h>
//#include <sys/resource.h>
//#include <math.h>
//#include <cstdio>

using namespace std;

struct Formula;
struct SenseAction;
struct ConEffect;
struct OnticAction;
struct Effect;

typedef list<Effect> EffectList;
typedef set<string> StringSet;
typedef pair<string, StringSet> SingleTypePair;
typedef set<SingleTypePair> MultiTypeSet;
typedef pair<string, MultiTypeSet> MultiTypePair;
typedef set<MultiTypePair> PredicateSet;
typedef list<SenseAction> SenseActionList;
typedef list<OnticAction> OnticActionList;

struct Formula
{
	string label;
	Formula* left;
	Formula* right;
};

//观察动作的描述
struct SenseAction
{
    string name; // action name
    MultiTypeSet paras; // parameters
    Formula preCondition;
    Formula observe; //需要观察的“公式”
};

//物理动作中的effect（效果二元组）
struct Effect
{
    StringSet condition; //效果中的条件
    StringSet lits;  
};

//物理动作的描述
struct OnticAction
{
    string name; //动作的名称
    MultiTypeSet paras;
    Formula preConditions;
    EffectList effects; //效果二元组
};

#endif
