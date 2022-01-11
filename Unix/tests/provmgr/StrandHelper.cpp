/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <tests/provmgr/StrandHelper.h>

NITS_EXTERN_C void ContextTest_Post_NO_OP( _In_ Strand* self_, _In_ Message* msg)
{
    MI_UNUSED( msg );
    MI_UNUSED(self_);
}

NITS_EXTERN_C void ContextTest_PostControl_NO_OP( _In_ Strand* self, _In_ Message* msg)
{
    MI_UNUSED( self );
    MI_UNUSED( msg );
}

NITS_EXTERN_C void ContextTest_Ack_NO_OP( _In_ Strand* self )
{
    MI_UNUSED( self );
}

NITS_EXTERN_C void ContextTest_Cancel_NO_OP( _In_ Strand* self )
{
    MI_UNUSED( self );
}

NITS_EXTERN_C void ContextTest_Cancel_SimulateUnsubscribeProvider( _In_ Strand* self )
{
    Context* ctx = FromOffset(Context, strand, self);
    SubscriptionContext* subCtx = (SubscriptionContext*)ctx;
    DEBUG_ASSERT( subCtx->baseCtx.ctxType == CTX_TYPE_IND_LIFECYCLE );

    //
    // Remove subscription from submgr, otherwise SubMgrSubscription leaked
    //
    SubscriptionManager* submgr = subCtx->baseCtx.provider->subMgr;
    SubMgrSubscription* sub = subCtx->subscription;
    SubMgr_DeleteSubscription(submgr, sub);

    //
    // post final message to leftside
    //
    PostResultMsg* msg = PostResultMsg_New(0);
    msg->errorMessage = SERVER_EXCEEDED_LIMIT_MSG;
    msg->result = MI_RESULT_SERVER_LIMITS_EXCEEDED;
    Strand_Post( self, &msg->base );
    PostResultMsg_Release( msg );

    //
    // Release the refcount added in SubscrContext_Init function
    // simulate the behavior of context.c:Context_PostMessageLeft
    //
    SubMgrSubscription_Release( sub );
}

NITS_EXTERN_C void ContextTest_Close_NO_OP( _In_ Strand* self_ )
{
    MI_UNUSED( self_ );
}

NITS_EXTERN_C void ContextTest_Finish_NO_OP( _In_ Strand* self_ )
{
    MI_UNUSED( self_ );
}

/*
 * StrandFT functions that perform non-default tasks
 */
 
//
// Return an Ack to caller.  No other processing is required since this is 
// designed to simulate reception and processing of a message.
//
NITS_EXTERN_C void ContextTest_Post_ImmediateAck( _In_ Strand* self_, _In_ Message* msg)
{
    MI_UNUSED( msg );
    
    Strand_Ack(self_);
}

//
// Destory the context upon finished
//
NITS_EXTERN_C void _ContextTest_Finish( _In_ Strand* self_ )
{
    Context* self = FromOffset(Context, strand, self_);
    _Context_Destroy(self);
}


NITS_EXTERN_C void ContextTest_Ack_ForSubscriptionContext( _In_ Strand* self_)
{
    Context* self = FromOffset(Context, strand, self_);
    ptrdiff_t tryingToPostLeftValue = ReadWithFence(&self->tryingToPostLeft);

    // al management done by strand implementation except broadcasting cond var

    // wake up Context_PostMessageLeft if appropriate
    // (no point on waking up Context_PostMessageLeft if CONTEXT_STRANDAUX_TRYPOSTLEFT is scheduled to run after us)
    if( CONTEXT_POSTLEFT_POSTING == tryingToPostLeftValue )    
    {
        CondLock_Broadcast((ptrdiff_t)self);
    }
}

NITS_EXTERN_C void ContextTest_Aux_PostLeft_ForSubscriptionContext( _In_ Strand* self_ )
{
    Context* self = FromOffset(Context, strand, self_);
    ptrdiff_t oldValue;

    if( !self->strand.info.thisAckPending )
    {
        Strand_Post( &self->strand, self->msgPostingLeft );
        self->msgPostingLeft = NULL; 
        oldValue = Atomic_Swap(&self->tryingToPostLeft,(ptrdiff_t)0);
        // wake up _Context_PostMessageLeft 
        CondLock_Broadcast((ptrdiff_t)self);
    }
    else
    {
        oldValue = Atomic_Swap(&self->tryingToPostLeft,(ptrdiff_t)CONTEXT_POSTLEFT_POSTING);
    }

    DEBUG_ASSERT( (CONTEXT_POSTLEFT_POSTING|CONTEXT_POSTLEFT_SCHEDULED) == oldValue );
}

/*
 * StrandFT functions and table for a faked "Left" side of an interaction.
 */
StrandFT ContextTest_Left_InteractionFT = 
{
    ContextTest_Post_ImmediateAck, 
    ContextTest_PostControl_NO_OP, 
    ContextTest_Ack_NO_OP,
    NULL, 
    ContextTest_Close_NO_OP,
    ContextTest_Finish_NO_OP,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/*
 * StrandFT functions and table for a faked "Right" side of an interaction that
 * sits within the SubscriptionContext's Context.
 */
StrandFT ContextTest_Right_InteractionFT = 
{
    ContextTest_Post_NO_OP, 
    ContextTest_PostControl_NO_OP, 
    ContextTest_Ack_ForSubscriptionContext,
    ContextTest_Cancel_NO_OP, 
    ContextTest_Close_NO_OP,
    _ContextTest_Finish,
    NULL,
    ContextTest_Aux_PostLeft_ForSubscriptionContext,
    NULL,
    NULL,
    NULL,
    NULL 
};

/*
 * StrandFT functions and table for a faked "Right" side of an interaction that
 * sits within the SubscriptionContext's Context.
 * It simulates the cancel function of SubscriptionContext, used by
 * TestContext_AggregationWithSubscr_Setup only
 */
StrandFT SimSubscribeContext_Right_InteractionFT = 
{
    ContextTest_Post_NO_OP, 
    ContextTest_PostControl_NO_OP, 
    ContextTest_Ack_ForSubscriptionContext,
    ContextTest_Cancel_SimulateUnsubscribeProvider, 
    ContextTest_Close_NO_OP,
    _ContextTest_Finish,
    NULL,
    ContextTest_Aux_PostLeft_ForSubscriptionContext,
    NULL,
    NULL,
    NULL,
    NULL 
};

MI_Result CreateAndAddSubscriptionHelper(
    SubscriptionManager* mgr,
    Provider* provider,
    InteractionOpenParams* interactionParams,
    SubscriptionContext** subscrContext )
{
    // Add subscription
    MI_Result r = SubMgr_CreateSubscription(
        mgr,
        provider,
        interactionParams,
        subscrContext );

    NitsCompare( MI_RESULT_OK, r, PAL_T("Failed to add subscription") );

    if (r == MI_RESULT_OK)
    {
        // add it to the list
        SubscriptionList_AddSubscription( &mgr->subscrList, (*subscrContext)->subscription );

        // And leave the new context strand now
        Strand_Leave( &(*subscrContext)->baseCtx.strand );

        //
        // release the one refcount added within SubMgr_CreateSubscription
        //
        SubMgrSubscription_Release( (*subscrContext)->subscription );
    }

    return r;
}

_Use_decl_annotations_
MI_Result Test_Provider_Init(
    Provider* provider )
{
    /* Provider already initialized. Nothing to do. */
    if (provider->subMgr)
    {
        return MI_RESULT_OK;
    }
    provider->subMgr = SubMgr_New();
    if (!provider->subMgr)
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    SubMgr_Init(provider->subMgr, provider);

    return MI_RESULT_OK;
}

_Use_decl_annotations_
void Test_Provider_Finalize(
    Provider* provider )
{
    if (provider->subMgr)
    {
        SubscriptionManager* submgr = provider->subMgr;
        Provider_Finalize(provider);
        PAL_Free(submgr);
    }
}

