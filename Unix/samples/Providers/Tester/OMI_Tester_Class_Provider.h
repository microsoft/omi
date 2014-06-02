/* @migen@ */
#ifndef _OMI_Tester_Class_Provider_h
#define _OMI_Tester_Class_Provider_h

#include "OMI_Tester.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** OMI_Tester provider class declaration
**
**==============================================================================
*/

class OMI_Tester_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    OMI_Tester_Class_Provider(
        Module* module);

    ~OMI_Tester_Class_Provider();

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
        const OMI_Tester_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const OMI_Tester_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const OMI_Tester_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const OMI_Tester_Class& instance);

    void Invoke_Func1(
        Context& context,
        const String& nameSpace,
        const OMI_Tester_Class& instanceName,
        const OMI_Tester_Func1_Class& in);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _OMI_Tester_Class_Provider_h */

