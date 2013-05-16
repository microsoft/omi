/* @migen@ */
#ifndef _Test_Class_Provider_h
#define _Test_Class_Provider_h

#include "Test.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** Test provider class declaration
**
**==============================================================================
*/

class Test_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    Test_Class_Provider(
        Module* module);

    ~Test_Class_Provider();

    void Load(
        Context& context);

    void Unload(
        Context& context);

    void EnumerateInstances(
        Context& context,
        const String& nameSpace,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void GetInstance(
        Context& context,
        const String& nameSpace,
        const Test_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const Test_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const Test_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const Test_Class& instance);

    void AssociatorInstancesId(
        Context& context,
        const String& nameSpace,
        const Identifier_Class& instanceName, 
        const String& resultClass,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void AssociatorInstancesRf(
        Context& context,
        const String& nameSpace,
        const Reference_Class& instanceName, 
        const String& resultClass,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void ReferenceInstancesId(
        Context& context,
        const String& nameSpace,
        const Identifier_Class& instanceName, 
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void ReferenceInstancesRf(
        Context& context,
        const String& nameSpace,
        const Reference_Class& instanceName, 
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void Invoke_StaticFun(
        Context& context,
        const String& nameSpace,
        const Test_Class& instanceName,
        const Test_StaticFun_Class& in);

    void Invoke_InstanceFun(
        Context& context,
        const String& nameSpace,
        const Test_Class& instanceName,
        const Test_InstanceFun_Class& in);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Test_Class_Provider_h */

