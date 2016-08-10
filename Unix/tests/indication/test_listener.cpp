/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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



