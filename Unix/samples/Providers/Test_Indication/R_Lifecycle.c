/* @migen@ */
#include <MI.h>
#include "R_Lifecycle.h"

void MI_CALL R_Lifecycle_Load(
    R_Lifecycle_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_Lifecycle_Unload(
    R_Lifecycle_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_Lifecycle_EnumerateInstances(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL R_Lifecycle_GetInstance(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_Lifecycle* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL R_Lifecycle_CreateInstance(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_Lifecycle* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL R_Lifecycle_ModifyInstance(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_Lifecycle* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL R_Lifecycle_DeleteInstance(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_Lifecycle* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL R_Lifecycle_Invoke_GenericMethod(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_Lifecycle* instanceName,
    const R_Lifecycle_GenericMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL R_Lifecycle_Invoke_ThreadControl(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_Lifecycle* instanceName,
    const R_Lifecycle_ThreadControl* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL R_Lifecycle_Invoke_GenericInstMethod(
    R_Lifecycle_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_Lifecycle* instanceName,
    const R_Lifecycle_GenericInstMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

