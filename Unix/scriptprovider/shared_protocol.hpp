// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#ifndef INCLUDED_SHARED_PROTOCOL_HPP
#define INCLUDED_SHARED_PROTOCOL_HPP


#include "debug_tags.hpp"
#include "socket_wrapper.hpp"
#include "unique_ptr.hpp"


#include <cassert>
#include <MI.h>


#define EXPORT_PUBLIC __attribute__ ((visibility ("default")))


namespace protocol
{


// typedefs
//------------------------------------------------------------------------------
typedef unsigned char boolean_t;
typedef MI_Uint32 opcode_t;
typedef unsigned int item_count_t;
typedef unsigned char data_type_t;


// constants to define NULL
//------------------------------------------------------------------------------
data_type_t const MI_NULL_FLAG = 64;
unsigned int const NULL_STRING = 0xFFFFFFFF;
unsigned int const NULL_COUNT = 0xFFFFFFFF;
unsigned int const MI_METHOD_FLAG = 0x01;


// constants for function table
//------------------------------------------------------------------------------
MI_Uint32 const NO_FUNCTION_TABLE = 0;
MI_Uint32 const HAS_FUNCTION_TABLE = 1 << 0;


// OpCode constants
//------------------------------------------------------------------------------
static MI_Uint32 const MODULE_LOAD = 0;
static MI_Uint32 const MODULE_UNLOAD = 1;

static MI_Uint32 const CLASS_LOAD = 2;
static MI_Uint32 const CLASS_UNLOAD = 3;
static MI_Uint32 const GET_INSTANCE = 4;
static MI_Uint32 const ENUMERATE_INSTANCES = 5;
static MI_Uint32 const CREATE_INSTANCE = 6;
static MI_Uint32 const MODIFY_INSTANCE = 7;
static MI_Uint32 const DELETE_INSTANCE = 8;
static MI_Uint32 const ASSOCIATOR_INSTANCES = 9;
static MI_Uint32 const REFERENCE_INSTANCES = 10;
static MI_Uint32 const ENABLE_INDICATIONS = 11;
static MI_Uint32 const DISABLE_INDICATIONS = 12;
static MI_Uint32 const SUBSCRIBE = 13;
static MI_Uint32 const UNSUBSCRIBE = 14;
static MI_Uint32 const INVOKE = 15;

static MI_Uint32 const POST_RESULT = 50;
static MI_Uint32 const POST_INSTANCE = 51;
static MI_Uint32 const POST_INDICATION = 52;

static MI_Uint32 const HAS_INSTANCE_FLAG = 1 << 0;
static MI_Uint32 const HAS_INPUT_PARAMETERS_FLAG = 1 << 2;


// methods
//------------------------------------------------------------------------------
inline int
send_item_count (
    item_count_t const& count,
    socket_wrapper& sock)
{
    return sock.send (
        reinterpret_cast<socket_wrapper::byte_t const*>(&count),
        sizeof (item_count_t));
}


inline int
send_boolean (
    MI_Boolean const& val,
    socket_wrapper& sock)
{
    boolean_t temp = val ? 1 : 0;
    return sock.send (
        reinterpret_cast<socket_wrapper::byte_t const*>(&temp),
        sizeof (boolean_t));
}


inline int
send_type (
    data_type_t const& type,
    socket_wrapper& sock)
{
    return sock.send (
        reinterpret_cast<socket_wrapper::byte_t const*>(&type),
        sizeof (data_type_t));
}


inline int
send_opcode (
    opcode_t const& opcode,
    socket_wrapper& sock)
{
    return sock.send (reinterpret_cast<socket_wrapper::byte_t const*>(&opcode),
                      sizeof (opcode_t));
}


EXPORT_PUBLIC int
send (
    MI_Char const* const str,
    socket_wrapper& sock);


inline int
send (
    MI_Char* const str,
    socket_wrapper& sock)
{
    return send (const_cast<MI_Char const*>(str), sock);
}


template<typename char_t, typename traits>
int
send (
    std::basic_string<char_t, traits> const& text,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("protocol::send (std::basic_string)");
    item_count_t const len = text.size ();
    int rval = send_item_count (len, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = sock.send (
            reinterpret_cast<socket_wrapper::byte_t const*>(text.c_str ()),
            len * sizeof (char_t));
    }
    return rval;
}


EXPORT_PUBLIC int
send (
    MI_Datetime const& value,
    socket_wrapper& sock);


template<typename T>
int
send (
    T const& value,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("protocol::send (template)");
    return sock.send (
        reinterpret_cast<socket_wrapper::byte_t const*>(&value),
        sizeof (T));
}


inline int
recv_item_count (
    item_count_t* pCountOut,
    socket_wrapper& sock)
{
    assert (pCountOut);
    return sock.recv (reinterpret_cast<socket_wrapper::byte_t*>(pCountOut),
                      sizeof (item_count_t));
}


EXPORT_PUBLIC int
recv_boolean (
    MI_Boolean* const pBooleanOut,
    socket_wrapper& sock);


inline int
recv_type (
    data_type_t* pTypeOut,
    socket_wrapper& sock)
{
    assert (pTypeOut);
    return sock.recv (reinterpret_cast<socket_wrapper::byte_t*>(pTypeOut),
                      sizeof (data_type_t));
}


inline int
recv_opcode (
    opcode_t* const pOpcodeOut,
    socket_wrapper& sock)
{
    return sock.recv (reinterpret_cast<socket_wrapper::byte_t*>(pOpcodeOut),
                      sizeof (opcode_t));
}


EXPORT_PUBLIC int
recv (
    MI_Char** const ppStringOut,
    socket_wrapper& sock);


template<typename char_t, typename traits>
int
recv (
    std::basic_string<char_t, traits>* const pStringOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("protocol::recv (std::basic_string)");
    assert (pStringOut);
    MI_Char* pText = NULL;
    int rval = recv (&pText, sock);
    util::unique_ptr<MI_Char[]> holder (pText);
    if (socket_wrapper::SUCCESS == rval)
    {
        if (pText)
        {
            pStringOut->assign (pText);
        }
        else
        {
            pStringOut->erase ();
        }
    }
    return rval;
}


EXPORT_PUBLIC int
recv (
    MI_Datetime* const pValueOut,
    socket_wrapper& sock);


template<typename T>
int
recv (
    T* pValueOut,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("protocol::recv (template)");
    assert (pValueOut);
    return sock.recv (
        reinterpret_cast<socket_wrapper::byte_t*>(pValueOut),
        sizeof (T));
}


} // namespace protocol


#undef EXPORT_PUBLIC


#endif // INCLUDED_SHARED_PROTOCOL_HPP
