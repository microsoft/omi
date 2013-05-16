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
# include <pthread.h>
# include <sys/socket.h>
# include <netinet/tcp.h>
# include <netinet/in.h>
# include <sys/time.h>
# include <sys/types.h>
# include <netdb.h>
# include <fcntl.h>
# include <arpa/inet.h>
# include <signal.h>
// PATH_MAX
# include <limits.h>
// readv/writev headers
# include <sys/uio.h>
#include <strings.h>

# include <sys/socket.h>
# include <sys/un.h>
# include <unistd.h>
# include <sys/stat.h>
#endif

#include <base/log.h>
#include <base/strings.h>
#include <io/io.h>

#if !defined PATH_MAX   // Some HP-UX's don't define PATH_MAX in <limits.h> unless you specify several symbols before including it
# define PATH_MAX _XOPEN_PATH_MAX
#endif

// #define ENABLE_TRACING
// #define TRACING_LEVEL 4
#include <logging.h>

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

int LastSocketError;
int ListenerSocket;

static char *globalSocketName = NULL;

void StopHere(int sock)
{
    if (sock == ListenerSocket)
    {
        // printf("Stop here to attach\n");
    }
}

int doMutexStuff(int Sock, int Lock)
{
    static pthread_mutex_t thisMethodLock;
    static pthread_mutex_t socketLock;
    static int mutexInitialized = 0;
    static int mutexlocked = 0;
    static pthread_t owner;
    static int lastSocketLocked = 0;
    int isNonBlockingSocket = 0;

    LOGD2((ZT("doMutexStuff - Begin. socket: %d, lock: %d --> %d"), Sock, mutexlocked, Lock));

    if (mutexInitialized == 0)
    {
        pthread_mutex_init(&socketLock, NULL);
        pthread_mutex_init(&thisMethodLock, NULL);
        mutexInitialized = 1;
    }

    if ((mutexlocked <= 0 && Lock == 0) || Sock == INVALID_SOCK)
    {
        LOGD2((ZT("doMutexStuff - Attempt to unlock mutex for socket %d, but no mutex has been set. Ignoring."), Sock));
        return 1; // Pretend it's a blocking socket
    }

try_again:
    pthread_mutex_lock(&thisMethodLock);

    // Need to figure out what kind of socket this is
    if (Sock != INVALID_SOCK)
    {
        int flags = fcntl(Sock, F_GETFL, 0);

        if ((flags & O_NONBLOCK) != 0)
        {
            isNonBlockingSocket = 1;
            LOGD2((ZT("doMutexStuff - Awesome! socket %d is NOT blocking"), Sock));
        }
        else
        {
            isNonBlockingSocket = 0;
            LOGD2((ZT("doMutexStuff - Never mind, socket %d is blocking"), Sock));
            goto NotLocked;
        }
    }
    else
    {
        LOGE2((ZT("doMutexStuff - Attempt to perform mutex operation on INVALID socket")));

        // Check out pthread_-if
        if (mutexlocked > 0 && pthread_equal(owner, pthread_self()))
        {
            // If it was locked before, it must be a non-blocking socket
            isNonBlockingSocket = 1;
        }
    }

    if (mutexlocked > 0 && pthread_equal(owner, pthread_self()))
    {
        isNonBlockingSocket = 1;

        // If we're going recursive, and we're in the same thread, then this had better be for
        // the same socket
#if TRACING_LEVEL > 3
        if (Sock != lastSocketLocked)
        {
            LOGD2((ZT("domutexstuff - trying to lock a new socket but mutex is being used. old socket: %d, new socket: %d"), lastSocketLocked, Sock));
                }
#endif
        assert(Sock == lastSocketLocked);

        if (Lock == 1)
        {
            LOGD2((ZT("doMutexStuff - Thread %ld has executed a RECURSIVE mutex"), owner));
            mutexlocked++;
            goto NotLocked;
        }
#if TRACING_LEVEL > 3
        else
        {
            LOGD2((ZT("doMutexStuff - Thread is going to free the mutex socket: %d"), Sock));
        }
#endif
    }

    if (Lock == 1)
    {
        int iStat = pthread_mutex_trylock(&socketLock);
        if (iStat != 0)
        {
            if (iStat != EBUSY)
            {
               LOGE2((ZT("doMutexStuff - Error locking mutex.")));
            }
            else
            {
               LOGW2((ZT("doMutexStuff - Attempt to lock locked mutex")));
               pthread_mutex_unlock(&thisMethodLock);
               usleep(50);
               goto try_again;
            }
        }
        else
        {
            LOGD2((ZT("doMutexStuff - thread has executed an INITIAL non-blocking mutex. socket: %d"), Sock));
            owner = pthread_self();
            lastSocketLocked = Sock;
            mutexlocked++;
        }
    }
    else
    {
        mutexlocked--;

        if (mutexlocked <= 0)
        {
            if (pthread_mutex_unlock(&socketLock) != 0)
            {
                LOGE2((ZT("doMutexStuff - Error unlocking mutex")));
            }

            LOGD2((ZT("doMutexStuff - thread mutex COMPLETELY unlocked. count: %d"), mutexlocked));
            lastSocketLocked = INVALID_SOCK;
        }
        else
        {
            LOGD2((ZT("doMutexStuff - Thread recursive mutex unlocked. count: %d"), mutexlocked));
        }
    }

NotLocked:
    assert(mutexlocked >= 0);
    pthread_mutex_unlock(&thisMethodLock);
    LOGD2((ZT("doMutexStuff - Exit. isNonBlocking: %d, mutexlocked: %d"), isNonBlockingSocket, mutexlocked));
    return isNonBlockingSocket;
}

int lockMutex(int Sock)
{
    LOGD2((ZT("lockMutex - begin. socket: %d"), Sock));
    return(doMutexStuff(Sock, 1));
}

void unlockMutex(int Sock)
{
    LOGD2((ZT("unlockMutex - begin. socket: %d"), Sock));
    (void)doMutexStuff(Sock, 0);
}

int _TestWOULDBLOCK()
{
#if defined(CONFIG_OS_WINDOWS)
    return GetLastError() == WSAEWOULDBLOCK;
#else
    return (LastSocketError == EWOULDBLOCK || LastSocketError == EINPROGRESS || LastSocketError == EALREADY) ? 1 : 0;
#endif
}

int _TestEAGAIN()
{
#if defined(CONFIG_OS_WINDOWS)
    return 0;
#else
    return( LastSocketError == EAGAIN) ? 1 : 0;
#endif
}

int _TestEINTR()
{
#if defined(CONFIG_OS_WINDOWS)
    return GetLastError() == WSAEINTR;
#else
    return errno == EINTR;
#endif
}

int _Read(Sock sock, void* data, size_t size)
{
    int bytesRead = 0;

    LOGD2((ZT("Entered _Read for socket %d"), sock));

    if (sock == INVALID_SOCK || data == NULL || size <= 0)
    {
        errno = EINVAL;
        LastSocketError = EINVAL;
        return -1;
    }

#if defined(CONFIG_OS_WINDOWS)
    bytesRead = recv(sock, data, (int)size, 0);
#else
    LastSocketError = 0;
    errno = 0;
    bytesRead = read(sock, data, size);
    LastSocketError = errno;
#endif

    if (bytesRead < 0)
    {
        if (LastSocketError != EAGAIN && LastSocketError != EINTR)
        {
            //char Diag[1024];
            LOGE((ZT("Error on read for socket %d: %s"), sock, strerror(LastSocketError)));
            LOGE2((ZT("Error on read for socket %d: %s"), sock, strerror(LastSocketError)));
            close(sock);
            sock = INVALID_SOCK;
        }
    }

    LOGD2((ZT("_Read - Exiting read. socket: %d, bytes read: %d"), sock, bytesRead));
    return bytesRead;
}

int _Write(Sock sock, const void* data, size_t size)
{
    int bytesSent = 0;

    lockMutex(sock);

    LOGD2((ZT("_Write - begin. socket: %d"), sock));
    if (sock == INVALID_SOCK || data == NULL || size <= 0)
    {
        errno = EINVAL;
        unlockMutex(sock);
        return -1;
    }

#if defined(CONFIG_OS_WINDOWS)
    bytesSent = send(sock, data, (int)size, 0);
#else
    errno = 0;
    bytesSent = write(sock, data, size);
    LastSocketError = errno;

    if (bytesSent < 0)
    {
        if (LastSocketError != EAGAIN && LastSocketError != EINTR)
        {
            LOGW((ZT("_Write - Error on write. socket: %d (%s)"), sock, strerror(LastSocketError)));
            LOGE2((ZT("_Write - Error on write. socket: %d, error: %d (%s)"), sock, LastSocketError, strerror(LastSocketError)));
            // assert(sock != ListenerSocket);
            StopHere(sock);
            unlockMutex(sock);
            Sock_Close(sock);
            sock = INVALID_SOCK;

            return bytesSent;
        }
    }
#endif

    unlockMutex(sock);
    LOGD2((ZT("_Write - Exiting write. socket (INVALID_SOCK if error): %d, %d bytes sent"), sock, bytesSent));
    return bytesSent;
}

int _ReadV(Sock sock, const struct iovec* iov, size_t  iovcnt)
{
    LOGD2((ZT("_ReadV - Entered _ReadV for socket %d"), sock));

    lockMutex(sock);

    if (sock == INVALID_SOCK || iov == NULL || iovcnt <= 0)
    {
        errno = EINVAL;
        LOGE2((ZT("_ReadV - Parameter error. sock: %d, iov: %p, iovcnt: %u"), sock, iov, (unsigned int)iovcnt));
        unlockMutex(sock);
        return -1;
    }

#if defined(CONFIG_OS_WINDOWS)
    int res = 0;
    int total = 0;
    size_t index = 0;

    for ( ; index < iovcnt; index++)
    {
        errno = 0;
        res = recv(sock, iov[index].iov_base, (int)iov[index].iov_len, 0);
        LastSocketError = errno;

        if (res < 0 && total == 0)
            return res;

        if (res < 0)
            return total;

        total += res;

        if (res == 0 || (size_t)res != iov[index].iov_len)
            return total;
    }
    return total;
#else
    int bytesRead = 0;

    /* Attempt to read bytes */
    int flags = fcntl(sock, F_GETFL, 0);

    int isNonBlockingSocket = 0;
    if (flags & O_NONBLOCK)
    {
        isNonBlockingSocket = 1;
    }

    LastSocketError = 0;

    // The Sun doesn't like data as a void
    if (isNonBlockingSocket != 0)
    {
        fd_set SingleSocketSet;
        FD_ZERO(&SingleSocketSet);

        FD_SET(sock, &SingleSocketSet);

        struct timeval TimeOut;

        TimeOut.tv_sec = 0;
        TimeOut.tv_usec = 20000;
        int numReady = select(sock + 1, &SingleSocketSet, NULL, NULL, &TimeOut);
        if (numReady > 0)
        {
            flags &= ~O_NONBLOCK;
            fcntl(sock, F_SETFL, flags);

            bytesRead = readv(sock, iov, iovcnt);

            flags |= O_NONBLOCK;
            fcntl(sock, F_SETFL, flags);
        }
        else
        {
            LOGW2((ZT("_ReadV - Select says socket %d has no data. Returning MI_RESULT_WOULD_BLOCK"), sock));
            unlockMutex(sock);
            return MI_RESULT_WOULD_BLOCK;
        }
    }
    else
    {
        errno = 0;
        bytesRead = readv(sock, iov, iovcnt);
        LastSocketError = errno;
    }

    if (bytesRead < 0)
    {
        if (LastSocketError != EAGAIN && LastSocketError != EINTR)
        {
            LOGW((ZT("_ReadV - Error for socket %d with %u buffers: %s"), sock, (unsigned int)iovcnt, strerror(LastSocketError)));
            LOGE2((ZT("_ReadV - Error for socket %d with %u buffers: %s"), sock, (unsigned int)iovcnt, strerror(LastSocketError)));

            // assert(sock != ListenerSocket);
            unlockMutex(sock);
            StopHere(sock);
            Sock_Close(sock);
            sock = INVALID_SOCK;

            return bytesRead;
        }
    }
    LOGD2((ZT("_ReadV - Exiting. socket (INVALID_SOCK if error): %d, %d bytes read, error: %d (%s)"), sock, bytesRead, LastSocketError, strerror(LastSocketError)));
    unlockMutex(sock);
    return bytesRead;
#endif
}

int _WriteV(Sock sock, const struct iovec* iov, size_t iovcnt)
{
    LOGD2((ZT("_WriteV - Begin. socket: %d"), sock));
    lockMutex(sock);

    if (sock == INVALID_SOCK || iov == NULL || iovcnt <= 0)
    {
        LOGE2((ZT("_WriteV - parameter error. sock: %d, iov: %p, iovcnt: %u"), sock, iov, (unsigned int)iovcnt));
        errno = EINVAL;
        unlockMutex(sock);
        return -1;
    }

#if defined(CONFIG_OS_WINDOWS)
    int res = 0;
    int total = 0;
    size_t index = 0;

    for ( ; index < iovcnt; index++)
    {
        LastSocketError = errno = 0;
        res = send(sock, iov[index].iov_base, (int)iov[index].iov_len, 0);
        LastSocketError = errno;

        if (res < 0 && total == 0)
        {
            unlockMutex(sock);
            return res;
        }

        if (res < 0)
        {
            unlockMutex(sock);
            return total;
        }

        total += res;

        if (res == 0 || (size_t)res != iov[index].iov_len)
        {
            unlockMutex(sock);
            return total;
        }
    }
    return total;
#else
    LastSocketError = 0;
    errno = 0;
    int bytesSent = writev(sock, iov, iovcnt);
    LastSocketError = errno;

    if (bytesSent < 0)
    {
        if (LastSocketError != EAGAIN && LastSocketError != EINTR)
        {
            LOGW((ZT("_WriteV - Error on writev for socket %d: %s"), sock, strerror(LastSocketError)));
            LOGE2((ZT("_WriteV - Error on writev for socket %d: %s"), sock, strerror(LastSocketError)));

            // assert(sock != ListenerSocket);
            unlockMutex(sock);
            StopHere(sock);
            Sock_Close(sock);
            sock = INVALID_SOCK;

            return bytesSent;
        }
    }

    LOGD2((ZT("_WriteV - Exiting. socket (INVALID_SOCK if error): %d, %d bytes sent, error %d (%s)"), sock, bytesSent, LastSocketError, strerror(LastSocketError)));
    unlockMutex(sock);
    return bytesSent;
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
    LOGD2((ZT("Sock_Start - Begin")));
#if defined(CONFIG_OS_WINDOWS)
    WORD version = MAKEWORD(2, 0);
    WSADATA data;
    int rc;

    rc = WSAStartup (version, &data);

    if (rc != 0)
    {
        return MI_RESULT_FAILED;
    }

#else
    /* ignore PIPE signal */
    struct sigaction sig_acts;

    sig_acts.sa_handler = SIG_IGN;
    sigfillset(&(sig_acts.sa_mask));
    sig_acts.sa_flags = 0;

    sigaction(SIGPIPE, &sig_acts, NULL);

#endif /* CONFIG_OS_WINDOWS */
    LOGD2((ZT("Sock_Start - Successful exit")));
    return MI_RESULT_OK;
}

void Sock_Stop()
{
#if defined(CONFIG_OS_WINDOWS)
    LOGD2((ZT("Sock_Stop - Begin")));
    WSACleanup();
#endif /* CONFIG_OS_WINDOWS */
}

MI_Result Sock_Create(Sock* sock, MI_Boolean is_ipv6)
{
    MI_Result r;

    LOGD2((ZT("Sock_Create - Begin. is_ipv6: %d"), is_ipv6));

    errno = 0;
    *sock = socket(is_ipv6 ? AF_INET6 : AF_INET, SOCK_STREAM, IPPROTO_TCP);
    LastSocketError = errno;
    LOGD2((ZT("Sock_Create - socket returned: %d, errno: %d (%s)"), (int)*sock, LastSocketError, strerror(LastSocketError)));
    if (*sock < 0)
    {
        LOGE2((ZT("Sock_Create - Socket create failed with error %d (%s)"), errno, strerror(errno)));
        return MI_RESULT_FAILED;
    }

    r = Sock_SetCloseOnExec(*sock, MI_TRUE);
    if (r != MI_RESULT_OK)
    {
        LOGW((ZT("Sock_Create - fcntl(F_SETFD) failed")));
        LOGE2((ZT("Sock_Create - fcntl(F_SETFD) failed with status: %d (%s)"), (int)r, mistrerror(r)));
    }

    LOGD2((ZT("Sock_Create - Successful exit")));
    return MI_RESULT_OK;
}

MI_Result Sock_Close(Sock self)
{
    int status = 0;
    lockMutex(self);
    int oldSockNumber = self;

    LOGD2((ZT("Sock_Close - Begin. socket: %d"), self));
    errno = 0;
    if (self != INVALID_SOCK)
    {
#if defined(CONFIG_OS_WINDOWS)
        status = closesocket(self);
#else
        LastSocketError = 0;
        StopHere(self);
        LastSocketError = errno;
        self = INVALID_SOCK;
#endif

        unlockMutex(oldSockNumber);

        // Have to do this after the unlock, but we already set the external
        // values to INVALID, so it should be safe.
        errno = 0;
        status = close(oldSockNumber);
    }
    else
    {
       unlockMutex(oldSockNumber);
    }

    LOGD2((ZT("Sock_Close - Exit. errno: %d (%s)"), errno, strerror(errno)));
    return status == 0 ? MI_RESULT_OK : MI_RESULT_FAILED;
}

MI_Result Sock_Bind(Sock self, const Addr* addr)
{
    int r;

    LOGD2((ZT("Sock_Bind - Begin. socket: %d"), self));
    lockMutex(self);
    LastSocketError = 0;
    errno = 0;

    r = bind(self, &addr->u.sock_addr, (size_t)addr->sock_addr_size);
    LastSocketError = errno;
    unlockMutex(self);

    if (r < 0)
    {
        // perror("Socket bind: ");
        LOGW((ZT("Sock_Bind - Error binding. socket: %d: errno: %d (%s)"), self, LastSocketError, strerror(LastSocketError)));
        LOGE2((ZT("Sock_Bind - Error binding. socket: %d: errno: %d (%s)"), self, LastSocketError, strerror(LastSocketError)));
        return MI_RESULT_FAILED;
    }

    LOGD2((ZT("Sock_Bind - Successful exit. socket: %d"), self));
    return MI_RESULT_OK;
}

MI_Result Sock_Listen(Sock self)
{
    int r;

    LOGD2((ZT("Sock_Listen - Begin. socket: %d"), self));
    lockMutex(self);
    LastSocketError = 0;
    errno = 0;
    r = listen(self, 15);
    LastSocketError = errno;
    ListenerSocket = self;
    unlockMutex(self);

    if (r != 0)
    {
        LOGE2((ZT("Sock_Listen - Error. socket: %d: errno: %d (%s)"), self, LastSocketError, strerror(LastSocketError)));
        return MI_RESULT_FAILED;
    }

    LOGD2((ZT("Sock_Listen - Successful exit. socket: %d"), self));
    return MI_RESULT_OK;
}

MI_Result Sock_Accept(
    Sock self,
    Sock* sock,
    Addr* addr)
{
    MI_Result r;
    socklen_t addrlen = sizeof(*addr);

    LOGD2((ZT("Sock_Accept - Begin. socket: %d"), self));

    lockMutex(self);
    errno = 0;
    *sock = accept(self, (struct sockaddr*)addr, &addrlen);
    LastSocketError = errno;

    if (*sock < 0)
    {
        if (_TestWOULDBLOCK() || _TestEAGAIN())
        {
            unlockMutex(self);
            return MI_RESULT_WOULD_BLOCK;
        }
        unlockMutex(self);
        return MI_RESULT_FAILED;
    }

    r = Sock_SetCloseOnExec(*sock, MI_TRUE);
    unlockMutex(self);
    if (r != MI_RESULT_OK)
    {
        LOGW((ZT("Sock_Accept - fcntl(F_SETFD) failed")));
        LOGE2((ZT("Sock_Accept - fcntl(F_SETFD) failed with status %d (%s)"), (int)r, mistrerror(r)));
    }

    LOGD2((ZT("Sock_Accept - Successful exit. socket: %d"), self));
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

    LOGD2((ZT("Sock_SetCloseOnExec - Begin. socket: %d"), self));
    if ((sock_flags = fcntl(self, F_GETFD, 0)) < 0)
    {
        LOGE2((ZT("Sock_SetCloseOnExec - Error getting flags. socket: %d: errno: %d (%s)"), self, LastSocketError, strerror(LastSocketError)));
        return MI_RESULT_FAILED;
    }

    if (closeOnExec)
        sock_flags |= FD_CLOEXEC;
    else
        sock_flags &= ~FD_CLOEXEC;

    if (fcntl(self, F_SETFD, sock_flags) < 0)
    {
        LOGE2((ZT("Sock_SetCloseOnExec - Error setting flags. socket: %d: errno: %d (%s)"), self, LastSocketError, strerror(LastSocketError)));
        return MI_RESULT_FAILED;
    }
#endif

    LOGD2((ZT("Sock_SetCloseOnExec - Successful exit. socket: %d"), self));
    return MI_RESULT_OK;
}

MI_Result Sock_Connect(
    Sock self,
    const Addr* addr)
{
    int r;
    int flags;
    int isNonBlockingSocket = 0;

    LOGD2((ZT("Sock_Connect - Begin. socket: %d"), self));
    lockMutex(self);
    flags = fcntl(self, F_GETFL, 0);
    if ((flags & O_NONBLOCK) != 0)
    {
        isNonBlockingSocket = 1;
        flags &= ~O_NONBLOCK;
        fcntl(self, F_SETFL, flags);
    }

    errno = 0;
    r = connect(self, &addr->u.sock_addr, (size_t)addr->sock_addr_size);
    LastSocketError = errno;

    if (isNonBlockingSocket != 0)
    {
        flags |= O_NONBLOCK;
        fcntl(self, F_SETFL, flags);
    }

    unlockMutex(self);
    if (r < 0)
    {
        LOGE2((ZT("Sock_Connect - Error from connect. socket: %d: errno: %d (%s)"), self, LastSocketError, strerror(LastSocketError)));
        return MI_RESULT_FAILED;
    }
    LOGD2((ZT("Sock_Connect - Successful exit. socket: %d"), self));
    return MI_RESULT_OK;
}

MI_Result Sock_ReuseAddr(
    Sock self,
    MI_Boolean flag_)
{
    int flag = flag_ ? 1 : 0;
    int r;

    LOGD2((ZT("Sock_ReuseAddr - Begin. socket: %d"), self));
    lockMutex(self);

    LastSocketError = 0;
    errno = 0;
    r = setsockopt(self, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, sizeof(flag));
    LastSocketError = errno;

    unlockMutex(self);
    if (r != 0)
    {
        LOGE2((ZT("Sock_Connect - Error from setsockopt. socket: %d: errno: %d (%s)"), self, LastSocketError, strerror(LastSocketError)));
        return MI_RESULT_FAILED;
    }

    usleep(50);
    LOGD2((ZT("Sock_ReuseAddr - Successful exit. socket: %d"), self));
    return MI_RESULT_OK;
}

MI_Result Sock_SetBlocking(
    Sock self,
    MI_Boolean flag_)
{
#if defined(CONFIG_OS_WINDOWS)
    unsigned long flag = flag_ ? 0 : 1;

    if (ioctlsocket(self, FIONBIO, &flag) != 0)
    {
        return MI_RESULT_FAILED;
    }
#else
    int flags = fcntl(self, F_GETFL, 0);

    LOGD2((ZT("Sock_SetBlocking - Begin. socket: %d, flag: %05X --> %d"), self, flags & O_NONBLOCK, flag_));

    if (flag_)
    {
        flags &= ~O_NONBLOCK;
    }
    else
    {
        flags |= O_NONBLOCK;
    }

    if (fcntl(self, F_SETFL, flags) < 0)
    {
        LOGE2((ZT("Sock_SetBlocking - Error from fcntl. socket: %d: errno: %d (%s)"), self, LastSocketError, strerror(LastSocketError)));
        return MI_RESULT_FAILED;
    }
#endif

    LOGD2((ZT("Sock_SetBlocking - Successful end. socket: %d"), self));
    return MI_RESULT_OK;
}

MI_Result Sock_SetNoDelay(
    Sock self,
    MI_Boolean flag)
{
    LOGD2((ZT("Sock_SetNoDelay - Begin. socket: %d, flag: %d"), self, flag));
    lockMutex(self);

    int opt = flag ? 1 : 0;
    int r;

    LastSocketError = 0;
    errno = 0;
    r = setsockopt(self, IPPROTO_TCP, TCP_NODELAY, (char*)&opt, sizeof(opt));
    LastSocketError = errno;

    unlockMutex(self);

    if (r != 0)
    {
        LOGE2((ZT("Sock_SetNoDelay - Error from setsockopt. socket: %d, error: %d (%s)"), self, errno, strerror(errno)));
        return MI_RESULT_FAILED;
    }

    LOGD2((ZT("Sock_SetNoDelay - Successful end. socket: %d"), self));
    return MI_RESULT_OK;
}

MI_Result Sock_Read(
    Sock self,
    void* data,
    size_t size,
    size_t* sizeRead)
{
    (void)lockMutex(self);

    int n;
    int amtLeft = size;

    LOGD2((ZT("Sock_Read - Begin. socket: %d, max. bytes wanted: %u"), self, (unsigned int)size));

    if (data == NULL)
    {
        LOGE2((ZT("Sock_Read - Argument error: NULL pointer")));
        unlockMutex(self);
        return MI_RESULT_FAILED;
    }

    *sizeRead = 0;

    /* Attempt to read bytes */
    int flags = fcntl(self, F_GETFL, 0);

    int isNonBlockingSocket = 0;
    if (flags & O_NONBLOCK)
    {
        isNonBlockingSocket = 1;
    }

    // The Sun doesn't like data as a void
    if (isNonBlockingSocket != 0)
    {
        fd_set SingleSocketSet;
        FD_ZERO(&SingleSocketSet);

        FD_SET(self, &SingleSocketSet);

        struct timeval TimeOut;

        TimeOut.tv_sec = 0;
        TimeOut.tv_usec = 20000;
        int numReady = select(self + 1, &SingleSocketSet, NULL, NULL, &TimeOut);

        if (numReady > 0)
        {
            flags &= ~O_NONBLOCK;
            fcntl(self, F_SETFL, flags);

            n = _Read(self, (char*)data, amtLeft);

            flags |= O_NONBLOCK;
            fcntl(self, F_SETFL, flags);
        }
        else
        {
            LOGW2((ZT("Sock_Read - Select says socket %d has no data. Returning WOULD_BLOCK"), self));
            unlockMutex(self);
            return MI_RESULT_WOULD_BLOCK;
        }
    }
    else
    {
        n = _Read(self, (char*)data, amtLeft);
    }

    if (n > 0)
    {
        LOGD2((ZT("Sock_Read - Read %d bytes from socket %d with error %d (%s), data: [0x%02X %02X %02X %02X ...]"), n, self, LastSocketError, strerror(LastSocketError), *(unsigned char*)data, *((unsigned char*)data + 1), *((unsigned char*)data + 2), *((unsigned char*)data + 3)));
        *sizeRead = n;
    }
    else if (n == 0)
    {
        LOGD2((ZT("Sock_Read - Socket %d was empty, 0 bytes returned"), self));
        *sizeRead = 0;
    }
    else
    {
        // Flag to the rest of the system that the socket had an unrecoverable error and was closed.
        LOGE2((ZT("Sock_Read - Read error on socket %d. errno: %d (%s)"), self, LastSocketError, strerror(LastSocketError)));
        *sizeRead = 0;
        unlockMutex(self);
        return MI_RESULT_FAILED;
    }
    unlockMutex(self);
    LOGD2((ZT("Sock_Read - Successful exit. socket: %d, bytes read: %u"), self, (unsigned int)*sizeRead));
    return MI_RESULT_OK;
}

MI_Result Sock_Write(
    Sock self,
    const void* data,
    size_t size,
    size_t* sizeWritten)
{
    LOGD2((ZT("Sock_Write - Begin. socket: %d, bytes to write: %u"), self, (unsigned int)size));

    int isNonBlocking = lockMutex(self);
    int n;
    size_t bytesLeft = size;
    int flags = fcntl(self, F_GETFL, 0);

    *sizeWritten = 0;

    if (isNonBlocking != 0)
    {
        fd_set SingleSocketSet;
        FD_ZERO(&SingleSocketSet);

        FD_SET(self, &SingleSocketSet);

        struct timeval TimeOut;

        TimeOut.tv_sec = 0;
        TimeOut.tv_usec = 20000;
        int numReady = select(self + 1, NULL, &SingleSocketSet, NULL, &TimeOut);

        if (numReady > 0)
        {
            flags &= ~O_NONBLOCK;
            fcntl(self, F_SETFL, flags);

            /* Attempt to write bytes */
            n = _Write(self, (void*)data, bytesLeft);
            LOGD2((ZT("Sock_Write - Socket send. %u bytes requested, %d bytes sent."), (unsigned int)bytesLeft, n));

            flags |= O_NONBLOCK;
            fcntl(self, F_SETFL, flags);
        }
        else
        {
            *sizeWritten = 0;
            LOGX2((ZT("Sock_Read - Select says socket %d has no data. Returning WOULD_BLOCK"), self));
            unlockMutex(self);
            return MI_RESULT_WOULD_BLOCK;
        }
    }
    else
    {
        n = _Write(self, (void*)data, bytesLeft);
    }

    if (n > 0)
    {
        *sizeWritten = n;
    }
    else
    {
        // *sizeWritten == 0 is a flag to the rest of the system that the socket
        // had an unrecoverable error and was closed.
        LOGE2((ZT("Sock_Write - Write error on socket %d. errno: %d (%s)"), (int)self, LastSocketError, strerror(LastSocketError)));
        *sizeWritten = 0;
    }
    unlockMutex(self);     // this isn't strictly necessary, but is done for the sake of symmetry.
    LOGD2((ZT("Sock_Write - Successful end. socket: %d, bytes written: %u"), self, (unsigned int)*sizeWritten));
    return MI_RESULT_OK;
}

/*
 Read into memory pointed to by a vector of buffer pointers (a scatter vector)

 @param [in]    self - the socket to read from
 @param [in]    iov - the array of buffer descriptors telling where to read
 @param [in]    iovcnt - the soize of iov
 @param [out]   sizeRead - how many bytes were actually read

 @returns       an MI_Result: MI_RESULT_OK for succeess, another value for failure
*/
MI_Result Sock_ReadV(
    Sock self,
    const struct iovec* iov,
    size_t  iovcnt,
    size_t* sizeRead)
{
    int n;
    int isNonBlocking = lockMutex(self);

    LOGD2((ZT("Sock_ReadV - Begin. socket: %d, isNonBlocking: %d"), self, isNonBlocking));

    *sizeRead = 0;
    if (isNonBlocking == 0)
    {
        // blocking socket--read once
        n = _ReadV(self, iov, iovcnt);
        if (n < 0)
        {                               // error
            *sizeRead = 0;
            unlockMutex(self);
            LOGE2((ZT("Sock_ReadV - _ReadV failed. errno: %d (%s)"), LastSocketError, strerror(LastSocketError)));
            return MI_RESULT_FAILED;
        }
        *sizeRead = n;

        unlockMutex(self);
        return MI_RESULT_OK;
    }

    // non-blocking socket: try several times to read
    {
        // calculate bytes to read needed
        size_t amtNeeded;
        int readAttempt;
        int n;
        struct iovec* currIov;
        struct iovec* currReadIov;
        struct iovec* readIov;
        size_t iovPos;
        size_t readVecCnt = 0;
        size_t currVecBegin;
        size_t currVecEnd;
        size_t bufOffset;

        amtNeeded = 0;
        for (iovPos = 0; iovPos < iovcnt; iovPos++)
        {
            amtNeeded += (iov + iovPos)->iov_len;
        }

        readIov = (struct iovec*)malloc(sizeof (struct iovec) * iovcnt);
        for (readAttempt = 0; readAttempt < 10; readAttempt++)
        {
            for (iovPos = 0; iovPos < iovcnt; iovPos++)
            {
                // Create a new scatter vector that accurately lists the remaining unread buffer areas.
                // The first time, the new vector will be the same as the original.  In subsequent
                // reads, the first scatter vector component will contain a pointer and size that describe
                // the end part of the last partially-read buffer and the remaining scatter vector components
                // will be copies of the original vector's components that occurred after the partially-read
                // vector.
                readVecCnt = 0;
                currVecBegin = 0;
                for (iovPos = 0; iovPos < iovcnt; iovPos++)
                {
                    currIov = (struct iovec*)iov + iovPos;
                    currVecEnd = currVecBegin + currIov->iov_len;
                    if (currVecEnd >= *sizeRead)
                    {                   // this iovec will be populated
                        currReadIov = readIov + readVecCnt;
                        if (*sizeRead > currVecBegin)
                        {               // part of this buffer needs to be read
                            bufOffset = *sizeRead - currVecBegin;
                        }
                        else
                        {               // the entire buffer needs to be read
                            bufOffset = 0;
                        }
                        currReadIov->iov_base = (void*)((char*)currIov->iov_base + bufOffset);
                        currReadIov->iov_len = currIov->iov_len - bufOffset;
                        readVecCnt++;   // add thus buffer to the iovec list used with readv
                    }
                    currVecBegin = currVecEnd;
                }
            }

            // Attempt to read bytes
            n = _ReadV(self, readIov, readVecCnt);
            if (n < 0)
            {
                if (!_TestEINTR())
                {
                    // Check for would block error
                    if (_TestWOULDBLOCK() || _TestEAGAIN())
                    {
                        free(readIov);
                        unlockMutex(self);
                        return MI_RESULT_WOULD_BLOCK;
                    }
                    // read failed for another reason
                    *sizeRead = 0;
                    free(readIov);
                    unlockMutex(self);
                    LOGE2((ZT("Sock_ReadV - _ReadV failed. errno: %d (%s)"), LastSocketError, strerror(LastSocketError)));
                    return MI_RESULT_FAILED;
                }
                n = 0;
            }
            else
            {
                *sizeRead += n;
                if (*sizeRead >= amtNeeded)
                {
                    break;
                }
            }
            usleep(100000);                 // wait a while before trying again
        } // for (readAttempts ...)
        free(readIov);
        unlockMutex(self);
        LOGD2((ZT("Sock_ReadV - Successful exit. socket: %d, bytes written: %u"), self, (unsigned int)*sizeRead));
        return MI_RESULT_OK;
    }
}

/*
 Write from memory pointed to by a vector of buffer pointers (a gather vector)

 @param [in]    self - the socket to write to
 @param [in]    iov - the array of buffer descriptors telling where to read
 @param [in]    iovcnt - the soize of iov
 @param [out]   sizeWritten - how many bytes were actually written

 @returns       an MI_Result: MI_RESULT_OK for succeess, another value for failure
*/
MI_Result Sock_WriteV(
    Sock self,
    const struct iovec* iov,
    size_t iovcnt,
    size_t* sizeWritten)
{
#ifdef __hpux
    usleep(1000);                       // wait 1 ms for timed-out socket to recover on HP_UX
#endif
    LOGD2((ZT("Sock_WriteV - Begin. socket: %d, no. buffers: %u"), self, (unsigned int)iovcnt));

    if (iovcnt == 0)
    {
        LOGD2((ZT("Sock_WriteV - 0 buffers. Returning OK")));
        return MI_RESULT_OK;
    }

    int isNonBlocking = lockMutex(self);

    int n;

    // Make a copy of the vector
    int memNeeded = sizeof(struct iovec) * iovcnt;
    struct iovec* baseVector = (struct iovec *)malloc(memNeeded); // the fixed pointer used for freeing
    memcpy(baseVector, iov, memNeeded);

    size_t vectorsLeft = iovcnt;

    struct iovec* currentVector = baseVector;   // the variable pointer used in the loop
    *sizeWritten = 0;

    int flags = fcntl(self, F_GETFL, 0);

    if (isNonBlocking != 0)
    {
        fd_set SingleSocketSet;
        FD_ZERO(&SingleSocketSet);

        FD_SET(self, &SingleSocketSet);

        struct timeval TimeOut;

        TimeOut.tv_sec = 0;
        TimeOut.tv_usec = 20000;
        int numReady = select(self + 1, NULL, &SingleSocketSet, NULL, &TimeOut);
        if (numReady > 0)
        {
            flags &= ~O_NONBLOCK;
            fcntl(self, F_SETFL, flags);
        }
        else
        {
            LOGW2((ZT("Sock_Read - Select says socket %d has no data. Returning MI_RESULT_WOULD_BLOCK"), self));
            free(baseVector);
            unlockMutex(self);
            return MI_RESULT_WOULD_BLOCK;
        }
    }

    LOGD2((ZT("Sock_WriteV - Socket send. Attempting %u vectors."), (unsigned int)vectorsLeft));
    errno = 0;
    n = _WriteV(self, currentVector, vectorsLeft);
    LOGD2((ZT("Sock_WriteV - Socket send. %u vectors requested, %d bytes sent."), (unsigned int)vectorsLeft, n));

    if (isNonBlocking != 0)
    {
        flags |= O_NONBLOCK;
        fcntl(self, F_SETFL, flags);
    }

    int Ret = MI_RESULT_OK;
    if (n > 0)
    {
        *sizeWritten = n;
    }
    else
    {
        // Why yes, this is a magic flag to the rest of the system that the socket had an unrecoverable
        // error and was closed.  This isn't completely clear?
        LOGW2((ZT("Sock_Read - Error. socket: %d, Returning MI_RESULT_FAILED"), self));
        *sizeWritten = 0;
        Ret = MI_RESULT_FAILED;
    }

    free(baseVector);
    unlockMutex(self);
    LOGD2((ZT("Sock_WriteV - Socket send. bytes written: %u"), (unsigned int)*sizeWritten));
    return Ret;
}

MI_Result Sock_CreateListener(
    Sock* sock,
    const Addr* addr)
{
    LOGD2((ZT("Sock_CreateListener - Begin")));
    MI_Result r;

    /* Create socket */
    {
        r = Sock_Create(sock, addr->is_ipv6);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("Sock_CreateListener - Sock_Create failed. error: %d (%s)"), (int)r, mistrerror(r)));
            return r;
        }
    }

    /* Reuse the address (to prevent binding failures) */
    {
        r = Sock_ReuseAddr(*sock, MI_TRUE);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(*sock);
            LOGE2((ZT("Sock_CreateListener - Sock_ReuseAddr failed. error: %d (%s)"), (int)r, mistrerror(r)));
            return r;
        }
    }

    /* Bind the socket to the address */
    {
        r = Sock_Bind(*sock, addr);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(*sock);
            LOGE2((ZT("Sock_CreateListener - Sock_Bind failed. error: %d (%s)"), (int)r, mistrerror(r)));
            return r;
        }
    }

    /* Listen on this socket for connections */
    {
        r = Sock_Listen(*sock);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(*sock);
            unlockMutex(*sock);
            LOGE2((ZT("Sock_CreateListener - Sock_Listen failed. error: %d (%s)"), (int)r, mistrerror(r)));
            return r;
        }
    }

    LOGD2((ZT("Sock_CreateListener - Successful exit. socket: %d"), (int)*sock));
    return MI_RESULT_OK;
}

#if !defined(CONFIG_OS_WINDOWS)

static char s_oldWD[PATH_MAX];          // the old working directory if it was changed to use a short special file name for the sockaddr_un structure

/*
 Populate a sockaddr structure from the given socket special file name.  If the special
 file path name is too long (92 - 108 characters, including the trailing NUL, depending
 on platform), change to the special files's directory and populate the structure
 with the file's base name only.

 @param[in]     sock - The descriptor of the socket to be named
 @param[in]     socketName - The name of the socket special file
 @param[out]    addr - The sockaddr_un structure to populate
 @param[out]    socketFileNameIsLong - True if only the base socket file name was set in the structure

 @returns       MI_RESULT_OK on success, another MI_Result on error
*/
MI_Result CreateSpecialFileAndBindSocket(
    Sock* sock,
    const char* socketName,
    MI_Boolean isListener)
{
    struct sockaddr_un addr_un;
    MI_Boolean socketFileNameIsLong;

    LOGD2((ZT("CreateSpecialFileAndBindSocket - Begin. socket file: %s"), socketName));
    if (sock == NULL || socketName == NULL)
    {
        LOGE((ZT("CreateSpecialFileAndBindSocket - internal argument error")));
        LOGE2((ZT("CreateSpecialFileAndBindSocket - internal argument error")));
        return MI_RESULT_FAILED;
    }

    memset(&addr_un, 0, sizeof (struct sockaddr_un));
    addr_un.sun_family = AF_UNIX;
    socketFileNameIsLong = MI_FALSE;

    // check if the socket name is longer that the size of the sun_path array (92...108 characters)
    if (strlen(socketName) >= sizeof addr_un.sun_path)
    {
        // this branch is taken if the name won't fit in the 92...108 characters
        char socketDirName[sizeof addr_un.sun_path];
        char* pBaseName = strrchr(socketName, '/');

        if (pBaseName == NULL || strlen(pBaseName + 1) >= sizeof addr_un.sun_path)
        {
            // if the base name segment is too long, we can't work
            LOGE((ZT("CreateSpecialFileAndBindSocket - Socket file path too long (> %u): '%s'"), (unsigned int)(sizeof addr_un.sun_path - 1), socketName));
            LOGE2((ZT("CreateSpecialFileAndBindSocket - Socket file path too long (> %u): '%s'"), (unsigned int)(sizeof addr_un.sun_path - 1), socketName));
            return MI_RESULT_FAILED;
        }

        // separate the directory part from the base name and change to the directory
        // set the socket special file name to just the base name to make it < 92...108 characters
        strncpy(socketDirName, socketName, (size_t)(pBaseName - socketName));
        socketDirName[pBaseName - socketName] = '\0';
        strcpy(addr_un.sun_path, pBaseName + 1);
        if (getcwd(s_oldWD, PATH_MAX) == NULL || chdir(socketDirName) < 0)
        {                               // can't get working dir. or can't change to new dir.
            LOGE((ZT("CreateSpecialFileAndBindSocket - Cannot change current working directory")));
            LOGE2((ZT("CreateSpecialFileAndBindSocket - Cannot change current working directory")));
            return MI_RESULT_FAILED;
        }
        socketFileNameIsLong = MI_TRUE;
    }
    else
    {
        strcpy(addr_un.sun_path, socketName);
    }

    if (isListener)
    {
        // Try to bind.  If we can, then the server is running.  If we can't, then delete the socket
        // special file and try to bind again.  There has to be a better way of doing this.
        // if (bind(*sock, &addr->sock_addr, sizeof (struct sock_addr) + strlen(addr.sun_path) < 0))
        unlink(socketName);
        if (bind(*sock, (const struct sockaddr*)&addr_un, sizeof (struct sockaddr_un)) < 0)
        {
            // The first bind failed.  Unlink the file and try again.
            LOGD2((ZT("CreateSpecialFileAndBindSocket (listener) unlinking socket file %s"), socketName));
            unlink(socketName);

            if (bind(*sock, (const struct sockaddr*)&addr_un, sizeof (struct sockaddr_un)) < 0)
            {
                LOGE2((ZT("CreateSpecialFileAndBindSocket (listener) -- Unable to unlink and bind again to transport endpoint %s"), socketName));

                if (socketFileNameIsLong)
                {
                    (void)chdir(s_oldWD);
                }
                LOGE2((ZT("CreateSpecialFileAndBindSocket (listener) - Cannot change current working directory")));
                return MI_RESULT_FAILED;
            }
        }
        LOGD2((ZT("CreateSpecialFileAndBindSocket (listener) - Bound socket %d to socket file %s"), (int)*sock, socketName));
    }
    else
    {
        MI_Result r;
        unsigned int connectionTries = 0;

        // Try to connect for sending.
        while (connectionTries < 500)
        {
            errno = 0;
            r = connect(*sock, (const struct sockaddr *)&addr_un, sizeof (struct sockaddr_un));
            LastSocketError = errno;

            // If we're already connected, then we're done.  Note that when we're
            // working with a non-blocking socket, we'll get one of these when the
            // connection finally completes.
            if (LastSocketError == EISCONN || LastSocketError == EALREADY)
            {
                break;  // If it's a non-blocking socket, at some point it will turn to this
            }

            if (_TestWOULDBLOCK())
            {
                connectionTries++;
                usleep(50);
                continue;
            }

            if (r != 0)
            {
                if (socketFileNameIsLong)
                {
                    (void)chdir(s_oldWD);
                }

                if (_TestWOULDBLOCK() || _TestEAGAIN())
                {
                    return MI_RESULT_WOULD_BLOCK;
                }

                LOGE2((ZT("CreateSpecialFileAndBindSocket (connector) - Connect-not blocking/again and not zero. errno: %d (%s)"), LastSocketError, strerror(LastSocketError)));
                return MI_RESULT_FAILED;
            }
            break;
        }

        if (_TestWOULDBLOCK())
        {
            LOGE2((ZT("CreateSpecialFileAndBindSocket (connector) - Socket %d is still in connection sock_wait state after %d tries."), (int)*sock, connectionTries));
        }
    }

    // if we changed the directory to get around a too-long special file name, change it back
    if (socketFileNameIsLong)
    {
        (void)chdir(s_oldWD);
    }

    LOGD2((ZT("CreateSpecialFileAndBindSocket - Successful exit")));
    return MI_RESULT_OK;
}

#endif

/*
 Create the listener side of a socket, both of whose sides are on the local computer

 @param[out]    sock - The socket descriptor
 @param[in]     socketName - The name of the socket special file

 @returns       MI_RESULT_OK on success, another MI_Result on error
*/
MI_Result Sock_CreateLocalListener(
    Sock* sock,
    const char* socketName)
{
    LOGD2((ZT("Sock_CreateLocalListener - Begin. socket file: %s"), socketName));
    if (globalSocketName != NULL)
    {
        free(globalSocketName);
        globalSocketName = NULL;
        globalSocketName = (char *)malloc(strlen(socketName) + 1);
        strcpy(globalSocketName, socketName);
    }

#if defined(CONFIG_OS_WINDOWS)
    unsigned short port = (unsigned short)atol(socketName);
    Addr addr;

    Addr_InitAny(&addr, port);
    return Sock_CreateListener(sock, &addr);
#else
    MI_Result r;

    *sock = socket(PF_UNIX, SOCK_STREAM, 0);
    if (*sock < 0)
    {
        return MI_RESULT_FAILED;
    }

    LOGD2((ZT("Sock_CreateLocalListener  - Allocated socket: %d"), (int)*sock));
    if (MI_RESULT_OK != Sock_SetCloseOnExec(*sock, MI_TRUE))
    {
        LOGW((ZT("fcntl(F_SETFD) failed")));
    }

    lockMutex(*sock);

    /* Reuse the address (to prevent binding failures) */
    r = Sock_ReuseAddr(*sock, MI_TRUE);

    if (r != MI_RESULT_OK)
    {
        LOGE2((ZT("Sock_CreateLocalListener - Sock_ResuseAddr failed. error: %d (%s)"), (int)r, mistrerror(r)));
        Sock_Close(*sock);
        unlockMutex(*sock);
        return r;
    }

    r = CreateSpecialFileAndBindSocket(sock, socketName, MI_TRUE);
    if (r != MI_RESULT_OK)
    {
        Sock_Close(*sock);
        unlockMutex(*sock);
        LOGE2((ZT("Sock_CreateLocalListener - Sock_CreateSpecialFileAndBindSocket - Sock_ResuseAddr failed. error: %d (%s)"), (int)r, mistrerror(r)));
        return r;
    }

    /* Change mode to allow non-root to connect to it (they need 'w' to connect) */
    chmod(socketName, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);

    /* Listen on this socket for connections */
    {
        r = Sock_Listen(*sock);
        LOGD2((ZT("CreateLocalListener - Now listening on socket %d"), (int)*sock));

        if (r != MI_RESULT_OK)
        {
            Sock_Close(*sock);
            unlockMutex(*sock);
            LOGE2((ZT("Sock_CreateLocalListener - Sock_Listen failed. error: %d (%s)"), (int)r, mistrerror(r)));
            return r;
        }
    }

    LOGD2((ZT("Sock_CreateLocalListener - Successful exit. socket: %d"), (int)*sock));
    unlockMutex(*sock);
    return MI_RESULT_OK;
#endif
}

/*
 Create the sender side of a socket, both of whose sides are on the local computer

 @param[out]    sock - The socket descriptor
 @param[in]     socketName - The name of the socket special file

 @returns       MI_RESULT_OK on success, another MI_Result on error
*/
MI_Result Sock_CreateLocalConnector(
    Sock* sock,
    const char* socketName)
{
    LOGD2((ZT("Sock_CreateLocalConnector - Begin. socket file: %s"), socketName));

#if defined(CONFIG_OS_WINDOWS)
    unsigned short port = (unsigned short)atol(socketName);
    Addr addr;
    MI_Result r;

    // Initialize address.
    lockMutex(*sock);
    r = Addr_Init(&addr, "127.0.0.1", port, MI_FALSE);
    if (r != MI_RESULT_OK)
    {
        return MI_RESULT_FAILED;
    }

    // Create client socket.
    r = Sock_Create(sock);
    if (r != MI_RESULT_OK)
    {
        close(*sock);
        return MI_RESULT_FAILED;
    }

    // unlock mutex now because non-blocking sockets won't unlock if they were blocking when locked
    unlockMutex(*sock);

    r = Sock_SetBlocking(*sock, MI_FALSE);
    if (r != MI_RESULT_OK)
    {
        Sock_Close(*sock);
        return MI_RESULT_FAILED;
    }

    // Connect to server.
    lockMutex(*sock);
    r = Sock_Connect(*sock, &addr);
    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        Sock_Close(*sock);
        return MI_RESULT_FAILED;
    }

    unlockMutex(*sock);
    return r;
#else
    MI_Result r;

    LastSocketError = 0;
    *sock = socket(PF_UNIX, SOCK_STREAM, 0);
    LastSocketError = errno;
    if (*sock < 0)
    {
        LOGE2((ZT("Sock_CreateLocalConnector - Error %d (%s) creating socket"), LastSocketError, strerror(LastSocketError)));
        return MI_RESULT_FAILED;
    }

    if (MI_RESULT_OK != Sock_SetCloseOnExec(*sock, MI_TRUE))
    {
        LOGW((ZT("fcntl(F_SETFD) failed")));
    }

    // unlock mutex now because non-blocking sockets won't unlock if they were blocking when locked
    unlockMutex(*sock);
    r = Sock_SetBlocking(*sock, MI_FALSE);
    if (r != MI_RESULT_OK)
    {
        Sock_Close(*sock);
        LOGE2((ZT("Sock_CreateLocalConnector - Error setting non-blocking. socket: %d, result: %d (%s)"), (int)*sock, (int)r, mistrerror(r)));
        return MI_RESULT_FAILED;
    }

    lockMutex(*sock);
    r = CreateSpecialFileAndBindSocket(sock, socketName, MI_FALSE);
    if (r != MI_RESULT_OK)
    {
        Sock_Close(*sock);
        unlockMutex(*sock);
        LOGE2((ZT("Sock_CreateLocalConnector - Error binding. socket: %d: result: %d (%s)"), (int)*sock, (int)r, mistrerror(r)));
        return r;
    }

    unlockMutex(*sock);
    LOGD2((ZT("Sock_CreateLocalListener - Successful exit. socket: %d"), (int)*sock));
    return MI_RESULT_OK;
#endif
}
