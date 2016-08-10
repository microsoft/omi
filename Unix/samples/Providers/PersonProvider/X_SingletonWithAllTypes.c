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
#include "X_SingletonWithAllTypes.h"

void MI_CALL X_SingletonWithAllTypes_Load(
    X_SingletonWithAllTypes_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL X_SingletonWithAllTypes_Unload(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL X_SingletonWithAllTypes_EnumerateInstances(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL X_SingletonWithAllTypes_GetInstance(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SingletonWithAllTypes* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL X_SingletonWithAllTypes_CreateInstance(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SingletonWithAllTypes* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL X_SingletonWithAllTypes_ModifyInstance(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SingletonWithAllTypes* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL X_SingletonWithAllTypes_DeleteInstance(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SingletonWithAllTypes* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

