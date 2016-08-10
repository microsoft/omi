/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include <util.h>
#include "XYZ_DiskFault.h"

struct _XYZ_DiskFault_Self
{
    SelfStruct self;
};

/*
 * Callback function to trigger indication
 */
MI_Uint32 MI_CALL TriggerIndication(
    _In_ void* callbackdata)
{
    XYZ_DiskFault_Self* self = (XYZ_DiskFault_Self*)callbackdata;
    MI_Context * context = (MI_Context *)self->self.context;
    XYZ_DiskFault fault;
    MI_Result r;

    /* construct indication */
    r = XYZ_DiskFault_Construct(&fault, context);
    CHECKR_POST_RETURN(context, r);

    /* set properties of indication */
    r = XYZ_DiskFault_Set_detailmessage( &fault, MI_T("Disk fault messsage") );
    CHECKR_POST_RETURN(context, r);
    XYZ_DiskFault_Set_SequenceNumber( &fault,  ++(self->self.seqid));

    /* post indication to server, server will dispatch to subscribed clients */
    /* provider can generate bookmark value on the fly and subscribe clients */
    /* could start new subscribe request with bookmark value to resume the subscription */
    /* if and only if provider supports bookmark */
    XYZ_DiskFault_Post( &fault, context, 0, MI_T("bookmark"));
    CHECKR_POST_RETURN(context, r);

    /* destruct indication */
    XYZ_DiskFault_Destruct( &fault );

    return 1;
}

XYZ_DiskFault_Self g_self;

void MI_CALL XYZ_DiskFault_Load(
    XYZ_DiskFault_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = &g_self;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL XYZ_DiskFault_Unload(
    XYZ_DiskFault_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL XYZ_DiskFault_EnableIndications(
    XYZ_DiskFault_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    /* TODO: store indicationsContext for posting indication usage */
    /* NOTE:Call one of following functions if and ONLY if encount termination error,
            which will finalize the indicationsContext, 
            and terminate all active subscriptions to current class,
             MI_Context_PostResult
             MI_Context_PostError
             MI_Context_PostCimError
            */

    int code;
    memset( self, 0, sizeof(XYZ_DiskFault_Self) );
    self->self.context = indicationsContext;
    self->self.postindication = TriggerIndication;

    /*
     * Create a background thread that will periodically fire alert indications, 
     * simulating disk faults originating from a storage subsystem.
     */
    code = Thread_Create(&self->self.thread, fireIndication, (void*)self);
    if ( code != 0 )
    {
        /* Failed to create thread */
        MI_Context_PostError( indicationsContext, MI_RESULT_FAILED, MI_T("MI"), MI_T("Failed to create thread") );
    }
}

void MI_CALL XYZ_DiskFault_DisableIndications(
    XYZ_DiskFault_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    /* TODO: stop background thread that monitors subscriptions */
    MI_Uint32 retValue;
    self->self.disabling = MI_TRUE;
    Thread_Join( & self->self.thread, &retValue );
    MI_PostResult(indicationsContext, MI_RESULT_OK);
}

void MI_CALL XYZ_DiskFault_Subscribe(
    XYZ_DiskFault_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf)
{
    /* NOTE: This function indicates a new subscription occurs */
}

void MI_CALL XYZ_DiskFault_Unsubscribe(
    XYZ_DiskFault_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf)
{
    /* NOTE: This function indicates a subscription was cancelled */
    MI_PostResult(context, MI_RESULT_OK);
}

