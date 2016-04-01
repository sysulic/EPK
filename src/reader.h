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
  MultiTypeList objects;
  Formula init;
  Formula goal;

 public:
  Reader() {}
  ~Reader() {}

  void exec(const char* dFile, const char* pFile);

  // intermediate structure
  void printTree(ofstream & file, Formula * f, size_t deep);
  void removeImply(Formula * f);
  void removeOneof(Formula * f);
  void removeDoubleNot(Formula * f);
  void inwardMoveNot(Formula * f) ;
  void mergeK(Formula * f);
  void mergeDK(Formula * f);
  void inwardMoveAnd(Formula * f);
  void inwardMoveOr(Formula * f) ;
  void convertToDNFTree(Formula * f);
  void convertToDNFTree2(Formula * f);
  void convertToCNFTree(Formula * f);

  void printInit(ofstream &);
  void printGoal(ofstream &);
  void printSenseActions(ofstream &);
  void printOnticActions(ofstream &);
};

#endif
