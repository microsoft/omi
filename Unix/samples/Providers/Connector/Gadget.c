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
#include "Gadget.h"

static Gadget* FindGadget(MI_Uint32 SerialNumber)
{
    return NULL;
}

void MI_CALL Gadget_Load(
    Gadget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Gadget_Unload(
    Gadget_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Gadget_EnumerateInstances(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Gadget_GetInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Gadget_CreateInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Gadget_ModifyInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Gadget_DeleteInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Gadget_Invoke_ChangeState(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Gadget* instanceName,
    const Gadget_ChangeState* in)
{
    Gadget* g;
    
    /* Find the gadget with the given instance name */
    g = FindGadget(instanceName->SerialNumber.value);

    if (g)
    {
        Gadget_ChangeState out;

        /* Build and post the output parameter and return value */
        Gadget_ChangeState_Construct(&out, context);
        Gadget_ChangeState_Set_OldState(&out, g->State.value);
        Gadget_ChangeState_Set_MIReturn(&out, 0);
        Gadget_ChangeState_Post(&out, context);
        Gadget_ChangeState_Destruct(&out);

        /* Update the gadget */
        g->State = in->NewState;

        /* Post result and return */
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }

    /* Not found */
    MI_PostResult(context, MI_RESULT_NOT_FOUND);
}
void MI_CALL Gadget_Invoke_Foo(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Gadget* instanceName,
    const Gadget_Foo* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

