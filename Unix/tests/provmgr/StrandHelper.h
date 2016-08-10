/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _provmgr_strand_helper_h
#define _provmgr_strand_helper_h
#include <ut/ut.h>
#include <pal/palcommon.h>
#include <pal/strings.h>
#include <provmgr/SubscriptionContext.h>
#include <provmgr/AggregationContext.h>
#include <provmgr/SubMgr.h>
#include <base/Strand.h>

PAL_BEGIN_EXTERNC
/*
 * Generic StrandFT functions for faked interaction interface function tables.
 * These functions are designed for re-use within the provmgr unit tests.
 */

void ContextTest_Post_NO_OP( _In_ Strand* self_, _In_ Message* msg);
void ContextTest_PostControl_NO_OP( _In_ Strand* self, _In_ Message* msg);
void ContextTest_Ack_NO_OP( _In_ Strand* self );
void ContextTest_Cancel_NO_OP( _In_ Strand* self );
void ContextTest_Close_NO_OP( _In_ Strand* self_ );
void ContextTest_Finish_NO_OP( _In_ Strand* self_ );
void ContextTest_Post_ImmediateAck( _In_ Strand* self_, _In_ Message* msg);
void ContextTest_Ack_ForSubscriptionContext( _In_ Strand* self_);
void ContextTest_Aux_PostLeft_ForSubscriptionContext( _In_ Strand* self_ );

/*
#ifdef _PREFAST_
#pragma prefast (pop)
#endif / * _PREFAST_ */

/*
 * StrandFT functions and table for a faked "Left" side of an interaction.
 */
extern StrandFT ContextTest_Left_InteractionFT;

/*
 * StrandFT functions and table for a faked "Right" side of an interaction that
 * sits within the SubscriptionContext's Context.
 */
extern StrandFT ContextTest_Right_InteractionFT;

/*
 * StrandFT functions and table for a faked "Right" side of an interaction that
 * sits within the SubscriptionContext's Context.
 * It simulates the cancel function of SubscriptionContext
 */
extern StrandFT SimSubscribeContext_Right_InteractionFT;

#define SERVER_EXCEEDED_LIMIT_MSG MI_T("server limits exceeded")

MI_Result CreateAndAddSubscriptionHelper(
    SubscriptionManager* mgr,
    Provider* provider,
    InteractionOpenParams* interactionParams,
    SubscriptionContext** subscrContext );

MI_Result Test_Provider_Init(
    _Inout_ Provider* provider );

void Test_Provider_Finalize(
    _In_ _Post_invalid_ Provider* provider );

PAL_END_EXTERNC

#endif /* _provmgr_strand_helper_h */

