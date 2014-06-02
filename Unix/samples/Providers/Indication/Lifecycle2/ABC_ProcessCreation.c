/* @migen@ */
#include <MI.h>
#include <util.h>
#include "ABC_Process.h"
#include "ABC_ProcessCreation.h"

struct _ABC_ProcessCreation_Self
{
    SelfStruct self;
};

/*
 * Callback function to trigger indication
 */
MI_Uint32 MI_CALL TriggerIndication(
    _In_ void* callbackdata)
{
    ABC_ProcessCreation_Self* self = (ABC_ProcessCreation_Self*)callbackdata;
    MI_Context * context = (MI_Context *)self->self.context;
    ABC_ProcessCreation proccreate;
    ABC_Process source;
    MI_Result r;

    /* construct source instance */
    r = ABC_Process_Construct(&source, context);
    CHECKR_POST_RETURN(context, r);
    r = ABC_Process_Set_Name( &source, MI_T("gedit") );
    CHECKR_POST_RETURN(context, r);
    r = ABC_Process_Set_Caption( &source, MI_T("GUI EDITOR") );
    CHECKR_POST_RETURN(context, r);

    /* construct indication */
    r = ABC_ProcessCreation_Construct(&proccreate, context);
    CHECKR_POST_RETURN(context, r);

    /* set properties of indication */
    r = ABC_ProcessCreation_Set_SourceInstance( &proccreate, &source.__instance );
    CHECKR_POST_RETURN(context, r);
    ABC_ProcessCreation_Set_SequenceNumber( &proccreate,  ++(self->self.seqid));

    /* post indication to server, server will dispatch to subscribed clients */
    ABC_ProcessCreation_Post( &proccreate, context, 0, NULL);
    CHECKR_POST_RETURN(context, r);

    /* destruct indication */
    ABC_ProcessCreation_Destruct( &proccreate );

    /* destruct source */
    ABC_Process_Destruct( &source );

    return 1;
}

ABC_ProcessCreation_Self g_self;

void MI_CALL ABC_ProcessCreation_Load(
    ABC_ProcessCreation_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = &g_self;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_ProcessCreation_Unload(
    ABC_ProcessCreation_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_ProcessCreation_EnableIndications(
    ABC_ProcessCreation_Self* self,
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
    memset( self, 0, sizeof(ABC_ProcessCreation_Self) );
    self->self.context = indicationsContext;
    self->self.postindication = TriggerIndication;

    /*
     * Create a background thread that will periodically fire indications, 
     * simulating process creation events originating from system.
     */
    code = Thread_Create(&self->self.thread, fireIndication, (void*)self);
    if ( code != 0 )
    {
        /* Failed to create thread */
        MI_Context_PostError( indicationsContext, MI_RESULT_FAILED, MI_T("MI"), MI_T("Failed to create thread") );
    }
}

void MI_CALL ABC_ProcessCreation_DisableIndications(
    ABC_ProcessCreation_Self* self,
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

void MI_CALL ABC_ProcessCreation_Subscribe(
    ABC_ProcessCreation_Self* self,
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

void MI_CALL ABC_ProcessCreation_Unsubscribe(
    ABC_ProcessCreation_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf)
{
    /* NOTE: This function indicates a subscription was cancelled */
    MI_PostResult(context, MI_RESULT_OK);
}

