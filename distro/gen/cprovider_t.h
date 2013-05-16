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

//==============================================================================
//
// cprovider.h - source code templates for the provider .c file.
//
//==============================================================================

#ifndef _migen_cprovider_t_h
#define _migen_cprovider_t_h

//==============================================================================
//
// COMMON_PROVIDER_STUBS
//
//==============================================================================

#define COMMON_PROVIDER_STUBS "\
void MI_CALL <ALIAS>_Load(\n\
    <ALIAS>_Self** self,\n\
    MI_Module_Self* selfModule,\n\
    MI_Context* context)\n\
{\n\
    *self = NULL;\n\
    MI_PostResult(context, MI_RESULT_OK);\n\
}\n\
\n\
void MI_CALL <ALIAS>_Unload(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context)\n\
{\n\
    MI_PostResult(context, MI_RESULT_OK);\n\
}\n\
\n"

//==============================================================================
//
// INSTANCE_PROVIDER_STUBS
//
//==============================================================================

#define INSTANCE_PROVIDER_STUBS COMMON_PROVIDER_STUBS "\
void MI_CALL <ALIAS>_EnumerateInstances(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void MI_CALL <ALIAS>_GetInstance(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS>* instanceName,\n\
    const MI_PropertySet* propertySet)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void MI_CALL <ALIAS>_CreateInstance(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS>* newInstance)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void MI_CALL <ALIAS>_ModifyInstance(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS>* modifiedInstance,\n\
    const MI_PropertySet* propertySet)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void MI_CALL <ALIAS>_DeleteInstance(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS>* instanceName)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n"

//==============================================================================
//
// ASSOCIATION_PROVIDER_STUBS
//
//==============================================================================

#define ASSOCIATION_PROVIDER_STUBS INSTANCE_PROVIDER_STUBS "\
void MI_CALL <ALIAS>_AssociatorInstances(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const MI_Instance* instanceName,\n\
    const MI_Char* resultClass,\n\
    const MI_Char* role,\n\
    const MI_Char* resultRole,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void MI_CALL <ALIAS>_ReferenceInstances(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const MI_Instance* instanceName,\n\
    const MI_Char* role,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n"

#define ROLE_PROVIDER_STUBS INSTANCE_PROVIDER_STUBS "\
void MI_CALL <ALIAS>_AssociatorInstances<ROLE1>(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS1>* instanceName,\n\
    const MI_Char* resultClass,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void MI_CALL <ALIAS>_AssociatorInstances<ROLE2>(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS2>* instanceName,\n\
    const MI_Char* resultClass,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void MI_CALL <ALIAS>_ReferenceInstances<ROLE1>(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS1>* instanceName,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void MI_CALL <ALIAS>_ReferenceInstances<ROLE2>(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS2>* instanceName,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n"

//==============================================================================
//
// INDICATION_PROVIDER_STUBS
//
//==============================================================================

#define INDICATION_PROVIDER_STUBS COMMON_PROVIDER_STUBS "\
void MI_CALL <ALIAS>_EnableIndications(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* indicationsContext,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className)\n\
{\n\
    /* TODO: store indicationsContext for later usage */\n\
    /* NOTE: Do not call MI_PostResult on this context */\n\
}\n\
\n\
void MI_CALL <ALIAS>_DisableIndications(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* indicationsContext,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className)\n\
{\n\
    /* TODO: stop background thread that monitors subscriptions */\n\
\n\
    MI_PostResult(indicationsContext, MI_RESULT_OK);\n\
}\n\
\n\
void MI_CALL <ALIAS>_Subscribe(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const MI_Filter* filter,\n\
    const MI_Char* bookmark,\n\
    MI_Uint64  subscriptionID,\n\
    void** subscriptionSelf)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void MI_CALL <ALIAS>_Unsubscribe(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    MI_Uint64  subscriptionID,\n\
    void* subscriptionSelf)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n"

//==============================================================================
//
// EXTRINSIC_METHOD_STUB
//
//==============================================================================

#define EXTRINSIC_METHOD_STUB "\
void MI_CALL <ALIAS>_Invoke_<METHOD>(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const MI_Char* methodName,\n\
    const <ALIAS>* instanceName,\n\
    const <ALIAS>_<METHOD>* in)\n\
{\n\
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n"

#endif /* _migen_cprovider_t_h */
