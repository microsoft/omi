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

#include "sock.h"
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
# include <signal.h>
// readv/writev headers
# include <sys/uio.h>

# include <sys/socket.h>
# include <sys/un.h>
# include <unistd.h>
# include <sys/stat.h>
#endif

#include <base/log.h>
#include <pal/strings.h>
#include <pal/format.h>

// #define ENABLE_TRACING 1
#ifdef ENABLE_TRACING
# define TRACING_LEVEL 4
# include <deprecated/logging/logging.h>
#else
# define LOGE2(a)
# define LOGW2(a)
# define LOGD2(a)
# define LOGX2(a)
#endif

#define MINSOCKBUFSIZE 4096

/*
**==============================================================================
**
** Local definitions.
**
**==============================================================================
*/

#if defined(CONFIG_OS_WINDOWS)
typedef int socklen_t;
#endif

MI_INLINE int _GetErrorCode()
{
#if defined(CONFIG_OS_WINDOWS)
    return WSAGetLastError();
#else
    return errno;
#endif
}

MI_INLINE int _TestWOULDBLOCK()
{
#if defined(CONFIG_OS_WINDOWS)
    return WSAGetLastError() == WSAEWOULDBLOCK;
#else
    return errno == EWOULDBLOCK || errno == EINPROGRESS;
#endif
}

MI_INLINE int _TestEAGAIN()
{
#if defined(CONFIG_OS_WINDOWS)
    return 0;
#else
    return errno == EAGAIN;
#endif
}

MI_INLINE int _TestEINTR()
{
#if defined(CONFIG_OS_WINDOWS)
    return WSAGetLastError() == WSAEINTR;
#else
    return errno == EINTR;
#endif
}

MI_INLINE void _LogSockWriteError()
{
#if defined(CONFIG_OS_WINDOWS)
#else
    trace_SockWrite_Failed(errno);
#endif
}

MI_INLINE int _Read(Sock sock, void* data, size_t size)
{
#if defined(CONFIG_OS_WINDOWS)
    return recv(sock, data, (int)size, 0);
#else
    int n = read(sock, data, size);
    if (n < 0)
    {
        if (errno == EAGAIN)
            LOGD2((ZT("_Read - read failed with EAGAIN. socket: %d"), sock));
        else
            LOGE2((ZT("_Read - read failed. socket: %d, errno: %d (%s)"), sock, errno, strerror(errno)));
    }
    return n;
#endif
}

MI_INLINE int _Write(Sock sock, const void* data, size_t size)
{
#if defined(CONFIG_OS_WINDOWS)
    return send(sock, data, (int)size, 0);
#else
    int n = write(sock, data, size);
    if (n < 0)
    {
        LOGE2((ZT("_Write - write failed. socket: %d, errno: %d (%s)"), sock, errno, strerror(errno)));
    }
    return n;
#endif
}

MI_INLINE int _ReadV(Sock sock, const IOVec* iov, size_t  iovcnt)
{
#if defined(CONFIG_OS_WINDOWS)
    int res = 0;
    int total = 0;
    size_t index = 0;

    for ( ; index < iovcnt; index++)
    {
        res = recv(sock, iov[index].ptr, (int)iov[index].len, 0);

        if (res < 0 && 0 == total)
            return res;

        if (res < 0)
            return total;

        total += res;

        if (res == 0 || (size_t)res != iov[index].len)
            return total;
    }
    return total;
#else
    return readv(sock, (struct iovec*)iov, iovcnt);
#endif
}

MI_INLINE int _WriteV(Sock sock, const IOVec* iov, size_t  iovcnt)
{
#if defined(CONFIG_OS_WINDOWS)
    int res = 0;
    int total = 0;
    size_t index = 0;

    for (; index < iovcnt; index++)
    {
        res = send(sock, iov[index].ptr, (int)iov[index].len, 0);
        if (res < 0 && 0 == total)
            return res;

        if (res < 0)
            return total;

        total += res;

        if (res == 0 || (size_t)res != iov[index].len)
            return total;
    }
    return total;
#else
    return writev(sock, (struct iovec*)iov, iovcnt);
#endif
}

/*
**==============================================================================
**
** Public definitions.
**
**==============================================================================
*/

MI_Result Sock_Start()
{
#if defined(CONFIG_OS_WINDOWS)
    WORD version = MAKEWORD(2, 0);
    WSADATA data;
    int rc;

    rc = WSAStartup (version, &data);

    if (rc != 0)
        return MI_RESULT_FAILED;

#else
    /* ignore PIPE signal */
    struct sigaction sig_acts;

    sig_acts.sa_handler = SIG_IGN;
    sigfillset(&(sig_acts.sa_mask));
    sig_acts.sa_flags = 0;

    sigaction(SIGPIPE, &sig_acts, NULL);

#endif /* CONFIG_OS_WINDOWS */
    return MI_RESULT_OK;
}

void Sock_Stop()
{
#if defined(CONFIG_OS_WINDOWS)
    WSACleanup();
#endif /* CONFIG_OS_WINDOWS */
}

MI_Result Sock_Create(
    Sock* sock,
    MI_Boolean is_ipv6)
{
    *sock = socket(is_ipv6 ? AF_INET6 : AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*sock == INVALID_SOCK)
        return MI_RESULT_FAILED;

    if (MI_RESULT_OK != Sock_SetCloseOnExec(*sock, MI_TRUE))
        trace_fcntl_failed(errno);

    return MI_RESULT_OK;
}

MI_Result Sock_Close(Sock self)
{
    int status;
#if defined(CONFIG_OS_WINDOWS)
    status = closesocket(self);
#else
    status = close(self);
#endif
    trace_Sock_Close((int)self);
    return status == 0 ? MI_RESULT_OK : MI_RESULT_FAILED;
}

MI_Result Sock_Bind(
    Sock self,
    const Addr* addr)
{
    int r;

    r = bind(self, &addr->u.sock_addr, (socklen_t)addr->sock_addr_size);
    if (r != 0)
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

MI_Result Sock_Listen(Sock self)
{
    int r;

    r = listen(self, 15);

    if (r != 0)
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

MI_Result Sock_Accept(
    Sock self,
    Sock* sock,
    Addr* addr)
{
    socklen_t addrlen = sizeof(*addr);

    *sock = accept(self, (struct sockaddr*)addr, &addrlen);

    if (*sock == -1)
    {
        if (_TestWOULDBLOCK() || _TestEAGAIN())
            return MI_RESULT_WOULD_BLOCK;
        else
            return MI_RESULT_FAILED;
    }

    if (MI_RESULT_OK != Sock_SetCloseOnExec(*sock,MI_TRUE))
    {
        trace_fcntl_failed(errno);
    }
    trace_Socket_Accept((int)*sock);
    return MI_RESULT_OK;
}

MI_Result Sock_SetCloseOnExec(
    Sock self,
    MI_Boolean closeOnExec)
{
#if defined(CONFIG_OS_WINDOWS)
    MI_UNUSED(self);
    MI_UNUSED(closeOnExec);
#else
    int sock_flags;
    if ((sock_flags = fcntl(self, F_GETFD, 0)) < 0)
        return MI_RESULT_FAILED;

    if (closeOnExec)
        sock_flags |= FD_CLOEXEC;
    else
        sock_flags &= ~FD_CLOEXEC;

    if (fcntl(self, F_SETFD, sock_flags) < 0)
        return MI_RESULT_FAILED;
#endif

    return MI_RESULT_OK;
}

MI_Result Sock_Connect(
    Sock self,
    const Addr* addr)
{
    int r;
    int flags;
    int isNonBlockingSocket = 0;
#ifdef ENABLE_TRACING
    int connectErrno;
#endif

    LOGD2((ZT("Sock_Connect - Begin. socket: %d"), self));
//    lockMutex(self);
    flags = fcntl(self, F_GETFL, 0);
    if ((flags & O_NONBLOCK) != 0)
    {
        isNonBlockingSocket = 1;
        flags &= ~O_NONBLOCK;
        fcntl(self, F_SETFL, flags);
    }

    r = connect(self, &addr->u.sock_addr, (size_t)addr->sock_addr_size);
#ifdef ENABLE_TRACING
    connectErrno = errno;
#endif

    if (isNonBlockingSocket != 0)
    {
        flags |= O_NONBLOCK;
        fcntl(self, F_SETFL, flags);
    }

//    unlockMutex(self);
    if (r < 0)
    {
        LOGE2((ZT("Sock_Connect - Error from connect. socket: %d: errno: %d (%s)"), self, connectErrno, strerror(connectErrno)));
        return MI_RESULT_FAILED;
    }

    LOGD2((ZT("Sock_Connect - OK exit. socket: %d"), self));
    return MI_RESULT_OK;
}

MI_Result Sock_ReuseAddr(
    Sock self,
    MI_Boolean flag_)
{
    int flag = flag_ ? 1 : 0;
    int r;

    r = setsockopt(self, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, sizeof(flag));

    if (r != 0)
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

MI_Result Sock_SetBlocking(
    Sock self,
    MI_Boolean flag_)
{
#if defined(CONFIG_OS_WINDOWS)
    unsigned long flag = flag_ ? 0 : 1;

    if (ioctlsocket(self, FIONBIO, &flag) != 0)
        return MI_RESULT_FAILED;
#else
    int flags = fcntl(self, F_GETFL, 0);

    if (flag_)
        flags &= ~O_NONBLOCK;
    else
        flags |= O_NONBLOCK;

    if (fcntl(self, F_SETFL, flags) == -1)
        return MI_RESULT_FAILED;
#endif

    return MI_RESULT_OK;
}

MI_Result Sock_SetNoDelay(
    Sock self,
    MI_Boolean flag)
{
    int opt = flag ? 1 : 0;
    int r;

    r = setsockopt(self, IPPROTO_TCP, TCP_NODELAY, (char*)&opt, sizeof(opt));

    if (r != 0)
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

MI_Result Sock_Read(
    Sock self,
    void* data,
    size_t size,
    size_t* sizeRead)
{
    int n;

    LOGD2((ZT("Sock_Read - Begin. socket: %d, size: %u"), (int)self, (unsigned int)size));

    *sizeRead = 0;

    for ( ; ; )
    {
        /* Attempt to read bytes */
        n = _Read(self, data, size);

        if (n >= 0)
        {
            *sizeRead = n;
            LOGD2((ZT("Sock_Read - OK exit. %d bytes read"), n));
            return MI_RESULT_OK;
        }

        /* Repeat operation if instruction interrupted */
        if (_TestEINTR())
        {
            LOGD2((ZT("Sock_Read - _Read returned EINTR")));
            continue;
        }

        /* Check for would block error */
        if (_TestWOULDBLOCK() || _TestEAGAIN())
        {
            LOGD2((ZT("Sock_Read - _Read returned WOULD_BLOCK")));
            return MI_RESULT_WOULD_BLOCK;
        }

        /* Failed */
        trace_SockRead_Failed( _GetErrorCode() );
        break;
    }

    LOGE2((ZT("Sock_Read - _Read failed with errno: %d (%s)"), errno, strerror(errno)));

    return MI_RESULT_FAILED;
}

MI_Result Sock_Write(
    Sock self,
    const void* data,
    size_t size,
    size_t* sizeWritten)
{
    int n;

    LOGD2((ZT("Sock_Write - Begin. socket: %d, size: %u"), (int)self, (unsigned int)size));

    *sizeWritten = 0;

    for ( ; ; )
    {
        /* Attempt to write bytes */
        n = _Write(self, data, size);

        if (n >= 0)
        {
            *sizeWritten = (size_t)n;
            LOGD2((ZT("Sock_Write - OK exit. %d bytes written"), n));
            return MI_RESULT_OK;
        }

        /* Repeat operation if instruction interrupted */
        if (_TestEINTR())
        {
            LOGD2((ZT("Sock_Write - _Write returned EINTR")));
            continue;
        }

        /* Check for would block error */
        if (_TestWOULDBLOCK() || _TestEAGAIN())
        {
            LOGD2((ZT("Sock_Write - _Write returned WOULD_BLOCK")));
            return MI_RESULT_WOULD_BLOCK;
        }

        /* Failed */
        if (size > MINSOCKBUFSIZE)
        {
            /* Retry operation with smaller buffer size */
            size = size >> 1;
        }
        else
        {
            _LogSockWriteError();
            break;
        }
    }

    LOGE2((ZT("Sock_Write - _Write failed with errno:L %d (%s)"), errno, strerror(errno)));
    return MI_RESULT_FAILED;
}

MI_Result Sock_ReadV(
    Sock self,
    const IOVec* iov,
    size_t  iovcnt,
    size_t* sizeRead)
{
    int n;

    * sizeRead = 0;

    for ( ; ; )
    {
        /* Attempt to read bytes */
        n = _ReadV(self, iov, iovcnt);

        if (n >= 0)
        {
            *sizeRead = n;
            return MI_RESULT_OK;
        }

        /* Repeat operation if instruction interrupted */
        if (_TestEINTR())
            continue;

        /* Check for would block error */
        if (_TestWOULDBLOCK() || _TestEAGAIN())
            return MI_RESULT_WOULD_BLOCK;

        /* Failed */
        trace_SockReadV_Failed( _GetErrorCode() );
        break;
    }

    return MI_RESULT_FAILED;
}

MI_Result Sock_WriteV(
    Sock self,
    const IOVec* iov,
    size_t  iovcnt,
    size_t* sizeWritten)
{
    int n, error;

    * sizeWritten = 0;

    for ( ; ; )
    {
        /* Attempt to read bytes */
        n = _WriteV(self, iov, iovcnt);

        if (n >= 0)
        {
            *sizeWritten = n;
            return MI_RESULT_OK;
        }

        /* Repeat operation if instruction interrupted */
        if (_TestEINTR())
            continue;

        /* Check for would block error */
        if (_TestWOULDBLOCK() || _TestEAGAIN())
            return MI_RESULT_WOULD_BLOCK;

        /* Failed */
        error = _GetErrorCode();
        trace_SockWriteV_Failed(error);
#ifdef CONFIG_OS_WINDOWS
        // On Windows initial send auth message can fail because the sockets is not connected yet
        // in that case we send this special error so it can be retried
        if (WSAENOTCONN == error)
        {
            return MI_RESULT_NOT_FOUND;
        }
#endif
        break;
    }

    return MI_RESULT_FAILED;
}

MI_Result Sock_CreateListener(
    Sock* sock,
    const Addr* addr)
{
    MI_Result r;

    /* Create socket */
    {
        r = Sock_Create(sock, addr->is_ipv6);

        if (r != MI_RESULT_OK)
            return r;
    }

    /* Reuse the address (to prevent binding failures) */
    {
        r = Sock_ReuseAddr(*sock, MI_TRUE);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(*sock);
            return r;
        }
    }

    /* Bind the socket to the address */
    {
        r = Sock_Bind(*sock, addr);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(*sock);
            return r;
        }
    }

    /* Listen on this socket for connections */
    {
        r = Sock_Listen(*sock);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(*sock);
            return r;
        }
    }

    return MI_RESULT_OK;
}

MI_Result Sock_CreateLocalListener(
    Sock* sock,
    const char* socketName)
{
#if defined(CONFIG_OS_WINDOWS)
    unsigned short port = (unsigned short)atol(socketName);
    Addr addr;

    Addr_InitAny(&addr, port);
    return Sock_CreateListener(sock, &addr);
#else
    MI_Result r;
    struct sockaddr_un addr;

    *sock = socket(PF_UNIX, SOCK_STREAM, 0);

    if (*sock == -1)
        return MI_RESULT_FAILED;

    if (MI_RESULT_OK != Sock_SetCloseOnExec(*sock,MI_TRUE))
    {
        trace_fcntl_failed(errno);
    }

    /* Reuse the address (to prevent binding failures) */
    {
        r = Sock_ReuseAddr(*sock, MI_TRUE);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(*sock);
            return r;
        }
    }

    memset(&addr, 0, sizeof(addr));

    addr.sun_family = AF_UNIX;

    if (Strlcpy(addr.sun_path, socketName, sizeof(addr.sun_path))
        >= sizeof(addr.sun_path))
    {
        Sock_Close(*sock);
        trace_SocketFilePathTooLong(
            (int)(sizeof(addr.sun_path)-1), scs(socketName));
            return MI_RESULT_FAILED;
    }

    unlink(socketName);

    // if (bind(*sock, (const struct sockaddr_un*)&addr, (socklen_t)sizeof (struct sockaddr_un)) != 0)
    if (bind(*sock, (const struct sockaddr*)&addr, (socklen_t)sizeof (struct sockaddr_un)) != 0)
    {
        Sock_Close(*sock);
        return MI_RESULT_FAILED;
    }

    /* Change mode to allow non-root to connect to it (they need 'w' to connect) */

    chmod(socketName, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);

    /* Listen on this socket for connections */
    {
        r = Sock_Listen(*sock);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(*sock);
            return r;
        }
    }

    return MI_RESULT_OK;
#endif
}

MI_Result Sock_CreateLocalConnector(
    Sock* sock,
    const char* socketName)
{
#if defined(CONFIG_OS_WINDOWS)
    unsigned short port = (unsigned short)atol(socketName);
    Addr addr;
    MI_Result r;

    // Initialize address.
    r = Addr_Init(&addr, "127.0.0.1", port, MI_FALSE);
    if (r != MI_RESULT_OK)
        return MI_RESULT_FAILED;

    // Create client socket.
    r = Sock_Create(sock, MI_FALSE);
    if (r != MI_RESULT_OK)
    {
        Sock_Close(*sock);
        return MI_RESULT_FAILED;
    }

    r = Sock_SetBlocking(*sock, MI_FALSE);
    if (r != MI_RESULT_OK)
    {
        Sock_Close(*sock);
        return MI_RESULT_FAILED;
    }

    // Connect to server.
    r = Sock_Connect(*sock, &addr);
    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        Sock_Close(*sock);
        return MI_RESULT_FAILED;
    }
    return r;
#else
    struct sockaddr_un addr;
    MI_Result r;

    *sock = socket(PF_UNIX, SOCK_STREAM, 0);

    if (*sock == -1)
    {
        trace_LocalSocketFailed(socketName);
        return MI_RESULT_FAILED;
    }

    if (MI_RESULT_OK != Sock_SetCloseOnExec(*sock,MI_TRUE))
    {
        trace_LocalSocket_SetOnExecFailed(socketName);
        trace_fcntl_failed(errno);
    }

    r = Sock_SetBlocking(*sock, MI_FALSE);
    if (r != MI_RESULT_OK)
    {
        trace_LocalSocket_SetBlockingFailed(socketName);
        Sock_Close(*sock);
        return MI_RESULT_FAILED;
    }

    memset(&addr, 0, sizeof(addr));

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socketName, sizeof addr.sun_path - 1);

    // if (connect(*sock, (const struct sockaddr_un*)&addr, (socklen_t)sizeof (struct sockaddr_un)) != 0)
    if (connect(*sock, (const struct sockaddr*)&addr, (socklen_t)sizeof (struct sockaddr_un)) != 0)
    {
        if (_TestWOULDBLOCK() || _TestEAGAIN())
            return MI_RESULT_WOULD_BLOCK;

        trace_LocalSocket_ConnectFailed(socketName, errno);

        Sock_Close(*sock);
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
#endif
}

static MI_Result _CreateSocketAndConnect(
    Sock* s,
    Addr* addr)
{
    MI_Result r;

    // Create client socket.
    r = Sock_Create(s, addr->is_ipv6);
    if (r != MI_RESULT_OK)
    {
        LOGE2((ZT("_CreateSocketAndConnect - Sock_Create failed. result: %d (%s)"), r, mistrerror(r)));
        return r;
    }

    r = Sock_SetBlocking(*s, MI_FALSE);
    if (r != MI_RESULT_OK)
        return r;

    r = Sock_Connect(*s, addr);
    if (r != MI_RESULT_OK)
    {
        if (r == MI_RESULT_WOULD_BLOCK)
        {
            LOGW2((ZT("_CreateSocketAndConnect - Sock_Connect would block")));
        }
        else
        {
            LOGE2((ZT("_CreateSocketAndConnect - Sock_Connect failed. result: %d (%s)"), r, mistrerror(r)));
        }
    }

    return r;
}

MI_Result Sock_CreateIPConnector(
    Sock* s,
    const char* hostAndPort)
{
    /* create a connector to a remote address given in the form _host_:_port_ */
    Addr addr;
    MI_Result r;
    unsigned short port;
    size_t len;
    char host[128];
    /* TODO: detect IPv6 numeric addresses, in the form XXXX:XXXX:XXXX:XXXX:XXXX:XXXX:XXXX:XXXX/dd */
    const char* posColon = strchr(hostAndPort, ':');

    if (posColon == NULL)
        return MI_RESULT_INVALID_PARAMETER;
    len = (size_t)(posColon - hostAndPort);
    if (len >= sizeof host)
        return MI_RESULT_INVALID_PARAMETER;
    port = (unsigned short)atol(posColon + 1);
	memcpy(host, hostAndPort, len);
    host[len] = '\0';

    /* This code tries to connect using the primary addressing family */
		/* (IPv4 or IPv6). If that fails and Addr_Init has a secondary */
		/* addressing family, it tries using the secondary family next. */

    /* Initialize primary family address. */
    r = Addr_Init(&addr, host, port, MI_FALSE);
    if (r != MI_RESULT_OK)
        return r;

    /* Connect to server. */
    r = _CreateSocketAndConnect(s, &addr);
    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        MI_Result r2;

        Sock_Close(*s);

        /* Initialize secondary address. */
        r2 = Addr_Init(&addr, host, port, MI_TRUE);
        if (r2 != MI_RESULT_OK)
            return r;               /* on error, return original failure */
        r2 = _CreateSocketAndConnect(s, &addr);
        if (r2 != MI_RESULT_OK && r2 != MI_RESULT_WOULD_BLOCK)
        {
            Sock_Close(*s);

            return r;               /* on error, return original failure */
        }
        r = r2;
    }

#ifdef ENABLE_TRACING
    if (r != MI_RESULT_OK)
        LOGD2((ZT("_CreateConnector - Connect failure. host: %s, result: %d (%s)"), host, (int)r, mistrerror(r)));
#endif

    return r;
}
