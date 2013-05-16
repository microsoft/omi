
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "mof.y"


#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MI.h>
#include "buffer.h"
#include "types.h"
#include "state.h"
#include "ptrarray.h"

#define ARRAYOF(TYPE) ((MI_Uint32)TYPE | (MI_Uint32)MI_ARRAY_BIT)

extern int yylex();
extern int openIncludeFile(const char* path);



/* Line 189 of yacc.c  */
#line 93 "mof.tab.c"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_ERROR = 258,
     TOK_BOOLEAN = 259,
     TOK_SINT8 = 260,
     TOK_UINT8 = 261,
     TOK_SINT16 = 262,
     TOK_UINT16 = 263,
     TOK_SINT32 = 264,
     TOK_UINT32 = 265,
     TOK_SINT64 = 266,
     TOK_UINT64 = 267,
     TOK_REAL32 = 268,
     TOK_REAL64 = 269,
     TOK_DATETIME = 270,
     TOK_CHAR16 = 271,
     TOK_STRING = 272,
     TOK_BOOLEAN_VALUE = 273,
     TOK_REF = 274,
     TOK_SCOPE = 275,
     TOK_CLASS = 276,
     TOK_QUALIFIER = 277,
     TOK_OBJECT = 278,
     TOK_FLAVOR = 279,
     TOK_INSTANCE = 280,
     TOK_OF = 281,
     TOK_AS = 282,
     TOK_PRAGMA = 283,
     TOK_INTEGER_VALUE = 284,
     TOK_REAL_VALUE = 285,
     TOK_STRING_VALUE = 286,
     TOK_CHAR_VALUE = 287,
     TOK_IDENT = 288,
     TOK_ALIAS_IDENTIFIER = 289,
     TOK_NULL = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 21 "mof.y"

    MI_Boolean boolean;
    MI_Sint64 integer;
    MI_Real64 real;
    MI_Char16 character;
    char* string;
    char* identifier;
    char* dollarIdentifier;
    MI_Type type;
    MI_PropertyDecl* property;
    MI_MethodDecl* methodDecl;
    MI_ParameterDecl* parameter;
    MOF_ParameterList parameterList;
    MOF_FeatureList featureList;
    MI_QualifierDecl* qualifierDeclaration;
    MOF_ConstantValue constantValue;
    MOF_Initializer initializer;
    MI_Uint32 flags;
    MI_Qualifier* qualifier;
    MOF_QualifierList qualifierList;
    MI_ClassDecl* classDeclaration;
    MI_InstanceDecl* instanceDeclaration;



/* Line 214 of yacc.c  */
#line 190 "mof.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 202 "mof.tab.c"

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
# if YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  27
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   598

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  166
/* YYNRULES -- Number of states.  */
#define YYNSTATES  338

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      36,    37,     2,     2,    38,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,    42,
       2,    43,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      24,    32,    36,    42,    47,    54,    59,    63,    65,    67,
      69,    71,    73,    75,    78,    81,    84,    87,    90,    93,
      97,   102,   107,   113,   119,   126,   133,   141,   145,   150,
     155,   161,   167,   174,   181,   189,   193,   198,   203,   209,
     215,   222,   229,   237,   242,   248,   254,   261,   268,   276,
     284,   293,   298,   304,   310,   317,   324,   332,   340,   349,
     356,   364,   370,   377,   379,   383,   386,   390,   394,   399,
     403,   408,   413,   419,   425,   432,   435,   440,   444,   450,
     456,   458,   462,   464,   466,   470,   473,   479,   486,   494,
     503,   507,   510,   512,   515,   518,   522,   527,   533,   537,
     539,   543,   545,   548,   552,   557,   561,   563,   569,   571,
     575,   577,   580,   582,   584,   586,   590,   593,   595,   599,
     601,   603,   608,   610,   612,   616,   619,   621,   625,   627,
     629,   631,   633,   635,   637,   639,   642,   644,   646,   648,
     650,   652,   654,   656,   658,   660,   662,   664,   666,   668,
     670,   672,   674,   676,   678,   680,   682
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    48,    -1,    47,    48,    -1,     3,    -1,
      49,    -1,    50,    -1,    61,    -1,    67,    -1,    28,    33,
      36,    87,    37,    -1,    28,    33,    36,    87,    38,    33,
      37,    -1,    21,    88,    51,    -1,    21,    88,    39,    88,
      51,    -1,    71,    21,    88,    51,    -1,    71,    21,    89,
      39,    89,    51,    -1,    40,    52,    41,    42,    -1,    40,
      41,    42,    -1,    53,    -1,    58,    -1,    56,    -1,    57,
      -1,    54,    -1,    55,    -1,    52,    53,    -1,    52,    58,
      -1,    52,    56,    -1,    52,    57,    -1,    52,    54,    -1,
      52,    55,    -1,    90,    88,    42,    -1,    71,    90,    88,
      42,    -1,    90,    88,    66,    42,    -1,    71,    90,    88,
      66,    42,    -1,    90,    88,    43,    79,    42,    -1,    71,
      90,    88,    43,    79,    42,    -1,    90,    88,    66,    43,
      79,    42,    -1,    71,    90,    88,    66,    43,    79,    42,
      -1,    89,    88,    42,    -1,    71,    89,    88,    42,    -1,
      89,    88,    66,    42,    -1,    71,    89,    88,    66,    42,
      -1,    89,    88,    43,    79,    42,    -1,    71,    89,    88,
      43,    79,    42,    -1,    89,    88,    66,    43,    79,    42,
      -1,    71,    89,    88,    66,    43,    79,    42,    -1,    23,
      88,    42,    -1,    71,    23,    88,    42,    -1,    23,    88,
      66,    42,    -1,    71,    23,    88,    66,    42,    -1,    23,
      88,    43,    79,    42,    -1,    71,    23,    88,    43,    79,
      42,    -1,    23,    88,    66,    43,    79,    42,    -1,    71,
      23,    88,    66,    43,    79,    42,    -1,    89,    19,    88,
      42,    -1,    71,    89,    19,    88,    42,    -1,    89,    19,
      88,    66,    42,    -1,    71,    89,    19,    88,    66,    42,
      -1,    89,    19,    88,    43,    79,    42,    -1,    71,    89,
      19,    88,    43,    79,    42,    -1,    89,    19,    88,    66,
      43,    79,    42,    -1,    71,    89,    19,    88,    66,    43,
      79,    42,    -1,    23,    19,    88,    42,    -1,    71,    23,
      19,    88,    42,    -1,    23,    19,    88,    66,    42,    -1,
      71,    23,    19,    88,    66,    42,    -1,    23,    19,    88,
      43,    79,    42,    -1,    23,    19,    88,    66,    43,    79,
      42,    -1,    71,    23,    19,    88,    43,    79,    42,    -1,
      71,    23,    19,    88,    66,    43,    79,    42,    -1,    90,
      88,    36,    59,    37,    42,    -1,    71,    90,    88,    36,
      59,    37,    42,    -1,    90,    88,    36,    37,    42,    -1,
      71,    90,    88,    36,    37,    42,    -1,    60,    -1,    59,
      38,    60,    -1,    90,    88,    -1,    71,    90,    88,    -1,
      88,    19,    88,    -1,    71,    88,    19,    88,    -1,    90,
      88,    66,    -1,    71,    90,    88,    66,    -1,    88,    19,
      88,    66,    -1,    71,    88,    19,    88,    66,    -1,    22,
      88,    62,    63,    42,    -1,    22,    88,    62,    63,    75,
      42,    -1,    39,    90,    -1,    39,    90,    43,    83,    -1,
      39,    90,    66,    -1,    39,    90,    66,    43,    83,    -1,
      38,    20,    36,    64,    37,    -1,    65,    -1,    64,    38,
      65,    -1,    88,    -1,    21,    -1,    44,    29,    45,    -1,
      44,    45,    -1,    25,    26,    89,    68,    42,    -1,    71,
      25,    26,    89,    68,    42,    -1,    25,    26,    89,    27,
      34,    68,    42,    -1,    71,    25,    26,    89,    27,    34,
      68,    42,    -1,    40,    69,    41,    -1,    40,    41,    -1,
      70,    -1,    69,    70,    -1,    88,    42,    -1,    71,    88,
      42,    -1,    88,    43,    79,    42,    -1,    71,    88,    43,
      79,    42,    -1,    44,    72,    45,    -1,    73,    -1,    72,
      38,    73,    -1,    88,    -1,    88,    74,    -1,    88,    39,
      77,    -1,    88,    74,    39,    77,    -1,    36,    86,    37,
      -1,    84,    -1,    38,    24,    36,    76,    37,    -1,    78,
      -1,    76,    38,    78,    -1,    78,    -1,    77,    78,    -1,
      88,    -1,    82,    -1,    80,    -1,    40,    81,    41,    -1,
      40,    41,    -1,    82,    -1,    81,    38,    82,    -1,    86,
      -1,    34,    -1,    25,    26,    88,    68,    -1,    86,    -1,
      84,    -1,    40,    85,    41,    -1,    40,    41,    -1,    86,
      -1,    85,    38,    86,    -1,    87,    -1,    29,    -1,    18,
      -1,    30,    -1,    32,    -1,    35,    -1,    31,    -1,    87,
      31,    -1,    33,    -1,     4,    -1,    15,    -1,    17,    -1,
      23,    -1,    22,    -1,    33,    -1,     4,    -1,     5,    -1,
       6,    -1,     7,    -1,     8,    -1,     9,    -1,    10,    -1,
      11,    -1,    12,    -1,    13,    -1,    14,    -1,    16,    -1,
      15,    -1,    17,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   133,   133,   136,   139,   145,   148,   159,   166,   178,
     214,   252,   269,   300,   323,   362,   366,   375,   389,   399,
     409,   419,   429,   439,   457,   470,   483,   495,   508,   523,
     529,   541,   548,   561,   576,   597,   613,   637,   654,   677,
     695,   719,   738,   763,   783,   811,   818,   831,   839,   853,
     862,   873,   883,   897,   914,   937,   955,   979,   998,  1023,
    1043,  1071,  1078,  1091,  1099,  1113,  1122,  1132,  1147,  1165,
    1173,  1187,  1197,  1215,  1223,  1238,  1244,  1256,  1273,  1296,
    1303,  1316,  1334,  1360,  1367,  1376,  1381,  1396,  1402,  1420,
    1426,  1430,  1436,  1447,  1453,  1464,  1471,  1479,  1489,  1498,
    1511,  1515,  1522,  1530,  1545,  1553,  1563,  1579,  1599,  1605,
    1611,  1624,  1651,  1679,  1706,  1736,  1743,  1749,  1779,  1783,
    1789,  1793,  1799,  1812,  1820,  1826,  1830,  1838,  1846,  1856,
    1860,  1867,  1876,  1883,  1889,  1893,  1901,  1909,  1919,  1924,
    1929,  1934,  1939,  1944,  1950,  1954,  1966,  1970,  1974,  1978,
    1982,  1986,  1995,  2001,  2005,  2009,  2013,  2017,  2021,  2025,
    2029,  2033,  2037,  2041,  2045,  2049,  2053
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_ERROR", "TOK_BOOLEAN", "TOK_SINT8",
  "TOK_UINT8", "TOK_SINT16", "TOK_UINT16", "TOK_SINT32", "TOK_UINT32",
  "TOK_SINT64", "TOK_UINT64", "TOK_REAL32", "TOK_REAL64", "TOK_DATETIME",
  "TOK_CHAR16", "TOK_STRING", "TOK_BOOLEAN_VALUE", "TOK_REF", "TOK_SCOPE",
  "TOK_CLASS", "TOK_QUALIFIER", "TOK_OBJECT", "TOK_FLAVOR", "TOK_INSTANCE",
  "TOK_OF", "TOK_AS", "TOK_PRAGMA", "TOK_INTEGER_VALUE", "TOK_REAL_VALUE",
  "TOK_STRING_VALUE", "TOK_CHAR_VALUE", "TOK_IDENT",
  "TOK_ALIAS_IDENTIFIER", "TOK_NULL", "'('", "')'", "','", "':'", "'{'",
  "'}'", "';'", "'='", "'['", "']'", "$accept", "mofSpecification",
  "mofProduction", "compilerDirective", "classDeclaration", "classBody",
  "classFeatureList", "propertyDeclaration", "staticInstanceDeclaration",
  "lazyInstanceDeclaration", "referenceDeclaration",
  "lazyReferenceDeclaration", "methodDeclaration", "parameterList",
  "parameter", "qualifierDeclaration", "qualifierType", "scopeExpr",
  "scopeList", "scope", "subscript", "instanceDeclaration", "instanceBody",
  "valueDeclarationList", "valueDeclaration", "qualifierExpr",
  "qualifierList", "qualifier", "qualifierParameter", "flavorExpr",
  "flavorList", "qualifierFlavorList", "flavor", "initializer",
  "arrayInitializer", "arrayInitializerList", "scalarInitializer",
  "nonAggregateInitializer", "nonAggregateArrayInitializer",
  "nonAggregateArrayInitializerList", "constantValue", "stringValue",
  "identifier", "restrictedIdentifier", "dataType", 0
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
     285,   286,   287,   288,   289,   290,    40,    41,    44,    58,
     123,   125,    59,    61,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    47,    47,    48,    48,    48,    48,    49,
      49,    50,    50,    50,    50,    51,    51,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    53,
      53,    53,    53,    53,    53,    53,    53,    54,    54,    54,
      54,    54,    54,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    56,    56,    56,    56,    56,    56,    56,
      56,    57,    57,    57,    57,    57,    57,    57,    57,    58,
      58,    58,    58,    59,    59,    60,    60,    60,    60,    60,
      60,    60,    60,    61,    61,    62,    62,    62,    62,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    67,    67,
      68,    68,    69,    69,    70,    70,    70,    70,    71,    72,
      72,    73,    73,    73,    73,    74,    74,    75,    76,    76,
      77,    77,    78,    79,    79,    80,    80,    81,    81,    82,
      82,    82,    83,    83,    84,    84,    85,    85,    86,    86,
      86,    86,    86,    86,    87,    87,    88,    88,    88,    88,
      88,    88,    89,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     5,
       7,     3,     5,     4,     6,     4,     3,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     3,
       4,     4,     5,     5,     6,     6,     7,     3,     4,     4,
       5,     5,     6,     6,     7,     3,     4,     4,     5,     5,
       6,     6,     7,     4,     5,     5,     6,     6,     7,     7,
       8,     4,     5,     5,     6,     6,     7,     7,     8,     6,
       7,     5,     6,     1,     3,     2,     3,     3,     4,     3,
       4,     4,     5,     5,     6,     2,     4,     3,     5,     5,
       1,     3,     1,     1,     3,     2,     5,     6,     7,     8,
       3,     2,     1,     2,     2,     3,     4,     5,     3,     1,
       3,     1,     2,     3,     4,     3,     1,     5,     1,     3,
       1,     2,     1,     1,     1,     3,     2,     1,     3,     1,
       1,     4,     1,     1,     3,     2,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     4,     0,     0,     0,     0,     0,     0,     2,     5,
       6,     7,     8,     0,   147,   148,   149,   151,   150,   146,
       0,     0,     0,     0,     0,   109,   111,     1,     3,     0,
       0,     0,     0,    11,     0,     0,   152,     0,     0,     0,
     108,     0,     0,     0,   112,   116,   146,     0,     0,     0,
       0,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   165,   164,   166,     0,     0,     0,    17,    21,
      22,    19,    20,    18,     0,     0,     0,    85,     0,     0,
       0,     0,     0,   144,     0,   110,   140,   139,   141,   142,
     143,     0,   138,   113,   120,   122,   135,     0,   136,     0,
      13,     0,     0,    12,     0,     0,    16,     0,    23,    27,
      28,    25,    26,    24,     0,     0,     0,     0,     0,     0,
       0,     0,    87,     0,     0,    83,     0,     0,   101,     0,
     102,     0,     0,    96,   145,     9,     0,   115,   121,     0,
     134,   114,     0,     0,     0,     0,    45,     0,     0,    15,
       0,     0,     0,     0,     0,     0,    37,     0,     0,     0,
      29,     0,     0,    86,   133,   132,     0,    95,     0,     0,
       0,    84,     0,   100,   103,     0,   104,     0,     0,   137,
      14,     0,    97,    61,     0,     0,     0,   130,     0,     0,
     124,   123,   129,    47,     0,     0,    46,     0,     0,     0,
      38,     0,     0,     0,    30,     0,     0,    53,     0,     0,
       0,    39,     0,   153,   165,   166,     0,     0,    73,     0,
       0,     0,     0,    31,     0,    94,    88,    93,     0,    90,
      92,     0,    98,   105,     0,     0,    10,     0,     0,    63,
       0,     0,   126,     0,   127,    49,     0,    62,     0,     0,
       0,    48,     0,    54,     0,     0,     0,    40,     0,     0,
       0,     0,    32,     0,     0,    55,     0,    41,     0,    71,
       0,     0,     0,     0,     0,    75,    33,     0,    89,     0,
       0,   118,     0,   106,    99,    65,     0,     0,     0,   125,
      51,     0,    64,     0,    50,     0,     0,    56,     0,    42,
       0,    72,     0,    34,     0,    57,     0,    43,    69,    74,
       0,    76,    77,    79,    35,    91,   117,     0,   107,    66,
     131,   128,    67,     0,    52,    58,     0,    44,    70,    36,
      59,    78,    80,    81,   119,    68,    60,    82
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    33,    67,    68,    69,    70,
      71,    72,    73,   217,   218,    11,    35,    79,   228,   229,
     122,    12,    82,   129,   130,   219,    24,    25,    44,   126,
     280,    93,    94,   189,   190,   243,   191,   163,   164,    97,
     192,    92,    95,    75,   221
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -183
static const yytype_int16 yypact[] =
{
      43,  -183,   513,   513,     5,     3,   513,    13,  -183,  -183,
    -183,  -183,  -183,    18,  -183,  -183,  -183,  -183,  -183,  -183,
     -18,    10,    26,    20,   -21,  -183,    22,  -183,  -183,   522,
      46,   513,   319,  -183,   581,    28,  -183,    -8,    52,   513,
    -183,   326,   513,   192,    55,  -183,    59,    76,    79,    26,
      76,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,   174,    82,   360,  -183,  -183,
    -183,  -183,  -183,  -183,   472,   183,   513,   101,   106,    47,
      94,   136,   100,  -183,    38,  -183,  -183,  -183,  -183,  -183,
    -183,   110,   125,   513,  -183,  -183,  -183,    40,  -183,   513,
    -183,    26,    -7,  -183,   513,    67,  -183,   133,  -183,  -183,
    -183,  -183,  -183,  -183,   487,   496,   513,   513,   121,    57,
      90,   -19,    89,   154,   155,  -183,   152,   178,  -183,   151,
    -183,   513,    96,  -183,  -183,  -183,   187,  -183,  -183,   326,
    -183,   513,    76,   191,   184,   169,  -183,   544,   128,  -183,
     513,   188,   513,   193,   118,   213,  -183,   544,   140,   237,
    -183,   544,   143,  -183,  -183,  -183,   189,  -183,    90,   510,
     202,  -183,   198,  -183,  -183,   161,  -183,   544,   221,  -183,
    -183,   178,  -183,  -183,   544,   172,   247,  -183,   529,   238,
    -183,  -183,  -183,  -183,   544,   219,  -183,   544,   225,   222,
    -183,   544,   233,   278,  -183,   544,   236,  -183,   544,   254,
     274,  -183,   544,   295,   298,   299,   277,   261,  -183,   442,
     301,   513,   279,  -183,   544,  -183,  -183,  -183,   265,  -183,
    -183,   513,  -183,  -183,   544,   296,  -183,   297,   303,  -183,
     544,   513,  -183,    95,  -183,  -183,   304,  -183,   544,   262,
     305,  -183,   544,  -183,   544,   264,   306,  -183,   544,   307,
     272,   308,  -183,   544,   309,  -183,   544,  -183,   311,  -183,
     312,   401,   318,   513,   513,   315,  -183,   320,  -183,   510,
     275,  -183,   336,  -183,  -183,  -183,   337,   178,   407,  -183,
    -183,   338,  -183,   544,  -183,   339,   340,  -183,   544,  -183,
     342,  -183,   343,  -183,   344,  -183,   345,  -183,  -183,  -183,
     513,   315,   315,  -183,  -183,  -183,  -183,   513,  -183,  -183,
    -183,  -183,  -183,   346,  -183,  -183,   347,  -183,  -183,  -183,
    -183,   315,  -183,  -183,  -183,  -183,  -183,  -183
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -183,  -183,   333,  -183,  -183,   -39,  -183,   276,   323,   324,
     325,   327,   328,   138,   126,  -183,  -183,  -183,  -183,   117,
    -103,  -183,   -99,  -183,   269,    23,  -183,   361,  -183,  -183,
    -183,   300,   -88,  -117,  -183,  -183,  -182,   234,   377,  -183,
     -34,   381,    -2,    -4,   -20
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -153
static const yytype_int16 yytable[] =
{
      20,    21,   148,   144,    26,   138,   244,    91,   100,    98,
     166,   103,    76,    27,    77,   158,   162,    39,    37,    80,
     143,    31,    32,    13,    40,    48,   167,    47,   172,    50,
      13,    22,    81,    81,     2,     3,    23,    26,     4,    29,
     210,     5,   185,    30,   222,   102,     1,    76,   198,    34,
     202,   206,   209,   138,   116,    74,    38,     6,    41,    36,
     235,    42,    43,   105,     2,     3,    78,   238,     4,   134,
     115,     5,    49,   118,   119,   135,   136,   246,   139,   132,
     250,   140,   237,    83,   256,   124,   165,     6,   261,   125,
      74,   264,   249,   159,    99,   268,   255,   142,  -152,   160,
     161,   121,   145,   180,   131,   179,   321,   277,    86,   146,
     147,   121,   151,   153,   154,   155,    32,   282,   101,    87,
      88,    83,    89,   286,   106,    90,   123,   132,   127,   175,
      43,   291,   168,   288,   165,   295,   289,   296,   176,   177,
      14,   300,   133,   281,   120,   121,   304,   137,   195,   306,
     199,    15,   131,    16,   203,    14,   134,   220,    17,    18,
     204,   205,   121,   156,   157,   121,    15,   230,    16,    19,
     193,   194,   313,    17,    18,   149,   323,   128,    14,   170,
       6,   326,   211,   212,    19,   223,   224,    14,   320,    15,
     169,    16,   173,   104,   171,     6,    17,    18,    15,   273,
      16,   220,   117,   233,   234,    17,    18,    19,   332,   333,
      86,   183,   184,   121,   239,   240,    19,   272,    81,   275,
     178,    87,    88,    83,    89,   181,   182,    90,   337,   334,
     196,   197,   121,    96,   225,   200,   201,   121,   231,   287,
     232,   213,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,   214,    63,   215,   207,   208,   121,   236,    17,
      18,   247,   248,   121,   253,   254,   121,   251,   252,   220,
      19,   311,   312,   241,   216,   257,   258,   230,   262,   263,
     245,     6,   213,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,   214,    63,   215,   265,   266,   270,   271,
      17,    18,   278,   279,   292,   293,   297,   298,   331,   302,
     271,    19,   316,   317,  -147,   259,   267,  -148,  -149,   269,
     274,   276,     6,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,   310,   283,   284,
      28,   260,    65,   108,    86,   285,   290,   294,   299,   301,
     303,   305,    36,   307,   308,    87,    88,    83,    89,   121,
      66,    90,   314,     6,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,   318,   319,
     322,   324,   325,    65,   327,   328,   329,   330,   335,   336,
     109,   110,   111,    36,   112,   113,   315,   309,   174,   141,
      85,   107,   226,    45,     6,   213,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,   214,    63,   215,    84,
       0,     0,     0,    17,    18,    86,     0,     0,     0,     0,
       0,     0,   186,     0,    19,     0,    87,    88,    83,    89,
       0,   187,    90,     0,     0,     6,   213,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,   214,    63,   215,
       0,     0,     0,     0,    17,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    19,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,    14,     0,     0,     0,   114,     0,     0,     0,     0,
      14,     0,    15,     0,    16,    36,   150,     0,     0,    17,
      18,    15,     0,    16,    14,   152,     0,    14,    17,    18,
      19,     0,     0,     0,     0,    15,    14,    16,    15,    19,
      16,   227,    17,    18,     0,    17,    18,    15,     0,    16,
       0,     0,     0,    19,    17,    18,    19,    86,     0,     0,
       0,     0,     0,     0,   186,    46,     0,     0,    87,    88,
      83,    89,    86,   187,    90,     0,     0,     0,     0,   186,
     242,     0,     0,    87,    88,    83,    89,     0,   187,    90,
       0,     0,     0,     0,   188,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64
};

static const yytype_int16 yycheck[] =
{
       2,     3,   105,   102,     6,    93,   188,    41,    47,    43,
      29,    50,    32,     0,    34,   118,   119,    38,    22,    27,
      27,    39,    40,     0,    45,    29,    45,    29,   127,    31,
       7,    26,    40,    40,    21,    22,    33,    39,    25,    21,
     157,    28,   145,    25,   161,    49,     3,    67,   151,    39,
     153,   154,   155,   141,    74,    32,    36,    44,    36,    33,
     177,    39,    40,    65,    21,    22,    38,   184,    25,    31,
      74,    28,    26,    75,    76,    37,    38,   194,    38,    81,
     197,    41,   181,    31,   201,    38,   120,    44,   205,    42,
      67,   208,   195,    36,    39,   212,   199,   101,    39,    42,
      43,    44,   104,   142,    81,   139,   288,   224,    18,    42,
      43,    44,   114,   115,   116,   117,    40,   234,    39,    29,
      30,    31,    32,   240,    42,    35,    20,   129,    34,   131,
      40,   248,    43,    38,   168,   252,    41,   254,    42,    43,
       4,   258,    42,   231,    43,    44,   263,    37,   150,   266,
     152,    15,   129,    17,    36,     4,    31,   159,    22,    23,
      42,    43,    44,    42,    43,    44,    15,   169,    17,    33,
      42,    43,   275,    22,    23,    42,   293,    41,     4,    24,
      44,   298,    42,    43,    33,    42,    43,     4,   287,    15,
      36,    17,    41,    19,    42,    44,    22,    23,    15,   219,
      17,   203,    19,    42,    43,    22,    23,    33,   311,   312,
      18,    42,    43,    44,    42,    43,    33,   219,    40,   221,
      33,    29,    30,    31,    32,    34,    42,    35,   331,   317,
      42,    43,    44,    41,    45,    42,    43,    44,    36,   241,
      42,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    42,    43,    44,    37,    22,
      23,    42,    43,    44,    42,    43,    44,    42,    43,   271,
      33,   273,   274,    26,    37,    42,    43,   279,    42,    43,
      42,    44,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    42,    43,    37,    38,
      22,    23,    37,    38,    42,    43,    42,    43,   310,    37,
      38,    33,    37,    38,    19,    37,    42,    19,    19,    42,
      19,    42,    44,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    19,    42,    42,
       7,   203,    23,    67,    18,    42,    42,    42,    42,    42,
      42,    42,    33,    42,    42,    29,    30,    31,    32,    44,
      41,    35,    42,    44,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    42,    42,
      42,    42,    42,    23,    42,    42,    42,    42,    42,    42,
      67,    67,    67,    33,    67,    67,   279,   271,   129,    99,
      39,    41,   168,    26,    44,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    38,
      -1,    -1,    -1,    22,    23,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    33,    -1,    29,    30,    31,    32,
      -1,    34,    35,    -1,    -1,    44,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,     4,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
       4,    -1,    15,    -1,    17,    33,    19,    -1,    -1,    22,
      23,    15,    -1,    17,     4,    19,    -1,     4,    22,    23,
      33,    -1,    -1,    -1,    -1,    15,     4,    17,    15,    33,
      17,    21,    22,    23,    -1,    22,    23,    15,    -1,    17,
      -1,    -1,    -1,    33,    22,    23,    33,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    33,    -1,    -1,    29,    30,
      31,    32,    18,    34,    35,    -1,    -1,    -1,    -1,    25,
      41,    -1,    -1,    29,    30,    31,    32,    -1,    34,    35,
      -1,    -1,    -1,    -1,    40,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    21,    22,    25,    28,    44,    47,    48,    49,
      50,    61,    67,    71,     4,    15,    17,    22,    23,    33,
      88,    88,    26,    33,    72,    73,    88,     0,    48,    21,
      25,    39,    40,    51,    39,    62,    33,    89,    36,    38,
      45,    36,    39,    40,    74,    84,    33,    88,    89,    26,
      88,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    23,    41,    52,    53,    54,
      55,    56,    57,    58,    71,    89,    90,    90,    38,    63,
      27,    40,    68,    31,    87,    73,    18,    29,    30,    32,
      35,    86,    87,    77,    78,    88,    41,    85,    86,    39,
      51,    39,    89,    51,    19,    88,    42,    41,    53,    54,
      55,    56,    57,    58,    23,    89,    90,    19,    88,    88,
      43,    44,    66,    20,    38,    42,    75,    34,    41,    69,
      70,    71,    88,    42,    31,    37,    38,    37,    78,    38,
      41,    77,    89,    27,    68,    88,    42,    43,    66,    42,
      19,    88,    19,    88,    88,    88,    42,    43,    66,    36,
      42,    43,    66,    83,    84,    86,    29,    45,    43,    36,
      24,    42,    68,    41,    70,    88,    42,    43,    33,    86,
      51,    34,    42,    42,    43,    66,    25,    34,    40,    79,
      80,    82,    86,    42,    43,    88,    42,    43,    66,    88,
      42,    43,    66,    36,    42,    43,    66,    42,    43,    66,
      79,    42,    43,     4,    15,    17,    37,    59,    60,    71,
      88,    90,    79,    42,    43,    45,    83,    21,    64,    65,
      88,    36,    42,    42,    43,    79,    37,    68,    79,    42,
      43,    26,    41,    81,    82,    42,    79,    42,    43,    66,
      79,    42,    43,    42,    43,    66,    79,    42,    43,    37,
      59,    79,    42,    43,    79,    42,    43,    42,    79,    42,
      37,    38,    88,    90,    19,    88,    42,    79,    37,    38,
      76,    78,    79,    42,    42,    42,    79,    88,    38,    41,
      42,    79,    42,    43,    42,    79,    79,    42,    43,    42,
      79,    42,    37,    42,    79,    42,    79,    42,    42,    60,
      19,    88,    88,    66,    42,    65,    37,    38,    42,    42,
      68,    82,    42,    79,    42,    42,    79,    42,    42,    42,
      42,    88,    66,    66,    78,    42,    42,    66
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
# if YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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
        case 2:

/* Line 1455 of yacc.c  */
#line 134 "mof.y"
    {
    ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 137 "mof.y"
    {
    ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 140 "mof.y"
    {
        YYABORT;
    ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 146 "mof.y"
    {
    ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 149 "mof.y"
    {
        /* TODO: validate the class here] */
        (yyvsp[(1) - (1)].classDeclaration)->flags = MI_FLAG_CLASS;
        (yyvsp[(1) - (1)].classDeclaration)->flags |= GetQualFlags((yyvsp[(1) - (1)].classDeclaration)->qualifiers, (yyvsp[(1) - (1)].classDeclaration)->numQualifiers);
        if (FinalizeClass((yyvsp[(1) - (1)].classDeclaration)) != 0)
            YYABORT;
        AddClassDecl((yyvsp[(1) - (1)].classDeclaration));
        if (state.classDeclCallback)
            (*state.classDeclCallback)((yyvsp[(1) - (1)].classDeclaration), state.classDeclCallbackData);
    ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 160 "mof.y"
    {
        AddQualifierDeclaration((yyvsp[(1) - (1)].qualifierDeclaration));

        if (state.qualifierDeclCallback)
            (*state.qualifierDeclCallback)((yyvsp[(1) - (1)].qualifierDeclaration), state.qualifierDeclCallbackData);
    ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 167 "mof.y"
    {
        if (FinalizeInstance((yyvsp[(1) - (1)].instanceDeclaration)) != 0)
            YYABORT;

        AddInstanceDecl((yyvsp[(1) - (1)].instanceDeclaration));

        if (state.instanceDeclCallback)
            (*state.instanceDeclCallback)((yyvsp[(1) - (1)].instanceDeclaration), state.instanceDeclCallbackData);
    ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 179 "mof.y"
    {
        if (strcmp((yyvsp[(2) - (5)].string), "include") == 0)
        {
            if (openIncludeFile((yyvsp[(4) - (5)].string)) != 0)
                YYABORT;
        }
        else if (strcmp((yyvsp[(2) - (5)].string), "namespace") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)((yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].string), state.pragmaCallbackData);
        }
        else if (strcmp((yyvsp[(2) - (5)].string), "deleteclass") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)((yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].string), state.pragmaCallbackData);
        }
        else if (strcmp((yyvsp[(2) - (5)].string), "instancelocale") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)((yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].string), state.pragmaCallbackData);
        }
        else if (strcmp((yyvsp[(2) - (5)].string), "locale") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)((yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].string), state.pragmaCallbackData);
        }
        else
        {
            yywarnf(ID_UNKNOWN_PRAGMA,
                "warning: unknown pragma: %s=%s", (yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].string));

            if (state.pragmaCallback)
                (*state.pragmaCallback)((yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].string), state.pragmaCallbackData);
        }
    ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 215 "mof.y"
    {
        if (strcmp((yyvsp[(2) - (7)].string), "include") == 0)
        {
            if (openIncludeFile((yyvsp[(4) - (7)].string)) != 0)
                YYABORT;
        }
        else if (strcmp((yyvsp[(2) - (7)].string), "namespace") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)((yyvsp[(2) - (7)].string), (yyvsp[(4) - (7)].string), state.pragmaCallbackData);
        }
        else if (strcmp((yyvsp[(2) - (7)].string), "deleteclass") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)((yyvsp[(2) - (7)].string), (yyvsp[(4) - (7)].string), state.pragmaCallbackData);
        }
        else if (strcmp((yyvsp[(2) - (7)].string), "instancelocale") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)((yyvsp[(2) - (7)].string), (yyvsp[(4) - (7)].string), state.pragmaCallbackData);
        }
        else if (strcmp((yyvsp[(2) - (7)].string), "locale") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)((yyvsp[(2) - (7)].string), (yyvsp[(4) - (7)].string), state.pragmaCallbackData);
        }
        else
        {
            yywarnf(ID_UNKNOWN_PRAGMA,
                "warning: unknown pragma: %s=%s", (yyvsp[(2) - (7)].string), (yyvsp[(4) - (7)].string));

            if (state.pragmaCallback)
                (*state.pragmaCallback)((yyvsp[(2) - (7)].string), (yyvsp[(4) - (7)].string), state.pragmaCallbackData);
        }
    ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 253 "mof.y"
    {
        /* Check whether class already exists */
        if (FindClassDecl((yyvsp[(2) - (3)].string)))
        {
            yywarnf(ID_CLASS_ALREADY_DEFINED, "class already defined: \"%s\"", (yyvsp[(2) - (3)].string));
            /* YYABORT; */
        }

        (yyval.classDeclaration) = CALLOC_T(MI_ClassDecl, 1);
        (yyval.classDeclaration)->flags = MI_FLAG_CLASS;
        (yyval.classDeclaration)->name = (yyvsp[(2) - (3)].string);
        (yyval.classDeclaration)->properties = (yyvsp[(3) - (3)].featureList).propertySet.data;
        (yyval.classDeclaration)->numProperties = (yyvsp[(3) - (3)].featureList).propertySet.size;
        (yyval.classDeclaration)->methods = (yyvsp[(3) - (3)].featureList).methodList.data;
        (yyval.classDeclaration)->numMethods = (yyvsp[(3) - (3)].featureList).methodList.size;
    ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 270 "mof.y"
    {
        const MI_ClassDecl* scd;

        /* Check whether class already exists */
        if (FindClassDecl((yyvsp[(2) - (5)].string)))
        {
            yywarnf(ID_CLASS_ALREADY_DEFINED, "class already defined: \"%s\"", (yyvsp[(2) - (5)].string));
            /* YYABORT; */
        }

        /* Check whether superclass exists */
        scd = FindClassDecl((yyvsp[(4) - (5)].string));

        if (!scd)
        {
            yyerrorf(ID_UNDEFINED_SUPERCLASS,
                "super class of \"%s\" is undefined: \"%s\"", (yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].string));
            YYABORT;
        }

        (yyval.classDeclaration) = CALLOC_T(MI_ClassDecl, 1);
        (yyval.classDeclaration)->flags = MI_FLAG_CLASS;
        (yyval.classDeclaration)->name = (yyvsp[(2) - (5)].string);
        (yyval.classDeclaration)->superClass = (yyvsp[(4) - (5)].string);
        (yyval.classDeclaration)->superClassDecl = (MI_ClassDecl*)scd;
        (yyval.classDeclaration)->properties = (yyvsp[(5) - (5)].featureList).propertySet.data;
        (yyval.classDeclaration)->numProperties = (yyvsp[(5) - (5)].featureList).propertySet.size;
        (yyval.classDeclaration)->methods = (yyvsp[(5) - (5)].featureList).methodList.data;
        (yyval.classDeclaration)->numMethods = (yyvsp[(5) - (5)].featureList).methodList.size;
    ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 301 "mof.y"
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_CLASS, &(yyvsp[(1) - (4)].qualifierList)) != 0)
            YYABORT;

        /* Check whether class already exists */
        if (FindClassDecl((yyvsp[(3) - (4)].string)))
        {
            yywarnf(ID_CLASS_ALREADY_DEFINED, "class already defined: \"%s\"", (yyvsp[(3) - (4)].string));
            /* YYABORT; */
        }

        (yyval.classDeclaration) = CALLOC_T(MI_ClassDecl, 1);
        (yyval.classDeclaration)->flags = MI_FLAG_CLASS;
        (yyval.classDeclaration)->name = (yyvsp[(3) - (4)].string);
        (yyval.classDeclaration)->properties = (yyvsp[(4) - (4)].featureList).propertySet.data;
        (yyval.classDeclaration)->numProperties = (yyvsp[(4) - (4)].featureList).propertySet.size;
        (yyval.classDeclaration)->methods = (yyvsp[(4) - (4)].featureList).methodList.data;
        (yyval.classDeclaration)->numMethods = (yyvsp[(4) - (4)].featureList).methodList.size;
        (yyval.classDeclaration)->qualifiers = (yyvsp[(1) - (4)].qualifierList).data;
        (yyval.classDeclaration)->numQualifiers = (yyvsp[(1) - (4)].qualifierList).size;
    ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 324 "mof.y"
    {
        const MI_ClassDecl* scd;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_CLASS, &(yyvsp[(1) - (6)].qualifierList)) != 0)
            YYABORT;

        /* Check whether class already exists */
        if (FindClassDecl((yyvsp[(3) - (6)].string)))
        {
            yywarnf(ID_CLASS_ALREADY_DEFINED, "class already defined: \"%s\"", (yyvsp[(3) - (6)].string));
            /* YYABORT; */
        }

        /* Check whether superclass exists */
        scd = FindClassDecl((yyvsp[(5) - (6)].string));

        if (!scd)
        {
            yyerrorf(ID_UNDEFINED_SUPERCLASS,
                "super class of \"%s\" is undefined: \"%s\"", (yyvsp[(3) - (6)].string), (yyvsp[(5) - (6)].string));
            YYABORT;
        }

        (yyval.classDeclaration) = CALLOC_T(MI_ClassDecl, 1);
        (yyval.classDeclaration)->flags = MI_FLAG_CLASS;
        (yyval.classDeclaration)->name = (yyvsp[(3) - (6)].string);
        (yyval.classDeclaration)->superClass = scd->name;
        (yyval.classDeclaration)->superClassDecl = (MI_ClassDecl*)scd;
        (yyval.classDeclaration)->properties = (yyvsp[(6) - (6)].featureList).propertySet.data;
        (yyval.classDeclaration)->numProperties = (yyvsp[(6) - (6)].featureList).propertySet.size;
        (yyval.classDeclaration)->methods = (yyvsp[(6) - (6)].featureList).methodList.data;
        (yyval.classDeclaration)->numMethods = (yyvsp[(6) - (6)].featureList).methodList.size;
        (yyval.classDeclaration)->qualifiers = (yyvsp[(1) - (6)].qualifierList).data;
        (yyval.classDeclaration)->numQualifiers = (yyvsp[(1) - (6)].qualifierList).size;
    ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 363 "mof.y"
    {
        (yyval.featureList) = (yyvsp[(2) - (4)].featureList);
    ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 367 "mof.y"
    {
        (yyval.featureList).propertySet.data = NULL;
        (yyval.featureList).propertySet.size = 0;
        (yyval.featureList).methodList.data = NULL;
        (yyval.featureList).methodList.size = 0;
    ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 376 "mof.y"
    {
        if (CheckPropertyValueConstraints((yyvsp[(1) - (1)].property)) != 0)
        {
            YYABORT;
        }
        (yyval.featureList).propertySet.data = NULL;
        (yyval.featureList).propertySet.size = 0;
        (yyval.featureList).methodList.data = NULL;
        (yyval.featureList).methodList.size = 0;
        (yyvsp[(1) - (1)].property)->flags = MI_FLAG_PROPERTY;
        (yyvsp[(1) - (1)].property)->flags |= GetQualFlags((yyvsp[(1) - (1)].property)->qualifiers, (yyvsp[(1) - (1)].property)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).propertySet, (yyvsp[(1) - (1)].property));
    ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 390 "mof.y"
    {
        (yyval.featureList).propertySet.data = NULL;
        (yyval.featureList).propertySet.size = 0;
        (yyval.featureList).methodList.data = NULL;
        (yyval.featureList).methodList.size = 0;
        (yyvsp[(1) - (1)].methodDecl)->flags = MI_FLAG_METHOD;
        (yyvsp[(1) - (1)].methodDecl)->flags |= GetQualFlags((yyvsp[(1) - (1)].methodDecl)->qualifiers, (yyvsp[(1) - (1)].methodDecl)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).methodList, (yyvsp[(1) - (1)].methodDecl));
    ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 400 "mof.y"
    {
        (yyval.featureList).propertySet.data = NULL;
        (yyval.featureList).propertySet.size = 0;
        (yyval.featureList).methodList.data = NULL;
        (yyval.featureList).methodList.size = 0;
        (yyvsp[(1) - (1)].property)->flags = MI_FLAG_PROPERTY;
        (yyvsp[(1) - (1)].property)->flags |= GetQualFlags((yyvsp[(1) - (1)].property)->qualifiers, (yyvsp[(1) - (1)].property)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).propertySet, (yyvsp[(1) - (1)].property));
    ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 410 "mof.y"
    {
        (yyval.featureList).propertySet.data = NULL;
        (yyval.featureList).propertySet.size = 0;
        (yyval.featureList).methodList.data = NULL;
        (yyval.featureList).methodList.size = 0;
        (yyvsp[(1) - (1)].property)->flags = MI_FLAG_PROPERTY;
        (yyvsp[(1) - (1)].property)->flags |= GetQualFlags((yyvsp[(1) - (1)].property)->qualifiers, (yyvsp[(1) - (1)].property)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).propertySet, (yyvsp[(1) - (1)].property));
    ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 420 "mof.y"
    {
        (yyval.featureList).propertySet.data = NULL;
        (yyval.featureList).propertySet.size = 0;
        (yyval.featureList).methodList.data = NULL;
        (yyval.featureList).methodList.size = 0;
        (yyvsp[(1) - (1)].property)->flags = MI_FLAG_PROPERTY;
        (yyvsp[(1) - (1)].property)->flags |= GetQualFlags((yyvsp[(1) - (1)].property)->qualifiers, (yyvsp[(1) - (1)].property)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).propertySet, (yyvsp[(1) - (1)].property));
    ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 430 "mof.y"
    {
        (yyval.featureList).propertySet.data = NULL;
        (yyval.featureList).propertySet.size = 0;
        (yyval.featureList).methodList.data = NULL;
        (yyval.featureList).methodList.size = 0;
        (yyvsp[(1) - (1)].property)->flags = MI_FLAG_PROPERTY;
        (yyvsp[(1) - (1)].property)->flags |= GetQualFlags((yyvsp[(1) - (1)].property)->qualifiers, (yyvsp[(1) - (1)].property)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).propertySet, (yyvsp[(1) - (1)].property));
    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 440 "mof.y"
    {
        if (CheckPropertyValueConstraints((yyvsp[(2) - (2)].property)) != 0)
        {
            YYABORT;
        }

        if (FindProperty(&(yyvsp[(1) - (2)].featureList).propertySet, (yyvsp[(2) - (2)].property)->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", (yyvsp[(2) - (2)].property)->name);
            YYABORT;
        }

        (yyvsp[(2) - (2)].property)->flags = MI_FLAG_PROPERTY;
        (yyvsp[(2) - (2)].property)->flags |= GetQualFlags((yyvsp[(2) - (2)].property)->qualifiers, (yyvsp[(2) - (2)].property)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).propertySet, (yyvsp[(2) - (2)].property));
    ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 458 "mof.y"
    {
        if (FindMethod(&(yyvsp[(1) - (2)].featureList).methodList, (yyvsp[(2) - (2)].methodDecl)->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", (yyvsp[(2) - (2)].methodDecl)->name);
            YYABORT;
        }

        (yyvsp[(2) - (2)].methodDecl)->flags = MI_FLAG_METHOD;
        (yyvsp[(2) - (2)].methodDecl)->flags |= GetQualFlags((yyvsp[(2) - (2)].methodDecl)->qualifiers, (yyvsp[(2) - (2)].methodDecl)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).methodList, (yyvsp[(2) - (2)].methodDecl));
    ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 471 "mof.y"
    {
        if (FindProperty(&(yyvsp[(1) - (2)].featureList).propertySet, (yyvsp[(2) - (2)].property)->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", (yyvsp[(2) - (2)].property)->name);
            YYABORT;
        }

        (yyvsp[(2) - (2)].property)->flags = MI_FLAG_PROPERTY;
        (yyvsp[(2) - (2)].property)->flags |= GetQualFlags((yyvsp[(2) - (2)].property)->qualifiers, (yyvsp[(2) - (2)].property)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).propertySet, (yyvsp[(2) - (2)].property));
    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 484 "mof.y"
    {
        if (FindProperty(&(yyvsp[(1) - (2)].featureList).propertySet, (yyvsp[(2) - (2)].property)->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", (yyvsp[(2) - (2)].property)->name);
            YYABORT;
        }
        (yyvsp[(2) - (2)].property)->flags = MI_FLAG_PROPERTY;
        (yyvsp[(2) - (2)].property)->flags |= GetQualFlags((yyvsp[(2) - (2)].property)->qualifiers, (yyvsp[(2) - (2)].property)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).propertySet, (yyvsp[(2) - (2)].property));
    ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 496 "mof.y"
    {
        if (FindProperty(&(yyvsp[(1) - (2)].featureList).propertySet, (yyvsp[(2) - (2)].property)->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", (yyvsp[(2) - (2)].property)->name);
            YYABORT;
        }

        (yyvsp[(2) - (2)].property)->flags = MI_FLAG_PROPERTY;
        (yyvsp[(2) - (2)].property)->flags |= GetQualFlags((yyvsp[(2) - (2)].property)->qualifiers, (yyvsp[(2) - (2)].property)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).propertySet, (yyvsp[(2) - (2)].property));
    ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 509 "mof.y"
    {
        if (FindProperty(&(yyvsp[(1) - (2)].featureList).propertySet, (yyvsp[(2) - (2)].property)->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", (yyvsp[(2) - (2)].property)->name);
            YYABORT;
        }

        (yyvsp[(2) - (2)].property)->flags = MI_FLAG_PROPERTY;
        (yyvsp[(2) - (2)].property)->flags |= GetQualFlags((yyvsp[(2) - (2)].property)->qualifiers, (yyvsp[(2) - (2)].property)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).propertySet, (yyvsp[(2) - (2)].property));
    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 524 "mof.y"
    {
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->name = (yyvsp[(2) - (3)].string);
        (yyval.property)->type = (yyvsp[(1) - (3)].type);
    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 530 "mof.y"
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PROPERTY, &(yyvsp[(1) - (4)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->name = (yyvsp[(3) - (4)].string);
        (yyval.property)->type = (yyvsp[(2) - (4)].type);
        (yyval.property)->qualifiers = (yyvsp[(1) - (4)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (4)].qualifierList).size;
    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 542 "mof.y"
    {
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->name = (yyvsp[(2) - (4)].string);
        (yyval.property)->type = ARRAYOF((yyvsp[(1) - (4)].type));
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(3) - (4)].integer);
    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 549 "mof.y"
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PROPERTY, &(yyvsp[(1) - (5)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->name = (yyvsp[(3) - (5)].string);
        (yyval.property)->type = ARRAYOF((yyvsp[(2) - (5)].type));
        (yyval.property)->qualifiers = (yyvsp[(1) - (5)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (5)].qualifierList).size;
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(4) - (5)].integer);
    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 562 "mof.y"
    {
        void* value;

        if (InitializerToValue(&(yyvsp[(4) - (5)].initializer), (yyvsp[(1) - (5)].type), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->name = (yyvsp[(2) - (5)].string);
        (yyval.property)->type = (yyvsp[(1) - (5)].type);
        (yyval.property)->value = value;
    ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 577 "mof.y"
    {
        void* value;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PROPERTY, &(yyvsp[(1) - (6)].qualifierList)) != 0)
            YYABORT;

        if (InitializerToValue(&(yyvsp[(5) - (6)].initializer), (yyvsp[(2) - (6)].type), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->name = (yyvsp[(3) - (6)].string);
        (yyval.property)->type = (yyvsp[(2) - (6)].type);
        (yyval.property)->qualifiers = (yyvsp[(1) - (6)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (6)].qualifierList).size;
        (yyval.property)->value = value;
    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 598 "mof.y"
    {
        void* value;

        if (InitializerToValue(&(yyvsp[(5) - (6)].initializer), ARRAYOF((yyvsp[(1) - (6)].type)), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->name = (yyvsp[(2) - (6)].string);
        (yyval.property)->type = ARRAYOF((yyvsp[(1) - (6)].type));
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(3) - (6)].integer);
        (yyval.property)->value = value;
    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 614 "mof.y"
    {
        void* value;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PROPERTY, &(yyvsp[(1) - (7)].qualifierList)) != 0)
            YYABORT;

        if (InitializerToValue(&(yyvsp[(6) - (7)].initializer), ARRAYOF((yyvsp[(2) - (7)].type)), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->name = (yyvsp[(3) - (7)].string);
        (yyval.property)->type = ARRAYOF((yyvsp[(2) - (7)].type));
        (yyval.property)->qualifiers = (yyvsp[(1) - (7)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (7)].qualifierList).size;
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(4) - (7)].integer);
        (yyval.property)->value = value;
    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 638 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(1) - (3)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(1) - (3)].string));
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCE;
        (yyval.property)->name = (yyvsp[(2) - (3)].string);
        (yyval.property)->className = cd->name;
    ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 655 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(2) - (4)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(2) - (4)].string));
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (4)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCE;
        (yyval.property)->name = (yyvsp[(3) - (4)].string);
        (yyval.property)->className = cd->name;
        (yyval.property)->qualifiers = (yyvsp[(1) - (4)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (4)].qualifierList).size;
    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 678 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(1) - (4)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(1) - (4)].string));
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCEA;
        (yyval.property)->name = (yyvsp[(2) - (4)].string);
        (yyval.property)->className = cd->name;
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(3) - (4)].integer);
    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 696 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(2) - (5)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(2) - (5)].string));
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (5)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCEA;
        (yyval.property)->name = (yyvsp[(3) - (5)].string);
        (yyval.property)->className = cd->name;
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(4) - (5)].integer);
        (yyval.property)->qualifiers = (yyvsp[(1) - (5)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (5)].qualifierList).size;
    ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 720 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(1) - (5)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(1) - (5)].string));
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCE;
        (yyval.property)->name = (yyvsp[(2) - (5)].string);
        (yyval.property)->className = cd->name;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 739 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(2) - (6)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(2) - (6)].string));
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (6)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCE;
        (yyval.property)->name = (yyvsp[(3) - (6)].string);
        (yyval.property)->className = cd->name;
        (yyval.property)->qualifiers = (yyvsp[(1) - (6)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (6)].qualifierList).size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 764 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(1) - (6)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(1) - (6)].string));
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCEA;
        (yyval.property)->name = (yyvsp[(2) - (6)].string);
        (yyval.property)->className = cd->name;
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(3) - (6)].integer);
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 784 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(2) - (7)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(2) - (7)].string));
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (7)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCEA;
        (yyval.property)->name = (yyvsp[(3) - (7)].string);
        (yyval.property)->className = cd->name;
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(4) - (7)].integer);
        (yyval.property)->qualifiers = (yyvsp[(1) - (7)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (7)].qualifierList).size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 812 "mof.y"
    {
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCE;
        (yyval.property)->name = (yyvsp[(2) - (3)].string);
        (yyval.property)->className = "?";
    ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 819 "mof.y"
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (4)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCE;
        (yyval.property)->name = (yyvsp[(3) - (4)].string);
        (yyval.property)->className = "?";
        (yyval.property)->qualifiers = (yyvsp[(1) - (4)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (4)].qualifierList).size;
    ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 832 "mof.y"
    {
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCEA;
        (yyval.property)->name = (yyvsp[(2) - (4)].string);
        (yyval.property)->className = "?";
        (yyval.property)->subscript = 0;
    ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 840 "mof.y"
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (5)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCEA;
        (yyval.property)->name = (yyvsp[(3) - (5)].string);
        (yyval.property)->className = "?";
        (yyval.property)->subscript = 0;
        (yyval.property)->qualifiers = (yyvsp[(1) - (5)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (5)].qualifierList).size;
    ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 854 "mof.y"
    {
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCE;
        (yyval.property)->name = (yyvsp[(2) - (5)].string);
        (yyval.property)->className = "?";
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 863 "mof.y"
    {
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCE;
        (yyval.property)->name = (yyvsp[(3) - (6)].string);
        (yyval.property)->className = "?";
        (yyval.property)->qualifiers = (yyvsp[(1) - (6)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (6)].qualifierList).size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 874 "mof.y"
    {
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCEA;
        (yyval.property)->name = (yyvsp[(2) - (6)].string);
        (yyval.property)->className = "?";
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(3) - (6)].integer);
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 884 "mof.y"
    {
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_INSTANCEA;
        (yyval.property)->name = (yyvsp[(3) - (7)].string);
        (yyval.property)->className = "?";
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(4) - (7)].integer);
        (yyval.property)->qualifiers = (yyvsp[(1) - (7)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (7)].qualifierList).size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 898 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(1) - (4)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(1) - (4)].string));
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCE;
        (yyval.property)->name = (yyvsp[(3) - (4)].string);
        (yyval.property)->className = cd->name;
    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 915 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(2) - (5)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(2) - (5)].string));
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (5)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCE;
        (yyval.property)->name = (yyvsp[(4) - (5)].string);
        (yyval.property)->className = cd->name;
        (yyval.property)->qualifiers = (yyvsp[(1) - (5)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (5)].qualifierList).size;
    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 938 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(1) - (5)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(1) - (5)].string));
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCEA;
        (yyval.property)->name = (yyvsp[(3) - (5)].string);
        (yyval.property)->className = cd->name;
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(4) - (5)].integer);
    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 956 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(2) - (6)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(2) - (6)].string));
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (6)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCEA;
        (yyval.property)->name = (yyvsp[(4) - (6)].string);
        (yyval.property)->className = cd->name;
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(5) - (6)].integer);
        (yyval.property)->qualifiers = (yyvsp[(1) - (6)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (6)].qualifierList).size;
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 980 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(1) - (6)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(1) - (6)].string));
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCE;
        (yyval.property)->name = (yyvsp[(3) - (6)].string);
        (yyval.property)->className = cd->name;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 999 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(2) - (7)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(2) - (7)].string));
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (7)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCE;
        (yyval.property)->name = (yyvsp[(4) - (7)].string);
        (yyval.property)->className = cd->name;
        (yyval.property)->qualifiers = (yyvsp[(1) - (7)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (7)].qualifierList).size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 1024 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(1) - (7)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(1) - (7)].string));
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCEA;
        (yyval.property)->name = (yyvsp[(3) - (7)].string);
        (yyval.property)->className = cd->name;
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(4) - (7)].integer);
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 1044 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(2) - (8)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(2) - (8)].string));
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (8)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCEA;
        (yyval.property)->name = (yyvsp[(4) - (8)].string);
        (yyval.property)->className = cd->name;
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(5) - (8)].integer);
        (yyval.property)->qualifiers = (yyvsp[(1) - (8)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (8)].qualifierList).size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 1072 "mof.y"
    {
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCE;
        (yyval.property)->name = (yyvsp[(3) - (4)].string);
        (yyval.property)->className = "?";
    ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 1079 "mof.y"
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (5)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCE;
        (yyval.property)->name = (yyvsp[(4) - (5)].string);
        (yyval.property)->className = "?";
        (yyval.property)->qualifiers = (yyvsp[(1) - (5)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (5)].qualifierList).size;
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 1092 "mof.y"
    {
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCEA;
        (yyval.property)->name = (yyvsp[(3) - (5)].string);
        (yyval.property)->className = "?";
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(4) - (5)].integer);
    ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1100 "mof.y"
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (6)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCEA;
        (yyval.property)->name = (yyvsp[(4) - (6)].string);
        (yyval.property)->className = "?";
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(5) - (6)].integer);
        (yyval.property)->qualifiers = (yyvsp[(1) - (6)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (6)].qualifierList).size;
    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1114 "mof.y"
    {
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCE;
        (yyval.property)->name = (yyvsp[(3) - (6)].string);
        (yyval.property)->className = "?";
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1123 "mof.y"
    {
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCEA;
        (yyval.property)->name = (yyvsp[(3) - (7)].string);
        (yyval.property)->className = "?";
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(4) - (7)].integer);
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1133 "mof.y"
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (7)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCE;
        (yyval.property)->name = (yyvsp[(4) - (7)].string);
        (yyval.property)->className = "?";
        (yyval.property)->qualifiers = (yyvsp[(1) - (7)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (7)].qualifierList).size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
	;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1148 "mof.y"
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &(yyvsp[(1) - (8)].qualifierList)) != 0)
            YYABORT;

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->type = MI_REFERENCEA;
        (yyval.property)->name = (yyvsp[(4) - (8)].string);
        (yyval.property)->className = "?";
        (yyval.property)->subscript = (MI_Uint32)(yyvsp[(5) - (8)].integer);
        (yyval.property)->qualifiers = (yyvsp[(1) - (8)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (8)].qualifierList).size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
	;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1166 "mof.y"
    {
        (yyval.methodDecl) = CALLOC_T(MI_MethodDecl, 1);
        (yyval.methodDecl)->name = (yyvsp[(2) - (6)].string);
        (yyval.methodDecl)->parameters = (yyvsp[(4) - (6)].parameterList).data;
        (yyval.methodDecl)->numParameters = (yyvsp[(4) - (6)].parameterList).size;
        (yyval.methodDecl)->returnType = (yyvsp[(1) - (6)].type);
    ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1174 "mof.y"
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_METHOD, &(yyvsp[(1) - (7)].qualifierList)) != 0)
            YYABORT;

        (yyval.methodDecl) = CALLOC_T(MI_MethodDecl, 1);
        (yyval.methodDecl)->name = (yyvsp[(3) - (7)].string);
        (yyval.methodDecl)->parameters = (yyvsp[(5) - (7)].parameterList).data;
        (yyval.methodDecl)->numParameters = (yyvsp[(5) - (7)].parameterList).size;
        (yyval.methodDecl)->qualifiers = (yyvsp[(1) - (7)].qualifierList).data;
        (yyval.methodDecl)->numQualifiers = (yyvsp[(1) - (7)].qualifierList).size;
        (yyval.methodDecl)->returnType = (yyvsp[(2) - (7)].type);
    ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 1188 "mof.y"
    {
        MOF_ParameterList parameterList = PTRARRAY_INITIALIZER;

        (yyval.methodDecl) = CALLOC_T(MI_MethodDecl, 1);
        (yyval.methodDecl)->name = (yyvsp[(2) - (5)].string);
        (yyval.methodDecl)->parameters = parameterList.data;
        (yyval.methodDecl)->numParameters = parameterList.size;
        (yyval.methodDecl)->returnType = (yyvsp[(1) - (5)].type);
    ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1198 "mof.y"
    {
        MOF_ParameterList parameterList = PTRARRAY_INITIALIZER;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_METHOD, &(yyvsp[(1) - (6)].qualifierList)) != 0)
            YYABORT;

        (yyval.methodDecl) = CALLOC_T(MI_MethodDecl, 1);
        (yyval.methodDecl)->name = (yyvsp[(3) - (6)].string);
        (yyval.methodDecl)->parameters = parameterList.data;
        (yyval.methodDecl)->numParameters = parameterList.size;
        (yyval.methodDecl)->qualifiers = (yyvsp[(1) - (6)].qualifierList).data;
        (yyval.methodDecl)->numQualifiers = (yyvsp[(1) - (6)].qualifierList).size;
        (yyval.methodDecl)->returnType = (yyvsp[(2) - (6)].type);
    ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1216 "mof.y"
    {
        (yyvsp[(1) - (1)].parameter)->flags = MI_FLAG_PARAMETER;
        (yyvsp[(1) - (1)].parameter)->flags |= GetQualFlags((yyvsp[(1) - (1)].parameter)->qualifiers, (yyvsp[(1) - (1)].parameter)->numQualifiers);
        (yyval.parameterList).data = NULL;
        (yyval.parameterList).size = 0;
        MofPtrArray_Append((MofPtrArray*)&(yyval.parameterList), (yyvsp[(1) - (1)].parameter));
    ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1224 "mof.y"
    {
        if (FindParameter(&(yyvsp[(1) - (3)].parameterList), (yyvsp[(3) - (3)].parameter)->name))
        {
            yyerrorf(ID_PARAMETER_ALREADY_DEFINED,
                "parameter already defined: \"%s\"", (yyvsp[(3) - (3)].parameter)->name);
            YYABORT;
        }

        (yyvsp[(3) - (3)].parameter)->flags = MI_FLAG_PARAMETER;
        (yyvsp[(3) - (3)].parameter)->flags |= GetQualFlags((yyvsp[(3) - (3)].parameter)->qualifiers, (yyvsp[(3) - (3)].parameter)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.parameterList), (yyvsp[(3) - (3)].parameter));
    ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1239 "mof.y"
    {
        (yyval.parameter) = CALLOC_T(MI_ParameterDecl, 1);
        (yyval.parameter)->name = (yyvsp[(2) - (2)].string);
        (yyval.parameter)->type = (yyvsp[(1) - (2)].type);
    ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1245 "mof.y"
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &(yyvsp[(1) - (3)].qualifierList)) != 0)
            YYABORT;

        (yyval.parameter) = CALLOC_T(MI_ParameterDecl, 1);
        (yyval.parameter)->name = (yyvsp[(3) - (3)].string);
        (yyval.parameter)->type = (yyvsp[(2) - (3)].type);
        (yyval.parameter)->qualifiers = (yyvsp[(1) - (3)].qualifierList).data;
        (yyval.parameter)->numQualifiers = (yyvsp[(1) - (3)].qualifierList).size;
    ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1257 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(1) - (3)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(1) - (3)].string));
            YYABORT;
        }

        (yyval.parameter) = CALLOC_T(MI_ParameterDecl, 1);
        (yyval.parameter)->name = (yyvsp[(3) - (3)].string);
        (yyval.parameter)->type = MI_REFERENCE;
        (yyval.parameter)->className = cd->name;
    ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1274 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(2) - (4)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(2) - (4)].string));
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &(yyvsp[(1) - (4)].qualifierList)) != 0)
            YYABORT;

        (yyval.parameter) = CALLOC_T(MI_ParameterDecl, 1);
        (yyval.parameter)->name = (yyvsp[(4) - (4)].string);
        (yyval.parameter)->type = MI_REFERENCE;
        (yyval.parameter)->className = cd->name;
        (yyval.parameter)->qualifiers = (yyvsp[(1) - (4)].qualifierList).data;
        (yyval.parameter)->numQualifiers = (yyvsp[(1) - (4)].qualifierList).size;
    ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1297 "mof.y"
    {
        (yyval.parameter) = CALLOC_T(MI_ParameterDecl, 1);
        (yyval.parameter)->name = (yyvsp[(2) - (3)].string);
        (yyval.parameter)->type = ARRAYOF((yyvsp[(1) - (3)].type));
        (yyval.parameter)->subscript = (MI_Uint32)(yyvsp[(3) - (3)].integer);
    ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 1304 "mof.y"
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &(yyvsp[(1) - (4)].qualifierList)) != 0)
            YYABORT;

        (yyval.parameter) = CALLOC_T(MI_ParameterDecl, 1);
        (yyval.parameter)->name = (yyvsp[(3) - (4)].string);
        (yyval.parameter)->type = ARRAYOF((yyvsp[(2) - (4)].type));
        (yyval.parameter)->subscript = (MI_Uint32)(yyvsp[(4) - (4)].integer);
        (yyval.parameter)->qualifiers = (yyvsp[(1) - (4)].qualifierList).data;
        (yyval.parameter)->numQualifiers = (yyvsp[(1) - (4)].qualifierList).size;
    ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1317 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(1) - (4)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(1) - (4)].string));
            YYABORT;
        }

        (yyval.parameter) = CALLOC_T(MI_ParameterDecl, 1);
        (yyval.parameter)->name = (yyvsp[(3) - (4)].string);
        (yyval.parameter)->type = ARRAYOF(MI_REFERENCE);
        (yyval.parameter)->className = cd->name;
        (yyval.parameter)->subscript = (MI_Uint32)(yyvsp[(4) - (4)].integer);
    ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1335 "mof.y"
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl((yyvsp[(2) - (5)].string));
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", (yyvsp[(2) - (5)].string));
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &(yyvsp[(1) - (5)].qualifierList)) != 0)
            YYABORT;

        (yyval.parameter) = CALLOC_T(MI_ParameterDecl, 1);
        (yyval.parameter)->name = (yyvsp[(4) - (5)].string);
        (yyval.parameter)->type = ARRAYOF(MI_REFERENCE);
        (yyval.parameter)->className = cd->name;
        (yyval.parameter)->subscript = (MI_Uint32)(yyvsp[(5) - (5)].integer);
        (yyval.parameter)->qualifiers = (yyvsp[(1) - (5)].qualifierList).data;
        (yyval.parameter)->numQualifiers = (yyvsp[(1) - (5)].qualifierList).size;
    ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1361 "mof.y"
    {
        (yyvsp[(3) - (5)].qualifierDeclaration)->name = (yyvsp[(2) - (5)].string);
        (yyvsp[(3) - (5)].qualifierDeclaration)->scope = (yyvsp[(4) - (5)].flags);
        (yyvsp[(3) - (5)].qualifierDeclaration)->flavor = 0;
        (yyval.qualifierDeclaration) = (yyvsp[(3) - (5)].qualifierDeclaration);
    ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1368 "mof.y"
    {
        (yyvsp[(3) - (6)].qualifierDeclaration)->name = (yyvsp[(2) - (6)].string);
        (yyvsp[(3) - (6)].qualifierDeclaration)->scope = (yyvsp[(4) - (6)].flags);
        (yyvsp[(3) - (6)].qualifierDeclaration)->flavor = (yyvsp[(5) - (6)].flags);
        (yyval.qualifierDeclaration) = (yyvsp[(3) - (6)].qualifierDeclaration);
    ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1377 "mof.y"
    {
        (yyval.qualifierDeclaration) = CALLOC_T(MI_QualifierDecl, 1);
        (yyval.qualifierDeclaration)->type = (yyvsp[(2) - (2)].type);
    ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1382 "mof.y"
    {
        void* value;

        if (InitializerToValue(&(yyvsp[(4) - (4)].initializer), (yyvsp[(2) - (4)].type), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        (yyval.qualifierDeclaration) = CALLOC_T(MI_QualifierDecl, 1);
        (yyval.qualifierDeclaration)->type = (yyvsp[(2) - (4)].type);
        (yyval.qualifierDeclaration)->value = value;
        ReleaseInitializer(&(yyvsp[(4) - (4)].initializer));
    ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1397 "mof.y"
    {
        (yyval.qualifierDeclaration) = CALLOC_T(MI_QualifierDecl, 1);
        (yyval.qualifierDeclaration)->type = ARRAYOF((yyvsp[(2) - (3)].type));
        (yyval.qualifierDeclaration)->subscript = (MI_Uint32)(yyvsp[(3) - (3)].integer);
    ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1403 "mof.y"
    {
        void* value = NULL;

        if (InitializerToValue(&(yyvsp[(5) - (5)].initializer), ARRAYOF((yyvsp[(2) - (5)].type)), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        (yyval.qualifierDeclaration) = CALLOC_T(MI_QualifierDecl, 1);
        (yyval.qualifierDeclaration)->type = ARRAYOF((yyvsp[(2) - (5)].type));
        (yyval.qualifierDeclaration)->subscript = (MI_Uint32)(yyvsp[(3) - (5)].integer);
        (yyval.qualifierDeclaration)->value = value;
        ReleaseInitializer(&(yyvsp[(5) - (5)].initializer));
    ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1421 "mof.y"
    {
        (yyval.flags) = (yyvsp[(4) - (5)].flags);
    ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1427 "mof.y"
    {
        (yyval.flags) = (yyvsp[(1) - (1)].flags);
    ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1431 "mof.y"
    {
        (yyval.flags) |= (yyvsp[(3) - (3)].flags);
    ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1437 "mof.y"
    {
        MI_Uint32 flag;
        flag = GetScopeFlag((yyvsp[(1) - (1)].string));
        if (flag == MI_FLAG_NULL)
        {
            yyerrorf(ID_UNKNOWN_SCOPE, "invalid qualifer scope: \"%s\"", (yyvsp[(1) - (1)].string));
            YYABORT;
        }
        (yyval.flags) = flag;
    ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1448 "mof.y"
    {
        (yyval.flags) = MI_FLAG_CLASS;
    ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1454 "mof.y"
    {
        if ((yyvsp[(2) - (3)].integer) <= 0)
        {
            yyerrorf(ID_ILLEGAL_ARRAY_SUBSCRIPT,
                "illegal array subscript: " SINT64_FMT, (yyvsp[(2) - (3)].integer));
            YYABORT;
        }

        (yyval.integer) = (yyvsp[(2) - (3)].integer);
    ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1465 "mof.y"
    {
        /* 0 signifies a dynamic array */
        (yyval.integer) = 0;
    ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1472 "mof.y"
    {
        (yyval.instanceDeclaration) = CALLOC_T(MI_InstanceDecl, 1);
        (yyval.instanceDeclaration)->flags = 0;
        (yyval.instanceDeclaration)->name = (yyvsp[(3) - (5)].string);
        (yyval.instanceDeclaration)->properties = (yyvsp[(4) - (5)].featureList).propertySet.data;
        (yyval.instanceDeclaration)->numProperties = (yyvsp[(4) - (5)].featureList).propertySet.size;
    ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1480 "mof.y"
    {
        (yyval.instanceDeclaration) = CALLOC_T(MI_InstanceDecl, 1);
        (yyval.instanceDeclaration)->flags = 0;
        (yyval.instanceDeclaration)->name = (yyvsp[(4) - (6)].string);
        (yyval.instanceDeclaration)->properties = (yyvsp[(5) - (6)].featureList).propertySet.data;
        (yyval.instanceDeclaration)->numProperties = (yyvsp[(5) - (6)].featureList).propertySet.size;
        (yyval.instanceDeclaration)->qualifiers = (yyvsp[(1) - (6)].qualifierList).data;
        (yyval.instanceDeclaration)->numQualifiers = (yyvsp[(1) - (6)].qualifierList).size;
    ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1490 "mof.y"
    {
        /* TODO: handle alias */
        (yyval.instanceDeclaration) = CALLOC_T(MI_InstanceDecl, 1);
        (yyval.instanceDeclaration)->flags = 0;
        (yyval.instanceDeclaration)->name = (yyvsp[(3) - (7)].string);
        (yyval.instanceDeclaration)->properties = (yyvsp[(6) - (7)].featureList).propertySet.data;
        (yyval.instanceDeclaration)->numProperties = (yyvsp[(6) - (7)].featureList).propertySet.size;
    ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1499 "mof.y"
    {
        /* TODO: handle alias */
        (yyval.instanceDeclaration) = CALLOC_T(MI_InstanceDecl, 1);
        (yyval.instanceDeclaration)->flags = 0;
        (yyval.instanceDeclaration)->name = (yyvsp[(4) - (8)].string);
        (yyval.instanceDeclaration)->properties = (yyvsp[(7) - (8)].featureList).propertySet.data;
        (yyval.instanceDeclaration)->numProperties = (yyvsp[(7) - (8)].featureList).propertySet.size;
        (yyval.instanceDeclaration)->qualifiers = (yyvsp[(1) - (8)].qualifierList).data;
        (yyval.instanceDeclaration)->numQualifiers = (yyvsp[(1) - (8)].qualifierList).size;
    ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1512 "mof.y"
    {
        (yyval.featureList) = (yyvsp[(2) - (3)].featureList);
    ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1516 "mof.y"
    {
        (yyval.featureList).propertySet.data = NULL;
        (yyval.featureList).propertySet.size = 0;
    ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1523 "mof.y"
    {
        (yyval.featureList).propertySet.data = NULL;
        (yyval.featureList).propertySet.size = 0;
        (yyvsp[(1) - (1)].property)->flags = MI_FLAG_PROPERTY;
        (yyvsp[(1) - (1)].property)->flags |= GetQualFlags((yyvsp[(1) - (1)].property)->qualifiers, (yyvsp[(1) - (1)].property)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).propertySet, (yyvsp[(1) - (1)].property));
    ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1531 "mof.y"
    {
        if (FindProperty(&(yyvsp[(1) - (2)].featureList).propertySet, (yyvsp[(2) - (2)].property)->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "instance property already defined: \"%s\"", (yyvsp[(2) - (2)].property)->name);
            YYABORT;
        }

        (yyvsp[(2) - (2)].property)->flags = MI_FLAG_PROPERTY;
        (yyvsp[(2) - (2)].property)->flags |= GetQualFlags((yyvsp[(2) - (2)].property)->qualifiers, (yyvsp[(2) - (2)].property)->numQualifiers);
        MofPtrArray_Append((MofPtrArray*)&(yyval.featureList).propertySet, (yyvsp[(2) - (2)].property));
    ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1546 "mof.y"
    {
        MI_Type type = MI_STRING;		/* this is overwritten with the correct value in FinalizeInstance */
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->name = (yyvsp[(1) - (2)].string);
        (yyval.property)->type = type;
        (yyval.property)->value = NULL;
    ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1554 "mof.y"
    {
        MI_Type type = MI_STRING;		/* this is overwritten with the correct value in FinalizeInstance */
        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->name = (yyvsp[(2) - (3)].string);
        (yyval.property)->type = type;
        (yyval.property)->value = NULL;
        (yyval.property)->qualifiers = (yyvsp[(1) - (3)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (3)].qualifierList).size;
    ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1564 "mof.y"
    {
        void* value;
        MI_Type type = InitializerToType(&(yyvsp[(3) - (4)].initializer));

        if (InitializerToValue(&(yyvsp[(3) - (4)].initializer), type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->name = (yyvsp[(1) - (4)].string);
        (yyval.property)->type = type;
        (yyval.property)->value = value;
    ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1580 "mof.y"
    {
        void* value;
        MI_Type type = InitializerToType(&(yyvsp[(4) - (5)].initializer));

        if (InitializerToValue(&(yyvsp[(4) - (5)].initializer), type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        (yyval.property) = CALLOC_T(MI_PropertyDecl, 1);
        (yyval.property)->name = (yyvsp[(2) - (5)].string);
        (yyval.property)->type = type;
        (yyval.property)->value = value;
        (yyval.property)->qualifiers = (yyvsp[(1) - (5)].qualifierList).data;
        (yyval.property)->numQualifiers = (yyvsp[(1) - (5)].qualifierList).size;
    ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1600 "mof.y"
    {
        (yyval.qualifierList) = (yyvsp[(2) - (3)].qualifierList);
    ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1606 "mof.y"
    {
        (yyval.qualifierList).data = NULL;
        (yyval.qualifierList).size = 0;
        MofPtrArray_Append((MofPtrArray*)&(yyval.qualifierList), (yyvsp[(1) - (1)].qualifier));
    ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1612 "mof.y"
    {
        if (FindQualifier(&(yyvsp[(1) - (3)].qualifierList), (yyvsp[(3) - (3)].qualifier)->name))
        {
            yyerrorf(ID_DUPLICATE_QUALIFIER,
                "duplicate qualifier: \"%s\"", (yyvsp[(3) - (3)].qualifier)->name);
            YYABORT;
        }

        MofPtrArray_Append((MofPtrArray*)&(yyval.qualifierList), (yyvsp[(3) - (3)].qualifier));
    ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1625 "mof.y"
    {
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;

        qd = FindQualifierDeclaration((yyvsp[(1) - (1)].string));

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", (yyvsp[(1) - (1)].string));
            YYABORT;
        }

        if (qd->type != MI_BOOLEAN)
        {
            yyerrorf(ID_MISSING_QUALIFIER_INITIALIZER,
                "qualifier is missing initializer: \"%s\"", (yyvsp[(1) - (1)].string));
            YYABORT;
        }

        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = qd->flavor;
        q->value = NewTrueValue();
        (yyval.qualifier) = q;
    ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1652 "mof.y"
    {
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;
        void* value;

        qd = FindQualifierDeclaration((yyvsp[(1) - (2)].string));

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", (yyvsp[(1) - (2)].string));
            YYABORT;
        }

        if (InitializerToValue(&(yyvsp[(2) - (2)].initializer), qd->type, &value) != 0)
        {
            yyerrorf(ID_INVALID_QUALIFIER_INITIALIZER,
                "invalid initializer for qualifer: \"%s\"", (yyvsp[(1) - (2)].string));
            YYABORT;
        }

        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = qd->flavor;
        q->value = value;
        (yyval.qualifier) = q;
    ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1680 "mof.y"
    {
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;

        qd = FindQualifierDeclaration((yyvsp[(1) - (3)].string));

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", (yyvsp[(1) - (3)].string));
            YYABORT;
        }

        if (qd->type != MI_BOOLEAN)
        {
            yyerrorf(ID_MISSING_QUALIFIER_INITIALIZER,
                "qualifier is missing initializer: \"%s\"", (yyvsp[(1) - (3)].string));
            YYABORT;
        }

        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = PropagateFlavors((yyvsp[(3) - (3)].flags), qd->flavor);
        q->value = NewTrueValue();
        (yyval.qualifier) = q;
    ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1707 "mof.y"
    {
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;
        void* value;

        qd = FindQualifierDeclaration((yyvsp[(1) - (4)].string));

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", (yyvsp[(1) - (4)].string));
            YYABORT;
        }

        if (InitializerToValue(&(yyvsp[(2) - (4)].initializer), qd->type, &value) != 0)
        {
            yyerrorf(ID_INVALID_QUALIFIER_INITIALIZER,
                "invalid initializer for qualifer: \"%s\"", (yyvsp[(1) - (4)].string));
            YYABORT;
        }

        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->value = value;
        q->flavor = PropagateFlavors((yyvsp[(4) - (4)].flags), qd->flavor);
        (yyval.qualifier) = q;
    ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1737 "mof.y"
    {
        memset(&(yyval.initializer), 0, sizeof((yyval.initializer)));
        (yyval.initializer).data = CALLOC_T(MOF_ConstantValue, 1);
        (yyval.initializer).data[0] = (yyvsp[(2) - (3)].constantValue);
        (yyval.initializer).size = 1;
    ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1744 "mof.y"
    {
        (yyval.initializer) = (yyvsp[(1) - (1)].initializer);
    ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1750 "mof.y"
    {
        /* Reject incompatiable ToSubclass and Restricted flavors */
        if ((yyvsp[(4) - (5)].flags) & MI_FLAG_TOSUBCLASS && (yyvsp[(4) - (5)].flags) & MI_FLAG_RESTRICTED)
        {
            yyerrorf(ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s",
                "ToSubclass", "Restricted");
            YYABORT;
        }

        /* Reject incompatiable ToInstance and Restricted flavors */
        if ((yyvsp[(4) - (5)].flags) & MI_FLAG_TOINSTANCE && (yyvsp[(4) - (5)].flags) & MI_FLAG_RESTRICTED)
        {
            yyerrorf(ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s",
                "ToInstance", "Restricted");
            YYABORT;
        }

        /* Reject incompatiable EnableOverride and DisableOverride flavors */
        if ((yyvsp[(4) - (5)].flags) & MI_FLAG_ENABLEOVERRIDE && (yyvsp[(4) - (5)].flags) & MI_FLAG_DISABLEOVERRIDE)
        {
            yyerrorf(ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s",
                "EnableOverride", "DisableOverride");
            YYABORT;
        }

        (yyval.flags) = (yyvsp[(4) - (5)].flags);
    ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1780 "mof.y"
    {
        (yyval.flags) = (yyvsp[(1) - (1)].flags);
    ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1784 "mof.y"
    {
        (yyval.flags) |= (yyvsp[(3) - (3)].flags);
    ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1790 "mof.y"
    {
        (yyval.flags) = (yyvsp[(1) - (1)].flags);
    ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1794 "mof.y"
    {
        (yyval.flags) |= (yyvsp[(2) - (2)].flags);
    ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1800 "mof.y"
    {
        MI_Uint32 flag;
        flag = GetFlavorFlag((yyvsp[(1) - (1)].string));
        if (flag == MI_FLAG_NULL)
        {
            yyerrorf(ID_UNKNOWN_FLAVOR, "invalid qualifer flavor: \"%s\"", (yyvsp[(1) - (1)].string));
            YYABORT;
        }
        (yyval.flags) = flag;
    ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1813 "mof.y"
    {
        memset(&(yyval.initializer), 0, sizeof((yyval.initializer)));
        (yyval.initializer).data = CALLOC_T(MOF_ConstantValue, 1);
        (yyval.initializer).data[0] = (yyvsp[(1) - (1)].constantValue);
        (yyval.initializer).size = 1;
        (yyval.initializer).isArray = MI_FALSE;
    ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1821 "mof.y"
    {
        (yyval.initializer) = (yyvsp[(1) - (1)].initializer);
    ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1827 "mof.y"
    {
        (yyval.initializer) = (yyvsp[(2) - (3)].initializer);
    ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1831 "mof.y"
    {
        (yyval.initializer).data = NULL;
        (yyval.initializer).size = 0;
        (yyval.initializer).isArray = MI_TRUE;
    ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1839 "mof.y"
    {
        memset(&(yyval.initializer), 0, sizeof((yyval.initializer)));
        (yyval.initializer).data = CALLOC_T(MOF_ConstantValue, 1);
        (yyval.initializer).data[0] = (yyvsp[(1) - (1)].constantValue);
        (yyval.initializer).size = 1;
        (yyval.initializer).isArray = MI_TRUE;
    ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1847 "mof.y"
    {
        (yyvsp[(1) - (3)].initializer).data = REALLOC_T(MOF_ConstantValue, (yyvsp[(1) - (3)].initializer).data, (yyvsp[(1) - (3)].initializer).size + 1);
        (yyvsp[(1) - (3)].initializer).data[(yyvsp[(1) - (3)].initializer).size] = (yyvsp[(3) - (3)].constantValue);
        (yyvsp[(1) - (3)].initializer).size++;
        (yyvsp[(1) - (3)].initializer).isArray = MI_TRUE;
        (yyval.initializer) = (yyvsp[(1) - (3)].initializer);
    ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1857 "mof.y"
    {
        (yyval.constantValue) = (yyvsp[(1) - (1)].constantValue);
	;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1861 "mof.y"
    {
        (yyval.constantValue).type = TOK_INSTANCE;
        (yyval.constantValue).value.instanceDecl = NULL;
        /* TODO: look up alias, get and store instance decl. for alias */
        (yyval.constantValue).tooBigForSint64 = MI_FALSE;
	;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1868 "mof.y"
    {
        (yyval.constantValue).type = TOK_INSTANCE;
        (yyval.constantValue).value.instanceDecl = NULL;
        /* TODO: lopok up class type of $3, make sure instance fields match class, store instance */
        (yyval.constantValue).tooBigForSint64 = MI_FALSE;
	;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1877 "mof.y"
    {
        memset(&(yyval.initializer), 0, sizeof((yyval.initializer)));
        (yyval.initializer).data = CALLOC_T(MOF_ConstantValue, 1);
        (yyval.initializer).data[0] = (yyvsp[(1) - (1)].constantValue);
        (yyval.initializer).size = 1;
    ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1884 "mof.y"
    {
        (yyval.initializer) = (yyvsp[(1) - (1)].initializer);
    ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1890 "mof.y"
    {
        (yyval.initializer) = (yyvsp[(2) - (3)].initializer);
	;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1894 "mof.y"
    {
        (yyval.initializer).data = NULL;
        (yyval.initializer).size = 0;
        (yyval.initializer).isArray = MI_TRUE;
    ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1902 "mof.y"
    {
        memset(&(yyval.initializer), 0, sizeof((yyval.initializer)));
        (yyval.initializer).data = CALLOC_T(MOF_ConstantValue, 1);
        (yyval.initializer).data[0] = (yyvsp[(1) - (1)].constantValue);
        (yyval.initializer).size = 1;
        (yyval.initializer).isArray = MI_TRUE;
    ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1910 "mof.y"
    {
        (yyvsp[(1) - (3)].initializer).data = REALLOC_T(MOF_ConstantValue, (yyvsp[(1) - (3)].initializer).data, (yyvsp[(1) - (3)].initializer).size + 1);
        (yyvsp[(1) - (3)].initializer).data[(yyvsp[(1) - (3)].initializer).size] = (yyvsp[(3) - (3)].constantValue);
        (yyvsp[(1) - (3)].initializer).size++;
        (yyvsp[(1) - (3)].initializer).isArray = MI_TRUE;
        (yyval.initializer) = (yyvsp[(1) - (3)].initializer);
    ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1920 "mof.y"
    {
        (yyval.constantValue).type = TOK_STRING_VALUE;
        (yyval.constantValue).value.string = (yyvsp[(1) - (1)].string);
    ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1925 "mof.y"
    {
        (yyval.constantValue).type = TOK_INTEGER_VALUE;
        (yyval.constantValue).value.integer = (yyvsp[(1) - (1)].integer);
    ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1930 "mof.y"
    {
        (yyval.constantValue).type = TOK_BOOLEAN_VALUE;
        (yyval.constantValue).value.boolean = (yyvsp[(1) - (1)].boolean);
    ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1935 "mof.y"
    {
        (yyval.constantValue).type = TOK_REAL_VALUE;
        (yyval.constantValue).value.real = (yyvsp[(1) - (1)].real);
    ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1940 "mof.y"
    {
        (yyval.constantValue).type = TOK_CHAR_VALUE;
        (yyval.constantValue).value.character = (yyvsp[(1) - (1)].character);
    ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1945 "mof.y"
    {
        (yyval.constantValue).type = TOK_NULL;
    ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1951 "mof.y"
    {
        (yyval.string) = (yyvsp[(1) - (1)].string);
    ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1955 "mof.y"
    {
        size_t size = strlen((yyvsp[(1) - (2)].string)) + strlen((yyvsp[(2) - (2)].string)) + 1;
        (yyval.string) = (char*)MOF_Realloc(&state.heap, (yyvsp[(1) - (2)].string), size);
        Strcat((yyval.string), size, (yyvsp[(2) - (2)].string));
        MOF_Free(&state.heap, (yyvsp[(2) - (2)].string));
    ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1967 "mof.y"
    {
        (yyval.string) = (yyvsp[(1) - (1)].string);
    ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1971 "mof.y"
    {
        (yyval.string) = "Boolean";
    ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1975 "mof.y"
    {
        (yyval.string) = "Datetime";
    ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1979 "mof.y"
    {
        (yyval.string) = "String";
    ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1983 "mof.y"
    {
        (yyval.string) = "Object";
    ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1987 "mof.y"
    {
        (yyval.string) = "Qualifier";
    ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1996 "mof.y"
    {
        (yyval.string) = (yyvsp[(1) - (1)].string);
    ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 2002 "mof.y"
    {
        (yyval.type) = MI_BOOLEAN;
    ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 2006 "mof.y"
    {
        (yyval.type) = MI_SINT8;
    ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 2010 "mof.y"
    {
        (yyval.type) = MI_UINT8;
    ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 2014 "mof.y"
    {
        (yyval.type) = MI_SINT16;
    ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 2018 "mof.y"
    {
        (yyval.type) = MI_UINT16;
    ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 2022 "mof.y"
    {
        (yyval.type) = MI_SINT32;
    ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 2026 "mof.y"
    {
        (yyval.type) = MI_UINT32;
    ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 2030 "mof.y"
    {
        (yyval.type) = MI_SINT64;
    ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 2034 "mof.y"
    {
        (yyval.type) = MI_UINT64;
    ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 2038 "mof.y"
    {
        (yyval.type) = MI_REAL32;
    ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 2042 "mof.y"
    {
        (yyval.type) = MI_REAL64;
    ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 2046 "mof.y"
    {
        (yyval.type) = MI_CHAR16;
    ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 2050 "mof.y"
    {
        (yyval.type) = MI_DATETIME;
    ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 2054 "mof.y"
    {
        (yyval.type) = MI_STRING;
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 4421 "mof.tab.c"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



