#ifndef READER_H
#define READER_H

#include "define.h"

using namespace std;

class Reader
{
 public:
  /* domain name */
  string m_domain_name;

  /* reading from the input file */
  StringList m_fluents;
  StringList m_actions;
  PropositionList m_propositions;
  //StringList2 m_init;
  Node m_init;
  StringList m_goal; // set of literals in the goal
  StringList2 m_gd; // goal description
 public:
  string name(Literal x);
  StringList name(Literals* x);
  int read();
  void print() const;
};

#endif
