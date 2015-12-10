 /*
 * File: epddl-parser-cpp.l
 * Description: A parser for a sepecific file type epddl.
 *
 * Created by Biqing Fang on 10/25/2015.
 */
%{
#include "reader.h"

int yyerror(char *s);
int yylex(void);

extern Reader reader;

%}

%union{
  string* str;
  StringSet* str_set;
  SingleTypePair* singletype_pair;
  MultiTypeSet* multitype_set;
  MultiTypePair* multitype_pair;
  PredicateSet* pre_set;
  Effect* eff;
  EffectList* eff_set;
  SenseAction* sense_action;
  OnticAction* ontic_action;
  SenseActionList* sense_list;
  OnticActionList* ontic_list;
  Formula* tree;
}

%start epddlDoc

%token <str> NAME

%token K
%token DK
%token AND
%token OR
%token NOT
%token IMPLY
%token ONEOF

%token <str> TRUE
%token <str> FALSE

%token LEFT_PAREN
%token RIGHT_PAREN
%token COMMA
%token COLON
%token CONNECTOR
%token DEFINE
%token DOMAIN
%token TYPES
%token PREDICATES
%token PRECONDITION
%token ACTION
%token PARAMETERS
%token OBSERVE
%token EFFECT
%token PROBLEM
%token OBJECTS
%token INIT
%token GOAL

%type <str> domainName

%type <str_set> typesDef
%type <str_set> primTypes
%type <str> primType

%type <pre_set> predicatesDef
%type <pre_set> atomicFormulaSkeletons
%type <multitype_pair> atomicFormulaSkeleton
%type <str> predicate
%type <multitype_set> typedVariableList
%type <singletype_pair> singleTypeVarList
%type <str_set> variables

%type <str> lit
%type <str_set> litSet
%type <eff> effect
%type <eff_set> effects
%type <str> actionSymbol
%type <multitype_set> parameters
%type <tree> observe
%type <sense_action> senseAction
%type <ontic_action> onticAction
%type <sense_list> senseActionsDef
%type <ontic_list> onticActionsDef

%type <tree> precondition
%type <tree> formula
%type <tree> episFormulas
%type <tree> episFormula
%type <tree> objFormula
%type <tree> objFormulas

%type <str> problemDecl
%type <str> atomicProp

%type <multitype_set> objectDecl
%type <multitype_set> objectTypes
%type <singletype_pair> singleType
%type <str_set> objects
%type <str> object

%type <tree> init
%type <tree> goal
%%

/******************* Start of grammar *************************/

epddlDoc : domain | problem;

/************* DOMAINS ****************************/

domain
	:	LEFT_PAREN
			DEFINE domainName
			typesDef
			predicatesDef
			senseActionsDef
			onticActionsDef
		RIGHT_PAREN
	{
		reader.domainName = *$3;
		reader.types = *$4;
		reader.predicates = *$5;
		reader.senseActions = *$6;
		reader.onticActions = *$7;
		// cout << "domain done" << endl;
	}
	;
domainName
	:	LEFT_PAREN DOMAIN NAME RIGHT_PAREN
	{
		$$ = $3;
	}
	;

/******** typesdef ********/
typesDef
	:	LEFT_PAREN COLON TYPES primTypes RIGHT_PAREN
	{
		$$ = $4;
	}
	|	LEFT_PAREN COLON TYPES RIGHT_PAREN
	{
		$$ = new StringSet;
	}
	;
primTypes
	:	primTypes primType
	{
		$$ = $1;
		$$->insert(*$2);
	}
	|	primType
	{
		$$ = new StringSet;
		$$->insert(*$1);
	}
	;
primType
	:	NAME
	{
		$$ =  new string(*$1);
	}
	;

/***** predicatesdef *****/
predicatesDef
	:	LEFT_PAREN COLON PREDICATES atomicFormulaSkeletons RIGHT_PAREN
	{
		$$ = $4;
	}
	|	LEFT_PAREN COLON PREDICATES RIGHT_PAREN
	{
		$$ = new PredicateSet
	}
	;
atomicFormulaSkeletons
	:	atomicFormulaSkeletons atomicFormulaSkeleton
	{
		$$ = $1;
		$$->insert(*$2);
	}
	|	atomicFormulaSkeleton
	{
		$$ = new PredicateSet;
		$$->insert(*$1);
	}
	;
atomicFormulaSkeleton
	:	LEFT_PAREN predicate typedVariableList RIGHT_PAREN
	{
		$$ = new MultiTypePair;
		$$->first = *$2;
		$$->second = *$3;
	}
	;
predicate
	:	NAME
	{ 
		$$ = $1;
	}
	;
typedVariableList
	:	typedVariableList singleTypeVarList
	{
		$$ = $1;
		$$->insert(*$2);
	}
	|	singleTypeVarList
	{
		$$ = new MultiTypeSet;
		$$->insert(*$1);
	}
	;
singleTypeVarList
	:	variables CONNECTOR primType
	{
		$$ = new SingleTypePair;
		$$->first = *$3;
		$$->second = *$1;
	}
	;
variables
	:	variables NAME
	{
		$$ = $1;
		$$->insert(*$2);
	}
	|	NAME
	{
		$$ = new StringSet;
		$$->insert(*$1);
	}
	;
/****** actionsdef ******/
senseActionsDef
	:	senseActionsDef senseAction
	{
		$$ = $1;
		$$->insert($$->begin(), *$2);
	}
	|	senseAction
	{
		$$ = new SenseActionList;
		$$->insert($$->begin(), *$1);
	}
	;
senseAction
	:	LEFT_PAREN
			COLON ACTION actionSymbol
			COLON PARAMETERS LEFT_PAREN parameters RIGHT_PAREN
			COLON PRECONDITION LEFT_PAREN precondition RIGHT_PAREN
			COLON OBSERVE LEFT_PAREN observe RIGHT_PAREN
		RIGHT_PAREN
	{
		$$ = new SenseAction;
		$$->name = *$4;
		$$->paras = *$8;
		$$->preCondition = *$13;
		$$->observe = *$18;
		// cout << "senseActions done" << endl;
	}
	;
onticActionsDef
	:	onticActionsDef onticAction
	{
		$$ = $1;
		$$->insert($$->begin(), *$2);
	}
	|	onticAction
	{
		$$ = new OnticActionList;
		$$->insert($$->begin(), *$1);
	}
	;
onticAction
	:	LEFT_PAREN
			COLON ACTION actionSymbol
			COLON PARAMETERS LEFT_PAREN parameters RIGHT_PAREN
			COLON PRECONDITION LEFT_PAREN precondition RIGHT_PAREN
			COLON EFFECT LEFT_PAREN effects RIGHT_PAREN
		RIGHT_PAREN
	{
		$$ = new OnticAction;
		$$->name = *$4;
		$$->paras = *$8;
		$$->preConditions = *$13;
		$$->effects = *$18;	
		// cout << "onticAction done" << endl;
	}
	;
actionSymbol
	:	NAME { $$ = $1; }
	;
/** parameters **/
parameters
	:	typedVariableList { $$ = $1; }
	|	{ $$ = new MultiTypeSet; }
	;
/** precondition **/
precondition
	:	formula 	{ $$ = $1; }
	;
// definition of any kinds of formulas which include 'K' or not
formula
	:	episFormula 		{ $$ = $1; }
	|	objFormula 			{ $$ = $1; }
	|	AND episFormulas	{ $$ = new Formula("&", $2->left, $2->right); }
	|	OR episFormulas		{ $$ = new Formula("|", $2->left, $2->right); }
	;
episFormulas
	:	episFormulas LEFT_PAREN episFormula RIGHT_PAREN
	{
		if ($1->right == NULL) {
			$$ = $1;
		} else {
			$$ = new Formula("same", $1, NULL);
		}
		$$->right = $3;
	}
	|	LEFT_PAREN episFormula RIGHT_PAREN
	{
		$$ = new Formula("same", $2, NULL);
	}
	;
episFormula
	:	K LEFT_PAREN objFormula RIGHT_PAREN
	{
		$$ = new Formula("K", $3, NULL);
	}
	|	DK LEFT_PAREN objFormula RIGHT_PAREN
	{
		$$ = new Formula("DK", $3, NULL);
	}
	;
objFormula
	:	AND objFormulas		{ $$ = new Formula("&", $2->left, $2->right); }
	|	OR objFormulas		{ $$ = new Formula("|", $2->left, $2->right); }
	|	NOT objFormulas		{ $$ = new Formula("!", $2->left, $2->right); }
	|	IMPLY objFormulas	{ $$ = new Formula("->", $2->left, $2->right); }
	|	ONEOF objFormulas	{ $$ = new Formula("oneof", $2->left, $2->right); }
	|	atomicProp			{ $$ = new Formula(*$1); }
	;
objFormulas
	:	objFormulas LEFT_PAREN objFormula RIGHT_PAREN
	{
		if ($1->right == NULL) {
			$$ = $1;
		} else {
			$$ = new Formula("same", $1, NULL);
		}
		$$->right = $3;
	}
	|	LEFT_PAREN objFormula RIGHT_PAREN
	{
		$$ = new Formula("same", $2, NULL);
	}
	;
atomicProp
	:	predicate variables
	{
		$$ = new string(*$1);
		for (StringSet::iterator ssi = (*$2).begin(); ssi != (*$2).end(); ssi++)
		{
			*$$ += " " + *ssi;
		}
		reader.atomicPropSet.insert(*$$);
	}
	|	NAME { $$ = $1; reader.atomicPropSet.insert(*$$); }
	;
/** observe **/
observe
	:	objFormula { $$ = $1; }
	;
/** effect **/
effects
	:	effects LEFT_PAREN effect RIGHT_PAREN
	{
		$$ = $1;
		$$->insert($$->begin(), *$3);
	}
	|	LEFT_PAREN effect RIGHT_PAREN
	{
		$$ = new EffectList;
		$$->insert($$->begin(), *$2);
	}
	;
effect
	:	LEFT_PAREN litSet RIGHT_PAREN COMMA LEFT_PAREN litSet RIGHT_PAREN
	{
		$$ = new Effect;
		$$->condition = *$2;
		$$->lits = *$2;
	}
	;
litSet
	:	litSet COMMA lit
	{
		$$ = $1;
		$$->insert(*$3);
		reader.atomicPropSet.insert(*$3); 
	}
	|	lit
	{
		$$ = new StringSet;
		$$->insert(*$1);
		reader.atomicPropSet.insert(*$1);
	}
	;
lit
	:	NAME { $$ = $1; }
	|	NOT LEFT_PAREN NAME RIGHT_PAREN { $$ = new string("not(" + *$3 + ")");}
	|	predicate variables
	{
		$$ = new string(*$1);
		for (StringSet::iterator ssi = (*$2).begin(); ssi != (*$2).end(); ssi++)
		{
			*$$ += " " + *ssi;
		}
	}
	|	TRUE	{ $$ = $1; }
	|	FALSE	{ $$ = $1; }
	;
/************* PROBLEMS ***************************/

problem
	:	LEFT_PAREN
			DEFINE problemDecl
			problemDomain
			objectDecl
			init
			goal
		RIGHT_PAREN
	{
		reader.problemName = *$3;
		reader.objects = *$5;
		reader.init = *$6;
		reader.goal = *$7;
		// cout << "problem done" << endl;
	}
	;
problemDecl
	:	LEFT_PAREN PROBLEM NAME RIGHT_PAREN
	{
		$$ = $3;
	}
	;
problemDomain
	:	LEFT_PAREN COLON DOMAIN NAME RIGHT_PAREN
	;
/** objectdecl **/
objectDecl
	:	LEFT_PAREN COLON OBJECTS objectTypes RIGHT_PAREN
	{
		$$ = $4;
	}
	|	LEFT_PAREN COLON OBJECTS RIGHT_PAREN
	{
		$$ = new MultiTypeSet;
	}
	;
objectTypes
	:	objectTypes singleType
	{
		$$ = $1;
		$$->insert(*$2);
	}
	|	singleType
	{
		$$ = new MultiTypeSet;
		$$->insert(*$1);
	}
	;
singleType
	:	objects CONNECTOR primType
	{
		$$ = new SingleTypePair;
		$$->first = *$3;
		$$->second = *$1;
	}
	;
objects
	:	objects object
	{
		$$ = $1;
		$$->insert(*$2);
	}
	|	object
	{
		$$ = new StringSet;
		$$->insert(*$1);
	}
	;
object
	:	NAME { $$ = $1; }
	;
/** init **/
init
	:	LEFT_PAREN COLON INIT LEFT_PAREN formula RIGHT_PAREN RIGHT_PAREN
	{
		$$ = $5;
		// cout << "init done" << endl;
	}
	;
/** goal **/
goal
	:	LEFT_PAREN COLON GOAL LEFT_PAREN formula RIGHT_PAREN RIGHT_PAREN
	{
		$$ = $5;
	}
	;

%%

int yyerror(string s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
  return 0;
}

int yyerror(char *s)  // 当yacc遇到语法错误时，会回调yyerror函数，并且把错误信息放在参数s中
{
	return yyerror(string(s));
}
