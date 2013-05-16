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

#include "utils.h"
#include <ut/ut.h>
#include <io/io.h>
#include <base/paths.h>
#include <omiclient/client.h>
#include <iostream>

#if defined(CONFIG_OS_WINDOWS)
#include <process.h>
#else
#include <unistd.h>
#include <sys/wait.h>

static pid_t child;
#endif

using namespace std;

#define REQUEST_HEADER_FMT \
    "POST /wsman HTTP/1.1\r\n" \
    "Content-Length: %d\r\n"\
    "Connection: Keep-Alive\r\n"\
    "Content-Type: application/soap+xml;charset=UTF-8\r\n"\
    "Authorization:    Basic \t \tcm9vdDpPcHNNZ3IyMDA3UjI=\t \r\n"\
    "\r\n"

#define REQUEST_HEADER_FMT_UTF16 \
    "POST /wsman HTTP/1.1\r\n" \
    "Content-Length: %d\r\n"\
    "Connection: Keep-Alive\r\n"\
    "Content-Type: application/soap+xml;charset=UTF-16\r\n"\
    "Authorization:    Basic \t \tcm9vdDpPcHNNZ3IyMDA3UjI=\t \r\n"\
    "\r\n"
 
#define REQUEST_HEADER_MAX_SIZE sizeof(REQUEST_HEADER_FMT_UTF16)

Sock SockConnectLocal(unsigned short port)
{
    Sock sock;
    Addr addr;
    MI_Result r;

    Sock_Start();

    // Initialize address (connect using loopback).
    r = Addr_Init(&addr, "127.0.0.1", port, MI_FALSE);
    UT_ASSERT(r == MI_RESULT_OK);

    // Create client socket.
    r = Sock_Create(&sock, MI_FALSE);
    UT_ASSERT(r == MI_RESULT_OK);
 
    r = Sock_Connect(sock, &addr);
    UT_ASSERT(r == MI_RESULT_OK);
    return sock;
}

void SockSendRecvHTTP(
    Sock s,
    bool useUtf16HeaderAttribute,
    const string& request_body,
    string& response_header,
    string& response_body)
{
    // prepare data to send

    char currentLine[REQUEST_HEADER_MAX_SIZE + 10 /* content length */ ];

    size_t buf_size, sent = 0;
    MI_Result r;

    buf_size = (size_t)Snprintf(
        currentLine,
        sizeof(currentLine),
        (useUtf16HeaderAttribute ? REQUEST_HEADER_FMT_UTF16 : REQUEST_HEADER_FMT), 
        (int)request_body.size() );

    r = Sock_Write(s, currentLine, buf_size, &sent);
    UT_ASSERT (MI_RESULT_OK == r);
    UT_ASSERT (sent == buf_size);

    // body (if present)
    if (!request_body.empty())
    {
        sent = 0;
        r = Sock_Write(s, request_body.c_str(), request_body.size(), &sent);

        UT_ASSERT (MI_RESULT_OK == r);
        UT_ASSERT (sent == request_body.size());
    }

    // read resonse

    response_header.resize(16 * 1024);
    size_t read = 0, buf_read = 0;
    string::size_type pos_crcr;

    for (;;)
    {
        r = Sock_Read(s, &response_header[0], response_header.size() - buf_read, &read);
        UT_ASSERT (MI_RESULT_OK == r);

        buf_read += read;

        pos_crcr = response_header.find("\r\n\r\n");

        if (string::npos != pos_crcr)
        {
            response_header.resize(buf_read);
            break;
        }
    }

    response_body = response_header.substr(pos_crcr + 4);
    response_header = response_header.substr(0, pos_crcr);

    const char CONTENT_LEN[] = "Content-Length:";

    string::size_type pos_cl = response_header.find(CONTENT_LEN);
    size_t contentLength = 0;

    if (string::npos != pos_cl)
    {
        contentLength = atol(response_header.c_str() + pos_cl + sizeof(CONTENT_LEN)-1);
    }
    //cout << "cl: " << contentLength << endl;
    //cout << "resp header: " << response_header << endl << endl << "body: " << response_body << endl;

    while (response_body.size() < contentLength)
    {
        size_t old_size = response_body.size();
        response_body.resize(contentLength);

        r = Sock_Read(s, &response_body[0] + old_size, contentLength - old_size, &read);
        UT_ASSERT (MI_RESULT_OK == r);

        response_body.resize(old_size + read);
    }
    //cout << "resp header: " << response_header << endl << endl << "body: " << response_body << endl;
}



/* launching and terminating the server */
void StartServerAndConnect(
    bool ignoreAuth,
    ProtocolCallback callback,
    Protocol** protocol)
{
    const char* path = GetPath(ID_SERVERPROGRAM);
    char http[32];
    char https[32];
    string socketFile = GetPath(ID_SOCKETFILE);

    Snprintf(http, sizeof(http),"%d", ut::getUnittestPortNumberWSMANHTTP());
    Snprintf(https, sizeof(https),"%d", ut::getUnittestPortNumberWSMANHTTPS());

    std::string v;

    if (!ut::testGetAttr("skipServer", v))
    {

#if defined(CONFIG_OS_WINDOWS)
    MI_UNUSED(ignoreAuth);

    intptr_t res = _spawnl(_P_NOWAIT, path, path, "--stopnoop", "--rundir", 
        GetPath(ID_PREFIX), 
        "--httpport", http,
        "--httpsport", https,
        "--livetime", "300",
        NULL);
    res = res;
#else
    child = fork();
    if (!child)
    {
        execl(path, path, "--stopnoop", 
            ignoreAuth ? "--ignoreAuthentication" : "--stopnoop", 
            "--rundir", GetPath(ID_PREFIX), 
            "--httpport", http,
            "--httpsport", https,
#if 0
            "--httptrace",
            "--loglevel", "4",
            "-l",
#endif
            "--socketfile", socketFile.c_str(),
            "--livetime", "300",
            NULL );
        exit(1); // never get here
    }
#endif
    }


    // wait for server to start
    // trying to connect in a loop:
    // since connect may fail quickly if server is not running
    // keep doing it in  a loop
    int attempt;

    ZChar sockfile[MAX_PATH_SIZE];
    ZStrlcpy(sockfile, socketFile.c_str(), MI_COUNT(sockfile));

    for ( attempt = 0; attempt < 400; attempt++ )
    {
        mi::Client cl;
        const MI_Uint64 TIMEOUT = 1 * 1000 * 1000;

#if defined(CONFIG_OS_WINDOWS)
        if (cl.Connect(MI_T("7777"), MI_T("unittest"), MI_T("unittest"), TIMEOUT))
#else
        if (cl.Connect(sockfile, USER_Z, PASSWORD_Z, TIMEOUT))
#endif
            break;

        ut::sleep_ms(10);
    }

    if ( attempt == 400 )
    {
        std::cout << "Warning: unable to connect to the server!\n";
    }

    Protocol_New_Connector(
        protocol, 
        0, 
        socketFile.c_str(), 
        callback, 
        0,
        0, 
        0, 
        USER, 
        PASSWORD);
}

void StopServerAndDisconnect(
    Protocol** protocol)
{
    NoOpReq* rqt;
    std::string v;

    if (ut::testGetAttr("skipServer", v))
    {
        Protocol_Delete(*protocol);
        *protocol = 0;
        return ;
    }

    rqt = NoOpReq_New(0);
    if (rqt)
    {
        Protocol_Send(*protocol, &rqt->base);
        NoOpReq_Release(rqt);
    }
    Protocol_Run(*protocol, 20000);

    Protocol_Delete(*protocol);
    *protocol = 0;

#if !defined(CONFIG_OS_WINDOWS)
    int attempt = 0;
    do {
        usleep(20000);
        attempt++;

        if (attempt > 100 )
        {
            cout << "Warning: unable to stop the server!\n";
            break;
        }
    }
    while( child != waitpid(child, 0, WNOHANG));
#endif
}
