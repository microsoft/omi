// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#include "mi_value_test.hpp"


#include <cstdlib>
#include <mi_value.hpp>
#include <sys/socket.h>
#include <unistd.h>


using test::mi_value_test;


namespace
{


template<typename T, size_t N>
size_t
card (T const (&)[N])
{
    return N;
}


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


std::basic_string<MI_Char>
create_rand_string (
    size_t len)
{
    std::basic_string<MI_Char> str;
    for (size_t i = 0; i < len; ++i)
    {
        str.push_back (rand_char ());
    }
    return str;
}


void
rand_timestamp (
    scx::MI_Timestamp* pTimestamp)
{
    pTimestamp->setYear (rand ());
    pTimestamp->setMonth (rand () % 12 + 1);
    pTimestamp->setDay (rand () % 28 + 1);
    pTimestamp->setHour (rand () % 24);
    pTimestamp->setMinute (rand () % 60);
    pTimestamp->setSecond (rand () % 60);
    pTimestamp->setMicroseconds (rand () % 1000000);
    pTimestamp->setUTC (0);
}


void
rand_interval (
    scx::MI_Interval* pInterval)
{
    pInterval->setDays (rand ());
    pInterval->setHours (rand () % 24);
    pInterval->setMinutes (rand () % 60);
    pInterval->setSeconds (rand () % 60);
    pInterval->setMicroseconds (rand () % 1000000);
}


} // namespace <unnamed>


/*ctor*/
mi_value_test::mi_value_test ()
{
    add_test (MAKE_TEST (mi_value_test::test01));
    add_test (MAKE_TEST (mi_value_test::test02));
    add_test (MAKE_TEST (mi_value_test::test03));
    add_test (MAKE_TEST (mi_value_test::test04));
    add_test (MAKE_TEST (mi_value_test::test05));
    add_test (MAKE_TEST (mi_value_test::test06));
    add_test (MAKE_TEST (mi_value_test::test07));
    add_test (MAKE_TEST (mi_value_test::test08));
    add_test (MAKE_TEST (mi_value_test::test09));
    add_test (MAKE_TEST (mi_value_test::test10));
    add_test (MAKE_TEST (mi_value_test::test11));
    add_test (MAKE_TEST (mi_value_test::test12));
    add_test (MAKE_TEST (mi_value_test::test13));
    add_test (MAKE_TEST (mi_value_test::test14));
    add_test (MAKE_TEST (mi_value_test::test15));
    add_test (MAKE_TEST (mi_value_test::test16));
    add_test (MAKE_TEST (mi_value_test::test17));
    add_test (MAKE_TEST (mi_value_test::test18));
    add_test (MAKE_TEST (mi_value_test::test19));
    add_test (MAKE_TEST (mi_value_test::test20));
}


int
mi_value_test::test01 ()
{
    // test MI_Value<MI_BOOLEAN>
    int rval = EXIT_SUCCESS;
    // ctor
    scx::MI_Value<MI_BOOLEAN> val0;
    scx::MI_Value<MI_BOOLEAN> val1 (MI_FALSE);
    scx::MI_Value<MI_BOOLEAN> val2 (MI_TRUE);
    scx::MI_Value<MI_BOOLEAN> val3 (val1);
    scx::MI_Value<MI_BOOLEAN> val4 (val2);
    if (MI_FALSE != val1.getValue () ||
        MI_TRUE != val2.getValue () ||
        MI_FALSE != val3.getValue () ||
        MI_TRUE != val4.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = val4;
    val2 = val3;
    val3 = MI_TRUE;
    val4 = MI_FALSE;
    if (MI_TRUE != val1.getValue () ||
        MI_FALSE != val2.getValue () ||
        MI_TRUE != val3.getValue () ||
        MI_FALSE != val4.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_BOOLEAN != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (MI_FALSE);
    val2.setValue (MI_TRUE);
    if (MI_FALSE != val1.getValue () ||
        MI_TRUE != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Boolean val;
                rval = protocol::recv_boolean (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    MI_FALSE != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send_boolean (MI_TRUE, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_BOOLEAN>::Ptr pValue;
                    rval = scx::MI_Value<MI_BOOLEAN>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        MI_TRUE != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test02 ()
{
    // test MI_Value<MI_UINT8>
    int rval = EXIT_SUCCESS;
    MI_Uint8 v1 = static_cast<MI_Uint8>(
        rand () % scx::MI_Limits<MI_UINT8>::max ());
    MI_Uint8 v2;
    do {
        v2 = static_cast<MI_Uint8>(
            rand () % scx::MI_Limits<MI_UINT8>::max ());
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_UINT8> val0;
    scx::MI_Value<MI_UINT8> val1 (v1);
    scx::MI_Value<MI_UINT8> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_UINT8 != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Uint8 val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_UINT8>::Ptr pValue;
                    rval = scx::MI_Value<MI_UINT8>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test03 ()
{
    // test MI_Value<MI_SINT8>
    int rval = EXIT_SUCCESS;
    MI_Sint8 v1 = static_cast<MI_Sint8>(
        rand () % (scx::MI_Limits<MI_SINT8>::max () -
                   scx::MI_Limits<MI_SINT8>::min ()) +
        scx::MI_Limits<MI_SINT8>::min ());
    MI_Sint8 v2;
    do {
        v2 = static_cast<MI_Sint8>(
            rand () % (scx::MI_Limits<MI_SINT8>::max () -
                       scx::MI_Limits<MI_SINT8>::min ()) +
            scx::MI_Limits<MI_SINT8>::min ());
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_SINT8> val0;
    scx::MI_Value<MI_SINT8> val1 (v1);
    scx::MI_Value<MI_SINT8> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_SINT8 != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Sint8 val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_SINT8>::Ptr pValue;
                    rval = scx::MI_Value<MI_SINT8>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test04 ()
{
    // test MI_Value<MI_UINT16>
    int rval = EXIT_SUCCESS;
    MI_Uint16 v1 = static_cast<MI_Uint16>(
        rand () % scx::MI_Limits<MI_UINT16>::max ());
    MI_Uint16 v2;
    do {
        v2 = static_cast<MI_Uint16>(
            rand () % scx::MI_Limits<MI_UINT16>::max ());
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_UINT16> val0;
    scx::MI_Value<MI_UINT16> val1 (v1);
    scx::MI_Value<MI_UINT16> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_UINT16 != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Uint16 val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_UINT16>::Ptr pValue;
                    rval = scx::MI_Value<MI_UINT16>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test05 ()
{
    // test MI_Value<MI_SINT16>
    int rval = EXIT_SUCCESS;
    MI_Sint16 v1 = static_cast<MI_Sint16>(
        rand () % (scx::MI_Limits<MI_SINT16>::max () -
                   scx::MI_Limits<MI_SINT16>::min ()) +
        scx::MI_Limits<MI_SINT16>::min ());
    MI_Sint16 v2;
    do {
        v2 = static_cast<MI_Sint16>(
            rand () % (scx::MI_Limits<MI_SINT16>::max () -
                       scx::MI_Limits<MI_SINT16>::min ()) +
            scx::MI_Limits<MI_SINT16>::min ());
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_SINT16> val0;
    scx::MI_Value<MI_SINT16> val1 (v1);
    scx::MI_Value<MI_SINT16> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_SINT16 != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Sint16 val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_SINT16>::Ptr pValue;
                    rval = scx::MI_Value<MI_SINT16>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test06 ()
{
    // test MI_Value<MI_UINT32>
    int rval = EXIT_SUCCESS;
    MI_Uint32 v1 = static_cast<MI_Uint32>(rand ());
    MI_Uint32 v2;
    do {
        v2 = static_cast<MI_Uint32>(rand ());
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_UINT32> val0;
    scx::MI_Value<MI_UINT32> val1 (v1);
    scx::MI_Value<MI_UINT32> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_UINT32 != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Uint32 val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_UINT32>::Ptr pValue;
                    rval = scx::MI_Value<MI_UINT32>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test07 ()
{
    // test MI_Value<MI_SINT32>
    int rval = EXIT_SUCCESS;
    MI_Sint32 v1 = static_cast<MI_Sint32>(rand ()) +
        scx::MI_Limits<MI_SINT32>::min ();
    MI_Sint32 v2;
    do {
        v2 = static_cast<MI_Sint32>(rand ()) +
            scx::MI_Limits<MI_SINT32>::min ();
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_SINT32> val0;
    scx::MI_Value<MI_SINT32> val1 (v1);
    scx::MI_Value<MI_SINT32> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_SINT32 != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Sint32 val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_SINT32>::Ptr pValue;
                    rval = scx::MI_Value<MI_SINT32>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test08 ()
{
    // test MI_Value<MI_UINT64>
    int rval = EXIT_SUCCESS;
    MI_Uint64 v1 = static_cast<MI_Uint64>(rand ()) << 32 |
        static_cast<MI_Uint64>(rand ());
    MI_Uint64 v2;
    do {
        v2 = static_cast<MI_Uint64>(rand ()) << 32 |
            static_cast<MI_Uint64>(rand ());
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_UINT64> val0;
    scx::MI_Value<MI_UINT64> val1 (v1);
    scx::MI_Value<MI_UINT64> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_UINT64 != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Uint64 val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_UINT64>::Ptr pValue;
                    rval = scx::MI_Value<MI_UINT64>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test09 ()
{
    // test MI_Value<MI_SINT64>
    int rval = EXIT_SUCCESS;
    MI_Sint64 v1 = static_cast<MI_Sint64>(rand ()) << 32 |
        static_cast<MI_Sint64>(rand ());
    MI_Sint64 v2;
    do {
        v2 = static_cast<MI_Sint64>(rand ()) << 32 |
            static_cast<MI_Sint64>(rand ());
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_SINT64> val0;
    scx::MI_Value<MI_SINT64> val1 (v1);
    scx::MI_Value<MI_SINT64> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_SINT64 != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Sint64 val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_SINT64>::Ptr pValue;
                    rval = scx::MI_Value<MI_SINT64>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test10 ()
{
    // test MI_Value<MI_REAL32>
    int rval = EXIT_SUCCESS;
    MI_Real32 v1 = static_cast<MI_Real32>(rand ()) /
        static_cast<MI_Real32>(RAND_MAX);
    MI_Real32 v2;
    do {
        v2 = static_cast<MI_Real32>(rand ()) /
            static_cast<MI_Real32>(RAND_MAX);
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_REAL32> val0;
    scx::MI_Value<MI_REAL32> val1 (v1);
    scx::MI_Value<MI_REAL32> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_REAL32 != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Real32 val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_REAL32>::Ptr pValue;
                    rval = scx::MI_Value<MI_REAL32>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test11 ()
{
    // test MI_Value<MI_REAL64>
    int rval = EXIT_SUCCESS;
    MI_Real64 v1 = static_cast<MI_Real64>(rand ()) /
        static_cast<MI_Real64>(RAND_MAX);
    MI_Real64 v2;
    do {
        v2 = static_cast<MI_Real64>(rand ()) /
            static_cast<MI_Real64>(RAND_MAX);
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_REAL64> val0;
    scx::MI_Value<MI_REAL64> val1 (v1);
    scx::MI_Value<MI_REAL64> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_REAL64 != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Real64 val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_REAL64>::Ptr pValue;
                    rval = scx::MI_Value<MI_REAL64>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test12 ()
{
    // test MI_Value<MI_CHAR16>
    int rval = EXIT_SUCCESS;
    MI_Char16 v1 = static_cast<MI_Char16>(
        rand () % scx::MI_Limits<MI_CHAR16>::max ());
    MI_Char16 v2;
    do {
        v2 = static_cast<MI_Char16>(
            rand () % scx::MI_Limits<MI_CHAR16>::max ());
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_CHAR16> val0;
    scx::MI_Value<MI_CHAR16> val1 (v1);
    scx::MI_Value<MI_CHAR16> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_CHAR16 != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Char16 val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_CHAR16>::Ptr pValue;
                    rval = scx::MI_Value<MI_CHAR16>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test13 ()
{
    // test MI_Value<MI_STRING>
    int rval = EXIT_SUCCESS;
    scx::MI_Value<MI_STRING>::type_t v1 = create_rand_string (10);
    scx::MI_Value<MI_STRING>::type_t v2;
    do {
        v2 = create_rand_string (10);
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_STRING> val0;
    scx::MI_Value<MI_STRING> val1 (v1);
    scx::MI_Value<MI_STRING> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_STRING != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                scx::MI_Value<MI_STRING>::type_t val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_STRING>::Ptr pValue;
                    rval = scx::MI_Value<MI_STRING>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test14 ()
{
    // test MI_Value<MI_STRING>
    int rval = EXIT_SUCCESS;
    scx::MI_Value<MI_STRING>::type_t v1 = create_rand_string (10);
    scx::MI_Value<MI_STRING>::type_t v2;
    do {
        v2 = create_rand_string (10);
    } while (v1 == v2);
    // ctor
    scx::MI_Value<MI_STRING> val0;
    scx::MI_Value<MI_STRING> val1 (v1);
    scx::MI_Value<MI_STRING> val2 (val1);
    if (v1 != val1.getValue () ||
        v1 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator =
    val1 = v2;
    val2 = val1;
    if (v2 != val1.getValue () ||
        v2 != val2.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_STRING != val0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // setValue
    val1.setValue (v1);
    if (v1 != val1.getValue ())
    {
        rval = EXIT_FAILURE;
    }
    // operator ==
    if (val1 == val2 ||
        !(val1 == val1))
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = val1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                scx::MI_Value<MI_STRING>::type_t val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    v1 != val)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                rval = protocol::send (v2, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Value<MI_STRING>::Ptr pValue;
                    rval = scx::MI_Value<MI_STRING>::recv (&pValue, *pSock0);
                    if (EXIT_SUCCESS != rval ||
                        NULL == pValue.get ()  ||
                        v2 != pValue->getValue ())
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    return rval;
}


int
mi_value_test::test15 ()
{
    // test MI_Timestamp
    int rval = EXIT_SUCCESS;
    MI_Uint32 v0year = rand ();
    MI_Uint32 v0mo = rand () % 12 + 1;
    MI_Uint32 v0day = rand () % 28 + 1;
    MI_Uint32 v0hour = rand () % 24;
    MI_Uint32 v0min = rand () % 60;
    MI_Uint32 v0sec = rand () % 60;
    MI_Uint32 v0ms = rand () % 1000000;
    MI_Sint32 v0utc = rand () % 27 - 12;
    MI_Uint32 v1year = rand ();
    MI_Uint32 v1mo = rand () % 12 + 1;
    MI_Uint32 v1day = rand () % 28 + 1;
    MI_Uint32 v1hour = rand () % 24;
    MI_Uint32 v1min = rand () % 60;
    MI_Uint32 v1sec = rand () % 60;
    MI_Uint32 v1ms = rand () % 1000000;
    MI_Sint32 v1utc = rand () % 27 - 12;
    // ctor
    scx::MI_Timestamp v0;
    scx::MI_Timestamp v1 (
        v1year, v1mo, v1day, v1hour, v1min, v1sec, v1ms, v1utc);
    if (v1.getYear () != v1year ||
        v1.getMonth () != v1mo ||
        v1.getDay () != v1day ||
        v1.getHour () != v1hour ||
        v1.getMinute () != v1min ||
        v1.getSecond () != v1sec ||
        v1.getMicroseconds () != v1ms ||
        v1.getUTC () != v1utc)
    {
        rval = EXIT_FAILURE;
    }
    // set
    v0.setYear (v0year);
    v0.setMonth (v0mo);
    v0.setDay (v0day);
    v0.setHour (v0hour);
    v0.setMinute (v0min);
    v0.setSecond (v0sec);
    v0.setMicroseconds (v0ms);
    v0.setUTC (v0utc);
    if (v0.getYear () != v0year ||
        v0.getMonth () != v0mo ||
        v0.getDay () != v0day ||
        v0.getHour () != v0hour ||
        v0.getMinute () != v0min ||
        v0.getSecond () != v0sec ||
        v0.getMicroseconds () != v0ms ||
        v0.getUTC () != v0utc)
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_DATETIME != v0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // isTimestamp
    if (!v1.isTimestamp ())
    {
        rval = EXIT_FAILURE;
    }
    // clone
    scx::MI_Datetime::Ptr ptrV2 = v1.clone ();
    if (ptrV2 &&
        ptrV2->isTimestamp ())
    {
        scx::MI_Timestamp* pV2 = static_cast<scx::MI_Timestamp*>(ptrV2.get ());
        if (v1.getYear () != pV2->getYear () ||
            v1.getMonth () != pV2->getMonth () ||
            v1.getDay () != pV2->getDay () ||
            v1.getHour () != pV2->getHour () ||
            v1.getMinute () != pV2->getMinute () ||
            v1.getSecond () != pV2->getSecond () ||
            v1.getMicroseconds () != pV2->getMicroseconds () ||
            v1.getUTC () != pV2->getUTC ())
        {
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = v1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Datetime val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    !val.isTimestamp ||
                    v1.getYear () != val.u.timestamp.year ||
                    v1.getMonth () != val.u.timestamp.month ||
                    v1.getDay () != val.u.timestamp.day ||
                    v1.getHour () != val.u.timestamp.hour ||
                    v1.getMinute () != val.u.timestamp.minute ||
                    v1.getSecond () != val.u.timestamp.second ||
                    v1.getMicroseconds () != val.u.timestamp.microseconds ||
                    v1.getUTC () != val.u.timestamp.utc)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                MI_Datetime tsOut;
                tsOut.isTimestamp = MI_TRUE;
                tsOut.u.timestamp.year = static_cast<MI_Uint32>(rand ());
                tsOut.u.timestamp.month =
                    static_cast<MI_Uint32>(rand () % 12 + 1);
                tsOut.u.timestamp.day =
                    static_cast<MI_Uint32>(rand () % 28 + 1);
                tsOut.u.timestamp.hour = static_cast<MI_Uint32>(rand () % 24);
                tsOut.u.timestamp.minute = static_cast<MI_Uint32>(rand () % 60);
                tsOut.u.timestamp.second = static_cast<MI_Uint32>(rand () % 60);
                tsOut.u.timestamp.microseconds =
                    static_cast<MI_Uint32>(rand () % 1000000);
                tsOut.u.timestamp.utc =
                    static_cast<MI_Sint32>(rand () % 27 - 12);
                rval = protocol::send (tsOut, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Datetime::Ptr pDatetime;
                    rval = scx::MI_Datetime::recv (&pDatetime, *pSock0);
                    if (EXIT_SUCCESS == rval &&
                        NULL != pDatetime.get ()  &&
                        pDatetime->isTimestamp ())
                    {
                        scx::MI_Timestamp* pTS =
                            static_cast<scx::MI_Timestamp*>(pDatetime.get ());
                        if (tsOut.u.timestamp.year != pTS->getYear () ||
                            tsOut.u.timestamp.month != pTS->getMonth () ||
                            tsOut.u.timestamp.day != pTS->getDay () ||
                            tsOut.u.timestamp.hour != pTS->getHour () ||
                            tsOut.u.timestamp.minute != pTS->getMinute () ||
                            tsOut.u.timestamp.second != pTS->getSecond () ||
                            tsOut.u.timestamp.microseconds !=
                                pTS->getMicroseconds () ||
                            tsOut.u.timestamp.utc != pTS->getUTC ())
                        {
                            rval = EXIT_FAILURE;
                        }
                    }
                    else
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    // operator ==
    if (v0 == v1 ||
        !(v0 == v0))
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_value_test::test16 ()
{
    // test MI_Interval
    int rval = EXIT_SUCCESS;
    MI_Uint32 v0days = rand ();
    MI_Uint32 v0hours = rand () % 24;
    MI_Uint32 v0mins = rand () % 60;
    MI_Uint32 v0secs = rand () % 60;
    MI_Uint32 v0ms = rand () % 1000000;
    MI_Uint32 v1days = rand ();
    MI_Uint32 v1hours = rand () % 24;
    MI_Uint32 v1mins = rand () % 60;
    MI_Uint32 v1secs = rand () % 60;
    MI_Uint32 v1ms = rand () % 1000000;
    // ctor
    scx::MI_Interval v0;
    scx::MI_Interval v1 (v1days, v1hours, v1mins, v1secs, v1ms);
    if (v1.getDays () != v1days ||
        v1.getHours () != v1hours ||
        v1.getMinutes () != v1mins ||
        v1.getSeconds () != v1secs ||
        v1.getMicroseconds () != v1ms)
    {
        rval = EXIT_FAILURE;
    }
    // set
    v0.setDays (v0days);
    v0.setHours (v0hours);
    v0.setMinutes (v0mins);
    v0.setSeconds (v0secs);
    v0.setMicroseconds (v0ms);
    if (v0.getDays () != v0days ||
        v0.getHours () != v0hours ||
        v0.getMinutes () != v0mins ||
        v0.getSeconds () != v0secs ||
        v0.getMicroseconds () != v0ms)
    {
        rval = EXIT_FAILURE;
    }
    // getType
    if (MI_DATETIME != v0.getType ())
    {
        rval = EXIT_FAILURE;
    }
    // isTimestamp
    if (v1.isTimestamp ())
    {
        rval = EXIT_FAILURE;
    }
    // clone
    scx::MI_Datetime::Ptr ptrV2 = v1.clone ();
    if (ptrV2 &&
        !ptrV2->isTimestamp ())
    {
        scx::MI_Interval* pV2 = static_cast<scx::MI_Interval*>(ptrV2.get ());
        if (v1.getDays () != pV2->getDays () ||
            v1.getHours () != pV2->getHours () ||
            v1.getMinutes () != pV2->getMinutes () ||
            v1.getSeconds () != pV2->getSeconds () ||
            v1.getMicroseconds () != pV2->getMicroseconds ())
        {
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        rval = EXIT_FAILURE;
    }
    // send/recv
    if (EXIT_SUCCESS == rval)
    {
        socket_wrapper::Ptr pSock0;
        socket_wrapper::Ptr pSock1;
        rval = create_sockets (&pSock0, &pSock1);
        if (EXIT_SUCCESS == rval)
        {
            rval = v1.send (*pSock0);
            if (EXIT_SUCCESS == rval)
            {
                MI_Datetime val;
                rval = protocol::recv (&val, *pSock1);
                if (EXIT_SUCCESS != rval ||
                    val.isTimestamp ||
                    v1.getDays () != val.u.interval.days ||
                    v1.getHours () != val.u.interval.hours ||
                    v1.getMinutes () != val.u.interval.minutes ||
                    v1.getSeconds () != val.u.interval.seconds ||
                    v1.getMicroseconds () != val.u.interval.microseconds)
                {
                    rval = EXIT_FAILURE;
                }
            }
            if (EXIT_SUCCESS == rval)
            {
                MI_Datetime tsOut;
                tsOut.isTimestamp = MI_FALSE;
                tsOut.u.interval.days = static_cast<MI_Uint32>(rand ());
                tsOut.u.interval.hours = static_cast<MI_Uint32>(rand () % 24);
                tsOut.u.interval.minutes = static_cast<MI_Uint32>(rand () % 60);
                tsOut.u.interval.seconds = static_cast<MI_Uint32>(rand () % 60);
                tsOut.u.timestamp.microseconds =
                    static_cast<MI_Uint32>(rand () % 1000000);
                rval = protocol::send (tsOut, *pSock1);
                if (EXIT_SUCCESS == rval)
                {
                    scx::MI_Datetime::Ptr pDatetime;
                    rval = scx::MI_Datetime::recv (&pDatetime, *pSock0);
                    if (EXIT_SUCCESS == rval &&
                        NULL != pDatetime.get ()  &&
                        !pDatetime->isTimestamp ())
                    {
                        scx::MI_Interval* pInt =
                            static_cast<scx::MI_Interval*>(pDatetime.get ());
                        if (tsOut.u.interval.days != pInt->getDays () ||
                            tsOut.u.interval.hours != pInt->getHours () ||
                            tsOut.u.interval.minutes != pInt->getMinutes () ||
                            tsOut.u.interval.seconds != pInt->getSeconds () ||
                            tsOut.u.interval.microseconds !=
                                pInt->getMicroseconds ())
                        {
                            rval = EXIT_FAILURE;
                        }
                    }
                    else
                    {
                        rval = EXIT_FAILURE;
                    }
                } 
            }
        }
    }
    // operator ==
    if (v0 == v1 ||
        !(v0 == v0))
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_value_test::test17 ()
{
    // test MI_Array<MI_BOOLEANA>
#if (1)
    MI_Boolean vals[] = {
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
    };
    MI_Boolean insertVals[] = {
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
//        rand () % 2 ? MI_TRUE : MI_FALSE,
//        rand () % 2 ? MI_TRUE : MI_FALSE,
//        rand () % 2 ? MI_TRUE : MI_FALSE,
    };
#else
    MI_Boolean insertVals[] = {
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
    };
    MI_Boolean vals[] = {
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
        rand () % 2 ? MI_TRUE : MI_FALSE,
    };
#endif
    int rval = EXIT_SUCCESS;
    // ctor
    scx::MI_Array<MI_BOOLEANA> arr;
    if (0 != arr.size ())
    {
        rval = EXIT_FAILURE;
    }
    // push_back
    for (size_t i = 0; EXIT_FAILURE != rval && i < card (vals); ++i)
    {
        arr.push_back (vals[i]);
        if ((1 + i) == arr.size ())
        {
            for (size_t x = 0; EXIT_FAILURE != rval && x <= i; ++x)
            {
                if (arr[x] != vals[x])
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
        else
        {
            rval = EXIT_FAILURE;
        }
    }
    // insert
    for (size_t i = 0; EXIT_FAILURE != rval && i < card (insertVals); ++i)
    {
        arr.insert (i, insertVals[i]);
        if ((1 + card (vals) + i) == arr.size ())
        {
            for (size_t x = 0; EXIT_FAILURE != rval && x <= i; ++x)
            {
                if (arr[x] != insertVals[x])
                {
                    rval = EXIT_FAILURE;
                }
            }
            for (size_t x = 0; EXIT_FAILURE != rval && x < card (vals); ++x)
            {
                if (arr[x + i + 1] != vals[x])
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
        else
        {
            rval = EXIT_FAILURE;
        }
    }
    // erase
    size_t count = arr.size ();
    size_t index = count / 4;
    count /= 2;
    for (size_t i = 0; i < count; ++i)
    {
        // vals[] = { 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
        // insertVals[] = { 1, 2, 3, 4, 5 }

        // count = 15
        // index = 3
        // count 7

        //    arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
        // 0, arr[] = { 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
        // 1, arr[] = { 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
        // 2, arr[] = { 1, 2, 3, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
        // 3, arr[] = { 1, 2, 3, 8, 9, 10, 11, 12, 13, 14, 15 }
        // 4, arr[] = { 1, 2, 3, 9, 10, 11, 12, 13, 14, 15 }
        // 5, arr[] = { 1, 2, 3, 10, 11, 12, 13, 14, 15 }
        // 6, arr[] = { 1, 2, 3, 11, 12, 13, 14, 15 }

        arr.erase (index);
        if (card (vals) + card (insertVals) - i - 1 == arr.size ())
        {
            for (size_t j = 0; EXIT_FAILURE != rval && j < arr.size (); ++j)
            {
                if (j < index)
                {
                    if (j < card (insertVals))
                    {
                        std::cout << "case 1:" << std::endl;
                        if (arr[j] != insertVals[j])
                        {
                            rval = EXIT_FAILURE;
                        }
                    }
                    else
                    {
                        std::cout << "case 2: *****" << std::endl;
                        if (arr[j] != vals[j - card (insertVals)])
                        {
                            std::cout << "fail" << std::endl;
                            rval = EXIT_FAILURE;
                        }
                    }
                }
                else
                {
                    if (j + i + 1 < card (insertVals))
                    {
                        std::cout << "case 3:" << std::endl;
                        // index = 3
                        // card (insertVals) = 5
                        // i = 0;
                        // j = 3; insertVals[4]
                        // card - index = 2
                        std::cout << "j: " << j << std::endl;
                        std::cout << "i: " << i << std::endl;
                        if (arr[j] != insertVals[j + i + 1])
                        {
                            std::cout << "fail" << std::endl;
                            std::cout << "j: " << j << std::endl;
                            std::cout << "i: " << i << std::endl;
                            std::cout << "index: " << index << std::endl;
                            std::cout << "arr[j]: " << (arr[j] ? "true" : "false") << std::endl;
                            std::cout << "insertVals[j]: " << (insertVals[j] ? "true" : "false") << std::endl;
                            std::cout << "insertVals[j + i - 1]: " << (insertVals[j + i - 1] ? "true" : "false") << std::endl;
                            std::cout << "insertVals[j + i]: " << (insertVals[j + i] ? "true" : "false") << std::endl;
                            std::cout << "insertVals[j + i + 1]: " << (insertVals[j + i + 1] ? "true" : "false") << std::endl;
                            rval = EXIT_FAILURE;
                        }
                    }
                    else
                    {
                        std::cout << "case 4:" << std::endl;
                        // index = 3
                        // card (insertVals) = 5
                        // i = 0;
                        // j = 4; ??? vals[0]
                        // card - index = 2
                        std::cout << "j: " << j << std::endl;
                        std::cout << "i: " << i << std::endl;
                        if (arr[j] != vals[j + i + 1 - card (insertVals)])
                        {
                            std::cout << "fail" << std::endl;
                            std::cout << "j: " << j << std::endl;
                            std::cout << "i: " << i << std::endl;
                            std::cout << "index: " << index << std::endl;
                            std::cout << "arr[j]: " << (arr[j] ? "true" : "false") << std::endl;
                            std::cout << "vals[j]: " << (insertVals[j] ? "true" : "false") << std::endl;
                            std::cout << "vals[j + i - 1 - card]: " << (vals[j + i - 1 - card (insertVals)] ? "true" : "false") << std::endl;
                            std::cout << "vals[j + i - card]: " << (vals[j + i - card (insertVals)] ? "true" : "false") << std::endl;
                            std::cout << "vals[j + i + 1 - card]: " << (vals[j + i + 1 - card (insertVals)] ? "true" : "false") << std::endl;
                            rval = EXIT_FAILURE;
                        }
                    }
                }
            }
        }
        else
        {
            rval = EXIT_FAILURE;
        }
    }

    socket_wrapper::Ptr sendSock;
    socket_wrapper::Ptr recvSock;
    if (EXIT_SUCCESS == rval &&
        EXIT_SUCCESS == (rval = create_sockets (&sendSock, &recvSock)))
    {
        scx::MI_Array<MI_BOOLEANA> out;
        for (size_t i = 0; EXIT_FAILURE != rval && i < card (vals); ++i)
        {
            out.push_back (vals[i]);
        }
        out.send (*sendSock);

        protocol::item_count_t count;
        rval = protocol::recv_item_count (&count, *recvSock);
        util::unique_ptr<MI_Boolean[]> pVals (new MI_Boolean[count]);
        for (protocol::item_count_t i = 0;
             EXIT_SUCCESS == rval && i < count;
             ++i)
        {
            rval = protocol::recv_boolean (pVals.get () + i, *recvSock);
        }

        if (EXIT_SUCCESS == rval &&
            card (vals) == count)
        {
            for (protocol::item_count_t i = 0;
                 EXIT_SUCCESS == rval && i < count;
                 ++i)
            {
                if (out[i] != pVals[i])
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
        else
        {
            rval = EXIT_FAILURE;
        }
        
    }
    

    return rval;
}


// MI_Array
// - empty ctor
// - getType
// - size
// - operator [] (const and non-const)
// - push_back
// - insert
// - erase
// - send
// - /*static*/ recv

// MI_BOOLEANA
// MI_UINT8A
// MI_SINT8A
// MI_UINT16A
// MI_SINT16A
// MI_UINT32A
// MI_SINT32A
// MI_UINT64A
// MI_SINT64A
// MI_REAL32A
// MI_REAL64A
// MI_CHAR16A
// MI_STRINGA
// MI_DATETIMEA

// MI_Boolean has specialized send / recv

// MI_Array<MI_DATETIMEA>
// - empty ctor
// - getType
// - size
// - getValueAt (const and non-const)
// - setValueAt (Value_t and ValuePtr_t)
// - push_back (Value_t and ValuePtr_t)
// - insert (Value_t and ValuePtr_t)
// - erase
// - send
// - /*static*/ recv

// MI_PropertySet
// - empty ctor
// - GetElementCount
// - ContainsElement MI_Char const* and basic_string<MI_Char>
// - GetElementAt
// - operator []
// - /*static*/ recv

// *removed* // protocol::send (MI_Value<MI_STRING>, socket_wrapper)

// operator ==


int
mi_value_test::test18 ()
{
    int rval = EXIT_SUCCESS;
    return rval;
}


int
mi_value_test::test19 ()
{
    int rval = EXIT_SUCCESS;
    return rval;
}


int
mi_value_test::test20 ()
{
    int rval = EXIT_SUCCESS;
    return rval;
}
