/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

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

/* Include network headers */
#if defined(CONFIG_OS_WINDOWS)
# include <winsock2.h>
#elif defined(CONFIG_POSIX)
# include <unistd.h>
# include <errno.h>
# include <sys/socket.h>
# include <netinet/tcp.h>
# include <netinet/in.h>
# include <sys/time.h>
# include <sys/types.h>
# include <netdb.h>
# include <fcntl.h>
# include <arpa/inet.h>
#endif

#define BUFFER_SIZE 256
#define DATA_SIZE 100000

using namespace std;

static bool s_done = false;
static bool s_timeout_called = false;
static bool s_stoprunning_called = false;
// client callback data
static bool s_cln_connected = false;
static vector<char> s_cln_out;
static vector<char> s_cln_in;
static vector<char> s_data;
static Handler* s_cln_h;

// server callback
static vector<char> s_srv_data;
static Handler* s_srv_h;

#if defined(_MSC_VER)
#undef BEGIN_EXTERNC
#undef END_EXTERNC
#define BEGIN_EXTERNC
#define END_EXTERNC
#endif

NitsSetup(TestSelectorSetup)
{
    s_timeout_called = false;
    s_stoprunning_called = false;
    s_data.clear();

    s_cln_connected = false;
    s_cln_out.clear();
    s_cln_in.clear();

    s_srv_data.clear();
    s_srv_h = 0;
    s_cln_h = 0;
}
NitsEndSetup

NitsCleanup(TestSelectorSetup)
NitsEndCleanup

NitsTestWithSetup(TestAddr, TestSelectorSetup)
{
    /* sockaddr_in must fit within an Addr object */
    {    
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 24002)
#endif
        /* disabling IPv6 OACR warnings - D3M bug 52 */
        size_t x = sizeof(struct sockaddr_in);
#ifdef _PREFAST_
#pragma prefast (pop)
#endif
        size_t y = sizeof(Addr);
        TEST_ASSERT(x <= y);
    }
}
NitsEndTest


static void GenRandData(vector<char>& data)
{
    data.clear();
    data.reserve(DATA_SIZE);

    for (size_t i = 0; i < DATA_SIZE; i++)
    {
        data.push_back(char(rand()));
    }
}

BEGIN_EXTERNC
static MI_Boolean ClientCallback(
    Selector* sel,
    Handler* handler,
    MI_Uint32 mask, 
    MI_Uint64 currentTimeUsec)
{
    MI_Result r;
    MI_UNUSED(sel);
    MI_UNUSED(currentTimeUsec);

    s_cln_h = handler;

    /* Process write event */
    if (mask & SELECTOR_WRITE)
    {
        for (;;)
        {
            if (!s_cln_connected)
            {
                // Generate random data sequence.
                GenRandData(s_data);
                s_cln_out = s_data;

                // Watch for READ and WRITE events.
                handler->mask = SELECTOR_READ|SELECTOR_WRITE;

                s_cln_connected = true;
                //break;
            }

            // Write out data to server.
            if (s_cln_out.size())
            {
                size_t n = 0;
                size_t m = 7 + (int)(rand() % 256);

                if (m > s_cln_out.size())
                    m = s_cln_out.size();

                r = Sock_Write(handler->sock, &s_cln_out[0], m, &n);

                s_cln_out.erase(s_cln_out.begin(), s_cln_out.begin() + n);
#if defined(TRACE_IO)
                printf("CLIENT.WROTE[%u]\n", n);
#endif

                // If all data written, then quit watching for write.
                if (s_cln_out.size() == 0)
                {
                    handler->mask = SELECTOR_READ;
                }

                if (r == MI_RESULT_WOULD_BLOCK)
                    break;

                TEST_ASSERT(r == MI_RESULT_OK);
            }
            else
                break;
        }
    }

    /* Process read event */
    if (mask & SELECTOR_READ)
    {
        for (;;)
        {
            char buf[BUFFER_SIZE];
            size_t n = 0;

            r = Sock_Read(handler->sock, buf, sizeof(buf), &n);

            s_cln_in.insert(s_cln_in.end(), buf, buf + n);

#if defined(TRACE_IO)
            printf("CLIENT.READ[%u]\n", n);
#endif
            // All data has been written (check whether it is identical).
            if (s_cln_in.size() == s_data.size())
            {
                TEST_ASSERT(s_cln_in == s_data);
                return MI_FALSE;
            }

            if (r == MI_RESULT_WOULD_BLOCK)
                break;

            TEST_ASSERT(r == MI_RESULT_OK);


            break;
        }
    }

    if (mask & SELECTOR_REMOVE)
    {
        Sock_Close(handler->sock);
        PAL_Free(handler);
        handler = 0;
    }

    if (mask & SELECTOR_DESTROY)
    {
        if (handler)
        {
            Sock_Close(handler->sock);
            PAL_Free(handler);
        }
    }

    return MI_TRUE;
}
END_EXTERNC

BEGIN_EXTERNC
static MI_Boolean ServerCallback(
    Selector* sel,
    Handler* handler,
    MI_Uint32 mask, 
    MI_Uint64 currentTimeUsec)
{
    char buf[BUFFER_SIZE];
    MI_Result r;
    MI_UNUSED(sel);
    MI_UNUSED(currentTimeUsec);
    size_t n = 0;

    s_srv_h = handler;

    // Process READ events.
    if (mask & SELECTOR_READ)
    {
        for (;;)
        {
            // Read request:
            n = 0;
            r = Sock_Read(handler->sock, buf, sizeof(buf), &n);
            s_srv_data.insert(s_srv_data.end(), buf, buf + n);

#if defined(TRACE_IO)
            printf("SERVER.READ[%u]\n", n);
#endif
            if (r == MI_RESULT_WOULD_BLOCK)
                break;

            TEST_ASSERT(r == MI_RESULT_OK);

            // Did client close connection?
            if (n == 0)
            {
                return MI_FALSE;
            }

            // Save incoming data.

            // Now solicit read and write events.
            handler->mask = SELECTOR_READ|SELECTOR_WRITE;
            //break;
                        
            // if event 'write' was already set and we have nothing to write
            // new event will never arrive
            // so we need to try to write data once it's available
            mask |= SELECTOR_WRITE;
        }
    }

    // Process WRITE events.
    if (mask & SELECTOR_WRITE)
    {
        for (;;)
        {
            n = 0;
            size_t m = 7 + (int)(rand() % 256);

            if (m >= s_srv_data.size())
                m = s_srv_data.size();

            // Write response:
            r = Sock_Write(handler->sock, &s_srv_data[0], m, &n);

            s_srv_data.erase(s_srv_data.begin(), s_srv_data.begin() + n);
#if defined(TRACE_IO)
            printf("SERVER.WRITE[%u]\n", n);
#endif
            if (s_srv_data.size() == 0)
            {
                /* Watch for read events (but not write events) */
                handler->mask = SELECTOR_READ;
                break;
            }

            if (r == MI_RESULT_WOULD_BLOCK)
                break;

            TEST_ASSERT(r == MI_RESULT_OK);

            //break;
        }
    }

    if (mask & SELECTOR_REMOVE)
    {
        r = Sock_Close(handler->sock);
        TEST_ASSERT(r == MI_RESULT_OK);
        s_done = true;
        PAL_Free(handler);
        handler = 0;
    }

    if (mask & SELECTOR_DESTROY)
    {
        if (handler)
        {
            Sock_Close(handler->sock);
            PAL_Free(handler);
        }
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
    MI_Result r;
    Sock s;
    Addr addr;

    MI_UNUSED(currentTimeUsec);

    if (mask & SELECTOR_READ)
    {
        r = Sock_Accept(handler->sock, &s, &addr);
        TEST_ASSERT(r == MI_RESULT_OK);

        // Set to non-blocking I/O.
        r = Sock_SetBlocking(s, MI_FALSE);
        TEST_ASSERT(r == MI_RESULT_OK);

        // Create handler for new client.
        {
            Handler* h;
            h = (Handler*)PAL_Calloc(1, sizeof(Handler));
            TEST_ASSERT(h != NULL);
            if(h == NULL)
                return MI_FALSE;
            h->sock = s;
            h->mask = SELECTOR_READ;
            h->callback = ServerCallback;

            r = Selector_AddHandler(sel, h);
            TEST_ASSERT(r == MI_RESULT_OK);
        }
    }

    if (mask & SELECTOR_REMOVE)
    {
        Sock_Close(handler->sock);
        PAL_Free(handler);
        handler = 0;
    }

    if (mask & SELECTOR_DESTROY)
    {
        if (handler)
        {
            Sock_Close(handler->sock);
            PAL_Free(handler);
        }
    }

    return MI_TRUE;
}
END_EXTERNC

BEGIN_EXTERNC
static MI_Boolean TimeoutCallback(
    Selector* sel,
    Handler* handler,
    MI_Uint32 mask, 
    MI_Uint64 currentTimeUsec)
{
    MI_UNUSED(sel);

    if (mask & (SELECTOR_READ | SELECTOR_WRITE))
    {
        UT_ASSERT_FAILED_MSG("TimeoutCallback: unexpected message!");
    }

    if (mask & SELECTOR_ADD)
    {
        handler->fireTimeoutAt = currentTimeUsec + 2000;
    }

    if (mask & SELECTOR_TIMEOUT)
    {
        s_timeout_called = true;
        return MI_FALSE;
    }

    if (mask & (SELECTOR_REMOVE | SELECTOR_DESTROY))
    {
        if (INVALID_SOCK != handler->sock)
            Sock_Close(handler->sock);

        PAL_Free(handler);
    }

    return MI_TRUE;
}
END_EXTERNC

BEGIN_EXTERNC
static MI_Boolean _StopRunningCallback(
    Selector* sel,
    Handler* handler,
    MI_Uint32 mask, 
    MI_Uint64 currentTimeUsec)
{

    if (mask & SELECTOR_READ)
    {
        Sock s;
        Addr addr;

        Sock_Accept(handler->sock, &s, &addr);
        if (INVALID_SOCK != s)
            Sock_Close(s);

        Selector_StopRunning(sel);
        s_stoprunning_called = true;

        return MI_TRUE;        
    }
    if (mask & SELECTOR_WRITE)
    {
        Selector_StopRunning(sel);
        s_stoprunning_called = true;
        return MI_TRUE;        
    }

    if (mask & SELECTOR_ADD)
    {
        handler->fireTimeoutAt = currentTimeUsec + 1000;
    }

    if (mask & SELECTOR_TIMEOUT)
    {
        handler->fireTimeoutAt = 0;
        Selector_StopRunning(sel);
        s_stoprunning_called = true;
        return MI_TRUE;
    }

    if (mask & (SELECTOR_REMOVE | SELECTOR_DESTROY))
    {
        if (INVALID_SOCK != handler->sock)
            Sock_Close(handler->sock);

        PAL_Free(handler);
    }

    return MI_TRUE;
}
END_EXTERNC

static unsigned short PORT = ut::getUnittestPortNumber() + 1;

static Sock CreateClientSocket()
{
    Sock sock;
    Addr addr;
    MI_Result r;

    // Initialize address (connect using loopback).
    r = Addr_Init(&addr, "127.0.0.1", PORT, MI_FALSE);
    TEST_ASSERT(r == MI_RESULT_OK);

    // Create client socket.
    r = Sock_Create(&sock, MI_FALSE);
    TEST_ASSERT(r == MI_RESULT_OK);
 
    // Set to non-blocking I/O.
    Sock_SetBlocking(sock, MI_FALSE);

    // Listen to server.
    r = Sock_Connect(sock, &addr);
    TEST_ASSERT(r == MI_RESULT_OK || r == MI_RESULT_WOULD_BLOCK);

    return sock;
}

static Sock CreateListenerSock()
{
    Sock sock;
    Addr addr;
    MI_Result r;

    // Initialize listener address and port.
    Addr_InitAny(&addr, PORT);

    // Create server listener socket.
    r = Sock_CreateListener(&sock, &addr);
    TEST_ASSERT(r == MI_RESULT_OK);

    return sock;
}

/*
**==============================================================================
**
**
**     This test creates a TCP client and TCP server that runs in the same 
**     thread. The client connects to the server and sends a long message
**     using non-blocking I/O. The server echos the message back. Once the
**     entire message has been echoed back, both the client and the server
**     exit and the test is finished.
**
**==============================================================================
*/
NitsTestWithSetup(TestClientServer, TestSelectorSetup)
{
    Selector sel;
    Sock lsock;
    Sock csock;
    MI_Result r;
    MI_Boolean timeRead;
    MI_Uint64 deadline;
    MI_Result selectorInitResult;

    memset(&lsock, 0, sizeof(Sock));
    memset(&csock, 0, sizeof(Sock));
    // Initialize the network:
    Sock_Start();

    // Initialize the selector object.
    selectorInitResult = Selector_Init(&sel);
    if(!TEST_ASSERT(MI_RESULT_OK == selectorInitResult))
        goto TestEnd;

    // Create listener socket:
    lsock = CreateListenerSock();
    
    // Add  handler for listener socket.
    {
        Handler* h = (Handler*)PAL_Calloc(1, sizeof(Handler));

        if(!TEST_ASSERT(h))
        {
            Sock_Close(lsock);
            goto TestEnd;
        }

        h->sock = lsock;
        h->mask = SELECTOR_READ;
        h->callback = ListenCallback;

        // Watch for connection requests.
        r = Selector_AddHandler(&sel, h);
        if(!TEST_ASSERT(r == MI_RESULT_OK))
            goto TestEnd;
    }

    // Create client socket and attempt connect:
    csock = CreateClientSocket();

    // Add handler for client socket:
    {
        Handler* h = (Handler*)PAL_Calloc(1, sizeof(Handler));

        TEST_ASSERT(h);
        if(h == NULL)
        {
            Sock_Close(csock);
            goto TestEnd;
        }

        h->sock = csock;
        h->mask = SELECTOR_WRITE;
        h->callback = ClientCallback;

        // Watch for write events (indicating that connection is ready).
        r = Selector_AddHandler(&sel, h);
        TEST_ASSERT(r == MI_RESULT_OK);
    }

    // Cancel this loop after N seconds.    
    timeRead = PAL_Time(&deadline);
    TEST_ASSERT(timeRead == PAL_TRUE);
    if(timeRead == PAL_FALSE)
        goto TestEnd;

    deadline += 100*1000000;

    // Wait for connections.
    while (!s_done)
    {
        MI_Uint64 now;
        timeRead = PAL_Time(&now);
        TEST_ASSERT(timeRead == PAL_TRUE);
        if(timeRead == PAL_FALSE)
            goto TestEnd;

        if (now >= deadline)
        {
            if (s_srv_h)
                cout << "srv mask " << s_srv_h->mask << "; ";

            if (s_cln_h)
                cout << "cln mask " << s_cln_h->mask << "; ";

            cout << "out size " << s_cln_out.size() << 
                "; in size " << s_cln_in.size() <<
                "; data size " << s_data.size() <<
                "; srv data size " << s_srv_data.size() << endl;
            UT_ASSERT_FAILED_MSG("Timed out!");
            break;
        }

        r = Selector_Run(&sel, 1000*1000, MI_FALSE);
        TEST_ASSERT(r == MI_RESULT_OK || r == MI_RESULT_TIME_OUT);
    }

    // Verify that client had received all data back
    TEST_ASSERT( s_cln_in == s_data );
    
TestEnd:    
    // Destroy the selector.
    if(MI_RESULT_OK == selectorInitResult)
        Selector_Destroy(&sel);

    // Shutdown the network.
    Sock_Stop();
}
NitsEndTest

NitsTestWithSetup(TestTimeNow, TestSelectorSetup)
{
    MI_Uint64 t1 = 0, t2 = 0;

    TEST_ASSERT(PAL_TRUE == PAL_Time(&t1));

    // sleep 1 ms
    ut::sleep_ms( 1 );
    TEST_ASSERT(PAL_TRUE == PAL_Time(&t2));

    // expect difference to be 0.1 -  1 sec
    if ((t2-t1) <= 100 || (t2-t1) >= 1000000)
        std::cout << "warning: unexpected time diff; t1 " << t1 << "; t2 " << t2 << endl;

    // With VM-driven environment, timing becomes very tricky and un-reliable
    TEST_ASSERT(t2 > t1);
}
NitsEndTest

NitsTestWithSetup(TestSelectorTimeoutEvent, TestSelectorSetup)
{
    Selector sel;
    Sock lsock;
    MI_Result r;
    MI_Result selectorInitResult;

    // Initialize the network:
    Sock_Start();

    // Initialize the selector object.
    selectorInitResult = Selector_Init(&sel);
    if(!TEST_ASSERT(MI_RESULT_OK == selectorInitResult))
        goto TestCleanup;

    // Create listener socket:
    lsock = CreateListenerSock();
    
    // Add  handler for listener socket.
    {
        Handler* h = (Handler*)PAL_Calloc(1, sizeof(Handler));

        TEST_ASSERT(h);

        if(h == NULL)
        {
            Sock_Close(lsock);
            goto TestCleanup;
        }
        h->sock = lsock;
        h->mask = SELECTOR_READ;
        h->callback = TimeoutCallback;

        // Watch for connection requests.
        // 'add' will set timeout for 2 ms;
        r = Selector_AddHandler(&sel, h);
        TEST_ASSERT(r == MI_RESULT_OK);
    }

    r = Selector_Run(&sel, 1000*1000, MI_FALSE);
    TEST_ASSERT(s_timeout_called);
    // 'timeout' event on socekt is triggered na dremoves socket, so 
    // selector returns 'failed'
    TEST_ASSERT(r == MI_RESULT_FAILED);

TestCleanup:
    // Destroy the selector.
    if(selectorInitResult == MI_RESULT_OK)
        Selector_Destroy(&sel);

    // Shutdown the network.
    Sock_Stop();
}
NitsEndTest

NitsTestWithSetup(TestSelectorTimeoutWithNoSocketHandler, TestSelectorSetup)
{
    Selector sel;
    MI_Result r;
    MI_Result selectorInitResult;

    // Initialize the network:
    Sock_Start();

    // Initialize the selector object.
    selectorInitResult = Selector_Init(&sel);
    if(!TEST_ASSERT(MI_RESULT_OK == selectorInitResult))
        goto TestEnd;

    // Add  handler for listener socket.
    {
        Handler* h = (Handler*)PAL_Calloc(1, sizeof(Handler));

        TEST_ASSERT(h);

        if(h == NULL)
        {
            goto TestEnd;
        }
        h->sock = INVALID_SOCK;
        h->callback = TimeoutCallback;

        // 'add' will set timeout for 2 ms;
        r = Selector_AddHandler(&sel, h);
        TEST_ASSERT(r == MI_RESULT_OK);
    }

    s_timeout_called = false;
    r = Selector_Run(&sel, 1000*1000, MI_FALSE);
    TEST_ASSERT(s_timeout_called);
    // 'timeout' event on socekt is triggered na dremoves socket, so 
    // selector returns 'failed'
    TEST_ASSERT(r == MI_RESULT_FAILED);
TestEnd:
    // Destroy the selector.
    if(MI_RESULT_OK == selectorInitResult)
        Selector_Destroy(&sel);

    // Shutdown the network.
    Sock_Stop();
}
NitsEndTest

NitsTestWithSetup(TestSelectorStopRunning, TestSelectorSetup)
{
    Selector sel;
    MI_Result r;
    MI_Result selectorInitResult;

    // Initialize the network:
    Sock_Start();

    // Initialize the selector object.
    selectorInitResult = Selector_Init(&sel);
    if(!TEST_ASSERT(MI_RESULT_OK == selectorInitResult))
        goto TestEnd;

    // Add  that will call 'stop-running' from handler
    {
        Handler* h = (Handler*)PAL_Calloc(1, sizeof(Handler));

        TEST_ASSERT(h);
        if(h == NULL)
            goto TestEnd;

        h->sock = INVALID_SOCK;
        h->callback = _StopRunningCallback;

        // 'add' will set timeout for 2 ms;
        r = Selector_AddHandler(&sel, h);
        TEST_ASSERT(r == MI_RESULT_OK);
    }

    r = Selector_Run(&sel, 60 * 1000*1000, MI_FALSE);

    TEST_ASSERT(s_stoprunning_called);

    // Stop-running call should return OK
    TEST_ASSERT(r == MI_RESULT_OK);

TestEnd:
    // Destroy the selector.
    if(MI_RESULT_OK == selectorInitResult)
        Selector_Destroy(&sel);

    // Shutdown the network.
    Sock_Stop();
}
NitsEndTest

static Sock SockConnectLocal(unsigned short port)
{
    Sock sock;
    Addr addr;
    MI_Result r;

    Sock_Start();

    // Initialize address (connect using loopback).
    r = Addr_Init(&addr, "127.0.0.1", port, MI_FALSE);
    TEST_ASSERT(r == MI_RESULT_OK);

    // Create client socket.
    r = Sock_Create(&sock, MI_FALSE);
    TEST_ASSERT(r == MI_RESULT_OK);
 
    r = Sock_Connect(sock, &addr);
    TEST_ASSERT(r == MI_RESULT_OK);
    return sock;
}

BEGIN_EXTERNC
static void* MI_CALL _ConnectorThread(void* )
{
    // Initialize the network:
    Sock_Start();

    Sock s = SockConnectLocal(PORT);

    Sock_Close(s);

    // Shutdown the network.
    Sock_Stop();
    return 0;
}
END_EXTERNC

NitsTestWithSetup(TestSelectorWithIndefiniteTimeout, TestSelectorSetup)
{
    Selector sel;
    MI_Result r;
    MI_Result selectorInitResult;

    // Initialize the network:
    Sock_Start();

    // Initialize the selector object.
    selectorInitResult = Selector_Init(&sel);
    if(!TEST_ASSERT(MI_RESULT_OK == selectorInitResult))
        goto DestroySelector;

    // Add  that will call 'stop-running' from handler
    {
        Handler* h = (Handler*)PAL_Calloc(1, sizeof(Handler));

        TEST_ASSERT(h);

        if(h == NULL)
            goto DestroySelector;

        h->sock =  CreateListenerSock();;
        h->mask = SELECTOR_READ;
        h->callback = _StopRunningCallback;

        // 'add' will set timeout for 2 ms;
        r = Selector_AddHandler(&sel, h);
        TEST_ASSERT(r == MI_RESULT_OK);
    }

    Thread t;
    int threadCreationResult;

    // create a connector thread
    threadCreationResult = Thread_CreateJoinable(
        &t, (ThreadProc) _ConnectorThread, NULL, 0);
    TEST_ASSERT(MI_RESULT_OK == threadCreationResult);
    if(threadCreationResult != MI_RESULT_OK)
        goto DestroySelector;

    r = Selector_Run(&sel, TIME_NEVER, MI_FALSE);

    TEST_ASSERT(s_stoprunning_called);

    // Stop-running call should return OK
    TEST_ASSERT(r == MI_RESULT_OK);

    PAL_Uint32 ret;
    TEST_ASSERT(Thread_Join(&t, &ret) == 0);
    Thread_Destroy( &t );

DestroySelector:
    // Destroy the selector.
    if(MI_RESULT_OK == selectorInitResult)
        Selector_Destroy(&sel);

    // Shutdown the network.
    Sock_Stop();

}
NitsEndTest

#if defined(_MSC_VER)
/* Strange, but for this particular file VS compiler 
    thinks that 'catch' after 'try {setup()}' is unreachable 
    (which is true) */

/* warning C4702: unreachable code */
# pragma warning(disable : 4702)

#endif /* _MSC_VER */



