// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#include "shared_protocol.hpp"


#include <sstream>


namespace protocol
{


int
recv_boolean (
    MI_Boolean* const pBooleanOut,
    socket_wrapper& sock)
{
    assert (pBooleanOut);
    protocol::boolean_t val;
    int rval = sock.recv (&val, sizeof (protocol::boolean_t));
    if (socket_wrapper::SUCCESS == rval)
    {
        *pBooleanOut = val ? MI_TRUE : MI_FALSE;
    }
    return rval;
}


#if (1)
#define PRINT_SEND_STR (PRINT_BOOKENDS)
#else
#define PRINT_SEND_STR (0)
#endif

#if (PRINT_SEND_STR)
#define SEND_STR_BOOKEND(x) SCX_BOOKEND (x)
#define SEND_STR_PRINT(x) SCX_BOOKEND_PRINT (x)
#else
#define SEND_STR_BOOKEND(x)
#define SEND_STR_PRINT(x)
#endif

int
send (
    MI_Char const* const str,
    socket_wrapper& sock)
{
    //SCX_BOOKEND ("protocol::send (MI_Char*)");
    SEND_STR_BOOKEND ("protocol::send (MI_Char*)");
    int rval = socket_wrapper::SUCCESS;
    if (NULL != str)
    {
        ssize_t const nStrLen = strlen (str);
#if (PRINT_SEND_STR)
        std::ostringstream strm;
        strm << "nStrLen: " << nStrLen;
        SEND_STR_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
        strm << "str: \"" << str << '\"';
        SEND_STR_PRINT (strm.str ());
#endif
        rval = send_item_count (nStrLen, sock);
        if (socket_wrapper::SUCCESS == rval &&
            0 < nStrLen)
        {
            rval = sock.send (
                reinterpret_cast<socket_wrapper::byte_t const*>(str),
                nStrLen);
        }
    }
    else
    {
        SEND_STR_PRINT ("str is NULL");
        rval = send_item_count (NULL_STRING, sock);
    }
    return rval;
}


#if (1)
#define PRINT_SEND_DATETIME (PRINT_BOOKENDS)
#else
#define PRINT_SEND_DATETIME (0)
#endif

#if (PRINT_SEND_DATETIME)
#define SEND_DATETIME_BOOKEND(x) SCX_BOOKEND (x)
#define SEND_DATETIME_PRINT(x) SCX_BOOKEND_PRINT (x)
#else
#define SEND_DATETIME_BOOKEND(x)
#define SEND_DATETIME_PRINT(x)
#endif

int
send (
    MI_Datetime const& value,
    socket_wrapper& sock)
{
    //SCX_BOOKEND ("protocol::send (MI_Datetime)");
    SEND_DATETIME_BOOKEND ("protocol::send (MI_Datetime)");
    int rval = send_boolean (value.isTimestamp, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        if (value.isTimestamp)
        {
            rval = send (value.u.timestamp, sock);
        }
        else
        {
            rval = sock.send (
                reinterpret_cast<socket_wrapper::byte_t const*>(
                    &(value.u.interval)), 5 * sizeof (MI_Uint32));
        }
    }
    return rval;
}


#if (1)
#define PRINT_RECV_STR (PRINT_BOOKENDS)
#else
#define PRINT_RECV_STR (0)
#endif

#if (PRINT_RECV_STR)
#define RECV_STR_BOOKEND(x) SCX_BOOKEND (x)
#define RECV_STR_PRINT(x) SCX_BOOKEND_PRINT (x)
#else
#define RECV_STR_BOOKEND(x)
#define RECV_STR_PRINT(x)
#endif

int
recv (
    MI_Char** const ppStringOut,
    socket_wrapper& sock)
{
    //SCX_BOOKEND ("protocol::recv (MI_Char**)");
    RECV_STR_BOOKEND ("protocol::recv (MI_Char**)");
    assert (ppStringOut);
    item_count_t count;
    int rval = recv_item_count (&count, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
#if (PRINT_RECV_STR)
        std::ostringstream strm;
        strm << "strlen is " << count;
        RECV_STR_PRINT (strm.str ());
#endif
        util::unique_ptr<MI_Char[]> pText;
        if (NULL_STRING != count &&
            0 != count)
        {
            pText.reset (new MI_Char[count +1]);
            pText[count] = '\0';
            rval = sock.recv (
                reinterpret_cast<socket_wrapper::byte_t*>(pText.get ()),
                count * sizeof (MI_Char));
#if (PRINT_RECV_STR)
            if (socket_wrapper::SUCCESS == rval)
            {
                strm.str ("");
                strm.clear ();
                strm << "string is \"" << pText.get () << "\"";
                RECV_STR_PRINT (strm.str ());
            }
            else
            {
                RECV_STR_PRINT ("failed to read string");
            }
        }
        else
        {
            if (NULL_STRING == count)
            {
                RECV_STR_PRINT ("str is NULL");
            }
            else
            {
                RECV_STR_PRINT ("count is 0");
            }
#endif
        }
        if (socket_wrapper::SUCCESS == rval)
        {
            if (NULL != *ppStringOut)
            {
                delete[] *ppStringOut;
            }
            *ppStringOut = pText.release ();
        }
    }
    return rval;
}


#if (1)
#define PRINT_RECV_DATETIME (PRINT_BOOKENDS)
#else
#define PRINT_RECV_DATETIME (0)
#endif

#if (PRINT_RECV_DATETIME)
#define RECV_DATETIME_BOOKEND(x) SCX_BOOKEND (x)
#define RECV_DATETIME_PRINT(x) SCX_BOOKEND_PRINT (x)
#else
#define RECV_DATETIME_BOOKEND(x)
#define RECV_DATETIME_PRINT(x)
#endif

int
recv (
    MI_Datetime* const pValueOut,
    socket_wrapper& sock)
{
    //SCX_BOOKEND ("protocol::recv (MI_Datetime)");
    RECV_DATETIME_BOOKEND ("protocol::recv (MI_Datetime)");
    assert (pValueOut);
    MI_Boolean isTimestamp;
    int rval = recv_boolean (&isTimestamp, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        if (isTimestamp)
        {
            pValueOut->isTimestamp = MI_TRUE;
            rval = recv (&(pValueOut->u.timestamp), sock);
        }
        else
        {
            pValueOut->isTimestamp = MI_FALSE;
            rval = sock.recv (
                reinterpret_cast<socket_wrapper::byte_t*>(
                    &(pValueOut->u.interval)), 5 * sizeof (MI_Uint32));
        }
    }
    return rval;
}


} // namespace protocol
