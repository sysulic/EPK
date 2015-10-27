/*
 * File: epddl-parser-cpp.l
 * Description: A parser for a sepecific file type epddl.
 *
 * Created by Biqing Fang on 10/25/2015.
 */
%{
#include <iostream>
#include <string>

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

%token <s> NAME
%token <s> VARIABLE
%token <s> VARIABLES  // VARIABLE*
%token <s> VARIABLEX  // VARIABLE+
%token <s> DIGIT
%token <s> NUMBER
%token <s> TERMS

%token K
%token DK
%token AND
%token OR
%token NOT

%token LEFT_PAREN
%token RIGHT_PAREN
%token COMMA
%token DEFINE
%token DOMAIN
%token TYPES
%token PREDICATES
%token PRECONDITION
%token ACTION
%token PARAMETERS
%token OBSERVE
%token EFFECT

%type <s> epddlDoc
%type <s> domain
%type <s> domainName
%type <s> problem
%%

/*********************** Start of grammar ******************************/

epddlDoc : domain | problem { cout << "epddlDoc matched" << endl; }

/************* DOMAINS ****************************/

domain
	:	LEFT_PAREN
			DEFINE domainName
			typesDef
			predicatesDef
			actionsDef
		RIGHT_PAREN
	|	LEFT_PAREN
			DEFINE domainName
			predicatesDef
			actionsDef
		RIGHT_PAREN
	|	LEFT_PAREN
			DEFINE domainName
			actionsDef
		RIGHT_PAREN
{
	cout << "domain matched" << endl;
}
	;
domainName
	:	LEFT_PAREN DOMAIN NAME RIGHT_PAREN
	;

/******** typesdef ********/
typesDef
	:	LEFT_PAREN TYPES primTypes RIGHT_PAREN
{
	cout << "typesdef matched" << endl;
}
	;
primTypes
	:	primTypes primType
	|	primType
{
	cout << "primTypes matched" << endl;
}
	;
primType
	:	NAME
{
	cout << "primType matched" << endl;
}
	;

/***** predicatesdef *****/
predicatesDef
	:	LEFT_PAREN PREDICATES atomicFormulaSkeletons RIGHT_PAREN
{
	cout << "predicatesDef matched" << endl;
}
	;
atomicFormulaSkeletons
	:	atomicFormulaSkeletons atomicFormulaSkeleton
	|	atomicFormulaSkeleton
{
	cout << "atomicFormulaSkeletons matched" << endl;
}
	;
atomicFormulaSkeleton
	:	LEFT_PAREN predicate typedVariableList RIGHT_PAREN
{
	cout << "atomicFormulaSkeleton matched" << endl;
}
	;
predicate
	:	NAME
{
	cout << "predicate matched" << endl;
}
	;
// If have any typed variables, they must come FIRST!  确定类型的变量放在前面
typedVariableList
	:	VARIABLES
	|	singleTypeVarLists VARIABLES
{
	cout << "typedVariableList matched" << endl;
}
	;
singleTypeVarLists
	:	singleTypeVarLists singleTypeVarList
	|	singleTypeVarList
{
	cout << "singleTypeVarLists matched" << endl;
}
	;
singleTypeVarList
	:	VARIABLEX '-' primType
{
	cout << "singleTypeVarList matched" << endl;
}
	;

/****** actionsdef ******/
actionsDef
	:	actionsDef actionDef
	|	actionDef
{
	cout << "actionsDef matched" << endl;
}
	;
actionDef
	:	LEFT_PAREN
			ACTION actionSymbol
			PARAMETERS LEFT_PAREN typedVariableList RIGHT_PAREN
			PRECONDITION LEFT_PAREN precondition RIGHT_PAREN
			OBSERVE LEFT_PAREN observe RIGHT_PAREN {
				cout << "observe match done" << endl;
			}
		RIGHT_PAREN
	|	LEFT_PAREN
			ACTION actionSymbol
			PARAMETERS LEFT_PAREN typedVariableList RIGHT_PAREN
			PRECONDITION LEFT_PAREN precondition RIGHT_PAREN
			EFFECT LEFT_PAREN effect RIGHT_PAREN {
				cout << "effect match done" << endl;
			}
		RIGHT_PAREN
{
	cout << "actionDef matched" << endl;
}
	;
actionSymbol
	:	NAME
{
	cout << "actionSymbol matched" << endl;
}
	;

/** precondition **/
precondition
	:	episFormula
	|	formula
{
	cout << "precondition matched" << endl;
}
	;
episFormula
	:	K LEFT_PAREN formula RIGHT_PAREN
	|	DK LEFT_PAREN formula RIGHT_PAREN
	|	AND LEFT_PAREN episFormula RIGHT_PAREN
	|	OR LEFT_PAREN episFormula RIGHT_PAREN
{
	cout << "episFormula matched" << endl;
}
	;
formula
	:	atomicTermFormula
	|	AND formula formula
	|	OR formula formula  // expr expr == expr+
	|	NOT formula
	|	LEFT_PAREN formula RIGHT_PAREN
{
	cout << "formula matched" << endl;
}
	;
atomicTermFormula
	:	LEFT_PAREN predicate TERMS RIGHT_PAREN
{
	cout << "atomicTermFormula matched" << endl;
}
	;

/** observe **/
observe
	:	atomicTermFormula  // observe - only predicate here (incomplete)
{
	cout << "observe matched" << endl;
}
	;

/** effect **/
effect
	:	LEFT_PAREN singleEffect RIGHT_PAREN
	|	LEFT_PAREN singleEffect RIGHT_PAREN COMMA effect
{
	cout << "effect matched" << endl;
}
	;
singleEffect
	:	formula COMMA formula
{
	cout << "singleEffect matched" << endl;
}
	;

/************* PROBLEMS ***************************/

problem
	: "problem hahaha"
{
	cout << "problem matched" << endl;
}
	;

%%

void yyerror(const char *s)  // 当yacc遇到语法错误时，会回调yyerror函数，并且把错误信息放在参数s中
{
	cerr << s << endl;  // 直接输出错误信息
}

int main()  // 程序主函数，这个函数也可以放到其它.c, .cpp文件里
{
	const char* sFile="../epddl-doc/mytest/demo_domain.epddl";  // 打开要读取的文本文件
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
