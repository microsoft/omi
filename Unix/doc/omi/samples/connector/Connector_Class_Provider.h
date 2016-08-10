/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#ifndef _Connector_Class_Provider_h
#define _Connector_Class_Provider_h

#include "Connector.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** Connector provider class declaration
**
**==============================================================================
*/

class Connector_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    Connector_Class_Provider(
        Module* module);

    ~Connector_Class_Provider();

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
        const Connector_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const Connector_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const Connector_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const Connector_Class& instance);

    void AssociatorInstancesLeft(
        Context& context,
        const String& nameSpace,
        const Widget_Class& instanceName, 
        const String& resultClass,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void AssociatorInstancesRight(
        Context& context,
        const String& nameSpace,
        const Gadget_Class& instanceName, 
        const String& resultClass,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void ReferenceInstancesLeft(
        Context& context,
        const String& nameSpace,
        const Widget_Class& instanceName, 
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void ReferenceInstancesRight(
        Context& context,
        const String& nameSpace,
        const Gadget_Class& instanceName, 
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Connector_Class_Provider_h */

