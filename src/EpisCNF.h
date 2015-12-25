#ifndef EPISCNF_H
#define	EPISCNF_H

#include <boost/dynamic_bitset.hpp>
#include "define2.h"
#include "EpisDNF.h"

using namespace std;

struct OnticAction;
struct EpisAction;
class PropTerm;
class PropDNF;

//以下4个数据结构完全和PropTerm、PropDNF、EpisTerm、EpisDNF对应
class PropClause
{
public:
    PropClause(int len) { literals.resize(length = len); }
    PropClause() {}
    ~PropClause() {}
    PropTerm negation() const; //求出该命题子句的否定，结果就变成了一个命题项
    bool entails(const PropClause &) const;
    PropClause group(const PropClause &) const;
    bool is_true() const;
    PropClause& minimal(); //对于PropClause的化简，就是如果出现一个原子的正负文字，则为True
    size_t length;
    boost::dynamic_bitset<> literals;
    void show(ofstream & out) const;
};
  

class PropCNF
{
public:
    PropCNF group(const PropCNF &) const;
    PropDNF negation() const;
    PropCNF& minimal();
    bool entails(PropCNF& propCNF);
    list<PropClause> prop_clauses;
    void show(ofstream & out) const;
};

//认知子句的形式为：一个K^和若干个K的析取，需要注意若干个K^的析取可以合成变为一个K^
class EpisClause
{
public:
    void min();//把neg后面合成一个
    EpisClause& minimal();
    EpisClause& separable();
    bool entails(const EpisClause&); //Doctor Fang has not given this reasoning rule
    list<PropCNF> pos_propCNFs; //认知子句的K部分，有若干个，当然可以一个都没有
    list<PropCNF> neg_propCNFs; //认知子句的K^部分，注意只有一个
    PropCNF neg_propCNF; //认知子句的K^部分，注意只有一个
    void show(ofstream & out) const;
};

//认知子句的合取，其实就是所有动作(包括物理动作和观察动作)的前置条件
class EpisCNF {
public:
    EpisCNF();
    list<EpisClause> epis_clauses;
    void show(ofstream & out) const;
};

#endif	/* EPISCNF_H */

