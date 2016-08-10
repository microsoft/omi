/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <ut/ut.h>
#include <provmgr/SubscriptionContext.h>
#include <provmgr/AggregationContext.h>
#include <provmgr/provmgr.h>
#include <provmgr/SubMgr.h>

using namespace std;

NitsTest(TestAggregationContext_InitClose)

    AggregationContext context;
    Provider provider;
    SubscriptionManager mgr;

    memset( &context, 0, sizeof(AggregationContext) );
    memset( &mgr, 0, sizeof(SubscriptionManager) );
    memset( &provider, 0, sizeof(provider) );
    provider.refusedUnload = MI_TRUE;

    NitsCompare( MI_RESULT_OK, AggrContext_Init(&context, &provider, &mgr), PAL_T("AggrContext_Init failed"));
    NitsCompare( CTX_TYPE_IND_AGGREGATION, context.baseCtx.ctxType, PAL_T("AggrContext_Init failed"));
    NitsAssert( &mgr == AggrContext_GetManager( &context ), PAL_T("AggrContext_Init failed"));

    AggrContext_Close(&context);
    NitsCompare( 0xFFFFFFFF, context.baseCtx.magic, PAL_T("aggregation context has unexpected magic number") );

NitsEndTest

NitsTest (TestAggregationContext_NewAndDelete)

    AggregationContext* context;
    SubscriptionManager mgr;
    Provider provider;

    memset( &mgr, 0, sizeof(SubscriptionManager) );
    memset( &provider, 0, sizeof(provider) );
    provider.refusedUnload = MI_TRUE;

    context = AggrContext_New();
    NitsAssertOrReturn(context, PAL_T("AggrContext_New failed"));

    NitsCompare( MI_RESULT_OK, AggrContext_Init( context, &provider, &mgr ), PAL_T("AggrContext_Init failed") );
    AggrContext_Delete( context );

NitsEndTest
