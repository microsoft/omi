#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define yyparse wqlparse
#define yylex wqllex
#define yyerror wqlerror
#define yychar wqlchar
#define yyval wqlval
#define yylval wqllval
#define yydebug wqldebug
#define yynerrs wqlnerrs
#define yyerrflag wqlerrflag
#define yyss wqlss
#define yyssp wqlssp
#define yyvs wqlvs
#define yyvsp wqlvsp
#define yylhs wqllhs
#define yylen wqllen
#define yydefred wqldefred
#define yydgoto wqldgoto
#define yysindex wqlsindex
#define yyrindex wqlrindex
#define yygindex wqlgindex
#define yytable wqltable
#define yycheck wqlcheck
#define yyname wqlname
#define yyrule wqlrule
#define YYPREFIX "wql"
#line 1 "wql.y"


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
typedef union
{
    WQL_Symbol symbol;
    MI_Char* string;
    long long integer;
    double real;
    unsigned char boolean;
} YYSTYPE;
#line 79 "y.tab.c"
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
short wqllhs[] = {                                        -1,
    0,    0,    3,    3,    5,    5,    4,    4,    4,    4,
    4,    6,    6,    6,    6,    6,    6,    6,    6,    1,
    1,    1,    1,    1,    1,    2,    2,    2,
};
short wqllen[] = {                                         2,
    4,    6,    1,    1,    1,    3,    3,    2,    3,    3,
    1,    3,    3,    3,    3,    3,    3,    3,    3,    1,
    1,    1,    1,    1,    1,    1,    3,    6,
};
short wqldefred[] = {                                      0,
    0,    0,    5,    3,    0,    0,    0,    0,    0,    6,
    0,    0,   24,    0,   20,   21,   22,   23,    0,    0,
   25,    0,   11,    8,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   19,    7,    0,
   14,   15,   13,   16,   12,   17,   18,    0,    9,    0,
    0,   28,
};
short wqldgoto[] = {                                       2,
   20,   21,    5,   22,    6,   23,
};
short wqlsindex[] = {                                   -259,
  -35,    0,    0,    0, -249,  -27, -254, -251, -243,    0,
  -40,  -40,    0, -252,    0,    0,    0,    0,  -40, -255,
    0, -240,    0,    0, -247, -245,  -37, -227, -227, -227,
 -227, -227, -227, -227,  -40,  -40, -224,    0,    0, -221,
    0,    0,    0,    0,    0,    0,    0, -222,    0, -219,
 -235,    0,
};
short wqlrindex[] = {                                      0,
    0,    0,    0,    0,    0, -223,    0,    0,   43,    0,
    0,    0,    0, -236,    0,    0,    0,    0,    0,    0,
    0,   46,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    1,    0,    0,    3,
    0,    0,    0,    0,    0,    0,    0,    6,    0,    0,
    0,    0,
};
short wqlgindex[] = {                                      0,
   25,    0,    0,  -10,    0,    0,
};
#define YYTABLESIZE 274
short wqltable[] = {                                      19,
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
short wqlcheck[] = {                                      40,
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
#if YYDEBUG
char *wqlname[] = {
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
"WQL_REAL","WQL_STRING",
};
char *wqlrule[] = {
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
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)PAL_Realloc(yyss, newsize * sizeof(*newss))
          : (short *)PAL_Malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)PAL_Realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)PAL_Malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

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

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

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
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
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

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
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
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 70 "wql.y"
{
        YACCTRACE(Start1);
        wqlstate.wql->className = yyvsp[0].string;
    }
break;
case 2:
#line 75 "wql.y"
{
        YACCTRACE(Start2);
        wqlstate.wql->className = yyvsp[-2].string;
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

        wqlstate.wql->properties[wqlstate.wql->nproperties++] = yyvsp[0].string;
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

        wqlstate.wql->properties[wqlstate.wql->nproperties++] = yyvsp[0].string;
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[0].symbol;
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[0].symbol;
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[0].symbol;
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[0].symbol;
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[0].symbol;
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[0].symbol;
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[-2].symbol;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = yyvsp[0].symbol;
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
        lhs.value.string = yyvsp[-2].string;
        lhs.type = WQL_TYPE_STRING;

        /* Right-hand-side (embedded class name) */
        memset(&rhs, 0, sizeof(WQL_Symbol));
        rhs.value.string = yyvsp[0].string;
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
        yyval.symbol.value.boolean = yyvsp[0].boolean;
        yyval.symbol.type = WQL_TYPE_BOOLEAN;
    }
break;
case 21:
#line 357 "wql.y"
{
        YACCTRACE(Operand2);
        yyval.symbol.value.integer = yyvsp[0].integer;
        yyval.symbol.type = WQL_TYPE_INTEGER;
    }
break;
case 22:
#line 363 "wql.y"
{
        YACCTRACE(Operand3);
        yyval.symbol.value.real = yyvsp[0].real;
        yyval.symbol.type = WQL_TYPE_REAL;
    }
break;
case 23:
#line 369 "wql.y"
{
        YACCTRACE(Operand4);
        yyval.symbol.value.string = yyvsp[0].string;
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
        yyval.symbol = yyvsp[0].symbol;
    }
break;
case 26:
#line 388 "wql.y"
{
        YACCTRACE(Property1);
        yyval.symbol.value.string = yyvsp[0].string;
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

        yyval.symbol.value.string = yyvsp[-2].string;
        yyval.symbol.value.embeddedClassName = NULL;
        yyval.symbol.value.embeddedPropertyName = yyvsp[0].string;
        yyval.symbol.type = WQL_TYPE_IDENTIFIER;
    }
break;
case 28:
#line 406 "wql.y"
{
        MI_Char* str;
        YACCTRACE(Property2);

        yyval.symbol.value.string = yyvsp[-5].string;
        yyval.symbol.value.embeddedClassName = yyvsp[-3].string;
        yyval.symbol.value.embeddedPropertyName = yyvsp[0].string;
        yyval.symbol.type = WQL_TYPE_IDENTIFIER;
    }
break;
#line 859 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
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
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
