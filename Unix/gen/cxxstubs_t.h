//==============================================================================
//
// stubs.h - templates for generating 'stubs.cpp'.
//
//==============================================================================

#ifndef _migen_cxxstubs_t_h
#define _migen_cxxstubs_t_h

//==============================================================================
//
// COMMON_PROVIDER_STUBS_CPP
//
//==============================================================================

#define COMMON_PROVIDER_STUBS_CPP "\
MI_EXTERN_C void MI_CALL <ALIAS>_Load(\n\
    <ALIAS>_Self** self,\n\
    MI_Module_Self* selfModule,\n\
    MI_Context* context)\n\
{\n\
    MI_Result r = MI_RESULT_OK;\n\
    Context ctx(context, &r);\n\
    <ALIAS>_Class_Provider* prov = new <ALIAS>_Class_Provider((Module*)selfModule);\n\
\n\
    prov->Load(ctx);\n\
    if (MI_RESULT_OK != r)\n\
    {\n\
        delete prov;\n\
        MI_Context_PostResult(context, r);\n\
        return;\n\
    }\n\
    *self = (<ALIAS>_Self*)prov;\n\
    MI_Context_PostResult(context, MI_RESULT_OK);\n\
}\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_Unload(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context)\n\
{\n\
    MI_Result r = MI_RESULT_OK;\n\
    Context ctx(context, &r);\n\
    <ALIAS>_Class_Provider* prov = (<ALIAS>_Class_Provider*)self;\n\
\n\
    prov->Unload(ctx);\n\
    delete ((<ALIAS>_Class_Provider*)self);\n\
    MI_Context_PostResult(context, r);\n\
}\n\
\n"

//==============================================================================
//
// INSTANCE_PROVIDER_STUBS_CPP
//
//==============================================================================

#define INSTANCE_PROVIDER_STUBS_CPP COMMON_PROVIDER_STUBS_CPP   "\
MI_EXTERN_C void MI_CALL <ALIAS>_EnumerateInstances(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    Context  cxxContext(context);\n\
\n\
    cxxSelf->EnumerateInstances(\n\
        cxxContext,\n\
        nameSpace,\n\
        __PropertySet(propertySet),\n\
        __bool(keysOnly),\n\
        filter);\n\
}\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_GetInstance(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS>* instanceName,\n\
    const MI_PropertySet* propertySet)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    Context  cxxContext(context);\n\
    <ALIAS>_Class cxxInstanceName(instanceName, true);\n\
\n\
    cxxSelf->GetInstance(\n\
        cxxContext,\n\
        nameSpace,\n\
        cxxInstanceName,\n\
        __PropertySet(propertySet));\n\
}\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_CreateInstance(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS>* newInstance)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    Context  cxxContext(context);\n\
    <ALIAS>_Class cxxNewInstance(newInstance, false);\n\
\n\
    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);\n\
}\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_ModifyInstance(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS>* modifiedInstance,\n\
    const MI_PropertySet* propertySet)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    Context  cxxContext(context);\n\
    <ALIAS>_Class cxxModifiedInstance(modifiedInstance, false);\n\
\n\
    cxxSelf->ModifyInstance(\n\
        cxxContext,\n\
        nameSpace,\n\
        cxxModifiedInstance,\n\
        __PropertySet(propertySet));\n\
}\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_DeleteInstance(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS>* instanceName)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    Context  cxxContext(context);\n\
    <ALIAS>_Class cxxInstanceName(instanceName, true);\n\
\n\
    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);\n\
}\n\
\n"

//==============================================================================
//
// ASSOCIATION_PROVIDER_STUBS_CPP
//
//==============================================================================

#define ASSOCIATION_PROVIDER_STUBS_CPP INSTANCE_PROVIDER_STUBS_CPP "\
MI_EXTERN_C void MI_CALL <ALIAS>_AssociatorInstances(\n\
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
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    Context  cxxContext(context);\n\
\n\
    cxxSelf->AssociatorInstances(\n\
        cxxContext, \n\
        nameSpace,\n\
        instanceName, \n\
        resultClass,\n\
        role,\n\
        resultRole,\n\
        __PropertySet(propertySet),\n\
        __bool(keysOnly),\n\
        filter);\n\
}\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_ReferenceInstances(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* resultClass,\n\
    const MI_Instance* instanceName,\n\
    const MI_Char* role,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    Context  cxxContext(context);\n\
\n\
    cxxSelf->ReferenceInstances(\n\
        cxxContext,\n\
        nameSpace,\n\
        instanceName,\n\
        role,\n\
        __PropertySet(propertySet),\n\
        __bool(keysOnly),\n\
        filter);\n\
}\n\
\n"

#define ASSOCIATION_PROVIDER_STUBS_CPP_ROLES INSTANCE_PROVIDER_STUBS_CPP "\
MI_EXTERN_C void MI_CALL <ALIAS>_AssociatorInstances<ROLE1>(\n\
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
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    <ALIAS1>_Class cxxInstanceName(instanceName, true);\n\
    Context  cxxContext(context);\n\
\n\
    cxxSelf->AssociatorInstances<ROLE1>(\n\
        cxxContext, \n\
        nameSpace,\n\
        cxxInstanceName,\n\
        resultClass,\n\
        __PropertySet(propertySet),\n\
        __bool(keysOnly),\n\
        filter);\n\
}\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_AssociatorInstances<ROLE2>(\n\
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
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    <ALIAS2>_Class cxxInstanceName(instanceName, true);\n\
    Context  cxxContext(context);\n\
\n\
    cxxSelf->AssociatorInstances<ROLE2>(\n\
        cxxContext,\n\
        nameSpace,\n\
        cxxInstanceName,\n\
        resultClass,\n\
        __PropertySet(propertySet),\n\
        __bool(keysOnly),\n\
        filter);\n\
}\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_ReferenceInstances<ROLE1>(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* resultClass,\n\
    const <ALIAS1>* instanceName,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    <ALIAS1>_Class cxxInstanceName(instanceName, true);\n\
    Context  cxxContext(context);\n\
\n\
    cxxSelf->ReferenceInstances<ROLE1>(\n\
        cxxContext,\n\
        nameSpace,\n\
        cxxInstanceName,\n\
        __PropertySet(propertySet),\n\
        __bool(keysOnly),\n\
        filter);\n\
}\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_ReferenceInstances<ROLE2>(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* resultClass,\n\
    const <ALIAS2>* instanceName,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    <ALIAS2>_Class cxxInstanceName(instanceName, true);\n\
    Context  cxxContext(context);\n\
\n\
    cxxSelf->ReferenceInstances<ROLE2>(\n\
        cxxContext,\n\
        nameSpace,\n\
        cxxInstanceName,\n\
        __PropertySet(propertySet),\n\
        __bool(keysOnly),\n\
        filter);\n\
}\n\
\n"

//==============================================================================
//
// INDICATION_PROVIDER_STUBS_CPP
//
//==============================================================================

#define INDICATION_PROVIDER_STUBS_CPP COMMON_PROVIDER_STUBS_CPP "\
MI_EXTERN_C void MI_CALL <ALIAS>_EnableIndications(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* indicationsContext,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
\n\
    cxxSelf->SetIndicationContext(indicationsContext);\n\
    cxxSelf->EnableIndications();\n\
}\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_DisableIndications(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* indicationsContext,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
\n\
    cxxSelf->DisableIndications();\n\
    cxxSelf->SetIndicationContext(0);\n\
\n\
    MI_Context_PostResult(indicationsContext, MI_RESULT_OK);\n\
}\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_Subscribe(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const MI_Filter* filter,\n\
    const MI_Char* bookmark,\n\
    MI_Uint64  subscriptionID,\n\
    void** subscriptionSelf)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    Context  cxxContext(context);\n\
\n\
    cxxSelf->Subscribe(\n\
        cxxContext,\n\
        nameSpace,\n\
        filter,\n\
        bookmark,\n\
        subscriptionID,\n\
        subscriptionSelf);\n\
}\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_Unsubscribe(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    MI_Uint64  subscriptionID,\n\
    void* subscriptionSelf)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    Context  cxxContext(context);\n\
\n\
    cxxSelf->Unsubscribe(\n\
        cxxContext,\n\
        nameSpace,\n\
        subscriptionID,\n\
        subscriptionSelf);\n\
}\n\
\n"

//==============================================================================
//
// EXTRINSIC_METHOD_STUB_CPP
//
//==============================================================================

#define EXTRINSIC_METHOD_STUB_CPP "\
MI_EXTERN_C void MI_CALL <ALIAS>_Invoke_<METHOD>(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const MI_Char* methodName,\n\
    const <ALIAS>* instanceName,\n\
    const <ALIAS>_<METHOD>* in)\n\
{\n\
    <ALIAS>_Class_Provider* cxxSelf =((<ALIAS>_Class_Provider*)self);\n\
    <ALIAS>_Class instance(instanceName, false);\n\
    Context  cxxContext(context);\n\
    <ALIAS>_<METHOD>_Class param(in, false);\n\
\n\
    cxxSelf->Invoke_<METHOD>(cxxContext, nameSpace, instance, param);\n\
}\n\
\n"

#endif /* _migen_cxxstubs_t_h */
