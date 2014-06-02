%{

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

%}

%union
{
    WQL_Symbol symbol;
    MI_Char* string;
    long long integer;
    double real;
    unsigned char boolean;
}

%left WQL_DOT
%left WQL_COLON
%left WQL_OR
%left WQL_AND
%nonassoc WQL_NOT

%token WQL_ERROR
%token WQL_LT
%token WQL_FROM
%token WQL_LE
%token WQL_WHERE
%token WQL_NE
%token WQL_GT
%token WQL_EQ
%token WQL_SELECT
%token WQL_GE
%token WQL_NULL
%token WQL_LIKE
%token WQL_ISA
%token WQL_DOT
%token WQL_COLON

%token <string> WQL_IDENTIFIER;
%token <boolean> WQL_BOOLEAN;
%token <integer> WQL_INTEGER;
%token <real> WQL_REAL;
%token <string> WQL_STRING;

%type <symbol> Operand;

%type <symbol> Property;

%%

Start
    : WQL_SELECT SelectList WQL_FROM WQL_IDENTIFIER
    {
        YACCTRACE(Start1);
        wqlstate.wql->className = $4;
    }
    | WQL_SELECT SelectList WQL_FROM WQL_IDENTIFIER WQL_WHERE Condition
    {
        YACCTRACE(Start2);
        wqlstate.wql->className = $4;
    }

SelectList
    : '*'
    {
        YACCTRACE(SelectList1);
    }
    | PropertyList
    {
        YACCTRACE(SelectList2);
    }

PropertyList
    : WQL_IDENTIFIER
    {
        YACCTRACE(PropertyList1);

        if (wqlstate.wql->nproperties == WQL_MAX_PROPERTIES)
        {
            yyerror("property array overflow");
            YYABORT;
        }

        wqlstate.wql->properties[wqlstate.wql->nproperties++] = $1;
    }
    | PropertyList ',' WQL_IDENTIFIER
    {
        YACCTRACE(PropertyList2);

        if (wqlstate.wql->nproperties == WQL_MAX_PROPERTIES)
        {
            yyerror("property array overflow");
            YYABORT;
        }

        wqlstate.wql->properties[wqlstate.wql->nproperties++] = $3;
    }

Condition
    : '(' Condition ')'
    {
        YACCTRACE(Condition1);
    }
    | WQL_NOT Condition
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
    | Condition WQL_AND Condition
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
    | Condition WQL_OR Condition
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
    | Predicate
    {
        YACCTRACE(Condition5);
    }

Predicate
    : Operand WQL_EQ Operand
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $1;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $3;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
    | Operand WQL_NE Operand
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $1;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $3;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
    | Operand WQL_LT Operand
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $1;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $3;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
    | Operand WQL_LE Operand
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $1;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $3;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
    | Operand WQL_GT Operand
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $1;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $3;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
    | Operand WQL_GE Operand
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $1;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $3;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
    | Operand WQL_LIKE Operand
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

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $1;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = $3;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }
    | WQL_IDENTIFIER WQL_ISA WQL_IDENTIFIER
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
        lhs.value.string = $1;
        lhs.type = WQL_TYPE_STRING;

        /* Right-hand-side (embedded class name) */
        memset(&rhs, 0, sizeof(WQL_Symbol));
        rhs.value.string = $3;
        rhs.type = WQL_TYPE_STRING;

        /* Operator */
        memset(&operator, 0, sizeof(WQL_Symbol));
        operator.type = WQL_TYPE_ISA;

        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = lhs;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = rhs;
        wqlstate.wql->symbols[wqlstate.wql->nsymbols++] = operator;
    }

Operand
    : WQL_BOOLEAN
    {
        YACCTRACE(Operand1);
        $$.value.boolean = $1;
        $$.type = WQL_TYPE_BOOLEAN;
    }
    | WQL_INTEGER
    {
        YACCTRACE(Operand2);
        $$.value.integer = $1;
        $$.type = WQL_TYPE_INTEGER;
    }
    | WQL_REAL
    {
        YACCTRACE(Operand3);
        $$.value.real = $1;
        $$.type = WQL_TYPE_REAL;
    }
    | WQL_STRING
    {
        YACCTRACE(Operand4);
        $$.value.string = $1;
        $$.type = WQL_TYPE_STRING;
    }
    | WQL_NULL
    {
        YACCTRACE(Operand6);
        $$.value.integer = 0;
        $$.type = WQL_TYPE_NULL;
    }
    | Property
    {
        YACCTRACE(Operand7);
        $$ = $1;
    }

Property
    : WQL_IDENTIFIER
    {
        YACCTRACE(Property1);
        $$.value.string = $1;
        $$.value.embeddedClassName = NULL;
        $$.value.embeddedPropertyName = NULL;
        $$.type = WQL_TYPE_IDENTIFIER;
    }
    | WQL_IDENTIFIER WQL_DOT WQL_IDENTIFIER
    {
        MI_Char* str;
        YACCTRACE(Property2);

        $$.value.string = $1;
        $$.value.embeddedClassName = NULL;
        $$.value.embeddedPropertyName = $3;
        $$.type = WQL_TYPE_IDENTIFIER;
    }
    | WQL_IDENTIFIER WQL_DOT WQL_IDENTIFIER WQL_COLON WQL_COLON WQL_IDENTIFIER
    {
        MI_Char* str;
        YACCTRACE(Property2);

        $$.value.string = $1;
        $$.value.embeddedClassName = $3;
        $$.value.embeddedPropertyName = $6;
        $$.type = WQL_TYPE_IDENTIFIER;
    }
