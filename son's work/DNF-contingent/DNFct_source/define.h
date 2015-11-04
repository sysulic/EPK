#ifndef DEFINE_H
#define DEFINE_H

#include <string>
#include <string.h>
#include <iostream>
#include <set>
#include <list>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include <sys/resource.h>
#include <boost/dynamic_bitset.hpp>
#include <math.h>
#include <cstdio>

using namespace std;

#define HASH_SIZE 16384
#define HASH_BITS 16383

#define DEBUG

#define PRINT_TIME_DETAILS
//#define PRINT_DOMAIN
//#define PRINT_INTERAL_DOMAIN
//#define PRINT_SUMMARY
//#define PRINT_PICKUP_NODE
//#define PRINT_LOOKUP_TABLE


#ifdef PRINT_PICKUP_NODE
#define PRINT_MAPPING
#endif

#ifdef PRINT_LOOKUP_TABLE
#define PRINT_MAPPING
#endif

#ifdef PRINT_TIME_DETAILS 
#define RESUME_TIMER(x) m_timer->start(x) 
#define PAUSE_TIMER(x) m_timer->end(x) 
#else
#define RESUME_TIMER(x) m_timer->end(x) 
#define PAUSE_TIMER(x)
#endif

//#define USE_GOAL_LOOKUP
//#define USE_TRANSITION_LOOKUP
//#define USE_HEURISTIC_LOOKUP
#define UPDATE_SHORTER_PLAN

/***********************************************************************
 Do not change the following
************************************************************************/

class Action;
class Domain;

#define NEGATE(l,x) (x = ((l % 2 == 0) ? l+1 : l-1))

/***********************************************************************
 Constants
************************************************************************/
#define NEGATION_SYMBOL "-"

// maximum fluent/action name length
#define MAX_LEN 200

#define ERROR_001 "Invalid fluent/literal. Check the fluent declaration"
#define ERROR_002 ""
#define ERROR_003 ""
#define ERROR_004 ""

enum Algorithm {
  GREEDY
};

enum Semantics {
  PC,
  PH
};

enum Task {
  SEARCH,
  DOPLAN
};

// timers
#define READ_TIMER 0
#define BUILD_TIMER 1
#define SEARCH_TIMER 2
#define GOAL_TIMER 3
#define HEURISTIC_TIMER 4
#define RESULT_TIMER 5
#define TRANSITION_LOOKUP_TIMER 6
#define EXECUTABILITY_TIMER 7
#define ACTUAL_RESULT_TIMER 8
#define DIRECT_EFFECT_TIMER 9
#define INDIRECT_EFFECT_TIMER 10
#define IDLE_TIMER 11
#define NEXTSTATE_TIMER 12
#define COMMUNICATION_TIMER 13
#define ESSENTIAL_FLUENTS_TIMER 14
#define UNEXPANDED 15 
#define EXPANDED 16
#define GOAL_REACHABLE 17
#define ISOLATED 18
#define OUT_ISOLATED 19
#define DEAD 20



/***********************************************************************
 Types -- For scanner & parser
************************************************************************/
// for scanner & parser
typedef set<string> StringList;
typedef set<StringList> StringList2;

enum PropositionType {
  STATIC,
  DYNAMIC,
  EXECUTABILITY,
  IMPOSSIBILITY
};

typedef int Fluent;
typedef set<Fluent> Fluents;

// literals
typedef unsigned short Literal;

#define FALSE 65534
#define TRUE 65535
#define INFINITY 65535

// set of literals and states
typedef set<Literal> Literals;

class Node {
public:
	string label;
	Node* left;
	Node* right;
};

class Proposition {
 public:
  PropositionType n_type;
  string act_name;
  StringList precond;
  StringList effect;
  
  const StringList* get_precondition() const{
    return &precond;
  };

  const StringList* get_effect() const {
    return &effect;
  };

  void print() const {
    bool first = true;
    StringList::const_iterator it;

    switch (n_type) {
    case DYNAMIC:
      cout << act_name << " causes ";
      break;
    case EXECUTABILITY:
      cout << "executable " << act_name << " ";
      break;
    case IMPOSSIBILITY: 
      cout << "impossible " << act_name << " ";
      break;
    default: /* static */
      break;
    }

    for (it = effect.begin(); it != effect.end(); it++) {
      if (!first)
	cout << ",";
      first = false;
      cout << *it; 
    }
    
    first = true;
    for (it = precond.begin(); it != precond.end(); it++) {
      if (!first)
	cout << ",";
      else
	cout << " if ";
      first = false;
      cout << *it; 
    }
  };

};

typedef list<Proposition> PropositionList;

#endif
