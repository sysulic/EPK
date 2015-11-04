#include <set>
#include <map>
#include <algorithm>    // for set_intersection, set_union
#include <functional>   // for less
#include "reader.h"


// prototype of bison-generated parser function
int yyparse();

StringList Reader::name(Literals* x)
{
  StringList y;
  Literals::iterator it;

  for (it = x->begin(); it != x->end(); it++) {
    y.insert(name(*it));
  }

  return y;
}

string Reader::name(Literal x)
{
  unsigned short i = x / 2;
  StringList::iterator it;

  if (i >= m_fluents.size())
    return NULL;

  it = m_fluents.begin();

  for (i = 0; i < x/2; i++) {
    it++;
  }

  if (x % 2 == 0)
    return *it;
  
  return (NEGATION_SYMBOL + (*it));
}

int Reader::read()
{
  return yyparse();
}

void Reader::print() const
{
  StringList::const_iterator it;
  StringList2::const_iterator it2;
  PropositionList::const_iterator it3;
  bool first, first2;
  unsigned int i;

  cout << "FLUENT DECLARATION" << endl;
  cout << "----------------------------" << endl;
  for (it = m_fluents.begin(); it != m_fluents.end(); it++) {
    if (!first)
      cout << ",";
    first = false;
    cout << *it; 
  }

  cout << endl;
  cout << endl;

  cout << "PROPOSITIONS" << endl;
  cout << "----------------------------" << endl;
  for (it3 = m_propositions.begin(); it3 != m_propositions.end(); it3++) {    
    it3->print();
    cout << endl;
  }

  cout << endl;

  // print init cstate
  cout <<  "INIT" << endl;
  cout <<  "----------------------------" << endl;

  i = 0;
  /*
  for (it2 = m_init.begin(); it2 != m_init.end(); it2++) {
    cout << "State " << i++ << ": ";
    first = true;
    for (it = it2->begin(); it != it2->end(); it++) {
      if (!first)
	cout << ",";
      first = false;
      cout << *it; 
    }
    cout << endl;
  }
  */

  cout << endl;

  // print goal state
  cout <<  "GOAL " << endl;
  cout <<  "----------------------------" << endl;
  first2 = true;
  for (it2 = m_gd.begin(); it2 != m_gd.end(); it2++) {
    if (!first2)
      cout << " AND ";
    first2 = false;
    first = true;
    cout << "(";
    for (it = it2->begin(); it != it2->end(); it++) {
      if (!first)
	cout << " OR ";
      first = false;
      cout << *it; 
    }
    cout << ")";
  }
  cout << endl << endl;  

  // print statistics
  cout <<  "STATISTICS " << endl;
  cout <<  "----------------------------" << endl;
  cout << "Total actions: " << m_actions.size() << endl;
  cout << "Total fluents: " << m_fluents.size() << endl;
  cout << "Unknown fluents: " << endl;
  i = 0;
  /*
  for (it2 = m_init.begin(); it2 != m_init.end(); it2++) {
    cout << "\tState " << i++ << ": ";
    cout << m_fluents.size() - (*it2).size();
    cout << endl;
  }
  */
  cout << endl;
}
