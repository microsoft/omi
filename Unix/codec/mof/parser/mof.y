%{

#include "mofy.redef.h"
#include "mofcommon.h"
#include "buffer.h"
#include "types.h"
#include "ptrarray.h"
#include "utility.h"

#define ARRAYOF(TYPE) ((MI_Uint32)TYPE | (MI_Uint32)MI_ARRAY_BIT)


extern int yylex(void);
extern int openIncludeFile(const MI_Char* path);
%}

%union
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
}

%start mofSpecification

%token TOK_ERROR
%token TOK_BOOLEAN
%token TOK_SINT8
%token TOK_UINT8
%token TOK_SINT16
%token TOK_UINT16
%token TOK_SINT32
%token TOK_UINT32
%token TOK_SINT64
%token TOK_UINT64
%token TOK_REAL32
%token TOK_REAL64
%token TOK_DATETIME
%token TOK_CHAR16
%token TOK_STRING
%token TOK_BOOLEAN_VALUE
%token TOK_REF
%token TOK_SCOPE
%token TOK_CLASS
%token TOK_ASSOCIATION
%token TOK_INDICATION
%token TOK_QUALIFIER
%token TOK_PROPERTY
%token TOK_REFERENCE
%token TOK_METHOD
%token TOK_PARAMETER
%token TOK_ANY
%token TOK_FLAVOR
%token TOK_ENABLEOVERRIDE
%token TOK_DISABLEOVERRIDE
%token TOK_RESTRICTED
%token TOK_TOSUBCLASS
%token TOK_TRANSLATABLE
%token TOK_INSTANCE
%token TOK_OF
%token TOK_AS
%token TOK_PRAGMA
%token TOK_SCHEMA
%token TOK_INTEGER_VALUE
%token TOK_REAL_VALUE
%token TOK_STRING_VALUE
%token TOK_CHAR_VALUE
%token TOK_IDENT
%token TOK_ALIAS_IDENTIFIER
%token TOK_NULL
%token TOK_TOINSTANCE /*WMI specific*/

%type <string> stringValue
%type <string> TOK_STRING_VALUE
%type <string> identifier
%type <string> objectRef
%type <integer> TOK_INTEGER_VALUE
%type <real> TOK_REAL_VALUE
%type <character> TOK_CHAR_VALUE
%type <boolean> TOK_BOOLEAN_VALUE
%type <string> TOK_IDENT
%type <string> TOK_ALIAS_IDENTIFIER
%type <string> alias
%type <constantValue> constantValue
%type <type> dataType
%type <property> propertyDeclaration
%type <parameter> parameter
%type <parameterList> parameterList
%type <property> referenceDeclaration
%type <methodDecl> methodDeclaration 
%type <featureList> classFeatureList
%type <featureList> classBody
%type <featureList> instanceBody
%type <qualifierDeclaration> qualifierDeclaration
%type <qualifierDeclaration> qualifierType
%type <integer> subscript
%type <initializer> initializer
%type <initializer> arrayInitializer
%type <initializer> arrayInitializerList
%type <flags> scope
%type <flags> scopeList
%type <flags> scopeExpr
%type <flags> flavor
%type <flags> flavorList
%type <flags> flavorExpr
%type <qualifier> qualifier
%type <qualifierList> qualifierList
%type <qualifierList> qualifierExpr
%type <initializer> qualifierParameter
%type <classDeclaration> classDeclaration
%type <instanceDeclaration> instanceDeclaration
%type <property> valueInitializer
%type <featureList> valueInitializerList 

%%

mofSpecification
    : mofProduction
    {
    }
    | mofSpecification mofProduction
    { 
    }
    | TOK_ERROR
    {
        YYABORT;
    }

mofProduction
    : compilerDirective
    {
    }
    | classDeclaration
    {
        /* [TODO: validate the class here] */
        $1->flags = MI_FLAG_CLASS;
        $1->flags |= GetQualFlags(state, $1->qualifiers, $1->numQualifiers);
        if (FinalizeClass(state, $1) != 0)
            YYABORT;
            
        if (AddClassDecl(state, $1) != 0)
            YYABORT;
    }
    | qualifierDeclaration
    {
        AddQualifierDeclaration(state, $1);
    }
    | instanceDeclaration
    {
        if (FinalizeInstance(state, $1) != 0)
            YYABORT;

        if (AddInstanceDecl(state, $1) != 0)
            YYABORT;
    }

compilerDirective
    : TOK_PRAGMA TOK_IDENT '(' stringValue ')'
    {
        if (Tcscmp($2, MI_T("include")) == 0)
        {
            if (openIncludeFile(state, $4) != 0)
                YYABORT;
        }
        else if (Tcscmp($2, MI_T("instancelocale")) == 0)
        {
            if (state->pragmaCallback)
                (*state->pragmaCallback)($2, $4, state->pragmaCallbackData);
        }
        else if (Tcscmp($2, MI_T("locale")) == 0)
        {
            if (state->pragmaCallback)
                (*state->pragmaCallback)($2, $4, state->pragmaCallbackData);
        }
        else if (Tcscmp($2, MI_T("namespace")) == 0)
        {
            if (state->pragmaCallback)
                (*state->pragmaCallback)($2, $4, state->pragmaCallbackData);
        }
        else
        {
            yywarnf(state->errhandler, ID_UNKNOWN_PRAGMA, 
                "warning: unknown pragma: %s=%s", $2, $4);

            if (state->pragmaCallback)
                (*state->pragmaCallback)($2, $4, state->pragmaCallbackData);
        }
    }

classDeclaration
    : TOK_CLASS identifier classBody
    {
        /* Check whether class already exists */
        if (FindClassDeclBufferOnly(state, $2))
        {
            yyerrorf(state->errhandler, ID_CLASS_ALREADY_DEFINED, 
                "class already defined: \"%s\"", $2);
            YYABORT;
        }

        $$ = CALLOC_T(MI_ClassDecl, 1);
        $$->flags = MI_FLAG_CLASS;
        $$->name = $2;
        $$->properties = $3.propertySet.data;
        $$->numProperties = $3.propertySet.size;
        $$->methods = $3.methodList.data;
        $$->numMethods = $3.methodList.size;
    }
    | TOK_CLASS identifier ':' identifier classBody
    {
        const MI_ClassDecl* scd;

        /* Check whether class already exists */
        if (FindClassDeclBufferOnly(state, $2))
        {
            yyerrorf(state->errhandler, ID_CLASS_ALREADY_DEFINED, 
                "class already defined: \"%s\"", $2);
            YYABORT;
        }
 
        /* Check whether superclass exists */
        scd = FindClassDecl(state, $4);

        if (!scd)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_SUPERCLASS, 
                "super class of \"%s\" is undefined: \"%s\"", $2, $4);
            YYABORT;
        }

        $$ = CALLOC_T(MI_ClassDecl, 1);
        $$->flags = MI_FLAG_CLASS;
        $$->name = $2;
        $$->superClass = $4;
        $$->superClassDecl = (MI_ClassDecl*)scd;
        $$->properties = $5.propertySet.data;
        $$->numProperties = $5.propertySet.size;
        $$->methods = $5.methodList.data;
        $$->numMethods = $5.methodList.size;
    }
    | qualifierExpr TOK_CLASS identifier classBody
    {
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_CLASS, &$1) != 0)
            YYABORT;

        /* Check whether class already exists */
        if (FindClassDeclBufferOnly(state, $3))
        {
            yyerrorf(state->errhandler, ID_CLASS_ALREADY_DEFINED, 
                "class already defined: \"%s\"", $3);
            YYABORT;
        }

        $$ = CALLOC_T(MI_ClassDecl, 1);
        $$->flags = MI_FLAG_CLASS;
        $$->name = $3;
        $$->properties = $4.propertySet.data;
        $$->numProperties = $4.propertySet.size;
        $$->methods = $4.methodList.data;
        $$->numMethods = $4.methodList.size;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | qualifierExpr TOK_CLASS identifier ':' identifier classBody
    {
        const MI_ClassDecl* scd;

        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_CLASS, &$1) != 0)
            YYABORT;

        /* Check whether class already exists */
        if (FindClassDeclBufferOnly(state, $3))
        {
            yyerrorf(state->errhandler, ID_CLASS_ALREADY_DEFINED, 
                "class already defined: \"%s\"", $3);
            YYABORT;
        }

        /* Check whether superclass exists */
        scd = FindClassDecl(state, $5);

        if (!scd)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_SUPERCLASS, 
                "super class of \"%s\" is undefined: \"%s\"", $3, $5);
            YYABORT;
        }

        $$ = CALLOC_T(MI_ClassDecl, 1);
        $$->flags = MI_FLAG_CLASS;
        $$->name = $3;
        $$->superClass = scd->name;
        $$->superClassDecl = (MI_ClassDecl*)scd;
        $$->properties = $6.propertySet.data;
        $$->numProperties = $6.propertySet.size;
        $$->methods = $6.methodList.data;
        $$->numMethods = $6.methodList.size;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }

classBody
    : '{' classFeatureList '}' ';'
    {
        $$ = $2;
    }
    | '{' '}' ';'
    {
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $$.methodList.data = NULL;
        $$.methodList.size = 0;
    }

classFeatureList
    : propertyDeclaration
    {
        if (CheckPropertyValueConstraints(state, $1) != 0)
        {
            YYABORT;
        }
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $$.methodList.data = NULL;
        $$.methodList.size = 0;
        $1->flags = MI_FLAG_PROPERTY;
        $1->flags |= GetQualFlags(state, $1->qualifiers, $1->numQualifiers);
        if (Codec_PtrArray_Append(state, (Codec_PtrArray*)&$$.propertySet, $1) != 0)
        {
            YYABORT;
        }
    }
    | methodDeclaration
    {
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $$.methodList.data = NULL;
        $$.methodList.size = 0;
        $1->flags = MI_FLAG_METHOD;
        $1->flags |= GetQualFlags(state, $1->qualifiers, $1->numQualifiers);
        if (Codec_PtrArray_Append(state, (Codec_PtrArray*)&$$.methodList, $1) != 0)
        {
            YYABORT;
        }
    }
    | referenceDeclaration
    {
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $$.methodList.data = NULL;
        $$.methodList.size = 0;
        $1->flags = MI_FLAG_PROPERTY;
        $1->flags |= GetQualFlags(state, $1->qualifiers, $1->numQualifiers);
        if (Codec_PtrArray_Append(state, (Codec_PtrArray*)&$$.propertySet, $1) !=0)
        {
            YYABORT;
        }
    }
    | classFeatureList propertyDeclaration
    {
        if (CheckPropertyValueConstraints(state, $2) != 0)
        {
            YYABORT;
        }

        if (FindProperty(&$1.propertySet, $2->name))
        {
            yyerrorf(state->errhandler, ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", $2->name);
            YYABORT;
        }

        $2->flags = MI_FLAG_PROPERTY;
        $2->flags |= GetQualFlags(state, $2->qualifiers, $2->numQualifiers);
        if (Codec_PtrArray_Append(state, (Codec_PtrArray*)&$$.propertySet, $2) != 0)
        {
            YYABORT;
        }
    }
    | classFeatureList methodDeclaration
    {
        if (FindMethod(&$1.methodList, $2->name))
        {
            yyerrorf(state->errhandler, ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", $2->name);
            YYABORT;
        }

        $2->flags = MI_FLAG_METHOD;
        $2->flags |= GetQualFlags(state, $2->qualifiers, $2->numQualifiers);
        if (Codec_PtrArray_Append(state, (Codec_PtrArray*)&$$.methodList, $2) != 0)
        {
            YYABORT;
        }
    }
    | classFeatureList referenceDeclaration
    {
        if (FindProperty(&$1.propertySet, $2->name))
        {
            yyerrorf(state->errhandler, ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", $2->name);
            YYABORT;
        }

        $2->flags = MI_FLAG_PROPERTY;
        $2->flags |= GetQualFlags(state, $2->qualifiers, $2->numQualifiers);
        if (Codec_PtrArray_Append(state, (Codec_PtrArray*)&$$.propertySet, $2) != 0)
        {
            YYABORT;
        }
    }

qualifierExpr
    : '[' qualifierList ']'
    {
        $$ = $2;
    }

qualifierList
    : qualifier
    {
        $$.data = NULL;
        $$.size = 0;
        if (Codec_PtrArray_Append(state, (Codec_PtrArray*)&$$, $1) != 0)
        {
            YYABORT;
        }
    }
    | qualifierList ',' qualifier
    {
        if (FindQualifier(&$1, $3->name))
        {
            yyerrorf(state->errhandler, ID_DUPLICATE_QUALIFIER, 
                "duplicate qualifier: \"%s\"", $3->name);
            YYABORT;
        }

        if (Codec_PtrArray_Append(state, (Codec_PtrArray*)&$$, $3) != 0)
        {
            YYABORT;
        }
    }

qualifier
    : identifier
    {
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;

        qd = FindQualifierDeclaration(state, $1);

        if (!qd)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", $1);
            YYABORT;
        }

        if (qd->type != MI_BOOLEAN)
        {
            yyerrorf(state->errhandler, ID_MISSING_QUALIFIER_INITIALIZER, 
                "qualifier is missing initializer: \"%s\"", $1);
            YYABORT;
        }
        
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = qd->flavor;
        q->value = NewTrueValue(state);
        $$ = q;
    }
    | identifier qualifierParameter
    {
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;
        void* value;

        qd = FindQualifierDeclaration(state, $1);

        if (!qd)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", $1);
            YYABORT;
        }

        if (InitializerToValue(state, &$2, qd->type, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_QUALIFIER_INITIALIZER, 
                "invalid initializer for qualifer: \"%s\"", $1);
            YYABORT;
        }
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = qd->flavor;
        q->value = value;
        $$ = q;
    }
    | identifier ':' flavor
    {
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;

        qd = FindQualifierDeclaration(state, $1);

        if (!qd)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", $1);
            YYABORT;
        }

        if (qd->type != MI_BOOLEAN)
        {
            yyerrorf(state->errhandler, ID_MISSING_QUALIFIER_INITIALIZER, 
                "qualifier is missing initializer: \"%s\"", $1);
            YYABORT;
        }
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = PropagateFlavors($3, qd->flavor);
        q->value = NewTrueValue(state);
        $$ = q;
    }
    | identifier qualifierParameter ':' flavor
    {
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;
        void* value;

        qd = FindQualifierDeclaration(state, $1);

        if (!qd)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", $1);
            YYABORT;
        }

        if (InitializerToValue(state, &$2, qd->type, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_QUALIFIER_INITIALIZER, 
                "invalid initializer for qualifer: \"%s\"", $1);
            YYABORT;
        }
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->value = value;
        q->flavor = PropagateFlavors($4, qd->flavor);
        $$ = q;
    }

qualifierParameter
    : '(' constantValue ')'
    {
        memset(&$$, 0, sizeof($$));
        $$.data = CALLOC_T(MOF_ConstantValue, 1);
        $$.data[0] = $2;
        $$.size = 1;
    }
    | arrayInitializer
    {
        $$ = $1;
    }

flavorList
    : flavor
    {
        $$ = $1;
    }
    | flavorList ',' flavor
    {
        $$ |= $3;
    }

flavor
    : TOK_ENABLEOVERRIDE
    {
        $$ = MI_FLAG_ENABLEOVERRIDE;
    }
    | TOK_DISABLEOVERRIDE
    {
        $$ = MI_FLAG_DISABLEOVERRIDE;
    }
    | TOK_RESTRICTED
    {
        $$ = MI_FLAG_RESTRICTED;
    }
    | TOK_TOSUBCLASS
    {
        $$ = MI_FLAG_TOSUBCLASS;
    }
    | TOK_TRANSLATABLE
    {
        $$ = MI_FLAG_TRANSLATABLE;
    }
    | TOK_TOINSTANCE
    {   /* WMI specific, ignore now */
        $$ = 0;
    }

propertyDeclaration
    : dataType identifier ';'
    {
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->name = $2;
        $$->type = $1;
    }
    | qualifierExpr dataType identifier ';'
    {
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PROPERTY, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->name = $3;
        $$->type = $2;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | dataType identifier subscript ';'
    {
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->name = $2;
        $$->type = ARRAYOF($1);
        $$->subscript = (MI_Uint32)$3;
    }
    | qualifierExpr dataType identifier subscript ';'
    {
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PROPERTY, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->name = $3;
        $$->type = ARRAYOF($2);
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        $$->subscript = (MI_Uint32)$4;
    }
    | dataType identifier '=' initializer ';'
    {
        void* value;

        if (InitializerToValue(state, &$4, $1, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->name = $2;
        $$->type = $1;
        $$->value = value;
    }
    | qualifierExpr dataType identifier '=' initializer ';'
    {
        void* value;

        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PROPERTY, &$1) != 0)
            YYABORT;

        if (InitializerToValue(state, &$5, $2, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->name = $3;
        $$->type = $2;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        $$->value = value;
    }
    | dataType identifier subscript '=' initializer ';'
    {
        void* value;

        if (InitializerToValue(state, &$5, ARRAYOF($1), &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->name = $2;
        $$->type = ARRAYOF($1);
        $$->subscript = (MI_Uint32)$3;
        $$->value = value;
    }
    | qualifierExpr dataType identifier subscript '=' initializer ';'
    {
        void* value;

        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PROPERTY, &$1) != 0)
            YYABORT;

        if (InitializerToValue(state, &$6, ARRAYOF($2), &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->name = $3;
        $$->type = ARRAYOF($2);
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        $$->subscript = (MI_Uint32)$4;
        $$->value = value;
    }

referenceDeclaration
    : objectRef identifier ';'
    {
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCE;
        $$->name = $2;
        $$->className = $1;
    }
    | qualifierExpr objectRef identifier ';'
    {
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCE;
        $$->name = $3;
        $$->className = $2;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | objectRef identifier initializer';'
    {
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCE;
        $$->name = $2;
        $$->className = $1;
        yywarnf(state->errhandler, ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* [TODO: use initializer */
    }
    | qualifierExpr objectRef identifier initializer ';'
    {
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCE;
        $$->name = $3;
        $$->className = $2;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        yywarnf(state->errhandler, ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* [TODO: use initializer] */
    }

methodDeclaration
    : dataType identifier '(' parameterList ')' ';'
    {
        $$ = CALLOC_T(MI_MethodDecl, 1);
        $$->name = $2;
        $$->parameters = CreateParameterSet(state, $4.data, $4.size, $1);
        if (!$$->parameters)
            YYABORT;
        $$->numParameters = $4.size + 1;
        $$->returnType = $1;
    }
    | qualifierExpr dataType identifier '(' parameterList ')' ';'
    {
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_METHOD, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_MethodDecl, 1);
        $$->name = $3;
        $$->parameters = CreateParameterSet(state, $5.data, $5.size, $2);
        if (!$$->parameters)
            YYABORT;
        $$->numParameters = $5.size + 1;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        $$->returnType = $2;
    }
    | dataType identifier '(' ')' ';'
    {
        MOF_ParameterList parameterList = PTRARRAY_INITIALIZER;

        $$ = CALLOC_T(MI_MethodDecl, 1);
        $$->name = $2;
        $$->parameters = CreateParameterSet(state, parameterList.data, parameterList.size, $1);
        if (!$$->parameters)
            YYABORT;
        $$->numParameters = parameterList.size + 1;
        $$->returnType = $1;
    }
    | qualifierExpr dataType identifier '(' ')' ';'
    {
        MOF_ParameterList parameterList = PTRARRAY_INITIALIZER;

        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_METHOD, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_MethodDecl, 1);
        $$->name = $3;
        $$->parameters = CreateParameterSet(state, parameterList.data, parameterList.size, $2);
        if (!$$->parameters)
            YYABORT;
        $$->numParameters = parameterList.size + 1;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        $$->returnType = $2;
    }

dataType
    : TOK_BOOLEAN
    {
        $$ = MI_BOOLEAN;
    }
    | TOK_SINT8
    {
        $$ = MI_SINT8;
    }
    | TOK_UINT8
    {
        $$ = MI_UINT8;
    }
    | TOK_SINT16
    {
        $$ = MI_SINT16;
    }
    | TOK_UINT16
    {
        $$ = MI_UINT16;
    }
    | TOK_SINT32
    {
        $$ = MI_SINT32;
    }
    | TOK_UINT32
    {
        $$ = MI_UINT32;
    }
    | TOK_SINT64
    {
        $$ = MI_SINT64;
    }
    | TOK_UINT64
    {
        $$ = MI_UINT64;
    }
    | TOK_REAL32
    {
        $$ = MI_REAL32;
    }
    | TOK_REAL64
    {
        $$ = MI_REAL64;
    }
    | TOK_CHAR16
    {
        $$ = MI_CHAR16;
    }
    | TOK_DATETIME
    {
        $$ = MI_DATETIME;
    }
    | TOK_STRING
    {
        $$ = MI_STRING;
    }

objectRef
    : identifier TOK_REF
    {
        $$ = $1;
    }

parameterList
    : parameter
    {
        $1->flags = MI_FLAG_PARAMETER;
        $1->flags |= GetQualFlags(state, $1->qualifiers, $1->numQualifiers);
        $$.data = NULL;
        $$.size = 0;
        if (Codec_PtrArray_Append(state, (Codec_PtrArray*)&$$, $1) != 0)
        {
            YYABORT;
        }
    }
    | parameterList ',' parameter
    {
        if (FindParameter(&$1, $3->name))
        {
            yyerrorf(state->errhandler, ID_PARAMETER_ALREADY_DEFINED, 
                "parameter already defined: \"%s\"", $3->name);
            YYABORT;
        }

        $3->flags = MI_FLAG_PARAMETER;
        $3->flags |= GetQualFlags(state, $3->qualifiers, $3->numQualifiers);
        if (Codec_PtrArray_Append(state, (Codec_PtrArray*)&$$, $3) != 0)
        {
            YYABORT;
        }
    }

parameter
    : dataType identifier
    {
        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $2;
        $$->type = $1;
    }
    | objectRef identifier
    {
        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $2;
        $$->type = MI_REFERENCE;
        $$->className = $1;
    }
    | qualifierExpr dataType identifier
    {
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PARAMETER, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $3;
        $$->type = $2;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | qualifierExpr objectRef identifier
    {
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PARAMETER, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $3;
        $$->type = MI_REFERENCE;
        $$->className = $2;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | dataType identifier subscript
    {
        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $2;
        $$->type = ARRAYOF($1);
        $$->subscript = (MI_Uint32)$3;
    }
    | objectRef identifier subscript
    {
        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $2;
        $$->type = ARRAYOF(MI_REFERENCE);
        $$->className = $1;
        $$->subscript = (MI_Uint32)$3;
    }
    | qualifierExpr dataType identifier subscript
    {
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PARAMETER, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $3;
        $$->type = ARRAYOF($2);
        $$->subscript = (MI_Uint32)$4;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | qualifierExpr objectRef identifier subscript
    {
        /* Check qualifier scope */
        if (CheckScope(state, MI_FLAG_PARAMETER, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $3;
        $$->type = ARRAYOF(MI_REFERENCE);
        $$->className = $2;
        $$->subscript = (MI_Uint32)$4;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }

subscript
    : '[' TOK_INTEGER_VALUE ']'
    {
        if ($2 <= 0)
        {
            yyerrorf(state->errhandler, ID_ILLEGAL_ARRAY_SUBSCRIPT, 
                "illegal array subscript: " SINT64_FMT, $2);
            YYABORT;
        }

        $$ = $2;
    }
    | '[' ']'
    {
        /* 0 signifies a dynamic array */
        $$ = 0;
    }

initializer
    : constantValue
    {
        memset(&$$, 0, sizeof($$));
        $$.data = CALLOC_T(MOF_ConstantValue, 1);
        $$.data[0] = $1;
        $$.size = 1;
    }
    | arrayInitializer
    {
        $$ = $1;
    }

arrayInitializer
    : '{' arrayInitializerList '}'
    {
        $$ = $2;
    }
    | '{' '}'
    {
        $$.data = NULL;
        $$.size = 0;
        $$.isArray = 1;
    }

arrayInitializerList
    : constantValue
    {
        memset(&$$, 0, sizeof($$));
        $$.data = CALLOC_T(MOF_ConstantValue, 1);
        $$.data[0] = $1;
        $$.size = 1;
        $$.isArray = 1;
    }
    | arrayInitializerList ',' constantValue
    {
        size_t orgsize = $1.size;
        $1.data = REALLOC_T(MOF_ConstantValue, $1.data, orgsize, orgsize + 1);
        // check return value
        $1.data[$1.size] = $3;
        $1.size++;
        $$ = $1;
    }

constantValue
    : TOK_INTEGER_VALUE
    {
        $$.type = TOK_INTEGER_VALUE;
        $$.value.integer = $1;
    }
    | TOK_REAL_VALUE
    {
        $$.type = TOK_REAL_VALUE;
        $$.value.real = $1;
    }
    | TOK_CHAR_VALUE
    {
        $$.type = TOK_CHAR_VALUE;
        $$.value.character = $1;
    }
    | stringValue
    {
        $$.type = TOK_STRING_VALUE;
        $$.value.string = $1;
    }
    | TOK_BOOLEAN_VALUE
    {
        $$.type = TOK_BOOLEAN_VALUE;
        $$.value.boolean = $1;
    }
    | TOK_NULL
    {
        $$.type = TOK_NULL;
    }
    | TOK_ALIAS_IDENTIFIER
    {
        $$.type = TOK_ALIAS_IDENTIFIER;
        $$.value.string = $1;
    }

stringValue
    : TOK_STRING_VALUE
    {
	$$ = $1;
    }
    | stringValue TOK_STRING_VALUE
    {
        size_t orgsize = Tcslen($1);
        size_t newsize = Tcslen($2) + 1;
        size_t tsize = orgsize+newsize;
        size_t orgbufsize = orgsize * sizeof(ZChar);
        size_t bufsize = tsize * sizeof(ZChar);
        $$ = (ZChar*)MOF_Realloc(state->batch, $1, orgbufsize, bufsize);
        Tcslcat($$, $2, tsize);
        /* MOF_Free(&state->heap, $2); */
    }

qualifierDeclaration
    : TOK_QUALIFIER identifier qualifierType scopeExpr ';'
    {
        $3->name = $2;
        $3->scope = $4;
        $3->flavor = 0;
        $$ = $3;
    }
    | TOK_QUALIFIER identifier qualifierType scopeExpr flavorExpr ';'
    {
        $3->name = $2;
        $3->scope = $4;
        $3->flavor = $5;
        $$ = $3;
    }

qualifierType
    : ':' dataType
    {
        $$ = CALLOC_T(MI_QualifierDecl, 1);
        $$->type = $2;
    }
    | ':' dataType '=' initializer
    {
        void* value;

        if (InitializerToValue(state, &$4, $2, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        $$ = CALLOC_T(MI_QualifierDecl, 1);
        $$->type = $2;
        $$->value = value;
        ReleaseInitializer(state, &$4);
    }
    | ':' dataType subscript
    {
        $$ = CALLOC_T(MI_QualifierDecl, 1);
        $$->type = ARRAYOF($2);
        $$->subscript = (MI_Uint32)$3;
    }
    | ':' dataType subscript '=' initializer
    {
        void* value = NULL;

        if (InitializerToValue(state, &$5, ARRAYOF($2), &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        $$ = CALLOC_T(MI_QualifierDecl, 1);
        $$->type = ARRAYOF($2);
        $$->subscript = (MI_Uint32)$3;
        $$->value = value;
        ReleaseInitializer(state, &$5);
    }

scopeExpr
    : ',' TOK_SCOPE '(' scopeList ')'
    {
        $$ = $4;
    }

scopeList
    : scope
    {
        $$ = $1;
    }
    | scopeList ',' scope
    {
        $$ |= $3;
    }

scope
    : TOK_CLASS
    {
        $$ = MI_FLAG_CLASS;
    }
    | TOK_ASSOCIATION
    {
        $$ = MI_FLAG_ASSOCIATION;
    }
    | TOK_INDICATION
    {
        $$ = MI_FLAG_INDICATION;
    }
    | TOK_PROPERTY
    {
        $$ = MI_FLAG_PROPERTY;
    }
    | TOK_REFERENCE
    {
        $$ = MI_FLAG_REFERENCE;
    }
    | TOK_METHOD
    {
        $$ = MI_FLAG_METHOD;
    }
    | TOK_PARAMETER
    {
        $$ = MI_FLAG_PARAMETER;
    }
    | TOK_ANY
    {
        $$ = MI_FLAG_ANY;
    }

flavorExpr
    : ',' TOK_FLAVOR '(' flavorList ')'
    {
        /* Reject incompatiable ToSubclass and Restricted flavors */
        if ($4 & MI_FLAG_TOSUBCLASS && $4 & MI_FLAG_RESTRICTED)
        {
            yyerrorf(state->errhandler, ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s", 
                "ToSubclass", "Restricted");
            YYABORT;
        }

        /* Reject incompatiable EnableOverride and DisableOverride flavors */
        if ($4 & MI_FLAG_ENABLEOVERRIDE && $4 & MI_FLAG_DISABLEOVERRIDE)
        {
            yyerrorf(state->errhandler, ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s", 
                "EnableOverride", "DisableOverride");
            YYABORT;
        }

        $$ = $4;
    }

instanceDeclaration
    : TOK_INSTANCE TOK_OF identifier instanceBody
    {
        $$ = CALLOC_T(MI_InstanceDecl, 1);
        $$->flags = 0;
        $$->name = $3;
        $$->properties = $4.propertySet.data;
        $$->numProperties = $4.propertySet.size;
    }
    | qualifierExpr TOK_INDICATION TOK_OF identifier instanceBody
    {
        $$ = CALLOC_T(MI_InstanceDecl, 1);
        $$->flags = 0;
        $$->name = $4;
        $$->properties = $5.propertySet.data;
        $$->numProperties = $5.propertySet.size;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | TOK_INSTANCE TOK_OF identifier alias instanceBody
    {
        $$ = CALLOC_T(MI_InstanceDecl, 1);
        $$->flags = 0;
        $$->name = $3;
        $$->alias = $4;
        $$->properties = $5.propertySet.data;
        $$->numProperties = $5.propertySet.size;
    }
    | qualifierExpr TOK_INDICATION TOK_OF identifier alias instanceBody
    {
        /* [TODO]: handle alias */
        $$ = CALLOC_T(MI_InstanceDecl, 1);
        $$->flags = 0;
        $$->name = $4;
        $$->alias = $5;
        $$->properties = $6.propertySet.data;
        $$->numProperties = $6.propertySet.size;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }

instanceBody
    : '{' valueInitializerList '}' ';'
    {
        $$ = $2;
    }

alias
    : TOK_AS TOK_ALIAS_IDENTIFIER
    {
        $$ = $2;
        if (state->onAliasDeclared)
            (*state->onAliasDeclared)(state);
    }

valueInitializerList
    : valueInitializer
    {
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $1->flags = MI_FLAG_PROPERTY;
        $1->flags |= GetQualFlags(state, $1->qualifiers, $1->numQualifiers);
        if (Codec_PtrArray_Append(state, (Codec_PtrArray*)&$$.propertySet, $1) != 0)
        {
            YYABORT;
        }
    }
    | valueInitializerList valueInitializer
    {
        if (FindProperty(&$1.propertySet, $2->name))
        {
            yyerrorf(state->errhandler, ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "instance property already defined: \"%s\"", $2->name);
            YYABORT;
        }

        $2->flags = MI_FLAG_PROPERTY;
        $2->flags |= GetQualFlags(state, $2->qualifiers, $2->numQualifiers);
        if (Codec_PtrArray_Append(state, (Codec_PtrArray*)&$$.propertySet, $2) != 0)
        {
            YYABORT;
        }
    }

valueInitializer
    : identifier '=' initializer ';'
    {
        void* value;
        MI_Type type = InitializerToType(&$3);

        if (InitializerToValue(state, &$3, type, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->name = $1;
        $$->type = type;
        $$->value = value;
    }
    | qualifierExpr identifier '=' initializer ';'
    {
        void* value;
        MI_Type type = InitializerToType(&$4);

        if (InitializerToValue(state, &$4, type, &value) != 0)
        {
            yyerrorf(state->errhandler, ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->name = $2;
        $$->type = type;
        $$->value = value;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }

identifier
    : TOK_IDENT 
    {
        $$ = $1;
    }
    | TOK_ASSOCIATION
    {
        $$ = Batch_Tcsdup(state->batch, "Association");
    }
    | TOK_INDICATION
    {
        $$ = Batch_Tcsdup(state->batch, "Indication");
    }
    | TOK_REFERENCE
    {
        $$ = Batch_Tcsdup(state->batch, "Reference");
    }
    | TOK_PROPERTY
    {
        $$ = Batch_Tcsdup(state->batch, "Property");
    }
