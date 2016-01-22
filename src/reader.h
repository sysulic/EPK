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
  void convertToCNFTree(Formula * f);

  void printInit(ofstream & out_begin, ofstream & out_end);
  void printGoal(ofstream & out_begin, ofstream & out_end);
  void printSenseActions(ofstream & out_file);
  void printOnticActions(ofstream & out_file);
};

#endif
