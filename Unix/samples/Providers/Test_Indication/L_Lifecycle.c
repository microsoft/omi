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
#include "L_Lifecycle.h"

void MI_CALL L_Lifecycle_Load(
    L_Lifecycle_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL L_Lifecycle_Unload(
    L_Lifecycle_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL L_Lifecycle_EnumerateInstances(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL L_Lifecycle_GetInstance(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_Lifecycle* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL L_Lifecycle_CreateInstance(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_Lifecycle* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL L_Lifecycle_ModifyInstance(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_Lifecycle* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL L_Lifecycle_DeleteInstance(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_Lifecycle* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL L_Lifecycle_Invoke_GenericMethod(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_Lifecycle* instanceName,
    const L_Lifecycle_GenericMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL L_Lifecycle_Invoke_ThreadControl(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_Lifecycle* instanceName,
    const L_Lifecycle_ThreadControl* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL L_Lifecycle_Invoke_GenericInstMethod(
    L_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_Lifecycle* instanceName,
    const L_Lifecycle_GenericInstMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

