/*
 * File: epddl-lexer-cpp.l
 * Description: A lexer for a sepecific file type epddl.
 *
 * Created by Biqing Fang on 10/25/2015.
 */

%{
#include "define.h"
#include "parse.h"	//用yacc编译yacc.y后生成的C头文件，内含%token、YYSTYPE、yylval等定义(都是C宏)，供lex.yy.c和yacc.tab.c使用

int yyerror(char *s);

%}

name				[a-zA-Z0-9\?][a-zA-Z_0-9\-]*

%%

"K"					{ return K; }
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
"-"					{ return CONNECTOR; }
"define"			{ return DEFINE; }
"domain"			{ return DOMAIN; }
"types"				{ return TYPES; }
"predicates"		{ return PREDICATES; }
"precondition"		{ return PRECONDITION; }
"action" 			{ return ACTION; }
"parameters"		{ return PARAMETERS; }
"observe"			{ yylval.str = new string(yytext); return OBSERVE; }
"effect"			{ yylval.str = new string(yytext); return EFFECT; }
"problem"			{ yylineno = 1; return PROBLEM; }
"objects"			{ return OBJECTS; }
"init"				{ return INIT; }
"goal"				{ return GOAL; }

"True"				{ yylval.str = new string(yytext); return TRUE; }
"False"				{ yylval.str = new string(yytext); return FALSE; }

{name}				{ yylval.str = new string(yytext); return NAME; }
\n 					{ yylineno++; }
%%

int yywrap(void)
{
	// puts("-----the file is end");
	return 1;  // 返回1表示读取全部结束。如果要接着读其它文件，可以这里fopen该文件，文件指针赋给yyin，并返回0
}
