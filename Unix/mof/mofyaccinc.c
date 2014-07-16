
# line 2 "mof.y"

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "buffer.h"
#include "types.h"
#include "state.h"
#include "ptrarray.h"

#define ARRAYOF(TYPE) ((MI_Uint32)TYPE | (MI_Uint32)MI_ARRAY_BIT)

extern int yylex();
extern int openIncludeFile(const char* path);


# line 20 "mof.y"
typedef union
#ifdef __cplusplus
        YYSTYPE
#endif

{
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
} YYSTYPE;
# define TOK_ERROR 257
# define TOK_BOOLEAN 258
# define TOK_SINT8 259
# define TOK_UINT8 260
# define TOK_SINT16 261
# define TOK_UINT16 262
# define TOK_SINT32 263
# define TOK_UINT32 264
# define TOK_SINT64 265
# define TOK_UINT64 266
# define TOK_REAL32 267
# define TOK_REAL64 268
# define TOK_DATETIME 269
# define TOK_CHAR16 270
# define TOK_STRING 271
# define TOK_OBJECT 272
# define TOK_BOOLEAN_VALUE 273
# define TOK_REF 274
# define TOK_SCOPE 275
# define TOK_CLASS 276
# define TOK_ASSOCIATION 277
# define TOK_INDICATION 278
# define TOK_QUALIFIER 279
# define TOK_PROPERTY 280
# define TOK_REFERENCE 281
# define TOK_METHOD 282
# define TOK_PARAMETER 283
# define TOK_ANY 284
# define TOK_FLAVOR 285
# define TOK_ENABLEOVERRIDE 286
# define TOK_DISABLEOVERRIDE 287
# define TOK_RESTRICTED 288
# define TOK_TOSUBCLASS 289
# define TOK_TOINSTANCE 290
# define TOK_TRANSLATABLE 291
# define TOK_INSTANCE 292
# define TOK_OF 293
# define TOK_AS 294
# define TOK_PRAGMA 295
# define TOK_SCHEMA 296
# define TOK_INTEGER_VALUE 297
# define TOK_REAL_VALUE 298
# define TOK_STRING_VALUE 299
# define TOK_CHAR_VALUE 300
# define TOK_IDENT 301
# define TOK_ALIAS_IDENTIFIER 302
# define TOK_NULL 303

#ifdef __STDC__
#include <stdlib.h>
#include <string.h>
#define YYCONST const
#else
#include <malloc.h>
#include <memory.h>
#define YYCONST
#endif

#if defined(__cplusplus) || defined(__STDC__)

#if defined(__cplusplus) && defined(__EXTERN_C__)
extern "C" {
#endif
#ifndef yyerror
#if defined(__cplusplus)
        void yyerror(YYCONST char *);
#endif
#endif
#ifndef yylex
        int yylex(void);
#endif
        int yyparse(void);
#if defined(__cplusplus) && defined(__EXTERN_C__)
}
#endif

#endif

#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
YYSTYPE yylval;
YYSTYPE yyval;
typedef int yytabelem;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
#if YYMAXDEPTH > 0
int yy_yys[YYMAXDEPTH], *yys = yy_yys;
YYSTYPE yy_yyv[YYMAXDEPTH], *yyv = yy_yyv;
#else   /* user does initial allocation */
int *yys;
YYSTYPE *yyv;
#endif
static int yymaxdepth = YYMAXDEPTH;
# define YYERRCODE 256
static YYCONST yytabelem yyexca[] ={
-1, 1,
        0, -1,
        -2, 0,
        };
# define YYNPROD 190
# define YYLAST 1108
static YYCONST yytabelem yyact[]={

   151,   147,   149,   201,   102,   155,   119,    15,    13,   120,
   121,    61,    96,   190,   240,    13,    98,   202,   257,    48,
   152,   103,   104,   105,   106,   107,   108,    39,   183,   145,
   310,   265,    33,   210,    42,    75,    76,    77,    78,    79,
    80,    81,    82,    83,    84,    85,    87,    86,    88,   134,
   208,   185,    90,    19,    22,    23,    26,    25,    24,   304,
    52,    21,    30,    31,    45,    44,    27,    28,    29,   335,
    20,   160,    18,    95,    96,    42,    46,   250,    17,    32,
   241,   242,   243,    57,   244,   245,   246,   247,   248,    36,
   101,   282,   131,   284,   135,   137,   148,   146,    54,    66,
    37,    56,    38,    35,   100,   171,   157,    19,    22,    23,
    26,    25,    24,    89,   188,    21,    30,    46,   354,   114,
    27,    28,    29,   148,    20,   207,    18,   148,   122,    46,
    97,   353,    17,   164,   322,   349,   323,   173,   206,   177,
   303,   161,   259,   110,   111,    61,   112,    53,   205,   115,
   192,   348,   159,   167,   168,   170,   318,   175,   319,   179,
   347,   157,    70,   125,   144,   140,    59,   345,    59,   215,
   219,   154,   223,   343,   196,    36,   342,   231,   228,   142,
    69,   236,   234,    98,   341,   340,    37,    13,    38,    35,
   221,   156,   225,    19,    22,    23,    26,    25,    24,   252,
     9,    21,    30,    11,   255,   180,    27,    28,    29,   292,
    20,   293,    18,    68,   334,   181,    12,   189,    17,     8,
   270,   123,   141,   278,   275,   260,   129,   283,   281,   272,
   330,   285,   264,    13,   287,   328,   288,   290,   289,    67,
   249,   294,    65,   296,   128,   326,    19,    22,    23,    26,
    25,    24,   325,   321,    21,    30,   316,   314,   300,    27,
    28,    29,   312,    20,   121,    18,   307,    64,   271,   305,
   217,    17,   301,   311,   209,   114,   299,   127,   315,    13,
   279,   317,   280,   273,   320,   274,   308,   309,   324,   214,
   114,   216,    50,   327,   206,   291,   306,   329,   286,   110,
   111,    61,   112,   126,   205,   115,   124,   263,   256,   206,
   337,   338,   117,   333,   110,   111,    61,   112,   114,   205,
   115,   148,   336,   344,    13,   251,   193,   346,   166,   182,
   268,   339,   269,   253,   162,   254,   350,   332,   351,   130,
   331,   352,   110,   111,    61,   112,    93,   163,   115,   165,
   198,   276,   192,   277,    75,    76,    77,    78,    79,    80,
    81,    82,    83,    84,    85,    87,    86,    88,    74,    13,
     4,   158,    19,    22,    23,    26,    25,    24,   238,   148,
    21,    30,   232,   148,   233,    27,    28,    29,   226,    20,
   227,    18,   235,   229,   237,   230,   222,    17,   224,   184,
    75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
    85,    87,    86,    88,    74,   199,    41,   200,    19,    22,
    23,    26,    25,    24,   148,   148,    21,    30,   148,    43,
     7,    27,    28,    29,   194,    20,   195,    18,   218,     5,
   220,    13,   176,    17,   178,   187,    75,    76,    77,    78,
    79,    80,    81,    82,    83,    84,    85,    87,    86,    88,
   114,     2,   113,    14,    19,    22,    23,    26,    25,    24,
   148,    99,    21,    30,   148,   355,    55,    27,    28,    29,
    40,    20,    13,    18,   110,   111,    61,   112,    58,    17,
   115,    75,    76,    77,    78,    79,    80,    81,    82,    83,
    84,    85,    87,    86,    88,   114,    60,   143,   295,    19,
    22,    23,    26,    25,    24,    92,   191,    21,    30,   172,
   239,   174,    27,    28,    29,   116,    20,    13,    18,   110,
   111,    61,   112,   258,    17,   115,    75,    76,    77,    78,
    79,    80,    81,    82,    83,    84,    85,    87,    86,    88,
   313,   148,   203,   262,    19,    22,    23,    26,    25,    24,
    49,   150,    21,    30,     6,    63,     1,    27,    28,    29,
     0,    20,   297,    18,   261,   298,     0,   262,     0,    17,
    75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
    85,    87,    86,    88,     0,     0,     0,     0,    19,    22,
    23,    26,    25,    24,     0,     0,    21,    30,    36,     0,
     0,    27,    28,    29,     0,    20,     0,    18,     0,    37,
     0,    38,    35,    17,     0,     0,    19,    22,    23,    26,
    25,    24,     0,     0,    21,    30,     0,     0,     0,    27,
    28,    29,     0,    20,     0,    18,    13,     0,     0,    36,
     0,    17,     0,     0,     0,    34,     0,     0,     0,     0,
    37,     0,    38,    35,     0,    16,     0,    19,    22,    23,
    26,    25,    24,     0,     0,    21,    30,     0,     0,     0,
    27,    28,    29,   211,    20,     0,    18,    47,     0,     0,
     0,     0,    17,     0,    36,    51,     0,     0,     0,     0,
     0,    62,    73,     0,    91,    37,     0,    38,    35,     0,
     0,     0,    19,    22,    23,    26,    25,    24,     0,    73,
    21,    30,    36,     0,     0,    27,    28,    29,   133,    20,
    71,    18,     0,    37,    94,    38,    35,    17,   169,     0,
    19,    22,    23,    26,    25,    24,   139,    71,    21,    30,
    36,     0,     0,    27,    28,    29,   132,    20,   204,    18,
     0,    37,     0,    38,    35,    17,   138,     0,    19,    22,
    23,    26,    25,    24,     0,     0,    21,    30,    36,     0,
     0,    27,    28,    29,     0,    20,     0,    18,     0,    37,
     0,    38,    35,    17,   136,     0,    19,    22,    23,    26,
    25,    24,     0,     0,    21,    30,    36,     0,     0,    27,
    28,    29,     3,    20,     0,    18,   109,    37,   118,    38,
    35,    17,   212,     0,    19,    22,    23,    26,    25,    24,
     0,     9,    21,    30,    11,     0,     0,    27,    28,    29,
     0,    20,     0,    18,   153,    10,    10,    12,     0,    17,
     8,    75,    76,    77,    78,    79,    80,    81,    82,    83,
    84,    85,    87,    86,    88,     0,     0,     0,     0,   267,
     0,     0,     0,   212,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    72,     0,     0,     0,     0,     0,   266,     0,     0,
     0,     0,     0,     0,     0,   186,     0,     0,    72,     0,
     0,     0,     0,   302,     0,     0,     0,     0,   212,   197,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   186,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   213,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   213,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   213 };
static YYCONST yytabelem yypact[]={

   555,   -76,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,  -294,   -30,
  -213,   548,  -266,   548,-10000000,   389,     6,-10000000,-10000000,-10000000,
-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,
-10000000,   -30,  -274,   234,-10000000,-10000000,-10000000,-10000000,-10000000,   548,
    54,-10000000,    43,  -288,-10000000,   -30,   142,    -6,   -30,   302,
   593,   -49,  -278,-10000000,   548,    46,  -265,   232,-10000000,   187,
   -35,-10000000,   -47,    96,   280,-10000000,-10000000,-10000000,-10000000,-10000000,
-10000000,   548,  -223,   520,   492,-10000000,-10000000,-10000000,-10000000,-10000000,
-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,
   -30,  -111,   120,  -246,    36,-10000000,   436,   -49,  -297,-10000000,
  -265,  -265,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,   330,
-10000000,-10000000,-10000000,  -289,-10000000,-10000000,    27,-10000000,-10000000,-10000000,
   548,-10000000,-10000000,   275,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,
-10000000,   288,   548,   464,  -169,   460,   548,   383,   548,   -47,
-10000000,   -49,-10000000,   270,  -257,   359,    45,    53,   -80,   391,
   267,-10000000,   375,   548,-10000000,-10000000,  -265,-10000000,-10000000,-10000000,
   232,   309,-10000000,-10000000,   356,     2,   233,   230,   379,   548,
   337,   548,-10000000,   329,     2,   334,-10000000,   323,     2,   333,
-10000000,-10000000,-10000000,   338,  -196,-10000000,-10000000,-10000000,    45,   -16,
-10000000,   266,-10000000,-10000000,-10000000,     2,   274,-10000000,-10000000,-10000000,
     2,   249,-10000000,-10000000,-10000000,-10000000,  -275,    17,   533,   248,
-10000000,   548,  -243,   322,-10000000,   271,     2,   188,-10000000,   224,
     2,   292,-10000000,   221,     2,    32,-10000000,     2,   239,-10000000,
     2,   177,-10000000,     2,   236,-10000000,   150,     2,  -265,   531,
-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,
-10000000,-10000000,   217,-10000000,     2,   213,-10000000,   -30,    15,-10000000,
-10000000,   210,   278,-10000000,     5,   548,   548,  -244,-10000000,     2,
   203,   509,   198,-10000000,     2,   197,-10000000,     2,    97,-10000000,
     2,   194,-10000000,    75,     2,   193,-10000000,   186,-10000000,     2,
   176,-10000000,-10000000,     2,   171,   296,-10000000,-10000000,  -196,-10000000,
   155,-10000000,   -54,-10000000,  -154,-10000000,-10000000,-10000000,     5,     5,
   548,   126,-10000000,   125,-10000000,   117,-10000000,   114,-10000000,     2,
   108,-10000000,-10000000,     2,   101,-10000000,-10000000,    92,-10000000,    76,
-10000000,  -265,-10000000,-10000000,-10000000,   -83,-10000000,-10000000,-10000000,     5,
-10000000,-10000000,-10000000,-10000000,    72,-10000000,    59,-10000000,-10000000,-10000000,
-10000000,   350,-10000000,-10000000,-10000000,-10000000 };
static YYCONST yytabelem yypgo[]={

     0,   566,   462,   655,    20,   130,   758,   683,   242,    33,
    50,   239,   213,   180,   162,    99,   565,    65,    73,   564,
   560,     1,     3,   552,   533,    17,    51,   445,   525,    14,
   520,   515,     4,   508,    90,   507,   416,   480,   844,   476,
   439,   430,     0,     2,   461,   370 };
static YYCONST yytabelem yyr1[]={

     0,     1,     1,     1,    44,    44,    44,    44,    45,    45,
    40,    40,    40,    40,    17,    17,    16,    16,    16,    16,
    16,    16,    16,    16,    16,    16,    16,    16,    38,    37,
    37,    36,    36,    36,    36,    39,    39,    33,    33,    34,
    34,    32,    32,    32,    32,    32,    32,     8,     8,     8,
     8,     8,     8,     8,     8,    13,    13,    13,    13,    13,
    13,    13,    13,    14,    14,    14,    14,    14,    14,    14,
    14,    11,    11,    11,    11,    11,    11,    11,    11,    12,
    12,    12,    12,    12,    12,    12,    12,    15,    15,    15,
    15,    10,    10,     9,     9,     9,     9,     9,     9,     9,
     9,    21,    21,    22,    22,    23,    23,    24,    24,    25,
    25,    25,    26,    26,    27,    27,    28,    28,     6,     6,
     6,     6,     6,     6,     2,     2,    19,    19,    20,    20,
    20,    20,    31,    30,    30,    29,    29,    29,    29,    29,
    29,    29,    29,    35,    41,    41,    41,    41,    18,    18,
     5,    43,    43,    42,    42,    42,    42,     4,     4,     4,
     4,     4,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     7,     7,     7,     7,
     7,     7,     7,     7,     7,     7,     7,     7,     7,     7 };
static YYCONST yytabelem yyr2[]={

     0,     3,     5,     3,     3,     3,     3,     3,    11,    15,
     7,    11,     9,    13,     9,     7,     3,     3,     3,     3,
     3,     3,     5,     5,     5,     5,     5,     5,     7,     3,
     7,     3,     5,     7,     9,     7,     3,     3,     7,     3,
     5,     3,     3,     3,     3,     3,     3,     7,     9,     9,
    11,    11,    13,    13,    15,     7,     9,     9,    11,    11,
    13,    13,    15,     7,     9,     9,    11,    11,    13,    13,
    15,     9,    11,    13,    15,    11,    13,    15,    17,     9,
    11,    11,    13,    13,    15,    15,    17,    13,    15,    11,
    13,     3,     7,     5,     7,     7,     9,     7,     9,     9,
    11,     7,     5,     3,     3,     7,     5,     3,     7,     3,
     3,    13,     3,     3,     7,     5,     3,     7,     3,     3,
     3,     3,     3,     3,     3,     5,    11,    13,     5,     9,
     7,    11,    11,     3,     7,     3,     3,     3,     3,     3,
     3,     3,     3,    11,     9,    11,    11,    13,     9,     7,
     5,     3,     5,     5,     7,     9,    11,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3 };
static YYCONST yytabelem yychk[]={

-10000000,    -1,   -44,   257,   -45,   -40,   -19,   -41,   295,   276,
   -38,   279,   292,    91,   -44,   301,    -3,   301,   295,   276,
   293,   284,   277,   278,   281,   280,   279,   289,   290,   291,
   285,   276,   292,    -4,    -3,   272,   258,   269,   271,   293,
   -37,   -36,    -4,    40,   -17,    58,   123,    -3,   293,   -20,
    58,    -3,    -4,    93,    44,   -39,    58,    40,   -27,   123,
    -2,   299,    -3,   -16,   125,    -8,   -15,   -11,   -12,   -13,
   -14,    -7,   -38,    -3,   272,   258,   259,   260,   261,   262,
   263,   264,   265,   266,   267,   268,   270,   269,   271,   -17,
    58,    -3,   -31,    44,    -7,   -18,   123,    -5,   294,   -36,
    58,   -34,   -32,   286,   287,   288,   289,   290,   291,    -6,
   297,   298,   300,    -2,   273,   303,   -28,   125,    -6,    41,
    44,   299,   -17,   125,    -8,   -15,   -11,   -12,   -13,   -14,
    59,    -4,    -7,    -3,   272,    -4,   274,    -4,   274,    -3,
   -18,    -5,    59,   -35,    44,   275,    61,   -21,    91,   -43,
   125,   -42,    -4,   -38,   -18,   302,   -34,   -32,    41,   125,
    44,    -4,    59,    59,   -21,    61,    40,    -4,    -4,   274,
    -4,   274,    59,   -21,    61,    -4,    59,   -21,    61,    -4,
   -17,   -18,    59,   285,    40,   -26,    -6,   -27,    61,   297,
    93,   125,   -42,    59,    59,    61,    -4,    -6,    41,    59,
    61,   -22,   -25,   -23,    -6,   302,   292,   123,   -10,    41,
    -9,    -7,    -3,   -38,    59,   -21,    61,    40,    59,   -21,
    61,    -4,    59,   -21,    61,    -4,    59,    61,   -22,    59,
    61,   -21,    59,    61,   -22,    59,   -21,    61,    40,   -30,
   -29,   276,   277,   278,   280,   281,   282,   283,   284,   -26,
    93,    59,   -22,    59,    61,   -22,    59,   293,   -24,   125,
   -25,    41,    44,    59,    -4,   274,    -7,    -3,    59,    61,
   -22,   -10,    41,    59,    61,   -22,    59,    61,   -21,    59,
    61,   -22,    59,   -21,    61,   -22,    59,   -22,    59,    61,
   -22,    59,    59,    61,   -22,   -33,   -32,    41,    44,    59,
   -22,    59,    -3,   125,    44,    59,    -9,   -21,    -4,    -4,
   274,   -22,    59,    41,    59,   -22,    59,   -22,    59,    61,
   -22,    59,    59,    61,   -22,    59,    59,   -22,    59,   -22,
    59,    44,    41,   -29,    59,   123,   -25,   -21,   -21,    -4,
    59,    59,    59,    59,   -22,    59,   -22,    59,    59,    59,
   -32,   -43,   -21,    59,    59,   125 };
static YYCONST yytabelem yydef[]={

     0,    -2,     1,     3,     4,     5,     6,     7,     0,     0,
     0,     0,     0,     0,     2,     0,     0,   162,   163,   164,
   165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
   175,     0,     0,     0,   157,   158,   159,   160,   161,     0,
     0,    29,    31,     0,    10,     0,     0,     0,     0,     0,
     0,   157,     0,    28,     0,    32,     0,     0,    36,     0,
     0,   124,     0,     0,     0,    16,    17,    18,    19,    20,
    21,     0,     0,     0,     0,   176,   177,   178,   179,   180,
   181,   182,   183,   184,   185,   186,   187,   188,   189,    12,
     0,     0,     0,     0,   128,   144,     0,     0,     0,    30,
     0,    33,    39,    41,    42,    43,    44,    45,    46,     0,
   118,   119,   120,   121,   122,   123,     0,   115,   116,     8,
     0,   125,    11,     0,    22,    23,    24,    25,    26,    27,
    15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   145,     0,   126,     0,     0,     0,     0,   130,     0,     0,
     0,   151,     0,     0,   146,   150,    34,    40,    35,   114,
     0,     0,    14,    47,     0,     0,     0,     0,     0,     0,
     0,     0,    55,     0,     0,     0,    63,     0,     0,     0,
    13,   147,   127,     0,     0,   129,   112,   113,     0,     0,
   102,     0,   152,   149,   153,     0,     0,   117,     9,    49,
     0,     0,   103,   104,   109,   110,     0,     0,     0,     0,
    91,     0,     0,     0,    48,     0,     0,     0,    56,     0,
     0,     0,    64,     0,     0,     0,    57,     0,     0,    71,
     0,     0,    65,     0,     0,    79,     0,     0,     0,     0,
   133,   135,   136,   137,   138,   139,   140,   141,   142,   131,
   101,   148,     0,   154,     0,     0,    51,     0,     0,   106,
   107,     0,     0,    89,    93,     0,     0,     0,    50,     0,
     0,     0,     0,    58,     0,     0,    72,     0,     0,    66,
     0,     0,    80,     0,     0,     0,    59,     0,    75,     0,
     0,    67,    81,     0,     0,     0,    37,   132,     0,   155,
     0,    53,     0,   105,     0,    87,    92,    97,    94,    95,
     0,     0,    52,     0,    90,     0,    60,     0,    76,     0,
     0,    68,    82,     0,     0,    61,    73,     0,    69,     0,
    83,     0,   143,   134,   156,     0,   108,    98,    99,    96,
    54,    88,    62,    74,     0,    70,     0,    85,    77,    84,
    38,     0,   100,    78,    86,   111 };
typedef struct
#ifdef __cplusplus
        yytoktype
#endif
{
#ifdef __cplusplus
const
#endif
char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#       define YYDEBUG  0       /* don't allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =
{
        { "TOK_ERROR",  257 },
        { "TOK_BOOLEAN",        258 },
        { "TOK_SINT8",  259 },
        { "TOK_UINT8",  260 },
        { "TOK_SINT16", 261 },
        { "TOK_UINT16", 262 },
        { "TOK_SINT32", 263 },
        { "TOK_UINT32", 264 },
        { "TOK_SINT64", 265 },
        { "TOK_UINT64", 266 },
        { "TOK_REAL32", 267 },
        { "TOK_REAL64", 268 },
        { "TOK_DATETIME",       269 },
        { "TOK_CHAR16", 270 },
        { "TOK_STRING", 271 },
        { "TOK_OBJECT", 272 },
        { "TOK_BOOLEAN_VALUE",  273 },
        { "TOK_REF",    274 },
        { "TOK_SCOPE",  275 },
        { "TOK_CLASS",  276 },
        { "TOK_ASSOCIATION",    277 },
        { "TOK_INDICATION",     278 },
        { "TOK_QUALIFIER",      279 },
        { "TOK_PROPERTY",       280 },
        { "TOK_REFERENCE",      281 },
        { "TOK_METHOD", 282 },
        { "TOK_PARAMETER",      283 },
        { "TOK_ANY",    284 },
        { "TOK_FLAVOR", 285 },
        { "TOK_ENABLEOVERRIDE", 286 },
        { "TOK_DISABLEOVERRIDE",        287 },
        { "TOK_RESTRICTED",     288 },
        { "TOK_TOSUBCLASS",     289 },
        { "TOK_TOINSTANCE",     290 },
        { "TOK_TRANSLATABLE",   291 },
        { "TOK_INSTANCE",       292 },
        { "TOK_OF",     293 },
        { "TOK_AS",     294 },
        { "TOK_PRAGMA", 295 },
        { "TOK_SCHEMA", 296 },
        { "TOK_INTEGER_VALUE",  297 },
        { "TOK_REAL_VALUE",     298 },
        { "TOK_STRING_VALUE",   299 },
        { "TOK_CHAR_VALUE",     300 },
        { "TOK_IDENT",  301 },
        { "TOK_ALIAS_IDENTIFIER",       302 },
        { "TOK_NULL",   303 },
        { "-unknown-", }        -1      /* ends search */
}; 

#ifdef __cplusplus
const
#endif
char * yyreds[] =
{
        "-no such reduction-",
        "mofSpecification : mofProduction",
        "mofSpecification : mofSpecification mofProduction",
        "mofSpecification : TOK_ERROR",
        "mofProduction : compilerDirective",
        "mofProduction : classDeclaration",
        "mofProduction : qualifierDeclaration",
        "mofProduction : instanceDeclaration",
        "compilerDirective : TOK_PRAGMA TOK_IDENT '(' stringValue ')'",
        "compilerDirective : TOK_PRAGMA TOK_IDENT '(' stringValue ',' identifier ')'",
        "classDeclaration : TOK_CLASS classNameIdentifier classBody",
        "classDeclaration : TOK_CLASS classNameIdentifier ':' classNameIdentifier classBody",
        "classDeclaration : qualifierExpr TOK_CLASS classNameIdentifier classBody",
        "classDeclaration : qualifierExpr TOK_CLASS classNameIdentifier ':' classNameIdentifier classBody",
        "classBody : '{' classFeatureList '}' ';'",
        "classBody : '{' '}' ';'",
        "classFeatureList : propertyDeclaration",
        "classFeatureList : methodDeclaration",
        "classFeatureList : referenceDeclaration",
        "classFeatureList : dynamicReferenceDeclaration",
        "classFeatureList : staticEmbeddedInstanceDeclaration",
        "classFeatureList : dynamicEmbeddedInstanceDeclaration",
        "classFeatureList : classFeatureList propertyDeclaration",
        "classFeatureList : classFeatureList methodDeclaration",
        "classFeatureList : classFeatureList referenceDeclaration",
        "classFeatureList : classFeatureList dynamicReferenceDeclaration",
        "classFeatureList : classFeatureList staticEmbeddedInstanceDeclaration",
        "classFeatureList : classFeatureList dynamicEmbeddedInstanceDeclaration",
        "qualifierExpr : '[' qualifierList ']'",
        "qualifierList : qualifier",
        "qualifierList : qualifierList ',' qualifier",
        "qualifier : identifier",
        "qualifier : identifier qualifierParameter",
        "qualifier : identifier ':' qualifierFlavorList",
        "qualifier : identifier qualifierParameter ':' qualifierFlavorList",
        "qualifierParameter : '(' constantValue ')'",
        "qualifierParameter : nonAggregateArrayInitializer",
        "flavorList : flavor",
        "flavorList : flavorList ',' flavor",
        "qualifierFlavorList : flavor",
        "qualifierFlavorList : qualifierFlavorList flavor",
        "flavor : TOK_ENABLEOVERRIDE",
        "flavor : TOK_DISABLEOVERRIDE",
        "flavor : TOK_RESTRICTED",
        "flavor : TOK_TOSUBCLASS",
        "flavor : TOK_TOINSTANCE",
        "flavor : TOK_TRANSLATABLE",
        "propertyDeclaration : dataType identifier ';'",
        "propertyDeclaration : qualifierExpr dataType identifier ';'",
        "propertyDeclaration : dataType identifier subscript ';'",
        "propertyDeclaration : qualifierExpr dataType identifier subscript ';'",
        "propertyDeclaration : dataType identifier '=' initializer ';'",
        "propertyDeclaration : qualifierExpr dataType identifier '=' initializer ';'",
        "propertyDeclaration : dataType identifier subscript '=' initializer ';'",
        "propertyDeclaration : qualifierExpr dataType identifier subscript '=' initializer ';'",
        "staticEmbeddedInstanceDeclaration : classNameIdentifier identifier ';'",
        "staticEmbeddedInstanceDeclaration : qualifierExpr classNameIdentifier identifier ';'",
        "staticEmbeddedInstanceDeclaration : classNameIdentifier identifier subscript ';'",
        "staticEmbeddedInstanceDeclaration : qualifierExpr classNameIdentifier identifier subscript ';'",
        "staticEmbeddedInstanceDeclaration : classNameIdentifier identifier '=' initializer ';'",
        "staticEmbeddedInstanceDeclaration : qualifierExpr classNameIdentifier identifier '=' initializer ';'",
        "staticEmbeddedInstanceDeclaration : classNameIdentifier identifier subscript '=' initializer ';'",
        "staticEmbeddedInstanceDeclaration : qualifierExpr classNameIdentifier identifier subscript '=' initializer ';'",
        "dynamicEmbeddedInstanceDeclaration : TOK_OBJECT identifier ';'",
        "dynamicEmbeddedInstanceDeclaration : qualifierExpr TOK_OBJECT identifier ';'",
        "dynamicEmbeddedInstanceDeclaration : TOK_OBJECT identifier subscript ';'",
        "dynamicEmbeddedInstanceDeclaration : qualifierExpr TOK_OBJECT identifier subscript ';'",
        "dynamicEmbeddedInstanceDeclaration : TOK_OBJECT identifier '=' initializer ';'",
        "dynamicEmbeddedInstanceDeclaration : qualifierExpr TOK_OBJECT identifier '=' initializer ';'",
        "dynamicEmbeddedInstanceDeclaration : TOK_OBJECT identifier subscript '=' initializer ';'",
        "dynamicEmbeddedInstanceDeclaration : qualifierExpr TOK_OBJECT identifier subscript '=' initializer ';'",
        "referenceDeclaration : classNameIdentifier TOK_REF identifier ';'",
        "referenceDeclaration : qualifierExpr classNameIdentifier TOK_REF identifier ';'",
        "referenceDeclaration : classNameIdentifier TOK_REF identifier '=' initializer ';'",
        "referenceDeclaration : qualifierExpr classNameIdentifier TOK_REF identifier '=' initializer ';'",
        "referenceDeclaration : classNameIdentifier TOK_REF identifier subscript ';'",
        "referenceDeclaration : qualifierExpr classNameIdentifier TOK_REF identifier subscript ';'",
        "referenceDeclaration : classNameIdentifier TOK_REF identifier subscript '=' initializer ';'",
        "referenceDeclaration : qualifierExpr classNameIdentifier TOK_REF identifier subscript '=' initializer ';'",
        "dynamicReferenceDeclaration : TOK_OBJECT TOK_REF identifier ';'",
        "dynamicReferenceDeclaration : qualifierExpr TOK_OBJECT TOK_REF identifier ';'",
        "dynamicReferenceDeclaration : TOK_OBJECT TOK_REF identifier subscript ';'",
        "dynamicReferenceDeclaration : qualifierExpr TOK_OBJECT TOK_REF identifier subscript ';'",
        "dynamicReferenceDeclaration : TOK_OBJECT TOK_REF identifier '=' initializer ';'",
        "dynamicReferenceDeclaration : TOK_OBJECT TOK_REF identifier subscript '=' initializer ';'",
        "dynamicReferenceDeclaration : qualifierExpr TOK_OBJECT TOK_REF identifier '=' initializer ';'",
        "dynamicReferenceDeclaration : qualifierExpr TOK_OBJECT TOK_REF identifier subscript '=' initializer ';'",
        "methodDeclaration : dataType identifier '(' parameterList ')' ';'",
        "methodDeclaration : qualifierExpr dataType identifier '(' parameterList ')' ';'",
        "methodDeclaration : dataType identifier '(' ')' ';'",
        "methodDeclaration : qualifierExpr dataType identifier '(' ')' ';'",
        "parameterList : parameter",
        "parameterList : parameterList ',' parameter",
        "parameter : dataType identifier",
        "parameter : classNameIdentifier TOK_REF identifier",
        "parameter : qualifierExpr dataType identifier",
        "parameter : qualifierExpr classNameIdentifier TOK_REF identifier",
        "parameter : dataType identifier subscript",
        "parameter : classNameIdentifier TOK_REF identifier subscript",
        "parameter : qualifierExpr dataType identifier subscript",
        "parameter : qualifierExpr classNameIdentifier TOK_REF identifier subscript",
        "subscript : '[' TOK_INTEGER_VALUE ']'",
        "subscript : '[' ']'",
        "initializer : scalarInitializer",
        "initializer : arrayInitializer",
        "arrayInitializer : '{' arrayInitializerList '}'",
        "arrayInitializer : '{' '}'",
        "arrayInitializerList : scalarInitializer",
        "arrayInitializerList : arrayInitializerList ',' scalarInitializer",
        "scalarInitializer : constantValue",
        "scalarInitializer : TOK_ALIAS_IDENTIFIER",
        "scalarInitializer : TOK_INSTANCE TOK_OF classNameIdentifier '{' valueInitializerList '}'",
        "nonAggregateInitializer : constantValue",
        "nonAggregateInitializer : nonAggregateArrayInitializer",
        "nonAggregateArrayInitializer : '{' nonAggregateArrayInitializerList '}'",
        "nonAggregateArrayInitializer : '{' '}'",
        "nonAggregateArrayInitializerList : constantValue",
        "nonAggregateArrayInitializerList : nonAggregateArrayInitializerList ',' constantValue",
        "constantValue : TOK_INTEGER_VALUE",
        "constantValue : TOK_REAL_VALUE",
        "constantValue : TOK_CHAR_VALUE",
        "constantValue : stringValue",
        "constantValue : TOK_BOOLEAN_VALUE",
        "constantValue : TOK_NULL",
        "stringValue : TOK_STRING_VALUE",
        "stringValue : stringValue TOK_STRING_VALUE",
        "qualifierDeclaration : TOK_QUALIFIER identifier qualifierType scopeExpr ';'",
        "qualifierDeclaration : TOK_QUALIFIER identifier qualifierType scopeExpr flavorExpr ';'",
        "qualifierType : ':' dataType",
        "qualifierType : ':' dataType '=' nonAggregateInitializer",
        "qualifierType : ':' dataType subscript",
        "qualifierType : ':' dataType subscript '=' nonAggregateInitializer",
        "scopeExpr : ',' TOK_SCOPE '(' scopeList ')'",
        "scopeList : scope",
        "scopeList : scopeList ',' scope",
        "scope : TOK_CLASS",
        "scope : TOK_ASSOCIATION",
        "scope : TOK_INDICATION",
        "scope : TOK_PROPERTY",
        "scope : TOK_REFERENCE",
        "scope : TOK_METHOD",
        "scope : TOK_PARAMETER",
        "scope : TOK_ANY",
        "flavorExpr : ',' TOK_FLAVOR '(' flavorList ')'",
        "instanceDeclaration : TOK_INSTANCE TOK_OF classNameIdentifier instanceBody",
        "instanceDeclaration : qualifierExpr TOK_INSTANCE TOK_OF classNameIdentifier instanceBody",
        "instanceDeclaration : TOK_INSTANCE TOK_OF identifier alias instanceBody",
        "instanceDeclaration : qualifierExpr TOK_INSTANCE TOK_OF classNameIdentifier alias instanceBody",
        "instanceBody : '{' valueInitializerList '}' ';'",
        "instanceBody : '{' '}' ';'",
        "alias : TOK_AS TOK_ALIAS_IDENTIFIER",
        "valueInitializerList : valueInitializer",
        "valueInitializerList : valueInitializerList valueInitializer",
        "valueInitializer : identifier ';'",
        "valueInitializer : qualifierExpr identifier ';'",
        "valueInitializer : identifier '=' initializer ';'",
        "valueInitializer : qualifierExpr identifier '=' initializer ';'",
        "identifier : classNameIdentifier",
        "identifier : TOK_OBJECT",
        "identifier : TOK_BOOLEAN",
        "identifier : TOK_DATETIME",
        "identifier : TOK_STRING",
        "classNameIdentifier : TOK_IDENT",
        "classNameIdentifier : TOK_PRAGMA",
        "classNameIdentifier : TOK_CLASS",
        "classNameIdentifier : TOK_OF",
        "classNameIdentifier : TOK_ANY",
        "classNameIdentifier : TOK_ASSOCIATION",
        "classNameIdentifier : TOK_INDICATION",
        "classNameIdentifier : TOK_REFERENCE",
        "classNameIdentifier : TOK_PROPERTY",
        "classNameIdentifier : TOK_QUALIFIER",
        "classNameIdentifier : TOK_TOSUBCLASS",
        "classNameIdentifier : TOK_TOINSTANCE",
        "classNameIdentifier : TOK_TRANSLATABLE",
        "classNameIdentifier : TOK_FLAVOR",
        "dataType : TOK_BOOLEAN",
        "dataType : TOK_SINT8",
        "dataType : TOK_UINT8",
        "dataType : TOK_SINT16",
        "dataType : TOK_UINT16",
        "dataType : TOK_SINT32",
        "dataType : TOK_UINT32",
        "dataType : TOK_SINT64",
        "dataType : TOK_UINT64",
        "dataType : TOK_REAL32",
        "dataType : TOK_REAL64",
        "dataType : TOK_CHAR16",
        "dataType : TOK_DATETIME",
        "dataType : TOK_STRING",
};
#endif /* YYDEBUG */
# line  1 "/usr/ccs/bin/yaccpar"
/*
 * Copyright (c) 1993 by Sun Microsystems, Inc.
 */

/*
** Skeleton parser driver for yacc output
*/

/*
** yacc user known macros and defines
*/
#define YYERROR         goto yyerrlab
#define YYACCEPT        return(0)
#define YYABORT         return(1)
#define YYBACKUP( newtoken, newvalue )\
{\
        if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
        {\
                yyerror( "syntax error - cannot backup" );\
                goto yyerrlab;\
        }\
        yychar = newtoken;\
        yystate = *yyps;\
        yylval = newvalue;\
        goto yynewstate;\
}
#define YYRECOVERING()  (!!yyerrflag)
#define YYNEW(type)     PAL_Malloc(sizeof(type) * yynewmax)
#define YYCOPY(to, from, type) \
        (type *) memcpy(to, (char *) from, yymaxdepth * sizeof (type))
#define YYENLARGE( from, type) \
        (type *) PAL_Realloc((char *) from, yynewmax * sizeof(type))
#ifndef YYDEBUG
#       define YYDEBUG  1       /* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;                    /* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG          (-10000000)

/*
** global variables used by the parser
*/
YYSTYPE *yypv;                  /* top of value stack */
int *yyps;                      /* top of state stack */

int yystate;                    /* current state */
int yytmp;                      /* extra var (lasts between blocks) */

int yynerrs;                    /* number of errors */
int yyerrflag;                  /* error recovery flag */
int yychar;                     /* current input token number */



#ifdef YYNMBCHARS
#define YYLEX()         yycvtok(yylex())
/*
** yycvtok - return a token if i is a wchar_t value that exceeds 255.
**      If i<255, i itself is the token.  If i>255 but the neither 
**      of the 30th or 31st bit is on, i is already a token.
*/
#if defined(__STDC__) || defined(__cplusplus)
int yycvtok(int i)
#else
int yycvtok(i) int i;
#endif
{
        int first = 0;
        int last = YYNMBCHARS - 1;
        int mid;
        wchar_t j;

        if(i&0x60000000){/*Must convert to a token. */
                if( yymbchars[last].character < i ){
                        return i;/*Giving up*/
                }
                while ((last>=first)&&(first>=0)) {/*Binary search loop*/
                        mid = (first+last)/2;
                        j = yymbchars[mid].character;
                        if( j==i ){/*Found*/ 
                                return yymbchars[mid].tvalue;
                        }else if( j<i ){
                                first = mid + 1;
                        }else{
                                last = mid -1;
                        }
                }
                /*No entry in the table.*/
                return i;/* Giving up.*/
        }else{/* i is already a token. */
                return i;
        }
}
#else/*!YYNMBCHARS*/
#define YYLEX()         yylex()
#endif/*!YYNMBCHARS*/

/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
#if defined(__STDC__) || defined(__cplusplus)
int yyparse(void)
#else
int yyparse()
#endif
{
        register YYSTYPE *yypvt = 0;    /* top of value stack for $vars */

#if defined(__cplusplus) || defined(lint)
/*
        workarounds to please C++ and lint - goto's inside
        switch should never be executed
*/
        static int __yaccpar_lint_workaround__ = 0;
        switch (__yaccpar_lint_workaround__)
        {
                case 1: goto yyerrlab;
                case 2: goto yynewstate;
        }
#endif

        /*
        ** Initialize externals - yyparse may be called more than once
        */
        yypv = &yyv[-1];
        yyps = &yys[-1];
        yystate = 0;
        yytmp = 0;
        yynerrs = 0;
        yyerrflag = 0;
        yychar = -1;

#if YYMAXDEPTH <= 0
        if (yymaxdepth <= 0)
        {
                if ((yymaxdepth = YYEXPAND(0)) <= 0)
                {
                        yyerror("yacc initialization error");
                        YYABORT;
                }
        }
#endif

        {
                register YYSTYPE *yy_pv;        /* top of value stack */
                register int *yy_ps;            /* top of state stack */
                register int yy_state;          /* current state */
                register int  yy_n;             /* internal state number info */
        goto yystack;   /* moved from 6 lines above to here to please C++ */

                /*
                ** get globals into registers.
                ** branch to here only if YYBACKUP was called.
                */
        yynewstate:
                yy_pv = yypv;
                yy_ps = yyps;
                yy_state = yystate;
                goto yy_newstate;

                /*
                ** get globals into registers.
                ** either we just started, or we just finished a reduction
                */
        yystack:
                yy_pv = yypv;
                yy_ps = yyps;
                yy_state = yystate;

                /*
                ** top of for (;;) loop while no reductions done
                */
        yy_stack:
                /*
                ** put a state and value onto the stacks
                */
#if YYDEBUG
                /*
                ** if debugging, look up token value in list of value vs.
                ** name pairs.  0 and negative (-1) are special values.
                ** Note: linear search is used since time is not a real
                ** consideration while debugging.
                */
                if ( yydebug )
                {
                        register int yy_i;

                        printf( "State %d, token ", yy_state );
                        if ( yychar == 0 )
                                printf( "end-of-file\n" );
                        else if ( yychar < 0 )
                                printf( "-none-\n" );
                        else
                        {
                                for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
                                        yy_i++ )
                                {
                                        if ( yytoks[yy_i].t_val == yychar )
                                                break;
                                }
                                printf( "%s\n", yytoks[yy_i].t_name );
                        }
                }
#endif /* YYDEBUG */
                if ( ++yy_ps >= &yys[ yymaxdepth ] )    /* room on stack? */
                {
                        /*
                        ** reallocate and recover.  Note that pointers
                        ** have to be reset, or bad things will happen
                        */
                        long yyps_index = (yy_ps - yys);
                        long yypv_index = (yy_pv - yyv);
                        long yypvt_index = (yypvt - yyv);
                        int yynewmax;
#ifdef YYEXPAND
                        yynewmax = YYEXPAND(yymaxdepth);
#else
                        yynewmax = 2 * yymaxdepth;      /* double table size */
                        if (yymaxdepth == YYMAXDEPTH)   /* first time growth */
                        {
                                char *newyys = (char *)YYNEW(int);
                                char *newyyv = (char *)YYNEW(YYSTYPE);
                                if (newyys != 0 && newyyv != 0)
                                {
                                        yys = YYCOPY(newyys, yys, int);
                                        yyv = YYCOPY(newyyv, yyv, YYSTYPE);
                                }
                                else
                                        yynewmax = 0;   /* failed */
                        }
                        else                            /* not first time */
                        {
                                yys = YYENLARGE(yys, int);
                                yyv = YYENLARGE(yyv, YYSTYPE);
                                if (yys == 0 || yyv == 0)
                                        yynewmax = 0;   /* failed */
                        }
#endif
                        if (yynewmax <= yymaxdepth)     /* tables not expanded */
                        {
                                yyerror( "yacc stack overflow" );
                                YYABORT;
                        }
                        yymaxdepth = yynewmax;

                        yy_ps = yys + yyps_index;
                        yy_pv = yyv + yypv_index;
                        yypvt = yyv + yypvt_index;
                }
                *yy_ps = yy_state;
                *++yy_pv = yyval;

                /*
                ** we have a new state - find out what to do
                */
        yy_newstate:
                if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
                        goto yydefault;         /* simple state */
#if YYDEBUG
                /*
                ** if debugging, need to mark whether new token grabbed
                */
                yytmp = yychar < 0;
#endif
                if ( ( yychar < 0 ) && ( ( yychar = YYLEX() ) < 0 ) )
                        yychar = 0;             /* reached EOF */
#if YYDEBUG
                if ( yydebug && yytmp )
                {
                        register int yy_i;

                        printf( "Received token " );
                        if ( yychar == 0 )
                                printf( "end-of-file\n" );
                        else if ( yychar < 0 )
                                printf( "-none-\n" );
                        else
                        {
                                for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
                                        yy_i++ )
                                {
                                        if ( yytoks[yy_i].t_val == yychar )
                                                break;
                                }
                                printf( "%s\n", yytoks[yy_i].t_name );
                        }
                }
#endif /* YYDEBUG */
                if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
                        goto yydefault;
                if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )  /*valid shift*/
                {
                        yychar = -1;
                        yyval = yylval;
                        yy_state = yy_n;
                        if ( yyerrflag > 0 )
                                yyerrflag--;
                        goto yy_stack;
                }

        yydefault:
                if ( ( yy_n = yydef[ yy_state ] ) == -2 )
                {
#if YYDEBUG
                        yytmp = yychar < 0;
#endif
                        if ( ( yychar < 0 ) && ( ( yychar = YYLEX() ) < 0 ) )
                                yychar = 0;             /* reached EOF */
#if YYDEBUG
                        if ( yydebug && yytmp )
                        {
                                register int yy_i;

                                printf( "Received token " );
                                if ( yychar == 0 )
                                        printf( "end-of-file\n" );
                                else if ( yychar < 0 )
                                        printf( "-none-\n" );
                                else
                                {
                                        for ( yy_i = 0;
                                                yytoks[yy_i].t_val >= 0;
                                                yy_i++ )
                                        {
                                                if ( yytoks[yy_i].t_val
                                                        == yychar )
                                                {
                                                        break;
                                                }
                                        }
                                        printf( "%s\n", yytoks[yy_i].t_name );
                                }
                        }
#endif /* YYDEBUG */
                        /*
                        ** look through exception table
                        */
                        {
                                register YYCONST int *yyxi = yyexca;

                                while ( ( *yyxi != -1 ) ||
                                        ( yyxi[1] != yy_state ) )
                                {
                                        yyxi += 2;
                                }
                                while ( ( *(yyxi += 2) >= 0 ) &&
                                        ( *yyxi != yychar ) )
                                        ;
                                if ( ( yy_n = yyxi[1] ) < 0 )
                                        YYACCEPT;
                        }
                }

                /*
                ** check for syntax error
                */
                if ( yy_n == 0 )        /* have an error */
                {
                        /* no worry about speed here! */
                        switch ( yyerrflag )
                        {
                        case 0:         /* new error */
                                yyerror( "syntax error" );
                                goto skip_init;
                        yyerrlab:
                                /*
                                ** get globals into registers.
                                ** we have a user generated syntax type error
                                */
                                yy_pv = yypv;
                                yy_ps = yyps;
                                yy_state = yystate;
                        skip_init:
                                yynerrs++;
                                /* FALLTHRU */
                        case 1:
                        case 2:         /* incompletely recovered error */
                                        /* try again... */
                                yyerrflag = 3;
                                /*
                                ** find state where "error" is a legal
                                ** shift action
                                */
                                while ( yy_ps >= yys )
                                {
                                        yy_n = yypact[ *yy_ps ] + YYERRCODE;
                                        if ( yy_n >= 0 && yy_n < YYLAST &&
                                                yychk[yyact[yy_n]] == YYERRCODE)                                        {
                                                /*
                                                ** simulate shift of "error"
                                                */
                                                yy_state = yyact[ yy_n ];
                                                goto yy_stack;
                                        }
                                        /*
                                        ** current state has no shift on
                                        ** "error", pop stack
                                        */
#if YYDEBUG
#       define _POP_ "Error recovery pops state %d, uncovers state %d\n"
                                        if ( yydebug )
                                                printf( _POP_, *yy_ps,
                                                        yy_ps[-1] );
#       undef _POP_
#endif
                                        yy_ps--;
                                        yy_pv--;
                                }
                                /*
                                ** there is no state on stack with "error" as
                                ** a valid shift.  give up.
                                */
                                YYABORT;
                        case 3:         /* no shift yet; eat a token */
#if YYDEBUG
                                /*
                                ** if debugging, look up token in list of
                                ** pairs.  0 and negative shouldn't occur,
                                ** but since timing doesn't matter when
                                ** debugging, it doesn't hurt to leave the
                                ** tests here.
                                */
                                if ( yydebug )
                                {
                                        register int yy_i;

                                        printf( "Error recovery discards " );
                                        if ( yychar == 0 )
                                                printf( "token end-of-file\n" );
                                        else if ( yychar < 0 )
                                                printf( "token -none-\n" );
                                        else
                                        {
                                                for ( yy_i = 0;
                                                        yytoks[yy_i].t_val >= 0;
                                                        yy_i++ )
                                                {
                                                        if ( yytoks[yy_i].t_val
                                                                == yychar )
                                                        {
                                                                break;
                                                        }
                                                }
                                                printf( "token %s\n",
                                                        yytoks[yy_i].t_name );
                                        }
                                }
#endif /* YYDEBUG */
                                if ( yychar == 0 )      /* reached EOF. quit */
                                        YYABORT;
                                yychar = -1;
                                goto yy_newstate;
                        }
                }/* end if ( yy_n == 0 ) */
                /*
                ** reduction by production yy_n
                ** put stack tops, etc. so things right after switch
                */
#if YYDEBUG
                /*
                ** if debugging, print the string that is the user's
                ** specification of the reduction which is just about
                ** to be done.
                */
                if ( yydebug )
                        printf( "Reduce by (%d) \"%s\"\n",
                                yy_n, yyreds[ yy_n ] );
#endif
                yytmp = yy_n;                   /* value to switch over */
                yypvt = yy_pv;                  /* $vars top of value stack */
                /*
                ** Look in goto table for next state
                ** Sorry about using yy_state here as temporary
                ** register variable, but why not, if it works...
                ** If yyr2[ yy_n ] doesn't have the low order bit
                ** set, then there is no action to be done for
                ** this reduction.  So, no saving & unsaving of
                ** registers done.  The only difference between the
                ** code just after the if and the body of the if is
                ** the goto yy_stack in the body.  This way the test
                ** can be made before the choice of what to do is needed.
                */
                {
                        /* length of production doubled with extra bit */
                        register int yy_len = yyr2[ yy_n ];

                        if ( !( yy_len & 01 ) )
                        {
                                yy_len >>= 1;
                                yyval = ( yy_pv -= yy_len )[1]; /* $$ = $1 */
                                yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
                                        *( yy_ps -= yy_len ) + 1;
                                if ( yy_state >= YYLAST ||
                                        yychk[ yy_state =
                                        yyact[ yy_state ] ] != -yy_n )
                                {
                                        yy_state = yyact[ yypgo[ yy_n ] ];
                                }
                                goto yy_stack;
                        }
                        yy_len >>= 1;
                        yyval = ( yy_pv -= yy_len )[1]; /* $$ = $1 */
                        yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
                                *( yy_ps -= yy_len ) + 1;
                        if ( yy_state >= YYLAST ||
                                yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
                        {
                                yy_state = yyact[ yypgo[ yy_n ] ];
                        }
                }
                                        /* save until reenter driver code */
                yystate = yy_state;
                yyps = yy_ps;
                yypv = yy_pv;
        }
        /*
        ** code supplied by user is placed in this switch
        */
        switch( yytmp )
        {
                
case 1:
# line 167 "mof.y"
{
    } break;
case 2:
# line 170 "mof.y"
{ 
    } break;
case 3:
# line 173 "mof.y"
{
        YYABORT;
    } break;
case 4:
# line 179 "mof.y"
{
    } break;
case 5:
# line 182 "mof.y"
{
        /* [TODO: validate the class here] */
        yypvt[-0].classDeclaration->flags = MI_FLAG_CLASS;
        yypvt[-0].classDeclaration->flags |= GetQualFlags(yypvt[-0].classDeclaration->qualifiers, yypvt[-0].classDeclaration->numQualifiers);
        if (FinalizeClass(yypvt[-0].classDeclaration) != 0)
            YYABORT;
            
        AddClassDecl(yypvt[-0].classDeclaration);

        if (state.classDeclCallback)
            (*state.classDeclCallback)(yypvt[-0].classDeclaration, state.classDeclCallbackData);
    } break;
case 6:
# line 195 "mof.y"
{
        AddQualifierDeclaration(yypvt[-0].qualifierDeclaration);

        if (state.qualifierDeclCallback)
            (*state.qualifierDeclCallback)(yypvt[-0].qualifierDeclaration, state.qualifierDeclCallbackData);
    } break;
case 7:
# line 202 "mof.y"
{
        if (FinalizeInstance(yypvt[-0].instanceDeclaration) != 0)
            YYABORT;

        AddInstanceDecl(yypvt[-0].instanceDeclaration);

        if (state.instanceDeclCallback)
            (*state.instanceDeclCallback)(yypvt[-0].instanceDeclaration, state.instanceDeclCallbackData);
    } break;
case 8:
# line 214 "mof.y"
{
        if (strcmp(yypvt[-3].string, "include") == 0)
        {
            if (openIncludeFile(yypvt[-1].string) != 0)
                YYABORT;
        }
        else if (strcmp(yypvt[-3].string, "instancelocale") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)(yypvt[-3].string, yypvt[-1].string, state.pragmaCallbackData);
        }
        else if (strcmp(yypvt[-3].string, "locale") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)(yypvt[-3].string, yypvt[-1].string, state.pragmaCallbackData);
        }
        else if (strcmp(yypvt[-3].string, "namespace") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)(yypvt[-3].string, yypvt[-1].string, state.pragmaCallbackData);
        }
        else if (state.extensionsEnabled == MI_TRUE && strcmp(yypvt[-3].string, "deleteclass") == 0)
        {
            yywarnf(ID_UNKNOWN_PRAGMA, 
                "warning: nonstandard pragma: %s(%s)", yypvt[-5].string, yypvt[-3].string);

            if (state.pragmaCallback)
                (*state.pragmaCallback)(yypvt[-3].string, yypvt[-1].string, state.pragmaCallbackData);
        }
        else
        {
            yywarnf(ID_UNKNOWN_PRAGMA, 
                "warning: unknown pragma: %s(%s)", yypvt[-3].string, yypvt[-1].string);

            if (state.pragmaCallback)
                (*state.pragmaCallback)(yypvt[-3].string, yypvt[-1].string, state.pragmaCallbackData);
        }
    } break;
case 9:
# line 250 "mof.y"
{
        if (state.extensionsEnabled == MI_TRUE && strcmp(yypvt[-5].string, "deleteclass") == 0)
        {
            yywarnf(ID_UNKNOWN_PRAGMA, 
                "warning: nonstandard pragma: %s(%s)", yypvt[-5].string, yypvt[-3].string);

            if (state.pragmaCallback)
                (*state.pragmaCallback)(yypvt[-5].string, yypvt[-3].string, state.pragmaCallbackData);
        }
        else
        {
            yywarnf(ID_UNKNOWN_PRAGMA, 
                "warning: unknown pragma: %s(%s)", yypvt[-5].string, yypvt[-3].string);

            if (state.pragmaCallback)
                (*state.pragmaCallback)(yypvt[-5].string, yypvt[-3].string, state.pragmaCallbackData);
        }
    } break;
case 10:
# line 268 "mof.y"
{
        /* Check whether class already exists */
        if (FindClassDecl(yypvt[-1].string))
        {
            if (state.extensionsEnabled == MI_FALSE)
            {
                yyerrorf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yypvt[-1].string);
                YYABORT;
            }
            else
                yywarnf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yypvt[-1].string);
        }

        yyval.classDeclaration = CALLOC_T(MI_ClassDecl, 1);
        yyval.classDeclaration->flags = MI_FLAG_CLASS;
        yyval.classDeclaration->name = yypvt[-1].string;
        yyval.classDeclaration->properties = yypvt[-0].featureList.propertySet.data;
        yyval.classDeclaration->numProperties = yypvt[-0].featureList.propertySet.size;
        yyval.classDeclaration->methods = yypvt[-0].featureList.methodList.data;
        yyval.classDeclaration->numMethods = yypvt[-0].featureList.methodList.size;
    } break;
case 11:
# line 292 "mof.y"
{
        const MI_ClassDecl* scd;

        /* Check whether class already exists */
        if (FindClassDecl(yypvt[-3].string))
        {
            if (state.extensionsEnabled == MI_FALSE)
            {
                yyerrorf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yypvt[-3].string);
                YYABORT;
            }
            else
                yywarnf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yypvt[-3].string);
        }
 
        /* Check whether superclass exists */
        scd = FindClassDecl(yypvt[-1].string);

        if (!scd)
        {
            yyerrorf(ID_UNDEFINED_SUPERCLASS, 
                "super class of \"%s\" is undefined: \"%s\"", yypvt[-3].string, yypvt[-1].string);
            YYABORT;
        }

        yyval.classDeclaration = CALLOC_T(MI_ClassDecl, 1);
        yyval.classDeclaration->flags = MI_FLAG_CLASS;
        yyval.classDeclaration->name = yypvt[-3].string;
        yyval.classDeclaration->superClass = yypvt[-1].string;
        yyval.classDeclaration->superClassDecl = (MI_ClassDecl*)scd;
        yyval.classDeclaration->properties = yypvt[-0].featureList.propertySet.data;
        yyval.classDeclaration->numProperties = yypvt[-0].featureList.propertySet.size;
        yyval.classDeclaration->methods = yypvt[-0].featureList.methodList.data;
        yyval.classDeclaration->numMethods = yypvt[-0].featureList.methodList.size;
    } break;
case 12:
# line 330 "mof.y"
{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_CLASS, &yypvt[-3].qualifierList) != 0)
            YYABORT;

        /* Check whether class already exists */
        if (FindClassDecl(yypvt[-1].string))
        {
            if (state.extensionsEnabled == MI_FALSE)
            {
                yyerrorf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yypvt[-1].string);
                YYABORT;
            }
            else
                yywarnf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yypvt[-1].string);
        }

        yyval.classDeclaration = CALLOC_T(MI_ClassDecl, 1);
        yyval.classDeclaration->flags = MI_FLAG_CLASS;
        yyval.classDeclaration->name = yypvt[-1].string;
        yyval.classDeclaration->properties = yypvt[-0].featureList.propertySet.data;
        yyval.classDeclaration->numProperties = yypvt[-0].featureList.propertySet.size;
        yyval.classDeclaration->methods = yypvt[-0].featureList.methodList.data;
        yyval.classDeclaration->numMethods = yypvt[-0].featureList.methodList.size;
        yyval.classDeclaration->qualifiers = yypvt[-3].qualifierList.data;
        yyval.classDeclaration->numQualifiers = yypvt[-3].qualifierList.size;
    } break;
case 13:
# line 360 "mof.y"
{
        const MI_ClassDecl* scd;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_CLASS, &yypvt[-5].qualifierList) != 0)
            YYABORT;

        /* Check whether class already exists */
        if (FindClassDecl(yypvt[-3].string))
        {
            if (state.extensionsEnabled == MI_FALSE)
            {
                yyerrorf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yypvt[-3].string);
                YYABORT;
            }
            else
                yywarnf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yypvt[-3].string);
        }

        /* Check whether superclass exists */
        scd = FindClassDecl(yypvt[-1].string);

        if (!scd)
        {
            yyerrorf(ID_UNDEFINED_SUPERCLASS, 
                "super class of \"%s\" is undefined: \"%s\"", yypvt[-3].string, yypvt[-1].string);
            YYABORT;
        }

        yyval.classDeclaration = CALLOC_T(MI_ClassDecl, 1);
        yyval.classDeclaration->flags = MI_FLAG_CLASS;
        yyval.classDeclaration->name = yypvt[-3].string;
        yyval.classDeclaration->superClass = scd->name;
        yyval.classDeclaration->superClassDecl = (MI_ClassDecl*)scd;
        yyval.classDeclaration->properties = yypvt[-0].featureList.propertySet.data;
        yyval.classDeclaration->numProperties = yypvt[-0].featureList.propertySet.size;
        yyval.classDeclaration->methods = yypvt[-0].featureList.methodList.data;
        yyval.classDeclaration->numMethods = yypvt[-0].featureList.methodList.size;
        yyval.classDeclaration->qualifiers = yypvt[-5].qualifierList.data;
        yyval.classDeclaration->numQualifiers = yypvt[-5].qualifierList.size;
    } break;
case 14:
# line 406 "mof.y"
{
        yyval.featureList = yypvt[-2].featureList;
    } break;
case 15:
# line 410 "mof.y"
{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
    } break;
case 16:
# line 419 "mof.y"
{
        if (CheckPropertyValueConstraints(yypvt[-0].property) != 0)
        {
            YYABORT;
        }
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yypvt[-0].property->flags = MI_FLAG_PROPERTY;
        yypvt[-0].property->flags |= GetQualFlags(yypvt[-0].property->qualifiers, yypvt[-0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yypvt[-0].property);
    } break;
case 17:
# line 433 "mof.y"
{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yypvt[-0].methodDecl->flags = MI_FLAG_METHOD;
        yypvt[-0].methodDecl->flags |= GetQualFlags(yypvt[-0].methodDecl->qualifiers, yypvt[-0].methodDecl->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.methodList, yypvt[-0].methodDecl);
    } break;
case 18:
# line 443 "mof.y"
{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yypvt[-0].property->flags = MI_FLAG_PROPERTY;
        yypvt[-0].property->flags |= GetQualFlags(yypvt[-0].property->qualifiers, yypvt[-0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yypvt[-0].property);
    } break;
case 19:
# line 453 "mof.y"
{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yypvt[-0].property->flags = MI_FLAG_PROPERTY;
        yypvt[-0].property->flags |= GetQualFlags(yypvt[-0].property->qualifiers, yypvt[-0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yypvt[-0].property);
    } break;
case 20:
# line 463 "mof.y"
{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yypvt[-0].property->flags = MI_FLAG_PROPERTY;
        yypvt[-0].property->flags |= GetQualFlags(yypvt[-0].property->qualifiers, yypvt[-0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yypvt[-0].property);
    } break;
case 21:
# line 473 "mof.y"
{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yypvt[-0].property->flags = MI_FLAG_PROPERTY;
        yypvt[-0].property->flags |= GetQualFlags(yypvt[-0].property->qualifiers, yypvt[-0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yypvt[-0].property);
    } break;
case 22:
# line 483 "mof.y"
{
        if (CheckPropertyValueConstraints(yypvt[-0].property) != 0)
        {
            YYABORT;
        }

        if (FindProperty(&yypvt[-1].featureList.propertySet, yypvt[-0].property->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", yypvt[-0].property->name);
            YYABORT;
        }

        yypvt[-0].property->flags = MI_FLAG_PROPERTY;
        yypvt[-0].property->flags |= GetQualFlags(yypvt[-0].property->qualifiers, yypvt[-0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yypvt[-0].property);
    } break;
case 23:
# line 501 "mof.y"
{
        if (FindMethod(&yypvt[-1].featureList.methodList, yypvt[-0].methodDecl->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", yypvt[-0].methodDecl->name);
            YYABORT;
        }

        yypvt[-0].methodDecl->flags = MI_FLAG_METHOD;
        yypvt[-0].methodDecl->flags |= GetQualFlags(yypvt[-0].methodDecl->qualifiers, yypvt[-0].methodDecl->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.methodList, yypvt[-0].methodDecl);
    } break;
case 24:
# line 514 "mof.y"
{
        if (FindProperty(&yypvt[-1].featureList.propertySet, yypvt[-0].property->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", yypvt[-0].property->name);
            YYABORT;
        }

        yypvt[-0].property->flags = MI_FLAG_PROPERTY;
        yypvt[-0].property->flags |= GetQualFlags(yypvt[-0].property->qualifiers, yypvt[-0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yypvt[-0].property);
    } break;
case 25:
# line 527 "mof.y"
{
        if (FindProperty(&yypvt[-1].featureList.propertySet, yypvt[-0].property->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", yypvt[-0].property->name);
            YYABORT;
        }
        yypvt[-0].property->flags = MI_FLAG_PROPERTY;
        yypvt[-0].property->flags |= GetQualFlags(yypvt[-0].property->qualifiers, yypvt[-0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yypvt[-0].property);
    } break;
case 26:
# line 539 "mof.y"
{
        if (FindProperty(&yypvt[-1].featureList.propertySet, yypvt[-0].property->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", yypvt[-0].property->name);
            YYABORT;
        }

        yypvt[-0].property->flags = MI_FLAG_PROPERTY;
        yypvt[-0].property->flags |= GetQualFlags(yypvt[-0].property->qualifiers, yypvt[-0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yypvt[-0].property);
    } break;
case 27:
# line 552 "mof.y"
{
        if (FindProperty(&yypvt[-1].featureList.propertySet, yypvt[-0].property->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", yypvt[-0].property->name);
            YYABORT;
        }

        yypvt[-0].property->flags = MI_FLAG_PROPERTY;
        yypvt[-0].property->flags |= GetQualFlags(yypvt[-0].property->qualifiers, yypvt[-0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yypvt[-0].property);
    } break;
case 28:
# line 567 "mof.y"
{
        yyval.qualifierList = yypvt[-1].qualifierList;
    } break;
case 29:
# line 573 "mof.y"
{
        yyval.qualifierList.data = NULL;
        yyval.qualifierList.size = 0;
        PtrArray_Append((PtrArray*)&yyval.qualifierList, yypvt[-0].qualifier);
    } break;
case 30:
# line 579 "mof.y"
{
        if (FindQualifier(&yypvt[-2].qualifierList, yypvt[-0].qualifier->name))
        {
            yyerrorf(ID_DUPLICATE_QUALIFIER, 
                "duplicate qualifier: \"%s\"", yypvt[-0].qualifier->name);
            YYABORT;
        }

        PtrArray_Append((PtrArray*)&yyval.qualifierList, yypvt[-0].qualifier);
    } break;
case 31:
# line 592 "mof.y"
{
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;

        qd = FindQualifierDeclaration(yypvt[-0].string);

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", yypvt[-0].string);
            YYABORT;
        }

        if (qd->type != MI_BOOLEAN)
        {
            yyerrorf(ID_MISSING_QUALIFIER_INITIALIZER, 
                "qualifier is missing initializer: \"%s\"", yypvt[-0].string);
            YYABORT;
        }
        
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = qd->flavor;
        q->value = NewTrueValue();
        yyval.qualifier = q;
    } break;
case 32:
# line 620 "mof.y"
{
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;
        void* value;

        qd = FindQualifierDeclaration(yypvt[-1].string);

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", yypvt[-1].string);
            YYABORT;
        }

        if (InitializerToValue(&yypvt[-0].initializer, qd->type, &value) != 0)
        {
            yyerrorf(ID_INVALID_QUALIFIER_INITIALIZER, 
                "invalid initializer for qualifer: \"%s\"", yypvt[-1].string);
            YYABORT;
        }
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = qd->flavor;
        q->value = value;
        yyval.qualifier = q;
    } break;
case 33:
# line 648 "mof.y"
{
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;

        qd = FindQualifierDeclaration(yypvt[-2].string);

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", yypvt[-2].string);
            YYABORT;
        }

        if (qd->type != MI_BOOLEAN)
        {
            yyerrorf(ID_MISSING_QUALIFIER_INITIALIZER, 
                "qualifier is missing initializer: \"%s\"", yypvt[-2].string);
            YYABORT;
        }
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = PropagateFlavors(yypvt[-0].flags, qd->flavor);
        q->value = NewTrueValue();
        yyval.qualifier = q;
    } break;
case 34:
# line 675 "mof.y"
{
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;
        void* value;

        qd = FindQualifierDeclaration(yypvt[-3].string);

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", yypvt[-3].string);
            YYABORT;
        }

        if (InitializerToValue(&yypvt[-2].initializer, qd->type, &value) != 0)
        {
            yyerrorf(ID_INVALID_QUALIFIER_INITIALIZER, 
                "invalid initializer for qualifer: \"%s\"", yypvt[-3].string);
            YYABORT;
        }
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->value = value;
        q->flavor = PropagateFlavors(yypvt[-0].flags, qd->flavor);
        yyval.qualifier = q;
    } break;
case 35:
# line 705 "mof.y"
{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yypvt[-1].constantValue;
        yyval.initializer.size = 1;
    } break;
case 36:
# line 712 "mof.y"
{
        yyval.initializer = yypvt[-0].initializer;
    } break;
case 37:
# line 718 "mof.y"
{
        yyval.flags = yypvt[-0].flags;
    } break;
case 38:
# line 722 "mof.y"
{
        yyval.flags |= yypvt[-0].flags;
    } break;
case 39:
# line 728 "mof.y"
{
        yyval.flags = yypvt[-0].flags;
    } break;
case 40:
# line 732 "mof.y"
{
        yyval.flags |= yypvt[-0].flags;
    } break;
case 41:
# line 738 "mof.y"
{
        yyval.flags = MI_FLAG_ENABLEOVERRIDE;
    } break;
case 42:
# line 742 "mof.y"
{
        yyval.flags = MI_FLAG_DISABLEOVERRIDE;
    } break;
case 43:
# line 746 "mof.y"
{
        yyval.flags = MI_FLAG_RESTRICTED;
    } break;
case 44:
# line 750 "mof.y"
{
        yyval.flags = MI_FLAG_TOSUBCLASS;
    } break;
case 45:
# line 754 "mof.y"
{
        yyval.flags = MI_FLAG_TOINSTANCE;
        if (state.extensionsEnabled == MI_FALSE)
        {
            yyerrorf(ID_UNSUPPORTED, "Unsupported flavor: ToInstance");
            YYABORT;
        }
    } break;
case 46:
# line 763 "mof.y"
{
        yyval.flags = MI_FLAG_TRANSLATABLE;
    } break;
case 47:
# line 769 "mof.y"
{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yypvt[-1].string;
        yyval.property->type = yypvt[-2].type;
    } break;
case 48:
# line 775 "mof.y"
{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PROPERTY, &yypvt[-3].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yypvt[-1].string;
        yyval.property->type = yypvt[-2].type;
        yyval.property->qualifiers = yypvt[-3].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-3].qualifierList.size;
    } break;
case 49:
# line 787 "mof.y"
{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yypvt[-2].string;
        yyval.property->type = ARRAYOF(yypvt[-3].type);
        yyval.property->subscript = (MI_Uint32)yypvt[-1].integer;
    } break;
case 50:
# line 794 "mof.y"
{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PROPERTY, &yypvt[-4].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yypvt[-2].string;
        yyval.property->type = ARRAYOF(yypvt[-3].type);
        yyval.property->qualifiers = yypvt[-4].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-4].qualifierList.size;
        yyval.property->subscript = (MI_Uint32)yypvt[-1].integer;
    } break;
case 51:
# line 807 "mof.y"
{
        void* value;

        if (InitializerToValue(&yypvt[-1].initializer, yypvt[-4].type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yypvt[-3].string;
        yyval.property->type = yypvt[-4].type;
        yyval.property->value = value;
    } break;
case 52:
# line 822 "mof.y"
{
        void* value;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PROPERTY, &yypvt[-5].qualifierList) != 0)
            YYABORT;

        if (InitializerToValue(&yypvt[-1].initializer, yypvt[-4].type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yypvt[-3].string;
        yyval.property->type = yypvt[-4].type;
        yyval.property->qualifiers = yypvt[-5].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-5].qualifierList.size;
        yyval.property->value = value;
    } break;
case 53:
# line 843 "mof.y"
{
        void* value;

        if (InitializerToValue(&yypvt[-1].initializer, ARRAYOF(yypvt[-5].type), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yypvt[-4].string;
        yyval.property->type = ARRAYOF(yypvt[-5].type);
        yyval.property->subscript = (MI_Uint32)yypvt[-3].integer;
        yyval.property->value = value;
    } break;
case 54:
# line 859 "mof.y"
{
        void* value;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PROPERTY, &yypvt[-6].qualifierList) != 0)
            YYABORT;

        if (InitializerToValue(&yypvt[-1].initializer, ARRAYOF(yypvt[-5].type), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yypvt[-4].string;
        yyval.property->type = ARRAYOF(yypvt[-5].type);
        yyval.property->qualifiers = yypvt[-6].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-6].qualifierList.size;
        yyval.property->subscript = (MI_Uint32)yypvt[-3].integer;
        yyval.property->value = value;
    } break;
case 55:
# line 883 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-2].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-2].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yypvt[-1].string;
        yyval.property->className = cd->name;
    } break;
case 56:
# line 900 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-2].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-2].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yypvt[-3].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yypvt[-1].string;
        yyval.property->className = cd->name;
        yyval.property->qualifiers = yypvt[-3].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-3].qualifierList.size;
    } break;
case 57:
# line 923 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-3].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-3].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yypvt[-2].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yypvt[-1].integer;
    } break;
case 58:
# line 941 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-3].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-3].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yypvt[-4].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yypvt[-2].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yypvt[-1].integer;
        yyval.property->qualifiers = yypvt[-4].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-4].qualifierList.size;
    } break;
case 59:
# line 965 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-4].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-4].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yypvt[-3].string;
        yyval.property->className = cd->name;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    } break;
case 60:
# line 984 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-4].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-4].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yypvt[-5].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yypvt[-3].string;
        yyval.property->className = cd->name;
        yyval.property->qualifiers = yypvt[-5].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-5].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    } break;
case 61:
# line 1009 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-5].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-5].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yypvt[-4].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yypvt[-3].integer;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    } break;
case 62:
# line 1029 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-5].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-5].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yypvt[-6].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yypvt[-4].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yypvt[-3].integer;
        yyval.property->qualifiers = yypvt[-6].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-6].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    } break;
case 63:
# line 1057 "mof.y"
{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yypvt[-1].string;
        yyval.property->className = "?";
    } break;
case 64:
# line 1066 "mof.y"
{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yypvt[-1].string;
        yyval.property->className = "?";
        yyval.property->qualifiers = yypvt[-3].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-3].qualifierList.size;
    } break;
case 65:
# line 1077 "mof.y"
{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yypvt[-2].string;
        yyval.property->className = "?";
        yyval.property->subscript = 0;
    } break;
case 66:
# line 1087 "mof.y"
{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yypvt[-2].string;
        yyval.property->className = "?";
        yyval.property->subscript = 0;
        yyval.property->qualifiers = yypvt[-4].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-4].qualifierList.size;
    } break;
case 67:
# line 1099 "mof.y"
{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yypvt[-3].string;
        yyval.property->className = "?";
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    } break;
case 68:
# line 1110 "mof.y"
{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yypvt[-3].string;
        yyval.property->className = "?";
        yyval.property->qualifiers = yypvt[-5].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-5].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    } break;
case 69:
# line 1123 "mof.y"
{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yypvt[-4].string;
        yyval.property->className = "?";
        yyval.property->subscript = (MI_Uint32)yypvt[-3].integer;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    } break;
case 70:
# line 1135 "mof.y"
{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yypvt[-4].string;
        yyval.property->className = "?";
        yyval.property->subscript = (MI_Uint32)yypvt[-3].integer;
        yyval.property->qualifiers = yypvt[-6].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-6].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    } break;
case 71:
# line 1151 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-3].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-3].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yypvt[-1].string;
        yyval.property->className = cd->name;
    } break;
case 72:
# line 1168 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-3].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-3].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yypvt[-4].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yypvt[-1].string;
        yyval.property->className = cd->name;
        yyval.property->qualifiers = yypvt[-4].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-4].qualifierList.size;
    } break;
case 73:
# line 1191 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-5].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-5].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yypvt[-3].string;
        yyval.property->className = cd->name;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* [TODO: use initializer */
    } break;
case 74:
# line 1210 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-5].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-5].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yypvt[-6].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yypvt[-3].string;
        yyval.property->className = cd->name;
        yyval.property->qualifiers = yypvt[-6].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-6].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* [TODO: use initializer */
    } break;
case 75:
# line 1235 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-4].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-4].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yypvt[-2].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yypvt[-1].integer;
    } break;
case 76:
# line 1253 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-4].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-4].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yypvt[-5].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yypvt[-2].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yypvt[-1].integer;
        yyval.property->qualifiers = yypvt[-5].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-5].qualifierList.size;
    } break;
case 77:
# line 1277 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-6].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-6].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yypvt[-4].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yypvt[-3].integer;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    } break;
case 78:
# line 1297 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-6].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-6].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yypvt[-7].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yypvt[-4].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yypvt[-3].integer;
        yyval.property->qualifiers = yypvt[-7].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-7].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    } break;
case 79:
# line 1325 "mof.y"
{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yypvt[-1].string;
        yyval.property->className = "?";
    } break;
case 80:
# line 1332 "mof.y"
{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yypvt[-4].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yypvt[-1].string;
        yyval.property->className = "?";
        yyval.property->qualifiers = yypvt[-4].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-4].qualifierList.size;
    } break;
case 81:
# line 1345 "mof.y"
{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yypvt[-2].string;
        yyval.property->className = "?";
        yyval.property->subscript = (MI_Uint32)yypvt[-1].integer;
    } break;
case 82:
# line 1353 "mof.y"
{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yypvt[-5].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yypvt[-2].string;
        yyval.property->className = "?";
        yyval.property->subscript = (MI_Uint32)yypvt[-1].integer;
        yyval.property->qualifiers = yypvt[-5].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-5].qualifierList.size;
    } break;
case 83:
# line 1367 "mof.y"
{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yypvt[-3].string;
        yyval.property->className = "?";
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    } break;
case 84:
# line 1376 "mof.y"
{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yypvt[-4].string;
        yyval.property->className = "?";
        yyval.property->subscript = (MI_Uint32)yypvt[-3].integer;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    } break;
case 85:
# line 1386 "mof.y"
{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yypvt[-6].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yypvt[-3].string;
        yyval.property->className = "?";
        yyval.property->qualifiers = yypvt[-6].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-6].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
        } break;
case 86:
# line 1401 "mof.y"
{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yypvt[-7].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yypvt[-4].string;
        yyval.property->className = "?";
        yyval.property->subscript = (MI_Uint32)yypvt[-3].integer;
        yyval.property->qualifiers = yypvt[-7].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-7].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
        } break;
case 87:
# line 1419 "mof.y"
{
        yyval.methodDecl = CALLOC_T(MI_MethodDecl, 1);
        yyval.methodDecl->name = yypvt[-4].string;
        yyval.methodDecl->parameters = yypvt[-2].parameterList.data;
        yyval.methodDecl->numParameters = yypvt[-2].parameterList.size;
        yyval.methodDecl->returnType = yypvt[-5].type;
    } break;
case 88:
# line 1427 "mof.y"
{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_METHOD, &yypvt[-6].qualifierList) != 0)
            YYABORT;

        yyval.methodDecl = CALLOC_T(MI_MethodDecl, 1);
        yyval.methodDecl->name = yypvt[-4].string;
        yyval.methodDecl->parameters = yypvt[-2].parameterList.data;
        yyval.methodDecl->numParameters = yypvt[-2].parameterList.size;
        yyval.methodDecl->qualifiers = yypvt[-6].qualifierList.data;
        yyval.methodDecl->numQualifiers = yypvt[-6].qualifierList.size;
        yyval.methodDecl->returnType = yypvt[-5].type;
    } break;
case 89:
# line 1441 "mof.y"
{
        MOF_ParameterList parameterList = PTRARRAY_INITIALIZER;

        yyval.methodDecl = CALLOC_T(MI_MethodDecl, 1);
        yyval.methodDecl->name = yypvt[-3].string;
        yyval.methodDecl->parameters = parameterList.data;
        yyval.methodDecl->numParameters = parameterList.size;
        yyval.methodDecl->returnType = yypvt[-4].type;
    } break;
case 90:
# line 1451 "mof.y"
{
        MOF_ParameterList parameterList = PTRARRAY_INITIALIZER;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_METHOD, &yypvt[-5].qualifierList) != 0)
            YYABORT;

        yyval.methodDecl = CALLOC_T(MI_MethodDecl, 1);
        yyval.methodDecl->name = yypvt[-3].string;
        yyval.methodDecl->parameters = parameterList.data;
        yyval.methodDecl->numParameters = parameterList.size;
        yyval.methodDecl->qualifiers = yypvt[-5].qualifierList.data;
        yyval.methodDecl->numQualifiers = yypvt[-5].qualifierList.size;
        yyval.methodDecl->returnType = yypvt[-4].type;
    } break;
case 91:
# line 1469 "mof.y"
{
        yypvt[-0].parameter->flags = MI_FLAG_PARAMETER;
        yypvt[-0].parameter->flags |= GetQualFlags(yypvt[-0].parameter->qualifiers, yypvt[-0].parameter->numQualifiers);
        yyval.parameterList.data = NULL;
        yyval.parameterList.size = 0;
        PtrArray_Append((PtrArray*)&yyval.parameterList, yypvt[-0].parameter);
    } break;
case 92:
# line 1477 "mof.y"
{
        if (FindParameter(&yypvt[-2].parameterList, yypvt[-0].parameter->name))
        {
            yyerrorf(ID_PARAMETER_ALREADY_DEFINED, 
                "parameter already defined: \"%s\"", yypvt[-0].parameter->name);
            YYABORT;
        }

        yypvt[-0].parameter->flags = MI_FLAG_PARAMETER;
        yypvt[-0].parameter->flags |= GetQualFlags(yypvt[-0].parameter->qualifiers, yypvt[-0].parameter->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.parameterList, yypvt[-0].parameter);
    } break;
case 93:
# line 1492 "mof.y"
{
        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yypvt[-0].string;
        yyval.parameter->type = yypvt[-1].type;
    } break;
case 94:
# line 1498 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-2].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-2].string);
            YYABORT;
        }

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yypvt[-0].string;
        yyval.parameter->type = MI_REFERENCE;
        yyval.parameter->className = cd->name;
    } break;
case 95:
# line 1515 "mof.y"
{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &yypvt[-2].qualifierList) != 0)
            YYABORT;

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yypvt[-0].string;
        yyval.parameter->type = yypvt[-1].type;
        yyval.parameter->qualifiers = yypvt[-2].qualifierList.data;
        yyval.parameter->numQualifiers = yypvt[-2].qualifierList.size;
    } break;
case 96:
# line 1527 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-2].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-2].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &yypvt[-3].qualifierList) != 0)
            YYABORT;

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yypvt[-0].string;
        yyval.parameter->type = MI_REFERENCE;
        yyval.parameter->className = cd->name;
        yyval.parameter->qualifiers = yypvt[-3].qualifierList.data;
        yyval.parameter->numQualifiers = yypvt[-3].qualifierList.size;
    } break;
case 97:
# line 1550 "mof.y"
{
        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yypvt[-1].string;
        yyval.parameter->type = ARRAYOF(yypvt[-2].type);
        yyval.parameter->subscript = (MI_Uint32)yypvt[-0].integer;
    } break;
case 98:
# line 1557 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-3].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-3].string);
            YYABORT;
        }

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yypvt[-1].string;
        yyval.parameter->type = ARRAYOF(MI_REFERENCE);
        yyval.parameter->className = cd->name;
        yyval.parameter->subscript = (MI_Uint32)yypvt[-0].integer;
    } break;
case 99:
# line 1575 "mof.y"
{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &yypvt[-3].qualifierList) != 0)
            YYABORT;

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yypvt[-1].string;
        yyval.parameter->type = ARRAYOF(yypvt[-2].type);
        yyval.parameter->subscript = (MI_Uint32)yypvt[-0].integer;
        yyval.parameter->qualifiers = yypvt[-3].qualifierList.data;
        yyval.parameter->numQualifiers = yypvt[-3].qualifierList.size;
    } break;
case 100:
# line 1588 "mof.y"
{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yypvt[-3].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yypvt[-3].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &yypvt[-4].qualifierList) != 0)
            YYABORT;

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yypvt[-1].string;
        yyval.parameter->type = ARRAYOF(MI_REFERENCE);
        yyval.parameter->className = cd->name;
        yyval.parameter->subscript = (MI_Uint32)yypvt[-0].integer;
        yyval.parameter->qualifiers = yypvt[-4].qualifierList.data;
        yyval.parameter->numQualifiers = yypvt[-4].qualifierList.size;
    } break;
case 101:
# line 1614 "mof.y"
{
        if (yypvt[-1].integer <= 0)
        {
            yyerrorf(ID_ILLEGAL_ARRAY_SUBSCRIPT, 
                "illegal array subscript: " SINT64_FMT, yypvt[-1].integer);
            YYABORT;
        }

        yyval.integer = yypvt[-1].integer;
    } break;
case 102:
# line 1625 "mof.y"
{
        /* 0 signifies a dynamic array */
        yyval.integer = 0;
    } break;
case 103:
# line 1632 "mof.y"
{
        yyval.initializer = yypvt[-0].initializer;
    } break;
case 104:
# line 1636 "mof.y"
{
        yyval.initializer = yypvt[-0].initializer;
    } break;
case 105:
# line 1642 "mof.y"
{
        yyval.initializer = yypvt[-1].initializer;
    } break;
case 106:
# line 1646 "mof.y"
{
        yyval.initializer.data = NULL;
        yyval.initializer.size = 0;
        yyval.initializer.isArray = 1;
    } break;
case 107:
# line 1654 "mof.y"
{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yypvt[-0].initializer.data[0];
        yyval.initializer.size = 1;
        yyval.initializer.isArray = 1;
    } break;
case 108:
# line 1662 "mof.y"
{
        yypvt[-2].initializer.data = REALLOC_T(MOF_ConstantValue, yypvt[-2].initializer.data, yypvt[-2].initializer.size + 1);
        yypvt[-2].initializer.data[yypvt[-2].initializer.size] = yypvt[-0].initializer.data[0];
        yypvt[-2].initializer.size++;
        yyval.initializer = yypvt[-2].initializer;
    } break;
case 109:
# line 1671 "mof.y"
{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yypvt[-0].constantValue;
        yyval.initializer.size = 1;
    } break;
case 110:
# line 1678 "mof.y"
{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0].type = TOK_STRING_VALUE;
        yyval.initializer.data[0].value.string = yypvt[-0].string;
        yyval.initializer.size = 1;
        /* TODO: look up alias, get and store instance decl. for alias */
    } break;
case 111:
# line 1687 "mof.y"
{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0].type = TOK_STRING_VALUE;
        yyval.initializer.data[0].value.string = yypvt[-3].string;
        yyval.initializer.size = 1;
        /* TODO: look up class $3, validate property names/types, store dynamic instance properties in this instance */
    } break;
case 112:
# line 1698 "mof.y"
{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yypvt[-0].constantValue;
        yyval.initializer.size = 1;
    } break;
case 113:
# line 1705 "mof.y"
{
        yyval.initializer = yypvt[-0].initializer;
    } break;
case 114:
# line 1711 "mof.y"
{
        yyval.initializer = yypvt[-1].initializer;
    } break;
case 115:
# line 1715 "mof.y"
{
        yyval.initializer.data = NULL;
        yyval.initializer.size = 0;
        yyval.initializer.isArray = MI_TRUE;
    } break;
case 116:
# line 1723 "mof.y"
{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yypvt[-0].constantValue;
        yyval.initializer.size = 1;
        yyval.initializer.isArray = MI_TRUE;
    } break;
case 117:
# line 1731 "mof.y"
{
        yypvt[-2].initializer.data = REALLOC_T(MOF_ConstantValue, yypvt[-2].initializer.data, yypvt[-2].initializer.size + 1);
        yypvt[-2].initializer.data[yypvt[-2].initializer.size] = yypvt[-0].constantValue;
        yypvt[-2].initializer.size++;
        yypvt[-2].initializer.isArray = MI_TRUE;
        yyval.initializer = yypvt[-2].initializer;
    } break;
case 118:
# line 1741 "mof.y"
{
        yyval.constantValue.type = TOK_INTEGER_VALUE;
        yyval.constantValue.value.integer = yypvt[-0].integer;
    } break;
case 119:
# line 1746 "mof.y"
{
        yyval.constantValue.type = TOK_REAL_VALUE;
        yyval.constantValue.value.real = yypvt[-0].real;
    } break;
case 120:
# line 1751 "mof.y"
{
        yyval.constantValue.type = TOK_CHAR_VALUE;
        yyval.constantValue.value.character = yypvt[-0].character;
    } break;
case 121:
# line 1756 "mof.y"
{
        yyval.constantValue.type = TOK_STRING_VALUE;
        yyval.constantValue.value.string = yypvt[-0].string;
    } break;
case 122:
# line 1761 "mof.y"
{
        yyval.constantValue.type = TOK_BOOLEAN_VALUE;
        yyval.constantValue.value.boolean = yypvt[-0].boolean;
    } break;
case 123:
# line 1766 "mof.y"
{
        yyval.constantValue.type = TOK_NULL;
    } break;
case 124:
# line 1772 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 125:
# line 1776 "mof.y"
{
        size_t size = strlen(yypvt[-1].string) + strlen(yypvt[-0].string) + 1;
        yyval.string = (char*)MOF_Realloc(&state.heap, yypvt[-1].string, size);
        Strcat(yyval.string, size, yypvt[-0].string);
        MOF_Free(&state.heap, yypvt[-0].string);
    } break;
case 126:
# line 1785 "mof.y"
{
        yypvt[-2].qualifierDeclaration->name = yypvt[-3].string;
        yypvt[-2].qualifierDeclaration->scope = yypvt[-1].flags;
        yypvt[-2].qualifierDeclaration->flavor = 0;
        yyval.qualifierDeclaration = yypvt[-2].qualifierDeclaration;
    } break;
case 127:
# line 1792 "mof.y"
{
        yypvt[-3].qualifierDeclaration->name = yypvt[-4].string;
        yypvt[-3].qualifierDeclaration->scope = yypvt[-2].flags;
        yypvt[-3].qualifierDeclaration->flavor = yypvt[-1].flags;
        yyval.qualifierDeclaration = yypvt[-3].qualifierDeclaration;
    } break;
case 128:
# line 1801 "mof.y"
{
        yyval.qualifierDeclaration = CALLOC_T(MI_QualifierDecl, 1);
        yyval.qualifierDeclaration->type = yypvt[-0].type;
    } break;
case 129:
# line 1806 "mof.y"
{
        void* value;

        if (InitializerToValue(&yypvt[-0].initializer, yypvt[-2].type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.qualifierDeclaration = CALLOC_T(MI_QualifierDecl, 1);
        yyval.qualifierDeclaration->type = yypvt[-2].type;
        yyval.qualifierDeclaration->value = value;
        ReleaseInitializer(&yypvt[-0].initializer);
    } break;
case 130:
# line 1821 "mof.y"
{
        yyval.qualifierDeclaration = CALLOC_T(MI_QualifierDecl, 1);
        yyval.qualifierDeclaration->type = ARRAYOF(yypvt[-1].type);
        yyval.qualifierDeclaration->subscript = (MI_Uint32)yypvt[-0].integer;
    } break;
case 131:
# line 1827 "mof.y"
{
        void* value = NULL;

        if (InitializerToValue(&yypvt[-0].initializer, ARRAYOF(yypvt[-3].type), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.qualifierDeclaration = CALLOC_T(MI_QualifierDecl, 1);
        yyval.qualifierDeclaration->type = ARRAYOF(yypvt[-3].type);
        yyval.qualifierDeclaration->subscript = (MI_Uint32)yypvt[-2].integer;
        yyval.qualifierDeclaration->value = value;
        ReleaseInitializer(&yypvt[-0].initializer);
    } break;
case 132:
# line 1845 "mof.y"
{
        yyval.flags = yypvt[-1].flags;
    } break;
case 133:
# line 1851 "mof.y"
{
        yyval.flags = yypvt[-0].flags;
    } break;
case 134:
# line 1855 "mof.y"
{
        yyval.flags |= yypvt[-0].flags;
    } break;
case 135:
# line 1861 "mof.y"
{
        yyval.flags = MI_FLAG_CLASS;
    } break;
case 136:
# line 1865 "mof.y"
{
        yyval.flags = MI_FLAG_ASSOCIATION;
    } break;
case 137:
# line 1869 "mof.y"
{
        yyval.flags = MI_FLAG_INDICATION;
    } break;
case 138:
# line 1873 "mof.y"
{
        yyval.flags = MI_FLAG_PROPERTY;
    } break;
case 139:
# line 1877 "mof.y"
{
        yyval.flags = MI_FLAG_REFERENCE;
    } break;
case 140:
# line 1881 "mof.y"
{
        yyval.flags = MI_FLAG_METHOD;
    } break;
case 141:
# line 1885 "mof.y"
{
        yyval.flags = MI_FLAG_PARAMETER;
    } break;
case 142:
# line 1889 "mof.y"
{
        yyval.flags = MI_FLAG_ANY;
    } break;
case 143:
# line 1895 "mof.y"
{
        /* Reject incompatiable ToSubclass and Restricted flavors */
        if (yypvt[-1].flags & MI_FLAG_TOSUBCLASS && yypvt[-1].flags & MI_FLAG_RESTRICTED)
        {
            yyerrorf(ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s", 
                "ToSubclass", "Restricted");
            YYABORT;
        }

        /* Reject incompatiable EnableOverride and DisableOverride flavors */
        if (yypvt[-1].flags & MI_FLAG_ENABLEOVERRIDE && yypvt[-1].flags & MI_FLAG_DISABLEOVERRIDE)
        {
            yyerrorf(ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s", 
                "EnableOverride", "DisableOverride");
            YYABORT;
        }

        yyval.flags = yypvt[-1].flags;
    } break;
case 144:
# line 1917 "mof.y"
{
        yyval.instanceDeclaration = CALLOC_T(MI_InstanceDecl, 1);
        yyval.instanceDeclaration->flags = 0;
        yyval.instanceDeclaration->name = yypvt[-1].string;
        yyval.instanceDeclaration->properties = yypvt[-0].featureList.propertySet.data;
        yyval.instanceDeclaration->numProperties = yypvt[-0].featureList.propertySet.size;
    } break;
case 145:
# line 1925 "mof.y"
{
        yyval.instanceDeclaration = CALLOC_T(MI_InstanceDecl, 1);
        yyval.instanceDeclaration->flags = 0;
        yyval.instanceDeclaration->name = yypvt[-1].string;
        yyval.instanceDeclaration->properties = yypvt[-0].featureList.propertySet.data;
        yyval.instanceDeclaration->numProperties = yypvt[-0].featureList.propertySet.size;
        yyval.instanceDeclaration->qualifiers = yypvt[-4].qualifierList.data;
        yyval.instanceDeclaration->numQualifiers = yypvt[-4].qualifierList.size;
    } break;
case 146:
# line 1935 "mof.y"
{
        /* [TODO]: handle alias */
        yyval.instanceDeclaration = CALLOC_T(MI_InstanceDecl, 1);
        yyval.instanceDeclaration->flags = 0;
        yyval.instanceDeclaration->name = yypvt[-2].string;
        yyval.instanceDeclaration->properties = yypvt[-0].featureList.propertySet.data;
        yyval.instanceDeclaration->numProperties = yypvt[-0].featureList.propertySet.size;
    } break;
case 147:
# line 1944 "mof.y"
{
        /* [TODO]: handle alias */
        yyval.instanceDeclaration = CALLOC_T(MI_InstanceDecl, 1);
        yyval.instanceDeclaration->flags = 0;
        yyval.instanceDeclaration->name = yypvt[-2].string;
        yyval.instanceDeclaration->properties = yypvt[-0].featureList.propertySet.data;
        yyval.instanceDeclaration->numProperties = yypvt[-0].featureList.propertySet.size;
        yyval.instanceDeclaration->qualifiers = yypvt[-5].qualifierList.data;
        yyval.instanceDeclaration->numQualifiers = yypvt[-5].qualifierList.size;
    } break;
case 148:
# line 1957 "mof.y"
{
        yyval.featureList = yypvt[-2].featureList;
    } break;
case 149:
# line 1961 "mof.y"
{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
    } break;
case 150:
# line 1970 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 151:
# line 1976 "mof.y"
{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yypvt[-0].property->flags = MI_FLAG_PROPERTY;
        yypvt[-0].property->flags |= GetQualFlags(yypvt[-0].property->qualifiers, yypvt[-0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yypvt[-0].property);
    } break;
case 152:
# line 1984 "mof.y"
{
        if (FindProperty(&yypvt[-1].featureList.propertySet, yypvt[-0].property->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "instance property already defined: \"%s\"", yypvt[-0].property->name);
            YYABORT;
        }

        yypvt[-0].property->flags = MI_FLAG_PROPERTY;
        yypvt[-0].property->flags |= GetQualFlags(yypvt[-0].property->qualifiers, yypvt[-0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yypvt[-0].property);
    } break;
case 153:
# line 1999 "mof.y"
{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yypvt[-1].string;
        yyval.property->type = TOK_NULL;
    } break;
case 154:
# line 2005 "mof.y"
{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yypvt[-1].string;
        yyval.property->type = TOK_NULL;
        yyval.property->qualifiers = yypvt[-2].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-2].qualifierList.size;
    } break;
case 155:
# line 2013 "mof.y"
{
        void* value;
        MI_Type type = InitializerToType(&yypvt[-1].initializer);
        if (InitializerToValue(&yypvt[-1].initializer, type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yypvt[-3].string;
        yyval.property->type = type;
        yyval.property->value = value;
    } break;
case 156:
# line 2028 "mof.y"
{
        void* value;
        MI_Type type = InitializerToType(&yypvt[-1].initializer);

        if (InitializerToValue(&yypvt[-1].initializer, type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yypvt[-3].string;
        yyval.property->type = type;
        yyval.property->value = value;
        yyval.property->qualifiers = yypvt[-4].qualifierList.data;
        yyval.property->numQualifiers = yypvt[-4].qualifierList.size;
    } break;
case 157:
# line 2048 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 158:
# line 2052 "mof.y"
{
        yyval.string = "Object";
    } break;
case 159:
# line 2056 "mof.y"
{
        yyval.string = "Boolean";
    } break;
case 160:
# line 2060 "mof.y"
{
        yyval.string = "Datetime";
    } break;
case 161:
# line 2064 "mof.y"
{
        yyval.string = "String";
    } break;
case 162:
# line 2074 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 163:
# line 2078 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 164:
# line 2082 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 165:
# line 2086 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 166:
# line 2090 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 167:
# line 2094 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 168:
# line 2098 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 169:
# line 2102 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 170:
# line 2106 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 171:
# line 2110 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 172:
# line 2114 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 173:
# line 2118 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 174:
# line 2122 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 175:
# line 2126 "mof.y"
{
        yyval.string = yypvt[-0].string;
    } break;
case 176:
# line 2132 "mof.y"
{
        yyval.type = MI_BOOLEAN;
    } break;
case 177:
# line 2136 "mof.y"
{
        yyval.type = MI_SINT8;
    } break;
case 178:
# line 2140 "mof.y"
{
        yyval.type = MI_UINT8;
    } break;
case 179:
# line 2144 "mof.y"
{
        yyval.type = MI_SINT16;
    } break;
case 180:
# line 2148 "mof.y"
{
        yyval.type = MI_UINT16;
    } break;
case 181:
# line 2152 "mof.y"
{
        yyval.type = MI_SINT32;
    } break;
case 182:
# line 2156 "mof.y"
{
        yyval.type = MI_UINT32;
    } break;
case 183:
# line 2160 "mof.y"
{
        yyval.type = MI_SINT64;
    } break;
case 184:
# line 2164 "mof.y"
{
        yyval.type = MI_UINT64;
    } break;
case 185:
# line 2168 "mof.y"
{
        yyval.type = MI_REAL32;
    } break;
case 186:
# line 2172 "mof.y"
{
        yyval.type = MI_REAL64;
    } break;
case 187:
# line 2176 "mof.y"
{
        yyval.type = MI_CHAR16;
    } break;
case 188:
# line 2180 "mof.y"
{
        yyval.type = MI_DATETIME;
    } break;
case 189:
# line 2184 "mof.y"
{
        yyval.type = MI_STRING;
    } break;
# line  531 "/usr/ccs/bin/yaccpar"
        }
        goto yystack;           /* reset registers in driver code */
}

