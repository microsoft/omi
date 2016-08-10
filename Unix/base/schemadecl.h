/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_schemadecl_h
#define _omi_schemadecl_h

#include "config.h"
#include <common.h>

BEGIN_EXTERNC

MI_ClassDecl* SchemaDecl_FindClassDecl(
    const MI_SchemaDecl* self,
    const ZChar* name);

MI_MethodDecl* SchemaDecl_FindMethodDecl(
    const MI_ClassDecl* cd,
    const ZChar* name);

END_EXTERNC

#endif /* _omi_schemadecl_h */
