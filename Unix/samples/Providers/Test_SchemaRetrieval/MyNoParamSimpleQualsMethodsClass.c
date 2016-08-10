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
#include "MyNoParamSimpleQualsMethodsClass.h"

void MI_CALL MyNoParamSimpleQualsMethodsClass_Load(
    MyNoParamSimpleQualsMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Unload(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_BooleanMethod(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_BooleanMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_StringMethod(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_StringMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Char16Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Char16Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Uint8Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Uint8Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Sint8Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Sint8Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Uint16Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Uint16Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Sint16Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Sint16Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Uint32Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Uint32Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Sint32Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Sint32Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Uint64Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Uint64Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Sint64Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Sint64Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Real32Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Real32Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_Real64Method(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_Real64Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamSimpleQualsMethodsClass_Invoke_DatetimeMethod(
    MyNoParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamSimpleQualsMethodsClass* instanceName,
    const MyNoParamSimpleQualsMethodsClass_DatetimeMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

