/* @migen@ */
#include <MI.h>
#include "Gadget.h"

void MI_CALL Gadget_Load(
    Gadget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Gadget_Unload(
    Gadget_Self* self,
    MI_Context* context)
{
    MI_Context_PostResult(context, MI_RESULT_OK);
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
    // Gadget.Key=1003:
    Gadget gadget1;
    Gadget_Construct(&gadget1, context);
    Gadget_Set_Key(&gadget1, 1003);
    Gadget_Set_ModelNumber(&gadget1, 3);
    Gadget_Set_Size(&gadget1, 33);
    Gadget_Post(&gadget1, context);
    Gadget_Destruct(&gadget1);

    // Gadget.Key=1004:
    Gadget gadget2;
    Gadget_Construct(&gadget2, context);
    Gadget_Set_Key(&gadget2, 1004);
    Gadget_Set_ModelNumber(&gadget2, 4);
    Gadget_Set_Size(&gadget2, 43);
    Gadget_Post(&gadget2, context);
    Gadget_Destruct(&gadget2);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Gadget_GetInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_Result r = MI_RESULT_OK;
    Gadget g;
    Gadget_Construct(&g, context);
    if (instanceName->Key.value == 1003)
    {
        // Gadget.Key=1003:
        Gadget_Set_Key(&g, 1003);
        Gadget_Set_ModelNumber(&g, 3);
        Gadget_Set_Size(&g, 33);
        Gadget_Post(&g, context);
    }
    else if (instanceName->Key.value == 1004)
    {
        // Gadget.Key=1004:
        Gadget_Set_Key(&g, 1004);
        Gadget_Set_ModelNumber(&g, 4);
        Gadget_Set_Size(&g, 43);
        Gadget_Post(&g, context);
    }
    else
    {
        r = MI_RESULT_NOT_FOUND;
    }

    Gadget_Destruct(&g);
    MI_Context_PostResult(context, r);
}

void MI_CALL Gadget_CreateInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* newInstance)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Gadget_ModifyInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Gadget_DeleteInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
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
    Gadget_ChangeState out;
    Gadget_ChangeState_Construct(&out, context);

    // Perform desired action here
    // ...
    
    // Set the output parameter
    Gadget_ChangeState_Set_OldState(&out, 2);

    // Set the return value
    Gadget_ChangeState_Set_MIReturn(&out, MI_RESULT_OK);

    // Post the output parameters
    Gadget_ChangeState_Post(&out, context);

    Gadget_ChangeState_Destruct(&out);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

