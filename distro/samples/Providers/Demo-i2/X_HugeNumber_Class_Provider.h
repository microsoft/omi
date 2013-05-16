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
#ifndef _X_HugeNumber_Class_Provider_h
#define _X_HugeNumber_Class_Provider_h

#include "X_HugeNumber.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** X_HugeNumber provider class declaration
**
**==============================================================================
*/

class X_HugeNumber_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    X_HugeNumber_Class_Provider(
        Module* module);

    ~X_HugeNumber_Class_Provider();

    void EnumerateInstances(
        Context&  context,
        const String& nameSpace,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void GetInstance(
        Context&  context,
        const String& nameSpace,
        const X_HugeNumber_Class& instance_ref,
        const PropertySet& propertySet);

    void CreateInstance(
        Context&  context,
        const String& nameSpace,
        const X_HugeNumber_Class& new_instance);

    void ModifyInstance(
        Context&  context,
        const String& nameSpace,
        const X_HugeNumber_Class& new_instance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context&  context,
        const String& nameSpace,
        const X_HugeNumber_Class& instance_ref);

    void Invoke_SpellMagnitude(
        Context&  context,
        const String& nameSpace,
        const X_HugeNumber_Class& instance,
        const X_HugeNumber_SpellMagnitude_Class& in_param );

    void Invoke_TestEmbedded(
        Context&  context,
        const String& nameSpace,
        const X_HugeNumber_Class& instance,
        const X_HugeNumber_TestEmbedded_Class& in_param );

    void Load(
        Context& context);

    void Unload(
        Context& context);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_HugeNumber_Class_Provider_h */

