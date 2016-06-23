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
// cxxprovider.h - template for generating C++ provider header and source.
//
//==============================================================================

#ifndef _migen_cxxprovider_t_h
#define _migen_cxxprovider_t_h

//==============================================================================
//
// COMMON_PROVIDER_LOAD_UNLOAD_DECLARATION
//
//==============================================================================

#define COMMON_PROVIDER_LOAD_UNLOAD_DECLARATION   "\
    void Load(\n\
        Context& context);\n\
\n\
    void Unload(\n\
        Context& context);\n\
\n"

//==============================================================================
//
// COMMON_PROVIDER_CLASS_DECLARATION
//
//==============================================================================

#define COMMON_PROVIDER_CLASS_DECLARATION   "\
class <ALIAS>_Class_Provider\n\
{\n\
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */\n\
private:\n\
    Module* m_Module;\n\
<DATA_MEMBERS>\
\n\
public:\n\
    <ALIAS>_Class_Provider(\n\
        Module* module);\n\
\n\
    ~<ALIAS>_Class_Provider();\n\
\n\
    inline Module* getModule()\n\
    {\n\
        return m_Module;\n\
    }\n\
\n"   COMMON_PROVIDER_LOAD_UNLOAD_DECLARATION

//==============================================================================
//
// COMMON_PROVIDER_CLASS_DECLARATION_END
//
//==============================================================================

#define COMMON_PROVIDER_CLASS_DECLARATION_END \
    "/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */"

//==============================================================================
//
// INSTANCE_PROVIDER_CLASS_DECL
//
//==============================================================================

#define INSTANCE_PROVIDER_CLASS_DECLARATION COMMON_PROVIDER_CLASS_DECLARATION "\
    void EnumerateInstances(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const PropertySet& propertySet,\n\
        bool keysOnly,\n\
        const MI_Filter* filter);\n\
\n\
    void GetInstance(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const <ALIAS>_Class& instance,\n\
        const PropertySet& propertySet);\n\
\n\
    void CreateInstance(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const <ALIAS>_Class& newInstance);\n\
\n\
    void ModifyInstance(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const <ALIAS>_Class& modifiedInstance,\n\
        const PropertySet& propertySet);\n\
\n\
    void DeleteInstance(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const <ALIAS>_Class& instance);\n\
\n"

//==============================================================================
//
// CPP: ASSOCIATION_PROVIDER_CLASS_DECLARATION
//
//==============================================================================

#define ASSOCIATION_PROVIDER_CLASS_DECLARATION INSTANCE_PROVIDER_CLASS_DECLARATION "\
    void AssociatorInstances(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const MI_Instance* instanceName, \n\
        const String& resultClass,\n\
        const String& role,\n\
        const String& resultRole,\n\
        const PropertySet& propertySet,\n\
        bool keysOnly,\n\
        const MI_Filter* filter);\n\
\n\
    void ReferenceInstances(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const MI_Instance* instanceName, \n\
        const String& role,\n\
        const PropertySet& propertySet,\n\
        bool keysOnly,\n\
        const MI_Filter* filter);\n\
\n"

#define ASSOCIATION_PROVIDER_CLASS_DECLARATION_ROLES INSTANCE_PROVIDER_CLASS_DECLARATION "\
    void AssociatorInstances<ROLE1>(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const <ALIAS1>_Class& instanceName, \n\
        const String& resultClass,\n\
        const PropertySet& propertySet,\n\
        bool keysOnly,\n\
        const MI_Filter* filter);\n\
\n\
    void AssociatorInstances<ROLE2>(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const <ALIAS2>_Class& instanceName, \n\
        const String& resultClass,\n\
        const PropertySet& propertySet,\n\
        bool keysOnly,\n\
        const MI_Filter* filter);\n\
\n\
    void ReferenceInstances<ROLE1>(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const <ALIAS1>_Class& instanceName, \n\
        const PropertySet& propertySet,\n\
        bool keysOnly,\n\
        const MI_Filter* filter);\n\
\n\
    void ReferenceInstances<ROLE2>(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const <ALIAS2>_Class& instanceName, \n\
        const PropertySet& propertySet,\n\
        bool keysOnly,\n\
        const MI_Filter* filter);\n\
\n"

//==============================================================================
//
// INDICATION_PROVIDER_CLASS_DECLARATION
//
//==============================================================================

#define INDICATION_PROVIDER_CLASS_DECLARATION COMMON_PROVIDER_CLASS_DECLARATION "\
    void Subscribe(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const MI_Filter* filter,\n\
        const String& bookmark,\n\
        MI_Uint64  subscriptionID,\n\
        void** subscriptionSelf);\n\
\n\
    void Unsubscribe(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        MI_Uint64  subscriptionID,\n\
        void* subscriptionSelf);\n\
\n\
    void EnableIndications();\n\
\n\
    void DisableIndications();\n\
\n\
    void SetIndicationContext(\n\
        MI_Context* indicationsContext)\n\
    {\n\
        m_IndicationsContext = indicationsContext;\n\
    }\n\
\n\
    MI_Result Post(\n\
        const Instance& indication,\n\
        MI_Uint32 subscriptionIDCount = 0,\n\
        const String& bookmark = String())\n\
    {\n\
        if (m_IndicationsContext)\n\
        {\n\
            Context(m_IndicationsContext).Post(\n\
                indication,\n\
                subscriptionIDCount,\n\
                bookmark);\n\
            return MI_RESULT_OK;\n\
        }\n\
        return MI_RESULT_FAILED;\n\
    }\n\
\n"

//==============================================================================
//
// EXTRINSIC_METHOD_PROVIDER_CLASS_DECLARATION
//
//==============================================================================

#define EXTRINSIC_METHOD_PROVIDER_CLASS_DECLARATION     "\
    void Invoke_<METHOD>(\n\
        Context& context,\n\
        const String& nameSpace,\n\
        const <ALIAS>_Class& instanceName,\n\
        const <ALIAS>_<METHOD>_Class& in);\n\
\n"

//==============================================================================
//
// COMMON_PROVIDER_CLASS_LOAD_UNLOAD_CPP
//
//==============================================================================

#define COMMON_PROVIDER_CLASS_LOAD_UNLOAD_CPP  "\
void <ALIAS>_Class_Provider::Load(\n\
        Context& context)\n\
{\n\
    context.Post(MI_RESULT_OK);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::Unload(\n\
        Context& context)\n\
{\n\
    context.Post(MI_RESULT_OK);\n\
}\n\
\n"

//==============================================================================
//
// INSTANCE_PROVIDER_CLASS_STUBS_CPP
//
//==============================================================================

#define INSTANCE_PROVIDER_CLASS_STUBS_CPP  "\
<ALIAS>_Class_Provider::<ALIAS>_Class_Provider(\n\
    Module* module) :\n\
    m_Module(module)\n\
{\n\
}\n\
\n\
<ALIAS>_Class_Provider::~<ALIAS>_Class_Provider()\n\
{\n\
}\n\
\n\
void <ALIAS>_Class_Provider::Load(\n\
        Context& context)\n\
{\n\
    context.Post(MI_RESULT_OK);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::Unload(\n\
        Context& context)\n\
{\n\
    context.Post(MI_RESULT_OK);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::EnumerateInstances(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const PropertySet& propertySet,\n\
    bool keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::GetInstance(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const <ALIAS>_Class& instanceName,\n\
    const PropertySet& propertySet)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::CreateInstance(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const <ALIAS>_Class& newInstance)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::ModifyInstance(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const <ALIAS>_Class& modifiedInstance,\n\
    const PropertySet& propertySet)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::DeleteInstance(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const <ALIAS>_Class& instanceName)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n"

//==============================================================================
//
// CPP: ASSOCIATION_PROVIDER_CLASS_STUBS_CPP
//
//==============================================================================

#define ASSOCIATION_PROVIDER_CLASS_STUBS_CPP INSTANCE_PROVIDER_CLASS_STUBS_CPP "\
void <ALIAS>_Class_Provider::AssociatorInstances(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const MI_Instance* instanceName, \n\
    const String& resultClass,\n\
    const String& role,\n\
    const String& resultRole,\n\
    const PropertySet& propertySet,\n\
    bool keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::ReferenceInstances(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const MI_Instance* instanceName, \n\
    const String& role,\n\
    const PropertySet& propertySet,\n\
    bool keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n"

#define ASSOCIATION_PROVIDER_CLASS_STUBS_CPP_ROLES INSTANCE_PROVIDER_CLASS_STUBS_CPP "\
void <ALIAS>_Class_Provider::AssociatorInstances<ROLE1>(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const <ALIAS1>_Class& instanceName, \n\
    const String& resultClass,\n\
    const PropertySet& propertySet,\n\
    bool keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::AssociatorInstances<ROLE2>(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const <ALIAS2>_Class& instanceName, \n\
    const String& resultClass,\n\
    const PropertySet& propertySet,\n\
    bool keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::ReferenceInstances<ROLE1>(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const <ALIAS1>_Class& instanceName, \n\
    const PropertySet& propertySet,\n\
    bool keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::ReferenceInstances<ROLE2>(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const <ALIAS2>_Class& instanceName, \n\
    const PropertySet& propertySet,\n\
    bool keysOnly,\n\
    const MI_Filter* filter)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n"

//==============================================================================
//
// INDICATION_PROVIDER_CLASS_STUBS_CPP
//
//==============================================================================

#define INDICATION_PROVIDER_CLASS_STUBS_CPP  "\
<ALIAS>_Class_Provider::<ALIAS>_Class_Provider(\n\
    Module* module) :\n\
    m_Module(module),\n\
    m_IndicationsContext(0)\n\
{\n\
}\n\
\n\
<ALIAS>_Class_Provider::~<ALIAS>_Class_Provider()\n\
{\n\
}\n\
\n\
void <ALIAS>_Class_Provider::Load(\n\
        Context& context)\n\
{\n\
    context.Post(MI_RESULT_OK);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::Unload(\n\
        Context& context)\n\
{\n\
    context.Post(MI_RESULT_OK);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::EnableIndications()\n\
{\n\
}\n\
\n\
void <ALIAS>_Class_Provider::DisableIndications()\n\
{\n\
}\n\
\n\
void <ALIAS>_Class_Provider::Subscribe(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const MI_Filter* filter,\n\
    const String& bookmark,\n\
    MI_Uint64  subscriptionID,\n\
    void** subscriptionSelf)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n\
void <ALIAS>_Class_Provider::Unsubscribe(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    MI_Uint64  subscriptionID,\n\
    void* subscriptionSelf)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n"

//==============================================================================
//
// EXTRINSIC_METHOD_CLASS_STUB_CPP
//
//==============================================================================

#define EXTRINSIC_METHOD_CLASS_STUB_CPP     "\
void <ALIAS>_Class_Provider::Invoke_<METHOD>(\n\
    Context& context,\n\
    const String& nameSpace,\n\
    const <ALIAS>_Class& instanceName,\n\
    const <ALIAS>_<METHOD>_Class& in)\n\
{\n\
    context.Post(MI_RESULT_NOT_SUPPORTED);\n\
}\n\
\n"

#endif /* _migen_cxxprovider_t_h */
