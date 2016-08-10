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
#include "MyOptionTestClass.h"

void MI_CALL MyOptionTestClass_Load(
    MyOptionTestClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyOptionTestClass_Unload(
    MyOptionTestClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyOptionTestClass_Invoke_Uint32EmptyParamMethod(
    MyOptionTestClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestClass* instanceName,
    const MyOptionTestClass_Uint32EmptyParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyOptionTestClass_Invoke_Sint64SimpleParamsMethod(
    MyOptionTestClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestClass* instanceName,
    const MyOptionTestClass_Sint64SimpleParamsMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyOptionTestClass_Invoke_MultiQualMethod(
    MyOptionTestClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestClass* instanceName,
    const MyOptionTestClass_MultiQualMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

