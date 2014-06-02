/* @migen@ */
#ifndef _Gadget_Class_Provider_h
#define _Gadget_Class_Provider_h

#include "Gadget.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** Gadget provider class declaration
**
**==============================================================================
*/

class Gadget_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    Gadget_Class_Provider(
        Module* module);

    ~Gadget_Class_Provider();

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
        const Gadget_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const Gadget_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const Gadget_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const Gadget_Class& instance);

    void Invoke_ChangeState(
        Context& context,
        const String& nameSpace,
        const Gadget_Class& instanceName,
        const Gadget_ChangeState_Class& in);

    void Invoke_Foo(
        Context& context,
        const String& nameSpace,
        const Gadget_Class& instanceName,
        const Gadget_Foo_Class& in);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Gadget_Class_Provider_h */

