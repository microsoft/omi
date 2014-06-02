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
#include <indication/indimgr/listener.h>
#include <pal/strings.h>

using namespace std;

NitsSetup(TestListenerSetup)
NitsEndSetup

NitsCleanup(TestListenerSetup)
NitsEndCleanup

// UT_ASSERT_FAILED_MSG("");

NitsTestWithSetup(TestCreateListener, TestListenerSetup)
{
    Listener* listener = Listener_New(LISTENER_TEMP);
    UT_ASSERT( NULL != listener);
    if (listener)
    {
        UT_ASSERT( Listener_GetRefcount(listener) == 1 );

        // identifier gets generated upon adding to indication manager cache
        UT_ASSERT( NULL == listener->base.identifier );

        UT_ASSERT( listener->PersistenceType == LISTENER_TEMP );

        Listener_Release(listener);
    }

    listener = Listener_New(LISTENER_PERMANENT);
    UT_ASSERT( NULL != listener );
    if (listener)
    {
        UT_ASSERT( Listener_GetRefcount(listener) == 1 );

        // identifier gets generated upon adding to indication manager cache
        UT_ASSERT( NULL == listener->base.identifier );

        Listener_AddRef(listener);
        UT_ASSERT( Listener_GetRefcount(listener) == 2);
        Listener_AddRef(listener);
        UT_ASSERT( Listener_GetRefcount(listener) == 3);
        Listener_AddRef(listener);
        UT_ASSERT( Listener_GetRefcount(listener) == 4);
        Listener_Release(listener);
        Listener_Release(listener);
        Listener_Release(listener);

        Listener_Release(listener);
    }
}
NitsEndTest



