/*
 **==============================================================================
 **
 ** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
 ** for license information.
 **
 **==============================================================================
 */

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
extern YYSTYPE yylval;
