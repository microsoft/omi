/* @migen@ */
#include <MI.h>
#include <base/strings.h>
#include "PS_Module.h"
#include "util.h"

void MI_CALL PS_Module_Load(
    _Outptr_result_maybenull_ PS_Module_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL PS_Module_Unload(
    _In_opt_ PS_Module_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL PS_Module_EnumerateInstances(
    _In_opt_ PS_Module_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_Result r;
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);
    r = ConstructModuleInstances(context);
    if ( r == MI_RESULT_OK )
        r = PS_Module_Post(&psmodule, context);
    DestructModuleInstances();
    MI_Context_PostResult(context, r);
}

void MI_CALL PS_Module_GetInstance(
    _In_opt_ PS_Module_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const PS_Module* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_Result r = MI_RESULT_INVALID_PARAMETER;
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);
    if ((instanceName->InstanceID.exists == MI_FALSE)||
        (instanceName->InstanceID.value == NULL))
    {
        MI_Context_PostResult(context, r);
        return;
    }
    if (Zcasecmp(instanceName->InstanceID.value, psmodule.InstanceID.value) == 0)
    {
        r = ConstructModuleInstances(context);
        if ( r == MI_RESULT_OK )
            r = PS_Module_Post(&psmodule, context);
        DestructModuleInstances();
    }
    MI_Context_PostResult(context, r);
}

void MI_CALL PS_Module_CreateInstance(
    _In_opt_ PS_Module_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const PS_Module* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL PS_Module_ModifyInstance(
    _In_opt_ PS_Module_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const PS_Module* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL PS_Module_DeleteInstance(
    _In_opt_ PS_Module_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const PS_Module* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

