/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _mof_instancedecl_h
#define _mof_instancedecl_h

//#ifndef MI_CHAR_TYPE
//# define MI_CHAR_TYPE 1
//#endif

#include <MI.h>

/*
**==============================================================================
**
** struct MI_InstanceDecl
**
**     Represents an instance declaration (as encountered in MOF).
**
**==============================================================================
*/

typedef struct _MI_InstanceDecl MI_InstanceDecl;

struct _MI_InstanceDecl /* extends MI_ObjectDecl */
{
    /* Fields inherited from MI_FeatureDecl */
    MI_Uint32 flags;
    MI_Uint32 code;
    MI_CONST MI_Char* name; /* name of class of which this is an instance */
    struct _MI_Qualifier MI_CONST* MI_CONST* qualifiers; /* unused */
    MI_Uint32 numQualifiers; /* unused */

    /* Fields inherited from MI_ObjectDecl */
    struct _MI_PropertyDecl MI_CONST* MI_CONST* properties;
    MI_Uint32 numProperties;
    MI_Uint32 size;

    /* Extended Fields*/
    MI_Char* alias; /* alias name */
    const MI_ClassDecl * decl; /* corresponding classdecl */
    MI_Uint32 refs; /* referenced times, 0 means no body refer to it */
    MI_Instance *instance; /* finalized instance */
};

#endif /* _mof_instancedecl_h */
