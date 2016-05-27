#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20100216

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)


#ifndef yyparse
#define yyparse    mofparse
#endif /* yyparse */

#ifndef yylex
#define yylex      moflex
#endif /* yylex */

#ifndef yyerror
#define yyerror    moferror
#endif /* yyerror */

#ifndef yychar
#define yychar     mofchar
#endif /* yychar */

#ifndef yyval
#define yyval      mofval
#endif /* yyval */

#ifndef yylval
#define yylval     moflval
#endif /* yylval */

#ifndef yydebug
#define yydebug    mofdebug
#endif /* yydebug */

#ifndef yynerrs
#define yynerrs    mofnerrs
#endif /* yynerrs */

#ifndef yyerrflag
#define yyerrflag  moferrflag
#endif /* yyerrflag */

#ifndef yylhs
#define yylhs      moflhs
#endif /* yylhs */

#ifndef yylen
#define yylen      moflen
#endif /* yylen */

#ifndef yydefred
#define yydefred   mofdefred
#endif /* yydefred */

#ifndef yydgoto
#define yydgoto    mofdgoto
#endif /* yydgoto */

#ifndef yysindex
#define yysindex   mofsindex
#endif /* yysindex */

#ifndef yyrindex
#define yyrindex   mofrindex
#endif /* yyrindex */

#ifndef yygindex
#define yygindex   mofgindex
#endif /* yygindex */

#ifndef yytable
#define yytable    moftable
#endif /* yytable */

#ifndef yycheck
#define yycheck    mofcheck
#endif /* yycheck */

#ifndef yyname
#define yyname     mofname
#endif /* yyname */

#ifndef yyrule
#define yyrule     mofrule
#endif /* yyrule */
#define YYPREFIX "mof"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
#ifdef YYPARSE_PARAM_TYPE
#define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
#else
#define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
#endif
#else
#define YYPARSE_DECL() yyparse(void)
#endif /* YYPARSE_PARAM */

extern int YYPARSE_DECL();

#line 1 "mof.y"


#include "mofy.redef.h"
#include "mofcommon.h"
#include "buffer.h"
#include "types.h"
#include "ptrarray.h"
#include "utility.h"

#define ARRAYOF(TYPE) ((MI_Uint32)TYPE | (MI_Uint32)MI_ARRAY_BIT)

extern int moflex(MOF_State *state);
//extern int openIncludeFile(const MI_Char* path);

#ifndef _mofy_tab_h
#line 17 "mof.y"
typedef union
{
    MI_Boolean boolean;
    MI_Sint64 integer;
    MI_Real64 real;
    MI_Char16 character;
    MI_Char* string;
    MI_Char* identifier;
    MI_Char* dollarIdentifier;
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
#line 154 "mofy.tab.c"
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
#define TOK_BOOLEAN_VALUE 272
#define TOK_REF 273
#define TOK_SCOPE 274
#define TOK_CLASS 275
#define TOK_ASSOCIATION 276
#define TOK_INDICATION 277
#define TOK_QUALIFIER 278
#define TOK_PROPERTY 279
#define TOK_REFERENCE 280
#define TOK_METHOD 281
#define TOK_PARAMETER 282
#define TOK_ANY 283
#define TOK_FLAVOR 284
#define TOK_ENABLEOVERRIDE 285
#define TOK_DISABLEOVERRIDE 286
#define TOK_RESTRICTED 287
#define TOK_TOSUBCLASS 288
#define TOK_TRANSLATABLE 289
#define TOK_INSTANCE 290
#define TOK_OF 291
#define TOK_AS 292
#define TOK_PRAGMA 293
#define TOK_SCHEMA 294
#define TOK_INTEGER_VALUE 295
#define TOK_REAL_VALUE 296
#define TOK_STRING_VALUE 297
#define TOK_CHAR_VALUE 298
#define TOK_IDENT 299
#define TOK_ALIAS_IDENTIFIER 300
#define TOK_NULL 301
#define TOK_TOINSTANCE 302
#define YYERRCODE 256
#endif
static const short moflhs[] = {                          -1,
    0,    0,    0,   35,   35,   35,   35,   36,   31,   31,
   31,   31,   13,   13,   12,   12,   12,   12,   12,   12,
   29,   28,   28,   27,   27,   27,   27,   30,   30,   25,
   25,   24,   24,   24,   24,   24,   24,    7,    7,    7,
    7,    7,    7,    7,    7,   10,   10,   10,   10,   11,
   11,   11,   11,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    3,    9,    9,
    8,    8,    8,    8,    8,    8,    8,    8,   17,   17,
   18,   18,   19,   19,   20,   20,    5,    5,    5,    5,
    5,    5,    5,    1,    1,   15,   15,   16,   16,   16,
   16,   23,   22,   22,   21,   21,   21,   21,   21,   21,
   21,   21,   26,   32,   32,   32,   32,   14,    4,   34,
   34,   33,   33,    2,    2,    2,    2,    2,
};
static const short moflen[] = {                           2,
    1,    2,    1,    1,    1,    1,    1,    5,    3,    5,
    4,    6,    4,    3,    1,    1,    1,    2,    2,    2,
    3,    1,    3,    1,    2,    3,    4,    3,    1,    1,
    3,    1,    1,    1,    1,    1,    1,    3,    4,    4,
    5,    5,    6,    6,    7,    3,    4,    4,    5,    6,
    7,    5,    6,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    2,    1,    3,
    2,    2,    3,    3,    3,    3,    4,    4,    3,    2,
    1,    1,    3,    2,    1,    3,    1,    1,    1,    1,
    1,    1,    1,    1,    2,    5,    6,    2,    4,    3,
    5,    5,    1,    3,    1,    1,    1,    1,    1,    1,
    1,    1,    5,    4,    5,    5,    6,    4,    2,    1,
    2,    4,    5,    1,    1,    1,    1,    1,
};
static const short mofdefred[] = {                        0,
    3,    0,    0,    0,    0,    0,    0,    6,    0,    5,
    7,    1,    4,  125,  126,  128,  127,  124,    0,    0,
    0,    0,    0,   22,    0,    2,    0,    0,    0,    0,
    9,    0,    0,    0,    0,    0,    0,    0,   29,    0,
   21,    0,    0,    0,    0,   54,   55,   56,   57,   58,
   59,   60,   61,   62,   63,   64,   66,   65,   67,    0,
    0,    0,    0,   15,   17,   16,    0,    0,    0,    0,
    0,    0,    0,    0,  114,   94,    0,   91,   87,   88,
   89,   93,   92,    0,    0,   32,   33,   34,   35,   36,
   37,   26,   84,   85,    0,    0,   23,    0,   11,    0,
   10,   14,   68,    0,    0,    0,   18,   20,   19,    0,
    0,    0,    0,    0,    0,   96,    0,    0,  119,    0,
    0,  120,    0,  116,   95,    8,   28,   83,    0,   27,
    0,    0,  115,   46,   81,    0,   82,    0,   38,    0,
    0,   13,    0,    0,    0,   80,   99,    0,    0,    0,
   97,    0,    0,    0,  121,   86,   12,  117,   48,    0,
    0,    0,   69,    0,    0,    0,   40,    0,   47,    0,
    0,   39,    0,    0,   79,  101,  105,  106,  107,  108,
  109,  110,  111,  112,  103,    0,    0,    0,    0,  118,
   52,    0,    0,    0,    0,    0,    0,   42,    0,   49,
    0,    0,    0,   41,    0,  102,    0,   30,    0,  122,
    0,   76,   75,   50,   70,    0,    0,   44,   53,    0,
   43,    0,  104,  113,    0,  123,   78,   77,   51,   45,
   31,
};
static const short mofdgoto[] = {                         7,
   84,   61,  161,   74,  135,  162,   64,  163,  164,   65,
   66,   67,   31,   75,    8,   33,  114,  136,  137,   95,
  185,  186,   71,   92,  209,  118,   24,   25,  165,   40,
   10,   11,  122,  123,   12,   13,
};
static const short mofsindex[] = {                       55,
    0, -162, -162, -275, -278, -162,   53,    0, -242,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -50,  -19,
 -162,  -15,  -28,    0,  -13,    0, -162, -248, -162,  -89,
    0,  213,    3, -108, -246, -145,  -14,   83,    0,    4,
    0, -162,  -44, -162,  -69,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    2,
 -203, -162, -162,    0,    0,    0,  -65,  135,  -33, -199,
  -10, -229,   45,  -37,    0,    0,  -40,    0,    0,    0,
    0,    0,    0, -215,   51,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -21,  -14,    0, -162,    0, -108,
    0,    0,    0,  -11,    6,   63,    0,    0,    0, -162,
 -162,  -88,   69,   38,   88,    0, -154,   75,    0,   74,
 -162,    0,   58,    0,    0,    0,    0,    0, -145,    0,
  -69,  -37,    0,    0,    0,   81,    0,  -41,    0,   69,
   37,    0,   -4,   17,   48,    0,    0,   69, -118,   98,
    0,   69,   82,   86,    0,    0,    0,    0,    0,   89,
 -162, -162,    0,   22,  135,   95,    0,   69,    0,  101,
  -17,    0,   69,   50,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   28,  -14,  107,   69,    0,
    0,   56,   56,  108,   40, -162, -162,    0,  109,    0,
  126,   47,  127,    0,   69,    0, -118,    0,   49,    0,
  130,    0,    0,    0,    0,   56,   56,    0,    0,  150,
    0,  154,    0,    0,  -14,    0,    0,    0,    0,    0,
    0,
};
static const short mofrindex[] = {                        0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -12,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   -6,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  172,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -22,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  187,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   66,   72,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   79,   85,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,
};
static const short mofgindex[] = {                        0,
  197,  347,  -23,  133,  -27,  -26,  170,   60,   93,  173,
  189,    0,  -25,  -47,    0,    0,  -92,  -84,  242,    0,
   59,    0,    0,  -93,    0,    0,  225,    0,   10,    0,
    0,    0,  146,    0,  263,    0,
};
#define YYTABLESIZE 544
static const short moftable[] = {                       160,
  126,    6,  130,   63,  146,   69,   62,   29,   85,    9,
   94,   36,  141,   98,   73,   21,    9,   99,   90,  101,
   22,   90,  129,  201,   35,    6,  124,  113,  147,   37,
   42,   24,   27,  117,   28,   60,   90,   25,   32,   68,
   63,  111,   44,   62,  110,  138,   70,  134,  116,    6,
   76,  174,  133,   30,  169,  166,  171,  112,  170,  106,
  102,   96,  194,  176,  139,  195,  140,  188,  206,  103,
  119,  207,   30,    6,  115,  172,   68,  173,   30,   41,
   24,  125,  121,  199,  158,   73,   25,  220,  203,  224,
  195,  127,  225,  208,   38,  167,  112,  168,  148,  212,
  213,  156,   90,  128,  211,  157,   72,  112,  204,   72,
  205,   38,   71,   14,   15,   71,   16,   17,   38,   74,
  222,  142,   74,  227,  228,   73,   78,  149,   73,  150,
    6,  231,  121,  151,  152,    6,   18,  187,  197,  159,
  175,  196,  189,    6,  190,    6,  112,  191,    6,   79,
   80,   76,   81,  198,   82,   83,  177,  178,  179,  200,
  180,  181,  182,  183,  184,  210,  214,  218,   46,   47,
   48,   49,   50,   51,   52,   53,   54,   55,   56,   57,
   58,   59,  154,   72,  219,  221,   14,   15,  226,   16,
   17,   38,   46,   47,   48,   49,   50,   51,   52,   53,
   54,   55,   56,   57,   58,   59,  145,   93,  229,   18,
   14,   15,  230,   16,   17,   98,   46,   47,   48,   49,
   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,
  100,   77,  132,   18,   14,   15,  107,   16,   17,  108,
   46,   47,   48,   49,   50,   51,   52,   53,   54,   55,
   56,   57,   58,   59,  215,  109,  125,   18,   14,   15,
   78,   16,   17,  202,   39,  223,   97,   78,  155,   26,
   86,   87,   88,   89,   90,    0,    0,    0,    0,    0,
    0,   18,    0,   79,   80,   76,   81,   91,   82,   83,
   79,   80,   76,   81,    0,   82,   83,   46,   47,   48,
   49,   50,   51,   52,   53,   54,   55,   56,   57,   58,
   59,    1,    0,    0,    0,   14,   15,    0,   16,   17,
   14,   15,    0,   16,   17,    0,    0,    2,    0,    2,
    3,    0,    3,   14,   15,    0,   16,   17,   18,    0,
   78,    0,    4,   18,    4,    5,    0,    5,   19,   20,
    0,    0,   23,    0,   78,    0,   18,    0,    0,    0,
    0,    0,    0,   79,   80,   76,   81,   34,   82,   83,
    0,    0,    0,   43,    0,   45,    0,   79,   80,   76,
   81,    0,   82,   83,    0,    0,    0,    0,   23,    0,
  100,    0,   46,   47,   48,   49,   50,   51,   52,   53,
   54,   55,   56,   57,   58,   59,    0,    0,  104,  105,
   14,   15,    0,   16,   17,    0,    0,    0,    0,  120,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   18,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  131,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  143,  144,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  153,    0,  120,
   46,   47,   48,   49,   50,   51,   52,   53,   54,   55,
   56,   57,   58,   59,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  192,  193,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  216,  217,
};
static const short mofcheck[] = {                        41,
   41,   91,   96,   30,   93,   32,   30,   58,   36,    0,
   38,   40,  105,   58,  123,  291,    7,   43,   41,   45,
  299,   44,   44,   41,   40,   91,   74,   61,  113,   58,
   44,   44,  275,   44,  277,  125,   59,   44,   58,   30,
   67,   68,  291,   67,   68,   40,   44,   59,   59,   91,
  297,  144,  100,  123,   59,  140,   40,   91,  143,  125,
   59,   58,   41,  148,   59,   44,   61,  152,   41,  273,
  300,   44,  123,   91,  274,   59,   67,   61,  123,   93,
   93,  297,   73,  168,  132,  123,   93,   41,  173,   41,
   44,   41,   44,  187,  123,   59,   91,   61,   61,  192,
  193,  129,  125,  125,  189,  131,   41,   91,   59,   44,
   61,  123,   41,  276,  277,   44,  279,  280,  123,   41,
  205,   59,   44,  216,  217,   41,  272,   40,   44,  284,
   91,  225,  123,   59,   61,   91,  299,   40,  165,   59,
   93,  165,   61,   91,   59,   91,   91,   59,   91,  295,
  296,  297,  298,   59,  300,  301,  275,  276,  277,   59,
  279,  280,  281,  282,  283,   59,   59,   59,  258,  259,
  260,  261,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,  125,  292,   59,   59,  276,  277,   59,  279,
  280,  123,  258,  259,  260,  261,  262,  263,  264,  265,
  266,  267,  268,  269,  270,  271,  295,  125,   59,  299,
  276,  277,   59,  279,  280,   44,  258,  259,  260,  261,
  262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
   44,   35,  100,  299,  276,  277,   67,  279,  280,   67,
  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,
  268,  269,  270,  271,  195,   67,  297,  299,  276,  277,
  272,  279,  280,  171,   23,  207,   42,  272,  123,    7,
  285,  286,  287,  288,  289,   -1,   -1,   -1,   -1,   -1,
   -1,  299,   -1,  295,  296,  297,  298,  302,  300,  301,
  295,  296,  297,  298,   -1,  300,  301,  258,  259,  260,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  257,   -1,   -1,   -1,  276,  277,   -1,  279,  280,
  276,  277,   -1,  279,  280,   -1,   -1,  275,   -1,  275,
  278,   -1,  278,  276,  277,   -1,  279,  280,  299,   -1,
  272,   -1,  290,  299,  290,  293,   -1,  293,    2,    3,
   -1,   -1,    6,   -1,  272,   -1,  299,   -1,   -1,   -1,
   -1,   -1,   -1,  295,  296,  297,  298,   21,  300,  301,
   -1,   -1,   -1,   27,   -1,   29,   -1,  295,  296,  297,
  298,   -1,  300,  301,   -1,   -1,   -1,   -1,   42,   -1,
   44,   -1,  258,  259,  260,  261,  262,  263,  264,  265,
  266,  267,  268,  269,  270,  271,   -1,   -1,   62,   63,
  276,  277,   -1,  279,  280,   -1,   -1,   -1,   -1,   73,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  299,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   98,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  110,  111,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  121,   -1,  123,
  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,
  268,  269,  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  161,  162,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  196,  197,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 302
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,"':'","';'",0,"'='",
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"TOK_ERROR","TOK_BOOLEAN","TOK_SINT8","TOK_UINT8","TOK_SINT16",
"TOK_UINT16","TOK_SINT32","TOK_UINT32","TOK_SINT64","TOK_UINT64","TOK_REAL32",
"TOK_REAL64","TOK_DATETIME","TOK_CHAR16","TOK_STRING","TOK_BOOLEAN_VALUE",
"TOK_REF","TOK_SCOPE","TOK_CLASS","TOK_ASSOCIATION","TOK_INDICATION",
"TOK_QUALIFIER","TOK_PROPERTY","TOK_REFERENCE","TOK_METHOD","TOK_PARAMETER",
"TOK_ANY","TOK_FLAVOR","TOK_ENABLEOVERRIDE","TOK_DISABLEOVERRIDE",
"TOK_RESTRICTED","TOK_TOSUBCLASS","TOK_TRANSLATABLE","TOK_INSTANCE","TOK_OF",
"TOK_AS","TOK_PRAGMA","TOK_SCHEMA","TOK_INTEGER_VALUE","TOK_REAL_VALUE",
"TOK_STRING_VALUE","TOK_CHAR_VALUE","TOK_IDENT","TOK_ALIAS_IDENTIFIER",
"TOK_NULL","TOK_TOINSTANCE",
};
static const char *yyrule[] = {
"$accept : mofSpecification",
"mofSpecification : mofProduction",
"mofSpecification : mofSpecification mofProduction",
"mofSpecification : TOK_ERROR",
"mofProduction : compilerDirective",
"mofProduction : classDeclaration",
"mofProduction : qualifierDeclaration",
"mofProduction : instanceDeclaration",
"compilerDirective : TOK_PRAGMA TOK_IDENT '(' stringValue ')'",
"classDeclaration : TOK_CLASS identifier classBody",
"classDeclaration : TOK_CLASS identifier ':' identifier classBody",
"classDeclaration : qualifierExpr TOK_CLASS identifier classBody",
"classDeclaration : qualifierExpr TOK_CLASS identifier ':' identifier classBody",
"classBody : '{' classFeatureList '}' ';'",
"classBody : '{' '}' ';'",
"classFeatureList : propertyDeclaration",
"classFeatureList : methodDeclaration",
"classFeatureList : referenceDeclaration",
"classFeatureList : classFeatureList propertyDeclaration",
"classFeatureList : classFeatureList methodDeclaration",
"classFeatureList : classFeatureList referenceDeclaration",
"qualifierExpr : '[' qualifierList ']'",
"qualifierList : qualifier",
"qualifierList : qualifierList ',' qualifier",
"qualifier : identifier",
"qualifier : identifier qualifierParameter",
"qualifier : identifier ':' flavor",
"qualifier : identifier qualifierParameter ':' flavor",
"qualifierParameter : '(' constantValue ')'",
"qualifierParameter : arrayInitializer",
"flavorList : flavor",
"flavorList : flavorList ',' flavor",
"flavor : TOK_ENABLEOVERRIDE",
"flavor : TOK_DISABLEOVERRIDE",
"flavor : TOK_RESTRICTED",
"flavor : TOK_TOSUBCLASS",
"flavor : TOK_TRANSLATABLE",
"flavor : TOK_TOINSTANCE",
"propertyDeclaration : dataType identifier ';'",
"propertyDeclaration : qualifierExpr dataType identifier ';'",
"propertyDeclaration : dataType identifier subscript ';'",
"propertyDeclaration : qualifierExpr dataType identifier subscript ';'",
"propertyDeclaration : dataType identifier '=' initializer ';'",
"propertyDeclaration : qualifierExpr dataType identifier '=' initializer ';'",
"propertyDeclaration : dataType identifier subscript '=' initializer ';'",
"propertyDeclaration : qualifierExpr dataType identifier subscript '=' initializer ';'",
"referenceDeclaration : objectRef identifier ';'",
"referenceDeclaration : qualifierExpr objectRef identifier ';'",
"referenceDeclaration : objectRef identifier initializer ';'",
"referenceDeclaration : qualifierExpr objectRef identifier initializer ';'",
"methodDeclaration : dataType identifier '(' parameterList ')' ';'",
"methodDeclaration : qualifierExpr dataType identifier '(' parameterList ')' ';'",
"methodDeclaration : dataType identifier '(' ')' ';'",
"methodDeclaration : qualifierExpr dataType identifier '(' ')' ';'",
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
"objectRef : identifier TOK_REF",
"parameterList : parameter",
"parameterList : parameterList ',' parameter",
"parameter : dataType identifier",
"parameter : objectRef identifier",
"parameter : qualifierExpr dataType identifier",
"parameter : qualifierExpr objectRef identifier",
"parameter : dataType identifier subscript",
"parameter : objectRef identifier subscript",
"parameter : qualifierExpr dataType identifier subscript",
"parameter : qualifierExpr objectRef identifier subscript",
"subscript : '[' TOK_INTEGER_VALUE ']'",
"subscript : '[' ']'",
"initializer : constantValue",
"initializer : arrayInitializer",
"arrayInitializer : '{' arrayInitializerList '}'",
"arrayInitializer : '{' '}'",
"arrayInitializerList : constantValue",
"arrayInitializerList : arrayInitializerList ',' constantValue",
"constantValue : TOK_INTEGER_VALUE",
"constantValue : TOK_REAL_VALUE",
"constantValue : TOK_CHAR_VALUE",
"constantValue : stringValue",
"constantValue : TOK_BOOLEAN_VALUE",
"constantValue : TOK_NULL",
"constantValue : TOK_ALIAS_IDENTIFIER",
"stringValue : TOK_STRING_VALUE",
"stringValue : stringValue TOK_STRING_VALUE",
"qualifierDeclaration : TOK_QUALIFIER identifier qualifierType scopeExpr ';'",
"qualifierDeclaration : TOK_QUALIFIER identifier qualifierType scopeExpr flavorExpr ';'",
"qualifierType : ':' dataType",
"qualifierType : ':' dataType '=' initializer",
"qualifierType : ':' dataType subscript",
"qualifierType : ':' dataType subscript '=' initializer",
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
"instanceDeclaration : TOK_INSTANCE TOK_OF identifier instanceBody",
"instanceDeclaration : qualifierExpr TOK_INDICATION TOK_OF identifier instanceBody",
"instanceDeclaration : TOK_INSTANCE TOK_OF identifier alias instanceBody",
"instanceDeclaration : qualifierExpr TOK_INDICATION TOK_OF identifier alias instanceBody",
"instanceBody : '{' valueInitializerList '}' ';'",
"alias : TOK_AS TOK_ALIAS_IDENTIFIER",
"valueInitializerList : valueInitializer",
"valueInitializerList : valueInitializerList valueInitializer",
"valueInitializer : identifier '=' initializer ';'",
"valueInitializer : qualifierExpr identifier '=' initializer ';'",
"identifier : TOK_IDENT",
"identifier : TOK_ASSOCIATION",
"identifier : TOK_INDICATION",
"identifier : TOK_REFERENCE",
"identifier : TOK_PROPERTY",

};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

#if 0
int      yydebug;
int      yynerrs;

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;

#define YYPURE 0

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static YYSTACKDATA yystack;
#endif
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data, Batch *batch)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (short *)MOF_Realloc(batch, data->s_base, data->stacksize*sizeof(*newss), newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base  = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)MOF_Realloc(batch, data->l_base, data->stacksize*sizeof(*newvs), newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

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

    if (yystack.s_base == NULL && yygrowstack(&yystack, state->batch)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
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
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack, state->batch))
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

    yyerror("syntax error");

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
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack, state->batch))
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
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
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
#line 137 "mof.y"
	{
    }
break;
case 2:
#line 140 "mof.y"
	{ 
    }
break;
case 3:
#line 143 "mof.y"
	{
        YYABORT;
    }
break;
case 4:
#line 149 "mof.y"
	{
    }
break;
case 5:
#line 152 "mof.y"
	{
        /* [TODO: validate the class here] */
        yystack.l_mark[0].classDeclaration->flags = MI_FLAG_CLASS;
        yystack.l_mark[0].classDeclaration->flags |= GetQualFlags(state, yystack.l_mark[0].classDeclaration->qualifiers, yystack.l_mark[0].classDeclaration->numQualifiers);
        if (FinalizeClass(state, yystack.l_mark[0].classDeclaration) != 0)
            YYABORT;
            
        if (AddClassDecl(state, yystack.l_mark[0].classDeclaration) != 0)
            YYABORT;
    }
break;
case 6:
#line 163 "mof.y"
	{
        AddQualifierDeclaration(state, yystack.l_mark[0].qualifierDeclaration);
    }
break;
case 7:
#line 167 "mof.y"
	{
        if (FinalizeInstance(state, yystack.l_mark[0].instanceDeclaration) != 0)
            YYABORT;

        if (AddInstanceDecl(state, yystack.l_mark[0].instanceDeclaration) != 0)
            YYABORT;
    }
break;
case 8:
#line 177 "mof.y"
	{
        if (Tcscmp(yystack.l_mark[-3].string, MI_T("include")) == 0)
        {
            if (openIncludeFile(state, yystack.l_mark[-1].string) != 0)
                YYABORT;
        }
        else if (Tcscmp(yystack.l_mark[-3].string, MI_T("instancelocale")) == 0)
        {
            if (state->pragmaCallback)
                (*state->pragmaCallback)(yystack.l_mark[-3].string, yystack.l_mark[-1].string, state->pragmaCallbackData);
        }
        else if (Tcscmp(yystack.l_mark[-3].string, MI_T("locale")) == 0)
        {
            if (state->pragmaCallback)
                (*state->pragmaCallback)(yystack.l_mark[-3].string, yystack.l_mark[-1].string, state->pragmaCallbackData);
        }
        else if (Tcscmp(yystack.l_mark[-3].string, MI_T("namespace")) == 0)
        {
            if (state->pragmaCallback)
                (*state->pragmaCallback)(yystack.l_mark[-3].string, yystack.l_mark[-1].string, state->pragmaCallbackData);
        }
        else
        {
            yywarnf(state->errhandler, ID_UNKNOWN_PRAGMA, 
                "warning: unknown pragma: %s=%s", yystack.l_mark[-3].string, yystack.l_mark[-1].string);

            if (state->pragmaCallback)
                (*state->pragmaCallback)(yystack.l_mark[-3].string, yystack.l_mark[-1].string, state->pragmaCallbackData);
        }
    }
break;
case 9:
#line 210 "mof.y"
	{
        /* Check whether class already exists */
        if (FindClassDeclBufferOnly(state, yystack.l_mark[-1].string))
        {
            yyerrorf(state->errhandler, ID_CLASS_ALREADY_DEFINED, 
                "class already defined: \"%s\"", yystack.l_mark[-1].string);
            YYABORT;
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
case 10:
#line 228 "mof.y"
	{
        const MI_ClassDecl* scd;

        /* Check whether class already exists */
        if (FindClassDeclBufferOnly(state, yystack.l_mark[-3].string))
        {
            yyerrorf(state->errhandler, ID_CLASS_ALREADY_DEFINED, 
                "class already defined: \"%s\"", yystack.l_mark[-3].string);
            YYABORT;
        }
 
        /* Check whether superclass exists */
        scd = FindClassDecl(state, yystack.l_mark[-1].string);

        if (!scd)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_SUPERCLASS, 
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
case 11:
#line 260 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_CLASS, &yystack.l_mark[-3].qualifierList) != 0)
            YYABORT;

        /* Check whether class already exists */
        if (FindClassDeclBufferOnly(state, yystack.l_mark[-1].string))
        {
            yyerrorf(state->errhandler, ID_CLASS_ALREADY_DEFINED, 
                "class already defined: \"%s\"", yystack.l_mark[-1].string);
            YYABORT;
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
case 12:
#line 284 "mof.y"
	{
        const MI_ClassDecl* scd;

        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_CLASS, &yystack.l_mark[-5].qualifierList) != 0)
            YYABORT;

        /* Check whether class already exists */
        if (FindClassDeclBufferOnly(state, yystack.l_mark[-3].string))
        {
            yyerrorf(state->errhandler, ID_CLASS_ALREADY_DEFINED, 
                "class already defined: \"%s\"", yystack.l_mark[-3].string);
            YYABORT;
        }

        /* Check whether superclass exists */
        scd = FindClassDecl(state, yystack.l_mark[-1].string);

        if (!scd)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_SUPERCLASS, 
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
case 13:
#line 324 "mof.y"
	{
        yyval.featureList = yystack.l_mark[-2].featureList;
    }
break;
case 14:
#line 328 "mof.y"
	{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
    }
break;
case 15:
#line 337 "mof.y"
	{
        if (CheckPropertyValueConstraints(state, yystack.l_mark[0].property) != 0)
        {
            YYABORT;
        }
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(state, yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        if (Codec_PtrArray_Append(state, (PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property) != 0)
        {
            YYABORT;
        }
    }
break;
case 16:
#line 354 "mof.y"
	{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yystack.l_mark[0].methodDecl->flags = MI_FLAG_METHOD;
        yystack.l_mark[0].methodDecl->flags |= GetQualFlags(state, yystack.l_mark[0].methodDecl->qualifiers, yystack.l_mark[0].methodDecl->numQualifiers);
        if (Codec_PtrArray_Append(state, (PtrArray*)&yyval.featureList.methodList, yystack.l_mark[0].methodDecl) != 0)
        {
            YYABORT;
        }
    }
break;
case 17:
#line 367 "mof.y"
	{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yyval.featureList.methodList.data = NULL;
        yyval.featureList.methodList.size = 0;
        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(state, yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        if (Codec_PtrArray_Append(state, (PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property) !=0)
        {
            YYABORT;
        }
    }
break;
case 18:
#line 380 "mof.y"
	{
        if (CheckPropertyValueConstraints(state, yystack.l_mark[0].property) != 0)
        {
            YYABORT;
        }

        if (FindProperty(&yystack.l_mark[-1].featureList.propertySet, yystack.l_mark[0].property->name))
        {
            yyerrorf(state->errhandler, ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", yystack.l_mark[0].property->name);
            YYABORT;
        }

        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(state, yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        if (Codec_PtrArray_Append(state, (PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property) != 0)
        {
            YYABORT;
        }
    }
break;
case 19:
#line 401 "mof.y"
	{
        if (FindMethod(&yystack.l_mark[-1].featureList.methodList, yystack.l_mark[0].methodDecl->name))
        {
            yyerrorf(state->errhandler, ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", yystack.l_mark[0].methodDecl->name);
            YYABORT;
        }

        yystack.l_mark[0].methodDecl->flags = MI_FLAG_METHOD;
        yystack.l_mark[0].methodDecl->flags |= GetQualFlags(state, yystack.l_mark[0].methodDecl->qualifiers, yystack.l_mark[0].methodDecl->numQualifiers);
        if (Codec_PtrArray_Append(state, (PtrArray*)&yyval.featureList.methodList, yystack.l_mark[0].methodDecl) != 0)
        {
            YYABORT;
        }
    }
break;
case 20:
#line 417 "mof.y"
	{
        if (FindProperty(&yystack.l_mark[-1].featureList.propertySet, yystack.l_mark[0].property->name))
        {
            yyerrorf(state->errhandler, ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", yystack.l_mark[0].property->name);
            YYABORT;
        }

        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(state, yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        if (Codec_PtrArray_Append(state, (PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property) != 0)
        {
            YYABORT;
        }
    }
break;
case 21:
#line 435 "mof.y"
	{
        yyval.qualifierList = yystack.l_mark[-1].qualifierList;
    }
break;
case 22:
#line 441 "mof.y"
	{
        yyval.qualifierList.data = NULL;
        yyval.qualifierList.size = 0;
        if (Codec_PtrArray_Append(state, (PtrArray*)&yyval.qualifierList, yystack.l_mark[0].qualifier) != 0)
        {
            YYABORT;
        }
    }
break;
case 23:
#line 450 "mof.y"
	{
        if (FindQualifier(&yystack.l_mark[-2].qualifierList, yystack.l_mark[0].qualifier->name))
        {
            yyerrorf(state->errhandler, ID_DUPLICATE_QUALIFIER, 
                "duplicate qualifier: \"%s\"", yystack.l_mark[0].qualifier->name);
            YYABORT;
        }

        if (Codec_PtrArray_Append(state, (PtrArray*)&yyval.qualifierList, yystack.l_mark[0].qualifier) != 0)
        {
            YYABORT;
        }
    }
break;
case 24:
#line 466 "mof.y"
	{
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;

        qd = FindQualifierDeclaration(state, yystack.l_mark[0].string);

        if (!qd)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", yystack.l_mark[0].string);
            YYABORT;
        }

        if (qd->type != MI_BOOLEAN)
        {
            yyerrorf(state->errhandler, ID_MISSING_QUALIFIER_INITIALIZER, 
                "qualifier is missing initializer: \"%s\"", yystack.l_mark[0].string);
            YYABORT;
        }
        
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = qd->flavor;
        q->value = NewTrueValue(state);
        yyval.qualifier = q;
    }
break;
case 25:
#line 494 "mof.y"
	{
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;
        void* value;

        qd = FindQualifierDeclaration(state, yystack.l_mark[-1].string);

        if (!qd)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", yystack.l_mark[-1].string);
            YYABORT;
        }

        if (InitializerToValue(state, &yystack.l_mark[0].initializer, qd->type, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_QUALIFIER_INITIALIZER, 
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
case 26:
#line 522 "mof.y"
	{
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;

        qd = FindQualifierDeclaration(state, yystack.l_mark[-2].string);

        if (!qd)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", yystack.l_mark[-2].string);
            YYABORT;
        }

        if (qd->type != MI_BOOLEAN)
        {
            yyerrorf(state->errhandler, ID_MISSING_QUALIFIER_INITIALIZER, 
                "qualifier is missing initializer: \"%s\"", yystack.l_mark[-2].string);
            YYABORT;
        }
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = PropagateFlavors(yystack.l_mark[0].flags, qd->flavor);
        q->value = NewTrueValue(state);
        yyval.qualifier = q;
    }
break;
case 27:
#line 549 "mof.y"
	{
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;
        void* value;

        qd = FindQualifierDeclaration(state, yystack.l_mark[-3].string);

        if (!qd)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", yystack.l_mark[-3].string);
            YYABORT;
        }

        if (InitializerToValue(state, &yystack.l_mark[-2].initializer, qd->type, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_QUALIFIER_INITIALIZER, 
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
case 28:
#line 579 "mof.y"
	{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yystack.l_mark[-1].constantValue;
        yyval.initializer.size = 1;
    }
break;
case 29:
#line 586 "mof.y"
	{
        yyval.initializer = yystack.l_mark[0].initializer;
    }
break;
case 30:
#line 592 "mof.y"
	{
        yyval.flags = yystack.l_mark[0].flags;
    }
break;
case 31:
#line 596 "mof.y"
	{
        yyval.flags |= yystack.l_mark[0].flags;
    }
break;
case 32:
#line 602 "mof.y"
	{
        yyval.flags = MI_FLAG_ENABLEOVERRIDE;
    }
break;
case 33:
#line 606 "mof.y"
	{
        yyval.flags = MI_FLAG_DISABLEOVERRIDE;
    }
break;
case 34:
#line 610 "mof.y"
	{
        yyval.flags = MI_FLAG_RESTRICTED;
    }
break;
case 35:
#line 614 "mof.y"
	{
        yyval.flags = MI_FLAG_TOSUBCLASS;
    }
break;
case 36:
#line 618 "mof.y"
	{
        yyval.flags = MI_FLAG_TRANSLATABLE;
    }
break;
case 37:
#line 622 "mof.y"
	{   /* WMI specific, ignore now */
        yyval.flags = 0;
    }
break;
case 38:
#line 628 "mof.y"
	{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->type = yystack.l_mark[-2].type;
    }
break;
case 39:
#line 634 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PROPERTY, &yystack.l_mark[-3].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->type = yystack.l_mark[-2].type;
        yyval.property->qualifiers = yystack.l_mark[-3].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-3].qualifierList.size;
    }
break;
case 40:
#line 646 "mof.y"
	{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->type = ARRAYOF(yystack.l_mark[-3].type);
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-1].integer;
    }
break;
case 41:
#line 653 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PROPERTY, &yystack.l_mark[-4].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->type = ARRAYOF(yystack.l_mark[-3].type);
        yyval.property->qualifiers = yystack.l_mark[-4].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-4].qualifierList.size;
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-1].integer;
    }
break;
case 42:
#line 666 "mof.y"
	{
        void* value;

        if (InitializerToValue(state, &yystack.l_mark[-1].initializer, yystack.l_mark[-4].type, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->type = yystack.l_mark[-4].type;
        yyval.property->value = value;
    }
break;
case 43:
#line 681 "mof.y"
	{
        void* value;

        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PROPERTY, &yystack.l_mark[-5].qualifierList) != 0)
            YYABORT;

        if (InitializerToValue(state, &yystack.l_mark[-1].initializer, yystack.l_mark[-4].type, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
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
case 44:
#line 702 "mof.y"
	{
        void* value;

        if (InitializerToValue(state, &yystack.l_mark[-1].initializer, ARRAYOF(yystack.l_mark[-5].type), &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-4].string;
        yyval.property->type = ARRAYOF(yystack.l_mark[-5].type);
        yyval.property->subscript = (MI_Uint32)yystack.l_mark[-3].integer;
        yyval.property->value = value;
    }
break;
case 45:
#line 718 "mof.y"
	{
        void* value;

        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PROPERTY, &yystack.l_mark[-6].qualifierList) != 0)
            YYABORT;

        if (InitializerToValue(state, &yystack.l_mark[-1].initializer, ARRAYOF(yystack.l_mark[-5].type), &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
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
case 46:
#line 742 "mof.y"
	{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->className = yystack.l_mark[-2].string;
    }
break;
case 47:
#line 749 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_REFERENCE, &yystack.l_mark[-3].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yystack.l_mark[-1].string;
        yyval.property->className = yystack.l_mark[-2].string;
        yyval.property->qualifiers = yystack.l_mark[-3].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-3].qualifierList.size;
    }
break;
case 48:
#line 762 "mof.y"
	{
        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->className = yystack.l_mark[-3].string;
        yywarnf(state->errhandler, ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* [TODO: use initializer */
    }
break;
case 49:
#line 771 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_REFERENCE, &yystack.l_mark[-4].qualifierList) != 0)
            YYABORT;

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->type = MI_REFERENCE;
        yyval.property->name = yystack.l_mark[-2].string;
        yyval.property->className = yystack.l_mark[-3].string;
        yyval.property->qualifiers = yystack.l_mark[-4].qualifierList.data;
        yyval.property->numQualifiers = yystack.l_mark[-4].qualifierList.size;
        yywarnf(state->errhandler, ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* [TODO: use initializer] */
    }
break;
case 50:
#line 788 "mof.y"
	{
        yyval.methodDecl = CALLOC_T(MI_MethodDecl, 1);
        yyval.methodDecl->name = yystack.l_mark[-4].string;
        yyval.methodDecl->parameters = CreateParameterSet(state, yystack.l_mark[-2].parameterList.data, yystack.l_mark[-2].parameterList.size, yystack.l_mark[-5].type);
        if (!yyval.methodDecl->parameters)
            YYABORT;
        yyval.methodDecl->numParameters = yystack.l_mark[-2].parameterList.size + 1;
        yyval.methodDecl->returnType = yystack.l_mark[-5].type;
    }
break;
case 51:
#line 798 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_METHOD, &yystack.l_mark[-6].qualifierList) != 0)
            YYABORT;

        yyval.methodDecl = CALLOC_T(MI_MethodDecl, 1);
        yyval.methodDecl->name = yystack.l_mark[-4].string;
        yyval.methodDecl->parameters = CreateParameterSet(state, yystack.l_mark[-2].parameterList.data, yystack.l_mark[-2].parameterList.size, yystack.l_mark[-5].type);
        if (!yyval.methodDecl->parameters)
            YYABORT;
        yyval.methodDecl->numParameters = yystack.l_mark[-2].parameterList.size + 1;
        yyval.methodDecl->qualifiers = yystack.l_mark[-6].qualifierList.data;
        yyval.methodDecl->numQualifiers = yystack.l_mark[-6].qualifierList.size;
        yyval.methodDecl->returnType = yystack.l_mark[-5].type;
    }
break;
case 52:
#line 814 "mof.y"
	{
        MOF_ParameterList parameterList = PTRARRAY_INITIALIZER;

        yyval.methodDecl = CALLOC_T(MI_MethodDecl, 1);
        yyval.methodDecl->name = yystack.l_mark[-3].string;
        yyval.methodDecl->parameters = CreateParameterSet(state, parameterList.data, parameterList.size, yystack.l_mark[-4].type);
        if (!yyval.methodDecl->parameters)
            YYABORT;
        yyval.methodDecl->numParameters = parameterList.size + 1;
        yyval.methodDecl->returnType = yystack.l_mark[-4].type;
    }
break;
case 53:
#line 826 "mof.y"
	{
        MOF_ParameterList parameterList = PTRARRAY_INITIALIZER;

        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_METHOD, &yystack.l_mark[-5].qualifierList) != 0)
            YYABORT;

        yyval.methodDecl = CALLOC_T(MI_MethodDecl, 1);
        yyval.methodDecl->name = yystack.l_mark[-3].string;
        yyval.methodDecl->parameters = CreateParameterSet(state, parameterList.data, parameterList.size, yystack.l_mark[-4].type);
        if (!yyval.methodDecl->parameters)
            YYABORT;
        yyval.methodDecl->numParameters = parameterList.size + 1;
        yyval.methodDecl->qualifiers = yystack.l_mark[-5].qualifierList.data;
        yyval.methodDecl->numQualifiers = yystack.l_mark[-5].qualifierList.size;
        yyval.methodDecl->returnType = yystack.l_mark[-4].type;
    }
break;
case 54:
#line 846 "mof.y"
	{
        yyval.type = MI_BOOLEAN;
    }
break;
case 55:
#line 850 "mof.y"
	{
        yyval.type = MI_SINT8;
    }
break;
case 56:
#line 854 "mof.y"
	{
        yyval.type = MI_UINT8;
    }
break;
case 57:
#line 858 "mof.y"
	{
        yyval.type = MI_SINT16;
    }
break;
case 58:
#line 862 "mof.y"
	{
        yyval.type = MI_UINT16;
    }
break;
case 59:
#line 866 "mof.y"
	{
        yyval.type = MI_SINT32;
    }
break;
case 60:
#line 870 "mof.y"
	{
        yyval.type = MI_UINT32;
    }
break;
case 61:
#line 874 "mof.y"
	{
        yyval.type = MI_SINT64;
    }
break;
case 62:
#line 878 "mof.y"
	{
        yyval.type = MI_UINT64;
    }
break;
case 63:
#line 882 "mof.y"
	{
        yyval.type = MI_REAL32;
    }
break;
case 64:
#line 886 "mof.y"
	{
        yyval.type = MI_REAL64;
    }
break;
case 65:
#line 890 "mof.y"
	{
        yyval.type = MI_CHAR16;
    }
break;
case 66:
#line 894 "mof.y"
	{
        yyval.type = MI_DATETIME;
    }
break;
case 67:
#line 898 "mof.y"
	{
        yyval.type = MI_STRING;
    }
break;
case 68:
#line 904 "mof.y"
	{
        yyval.string = yystack.l_mark[-1].string;
    }
break;
case 69:
#line 910 "mof.y"
	{
        yystack.l_mark[0].parameter->flags = MI_FLAG_PARAMETER;
        yystack.l_mark[0].parameter->flags |= GetQualFlags(state, yystack.l_mark[0].parameter->qualifiers, yystack.l_mark[0].parameter->numQualifiers);
        yyval.parameterList.data = NULL;
        yyval.parameterList.size = 0;
        if (Codec_PtrArray_Append(state, (PtrArray*)&yyval.parameterList, yystack.l_mark[0].parameter) != 0)
        {
            YYABORT;
        }
    }
break;
case 70:
#line 921 "mof.y"
	{
        if (FindParameter(&yystack.l_mark[-2].parameterList, yystack.l_mark[0].parameter->name))
        {
            yyerrorf(state->errhandler, ID_PARAMETER_ALREADY_DEFINED, 
                "parameter already defined: \"%s\"", yystack.l_mark[0].parameter->name);
            YYABORT;
        }

        yystack.l_mark[0].parameter->flags = MI_FLAG_PARAMETER;
        yystack.l_mark[0].parameter->flags |= GetQualFlags(state, yystack.l_mark[0].parameter->qualifiers, yystack.l_mark[0].parameter->numQualifiers);
        if (Codec_PtrArray_Append(state, (PtrArray*)&yyval.parameterList, yystack.l_mark[0].parameter) != 0)
        {
            YYABORT;
        }
    }
break;
case 71:
#line 939 "mof.y"
	{
        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[0].string;
        yyval.parameter->type = yystack.l_mark[-1].type;
    }
break;
case 72:
#line 945 "mof.y"
	{
        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[0].string;
        yyval.parameter->type = MI_REFERENCE;
        yyval.parameter->className = yystack.l_mark[-1].string;
    }
break;
case 73:
#line 952 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PARAMETER, &yystack.l_mark[-2].qualifierList) != 0)
            YYABORT;

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[0].string;
        yyval.parameter->type = yystack.l_mark[-1].type;
        yyval.parameter->qualifiers = yystack.l_mark[-2].qualifierList.data;
        yyval.parameter->numQualifiers = yystack.l_mark[-2].qualifierList.size;
    }
break;
case 74:
#line 964 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PARAMETER, &yystack.l_mark[-2].qualifierList) != 0)
            YYABORT;

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[0].string;
        yyval.parameter->type = MI_REFERENCE;
        yyval.parameter->className = yystack.l_mark[-1].string;
        yyval.parameter->qualifiers = yystack.l_mark[-2].qualifierList.data;
        yyval.parameter->numQualifiers = yystack.l_mark[-2].qualifierList.size;
    }
break;
case 75:
#line 977 "mof.y"
	{
        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[-1].string;
        yyval.parameter->type = ARRAYOF(yystack.l_mark[-2].type);
        yyval.parameter->subscript = (MI_Uint32)yystack.l_mark[0].integer;
    }
break;
case 76:
#line 984 "mof.y"
	{
        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[-1].string;
        yyval.parameter->type = ARRAYOF(MI_REFERENCE);
        yyval.parameter->className = yystack.l_mark[-2].string;
        yyval.parameter->subscript = (MI_Uint32)yystack.l_mark[0].integer;
    }
break;
case 77:
#line 992 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PARAMETER, &yystack.l_mark[-3].qualifierList) != 0)
            YYABORT;

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[-1].string;
        yyval.parameter->type = ARRAYOF(yystack.l_mark[-2].type);
        yyval.parameter->subscript = (MI_Uint32)yystack.l_mark[0].integer;
        yyval.parameter->qualifiers = yystack.l_mark[-3].qualifierList.data;
        yyval.parameter->numQualifiers = yystack.l_mark[-3].qualifierList.size;
    }
break;
case 78:
#line 1005 "mof.y"
	{
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PARAMETER, &yystack.l_mark[-3].qualifierList) != 0)
            YYABORT;

        yyval.parameter = CALLOC_T(MI_ParameterDecl, 1);
        yyval.parameter->name = yystack.l_mark[-1].string;
        yyval.parameter->type = ARRAYOF(MI_REFERENCE);
        yyval.parameter->className = yystack.l_mark[-2].string;
        yyval.parameter->subscript = (MI_Uint32)yystack.l_mark[0].integer;
        yyval.parameter->qualifiers = yystack.l_mark[-3].qualifierList.data;
        yyval.parameter->numQualifiers = yystack.l_mark[-3].qualifierList.size;
    }
break;
case 79:
#line 1021 "mof.y"
	{
        if (yystack.l_mark[-1].integer <= 0)
        {
            yyerrorf(state->errhandler, ID_ILLEGAL_ARRAY_SUBSCRIPT, 
                "illegal array subscript: " SINT64_FMT, yystack.l_mark[-1].integer);
            YYABORT;
        }

        yyval.integer = yystack.l_mark[-1].integer;
    }
break;
case 80:
#line 1032 "mof.y"
	{
        /* 0 signifies a dynamic array */
        yyval.integer = 0;
    }
break;
case 81:
#line 1039 "mof.y"
	{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yystack.l_mark[0].constantValue;
        yyval.initializer.size = 1;
    }
break;
case 82:
#line 1046 "mof.y"
	{
        yyval.initializer = yystack.l_mark[0].initializer;
    }
break;
case 83:
#line 1052 "mof.y"
	{
        yyval.initializer = yystack.l_mark[-1].initializer;
    }
break;
case 84:
#line 1056 "mof.y"
	{
        yyval.initializer.data = NULL;
        yyval.initializer.size = 0;
        yyval.initializer.isArray = 1;
    }
break;
case 85:
#line 1063 "mof.y"
	{
        memset(&yyval.initializer, 0, sizeof(yyval.initializer));
        yyval.initializer.data = CALLOC_T(MOF_ConstantValue, 1);
        yyval.initializer.data[0] = yystack.l_mark[0].constantValue;
        yyval.initializer.size = 1;
        yyval.initializer.isArray = 1;
    }
break;
case 86:
#line 1071 "mof.y"
	{
        size_t orgsize = yystack.l_mark[-2].initializer.size;
        yystack.l_mark[-2].initializer.data = REALLOC_T(MOF_ConstantValue, yystack.l_mark[-2].initializer.data, orgsize, orgsize + 1);
        /* check return value
*/
        yystack.l_mark[-2].initializer.data[yystack.l_mark[-2].initializer.size] = yystack.l_mark[0].constantValue;
        yystack.l_mark[-2].initializer.size++;
        yyval.initializer = yystack.l_mark[-2].initializer;
    }
break;
case 87:
#line 1082 "mof.y"
	{
        yyval.constantValue.type = TOK_INTEGER_VALUE;
        yyval.constantValue.value.integer = yystack.l_mark[0].integer;
    }
break;
case 88:
#line 1087 "mof.y"
	{
        yyval.constantValue.type = TOK_REAL_VALUE;
        yyval.constantValue.value.real = yystack.l_mark[0].real;
    }
break;
case 89:
#line 1092 "mof.y"
	{
        yyval.constantValue.type = TOK_CHAR_VALUE;
        yyval.constantValue.value.character = yystack.l_mark[0].character;
    }
break;
case 90:
#line 1097 "mof.y"
	{
        yyval.constantValue.type = TOK_STRING_VALUE;
        yyval.constantValue.value.string = yystack.l_mark[0].string;
    }
break;
case 91:
#line 1102 "mof.y"
	{
        yyval.constantValue.type = TOK_BOOLEAN_VALUE;
        yyval.constantValue.value.boolean = yystack.l_mark[0].boolean;
    }
break;
case 92:
#line 1107 "mof.y"
	{
        yyval.constantValue.type = TOK_NULL;
    }
break;
case 93:
#line 1111 "mof.y"
	{
        yyval.constantValue.type = TOK_ALIAS_IDENTIFIER;
        yyval.constantValue.value.string = yystack.l_mark[0].string;
    }
break;
case 94:
#line 1118 "mof.y"
	{
	yyval.string = yystack.l_mark[0].string;
    }
break;
case 95:
#line 1122 "mof.y"
	{
        size_t orgsize = Tcslen(yystack.l_mark[-1].string);
        size_t newsize = Tcslen(yystack.l_mark[0].string) + 1;
        size_t tsize = orgsize+newsize;
        size_t orgbufsize = orgsize * sizeof(ZChar);
        size_t bufsize = tsize * sizeof(ZChar);
        yyval.string = (ZChar*)MOF_Realloc(state->batch, yystack.l_mark[-1].string, orgbufsize, bufsize);
        Tcslcat(yyval.string, yystack.l_mark[0].string, tsize);
        /* MOF_Free(&state->heap, $2); */
    }
break;
case 96:
#line 1135 "mof.y"
	{
        yystack.l_mark[-2].qualifierDeclaration->name = yystack.l_mark[-3].string;
        yystack.l_mark[-2].qualifierDeclaration->scope = yystack.l_mark[-1].flags;
        yystack.l_mark[-2].qualifierDeclaration->flavor = 0;
        yyval.qualifierDeclaration = yystack.l_mark[-2].qualifierDeclaration;
    }
break;
case 97:
#line 1142 "mof.y"
	{
        yystack.l_mark[-3].qualifierDeclaration->name = yystack.l_mark[-4].string;
        yystack.l_mark[-3].qualifierDeclaration->scope = yystack.l_mark[-2].flags;
        yystack.l_mark[-3].qualifierDeclaration->flavor = yystack.l_mark[-1].flags;
        yyval.qualifierDeclaration = yystack.l_mark[-3].qualifierDeclaration;
    }
break;
case 98:
#line 1151 "mof.y"
	{
        yyval.qualifierDeclaration = CALLOC_T(MI_QualifierDecl, 1);
        yyval.qualifierDeclaration->type = yystack.l_mark[0].type;
    }
break;
case 99:
#line 1156 "mof.y"
	{
        void* value;

        if (InitializerToValue(state, &yystack.l_mark[0].initializer, yystack.l_mark[-2].type, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.qualifierDeclaration = CALLOC_T(MI_QualifierDecl, 1);
        yyval.qualifierDeclaration->type = yystack.l_mark[-2].type;
        yyval.qualifierDeclaration->value = value;
        ReleaseInitializer(state, &yystack.l_mark[0].initializer);
    }
break;
case 100:
#line 1171 "mof.y"
	{
        yyval.qualifierDeclaration = CALLOC_T(MI_QualifierDecl, 1);
        yyval.qualifierDeclaration->type = ARRAYOF(yystack.l_mark[-1].type);
        yyval.qualifierDeclaration->subscript = (MI_Uint32)yystack.l_mark[0].integer;
    }
break;
case 101:
#line 1177 "mof.y"
	{
        void* value = NULL;

        if (InitializerToValue(state, &yystack.l_mark[0].initializer, ARRAYOF(yystack.l_mark[-3].type), &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.qualifierDeclaration = CALLOC_T(MI_QualifierDecl, 1);
        yyval.qualifierDeclaration->type = ARRAYOF(yystack.l_mark[-3].type);
        yyval.qualifierDeclaration->subscript = (MI_Uint32)yystack.l_mark[-2].integer;
        yyval.qualifierDeclaration->value = value;
        ReleaseInitializer(state, &yystack.l_mark[0].initializer);
    }
break;
case 102:
#line 1195 "mof.y"
	{
        yyval.flags = yystack.l_mark[-1].flags;
    }
break;
case 103:
#line 1201 "mof.y"
	{
        yyval.flags = yystack.l_mark[0].flags;
    }
break;
case 104:
#line 1205 "mof.y"
	{
        yyval.flags |= yystack.l_mark[0].flags;
    }
break;
case 105:
#line 1211 "mof.y"
	{
        yyval.flags = MI_FLAG_CLASS;
    }
break;
case 106:
#line 1215 "mof.y"
	{
        yyval.flags = MI_FLAG_ASSOCIATION;
    }
break;
case 107:
#line 1219 "mof.y"
	{
        yyval.flags = MI_FLAG_INDICATION;
    }
break;
case 108:
#line 1223 "mof.y"
	{
        yyval.flags = MI_FLAG_PROPERTY;
    }
break;
case 109:
#line 1227 "mof.y"
	{
        yyval.flags = MI_FLAG_REFERENCE;
    }
break;
case 110:
#line 1231 "mof.y"
	{
        yyval.flags = MI_FLAG_METHOD;
    }
break;
case 111:
#line 1235 "mof.y"
	{
        yyval.flags = MI_FLAG_PARAMETER;
    }
break;
case 112:
#line 1239 "mof.y"
	{
        yyval.flags = MI_FLAG_ANY;
    }
break;
case 113:
#line 1245 "mof.y"
	{
        /* Reject incompatiable ToSubclass and Restricted flavors */
        if (yystack.l_mark[-1].flags & MI_FLAG_TOSUBCLASS && yystack.l_mark[-1].flags & MI_FLAG_RESTRICTED)
        {
            yyerrorf(state->errhandler, ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s", 
                "ToSubclass", "Restricted");
            YYABORT;
        }

        /* Reject incompatiable EnableOverride and DisableOverride flavors */
        if (yystack.l_mark[-1].flags & MI_FLAG_ENABLEOVERRIDE && yystack.l_mark[-1].flags & MI_FLAG_DISABLEOVERRIDE)
        {
            yyerrorf(state->errhandler, ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s", 
                "EnableOverride", "DisableOverride");
            YYABORT;
        }

        yyval.flags = yystack.l_mark[-1].flags;
    }
break;
case 114:
#line 1267 "mof.y"
	{
        yyval.instanceDeclaration = CALLOC_T(MI_InstanceDecl, 1);
        yyval.instanceDeclaration->flags = 0;
        yyval.instanceDeclaration->name = yystack.l_mark[-1].string;
        yyval.instanceDeclaration->properties = yystack.l_mark[0].featureList.propertySet.data;
        yyval.instanceDeclaration->numProperties = yystack.l_mark[0].featureList.propertySet.size;
    }
break;
case 115:
#line 1275 "mof.y"
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
case 116:
#line 1285 "mof.y"
	{
        yyval.instanceDeclaration = CALLOC_T(MI_InstanceDecl, 1);
        yyval.instanceDeclaration->flags = 0;
        yyval.instanceDeclaration->name = yystack.l_mark[-2].string;
        yyval.instanceDeclaration->alias = yystack.l_mark[-1].string;
        yyval.instanceDeclaration->properties = yystack.l_mark[0].featureList.propertySet.data;
        yyval.instanceDeclaration->numProperties = yystack.l_mark[0].featureList.propertySet.size;
    }
break;
case 117:
#line 1294 "mof.y"
	{
        /* [TODO]: handle alias */
        yyval.instanceDeclaration = CALLOC_T(MI_InstanceDecl, 1);
        yyval.instanceDeclaration->flags = 0;
        yyval.instanceDeclaration->name = yystack.l_mark[-2].string;
        yyval.instanceDeclaration->alias = yystack.l_mark[-1].string;
        yyval.instanceDeclaration->properties = yystack.l_mark[0].featureList.propertySet.data;
        yyval.instanceDeclaration->numProperties = yystack.l_mark[0].featureList.propertySet.size;
        yyval.instanceDeclaration->qualifiers = yystack.l_mark[-5].qualifierList.data;
        yyval.instanceDeclaration->numQualifiers = yystack.l_mark[-5].qualifierList.size;
    }
break;
case 118:
#line 1308 "mof.y"
	{
        yyval.featureList = yystack.l_mark[-2].featureList;
    }
break;
case 119:
#line 1314 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
        if (state->onAliasDeclared)
            (*state->onAliasDeclared)(state);
    }
break;
case 120:
#line 1322 "mof.y"
	{
        yyval.featureList.propertySet.data = NULL;
        yyval.featureList.propertySet.size = 0;
        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(state, yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        if (Codec_PtrArray_Append(state, (PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property) != 0)
        {
            YYABORT;
        }
    }
break;
case 121:
#line 1333 "mof.y"
	{
        if (FindProperty(&yystack.l_mark[-1].featureList.propertySet, yystack.l_mark[0].property->name))
        {
            yyerrorf(state->errhandler, ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "instance property already defined: \"%s\"", yystack.l_mark[0].property->name);
            YYABORT;
        }

        yystack.l_mark[0].property->flags = MI_FLAG_PROPERTY;
        yystack.l_mark[0].property->flags |= GetQualFlags(state, yystack.l_mark[0].property->qualifiers, yystack.l_mark[0].property->numQualifiers);
        if (Codec_PtrArray_Append(state, (PtrArray*)&yyval.featureList.propertySet, yystack.l_mark[0].property) != 0)
        {
            YYABORT;
        }
    }
break;
case 122:
#line 1351 "mof.y"
	{
        void* value;
        MI_Type type = InitializerToType(&yystack.l_mark[-1].initializer);

        if (InitializerToValue(state, &yystack.l_mark[-1].initializer, type, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        yyval.property = CALLOC_T(MI_PropertyDecl, 1);
        yyval.property->name = yystack.l_mark[-3].string;
        yyval.property->type = type;
        yyval.property->value = value;
    }
break;
case 123:
#line 1367 "mof.y"
	{
        void* value;
        MI_Type type = InitializerToType(&yystack.l_mark[-1].initializer);

        if (InitializerToValue(state, &yystack.l_mark[-1].initializer, type, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
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
case 124:
#line 1387 "mof.y"
	{
        yyval.string = yystack.l_mark[0].string;
    }
break;
case 125:
#line 1391 "mof.y"
	{
        yyval.string = Batch_StrTcsdup(state->batch, "Association");
    }
break;
case 126:
#line 1395 "mof.y"
	{
        yyval.string = Batch_StrTcsdup(state->batch, "Indication");
    }
break;
case 127:
#line 1399 "mof.y"
	{
        yyval.string = Batch_StrTcsdup(state->batch, "Reference");
    }
break;
case 128:
#line 1403 "mof.y"
	{
        yyval.string = Batch_StrTcsdup(state->batch, "Property");
    }
break;
#line 2291 "mofy.tab.c"
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
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
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
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack, state->batch))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
