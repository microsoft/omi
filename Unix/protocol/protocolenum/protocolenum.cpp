/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <protocol/protocol.h>
#include <pal/format.h>
#include <base/paths.h>

STRAND_DEBUGNAME(EnumClient);

static size_t count = 0;

static void _Client_Post( _In_ Strand* self_, _In_ Message* msg)
{
    //trace_Client_PostMessage( msg->tag );
    
    switch (msg->tag)
    {
        case NoOpRspTag:
        {
            // Tprintf(ZT("==== _MessageCallback(): NoOpRspTag\n"));
            break;
        }
        case PostInstanceMsgTag:
        {
            // Tprintf(ZT("==== _MessageCallback(): PostInstanceMsgTag\n"));
            count++;
            break;
        }
        case SubscribeResTag:
        {
            // Tprintf(ZT("==== _MessageCallback(): SubscribeResTag\n"));
            break;
        }
        case PostResultMsgTag:
        {
            // Tprintf(ZT("==== _MessageCallback(): PostResultMsgTag\n"));
            Tprintf(ZT("COUNT{%u}\n"), (int)count);
            exit(0);
        }
        default:
        {
            Tprintf(ZT("==== _MessageCallback(): default\n"));
            break;
        }
    }

    Strand_Ack(self_);  // return an Ack to protocol
}

static void _Client_PostControl( _In_ Strand* self, _In_ Message* msg)
{
    ProtocolEventConnect* eventMsg = (ProtocolEventConnect*)msg;

    DEBUG_ASSERT( ProtocolEventConnectTag == msg->tag );

    if( eventMsg->success )
    {
        // Create enuemrate request:
        
        EnumerateInstancesReq* req ;
        {
            MI_Uint64 operationId = 1;
            req = EnumerateInstancesReq_New(operationId, BinaryProtocolFlag);
        
            if (!req)
            {
                Ftprintf(stderr, ZT("%s: EnumerateInstancesReq_New() failed\n"), argv[0]);
                exit(1);
            }
        
            req->deepInheritance = MI_TRUE;
            req->nameSpace = Batch_Zdup(req->base.batch, ZT("root/omi"));
            req->className = Batch_Zdup(req->base.batch, ZT("MILargeEvent"));
        
            if (!req->nameSpace || !req->className)
            {
                Ftprintf(stderr, PAL_T("%s: Out of memory\n"), argv[0]);
                exit(1);
            }
        }
        
        // Send the message:
        Strand_Post(strand,&req->base);
    }
    else
    {
        exit(1);
    }
}

static void _Client_Ack( _In_ Strand* self )
{
}

static void _Client_Close( _In_ Strand* self_ )
{
    trace_Client_Close();
    // management done by strand implementation
}

static void _Client_Finish( _In_ Strand* self_ )
{
    trace_Client_Finish();
    // nothing to do here, (class take care of deleting itself)
}

/*
	Manages the client protocol enumeration of the MILargeEvent 
	class on the root/omi namespace (test object)

	Behaviour:
	- Once the successful connect PostControl is received 
	   an enumerate instance message is issued and then just 
	   manages receiving and printing responses
*/
StrandFT _Client_InteractionFT =
{
    _Client_Post, 
    _Client_PostControl, 
    _Client_Ack,
    NULL, 
    _Client_Close,
    _Client_Finish,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL 
};

int main(int argc, char** argv)
{
    Strand* strand;

    // Create connector:

    ProtocolSocket* protocol;
    void* callbackData = NULL;

    strand = Strand_New( &_Client_InteractionFT, 0, 0, NULL );

    if( NULL == strand )
    {
        Ftprintf(stderr, ZT("%s: Strand_New() failed\n"), argv[0]);
        exit(1);
    }
    
    STRAND_SETDEBUG(strand,EnumClient);
    
    {
        MI_Result r = ProtocolSocketAndBase_New_Connector(
            &protocol, 
            &strand->info.interaction,
            OMI_GetPath(ID_SOCKETFILE),
            "unittest",
            "unittest");

        if (r != MI_RESULT_OK)
        {
            Ftprintf(stderr, ZT("%s: Protocol_New_Connector() failed\n"), argv[0]);
            exit(1);
        }
    }

    // Populate the fields of the request message:
    for (;;)
        Protocol_Run(protocol.protocolBase, 1000);

    return 0;
}
