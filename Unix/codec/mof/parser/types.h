/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */


#ifndef _mof_types_h
#define _mof_types_h

//#ifndef MI_CHAR_TYPE
//# define MI_CHAR_TYPE 2
//#endif

#include <MI.h>
#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <base/batch.h>
#include <pal/strings.h>
#include <pal/file.h>
#include <pal/dir.h>
#include "stringids.h"
#include "instancedecl.h"

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
}MOF_InstanceDeclList;



/*
**==============================================================================
**
** struct MI_InstanceAliasDecl
**
**     Represents an instance alias declaration (as encountered in MOF).
**
**==============================================================================
*/

typedef struct _MI_InstanceAliasDecl MI_InstanceAliasDecl;

struct _MI_InstanceAliasDecl
{
    MI_Uint32 id;
    MI_Uint32 lineno;
    MI_CONST MI_Char* name; /* name of alias of the instance */
    MI_CONST MI_InstanceDecl * decl; /* the instance decl */
};

typedef struct _MOF_InstanceAliasList
{
    MI_InstanceAliasDecl** data;
    MI_Uint32 size;
}MOF_InstanceAliasList;

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
        MI_Char* string;
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

/* Convert this initializer to a Statik value of the given type */
int InitializerToValue(
    void * mofstate,
    MOF_Initializer* self, 
    MI_Uint32 /*MI_Type*/ type,
    void** value);

/* Release all memory held by this initializer */
void ReleaseInitializer(
    void * mofstate,
    MOF_Initializer* self);

void FreeQualifierDeclaration(
    void * mofstate,
    MI_QualifierDecl* self);

int AddQualifierDeclaration(
    void * mofstate,
    MI_QualifierDecl* qd);

const MI_QualifierDecl* FindQualifierDeclaration(
    _In_ void * mofstate,
    _In_z_ const MI_Char* name);

int AddClassDecl(
    void * mofstate,
    MI_ClassDecl* cd);

const MI_ClassDecl* FindClassDecl(
    void * mofstate,
    const MI_Char* name);

const MI_ClassDecl* FindClassDeclBufferOnly(
    void * mofstate,
    const MI_Char* name);

const MI_InstanceAliasDecl* FindInstanceAliasDecl(
    void * mofstate,
    const MI_Char* name);

MI_Uint32 GetQualFlags(
    void * mofstate,
    MI_Qualifier** qualifiers,
    size_t numQualifiers);

void* NewTrueValue(void * mofstate);

int FinalizeClass(
    void * mofstate,
    MI_ClassDecl* cd);

int FinalizeInstance(
    void * mofstate,
    MI_InstanceDecl* decl);

int CheckScope(
    void * mofstate,
    MI_Uint32 scope,
    MOF_QualifierList* qualifiers);

int CheckPropertyValueConstraints(
    void * mofstate,
    const MI_PropertyDecl* pd);

MI_Type InitializerToType(const MOF_Initializer* initializer);

int AddInstanceDecl(
    void * mofstate,
    MI_InstanceDecl* instanceDecl);

MI_ParameterDecl ** CreateParameterSet(
    _In_ void * mofstate,
    _In_reads_(numOldParameters) MI_ParameterDecl ** oldParameters,
    _In_ MI_Uint32 numOldParameters,
    _In_ MI_Type methodReturnType);

/* Propagate flavors from 'from' mask to 'to' mask (return result mask) */
MI_Uint32 PropagateFlavors(MI_Uint32 to, MI_Uint32 from);

/* Set default flavors */
MI_Uint32 SetDefaultFlavors(MI_Uint32 flavor);

/* Find/Search functions */
MI_PropertyDecl* FindProperty(
    _In_ MOF_PropertyList* self,
    _In_z_ const MI_Char* name);

MI_ParameterDecl* FindParameter(
    _In_ MOF_ParameterList* self,
    _In_z_ const MI_Char* name);

MI_MethodDecl* FindMethod(
    _In_ MOF_MethodList* self,
    _In_z_ const MI_Char* name);

/* Find the given qualifier */
MI_Qualifier* FindQualifier(
    _In_ MOF_QualifierList* self,
    _In_z_ const MI_Char* name);

/* Is the qualifier is EmbeddedInstance or EmbeddedObject */
MI_Boolean IsEmbeddedQualifier(
    _In_z_ const MI_Char* name);

/* Print functions */
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

void MOF_PrintClassDecl(
    const MI_ClassDecl* self,
    FILE* file);

void MOF_PrintInstanceDecl(
    const MI_InstanceDecl* self,
    FILE* file);

/*
**==============================================================================
**
** Utilities of fixup 
**      classdecl size & property decl offset
**      methoddecl size & parameter decl offset
**
**==============================================================================
*/
int _FinalizeClassSize(_Inout_ MI_ClassDecl *decl);
int _FinalizeMethodSize(_Inout_ MI_MethodDecl *decl);


/*
**==============================================================================
**
** Open included file
**
**==============================================================================
*/
extern int openIncludeFile(_In_ void *mofstate, _In_z_ const MI_Char* path);

/*
**==============================================================================
**
** Close included file
**
**==============================================================================
*/
extern int closeIncludeFile(_In_ void *mofstate);


/*=============================================================================
**
** Global data structure & functions
**
=============================================================================*/
typedef struct _MOF_GlobalData
{
    MI_Boolean inited;
    Batch* b;
    MOF_QualifierDeclList qualifierDecls;
}MOF_GlobalData;

/*=============================================================================
**
** Global data contains resource needed by mof parser, including
** (1) Qualifiers Definition --
**        CIM Stanard Qualifiers
**        Optional qualifiers
**        MSFT qualifiers
**
=============================================================================*/
extern MOF_GlobalData g_d;

#endif /* _mof_types_h */
