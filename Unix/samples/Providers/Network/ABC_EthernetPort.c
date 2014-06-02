/* @migen@ */
#include <MI.h>
#include "ABC_EthernetPort.h"

void MI_CALL ABC_EthernetPort_Load(
    ABC_EthernetPort_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_EthernetPort_Unload(
    ABC_EthernetPort_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_EthernetPort_EnumerateInstances(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EthernetPort_GetInstance(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EthernetPort* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EthernetPort_CreateInstance(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EthernetPort* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EthernetPort_ModifyInstance(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EthernetPort* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EthernetPort_DeleteInstance(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EthernetPort* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EthernetPort_Invoke_RequestStateChange(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_RequestStateChange* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EthernetPort_Invoke_SetPowerState(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_SetPowerState* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EthernetPort_Invoke_Reset(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_Reset* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EthernetPort_Invoke_EnableDevice(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_EnableDevice* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EthernetPort_Invoke_OnlineDevice(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_OnlineDevice* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EthernetPort_Invoke_QuiesceDevice(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_QuiesceDevice* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EthernetPort_Invoke_SaveProperties(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_SaveProperties* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EthernetPort_Invoke_RestoreProperties(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_RestoreProperties* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

