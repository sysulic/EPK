#ifndef DEFINE_H
#define DEFINE_H


#include <string>
#include <iostream>
#include <set>
#include <list>
#include <map>
#include <queue>
#include <vector>
#include <stack>

#include "EpisDNF.h"
#include "EpisCNF.h"
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
typedef pair<string, StringSet> SingleTypePair;
typedef set<SingleTypePair> MultiTypeSet;
typedef pair<string, MultiTypeSet> MultiTypePair;
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

//观察动作的描述 - for preprocessing
struct PreSenseAction
{
    string name; // action name
    MultiTypeSet paras; // parameters
    Formula preCondition;
    Formula observe; //需要观察的“公式”
};

//物理动作中的effect（效果二元组）- for preprocessing
struct Effect
{
    StringSet condition; //效果中的条件
    StringSet lits;  
};

//物理动作的描述 - for preprocessing
struct PreOnticAction
{
    string name; //动作的名称
    MultiTypeSet paras;
    Formula preConditions;
    EffectList effects; //效果二元组
};

/**************************************************
 **************  final structure  *****************
 **************************************************/
/*
//物理动作中的effect（效果三元组）
struct ConEffect
{
    vector<int> conditions; //效果中的条件!!!
    vector<int> lits; //add集合存储的变量代表做完该动作之后，这些变量需要变为True!!!
    
};

//物理动作的描述
struct OnticAction
{
    string name; //动作的名称!!!
    EpisCNF pre_con; //动作执行的前置条件!!!
    vector<ConEffect> con_eff; //效果二元组!!!
};

//观察动作的描述
struct EpisAction
{
    string name; //动作的名称!!!
    EpisCNF pre_con; //动作执行的前置条件!!!

    PropDNF pos_res; //将所需要观察的“公式”化为DNF形式， 为了好做演进 positive result !!!
    PropDNF neg_res; //将所需要观察的“公式”化为DNF形式， 为了好做演进 negative result !!!
};

//搜索算法中的结点
struct Node
{
    EpisDNF kb; //结点的知识库
    //下面两个变量分别是在搜索过程中所需要的两中标记
    STATE_TYPE flag;
    bool isolated;
    Node(){};
    Node(STATE_TYPE s, bool b, EpisDNF ed, int n){flag = s; isolated = b; kb = ed; }; //num = n;
    ~Node(){};
};

struct Transition
{
    int front_bdd_state; //前一个结点
    int next_bdd_state;  //后一个结点
    bool is_observe_action; //是否为观察动作
    bool is_true; //是否为感知动作的+
    int action_number;  //动作的编号
};


struct pre {
    vector<int> k;
    vector<vector<int> > dk; 
};

enum SearchType {
    kHeuristic = 0,
    kDepthFirst = 1,
    kWidthFirst = 2,
};
*/

#endif
