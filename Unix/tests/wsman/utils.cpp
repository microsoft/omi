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
#include "utils.h"
#include <ut/ut.h>
#include <pal/format.h>
#include <base/paths.h>
#include <base/log.h>
#include <base/pidfile.h>
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

#define REQUEST_HEADER_FMT_WINRM \
    "POST /wsman HTTP/1.1\r\n" \
    "Host: localhost\r\n" \
    "User-Agent: Microsoft WinRM Client\r\n" \
    "Content-Length: %d\r\n"\
    "Connection: Keep-Alive\r\n"\
    "Content-Type: application/soap+xml;charset=UTF-8\r\n"\
    "Authorization:    Basic \t \tcm9vdDpPcHNNZ3IyMDA3UjI=\t \r\n"\
    "\r\n"

#define REQUEST_HEADER_FMT \
    "POST /wsman HTTP/1.1\r\n" \
    "Host: localhost\r\n" \
    "Content-Length: %d\r\n"\
    "Connection: Keep-Alive\r\n"\
    "Content-Type: application/soap+xml;charset=UTF-8\r\n"\
    "Authorization:    Basic \t \tcm9vdDpPcHNNZ3IyMDA3UjI=\t \r\n"\
    "\r\n"

#define REQUEST_HEADER_FMT_UTF16 \
    "POST /wsman HTTP/1.1\r\n" \
    "Host: localhost\r\n" \
    "Content-Length: %d\r\n"\
    "Connection: Keep-Alive\r\n"\
    "Content-Type: application/soap+xml;charset=UTF-16\r\n"\
    "Authorization:    Basic \t \tcm9vdDpPcHNNZ3IyMDA3UjI=\t \r\n"\
    "\r\n"

#define REQUEST_HEADER_FMT_UTF16_WINRM \
    "POST /wsman HTTP/1.1\r\n" \
    "Host: localhost\r\n" \
    "User-Agent: Microsoft WinRM Client\r\n" \
    "Content-Length: %d\r\n"\
    "Connection: Keep-Alive\r\n"\
    "Content-Type: application/soap+xml;charset=UTF-16\r\n"\
    "Authorization:    Basic \t \tcm9vdDpPcHNNZ3IyMDA3UjI=\t \r\n"\
    "\r\n"

#define REQUEST_HEADER_MAX_SIZE sizeof(REQUEST_HEADER_FMT_UTF16_WINRM)

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
    string& response_body,
    bool useWinRMUserAgent)
{
    // prepare data to send

    char currentLine[REQUEST_HEADER_MAX_SIZE + 10 /* content length */ ];

    size_t buf_size, sent = 0;
    MI_Result r;

    const char *requestHeader = NULL;

    if(useUtf16HeaderAttribute)
    {
        if(useWinRMUserAgent)
            requestHeader = REQUEST_HEADER_FMT_UTF16_WINRM;
        else
            requestHeader = REQUEST_HEADER_FMT_UTF16;
    }
    else
    {
        if(useWinRMUserAgent)
            requestHeader = REQUEST_HEADER_FMT_WINRM;
        else
            requestHeader = REQUEST_HEADER_FMT;
    }

    buf_size = (size_t)Snprintf(
        currentLine,
        sizeof(currentLine),
        requestHeader,
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

    // read response

    response_header.resize(16 * 1024);
    size_t read = 0, buf_read = 0;
    string::size_type pos_crcr;

    for ( ; ; )
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
    Strand* strand,
    ProtocolSocketAndBase** protocol)
{
    const char* path = OMI_GetPath(ID_SERVERPROGRAM);
    char http[32];
    char https[32];
    string socketFile = OMI_GetPath(ID_SOCKETFILE);

    Snprintf(http, sizeof(http),"%d", ut::getUnittestPortNumberWSMANHTTP());
    Snprintf(https, sizeof(https),"%d", ut::getUnittestPortNumberWSMANHTTPS());

    std::string v;

    if (!ut::testGetAttr("skipServer", v))
    {

#if defined(CONFIG_OS_WINDOWS)
    MI_UNUSED(ignoreAuth);

    intptr_t res = _spawnl(_P_NOWAIT, path, path, "--stopnoop", "--rundir",
        OMI_GetPath(ID_PREFIX),
        "--httpport", http,
        "--httpsport", https,
        "--livetime", "300",
        "--loglevel", Log_GetLevelString(Log_GetLevel()),        
        NULL);
    res = res;
#else
    child = fork();
    if (!child)
    {        
        execl(path, path, "--stopnoop",
            ignoreAuth ? "--ignoreAuthentication" : "--stopnoop",
            "--rundir", OMI_GetPath(ID_PREFIX),
            "--httpport", http,
            "--httpsport", https,
            "--loglevel", Log_GetLevelString(Log_GetLevel()),
#if 0            
            "--httptrace",
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

    ZChar sockfile[PAL_MAX_PATH_SIZE];
    TcsStrlcpy(sockfile, socketFile.c_str(), MI_COUNT(sockfile));

    for (attempt = 0; attempt < 400; attempt++)
    {
        mi::Client cl;
        const MI_Uint64 TIMEOUT = 1 * 1000 * 1000;  // 1 second

#if defined(CONFIG_OS_WINDOWS)
        if (cl.Connect(MI_T("7777"), MI_T("unittest"), MI_T("unittest"), TIMEOUT))
#else
        if (cl.Connect(sockfile, USER_Z, PASSWORD_Z, TIMEOUT))
#endif
            break;

        ut::sleep_ms(10);
    }

    if (attempt == 400)
    {
        std::cout << "Warning: unable to connect to the server!\n";
        DEBUG_ASSERT( MI_FALSE );
        UT_ASSERT( MI_FALSE );
    }

    InteractionOpenParams params;
    
    Strand_OpenPrepare(strand,&params,NULL,NULL,MI_TRUE);

    MI_Result result = ProtocolSocketAndBase_New_Connector(
                        protocol,
                        0,
                        socketFile.c_str(),
                        &params,
                        USER,
                        PASSWORD );

    UT_ASSERT( MI_RESULT_OK == result );
}

void StopServerAndDisconnect(
    Strand* strand,
    ProtocolSocketAndBase** protocol)
{
    NoOpReq* rqt;
    std::string v;

    if (!protocol || !*protocol)
        return;

    if (ut::testGetAttr("skipServer", v))
    {
        ProtocolSocketAndBase_ReadyToFinish(*protocol);
        *protocol = 0;
        return ;
    }

    rqt = NoOpReq_New(0);
    if (rqt)
    {
        Strand_SchedulePost(strand, &rqt->base.base);
        NoOpReq_Release(rqt);
    }
    Protocol_Run(&((*protocol)->internalProtocolBase), 10 * SELECT_BASE_TIMEOUT_MSEC * 1000);
    
    if (strand->info.opened && !strand->info.thisClosedOther)
    {
        Strand_ScheduleClose(strand);
        Protocol_Run(&((*protocol)->internalProtocolBase), 10 * SELECT_BASE_TIMEOUT_MSEC * 1000);
    }

    ProtocolSocketAndBase_ReadyToFinish(*protocol);
    *protocol = NULL;

#if !defined(CONFIG_OS_WINDOWS)
    int attempt = 0;
    do {
        usleep(20000);
        attempt++;

        if (attempt > 100)
        {
            int pid;

            if (PIDFile_Read(&pid) < 0)
            {
                pid = -1;
                break;
            }

            cout << "Warning: unable to stop the server for PID " << pid << std::endl;

            // TODO: If a test cannot send the noop message to the server, it will not stop.
            // This is way to force the server to stop by spawing another server that sends
            // SIGTERM to the running server, which causes it to exit.
            // Actual issue with the test needs to be investigated and fixed. Bug 530733 tracks this.
            const char* path = OMI_GetPath(ID_SERVERPROGRAM);
            static pid_t stoppingChild = fork();

            if (!stoppingChild)
            {        
                execl(path, path, "-s", NULL);
                exit(1); // never get here
            }           
            sleep(1);

            // At this point, if the server did not stop, it is hung, so no cleanup can be done.
            // Kill the server process.
            char buf[64];
            sprintf(buf, "ps -p %d && kill -9 %d", pid, pid);
            system(buf);
            sleep(1);
        }
    }
    while (child != waitpid(child, 0, WNOHANG));
#endif
}

string CreatePullRequestXML(const string& ctxID)
{
    string res = 
"<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""
"   xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
"   xmlns:n=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\""
"   xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\">"
"<s:Header>"
"<a:To>http://linux-22kv:22000/wsman</a:To>"
"<w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/"
"cn"
"</w:ResourceURI>"
"<a:ReplyTo>"
"<a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address>"
"</a:ReplyTo>"
"<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/enumeration/Pull</a:Action>"
"<w:MaxEnvelopeSize s:mustUnderstand=\"true\">102400</w:MaxEnvelopeSize>"
"<a:MessageID>uuid:FEF3DF41-FFEC-4ABE-ADFC-A8305DAB71C9</a:MessageID>"
"<w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><w:SelectorSet>"
"<w:Selector Name=\"__cimnamespace\">"
"ns"
"</w:Selector>"
"</w:SelectorSet>"
"<w:OperationTimeout>PT60.000S</w:OperationTimeout>"
"</s:Header>"
"<s:Body>"
"<n:Pull>"
"<wsen:EnumerationContext xmlns:wsen=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\">";
    
    res += ctxID;
    res += 
"</wsen:EnumerationContext>"
"<n:MaxElements>10000</n:MaxElements>"
"</n:Pull>"
"</s:Body></s:Envelope>"
;
 
    return res;
}

string GetCtxID(const string& s)
{
    // look for <wsen:EnumerationContext>NNN</wsen:EnumerationContext> 
    // and return NNN (or empty string if not found)
    string::size_type pos = s.find("<wsen:EnumerationContext>");
    string::size_type posEnd = s.find("</wsen:EnumerationContext>");

    if ( pos == string::npos ||
        posEnd == string::npos ||
        pos > posEnd )
        return string();

    return s.substr(pos + 25, posEnd - pos -25);
}

// Generic parsing function for extracting elements between tags
string GetElementByTag(const string& startTag, const string& endTag, const string& s)
{
    // look for <StartTag>element<EndTag> 
    // and return the value (or empty string if not found)
    string::size_type pos = s.find(startTag);
    string::size_type posEnd = s.find(endTag);

    if ( pos == string::npos ||
        posEnd == string::npos ||
        pos > posEnd )
        return string();

    return s.substr(pos + startTag.length(), posEnd - pos - startTag.length());
}

