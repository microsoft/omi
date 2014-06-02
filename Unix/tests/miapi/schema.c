/* @statikgen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#include <ctype.h>
#include <MI.h>
#include "MyClass.h"

/*
**==============================================================================
**
** Qualifier declarations
**
**==============================================================================
*/

/*
**==============================================================================
**
** MyClass
**
**==============================================================================
*/

/* property MyClass.Property */
static MI_CONST MI_PropertyDecl MyClass_Property_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707908, /* code */
    MI_T("Property"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MyClass, Property), /* offset */
    MI_T("MyClass"), /* origin */
    MI_T("MyClass"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MyClass_props[] =
{
    &MyClass_Property_prop,
};

/* class MyClass */
MI_CONST MI_ClassDecl MyClass_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7307, /* code */
    MI_T("MyClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MyClass_props, /* properties */
    MI_COUNT(MyClass_props), /* numProperties */
    sizeof(MyClass), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    NULL, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** __mi_server
**
**==============================================================================
*/

MI_Server* __mi_server;
/*
**==============================================================================
**
** Schema
**
**==============================================================================
*/

static MI_ClassDecl MI_CONST* MI_CONST classes[] =
{
    &MyClass_rtti,
};

MI_SchemaDecl testClassDecl =
{
    NULL, /* qualifierDecls */
    0, /* numQualifierDecls */
    classes, /* classDecls */
    MI_COUNT(classes), /* classDecls */
};

