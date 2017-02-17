/*
 **==============================================================================
 **
 ** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
 ** for license information.
 **
 **==============================================================================
 */

/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "mof.y"

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

#line 20 "mof.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union
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
#endif /* !YYSTYPE_IS_DECLARED */
#line 70 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define TOK_ERROR 257
#define TOK_BOOLEAN 258
#define TOK_SINT8 259
#define TOK_UINT8 260
#define TOK_SINT16 261
#define TOK_UINT16 262
#define TOK_SINT32 263
#define TOK_UINT32 264
#define TOK_SINT64 265
#define TOK_UINT64 266
#define TOK_REAL32 267
#define TOK_REAL64 268
#define TOK_DATETIME 269
#define TOK_CHAR16 270
#define TOK_STRING 271
#define TOK_OBJECT 272
#define TOK_BOOLEAN_VALUE 273
#define TOK_REF 274
#define TOK_SCOPE 275
#define TOK_CLASS 276
#define TOK_ASSOCIATION 277
#define TOK_INDICATION 278
#define TOK_QUALIFIER 279
#define TOK_PROPERTY 280
#define TOK_REFERENCE 281
#define TOK_METHOD 282
#define TOK_PARAMETER 283
#define TOK_ANY 284
#define TOK_FLAVOR 285
#define TOK_ENABLEOVERRIDE 286
#define TOK_DISABLEOVERRIDE 287
#define TOK_RESTRICTED 288
#define TOK_TOSUBCLASS 289
#define TOK_TOINSTANCE 290
#define TOK_TRANSLATABLE 291
#define TOK_INSTANCE 292
#define TOK_OF 293
#define TOK_AS 294
#define TOK_PRAGMA 295
#define TOK_SCHEMA 296
#define TOK_INTEGER_VALUE 297
#define TOK_REAL_VALUE 298
#define TOK_STRING_VALUE 299
#define TOK_CHAR_VALUE 300
#define TOK_IDENT 301
#define TOK_ALIAS_IDENTIFIER 302
#define TOK_NULL 303
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    0,   43,   43,   43,   43,   44,   44,   39,
   39,   39,   39,   16,   16,   15,   15,   15,   15,   15,
   15,   15,   15,   15,   15,   15,   15,   37,   36,   36,
   35,   35,   35,   35,   38,   38,   32,   32,   33,   33,
   31,   31,   31,   31,   31,   31,    7,    7,    7,    7,
    7,    7,    7,    7,   12,   12,   12,   12,   12,   12,
   12,   12,   13,   13,   13,   13,   13,   13,   13,   13,
   10,   10,   10,   10,   10,   10,   10,   10,   11,   11,
   11,   11,   11,   11,   11,   11,   14,   14,   14,   14,
    9,    9,    8,    8,    8,    8,    8,    8,    8,    8,
   20,   20,   21,   21,   22,   22,   23,   23,   24,   24,
   24,   25,   25,   26,   26,   27,   27,    5,    5,    5,
    5,    5,    5,    1,    1,   18,   18,   19,   19,   19,
   19,   30,   29,   29,   28,   28,   28,   28,   28,   28,
   28,   28,   34,   40,   40,   40,   40,   17,   17,    4,
   42,   42,   41,   41,   41,   41,    3,    3,    3,    3,
    3,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,
};
static const YYINT yylen[] = {                            2,
    1,    2,    1,    1,    1,    1,    1,    5,    7,    3,
    5,    4,    6,    4,    3,    1,    1,    1,    1,    1,
    1,    2,    2,    2,    2,    2,    2,    3,    1,    3,
    1,    2,    3,    4,    3,    1,    1,    3,    1,    2,
    1,    1,    1,    1,    1,    1,    3,    4,    4,    5,
    5,    6,    6,    7,    3,    4,    4,    5,    5,    6,
    6,    7,    3,    4,    4,    5,    5,    6,    6,    7,
    4,    5,    6,    7,    5,    6,    7,    8,    4,    5,
    5,    6,    6,    7,    7,    8,    6,    7,    5,    6,
    1,    3,    2,    3,    3,    4,    3,    4,    4,    5,
    3,    2,    1,    1,    3,    2,    1,    3,    1,    1,
    6,    1,    1,    3,    2,    1,    3,    1,    1,    1,
    1,    1,    1,    1,    2,    5,    6,    2,    4,    3,
    5,    5,    1,    3,    1,    1,    1,    1,    1,    1,
    1,    1,    5,    4,    5,    5,    6,    4,    3,    2,
    1,    2,    2,    3,    4,    5,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
    3,    0,    0,    0,    0,    0,    0,    6,    0,    5,
    7,    1,    4,  164,  167,  168,  171,  170,  169,  166,
  175,  172,  173,  174,  165,  163,  162,    0,  159,  160,
  161,  158,  157,    0,    0,    0,    0,   29,    0,    2,
    0,    0,    0,    0,   10,    0,    0,    0,    0,    0,
    0,    0,    0,   36,    0,    0,   28,    0,    0,    0,
  176,  177,  178,  179,  180,  181,  182,  183,  184,  185,
  186,  188,  187,  189,    0,    0,    0,    0,   16,   18,
   19,   20,   21,   17,    0,    0,    0,    0,    0,    0,
  144,    0,    0,  124,    0,  122,  118,  119,  120,  123,
    0,    0,   41,   42,   43,   44,   45,   46,   39,    0,
  115,  116,    0,    0,   30,    0,   12,    0,   11,    0,
    0,   15,    0,    0,    0,    0,   22,   24,   25,   26,
   27,   23,    0,    0,    0,    0,    0,    0,    0,    0,
  126,    0,    0,    0,    0,  151,    0,  150,  146,  125,
    8,    0,   35,   40,    0,  114,    0,    0,    0,  145,
    0,   63,    0,    0,    0,   55,    0,    0,    0,   47,
    0,    0,   14,    0,    0,    0,    0,    0,    0,  102,
  112,  129,  113,    0,    0,    0,  127,  149,  153,    0,
    0,    0,  152,    0,  117,   13,  147,   79,    0,    0,
    0,  110,    0,  109,    0,  104,  103,   65,    0,   71,
    0,    0,    0,   57,    0,    0,    0,    0,   91,    0,
    0,    0,   49,    0,    0,   64,    0,    0,    0,   56,
    0,    0,    0,   48,    0,    0,  101,  131,  135,  136,
  137,  138,  139,  140,  141,  142,  133,    0,    0,    0,
  154,    0,  148,    9,    0,   81,    0,    0,  106,    0,
  107,   67,    0,    0,   75,    0,   59,    0,   89,    0,
    0,    0,    0,    0,    0,   51,    0,   80,    0,    0,
    0,   66,    0,   72,    0,    0,    0,   58,    0,    0,
    0,    0,   50,    0,  132,    0,   37,    0,  155,    0,
   83,    0,    0,    0,  105,   69,   73,    0,   61,    0,
   97,   87,   92,    0,    0,   53,    0,   82,    0,   68,
    0,    0,   76,    0,   60,    0,   90,    0,   52,    0,
  134,  143,    0,  156,   84,    0,  108,   77,   98,    0,
   99,   85,    0,   70,   74,    0,   62,   88,   54,   38,
    0,  100,   86,   78,  111,
};
static const YYINT yydgoto[] = {                          7,
  101,   33,  144,   93,  204,  218,   79,  219,  220,   80,
   81,   82,   83,   84,   85,   45,   91,    8,   47,  138,
  205,  206,  260,  207,  182,  183,  113,  247,  248,   89,
  109,  298,  110,  142,   38,   39,  145,   55,   10,   11,
  146,  147,   12,   13,
};
static const YYINT yysindex[] = {                       -82,
    0,  675,  649, -264, -262,  649,  -76,    0, -236,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -38,    0,    0,
    0,    0,    0,   36,  649,   17,  -22,    0,  -10,    0,
  675, -235,  675,  107,    0,  719,   15,  -14, -179, -183,
  209,  228,  -47,    0,   70,  649,    0,  -30,  675,    6,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  426,   62,  565,  649,    0,    0,
    0,    0,    0,    0,  166,  493,  -28, -137,   25,  255,
    0, -143,  -14,    0,  -37,    0,    0,    0,    0,    0,
 -136,  126,    0,    0,    0,    0,    0,    0,    0,  228,
    0,    0,  -19,  228,    0,  675,    0, -117,    0,  649,
   20,    0,  649,   65,   12,  109,    0,    0,    0,    0,
    0,    0,  593,  621,  649,  -77,  -92,  113,  138, -106,
    0,  130,  133,  103,  649,    0,  291,    0,    0,    0,
    0,  649,    0,    0,  209,    0,  228,    6,  -14,    0,
   66,    0, -112,  123,   74,    0, -112,  134,   19,    0,
 -112,  169,    0,  649,   75,  649,   78,   21,  108,    0,
    0,    0,    0,  -92,  129,  156,    0,    0,    0, -112,
  172,  143,    0,  168,    0,    0,    0,    0, -112,  179,
  -79,    0,  -55,    0,  158,    0,    0,    0, -112,    0,
 -112,  212,  163,    0, -112,  164,  -39,  649,    0,   24,
  537,  182,    0, -112,   85,    0, -112,  233,   92,    0,
 -112,  246,   63,    0, -112,  254,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   46,  228,  187,
    0, -112,    0,    0,  190,    0, -112,  675,    0,  -17,
    0,    0,  195,  196,    0, -112,    0,  200,    0,  649,
  136,  201,  210,   -4,  649,    0,  216,    0, -112,  257,
  234,    0, -112,    0, -112,  258,  243,    0, -112,  247,
   54,  276,    0, -112,    0,  129,    0,   58,    0,  277,
    0,  278,  215,  -34,    0,    0,    0,  286,    0,  136,
    0,    0,    0,  649,  136,    0,  290,    0, -112,    0,
  292,  296,    0, -112,    0,  298,    0,  300,    0,  301,
    0,    0,  228,    0,    0,  363,    0,    0,    0,  136,
    0,    0,  302,    0,    0,  303,    0,    0,    0,    0,
  327,    0,    0,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   -2,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   56,    0,    0,
    0,    0,    0,    0,   -1,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  319,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -18,    0,    0,    0,    0,    0,    0,    0,    0,    4,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  337,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    7,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   99,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  104,
    0,    0,    0,    0,  106,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  114,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  339,    3,   -3,  272,  -32,   -9,  308,  121,  162,  314,
  316,  318,  329,  330,    0,  -36,  -63,    0,    0, -111,
  456,    0,    0, -191,  220,  380,    0,  124,    0,    0,
 -108,    0,  305,    0,  365,    0,    1,    0,    0,    0,
 -130,   86,  416,    0,
};
#define YYTABLESIZE 990
static const YYINT yytable[] = {                         34,
    9,  154,   37,  151,   28,   90,  152,    9,    6,  164,
  203,  261,  168,  172,    6,  180,  193,   51,  102,   43,
  112,  117,  121,  119,  155,  121,  304,  116,   35,  149,
   53,   49,  137,   56,   78,   52,   87,   48,   36,   41,
  121,   31,   32,   58,   86,   60,   77,   33,  154,  200,
   34,  169,   37,  212,  160,   42,   50,   59,   88,  216,
  233,  118,  136,  228,  272,  232,  236,  273,  140,  259,
  170,  121,  171,  124,  125,   78,  135,  111,  162,  234,
  163,  235,   57,  141,   44,   86,  295,   77,  134,  296,
   31,   32,   44,   46,  328,  197,   33,  273,  332,   34,
   53,  333,  136,  290,  181,  156,  121,  305,   90,    6,
  136,  136,  337,  280,   92,   94,  161,  286,  158,  165,
  122,  196,  195,  166,  198,  167,  199,  114,   44,  175,
  177,  178,  210,  226,  211,  227,  230,  139,  231,   93,
  297,  191,   93,  278,   94,  279,   95,   94,  194,   95,
  284,  181,  285,    6,   96,  136,  136,   96,  148,  311,
   96,  189,  150,  190,  136,  136,  153,  173,  136,  221,
  225,  217,  229,  184,    1,  136,   92,  185,  186,  201,
   96,  208,  136,  209,   97,   98,   94,   99,  187,  202,
  100,  188,  214,    2,  215,  249,    3,    6,  339,    2,
  237,  253,    3,  341,   97,   98,   94,   99,  254,    4,
  100,  275,    5,  258,  271,    4,  262,   96,    5,  179,
  193,  267,  269,  274,  350,   96,  136,  223,  352,  224,
  251,   76,  252,  221,  270,  217,  201,  256,   96,  257,
  276,   97,   98,   94,   99,  299,  202,  100,  301,   97,
   98,   94,   99,  306,  307,  100,    6,  201,  309,  312,
  303,  150,   97,   98,   94,   99,  310,  202,  100,  314,
  265,  315,  266,  221,  316,  217,   61,   62,   63,   64,
   65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
  126,  282,  320,  283,   14,   15,   16,   17,   18,   19,
    6,  325,   20,   21,  288,  327,  289,   22,   23,   24,
  340,   25,  293,   26,  294,  318,  323,  319,  324,   27,
   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
   71,   72,   73,   74,  329,  334,  335,  336,   14,   15,
   16,   17,   18,   19,  338,    6,   20,   21,  342,  157,
  344,   22,   23,   24,  345,   25,  347,   26,  348,  349,
  353,  354,  128,   27,   61,   62,   63,   64,   65,   66,
   67,   68,   69,   70,   71,   72,   73,   74,   75,  143,
  130,    6,   14,   15,   16,   17,   18,   19,   95,  159,
   20,   21,  127,  313,  291,   22,   23,   24,  128,   25,
  129,   26,  130,  238,  239,  240,  241,   27,  242,  243,
  244,  245,  246,  131,  132,  192,   54,    6,  157,  331,
  115,  351,   40,   61,   62,   63,   64,   65,   66,   67,
   68,   69,   70,   71,   72,   73,   74,   75,    0,    0,
    0,   14,   15,   16,   17,   18,   19,    0,    0,   20,
   21,  355,    0,    6,   22,   23,   24,    0,   25,    0,
   26,    0,    0,    0,    0,    0,   27,   61,   62,   63,
   64,   65,   66,   67,   68,   69,   70,   71,   72,   73,
   74,   96,    0,    0,    0,   14,   15,   16,   17,   18,
   19,    0,    0,   20,   21,    0,    0,    0,   22,   23,
   24,    0,   25,    0,   26,   97,   98,   94,   99,    0,
   27,  100,   29,  103,  104,  105,  106,  107,  108,    0,
    0,    0,    0,   30,    0,   31,   32,    0,    0,    0,
   14,   15,   16,   17,   18,   19,    0,    0,   20,   21,
    0,    0,    0,   22,   23,   24,    0,   25,   29,   26,
    0,    0,    0,    0,    0,   27,    0,    0,    0,   30,
    0,   31,   32,    0,    0,    0,   14,   15,   16,   17,
   18,   19,    0,    0,   20,   21,    0,    0,    0,   22,
   23,   24,    0,   25,   29,   26,    0,    0,    0,    0,
    0,   27,    0,    0,    0,   30,    0,   31,   32,    0,
    0,    0,   14,   15,   16,   17,   18,   19,    0,    0,
   20,   21,    0,    0,    0,   22,   23,   24,    0,   25,
   29,   26,  213,    0,    0,    0,  222,   27,    0,    0,
    0,   30,    0,   31,   32,    0,    0,    0,   14,   15,
   16,   17,   18,   19,    0,  250,   20,   21,    0,    0,
    0,   22,   23,   24,  255,   25,    0,   26,    0,    0,
    0,    0,    0,   27,  263,    0,  264,    0,    0,    0,
  268,    0,    0,    0,    0,    0,    0,    0,    0,  277,
    0,    0,  281,   29,    0,    0,  287,    0,    0,    0,
  292,    0,    0,    0,   30,    0,   31,   32,    0,  120,
    0,   14,   15,   16,   17,   18,   19,  300,    0,   20,
   21,    0,  302,    0,   22,   23,   24,    0,   25,    0,
   26,  308,    0,    0,    0,    0,   27,    0,    0,    0,
    0,    0,    0,    0,  317,    0,    0,    0,  321,    0,
  322,    0,    0,    0,  326,    0,    0,    0,    0,  330,
   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
   71,   72,   73,   74,  133,    0,    0,    0,   14,   15,
   16,   17,   18,   19,  343,    0,   20,   21,    0,  346,
    0,   22,   23,   24,    0,   25,    0,   26,    0,    0,
    0,    0,    0,   27,   61,   62,   63,   64,   65,   66,
   67,   68,   69,   70,   71,   72,   73,   74,    0,    0,
    0,    0,   14,   15,   16,   17,   18,   19,    0,    0,
   20,   21,   29,    0,    0,   22,   23,   24,    0,   25,
    0,   26,    0,   30,    0,   31,   32,   27,  123,    0,
   14,   15,   16,   17,   18,   19,    0,    0,   20,   21,
   29,    0,    0,   22,   23,   24,    0,   25,    0,   26,
    0,   30,    0,   31,   32,   27,  174,    0,   14,   15,
   16,   17,   18,   19,    0,    0,   20,   21,   29,    0,
    0,   22,   23,   24,    0,   25,    0,   26,    0,   30,
    0,   31,   32,   27,  176,    0,   14,   15,   16,   17,
   18,   19,    0,    0,   20,   21,   29,    0,    0,   22,
   23,   24,    0,   25,    0,   26,    0,   30,    0,   31,
   32,   27,    0,    0,   14,   15,   16,   17,   18,   19,
    0,    0,   20,   21,    0,    0,    0,   22,   23,   24,
    0,   25,    0,   26,    0,    0,    0,    0,    0,   27,
   14,   15,   16,   17,   18,   19,    0,    0,   20,   21,
    0,    0,    0,   22,   23,   24,    0,   25,    0,   26,
    0,    0,    0,    0,    0,   27,   61,   62,   63,   64,
   65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
};
static const YYINT yycheck[] = {                          3,
    0,  110,    6,   41,    2,  123,   44,    7,   91,  121,
  123,  203,  124,  125,   91,   93,  147,   40,   51,   58,
   53,   58,   41,   60,   44,   44,   44,   58,  293,   93,
  123,   35,   61,   44,   44,   58,   46,   35,  301,  276,
   59,   44,   44,   41,   44,   43,   44,   44,  157,  161,
   44,   40,   56,  165,  118,  292,   40,  293,   44,   41,
   40,   59,   91,  175,   41,  177,  178,   44,   44,  125,
   59,   75,   61,   77,   78,   85,   86,  125,   59,   59,
   61,   61,   93,   59,  123,   85,   41,   85,   86,   44,
   93,   93,  123,   58,   41,  159,   93,   44,   41,   93,
  123,   44,   91,   41,  137,  125,  125,  125,  123,   91,
   91,   91,  304,  225,  294,  299,  120,  229,  116,  123,
   59,  158,  155,   59,   59,   61,   61,   58,  123,  133,
  134,  135,   59,   59,   61,   61,   59,  275,   61,   41,
  249,  145,   44,   59,   41,   61,   41,   44,  152,   44,
   59,  184,   61,   91,   41,   91,   91,   44,  302,  271,
  273,   59,  299,   61,   91,   91,   41,   59,   91,  169,
  174,  169,  176,   61,  257,   91,  294,   40,  285,  292,
  273,   59,   91,   61,  297,  298,  299,  300,   59,  302,
  303,   59,   59,  276,   61,   40,  279,   91,  310,  276,
   93,   59,  279,  315,  297,  298,  299,  300,   41,  292,
  303,  221,  295,  293,  218,  292,   59,  273,  295,  297,
  351,   59,   59,  221,  333,  273,   91,   59,  340,   61,
   59,  125,   61,  233,  274,  233,  292,   59,  273,   61,
   59,  297,  298,  299,  300,   59,  302,  303,   59,  297,
  298,  299,  300,   59,   59,  303,   91,  292,   59,   59,
  258,  299,  297,  298,  299,  300,  270,  302,  303,  274,
   59,  275,   61,  273,   59,  273,  258,  259,  260,  261,
  262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
  125,   59,   59,   61,  276,  277,  278,  279,  280,  281,
   91,   59,  284,  285,   59,   59,   61,  289,  290,  291,
  314,  293,   59,  295,   61,   59,   59,   61,   61,  301,
  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,
  268,  269,  270,  271,   59,   59,   59,  123,  276,  277,
  278,  279,  280,  281,   59,   91,  284,  285,   59,  294,
   59,  289,  290,  291,   59,  293,   59,  295,   59,   59,
   59,   59,   44,  301,  258,  259,  260,  261,  262,  263,
  264,  265,  266,  267,  268,  269,  270,  271,  272,  125,
   44,   91,  276,  277,  278,  279,  280,  281,   50,  118,
  284,  285,   85,  273,  233,  289,  290,  291,   85,  293,
   85,  295,   85,  184,  276,  277,  278,  301,  280,  281,
  282,  283,  284,   85,   85,  125,   37,   91,  114,  296,
   56,  336,    7,  258,  259,  260,  261,  262,  263,  264,
  265,  266,  267,  268,  269,  270,  271,  272,   -1,   -1,
   -1,  276,  277,  278,  279,  280,  281,   -1,   -1,  284,
  285,  125,   -1,   91,  289,  290,  291,   -1,  293,   -1,
  295,   -1,   -1,   -1,   -1,   -1,  301,  258,  259,  260,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  273,   -1,   -1,   -1,  276,  277,  278,  279,  280,
  281,   -1,   -1,  284,  285,   -1,   -1,   -1,  289,  290,
  291,   -1,  293,   -1,  295,  297,  298,  299,  300,   -1,
  301,  303,  258,  286,  287,  288,  289,  290,  291,   -1,
   -1,   -1,   -1,  269,   -1,  271,  272,   -1,   -1,   -1,
  276,  277,  278,  279,  280,  281,   -1,   -1,  284,  285,
   -1,   -1,   -1,  289,  290,  291,   -1,  293,  258,  295,
   -1,   -1,   -1,   -1,   -1,  301,   -1,   -1,   -1,  269,
   -1,  271,  272,   -1,   -1,   -1,  276,  277,  278,  279,
  280,  281,   -1,   -1,  284,  285,   -1,   -1,   -1,  289,
  290,  291,   -1,  293,  258,  295,   -1,   -1,   -1,   -1,
   -1,  301,   -1,   -1,   -1,  269,   -1,  271,  272,   -1,
   -1,   -1,  276,  277,  278,  279,  280,  281,   -1,   -1,
  284,  285,   -1,   -1,   -1,  289,  290,  291,   -1,  293,
  258,  295,  167,   -1,   -1,   -1,  171,  301,   -1,   -1,
   -1,  269,   -1,  271,  272,   -1,   -1,   -1,  276,  277,
  278,  279,  280,  281,   -1,  190,  284,  285,   -1,   -1,
   -1,  289,  290,  291,  199,  293,   -1,  295,   -1,   -1,
   -1,   -1,   -1,  301,  209,   -1,  211,   -1,   -1,   -1,
  215,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  224,
   -1,   -1,  227,  258,   -1,   -1,  231,   -1,   -1,   -1,
  235,   -1,   -1,   -1,  269,   -1,  271,  272,   -1,  274,
   -1,  276,  277,  278,  279,  280,  281,  252,   -1,  284,
  285,   -1,  257,   -1,  289,  290,  291,   -1,  293,   -1,
  295,  266,   -1,   -1,   -1,   -1,  301,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  279,   -1,   -1,   -1,  283,   -1,
  285,   -1,   -1,   -1,  289,   -1,   -1,   -1,   -1,  294,
  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,
  268,  269,  270,  271,  272,   -1,   -1,   -1,  276,  277,
  278,  279,  280,  281,  319,   -1,  284,  285,   -1,  324,
   -1,  289,  290,  291,   -1,  293,   -1,  295,   -1,   -1,
   -1,   -1,   -1,  301,  258,  259,  260,  261,  262,  263,
  264,  265,  266,  267,  268,  269,  270,  271,   -1,   -1,
   -1,   -1,  276,  277,  278,  279,  280,  281,   -1,   -1,
  284,  285,  258,   -1,   -1,  289,  290,  291,   -1,  293,
   -1,  295,   -1,  269,   -1,  271,  272,  301,  274,   -1,
  276,  277,  278,  279,  280,  281,   -1,   -1,  284,  285,
  258,   -1,   -1,  289,  290,  291,   -1,  293,   -1,  295,
   -1,  269,   -1,  271,  272,  301,  274,   -1,  276,  277,
  278,  279,  280,  281,   -1,   -1,  284,  285,  258,   -1,
   -1,  289,  290,  291,   -1,  293,   -1,  295,   -1,  269,
   -1,  271,  272,  301,  274,   -1,  276,  277,  278,  279,
  280,  281,   -1,   -1,  284,  285,  258,   -1,   -1,  289,
  290,  291,   -1,  293,   -1,  295,   -1,  269,   -1,  271,
  272,  301,   -1,   -1,  276,  277,  278,  279,  280,  281,
   -1,   -1,  284,  285,   -1,   -1,   -1,  289,  290,  291,
   -1,  293,   -1,  295,   -1,   -1,   -1,   -1,   -1,  301,
  276,  277,  278,  279,  280,  281,   -1,   -1,  284,  285,
   -1,   -1,   -1,  289,  290,  291,   -1,  293,   -1,  295,
   -1,   -1,   -1,   -1,   -1,  301,  258,  259,  260,  261,
  262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 303
#define YYUNDFTOKEN 350
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,"':'","';'",0,"'='",
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"TOK_ERROR","TOK_BOOLEAN","TOK_SINT8","TOK_UINT8","TOK_SINT16",
"TOK_UINT16","TOK_SINT32","TOK_UINT32","TOK_SINT64","TOK_UINT64","TOK_REAL32",
"TOK_REAL64","TOK_DATETIME","TOK_CHAR16","TOK_STRING","TOK_OBJECT",
"TOK_BOOLEAN_VALUE","TOK_REF","TOK_SCOPE","TOK_CLASS","TOK_ASSOCIATION",
"TOK_INDICATION","TOK_QUALIFIER","TOK_PROPERTY","TOK_REFERENCE","TOK_METHOD",
"TOK_PARAMETER","TOK_ANY","TOK_FLAVOR","TOK_ENABLEOVERRIDE",
"TOK_DISABLEOVERRIDE","TOK_RESTRICTED","TOK_TOSUBCLASS","TOK_TOINSTANCE",
"TOK_TRANSLATABLE","TOK_INSTANCE","TOK_OF","TOK_AS","TOK_PRAGMA","TOK_SCHEMA",
"TOK_INTEGER_VALUE","TOK_REAL_VALUE","TOK_STRING_VALUE","TOK_CHAR_VALUE",
"TOK_IDENT","TOK_ALIAS_IDENTIFIER","TOK_NULL",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : mofSpecification",
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
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 167 "mof.y"
	{
    }
break;
case 2:
#line 170 "mof.y"
	{ 
    }
break;
case 3:
#line 173 "mof.y"
	{
        YYABORT;
    }
break;
case 4:
#line 179 "mof.y"
	{
    }
break;
case 5:
#line 182 "mof.y"
	{
        /* [TODO: validate the class here] */
        yystack.l_mark[0].classDeclaration->flags = MI_FLAG_CLASS;
        yystack.l_mark[0].classDeclaration->flags |= GetQualFlags(yystack.l_mark[0].classDeclaration->qualifiers, yystack.l_mark[0].classDeclaration->numQualifiers);
        if (FinalizeClass(yystack.l_mark[0].classDeclaration) != 0)
            YYABORT;
            
        AddClassDecl(yystack.l_mark[0].classDeclaration);

        if (state.classDeclCallback)
            (*state.classDeclCallback)(yystack.l_mark[0].classDeclaration, state.classDeclCallbackData);
    }
break;
case 6:
#line 195 "mof.y"
	{
        AddQualifierDeclaration(yystack.l_mark[0].qualifierDeclaration);

        if (state.qualifierDeclCallback)
            (*state.qualifierDeclCallback)(yystack.l_mark[0].qualifierDeclaration, state.qualifierDeclCallbackData);
    }
break;
case 7:
#line 202 "mof.y"
	{
        if (FinalizeInstance(yystack.l_mark[0].instanceDeclaration) != 0)
            YYABORT;

        AddInstanceDecl(yystack.l_mark[0].instanceDeclaration);

        if (state.instanceDeclCallback)
            (*state.instanceDeclCallback)(yystack.l_mark[0].instanceDeclaration, state.instanceDeclCallbackData);
    }
break;
case 8:
#line 214 "mof.y"
	{
        if (strcmp(yystack.l_mark[-3].string, "include") == 0)
        {
            if (openIncludeFile(yystack.l_mark[-1].string) != 0)
                YYABORT;
        }
        else if (strcmp(yystack.l_mark[-3].string, "instancelocale") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)(yystack.l_mark[-3].string, yystack.l_mark[-1].string, state.pragmaCallbackData);
        }
        else if (strcmp(yystack.l_mark[-3].string, "locale") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)(yystack.l_mark[-3].string, yystack.l_mark[-1].string, state.pragmaCallbackData);
        }
        else if (strcmp(yystack.l_mark[-3].string, "namespace") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)(yystack.l_mark[-3].string, yystack.l_mark[-1].string, state.pragmaCallbackData);
        }
        else if (state.extensionsEnabled == MI_TRUE && strcmp(yystack.l_mark[-3].string, "deleteclass") == 0)
        {
            yywarnf(ID_UNKNOWN_PRAGMA, 
                "warning: nonstandard pragma: %s(%s)", yystack.l_mark[-3].string, yystack.l_mark[-1].string);

            if (state.pragmaCallback)
                (*state.pragmaCallback)(yystack.l_mark[-3].string, yystack.l_mark[-1].string, state.pragmaCallbackData);
        }
        else
        {
            yywarnf(ID_UNKNOWN_PRAGMA, 
                "warning: unknown pragma: %s(%s)", yystack.l_mark[-3].string, yystack.l_mark[-1].string);

            if (state.pragmaCallback)
                (*state.pragmaCallback)(yystack.l_mark[-3].string, yystack.l_mark[-1].string, state.pragmaCallbackData);
        }
    }
break;
case 9:
#line 253 "mof.y"
	{
        if (state.extensionsEnabled == MI_TRUE && strcmp(yystack.l_mark[-5].string, "deleteclass") == 0)
        {
            yywarnf(ID_UNKNOWN_PRAGMA, 
                "warning: nonstandard pragma: %s(%s)", yystack.l_mark[-5].string, yystack.l_mark[-3].string);

            if (state.pragmaCallback)
                (*state.pragmaCallback)(yystack.l_mark[-5].string, yystack.l_mark[-3].string, state.pragmaCallbackData);
        }
        else
        {
            yywarnf(ID_UNKNOWN_PRAGMA, 
                "warning: unknown pragma: %s(%s)", yystack.l_mark[-5].string, yystack.l_mark[-3].string);

            if (state.pragmaCallback)
                (*state.pragmaCallback)(yystack.l_mark[-5].string, yystack.l_mark[-3].string, state.pragmaCallbackData);
        }
    }
break;
case 10:
#line 274 "mof.y"
	{
        /* Check whether class already exists */
        if (FindClassDecl(yystack.l_mark[-1].string))
        {
            if (state.extensionsEnabled == MI_FALSE)
            {
                yyerrorf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yystack.l_mark[-1].string);
                YYABORT;
            }
            else
                yywarnf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yystack.l_mark[-1].string);
        }

        yyval.classDeclaration = CALLOC_T(MI_ClassDecl, 1);
        yyval.classDeclaration->flags = MI_FLAG_CLASS;
        yyval.classDeclaration->name = yystack.l_mark[-1].string;
        yyval.classDeclaration->properties = yystack.l_mark[0].featureList.propertySet.data;
        yyval.classDeclaration->numProperties = yystack.l_mark[0].featureList.propertySet.size;
        yyval.classDeclaration->methods = yystack.l_mark[0].featureList.methodList.data;
        yyval.classDeclaration->numMethods = yystack.l_mark[0].featureList.methodList.size;
    }
break;
case 11:
#line 298 "mof.y"
	{
        const MI_ClassDecl* scd;

        /* Check whether class already exists */
        if (FindClassDecl(yystack.l_mark[-3].string))
        {
            if (state.extensionsEnabled == MI_FALSE)
            {
                yyerrorf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yystack.l_mark[-3].string);
                YYABORT;
            }
            else
                yywarnf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yystack.l_mark[-3].string);
        }
 
        /* Check whether superclass exists */
        scd = FindClassDecl(yystack.l_mark[-1].string);

        if (!scd)
        {
            yyerrorf(ID_UNDEFINED_SUPERCLASS, 
                "super class of \"%s\" is undefined: \"%s\"", yystack.l_mark[-3].string, yystack.l_mark[-1].string);
            YYABORT;
        }

        yyval.classDeclaration = CALLOC_T(MI_ClassDecl, 1);
        yyval.classDeclaration->flags = MI_FLAG_CLASS;
        yyval.classDeclaration->name = yystack.l_mark[-3].string;
        yyval.classDeclaration->superClass = yystack.l_mark[-1].string;
        yyval.classDeclaration->superClassDecl = (MI_ClassDecl*)scd;
        yyval.classDeclaration->properties = yystack.l_mark[0].featureList.propertySet.data;
        yyval.classDeclaration->numProperties = yystack.l_mark[0].featureList.propertySet.size;
        yyval.classDeclaration->methods = yystack.l_mark[0].featureList.methodList.data;
        yyval.classDeclaration->numMethods = yystack.l_mark[0].featureList.methodList.size;
    }
break;
case 12:
#line 336 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_CLASS, &yystack.l_mark[-3].qualifierList) != 0)
            YYABORT;

        /* Check whether class already exists */
        if (FindClassDecl(yystack.l_mark[-1].string))
        {
            if (state.extensionsEnabled == MI_FALSE)
            {
                yyerrorf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yystack.l_mark[-1].string);
                YYABORT;
            }
            else
                yywarnf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yystack.l_mark[-1].string);
        }

        yyval.classDeclaration = CALLOC_T(MI_ClassDecl, 1);
        yyval.classDeclaration->flags = MI_FLAG_CLASS;
        yyval.classDeclaration->name = yystack.l_mark[-1].string;
        yyval.classDeclaration->properties = yystack.l_mark[0].featureList.propertySet.data;
        yyval.classDeclaration->numProperties = yystack.l_mark[0].featureList.propertySet.size;
        yyval.classDeclaration->methods = yystack.l_mark[0].featureList.methodList.data;
        yyval.classDeclaration->numMethods = yystack.l_mark[0].featureList.methodList.size;
        yyval.classDeclaration->qualifiers = yystack.l_mark[-3].qualifierList.data;
        yyval.classDeclaration->numQualifiers = yystack.l_mark[-3].qualifierList.size;
    }
break;
case 13:
#line 366 "mof.y"
	{
        const MI_ClassDecl* scd;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_CLASS, &yystack.l_mark[-5].qualifierList) != 0)
            YYABORT;

        /* Check whether class already exists */
        if (FindClassDecl(yystack.l_mark[-3].string))
        {
            if (state.extensionsEnabled == MI_FALSE)
            {
                yyerrorf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yystack.l_mark[-3].string);
                YYABORT;
            }
            else
                yywarnf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", yystack.l_mark[-3].string);
        }

        /* Check whether superclass exists */
        scd = FindClassDecl(yystack.l_mark[-1].string);

        if (!scd)
        {
            yyerrorf(ID_UNDEFINED_SUPERCLASS, 
                "super class of \"%s\" is undefined: \"%s\"", yystack.l_mark[-3].string, yystack.l_mark[-1].string);
            YYABORT;
        }

        yyval.classDeclaration = CALLOC_T(MI_ClassDecl, 1);
        yyval.classDeclaration->flags = MI_FLAG_CLASS;
        yyval.classDeclaration->name = yystack.l_mark[-3].string;
        yyval.classDeclaration->superClass = scd->name;
        yyval.classDeclaration->superClassDecl = (MI_ClassDecl*)scd;
        yyval.classDeclaration->properties = yystack.l_mark[0].featureList.propertySet.data;
        yyval.classDeclaration->numProperties = yystack.l_mark[0].featureList.propertySet.size;
        yyval.classDeclaration->methods = yystack.l_mark[0].featureList.methodList.data;
        yyval.classDeclaration->numMethods = yystack.l_mark[0].featureList.methodList.size;
        yyval.classDeclaration->qualifiers = yystack.l_mark[-5].qualifierList.data;
        yyval.classDeclaration->numQualifiers = yystack.l_mark[-5].qualifierList.size;
    }
break;
case 14:
#line 412 "mof.y"
	{
        yyval.featureList = yystack.l_mark[-2].featureList;
    }
break;
case 15:
#line 416 "mof.y"
	{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
    }
break;
case 16:
#line 425 "mof.y"
	{
        if (CheckPropertyValueConstraints(yystack.l_mark[0].property) != 0)
        {
            YYABORT;
        }
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property);
    }
break;
case 17:
#line 439 "mof.y"
	{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yystack.l_mark[0].methodDecl->flags = MI_FLAG_METHOD;
        yystack.l_mark[0].methodDecl->flags |= GetQualFlags(yystack.l_mark[0].methodDecl->qualifiers, yystack.l_mark[0].methodDecl->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.methodList, yystack.l_mark[0].methodDecl);
    }
break;
case 18:
#line 449 "mof.y"
	{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property);
    }
break;
case 19:
#line 459 "mof.y"
	{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property);
    }
break;
case 20:
#line 469 "mof.y"
	{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property);
    }
break;
case 21:
#line 479 "mof.y"
	{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property);
    }
break;
case 22:
#line 489 "mof.y"
	{
        if (CheckPropertyValueConstraints(yystack.l_mark[0].property) != 0)
        {
            YYABORT;
        }

        if (FindProperty(&yystack.l_mark[-1].featureList.propertySet, yystack.l_mark[0].property->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", yystack.l_mark[0].property->name);
            YYABORT;
        }

        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property);
    }
break;
case 23:
#line 507 "mof.y"
	{
        if (FindMethod(&yystack.l_mark[-1].featureList.methodList, yystack.l_mark[0].methodDecl->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", yystack.l_mark[0].methodDecl->name);
            YYABORT;
        }

        yystack.l_mark[0].methodDecl->flags = MI_FLAG_METHOD;
        yystack.l_mark[0].methodDecl->flags |= GetQualFlags(yystack.l_mark[0].methodDecl->qualifiers, yystack.l_mark[0].methodDecl->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.methodList, yystack.l_mark[0].methodDecl);
    }
break;
case 24:
#line 520 "mof.y"
	{
        if (FindProperty(&yystack.l_mark[-1].featureList.propertySet, yystack.l_mark[0].property->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", yystack.l_mark[0].property->name);
            YYABORT;
        }

        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property);
    }
break;
case 25:
#line 533 "mof.y"
	{
        if (FindProperty(&yystack.l_mark[-1].featureList.propertySet, yystack.l_mark[0].property->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", yystack.l_mark[0].property->name);
            YYABORT;
        }
        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property);
    }
break;
case 26:
#line 545 "mof.y"
	{
        if (FindProperty(&yystack.l_mark[-1].featureList.propertySet, yystack.l_mark[0].property->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", yystack.l_mark[0].property->name);
            YYABORT;
        }

        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property);
    }
break;
case 27:
#line 558 "mof.y"
	{
        if (FindProperty(&yystack.l_mark[-1].featureList.propertySet, yystack.l_mark[0].property->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", yystack.l_mark[0].property->name);
            YYABORT;
        }

        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property);
    }
break;
case 28:
#line 573 "mof.y"
	{
        yyval.qualifierList = yystack.l_mark[-1].qualifierList;
    }
break;
case 29:
#line 579 "mof.y"
	{
        yyval.qualifierList.data = NULL;
        yyval.qualifierList.size = 0;
        PtrArray_Append((PtrArray*)&yyval.qualifierList, yystack.l_mark[0].qualifier);
    }
break;
case 30:
#line 585 "mof.y"
	{
        if (FindQualifier(&yystack.l_mark[-2].qualifierList, yystack.l_mark[0].qualifier->name))
        {
            yyerrorf(ID_DUPLICATE_QUALIFIER, 
                "duplicate qualifier: \"%s\"", yystack.l_mark[0].qualifier->name);
            YYABORT;
        }

        PtrArray_Append((PtrArray*)&yyval.qualifierList, yystack.l_mark[0].qualifier);
    }
break;
case 31:
#line 598 "mof.y"
	{
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;

        qd = FindQualifierDeclaration(yystack.l_mark[0].string);

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", yystack.l_mark[0].string);
            YYABORT;
        }

        if (qd->type != MI_BOOLEAN)
        {
            yyerrorf(ID_MISSING_QUALIFIER_INITIALIZER, 
                "qualifier is missing initializer: \"%s\"", yystack.l_mark[0].string);
            YYABORT;
        }
        
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = qd->flavor;
        q->value = NewTrueValue();
        yyval.qualifier = q;
    }
break;
case 32:
#line 626 "mof.y"
	{
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;
        void* value;

        qd = FindQualifierDeclaration(yystack.l_mark[-1].string);

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", yystack.l_mark[-1].string);
            YYABORT;
        }

        if (InitializerToValue(&yystack.l_mark[0].initializer, qd->type, &value) != 0)
        {
            yyerrorf(ID_INVALID_QUALIFIER_INITIALIZER, 
                "invalid initializer for qualifer: \"%s\"", yystack.l_mark[-1].string);
            YYABORT;
        }
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = qd->flavor;
        q->value = value;
        yyval.qualifier = q;
    }
break;
case 33:
#line 654 "mof.y"
	{
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;

        qd = FindQualifierDeclaration(yystack.l_mark[-2].string);

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", yystack.l_mark[-2].string);
            YYABORT;
        }

        if (qd->type != MI_BOOLEAN)
        {
            yyerrorf(ID_MISSING_QUALIFIER_INITIALIZER, 
                "qualifier is missing initializer: \"%s\"", yystack.l_mark[-2].string);
            YYABORT;
        }
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = PropagateFlavors(yystack.l_mark[0].flags, qd->flavor);
        q->value = NewTrueValue();
        yyval.qualifier = q;
    }
break;
case 34:
#line 681 "mof.y"
	{
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;
        void* value;

        qd = FindQualifierDeclaration(yystack.l_mark[-3].string);

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", yystack.l_mark[-3].string);
            YYABORT;
        }

        if (InitializerToValue(&yystack.l_mark[-2].initializer, qd->type, &value) != 0)
        {
            yyerrorf(ID_INVALID_QUALIFIER_INITIALIZER, 
                "invalid initializer for qualifer: \"%s\"", yystack.l_mark[-3].string);
            YYABORT;
        }
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->value = value;
        q->flavor = PropagateFlavors(yystack.l_mark[0].flags, qd->flavor);
        yyval.qualifier = q;
    }
break;
case 35:
#line 711 "mof.y"
	{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yystack.l_mark[-1].constantValue;
        yyval.initializer.size = 1;
    }
break;
case 36:
#line 718 "mof.y"
	{
        yyval.initializer = yystack.l_mark[0].initializer;
    }
break;
case 37:
#line 724 "mof.y"
	{
        yyval.flags = yystack.l_mark[0].flags;
    }
break;
case 38:
#line 728 "mof.y"
	{
        yyval.flags |= yystack.l_mark[0].flags;
    }
break;
case 39:
#line 734 "mof.y"
	{
        yyval.flags = yystack.l_mark[0].flags;
    }
break;
case 40:
#line 738 "mof.y"
	{
        yyval.flags |= yystack.l_mark[0].flags;
    }
break;
case 41:
#line 744 "mof.y"
	{
        yyval.flags = MI_FLAG_ENABLEOVERRIDE;
    }
break;
case 42:
#line 748 "mof.y"
	{
        yyval.flags = MI_FLAG_DISABLEOVERRIDE;
    }
break;
case 43:
#line 752 "mof.y"
	{
        yyval.flags = MI_FLAG_RESTRICTED;
    }
break;
case 44:
#line 756 "mof.y"
	{
        yyval.flags = MI_FLAG_TOSUBCLASS;
    }
break;
case 45:
#line 760 "mof.y"
	{
        yyval.flags = MI_FLAG_TOINSTANCE;
        if (state.extensionsEnabled == MI_FALSE)
        {
            yyerrorf(ID_UNSUPPORTED, "Unsupported flavor: ToInstance");
            YYABORT;
        }
    }
break;
case 46:
#line 769 "mof.y"
	{
        yyval.flags = MI_FLAG_TRANSLATABLE;
    }
break;
case 47:
#line 775 "mof.y"
	{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->type = yystack.l_mark[-2].type;
    }
break;
case 48:
#line 781 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PROPERTY, &yystack.l_mark[-3].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->type = yystack.l_mark[-2].type;
        yyval.property->qualifiers = yystack.l_mark[-3].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-3].qualifierList.size;
    }
break;
case 49:
#line 793 "mof.y"
	{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->type = ARRAYOF(yystack.l_mark[-3].type);
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-1].integer;
    }
break;
case 50:
#line 800 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PROPERTY, &yystack.l_mark[-4].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->type = ARRAYOF(yystack.l_mark[-3].type);
        yyval.property->qualifiers = yystack.l_mark[-4].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-4].qualifierList.size;
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-1].integer;
    }
break;
case 51:
#line 813 "mof.y"
	{
        void* value;

        if (InitializerToValue(&yystack.l_mark[-1].initializer, yystack.l_mark[-4].type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->type = yystack.l_mark[-4].type;
        yyval.property->value = value;
    }
break;
case 52:
#line 828 "mof.y"
	{
        void* value;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PROPERTY, &yystack.l_mark[-5].qualifierList) != 0)
            YYABORT;

        if (InitializerToValue(&yystack.l_mark[-1].initializer, yystack.l_mark[-4].type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->type = yystack.l_mark[-4].type;
        yyval.property->qualifiers = yystack.l_mark[-5].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-5].qualifierList.size;
        yyval.property->value = value;
    }
break;
case 53:
#line 849 "mof.y"
	{
        void* value;

        if (InitializerToValue(&yystack.l_mark[-1].initializer, ARRAYOF(yystack.l_mark[-5].type), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-4].string;
        yyval.property->type = ARRAYOF(yystack.l_mark[-5].type);
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-3].integer;
        yyval.property->value = value;
    }
break;
case 54:
#line 865 "mof.y"
	{
        void* value;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PROPERTY, &yystack.l_mark[-6].qualifierList) != 0)
            YYABORT;

        if (InitializerToValue(&yystack.l_mark[-1].initializer, ARRAYOF(yystack.l_mark[-5].type), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-4].string;
        yyval.property->type = ARRAYOF(yystack.l_mark[-5].type);
        yyval.property->qualifiers = yystack.l_mark[-6].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-6].qualifierList.size;
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-3].integer;
        yyval.property->value = value;
    }
break;
case 55:
#line 889 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-2].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-2].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->className = cd->name;
    }
break;
case 56:
#line 906 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-2].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-2].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yystack.l_mark[-3].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->className = cd->name;
        yyval.property->qualifiers = yystack.l_mark[-3].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-3].qualifierList.size;
    }
break;
case 57:
#line 929 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-3].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-3].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-1].integer;
    }
break;
case 58:
#line 947 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-3].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-3].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yystack.l_mark[-4].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-1].integer;
        yyval.property->qualifiers = yystack.l_mark[-4].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-4].qualifierList.size;
    }
break;
case 59:
#line 971 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-4].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-4].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->className = cd->name;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
break;
case 60:
#line 990 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-4].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-4].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yystack.l_mark[-5].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->className = cd->name;
        yyval.property->qualifiers = yystack.l_mark[-5].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-5].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
break;
case 61:
#line 1015 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-5].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-5].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yystack.l_mark[-4].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-3].integer;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
break;
case 62:
#line 1035 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-5].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-5].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yystack.l_mark[-6].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yystack.l_mark[-4].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-3].integer;
        yyval.property->qualifiers = yystack.l_mark[-6].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-6].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
break;
case 63:
#line 1063 "mof.y"
	{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->className = "?";
    }
break;
case 64:
#line 1072 "mof.y"
	{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->className = "?";
        yyval.property->qualifiers = yystack.l_mark[-3].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-3].qualifierList.size;
    }
break;
case 65:
#line 1083 "mof.y"
	{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->className = "?";
        yyval.property->subscript = 0;
    }
break;
case 66:
#line 1093 "mof.y"
	{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->className = "?";
        yyval.property->subscript = 0;
        yyval.property->qualifiers = yystack.l_mark[-4].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-4].qualifierList.size;
    }
break;
case 67:
#line 1105 "mof.y"
	{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->className = "?";
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
break;
case 68:
#line 1116 "mof.y"
	{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCE;
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->className = "?";
        yyval.property->qualifiers = yystack.l_mark[-5].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-5].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
break;
case 69:
#line 1129 "mof.y"
	{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yystack.l_mark[-4].string;
        yyval.property->className = "?";
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-3].integer;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
break;
case 70:
#line 1141 "mof.y"
	{
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_INSTANCEA;
        yyval.property->name = yystack.l_mark[-4].string;
        yyval.property->className = "?";
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-3].integer;
        yyval.property->qualifiers = yystack.l_mark[-6].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-6].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
break;
case 71:
#line 1157 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-3].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-3].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->className = cd->name;
    }
break;
case 72:
#line 1174 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-3].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-3].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yystack.l_mark[-4].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->className = cd->name;
        yyval.property->qualifiers = yystack.l_mark[-4].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-4].qualifierList.size;
    }
break;
case 73:
#line 1197 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-5].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-5].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->className = cd->name;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* [TODO: use initializer */
    }
break;
case 74:
#line 1216 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-5].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-5].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yystack.l_mark[-6].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->className = cd->name;
        yyval.property->qualifiers = yystack.l_mark[-6].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-6].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* [TODO: use initializer */
    }
break;
case 75:
#line 1241 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-4].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-4].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-1].integer;
    }
break;
case 76:
#line 1259 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-4].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-4].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yystack.l_mark[-5].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-1].integer;
        yyval.property->qualifiers = yystack.l_mark[-5].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-5].qualifierList.size;
    }
break;
case 77:
#line 1283 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-6].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-6].string);
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yystack.l_mark[-4].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-3].integer;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
break;
case 78:
#line 1303 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-6].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-6].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yystack.l_mark[-7].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yystack.l_mark[-4].string;
        yyval.property->className = cd->name;
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-3].integer;
        yyval.property->qualifiers = yystack.l_mark[-7].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-7].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
break;
case 79:
#line 1331 "mof.y"
	{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->className = "?";
    }
break;
case 80:
#line 1338 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yystack.l_mark[-4].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->className = "?";
        yyval.property->qualifiers = yystack.l_mark[-4].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-4].qualifierList.size;
    }
break;
case 81:
#line 1351 "mof.y"
	{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->className = "?";
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-1].integer;
    }
break;
case 82:
#line 1359 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yystack.l_mark[-5].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->className = "?";
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-1].integer;
        yyval.property->qualifiers = yystack.l_mark[-5].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-5].qualifierList.size;
    }
break;
case 83:
#line 1373 "mof.y"
	{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->className = "?";
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
break;
case 84:
#line 1382 "mof.y"
	{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yystack.l_mark[-4].string;
        yyval.property->className = "?";
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-3].integer;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
break;
case 85:
#line 1392 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yystack.l_mark[-6].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->className = "?";
        yyval.property->qualifiers = yystack.l_mark[-6].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-6].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
	}
break;
case 86:
#line 1407 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &yystack.l_mark[-7].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCEA;
        yyval.property->name = yystack.l_mark[-4].string;
        yyval.property->className = "?";
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-3].integer;
        yyval.property->qualifiers = yystack.l_mark[-7].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-7].qualifierList.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
	}
break;
case 87:
#line 1425 "mof.y"
	{
        yyval.methodDecl = CALLOC_T(MI_MethodDecl, 1);
        yyval.methodDecl->name = yystack.l_mark[-4].string;
        yyval.methodDecl->parameters = yystack.l_mark[-2].parameterList.data;
        yyval.methodDecl->numParameters = yystack.l_mark[-2].parameterList.size;
        yyval.methodDecl->returnType = yystack.l_mark[-5].type;
    }
break;
case 88:
#line 1433 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_METHOD, &yystack.l_mark[-6].qualifierList) != 0)
            YYABORT;

        yyval.methodDecl = CALLOC_T(MI_MethodDecl, 1);
        yyval.methodDecl->name = yystack.l_mark[-4].string;
        yyval.methodDecl->parameters = yystack.l_mark[-2].parameterList.data;
        yyval.methodDecl->numParameters = yystack.l_mark[-2].parameterList.size;
        yyval.methodDecl->qualifiers = yystack.l_mark[-6].qualifierList.data;
        yyval.methodDecl->numQualifiers = yystack.l_mark[-6].qualifierList.size;
        yyval.methodDecl->returnType = yystack.l_mark[-5].type;
    }
break;
case 89:
#line 1447 "mof.y"
	{
        MOF_ParameterList parameterList = PTRARRAY_INITIALIZER;

        yyval.methodDecl = CALLOC_T(MI_MethodDecl, 1);
        yyval.methodDecl->name = yystack.l_mark[-3].string;
        yyval.methodDecl->parameters = parameterList.data;
        yyval.methodDecl->numParameters = parameterList.size;
        yyval.methodDecl->returnType = yystack.l_mark[-4].type;
    }
break;
case 90:
#line 1457 "mof.y"
	{
        MOF_ParameterList parameterList = PTRARRAY_INITIALIZER;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_METHOD, &yystack.l_mark[-5].qualifierList) != 0)
            YYABORT;

        yyval.methodDecl = CALLOC_T(MI_MethodDecl, 1);
        yyval.methodDecl->name = yystack.l_mark[-3].string;
        yyval.methodDecl->parameters = parameterList.data;
        yyval.methodDecl->numParameters = parameterList.size;
        yyval.methodDecl->qualifiers = yystack.l_mark[-5].qualifierList.data;
        yyval.methodDecl->numQualifiers = yystack.l_mark[-5].qualifierList.size;
        yyval.methodDecl->returnType = yystack.l_mark[-4].type;
    }
break;
case 91:
#line 1475 "mof.y"
	{
        yystack.l_mark[0].parameter->flags = MI_FLAG_PARAMETER;
        yystack.l_mark[0].parameter->flags |= GetQualFlags(yystack.l_mark[0].parameter->qualifiers, yystack.l_mark[0].parameter->numQualifiers);
        yyval.parameterList.data = NULL;
        yyval.parameterList.size = 0;
        PtrArray_Append((PtrArray*)&yyval.parameterList, yystack.l_mark[0].parameter);
    }
break;
case 92:
#line 1483 "mof.y"
	{
        if (FindParameter(&yystack.l_mark[-2].parameterList, yystack.l_mark[0].parameter->name))
        {
            yyerrorf(ID_PARAMETER_ALREADY_DEFINED, 
                "parameter already defined: \"%s\"", yystack.l_mark[0].parameter->name);
            YYABORT;
        }

        yystack.l_mark[0].parameter->flags = MI_FLAG_PARAMETER;
        yystack.l_mark[0].parameter->flags |= GetQualFlags(yystack.l_mark[0].parameter->qualifiers, yystack.l_mark[0].parameter->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.parameterList, yystack.l_mark[0].parameter);
    }
break;
case 93:
#line 1498 "mof.y"
	{
        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[0].string;
        yyval.parameter->type = yystack.l_mark[-1].type;
    }
break;
case 94:
#line 1504 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-2].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-2].string);
            YYABORT;
        }

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[0].string;
        yyval.parameter->type = MI_REFERENCE;
        yyval.parameter->className = cd->name;
    }
break;
case 95:
#line 1521 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &yystack.l_mark[-2].qualifierList) != 0)
            YYABORT;

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[0].string;
        yyval.parameter->type = yystack.l_mark[-1].type;
        yyval.parameter->qualifiers = yystack.l_mark[-2].qualifierList.data;
        yyval.parameter->numQualifiers = yystack.l_mark[-2].qualifierList.size;
    }
break;
case 96:
#line 1533 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-2].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-2].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &yystack.l_mark[-3].qualifierList) != 0)
            YYABORT;

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[0].string;
        yyval.parameter->type = MI_REFERENCE;
        yyval.parameter->className = cd->name;
        yyval.parameter->qualifiers = yystack.l_mark[-3].qualifierList.data;
        yyval.parameter->numQualifiers = yystack.l_mark[-3].qualifierList.size;
    }
break;
case 97:
#line 1556 "mof.y"
	{
        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[-1].string;
        yyval.parameter->type = ARRAYOF(yystack.l_mark[-2].type);
        yyval.parameter->subscript = (MI_Uint32)yystack.l_mark[0].integer;
    }
break;
case 98:
#line 1563 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-3].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-3].string);
            YYABORT;
        }

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[-1].string;
        yyval.parameter->type = ARRAYOF(MI_REFERENCE);
        yyval.parameter->className = cd->name;
        yyval.parameter->subscript = (MI_Uint32)yystack.l_mark[0].integer;
    }
break;
case 99:
#line 1581 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &yystack.l_mark[-3].qualifierList) != 0)
            YYABORT;

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[-1].string;
        yyval.parameter->type = ARRAYOF(yystack.l_mark[-2].type);
        yyval.parameter->subscript = (MI_Uint32)yystack.l_mark[0].integer;
        yyval.parameter->qualifiers = yystack.l_mark[-3].qualifierList.data;
        yyval.parameter->numQualifiers = yystack.l_mark[-3].qualifierList.size;
    }
break;
case 100:
#line 1594 "mof.y"
	{
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl(yystack.l_mark[-3].string);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", yystack.l_mark[-3].string);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &yystack.l_mark[-4].qualifierList) != 0)
            YYABORT;

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[-1].string;
        yyval.parameter->type = ARRAYOF(MI_REFERENCE);
        yyval.parameter->className = cd->name;
        yyval.parameter->subscript = (MI_Uint32)yystack.l_mark[0].integer;
        yyval.parameter->qualifiers = yystack.l_mark[-4].qualifierList.data;
        yyval.parameter->numQualifiers = yystack.l_mark[-4].qualifierList.size;
    }
break;
case 101:
#line 1620 "mof.y"
	{
        if (yystack.l_mark[-1].integer <= 0)
        {
            yyerrorf(ID_ILLEGAL_ARRAY_SUBSCRIPT, 
                "illegal array subscript: " SINT64_FMT, yystack.l_mark[-1].integer);
            YYABORT;
        }

        yyval.integer = yystack.l_mark[-1].integer;
    }
break;
case 102:
#line 1631 "mof.y"
	{
        /* 0 signifies a dynamic array */
        yyval.integer = 0;
    }
break;
case 103:
#line 1638 "mof.y"
	{
        yyval.initializer = yystack.l_mark[0].initializer;
    }
break;
case 104:
#line 1642 "mof.y"
	{
        yyval.initializer = yystack.l_mark[0].initializer;
    }
break;
case 105:
#line 1648 "mof.y"
	{
        yyval.initializer = yystack.l_mark[-1].initializer;
    }
break;
case 106:
#line 1652 "mof.y"
	{
        yyval.initializer.data = NULL;
        yyval.initializer.size = 0;
        yyval.initializer.isArray = 1;
    }
break;
case 107:
#line 1660 "mof.y"
	{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yystack.l_mark[0].initializer.data[0];
        yyval.initializer.size = 1;
        yyval.initializer.isArray = 1;
    }
break;
case 108:
#line 1668 "mof.y"
	{
        yystack.l_mark[-2].initializer.data = REALLOC_T(MOF_ConstantValue, yystack.l_mark[-2].initializer.data, yystack.l_mark[-2].initializer.size + 1);
        yystack.l_mark[-2].initializer.data[yystack.l_mark[-2].initializer.size] = yystack.l_mark[0].initializer.data[0];
        yystack.l_mark[-2].initializer.size++;
        yyval.initializer = yystack.l_mark[-2].initializer;
    }
break;
case 109:
#line 1677 "mof.y"
	{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yystack.l_mark[0].constantValue;
        yyval.initializer.size = 1;
    }
break;
case 110:
#line 1684 "mof.y"
	{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0].type = TOK_STRING_VALUE;
        yyval.initializer.data[0].value.string = yystack.l_mark[0].string;
        yyval.initializer.size = 1;
        /* TODO: look up alias, get and store instance decl. for alias */
    }
break;
case 111:
#line 1693 "mof.y"
	{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0].type = TOK_STRING_VALUE;
        yyval.initializer.data[0].value.string = yystack.l_mark[-3].string;
        yyval.initializer.size = 1;
        /* TODO: look up class $3, validate property names/types, store dynamic instance properties in this instance */
    }
break;
case 112:
#line 1704 "mof.y"
	{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yystack.l_mark[0].constantValue;
        yyval.initializer.size = 1;
    }
break;
case 113:
#line 1711 "mof.y"
	{
        yyval.initializer = yystack.l_mark[0].initializer;
    }
break;
case 114:
#line 1717 "mof.y"
	{
        yyval.initializer = yystack.l_mark[-1].initializer;
    }
break;
case 115:
#line 1721 "mof.y"
	{
        yyval.initializer.data = NULL;
        yyval.initializer.size = 0;
        yyval.initializer.isArray = MI_TRUE;
    }
break;
case 116:
#line 1729 "mof.y"
	{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yystack.l_mark[0].constantValue;
        yyval.initializer.size = 1;
        yyval.initializer.isArray = MI_TRUE;
    }
break;
case 117:
#line 1737 "mof.y"
	{
        yystack.l_mark[-2].initializer.data = REALLOC_T(MOF_ConstantValue, yystack.l_mark[-2].initializer.data, yystack.l_mark[-2].initializer.size + 1);
        yystack.l_mark[-2].initializer.data[yystack.l_mark[-2].initializer.size] = yystack.l_mark[0].constantValue;
        yystack.l_mark[-2].initializer.size++;
        yystack.l_mark[-2].initializer.isArray = MI_TRUE;
        yyval.initializer = yystack.l_mark[-2].initializer;
    }
break;
case 118:
#line 1747 "mof.y"
	{
        yyval.constantValue.type = TOK_INTEGER_VALUE;
        yyval.constantValue.value.integer = yystack.l_mark[0].integer;
    }
break;
case 119:
#line 1752 "mof.y"
	{
        yyval.constantValue.type = TOK_REAL_VALUE;
        yyval.constantValue.value.real = yystack.l_mark[0].real;
    }
break;
case 120:
#line 1757 "mof.y"
	{
        yyval.constantValue.type = TOK_CHAR_VALUE;
        yyval.constantValue.value.character = yystack.l_mark[0].character;
    }
break;
case 121:
#line 1762 "mof.y"
	{
        yyval.constantValue.type = TOK_STRING_VALUE;
        yyval.constantValue.value.string = yystack.l_mark[0].string;
    }
break;
case 122:
#line 1767 "mof.y"
	{
        yyval.constantValue.type = TOK_BOOLEAN_VALUE;
        yyval.constantValue.value.boolean = yystack.l_mark[0].boolean;
    }
break;
case 123:
#line 1772 "mof.y"
	{
        yyval.constantValue.type = TOK_NULL;
    }
break;
case 124:
#line 1778 "mof.y"
	{
	yyval.string = yystack.l_mark[0].string;
    }
break;
case 125:
#line 1782 "mof.y"
	{
        size_t size = strlen(yystack.l_mark[-1].string) + strlen(yystack.l_mark[0].string) + 1;
        yyval.string = (char*)MOF_Realloc(&state.heap, yystack.l_mark[-1].string, size);
        Strcat(yyval.string, size, yystack.l_mark[0].string);
        MOF_Free(&state.heap, yystack.l_mark[0].string);
    }
break;
case 126:
#line 1791 "mof.y"
	{
        yystack.l_mark[-2].qualifierDeclaration->name = yystack.l_mark[-3].string;
        yystack.l_mark[-2].qualifierDeclaration->scope = yystack.l_mark[-1].flags;
        yystack.l_mark[-2].qualifierDeclaration->flavor = 0;
        yyval.qualifierDeclaration = yystack.l_mark[-2].qualifierDeclaration;
    }
break;
case 127:
#line 1798 "mof.y"
	{
        yystack.l_mark[-3].qualifierDeclaration->name = yystack.l_mark[-4].string;
        yystack.l_mark[-3].qualifierDeclaration->scope = yystack.l_mark[-2].flags;
        yystack.l_mark[-3].qualifierDeclaration->flavor = yystack.l_mark[-1].flags;
        yyval.qualifierDeclaration = yystack.l_mark[-3].qualifierDeclaration;
    }
break;
case 128:
#line 1807 "mof.y"
	{
        yyval.qualifierDeclaration = CALLOC_T(MI_QualifierDecl, 1);
        yyval.qualifierDeclaration->type = yystack.l_mark[0].type;
    }
break;
case 129:
#line 1812 "mof.y"
	{
        void* value;

        if (InitializerToValue(&yystack.l_mark[0].initializer, yystack.l_mark[-2].type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.qualifierDeclaration = CALLOC_T(MI_QualifierDecl, 1);
        yyval.qualifierDeclaration->type = yystack.l_mark[-2].type;
        yyval.qualifierDeclaration->value = value;
        ReleaseInitializer(&yystack.l_mark[0].initializer);
    }
break;
case 130:
#line 1827 "mof.y"
	{
        yyval.qualifierDeclaration = CALLOC_T(MI_QualifierDecl, 1);
        yyval.qualifierDeclaration->type = ARRAYOF(yystack.l_mark[-1].type);
        yyval.qualifierDeclaration->subscript = (MI_Uint32)yystack.l_mark[0].integer;
    }
break;
case 131:
#line 1833 "mof.y"
	{
        void* value = NULL;

        if (InitializerToValue(&yystack.l_mark[0].initializer, ARRAYOF(yystack.l_mark[-3].type), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.qualifierDeclaration = CALLOC_T(MI_QualifierDecl, 1);
        yyval.qualifierDeclaration->type = ARRAYOF(yystack.l_mark[-3].type);
        yyval.qualifierDeclaration->subscript = (MI_Uint32)yystack.l_mark[-2].integer;
        yyval.qualifierDeclaration->value = value;
        ReleaseInitializer(&yystack.l_mark[0].initializer);
    }
break;
case 132:
#line 1851 "mof.y"
	{
        yyval.flags = yystack.l_mark[-1].flags;
    }
break;
case 133:
#line 1857 "mof.y"
	{
        yyval.flags = yystack.l_mark[0].flags;
    }
break;
case 134:
#line 1861 "mof.y"
	{
        yyval.flags |= yystack.l_mark[0].flags;
    }
break;
case 135:
#line 1867 "mof.y"
	{
        yyval.flags = MI_FLAG_CLASS;
    }
break;
case 136:
#line 1871 "mof.y"
	{
        yyval.flags = MI_FLAG_ASSOCIATION;
    }
break;
case 137:
#line 1875 "mof.y"
	{
        yyval.flags = MI_FLAG_INDICATION;
    }
break;
case 138:
#line 1879 "mof.y"
	{
        yyval.flags = MI_FLAG_PROPERTY;
    }
break;
case 139:
#line 1883 "mof.y"
	{
        yyval.flags = MI_FLAG_REFERENCE;
    }
break;
case 140:
#line 1887 "mof.y"
	{
        yyval.flags = MI_FLAG_METHOD;
    }
break;
case 141:
#line 1891 "mof.y"
	{
        yyval.flags = MI_FLAG_PARAMETER;
    }
break;
case 142:
#line 1895 "mof.y"
	{
        yyval.flags = MI_FLAG_ANY;
    }
break;
case 143:
#line 1901 "mof.y"
	{
        /* Reject incompatiable ToSubclass and Restricted flavors */
        if (yystack.l_mark[-1].flags & MI_FLAG_TOSUBCLASS && yystack.l_mark[-1].flags & MI_FLAG_RESTRICTED)
        {
            yyerrorf(ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s", 
                "ToSubclass", "Restricted");
            YYABORT;
        }

        /* Reject incompatiable EnableOverride and DisableOverride flavors */
        if (yystack.l_mark[-1].flags & MI_FLAG_ENABLEOVERRIDE && yystack.l_mark[-1].flags & MI_FLAG_DISABLEOVERRIDE)
        {
            yyerrorf(ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s", 
                "EnableOverride", "DisableOverride");
            YYABORT;
        }

        yyval.flags = yystack.l_mark[-1].flags;
    }
break;
case 144:
#line 1923 "mof.y"
	{
        yyval.instanceDeclaration = CALLOC_T(MI_InstanceDecl, 1);
        yyval.instanceDeclaration->flags = 0;
        yyval.instanceDeclaration->name = yystack.l_mark[-1].string;
        yyval.instanceDeclaration->properties = yystack.l_mark[0].featureList.propertySet.data;
        yyval.instanceDeclaration->numProperties = yystack.l_mark[0].featureList.propertySet.size;
    }
break;
case 145:
#line 1931 "mof.y"
	{
        yyval.instanceDeclaration = CALLOC_T(MI_InstanceDecl, 1);
        yyval.instanceDeclaration->flags = 0;
        yyval.instanceDeclaration->name = yystack.l_mark[-1].string;
        yyval.instanceDeclaration->properties = yystack.l_mark[0].featureList.propertySet.data;
        yyval.instanceDeclaration->numProperties = yystack.l_mark[0].featureList.propertySet.size;
        yyval.instanceDeclaration->qualifiers = yystack.l_mark[-4].qualifierList.data;
        yyval.instanceDeclaration->numQualifiers = yystack.l_mark[-4].qualifierList.size;
    }
break;
case 146:
#line 1941 "mof.y"
	{
        /* [TODO]: handle alias */
        yyval.instanceDeclaration = CALLOC_T(MI_InstanceDecl, 1);
        yyval.instanceDeclaration->flags = 0;
        yyval.instanceDeclaration->name = yystack.l_mark[-2].string;
        yyval.instanceDeclaration->properties = yystack.l_mark[0].featureList.propertySet.data;
        yyval.instanceDeclaration->numProperties = yystack.l_mark[0].featureList.propertySet.size;
    }
break;
case 147:
#line 1950 "mof.y"
	{
        /* [TODO]: handle alias */
        yyval.instanceDeclaration = CALLOC_T(MI_InstanceDecl, 1);
        yyval.instanceDeclaration->flags = 0;
        yyval.instanceDeclaration->name = yystack.l_mark[-2].string;
        yyval.instanceDeclaration->properties = yystack.l_mark[0].featureList.propertySet.data;
        yyval.instanceDeclaration->numProperties = yystack.l_mark[0].featureList.propertySet.size;
        yyval.instanceDeclaration->qualifiers = yystack.l_mark[-5].qualifierList.data;
        yyval.instanceDeclaration->numQualifiers = yystack.l_mark[-5].qualifierList.size;
    }
break;
case 148:
#line 1963 "mof.y"
	{
        yyval.featureList = yystack.l_mark[-2].featureList;
    }
break;
case 149:
#line 1967 "mof.y"
	{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
    }
break;
case 150:
#line 1976 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 151:
#line 1982 "mof.y"
	{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property);
    }
break;
case 152:
#line 1990 "mof.y"
	{
        if (FindProperty(&yystack.l_mark[-1].featureList.propertySet, yystack.l_mark[0].property->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "instance property already defined: \"%s\"", yystack.l_mark[0].property->name);
            YYABORT;
        }

        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        PtrArray_Append((PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property);
    }
break;
case 153:
#line 2005 "mof.y"
	{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->type = TOK_NULL;
    }
break;
case 154:
#line 2011 "mof.y"
	{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->type = TOK_NULL;
        yyval.property->qualifiers = yystack.l_mark[-2].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-2].qualifierList.size;
    }
break;
case 155:
#line 2019 "mof.y"
	{
        void* value;
        MI_Type type = InitializerToType(&yystack.l_mark[-1].initializer);
        if (InitializerToValue(&yystack.l_mark[-1].initializer, type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->type = type;
        yyval.property->value = value;
    }
break;
case 156:
#line 2034 "mof.y"
	{
        void* value;
        MI_Type type = InitializerToType(&yystack.l_mark[-1].initializer);

        if (InitializerToValue(&yystack.l_mark[-1].initializer, type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->type = type;
        yyval.property->value = value;
        yyval.property->qualifiers = yystack.l_mark[-4].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-4].qualifierList.size;
    }
break;
case 157:
#line 2054 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 158:
#line 2058 "mof.y"
	{
        yyval.string = "Object";
    }
break;
case 159:
#line 2062 "mof.y"
	{
        yyval.string = "Boolean";
    }
break;
case 160:
#line 2066 "mof.y"
	{
        yyval.string = "Datetime";
    }
break;
case 161:
#line 2070 "mof.y"
	{
        yyval.string = "String";
    }
break;
case 162:
#line 2080 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 163:
#line 2084 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 164:
#line 2088 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 165:
#line 2092 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 166:
#line 2096 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 167:
#line 2100 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 168:
#line 2104 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 169:
#line 2108 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 170:
#line 2112 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 171:
#line 2116 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 172:
#line 2120 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 173:
#line 2124 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 174:
#line 2128 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 175:
#line 2132 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 176:
#line 2138 "mof.y"
	{
        yyval.type = MI_BOOLEAN;
    }
break;
case 177:
#line 2142 "mof.y"
	{
        yyval.type = MI_SINT8;
    }
break;
case 178:
#line 2146 "mof.y"
	{
        yyval.type = MI_UINT8;
    }
break;
case 179:
#line 2150 "mof.y"
	{
        yyval.type = MI_SINT16;
    }
break;
case 180:
#line 2154 "mof.y"
	{
        yyval.type = MI_UINT16;
    }
break;
case 181:
#line 2158 "mof.y"
	{
        yyval.type = MI_SINT32;
    }
break;
case 182:
#line 2162 "mof.y"
	{
        yyval.type = MI_UINT32;
    }
break;
case 183:
#line 2166 "mof.y"
	{
        yyval.type = MI_SINT64;
    }
break;
case 184:
#line 2170 "mof.y"
	{
        yyval.type = MI_UINT64;
    }
break;
case 185:
#line 2174 "mof.y"
	{
        yyval.type = MI_REAL32;
    }
break;
case 186:
#line 2178 "mof.y"
	{
        yyval.type = MI_REAL64;
    }
break;
case 187:
#line 2182 "mof.y"
	{
        yyval.type = MI_CHAR16;
    }
break;
case 188:
#line 2186 "mof.y"
	{
        yyval.type = MI_DATETIME;
    }
break;
case 189:
#line 2190 "mof.y"
	{
        yyval.type = MI_STRING;
    }
break;
#line 3296 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
