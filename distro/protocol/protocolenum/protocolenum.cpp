#include <protocol/protocol.h>
#include <io/io.h>
#include <base/paths.h>

static void _EventCallback(
    Protocol* protocol,
    ProtocolEvent event,
    void* data)
{
    // Zprintf(ZT("==== _EventCallback()\n"));

    if (event == PROTOCOLEVENT_CONNECT)
    {
        // Zprintf(ZT("==== EventCallback() PROTOCOLEVENT_CONNECT\n"));
        return;
    }

    if (event == PROTOCOLEVENT_CONNECT_FAILED)
    {
        // Zprintf(ZT("==== EventCallback() PROTOCOLEVENT_CONNECT_FAILED\n"));
        exit(1);
        return;
    }

    if (event == PROTOCOLEVENT_DISCONNECT)
    {
        // Zprintf(ZT("==== _EventCallback(): PROTOCOLEVENT_DISCONNECT\n"));
        return;
    }
}

static size_t count = 0;

static MI_Boolean _MessageCallback(
    Protocol* protocol,
    Message* msg,
    void* data)
{
    // Zprintf(ZT("==== _MessageCallback(): %u\n"), (int)count);

    switch (msg->tag)
    {
        case NoOpRspTag:
        {
            // Zprintf(ZT("==== _MessageCallback(): NoOpRspTag\n"));
            break;
        }
        case PostInstanceMsgTag:
        {
            // Zprintf(ZT("==== _MessageCallback(): PostInstanceMsgTag\n"));
            count++;
            break;
        }
        case SubscribeResTag:
        {
            // Zprintf(ZT("==== _MessageCallback(): SubscribeResTag\n"));
            break;
        }
        case PostResultMsgTag:
        {
            // Zprintf(ZT("==== _MessageCallback(): PostResultMsgTag\n"));
            Zprintf(ZT("COUNT{%u}\n"), (int)count);
            exit(0);
        }
        default:
        {
            Zprintf(ZT("==== _MessageCallback(): default\n"));
            break;
        }
    }
    return MI_TRUE;
}

int main(int argc, char** argv)
{
    // Create connector:

    Protocol* protocol;
    void* callbackData = NULL;
    {
        MI_Result r = Protocol_New_Connector(
            &protocol, 
            NULL,
            GetPath(ID_SOCKETFILE),
            _MessageCallback, 
            callbackData,
            _EventCallback, 
            callbackData,
            "unittest",
            "unittest");

        if (r != MI_RESULT_OK)
        {
            Fzprintf(stderr, ZT("%s: Protocol_New_Connector() failed\n"), argv[0]);
            exit(1);
        }
    }

    // Create enuemrate request:

    EnumerateInstancesReq* req ;
    {
        MI_Uint64 msgID = 1;
        req = EnumerateInstancesReq_New(msgID, BinaryProtocolFlag);

        if (!req)
        {
            Fzprintf(stderr, ZT("%s: EnumerateInstancesReq_New() failed\n"), argv[0]);
            exit(1);
        }

        req->deepInheritance = MI_TRUE;
        req->nameSpace = Batch_Zdup(req->base.batch, ZT("root/omi"));
        req->className = Batch_Zdup(req->base.batch, ZT("MILargeEvent"));
    }

    // Send the message:
    {
        MI_Result r = Protocol_Send(protocol, &req->base);

        if (r != MI_RESULT_OK)
        {
            Fzprintf(stderr, ZT("%s: Protocol_Send() failed\n"), argv[0]);
            exit(1);
        }
    }

    // Populate the fields of the request message:
    for (;;)
        Protocol_Run(protocol, 1000);

    return 0;
}
