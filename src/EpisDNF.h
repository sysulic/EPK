#ifndef EPISDNF_H
#define	EPISDNF_H

#include <boost/dynamic_bitset.hpp>
#include "define2.h"
#include "EpisCNF.h"

using namespace std; 

struct OnticAction;
struct EpisAction;
class PropClause;
class PropCNF;
class EpisClause;
class EpisCNF;

class PropTerm {
public:
    PropTerm(size_t len) { literals.resize(length = len); }
    PropTerm() {}
    ~PropTerm() {}
    bool consistent() const; //判断该命题项是否一致
    bool entails(const PropTerm &) const; //判断该命题项能够推出另外一个命题项
    bool entails(const PropClause &) const; //judge whether a PropTerm entails a PropClause or not
    bool equals(const PropTerm &);  //判断两个命题项是否等价
    PropTerm group(const PropTerm &) const; //merge two PropTerms
    PropClause negation(); //this function is used to judge ontic progression
    PropTerm& minimal(); //化简命题项，在这里其实就是若该命题项中同时出现一个原子的正负文字两个方面，那么该命题项就是False
    boost::dynamic_bitset<> literals;  //一个原子对应两位，那两位分别表示该原子构成的正文字和负文字
    size_t length;
    void show(ofstream & out) const;
    list<PropTerm> ontic_prog(const OnticAction &ontic_action); //在当前PropTerm上做物理动作的演进，并且返回演进结果
    void split(const vector<int> &missing_atom, const int index, 
                PropTerm& cur_propTerm, list<PropTerm>& result) const;//物理动作的裂项的辅助函数
};


class PropDNF {
public:
    bool consistent() const; //判断该命题DNF是否一致
    bool entails(const PropDNF &) const; //判断该命题DNF是否可以推出另外一个命题DNF
    bool equals(const PropDNF &); //判断两个命题DNF是否等价
    bool entails(const PropCNF &) const; //judge whether a PropDNF entails a PropDNF or not
    PropDNF& minimal(); //化简命题DNF，即若PropTerm1能够推出PropTerm2， 则从prop_terms中把PropTerm1删除
    PropDNF group(const PropDNF &) const; //merge two PropDNF
    void show(ofstream & out) const;
    list<PropTerm> prop_terms; //存储了多个命题项，这就构成了命题层面的DNF
    PropDNF ontic_prog(const OnticAction &ontic_action); //在当前PropDNF上做物理动作的演进，并且返回演进结果
    void convert_IPIA(); //将DNF转为质蕴含形式
    bool delete_operation_in_IPIA(const PropTerm &t, list<PropTerm> &pi, 
                list<PropTerm> &segma);
};

//认知项的形式为：一个K和若干个K^的合取，需要注意若干个K的合取可以合成变为一个K
class EpisTerm {
public:
    PropDNF pos_propDNF;    //认知项的K部分，注意只有一个
    list<PropDNF> neg_propDNFs; //认知项的K^部分，注意有若干个，当然也可以为空
    bool consistent() const; //判断该认知项是否一致
    bool entails(const EpisTerm &) const;    //判断该认知项能否够推出另外一个认知项
    bool equals(const EpisTerm &); //判断两个认知项是否等价
    bool entails(const EpisClause &) const; //judge whether an EpisTerm entails an EpisClause or not
    EpisTerm& minimal(); //化简认知项，即若K^1 |= K^2, 则删除K^2
    EpisTerm& separable();
    void show(ofstream & out) const;
    EpisTerm ontic_prog(const OnticAction &ontic_action); //在当前EpisTerm上做物理动作的演进，并且返回演进结果
    void convert_IPIA();
};

//其实就是认知项的析取，这个数据结构是用来存储知识库的
class EpisDNF {
public:
    list<EpisTerm> epis_terms;  //存储若干个认知项
    bool consistent() const; //判断认知项的析取是否一致 
    bool entails(const EpisDNF &) const; //判断一个知识库能够推出另一个知识库
    bool equals(const EpisDNF &); //判断两个知识库是否等价
    bool entails(const EpisCNF&) const; //判断该知识库能够推出某个动作的前置条件
    EpisDNF& minimal(); //对EpisDNF的化简，剔除冗余知识
    void show(ofstream & out) const;
    EpisDNF ontic_prog(const OnticAction &ontic_action); //在当前知识库上做物理动作的演进，并且返回演进结果
    vector<EpisDNF> epistemic_prog(const EpisAction &epis_action); //在当前知识库上做观察动作的演进，并且返回结果
    void convert_IPIA();
};


#endif	/* EPISDNF_H */
