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
#include <stdio.h>
#include "President.h"

#if 0
# define D(EXPR) EXPR
#else
# define D(EXPR)
#endif

void MI_CALL President_Load(
    President_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    D( printf("==== President_Load()\n"); )
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL President_Unload(
    President_Self* self,
    MI_Context* context)
{
    D( printf("==== President_Unload()\n"); )
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL President_EnumerateInstances(
    President_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    D( printf("==== President_EnumerateInstances()\n"); )

    /* Washington */
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, 1);
        President_Set_First(&inst, MI_T("George"));
        President_Set_Last(&inst, MI_T("Washington"));
        President_Post(&inst, context);
        President_Destruct(&inst);
    }

    /* Adams */
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, 2);
        President_Set_First(&inst, MI_T("John"));
        President_Set_Last(&inst, MI_T("Adams"));
        President_Post(&inst, context);
        President_Destruct(&inst);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL President_GetInstance(
    President_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const President* instanceName,
    const MI_PropertySet* propertySet)
{
    D( printf("==== President_GetInstance()\n"); )

    /* Washington */
    if (instanceName->Key.value == 1)
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, 1);
        President_Set_First(&inst, MI_T("George"));
        President_Set_Last(&inst, MI_T("Washington"));
        President_Post(&inst, context);
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }

    /* Adams */
    if (instanceName->Key.value == 2)
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, 2);
        President_Set_First(&inst, MI_T("John"));
        President_Set_Last(&inst, MI_T("Adams"));
        President_Post(&inst, context);
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }

    MI_PostResult(context, MI_RESULT_NOT_FOUND);
}

void MI_CALL President_CreateInstance(
    President_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const President* newInstance)
{
    D( printf("==== President_CreateInstance()\n"); )

#if 0
    MI_Instance_Print(MI_InstanceOf(newInstance), stdout, 0);

    // Post key back to requestor!
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, newInstance->Key.value);

        MI_Instance_Print(MI_InstanceOf(&inst), stdout, 0);

        President_Post(&inst, context);
        MI_PostResult(context, MI_RESULT_OK);
    }
#else
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
#endif
}

void MI_CALL President_ModifyInstance(
    President_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const President* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    D( printf("==== President_ModifyInstance()\n"); )

#if 0
    MI_Instance_Print(MI_InstanceOf(modifiedInstance), stdout, 0);
    MI_PostResult(context, MI_RESULT_OK);
#else
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
#endif
}

void MI_CALL President_DeleteInstance(
    President_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const President* instanceName)
{
    D( printf("==== President_DeleteInstance()\n"); )
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

