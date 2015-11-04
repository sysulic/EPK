/*
 * File: epddl-parser-cpp.l
 * Description: A parser for a sepecific file type epddl.
 *
 * Created by Biqing Fang on 10/25/2015.
 */
%{
#include <iostream>
#include <string>
#include "../sources/actions.h"

using namespace std;

extern "C"			//为了能够在C++程序里面调用C函数，必须把每一个需要使用的C函数，其声明都包括在extern "C"{}块里面，这样C++链接时才能成功链接它们。extern "C"用来在C++环境下设置C链接类型。
{					//lex.l中也有类似的这段extern "C"，可以把它们合并成一段，放到共同的头文件main.h中
	void yyerror(const char *s);
	extern int yylex(void);//该函数是在lex.yy.c里定义的，yyparse()里要调用该函数，为了能编译和链接，必须用extern加以声明
	extern char* yytext;
	extern int yylineno;
}

%}

%union{
	char* s;
}

%start epddlDoc

%token NAME
%token VARIABLE
%token DIGIT
%token NUMBER
%token TERMS

%token K
%token DK
%token AND
%token OR
%token NOT
%token IMPLY
%token ONEOF

%token LEFT_PAREN
%token RIGHT_PAREN
%token COMMA
%token COLON
%token MINUS
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

%type <s> epddlDoc
%type <s> domain
%type <s> domainName
%type <s> problem
%%

/*********************** Start of grammar ******************************/

epddlDoc : domain | problem { cout << yylineno << " : " << yytext << " epddlDoc matched" << endl; }

/************* DOMAINS ****************************/

domain
	:	LEFT_PAREN
			DEFINE domainName
			typesDef
			predicatesDef
		RIGHT_PAREN
	|	LEFT_PAREN
			DEFINE domainName
			predicatesDef
			actionsDef
		RIGHT_PAREN
	|	LEFT_PAREN
			DEFINE domainName
			typesDef
			predicatesDef
			actionsDef
		RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << " domain matched" << endl;
}
	;
domainName
	:	LEFT_PAREN DOMAIN NAME RIGHT_PAREN
	;

/******** typesdef ********/
typesDef
	:	LEFT_PAREN COLON TYPES primTypes RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << " typesdef matched" << endl;
}
	;
primTypes
	:	primType primTypes
	|	primType
{
	cout << yylineno << " : " << yytext << " primTypes matched" << endl;
}
	;
primType
	:	NAME
{
	cout << yylineno << " : " << yytext << " primType matched" << endl;
}
	;

/***** predicatesdef *****/
predicatesDef
	:	LEFT_PAREN COLON PREDICATES atomicFormulaSkeletons RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << " predicatesDef matched" << endl;
}
	;
atomicFormulaSkeletons
	:	atomicFormulaSkeletons atomicFormulaSkeleton
	|	atomicFormulaSkeleton
{
	cout << yylineno << " : " << yytext << " atomicFormulaSkeletons matched" << endl;
}
	;
atomicFormulaSkeleton
	:	LEFT_PAREN predicate typedVariableList RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << " atomicFormulaSkeleton matched" << endl;
}
	;
predicate
	:	NAME
{
	cout << yylineno << " : " << yytext << " predicate matched" << endl;
}
	;
typedVariableList
	:	singleTypeVarList singleTypeVarList 
	|	singleTypeVarList 
{
	cout << yylineno << " : " << yytext << " singleTypeVarLists matched" << endl;
}
	;
singleTypeVarList
	:	variables MINUS primType
{
	cout << yylineno << " : " << yytext << " singleTypeVarList matched" << endl;
}
	;
variables
	:	variables VARIABLE
	|	VARIABLE
{
	cout << yylineno << " : " << yytext << " variables matched" << endl;
}
	;
/****** actionsdef ******/
actionsDef
	:	actionsDef actionDef
	|	actionDef
{
	cout << yylineno << " : " << yytext << " actionsDef matched" << endl;
}
	;
actionDef
	:	LEFT_PAREN
			COLON ACTION actionSymbol
			COLON PARAMETERS LEFT_PAREN parameters RIGHT_PAREN
			COLON PRECONDITION LEFT_PAREN precondition RIGHT_PAREN
			COLON OBSERVE LEFT_PAREN observe RIGHT_PAREN {
				cout << yylineno << " : " << yytext << " observe match done" << endl;
			}
		RIGHT_PAREN
	|	LEFT_PAREN
			COLON ACTION actionSymbol
			COLON PARAMETERS LEFT_PAREN parameters RIGHT_PAREN
			COLON PRECONDITION LEFT_PAREN precondition RIGHT_PAREN
			COLON EFFECT LEFT_PAREN effects RIGHT_PAREN {
				cout << yylineno << " : " << yytext << " effect match done" << endl;
			}
		RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << " actionDef matched" << endl;
}
	;
actionSymbol
	:	NAME
{
	cout << yylineno << " : " << yytext << " actionSymbol matched" << endl;
}
	;
/** parameters **/
parameters
	:	typedVariableList
	|
	{
		cout << yylineno << " : " << yytext << "parameters matched" << endl;
	}
	;
/** precondition **/
precondition
	:	formula
{
	cout << yylineno << " : " << yytext << " precondition matched" << endl;
}
	;
// definition of any kinds of formulas which include 'K' or not
formula
	:	episFormula
	|	AND episFormulas
	|	OR episFormulas
{
	cout << yylineno << " : " << yytext << " formula matched" << endl;
}
	;
episFormulas
	:	episFormulas LEFT_PAREN episFormula RIGHT_PAREN
	|	LEFT_PAREN episFormula RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << " episFormulas matched" << endl;
}
	;
episFormula
	:	K LEFT_PAREN objFormula RIGHT_PAREN
	|	DK LEFT_PAREN objFormula RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << " episFormula matched" << endl;
}
	;
objFormula
	:	AND objFormulas
	|	OR objFormulas
	|	NOT objFormulas
	|	IMPLY objFormulas
	|	ONEOF objFormulas
	|	atomicProp
{
	cout << yylineno << " : " << yytext << " objFormula matched" << endl;
}
	;
objFormulas  // 递归地自解释通式：objFormula
	:	objFormulas LEFT_PAREN objFormula RIGHT_PAREN
	|	LEFT_PAREN objFormula RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << " objFormulaOrAtomicProps matched" << endl;
}
	;
atomicProp
	:	predicate variables
	|	NAME
	|
{
	cout << yylineno << " : " << yytext << " atomicProp matched" << endl;
}
	;
/** observe **/
observe
	:	objFormula
{
	cout << yylineno << " : " << yytext << " observe matched" << endl;
}
	;

/** effect **/
effects
	:	LEFT_PAREN effect RIGHT_PAREN
	|	LEFT_PAREN effect RIGHT_PAREN effects
{
	cout << yylineno << " : " << yytext << " effect matched" << endl;
}
	;
effect
	:	LEFT_PAREN litSet RIGHT_PAREN COMMA LEFT_PAREN litSet RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << " singleEffect matched" << endl;
}
	;
litSet
	:	litSet COMMA lit
	|	lit
{
	cout << yylineno << " : " << yytext << " litSet matched" << endl;
}
	;
lit
	:	NAME
	|	NOT LEFT_PAREN NAME RIGHT_PAREN
	|	predicate variables
	|
{
	cout << yylineno << " : " << yytext << " lit matched" << endl;
}
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
	|	LEFT_PAREN
			DEFINE problemDecl
			problemDomain
			init
			goal
		RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << "problem matched" << endl;
}
	;
problemDecl
	:	LEFT_PAREN PROBLEM NAME RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << "problemDecl matched" << endl;
}
	;
problemDomain
	:	LEFT_PAREN COLON DOMAIN NAME RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << "problemDomain matched" << endl;
}
	;
/** objectdecl **/
objectDecl
	:	LEFT_PAREN COLON OBJECTS objectTypes RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << "objectDecl matched" << endl;
}
	;
objectTypes
	:	objectTypes singleType
	|	singleType
{
	cout << yylineno << " : " << yytext << "objectTypes matched" << endl;
}
	;
singleType
	:	objects MINUS primType
{
	cout << yylineno << " : " << yytext << "singleType matched" << endl;
}
	;
objects
	:	objects object
	|	object
{
	cout << yylineno << " : " << yytext << "objects matched" << endl;
}
	;
object
	:	NAME
	;
/** init **/
init
	:	LEFT_PAREN COLON INIT LEFT_PAREN formula RIGHT_PAREN RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << "init matched" << endl;
}
	;
/** goal **/
goal
	:	LEFT_PAREN COLON GOAL LEFT_PAREN formula RIGHT_PAREN RIGHT_PAREN
{
	cout << yylineno << " : " << yytext << "goal matched" << endl;
}
	;

%%

void yyerror(const char *s)  // 当yacc遇到语法错误时，会回调yyerror函数，并且把错误信息放在参数s中
{
	cerr << s << ":" << yylineno << " " << yytext << endl;  // 直接输出错误信息
}

int main()  // 程序主函数，这个函数也可以放到其它.c, .cpp文件里
{
	const char* sFile="../epddl-doc/mytest/my_p.epddl";  // 打开要读取的文本文件
	FILE* fp=fopen(sFile, "r");
	if(fp==NULL)
	{
		printf("cannot open %s\n", sFile);
		return -1;
	}
	extern FILE* yyin;  // yyin和yyout都是FILE*类型
	yyin = fp;  // yacc会从yyin读取输入，yyin默认是标准输入，这里改为磁盘文件。yacc默认向yyout输出，可修改yyout改变输出目的

	printf("-----begin parsing %s\n", sFile);
	yyparse();  // 使yacc开始读取输入和解析，它会调用lex的yylex()读取记号
	puts("-----end parsing");

	fclose(fp);

	return 0;
}
