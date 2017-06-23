/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <common.h>
#include <pal/strings.h>
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

    if (Tcscmp(assocClass, MI_T("MSFT_PresidentLink")) != 0)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }

    if (Tcscmp(resultClass, MI_T("MSFT_President")) != 0)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }

    if (Tcscmp(role, MI_T("Prev")) != 0 &&
        Tcscmp(role, MI_T("Next")) != 0)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }

    if (Tcscmp(resultRole, MI_T("Prev")) != 0 &&
        Tcscmp(resultRole, MI_T("Next")) != 0)
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

    if (resultClass && Tcscmp(resultClass, MI_T("MSFT_PresidentLink")) != 0)
    {
        MI_PostResult(context, MI_RESULT_INVALID_PARAMETER);
        return;
    }

    if (role && 
        Tcscmp(role, MI_T("Prev")) != 0 &&
        Tcscmp(role, MI_T("Next")) != 0)
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

    if ((!role || Tcscmp(role, MI_T("Prev")) == 0) && value.uint32 == 1)
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

    if ((!role || Tcscmp(role, MI_T("Next")) == 0) && value.uint32 == 2)
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

