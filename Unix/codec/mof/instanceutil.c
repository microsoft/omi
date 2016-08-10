/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "instanceutil.h"
#if defined(_MSC_VER)
#include <common/instance.h>
#else
#include "base/instance.h"
#endif

_Use_decl_annotations_
MI_Result MI_CALL Mof_Instance_New(
    const MI_ClassDecl* classDecl,
    MI_Instance **instance)
{
#if defined(_MSC_VER)
    return Instance_New(classDecl, instance);
#else
    return Instance_New(instance, classDecl, NULL);
#endif
}

_Use_decl_annotations_
MI_Result MI_CALL Mof_Instance_InitDynamic(
    const MI_Char* className,
    MI_Uint32 metaType,
    MI_Instance** self)
{
#if defined(_MSC_VER)
    return Instance_InitDynamic(self, className, metaType);
#else
    return Instance_NewDynamic(self, className, metaType, NULL);
#endif
}

_Use_decl_annotations_
MI_Result MI_CALL Mof_Instance_Construct(
    const MI_ClassDecl* classDecl,
    MI_Instance* instance)
{
#if defined(_MSC_VER)
    return Instance_Construct(classDecl, instance);
#else
    return Instance_Construct( instance, classDecl, NULL);
#endif
}
