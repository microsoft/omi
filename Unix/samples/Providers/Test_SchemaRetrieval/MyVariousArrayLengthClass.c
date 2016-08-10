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
#include "MyVariousArrayLengthClass.h"

void MI_CALL MyVariousArrayLengthClass_Load(
    MyVariousArrayLengthClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyVariousArrayLengthClass_Unload(
    MyVariousArrayLengthClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyVariousArrayLengthClass_Invoke_MethodWithFixedSizeArrayParam(
    MyVariousArrayLengthClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyVariousArrayLengthClass* instanceName,
    const MyVariousArrayLengthClass_MethodWithFixedSizeArrayParam* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyVariousArrayLengthClass_Invoke_MethodWithArrayParam(
    MyVariousArrayLengthClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyVariousArrayLengthClass* instanceName,
    const MyVariousArrayLengthClass_MethodWithArrayParam* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

