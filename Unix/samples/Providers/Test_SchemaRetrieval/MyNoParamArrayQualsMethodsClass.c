/* @migen@ */
#include <MI.h>
#include "MyNoParamArrayQualsMethodsClass.h"

void MI_CALL MyNoParamArrayQualsMethodsClass_Load(
    MyNoParamArrayQualsMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Unload(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_BooleanMethod(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_BooleanMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_StringMethod(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_StringMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Char16Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Char16Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Uint8Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Uint8Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Sint8Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Sint8Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Uint16Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Uint16Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Sint16Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Sint16Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Uint32Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Uint32Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Sint32Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Sint32Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Uint64Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Uint64Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Sint64Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Sint64Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Real32Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Real32Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_Real64Method(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_Real64Method* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MyNoParamArrayQualsMethodsClass_Invoke_DatetimeMethod(
    MyNoParamArrayQualsMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyNoParamArrayQualsMethodsClass* instanceName,
    const MyNoParamArrayQualsMethodsClass_DatetimeMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

