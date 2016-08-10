//==============================================================================
//
// cprotypes.h - define source code tempalte for provider function prototypes.
//
//==============================================================================
#ifndef _migen_cprototypes_t_h
#define _migen_cprototypes_t_h

//==============================================================================
//
// COMMON_PROVIDER_PROTOTYPES
//
//==============================================================================

#define COMMON_PROVIDER_PROTOTYPES "\
MI_EXTERN_C void MI_CALL <ALIAS>_Load(\n\
    <ALIAS>_Self** self,\n\
    MI_Module_Self* selfModule,\n\
    MI_Context* context);\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_Unload(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context);\n\
\n"

//==============================================================================
//
// SPECIAL PATCH support for class-level Load function
//
//==============================================================================

#define OLD_PROVIDER_LOAD_PROTOTYPES "\
void MI_CALL <ALIAS>_Load(\n\
    <ALIAS>_Self** self,\n\
    MI_Context* context)"

#define NEW_PROVIDER_LOAD_PROTOTYPES "\
void MI_CALL <ALIAS>_Load(\n\
    <ALIAS>_Self** self,\n\
    MI_Module_Self* selfModule,\n\
    MI_Context* context)"

//==============================================================================
//
// INSTANCE_PROVIDER_PROTOTYPES
//
//==============================================================================

#define INSTANCE_PROVIDER_PROTOTYPES COMMON_PROVIDER_PROTOTYPES "\
MI_EXTERN_C void MI_CALL <ALIAS>_EnumerateInstances(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter);\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_GetInstance(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS>* instanceName,\n\
    const MI_PropertySet* propertySet);\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_CreateInstance(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS>* newInstance);\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_ModifyInstance(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS>* modifiedInstance,\n\
    const MI_PropertySet* propertySet);\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_DeleteInstance(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS>* instanceName);\n\
\n"

//==============================================================================
//
// ASSOCIATION_PROVIDER_PROTOTYPES
//
//==============================================================================

#define ASSOCIATION_PROVIDER_PROTOTYPES INSTANCE_PROVIDER_PROTOTYPES "\
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
    const MI_Filter* filter);\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_ReferenceInstances(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const MI_Instance* instanceName,\n\
    const MI_Char* role,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter);\n\
\n"

#define ROLE_PROVIDER_PROTOTYPES INSTANCE_PROVIDER_PROTOTYPES "\
MI_EXTERN_C void MI_CALL <ALIAS>_AssociatorInstances<ROLE1>(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS1>* instanceName,\n\
    const MI_Char* resultClass,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter);\n\
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
    const MI_Filter* filter);\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_ReferenceInstances<ROLE1>(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS1>* instanceName,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter);\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_ReferenceInstances<ROLE2>(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const <ALIAS2>* instanceName,\n\
    const MI_PropertySet* propertySet,\n\
    MI_Boolean keysOnly,\n\
    const MI_Filter* filter);\n\
\n"

//==============================================================================
//
// INDICATION_PROVIDER_PROTOTYPES
//
//==============================================================================

#define INDICATION_PROVIDER_PROTOTYPES COMMON_PROVIDER_PROTOTYPES "\
MI_EXTERN_C void MI_CALL <ALIAS>_EnableIndications(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* indicationsContext,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className);\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_DisableIndications(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* indicationsContext,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className);\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_Subscribe(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const MI_Filter* filter,\n\
    const MI_Char* bookmark,\n\
    MI_Uint64  subscriptionID,\n\
    void** subscriptionSelf);\n\
\n\
MI_EXTERN_C void MI_CALL <ALIAS>_Unsubscribe(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    MI_Uint64  subscriptionID,\n\
    void* subscriptionSelf);\n\
\n"

//==============================================================================
//
// EXTRINSIC_METHOD_PROTOTYPE
//
//==============================================================================

#define EXTRINSIC_METHOD_PROTOTYPE "\
MI_EXTERN_C void MI_CALL <ALIAS>_Invoke_<METHOD>(\n\
    <ALIAS>_Self* self,\n\
    MI_Context* context,\n\
    const MI_Char* nameSpace,\n\
    const MI_Char* className,\n\
    const MI_Char* methodName,\n\
    const <ALIAS>* instanceName,\n\
    const <ALIAS>_<METHOD>* in);\n\
\n"

#endif /* _migen_cprototypes_t_h */
