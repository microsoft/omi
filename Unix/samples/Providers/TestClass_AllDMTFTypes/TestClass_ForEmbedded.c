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
#include "TestClass_ForEmbedded.h"

void MI_CALL TestClass_ForEmbedded_Load(
    _Outptr_result_maybenull_ TestClass_ForEmbedded_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_ForEmbedded_Unload(
    _In_opt_ TestClass_ForEmbedded_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_ForEmbedded_EnumerateInstances(
    _In_opt_ TestClass_ForEmbedded_Self* self,
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

    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_ForEmbedded_GetInstance(
    _In_opt_ TestClass_ForEmbedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TestClass_ForEmbedded* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_ForEmbedded_CreateInstance(
    _In_opt_ TestClass_ForEmbedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TestClass_ForEmbedded* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_ForEmbedded_ModifyInstance(
    _In_opt_ TestClass_ForEmbedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TestClass_ForEmbedded* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_ForEmbedded_DeleteInstance(
    _In_opt_ TestClass_ForEmbedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const TestClass_ForEmbedded* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

