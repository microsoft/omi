/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#ifndef _Order_Class_Provider_h
#define _Order_Class_Provider_h

#include "Order.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** Order provider class declaration
**
**==============================================================================
*/

class Order_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;
    Module* GetModule( void ) { return m_Module; };
    MI_Context* m_IndicationsContext;

public:
    Order_Class_Provider(
        Module* module);

    ~Order_Class_Provider();

    void Load(
        Context& context);

    void Unload(
        Context& context);

    void Subscribe(
        Context& context,
        const String& nameSpace,
        const MI_Filter* filter,
        const String& bookmark,
        MI_Uint64  subscriptionID,
        void** subscriptionSelf);

    void Unsubscribe(
        Context& context,
        const String& nameSpace,
        MI_Uint64  subscriptionID,
        void* subscriptionSelf);

    void EnableIndications();

    void DisableIndications();

    void SetIndicationContext(
        MI_Context* indicationsContext)
    {
        m_IndicationsContext = indicationsContext;
    }

    MI_Result Post(
        const Instance& indication,
        MI_Uint32 subscriptionIDCount = 0,
        const String& bookmark = String())
    {
        if (m_IndicationsContext)
        {
            Context(m_IndicationsContext).Post(
                indication,
                subscriptionIDCount,
                bookmark);
            return MI_RESULT_OK;
        }
        return MI_RESULT_FAILED;
    }

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Order_Class_Provider_h */

