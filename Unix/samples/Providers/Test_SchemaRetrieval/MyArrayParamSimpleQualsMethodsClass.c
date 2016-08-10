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
#include "MyArrayParamSimpleQualsMethodsClass.h"

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Load(
    MyArrayParamSimpleQualsMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Unload(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_BooleanMethod(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_BooleanMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_StringMethod(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_StringMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Char16Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Char16Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Uint8Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Uint8Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Sint8Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Sint8Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Uint16Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Uint16Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Sint16Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Sint16Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Uint32Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Uint32Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Sint32Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Sint32Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Uint64Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Uint64Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Sint64Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Sint64Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Real32Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Real32Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_Real64Method(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_Real64Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyArrayParamSimpleQualsMethodsClass_Invoke_DatetimeMethod(
    MyArrayParamSimpleQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyArrayParamSimpleQualsMethodsClass* instanceName,
    const MyArrayParamSimpleQualsMethodsClass_DatetimeMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

