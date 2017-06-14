// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#ifndef INCLUDED_SOCKET_WRAPPER_HPP
#define INCLUDED_SOCKET_WRAPPER_HPP


#include "internal_counted_ptr.hpp"


#include <cstdlib>


#define EXPORT_PUBLIC __attribute__ ((visibility ("default")))


class EXPORT_PUBLIC socket_wrapper : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<socket_wrapper> Ptr;

    enum Result
    {
        SUCCESS = EXIT_SUCCESS,
        SEND_FAILED,
        RECV_FAILED,
        SOCKET_CLOSED,
    };

    typedef unsigned char byte_t;

    static int const INVALID_SOCKET = -1;


    EXPORT_PUBLIC explicit /*ctor*/ socket_wrapper (int fd);
    EXPORT_PUBLIC /*dtor*/ ~socket_wrapper ();

    EXPORT_PUBLIC int send (byte_t const* const pData, size_t const& nBytes);
    EXPORT_PUBLIC int recv (byte_t* const pDataOut, size_t const& nBytes);

    EXPORT_PUBLIC void close ();

private:

    /*ctor*/ socket_wrapper (socket_wrapper const&); // = delete
    socket_wrapper& operator = (socket_wrapper const&); // = delete

    int m_FD;
};


#undef EXPORT_PUBLIC


#endif // INCLUDED_SOCKET_WRAPPER_HPP
