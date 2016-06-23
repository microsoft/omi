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
#ifndef _MSFT_Alert_Class_Provider_h
#define _MSFT_Alert_Class_Provider_h

#include "MSFT_Alert.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** MSFT_Alert provider class declaration
**
**==============================================================================
*/

class MSFT_Alert_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;
    Module* GetModule( void ) { return m_Module; };
    MI_Context* m_IndicationsContext;

public:
    MSFT_Alert_Class_Provider(
        Module* module);

    ~MSFT_Alert_Class_Provider();

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

#endif /* _MSFT_Alert_Class_Provider_h */

