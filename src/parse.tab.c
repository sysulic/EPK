/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     K = 259,
     DK = 260,
     AND = 261,
     OR = 262,
     NOT = 263,
     IMPLY = 264,
     ONEOF = 265,
     TRUE = 266,
     FALSE = 267,
     LEFT_PAREN = 268,
     RIGHT_PAREN = 269,
     COMMA = 270,
     COLON = 271,
     CONNECTOR = 272,
     DEFINE = 273,
     DOMAIN = 274,
     TYPES = 275,
     PREDICATES = 276,
     PRECONDITION = 277,
     ACTION = 278,
     PARAMETERS = 279,
     OBSERVE = 280,
     EFFECT = 281,
     PROBLEM = 282,
     OBJECTS = 283,
     INIT = 284,
     GOAL = 285
   };
#endif
/* Tokens.  */
#define NAME 258
#define K 259
#define DK 260
#define AND 261
#define OR 262
#define NOT 263
#define IMPLY 264
#define ONEOF 265
#define TRUE 266
#define FALSE 267
#define LEFT_PAREN 268
#define RIGHT_PAREN 269
#define COMMA 270
#define COLON 271
#define CONNECTOR 272
#define DEFINE 273
#define DOMAIN 274
#define TYPES 275
#define PREDICATES 276
#define PRECONDITION 277
#define ACTION 278
#define PARAMETERS 279
#define OBSERVE 280
#define EFFECT 281
#define PROBLEM 282
#define OBJECTS 283
#define INIT 284
#define GOAL 285




/* Copy the first part of user declarations.  */
#line 7 "parse.y"

#include "reader.h"

int yyerror(char *s);
int yylex(void);

extern Reader reader;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
  PreSenseAction* sense_action;
  PreOnticAction* ontic_action;
  PreSenseActionList* sense_list;
  PreOnticActionList* ontic_list;
  Formula* tree;
}
/* Line 193 of yacc.c.  */
#line 182 "parse.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 195 "parse.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   202

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  190

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    15,    20,    26,    31,    34,
      36,    38,    44,    49,    52,    54,    59,    61,    64,    66,
      70,    73,    75,    78,    80,    82,    84,   105,   126,   128,
     130,   131,   133,   135,   137,   140,   143,   148,   152,   157,
     162,   165,   168,   171,   174,   177,   179,   184,   188,   190,
     192,   195,   197,   199,   204,   208,   216,   220,   222,   224,
     226,   228,   233,   236,   242,   251,   256,   262,   268,   273,
     276,   278,   282,   285,   287,   289,   297
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      32,     0,    -1,    33,    -1,    63,    -1,    13,    18,    34,
      35,    38,    45,    14,    -1,    13,    19,     3,    14,    -1,
      13,    16,    20,    36,    14,    -1,    13,    16,    20,    14,
      -1,    36,    37,    -1,    37,    -1,     3,    -1,    13,    16,
      21,    39,    14,    -1,    13,    16,    21,    14,    -1,    39,
      40,    -1,    40,    -1,    13,    41,    42,    14,    -1,     3,
      -1,    42,    43,    -1,    43,    -1,    44,    17,    37,    -1,
      44,     3,    -1,     3,    -1,    45,    46,    -1,    46,    -1,
      47,    -1,    48,    -1,    13,    16,    23,    49,    16,    24,
      13,    50,    14,    16,    22,    13,    51,    14,    16,    25,
      13,    58,    14,    14,    -1,    13,    16,    23,    49,    16,
      24,    13,    50,    14,    16,    22,    13,    51,    14,    16,
      26,    13,    59,    14,    14,    -1,     3,    -1,    42,    -1,
      -1,    52,    -1,    54,    -1,    55,    -1,     6,    53,    -1,
       7,    53,    -1,    53,    13,    54,    14,    -1,    13,    54,
      14,    -1,     4,    13,    55,    14,    -1,     5,    13,    55,
      14,    -1,     6,    56,    -1,     7,    56,    -1,     8,    56,
      -1,     9,    56,    -1,    10,    56,    -1,    57,    -1,    56,
      13,    55,    14,    -1,    13,    55,    14,    -1,    11,    -1,
      12,    -1,    41,    44,    -1,     3,    -1,    55,    -1,    59,
      13,    60,    14,    -1,    13,    60,    14,    -1,    13,    61,
      14,    15,    13,    61,    14,    -1,    61,    15,    62,    -1,
      62,    -1,    11,    -1,    12,    -1,     3,    -1,     8,    13,
       3,    14,    -1,    41,    44,    -1,     8,    13,    41,    44,
      14,    -1,    13,    18,    64,    65,    66,    71,    72,    14,
      -1,    13,    27,     3,    14,    -1,    13,    16,    19,     3,
      14,    -1,    13,    16,    28,    67,    14,    -1,    13,    16,
      28,    14,    -1,    67,    68,    -1,    68,    -1,    69,    17,
      37,    -1,    69,    70,    -1,    70,    -1,     3,    -1,    13,
      16,    29,    13,    52,    14,    14,    -1,    13,    16,    30,
      13,    52,    14,    14,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   113,   113,   113,   118,   132,   140,   144,   150,   155,
     162,   170,   174,   180,   185,   192,   200,   206,   211,   218,
     226,   231,   239,   240,   243,   244,   247,   264,   281,   285,
     286,   290,   294,   295,   296,   297,   300,   309,   315,   319,
     325,   326,   327,   328,   329,   330,   333,   342,   348,   349,
     350,   359,   363,   367,   372,   379,   387,   392,   399,   400,
     401,   402,   403,   411,   424,   440,   446,   450,   454,   460,
     465,   472,   480,   485,   492,   496,   504
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "K", "DK", "AND", "OR", "NOT",
  "IMPLY", "ONEOF", "TRUE", "FALSE", "LEFT_PAREN", "RIGHT_PAREN", "COMMA",
  "COLON", "CONNECTOR", "DEFINE", "DOMAIN", "TYPES", "PREDICATES",
  "PRECONDITION", "ACTION", "PARAMETERS", "OBSERVE", "EFFECT", "PROBLEM",
  "OBJECTS", "INIT", "GOAL", "$accept", "epddlDoc", "domain", "domainName",
  "typesDef", "primTypes", "primType", "predicatesDef",
  "atomicFormulaSkeletons", "atomicFormulaSkeleton", "predicate",
  "typedVariableList", "singleTypeVarList", "variables", "actionsDef",
  "action", "senseAction", "onticAction", "actionSymbol", "parameters",
  "precondition", "formula", "episFormulas", "episFormula", "objFormula",
  "objFormulas", "atomicProp", "observe", "effects", "effect", "litSet",
  "lit", "problem", "problemDecl", "problemDomain", "objectDecl",
  "objectTypes", "singleType", "objects", "object", "init", "goal", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    32,    33,    34,    35,    35,    36,    36,
      37,    38,    38,    39,    39,    40,    41,    42,    42,    43,
      44,    44,    45,    45,    46,    46,    47,    48,    49,    50,
      50,    51,    52,    52,    52,    52,    53,    53,    54,    54,
      55,    55,    55,    55,    55,    55,    56,    56,    57,    57,
      57,    57,    58,    59,    59,    60,    61,    61,    62,    62,
      62,    62,    62,    62,    63,    64,    65,    66,    66,    67,
      67,    68,    69,    69,    70,    71,    72
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     7,     4,     5,     4,     2,     1,
       1,     5,     4,     2,     1,     4,     1,     2,     1,     3,
       2,     1,     2,     1,     1,     1,    20,    20,     1,     1,
       0,     1,     1,     1,     2,     2,     4,     3,     4,     4,
       2,     2,     2,     2,     2,     1,     4,     3,     1,     1,
       2,     1,     1,     4,     3,     7,     3,     1,     1,     1,
       1,     4,     2,     5,     8,     4,     5,     5,     4,     2,
       1,     3,     2,     1,     1,     7,     7
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,    65,     0,     0,     0,     0,
      23,    24,    25,     0,     0,     0,     0,    10,     7,     0,
       9,     0,     0,     4,    22,     0,     0,     0,     0,     0,
       6,     8,     0,    12,     0,    14,     0,    66,    74,    68,
       0,    70,     0,    73,     0,     0,    64,    16,     0,    11,
      13,    28,     0,    67,    69,     0,    72,     0,     0,    21,
       0,    18,     0,     0,    71,    16,     0,     0,     0,     0,
       0,     0,     0,    48,    49,     0,     0,    32,    33,    45,
       0,    15,    17,    20,     0,     0,     0,     0,     0,    34,
      40,    35,    41,     0,    42,    43,    44,    50,     0,     0,
      19,    30,     0,     0,     0,     0,     0,     0,     0,     0,
      75,     0,    29,     0,    38,    39,    37,    47,     0,     0,
      76,     0,    36,    46,     0,     0,     0,     0,    31,     0,
       0,     0,     0,     0,     0,    52,     0,     0,     0,     0,
       0,     0,     0,     0,    26,    60,     0,    58,    59,     0,
       0,    57,    54,     0,    27,     0,    62,     0,     0,    53,
      16,     0,     0,    56,    61,     0,     0,    63,     0,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     8,    13,    39,    40,    20,    54,    55,
      95,    80,    81,    82,    29,    30,    31,    32,    72,   133,
     147,    96,   109,    97,    98,   110,    99,   156,   158,   161,
     170,   171,     4,     9,    15,    23,    60,    61,    62,    63,
      36,    49
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -103
static const yytype_int16 yypact[] =
{
      -1,     8,    39,  -103,  -103,     4,  -103,    47,    37,    41,
      49,    87,    84,    85,    86,    88,    89,    90,    79,    91,
      92,    93,    94,    96,  -103,  -103,    15,    95,    97,    21,
    -103,  -103,  -103,   103,    99,    98,   102,  -103,  -103,    16,
    -103,    35,   101,  -103,  -103,   104,    17,   100,   105,   106,
    -103,  -103,   108,  -103,    55,  -103,   114,  -103,  -103,  -103,
      18,  -103,     6,  -103,   109,   107,  -103,  -103,   116,  -103,
    -103,  -103,   112,  -103,  -103,   122,  -103,    53,   117,  -103,
      19,  -103,     7,   111,  -103,   118,   120,   123,   125,   125,
     126,   126,   126,  -103,  -103,   116,   127,  -103,  -103,  -103,
      53,  -103,  -103,  -103,   122,   129,    34,    34,    73,   130,
     131,   130,   131,    34,   131,   131,   131,   128,   132,   133,
    -103,   116,   126,   126,   134,   135,   136,   137,    66,    34,
    -103,   138,   116,   139,  -103,  -103,  -103,  -103,   140,   141,
    -103,   124,  -103,  -103,   142,   143,    53,   144,  -103,   145,
      63,   146,   147,    34,   149,  -103,   151,   150,    59,   152,
      83,   153,   150,   154,  -103,   166,   157,  -103,  -103,   116,
      78,  -103,  -103,   158,  -103,   168,   128,   159,    83,  -103,
     161,   116,   160,  -103,  -103,    22,    83,  -103,    82,  -103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -103,  -103,  -103,  -103,  -103,  -103,   -37,  -103,  -103,   148,
     -52,    24,   -77,   -94,  -103,   155,  -103,  -103,  -103,  -103,
    -103,   -93,    68,  -100,  -102,   -76,  -103,  -103,  -103,    14,
      -9,     0,  -103,  -103,  -103,  -103,  -103,   119,  -103,   121,
    -103,  -103
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -52
static const yytype_int16 yytable[] =
{
      68,   117,    51,   102,   124,   125,   127,   119,   126,    58,
     103,   127,     1,   112,   114,   115,   116,     7,    37,    37,
      58,    58,    79,    75,   104,   103,     5,   139,   138,    38,
      50,    59,    73,   101,    28,    43,   187,    85,    84,     6,
     122,   123,    90,    91,    92,    93,    94,   112,    52,    53,
      12,   155,    16,   148,    14,   102,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    10,   120,    52,    69,
      86,    87,   162,   163,    11,   176,    85,    86,    87,   122,
     123,    90,    91,    92,    93,    94,   165,   185,   151,   152,
      17,   166,   177,   178,   167,   168,   189,   178,    19,    26,
      18,    22,    21,    24,    25,    28,    45,    27,   169,    35,
      34,    67,    33,    42,    47,    48,    41,    71,    57,    79,
      66,    65,    77,   181,    56,    37,   169,    46,    83,    64,
     100,   103,   -51,   106,   169,   105,   107,    78,   108,   113,
     144,   118,   121,   128,   129,   132,   130,   131,   134,   135,
     136,   137,   140,   141,   142,   143,   146,   111,   149,   153,
     154,   150,   157,   160,   145,   159,   164,   172,   174,   -16,
     175,   180,   179,   186,   182,   184,   173,   188,   183,    74,
       0,     0,     0,    76,    44,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70
};

static const yytype_int16 yycheck[] =
{
      52,    95,    39,    80,   106,   107,   108,   100,   108,     3,
       3,   113,    13,    89,    90,    91,    92,    13,     3,     3,
       3,     3,     3,    17,    17,     3,    18,   129,   128,    14,
      14,    14,    14,    14,    13,    14,    14,     3,    75,     0,
       6,     7,     8,     9,    10,    11,    12,   123,    13,    14,
      13,   153,     3,   146,    13,   132,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    19,   104,    13,    14,
       4,     5,    13,    14,    27,   169,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,     3,   181,    25,    26,
       3,     8,    14,    15,    11,    12,    14,    15,    13,    20,
      16,    13,    16,    14,    14,    13,     3,    16,   160,    13,
      16,     3,    19,    16,    16,    13,    21,     3,    14,     3,
      14,    16,    13,   175,    23,     3,   178,    28,    16,    29,
      13,     3,    14,    13,   186,    24,    13,    30,    13,    13,
      16,    14,    13,    13,    13,   121,    14,    14,    14,    14,
      14,    14,    14,    14,    14,    14,    13,    89,    14,    13,
      13,    16,    13,    13,    22,    14,    14,    14,    14,     3,
      13,     3,    14,    13,    15,    14,   162,   186,   178,    60,
      -1,    -1,    -1,    62,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    32,    33,    63,    18,     0,    13,    34,    64,
      19,    27,    13,    35,    13,    65,     3,     3,    16,    13,
      38,    16,    13,    66,    14,    14,    20,    16,    13,    45,
      46,    47,    48,    19,    16,    13,    71,     3,    14,    36,
      37,    21,    16,    14,    46,     3,    28,    16,    13,    72,
      14,    37,    13,    14,    39,    40,    23,    14,     3,    14,
      67,    68,    69,    70,    29,    16,    14,     3,    41,    14,
      40,     3,    49,    14,    68,    17,    70,    13,    30,     3,
      42,    43,    44,    16,    37,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    41,    52,    54,    55,    57,
      13,    14,    43,     3,    17,    24,    13,    13,    13,    53,
      56,    53,    56,    13,    56,    56,    56,    44,    14,    52,
      37,    13,     6,     7,    55,    55,    54,    55,    13,    13,
      14,    14,    42,    50,    14,    14,    14,    14,    54,    55,
      14,    14,    14,    14,    16,    22,    13,    51,    52,    14,
      16,    25,    26,    13,    13,    55,    58,    13,    59,    14,
      13,    60,    13,    14,    14,     3,     8,    11,    12,    41,
      61,    62,    14,    60,    14,    13,    44,    14,    15,    14,
       3,    41,    15,    62,    14,    44,    13,    14,    61,    14
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 124 "parse.y"
    {
		reader.domainName = *(yyvsp[(3) - (7)].str);
		reader.types = *(yyvsp[(4) - (7)].str_set);
		reader.predicates = *(yyvsp[(5) - (7)].pre_set);
		// cout << "domain done" << endl;
	;}
    break;

  case 5:
#line 133 "parse.y"
    {
		(yyval.str) = (yyvsp[(3) - (4)].str);
	;}
    break;

  case 6:
#line 141 "parse.y"
    {
		(yyval.str_set) = (yyvsp[(4) - (5)].str_set);
	;}
    break;

  case 7:
#line 145 "parse.y"
    {
		(yyval.str_set) = new StringSet;
	;}
    break;

  case 8:
#line 151 "parse.y"
    {
		(yyval.str_set) = (yyvsp[(1) - (2)].str_set);
		(yyval.str_set)->insert(*(yyvsp[(2) - (2)].str));
	;}
    break;

  case 9:
#line 156 "parse.y"
    {
		(yyval.str_set) = new StringSet;
		(yyval.str_set)->insert(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 10:
#line 163 "parse.y"
    {
		(yyval.str) =  new string(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 11:
#line 171 "parse.y"
    {
		(yyval.pre_set) = (yyvsp[(4) - (5)].pre_set);
	;}
    break;

  case 12:
#line 175 "parse.y"
    {
		(yyval.pre_set) = new PredicateSet
	;}
    break;

  case 13:
#line 181 "parse.y"
    {
		(yyval.pre_set) = (yyvsp[(1) - (2)].pre_set);
		(yyval.pre_set)->insert(*(yyvsp[(2) - (2)].multitype_pair));
	;}
    break;

  case 14:
#line 186 "parse.y"
    {
		(yyval.pre_set) = new PredicateSet;
		(yyval.pre_set)->insert(*(yyvsp[(1) - (1)].multitype_pair));
	;}
    break;

  case 15:
#line 193 "parse.y"
    {
		(yyval.multitype_pair) = new MultiTypePair;
		(yyval.multitype_pair)->first = *(yyvsp[(2) - (4)].str);
		(yyval.multitype_pair)->second = *(yyvsp[(3) - (4)].multitype_set);
	;}
    break;

  case 16:
#line 201 "parse.y"
    { 
		(yyval.str) = (yyvsp[(1) - (1)].str);
	;}
    break;

  case 17:
#line 207 "parse.y"
    {
		(yyval.multitype_set) = (yyvsp[(1) - (2)].multitype_set);
		(yyval.multitype_set)->insert(*(yyvsp[(2) - (2)].singletype_pair));
	;}
    break;

  case 18:
#line 212 "parse.y"
    {
		(yyval.multitype_set) = new MultiTypeSet;
		(yyval.multitype_set)->insert(*(yyvsp[(1) - (1)].singletype_pair));
	;}
    break;

  case 19:
#line 219 "parse.y"
    {
		(yyval.singletype_pair) = new SingleTypePair;
		(yyval.singletype_pair)->first = *(yyvsp[(3) - (3)].str);
		(yyval.singletype_pair)->second = *(yyvsp[(1) - (3)].str_set);
	;}
    break;

  case 20:
#line 227 "parse.y"
    {
		(yyval.str_set) = (yyvsp[(1) - (2)].str_set);
		(yyval.str_set)->insert(*(yyvsp[(2) - (2)].str));
	;}
    break;

  case 21:
#line 232 "parse.y"
    {
		(yyval.str_set) = new StringSet;
		(yyval.str_set)->insert(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 24:
#line 243 "parse.y"
    { reader.senseActions.insert(reader.senseActions.begin(), *(yyvsp[(1) - (1)].sense_action)); ;}
    break;

  case 25:
#line 244 "parse.y"
    { reader.onticActions.insert(reader.onticActions.begin(), *(yyvsp[(1) - (1)].ontic_action)); ;}
    break;

  case 26:
#line 253 "parse.y"
    {
		(yyval.sense_action) = new PreSenseAction;
		(yyval.sense_action)->name = *(yyvsp[(4) - (20)].str);
		(yyval.sense_action)->type = *(yyvsp[(16) - (20)].str);
		(yyval.sense_action)->paras = *(yyvsp[(8) - (20)].multitype_set);
		(yyval.sense_action)->preCondition = *(yyvsp[(13) - (20)].tree);
		(yyval.sense_action)->observe = *(yyvsp[(18) - (20)].tree);
		// cout << "senseActions done" << endl;
	;}
    break;

  case 27:
#line 270 "parse.y"
    {
		(yyval.ontic_action) = new PreOnticAction;
		(yyval.ontic_action)->name = *(yyvsp[(4) - (20)].str);
		(yyval.ontic_action)->type = *(yyvsp[(16) - (20)].str);
		(yyval.ontic_action)->paras = *(yyvsp[(8) - (20)].multitype_set);
		(yyval.ontic_action)->preCondition = *(yyvsp[(13) - (20)].tree);
		(yyval.ontic_action)->effects = *(yyvsp[(18) - (20)].eff_set);	
		// cout << "onticAction done" << endl;
	;}
    break;

  case 28:
#line 281 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 29:
#line 285 "parse.y"
    { (yyval.multitype_set) = (yyvsp[(1) - (1)].multitype_set); ;}
    break;

  case 30:
#line 286 "parse.y"
    { (yyval.multitype_set) = new MultiTypeSet; ;}
    break;

  case 31:
#line 290 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 32:
#line 294 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 33:
#line 295 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 34:
#line 296 "parse.y"
    { (yyval.tree) = new Formula("&", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 35:
#line 297 "parse.y"
    { (yyval.tree) = new Formula("|", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 36:
#line 301 "parse.y"
    {
		if ((yyvsp[(1) - (4)].tree)->right == NULL) {
			(yyval.tree) = (yyvsp[(1) - (4)].tree);
		} else {
			(yyval.tree) = new Formula("same", (yyvsp[(1) - (4)].tree), NULL);
		}
		(yyval.tree)->right = (yyvsp[(3) - (4)].tree);
	;}
    break;

  case 37:
#line 310 "parse.y"
    {
		(yyval.tree) = new Formula("same", (yyvsp[(2) - (3)].tree), NULL);
	;}
    break;

  case 38:
#line 316 "parse.y"
    {
		(yyval.tree) = new Formula("K", (yyvsp[(3) - (4)].tree), NULL);
	;}
    break;

  case 39:
#line 320 "parse.y"
    {
		(yyval.tree) = new Formula("DK", (yyvsp[(3) - (4)].tree), NULL);
	;}
    break;

  case 40:
#line 325 "parse.y"
    { (yyval.tree) = new Formula("&", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 41:
#line 326 "parse.y"
    { (yyval.tree) = new Formula("|", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 42:
#line 327 "parse.y"
    { (yyval.tree) = new Formula("!", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 43:
#line 328 "parse.y"
    { (yyval.tree) = new Formula("->", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 44:
#line 329 "parse.y"
    { (yyval.tree) = new Formula("oneof", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 45:
#line 330 "parse.y"
    { (yyval.tree) = new Formula(*(yyvsp[(1) - (1)].str)); ;}
    break;

  case 46:
#line 334 "parse.y"
    {
		if ((yyvsp[(1) - (4)].tree)->right == NULL) {
			(yyval.tree) = (yyvsp[(1) - (4)].tree);
		} else {
			(yyval.tree) = new Formula("same", (yyvsp[(1) - (4)].tree), NULL);
		}
		(yyval.tree)->right = (yyvsp[(3) - (4)].tree);
	;}
    break;

  case 47:
#line 343 "parse.y"
    {
		(yyval.tree) = new Formula("same", (yyvsp[(2) - (3)].tree), NULL);
	;}
    break;

  case 48:
#line 348 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 49:
#line 349 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 50:
#line 351 "parse.y"
    {
		(yyval.str) = new string(*(yyvsp[(1) - (2)].str));
		for (StringSet::iterator ssi = (*(yyvsp[(2) - (2)].str_set)).begin(); ssi != (*(yyvsp[(2) - (2)].str_set)).end(); ssi++)
		{
			*(yyval.str) += " " + *ssi;
		}
		reader.atomicPropSet.insert(*(yyval.str));
	;}
    break;

  case 51:
#line 359 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); reader.atomicPropSet.insert(*(yyvsp[(1) - (1)].str)); ;}
    break;

  case 52:
#line 363 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 53:
#line 368 "parse.y"
    {
		(yyval.eff_set) = (yyvsp[(1) - (4)].eff_set);
		(yyval.eff_set)->insert((yyval.eff_set)->begin(), *(yyvsp[(3) - (4)].eff));
	;}
    break;

  case 54:
#line 373 "parse.y"
    {
		(yyval.eff_set) = new EffectList;
		(yyval.eff_set)->insert((yyval.eff_set)->begin(), *(yyvsp[(2) - (3)].eff));
	;}
    break;

  case 55:
#line 380 "parse.y"
    {
		(yyval.eff) = new Effect;
		(yyval.eff)->condition = *(yyvsp[(2) - (7)].str_set);
		(yyval.eff)->lits = *(yyvsp[(6) - (7)].str_set);
	;}
    break;

  case 56:
#line 388 "parse.y"
    {
		(yyval.str_set) = (yyvsp[(1) - (3)].str_set);
		(yyval.str_set)->insert(*(yyvsp[(3) - (3)].str));
	;}
    break;

  case 57:
#line 393 "parse.y"
    {
		(yyval.str_set) = new StringSet;
		(yyval.str_set)->insert(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 58:
#line 399 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 59:
#line 400 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 60:
#line 401 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); reader.atomicPropSet.insert(*(yyvsp[(1) - (1)].str)); ;}
    break;

  case 61:
#line 402 "parse.y"
    { (yyval.str) = new string("not(" + *(yyvsp[(3) - (4)].str) + ")");;}
    break;

  case 62:
#line 404 "parse.y"
    {
		(yyval.str) = new string(*(yyvsp[(1) - (2)].str));
		for (StringSet::iterator ssi = (*(yyvsp[(2) - (2)].str_set)).begin(); ssi != (*(yyvsp[(2) - (2)].str_set)).end(); ssi++)
		{
			*(yyval.str) += " " + *ssi;
		}
	;}
    break;

  case 63:
#line 412 "parse.y"
    { 
		(yyval.str) = new string("not("+*(yyvsp[(3) - (5)].str));
		for (StringSet::iterator ssi = (*(yyvsp[(4) - (5)].str_set)).begin(); ssi != (*(yyvsp[(4) - (5)].str_set)).end(); ssi++)
		{
			*(yyval.str) += " " + *ssi;
		}
		*(yyval.str) += ")";
	;}
    break;

  case 64:
#line 431 "parse.y"
    {
		reader.problemName = *(yyvsp[(3) - (8)].str);
		reader.objects = *(yyvsp[(5) - (8)].multitype_set);
		reader.init = *(yyvsp[(6) - (8)].tree);
		reader.goal = *(yyvsp[(7) - (8)].tree);
		// cout << "problem done" << endl;
	;}
    break;

  case 65:
#line 441 "parse.y"
    {
		(yyval.str) = (yyvsp[(3) - (4)].str);
	;}
    break;

  case 67:
#line 451 "parse.y"
    {
		(yyval.multitype_set) = (yyvsp[(4) - (5)].multitype_set);
	;}
    break;

  case 68:
#line 455 "parse.y"
    {
		(yyval.multitype_set) = new MultiTypeSet;
	;}
    break;

  case 69:
#line 461 "parse.y"
    {
		(yyval.multitype_set) = (yyvsp[(1) - (2)].multitype_set);
		(yyval.multitype_set)->insert(*(yyvsp[(2) - (2)].singletype_pair));
	;}
    break;

  case 70:
#line 466 "parse.y"
    {
		(yyval.multitype_set) = new MultiTypeSet;
		(yyval.multitype_set)->insert(*(yyvsp[(1) - (1)].singletype_pair));
	;}
    break;

  case 71:
#line 473 "parse.y"
    {
		(yyval.singletype_pair) = new SingleTypePair;
		(yyval.singletype_pair)->first = *(yyvsp[(3) - (3)].str);
		(yyval.singletype_pair)->second = *(yyvsp[(1) - (3)].str_set);
	;}
    break;

  case 72:
#line 481 "parse.y"
    {
		(yyval.str_set) = (yyvsp[(1) - (2)].str_set);
		(yyval.str_set)->insert(*(yyvsp[(2) - (2)].str));
	;}
    break;

  case 73:
#line 486 "parse.y"
    {
		(yyval.str_set) = new StringSet;
		(yyval.str_set)->insert(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 74:
#line 492 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 75:
#line 497 "parse.y"
    {
		(yyval.tree) = (yyvsp[(5) - (7)].tree);
		// cout << "init done" << endl;
	;}
    break;

  case 76:
#line 505 "parse.y"
    {
		(yyval.tree) = (yyvsp[(5) - (7)].tree);
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2059 "parse.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 510 "parse.y"


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

