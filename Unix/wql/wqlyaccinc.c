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

#ifndef yyparse
#define yyparse    wqlparse
#endif /* yyparse */

#ifndef yylex
#define yylex      wqllex
#endif /* yylex */

#ifndef yyerror
#define yyerror    wqlerror
#endif /* yyerror */

#ifndef yychar
#define yychar     wqlchar
#endif /* yychar */

#ifndef yyval
#define yyval      wqlval
#endif /* yyval */

#ifndef yylval
#define yylval     wqllval
#endif /* yylval */

#ifndef yydebug
#define yydebug    wqldebug
#endif /* yydebug */

#ifndef yynerrs
#define yynerrs    wqlnerrs
#endif /* yynerrs */

#ifndef yyerrflag
#define yyerrflag  wqlerrflag
#endif /* yyerrflag */

#ifndef yylhs
#define yylhs      wqllhs
#endif /* yylhs */

#ifndef yylen
#define yylen      wqllen
#endif /* yylen */

#ifndef yydefred
#define yydefred   wqldefred
#endif /* yydefred */

#ifndef yydgoto
#define yydgoto    wqldgoto
#endif /* yydgoto */

#ifndef yysindex
#define yysindex   wqlsindex
#endif /* yysindex */

#ifndef yyrindex
#define yyrindex   wqlrindex
#endif /* yyrindex */

#ifndef yygindex
#define yygindex   wqlgindex
#endif /* yygindex */

#ifndef yytable
#define yytable    wqltable
#endif /* yytable */

#ifndef yycheck
#define yycheck    wqlcheck
#endif /* yycheck */

#ifndef yyname
#define yyname     wqlname
#endif /* yyname */

#ifndef yyrule
#define yyrule     wqlrule
#endif /* yyrule */
#define YYPREFIX "wql"

#define YYPURE 0

#line 2 "wql.y"

#include <stdio.h>
#include "state.h"
#include "wql.h"

#if 0
# define YACCTRACE(MSG) \
    printf("WQL_TRACE: %s(%d): %s\n", __FILE__, __LINE__, #MSG)
#else
# define YACCTRACE(MSG)
#endif

extern int wqllex();
extern void wqlerror(const char* msg);

extern int yylex();
extern void yyerror(const char* msg);

extern void* wqlmalloc(size_t size);
extern MI_Char* wqlstrdup(const MI_Char* str);

#line 25 "wql.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union
{
    WQL_Symbol symbol;
    MI_Char* string;
    long long integer;
    double real;
    unsigned char boolean;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 139 "y.tab.c"

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

#define WQL_DOT 257
#define WQL_COLON 258
#define WQL_OR 259
#define WQL_AND 260
#define WQL_NOT 261
#define WQL_ERROR 262
#define WQL_LT 263
#define WQL_FROM 264
#define WQL_LE 265
#define WQL_WHERE 266
#define WQL_NE 267
#define WQL_GT 268
#define WQL_EQ 269
#define WQL_SELECT 270
#define WQL_GE 271
#define WQL_NULL 272
#define WQL_LIKE 273
#define WQL_ISA 274
#define WQL_IDENTIFIER 275
#define WQL_BOOLEAN 276
#define WQL_INTEGER 277
#define WQL_REAL 278
#define WQL_STRING 279
#define YYERRCODE 256
typedef short YYINT;
static const YYINT wqllhs[] = {                          -1,
    0,    0,    3,    3,    5,    5,    4,    4,    4,    4,
    4,    6,    6,    6,    6,    6,    6,    6,    6,    1,
    1,    1,    1,    1,    1,    2,    2,    2,
};
static const YYINT wqllen[] = {                           2,
    4,    6,    1,    1,    1,    3,    3,    2,    3,    3,
    1,    3,    3,    3,    3,    3,    3,    3,    3,    1,
    1,    1,    1,    1,    1,    1,    3,    6,
};
static const YYINT wqldefred[] = {                        0,
    0,    0,    5,    3,    0,    0,    0,    0,    0,    6,
    0,    0,   24,    0,   20,   21,   22,   23,    0,    0,
   25,    0,   11,    8,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   19,    7,    0,
   14,   15,   13,   16,   12,   17,   18,    0,    9,    0,
    0,   28,
};
static const YYINT wqldgoto[] = {                         2,
   20,   21,    5,   22,    6,   23,
};
static const YYINT wqlsindex[] = {                     -259,
  -35,    0,    0,    0, -249,  -27, -254, -251, -243,    0,
  -40,  -40,    0, -252,    0,    0,    0,    0,  -40, -255,
    0, -240,    0,    0, -247, -245,  -37, -227, -227, -227,
 -227, -227, -227, -227,  -40,  -40, -224,    0,    0, -221,
    0,    0,    0,    0,    0,    0,    0, -222,    0, -219,
 -235,    0,
};
static const YYINT wqlrindex[] = {                        0,
    0,    0,    0,    0,    0, -223,    0,    0,   43,    0,
    0,    0,    0, -236,    0,    0,    0,    0,    0,    0,
    0,   46,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    1,    0,    0,    3,
    0,    0,    0,    0,    0,    0,    0,    6,    0,    0,
    0,    0,
};
static const YYINT wqlgindex[] = {                        0,
   25,    0,    0,  -10,    0,    0,
};
#define YYTABLESIZE 274
static const YYINT wqltable[] = {                        19,
   27,   24,   26,   39,   25,   10,    4,   28,   27,   29,
    1,   30,   31,   32,    7,   33,    8,   34,   35,   36,
    9,   26,   11,   10,   48,   49,   26,   37,   26,   38,
   26,   26,   26,   50,   26,   25,   26,   36,   51,   52,
    4,   27,    1,   26,   13,    2,   10,   40,   15,   16,
   17,   18,   41,   42,   43,   44,   45,   46,   47,    0,
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
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   12,   35,   36,    0,    0,    0,    0,    0,    0,    0,
    0,   13,    0,    0,   14,   15,   16,   17,   18,    3,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   27,
   27,   26,   26,   27,   10,   27,    0,   27,   27,   27,
    0,   27,    0,   27,
};
static const YYINT wqlcheck[] = {                        40,
    0,   12,    0,   41,  257,    0,   42,  263,   19,  265,
  270,  267,  268,  269,  264,  271,   44,  273,  259,  260,
  275,  274,  266,  275,   35,   36,  263,  275,  265,  275,
  267,  268,  269,  258,  271,  257,  273,  260,  258,  275,
  264,   41,    0,   41,  272,    0,   41,  275,  276,  277,
  278,  279,   28,   29,   30,   31,   32,   33,   34,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  261,  259,  260,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  272,   -1,   -1,  275,  276,  277,  278,  279,  275,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  259,
  260,  259,  260,  263,  259,  265,   -1,  267,  268,  269,
   -1,  271,   -1,  273,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 279
#define YYUNDFTOKEN 288
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const wqlname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'",0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"WQL_DOT",
"WQL_COLON","WQL_OR","WQL_AND","WQL_NOT","WQL_ERROR","WQL_LT","WQL_FROM",
"WQL_LE","WQL_WHERE","WQL_NE","WQL_GT","WQL_EQ","WQL_SELECT","WQL_GE",
"WQL_NULL","WQL_LIKE","WQL_ISA","WQL_IDENTIFIER","WQL_BOOLEAN","WQL_INTEGER",
"WQL_REAL","WQL_STRING",0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const wqlrule[] = {
"$accept : Start",
"Start : WQL_SELECT SelectList WQL_FROM WQL_IDENTIFIER",
"Start : WQL_SELECT SelectList WQL_FROM WQL_IDENTIFIER WQL_WHERE Condition",
"SelectList : '*'",
"SelectList : PropertyList",
"PropertyList : WQL_IDENTIFIER",
"PropertyList : PropertyList ',' WQL_IDENTIFIER",
"Condition : '(' Condition ')'",
"Condition : WQL_NOT Condition",
"Condition : Condition WQL_AND Condition",
"Condition : Condition WQL_OR Condition",
"Condition : Predicate",
"Predicate : Operand WQL_EQ Operand",
"Predicate : Operand WQL_NE Operand",
"Predicate : Operand WQL_LT Operand",
"Predicate : Operand WQL_LE Operand",
"Predicate : Operand WQL_GT Operand",
"Predicate : Operand WQL_GE Operand",
"Predicate : Operand WQL_LIKE Operand",
"Predicate : WQL_IDENTIFIER WQL_ISA WQL_IDENTIFIER",
"Operand : WQL_BOOLEAN",
"Operand : WQL_INTEGER",
"Operand : WQL_REAL",
"Operand : WQL_STRING",
"Operand : WQL_NULL",
"Operand : Property",
"Property : WQL_IDENTIFIER",
"Property : WQL_IDENTIFIER WQL_DOT WQL_IDENTIFIER",
"Property : WQL_IDENTIFIER WQL_DOT WQL_IDENTIFIER WQL_COLON WQL_COLON WQL_IDENTIFIER",

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
#line 70 "wql.y"
	{
        YACCTRACE(Start1);
        wqlstate.wql->className = yystack.l_mark[0].string;
    }
break;
case 2:
#line 75 "wql.y"
	{
        YACCTRACE(Start2);
        wqlstate.wql->className = yystack.l_mark[-2].string;
    }
break;
case 3:
#line 82 "wql.y"
	{
        YACCTRACE(SelectList1);
    }
break;
case 4:
#line 86 "wql.y"
	{
        YACCTRACE(SelectList2);
    }
break;
case 5:
#line 92 "wql.y"
	{
        YACCTRACE(PropertyList1);

        if (wqlstate.wql->nproperties == WQL_MAX_PROPERTIES)
        {
            yyerror("property array overflow");
            YYABORT;
        }

        wqlstate.wql->properties[wqlstate.wql->nproperties++] = yystack.l_mark[0].string;
    }
break;
case 6:
#line 104 "wql.y"
	{
        YACCTRACE(PropertyList2);

        if (wqlstate.wql->nproperties == WQL_MAX_PROPERTIES)
        {
            yyerror("property array overflow");
            YYABORT;
        }

        wqlstate.wql->properties[wqlstate.wql->nproperties++] = yystack.l_mark[0].string;
    }
break;
case 7:
#line 118 "wql.y"
	{
        YACCTRACE(Condition1);
    }
break;
case 8:
#line 122 "wql.y"
	{
        WQL_Symbol operator;

        YACCTRACE(Condition2);

        if (wqlstate.wql->nsymbols == WQL_MAX_SYMBOLS)
        {
            yyerror("symbol array overflow");
            YYABORT;
        }

        memset(&operator, 0, sizeof(WQL_Symbol));
        operator.type = WQL_TYPE_NOT;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
break;
case 9:
#line 138 "wql.y"
	{
        WQL_Symbol operator;

        YACCTRACE(Condition3);

        if (wqlstate.wql->nsymbols == WQL_MAX_SYMBOLS)
        {
            yyerror("symbol array overflow");
            YYABORT;
        }

        memset(&operator, 0, sizeof(WQL_Symbol));
        operator.type = WQL_TYPE_AND;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
break;
case 10:
#line 154 "wql.y"
	{
        WQL_Symbol operator;

        YACCTRACE(Condition4);

        if (wqlstate.wql->nsymbols == WQL_MAX_SYMBOLS)
        {
            yyerror("symbol array overflow");
            YYABORT;
        }

        memset(&operator, 0, sizeof(WQL_Symbol));
        operator.type = WQL_TYPE_OR;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
break;
case 11:
#line 170 "wql.y"
	{
        YACCTRACE(Condition5);
    }
break;
case 12:
#line 176 "wql.y"
	{
        WQL_Symbol operator;

        YACCTRACE(Predicate1);

        if (wqlstate.wql->nsymbols + 3 > WQL_MAX_SYMBOLS)
        {
            yyerror("symbol array overflow");
            YYABORT;
        }

        memset(&operator, 0, sizeof(WQL_Symbol));
        operator.type = WQL_TYPE_EQ;

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[0].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
break;
case 13:
#line 195 "wql.y"
	{
        WQL_Symbol operator;

        YACCTRACE(Predicate2);

        if (wqlstate.wql->nsymbols + 3 > WQL_MAX_SYMBOLS)
        {
            yyerror("symbol array overflow");
            YYABORT;
        }

        memset(&operator, 0, sizeof(WQL_Symbol));
        operator.type = WQL_TYPE_NE;

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[0].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
break;
case 14:
#line 214 "wql.y"
	{
        WQL_Symbol operator;

        YACCTRACE(Predicate3);

        if (wqlstate.wql->nsymbols + 3 > WQL_MAX_SYMBOLS)
        {
            yyerror("symbol array overflow");
            YYABORT;
        }

        memset(&operator, 0, sizeof(WQL_Symbol));
        operator.type = WQL_TYPE_LT;

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[0].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
break;
case 15:
#line 233 "wql.y"
	{
        WQL_Symbol operator;

        YACCTRACE(Predicate4);

        if (wqlstate.wql->nsymbols + 3 > WQL_MAX_SYMBOLS)
        {
            yyerror("symbol array overflow");
            YYABORT;
        }

        memset(&operator, 0, sizeof(WQL_Symbol));
        operator.type = WQL_TYPE_LE;

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[0].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
break;
case 16:
#line 252 "wql.y"
	{
        WQL_Symbol operator;

        YACCTRACE(Predicate5);

        if (wqlstate.wql->nsymbols + 3 > WQL_MAX_SYMBOLS)
        {
            yyerror("symbol array overflow");
            YYABORT;
        }

        memset(&operator, 0, sizeof(WQL_Symbol));
        operator.type = WQL_TYPE_GT;

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[0].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
break;
case 17:
#line 271 "wql.y"
	{
        WQL_Symbol operator;

        YACCTRACE(Predicate6);

        if (wqlstate.wql->nsymbols + 3 > WQL_MAX_SYMBOLS)
        {
            yyerror("symbol array overflow");
            YYABORT;
        }

        memset(&operator, 0, sizeof(WQL_Symbol));
        operator.type = WQL_TYPE_GE;

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[0].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
break;
case 18:
#line 290 "wql.y"
	{
        WQL_Symbol operator;

        YACCTRACE(Predicate6);

        /* Only WQL LIKE is supported */
        if (wqlstate.wql->dialect != WQL_DIALECT_WQL)
        {
            yyerror("CQL LIKE not supported");
            YYABORT;
        }

        if (wqlstate.wql->nsymbols + 3 > WQL_MAX_SYMBOLS)
        {
            yyerror("symbol array overflow");
            YYABORT;
        }

        memset(&operator, 0, sizeof(WQL_Symbol));
        operator.type = WQL_TYPE_LIKE;

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yystack.l_mark[0].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
break;
case 19:
#line 316 "wql.y"
	{
        WQL_Symbol lhs;
        WQL_Symbol rhs;
        WQL_Symbol operator;

        YACCTRACE(Predicate7);

        /* Check for symbol stack overflow */
        if (wqlstate.wql->nsymbols + 3 > WQL_MAX_SYMBOLS)
        {
            yyerror("symbol array overflow");
            YYABORT;
        }

        /* Left-hand-side (embedded property name) */
        memset(&lhs, 0, sizeof(WQL_Symbol));
        lhs.value.string = yystack.l_mark[-2].string;
        lhs.type = WQL_TYPE_STRING;

        /* Right-hand-side (embedded class name) */
        memset(&rhs, 0, sizeof(WQL_Symbol));
        rhs.value.string = yystack.l_mark[0].string;
        rhs.type = WQL_TYPE_STRING;

        /* Operator */
        memset(&operator, 0, sizeof(WQL_Symbol));
        operator.type = WQL_TYPE_ISA;

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = lhs;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = rhs;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
break;
case 20:
#line 351 "wql.y"
	{
        YACCTRACE(Operand1);
        yyval.symbol.value.boolean = yystack.l_mark[0].boolean;
        yyval.symbol.type = WQL_TYPE_BOOLEAN;
    }
break;
case 21:
#line 357 "wql.y"
	{
        YACCTRACE(Operand2);
        yyval.symbol.value.integer = yystack.l_mark[0].integer;
        yyval.symbol.type = WQL_TYPE_INTEGER;
    }
break;
case 22:
#line 363 "wql.y"
	{
        YACCTRACE(Operand3);
        yyval.symbol.value.real = yystack.l_mark[0].real;
        yyval.symbol.type = WQL_TYPE_REAL;
    }
break;
case 23:
#line 369 "wql.y"
	{
        YACCTRACE(Operand4);
        yyval.symbol.value.string = yystack.l_mark[0].string;
        yyval.symbol.type = WQL_TYPE_STRING;
    }
break;
case 24:
#line 375 "wql.y"
	{
        YACCTRACE(Operand6);
        yyval.symbol.value.integer = 0;
        yyval.symbol.type = WQL_TYPE_NULL;
    }
break;
case 25:
#line 381 "wql.y"
	{
        YACCTRACE(Operand7);
        yyval.symbol = yystack.l_mark[0].symbol;
    }
break;
case 26:
#line 388 "wql.y"
	{
        YACCTRACE(Property1);
        yyval.symbol.value.string = yystack.l_mark[0].string;
        yyval.symbol.value.embeddedClassName = NULL;
        yyval.symbol.value.embeddedPropertyName = NULL;
        yyval.symbol.type = WQL_TYPE_IDENTIFIER;
    }
break;
case 27:
#line 396 "wql.y"
	{
        MI_Char* str;
        YACCTRACE(Property2);

        yyval.symbol.value.string = yystack.l_mark[-2].string;
        yyval.symbol.value.embeddedClassName = NULL;
        yyval.symbol.value.embeddedPropertyName = yystack.l_mark[0].string;
        yyval.symbol.type = WQL_TYPE_IDENTIFIER;
    }
break;
case 28:
#line 406 "wql.y"
	{
        MI_Char* str;
        YACCTRACE(Property2);

        yyval.symbol.value.string = yystack.l_mark[-5].string;
        yyval.symbol.value.embeddedClassName = yystack.l_mark[-3].string;
        yyval.symbol.value.embeddedPropertyName = yystack.l_mark[0].string;
        yyval.symbol.type = WQL_TYPE_IDENTIFIER;
    }
break;
#line 978 "y.tab.c"
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
