/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include "MI.h"
#include "TestClass_ForEmbedded.h"

void MI_CALL TestClass_ForEmbedded_Load(
    TestClass_ForEmbedded_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_ForEmbedded_Unload(
    TestClass_ForEmbedded_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_ForEmbedded_EnumerateInstances(
    TestClass_ForEmbedded_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_ForEmbedded_GetInstance(
    TestClass_ForEmbedded_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_ForEmbedded* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_ForEmbedded_CreateInstance(
    TestClass_ForEmbedded_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_ForEmbedded* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_ForEmbedded_ModifyInstance(
    TestClass_ForEmbedded_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_ForEmbedded* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_ForEmbedded_DeleteInstance(
    TestClass_ForEmbedded_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_ForEmbedded* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

