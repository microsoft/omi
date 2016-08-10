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
#include "ABC_RegisteredProfile.h"

void MI_CALL ABC_RegisteredProfile_Load(
    ABC_RegisteredProfile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_RegisteredProfile_Unload(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_RegisteredProfile_EnumerateInstances(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_RegisteredProfile_GetInstance(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RegisteredProfile* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_RegisteredProfile_CreateInstance(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RegisteredProfile* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_RegisteredProfile_ModifyInstance(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RegisteredProfile* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_RegisteredProfile_DeleteInstance(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RegisteredProfile* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_RegisteredProfile_Invoke_CloseConformantInstances(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_RegisteredProfile* instanceName,
    const ABC_RegisteredProfile_CloseConformantInstances* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_RegisteredProfile_Invoke_OpenConformantInstances(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_RegisteredProfile* instanceName,
    const ABC_RegisteredProfile_OpenConformantInstances* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_RegisteredProfile_Invoke_PullConformantInstances(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_RegisteredProfile* instanceName,
    const ABC_RegisteredProfile_PullConformantInstances* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

