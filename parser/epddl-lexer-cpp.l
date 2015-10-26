/*
 * File: epddl-lexer-cpp.l
 * Description: A lexer for a sepecific file type epddl.
 *
 * Created by Biqing Fang on 10/25/2015.
 /
/* Scanner for AL language */

%{
// #include "define.h"
// #include "tok.h"

int yyerror(char *s);
int yylineno1 = 1;
%}

name 			[a-zA-Z][a-zA-Z0-9-_]*
variable		?{name}
variables		{variable}*
variablex		{variable}+
digit			[0-9]
number			{digit}+

%%

{name} 			{ yylval.str_val = new std::string(yytext); return NAME; }
{variable}		{ return VARIABLE; }
{variables}		{ return VARIABLES; }
{variablex}		{ return VARIABLEX; }
{number}		{ yylval.str_val = new std::string(yytext); return NUMBER; }
{digit}			{ return DIGIT; }

";"				{ return SEMICOLON; } 
"fluent"		{ return FLUENT;}
"action"		{ return ACTION;}
"if" 			{ return IF;}
"causes" 		{ return CAUSES;}
"executable" 	{ return EXECUTABLE;}
"impossible" 	{ return IMPOSSIBLE;}
"initially" 	{ return INIT;}
"goal" 			{ return GOAL;}

"," 			{ return COMMA;}
"|" 			{ return OR;}
"(" 			{ return LEFT_PAREN;}
")" 			{ return RIGHT_PAREN;}
"-" 			{ yylval.str_val = new std::string(yytext); return NEGATION;}


[ \t]*			{ }
[\n]			{ yylineno1++; }
{comment} ;

.				{ std::cerr << "SCANNER "; yyerror(""); exit(1); }
%%
