
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_ERROR = 258,
     TOK_BOOLEAN = 259,
     TOK_SINT8 = 260,
     TOK_UINT8 = 261,
     TOK_SINT16 = 262,
     TOK_UINT16 = 263,
     TOK_SINT32 = 264,
     TOK_UINT32 = 265,
     TOK_SINT64 = 266,
     TOK_UINT64 = 267,
     TOK_REAL32 = 268,
     TOK_REAL64 = 269,
     TOK_DATETIME = 270,
     TOK_CHAR16 = 271,
     TOK_STRING = 272,
     TOK_BOOLEAN_VALUE = 273,
     TOK_REF = 274,
     TOK_SCOPE = 275,
     TOK_CLASS = 276,
     TOK_QUALIFIER = 277,
     TOK_OBJECT = 278,
     TOK_FLAVOR = 279,
     TOK_INSTANCE = 280,
     TOK_OF = 281,
     TOK_AS = 282,
     TOK_PRAGMA = 283,
     TOK_INTEGER_VALUE = 284,
     TOK_REAL_VALUE = 285,
     TOK_STRING_VALUE = 286,
     TOK_CHAR_VALUE = 287,
     TOK_IDENT = 288,
     TOK_ALIAS_IDENTIFIER = 289,
     TOK_NULL = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 21 "mof.y"

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



/* Line 1676 of yacc.c  */
#line 113 "mof.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


