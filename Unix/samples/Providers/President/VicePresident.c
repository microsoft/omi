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
    if (context && context->ft)
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

        /* Burr */
        {
            VicePresident inst;
            VicePresident_Construct(&inst, context);
            VicePresident_Set_Key(&inst, 3);
            VicePresident_Set_First(&inst, MI_T("Aaron"));
            VicePresident_Set_Last(&inst, MI_T("Burr"));
            VicePresident_Post(&inst, context);
            VicePresident_Destruct(&inst);
        }

        /* Clinton */
        {
            VicePresident inst;
            VicePresident_Construct(&inst, context);
            VicePresident_Set_Key(&inst, 4);
            VicePresident_Set_First(&inst, MI_T("George"));
            VicePresident_Set_Last(&inst, MI_T("Clinton"));
            VicePresident_Post(&inst, context);
            VicePresident_Destruct(&inst);
        }

        /* Elbridge Gerry */
        {
            VicePresident inst;
            VicePresident_Construct(&inst, context);
            VicePresident_Set_Key(&inst, 5);
            VicePresident_Set_First(&inst, MI_T("Elbridge"));
            VicePresident_Set_Last(&inst, MI_T("Gerry"));
            VicePresident_Post(&inst, context);
            VicePresident_Destruct(&inst);
        }
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

