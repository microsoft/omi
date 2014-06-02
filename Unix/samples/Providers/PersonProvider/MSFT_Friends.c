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
#include "MSFT_Friends.h"
#include "MSFT_Person.h"
#include <ctype.h>

void MI_CALL MSFT_Friends_Load(
    MSFT_Friends_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_Friends_Unload(
    MSFT_Friends_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_Friends_EnumerateInstances(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_Friends_GetInstance(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Friends* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_Friends_CreateInstance(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Friends* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_Friends_ModifyInstance(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Friends* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_Friends_DeleteInstance(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Friends* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

static int _Match(const MI_Char* p, const MI_Char* q)
{
    if (!p || !q)
        return 0;

    while (*p && *q)
        if (toupper((MI_Uint16)*p++) - toupper((MI_Uint16)*q++))
            return 0;

    return *p == '\0' && *q == '\0';
}

void MI_CALL MSFT_Friends_AssociatorInstances(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (MSFT_Person_IsA(instanceName))
    {
        if (_Match(role, MI_T("Left")) && 
            _Match(resultRole, MI_T("Right")))
        {
    if (((MSFT_Person*)instanceName)->Key.exists && ((MSFT_Person*)instanceName)->Key.value == 1)
    {
        MSFT_Person inst;
        MSFT_Person_Construct(&inst, context);
        MSFT_Person_Set_Key(&inst, 2);
        MSFT_Person_Set_First(&inst, MI_T("John"));
        MSFT_Person_Set_Last(&inst, MI_T("Adams"));
        MSFT_Person_Post(&inst, context);
        MSFT_Person_Destruct(&inst);
    }
}}

    if (MSFT_Person_IsA(instanceName))
    {
        if (_Match(role, MI_T("Right")) && 
            _Match(resultRole, MI_T("Left")))
        {
    if (((MSFT_Person*)instanceName)->Key.exists && ((MSFT_Person*)instanceName)->Key.value == 2)
    {
        MSFT_Person inst;
        MSFT_Person_Construct(&inst, context);
        MSFT_Person_Set_Key(&inst, 1);
        MSFT_Person_Set_First(&inst, MI_T("George"));
        MSFT_Person_Set_Last(&inst, MI_T("Washington"));
        MSFT_Person_Post(&inst, context);
        MSFT_Person_Destruct(&inst);
    }
}}
    MI_PostResult(context, MI_RESULT_OK);
}


void MI_CALL MSFT_Friends_ReferenceInstances(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}


void MI_CALL MSFT_Friends_Invoke_AddFriends(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Friends* instanceName,
    const MSFT_Friends_AddFriends* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_Friends_Invoke_AddFriend(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Friends* instanceName,
    const MSFT_Friends_AddFriend* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}
