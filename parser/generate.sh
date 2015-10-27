#!/bin/sh 
echo \~frank: flex .l
flex epddl-lexer-cpp.l
echo \~frank: bison -d .y
bison -d epddl-parser-cpp.y
echo \~frank: g++ -c .c
g++ -c lex.yy.c
echo \~frank: g++ -c parser.tab.c
g++ -c epddl-parser-cpp.tab.c
echo \~frank: g++ p.o l.o -o main
g++ epddl-parser-cpp.tab.o lex.yy.o -o main
