#ifndef READER_H
#define READER_H

#include "define.h"

using namespace std;

class Reader
{
 public:
  /****** common part ******/
  StringSet atomicPropSet;

  /****** domain part ******/
  string domainName;
  StringSet types;
  // list<谓词, 多对<类型, list<变量> > >
  PredicateSet predicates;
  SenseActionList senseActions;
  OnticActionList onticActions;

  /****** problem part ******/
  string problemName;
  MultiTypeSet objects;
  Formula init;
  Formula goal;

 public:
  //string name(Literal x);
  //StringList name(Literals* x);
  int read();
  void print() const;
};

#endif
