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

#ifndef _omi_sock_h
#define _omi_sock_h

#include "config.h"
#include <string.h>
#include <common.h>
#include "addr.h"

//#   if defined(CONFIG_POSIX)
//// readv/writev headers
//#       include <sys/uio.h>
//#   endif

BEGIN_EXTERNC

#if (!defined(SOCK_DEFINED))
#define SOCK_DEFINED
#if defined(CONFIG_OS_WINDOWS)
# if defined(_WIN64)
    typedef MI_Uint64 Sock;
# else
    typedef MI_Uint32 Sock;
# endif
# define INVALID_SOCK INVALID_SOCKET
#else
  typedef int Sock;
# define INVALID_SOCK ((Sock)-1)
#endif
#endif // SOCK_DEFINED

typedef struct _IOVec
{
    void *ptr;     /* Pointer to data.  */
    size_t len;     /* Length of data.  */
}
IOVec;

MI_Result Sock_Start();

void Sock_Stop();

MI_Result Sock_Create(
    Sock* sock,
    MI_Boolean is_ipv6);

MI_Result Sock_Close(
    Sock self);

MI_Result Sock_Bind(
    Sock self,
    const Addr* addr);

MI_Result Sock_Listen(
    Sock self);

MI_Result Sock_Accept(
    Sock self,
    Sock* sock,
    Addr* addr);

MI_Result Sock_Connect(
    Sock self,
    const Addr* addr);

MI_Result Sock_ReuseAddr(
    Sock self,
    MI_Boolean flag);

MI_Result Sock_SetBlocking(
    Sock self,
    MI_Boolean flag);

MI_Result Sock_SetNoDelay(
    Sock self,
    MI_Boolean flag);

MI_Result Sock_SetCloseOnExec(
    Sock self,
    MI_Boolean closeOnExec);

MI_Result Sock_Read(
    Sock self,
    void* data,
    size_t size,
    size_t* sizeRead);

MI_Result Sock_ReadV(
    Sock self,
    const IOVec* iov,
    size_t  iovcnt,
    size_t* sizeRead);

MI_Result Sock_Write(
    Sock self,
    const void* data,
    size_t size,
    size_t* sizeWritten);

MI_Result Sock_WriteV(
    Sock self,
    const IOVec* iov,
    size_t  iovcnt,
    size_t* sizeWritten);

MI_Result Sock_CreateListener(
    Sock* sock,
    const Addr* addr);

/* AF_LOCAL family */
MI_Result Sock_CreateLocalListener(
    Sock* sock,
    const char* addr);

/* AF_LOCAL, non-blocking, close-on-exec, connect */
MI_Result Sock_CreateLocalConnector(
    Sock* sock,
    const char* addr);

MI_Result Sock_CreateIPConnector(
    Sock* s,
    const char* hostAndPort);

MI_INLINE int Sock_GetLastError()
{
#if defined(CONFIG_OS_WINDOWS)
    return (int)GetLastError();
#else
    return (int)errno;
#endif
}

END_EXTERNC

#endif /* _omi_sock_h */
