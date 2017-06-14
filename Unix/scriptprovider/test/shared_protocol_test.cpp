// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#include "shared_protocol_test.hpp"


#include <cstdlib>
#include <errno.h>
#include <mi_type.hpp>
#include <shared_protocol.hpp>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>


using test::shared_protocol_test;


namespace
{


template<typename T, size_t N>
size_t
card (
    T const (&)[N])
{
    return N;
}


//void
//create_rand_blob (
//    unsigned char* blob,
//    size_t size)
//{
//    for (size_t i = 0; i < size; i += sizeof (int))
//    {
//        *(reinterpret_cast<int*>(blob + i)) = rand ();
//    }
//    size_t mod = size % sizeof (int);
//    if (0 < mod)
//    {
//        int val = rand ();
//        for (size_t i = 0; i < mod; ++i)
//        {
//            blob[size / sizeof (int) + i] =
//                *(reinterpret_cast<unsigned char*>(&val) + i);
//        }
//    }
//}


int
create_sockets (
    socket_wrapper::Ptr* ppSock0,
    socket_wrapper::Ptr* ppSock1)
{
    int rval = EXIT_SUCCESS;
    int fds[2];
    if (-1 != socketpair (AF_UNIX, SOCK_STREAM, 0, fds))
    {
        *ppSock0 = new socket_wrapper (fds[0]);
        *ppSock1 = new socket_wrapper (fds[1]);
    }
    else
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


char
rand_char ()
{
    return static_cast<char>(rand () % 95 + 32);
}


void
fill_char_array (
    char* pStart,
    char* pEnd)
{
    for (char* pos = pStart; pos != pEnd; ++pos)
    {
        *pos = rand_char ();
    }
}


char*
create_rand_string (
    size_t len)
{
    char* str = new char[len + 1];
    fill_char_array (str, str + len);
    str[len] = '\0';
    return str;
}



} // namespace (unnamed)


/*ctor*/
shared_protocol_test::shared_protocol_test ()
{
    add_test (MAKE_TEST (shared_protocol_test::test01));
    add_test (MAKE_TEST (shared_protocol_test::test02));
    add_test (MAKE_TEST (shared_protocol_test::test03));
    add_test (MAKE_TEST (shared_protocol_test::test04));
    add_test (MAKE_TEST (shared_protocol_test::test05));
    add_test (MAKE_TEST (shared_protocol_test::test06));
    add_test (MAKE_TEST (shared_protocol_test::test07));
    add_test (MAKE_TEST (shared_protocol_test::test08));
    add_test (MAKE_TEST (shared_protocol_test::test09));
    add_test (MAKE_TEST (shared_protocol_test::test10));
    add_test (MAKE_TEST (shared_protocol_test::test11));
    add_test (MAKE_TEST (shared_protocol_test::test12));
    add_test (MAKE_TEST (shared_protocol_test::test13));
    add_test (MAKE_TEST (shared_protocol_test::test14));
    add_test (MAKE_TEST (shared_protocol_test::test15));
    add_test (MAKE_TEST (shared_protocol_test::test16));
    add_test (MAKE_TEST (shared_protocol_test::test17));
    add_test (MAKE_TEST (shared_protocol_test::test18));
}


int
shared_protocol_test::test01 ()
{
    // test send_item_count and recv_item_count
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        protocol::item_count_t countOut =
            static_cast<protocol::item_count_t>(rand () % 1000);
        rval = protocol::send_item_count (countOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            protocol::item_count_t countIn;
            rval = protocol::recv_item_count (&countIn, *recvSock);
            if (EXIT_SUCCESS == rval &&
                countOut != countIn)
            {
                rval = EXIT_FAILURE;
            }
        }
    }
    return rval;
}


int
shared_protocol_test::test02 ()
{
    // test send_boolean and recv_boolean
    MI_Boolean vals[] = {
        MI_TRUE,
        MI_FALSE,
    };
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    for (size_t i = 0; EXIT_SUCCESS == rval && i < card (vals); ++i)
    {
        rval = protocol::send_boolean (vals[i], *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Boolean boolIn;
            rval = protocol::recv_boolean (&boolIn, *recvSock);
            if (EXIT_SUCCESS == rval &&
                vals[i] != boolIn)
            {
                rval = EXIT_FAILURE;
            }
        }
    }
    return rval;
}


int
shared_protocol_test::test03 ()
{
    // test send_type and recv_type
    protocol::data_type_t vals[] = {
        MI_BOOLEAN,
        MI_UINT8,
        MI_SINT8,
        MI_UINT16,
        MI_SINT16,
        MI_UINT32,
        MI_SINT32,
        MI_UINT64,
        MI_SINT64,
        MI_REAL32,
        MI_REAL64,
        MI_CHAR16,
        MI_DATETIME,
        MI_STRING,
        MI_REFERENCE,
        MI_INSTANCE,
        MI_BOOLEANA,
        MI_UINT8A,
        MI_SINT8A,
        MI_UINT16A,
        MI_SINT16A,
        MI_UINT32A,
        MI_SINT32A,
        MI_UINT64A,
        MI_SINT64A,
        MI_REAL32A,
        MI_REAL64A,
        MI_CHAR16A,
        MI_DATETIMEA,
        MI_STRINGA,
        MI_REFERENCEA,
        MI_INSTANCEA,
    };
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    for (size_t i = 0; EXIT_SUCCESS == rval && i < card (vals); ++i)
    {
        rval = protocol::send_type (vals[i], *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            protocol::data_type_t typeIn;
            rval = protocol::recv_type (&typeIn, *recvSock);
            if (EXIT_SUCCESS == rval &&
                vals[i] != typeIn)
            {
                rval = EXIT_FAILURE;
            }
        }
    }
    return rval;
}


int
shared_protocol_test::test04 ()
{
    // test send_opcode and recv_opcode
    protocol::opcode_t vals[] = {
        protocol::MODULE_LOAD,
        protocol::MODULE_UNLOAD,
        protocol::CLASS_LOAD,
        protocol::CLASS_UNLOAD,
        protocol::GET_INSTANCE,
        protocol::ENUMERATE_INSTANCES,
        protocol::CREATE_INSTANCE,
        protocol::MODIFY_INSTANCE,
        protocol::DELETE_INSTANCE,
        protocol::ASSOCIATOR_INSTANCES,
        protocol::REFERENCE_INSTANCES,
        protocol::ENABLE_INDICATIONS,
        protocol::DISABLE_INDICATIONS,
        protocol::SUBSCRIBE,
        protocol::UNSUBSCRIBE,
        protocol::INVOKE,
        protocol::POST_RESULT,
        protocol::POST_INSTANCE,
        protocol::POST_INDICATION,
    };
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    for (size_t i = 0; EXIT_SUCCESS == rval && i < card (vals); ++i)
    {
        rval = protocol::send_opcode (vals[i], *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            protocol::opcode_t opcodeIn;
            rval = protocol::recv_opcode (&opcodeIn, *recvSock);
            if (EXIT_SUCCESS == rval &&
                vals[i] != opcodeIn)
            {
                rval = EXIT_FAILURE;
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test05 ()
{
    // test send and recv (MI_Char*)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        // test a random string
        size_t len = rand () % 995 + 5;
        util::unique_ptr<MI_Char[]> strOut (create_rand_string (len));
        rval = protocol::send (strOut.get (), *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Char* pStrIn = NULL;
            rval = protocol::recv (&pStrIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                util::unique_ptr<MI_Char[]> strIn (pStrIn);
                if (NULL == pStrIn ||
                    len != strlen (pStrIn) ||
                    0 != strncmp (pStrIn, strOut.get (), len))
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS == rval)
    {
        // test a NULL string
        MI_Char* pStrOut = NULL;
        rval = protocol::send (pStrOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Char* pStrIn = NULL;
            rval = protocol::recv (&pStrIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                util::unique_ptr<MI_Char[]> strIn (pStrIn);
                if (NULL != pStrIn)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS == rval)
    {
        // test an empty string
        MI_Char* pStrOut = "";
        rval = protocol::send (pStrOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Char* pStrIn = NULL;
            rval = protocol::recv (&pStrIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                util::unique_ptr<MI_Char[]> strIn (pStrIn);
                if (NULL != pStrIn)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test06 ()
{
    // test send and recv (basic_string)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        // test a random string
        size_t len = rand () % 995 + 5;
        util::unique_ptr<MI_Char[]> strSrc (create_rand_string (len));
        std::basic_string<MI_Char> strOut (strSrc.get ());
        rval = protocol::send (strOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            std::basic_string<MI_Char> strIn;
            rval = protocol::recv (&strIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (len != strIn.length () ||
                    strOut != strIn)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS == rval)
    {
        // test an empty string
        std::basic_string<MI_Char> strOut ("");
        rval = protocol::send (strOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            std::basic_string<MI_Char> strIn ("whoops");
            rval = protocol::recv (&strIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (strIn != strOut)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test07 ()
{
    // test send and recv (template MI_Uint8)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        MI_Uint8 valOut = static_cast<MI_Uint8>(
            rand () % scx::MI_Limits<MI_UINT8>::max ());
        std::cout << "MI_Uint8 valOut = " << static_cast<unsigned int>(valOut)
                  << std::endl;
        rval = protocol::send<MI_Uint8> (valOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Uint8 valIn;
            rval = protocol::recv<MI_Uint8> (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (valIn != valOut)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test08 ()
{
    // test send and recv (template MI_Sint8)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        MI_Sint8 valOut = static_cast<MI_Sint8>(
            rand () % (scx::MI_Limits<MI_SINT8>::max () -
                       scx::MI_Limits<MI_SINT8>::min ()) +
            scx::MI_Limits<MI_SINT8>::min ());
        std::cout << "MI_Sint8 valOut = " << static_cast<int>(valOut)
                  << std::endl;
        rval = protocol::send<MI_Sint8> (valOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Sint8 valIn;
            rval = protocol::recv<MI_Sint8> (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (valIn != valOut)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test09 ()
{
    // test send and recv (template MI_Uint16)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        MI_Uint16 valOut = static_cast<MI_Uint16>(
            rand () % scx::MI_Limits<MI_UINT16>::max ());
        std::cout << "MI_Uint16 valOut = " << valOut << std::endl;
        rval = protocol::send (valOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Uint16 valIn;
            rval = protocol::recv (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (valIn != valOut)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test10 ()
{
    // test send and recv (template MI_Sint16)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        MI_Sint16 valOut = static_cast<MI_Sint16>(
            rand () % (scx::MI_Limits<MI_SINT16>::max () -
                       scx::MI_Limits<MI_SINT16>::min ()) +
            scx::MI_Limits<MI_SINT16>::min ());
        std::cout << "MI_Sint16 valOut = " << valOut << std::endl;
        rval = protocol::send (valOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Sint16 valIn;
            rval = protocol::recv (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (valIn != valOut)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test11 ()
{
    // test send and recv (template MI_Uint32)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        MI_Uint32 valOut = static_cast<MI_Uint32>(rand ());
        std::cout << "MI_Uint32 valOut = " << valOut << std::endl;
        rval = protocol::send (valOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Uint32 valIn;
            rval = protocol::recv (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (valIn != valOut)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test12 ()
{
    // test send and recv (template MI_Sint32)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        MI_Sint32 valOut = static_cast<MI_Sint32>(rand ());
        std::cout << "MI_Sint32 valOut = " << valOut << std::endl;
        rval = protocol::send (valOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Sint32 valIn;
            rval = protocol::recv (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (valIn != valOut)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test13 ()
{
    // test send and recv (template MI_Uint64)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        MI_Uint64 valOut = static_cast<MI_Uint64>(rand ()) << 32 |
            static_cast<MI_Uint64>(rand ());
        std::cout << "MI_Uint64 valOut = " << valOut << std::endl;
        rval = protocol::send (valOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Uint64 valIn;
            rval = protocol::recv (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (valIn != valOut)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test14 ()
{
    // test send and recv (template MI_Sint64)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        MI_Sint64 valOut = static_cast<MI_Sint64>(rand ()) << 32 |
            static_cast<MI_Sint64>(rand ());
        std::cout << "MI_Sint64 valOut = " << valOut << std::endl;
        rval = protocol::send (valOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Sint64 valIn;
            rval = protocol::recv (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (valIn != valOut)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test15 ()
{
    // test send and recv (template MI_Real32)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        MI_Real32 valOut = static_cast<float>(rand ()) /
            static_cast<float>(RAND_MAX);
        std::cout << "MI_Real32 valOut = " << valOut << std::endl;
        rval = protocol::send (valOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Real32 valIn;
            rval = protocol::recv (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (valIn != valOut)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test16 ()
{
    // test send and recv (template MI_Real64)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        MI_Real64 valOut = static_cast<double>(rand ()) /
            static_cast<double>(RAND_MAX);
        std::cout << "MI_Real64 valOut = " << valOut << std::endl;
        rval = protocol::send (valOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Real64 valIn;
            rval = protocol::recv (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (valIn != valOut)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test17 ()
{
    // test send and recv (template MI_Char16)
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    int rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        MI_Char16 valOut = static_cast<MI_Char16>(
            rand () % scx::MI_Limits<MI_CHAR16>::max ());
        std::cout << "MI_Char16 valOut = " << valOut << std::endl;
        rval = protocol::send (valOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Char16 valIn;
            rval = protocol::recv (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (valIn != valOut)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
shared_protocol_test::test18 ()
{
    // test send and recv (MI_Datetime)
    int rval = EXIT_SUCCESS;
    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    rval = create_sockets (&sendSock, &recvSock);
    if (EXIT_SUCCESS == rval)
    {
        MI_Datetime tsOut;
        tsOut.isTimestamp = MI_TRUE;
        tsOut.u.timestamp.year = static_cast<MI_Uint32>(rand ());
        tsOut.u.timestamp.month = static_cast<MI_Uint32>(rand () % 12 + 1);
        tsOut.u.timestamp.day = static_cast<MI_Uint32>(rand () % 28 + 1);
        tsOut.u.timestamp.hour = static_cast<MI_Uint32>(rand () % 24);
        tsOut.u.timestamp.minute = static_cast<MI_Uint32>(rand () % 60);
        tsOut.u.timestamp.second = static_cast<MI_Uint32>(rand () % 60);
        tsOut.u.timestamp.microseconds =
            static_cast<MI_Uint32>(rand () % 1000000);
        tsOut.u.timestamp.utc = static_cast<MI_Sint32>(rand () % 27 - 12);
        std::cout << "MI_Timestamp" << std::endl;
        rval = protocol::send (tsOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Datetime valIn;
            rval = protocol::recv (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (tsOut.isTimestamp != valIn.isTimestamp ||
                    tsOut.u.timestamp.year != valIn.u.timestamp.year ||
                    tsOut.u.timestamp.month != valIn.u.timestamp.month ||
                    tsOut.u.timestamp.day != valIn.u.timestamp.day ||
                    tsOut.u.timestamp.hour != valIn.u.timestamp.hour ||
                    tsOut.u.timestamp.minute != valIn.u.timestamp.minute ||
                    tsOut.u.timestamp.second != valIn.u.timestamp.second ||
                    tsOut.u.timestamp.microseconds !=
                        valIn.u.timestamp.microseconds ||
                    tsOut.u.timestamp.utc != valIn.u.timestamp.utc)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS == rval)
    {
        MI_Datetime tsOut;
        tsOut.isTimestamp = MI_FALSE;
        tsOut.u.interval.days = static_cast<MI_Uint32>(rand () % 28 + 1);
        tsOut.u.interval.hours = static_cast<MI_Uint32>(rand () % 24);
        tsOut.u.interval.minutes = static_cast<MI_Uint32>(rand () % 60);
        tsOut.u.interval.seconds = static_cast<MI_Uint32>(rand () % 60);
        tsOut.u.interval.microseconds =
            static_cast<MI_Uint32>(rand () % 1000000);
        std::cout << "MI_Interval" << std::endl;
        rval = protocol::send (tsOut, *sendSock);
        if (EXIT_SUCCESS == rval)
        {
            MI_Datetime valIn;
            rval = protocol::recv (&valIn, *recvSock);
            if (EXIT_SUCCESS == rval)
            {
                if (tsOut.isTimestamp != valIn.isTimestamp ||
                    tsOut.u.interval.hours != valIn.u.interval.hours ||
                    tsOut.u.interval.minutes != valIn.u.interval.minutes ||
                    tsOut.u.interval.seconds != valIn.u.interval.seconds ||
                    tsOut.u.interval.microseconds !=
                        valIn.u.interval.microseconds)
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
    }
    if (EXIT_SUCCESS != rval)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}
