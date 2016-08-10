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
