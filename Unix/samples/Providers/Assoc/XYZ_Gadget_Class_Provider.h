/* @migen@ */
#ifndef _XYZ_Gadget_Class_Provider_h
#define _XYZ_Gadget_Class_Provider_h

#include "XYZ_Gadget.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** XYZ_Gadget provider class declaration
**
**==============================================================================
*/

class XYZ_Gadget_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    XYZ_Gadget_Class_Provider(
        Module* module);

    ~XYZ_Gadget_Class_Provider();

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
        const XYZ_Gadget_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const XYZ_Gadget_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const XYZ_Gadget_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const XYZ_Gadget_Class& instance);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _XYZ_Gadget_Class_Provider_h */

