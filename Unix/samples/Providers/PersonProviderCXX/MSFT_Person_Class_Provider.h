/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#ifndef _MSFT_Person_Class_Provider_h
#define _MSFT_Person_Class_Provider_h

#include "MSFT_Person.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** MSFT_Person provider class declaration
**
**==============================================================================
*/

class MSFT_Person_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;
    Module* GetModule( void ) { return m_Module; };

public:
    MSFT_Person_Class_Provider(
        Module* module);

    ~MSFT_Person_Class_Provider();

    void EnumerateInstances(
        Context&  context,
        const String& nameSpace,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void GetInstance(
        Context&  context,
        const String& nameSpace,
        const MSFT_Person_Class& instance_ref,
        const PropertySet& propertySet);

    void CreateInstance(
        Context&  context,
        const String& nameSpace,
        const MSFT_Person_Class& new_instance);

    void ModifyInstance(
        Context&  context,
        const String& nameSpace,
        const MSFT_Person_Class& new_instance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context&  context,
        const String& nameSpace,
        const MSFT_Person_Class& instance_ref);

    void Invoke_Add(
        Context&  context,
        const String& nameSpace,
        const MSFT_Person_Class& instance,
        const MSFT_Person_Add_Class& in_param );

    void Invoke_TestAllTypes(
        Context&  context,
        const String& nameSpace,
        const MSFT_Person_Class& instance,
        const MSFT_Person_TestAllTypes_Class& in_param );

    void Invoke_StreamParams(
        Context&  context,
        const String& nameSpace,
        const MSFT_Person_Class& instance,
        const MSFT_Person_StreamParams_Class& in_param );

    void Load(
        Context& context);

    void Unload(
        Context& context);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */

private:
    MSFT_Person_Class _data[10];
    const size_t _SIZE;
    size_t _size;
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MSFT_Person_Class_Provider_h */

