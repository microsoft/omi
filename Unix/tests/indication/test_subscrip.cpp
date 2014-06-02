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

#include <vector>
#include <algorithm>
#include <ut/ut.h>
#include <indication/common/indicommon.h>
#include <indication/indimgr/subscrip.h>
#include <pal/strings.h>

using namespace std;

Filter* g_tempfilter;
Listener* g_templistener;


NitsSetup(TestSubscripSetup)
{
    g_templistener = Listener_New(LISTENER_TEMP);
    UT_ASSERT( NULL != g_templistener );
    const MI_Char* query = MI_T("select * from CIM_Indication");
    g_tempfilter = Filter_New(query, QUERY_LANGUAGE_WQL, NULL);
    UT_ASSERT( NULL != g_tempfilter );
}
NitsEndSetup

NitsCleanup(TestSubscripSetup)
{
    if (g_tempfilter)
    {
        Filter_Release(g_tempfilter);
        g_tempfilter = NULL;
    }
    if (g_templistener)
    {
        Listener_Release(g_templistener);
        g_templistener = NULL;
    }
}
NitsEndCleanup

NitsTestWithSetup(TestCreateSubscription, TestSubscripSetup)
{
    int refFilter = Filter_GetRefcount(g_tempfilter);
    int refListener = Listener_GetRefcount(g_templistener);
    Subscription* sub = Subscription_New((FilterBase*)g_tempfilter, g_templistener);
    UT_ASSERT(NULL != sub);
    if (sub)
    {
        int refFilter2 = Filter_GetRefcount(g_tempfilter);
        int refListener2 = Listener_GetRefcount(g_templistener);
        UT_ASSERT( refFilter2 == (refFilter+1) );
        UT_ASSERT( refListener2 == (refListener+1) );

        UT_ASSERT( Subscription_GetRefcount(sub) == 1 );

        // identifier gets generated upon adding to indication manager cache
        UT_ASSERT( NULL == sub->base.identifier );

        Subscription_AddRef(sub);
        UT_ASSERT( Subscription_GetRefcount(sub) == 2);
        Subscription_AddRef(sub);
        UT_ASSERT( Subscription_GetRefcount(sub) == 3);
        Subscription_AddRef(sub);
        UT_ASSERT( Subscription_GetRefcount(sub) == 4);
        Subscription_Release(sub);
        Subscription_Release(sub);
        Subscription_Release(sub);

        Subscription_Release(sub);

        refFilter2 = Filter_GetRefcount(g_tempfilter);
        refListener2 = Listener_GetRefcount(g_templistener);

        UT_ASSERT( refFilter2 == refFilter );
        UT_ASSERT( refListener2 == refListener );
    }
}
NitsEndTest




