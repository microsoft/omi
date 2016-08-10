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
#include "MyOptionTestDerivedClass.h"

void MI_CALL MyOptionTestDerivedClass_Load(
    MyOptionTestDerivedClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyOptionTestDerivedClass_Unload(
    MyOptionTestDerivedClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyOptionTestDerivedClass_Invoke_MyMethod(
    MyOptionTestDerivedClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestDerivedClass* instanceName,
    const MyOptionTestDerivedClass_MyMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyOptionTestDerivedClass_Invoke_Sint64SimpleParamsMethod(
    MyOptionTestDerivedClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestDerivedClass* instanceName,
    const MyOptionTestDerivedClass_Sint64SimpleParamsMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyOptionTestDerivedClass_Invoke_Uint32EmptyParamMethod(
    MyOptionTestDerivedClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestDerivedClass* instanceName,
    const MyOptionTestDerivedClass_Uint32EmptyParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyOptionTestDerivedClass_Invoke_MultiQualMethod(
    MyOptionTestDerivedClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyOptionTestDerivedClass* instanceName,
    const MyOptionTestDerivedClass_MultiQualMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

