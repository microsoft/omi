/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#ifndef _mof_instancedecl_h
#define _mof_instancedecl_h

#ifndef MI_CHAR_TYPE
# define MI_CHAR_TYPE 1
#endif

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
};

#endif /* _mof_instancedecl_h */
