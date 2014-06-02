/* @migen@ */
#include <MI.h>
#include "MySimpleParamMethodsClass.h"

void MI_CALL MySimpleParamMethodsClass_Load(
    MySimpleParamMethodsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MySimpleParamMethodsClass_Unload(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_BooleanSimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_BooleanSimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_StringSimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_StringSimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_Char16SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Char16SimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_Uint8SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Uint8SimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_Sint8SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Sint8SimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_Uint16SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Uint16SimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_Sint16SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Sint16SimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_Uint32SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Uint32SimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_Sint32SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Sint32SimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_Uint64SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Uint64SimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_Sint64SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Sint64SimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_Real32SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Real32SimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_Real64SimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_Real64SimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MySimpleParamMethodsClass_Invoke_DatetimeSimpleParamMethod(
    MySimpleParamMethodsClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySimpleParamMethodsClass* instanceName,
    const MySimpleParamMethodsClass_DatetimeSimpleParamMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

