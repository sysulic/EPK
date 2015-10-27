/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     VARIABLE = 259,
     VARIABLES = 260,
     VARIABLEX = 261,
     DIGIT = 262,
     NUMBER = 263,
     TERMS = 264,
     K = 265,
     DK = 266,
     AND = 267,
     OR = 268,
     NOT = 269,
     DEFINE = 270,
     DOMAIN = 271,
     TYPES = 272,
     PREDICATES = 273,
     PRECONDITION = 274,
     ACTION = 275,
     PARAMETERS = 276,
     OBSERVE = 277,
     EFFECT = 278
   };
#endif
/* Tokens.  */
#define NAME 258
#define VARIABLE 259
#define VARIABLES 260
#define VARIABLEX 261
#define DIGIT 262
#define NUMBER 263
#define TERMS 264
#define K 265
#define DK 266
#define AND 267
#define OR 268
#define NOT 269
#define DEFINE 270
#define DOMAIN 271
#define TYPES 272
#define PREDICATES 273
#define PRECONDITION 274
#define ACTION 275
#define PARAMETERS 276
#define OBSERVE 277
#define EFFECT 278




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 21 "epddl-parser-cpp.y"
{
	char* s;
}
/* Line 1529 of yacc.c.  */
#line 99 "epddl-parser-cpp.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

