/* @migen@ */
#ifndef _AllTypes_Class_Provider_h
#define _AllTypes_Class_Provider_h

#include "AllTypes.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** AllTypes provider class declaration
**
**==============================================================================
*/

class AllTypes_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    AllTypes_Class_Provider(
        Module* module);

    ~AllTypes_Class_Provider();

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
        const AllTypes_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const AllTypes_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const AllTypes_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const AllTypes_Class& instance);

    void AssociatorInstancesrefMain(
        Context& context,
        const String& nameSpace,
        const Main_Class& instanceName, 
        const String& resultClass,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void AssociatorInstancesrefRef(
        Context& context,
        const String& nameSpace,
        const Reference_Class& instanceName, 
        const String& resultClass,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void ReferenceInstancesrefMain(
        Context& context,
        const String& nameSpace,
        const Main_Class& instanceName, 
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void ReferenceInstancesrefRef(
        Context& context,
        const String& nameSpace,
        const Reference_Class& instanceName, 
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _AllTypes_Class_Provider_h */

