/*
 * File: epddl-lexer-cpp.l
 * Description: A lexer for a sepecific file type epddl.
 *
 * Created by Biqing Fang on 10/25/2015.
 */

%{
// #include "define.h"
// #include "tok.h"
#include "epddl-parser-cpp.tab.h"	//用yacc编译yacc.y后生成的C头文件，内含%token、YYSTYPE、yylval等定义(都是C宏)，供lex.yy.c和yacc.tab.c使用
#include <iostream>

using namespace std;

#ifdef __cplusplus  // for name mangling
extern "C"  //为了能够在C++程序里面调用C函数，必须把每一个需要使用的C函数，其声明都包括在extern "C"{}块里面，这样C++链接时才能成功链接它们。extern "C"用来在C++环境下设置C链接类型。
{		
#endif
    /* ... */
#ifdef __cplusplus
				//yacc.y中也有类似的这段extern "C"，可以把它们合并成一段，放到共同的头文件main.h中
	int yywrap(void);
	int yylex(void);	//这个是lex生成的词法分析函数，yacc的yyparse()里会调用它，如果这里不声明，生成的yacc.tab.c在编译时会找不到该函数
}
#endif

%}

name				[a-zA-Z][a-zA-Z_0-9\-]*
variable			\?{name}
digit				[0-9]
number				{digit}+
terms				({name}|{variable})*

%%

"K"					{ yylval.s = strdup(yytext); return K; }
"DK"				{ return DK; }

"and"				{ return AND; }
"or"				{ return OR; }
"not"				{ return NOT; }
"imply"				{ return IMPLY; }
"oneof"				{ return ONEOF; }

"("					{ return LEFT_PAREN; }
")"					{ return RIGHT_PAREN; }
","					{ return COMMA; }
":"					{ return COLON; }
"-"					{ return MINUS; }
"define"			{ return DEFINE; }
"domain"			{ return DOMAIN; }
"types"				{ return TYPES; }
"predicates"		{ return PREDICATES; }
"precondition"		{ return PRECONDITION; }
"action" 			{ return ACTION; }
"parameters"		{ return PARAMETERS; }
"observe"			{ return OBSERVE; }
"effect"			{ return EFFECT; }
"problem"			{ return PROBLEM; }
"objects"			{ return OBJECTS; }
"init"				{ return INIT; }
"goal"				{ return GOAL; }

{name}				{ return NAME; }
{variable}			{ return VARIABLE; }
{digit}				{ return DIGIT; }
{number}			{ return NUMBER; }
{terms}				{ return TERMS; }
\n 					{ yylineno++; }
%%

int yywrap(void)
{
	// puts("-----the file is end");
	return 1;  // 返回1表示读取全部结束。如果要接着读其它文件，可以这里fopen该文件，文件指针赋给yyin，并返回0
}
