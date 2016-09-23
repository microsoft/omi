/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _unittest_utility_h
#define _unittest_utility_h

#include <sock/sock.h>
#include <protocol/protocol.h>
#include <string>
#include <wsman/wsman.h>

Sock SockConnectLocal(
    unsigned short port);

void SockSendRecvHTTP(
    Sock sock,
    bool useUtf16HeaderAttribute,
    const std::string& request_body,
    std::string& response_header,
    std::string& response_body,
    bool useWinRMUserAgent = false);


/* launching and terminating the server */
/* starts server (with or without ignoreAuth option dependin on flag)
    and creates new connector to it */
#define USER "omi"
#define PASSWORD "CfgMgr2011"
#define USER_Z MI_T("omi")
#define PASSWORD_Z MI_T("CfgMgr2011")

void StartServerAndConnect(
    bool ignoreAuth,
    Strand* strand,
    ProtocolSocketAndBase** protocol);

void StopServerAndDisconnect(
    Strand* strand,
    ProtocolSocketAndBase** protocol);

std::string CreatePullRequestXML(
    const std::string& ctxID);

std::string GetCtxID(
    const std::string& s);

std::string GetElementByTag(
    const std::string& startTag,
    const std::string& endTag,
    const std::string& s);

MI_Result StartWSManInproc(OpenCallback callback, void* callbackData, WSMAN_Options* options = 0);
void StopWSManInproc();

#endif /* _unittest_utility_h */
