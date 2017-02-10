/* @migen@ */
#include <MI.h>
#include "Hosts.h"

void MI_CALL Hosts_Load(
    Hosts_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Hosts_Unload(
    Hosts_Self* self,
    MI_Context* context)
{
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Hosts_EnumerateInstances(
    Hosts_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Hosts_GetInstance(
    Hosts_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Hosts* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Hosts_CreateInstance(
    Hosts_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Hosts* newInstance)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Hosts_ModifyInstance(
    Hosts_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Hosts* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Hosts_DeleteInstance(
    Hosts_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Hosts* instanceName)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Hosts_Invoke_Ping(
    Hosts_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Hosts* instanceName,
    const Hosts_Ping* in)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

