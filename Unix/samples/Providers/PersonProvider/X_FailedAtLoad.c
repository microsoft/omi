/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include "X_FailedAtLoad.h"
#include <assert.h>

void MI_CALL X_FailedAtLoad_Load(
    X_FailedAtLoad_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    /* return this weird error code for unit-testing */
    MI_PostResult(context, MI_RESULT_SERVER_LIMITS_EXCEEDED);
}

void MI_CALL X_FailedAtLoad_Unload(
    X_FailedAtLoad_Self* self,
    MI_Context* context)
{
    assert("since load returned an error, this function should never be called!" && NULL);
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL X_FailedAtLoad_EnumerateInstances(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    assert("since load returned an error, this function should never be called!" && NULL);
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL X_FailedAtLoad_GetInstance(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_FailedAtLoad* instanceName,
    const MI_PropertySet* propertySet)
{
    assert("since load returned an error, this function should never be called!" && NULL);
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL X_FailedAtLoad_CreateInstance(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_FailedAtLoad* newInstance)
{
    assert("since load returned an error, this function should never be called!" && NULL);
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL X_FailedAtLoad_ModifyInstance(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_FailedAtLoad* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    assert("since load returned an error, this function should never be called!" && NULL);
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL X_FailedAtLoad_DeleteInstance(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_FailedAtLoad* instanceName)
{
    assert("since load returned an error, this function should never be called!" && NULL);
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}
