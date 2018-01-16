/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_addr_h
#define _omi_addr_h

#include "config.h"
#include <string.h>
#include <common.h>

BEGIN_EXTERNC

# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>

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
