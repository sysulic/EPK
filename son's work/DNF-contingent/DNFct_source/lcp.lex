/* Scanner for AL language */

%{
#include "define.h"
#include "tok.h"

int yyerror(char *s);
int yylineno1 = 1;
%}

digit		[0-9]
number	{digit}+
id [a-zA-Z][a-zA-Z_0-9]*
comment %.*$

%%

{number}	{ yylval.str_val = new std::string(yytext); return NUMBER; }
";"		{ return SEMICOLON; } 
"fluent" {return FLUENT;}
"action" {return ACTION;}
"if" {return IF;}
"causes" {return CAUSES;}
"executable" {return EXECUTABLE;}
"impossible" {return IMPOSSIBLE;}
"initially" {return INIT;}
"goal" {return GOAL;}

"," {return COMMA;}
"|" {return OR;}
"(" {return LEFT_PAREN;}
")" {return RIGHT_PAREN;}
"-" {yylval.str_val = new std::string(yytext); return NEGATION;}

{id} {yylval.str_val = new std::string(yytext); return ID;}

[ \t]*		{}
[\n]		{ yylineno1++;	}
{comment} ;

.		{ std::cerr << "SCANNER "; yyerror(""); exit(1);	}

