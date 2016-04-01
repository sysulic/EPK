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
     VARIABLE = 259,
     K = 260,
     DK = 261,
     AND = 262,
     OR = 263,
     NOT = 264,
     IMPLY = 265,
     ONEOF = 266,
     TRUE = 267,
     FALSE = 268,
     LEFT_PAREN = 269,
     RIGHT_PAREN = 270,
     COMMA = 271,
     COLON = 272,
     CONNECTOR = 273,
     DEFINE = 274,
     DOMAIN = 275,
     TYPES = 276,
     PREDICATES = 277,
     PRECONDITION = 278,
     ACTION = 279,
     PARAMETERS = 280,
     OBSERVE = 281,
     EFFECT = 282,
     PROBLEM = 283,
     OBJECTS = 284,
     INIT = 285,
     GOAL = 286
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
#define TRUE 267
#define FALSE 268
#define LEFT_PAREN 269
#define RIGHT_PAREN 270
#define COMMA 271
#define COLON 272
#define CONNECTOR 273
#define DEFINE 274
#define DOMAIN 275
#define TYPES 276
#define PREDICATES 277
#define PRECONDITION 278
#define ACTION 279
#define PARAMETERS 280
#define OBSERVE 281
#define EFFECT 282
#define PROBLEM 283
#define OBJECTS 284
#define INIT 285
#define GOAL 286




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
  StringList* str_list;
  SingleTypePair* singletype_pair;
  MultiTypeList* multitype_list;
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
#line 185 "parse.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 198 "parse.tab.c"

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
#define YYLAST   201

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNRULES -- Number of states.  */
#define YYNSTATES  176

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    15,    20,    26,    31,    34,
      36,    38,    44,    49,    52,    54,    59,    61,    64,    66,
      70,    73,    75,    78,    80,    82,    84,   105,   126,   128,
     130,   131,   133,   135,   137,   142,   146,   151,   156,   159,
     162,   165,   168,   171,   173,   175,   177,   180,   183,   185,
     188,   190,   192,   197,   201,   209,   213,   215,   217,   222,
     231,   236,   242,   248,   253,   256,   258,   262,   265,   267,
     269,   277
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      33,     0,    -1,    34,    -1,    64,    -1,    14,    19,    35,
      36,    39,    46,    15,    -1,    14,    20,     3,    15,    -1,
      14,    17,    21,    37,    15,    -1,    14,    17,    21,    15,
      -1,    37,    38,    -1,    38,    -1,     3,    -1,    14,    17,
      22,    40,    15,    -1,    14,    17,    22,    15,    -1,    40,
      41,    -1,    41,    -1,    14,    42,    43,    15,    -1,     3,
      -1,    43,    44,    -1,    44,    -1,    45,    18,    38,    -1,
      45,     4,    -1,     4,    -1,    46,    47,    -1,    47,    -1,
      48,    -1,    49,    -1,    14,    17,    24,    50,    17,    25,
      14,    51,    15,    17,    23,    14,    52,    15,    17,    26,
      14,    59,    15,    15,    -1,    14,    17,    24,    50,    17,
      25,    14,    51,    15,    17,    23,    14,    52,    15,    17,
      27,    14,    60,    15,    15,    -1,     3,    -1,    43,    -1,
      -1,    53,    -1,    55,    -1,    56,    -1,    54,    14,    53,
      15,    -1,    14,    53,    15,    -1,     5,    14,    53,    15,
      -1,     6,    14,    53,    15,    -1,     7,    54,    -1,     8,
      54,    -1,     9,    54,    -1,    10,    54,    -1,    11,    54,
      -1,    57,    -1,    12,    -1,    13,    -1,    42,    45,    -1,
      42,    58,    -1,     3,    -1,    58,     3,    -1,     3,    -1,
      56,    -1,    60,    14,    61,    15,    -1,    14,    61,    15,
      -1,    14,    62,    15,    16,    14,    62,    15,    -1,    62,
      16,    63,    -1,    63,    -1,    57,    -1,     9,    14,    57,
      15,    -1,    14,    19,    65,    66,    67,    72,    73,    15,
      -1,    14,    28,     3,    15,    -1,    14,    17,    20,     3,
      15,    -1,    14,    17,    29,    68,    15,    -1,    14,    17,
      29,    15,    -1,    68,    69,    -1,    69,    -1,    70,    18,
      38,    -1,    70,    71,    -1,    71,    -1,     3,    -1,    14,
      17,    30,    14,    53,    15,    15,    -1,    14,    17,    31,
      14,    53,    15,    15,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   115,   115,   115,   120,   134,   142,   146,   152,   157,
     164,   172,   176,   182,   187,   194,   202,   208,   213,   220,
     228,   233,   241,   242,   245,   246,   249,   266,   283,   287,
     288,   292,   296,   297,   300,   309,   315,   319,   325,   326,
     327,   328,   329,   330,   333,   334,   335,   346,   356,   359,
     364,   372,   376,   381,   388,   396,   401,   408,   412,   420,
     436,   442,   450,   454,   460,   465,   472,   480,   485,   492,
     496,   504
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "VARIABLE", "K", "DK", "AND",
  "OR", "NOT", "IMPLY", "ONEOF", "TRUE", "FALSE", "LEFT_PAREN",
  "RIGHT_PAREN", "COMMA", "COLON", "CONNECTOR", "DEFINE", "DOMAIN",
  "TYPES", "PREDICATES", "PRECONDITION", "ACTION", "PARAMETERS", "OBSERVE",
  "EFFECT", "PROBLEM", "OBJECTS", "INIT", "GOAL", "$accept", "epddlDoc",
  "domain", "domainName", "typesDef", "primTypes", "primType",
  "predicatesDef", "atomicFormulaSkeletons", "atomicFormulaSkeleton",
  "predicate", "typedVariableList", "singleTypeVarList", "variables",
  "actionsDef", "action", "senseAction", "onticAction", "actionSymbol",
  "parameters", "precondition", "formula", "formulas", "episFormula",
  "objFormula", "atomicProp", "names", "observe", "effects", "effect",
  "litSet", "lit", "problem", "problemDecl", "problemDomain", "objectDecl",
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
     285,   286
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    33,    34,    35,    36,    36,    37,    37,
      38,    39,    39,    40,    40,    41,    42,    43,    43,    44,
      45,    45,    46,    46,    47,    47,    48,    49,    50,    51,
      51,    52,    53,    53,    54,    54,    55,    55,    56,    56,
      56,    56,    56,    56,    57,    57,    57,    57,    57,    58,
      58,    59,    60,    60,    61,    62,    62,    63,    63,    64,
      65,    66,    67,    67,    68,    68,    69,    70,    70,    71,
      72,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     7,     4,     5,     4,     2,     1,
       1,     5,     4,     2,     1,     4,     1,     2,     1,     3,
       2,     1,     2,     1,     1,     1,    20,    20,     1,     1,
       0,     1,     1,     1,     4,     3,     4,     4,     2,     2,
       2,     2,     2,     1,     1,     1,     2,     2,     1,     2,
       1,     1,     4,     3,     7,     3,     1,     1,     4,     8,
       4,     5,     5,     4,     2,     1,     3,     2,     1,     1,
       7,     7
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,    60,     0,     0,     0,     0,
      23,    24,    25,     0,     0,     0,     0,    10,     7,     0,
       9,     0,     0,     4,    22,     0,     0,     0,     0,     0,
       6,     8,     0,    12,     0,    14,     0,    61,    69,    63,
       0,    65,     0,    68,     0,     0,    59,    16,     0,    11,
      13,    28,     0,    62,    64,     0,    67,     0,     0,    21,
       0,    18,     0,     0,    66,    16,     0,     0,     0,     0,
       0,     0,     0,    44,    45,     0,     0,    32,    33,    43,
       0,    15,    17,    20,     0,     0,     0,     0,     0,    38,
      39,    40,    41,    42,    50,    46,    47,     0,     0,    19,
      30,     0,     0,     0,     0,    49,    70,     0,    29,     0,
      36,    37,    35,     0,    71,     0,    34,     0,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,    51,     0,
       0,     0,     0,     0,     0,     0,     0,    26,     0,    57,
       0,    56,    53,     0,    27,     0,     0,     0,    52,     0,
       0,    55,    58,     0,     0,    54
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     8,    13,    39,    40,    20,    54,    55,
      95,    80,    81,    82,    29,    30,    31,    32,    72,   129,
     140,    96,   109,    97,    98,    99,   116,   149,   151,   154,
     160,   161,     4,     9,    15,    23,    60,    61,    62,    63,
      36,    49
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -151
static const yytype_int16 yypact[] =
{
      -9,   -12,    14,  -151,  -151,    17,  -151,    12,    20,    23,
      18,    24,    42,    74,    56,    76,    77,    78,    70,    72,
      80,    79,    81,    82,  -151,  -151,     9,    73,    83,    46,
    -151,  -151,  -151,    94,    84,    85,    87,  -151,  -151,    10,
    -151,    49,    86,  -151,  -151,    88,    13,    89,    90,    91,
    -151,  -151,   101,  -151,    60,  -151,   102,  -151,  -151,  -151,
      15,  -151,     1,  -151,    95,    92,  -151,  -151,   104,  -151,
    -151,  -151,    97,  -151,  -151,   108,  -151,    45,    98,  -151,
       7,  -151,     2,    93,  -151,    61,   103,   106,   107,   107,
     107,   107,   107,  -151,  -151,    75,   100,  -151,  -151,  -151,
      45,  -151,  -151,  -151,   108,   110,    45,    45,    45,   111,
     111,   111,   111,   111,  -151,   112,   119,   113,   114,  -151,
     104,   115,   116,   117,    45,  -151,  -151,   118,   104,   120,
    -151,  -151,  -151,   121,  -151,   109,  -151,   122,   123,    45,
     124,  -151,   125,    54,   126,   127,    59,   129,  -151,   131,
     130,    68,   132,    26,   133,   130,   134,  -151,   136,  -151,
      69,  -151,  -151,   137,  -151,    30,   135,    26,  -151,   138,
     140,  -151,  -151,    26,    71,  -151
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -151,  -151,  -151,  -151,  -151,  -151,   -39,  -151,  -151,   105,
     128,    35,   -79,    32,  -151,   139,  -151,  -151,  -151,  -151,
    -151,   -98,   -45,  -151,    -8,  -150,  -151,  -151,  -151,   -21,
     -17,   -10,  -151,  -151,  -151,  -151,  -151,   141,  -151,    96,
    -151,  -151
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -49
static const yytype_int16 yytable[] =
{
      51,   102,   118,   159,    58,     1,   103,     5,   121,   122,
     123,    79,    37,    37,     6,   169,    58,   159,    58,    75,
     104,    16,   101,   159,    38,    50,   133,    17,    59,    85,
      73,     7,    10,    85,    12,   158,    84,    14,    93,    94,
      11,   141,    93,    94,   110,   111,   112,   113,    85,   102,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    18,
      28,    43,    85,    52,    53,   119,    88,    89,    90,    91,
      92,    93,    94,    21,    52,    69,   -48,   -48,   114,    79,
     144,   145,   155,   156,   166,   167,   175,   167,    19,    27,
      22,    26,    24,    25,    28,    41,    35,    45,    34,    33,
      42,    48,    47,    57,    67,    71,    66,    65,    79,    77,
      56,    37,   100,    46,    83,   117,   103,   106,   105,    64,
     107,   108,   125,    78,   120,   124,   137,   115,   126,   127,
     130,   131,   132,   134,   163,   135,   136,   139,   148,   142,
     146,   147,   143,   150,   153,   138,   152,   157,   162,   164,
     165,   170,   168,   172,   173,   128,   174,   171,    76,    70,
       0,     0,     0,     0,     0,     0,     0,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      68,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    74
};

static const yytype_int16 yycheck[] =
{
      39,    80,   100,   153,     3,    14,     4,    19,   106,   107,
     108,     4,     3,     3,     0,   165,     3,   167,     3,    18,
      18,     3,    15,   173,    15,    15,   124,     3,    15,     3,
      15,    14,    20,     3,    14,     9,    75,    14,    12,    13,
      28,   139,    12,    13,    89,    90,    91,    92,     3,   128,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    17,
      14,    15,     3,    14,    15,   104,     7,     8,     9,    10,
      11,    12,    13,    17,    14,    15,    15,    16,     3,     4,
      26,    27,    14,    15,    15,    16,    15,    16,    14,    17,
      14,    21,    15,    15,    14,    22,    14,     3,    17,    20,
      17,    14,    17,    15,     3,     3,    15,    17,     4,    14,
      24,     3,    14,    29,    17,    15,     4,    14,    25,    30,
      14,    14,     3,    31,    14,    14,    17,    95,    15,    15,
      15,    15,    15,    15,   155,    15,    15,    14,   146,    15,
      14,    14,    17,    14,    14,    23,    15,    15,    15,    15,
      14,    16,    15,    15,    14,   120,   173,   167,    62,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    33,    34,    64,    19,     0,    14,    35,    65,
      20,    28,    14,    36,    14,    66,     3,     3,    17,    14,
      39,    17,    14,    67,    15,    15,    21,    17,    14,    46,
      47,    48,    49,    20,    17,    14,    72,     3,    15,    37,
      38,    22,    17,    15,    47,     3,    29,    17,    14,    73,
      15,    38,    14,    15,    40,    41,    24,    15,     3,    15,
      68,    69,    70,    71,    30,    17,    15,     3,    42,    15,
      41,     3,    50,    15,    69,    18,    71,    14,    31,     4,
      43,    44,    45,    17,    38,     3,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    42,    53,    55,    56,    57,
      14,    15,    44,     4,    18,    25,    14,    14,    14,    54,
      54,    54,    54,    54,     3,    45,    58,    15,    53,    38,
      14,    53,    53,    53,    14,     3,    15,    15,    43,    51,
      15,    15,    15,    53,    15,    15,    15,    17,    23,    14,
      52,    53,    15,    17,    26,    27,    14,    14,    56,    59,
      14,    60,    15,    14,    61,    14,    15,    15,     9,    57,
      62,    63,    15,    61,    15,    14,    15,    16,    15,    57,
      16,    63,    15,    14,    62,    15
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
#line 126 "parse.y"
    {
		reader.domainName = *(yyvsp[(3) - (7)].str);
		reader.types = *(yyvsp[(4) - (7)].str_set);
		reader.predicates = *(yyvsp[(5) - (7)].pre_set);
		// cout << "domain done" << endl;
	;}
    break;

  case 5:
#line 135 "parse.y"
    {
		(yyval.str) = (yyvsp[(3) - (4)].str);
	;}
    break;

  case 6:
#line 143 "parse.y"
    {
		(yyval.str_set) = (yyvsp[(4) - (5)].str_set);
	;}
    break;

  case 7:
#line 147 "parse.y"
    {
		(yyval.str_set) = new StringSet;
	;}
    break;

  case 8:
#line 153 "parse.y"
    {
		(yyval.str_set) = (yyvsp[(1) - (2)].str_set);
		(yyval.str_set)->insert(*(yyvsp[(2) - (2)].str));
	;}
    break;

  case 9:
#line 158 "parse.y"
    {
		(yyval.str_set) = new StringSet;
		(yyval.str_set)->insert(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 10:
#line 165 "parse.y"
    {
		(yyval.str) =  new string(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 11:
#line 173 "parse.y"
    {
		(yyval.pre_set) = (yyvsp[(4) - (5)].pre_set);
	;}
    break;

  case 12:
#line 177 "parse.y"
    {
		(yyval.pre_set) = new PredicateSet
	;}
    break;

  case 13:
#line 183 "parse.y"
    {
		(yyval.pre_set) = (yyvsp[(1) - (2)].pre_set);
		(yyval.pre_set)->insert(*(yyvsp[(2) - (2)].multitype_pair));
	;}
    break;

  case 14:
#line 188 "parse.y"
    {
		(yyval.pre_set) = new PredicateSet;
		(yyval.pre_set)->insert(*(yyvsp[(1) - (1)].multitype_pair));
	;}
    break;

  case 15:
#line 195 "parse.y"
    {
		(yyval.multitype_pair) = new MultiTypePair;
		(yyval.multitype_pair)->first = *(yyvsp[(2) - (4)].str);
		(yyval.multitype_pair)->second = *(yyvsp[(3) - (4)].multitype_list);
	;}
    break;

  case 16:
#line 203 "parse.y"
    { 
		(yyval.str) = (yyvsp[(1) - (1)].str);
	;}
    break;

  case 17:
#line 209 "parse.y"
    {
		(yyval.multitype_list) = (yyvsp[(1) - (2)].multitype_list);
		(yyval.multitype_list)->push_back(*(yyvsp[(2) - (2)].singletype_pair));
	;}
    break;

  case 18:
#line 214 "parse.y"
    {
		(yyval.multitype_list) = new MultiTypeList;
		(yyval.multitype_list)->push_back(*(yyvsp[(1) - (1)].singletype_pair));
	;}
    break;

  case 19:
#line 221 "parse.y"
    {
		(yyval.singletype_pair) = new SingleTypePair;
		(yyval.singletype_pair)->first = *(yyvsp[(3) - (3)].str);
		(yyval.singletype_pair)->second = *(yyvsp[(1) - (3)].str_list);
	;}
    break;

  case 20:
#line 229 "parse.y"
    {
		(yyval.str_list) = (yyvsp[(1) - (2)].str_list);
		(yyval.str_list)->push_back(*(yyvsp[(2) - (2)].str));
	;}
    break;

  case 21:
#line 234 "parse.y"
    {
		(yyval.str_list) = new StringList;
		(yyval.str_list)->push_back(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 24:
#line 245 "parse.y"
    { reader.senseActions.push_back(*(yyvsp[(1) - (1)].sense_action)); ;}
    break;

  case 25:
#line 246 "parse.y"
    { reader.onticActions.push_back(*(yyvsp[(1) - (1)].ontic_action)); ;}
    break;

  case 26:
#line 255 "parse.y"
    {
		(yyval.sense_action) = new PreSenseAction;
		(yyval.sense_action)->name = *(yyvsp[(4) - (20)].str);
		(yyval.sense_action)->type = *(yyvsp[(16) - (20)].str);
		(yyval.sense_action)->paras = *(yyvsp[(8) - (20)].multitype_list);
		(yyval.sense_action)->preCondition = *(yyvsp[(13) - (20)].tree);
		(yyval.sense_action)->observe = *(yyvsp[(18) - (20)].tree);
		// cout << "senseActions done" << endl;
	;}
    break;

  case 27:
#line 272 "parse.y"
    {
		(yyval.ontic_action) = new PreOnticAction;
		(yyval.ontic_action)->name = *(yyvsp[(4) - (20)].str);
		(yyval.ontic_action)->type = *(yyvsp[(16) - (20)].str);
		(yyval.ontic_action)->paras = *(yyvsp[(8) - (20)].multitype_list);
		(yyval.ontic_action)->preCondition = *(yyvsp[(13) - (20)].tree);
		(yyval.ontic_action)->effects = *(yyvsp[(18) - (20)].eff_set);	
		// cout << "onticAction done" << endl;
	;}
    break;

  case 28:
#line 283 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 29:
#line 287 "parse.y"
    { (yyval.multitype_list) = (yyvsp[(1) - (1)].multitype_list); ;}
    break;

  case 30:
#line 288 "parse.y"
    { (yyval.multitype_list) = new MultiTypeList; ;}
    break;

  case 31:
#line 292 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 32:
#line 296 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 33:
#line 297 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 34:
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

  case 35:
#line 310 "parse.y"
    {
		(yyval.tree) = new Formula("same", (yyvsp[(2) - (3)].tree), NULL);
	;}
    break;

  case 36:
#line 316 "parse.y"
    {
		(yyval.tree) = new Formula("K", (yyvsp[(3) - (4)].tree), NULL);
	;}
    break;

  case 37:
#line 320 "parse.y"
    {
		(yyval.tree) = new Formula("DK", (yyvsp[(3) - (4)].tree), NULL);
	;}
    break;

  case 38:
#line 325 "parse.y"
    { (yyval.tree) = new Formula("&", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 39:
#line 326 "parse.y"
    { (yyval.tree) = new Formula("|", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 40:
#line 327 "parse.y"
    { (yyval.tree) = new Formula("~", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 41:
#line 328 "parse.y"
    { (yyval.tree) = new Formula("=>", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 42:
#line 329 "parse.y"
    { (yyval.tree) = new Formula("oneof", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 43:
#line 330 "parse.y"
    { (yyval.tree) = new Formula(*(yyvsp[(1) - (1)].str)); ;}
    break;

  case 44:
#line 333 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 45:
#line 334 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 46:
#line 336 "parse.y"
    {
		(yyval.str) = new string(*(yyvsp[(1) - (2)].str));
		//bool variable_exist = false;
		for (StringList::iterator ssi = (*(yyvsp[(2) - (2)].str_list)).begin(); ssi != (*(yyvsp[(2) - (2)].str_list)).end(); ssi++)
		{
			//if ((*ssi)[0] == '?') variable_exist = true;
			*(yyval.str) += " " + *ssi;
		}
		//if (!variable_exist) reader.atomicPropSet.insert(*$$);
	;}
    break;

  case 47:
#line 347 "parse.y"
    {
		(yyval.str) = new string(*(yyvsp[(1) - (2)].str));
		//bool variable_exist = false;
		for (StringList::iterator ssi = (*(yyvsp[(2) - (2)].str_list)).begin(); ssi != (*(yyvsp[(2) - (2)].str_list)).end(); ssi++)
		{
			*(yyval.str) += " " + *ssi;
		}
		//reader.atomicPropSet.insert(*$$);
	;}
    break;

  case 48:
#line 356 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); reader.atomicPropSet.insert(*(yyvsp[(1) - (1)].str)); ;}
    break;

  case 49:
#line 360 "parse.y"
    {
		(yyval.str_list) = (yyvsp[(1) - (2)].str_list);
		(yyval.str_list)->push_back(*(yyvsp[(2) - (2)].str));
	;}
    break;

  case 50:
#line 365 "parse.y"
    {
		(yyval.str_list) = new StringList;
		(yyval.str_list)->push_back(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 51:
#line 372 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 52:
#line 377 "parse.y"
    {
		(yyval.eff_set) = (yyvsp[(1) - (4)].eff_set);
		(yyval.eff_set)->push_back(*(yyvsp[(3) - (4)].eff));
	;}
    break;

  case 53:
#line 382 "parse.y"
    {
		(yyval.eff_set) = new EffectList;
		(yyval.eff_set)->push_back(*(yyvsp[(2) - (3)].eff));
	;}
    break;

  case 54:
#line 389 "parse.y"
    {
		(yyval.eff) = new Effect;
		(yyval.eff)->condition = *(yyvsp[(2) - (7)].str_list);
		(yyval.eff)->lits = *(yyvsp[(6) - (7)].str_list);
	;}
    break;

  case 55:
#line 397 "parse.y"
    {
		(yyval.str_list) = (yyvsp[(1) - (3)].str_list);
		(yyval.str_list)->push_back(*(yyvsp[(3) - (3)].str));
	;}
    break;

  case 56:
#line 402 "parse.y"
    {
		(yyval.str_list) = new StringList;
		(yyval.str_list)->push_back(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 57:
#line 409 "parse.y"
    {
		(yyval.str) = (yyvsp[(1) - (1)].str);
	;}
    break;

  case 58:
#line 413 "parse.y"
    {
		(yyval.str) = new string("not(" + *(yyvsp[(3) - (4)].str) + ")");
	;}
    break;

  case 59:
#line 427 "parse.y"
    {
		reader.problemName = *(yyvsp[(3) - (8)].str);
		reader.objects = *(yyvsp[(5) - (8)].multitype_list);
		reader.init = *(yyvsp[(6) - (8)].tree);
		reader.goal = *(yyvsp[(7) - (8)].tree);
		// cout << "problem done" << endl;
	;}
    break;

  case 60:
#line 437 "parse.y"
    {
		(yyval.str) = (yyvsp[(3) - (4)].str);
	;}
    break;

  case 61:
#line 443 "parse.y"
    {
		if (*(yyvsp[(4) - (5)].str) != reader.domainName)
			cout << "Error: Wrong domain name!" << endl;
	;}
    break;

  case 62:
#line 451 "parse.y"
    {
		(yyval.multitype_list) = (yyvsp[(4) - (5)].multitype_list);
	;}
    break;

  case 63:
#line 455 "parse.y"
    {
		(yyval.multitype_list) = new MultiTypeList;
	;}
    break;

  case 64:
#line 461 "parse.y"
    {
		(yyval.multitype_list) = (yyvsp[(1) - (2)].multitype_list);
		(yyval.multitype_list)->push_back(*(yyvsp[(2) - (2)].singletype_pair));
	;}
    break;

  case 65:
#line 466 "parse.y"
    {
		(yyval.multitype_list) = new MultiTypeList;
		(yyval.multitype_list)->push_back(*(yyvsp[(1) - (1)].singletype_pair));
	;}
    break;

  case 66:
#line 473 "parse.y"
    {
		(yyval.singletype_pair) = new SingleTypePair;
		(yyval.singletype_pair)->first = *(yyvsp[(3) - (3)].str);
		(yyval.singletype_pair)->second = *(yyvsp[(1) - (3)].str_list);
	;}
    break;

  case 67:
#line 481 "parse.y"
    {
		(yyval.str_list) = (yyvsp[(1) - (2)].str_list);
		(yyval.str_list)->push_back(*(yyvsp[(2) - (2)].str));
	;}
    break;

  case 68:
#line 486 "parse.y"
    {
		(yyval.str_list) = new StringList;
		(yyval.str_list)->push_back(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 69:
#line 492 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 70:
#line 497 "parse.y"
    {
		(yyval.tree) = (yyvsp[(5) - (7)].tree);
		// cout << "init done" << endl;
	;}
    break;

  case 71:
#line 505 "parse.y"
    {
		(yyval.tree) = (yyvsp[(5) - (7)].tree);
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2038 "parse.tab.c"
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

