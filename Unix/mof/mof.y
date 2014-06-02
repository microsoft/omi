%{

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

%}

%union
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
%token TOK_OBJECT
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
%token TOK_TOINSTANCE
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

%type <string> stringValue
%type <string> TOK_STRING_VALUE
%type <string> classNameIdentifier
%type <string> identifier
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
%type <property> dynamicReferenceDeclaration
%type <property> staticEmbeddedInstanceDeclaration
%type <property> dynamicEmbeddedInstanceDeclaration
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
%type <initializer> scalarInitializer
%type <initializer> nonAggregateInitializer
%type <initializer> nonAggregateArrayInitializer
%type <initializer> nonAggregateArrayInitializerList
%type <flags> scope
%type <flags> scopeList
%type <flags> scopeExpr
%type <flags> flavor
%type <flags> flavorList
%type <flags> qualifierFlavorList
%type <flags> flavorExpr
%type <qualifier> qualifier
%type <qualifierList> qualifierList
%type <qualifierList> qualifierExpr
%type <initializer> qualifierParameter
%type <classDeclaration> classDeclaration
%type <instanceDeclaration> instanceDeclaration
%type <property> valueInitializer
%type <featureList> valueInitializerList 
%type <string> TOK_CLASS
%type <string> TOK_INSTANCE
%type <string> TOK_OF
%type <string> TOK_ANY
%type <string> TOK_ASSOCIATION
%type <string> TOK_INDICATION
%type <string> TOK_REFERENCE
%type <string> TOK_PROPERTY
%type <string> TOK_QUALIFIER
%type <string> TOK_TOSUBCLASS
%type <string> TOK_TOINSTANCE
%type <string> TOK_TRANSLATABLE
%type <string> TOK_FLAVOR
%type <string> TOK_BOOLEAN
%type <string> TOK_DATETIME
%type <string> TOK_STRING
%type <string> TOK_OBJECT
%type <string> TOK_PRAGMA

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
        $1->flags |= GetQualFlags($1->qualifiers, $1->numQualifiers);
        if (FinalizeClass($1) != 0)
            YYABORT;
            
        AddClassDecl($1);

        if (state.classDeclCallback)
            (*state.classDeclCallback)($1, state.classDeclCallbackData);
    }
    | qualifierDeclaration
    {
        AddQualifierDeclaration($1);

        if (state.qualifierDeclCallback)
            (*state.qualifierDeclCallback)($1, state.qualifierDeclCallbackData);
    }
    | instanceDeclaration
    {
        if (FinalizeInstance($1) != 0)
            YYABORT;

        AddInstanceDecl($1);

        if (state.instanceDeclCallback)
            (*state.instanceDeclCallback)($1, state.instanceDeclCallbackData);
    }

compilerDirective
    : TOK_PRAGMA TOK_IDENT '(' stringValue ')'
    {
        if (strcmp($2, "include") == 0)
        {
            if (openIncludeFile($4) != 0)
                YYABORT;
        }
        else if (strcmp($2, "instancelocale") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)($2, $4, state.pragmaCallbackData);
        }
        else if (strcmp($2, "locale") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)($2, $4, state.pragmaCallbackData);
        }
        else if (strcmp($2, "namespace") == 0)
        {
            if (state.pragmaCallback)
                (*state.pragmaCallback)($2, $4, state.pragmaCallbackData);
        }
        else if (state.extensionsEnabled == MI_TRUE && strcmp($2, "deleteclass") == 0)
        {
            yywarnf(ID_UNKNOWN_PRAGMA, 
                "warning: nonstandard pragma: %s(%s)", $2, $4);

            if (state.pragmaCallback)
                (*state.pragmaCallback)($2, $4, state.pragmaCallbackData);
        }
        else
        {
            yywarnf(ID_UNKNOWN_PRAGMA, 
                "warning: unknown pragma: %s(%s)", $2, $4);

            if (state.pragmaCallback)
                (*state.pragmaCallback)($2, $4, state.pragmaCallbackData);
        }
    }
    | TOK_PRAGMA TOK_IDENT '(' stringValue ',' identifier ')'
    {
        if (state.extensionsEnabled == MI_TRUE && strcmp($2, "deleteclass") == 0)
        {
            yywarnf(ID_UNKNOWN_PRAGMA, 
                "warning: nonstandard pragma: %s(%s)", $2, $4);

            if (state.pragmaCallback)
                (*state.pragmaCallback)($2, $4, state.pragmaCallbackData);
        }
        else
        {
            yywarnf(ID_UNKNOWN_PRAGMA, 
                "warning: unknown pragma: %s(%s)", $2, $4);

            if (state.pragmaCallback)
                (*state.pragmaCallback)($2, $4, state.pragmaCallbackData);
        }
    }

classDeclaration
    : TOK_CLASS classNameIdentifier classBody
    {
        /* Check whether class already exists */
        if (FindClassDecl($2))
        {
            if (state.extensionsEnabled == MI_FALSE)
            {
                yyerrorf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", $2);
                YYABORT;
            }
            else
                yywarnf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", $2);
        }

        $$ = CALLOC_T(MI_ClassDecl, 1);
        $$->flags = MI_FLAG_CLASS;
        $$->name = $2;
        $$->properties = $3.propertySet.data;
        $$->numProperties = $3.propertySet.size;
        $$->methods = $3.methodList.data;
        $$->numMethods = $3.methodList.size;
    }
    | TOK_CLASS classNameIdentifier ':' classNameIdentifier classBody
    {
        const MI_ClassDecl* scd;

        /* Check whether class already exists */
        if (FindClassDecl($2))
        {
            if (state.extensionsEnabled == MI_FALSE)
            {
                yyerrorf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", $2);
                YYABORT;
            }
            else
                yywarnf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", $2);
        }
 
        /* Check whether superclass exists */
        scd = FindClassDecl($4);

        if (!scd)
        {
            yyerrorf(ID_UNDEFINED_SUPERCLASS, 
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
    | qualifierExpr TOK_CLASS classNameIdentifier classBody
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_CLASS, &$1) != 0)
            YYABORT;

        /* Check whether class already exists */
        if (FindClassDecl($3))
        {
            if (state.extensionsEnabled == MI_FALSE)
            {
                yyerrorf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", $3);
                YYABORT;
            }
            else
                yywarnf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", $3);
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
    | qualifierExpr TOK_CLASS classNameIdentifier ':' classNameIdentifier classBody
    {
        const MI_ClassDecl* scd;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_CLASS, &$1) != 0)
            YYABORT;

        /* Check whether class already exists */
        if (FindClassDecl($3))
        {
            if (state.extensionsEnabled == MI_FALSE)
            {
                yyerrorf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", $3);
                YYABORT;
            }
            else
                yywarnf(ID_CLASS_ALREADY_DEFINED, 
                    "class already defined: \"%s\"", $3);
        }

        /* Check whether superclass exists */
        scd = FindClassDecl($5);

        if (!scd)
        {
            yyerrorf(ID_UNDEFINED_SUPERCLASS, 
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
        if (CheckPropertyValueConstraints($1) != 0)
        {
            YYABORT;
        }
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $$.methodList.data = NULL;
        $$.methodList.size = 0;
        $1->flags = MI_FLAG_PROPERTY;
        $1->flags |= GetQualFlags($1->qualifiers, $1->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.propertySet, $1);
    }
    | methodDeclaration
    {
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $$.methodList.data = NULL;
        $$.methodList.size = 0;
        $1->flags = MI_FLAG_METHOD;
        $1->flags |= GetQualFlags($1->qualifiers, $1->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.methodList, $1);
    }
    | referenceDeclaration
    {
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $$.methodList.data = NULL;
        $$.methodList.size = 0;
        $1->flags = MI_FLAG_PROPERTY;
        $1->flags |= GetQualFlags($1->qualifiers, $1->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.propertySet, $1);
    }
    | dynamicReferenceDeclaration
    {
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $$.methodList.data = NULL;
        $$.methodList.size = 0;
        $1->flags = MI_FLAG_PROPERTY;
        $1->flags |= GetQualFlags($1->qualifiers, $1->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.propertySet, $1);
    }
    | staticEmbeddedInstanceDeclaration
    {
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $$.methodList.data = NULL;
        $$.methodList.size = 0;
        $1->flags = MI_FLAG_PROPERTY;
        $1->flags |= GetQualFlags($1->qualifiers, $1->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.propertySet, $1);
    }
    | dynamicEmbeddedInstanceDeclaration
    {
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $$.methodList.data = NULL;
        $$.methodList.size = 0;
        $1->flags = MI_FLAG_PROPERTY;
        $1->flags |= GetQualFlags($1->qualifiers, $1->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.propertySet, $1);
    }
    | classFeatureList propertyDeclaration
    {
        if (CheckPropertyValueConstraints($2) != 0)
        {
            YYABORT;
        }

        if (FindProperty(&$1.propertySet, $2->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", $2->name);
            YYABORT;
        }

        $2->flags = MI_FLAG_PROPERTY;
        $2->flags |= GetQualFlags($2->qualifiers, $2->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.propertySet, $2);
    }
    | classFeatureList methodDeclaration
    {
        if (FindMethod(&$1.methodList, $2->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", $2->name);
            YYABORT;
        }

        $2->flags = MI_FLAG_METHOD;
        $2->flags |= GetQualFlags($2->qualifiers, $2->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.methodList, $2);
    }
    | classFeatureList referenceDeclaration
    {
        if (FindProperty(&$1.propertySet, $2->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "class feature already defined: \"%s\"", $2->name);
            YYABORT;
        }

        $2->flags = MI_FLAG_PROPERTY;
        $2->flags |= GetQualFlags($2->qualifiers, $2->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.propertySet, $2);
    }
    | classFeatureList dynamicReferenceDeclaration
    {
        if (FindProperty(&$1.propertySet, $2->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", $2->name);
            YYABORT;
        }
        $2->flags = MI_FLAG_PROPERTY;
        $2->flags |= GetQualFlags($2->qualifiers, $2->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.propertySet, $2);
    }
    | classFeatureList staticEmbeddedInstanceDeclaration
    {
        if (FindProperty(&$1.propertySet, $2->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", $2->name);
            YYABORT;
        }

        $2->flags = MI_FLAG_PROPERTY;
        $2->flags |= GetQualFlags($2->qualifiers, $2->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.propertySet, $2);
    }
    | classFeatureList dynamicEmbeddedInstanceDeclaration
    {
        if (FindProperty(&$1.propertySet, $2->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED,
                "class feature already defined: \"%s\"", $2->name);
            YYABORT;
        }

        $2->flags = MI_FLAG_PROPERTY;
        $2->flags |= GetQualFlags($2->qualifiers, $2->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.propertySet, $2);
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
        PtrArray_Append((PtrArray*)&$$, $1);
    }
    | qualifierList ',' qualifier
    {
        if (FindQualifier(&$1, $3->name))
        {
            yyerrorf(ID_DUPLICATE_QUALIFIER, 
                "duplicate qualifier: \"%s\"", $3->name);
            YYABORT;
        }

        PtrArray_Append((PtrArray*)&$$, $3);
    }

qualifier
    : identifier
    {
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;

        qd = FindQualifierDeclaration($1);

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", $1);
            YYABORT;
        }

        if (qd->type != MI_BOOLEAN)
        {
            yyerrorf(ID_MISSING_QUALIFIER_INITIALIZER, 
                "qualifier is missing initializer: \"%s\"", $1);
            YYABORT;
        }
        
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = qd->flavor;
        q->value = NewTrueValue();
        $$ = q;
    }
    | identifier qualifierParameter
    {
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;
        void* value;

        qd = FindQualifierDeclaration($1);

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", $1);
            YYABORT;
        }

        if (InitializerToValue(&$2, qd->type, &value) != 0)
        {
            yyerrorf(ID_INVALID_QUALIFIER_INITIALIZER, 
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
    | identifier ':' qualifierFlavorList
    {
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;

        qd = FindQualifierDeclaration($1);

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", $1);
            YYABORT;
        }

        if (qd->type != MI_BOOLEAN)
        {
            yyerrorf(ID_MISSING_QUALIFIER_INITIALIZER, 
                "qualifier is missing initializer: \"%s\"", $1);
            YYABORT;
        }
        
        q = CALLOC_T(MI_Qualifier, 1);
        q->name = qd->name; /* use casing of qualifier declaration name */
        q->type = qd->type;
        q->flavor = PropagateFlavors($3, qd->flavor);
        q->value = NewTrueValue();
        $$ = q;
    }
    | identifier qualifierParameter ':' qualifierFlavorList
    {
        MI_Qualifier* q;
        const MI_QualifierDecl* qd;
        void* value;

        qd = FindQualifierDeclaration($1);

        if (!qd)
        {
            yyerrorf(ID_UNDEFINED_QUALIFIER, "undefined qualifier: \"%s\"", $1);
            YYABORT;
        }

        if (InitializerToValue(&$2, qd->type, &value) != 0)
        {
            yyerrorf(ID_INVALID_QUALIFIER_INITIALIZER, 
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
    | nonAggregateArrayInitializer
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

qualifierFlavorList
    : flavor
    {
        $$ = $1;
    }
    | qualifierFlavorList flavor
    {
        $$ |= $2;
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
    | TOK_TOINSTANCE
    {
        $$ = MI_FLAG_TOINSTANCE;
        if (state.extensionsEnabled == MI_FALSE)
        {
            yyerrorf(ID_UNSUPPORTED, "Unsupported flavor: ToInstance");
            YYABORT;
        }
    }
    | TOK_TRANSLATABLE
    {
        $$ = MI_FLAG_TRANSLATABLE;
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
        if (CheckScope(MI_FLAG_PROPERTY, &$1) != 0)
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
        if (CheckScope(MI_FLAG_PROPERTY, &$1) != 0)
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

        if (InitializerToValue(&$4, $1, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
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
        if (CheckScope(MI_FLAG_PROPERTY, &$1) != 0)
            YYABORT;

        if (InitializerToValue(&$5, $2, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
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

        if (InitializerToValue(&$5, ARRAYOF($1), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
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
        if (CheckScope(MI_FLAG_PROPERTY, &$1) != 0)
            YYABORT;

        if (InitializerToValue(&$6, ARRAYOF($2), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
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

staticEmbeddedInstanceDeclaration
    : classNameIdentifier identifier ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($1);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $1);
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCE;
        $$->name = $2;
        $$->className = cd->name;
    }
    | qualifierExpr classNameIdentifier identifier ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($2);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $2);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCE;
        $$->name = $3;
        $$->className = cd->name;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | classNameIdentifier identifier subscript ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($1);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $1);
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCEA;
        $$->name = $2;
        $$->className = cd->name;
        $$->subscript = (MI_Uint32)$3;
    }
    | qualifierExpr classNameIdentifier identifier subscript ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($2);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $2);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCEA;
        $$->name = $3;
        $$->className = cd->name;
        $$->subscript = (MI_Uint32)$4;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | classNameIdentifier identifier '=' initializer ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($1);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $1);
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCE;
        $$->name = $2;
        $$->className = cd->name;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
    | qualifierExpr classNameIdentifier identifier '=' initializer ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($2);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $2);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCE;
        $$->name = $3;
        $$->className = cd->name;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
    | classNameIdentifier identifier subscript '=' initializer ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($1);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $1);
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCEA;
        $$->name = $2;
        $$->className = cd->name;
        $$->subscript = (MI_Uint32)$3;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
    | qualifierExpr classNameIdentifier identifier subscript '=' initializer ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($2);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $2);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCEA;
        $$->name = $3;
        $$->className = cd->name;
        $$->subscript = (MI_Uint32)$4;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }

dynamicEmbeddedInstanceDeclaration
    : TOK_OBJECT identifier ';'
    {
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCE;
        $$->name = $2;
        $$->className = "?";
    }
    | qualifierExpr TOK_OBJECT identifier ';'
    {
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCE;
        $$->name = $3;
        $$->className = "?";
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | TOK_OBJECT identifier subscript ';'
    {
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCEA;
        $$->name = $2;
        $$->className = "?";
        $$->subscript = 0;
    }
    | qualifierExpr TOK_OBJECT identifier subscript ';'
    {
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCEA;
        $$->name = $3;
        $$->className = "?";
        $$->subscript = 0;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | TOK_OBJECT identifier '=' initializer ';'
    {
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCE;
        $$->name = $2;
        $$->className = "?";
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
    | qualifierExpr TOK_OBJECT identifier '=' initializer ';'
    {
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCE;
        $$->name = $3;
        $$->className = "?";
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
    | TOK_OBJECT identifier subscript '=' initializer ';'
    {
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCEA;
        $$->name = $2;
        $$->className = "?";
        $$->subscript = (MI_Uint32)$3;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
    | qualifierExpr TOK_OBJECT identifier subscript '=' initializer ';'
    {
        if (state.extensionsEnabled == MI_FALSE)
            yywarnf(ID_UNSUPPORTED, "warning: OBJECT keyword is not supported");
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_INSTANCEA;
        $$->name = $3;
        $$->className = "?";
        $$->subscript = (MI_Uint32)$4;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }

referenceDeclaration
    : classNameIdentifier TOK_REF identifier ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($1);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $1);
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCE;
        $$->name = $3;
        $$->className = cd->name;
    }
    | qualifierExpr classNameIdentifier TOK_REF identifier ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($2);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $2);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCE;
        $$->name = $4;
        $$->className = cd->name;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | classNameIdentifier TOK_REF identifier '=' initializer ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($1);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $1);
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCE;
        $$->name = $3;
        $$->className = cd->name;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* [TODO: use initializer */
    }
    | qualifierExpr classNameIdentifier TOK_REF identifier '=' initializer ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($2);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $2);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCE;
        $$->name = $4;
        $$->className = cd->name;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* [TODO: use initializer */
    }
    | classNameIdentifier TOK_REF identifier subscript ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($1);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $1);
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCEA;
        $$->name = $3;
        $$->className = cd->name;
        $$->subscript = (MI_Uint32)$4;
    }
    | qualifierExpr classNameIdentifier TOK_REF identifier subscript ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($2);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $2);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCEA;
        $$->name = $4;
        $$->className = cd->name;
        $$->subscript = (MI_Uint32)$5;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | classNameIdentifier TOK_REF identifier subscript '=' initializer ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($1);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $1);
            YYABORT;
        }

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCEA;
        $$->name = $3;
        $$->className = cd->name;
        $$->subscript = (MI_Uint32)$4;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
    | qualifierExpr classNameIdentifier TOK_REF identifier subscript '=' initializer ';'
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($2);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $2);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCEA;
        $$->name = $4;
        $$->className = cd->name;
        $$->subscript = (MI_Uint32)$5;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }

dynamicReferenceDeclaration
    : TOK_OBJECT TOK_REF identifier ';'
    {
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCE;
        $$->name = $3;
        $$->className = "?";
    }
    | qualifierExpr TOK_OBJECT TOK_REF identifier ';'
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCE;
        $$->name = $4;
        $$->className = "?";
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | TOK_OBJECT TOK_REF identifier subscript ';'
    {
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCEA;
        $$->name = $3;
        $$->className = "?";
        $$->subscript = (MI_Uint32)$4;
    }
    | qualifierExpr TOK_OBJECT TOK_REF identifier subscript ';'
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCEA;
        $$->name = $4;
        $$->className = "?";
        $$->subscript = (MI_Uint32)$5;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | TOK_OBJECT TOK_REF identifier '=' initializer ';'
    {
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCE;
        $$->name = $3;
        $$->className = "?";
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
    | TOK_OBJECT TOK_REF identifier subscript '=' initializer ';'
    {
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCEA;
        $$->name = $3;
        $$->className = "?";
        $$->subscript = (MI_Uint32)$4;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
    }
    | qualifierExpr TOK_OBJECT TOK_REF identifier '=' initializer ';'
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCE;
        $$->name = $4;
        $$->className = "?";
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
	}
    | qualifierExpr TOK_OBJECT TOK_REF identifier subscript '=' initializer ';'
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_REFERENCE, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->type = MI_REFERENCEA;
        $$->name = $4;
        $$->className = "?";
        $$->subscript = (MI_Uint32)$5;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        yywarnf(ID_IGNORED_INITIALIZER, "warning: ignored initializer");
        /* TODO: use initializer */
	}

methodDeclaration
    : dataType identifier '(' parameterList ')' ';'
    {
        $$ = CALLOC_T(MI_MethodDecl, 1);
        $$->name = $2;
        $$->parameters = $4.data;
        $$->numParameters = $4.size;
        $$->returnType = $1;
    }
    | qualifierExpr dataType identifier '(' parameterList ')' ';'
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_METHOD, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_MethodDecl, 1);
        $$->name = $3;
        $$->parameters = $5.data;
        $$->numParameters = $5.size;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        $$->returnType = $2;
    }
    | dataType identifier '(' ')' ';'
    {
        MOF_ParameterList parameterList = PTRARRAY_INITIALIZER;

        $$ = CALLOC_T(MI_MethodDecl, 1);
        $$->name = $2;
        $$->parameters = parameterList.data;
        $$->numParameters = parameterList.size;
        $$->returnType = $1;
    }
    | qualifierExpr dataType identifier '(' ')' ';'
    {
        MOF_ParameterList parameterList = PTRARRAY_INITIALIZER;

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_METHOD, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_MethodDecl, 1);
        $$->name = $3;
        $$->parameters = parameterList.data;
        $$->numParameters = parameterList.size;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
        $$->returnType = $2;
    }

parameterList
    : parameter
    {
        $1->flags = MI_FLAG_PARAMETER;
        $1->flags |= GetQualFlags($1->qualifiers, $1->numQualifiers);
        $$.data = NULL;
        $$.size = 0;
        PtrArray_Append((PtrArray*)&$$, $1);
    }
    | parameterList ',' parameter
    {
        if (FindParameter(&$1, $3->name))
        {
            yyerrorf(ID_PARAMETER_ALREADY_DEFINED, 
                "parameter already defined: \"%s\"", $3->name);
            YYABORT;
        }

        $3->flags = MI_FLAG_PARAMETER;
        $3->flags |= GetQualFlags($3->qualifiers, $3->numQualifiers);
        PtrArray_Append((PtrArray*)&$$, $3);
    }

parameter
    : dataType identifier
    {
        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $2;
        $$->type = $1;
    }
    | classNameIdentifier TOK_REF identifier
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($1);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $1);
            YYABORT;
        }

        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $3;
        $$->type = MI_REFERENCE;
        $$->className = cd->name;
    }
    | qualifierExpr dataType identifier
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $3;
        $$->type = $2;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | qualifierExpr classNameIdentifier TOK_REF identifier
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($2);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $2);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $4;
        $$->type = MI_REFERENCE;
        $$->className = cd->name;
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
    | classNameIdentifier TOK_REF identifier subscript
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($1);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $1);
            YYABORT;
        }

        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $3;
        $$->type = ARRAYOF(MI_REFERENCE);
        $$->className = cd->name;
        $$->subscript = (MI_Uint32)$4;
    }
    | qualifierExpr dataType identifier subscript
    {
        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $3;
        $$->type = ARRAYOF($2);
        $$->subscript = (MI_Uint32)$4;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | qualifierExpr classNameIdentifier TOK_REF identifier subscript
    {
        const MI_ClassDecl* cd;

        /* Verify that class exists */
        cd = FindClassDecl($2);
        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", $2);
            YYABORT;
        }

        /* Check qualifier scope */
        if (CheckScope(MI_FLAG_PARAMETER, &$1) != 0)
            YYABORT;

        $$ = CALLOC_T(MI_ParameterDecl, 1);
        $$->name = $4;
        $$->type = ARRAYOF(MI_REFERENCE);
        $$->className = cd->name;
        $$->subscript = (MI_Uint32)$5;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }

subscript
    : '[' TOK_INTEGER_VALUE ']'
    {
        if ($2 <= 0)
        {
            yyerrorf(ID_ILLEGAL_ARRAY_SUBSCRIPT, 
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
    : scalarInitializer
    {
        $$ = $1;
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
    : scalarInitializer
    {
        memset(&$$, 0, sizeof($$));
        $$.data = CALLOC_T(MOF_ConstantValue, 1);
        $$.data[0] = $1.data[0];
        $$.size = 1;
        $$.isArray = 1;
    }
    | arrayInitializerList ',' scalarInitializer
    {
        $1.data = REALLOC_T(MOF_ConstantValue, $1.data, $1.size + 1);
        $1.data[$1.size] = $3.data[0];
        $1.size++;
        $$ = $1;
    }

scalarInitializer
    : constantValue
    {
        memset(&$$, 0, sizeof($$));
        $$.data = CALLOC_T(MOF_ConstantValue, 1);
        $$.data[0] = $1;
        $$.size = 1;
    }
    | TOK_ALIAS_IDENTIFIER
    {
        memset(&$$, 0, sizeof($$));
        $$.data = CALLOC_T(MOF_ConstantValue, 1);
        $$.data[0].type = TOK_STRING_VALUE;
        $$.data[0].value.string = $1;
        $$.size = 1;
        /* TODO: look up alias, get and store instance decl. for alias */
    }
    | TOK_INSTANCE TOK_OF classNameIdentifier '{' valueInitializerList '}'
    {
        memset(&$$, 0, sizeof($$));
        $$.data = CALLOC_T(MOF_ConstantValue, 1);
        $$.data[0].type = TOK_STRING_VALUE;
        $$.data[0].value.string = $3;
        $$.size = 1;
        /* TODO: look up class $3, validate property names/types, store dynamic instance properties in this instance */
    }

nonAggregateInitializer
    : constantValue
    {
        memset(&$$, 0, sizeof($$));
        $$.data = CALLOC_T(MOF_ConstantValue, 1);
        $$.data[0] = $1;
        $$.size = 1;
    }
    | nonAggregateArrayInitializer
    {
        $$ = $1;
    }

nonAggregateArrayInitializer
    : '{' nonAggregateArrayInitializerList '}'
    {
        $$ = $2;
    }
    | '{' '}'
    {
        $$.data = NULL;
        $$.size = 0;
        $$.isArray = MI_TRUE;
    }

nonAggregateArrayInitializerList
    : constantValue
    {
        memset(&$$, 0, sizeof($$));
        $$.data = CALLOC_T(MOF_ConstantValue, 1);
        $$.data[0] = $1;
        $$.size = 1;
        $$.isArray = MI_TRUE;
    }
    | nonAggregateArrayInitializerList ',' constantValue
    {
        $1.data = REALLOC_T(MOF_ConstantValue, $1.data, $1.size + 1);
        $1.data[$1.size] = $3;
        $1.size++;
        $1.isArray = MI_TRUE;
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

stringValue
    : TOK_STRING_VALUE
    {
	$$ = $1;
    }
    | stringValue TOK_STRING_VALUE
    {
        size_t size = strlen($1) + strlen($2) + 1;
        $$ = (char*)MOF_Realloc(&state.heap, $1, size);
        Strcat($$, size, $2);
        MOF_Free(&state.heap, $2);
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
    | ':' dataType '=' nonAggregateInitializer
    {
        void* value;

        if (InitializerToValue(&$4, $2, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        $$ = CALLOC_T(MI_QualifierDecl, 1);
        $$->type = $2;
        $$->value = value;
        ReleaseInitializer(&$4);
    }
    | ':' dataType subscript
    {
        $$ = CALLOC_T(MI_QualifierDecl, 1);
        $$->type = ARRAYOF($2);
        $$->subscript = (MI_Uint32)$3;
    }
    | ':' dataType subscript '=' nonAggregateInitializer
    {
        void* value = NULL;

        if (InitializerToValue(&$5, ARRAYOF($2), &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
            YYABORT;
        }

        $$ = CALLOC_T(MI_QualifierDecl, 1);
        $$->type = ARRAYOF($2);
        $$->subscript = (MI_Uint32)$3;
        $$->value = value;
        ReleaseInitializer(&$5);
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
            yyerrorf(ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s", 
                "ToSubclass", "Restricted");
            YYABORT;
        }

        /* Reject incompatiable EnableOverride and DisableOverride flavors */
        if ($4 & MI_FLAG_ENABLEOVERRIDE && $4 & MI_FLAG_DISABLEOVERRIDE)
        {
            yyerrorf(ID_INCOMPATIBLE_FLAVORS, "incompatible flavors: %s/%s", 
                "EnableOverride", "DisableOverride");
            YYABORT;
        }

        $$ = $4;
    }

instanceDeclaration
    : TOK_INSTANCE TOK_OF classNameIdentifier instanceBody
    {
        $$ = CALLOC_T(MI_InstanceDecl, 1);
        $$->flags = 0;
        $$->name = $3;
        $$->properties = $4.propertySet.data;
        $$->numProperties = $4.propertySet.size;
    }
    | qualifierExpr TOK_INSTANCE TOK_OF classNameIdentifier instanceBody
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
        /* [TODO]: handle alias */
        $$ = CALLOC_T(MI_InstanceDecl, 1);
        $$->flags = 0;
        $$->name = $3;
        $$->properties = $5.propertySet.data;
        $$->numProperties = $5.propertySet.size;
    }
    | qualifierExpr TOK_INSTANCE TOK_OF classNameIdentifier alias instanceBody
    {
        /* [TODO]: handle alias */
        $$ = CALLOC_T(MI_InstanceDecl, 1);
        $$->flags = 0;
        $$->name = $4;
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
    | '{' '}' ';'
    {
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $$.methodList.data = NULL;
        $$.methodList.size = 0;
    }

alias
    : TOK_AS TOK_ALIAS_IDENTIFIER
    {
        $$ = $2;
    }

valueInitializerList
    : valueInitializer
    {
        $$.propertySet.data = NULL;
        $$.propertySet.size = 0;
        $1->flags = MI_FLAG_PROPERTY;
        $1->flags |= GetQualFlags($1->qualifiers, $1->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.propertySet, $1);
    }
    | valueInitializerList valueInitializer
    {
        if (FindProperty(&$1.propertySet, $2->name))
        {
            yyerrorf(ID_CLASS_FEATURE_ALREADY_DEFINED, 
                "instance property already defined: \"%s\"", $2->name);
            YYABORT;
        }

        $2->flags = MI_FLAG_PROPERTY;
        $2->flags |= GetQualFlags($2->qualifiers, $2->numQualifiers);
        PtrArray_Append((PtrArray*)&$$.propertySet, $2);
    }

valueInitializer
    : identifier ';'
    {
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->name = $1;
        $$->type = TOK_NULL;
    }
    | qualifierExpr identifier ';'
    {
        $$ = CALLOC_T(MI_PropertyDecl, 1);
        $$->name = $2;
        $$->type = TOK_NULL;
        $$->qualifiers = $1.data;
        $$->numQualifiers = $1.size;
    }
    | identifier '=' initializer ';'
    {
        void* value;
        MI_Type type = InitializerToType(&$3);
        if (InitializerToValue(&$3, type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
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

        if (InitializerToValue(&$4, type, &value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer");
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
    : classNameIdentifier
    {
        $$ = $1;
    }
    | TOK_OBJECT
    {
        $$ = "Object";
    }
    | TOK_BOOLEAN
    {
        $$ = "Boolean";
    }
    | TOK_DATETIME
    {
        $$ = "Datetime";
    }
    | TOK_STRING
    {
        $$ = "String";
    }
    /* {S,U}INT{8,16,32,64} can also be added here */

/* Class names can appear at the beginning of property declarations (for embedded class
   types or before REF), so class names cannot collide with built-in type names, so
   they are more limited than identifer, above. */
classNameIdentifier
    : TOK_IDENT
    {
        $$ = $1;
    }
    | TOK_PRAGMA
    {
        $$ = $1;
    }
    | TOK_CLASS
    {
        $$ = $1;
    }
    | TOK_OF
    {
        $$ = $1;
    }
    | TOK_ANY
    {
        $$ = $1;
    }
    | TOK_ASSOCIATION
    {
        $$ = $1;
    }
    | TOK_INDICATION
    {
        $$ = $1;
    }
    | TOK_REFERENCE
    {
        $$ = $1;
    }
    | TOK_PROPERTY
    {
        $$ = $1;
    }
    | TOK_QUALIFIER
    {
        $$ = $1;
    }
    | TOK_TOSUBCLASS
    {
        $$ = $1;
    }
    | TOK_TOINSTANCE
    {
        $$ = $1;
    }
    | TOK_TRANSLATABLE
    {
        $$ = $1;
    }
    | TOK_FLAVOR
    {
        $$ = $1;
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
