/* @migen@ */
#ifndef _XYZ_Assoc2_Class_Provider_h
#define _XYZ_Assoc2_Class_Provider_h

#include "XYZ_Assoc2.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** XYZ_Assoc2 provider class declaration
**
**==============================================================================
*/

class XYZ_Assoc2_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    XYZ_Assoc2_Class_Provider(
        Module* module);

    ~XYZ_Assoc2_Class_Provider();

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
        const XYZ_Assoc2_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const XYZ_Assoc2_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const XYZ_Assoc2_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const XYZ_Assoc2_Class& instance);

    void AssociatorInstancesLeft(
        Context& context,
        const String& nameSpace,
        const XYZ_Widget2_Class& instanceName, 
        const String& resultClass,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void AssociatorInstancesRight(
        Context& context,
        const String& nameSpace,
        const XYZ_Gadget2_Class& instanceName, 
        const String& resultClass,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void ReferenceInstancesLeft(
        Context& context,
        const String& nameSpace,
        const XYZ_Widget2_Class& instanceName, 
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void ReferenceInstancesRight(
        Context& context,
        const String& nameSpace,
        const XYZ_Gadget2_Class& instanceName, 
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _XYZ_Assoc2_Class_Provider_h */

