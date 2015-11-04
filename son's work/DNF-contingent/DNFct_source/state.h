#ifndef STATE_H
#define STATE_H

#include "define.h"

class Planner;
class Action;
typedef vector<Action> ActionList;
typedef vector<Action*> pActionList;

/***********************************************************************
 Types -- Domain Description
************************************************************************/
class Effect {
 protected:
  Literals m_head;
  Literals m_body;
  bool m_nondet;
  //Literals m_neg_body; // negation of the body
 public:
  Effect();
  ~Effect();

  void set_body(Literals bd);
  void set_head(Literals hd);
  bool nondet() const;
  const Literals* get_body() const;  
  const Literals* get_head() const;
};

typedef list<Effect> EffectList;
typedef list<Literals> ExecList;

typedef Effect StaticLaw;
typedef list<StaticLaw> StaticLaws;

class StateH
{
public:
  boost::dynamic_bitset<> m_L; //Set of Literals
  Literals m_EF;
  StateH* pre;

  StateH(boost::dynamic_bitset<>& L);
  ~StateH();
  
  /* operators */ 
  int operator<(const StateH&) const;
  bool operator==(const StateH&) const;
  StateH operator=(const StateH& s);
  
  /* other functions */  
  bool includes(const boost::dynamic_bitset<>& x) const;  
  bool includes(const StateH* s) const;
  bool satisfies(const Literals* x) const;
  bool will_include(const Literals* x, const boost::dynamic_bitset<>& L) const;
  void insert(const Literals& x);
  bool intersect(const boost::dynamic_bitset<>& x) const;
};


class State
{
public:
  boost::dynamic_bitset<> m_L; //Set of Literals
  Literals m_EF;
  Literals m_nondet_EF;

  Planner* m_planner;
  boost::dynamic_bitset<> m_gd_sat;
  bool m_allocated;

protected:  
  int m_hvalue;     // heuristic value
  int m_gsatisfied; // -1: not computed; 0 : not satisfied; 1: satisfied
  int m_hash;  

public:
  State(Planner* planner);
  ~State();

  /* operators */
  void clear();
  int operator<(const State&) const;
  bool operator==(const State&) const;
  State operator=(const State& s);
  bool intersect(const Literals* x) const;
  bool intersect(const boost::dynamic_bitset<>& x) const;
  bool intersect(const State* s) const;  
  bool includes(const Literals* x) const;
  bool includes(const boost::dynamic_bitset<>& x) const;
  bool includes(const State* s) const;
 

  /* other functions */
  bool is_consistent() const;
  int hvalue();
  int hgvalue();  
  int hash();
  bool goal_satisfied();  
  bool satisfies(const Literals* x);
  bool satisfies(const Literal l);
  void insert(const Literals& x);
  void print() const;
};

class StateComp
{
 public:
  int operator()(const State* s1, const State* s2) const {
    return *s1 < *s2;
  }
};

typedef set<State*,StateComp> StateTable;

class CState {
  friend class PriotizedCState;
  friend class CStateComp;
 public:
  set<State*> m_states;  
  short m_status;
    
  map<CState*, const Action*> m_in_transitions; //Incomming transitions
  int m_active_in_transitions; // Incoming transitions not be goal_propagated
  vector<CState*> m_successors; //successor nodes obtained by sensing  
  int m_depth;   // length of the plan  

protected:
  int m_hvalue;        // heuristic value, -1 if not computed  
  int m_hcvalue;
  int m_hgvalue;
  int m_graph_heuristic;
  
  

public:
  /* constructor and destructor */
  CState();
  ~CState();

  void clear();
  bool operator<(const CState& right) const;
  CState operator=(const CState& s);
  void copy(const CState& cs);    
  bool decides(const Literal l);
  bool split(CState* cs1, CState* cs2, const Literal l);
  bool goal_satisfied();
  int hgvalue();
  int hcvalue(boost::dynamic_bitset<>* L);  
  int hcvalue(); 
  int hvalue();
  int graph_heuristic();  
  bool graph_build(vector<pActionList >* pA, vector<boost::dynamic_bitset<> >* pL, vector<vector<StateH*> >* pS);
  int plan_extract(vector<pActionList >* pA, vector<boost::dynamic_bitset<> >* pL, vector<vector<StateH*> >* pS);
  int hash();

  int get_depth() const;
  void set_depth(const int& len);
    
  const Action* get_action(CState* cs);
  bool is_successor(CState* cs, const Action* act);
  int propagatable_transitions();
  bool is_better(CState* cs);  

  /* other functions */
  void print() const;  
  void solution_print(Planner* planner, const int level);
  void solution_not_print(Planner* planner, const int level);
  void depth_propagate(Planner* planner);
};

class CStateComp
{
 public:
  int operator()(const CState* cs1, const CState* cs2) const {
    return *cs1 < *cs2;
  }
};

typedef set<CState*,CStateComp> CStateTable;

// Friend class with function object for comparison of cnodes
class PriotizedCState1 {
public :
  int operator()(CState* cs1, CState* cs2) const
  {	

	  if (cs1->hvalue() == cs2->hvalue()) {
			if (cs1->m_states.size() == cs2->m_states.size())			
				return cs1->hgvalue() > cs2->hgvalue();
			return cs1->m_states.size() >= cs2->m_states.size();
	  }
	  
	  return cs1->hvalue() < cs2->hvalue();

	/*	  
	if (cs1->graph_heuristic() == cs2->graph_heuristic()) {
		if (cs1->hvalue() == cs2->hvalue())		  
			return cs1->m_states.size() > cs2->m_states.size();		 
		return cs1->hvalue() < cs2->hvalue();		  			 
	}
	return cs1->graph_heuristic() > cs2->graph_heuristic();
	*/	  
  }
};

class PriotizedCState {
public :
  int operator()(CState* cs1, CState* cs2) const
  {	
	  if (cs1->hvalue() == cs2->hvalue())
		  return cs1->hcvalue() < cs2->hcvalue();
	  return cs1->hvalue() < cs2->hvalue();
  }
};

bool goal_satisfies(const boost::dynamic_bitset<>& L, const vector<StateH*>& S, const vector<Literals>& goal);
void exec_actions(ActionList& p_actions, vector<pActionList>* pA, const boost::dynamic_bitset<>& L);
void build_layer(const int t, const pActionList* p_actions, vector<boost::dynamic_bitset<> >* pL, vector<vector<StateH*> >* pS);
bool includes(const boost::dynamic_bitset<>& L, const Literals& x);
bool intersects(const boost::dynamic_bitset<>& L, const Literals& x);
void add(boost::dynamic_bitset<>* pL, const Literals* s);
bool add_set(const vector<StateH*>& S, const int i, const int size, StateH& s, set<StateH*>* S1);
void split_effect(vector<StateH*> *S, const boost::dynamic_bitset<>& L, const Effect& ef);
bool sat_value(StateH* s, const boost::dynamic_bitset<>& L, const Effect& ef, Literals* st);
void execute_effect(vector<StateH*>* S, boost::dynamic_bitset<>* L);
void free_graph(vector<vector<StateH*> >* pS);

bool goal_Satisfied(set<State*>* cs);
void print_set(const Literals& S);
void print_set(const boost::dynamic_bitset<>& L);
void print_literal(const Literal l);



typedef priority_queue<CState*,vector<CState*>,PriotizedCState> PriorityCStateQueue;
typedef priority_queue<CState*,vector<CState*>,PriotizedCState1> PriorityCStateQueue1;
#endif
