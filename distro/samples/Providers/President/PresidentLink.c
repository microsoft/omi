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
#include <common.h>
#include <base/strings.h>
#include "PresidentLink.h"

void MI_CALL PresidentLink_Load(
    PresidentLink_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL PresidentLink_Unload(
    PresidentLink_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL PresidentLink_EnumerateInstances(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL PresidentLink_GetInstance(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PresidentLink* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL PresidentLink_CreateInstance(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PresidentLink* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL PresidentLink_ModifyInstance(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PresidentLink* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL PresidentLink_DeleteInstance(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PresidentLink* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL PresidentLink_AssociatorInstances(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* assocClass,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result result;
    MI_Value value;
    MI_Type type;
    MI_Uint32 flags;

    if (Zcmp(assocClass, MI_T("PresidentLink")) != 0)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }

    if (Zcmp(resultClass, MI_T("President")) != 0)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }

    if (Zcmp(role, MI_T("Prev")) != 0 &&
        Zcmp(role, MI_T("Next")) != 0)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }

    if (Zcmp(resultRole, MI_T("Prev")) != 0 &&
        Zcmp(resultRole, MI_T("Next")) != 0)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }

    result = MI_Instance_GetElement(
        instanceName, MI_T("Key"), &value, &type, &flags, NULL);

    if (result != MI_RESULT_OK)
    {
        MI_PostResult(context, result);
        return;
    }

    if (type != MI_UINT32 || (flags & MI_FLAG_NULL))
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }

    if (value.uint32 == 1)
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, 2);
        President_Set_First(&inst, MI_T("John"));
        President_Set_Last(&inst, MI_T("Adams"));
        President_Post(&inst, context);
        President_Destruct(&inst);
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }

    if (value.uint32 == 2)
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, 1);
        President_Set_First(&inst, MI_T("George"));
        President_Set_Last(&inst, MI_T("Washington"));
        President_Post(&inst, context);
        President_Destruct(&inst);
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL PresidentLink_ReferenceInstances(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result result;
    MI_Value value;
    MI_Type type;
    MI_Uint32 flags;

    if (resultClass && Zcmp(resultClass, MI_T("PresidentLink")) != 0)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }

    if (role && 
        Zcmp(role, MI_T("Prev")) != 0 &&
        Zcmp(role, MI_T("Next")) != 0)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }

    result = MI_Instance_GetElement(
        instanceName, MI_T("Key"), &value, &type, &flags, NULL);

    if (result != MI_RESULT_OK || type != MI_UINT32 || flags & MI_FLAG_NULL)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }

    if ((!role || Zcmp(role, MI_T("Left")) == 0) && value.uint32 == 1)
    {
        President prev;
        President next;
        PresidentLink link;

        President_Construct(&prev, context);
        President_Set_Key(&prev, 1);

        President_Construct(&next, context);
        President_Set_Key(&next, 2);

        PresidentLink_Construct(&link, context);
        PresidentLink_Set_Prev(&link, &prev);
        PresidentLink_Set_Next(&link, &next);

        PresidentLink_Post(&link, context);
        MI_PostResult(context, MI_RESULT_OK);

        PresidentLink_Destruct(&link);
        President_Destruct(&prev);
        President_Destruct(&next);
        return;
    }

    if ((!role || Zcmp(role, MI_T("Right")) == 0) && value.uint32 == 2)
    {
        President prev;
        President next;
        PresidentLink link;

        President_Construct(&prev, context);
        President_Set_Key(&prev, 2);

        President_Construct(&next, context);
        President_Set_Key(&next, 1);

        PresidentLink_Construct(&link, context);
        PresidentLink_Set_Prev(&link, &prev);
        PresidentLink_Set_Next(&link, &next);

        PresidentLink_Post(&link, context);
        MI_PostResult(context, MI_RESULT_OK);

        PresidentLink_Destruct(&link);
        President_Destruct(&prev);
        President_Destruct(&next);
        return;
    }

    MI_PostResult(context, MI_RESULT_OK);
}

