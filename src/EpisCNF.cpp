#include "define2.h"


bool PropClause::entails(const PropClause& prop_clause) const
{
    return literals.is_subset_of(prop_clause.literals);
}

PropTerm PropClause::negation() const
{   
    PropTerm result(length);
    if (is_true()) {
        result.literals.set();
        return result;
    }
    for (size_t i = 0; i < literals.size(); i++) {
        if(literals[i]) {
            if (i % 2 == 0) 
                result.literals[i + 1] = 1;
            else                    //this else is useless!!!
                result.literals[i - 1] = 1;
        }
    }
    return result;
}

bool PropClause::is_true() const
{
    return literals.count() == literals.size(); 
}

PropClause& PropClause::minimal()
{
    PropClause result(length);
    for (int i = 0; i < length; i += 2) {
        if (literals[i] && literals[i + 1]) {
            result.literals.set(); //This PropClause is true,
                                // we can use a dynamic_bitset whose bits are 1.
            break;
        }          
    }
    *this = result;
    return *this;
}

PropClause PropClause::group(const PropClause& prop_clause) const
{
    PropClause result(length);
    for (int i = 0; i < length; i++) {
        if (literals[i] || prop_clause.literals[i])
            result.literals[i] = 1;
    }
    return result;
}

PropCNF PropCNF::group(const PropCNF& propCNF) const
{
    if (! prop_clauses.empty() && ! propCNF.prop_clauses.empty()) {
        PropCNF result;
        for (list<PropClause>::const_iterator it_i = prop_clauses.begin();
            it_i != prop_clauses.end(); it_i++) {
            for (list<PropClause>::const_iterator it_j = propCNF.prop_clauses.begin();
                it_j != propCNF.prop_clauses.end(); it_j++) {
                result.prop_clauses.push_back(it_i->group(*it_j));
            }
        }
        return result;
    } else if (prop_clauses.empty()) {
        return propCNF;
    } else {
        return *this;
    }
}

void PropClause::show(ofstream & out, bool print_new_line) const
{
    vector<int> id_atoms;
    // 提取原子
    for (size_t i = 0; i < literals.size(); ++ i)
        if (literals[i])
            id_atoms.push_back(i);
    if (id_atoms.empty())
        return ;
    // 注意奇数为非
    out << "(" << (id_atoms[0] % 2 ? "~" : "") << atomsByIndex[id_atoms[0] / 2];
    for (size_t i = 1; i < id_atoms.size(); ++ i)
        out << " | " << (id_atoms[i] % 2 ? "~" : "") << atomsByIndex[id_atoms[i] / 2];
    out << ")";
    if (print_new_line)
        out << endl;
}

void PropCNF::show(ofstream & out, bool print_new_line) const
{
    if (prop_clauses.empty())
        return ;
    out << "( ";
    prop_clauses.begin()->show(out, false);
    for (list<PropClause>::const_iterator it = (++ prop_clauses.begin());
            it != prop_clauses.end(); ++ it) {
        out << " & ";
        it->show(out, false);
    }
    out << " )";
    if (print_new_line)
        out << endl;
}

void EpisClause::show(ofstream & out) const
{
    for (list<PropCNF>::const_iterator it = pos_propCNFs.begin();
            it != pos_propCNFs.end(); ++it) {
        out << "K";
        it->show(out);
    }
    if (! neg_propCNF.prop_clauses.empty()) {
        out << "~K~";
        neg_propCNF.show(out);
    }
}

PropDNF PropCNF::negation() const
{
    PropDNF result;
    for (list<PropClause>::const_iterator it = prop_clauses.begin(); it != prop_clauses.end(); ++it) {
        result.prop_terms.push_back(it->negation());
    }
    return result;	
}

//a |= b <=> !b |= !a, but I think this method is not right!
bool PropCNF::entails(PropCNF& propCNF)
{
    return propCNF.negation().entails(this->negation());
}

PropCNF& PropCNF::minimal()
{
    for (list<PropClause>::iterator pre_it = prop_clauses.begin();
            pre_it != prop_clauses.end(); ) {
        bool is_delete = false;
        for (list<PropClause>::iterator post_it = prop_clauses.begin();
                post_it != prop_clauses.end(); ++post_it) {
            if (pre_it != post_it && pre_it->entails(*post_it)) {
                is_delete = true;
                pre_it = prop_clauses.erase(pre_it);
                break;
            }
        }
        if (! is_delete)
            ++pre_it;
    }
    
    return *this;
}

EpisClause& EpisClause::separable()
{
    for (list<PropCNF>::iterator it = pos_propCNFs.begin();
            it != pos_propCNFs.end(); ++it) {
        if (!neg_propCNF.entails(*it))
            *it = it->group(neg_propCNF);
    }
    return *this;
}

EpisClause& EpisClause::minimal()
{
    separable();
   
    for (list<PropCNF>::iterator pre_it = pos_propCNFs.begin();
            pre_it != pos_propCNFs.end(); ++pre_it) {
        for (list<PropCNF>::iterator post_it = pos_propCNFs.begin();
                post_it != pos_propCNFs.end(); ) {
            if (pre_it != post_it && pre_it->entails(*post_it)) {
                list<PropCNF>::iterator delete_it = post_it;
                post_it++;
                pos_propCNFs.erase(delete_it);
            }
            else
                post_it++;
        }
    }
    
    neg_propCNF.minimal();
    for (list<PropCNF>::iterator it = pos_propCNFs.begin();
            it != pos_propCNFs.end(); ++it) 
        it->minimal();
    
    return *this;
}

EpisCNF& EpisCNF::minimal() {
    for (list<EpisClause>::iterator it = epis_clauses.begin();
        it != epis_clauses.end(); ++it)
        it->minimal();
    return *this;
}

void EpisCNF::show(ofstream & out) const
{
    int i = 0;
    for(list<EpisClause>::const_iterator it = epis_clauses.begin(); it != epis_clauses.end(); ++it) {
        out << "epis cnf " << i++ << endl;
        it->show(out);
        out << endl;
    }
}

