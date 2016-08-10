/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#ifndef _TestEmbeddedOperations_Class_Provider_h
#define _TestEmbeddedOperations_Class_Provider_h

#include "TestEmbeddedOperations.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** TestEmbeddedOperations provider class declaration
**
**==============================================================================
*/

class TestEmbeddedOperations_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;
    Module* GetModule( void ) { return m_Module; };

public:
    TestEmbeddedOperations_Class_Provider(
        Module* module);

    ~TestEmbeddedOperations_Class_Provider();

    void EnumerateInstances(
        Context&  context,
        const String& nameSpace,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void GetInstance(
        Context&  context,
        const String& nameSpace,
        const TestEmbeddedOperations_Class& instance_ref,
        const PropertySet& propertySet);

    void CreateInstance(
        Context&  context,
        const String& nameSpace,
        const TestEmbeddedOperations_Class& new_instance);

    void ModifyInstance(
        Context&  context,
        const String& nameSpace,
        const TestEmbeddedOperations_Class& new_instance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context&  context,
        const String& nameSpace,
        const TestEmbeddedOperations_Class& instance_ref);

    void Invoke_TestEmbedded(
        Context&  context,
        const String& nameSpace,
        const TestEmbeddedOperations_Class& instance,
        const TestEmbeddedOperations_TestEmbedded_Class& in_param );

    void Invoke_TestEmbeddedInstanceReturnKey20100609(
        Context&  context,
        const String& nameSpace,
        const TestEmbeddedOperations_Class& instance,
        const TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class& in_param );

    void Invoke_TestEmbeddedObjectReturnKey20100609(
        Context&  context,
        const String& nameSpace,
        const TestEmbeddedOperations_Class& instance,
        const TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class& in_param );

    void Load(
        Context& context);

    void Unload(
        Context& context);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _TestEmbeddedOperations_Class_Provider_h */

