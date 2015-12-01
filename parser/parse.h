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
     K = 260,
     DK = 261,
     AND = 262,
     OR = 263,
     NOT = 264,
     IMPLY = 265,
     ONEOF = 266,
     LEFT_PAREN = 267,
     RIGHT_PAREN = 268,
     COMMA = 269,
     COLON = 270,
     CONNECTOR = 271,
     DEFINE = 272,
     DOMAIN = 273,
     TYPES = 274,
     PREDICATES = 275,
     PRECONDITION = 276,
     ACTION = 277,
     PARAMETERS = 278,
     OBSERVE = 279,
     EFFECT = 280,
     PROBLEM = 281,
     OBJECTS = 282,
     INIT = 283,
     GOAL = 284
   };
#endif
/* Tokens.  */
#define NAME 258
#define VARIABLE 259
#define K 260
#define DK 261
#define AND 262
#define OR 263
#define NOT 264
#define IMPLY 265
#define ONEOF 266
#define LEFT_PAREN 267
#define RIGHT_PAREN 268
#define COMMA 269
#define COLON 270
#define CONNECTOR 271
#define DEFINE 272
#define DOMAIN 273
#define TYPES 274
#define PREDICATES 275
#define PRECONDITION 276
#define ACTION 277
#define PARAMETERS 278
#define OBSERVE 279
#define EFFECT 280
#define PROBLEM 281
#define OBJECTS 282
#define INIT 283
#define GOAL 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "parse.y"
{
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
/* Line 1529 of yacc.c.  */
#line 123 "parse.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

