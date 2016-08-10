/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#ifndef _X_Number1000001_Class_Provider_h
#define _X_Number1000001_Class_Provider_h

#include "X_Number1000001.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** X_Number1000001 provider class declaration
**
**==============================================================================
*/

class X_Number1000001_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;
    Module* GetModule( void ) { return m_Module; };

public:
    X_Number1000001_Class_Provider(
        Module* module);

    ~X_Number1000001_Class_Provider();

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
        const X_Number1000001_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const X_Number1000001_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const X_Number1000001_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const X_Number1000001_Class& instance);

    void Invoke_SpellMagnitude(
        Context& context,
        const String& nameSpace,
        const X_Number1000001_Class& instance,
        const X_Number1000001_SpellMagnitude_Class& in);

    void Invoke_TestEmbedded(
        Context& context,
        const String& nameSpace,
        const X_Number1000001_Class& instance,
        const X_Number1000001_TestEmbedded_Class& in);

    void Invoke_Method1(
        Context& context,
        const String& nameSpace,
        const X_Number1000001_Class& instance,
        const X_Number1000001_Method1_Class& in);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_Number1000001_Class_Provider_h */

