/* @migen@ */
#ifndef _Derived_Class_Provider_h
#define _Derived_Class_Provider_h

#include "Derived.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** Derived provider class declaration
**
**==============================================================================
*/

class Derived_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    Derived_Class_Provider(
        Module* module);

    ~Derived_Class_Provider();

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
        const Derived_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const Derived_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const Derived_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const Derived_Class& instance);

    void Invoke_Foo(
        Context& context,
        const String& nameSpace,
        const Derived_Class& instanceName,
        const Derived_Foo_Class& in);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Derived_Class_Provider_h */

