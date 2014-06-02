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
#include "VicePresident.h"

void MI_CALL VicePresident_Load(
    VicePresident_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL VicePresident_Unload(
    VicePresident_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL VicePresident_EnumerateInstances(
    VicePresident_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    /* Adams */
    {
        VicePresident inst;
        VicePresident_Construct(&inst, context);
        VicePresident_Set_Key(&inst, 1);
        VicePresident_Set_First(&inst, MI_T("John"));
        VicePresident_Set_Last(&inst, MI_T("Adams"));
        VicePresident_Post(&inst, context);
        VicePresident_Destruct(&inst);
    }

    /* Jefferson */
    {
        VicePresident inst;
        VicePresident_Construct(&inst, context);
        VicePresident_Set_Key(&inst, 2);
        VicePresident_Set_First(&inst, MI_T("Thomas"));
        VicePresident_Set_Last(&inst, MI_T("Jefferson"));
        VicePresident_Post(&inst, context);
        VicePresident_Destruct(&inst);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL VicePresident_GetInstance(
    VicePresident_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const VicePresident* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL VicePresident_CreateInstance(
    VicePresident_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const VicePresident* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL VicePresident_ModifyInstance(
    VicePresident_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const VicePresident* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL VicePresident_DeleteInstance(
    VicePresident_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const VicePresident* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

