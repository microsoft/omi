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

    /* Jefferson */
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, 3);
        President_Set_First(&inst, MI_T("Thomas"));
        President_Set_Last(&inst, MI_T("Jefferson"));
        President_Post(&inst, context);
        President_Destruct(&inst);
    }

    /* Madison */
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, 4);
        President_Set_First(&inst, MI_T("James"));
        President_Set_Last(&inst, MI_T("Madison"));
        President_Post(&inst, context);
        President_Destruct(&inst);
    }

    /* Monroe */
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, 5);
        President_Set_First(&inst, MI_T("James"));
        President_Set_Last(&inst, MI_T("Monroe"));
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
        President_Destruct(&inst);
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
        President_Destruct(&inst);
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }

    /* Jefferson */
    if (instanceName->Key.value == 3)
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, 3);
        President_Set_First(&inst, MI_T("Thomas"));
        President_Set_Last(&inst, MI_T("Jefferson"));
        President_Post(&inst, context);
        President_Destruct(&inst);
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }

    /* Madison */
    if (instanceName->Key.value == 4)
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, 4);
        President_Set_First(&inst, MI_T("James"));
        President_Set_Last(&inst, MI_T("Madison"));
        President_Post(&inst, context);
        President_Destruct(&inst);
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }
  
    /* Monroe */
    if (instanceName->Key.value == 5)
    {
        President inst;
        President_Construct(&inst, context);
        President_Set_Key(&inst, 5);
        President_Set_First(&inst, MI_T("James"));
        President_Set_Last(&inst, MI_T("Monroe"));
        President_Post(&inst, context);
        President_Destruct(&inst);
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
        President_Destruct(&inst);
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

