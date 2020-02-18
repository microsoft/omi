/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "instanceutil.h"
#include "base/instance.h"

_Use_decl_annotations_
MI_Result MI_CALL Mof_Instance_New(
    const MI_ClassDecl* classDecl,
    MI_Instance **instance)
{
    return Instance_New(instance, classDecl, NULL);
}

_Use_decl_annotations_
MI_Result MI_CALL Mof_Instance_InitDynamic(
    const MI_Char* className,
    MI_Uint32 metaType,
    MI_Instance** self)
{
    return Instance_NewDynamic(self, className, metaType, NULL);
}

_Use_decl_annotations_
MI_Result MI_CALL Mof_Instance_Construct(
    const MI_ClassDecl* classDecl,
    MI_Instance* instance)
{
    return Instance_Construct( instance, classDecl, NULL);
}
