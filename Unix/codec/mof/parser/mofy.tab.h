/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _mofy_tab_h
#define _mofy_tab_h

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
extern YYSTYPE moflval;

#endif /* _mofy_tab_h */
