/* 
 * File:   define2.h
 * Author: Frank
 *
 * Created on 2015年12月19日, 下午9:24
 */

#ifndef DEFINE2_H
#define	DEFINE2_H

#include "define.h"
#include "EpisCNF.h"
#include "EpisDNF.h"


//物理动作中的effect（效果二元组）
struct ConEffect
{
    vector<int> condition; //效果中的条件
    vector<int> lits; //add集合存储的变量代表做完该动作之后，这些变量需要变为True
    
};

//物理动作的描述
struct OnticAction
{
    string name; //动作的名称
    EpisCNF pre_con; //动作执行的前置条件
    vector<ConEffect> con_eff; //效果二元组
};

//观察动作的描述
struct EpisAction
{
    string name; //动作的名称
    EpisCNF pre_con; //动作执行的前置条件

    PropDNF pos_res; //将所需要观察的“公式”化为DNF形式， 为了好做演进 positive result
    //PropDNF neg_res; //将所需要观察的“公式”化为DNF形式， 为了好做演进 negative result
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
    int front_state; //前一个结点
    int next_state;  //后一个结点
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


#endif	/* DEFINE2_H */

