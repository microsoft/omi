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

#ifndef _omi_addr_h
#define _omi_addr_h

#include "config.h"
#include <string.h>
#include <common.h>

BEGIN_EXTERNC

#if !defined(CONFIG_OS_WINDOWS)
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
#else
# include <winsock.h>
#endif

#ifdef _PREFAST_
# pragma prefast (push)
# pragma prefast (disable: 24002)
#endif

typedef struct _Addr
{
    union padded_address
    {
        struct sockaddr sock_addr;      /* either a sockaddr_in or a sockaddr_in6 */
        unsigned char padding[128];     /* the padding used in Linux, > sizeof (sockaddr_in6) */
    } u;
    MI_Boolean is_ipv6;                 /* MI_TRUE if sa_family from u.sock_addr is AF_INET6 */
    MI_Uint16 port_high_endian;         /* a copy of sa_port from u.sock_addr */
    MI_Uint16 sock_addr_size;           /* a copy of af_size from u.sock_addr */
}
Addr;

#ifdef _PREFAST_
# pragma prefast (pop)
#endif

MI_Result Addr_Init(
    Addr* self,
    const char* host,
    unsigned short port,
    MI_Boolean useSecondaryAddr);

void Addr_InitAny(
    Addr* self,
    unsigned short port);

END_EXTERNC

#endif /* _omi_addr_h */
