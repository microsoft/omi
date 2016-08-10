/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_classdecl_h
#define _omi_classdecl_h

#include "config.h"
#include <common.h>

BEGIN_EXTERNC

MI_MethodDecl* ClassDecl_FindMethodDecl(
    const MI_ClassDecl* self,
    const ZChar* name);

MI_PropertyDecl* ClassDecl_FindPropertyDecl(
    const MI_ClassDecl* self,
    const ZChar* name);

END_EXTERNC

#endif /* _omi_classdecl_h */
