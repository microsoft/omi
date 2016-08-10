/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _mof_types_h
#define _mof_types_h

#ifndef MI_CHAR_TYPE
# define MI_CHAR_TYPE 1
#endif

#include <MI.h>
#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <pal/file.h>
#include "heap.h"
#include "strids.h"
#include "instancedecl.h"

#define MOF_TRACE printf("MOF_TRACE: %s(%u)\n", __FILE__, __LINE__)

#define MOF_NOT_FOUND ((MI_Uint32)0xFFFFFFFF)

#define MOF_ASSERT(COND) assert(COND)

/* Type-aware forms of memory allocation functions */
#define CALLOC_T(ZT, N) ((ZT*)MOF_Calloc(&state.heap, N, sizeof(ZT)))
#define MALLOC_T(ZT, N) ((ZT*)MOF_Malloc(&state.heap, N * sizeof(ZT)))
#define REALLOC_T(ZT, PTR, N) ((ZT*)MOF_Realloc(&state.heap,PTR,(N)*sizeof(ZT)))

/*
**==============================================================================
**
** error reporting functions.
**
**==============================================================================
*/
extern void yyerror(const char* msg);

PRINTF_FORMAT(2, 3)
extern void yyerrorf(int id, const char *fmt, ...);

PRINTF_FORMAT(2, 3)
extern void yywarnf(int id, const char *fmt, ...);

/*
**==============================================================================
**
** MOF_QualifierList
**
**==============================================================================
*/

typedef struct _MOF_QualifierList
{
    MI_Qualifier** data;
    MI_Uint32 size;
}
MOF_QualifierList;

/*
**==============================================================================
**
** MOF_QualifierDeclList
**
**==============================================================================
*/

typedef struct _MOF_QualifierDeclList
{
    MI_QualifierDecl** data;
    MI_Uint32 size;
}
MOF_QualifierDeclList;

extern MOF_QualifierDeclList g_qualifierDecls;

/*
**==============================================================================
**
** MOF_ClassDeclList
**
**==============================================================================
*/

typedef struct _MOF_ClassDeclList
{
    MI_ClassDecl** data;
    MI_Uint32 size;
}
MOF_ClassDeclList;

/*
**==============================================================================
**
** MOF_InstanceDeclList
**
**==============================================================================
*/

typedef struct _MOF_InstanceDeclList
{
    MI_InstanceDecl** data;
    MI_Uint32 size;
}
MOF_InstanceDeclList;

/*
**==============================================================================
**
** MOF_LineList
**
**     Track the line where EmbeddedInstance qualifiers were encountered for
**     post processing.
**
**==============================================================================
*/

typedef struct _MOF_EmbeddedInstance
{
    /* Pointer to embedded instance qualifier */
    MI_Qualifier* qualifier;

    /* Line where EmbeddedInstance qualifier was encountered */
    unsigned int line;
}
MOF_EmbeddedInstance;

typedef struct _MOF_EmbeddedInstanceList
{
    MOF_EmbeddedInstance** data;
    MI_Uint32 size;
}
MOF_EmbeddedInstanceList;

/*
**==============================================================================
**
** MOF_PropertyList
**
**==============================================================================
*/

typedef struct _MOF_PropertyList
{
    MI_PropertyDecl** data;
    MI_Uint32 size;
}
MOF_PropertyList;

/*
**==============================================================================
**
** MOF_MethodList
**
**==============================================================================
*/

typedef struct _MOF_MethodList
{
    MI_MethodDecl** data;
    MI_Uint32 size;
}
MOF_MethodList;

/*
**==============================================================================
**
** MOF_ParameterList
**
**==============================================================================
*/

typedef struct _MOF_ParameterList
{
    MI_ParameterDecl** data;
    MI_Uint32 size;
}
MOF_ParameterList;

/*
**==============================================================================
**
** MOF_FeatureList
**
**==============================================================================
*/

typedef struct _MOFFeatureList
{
    MOF_PropertyList propertySet;
    MOF_MethodList methodList;
}
MOF_FeatureList;

/*
**==============================================================================
**
** MOF_ConstantValue
**
**     Represents a MOF constant value. The type field must be one of the 
**     following:
**         TOK_INTEGER_VALUE
**         TOK_REAL_VALUE
**         TOK_CHAR_VALUE
**         TOK_STRING_VALUE
**         TOK_NULL 
**
**     The union holds the value (or nothing if it is null).
**
**==============================================================================
*/

typedef struct _MOF_ConstantValue
{
    int type;
    union
    {
        MI_Sint64 integer;
        MI_Real64 real;
        MI_Char16 character;
        MI_Boolean boolean;
        char* string;
    }
    value;
    /* str-to-int conversion flag: boolean flag that indicates value is too big for sint64 */
    MI_Boolean tooBigForSint64;
}
MOF_ConstantValue;

/*
**==============================================================================
**
** MOF_Initializer
**
**     Represents a MOF initializer (both scalar and array). Scalars are
**     represented by a single constant value element with size set to 1. 
**     Arrays are are represented by an array of constant values with size
**     set to the size of the array.
**
**==============================================================================
*/

typedef struct _MOF_Initializer
{
    MOF_ConstantValue* data;
    MI_Uint32 size;
    MI_Boolean isArray;
}
MOF_Initializer;

/*
**==============================================================================
**
** Functions
**
**==============================================================================
*/

/* Convert this initializer to a static value of the given type */
int InitializerToValue(
    MOF_Initializer* self, 
    MI_Uint32 /*MI_Type*/ type,
    void** value);

/* Release all memory held by this initializer */
void ReleaseInitializer(
    MOF_Initializer* self);

void FreeQualifierDeclaration(
    MI_QualifierDecl* self);

int AddQualifierDeclaration(
    MI_QualifierDecl* qd);

const MI_QualifierDecl* FindQualifierDeclaration(
    const char* name);

int AddClassDecl(
    MI_ClassDecl* cd);

const MI_ClassDecl* FindClassDecl(
    const char* name);

void MOF_PrintQualifierDecl(
    const MI_QualifierDecl* self,
    FILE* file);

void PrintValue(
    const void* value, 
    MI_Type type,
    FILE* file);

void PrintQualifier(
    const MI_Qualifier* self, 
    size_t level, 
    FILE* file);

void PrintProperty(
    const MI_PropertyDecl* self, 
    size_t level, 
    FILE* file);

void PrintMethod(
    const MI_MethodDecl* self, 
    size_t level, 
    FILE* file);

MI_PropertyDecl* FindProperty(
    MOF_PropertyList* self,
    const char* name);

MI_ParameterDecl* FindParameter(
    MOF_ParameterList* self,
    const char* name);

MI_MethodDecl* FindMethod(
    MOF_MethodList* self,
    const char* name);

void MOF_PrintClassDecl(
    const MI_ClassDecl* self,
    FILE* file);

void MOF_PrintInstanceDecl(
    const MI_InstanceDecl* self,
    FILE* file);

MI_Uint32 GetQualFlags(
    MI_Qualifier** qualifiers,
    size_t numQualifiers);

void* NewTrueValue();

int FinalizeClass(
    MI_ClassDecl* cd);

int FinalizeInstance(
    MI_InstanceDecl* decl);

/* Propagate flavors from 'from' mask to 'to' mask (return result mask) */
MI_Uint32 PropagateFlavors(MI_Uint32 to, MI_Uint32 from);

/* Find the given qualifier */
MI_Qualifier* FindQualifier(
    MOF_QualifierList* self,
    const char* name);

int CheckScope(MI_Uint32 scope, MOF_QualifierList* qualifiers);

int CheckPropertyValueConstraints(
    const MI_PropertyDecl* pd);

int PerformPostProcessing();

MI_Type InitializerToType(const MOF_Initializer* initializer);

int AddInstanceDecl(
    MI_InstanceDecl* instanceDecl);

#endif /* _mof_types_h */
