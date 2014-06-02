/* @migen@ */
#include <MI.h>
#include "Address.h"

#if 0

#include <TypeConvertor.h>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <ProviderUtil.h>

#define IF_NOERROR_WRITE(_result, _context, _name, _type, _val) \
{ \
    if(_result == MI_RESULT_OK) \
    { \
        ConvertAndWrite(_context, _name, _type, _val); \
    } \
}

#define IF_NOERROR_WRITE_FOREACH(_result, _context, _name, _type, _valArray, _tmpVal,_typeName) \
{ \
    if(_result == MI_RESULT_OK) \
    { \
        for(MI_Uint32 i = 0; i < _valArray##.size; i++) \
        { \
            _tmpVal.##_typeName = _valArray##.data[i]; \
            ConvertAndWrite(_context, _name, _type, _tmpVal); \
        } \
    } \
}

static void CALLBACK TimerCallback(PTP_CALLBACK_INSTANCE instance, PVOID self, PTP_TIMER timer)
{
    MI_Result result = MI_RESULT_FAILED;

    if(!self)
        return;

    Address_Self * _self = (Address_Self *) self;

    result = MI_WriteVerbose(_self->refuseUnloadContext, L"TimerCallback: called MI_RequestUnload");
    result = MI_RequestUnload(_self->refuseUnloadContext);    

    CloseThreadpoolTimer(_self->longRunningTimer);

    if(result != MI_RESULT_OK)
        POST_ERROR(_self->refuseUnloadContext, result, MI_RESULT_TYPE_MI, MI_T("Request unload failed"));

    MI_PostResult(_self->refuseUnloadContext, result);    
}

MI_Boolean CheckForLongRunningScenario(MI_Context* context, Address_Self *self)
{
    MI_Result result = MI_RESULT_FAILED;
    MI_Boolean isLongRunning = MI_FALSE;
    
    result = MI_GetCustomOption(context, MI_T("LongRunningTask"), NULL, NULL);
    if(result == MI_RESULT_OK)
    {
        MI_Value val;

        result = MI_GetCustomOption(context, MI_T("LongRunningTimer"), NULL, &val);
        if(result == MI_RESULT_OK)
        {
            result = MI_RefuseUnload(context);
            if(result == MI_RESULT_OK)
            {
                isLongRunning = MI_TRUE;

                FILETIME now;
                ZeroMemory(&now, sizeof(FILETIME));

                //set to fire in x seconds once, as per operation option LongRunningTimer
                ULARGE_INTEGER ulDateTime;
                ulDateTime.QuadPart =  (ULONGLONG) -(val.sint32 * 10 * 1000 * 1000);

                now.dwHighDateTime = ulDateTime.HighPart;
                now.dwLowDateTime = ulDateTime.LowPart;

                self->refuseUnloadContext = context;
                self->longRunningTimer = CreateThreadpoolTimer(TimerCallback, self, NULL);
                SetThreadpoolTimer(self->longRunningTimer, &now, 0, 0);
            }
        }
    }

    return isLongRunning;
}

MI_Result ConvertAndWrite(MI_Context* context, MI_Char* optionName, MI_Type type, MI_Value val)
{
    std::wstring strValue;
    std::wstringstream msg;

    TypeConvertor convertor;

    msg << optionName << MI_T(" : type = ") << type;

    if(type != MI_STRING)
    {    
        convertor.GetWstr(type, (void *) &val, strValue);
        msg << MI_T(" : value = ") << strValue.c_str();
    }
    else
    {
        msg << MI_T(" : value = ") << val.string;
    }

    return MI_WriteWarning(context, msg.str().c_str());
}

void inline CheckError(MI_Result result, MI_Context *context, MI_Char* name, MI_Type &type, MI_Value &val)
{
    if(result == MI_RESULT_OK) 
    { 
        ConvertAndWrite(context, name, type, val); 
    }
}

void GetAndWriteCustomOptions(MI_Context* context)
{
    MI_Value val; 
    MI_Type type;
    MI_Value tmpVal;

    CheckError(MI_GetCustomOption(context, MI_T("op_sint8"), &type, &val), context, MI_T("op_sint8"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_uint8"), &type, &val), context, MI_T("op_uint8"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_sint16"), &type, &val), context, MI_T("op_sint16"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_uint16"), &type, &val), context, MI_T("op_uint16"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_sint32"), &type, &val), context, MI_T("op_sint32"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_uint32"), &type, &val), context, MI_T("op_uint32"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_sint64"), &type, &val), context, MI_T("op_sint64"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_uint64"), &type, &val), context, MI_T("op_uint64"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_real32"), &type, &val), context, MI_T("op_real32"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_real64"), &type, &val), context, MI_T("op_real64"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_bool"), &type, &val), context, MI_T("op_bool"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_string"), &type, &val), context, MI_T("op_string"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_datetime"), &type, &val), context, MI_T("op_datetime"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_char16"), &type, &val), context, MI_T("op_char16"), type, val);
    CheckError(MI_GetCustomOption(context, MI_T("op_instance"), &type, &val), context, MI_T("op_instance"), type, val);

    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_sint8a"), &type, &val), context, MI_T("op_sint8"), MI_SINT8, val.sint8a, tmpVal, sint8);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_uint8a"), &type, &val), context, MI_T("op_uint8"), MI_UINT8, val.uint8a, tmpVal, uint8);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_sint16a"), &type, &val), context, MI_T("op_sint16"), MI_SINT16, val.sint16a, tmpVal, sint16);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_uint16a"), &type, &val), context, MI_T("op_uint16"), MI_UINT16, val.uint16a, tmpVal, uint16);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_sint32a"), &type, &val), context, MI_T("op_sint32"), MI_SINT32, val.sint32a, tmpVal, sint32);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_uint32a"), &type, &val), context, MI_T("op_uint32"), MI_UINT32, val.uint32a, tmpVal, uint32);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_sint64a"), &type, &val), context, MI_T("op_sint64"), MI_SINT64, val.sint64a, tmpVal, sint64);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_uint64a"), &type, &val), context, MI_T("op_uint64"), MI_UINT64, val.sint64a, tmpVal, uint64);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_real32a"), &type, &val), context, MI_T("op_real32"), MI_REAL32, val.real32a, tmpVal, real32);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_real64a"), &type, &val), context, MI_T("op_real64"), MI_REAL64, val.real64a, tmpVal, real64);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_boola"), &type, &val), context, MI_T("op_bool"), MI_BOOLEAN, val.booleana, tmpVal, boolean);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_stringa"), &type, &val), context, MI_T("op_string"), MI_STRING, val.stringa, tmpVal, string);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_datetimea"), &type, &val), context, MI_T("op_datetime"), MI_DATETIMEA, val.datetimea, tmpVal, datetime);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_char16a"), &type, &val), context, MI_T("op_char16a"), MI_CHAR16, val.char16a, tmpVal, char16);
    IF_NOERROR_WRITE_FOREACH(MI_GetCustomOption(context, MI_T("op_instancea"), &type, &val), context, MI_T("op_instance"), MI_INSTANCE, val.instancea, tmpVal, instance);    
}

#endif

struct _Address_Self
{
    MI_Context* refuseUnloadContext;
    //PTP_TIMER longRunningTimer;
};

void MI_CALL Address_Load(
    _Outptr_result_maybenull_ Address_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = new Address_Self;
    (*self)->refuseUnloadContext = NULL;

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Address_Unload(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context)
{
    if(self != NULL) 
        delete self;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Address_EnumerateInstances(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Address_GetInstance(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Address* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    Address_Post(instanceName, context);

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Address_CreateInstance(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Address* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    Address_Post(newInstance, context);
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Address_ModifyInstance(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Address* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Address_DeleteInstance(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Address* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Address_Invoke_OperationOptionsStatic(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Address* instanceName,
    _In_opt_ const Address_OperationOptionsStatic* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Address_Invoke_OperationOptionsInstance(
    _In_opt_ Address_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Address* instanceName,
    _In_opt_ const Address_OperationOptionsInstance* in)
{    
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_PostResult(context, MI_RESULT_OK);
}

