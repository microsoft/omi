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
#include "OMI_EthernetPort.h"

void MI_CALL OMI_EthernetPort_Load(
    OMI_EthernetPort_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL OMI_EthernetPort_Unload(
    OMI_EthernetPort_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL OMI_EthernetPort_EnumerateInstances(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_EthernetPort_GetInstance(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_EthernetPort* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_EthernetPort_CreateInstance(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_EthernetPort* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_EthernetPort_ModifyInstance(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_EthernetPort* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_EthernetPort_DeleteInstance(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_EthernetPort* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_EthernetPort_Invoke_RequestStateChange(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_RequestStateChange* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_EthernetPort_Invoke_SetPowerState(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_SetPowerState* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_EthernetPort_Invoke_Reset(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_Reset* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_EthernetPort_Invoke_EnableDevice(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_EnableDevice* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_EthernetPort_Invoke_OnlineDevice(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_OnlineDevice* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_EthernetPort_Invoke_QuiesceDevice(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_QuiesceDevice* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_EthernetPort_Invoke_SaveProperties(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_SaveProperties* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_EthernetPort_Invoke_RestoreProperties(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_RestoreProperties* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

