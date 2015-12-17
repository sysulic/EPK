#include "EpisDNF.h"
#include "atoms.h"
#include "Progression.h"
#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <fstream>

bool PropTerm::consistent() const
{
    for(int i = 0; i < Atoms::instance().atoms_length(); i++){
        if(literals[i * 2] && literals[i * 2 + 1] )
            return false;
    }
    return true;
}

bool PropTerm::entails(const PropTerm& prop_term) const
{
    if (!this->consistent()) //first PropTerm is false
        return true;
    return prop_term.literals.is_subset_of(literals);
}

bool PropTerm::equals(const PropTerm& prop_term)
{
    if (prop_term.literals == literals)
	return true;
    return false;
}

//This reasoning rule is Proposition 3.4 PropTerm |= PropClause
bool PropTerm::entails(const PropClause& prop_clause) const
{
    //I understood Proposition 3.4 means if the PropTerm and PropClause has only one same literal, 
    //then return true, otherwise return false
    for (int i = 0; i < Atoms::instance().atoms_length(); i++) {
        if ((literals[2 * i] && prop_clause.literals[2 * i]) || 
                (literals[2 * i + 1] && prop_clause.literals[2 * i + 1]))
            return true;
    }
    return false;
}

PropClause PropTerm::negation()
{
    PropClause result(Atoms::instance().atoms_length() * 2);
    for (size_t i = 0; i < literals.size(); i++) {
        if (literals[i]) {
            if (i % 2 == 0)
                result.literals[i + 1] = 1;
            else
                result.literals[i - 1] = 1;
        }
    }
    return result;
}   

PropTerm PropTerm::group(const PropTerm& prop_term) const
{
    PropTerm result(Atoms::instance().atoms_length() * 2);
    for (int i = 0; i < Atoms::instance().atoms_length() * 2; i++) {
        if (literals[i] || prop_term.literals[i])
            result.literals[i] = 1;
    }
    return result;
}

PropTerm& PropTerm::minimal()
{
    if (consistent())
        return *this;
    literals.set(); //inconsistent means this PropTerm is false, we can use a dynamic_bitset whose bits are 1.
    return *this;
}

list<PropTerm> PropTerm::ontic_prog(const OnticAction& ontic_action)
{
    list<PropTerm> progression; //Maybe need to make current PropTerm split into some PropTerms

    vector<int> missing_atom;
    vector<PropTerm> conditions; //convert each con in effect triple to PropTerm 
    for (size_t eff_i = 0; eff_i < ontic_action.con_eff.size(); eff_i++) {
        ConEffect cur_con_eff = ontic_action.con_eff[eff_i];  //current effect triple         
        //convert vector<int> to PropTerm
        PropTerm condition(Atoms::instance().atoms_length() * 2);
        for (size_t i = 0; i < cur_con_eff.condition.size(); i++) { //current size of condition is 1
            if (cur_con_eff.condition[i] > 0) 
                condition.literals.set((cur_con_eff.condition[i] - 1) * 2, true);
            else
                condition.literals.set((- cur_con_eff.condition[i] - 1) * 2 + 1, true);
        }
        conditions.push_back(condition);
        //check current PropTerm. Mostly, splitting is necessary 
        if (!(this->entails(condition) || this->entails(condition.negation()))) {            
            // 把condition里面出现，但this里面没有出现过的原子加入missing_atom里面
            for (int l = 1; l <= Atoms::instance().length; ++ l) {
                int pos = (l - 1) * 2;
                int neg = (l - 1) * 2 + 1;
                if (! this->literals[pos] && ! this->literals[neg] && 
                        (condition.literals[pos] || condition.literals[neg])) {
                    missing_atom.push_back(l);
                }
            }
        }
    }
    if (missing_atom.empty())
        progression.push_back(*this);
    else {
        list<PropTerm> splitting_result;
        PropTerm cur_propTerm = *this;
        split(missing_atom, 0, cur_propTerm, splitting_result);
        progression.insert(progression.end(), splitting_result.begin(), 
                splitting_result.end());
    }

    //begin ontic progression for each PropTerm (many PropTerms are split by current PropTerm)
    for (list<PropTerm>::iterator it = progression.begin(); it != progression.end(); it++) {
        PropTerm origin = *it;//保存没做之前的状态，用作判断条件
        for (size_t eff_i = 0; eff_i < ontic_action.con_eff.size(); eff_i++) {
            if (origin.entails(conditions[eff_i])) {
                // deal with the elements in the add set
                for (size_t add_i = 0; add_i < ontic_action.con_eff[eff_i].add.size(); add_i++) {
                    int pos_i = (ontic_action.con_eff[eff_i].add[add_i] - 1) * 2;
                    int neg_i = pos_i + 1;
                    if (it->literals[neg_i])
                        it->literals.set(neg_i, false);
                    it->literals.set(pos_i, true);
                }
                
                // deal with the elements in the del set
                for (size_t del_i = 0; del_i < ontic_action.con_eff[eff_i].del.size(); del_i++) {
                    int pos_i = (ontic_action.con_eff[eff_i].del[del_i] - 1) * 2;
                    int neg_i = pos_i + 1;
                    if (it->literals[pos_i])
                        it->literals.set(pos_i, false);
                    it->literals.set(neg_i, true);
                }
            }
        }
    }

    return progression;
}

void PropTerm::show(FILE *out, bool print_new_line) const
{
    vector<int> id_atoms;
    // 提取原子
    for (size_t i = 0; i < literals.size(); ++ i)
        if (literals[i])
            id_atoms.push_back(i);
    if (id_atoms.empty())
        return ;
    // 注意奇数为非
    fprintf(out, "(%s%s", (id_atoms[0] % 2 ? "~" : ""),
            Atoms::instance().get_atom_string(id_atoms[0] / 2 + 1).c_str());
    for (size_t i = 1; i < id_atoms.size(); ++ i)
        fprintf(out, " & %s%s", (id_atoms[i] % 2 ? "~" : ""),
                Atoms::instance().get_atom_string(id_atoms[i] / 2 + 1).c_str());
    fprintf(out, ")");
    if (print_new_line)
        fprintf(out, "\n");
}

void PropTerm::split(const vector<int>& missing_atom, const int index, PropTerm& cur_propTerm,
        list<PropTerm>& result) const {
    if (index >= static_cast<int>(missing_atom.size())) {
        result.push_back(cur_propTerm);
        return ;
    }
    // 处理正原子
    int pos = (missing_atom[index] - 1) * 2;
    cur_propTerm.literals[pos] = true;
    split(missing_atom, index + 1, cur_propTerm, result);
    cur_propTerm.literals[pos] = false;
    // 处理负原子
    int neg = (missing_atom[index] - 1) * 2 + 1;
    cur_propTerm.literals[neg] = true;
    split(missing_atom, index + 1, cur_propTerm, result);
    cur_propTerm.literals[neg] = false;
}

bool PropDNF::consistent() const
{
    for (list<PropTerm>::const_iterator it = prop_terms.begin(); it != prop_terms.end(); it++) {
        if (it->consistent())
            return true;
    }   
    return false;
}

bool PropDNF::entails(const PropDNF& propDNF) const
{ 
    //This reasoning rule is Proposition 3.6 DNF |= DNF
    for (list<PropTerm>::const_iterator pre_it = prop_terms.begin(); pre_it != prop_terms.end(); pre_it++) {
        bool can_entail = false;
        for (list<PropTerm>::const_iterator post_it = propDNF.prop_terms.begin(); post_it != propDNF.prop_terms.end(); post_it++) {
            if (pre_it->entails(*post_it)) {
                can_entail = true;
                break;
            }
        }
        if (! can_entail)
            return false;
    }
    return true;
}

bool PropDNF::equals(const PropDNF& propDNF)
{
    return this->entails(propDNF) && propDNF.entails(*this);
}

//This reasoning rule is Proposition 3.3 DNF |= CNF
bool PropDNF::entails(const PropCNF& propCNF) const
{
    for (list<PropTerm>::const_iterator pre_it = prop_terms.begin(); pre_it != prop_terms.end(); pre_it++) {
        for (list<PropClause>::const_iterator post_it = propCNF.prop_clauses.begin(); post_it != propCNF.prop_clauses.end(); post_it++) {
            if (!pre_it->entails(*post_it))
                return false;
        }
    }
    return true;
}

PropDNF PropDNF::group(const PropDNF& propDNF) const
{
    // 处理任意一边为空的情况
    if (! prop_terms.empty() && ! propDNF.prop_terms.empty()) {
        PropDNF result;
        for (list<PropTerm>::const_iterator it_i = prop_terms.begin(); it_i != prop_terms.end(); it_i++) {
            for (list<PropTerm>::const_iterator it_j = propDNF.prop_terms.begin(); it_j != propDNF.prop_terms.end(); it_j++) 
                result.prop_terms.push_back(it_i->group(*it_j));
        }
        //need to add min and PI method
        return result;
    }
    else if (prop_terms.empty())
        return propDNF;
    else
        return *this;
}

PropDNF& PropDNF::minimal()
{  
    // 删除非consistent
    for (list<PropTerm>::iterator it = prop_terms.begin();
            it != prop_terms.end(); ) {
        if (! it->consistent())
            it = prop_terms.erase(it);
        else 
            ++ it;
    }
    // 处理蕴含关系
    for (list<PropTerm>::iterator it_1 = prop_terms.begin(); it_1 != prop_terms.end(); ) {
        bool is_delete = false;
        for (list<PropTerm>::iterator it_2 = prop_terms.begin();
                it_2 != prop_terms.end(); ++ it_2) {
            if (it_1 != it_2 && it_1->entails(*it_2)) {
                is_delete = true;
                it_1 = prop_terms.erase(it_1);
                break;
            }
        }
        if (! is_delete)
            ++ it_1;
    }
    return *this;
}

PropDNF PropDNF::ontic_prog(const OnticAction& ontic_action)
{
    PropDNF result;
    for (list<PropTerm>::iterator it = prop_terms.begin(); it != prop_terms.end(); it++) {
        list<PropTerm> res = it->ontic_prog(ontic_action);
        result.prop_terms.insert(result.prop_terms.end(), res.begin(), res.end());
    }
    return result;
}

void PropDNF::convert_IPIA() {
    assert(false);
    assert(! prop_terms.empty());
    list<PropTerm>::const_iterator it = prop_terms.begin();
    list<PropTerm> pi;
    pi.push_back(*it);
    for (++ it; it != prop_terms.end(); ++ it) {
        // Algorithm 1: Incremental prime implicant algorithm
        PropTerm t = *it;
        list<PropTerm> segma;
        segma.push_back(t);
        // delete operation
        bool is_t_delete = delete_operation_in_IPIA(t, pi, segma);
        if (! is_t_delete) {
            list<PropTerm> new_to_segma;
            for (size_t l = 0; l < t.literals.size(); ++ l) {
                if (! t.literals.test(l)) {
                    continue;
                }
                // 存在 t'属于pi，t''属于segma，
                // 且 (l属于t') && (~l属于t'') || (~l属于t') && (l属于t'')
                size_t _l = (l % 2 == 0) ? l + 1 : l - 1;
                for (list<PropTerm>::iterator it_pi = pi.begin();
                        it_pi != pi.end(); ++ it_pi) {
                    for (list<PropTerm>::iterator it_segma = segma.begin();
                            it_segma != segma.end(); ++ it_segma) {
                        if ((it_pi->literals.test(l) && it_segma->literals.test(_l)) ||
                                (it_pi->literals.test(_l) && it_segma->literals.test(l))) {
                            // t* = term(t', t'', l);
                            PropTerm tx = *it_pi;
                            tx.literals |= it_segma->literals;
                            tx.literals.reset(l);
                            tx.literals.reset(_l);
                            // segma = segma \cup {t*}
                            if (tx.consistent()) 
                                new_to_segma.push_back(tx);
                        }
                    }
                }
            }
            segma.insert(segma.end(), new_to_segma.begin(), new_to_segma.end());
            // delete operation，需要保证没有重复的元素
            delete_operation_in_IPIA(t, pi, segma);
        }
        // pi = pi \cup segma, update it for the next iteration
        pi.insert(pi.end(), segma.begin(), segma.end());
    }
    prop_terms = pi;
}
// 
bool PropDNF::delete_operation_in_IPIA(const PropTerm &t, list<PropTerm> &pi, 
        list<PropTerm> &segma) {
    list<PropTerm> segma_tmp = segma;
    // 处理pi
    for (list<PropTerm>::iterator it = pi.begin(); it != pi.end(); ) {
        bool is_delete = false;
        for (list<PropTerm>::const_iterator it_segma = segma_tmp.begin();
                (! is_delete) && (it_segma != segma_tmp.end()); ++ it_segma) {
            if (it->entails(*it_segma)) {
                is_delete = true;
                it = pi.erase(it);
            }
        }
        if (! is_delete)
            ++ it;
    }
    // 处理segma
    bool is_t_delete = false;
    for (list<PropTerm>::iterator it = segma.begin(); it != segma.end(); ) {
        bool is_delete = false;
        for (list<PropTerm>::const_iterator it_pi = pi.begin();
                (! is_delete) && (it_pi != pi.end()); ++ it_pi) {
            if (it->entails(*it_pi)) {
                is_delete = true;
                if (it->equals(t))
                    is_t_delete = true;
                it = segma.erase(it);
            }
        }
        if (! is_delete)
            ++ it;
    }
    return is_t_delete;
}

void PropDNF::show(FILE *out, bool print_new_line) const 
{
    if (prop_terms.empty())
        return ;
    fprintf(out, "( ");
    prop_terms.begin()->show(out, false);
    for (list<PropTerm>::const_iterator it = (++ prop_terms.begin());
            it != prop_terms.end(); ++ it) {
        fprintf(out, " | ");
        it->show(out, false);
    }
    fprintf(out, " )");
    if (print_new_line)
        fprintf(out, "\n");
}

bool EpisTerm::consistent() const
{
    if (!pos_propDNF.consistent())
        return false;
    else {
        for (list<PropDNF>::const_iterator it = neg_propDNFs.begin(); it != neg_propDNFs.end(); it++) {
            if (!it->consistent())
                return false;
        }
        return true;
    }
}

//This reasoning rule is Proposition 3.5
bool EpisTerm::entails(const EpisTerm& epis_term) const
{
    if (!pos_propDNF.entails(epis_term.pos_propDNF))
        return false;
    else {
        //The following is the first case of rule 2 in Proposition 3.5
        int count = 0; //The pos_propDNF of first EpisTerm can entail how many DNF in neg_propDNFs of second EpisTerm
        for (list<PropDNF>::const_iterator post_it = epis_term.neg_propDNFs.begin(); post_it != epis_term.neg_propDNFs.end(); post_it++) {
            if (pos_propDNF.entails(*post_it))
                count++;
            else 
                break;
        }
        if (count == static_cast<int>(epis_term.neg_propDNFs.size()))
            return true;
        
        //The following is the second case of rule 2 in Proposition 3.5
	for (list<PropDNF>::const_iterator post_it = epis_term.neg_propDNFs.begin(); post_it != epis_term.neg_propDNFs.end(); post_it++) {
            bool can_entail = false;
            for (list<PropDNF>::const_iterator pre_it = neg_propDNFs.begin(); pre_it != neg_propDNFs.end(); pre_it++) {
                if (pre_it->entails(*post_it)) {
                    can_entail = true;
                    break;
                }
	    }		
            if (!can_entail)
                return false;           
        }		
        return true;
    }
}

bool EpisTerm::equals(const EpisTerm& epis_term)
{
    return this->entails(epis_term) && epis_term.entails(*this);
}

//This reasoning is Proposition 3.2 EpisTerm |= EpisClause
bool EpisTerm::entails(const EpisClause& epis_clause) const
{
    //case 1 of Proposition 3.2
    PropDNF ec_neg_tmp = epis_clause.neg_propCNF.negation();
    if (!pos_propDNF.group(ec_neg_tmp).consistent())
        return true;
    
    //case 2 of Proposition 3.2
    for (list<PropDNF>::const_iterator it = neg_propDNFs.begin(); it != neg_propDNFs.end(); it++) {
        if (!it->group(ec_neg_tmp).consistent())
            return true;
    }
    
    //case 3 of Proposition 3.2
    for (list<PropCNF>::const_iterator it = epis_clause.pos_propCNFs.begin(); it != epis_clause.pos_propCNFs.end(); it++) {
        if (!pos_propDNF.group(it->negation()).consistent())
            return true;
    }
    
    return false;
}

EpisTerm& EpisTerm::minimal()
{    
    //For an EpisTerm, we need each \eta_i can entail \psi;
    separable();
    
    //For an EpisTerm, possible parts can't entail each other
    for (list<PropDNF>::iterator pre_it = neg_propDNFs.begin(); pre_it != neg_propDNFs.end(); pre_it++) {
        for (list<PropDNF>::iterator post_it = neg_propDNFs.begin(); post_it != neg_propDNFs.end(); ) {
            if (pre_it != post_it && pre_it->entails(*post_it)) {
                list<PropDNF>::iterator delete_it = post_it;
                post_it++;
                neg_propDNFs.erase(delete_it);
            }
            else
                post_it++;
        }
    } 
    
    //For an EpisTerm, we need that \psi and each \eta_i are minimal 
    pos_propDNF.minimal();
    for (list<PropDNF>::iterator it = neg_propDNFs.begin(); it != neg_propDNFs.end(); it++)
        it->minimal();
          
    return *this;
}

EpisTerm& EpisTerm::separable()
{
    for (list<PropDNF>::iterator it = neg_propDNFs.begin(); it != neg_propDNFs.end(); it++) {
        if (!it->entails(pos_propDNF)) 
            *it = it->group(pos_propDNF);
    }
    return *this;
}

void EpisTerm::show(FILE *out) const
{ 
    fprintf(out, "K");
    pos_propDNF.show(out);
    for (list<PropDNF>::const_iterator it = neg_propDNFs.begin();
            it != neg_propDNFs.end(); ++ it) {
        fprintf(out, "~K~");
        it->show(out);
    }
}


void EpisTerm::convert_IPIA() {
    if (! pos_propDNF.prop_terms.empty())
        pos_propDNF.convert_IPIA();
    for (list<PropDNF>::iterator it = neg_propDNFs.begin();
            it != neg_propDNFs.end(); ++ it) {
        it->convert_IPIA();
    }
}

EpisTerm EpisTerm::ontic_prog(const OnticAction& ontic_action)
{
    EpisTerm result;
    result.pos_propDNF = pos_propDNF.ontic_prog(ontic_action);
    for (list<PropDNF>::iterator it = neg_propDNFs.begin(); it != neg_propDNFs.end(); it++)
        result.neg_propDNFs.push_back(it->ontic_prog(ontic_action));
    return result;
}

//This method is based on Proposition 3.7, and it is a basis of method equals
bool EpisDNF::entails(const EpisDNF& episDNF) const
{	
    for (list<EpisTerm>::const_iterator pre_it  = epis_terms.begin(); pre_it != epis_terms.end(); pre_it++) {
        bool can_entail = false;
        for (list<EpisTerm>::const_iterator post_it = episDNF.epis_terms.begin(); post_it != episDNF.epis_terms.end(); post_it++) {
            if (pre_it->entails(*post_it)) {
                can_entail = true;
                break;
            }
        }
        if (!can_entail)
            return false;
    }
    return true;
}


//This reasoning rule is Proposition 3.7 EDNF |= ENDF
bool EpisDNF::equals(const EpisDNF& episDNF)
{
    return this->entails(episDNF) && episDNF.entails(*this);
}

//This method is Propposition 3.1 EpisDNF |= EpisCNF
bool EpisDNF::entails(const EpisCNF& episCNF) const {
    for (list<EpisTerm>::const_iterator pre_it = epis_terms.begin(); pre_it != epis_terms.end(); pre_it++) {
        for (list<EpisClause>::const_iterator post_it = episCNF.epis_clauses.begin(); post_it != episCNF.epis_clauses.end(); post_it++) {
            if (!pre_it->entails(*post_it))
                return false;
        }
    }
    return true;
}

EpisDNF& EpisDNF::minimal()
{
    for (list<EpisTerm>::iterator it = epis_terms.begin(); it != epis_terms.end(); it++)
        it-> minimal();
    return *this;
}

EpisDNF EpisDNF::ontic_prog(const OnticAction& ontic_action)
{
    EpisDNF result;
    for (list<EpisTerm>::iterator it = epis_terms.begin(); it != epis_terms.end(); it++) {
        result.epis_terms.push_back(it->ontic_prog(ontic_action));
    }
    result.minimal();
    return result;
}

vector<EpisDNF> EpisDNF::epistemic_prog(const EpisAction& epis_action)
{
    EpisDNF p_episDNF;
    EpisDNF n_episDNF;

    for (list<EpisTerm>::iterator it = epis_terms.begin(); it != epis_terms.end(); it++) {
        EpisTerm p_epis_term;
        EpisTerm n_epis_term;
        
        //For the K part of an EpisTerm
        p_epis_term.pos_propDNF = it->pos_propDNF.group(epis_action.pos_res);
        n_epis_term.pos_propDNF = it->pos_propDNF.group(epis_action.neg_res);
        
        //For the K^ part of an EpisTerm
        for (list<PropDNF>::iterator propDNF_it = it->neg_propDNFs.begin(); propDNF_it != it->neg_propDNFs.end(); propDNF_it++) {
            if (propDNF_it->entails(epis_action.pos_res))
                p_epis_term.neg_propDNFs.push_back(*propDNF_it);
            if (propDNF_it->entails(epis_action.neg_res))
                n_epis_term.neg_propDNFs.push_back(*propDNF_it);
        }
	p_episDNF.epis_terms.push_back(p_epis_term);
	n_episDNF.epis_terms.push_back(n_epis_term);  
    }    
    vector<EpisDNF> result;
    p_episDNF.minimal();
    result.push_back(p_episDNF);
    n_episDNF.minimal();
    result.push_back(n_episDNF);
    return result;
}

void EpisDNF::show(FILE *out) const
{ 
    int i = 0;
    for (list<EpisTerm>::const_iterator it = epis_terms.begin();
            it != epis_terms.end(); ++ it) {
        fprintf(out, "epis term %d:\n", i ++);
        it->show(out);
        fprintf(out, "\n");
    }
}

void EpisDNF::convert_IPIA() {
    for (list<EpisTerm>::iterator it = epis_terms.begin();
            it != epis_terms.end(); ++ it) {
        it->convert_IPIA();
    }
}
