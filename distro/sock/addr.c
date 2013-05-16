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

// #define ENABLE_TRACING
// #define TRACING_LEVEL 4
#include <logging.h>

#if defined(CONFIG_OS_WINDOWS)
typedef unsigned long InAddr;
typedef unsigned short InAddr6[8];
#else
typedef struct in_addr InAddr;
typedef struct in6_addr InAddr6;
#endif

/* disabling IPv6 OACR warnings - D3M bug 52 */

MI_Result Addr_Init(
    Addr* self,
    const char* host,
    unsigned short port,
    MI_Boolean useSecondaryAddr)
{
    struct addrinfo hints;
    struct addrinfo* addr_info;
    int error_no;

    LOGD2((ZT("Addr_Init - Creating an address for host: %s, port: %d"), host, port));

    // set hints and get the primary address
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;        // AF_UNSPEC means use preferred protocol
    error_no = getaddrinfo(host, NULL, &hints, &addr_info);
    if (error_no != 0)
    {
        LOGW2((ZT("Addr_Init - getaddrinfo of %s returned error: %d, (%s): %u"), host, error_no, strerror(error_no)));
        return MI_RESULT_FAILED;
    }

    if (useSecondaryAddr)
    {                                   // try again with the other address family if secondary protocol is wanted
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_family = addr_info->ai_family == AF_INET6 ? AF_INET : AF_INET6;
        error_no = getaddrinfo(host, NULL, &hints, &addr_info);
        if (error_no != 0)
        {
            LOGE2((ZT("Addr_Init - getaddrinfo of %s returned error: %d, (%s): %u"), host, error_no, strerror(error_no)));
            return MI_RESULT_FAILED;
        }
	}
    if (addr_info->ai_family == AF_INET6)
    {
        struct sockaddr_in6* addr6 = (struct sockaddr_in6*)(addr_info->ai_addr->sa_data - sizeof (unsigned short));
        addr6->sin6_port = htons(port);
	}
    else
    {
        struct sockaddr_in* addr4 = (struct sockaddr_in*)(addr_info->ai_addr->sa_data - sizeof (unsigned short));
        addr4->sin_port = htons(port);
	}
    memset(self->u.padding, 0, sizeof self->u.padding);
    memcpy(&self->u.sock_addr, addr_info->ai_addr, (size_t)addr_info->ai_addrlen);

    // Set the duplicate copies of family, port and socket type
    self->sock_addr_size = addr_info->ai_addrlen;
    self->port_high_endian = htons(port);
    self->is_ipv6 = (addr_info->ai_family == AF_INET6);
#if TRACING_LEVEL > 3
    if (addr_info->ai_family == AF_INET6)
    {
        struct sockaddr_in6* addr6 = (struct sockaddr_in6*)&self->u.sock_addr;
        LOGD2((ZT("Addr_Init - IPv6 address: %X:%X:%X:%X:%X:%X:%X:%X, port: %u"),
                (unsigned int)ntohs(*(unsigned short*)&addr6->sin6_addr),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 1)),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 2)),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 3)),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 4)),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 5)),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 6)),
                (unsigned int)ntohs(*((unsigned short*)&addr6->sin6_addr + 7)),
                (unsigned int)ntohs(addr6->sin6_port)));
    }
    else
    {
        struct sockaddr_in* addr4 = (struct sockaddr_in*)&self->u.sock_addr;
        LOGD2((ZT("Addr_Init - IPv4 address: %u.%u.%u.%u, port: %u"),
                (unsigned int)*((unsigned char*)&addr4->sin_addr.s_addr + 0),
                (unsigned int)*((unsigned char*)&addr4->sin_addr.s_addr + 1),
                (unsigned int)*((unsigned char*)&addr4->sin_addr.s_addr + 2),
                (unsigned int)*((unsigned char*)&addr4->sin_addr.s_addr + 3),
                (unsigned int)ntohs(addr4->sin_port)));
    }
#endif
    freeaddrinfo(addr_info);
    return MI_RESULT_OK;
}

void Addr_InitAny(
    Addr* self,
    unsigned short port)
{
    LOGD2((ZT("Addr_InitAny - Creating a loopback address for port %d"), port));
    struct sockaddr_in* addr4;
    unsigned int v4addr;

    memset((char*)self, 0, sizeof (Addr));

    // set the fields in the header
    self->sock_addr_size = 16;
    self->port_high_endian = htons(port);
    self->is_ipv6 = MI_FALSE;

    // set the fields in the bind address structure
    addr4 = (struct sockaddr_in*)&self->u.sock_addr;
    addr4->sin_family = AF_INET;
    addr4->sin_port = htons(port);
    v4addr = htonl(INADDR_ANY);
    memcpy(&addr4->sin_addr.s_addr, &v4addr, sizeof (uint32_t));

#if TRACING_LEVEL > 3
    LOGD2((ZT("Addr_InitAny - IPv4 address: %u.%u.%u.%u, port: %u"),
                (unsigned int)*((unsigned char*)&addr4->sin_addr.s_addr + 0),
                (unsigned int)*((unsigned char*)&addr4->sin_addr.s_addr + 1),
                (unsigned int)*((unsigned char*)&addr4->sin_addr.s_addr + 2),
                (unsigned int)*((unsigned char*)&addr4->sin_addr.s_addr + 3),
                (unsigned int)ntohs(addr4->sin_port)));
#endif

    return;
}
