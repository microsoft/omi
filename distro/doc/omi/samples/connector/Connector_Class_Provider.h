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

