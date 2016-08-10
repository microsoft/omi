/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include "MyDerivedClassOfRestrictedQualsOnBaseElements.h"

void MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Load(
    MyDerivedClassOfRestrictedQualsOnBaseElements_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Unload(
    MyDerivedClassOfRestrictedQualsOnBaseElements_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyDerivedClassOfRestrictedQualsOnBaseElements_Invoke_myMethod(
    MyDerivedClassOfRestrictedQualsOnBaseElements_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyDerivedClassOfRestrictedQualsOnBaseElements* instanceName,
    const MyDerivedClassOfRestrictedQualsOnBaseElements_myMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

