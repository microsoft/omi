/* @migen@ */
#ifndef _Main_Class_Provider_h
#define _Main_Class_Provider_h

#include "Main.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** Main provider class declaration
**
**==============================================================================
*/

class Main_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    Main_Class_Provider(
        Module* module);

    ~Main_Class_Provider();

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
        const Main_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const Main_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const Main_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const Main_Class& instance);

    void Invoke_ChangeState(
        Context& context,
        const String& nameSpace,
        const Main_Class& instanceName,
        const Main_ChangeState_Class& in);

    void Invoke_HelloWorld(
        Context& context,
        const String& nameSpace,
        const Main_Class& instanceName,
        const Main_HelloWorld_Class& in);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Main_Class_Provider_h */
