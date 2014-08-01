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

#include "addr.h"
#include <ctype.h>
#include <string.h>

// #define ENABLE_TRACING 1

/* Include network headers */
#if defined CONFIG_OS_WINDOWS

# include <winsock2.h>
  typedef unsigned long InAddr;

#else

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
  typedef in_addr_t InAddr;

#endif

MI_Result Addr_Init(
    Addr* self,
    const char* host,
    unsigned short port,
    MI_Boolean useSecondaryAddr)
{
#if defined CONFIG_OS_WINDOWS

/* disabling IPv6 OACR warnings - D3M bug 52 */

# ifdef _PREFAST_
#  pragma prefast (push)
#  pragma prefast (disable: 24001)
#  pragma prefast (disable: 24002)
#  pragma prefast (disable: 38026)
# endif
    struct sockaddr_in* sockaddr = (struct sockaddr_in*)self;

    /* Handle host name */
    const struct hostent* p = gethostbyname((char*)host);
    if (p == NULL)
        return MI_RESULT_FAILED;

    /* no support for IPv6 on Windows */
    if (useSecondaryAddr)
        return MI_RESULT_FAILED;

    /* Clear address */
    memset(self, 0, sizeof (Addr));

    /* set up values */
    sockaddr->sin_family = p->h_addrtype;
    self->is_ipv6 = MI_FALSE;
    self->sock_addr_size = sizeof (struct sockaddr_in);
    memcpy(&sockaddr->sin_addr, p->h_addr, p->h_length);

    /* Set the port */
    sockaddr->sin_port = htons(port);
    self->port_high_endian = htons(port);
    return MI_RESULT_OK;

# ifdef _PREFAST_
#  pragma prefast (pop)
# endif

#else /* defined CONFIG_OS_WINDOWS */

    struct addrinfo hints;
    struct addrinfo *addr_info, *rp;
    int error_no;

    /* set hints and get the primary address */
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;        /* AF_UNSPEC means use preferred protocol */
    error_no = getaddrinfo(host, NULL, &hints, &addr_info);
    if (error_no != 0)
        return MI_RESULT_FAILED;

    rp = addr_info;
    if (useSecondaryAddr && NULL != addr_info->ai_next)
    {
        // Advance to the next entry in the chain
        rp = rp->ai_next;
    }
    else if (useSecondaryAddr)
    {
        // No secondary address exists.
        return MI_RESULT_FAILED;
    }

    if (rp->ai_family == AF_INET6)
    {
        struct sockaddr_in6 * addr6 = (struct sockaddr_in6 *)(rp->ai_addr);
        // struct sockaddr_in6* addr6 = (struct sockaddr_in6*)(addr_info->ai_addr->sa_data - sizeof (unsigned short));
        addr6->sin6_port = htons(port);
    }
    else
    {
        struct sockaddr_in * addr4 = (struct sockaddr_in *)(rp->ai_addr);
        // struct sockaddr_in* addr4 = (struct sockaddr_in*)(addr_info->ai_addr->sa_data - sizeof (unsigned short));
        addr4->sin_port = htons(port);
    }

    memset(self->u.padding, 0, sizeof self->u.padding);
    memcpy(&self->u.sock_addr, rp->ai_addr, (size_t)rp->ai_addrlen);

    /* Set the duplicate copies of family, port and socket type */
    self->sock_addr_size = rp->ai_addrlen;
    self->port_high_endian = htons(port);
    self->is_ipv6 = (rp->ai_family == AF_INET6);

#if defined ENABLE_TRACING
    if (rp->ai_family == AF_INET6)
    {
        struct sockaddr_in6* addr6 = (struct sockaddr_in6*)&self->u.sock_addr;
        fprintf(stderr, "Addr_Init - IPv6 address: %X:%X:%X:%X:%X:%X:%X:%X, port: %u\n",
                (unsigned int)ntohs(*(unsigned short*)&addr6->sin6_addr),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 1)),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 2)),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 3)),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 4)),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 5)),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 6)),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 7)),
                (unsigned int)ntohs(addr6->sin6_port));
    }
    else
    {
        struct sockaddr_in* addr4 = (struct sockaddr_in*)&self->u.sock_addr;

        fprintf(stderr, "Addr_Init - IPv4 address: %u.%u.%u.%u, port: %u\n",
               (unsigned int)*((unsigned char*)&addr4->sin_addr.s_addr + 0),
               (unsigned int)*((unsigned char*)&addr4->sin_addr.s_addr + 1),
               (unsigned int)*((unsigned char*)&addr4->sin_addr.s_addr + 2),
               (unsigned int)*((unsigned char*)&addr4->sin_addr.s_addr + 3),
               (unsigned int)ntohs(addr4->sin_port));
    }
#endif /* defined(ENABLE_TRACING) */
    freeaddrinfo(addr_info);
    return MI_RESULT_OK;

#endif /* defined CONFIG_OS_WINDOWS ... else */
}

void Addr_InitAny(
    Addr* self,
    unsigned short port)
{
#ifdef _PREFAST_
# pragma prefast (push)
# pragma prefast (disable: 24002)
#endif
    struct sockaddr_in* addr4;
    MI_Uint32 v4addr;

    memset((char*)self, 0, sizeof (Addr));

    /* set the fields in the header */
    self->sock_addr_size = (MI_Uint16)sizeof (struct sockaddr_in);
    self->port_high_endian = htons(port);
    self->is_ipv6 = MI_FALSE;

    /* set the fields in the bind address structure */
    addr4 = (struct sockaddr_in*)&self->u.sock_addr;
    addr4->sin_family = AF_INET;
    addr4->sin_port = htons(port);
    v4addr = htonl(INADDR_ANY);
    memcpy(&addr4->sin_addr.s_addr, &v4addr, sizeof (MI_Uint32));
}

#ifdef _PREFAST_
#pragma prefast (pop)
#endif
