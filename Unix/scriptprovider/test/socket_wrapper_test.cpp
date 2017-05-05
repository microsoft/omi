#include "socket_wrapper_test.hpp"


#include <cstdlib>
#include <errno.h>
#include <signal.h>
#include <socket_wrapper.hpp>
#include <sys/socket.h>
#include <unistd.h>


using test::socket_wrapper_test;


namespace
{


void
create_rand_blob (
    unsigned char* blob,
    size_t size)
{
    for (size_t i = 0; i < size; i += sizeof (int))
    {
        *(reinterpret_cast<int*>(blob + i)) = rand ();
    }
    size_t mod = size % sizeof (int);
    if (0 < mod)
    {
        int val = rand ();
        for (size_t i = 0; i < mod; ++i)
        {
            blob[size / sizeof (int) + i] =
                *(reinterpret_cast<unsigned char*>(&val) + i);
        }
    }
}


} // namespace (unnamed)


/*ctor*/
socket_wrapper_test::socket_wrapper_test ()
{
    add_test (MAKE_TEST (socket_wrapper_test::test01));
    add_test (MAKE_TEST (socket_wrapper_test::test02));
    add_test (MAKE_TEST (socket_wrapper_test::test03));
    add_test (MAKE_TEST (socket_wrapper_test::test04));
}


int
socket_wrapper_test::test01 ()
{
    // test ctor
    int rval = EXIT_SUCCESS;
    int fds[2];
    if (-1 != socketpair (AF_UNIX, SOCK_STREAM, 0, fds))
    {
        socket_wrapper sock0 (fds[0]);
        socket_wrapper sock1 (fds[1]);
    }
    else
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
socket_wrapper_test::test02 ()
{
    // test dtor
    int rval = EXIT_SUCCESS;
    int fds[2];
    if (-1 != socketpair (AF_UNIX, SOCK_STREAM, 0, fds))
    {
        {
            socket_wrapper sock0 (fds[0]);
            socket_wrapper sock1 (fds[1]);
        }
        if (-1 != write (fds[0], &rval, sizeof (rval)) ||
            EBADF != errno)
        {
            rval = EXIT_FAILURE;
        }
        if (-1 != write (fds[1], &rval, sizeof (rval)) ||
            EBADF != errno)
        {
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
socket_wrapper_test::test03 ()
{
    // test close
    int rval = EXIT_SUCCESS;
    int fds[2];
    signal (SIGPIPE, SIG_IGN);
    if (-1 != socketpair (AF_UNIX, SOCK_STREAM, 0, fds))
    {
        socket_wrapper sock0 (fds[0]);
        socket_wrapper sock1 (fds[1]);
        sock0.close ();
        if (-1 != write (fds[0], &rval, sizeof (rval)) ||
            EBADF != errno)
        {
            rval = EXIT_FAILURE;
        }
        if (-1 != write (fds[1], &rval, sizeof (rval)) ||
            EPIPE != errno)
        {
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        rval = EXIT_FAILURE;
    }
    signal (SIGPIPE, SIG_DFL);
    return rval;
}


int
socket_wrapper_test::test04 ()
{
    // test send and recv
    int rval = EXIT_SUCCESS;
    size_t const BLOB_SIZE = 20;
    int fds[2];
    if (-1 != socketpair (AF_UNIX, SOCK_STREAM, 0, fds))
    {
        socket_wrapper sock0 (fds[0]);
        socket_wrapper sock1 (fds[1]);
        int originalBlob[BLOB_SIZE];
        create_rand_blob (reinterpret_cast<unsigned char*>(originalBlob),
                          sizeof (originalBlob));
        if (socket_wrapper::SUCCESS != sock0.send (
                reinterpret_cast<socket_wrapper::byte_t*>(originalBlob),
                sizeof (originalBlob)))
        {
            rval = EXIT_FAILURE;
        }
        int receivedBlob[BLOB_SIZE];
        if (socket_wrapper::SUCCESS != sock1.recv (
                reinterpret_cast<socket_wrapper::byte_t*>(receivedBlob),
                sizeof (receivedBlob)))
        {
            rval = EXIT_FAILURE;
        }
        if (0 != memcmp (originalBlob, receivedBlob, sizeof (originalBlob)))
        {
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}
