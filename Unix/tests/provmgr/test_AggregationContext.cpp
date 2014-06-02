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
