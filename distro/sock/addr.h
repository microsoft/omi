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

#ifndef _osc_addr_h
#define _osc_addr_h

#include "config.h"
#include <string.h>
#include <common.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

BEGIN_EXTERNC

#if defined(CONFIG_OS_WINDOWS)
typedef struct _Addr
{
    MI_Uint8 sock_addr[140];
}
#else
typedef struct _Addr
{
    MI_Boolean is_ipv6;                 // the information from sa_family from u.sock_addr
    MI_Uint16 port_high_endian;         // a copy of sa_port from u.sock_addr
    MI_Uint16 sock_addr_size;           // a copy of af_size from u.sock_addr
    union
    {
        struct sockaddr sock_addr;      // either a sockaddr_in or a sockaddr_in6
        unsigned char padding[128];     // the padding used in Linux, > sizeof (sockaddr_in6)
	} u;
}
Addr;
#endif

MI_Result Addr_Init(
    Addr* self,                         // the address structure for the result
    const char* host,                   // the hostname part of a URL
    unsigned short port,                // the port
    MI_Boolean useSecondaryAddr);       // MI_FALSE to use preferred protocol, MI_TRUE to use secondary protocol, if available

void Addr_InitAny(
    Addr* self,                         // the address structure for the result: IPv4 127.0.0.1
    unsigned short port);               // the port

END_EXTERNC

#endif /* _osc_addr_h */
