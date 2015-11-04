#ifndef PLAN_H
#define PLAN_H

#include "define.h"
#include "reader.h"
#include "timer.h"
#include "state.h"
#include "action.h"

/***********************************************************************
 Other classes used in Planner
************************************************************************/
typedef list<string> RawPlan;

/***********************************************************************
 Main class
************************************************************************/
class Planner 
{
  friend class State;
  friend class Action;
 public:
  /* input parameters */
  Semantics m_semantics;
  Task m_task;
  Algorithm m_algorithm;
  RawPlan m_plan;
  bool m_detect_essential;
  bool m_output_decisive;
  ActionList m_actions;         // action description
  ActionList m_sensings;		// sensing actions	  
  vector<Literals> m_gd;           // goal description, in CNF form:
  vector <boost::dynamic_bitset<> > m_goal_depend;
  boost::dynamic_bitset<> m_goal; // set of literals in the goal  
  boost::dynamic_bitset<> m_L;  // Literals in goals, preconditions of actions, and conditions of effects
  int m_depth;					// Depth of search tree
  int m_expanded;				// Number of expanded nodes
  int m_expanded_states;		// Total number of states of the expanded nodes
  int m_expanded_sum_state_size; // Total size of states of the expanded nodes

  map<CState*,int> m_commandNo;	// For printing solutions
protected:
  const Reader* m_reader;       // reader
  Timer* m_timer;               // timer
  
  string m_domain_name;         // domain name
  map<string,int> m_action_map; // action mapping
  map<string,int> m_sensing_map; // sensing action mapping
  Literals m_literals;          // fluent literals  
  //ActionList m_actions;         // action description
  StaticLaws m_statics;         // static laws
  CState m_init_cstate;         // init c-state
  //boost::dynamic_bitset<> m_goal; // set of literals in the goal  

  //set<Literals> m_gd;           // goal description, in CNF form:
                                // {(f ^ h ) v g} is represented as
                                // {{f,g},{h,g}}
  map<string,Literal> m_map;    // literal mapping

protected:
  /* for searching */
  vector<StateTable> m_states;   // state table (reached states)
  vector<CStateTable> m_cstates; // visited cstates
  PriorityCStateQueue m_queue; // current queue
  PriorityCStateQueue1 m_queue1; // current queue
  set<CState*> m_done;

 public:
  /* constructor and destructor */
  Planner(const Reader* reader, Timer* timer);
  virtual ~Planner();

  /* main function */
  bool main();

  /* generic functions */
  bool intersect(const Literals* x, const Literals* y) const;
  
  /* grounding functions */
  Literal ground(const string& x) const;
  Literals ground(const StringList* x) const;
  string convert(const Literal& x) const;
  StringList convert(const Literals& x) const;

  /* build the domain & check errors */
  bool build_domain();
  bool build_goal();    
  bool intersect(const boost::dynamic_bitset<>& S, const Literals& x);
  bool insert(boost::dynamic_bitset<>& S, const Literals& x);
  bool build_init();
  void print(const Node* node);
  unsigned long DNF_cost(const Node* node);
  unsigned long CNF_cost(const Node* node);
  bool timeout();
  bool DNF(const Node* node, list<boost::dynamic_bitset<> >& f);
  bool inconsistent(const boost::dynamic_bitset<>& s);
  bool annul(const list<boost::dynamic_bitset<> >& f, const list<boost::dynamic_bitset<> >& f1);
  void add_clause(list<boost::dynamic_bitset<> >& cs, const boost::dynamic_bitset<>& st);
  void merge(list<boost::dynamic_bitset<> >& lf, list<boost::dynamic_bitset<> >& rf, list<boost::dynamic_bitset<> >& f);


  Action* add_action(const string str);

  /* printing functions */
  void print_statistics() const;
  void print(const Literal& l) const;
  void print(const Literals& x) const;
  void print(const boost::dynamic_bitset<>& S) const;
  void print_interal_domain() const;
  void print_summary() const;

  /* functions used during the search */  
public:
  State* add_state(State* s);
  Literals negate(const Literals& x) const;  
  bool search();
  CState* first_unexpanded();
  bool expand(CState *cs);
  bool new_action_transition(CState* cs, const Action *act, CState* cs1);
  bool new_sensing_transition(CState* cs, const Action *act, CState* cs1, CState* cs2);
  void goal_propagate(CState* cs, CState* suc_goal);
  void goal_propagate(CState* cs, CState* suc_goal1, CState* suc_goal2);
  void dead_propagate(CState* cs);
  void isolation_propagate(CState* cs);
  void reconnection_propagate(CState* cs);



  bool execute();   // execute a plan and print out steps
  bool sat_value(State* s, const Effect& ef, Literals* st);
protected:  
  CState* next_cstate(CState* csin, const Action* act);
  bool add_state(CState* cs, CState* csout, set<State*>::iterator its, State* s);
  void split_effect(CState* cs, const Effect& ef, CState* csout);  
  void execute_effect(CState* csout, CState* cs);  
  bool explore_once();
};

#endif
