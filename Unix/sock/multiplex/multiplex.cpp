#include <vector>
#include <cstdlib>
#include <iostream>
#include <ut/ut.h>
#include <sock/addr.h>
#include <pal/sleep.h>
#include <pal/thread.h>
#include <base/result.h>
#include <sock/sock.h>
#include <sock/selector.h>

#define MAX_MESSAGES 10000
#define NUM_SESSIONS 10
#define TOTAL_MESSAGES (MAX_MESSAGES * NUM_SESSIONS)
#define MAX_QUEUE_SIZE 10
#define PORT 8000

//#define DUMP

// #define CHECK_DATA

using namespace std;

//==============================================================================
//
// Err()
//
//==============================================================================

static void Err(const char* msg)
{
    fprintf(stderr, "error: %s\n", msg);
    exit(1);
}

//==============================================================================
//
// Header:
// Body:
//
//==============================================================================

struct Header
{
    unsigned int word1;
    unsigned int word2;
    unsigned int word3;
    unsigned int word4;
};

struct Body
{
    unsigned char data[16*1024];
};

struct Msg
{
    Header header;
    Body body;
};

//==============================================================================
//
// Client:
//
//==============================================================================

struct ClientHandler : public Handler
{
    bool connected;
    size_t messagesSent;
    size_t offset;
    Msg msg;

    static unsigned long totalMessagesSent;

    ClientHandler()
    {
        connected = false;
        messagesSent = 0;
        offset = 0;

        msg.header.word1 = 0x11111111;
        msg.header.word2 = 0x22222222;
        msg.header.word3 = 0x33333333;
        msg.header.word4 = 0x44444444;
        memset(&msg.body.data, 0xBB, sizeof(msg.body.data));
    }
};

unsigned long ClientHandler::totalMessagesSent = 0;

BEGIN_EXTERNC
static MI_Boolean ClientCallback(
    Selector* sel,
    Handler* handler_,
    MI_Uint32 mask, 
    MI_Uint64 currentTimeUsec)
{
    ClientHandler* handler = (ClientHandler*)handler_;
    MI_UNUSED(sel);

    if (mask & SELECTOR_WRITE)
    {
        for (;;)
        {
            if (!handler->connected)
            {
                handler->mask = SELECTOR_READ | SELECTOR_WRITE;
                handler->connected = true;
            }

            if (handler->messagesSent != MAX_MESSAGES)
            {
                if (handler->offset == sizeof(Msg))
                    handler->offset = 0;

                size_t n = 0;

                MI_Result r = Sock_Write(
                    handler->sock, 
                    (char*)&handler->msg + handler->offset,
                    sizeof(Msg) - handler->offset,
                    &n);

                if (r == MI_RESULT_WOULD_BLOCK)
                    break;

                if (r != MI_RESULT_OK)
                    Err("Sock_Write() failed");

                handler->offset += n;

                if (handler->offset == sizeof(Msg))
                {
                    handler->messagesSent++;
                    ClientHandler::totalMessagesSent++;

                    if (ClientHandler::totalMessagesSent == TOTAL_MESSAGES)
                    {
                        printf("Wrote %lu messages\n",
                            ClientHandler::totalMessagesSent);
                        exit(0);
                    }
                }
            }
            else
            {
                // Quit watching for write events.
                handler->mask = SELECTOR_READ;
                break;
            }
        }
    }

    if (mask & SELECTOR_READ)
    {
        // Should be unreachable since serer sends no data:
        Err("Unexpected!");
    }

    if (mask & SELECTOR_REMOVE)
    {
        Sock_Close(handler->sock);
        delete handler;
    }
    else if (mask & SELECTOR_DESTROY)
    {
        Sock_Close(handler->sock);
        delete handler;
    }

    return MI_TRUE;
}
END_EXTERNC

void RunClient(const char* host)
{
    Sock_Start();

    Selector sel;
    Selector_Init(&sel);
    
    for (unsigned short i = 0; i < NUM_SESSIONS; i++)
    {
        Addr addr;
        Sock sock;

        if (Addr_Init(&addr, host, PORT) != MI_RESULT_OK)
            Err("Addr_Init() failed");

        if (Sock_Create(&sock) != MI_RESULT_OK)
            Err("Sock_Create() failed");

        if (Sock_SetBlocking(sock, MI_FALSE) != MI_RESULT_OK)
            Err("Sock_SetBlocking() failed");

        MI_Result r = Sock_Connect(sock, &addr);

        if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
            Err("Sock_Connect() failed");

        ClientHandler* h = new ClientHandler;
        h->sock = sock;
        h->mask = SELECTOR_WRITE;
        h->callback = ClientCallback;

        if (Selector_AddHandler(&sel, h) != MI_RESULT_OK)
            Err("Selector_AddHandler() failed");
    }

    for (;;)
    {
        MI_Result r = Selector_Run(&sel, 1000 * 10000);

        if (r != MI_RESULT_OK && r != MI_RESULT_TIME_OUT)
            Err("Selector_Run() failed");
    }

    Selector_Destroy(&sel);
    Sock_Stop();
}

//==============================================================================
//
// Server:
//
//==============================================================================

struct ServerHandler : public Handler
{
    size_t offset;
    bool readHeader;
    static unsigned long totalMessagesRecv;

    ServerHandler()
    {
        offset = 0;
        readHeader = true;
    }
};

unsigned long ServerHandler::totalMessagesRecv;

BEGIN_EXTERNC
static MI_Boolean ServerCallback(
    Selector* sel,
    Handler* handler_,
    MI_Uint32 mask, 
    MI_Uint64 currentTimeUsec)
{
    ServerHandler* handler = (ServerHandler*)handler_;

    // Process READ events.
    if (mask & SELECTOR_READ)
    {
        if (handler->readHeader)
        {
            Header header;
            size_t n = 0;

            MI_Result r = Sock_Read(
                handler->sock, 
                (char*)&header + handler->offset, 
                sizeof(header) - handler->offset,
                &n);

            if (r == MI_RESULT_WOULD_BLOCK)
                return MI_TRUE;

            if (r != MI_RESULT_OK)
                Err("Sock_Read() failed");

            // Did client close the connection?
            if (n == 0)
                return MI_FALSE;

            handler->offset += n;

            if (handler->offset == sizeof(Header))
            {

                if (header.word1 != 0x11111111)
                    Err("Expected 0x11111111");

                if (header.word2 != 0x22222222)
                    Err("Expected 0x22222222");

                if (header.word3 != 0x33333333)
                    Err("Expected 0x33333333");

                if (header.word4 != 0x44444444)
                    Err("Expected 0x44444444");

                handler->readHeader = false;
                handler->offset = 0;
            }

            // Check the data:

        }
        else
        {
            Body body;
            size_t n = 0;

            MI_Result r = Sock_Read(
                handler->sock, 
                (char*)&body + handler->offset, 
                sizeof(body) - handler->offset,
                &n);

            if (r == MI_RESULT_WOULD_BLOCK)
                return MI_TRUE;

            if (r != MI_RESULT_OK)
                Err("Sock_Read() failed");

            // Did client close the connection?
            if (n == 0)
                return MI_FALSE;

            handler->offset += n;

            if (handler->offset == sizeof(Body))
            {
#if defined(CHECK_DATA)
                for (size_t i = 0; i < sizeof(body.data); i++)
                {
                    if (body.data[i] != 0xBB)
                        Err("expected 0xBB");
                }
#endif

                handler->readHeader = true;
                handler->offset = 0;
                ServerHandler::totalMessagesRecv++;

                if (ServerHandler::totalMessagesRecv == TOTAL_MESSAGES)
                {
                    printf("done\n");
                }
            }
        }
    }

    // Process WRITE events.
    if (mask & SELECTOR_WRITE)
    {
        Err("Unexpected write event");
    }

    if (mask & SELECTOR_REMOVE)
    {
#if defined(DUMP)
        printf("Close connection\n");
#endif
        Sock_Close(handler->sock);
        delete handler;
    }
    else if (mask & SELECTOR_DESTROY)
    {
#if defined(DUMP)
        printf("Destory connection\n");
#endif
        Sock_Close(handler->sock);
        delete handler;
    }

    return MI_TRUE;
}
END_EXTERNC

BEGIN_EXTERNC
static MI_Boolean ListenCallback(
    Selector* sel,
    Handler* handler,
    MI_Uint32 mask, 
    MI_Uint64 currentTimeUsec)
{
    if (mask & SELECTOR_READ)
    {
        Sock sock;
        Addr addr;

        if (Sock_Accept(handler->sock, &sock, &addr) != MI_RESULT_OK)
            Err("Sock_Accept() failed");

        if (Sock_SetBlocking(sock, MI_FALSE) != MI_RESULT_OK)
            Err("Sock_SetBlocking() failed");

        // Create handler for new client.
        {
            ServerHandler* h = new ServerHandler;
            h->sock = sock;
            h->mask = SELECTOR_READ;
            h->callback = ServerCallback;

            if (Selector_AddHandler(sel, h) != MI_RESULT_OK)
                Err("Selector_AddHandler() failed");
        }
#if defined(DUMP)
        printf("Accepted connection\n");
#endif
    }

    if (mask & SELECTOR_REMOVE)
    {
        Sock_Close(handler->sock);
        PAL_Free(handler);
    }
    else if (mask & SELECTOR_DESTROY)
    {
        Sock_Close(handler->sock);
        PAL_Free(handler);
    }

    return MI_TRUE;
}
END_EXTERNC

void RunServer(const char* host)
{
    Sock_Start();

    Selector sel;
    Selector_Init(&sel);

    {
        Addr addr;
        Sock sock;

        if (Addr_Init(&addr, host, PORT) != MI_RESULT_OK)
            Err("Addr_Init() failed");

        if (Sock_CreateListener(&sock, &addr) != MI_RESULT_OK)
            Err("Sock_Create() failed");

        Handler* h = (Handler*)PAL_Calloc(1, sizeof(Handler));
        h->sock = sock;
        h->mask = SELECTOR_READ;
        h->callback = ListenCallback;

        if (Selector_AddHandler(&sel, h) != MI_RESULT_OK)
            Err("Selector_AddHandler() failed");
    }

    for (;;)
    {
        MI_Result r = Selector_Run(&sel, 1000 * 10000);

        if (r != MI_RESULT_OK && r != MI_RESULT_TIME_OUT)
            Err("Selector_Run() failed");
    }

    Selector_Destroy(&sel);
    Sock_Stop();
}

//==============================================================================
//
// MClient:
//
//==============================================================================

struct MClientHandler : public Handler
{
    bool connected;

    struct Session
    {
        size_t messagesSent;
        size_t offset;
        Msg msg;

        // Number of messages in the queue. If equal to MAX_QUEUE_SIZE, then
        // wait for continue message from server before writing another message.
        size_t queueSize;
    };

    Session sess[NUM_SESSIONS];
    size_t sessIndex;

    static unsigned long numAcks;
    static unsigned long totalMessagesSent;

    MClientHandler()
    {
        memset(this, 0, sizeof(*this));

        for (size_t i = 0; i < NUM_SESSIONS; i++)
        {
            Msg& msg = sess[i].msg;

            // Use word1 as the session number:
            msg.header.word1 = i;
            msg.header.word2 = 0x22222222;
            msg.header.word3 = 0x33333333;
            msg.header.word4 = 0x44444444;
            memset(&msg.body.data, 0xBB, sizeof(msg.body.data));
        }
    }

    // Select the next session that is ready to write:
    Session* GetReadySession()
    {
        for (size_t i = sessIndex; i < NUM_SESSIONS; i++)
        {
            if (sess[i].queueSize < MAX_QUEUE_SIZE &&
                sess[i].messagesSent < MAX_MESSAGES)
            {
                sessIndex = i;
                return &sess[i];
            }
        }

        for (size_t i = 0; i < sessIndex; i++)
        {
            if (sess[i].queueSize < MAX_QUEUE_SIZE &&
                sess[i].messagesSent < MAX_MESSAGES)
            {
                sessIndex = i;
                return &sess[i];
            }
        }

        // No sessions are ready to write:
        return 0;
    }
};

unsigned long MClientHandler::numAcks = 0;
unsigned long MClientHandler::totalMessagesSent = 0;

BEGIN_EXTERNC
static MI_Boolean MClientCallback(
    Selector* sel,
    Handler* handler_,
    MI_Uint32 mask, 
    MI_Uint64 currentTimeUsec)
{
    MClientHandler* handler = (MClientHandler*)handler_;
    MI_UNUSED(sel);

    if (mask & SELECTOR_WRITE)
    {
        // We just got the connection completion:
        if (!handler->connected)
            handler->connected = true;

        // Write data for each session:
        for (;;)
        {
            MClientHandler::Session* sess = handler->GetReadySession();

            // No session is ready to write, so quit watching write events:
            if (!sess)
            {
                handler->mask = SELECTOR_READ;
                break;
            }

            handler->mask = SELECTOR_READ | SELECTOR_WRITE;

            size_t n = 0;

            MI_Result r = Sock_Write(
                handler->sock, 
                (char*)&sess->msg + sess->offset,
                sizeof(Msg) - sess->offset,
                &n);

#if defined(DUMP)
            printf("send{%u}{%u}\n", (int)handler->sessIndex, (int)n);
#endif

            if (r == MI_RESULT_WOULD_BLOCK)
                break;

            if (r != MI_RESULT_OK)
                Err("Sock_Write() failed");

            if (n == 0)
                return MI_FALSE;

            sess->offset += n;

            // If complete message was written:
            if (sess->offset == sizeof(Msg))
            {
                sess->queueSize++;
                sess->messagesSent++;
                MClientHandler::totalMessagesSent++;
                sess->offset = 0;

                if (++handler->sessIndex == NUM_SESSIONS)
                    handler->sessIndex = 0;
            }
        }
    }

    if (mask & SELECTOR_READ)
    {
        size_t n = 0;

        // Read continue message (consists of session index):

        unsigned char sessIndex = 0;

        MI_Result r = Sock_Read(
            handler->sock, 
            (char*)&sessIndex,
            sizeof(sessIndex),
            &n);

        if (r == MI_RESULT_WOULD_BLOCK)
            return MI_TRUE;

        if (r != MI_RESULT_OK)
            Err("Sock_Read() failed");

        // Did server close the connection?
        if (n == 0)
            return MI_FALSE;

        if (n != sizeof(sessIndex))
            Err("Sock_Read() failed");

#if defined(DUMP)
        printf("recv{%u}{%u}\n", (int)handler->sessIndex, (int)n);
#endif

        // Set this session's queue size back to zero so it can start sending
        // data again:
        handler->sess[sessIndex].queueSize = 0;

        // Watch for write again (may already be enabled)
        handler->mask = SELECTOR_READ | SELECTOR_WRITE;

        MClientHandler::numAcks++;

        if (MClientHandler::numAcks == TOTAL_MESSAGES / MAX_QUEUE_SIZE)
        {
            printf("Wrote %lu messages\n",
                MClientHandler::totalMessagesSent++);
            exit(0);
        }
    }

    if (mask & SELECTOR_REMOVE)
    {
        Sock_Close(handler->sock);
        delete handler;
    }
    else if (mask & SELECTOR_DESTROY)
    {
        Sock_Close(handler->sock);
        delete handler;
    }

    return MI_TRUE;
}
END_EXTERNC

void RunMClient(const char* host)
{
    Sock_Start();

    Selector sel;
    Selector_Init(&sel);
    
    // Connect to server:
    {
        Addr addr;
        Sock sock;

        if (Addr_Init(&addr, host, PORT) != MI_RESULT_OK)
            Err("Addr_Init() failed");

        if (Sock_Create(&sock) != MI_RESULT_OK)
            Err("Sock_Create() failed");

        if (Sock_SetBlocking(sock, MI_FALSE) != MI_RESULT_OK)
            Err("Sock_SetBlocking() failed");

        MI_Result r = Sock_Connect(sock, &addr);

        if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
            Err("Sock_Connect() failed");

        MClientHandler* h = new MClientHandler;
        h->sock = sock;
        h->mask = SELECTOR_WRITE;
        h->callback = MClientCallback;

        if (Selector_AddHandler(&sel, h) != MI_RESULT_OK)
            Err("Selector_AddHandler() failed");
    }

    for (;;)
    {
        MI_Result r = Selector_Run(&sel, 1000 * 10000);

        if (r != MI_RESULT_OK && r != MI_RESULT_TIME_OUT)
            Err("Selector_Run() failed");
    }

    Selector_Destroy(&sel);
    Sock_Stop();
}

//==============================================================================
//
// MServer:
//
//==============================================================================

struct MServerHandler : public Handler
{
    bool connected;

    struct Session
    {
        size_t queueSize;
    };

    Session sess[NUM_SESSIONS];
    Msg msg;
    size_t offset;
    bool readHeader;

    static unsigned long totalMessagesRecv;

    MServerHandler()
    {
        memset(this, 0, sizeof(*this));
        readHeader = true;
    }
};

unsigned long MServerHandler::totalMessagesRecv;

BEGIN_EXTERNC
static MI_Boolean MServerCallback(
    Selector* sel,
    Handler* handler_,
    MI_Uint32 mask, 
    MI_Uint64 currentTimeUsec)
{
    MServerHandler* handler = (MServerHandler*)handler_;

    // Process READ events.
    if (mask & SELECTOR_READ)
    {
        if (handler->readHeader)
        {
            Header& header = handler->msg.header;

            size_t n = 0;

            MI_Result r = Sock_Read(
                handler->sock, 
                (char*)&header + handler->offset, 
                sizeof(header) - handler->offset,
                &n);

            if (r == MI_RESULT_WOULD_BLOCK)
                return MI_TRUE;

            if (r != MI_RESULT_OK)
                Err("Sock_Read() failed");

            // Did client close the connection?
            if (n == 0)
                return MI_FALSE;

            handler->offset += n;

#if defined(DUMP)
            printf("recv{%u}\n", (int)n);
#endif

            if (handler->offset == sizeof(Header))
            {
                size_t sessIndex = (size_t)header.word1;

                if (sessIndex < 0 || sessIndex >= NUM_SESSIONS)
                    Err("Expected session in range");

                if (header.word2 != 0x22222222)
                    Err("Expected 0x22222222");

                if (header.word3 != 0x33333333)
                    Err("Expected 0x33333333");

                if (header.word4 != 0x44444444)
                    Err("Expected 0x44444444");

                handler->readHeader = false;
                handler->offset = 0;
            }
        }
        else
        {
            Body& body = handler->msg.body;

            size_t n = 0;

            MI_Result r = Sock_Read(
                handler->sock, 
                (char*)&body + handler->offset, 
                sizeof(body) - handler->offset,
                &n);

            if (r == MI_RESULT_WOULD_BLOCK)
                return MI_TRUE;

            if (r != MI_RESULT_OK)
                Err("Sock_Read() failed");

            // Did client close the connection?
            if (n == 0)
                return MI_FALSE;

            handler->offset += n;

            if (handler->offset == sizeof(Body))
            {
#if defined(CHECK_DATA)
                for (size_t i = 0; i < sizeof(body.data); i++)
                {
                    if (body.data[i] != 0xBB)
                        Err("expected 0xBB");
                }
#endif

                size_t sessIndex = handler->msg.header.word1;

#if defined(DUMP)
                printf("recv{%u}{%u}\n", (int)sessIndex, sizeof(Body));
#endif

                if (sessIndex < 0 || sessIndex >= NUM_SESSIONS)
                    Err("sessIndex out of range");

                assert(handler->sess[sessIndex].queueSize < MAX_QUEUE_SIZE);

                if (++handler->sess[sessIndex].queueSize == MAX_QUEUE_SIZE)
                {
                    // Need to write a 'continue' message:
                    handler->mask = SELECTOR_WRITE;
                }

                handler->readHeader = true;
                handler->offset = 0;
                MServerHandler::totalMessagesRecv++;

                if (MServerHandler::totalMessagesRecv == TOTAL_MESSAGES)
                {
                    printf("done\n");
                }
            }
        }
    }

    // Process WRITE events.
    if (mask & SELECTOR_WRITE)
    {
        for (size_t i = 0; i < NUM_SESSIONS; i++)
        {
            if (handler->sess[i].queueSize == MAX_QUEUE_SIZE)
            {
                unsigned char sessIndex = (unsigned char)i;

                size_t n = 0;

                MI_Result r = Sock_Write(
                    handler->sock, 
                    (char*)&sessIndex,
                    sizeof(sessIndex),
                    &n);

                if (r == MI_RESULT_WOULD_BLOCK)
                    return MI_TRUE;

                if (r != MI_RESULT_OK)
                {
                    return MI_FALSE;
                }

                if (n == 0)
                    return MI_FALSE;

#if defined(DUMP)
                printf("send{%u}{%u}\n", (int)sessIndex, (int)n);
#endif

                handler->sess[i].queueSize = 0;
                handler->mask = SELECTOR_WRITE | SELECTOR_READ;
            }
        }

        handler->mask = SELECTOR_READ;
    }

    if (mask & SELECTOR_REMOVE)
    {
#if defined(DUMP)
        printf("Close connection\n");
#endif
        Sock_Close(handler->sock);
        delete handler;
    }
    else if (mask & SELECTOR_DESTROY)
    {
#if defined(DUMP)
        printf("Destory connection\n");
#endif
        Sock_Close(handler->sock);
        delete handler;
    }

    return MI_TRUE;
}
END_EXTERNC

BEGIN_EXTERNC
static MI_Boolean MListenCallback(
    Selector* sel,
    Handler* handler,
    MI_Uint32 mask, 
    MI_Uint64 currentTimeUsec)
{
    if (mask & SELECTOR_READ)
    {
        Sock sock;
        Addr addr;

        if (Sock_Accept(handler->sock, &sock, &addr) != MI_RESULT_OK)
            Err("Sock_Accept() failed");

        if (Sock_SetBlocking(sock, MI_FALSE) != MI_RESULT_OK)
            Err("Sock_SetBlocking() failed");

        // Create handler for new client.
        {
            MServerHandler* h = new MServerHandler;
            h->sock = sock;
            h->mask = SELECTOR_READ;
            h->callback = MServerCallback;

            if (Selector_AddHandler(sel, h) != MI_RESULT_OK)
                Err("Selector_AddHandler() failed");
        }

#if defined(DUMP)
        printf("Accepted connection\n");
#endif
    }

    if (mask & SELECTOR_REMOVE)
    {
        Sock_Close(handler->sock);
        PAL_Free(handler);
    }
    else if (mask & SELECTOR_DESTROY)
    {
        Sock_Close(handler->sock);
        PAL_Free(handler);
    }

    return MI_TRUE;
}
END_EXTERNC

void RunMServer(const char* host)
{
    Sock_Start();

    Selector sel;
    Selector_Init(&sel);

    {
        Addr addr;
        Sock sock;

        if (Addr_Init(&addr, host, PORT) != MI_RESULT_OK)
            Err("Addr_Init() failed");

        if (Sock_CreateListener(&sock, &addr) != MI_RESULT_OK)
            Err("Sock_Create() failed");

        Handler* h = (Handler*)PAL_Calloc(1, sizeof(Handler));
        h->sock = sock;
        h->mask = SELECTOR_READ;
        h->callback = MListenCallback;

        if (Selector_AddHandler(&sel, h) != MI_RESULT_OK)
            Err("Selector_AddHandler() failed");
    }

    for (;;)
    {
        MI_Result r = Selector_Run(&sel, 1000 * 10000);

        if (r != MI_RESULT_OK && r != MI_RESULT_TIME_OUT)
            Err("Selector_Run() failed");
    }

    Selector_Destroy(&sel);
    Sock_Stop();
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s [client|server]\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "client") == 0)
    {
        RunClient("127.0.0.1");
    }
    else if (strcmp(argv[1], "mclient") == 0)
    {
        RunMClient("127.0.0.1");
    }
    else if (strcmp(argv[1], "server") == 0)
    {
        RunServer("127.0.0.1");
    }
    else if (strcmp(argv[1], "mserver") == 0)
    {
        RunMServer("127.0.0.1");
    }
    else
    {
        fprintf(stderr, "%s: invalid first argument\n", argv[0]);
        exit(1);
    }

    return 0;
}
