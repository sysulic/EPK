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
  PreSenseActionList senseActions;
  PreOnticActionList onticActions;

  /****** problem part ******/
  string problemName;
  MultiTypeSet objects;
  Formula init;
  Formula goal;

 public:
  Reader();
  ~Reader();

  // intermediate structure
  void printTree(Formula & f, size_t deep);
  void removeImply(Formula & f);
  void removeOneof(Formula & f);
  void inwardMoveNot(Formula & f) ;
  void mergeK(Formula & f);
  void mergeDK(Formula & f);
  void inwardMoveAnd(Formula & f);
  void inwardMoveOr(Formula & f) ;
  void convertToDNFTree(Formula & f);
  void convertToCNFTree(Formula & f);
  void show();

};

#endif
