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
#include "Number.h"
#include <base/base.h>

void MI_CALL Number_Load(
    Number_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Number_Unload(
    Number_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Number_EnumerateInstances(
    Number_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Uint32 i;
    Number inst;
    MI_Char buf[11];
    size_t size;

    Number_Construct(&inst, context);
    Number_SetPtr_Description(&inst, 
        MI_T("This is a long long long long string"));

    for (i = 0; i < 10000; i++)
    {
        Number_Set_Number(&inst, i);
        Number_Set_NumberString(&inst, Uint32ToZStr(buf, i, &size));
        Number_Post(&inst, context);
    }

    Number_Destruct(&inst);
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Number_GetInstance(
    Number_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Number* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Number_CreateInstance(
    Number_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Number* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Number_ModifyInstance(
    Number_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Number* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Number_DeleteInstance(
    Number_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Number* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

