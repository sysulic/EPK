#ifndef ACTION_H
#define ACTION_H

#include "define.h"
#include "state.h"

class Planner;

/***********************************************************************
 class: Action
************************************************************************/
class Action {
 protected:
  const Planner* m_planner;
  string m_name;          // action name
  ExecList m_execs;       // executability conditions
  EffectList m_effects;   // conditional effects
  ExecList m_imposs;      // impossibility conditions
  Literals m_EF;		  // union of heads of effects  
  set<Action*> m_independents; //set of independent actions or sensings

 public:
  /* constructor & destructor */
  Action(const Planner* planner, const string& name);
  ~Action();

  bool m_sensing;		  // True for sensing action

  /* get/set functions */
  string get_name() const;
  void set_name(const string& name);
  void add_independent(Action* a);
  bool is_independent(Action* a) const;

  const EffectList* get_effects() const;
  const Literal lit() const; //Return the literal of a sensing action
  const ExecList* get_execs() const;
  const ExecList* get_imposs() const;

  void add_exec(const Literals ex);
  void add_imposs(const Literals imp);
  void add_effect(const Literals hd, const Literals bd);

  /* main functions */
  bool is_executable(const State* s) const;
  bool is_executable(const Literals* s) const;  
  bool noEffectIn(const boost::dynamic_bitset<>& L) const;
  bool is_executable(const boost::dynamic_bitset<>& L) const;  
  bool pre(const boost::dynamic_bitset<>& L, Literals* st) const;
  bool is_executable(const CState* cs) const;
  bool is_executable(const set<State*>* cs) const;
  void print() const;
};

typedef vector<Action> ActionList;
typedef vector<Action*> pActionList;

#endif
