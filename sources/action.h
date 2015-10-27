#ifndef ACTION_H
#define ACTION_H

//观察动作的描述
struct SensingAction
{
    string name; //动作的名称
    int num; //动作的编号
    EpisCNF pre_con; //动作执行的前置条件
    vector<set<int> > observe; //需要观察的“公式”
    vector<string> para_match;

    PropDNF pos_res; //将所需要观察的“公式”化为DNF形式， 为了好做演进 positive result
    PropDNF neg_res; //将所需要观察的“公式”化为DNF形式， 为了好做演进 negative result  
};

//物理动作中的effect（效果二元组）
struct ConEffect
{
    vector<int> condition; //效果中的条件
    vector<int> lits;
    // vector<int> add; //add集合存储的变量代表做完该动作之后，这些变量需要变为True
    // vector<int> del; //del集合存储的变量代表做完该动作之后，这些变量需要变为False
    
};

//物理动作的描述
struct OnticAction
{
    string name; //动作的名称
    int num; //动作的编号
    EpisCNF pre_con; //动作执行的前置条件
    vector<ConEffect> con_eff; //效果三元组
    vector<PropTerm> con; //use it to replace vector<int> condition
    vector<string> para_match;
};

#endif ACTION_H
