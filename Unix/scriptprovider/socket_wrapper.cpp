#include "socket_wrapper.hpp"


#include "debug_tags.hpp"


#include <errno.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>


namespace
{


template<typename char_t, typename traits_t>
std::basic_ostream<char_t, traits_t>& errnoText (
    std::basic_ostream<char_t, traits_t>& strm)
{
    static size_t const BUFFER_LEN = 256;
    char errorBuffer[BUFFER_LEN];
    int err = errno;
    char* pErrorText = strerror_r (err, errorBuffer, BUFFER_LEN);
    strm << pErrorText;
    errno = err;
    return strm;
}


}


/*ctor*/
socket_wrapper::socket_wrapper (
    int fd)
    : m_FD (fd)
{
    //SCX_BOOKEND ("socket_wrapper::ctor");
}


/*dtor*/
socket_wrapper::~socket_wrapper ()
{
    //SCX_BOOKEND ("socket_wrapper::dtor");
    close ();
}


int
socket_wrapper::send (
    byte_t const* const pData,
    size_t const& nBytes)
{
    //SCX_BOOKEND ("socket_wrapper::send");
    int rval = SUCCESS;
    ssize_t nBytesSent = 0;
    while (SUCCESS == rval &&
           -1 != nBytesSent &&
           nBytes > static_cast<size_t> (nBytesSent))
    {
        ssize_t nSent = write (m_FD, pData + nBytesSent, nBytes - nBytesSent);
        if (-1 != nSent)
        {
            nBytesSent += nSent;
        }
        else if (EINTR != errno)
        {
            // error (check errno { EACCESS, EAGAIN, EWOULDBLOCK, EBADF,
            //                      ECONNRESET, EDESTADDRREQ, EFAULT, EINVAL,
            //                      EISCONN, EMSGSIZE, ENOBUFS, ENOMEM,
            //                      ENOTCONN, ENOTSOCK, EOPNOTSUPP, EPIPE })
            close ();
            rval = SEND_FAILED;
            //std::ostringstream strm;
            //strm << "error on socket: (" << errno << ") \"" << errnoText
            //     << '\"';
            //SCX_BOOKEND_PRINT (strm.str ());
            //std::cerr << strm.str () << std::endl;
        }
    }
    return rval;
}


int
socket_wrapper::recv (
    byte_t* const pDataOut,
    size_t const& nBytes)
{
    //SCX_BOOKEND ("socket_wrapper::recv");
    int rval = SUCCESS;
    ssize_t nBytesRead = 0;
    while (SUCCESS == rval &&
           nBytes > static_cast<size_t> (nBytesRead))
    {
        ssize_t nRead = read (m_FD, pDataOut + nBytesRead, nBytes - nBytesRead);
        if (0 < nRead)
        {
            nBytesRead += nRead;
        }
        else if (0 == nRead)
        {
            // socket closed
            close ();
            rval = SOCKET_CLOSED;
            //SCX_BOOKEND_PRINT ("socket closed unexpectedly");
            //std::cerr << "socket closed unexpectedly" << std::endl;
        }
        else if (EINTR != errno)
        {
            // Error - check errno { EAGAIN, EBADF, EFAULT, EINVAL, EIO,
            //                       EISDIR }
            close ();
            rval = RECV_FAILED;
            //std::ostringstream strm;
            //strm << "error on socket: (" << errno << ") \"" << errnoText
            //     << '\"';
            //SCX_BOOKEND_PRINT (strm.str ());
            //std::cerr << strm.str () << std::endl;
            //strm.str ("");
            //strm.clear ();
        }
    }
    return rval;
}


void
socket_wrapper::close ()
{
    if (INVALID_SOCKET != m_FD)
    {
        //SCX_BOOKEND ("socket_wrapper::close");
        ::close (m_FD);
        m_FD = INVALID_SOCKET;
    }
}
