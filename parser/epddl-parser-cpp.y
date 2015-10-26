/*
 * File: epddl-parser-cpp.l
 * Description: A parser for a sepecific file type epddl.
 *
 * Created by Biqing Fang on 10/25/2015.
 */
%{
// #include "reader.h"
#include <iostream>
#include <string>  // cout sth for debugging
using namespace std;

int yyerror(char *s);
int yylex(void);

extern Reader reader;

%}

%union{

}

%start epddlDoc

%token NAME
%token VARIABLE
%token VARIABLES  // VARIABLE*
%token VARIABLEX  // VARIABLE+
%token DIGIT
%token NUMBER

%token DOMAIN
%token DOMAIN_NAME
%token TYPES
%token EITHER_TYPE
%token CONSTANTS
%token FUNCTIONS
%token PREDICATES
%token ACTION
%token DURATIVE_ACTION
%token PROBLEM
%token PROBLEM_NAME
%token PROBLEM_DOMAIN
%token OBJECTS
%token INIT
%token FUNC_HEAD
%token PRECONDITION
%token EFFECT
%token AND_GD
%token OR_GD
%token NOT_GD
%token IMPLY_GD
%token EXISTS_GD
%token FORALL_GD
%token COMPARISON_GD
%token AND_EFFECT
%token FORALL_EFFECT
%token WHEN_EFFECT
%token ASSIGN_EFFECT
%token NOT_EFFECT
%token PRED_HEAD
%token GOAL
%token BINARY_OP
%token UNARY_MINUS
%token INIT_EQ
%token INIT_AT
%token NOT_PRED_INIT
%token PRED_INST
%token PROBLEM_CONSTRAINT
%token PROBLEM_METRIC
%%

/*********************** Start of grammar ******************************/

epddlDoc : domain | problem

/************* DOMAINS ****************************/

domain
	: '(' "define" domainName
		( typesDef | EMPTY )
		( predicatesDef | EMPTY)
		actionsDef
		')'
	{
		// todo
	}
	;

domainName
	:	'(' "domain" NAME ')'
	;

/******** TYPESDEF ********/
typesDef
	:	'(' ":types" primTypes ')'
	;
primTypes
	:	primTypes primType
	|	primType
	;
primType
	:	NAME
	;

/***** PREDICATESDEF *****/
predicatesDef
	:	'(' ":predicates" atomicFormulaSkeletons ')'
	;
atomicFormulaSkeletons
	:	atomicFormulaSkeletons atomicFormulaSkeleton
	|	atomicFormulaSkeleton
	;
atomicFormulaSkeleton
	:	'(' predicate typedVariableList ')'
	;
predicate:
	:	NAME
	;
// If have any typed variables, they must come FIRST!  确定类型的变量放在前面
typedVariableList
	:	(VARABLES | singleTypeVarLists VARABLES)
	;
singleTypeVarLists
	:	singleTypeVarLists singleTypeVarList
	|	singleTypeVarList
	;
singleTypeVarList
	:	(VARABLEX '-' primType)
	;

/****** ACTIONSDEF ******/
actionsDef
	:	actionsDef actionDef
	|	actionDef
	;
actionDef
	:	
	;

/************* PROBLEMS ***************************/



/** BASIS **/
EMPTY
	: ;