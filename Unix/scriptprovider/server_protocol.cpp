#include "server_protocol.hpp"


#include "debug_tags.hpp"
#include "mi_memory_helper.hpp"
#include "mi_type.hpp"
#include "server.hpp"


#include <sstream>


namespace
{


template<typename T>
T* allocate_and_zero ()
{
    return reinterpret_cast<T*>(memset (new T, 0, sizeof (T)));
}


uint
getFieldSizeForType (
    MI_Type const& type)
{
    uint sz = 0;
    switch (type)
    {
    case MI_BOOLEAN:
        sz = sizeof (MI_BooleanField);
        break;
    case MI_UINT8:
        sz = sizeof (MI_Uint8Field);
        break;
    case MI_SINT8:
        sz = sizeof (MI_Sint8Field);
        break;
    case MI_UINT16:
        sz = sizeof (MI_Uint16Field);
        break;
    case MI_SINT16:
        sz = sizeof (MI_Sint16Field);
        break;
    case MI_UINT32:
        sz = sizeof (MI_Uint32Field);
        break;
    case MI_SINT32:
        sz = sizeof (MI_Sint32Field);
        break;
    case MI_UINT64:
        sz = sizeof (MI_Uint64Field);
        break;
    case MI_SINT64:
        sz = sizeof (MI_Sint64Field);
        break;
    case MI_REAL32:
        sz = sizeof (MI_Real32Field);
        break;
    case MI_REAL64:
        sz = sizeof (MI_Real64Field);
        break;
    case MI_CHAR16:
        sz = sizeof (MI_Char16Field);
        break;
    case MI_DATETIME:
        sz = sizeof (MI_DatetimeField);
        break;
    case MI_STRING:
        sz = sizeof (MI_StringField);
        break;
    case MI_INSTANCE:
        sz = sizeof (MI_InstanceField);
        break;
    case MI_BOOLEANA:
        sz = sizeof (MI_BooleanAField);
        break;
    case MI_UINT8A:
        sz = sizeof (MI_Uint8AField);
        break;
    case MI_SINT8A:
        sz = sizeof (MI_Sint8AField);
        break;
    case MI_UINT16A:
        sz = sizeof (MI_Uint16AField);
        break;
    case MI_SINT16A:
        sz = sizeof (MI_Sint16AField);
        break;
    case MI_UINT32A:
        sz = sizeof (MI_Uint32AField);
        break;
    case MI_SINT32A:
        sz = sizeof (MI_Sint32AField);
        break;
    case MI_UINT64A:
        sz = sizeof (MI_Uint64AField);
        break;
    case MI_SINT64A:
        sz = sizeof (MI_Sint64AField);
        break;
    case MI_REAL32A:
        sz = sizeof (MI_Real32AField);
        break;
    case MI_REAL64A:
        sz = sizeof (MI_Real64AField);
        break;
    case MI_CHAR16A:
        sz = sizeof (MI_Char16AField);
        break;
    case MI_DATETIMEA:
        sz = sizeof (MI_DatetimeAField);
        break;
    case MI_STRINGA:
        sz = sizeof (MI_StringAField);
        break;
    case MI_INSTANCEA:
        sz = sizeof (MI_InstanceAField);
        break;
    case MI_REFERENCE:
    case MI_REFERENCEA:
        std::ostringstream strm;
        strm << __FILE__ << '[' << __LINE__ << ']'
             << "encountered an unhandled param type: " << type;
        SCX_BOOKEND_PRINT (strm.str ());
        std::cerr << strm.str () << std::endl;
        break;
    }
    return sz;
}


struct ClassFinder
{
    /*ctor*/ ClassFinder (MI_Char const* const name)
        : m_Name (name) {}

    bool operator () (MI_ClassDecl const* pClass)
    {
        return m_Name == pClass->name;
    }

    std::string const m_Name;
};


struct Value
{
    std::basic_string<MI_Char> key;
    protocol::data_type_t type;
    MI_Value value;

    /*ctor*/ Value ()
    {
        memset (&value, 0, sizeof (MI_Value));
    }
};
    

void
destroy (
    Value* pValue)
{
    if (MI_ARRAY & pValue->type == MI_ARRAY)
    {
        switch (pValue->type)
        {
        case MI_BOOLEANA:
            delete[] pValue->value.booleana.data;
            pValue->value.booleana.data = NULL;
            break;
        case MI_UINT8A:
            delete[] pValue->value.uint8a.data;
            pValue->value.uint8a.data = NULL;
            break;
        case MI_SINT8A:
            delete[] pValue->value.sint8a.data;
            pValue->value.sint8a.data = NULL;
            break;
        case MI_UINT16A:
            delete[] pValue->value.uint16a.data;
            pValue->value.uint16a.data = NULL;
            break;
        case MI_SINT16A:
            delete[] pValue->value.sint16a.data;
            pValue->value.sint16a.data = NULL;
            break;
        case MI_UINT32A:
            delete[] pValue->value.uint32a.data;
            pValue->value.uint32a.data = NULL;
            break;
        case MI_SINT32A:
            delete[] pValue->value.sint32a.data;
            pValue->value.sint32a.data = NULL;
            break;
        case MI_UINT64A:
            delete[] pValue->value.uint64a.data;
            pValue->value.uint64a.data = NULL;
            break;
        case MI_SINT64A:
            delete[] pValue->value.sint64a.data;
            pValue->value.sint64a.data = NULL;
            break;
        case MI_REAL32A:
            delete[] pValue->value.real32a.data;
            pValue->value.real32a.data = NULL;
            break;
        case MI_REAL64A:
            delete[] pValue->value.real64a.data;
            pValue->value.real64a.data = NULL;
            break;
        case MI_CHAR16A:
            delete[] pValue->value.char16a.data;
            pValue->value.char16a.data = NULL;
            break;
        case MI_DATETIMEA:
            delete[] pValue->value.datetimea.data;
            pValue->value.datetimea.data = NULL;
            break;
        case MI_STRINGA:
            for (MI_Uint32 i = 0;
                 i < pValue->value.stringa.size;
                 ++i)
            {
                delete[] pValue->value.stringa.data[i];
            }
            delete[] pValue->value.stringa.data;
            pValue->value.stringa.data = NULL;
            break;
        case MI_REFERENCEA:
            SCX_BOOKEND_PRINT ("MI_ReferenceA not implemented");
            break;
        case MI_INSTANCEA:
            for (MI_Uint32 i = 0;
                 i < pValue->value.instancea.size;
                 ++i)
            {
                MI_Instance_Delete (pValue->value.instancea.data[i]);
            }
            delete[] pValue->value.instancea.data;
            pValue->value.instancea.data = NULL;
            break;
        }
        pValue->value.array.size = 0;
    }
}


template<scx::TypeID_t TYPE>
class Val
{
public:
    static int
    recv (
        typename scx::MI_Type<TYPE>::type_t* pValueOut,
        socket_wrapper& sock)
    {
        typename scx::MI_Type<TYPE>::type_t value;
        int rval = protocol::recv (&value, sock);
        if (socket_wrapper::SUCCESS == rval)
        {
            *pValueOut = value;
        }
        return rval;
    }

    static int
    send (
        typename scx::MI_Type<TYPE>::type_t const& value,
        socket_wrapper& sock)
    {
        return protocol::send (value, sock);
    }
};


template<>
class Val<MI_BOOLEAN>
{
public:
    static int
    recv (
        MI_Boolean* pValueOut,
        socket_wrapper& sock)
    {
        MI_Boolean value;
        int rval = protocol::recv_boolean (&value, sock);
        if (socket_wrapper::SUCCESS == rval)
        {
            *pValueOut = value;
        }
        return rval;
    }

    static int
    send (
        MI_Boolean const& value,
        socket_wrapper& sock)
    {
        return protocol::send_boolean (value, sock);
    }
};


template<>
class Val<MI_DATETIME>
{
public:
    static int
    recv (
        MI_Datetime* pDatetimeOut,
        socket_wrapper& sock)
    {
        MI_Boolean isTimestamp;
        int rval = protocol::recv_boolean (&isTimestamp, sock);
        if (socket_wrapper::SUCCESS == rval)
        {
            if (isTimestamp)
            {
                MI_Timestamp timestamp;
                rval = protocol::recv (&timestamp, sock);
                if (socket_wrapper::SUCCESS == rval)
                {
                    pDatetimeOut->isTimestamp = MI_TRUE;
                    pDatetimeOut->u.timestamp = timestamp;
                }
                else
                {
                    SCX_BOOKEND_PRINT ("Failed to read MI_Timestamp");
                    // todo error
                    rval = EXIT_FAILURE;
                }
            }
            else
            {
                MI_Interval interval = { 0, 0, 0, 0, 0, 0, 0, 0 };
                rval = sock.recv (
                    reinterpret_cast<socket_wrapper::byte_t*>(&(interval.days)),
                    5 * sizeof (MI_Uint32));
                if (socket_wrapper::SUCCESS == rval)
                {
                    pDatetimeOut->isTimestamp = MI_FALSE;
                    pDatetimeOut->u.interval = interval;
                }
                else
                {
                    SCX_BOOKEND_PRINT ("Failed to read MI_Interval");
                    // todo error
                    rval = EXIT_FAILURE;
                }
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("Failed to read MI_Datetime.isTimestamp");
            // todo error
            rval = EXIT_FAILURE;
        }
        return rval;
    }

    static int
    send (
        MI_Datetime const& datetime,
        socket_wrapper& sock)
    {
        int rval = protocol::send_boolean (datetime.isTimestamp, sock);
        if (socket_wrapper::SUCCESS == rval)
        {
            if (datetime.isTimestamp)
            {
                rval = protocol::send (datetime.u.timestamp, sock);
                if (socket_wrapper::SUCCESS != rval)
                {
                    SCX_BOOKEND_PRINT ("Failed to send MI_Timestamp");
                    // todo error
                    rval = EXIT_FAILURE;
                }
            }
            else
            {
                rval = sock.send (
                    reinterpret_cast<socket_wrapper::byte_t const*>(
                        &(datetime.u.interval.days)),
                    5 * sizeof (MI_Uint32));
                if (socket_wrapper::SUCCESS != rval)
                {
                    SCX_BOOKEND_PRINT ("Failed to send MI_Interval");
                    // todo error
                    rval = EXIT_FAILURE;
                }
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("Failed to send MI_Datetime.isTimestamp");
            // todo error
            return EXIT_FAILURE;
        }
        return rval;
    }
};


template<>
class Val<MI_STRING>
{
public:
    static int
    recv (
        MI_Char** ppStringOut,
        socket_wrapper& sock)
    {
        if (*ppStringOut)
        {
            SCX_BOOKEND_PRINT ("*ppStringOut is not NULL");
        }
        else
        {
            SCX_BOOKEND_PRINT ("*ppStringOut is NULL");
        }
        MI_Char* pString = NULL;
        int rval = protocol::recv (&pString, sock);
        if (socket_wrapper::SUCCESS == rval)
        {
            SCX_BOOKEND_PRINT ("recv string succeeded");
            *ppStringOut = pString;
        }
        else
        {
            SCX_BOOKEND_PRINT ("recv string failed");
        }
        return rval;
    }

    static int
    send (
        MI_Char const* const pString,
        socket_wrapper& sock)
    {
        return protocol::send (pString, sock);
    }
};


template<>
class Val<MI_INSTANCE>
{
public:
    static int
    send (
        MI_Instance const* const pInstance,
        socket_wrapper& sock)
    {
        return protocol::send (*pInstance, sock);
    }
};


template<scx::TypeID_t TYPE>
class Arr
{
public:
    template<typename T>
    static int
    recv (
        T** const ppData,
        MI_Uint32* const pSize,
        socket_wrapper& sock)
    {
        protocol::item_count_t count = 0;
        util::unique_ptr<
            typename scx::MI_ArrayType<TYPE>::nested_type_t[]> array;
        int rval = protocol::recv_item_count (&count, sock);
        if (socket_wrapper::SUCCESS == rval)
        {
            array.reset (
                new typename scx::MI_ArrayType<TYPE>::nested_type_t[count]);
            for (protocol::item_count_t i = 0;
                 i < count && socket_wrapper::SUCCESS == rval;
                 ++i)
            {
                rval = Val<TYPE & ~MI_ARRAY>::recv (array.get () + i, sock);
            }
        }
        if (socket_wrapper::SUCCESS == rval)
        {
            *ppData = array.release ();
            *pSize = count;
        }
        return rval;    
    }

    template<typename T>
    static int
    send (
        T const* const pData,
        MI_Uint32 const& size,
        socket_wrapper& sock)
    {
        int rval = protocol::send_item_count (
            static_cast<protocol::item_count_t>(size), sock);
        for (protocol::item_count_t i = 0;
             socket_wrapper::SUCCESS == rval && i < size;
             ++i)
        {
            rval = Val<TYPE & ~MI_ARRAY>::send (pData[i], sock);
        }
        return rval;
    }
};


template<>
class Arr<MI_INSTANCEA>
{
public:
    static int
    send (
        MI_Instance const* const* const ppInstances,
        MI_Uint32 const& size,
        socket_wrapper& sock)
    {
        int rval = protocol::send_item_count (
            static_cast<protocol::item_count_t>(size), sock);
        for (protocol::item_count_t i = 0;
             socket_wrapper::SUCCESS == rval && i < size;
             ++i)
        {
            rval = Val<MI_INSTANCE>::send (ppInstances[i], sock);
        }
        return rval;
    }
};


template<>
class Arr<MI_STRINGA>
{
public:
    static int
    recv (
        MI_Char*** const pppData,
        MI_Uint32* const pSize,
        socket_wrapper& sock)
    {
        protocol::item_count_t count = 0;
        util::unique_ptr<MI_Char*[]> array;
        int rval = protocol::recv_item_count (&count, sock);
        if (socket_wrapper::SUCCESS == rval)
        {
            array.reset (new MI_Char*[count]);
            for (protocol::item_count_t i = 0; i < count; ++i)
            {
                array[i] = NULL;
            }
            for (protocol::item_count_t i = 0;
                 i < count && socket_wrapper::SUCCESS == rval;
                 ++i)
            {
                rval = Val<MI_STRING>::recv (array.get () + i, sock);
            }
        }
        if (socket_wrapper::SUCCESS == rval)
        {
            *pppData = array.release ();
            *pSize = count;
        }
        else
        {
            for (protocol::item_count_t i = 0; i < count; ++i)
            {
                if (0 != array[i])
                {
                    delete[] array[i];
                }
            }
        }
        return rval;    
    }

    static int
    send (
        MI_Char const* const* const ppData,
        MI_Uint32 const& size,
        socket_wrapper& sock)
    {
        int rval = protocol::send_item_count (
            static_cast<protocol::item_count_t>(size), sock);
        for (protocol::item_count_t i = 0;
             socket_wrapper::SUCCESS == rval && i < size;
             ++i)
        {
            rval = Val<MI_STRING>::send (ppData[i], sock);
        }
        return rval;
    }
};

    
#if (1)
#define PRINT_RECV_ARRAY (PRINT_BOOKENDS)
#else
#define PRINT_RECV_ARRAY (0)
#endif

#if (PRINT_RECV_ARRAY)
#define ARRAY_BOOKEND(x) SCX_BOOKEND (x)
#define ARRAY_PRINT(x) SCX_BOOKEND_PRINT (x)
#else
#define ARRAY_BOOKEND(x)
#define ARRAY_PRINT(x)
#endif

template<typename T>
int
recv_array_items (
    T*** const pppDataOut,
    MI_Uint32* const pSizeOut,
    socket_wrapper& sock)
{
    ARRAY_BOOKEND ("read_array_items");
    if (NULL != *pppDataOut)
    {
        MI_DeleteArrayItems (*pppDataOut, *pSizeOut);
        delete[] *pppDataOut;
        *pppDataOut = NULL;
    }
    protocol::item_count_t count;
    int rval = protocol::recv_item_count (&count, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
#if (PRINT_RECV_ARRAY)
        std::ostringstream strm;
        strm << "count: " << count;
        ARRAY_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
#endif
        util::unique_ptr<T*[]> pTempArray;
        if (0 < count)
        {
            pTempArray.reset (new T*[count]);
            std::fill_n (pTempArray.get (), count, (T*)NULL);
            for (protocol::item_count_t i = 0;
                 socket_wrapper::SUCCESS == rval && i < count;
                 ++i)
            {
#if (PRINT_RECV_ARRAY)
                strm << "item: " << i;
                ARRAY_PRINT (strm.str ());
                strm.str ("");
                strm.clear ();
#endif
                T* pTemp = NULL;
                rval = protocol::recv (&pTemp, sock);
                if (socket_wrapper::SUCCESS == rval)
                {
                    pTempArray[i] = pTemp;
                }
            }
            if (socket_wrapper::SUCCESS != rval)
            {
                MI_DeleteArrayItems (pTempArray.get (), count);
            }
        }
        if (socket_wrapper::SUCCESS == rval)
        {
            *pppDataOut = pTempArray.release ();
            *pSizeOut = static_cast<MI_Uint32>(count);
        }
    }
#if (PRINT_RECV_ARRAY)
    else
    {
        ARRAY_PRINT ("recv item count failed");
    }
#endif
    return rval;
}


#if (1)
#define PRINT_RECV_VALUE (PRINT_BOOKENDS)
#else
#define PRINT_RECV_VALUE (0)
#endif

#if (PRINT_RECV_VALUE)
#define VALUE_BOOKEND(x) SCX_BOOKEND (x)
#define VALUE_PRINT(x) SCX_BOOKEND_PRINT (x)
#else
#define VALUE_BOOKEND(x)
#define VALUE_PRINT(x)
#endif

int
recv (
    MI_Value* const pValueOut,
    protocol::data_type_t const& type,
    MI_Context* const pContext,
    MI_SchemaDecl const* const pSchemaDecl,
    socket_wrapper& sock)
{
    VALUE_BOOKEND ("recv (MI_Value)");
    int rval = socket_wrapper::SUCCESS;
    switch (type)
    {
    case MI_BOOLEAN:
        VALUE_PRINT ("MI_BOOLEAN");
        rval = Val<MI_BOOLEAN>::recv (&(pValueOut->boolean), sock);
        break;
    case MI_UINT8:
        VALUE_PRINT ("MI_UINT8");
        rval = Val<MI_UINT8>::recv (&(pValueOut->uint8), sock);
        break;
    case MI_SINT8:
        VALUE_PRINT ("MI_SINT8");
        rval = Val<MI_SINT8>::recv (&(pValueOut->sint8), sock);
        break;
    case MI_UINT16:
        VALUE_PRINT ("MI_UINT16");
        rval = Val<MI_UINT16>::recv (&(pValueOut->uint16), sock);
        break;
    case MI_SINT16:
        VALUE_PRINT ("MI_SINT16");
        rval = Val<MI_SINT16>::recv (&(pValueOut->sint16), sock);
        break;
    case MI_UINT32:
        VALUE_PRINT ("MI_UINT32");
        rval = Val<MI_UINT32>::recv (&(pValueOut->uint32), sock);
        break;
    case MI_SINT32:
        VALUE_PRINT ("MI_SINT32");
        rval = Val<MI_SINT32>::recv (&(pValueOut->sint32), sock);
        break;
    case MI_UINT64:
        VALUE_PRINT ("MI_UINT64");
        rval = Val<MI_UINT64>::recv (&(pValueOut->uint64), sock);
        break;
    case MI_SINT64:
        VALUE_PRINT ("MI_SINT64");
        rval = Val<MI_SINT64>::recv (&(pValueOut->sint64), sock);
        break;
    case MI_REAL32:
        VALUE_PRINT ("MI_REAL32");
        rval = Val<MI_REAL32>::recv (&(pValueOut->real32), sock);
                    break;
    case MI_REAL64:
        VALUE_PRINT ("MI_REAL64");
        rval = Val<MI_REAL64>::recv (&(pValueOut->real64), sock);
        break;
    case MI_CHAR16:
        VALUE_PRINT ("MI_CHAR16");
        rval = Val<MI_CHAR16>::recv (&(pValueOut->char16), sock);
        break;
    case MI_DATETIME:
        VALUE_PRINT ("MI_DATETIME");
        rval = Val<MI_DATETIME>::recv (&(pValueOut->datetime), sock);
        break;
    case MI_STRING:
        VALUE_PRINT ("MI_STRING");
        rval = Val<MI_STRING>::recv (&(pValueOut->string), sock);
        break;
    case MI_REFERENCE:
        VALUE_PRINT ("MI_REFERENCE");
        VALUE_PRINT ("MI_Reference not implemented");
        rval = EXIT_FAILURE;
    case MI_INSTANCE:
        VALUE_PRINT ("MI_INSTANCE");
        rval = protocol::recv (&(pValueOut->instance), pContext, pSchemaDecl,
                               sock);
        break;
    case MI_BOOLEANA:
        VALUE_PRINT ("MI_BOOLEANA");
        rval = Arr<MI_BOOLEANA>::recv (
            &(pValueOut->booleana.data), &(pValueOut->booleana.size), sock);
        break;
    case MI_UINT8A:
        VALUE_PRINT ("MI_UINT8A");
        rval = Arr<MI_UINT8A>::recv (
            &(pValueOut->uint8a.data), &(pValueOut->uint8a.size), sock);
        break;
    case MI_SINT8A:
        VALUE_PRINT ("MI_SINT8A");
        rval = Arr<MI_SINT8A>::recv (
            &(pValueOut->sint8a.data), &(pValueOut->sint8a.size), sock);
        break;
    case MI_UINT16A:
        VALUE_PRINT ("MI_UINT16A");
        rval = Arr<MI_UINT16A>::recv (
            &(pValueOut->uint16a.data), &(pValueOut->uint16a.size), sock);
        break;
    case MI_SINT16A:
        VALUE_PRINT ("MI_SINT16A");
        rval = Arr<MI_SINT16A>::recv (
            &(pValueOut->sint16a.data), &(pValueOut->sint16a.size), sock);
        break;
    case MI_UINT32A:
        VALUE_PRINT ("MI_UINT32A");
        rval = Arr<MI_UINT32A>::recv (
            &(pValueOut->uint32a.data), &(pValueOut->uint32a.size), sock);
        break;
    case MI_SINT32A:
        VALUE_PRINT ("MI_SINT32A");
        rval = Arr<MI_SINT32A>::recv (
            &(pValueOut->sint32a.data), &(pValueOut->sint32a.size), sock);
        break;
    case MI_UINT64A:
        VALUE_PRINT ("MI_UINT64A");
        rval = Arr<MI_UINT64A>::recv (
            &(pValueOut->uint64a.data), &(pValueOut->uint64a.size), sock);
        break;
    case MI_SINT64A:
        VALUE_PRINT ("MI_SINT64A");
        rval = Arr<MI_SINT64A>::recv (
            &(pValueOut->sint64a.data), &(pValueOut->sint64a.size), sock);
        break;
    case MI_REAL32A:
        VALUE_PRINT ("MI_REAL32A");
        rval = Arr<MI_REAL32A>::recv (
            &(pValueOut->real32a.data), &(pValueOut->real32a.size), sock);
        break;
    case MI_REAL64A:
        VALUE_PRINT ("MI_REAL64A");
        rval = Arr<MI_REAL64A>::recv (
            &(pValueOut->real64a.data), &(pValueOut->real64a.size), sock);
        break;
    case MI_CHAR16A:
        VALUE_PRINT ("MI_CHAR16A");
        rval = Arr<MI_CHAR16A>::recv (
            &(pValueOut->char16a.data), &(pValueOut->char16a.size), sock);
        break;
    case MI_DATETIMEA:
        VALUE_PRINT ("MI_DATETIMEA");
        rval = Arr<MI_DATETIMEA>::recv (
            &(pValueOut->datetimea.data), &(pValueOut->datetimea.size), sock);
        break;
    case MI_STRINGA:
        VALUE_PRINT ("MI_STRINGA");
        rval = Arr<MI_STRINGA>::recv (
            &(pValueOut->stringa.data), &(pValueOut->stringa.size), sock);
        break;
    case MI_REFERENCEA:
        VALUE_PRINT ("MI_REFERENCEA");
        // todo
        VALUE_PRINT ("MI_REFERENCEA not implemented");
        rval = EXIT_FAILURE;
        break;
    case MI_INSTANCEA:
        VALUE_PRINT ("MI_INSTANCEA");
        // todo
        VALUE_PRINT ("MI_INSTANCEA not implemented");
        rval = EXIT_FAILURE;
        break;
    }
    return rval;
}


#if (1)
#define PRINT_SEND (PRINT_BOOKENDS)
#else
#define PRINT_SEND (0)
#endif

#if (PRINT_SEND)
#define SEND_BOOKEND(x) SCX_BOOKEND (x)
#define SEND_PRINT(x) SCX_BOOKEND_PRINT (x)
#else
#define SEND_BOOKEND(x)
#define SEND_PRINT(x)
#endif


int
send (
    MI_Value const& value,
    MI_Type const& type,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("send (MI_Value)");
    int rval = protocol::send_type (type, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        switch (type)
        {
        case MI_BOOLEAN:
            SEND_PRINT ("type: MI_BOOLEAN");
            rval = Val<MI_BOOLEAN>::send (value.boolean, sock);
            break;
        case MI_UINT8:
            SEND_PRINT ("type: MI_UINT8");
            rval = Val<MI_UINT8>::send (value.uint8, sock);
            break;
        case MI_SINT8:
            SEND_PRINT ("type: MI_SINT8");
            rval = Val<MI_SINT8>::send (value.sint8, sock);
            break;
        case MI_UINT16:
            SEND_PRINT ("type: MI_UINT16");
            rval = Val<MI_UINT16>::send (value.uint16, sock);
            break;
        case MI_SINT16:
            SEND_PRINT ("type: MI_SINT16");
            rval = Val<MI_SINT16>::send (value.sint16, sock);
            break;
        case MI_UINT32:
            SEND_PRINT ("type: MI_UINT32");
            rval = Val<MI_UINT32>::send (value.uint32, sock);
            break;
        case MI_SINT32:
            SEND_PRINT ("type: MI_SINT32");
            rval = Val<MI_SINT32>::send (value.sint32, sock);
            break;
        case MI_UINT64:
            SEND_PRINT ("type: MI_UINT64");
            rval = Val<MI_UINT64>::send (value.uint64, sock);
            break;
        case MI_SINT64:
            SEND_PRINT ("type: MI_SINT64");
            rval = Val<MI_SINT64>::send (value.sint64, sock);
            break;
        case MI_REAL32:
            SEND_PRINT ("type: MI_REAL32");
            rval = Val<MI_REAL32>::send (value.real32, sock);
            break;
        case MI_REAL64:
            SEND_PRINT ("type: MI_REAL64");
            rval = Val<MI_REAL64>::send (value.real64, sock);
            break;
        case MI_CHAR16:
            SEND_PRINT ("type: MI_CHAR16");
            rval = Val<MI_CHAR16>::send (value.char16, sock);
            break;
        case MI_DATETIME:
            SEND_PRINT ("type: MI_DATETIME");
            rval = Val<MI_DATETIME>::send (value.datetime, sock);
            break;
        case MI_STRING:
            SEND_PRINT ("type: MI_STRING");
            rval = Val<MI_STRING>::send (value.string, sock);
            break;
        case MI_INSTANCE:
            SEND_PRINT ("type: MI_INSTANCE");
            rval = Val<MI_INSTANCE>::send (value.instance, sock);
            break;
        case MI_BOOLEANA:
            SEND_PRINT ("type: MI_BOOLEANA");
            rval = Arr<MI_BOOLEANA>::send (
                value.booleana.data, value.booleana.size, sock);
            break;
        case MI_UINT8A:
            SEND_PRINT ("type: MI_UINT8A");
            rval = Arr<MI_UINT8A>::send (
                value.uint8a.data, value.uint8a.size, sock);
            break;
        case MI_SINT8A:
            SEND_PRINT ("type: MI_SINT8A");
            rval = Arr<MI_SINT8A>::send (
                value.sint8a.data, value.sint8a.size, sock);
            break;
        case MI_UINT16A:
            SEND_PRINT ("type: MI_UINT16A");
            rval = Arr<MI_UINT16A>::send (
                value.uint16a.data, value.uint16a.size, sock);
            break;
        case MI_SINT16A:
            SEND_PRINT ("type: MI_SINT16A");
            rval = Arr<MI_SINT16A>::send (
                value.sint16a.data, value.sint16a.size, sock);
            break;
        case MI_UINT32A:
            SEND_PRINT ("type: MI_UINT32A");
            rval = Arr<MI_UINT32A>::send (
                value.uint32a.data, value.uint32a.size, sock);
            break;
        case MI_SINT32A:
            SEND_PRINT ("type: MI_SINT32A");
            rval = Arr<MI_SINT32A>::send (
                value.sint32a.data, value.sint32a.size, sock);
            break;
        case MI_UINT64A:
            SEND_PRINT ("type: MI_UINT64A");
            rval = Arr<MI_UINT64A>::send (
                value.uint64a.data, value.uint64a.size, sock);
            break;
        case MI_SINT64A:
            SEND_PRINT ("type: MI_SINT64A");
            rval = Arr<MI_SINT64A>::send (
                value.sint64a.data, value.sint64a.size, sock);
            break;
        case MI_REAL32A:
            SEND_PRINT ("type: MI_REAL32A");
            rval = Arr<MI_REAL32A>::send (
                value.real32a.data, value.real32a.size, sock);
            break;
        case MI_REAL64A:
            SEND_PRINT ("type: MI_REAL64A");
            rval = Arr<MI_REAL64A>::send (
                value.real64a.data, value.real64a.size, sock);
            break;
        case MI_CHAR16A:
            SEND_PRINT ("type: MI_CHAR16A");
            rval = Arr<MI_CHAR16A>::send (
                value.char16a.data, value.char16a.size, sock);
            break;
        case MI_DATETIMEA:
            SEND_PRINT ("type: MI_DATETIMEA");
            rval = Arr<MI_DATETIMEA>::send (
                value.datetimea.data, value.datetimea.size, sock);
            break;
        case MI_STRINGA:
            SEND_PRINT ("type: MI_STRINGA");
            rval = Arr<MI_STRINGA>::send (
                value.stringa.data, value.stringa.size, sock);
            break;
        case MI_INSTANCEA:
            SEND_PRINT ("type: MI_INSTANCEA");
            rval = Arr<MI_INSTANCEA>::send (
                value.instancea.data, value.instancea.size, sock);
            break;
        case MI_REFERENCE:
        case MI_REFERENCEA:
            std::ostringstream strm;
            strm << __FILE__ << '[' << __LINE__ << ']'
                 << "encountered an unhandled param type: " << type;
            SEND_PRINT (strm.str ());
            std::cerr << strm.str () << std::endl;
            // todo: error
            rval = EXIT_FAILURE;
            break;
        }
    }
    return rval;
}


} // unnamed namespace


namespace protocol
{


#if (1)
#define PRINT_RECV_INSTANCE (PRINT_BOOKENDS)
#else
#define PRINT_RECV_INSTANCE (1)
#endif

#if (PRINT_RECV_INSTANCE)
#define INSTANCE_BOOKEND(x) SCX_BOOKEND (x)
#define INSTANCE_PRINT(x) SCX_BOOKEND_PRINT (x)
#else
#define INSTANCE_BOOKEND(x)
#define INSTANCE_PRINT(x)
#endif

int
recv (
    MI_Instance** const ppInstanceOut,
    MI_Context* const pContext,
    MI_SchemaDecl const* const pSchemaDecl,
    socket_wrapper& sock)
{
    INSTANCE_BOOKEND ("protocol::recv (MI_Instance)");
#if (PRINT_RECV_INSTANCE)
    std::ostringstream strm;
#endif
    // recv a flag the distinguishes whether this instance is a MI_Instance or
    // a MI_MethodDecl
    // if this is an MI_MethodDecl, the className will be the parent class
    // additionally, if this is a MI_MethodDecl, the next field to read will be
    // the MI_MethodDecl name
    int rval = socket_wrapper::SUCCESS;
    unsigned int flags = 0;
    if (socket_wrapper::SUCCESS == rval)
    {
        INSTANCE_BOOKEND ("recv flags");
        rval = recv (&flags, sock);
#if (PRINT_RECV_INSTANCE)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "flags: \"" << flags << "\"";
            INSTANCE_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            INSTANCE_PRINT ("recv flags failed");
        }
#endif
    }
    std::basic_string<MI_Char> className;
    if (socket_wrapper::SUCCESS == rval)
    {
        INSTANCE_BOOKEND ("recv class name");
        rval = recv (&className, sock);
#if (PRINT_RECV_INSTANCE)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "class name: \"" << className << "\"";
            INSTANCE_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            INSTANCE_PRINT ("recv className failed");
        }
#endif
    }
    std::basic_string<MI_Char> methodName;
    if (socket_wrapper::SUCCESS == rval &&
        protocol::MI_METHOD_FLAG == (protocol::MI_METHOD_FLAG & flags))
    {
        INSTANCE_BOOKEND ("recv method name");
        rval = recv (&methodName, sock);
#if (PRINT_RECV_INSTANCE)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "method name: \"" << methodName << "\"";
            INSTANCE_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            INSTANCE_PRINT ("recv methodName failed");
        }
#endif
    }
    item_count_t itemCount = 0;
    if (socket_wrapper::SUCCESS == rval)
    {
        INSTANCE_BOOKEND ("recv item count");
        rval = recv_item_count (&itemCount, sock);
#if (PRINT_RECV_INSTANCE)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "item count: \"" << itemCount << "\"";
            INSTANCE_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            INSTANCE_PRINT ("recv item count failed");
        }
#endif
    }
    std::vector<Value> values;
    if (socket_wrapper::SUCCESS == rval)
    {
        INSTANCE_BOOKEND ("recv_values");
        for (item_count_t i = 0;
             i < itemCount && socket_wrapper::SUCCESS == rval;
             ++i)
        {
            Value value;
            INSTANCE_BOOKEND ("recv value");
            INSTANCE_PRINT ("recv key");
            rval = recv (&(value.key), sock);
#if (PRINT_RECV_INSTANCE)
            if (socket_wrapper::SUCCESS == rval)
            {
                strm << "key: \"" << value.key << "\"";
                INSTANCE_PRINT (strm.str ());
                strm.str ("");
                strm.clear ();
            }
            else
            {
                INSTANCE_PRINT ("recv key failed");
            }
#endif
            if (socket_wrapper::SUCCESS == rval)
            {
                INSTANCE_PRINT ("recv type");
                rval = recv_type (&(value.type), sock);
#if (PRINT_RECV_INSTANCE)
                if (socket_wrapper::SUCCESS == rval)
                {
                    strm << "type: " << static_cast<int>(value.type);
                    INSTANCE_PRINT (strm.str ());
                    strm.str ("");
                    strm.clear ();
                }
                else
                {
                    INSTANCE_PRINT ("recv type failed");
                }
#endif
            }
            if (socket_wrapper::SUCCESS == rval)
            {
                INSTANCE_PRINT ("recv value");
                rval = ::recv (&(value.value), value.type, pContext,
                               pSchemaDecl, sock);
                if (socket_wrapper::SUCCESS == rval)
                {
                    INSTANCE_PRINT ("recv value SUCCEEDED");
                    values.push_back (value);
                }
#if (PRINT_RECV_INSTANCE)
                else
                {
                    INSTANCE_PRINT ("recv value FAILED");
                }
#endif
            }
        }  // recv value loop
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        if (pSchemaDecl)
        {
            MI_ClassDecl const* pClassDecl = findClassDecl (
                className.c_str (), pSchemaDecl);
            MI_MethodDecl const* pMethodDecl = NULL;
            if (protocol::MI_METHOD_FLAG == (protocol::MI_METHOD_FLAG & flags) &&
                pClassDecl)
            {
                // find the method decl in pClassDecl
                pMethodDecl = findMethodDecl (methodName.c_str (), pClassDecl);
#if (PRINT_RECV_INSTANCE)
                if (pMethodDecl)
                {
                    INSTANCE_PRINT ("MI_MethodDecl was found");
                }
                else
                {
                    INSTANCE_PRINT ("MI_MethodDecl was not found");
                }
            }
            else if (pClassDecl)
            {
                INSTANCE_PRINT ("MI_ClassDecl was found");
            }
            else
            {
                INSTANCE_PRINT ("MI_ClassDecl was not found");
#endif // PRINT_RECV_INSTANCE
            }
            MI_Instance* pNewInstance = NULL;
            MI_Result result = MI_RESULT_FAILED;
            if (pMethodDecl)
            {
                INSTANCE_BOOKEND ("MI_Context_NewParameters");
                result = MI_Context_NewParameters (
                    pContext, pMethodDecl, &pNewInstance);
#if (PRINT_RECV_INSTANCE)
                switch (result)
                {
                case MI_RESULT_OK:
                    INSTANCE_PRINT ("MI_RESULT_OK");
                    break;
                case MI_RESULT_FAILED:
                    INSTANCE_PRINT ("MI_RESULT_FAILED");
                    break;
                case MI_RESULT_INVALID_PARAMETER:
                    INSTANCE_PRINT ("MI_RESULT_INVALID_PARAMETER");
                    break;
                default:
                    INSTANCE_PRINT ("other error");
                    break;
                }
                if (pNewInstance)
                {
                    INSTANCE_PRINT ("pNewInstance is not NULL");
                    if (pNewInstance->classDecl)
                    {
                        INSTANCE_PRINT ("pNewInstance->classDecl is not NULL");
                    }
                    else
                    {
                        INSTANCE_PRINT ("pNewInstance->classDecl is NULL");
                    }
                }
                else
                {
                    INSTANCE_PRINT ("pNewInstance is NULL");
                }
#endif // PRINT_RECV_INSTANCE
            }
            else if (pClassDecl)
            {
                INSTANCE_PRINT ("MI_Context_NewInstance");
                result = MI_Context_NewInstance (
                    pContext, pClassDecl, &pNewInstance);
            }
            else
            {
                INSTANCE_PRINT ("MI_Instance declaration was not found");
                // todo: error
                rval = EXIT_FAILURE;
            }
            if (MI_RESULT_OK == result)
            {
                INSTANCE_PRINT ("MI_Instance was created");
                for (std::vector<Value>::iterator pos = values.begin (),
                         endPos = values.end ();
                     pos != endPos &&
                         MI_RESULT_OK == result;
                     ++pos)
                {
                    INSTANCE_BOOKEND ("-value-");
                    MI_Type tempType;
#if (PRINT_RECV_INSTANCE)
                    std::ostringstream strm;
                    strm << "pos->key: " << pos->key;
                    INSTANCE_PRINT (strm.str ());
                    strm.clear ();
                    strm.str ("");
                    if (pNewInstance)
                    {
                        INSTANCE_PRINT ("pNewInstance is not NULL");
                    }
                    else
                    {
                        INSTANCE_PRINT ("pNewInstance is NULL");
                    }
#endif // PRINT_RECV_INSTANCE
                    MI_Value value;
                    result = MI_Instance_GetElement (
                        pNewInstance, pos->key.c_str (), &value, &tempType,
                        NULL, NULL);
                    INSTANCE_PRINT ("mark 1");
                    if (MI_RESULT_OK == result &&
                        pos->type == tempType)
                    {
                        INSTANCE_PRINT ("GetElement succeeded");
                        result = MI_Instance_SetElement (
                            pNewInstance, pos->key.c_str (), &(pos->value),
                            static_cast<MI_Type>(pos->type), 0);
#if (PRINT_RECV_INSTANCE)
                        if (MI_RESULT_OK == result)
                        {
                            INSTANCE_PRINT ("SetElement succeeded");
                        }
                        else
                        {
                            INSTANCE_PRINT ("SetElement failed");
                        }
#endif
                    }
                    else if (MI_RESULT_OK == result)
                    {
                        INSTANCE_PRINT ("type mismatch");
                        result = MI_RESULT_TYPE_MISMATCH;
                    }
#if (PRINT_RECV_INSTANCE)
                    else
                    {
                        INSTANCE_PRINT ("GetElement failed.");
                    }
#endif
                }
                if (MI_RESULT_OK == result)
                {
                    INSTANCE_PRINT ("recv MI_Instance succeeded");
                    *ppInstanceOut = pNewInstance;
                }
                else
                {
                    INSTANCE_PRINT ("recv MI_Instance failed");
                    MI_Instance_Delete (pNewInstance);
                    // todo: error
                    rval = EXIT_FAILURE;
                }
            }
        }
        else
        {
            INSTANCE_PRINT ("MI_SchemaDecl is NULL");
            // todo: error
            rval = EXIT_FAILURE;
        }
    }
    for (std::vector<Value>::iterator pos = values.begin (),
             endPos = values.end ();
         pos != endPos;
         ++pos)
    {
        destroy (&(*pos));
    }
    return rval;
}


#if (1)
#define PRINT_QUALIFIER_DECL (PRINT_BOOKENDS)
#else
#define PRINT_QUALIFIER_DECL (0)
#endif

#if (PRINT_QUALIFIER_DECL)
#define QUALIFIER_DECL_BOOKEND(X) SCX_BOOKEND (X)
#define QUALIFIER_DECL_PRINT(X) SCX_BOOKEND_PRINT (X)
#else
#define QUALIFIER_DECL_BOOKEND(X)
#define QUALIFIER_DECL_PRINT(X)
#endif

int
recv (
    MI_QualifierDecl** const ppQualifierDeclOut,
    socket_wrapper& sock)
{
    QUALIFIER_DECL_BOOKEND ("protocol::recv (MI_QualifierDecl)");
    int rval = socket_wrapper::SUCCESS;
    util::unique_ptr<MI_QualifierDecl, MI_Deleter<MI_QualifierDecl> > pTemp (
        allocate_and_zero<MI_QualifierDecl> ());
#if (PRINT_QUALIFIER_DECL)
    std::ostringstream strm;
#endif
    if (socket_wrapper::SUCCESS == rval)
    {
        QUALIFIER_DECL_BOOKEND ("recv name");
        rval = recv (const_cast<MI_Char**>(&(pTemp->name)), sock);
#if (PRINT_QUALIFIER_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "name: " << pTemp->name;
            QUALIFIER_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            QUALIFIER_DECL_PRINT ("recv name failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        QUALIFIER_DECL_BOOKEND ("recv type");
        rval = recv (&(pTemp->type), sock);
#if (PRINT_QUALIFIER_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "type: " << pTemp->type;
            QUALIFIER_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            QUALIFIER_DECL_PRINT ("recv type failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        QUALIFIER_DECL_BOOKEND ("recv scope");
        rval = recv (&(pTemp->scope), sock);
#if (PRINT_QUALIFIER_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "scope: " << pTemp->scope;
            QUALIFIER_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            QUALIFIER_DECL_PRINT ("recv scope failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        QUALIFIER_DECL_BOOKEND ("recv flavor");
        rval = recv (&(pTemp->flavor), sock);
#if (PRINT_QUALIFIER_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "flavor: " << pTemp->flavor;
            QUALIFIER_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            QUALIFIER_DECL_PRINT ("recv flavor failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        QUALIFIER_DECL_BOOKEND ("recv value");
        if (0 == (pTemp->type & protocol::MI_NULL_FLAG))
        {
            QUALIFIER_DECL_PRINT ("value is not NULL, recv value");
            rval = ::recv (
                reinterpret_cast<MI_Value*>(&(pTemp->value)),
                pTemp->type, NULL, NULL, sock);
#if (PRINT_QUALIFIER_DECL)
            if (socket_wrapper::SUCCESS == rval)
            {
                QUALIFIER_DECL_PRINT ("recv value succeeded");
            }
            else
            {
                QUALIFIER_DECL_PRINT ("recv value failed");
            }
#endif
        }
#if (PRINT_QUALIFIER_DECL)
        else
        {
            QUALIFIER_DECL_PRINT ("value is NULL");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        pTemp->type &= ~MI_NULL_FLAG;
        *ppQualifierDeclOut = pTemp.release ();
    }
    return rval;
}


#if (1)
#define PRINT_QUALIFIER (PRINT_BOOKENDS)
#else
#define PRINT_QUALIFIER (0)
#endif

#if (PRINT_QUALIFIER)
#define QUALIFIER_BOOKEND(x) SCX_BOOKEND (x)
#define QUALIFIER_PRINT(x) SCX_BOOKEND_PRINT (x)
#else
#define QUALIFIER_BOOKEND(x)
#define QUALIFIER_PRINT(x)
#endif

int
recv (
    MI_Qualifier** const ppQualifierOut,
    socket_wrapper& sock)
{
    QUALIFIER_BOOKEND ("protocol::recv (MI_Qualifier)");
    int rval = socket_wrapper::SUCCESS;
    util::unique_ptr<MI_Qualifier, MI_Deleter<MI_Qualifier> > pTemp (
        allocate_and_zero<MI_Qualifier> ());
#if (PRINT_QUALIFIER)
    std::ostringstream strm;
#endif
    if (socket_wrapper::SUCCESS == rval)
    {
        QUALIFIER_BOOKEND ("recv name");
        rval = recv (const_cast<MI_Char**>(&(pTemp->name)), sock);
#if (PRINT_QUALIFIER)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "name: " << pTemp->name;
            QUALIFIER_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            QUALIFIER_PRINT ("recv name failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        QUALIFIER_BOOKEND ("recv type");
        rval = recv (&(pTemp->type), sock);
#if (PRINT_QUALIFIER)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "type: " << pTemp->type;
            QUALIFIER_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            QUALIFIER_PRINT ("recv type failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        QUALIFIER_BOOKEND ("recv flavor");
        rval = recv (&(pTemp->flavor), sock);
#if (PRINT_QUALIFIER)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "flavor: " << pTemp->flavor;
            QUALIFIER_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            QUALIFIER_PRINT ("recv flavor failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        QUALIFIER_BOOKEND ("recv value");
        if (0 == (pTemp->type & protocol::MI_NULL_FLAG))
        {
            QUALIFIER_PRINT ("value is not NULL, recv value");
            rval = ::recv (
                reinterpret_cast<MI_Value*>(&(pTemp->value)),
                pTemp->type, NULL, NULL, sock);
#if (PRINT_QUALIFIER)
            if (socket_wrapper::SUCCESS == rval)
            {
                QUALIFIER_PRINT ("recv value succeeded");
            }
            else
            {
                QUALIFIER_PRINT ("recv value failed");
            }
#endif
        }
#if (PRINT_QUALIFIER)
        else
        {
            QUALIFIER_PRINT ("value is NULL");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        pTemp->type &= ~MI_NULL_FLAG;
        *ppQualifierOut = pTemp.release ();
    }
    return rval;
}


#if (1)
#define PRINT_PROPERTY_DECL (PRINT_BOOKENDS)
#else
#define PRINT_PROPERTY_DECL (0)
#endif

#if (PRINT_PROPERTY_DECL)
#define PROPERTY_DECL_BOOKEND(X) SCX_BOOKEND (X)
#define PROPERTY_DECL_PRINT(X) SCX_BOOKEND_PRINT (X)
#else
#define PROPERTY_DECL_BOOKEND(X)
#define PROPERTY_DECL_PRINT(X)
#endif

int
recv (
    MI_PropertyDecl** const ppPropertyDeclOut,
    socket_wrapper& sock)
{
    PROPERTY_DECL_BOOKEND ("protocol::recv (MI_PropertyDecl)");
    int rval = socket_wrapper::SUCCESS;
    util::unique_ptr<MI_PropertyDecl, MI_Deleter<MI_PropertyDecl> > pTemp (
        allocate_and_zero<MI_PropertyDecl> ());
#if (PRINT_PROPERTY_DECL)
    std::ostringstream strm;
#endif
    {
        PROPERTY_DECL_BOOKEND ("recv flags");
        rval = recv (&(pTemp->flags), sock);
#if (PRINT_PROPERTY_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "flags: " << pTemp->flags;
            PROPERTY_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PROPERTY_DECL_PRINT ("recv flags failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PROPERTY_DECL_BOOKEND ("recv code");
        rval = recv (&(pTemp->code), sock);
#if (PRINT_PROPERTY_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "code: " << pTemp->code;
            PROPERTY_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PROPERTY_DECL_PRINT ("recv code failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PROPERTY_DECL_BOOKEND ("recv name");
        rval = recv (const_cast<MI_Char**>(&(pTemp->name)), sock);
#if (PRINT_PROPERTY_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "name: " << pTemp->name;
            PROPERTY_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PROPERTY_DECL_PRINT ("recv name failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PROPERTY_DECL_BOOKEND ("recv qualifiers");
        rval = recv_array_items (
            const_cast<MI_Qualifier***>(&(pTemp->qualifiers)),
            &(pTemp->numQualifiers), sock);
#if (PRINT_PROPERTY_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "qualifiers count: " << pTemp->numQualifiers;
            PROPERTY_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PROPERTY_DECL_PRINT ("recv qualifiers failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PROPERTY_DECL_BOOKEND ("recv type");
        rval = recv (&(pTemp->type), sock);
#if (PRINT_PROPERTY_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "type: " << pTemp->type;
            PROPERTY_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PROPERTY_DECL_PRINT ("recv type failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PROPERTY_DECL_BOOKEND ("recv className");
        rval = recv (const_cast<MI_Char**>(&(pTemp->className)), sock);
#if (PRINT_PROPERTY_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "className: " << pTemp->className;
            PROPERTY_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PROPERTY_DECL_PRINT ("recv className failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PROPERTY_DECL_BOOKEND ("recv origin");
        rval = recv (const_cast<MI_Char**>(&(pTemp->origin)), sock);
#if (PRINT_PROPERTY_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "origin: " << pTemp->origin;
            PROPERTY_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PROPERTY_DECL_PRINT ("recv origin failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PROPERTY_DECL_BOOKEND ("recv propagator");
        rval = recv (const_cast<MI_Char**>(&(pTemp->propagator)), sock);
#if (PRINT_PROPERTY_DECL)
        if (socket_wrapper::SUCCESS != rval)
        {
            PROPERTY_DECL_PRINT ("recv propagator failed");
        }
        else
        {
            strm << "propagator: " << pTemp->propagator;
            PROPERTY_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PROPERTY_DECL_BOOKEND ("recv value");
        if (0 == (pTemp->type & protocol::MI_NULL_FLAG))
        {
            PROPERTY_DECL_PRINT ("value is not NULL, recv value");
            rval = ::recv (
                reinterpret_cast<MI_Value*>(&(pTemp->value)),
                pTemp->type, NULL, NULL, sock);
#if (PRINT_PROPERTY_DECL)
            if (socket_wrapper::SUCCESS == rval)
            {
                PROPERTY_DECL_PRINT ("recv value succeeded");
            }
            else
            {
                PROPERTY_DECL_PRINT ("recv value failed");
            }
#endif
        }
#if (PRINT_PROPERTY_DECL)
        else
        {
            PROPERTY_DECL_PRINT ("value is NULL");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        pTemp->type &= ~MI_NULL_FLAG;
        *ppPropertyDeclOut = pTemp.release ();
    }
    return rval;
}


#if (1)
#define PRINT_PARAMETER_DECL (PRINT_BOOKENDS)
#else
#define PRINT_PARAMETER_DECL (0)
#endif

#if (PRINT_PARAMETER_DECL)
#define PARAMETER_DECL_BOOKEND(X) SCX_BOOKEND (X)
#define PARAMETER_DECL_PRINT(X) SCX_BOOKEND_PRINT (X)
#else
#define PARAMETER_DECL_BOOKEND(X)
#define PARAMETER_DECL_PRINT(X)
#endif

int
recv (
    MI_ParameterDecl** const ppParameterDeclOut,
    socket_wrapper& sock)
{
    PARAMETER_DECL_BOOKEND ("protocol::recv (MI_ParameterDecl)");
    int rval = socket_wrapper::SUCCESS;
    util::unique_ptr<MI_ParameterDecl, MI_Deleter<MI_ParameterDecl> > pTemp (
        allocate_and_zero<MI_ParameterDecl> ());
#if (PRINT_PARAMETER_DECL)
    std::ostringstream strm;
#endif
    if (socket_wrapper::SUCCESS == rval)
    {
        PARAMETER_DECL_BOOKEND ("recv flags");
        rval = recv (&(pTemp->flags), sock);
#if (PRINT_PARAMETER_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "flags: " << pTemp->flags;
            PARAMETER_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PARAMETER_DECL_PRINT ("recv flags failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PARAMETER_DECL_BOOKEND ("recv code");
        rval = recv (&(pTemp->code), sock);
#if (PRINT_PARAMETER_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "code: " << pTemp->code;
            PARAMETER_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PARAMETER_DECL_PRINT ("recv code failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PARAMETER_DECL_BOOKEND ("recv name");
        rval = recv (const_cast<MI_Char**>(&(pTemp->name)), sock);
#if (PRINT_PARAMETER_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "name: " << pTemp->name;
            PARAMETER_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PARAMETER_DECL_PRINT ("recv name failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PARAMETER_DECL_BOOKEND ("recv qualifiers");
        rval = recv_array_items (
            const_cast<MI_Qualifier***>(&(pTemp->qualifiers)),
            &(pTemp->numQualifiers), sock);
#if (PRINT_PARAMETER_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "qualifier count: " << pTemp->numQualifiers;
            PARAMETER_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PARAMETER_DECL_PRINT ("recv qualifiers failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PARAMETER_DECL_BOOKEND ("recv type");
        rval = recv (&(pTemp->type), sock);
#if (PRINT_PARAMETER_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "type: " << pTemp->type;
            PARAMETER_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PARAMETER_DECL_PRINT ("recv type failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        PARAMETER_DECL_BOOKEND ("recv className");
        rval = recv (const_cast<MI_Char**>(&(pTemp->className)), sock);
#if (PRINT_PARAMETER_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "className: " << pTemp->className;
            PARAMETER_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            PARAMETER_DECL_PRINT ("recv className failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        *ppParameterDeclOut = pTemp.release ();
    }
    return rval;
}


#if (1)
#define PRINT_METHOD_DECL (PRINT_BOOKENDS)
#else
#define PRINT_METHOD_DECL (0)
#endif

#if (PRINT_METHOD_DECL)
#define METHOD_DECL_BOOKEND(X) SCX_BOOKEND (X)
#define METHOD_DECL_PRINT(X) SCX_BOOKEND_PRINT (X)
#else
#define METHOD_DECL_BOOKEND(X)
#define METHOD_DECL_PRINT(X)
#endif

int
recv (
    MI_MethodDecl** const ppMethodDeclOut,
    socket_wrapper& sock)
{
    METHOD_DECL_BOOKEND ("protocol::recv (MI_MethodDecl)");
    int rval = socket_wrapper::SUCCESS;
    util::unique_ptr<MI_MethodDecl, MI_Deleter<MI_MethodDecl> > pTemp (
        allocate_and_zero<MI_MethodDecl> ());
#if (PRINT_METHOD_DECL)
    std::ostringstream strm;
#endif
    {
        METHOD_DECL_BOOKEND ("recv flags");
        rval = recv (&(pTemp->flags), sock);
#if (PRINT_METHOD_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "flags: " << pTemp->flags;
            METHOD_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            METHOD_DECL_PRINT ("recv flags failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        METHOD_DECL_BOOKEND ("recv code");
        rval = recv (&(pTemp->code), sock);
#if (PRINT_METHOD_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "code: " << pTemp->code;
            METHOD_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            METHOD_DECL_PRINT ("recv code failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        METHOD_DECL_BOOKEND ("recv name");
        rval = recv (const_cast<MI_Char**>(&(pTemp->name)), sock);
#if (PRINT_METHOD_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "name: " << pTemp->name;
            METHOD_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            METHOD_DECL_PRINT ("recv name failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        METHOD_DECL_BOOKEND ("recv qualifiers");
        rval = recv_array_items (
            const_cast<MI_Qualifier***>(&(pTemp->qualifiers)),
            &(pTemp->numQualifiers), sock);
#if (PRINT_METHOD_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "qualifiers count: " << pTemp->numQualifiers;
            METHOD_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            METHOD_DECL_PRINT ("recv qualifiers failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        METHOD_DECL_BOOKEND ("recv parameters");
        rval = recv_array_items (
            const_cast<MI_ParameterDecl***>(&(pTemp->parameters)),
            &(pTemp->numParameters), sock);
#if (PRINT_METHOD_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "parameters count: " << pTemp->numParameters;
            METHOD_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            METHOD_DECL_PRINT ("recv parameters failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        METHOD_DECL_BOOKEND ("recv returnType");
        protocol::data_type_t returnType;
        rval = recv_type (&returnType, sock);
        if (socket_wrapper::SUCCESS == rval)
        {
            pTemp->returnType = returnType;
#if (PRINT_METHOD_DECL)
            strm << "returnType: " << pTemp->returnType;
            METHOD_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            METHOD_DECL_PRINT ("recv returnType failed");
#endif
        }
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        METHOD_DECL_BOOKEND ("recv origin");
        rval = recv (const_cast<MI_Char**>(&(pTemp->origin)), sock);
#if (PRINT_METHOD_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "origin: " << pTemp->origin;
            METHOD_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            METHOD_DECL_PRINT ("recv origin failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        METHOD_DECL_BOOKEND ("recv propagator");
        rval = recv (const_cast<MI_Char**>(&(pTemp->propagator)), sock);
#if (PRINT_METHOD_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "propagator: " << pTemp->propagator;
            METHOD_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            METHOD_DECL_PRINT ("recv propagator failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        unsigned int sz = sizeof (MI_MethodDecl);
        for (MI_Uint32 i = 0; i < pTemp->numParameters; ++i)
        {
            (const_cast<MI_ParameterDecl*>(pTemp->parameters[i]))->offset = sz;
#if (PRINT_METHOD_DECL)
            strm << "Parameter: " << pTemp->parameters[i]->name
                 << ".offset: " << pTemp->parameters[i]->offset;
            METHOD_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
#endif
            sz += getFieldSizeForType (
                static_cast<MI_Type>(
                    pTemp->parameters[i]->type & ~MI_NULL_FLAG));
        }
        pTemp->size = sz;
#if (PRINT_METHOD_DECL)
        strm << "Method: " << pTemp->name << ".size: " << pTemp->size;
            METHOD_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
#endif
        pTemp->schema = NULL;
        pTemp->function = NULL;
        *ppMethodDeclOut = pTemp.release ();
    }
    return rval;
}


#if (1)
#define PRINT_SCRIPT_FT (PRINT_BOOKENDS)
#else
#define PRINT_SCRIPT_FT (0)
#endif

#if (PRINT_SCRIPT_FT)
#define SCRIPT_FT_BOOKEND(X) SCX_BOOKEND (X)
#define SCRIPT_FT_PRINT(X) SCX_BOOKEND_PRINT (X)
#else
#define SCRIPT_FT_BOOKEND(X)
#define SCRIPT_FT_PRINT(X)
#endif

int
recv (
    MI_ProviderScriptFT** const ppProviderScriptFTOut,
    socket_wrapper& sock)
{
    SCRIPT_FT_BOOKEND ("protocol::recv (MI_ProviderScriptFT)");
    int rval = socket_wrapper::SUCCESS;
    util::unique_ptr<MI_ProviderScriptFT,
                     MI_Deleter<MI_ProviderScriptFT> > pTemp (
        allocate_and_zero<MI_ProviderScriptFT> ());
#if (PRINT_SCRIPT_FT)
    std::ostringstream strm;
#endif
    {
        SCRIPT_FT_BOOKEND ("recv Load");
        rval = recv (const_cast<MI_Char**>(&(pTemp->Load)), sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "Load: " << pTemp->Load;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv Load failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv Unload");
        rval = recv (const_cast<MI_Char**>(&(pTemp->Unload)), sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "Unload: " << pTemp->Unload;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv Unload failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv GetInstance");
        rval = recv (const_cast<MI_Char**>(&(pTemp->GetInstance)), sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "GetInstance: " << pTemp->GetInstance;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv GetInstance failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv EnumerateInstances");
        rval = recv (const_cast<MI_Char**>(&(pTemp->EnumerateInstances)),
                     sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "EnumerateInstances: " << pTemp->EnumerateInstances;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv EnumerateInstances failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv CreateInstance");
        rval = recv (const_cast<MI_Char**>(&(pTemp->CreateInstance)),
                     sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "CreateInstance: " << pTemp->CreateInstance;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv CreateInstance failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv ModifyInstance");
        rval = recv (const_cast<MI_Char**>(&(pTemp->ModifyInstance)), sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "ModifyInstance: " << pTemp->ModifyInstance;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv ModifyInstance failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv DeleteInstance");
        rval = recv (const_cast<MI_Char**>(&(pTemp->DeleteInstance)), sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "DeleteInstance: " << pTemp->DeleteInstance;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv DeleteInstance failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv AssociatorInstances");
        rval = recv (
            const_cast<MI_Char**>(&(pTemp->AssociatorInstances)), sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "AssociatorInstances: " << pTemp->AssociatorInstances;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv AssociatorInstances failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv ReferenceInstances");
        rval = recv (
            const_cast<MI_Char**>(&(pTemp->ReferenceInstances)), sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "ReferenceInstances: " << pTemp->ReferenceInstances;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv ReferenceInstances failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv EnableIndications");
        rval = recv (const_cast<MI_Char**>(&(pTemp->EnableIndications)),
                     sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "EnableIndications: " << pTemp->EnableIndications;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv EnableIndications failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv DisableIndications");
        rval = recv (
            const_cast<MI_Char**>(&(pTemp->DisableIndications)), sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "DisableIndications: " << pTemp->DisableIndications;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv DisableIndications failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv Subscribe");
        rval = recv (const_cast<MI_Char**>(&(pTemp->Subscribe)), sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "Subscribe: " << pTemp->Subscribe;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv Subscribe failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv Unsubscribe");
        rval = recv (const_cast<MI_Char**>(&(pTemp->Unsubscribe)), sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "Unsubscribe" << pTemp->Unsubscribe;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv Unsubscribe failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        SCRIPT_FT_BOOKEND ("recv Invoke");
        rval = recv (const_cast<MI_Char**>(&(pTemp->Invoke)), sock);
#if (PRINT_SCRIPT_FT)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "Invoke: " << pTemp->Invoke;
            SCRIPT_FT_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCRIPT_FT_PRINT ("recv Invoke failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        *ppProviderScriptFTOut = pTemp.release ();
    }
    return rval;
}


#if (1)
#define PRINT_CLASS_DECL (PRINT_BOOKENDS)
#else
#define PRINT_CLASS_DECL (0)
#endif

#if (PRINT_CLASS_DECL)
#define CLASS_DECL_BOOKEND(X) SCX_BOOKEND (X)
#define CLASS_DECL_PRINT(X) SCX_BOOKEND_PRINT (X)
#else
#define CLASS_DECL_BOOKEND(X)
#define CLASS_DECL_PRINT(X)
#endif

int
recv (
    MI_ClassDeclEx** const ppClassDeclExOut,
    socket_wrapper& sock)
{
    CLASS_DECL_BOOKEND ("protocol::recv (MI_ClassDecl)");
    int rval = socket_wrapper::SUCCESS;
    util::unique_ptr<MI_ClassDeclEx, MI_Deleter<MI_ClassDeclEx> > pTemp (
        allocate_and_zero<MI_ClassDeclEx> ());
#if (PRINT_CLASS_DECL)
    std::ostringstream strm;
#endif
    if (socket_wrapper::SUCCESS == rval)
    {
        CLASS_DECL_BOOKEND ("recv flags");
        rval = recv (&(pTemp->flags), sock);
#if (PRINT_CLASS_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm <<"flags: " << pTemp->flags;
            CLASS_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            CLASS_DECL_PRINT ("recv flags failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        CLASS_DECL_BOOKEND ("recv code");
        rval = recv (&(pTemp->code), sock);
#if (PRINT_CLASS_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm <<"code: " << pTemp->code;
            CLASS_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            CLASS_DECL_PRINT ("recv code failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        CLASS_DECL_BOOKEND ("recv name");
        rval = recv (const_cast<MI_Char**>(&(pTemp->name)), sock);
#if (PRINT_CLASS_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm <<"name: " << pTemp->name;
            CLASS_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            CLASS_DECL_PRINT ("recv name failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        CLASS_DECL_BOOKEND ("recv qualifiers");
        rval = recv_array_items (
            const_cast<MI_Qualifier***>(&(pTemp->qualifiers)),
            &(pTemp->numQualifiers), sock);
#if (PRINT_CLASS_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm <<"qualifers count: " << pTemp->numQualifiers;
            CLASS_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            CLASS_DECL_PRINT ("recv qualifiers failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        CLASS_DECL_BOOKEND ("recv properties");
        rval = recv_array_items (
            const_cast<MI_PropertyDecl***>(&(pTemp->properties)),
            &(pTemp->numProperties), sock);
#if (PRINT_CLASS_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm <<"properties count: " << pTemp->numProperties;
            CLASS_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            CLASS_DECL_PRINT ("recv properties failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        CLASS_DECL_BOOKEND ("recv superClass");
        rval = recv (const_cast<MI_Char**>(&(pTemp->superClass)), sock);
#if (PRINT_CLASS_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "superClass: " << pTemp->superClass;
            CLASS_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            CLASS_DECL_PRINT ("recv superClass failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        CLASS_DECL_BOOKEND ("recv methods");
        rval = recv_array_items (
            const_cast<MI_MethodDecl***>(&(pTemp->methods)),
            &(pTemp->numMethods), sock);
#if (PRINT_CLASS_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "methods count: " << pTemp->numMethods;
            CLASS_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            CLASS_DECL_PRINT ("recv methods failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        CLASS_DECL_BOOKEND ("recv script table");
        rval = recv (
            const_cast<MI_ProviderScriptFT**>(&(pTemp->scriptFT)), sock);
#if (PRINT_CLASS_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            CLASS_DECL_PRINT ("recv script table succeeded");
        }
        else
        {
            CLASS_DECL_PRINT ("recv script table failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        CLASS_DECL_BOOKEND ("recv owning class name");
        rval = recv (const_cast<MI_Char**>(&(pTemp->owningClassName)), sock);
#if (PRINT_CLASS_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm << "superClass: " << pTemp->owningClassName;
            CLASS_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            CLASS_DECL_PRINT ("recv owning class name failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        unsigned int sz = sizeof (MI_Instance);
        for (MI_Uint32 i = 0; i < pTemp->numProperties; ++i)
        {
            (const_cast<MI_PropertyDecl*>(pTemp->properties[i]))->offset = sz;
#if (PRINT_CLASS_DECL)
            // todo: fix this
            strm << "Property: " << pTemp->properties[i]->name << ".offset: " <<
                pTemp->properties[i]->offset;
            CLASS_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
#endif
            sz += getFieldSizeForType (
                static_cast<MI_Type>(
                    pTemp->properties[i]->type & ~MI_NULL_FLAG));
        }
        pTemp->size = sz;
#if (PRINT_CLASS_DECL)
        strm << "Class: " << pTemp->name << ".size: " << pTemp->size;
            CLASS_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
#endif
        util::unique_ptr<MI_ProviderFT> pFT (new MI_ProviderFT);
//        pFT->Load = NULL != pTemp->scriptFT->Load ? Load : NULL;
        pFT->Load = NULL;
//        pFT->Unload = NULL != pTemp->scriptFT->Unload ? Unload : NULL;
        pFT->Unload = NULL;
        pFT->EnumerateInstances = NULL != pTemp->scriptFT->EnumerateInstances ?
            EnumerateInstances : NULL;
        pFT->GetInstance = NULL != pTemp->scriptFT->GetInstance ? GetInstance :
            NULL;
        pFT->CreateInstance = NULL != pTemp->scriptFT->CreateInstance ?
            CreateInstance : NULL;
        pFT->ModifyInstance = NULL != pTemp->scriptFT->ModifyInstance ?
            ModifyInstance : NULL;
        pFT->DeleteInstance = NULL != pTemp->scriptFT->DeleteInstance ?
            DeleteInstance : NULL;
        pFT->AssociatorInstances =
            NULL != pTemp->scriptFT->AssociatorInstances ? AssociatorInstances :
            NULL;
        pFT->ReferenceInstances = NULL != pTemp->scriptFT->ReferenceInstances ?
            ReferenceInstances : NULL;
        pFT->EnableIndications = NULL != pTemp->scriptFT->EnableIndications ?
            EnableIndications : NULL;
        pFT->DisableIndications = NULL != pTemp->scriptFT->DisableIndications ?
            DisableIndications : NULL;
        pFT->Subscribe = NULL != pTemp->scriptFT->Subscribe ? Subscribe : NULL;
        pFT->Unsubscribe = NULL != pTemp->scriptFT->Unsubscribe ? Unsubscribe :
            NULL;
        pFT->Invoke = Invoke;
        pTemp->providerFT = pFT.release ();
        *ppClassDeclExOut = pTemp.release ();
    }
    return rval;
}


#if (1)
#define PRINT_SCHEMA_DECL (PRINT_BOOKENDS)
#else
#define PRINT_SCHEMA_DECL (0)
#endif

#if (PRINT_SCHEMA_DECL)
#define SCHEMA_DECL_BOOKEND(X) SCX_BOOKEND (X)
#define SCHEMA_DECL_PRINT(X) SCX_BOOKEND_PRINT (X)
#else
#define SCHEMA_DECL_BOOKEND(X)
#define SCHEMA_DECL_PRINT(X)
#endif

int
recv (
    MI_SchemaDecl** const ppSchemaDeclOut,
    socket_wrapper& sock)
{
    SCHEMA_DECL_BOOKEND ("protocol::recv (MI_SchemaDecl)");
    for (int i = 0; i < 10; ++i)
        SCX_BOOKEND_PRINT ("**********");
    int rval = socket_wrapper::SUCCESS;
    util::unique_ptr<MI_SchemaDecl, MI_Deleter<MI_SchemaDecl> > pTemp (
        allocate_and_zero<MI_SchemaDecl> ());
#if (PRINT_SCHEMA_DECL)
    std::ostringstream strm;
#endif
    // recv qualifierDecls
    if (socket_wrapper::SUCCESS == rval)
    {
        SCHEMA_DECL_BOOKEND ("recv qualifierDecls");
        rval = recv_array_items (
            const_cast<MI_QualifierDecl***>(&(pTemp->qualifierDecls)),
            &(pTemp->numQualifierDecls), sock);
#if (PRINT_SCHEMA_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm <<"qualifierDecls count: " << pTemp->numQualifierDecls;
            SCHEMA_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCHEMA_DECL_PRINT ("recv qualifierDecls failed");
        }
#endif
    }
    // recv classDecls
    if (socket_wrapper::SUCCESS == rval)
    {
        SCHEMA_DECL_BOOKEND ("recv classDecls");
        rval = recv_array_items (
            const_cast<MI_ClassDeclEx***>(
                reinterpret_cast<MI_ClassDeclEx const* const**>(
                    &(pTemp->classDecls))),
            &(pTemp->numClassDecls), sock);
#if (PRINT_SCHEMA_DECL)
        if (socket_wrapper::SUCCESS == rval)
        {
            strm <<"classDecls count: " << pTemp->numClassDecls;
            SCHEMA_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
        }
        else
        {
            SCHEMA_DECL_PRINT ("recv classDecls failed");
        }
#endif
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        for (MI_ClassDecl const* const* pPos = pTemp->classDecls,
                 * const* const pEndPos =
                     pTemp->classDecls + pTemp->numClassDecls;
             pPos != pEndPos;
             ++pPos)
        {
#if (PRINT_SCHEMA_DECL)
            strm <<"class: " << (*pPos)->name;
            SCHEMA_DECL_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
#endif
            (const_cast<MI_ClassDecl*>(*pPos))->schema = pTemp.get ();
            // determine the superClass
            if (NULL != (*pPos)->superClass)
            {
                // find superClassDecl
#if (PRINT_SCHEMA_DECL)
                strm <<"superClass: " << (*pPos)->superClass;
                SCHEMA_DECL_PRINT (strm.str ());
                strm.str ("");
                strm.clear ();
#endif
                MI_ClassDecl const* const* pFoundPos =
                    std::find_if (pTemp->classDecls,
                                  pTemp->classDecls + pTemp->numClassDecls,
                                  ClassFinder ((*pPos)->superClass));
                if (pFoundPos != pTemp->classDecls + pTemp->numClassDecls)
                {
                    SCHEMA_DECL_PRINT ("superClassDecl was found");
                   (const_cast<MI_ClassDecl*>(*pPos))->superClassDecl =
                        *pFoundPos;
                }
#if (PRINT_SCHEMA_DECL)
                else
                {
                    SCHEMA_DECL_PRINT ("superClassDecl was NOT found");
                }
#endif
            }
            // assign schema to method decls
            for (MI_MethodDecl const* const* pMD = (*pPos)->methods,
                     * const* const pEndMD =
                         (*pPos)->methods + (*pPos)->numMethods;
                 pMD != pEndMD;
                 ++pMD)
            {
#if (PRINT_SCHEMA_DECL)
                strm <<"method: " << (*pMD)->name;
                SCHEMA_DECL_PRINT (strm.str ());
                strm.str ("");
                strm.clear ();
#endif
                (const_cast<MI_MethodDecl*>(*pMD))->schema = pTemp.get ();
                (const_cast<MI_MethodDecl*>(*pMD))->function = Invoke;
            }
        }
        *ppSchemaDeclOut = pTemp.release ();
    }
    return rval;
}


int
send (
    MI_Instance const& instance,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("protocol::send (MI_Instance)");
    int rval = socket_wrapper::SUCCESS;
    MI_Uint32 nItems;
    if (MI_RESULT_OK != MI_Instance_GetElementCount (&instance, &nItems))
    {
        SCX_BOOKEND_PRINT ("GetElementCount failed");
        // todo: error
        rval = EXIT_FAILURE;
    }
    // count the number of args that need to be sent
    item_count_t nArgs = 0;
    MI_Char const* argName;
    MI_Value argValue;
    MI_Type argType;
    MI_Uint32 argFlags;
    for (MI_Uint32 n = 0; 
         socket_wrapper::SUCCESS == rval && n < nItems;
         ++n)
    {
        if (MI_RESULT_OK == MI_Instance_GetElementAt (
                &instance, n, &argName, &argValue, &argType, &argFlags))
        {
            if (!(MI_FLAG_READONLY == (MI_FLAG_READONLY & argFlags) &&
                  MI_FLAG_KEY != (MI_FLAG_KEY & argFlags)) &&
                MI_FLAG_NULL != (MI_FLAG_NULL & argFlags))
            {
                ++nArgs;
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("GET_ELEMENT_AT - failed");
            // todo: error
            rval = EXIT_FAILURE;
        }
    }
        
    if (socket_wrapper::SUCCESS == rval &&
        socket_wrapper::SUCCESS == (
            rval = send (instance.classDecl->name, sock)))
    {
        rval = send_item_count (nArgs, sock);
    }
    
    for (MI_Uint32 n = 0;
         socket_wrapper::SUCCESS == rval && n < nItems;
         ++n)
    {
        if (MI_RESULT_OK == MI_Instance_GetElementAt (
                &instance, n, &argName, &argValue, &argType, &argFlags))
        {
            if (!(MI_FLAG_READONLY == (MI_FLAG_READONLY & argFlags) &&
                  MI_FLAG_KEY != (MI_FLAG_KEY & argFlags)) &&
                MI_FLAG_NULL != (MI_FLAG_NULL & argFlags))
            {
                if (socket_wrapper::SUCCESS == (
                        rval = send (argName, sock)))
                {
                    rval = ::send (argValue, argType, sock);
                }
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("GET_ELEMENT_AT - failed");
            // todo: error
            rval = EXIT_FAILURE;
        }
    }
    return rval;
}


int
send (
    MI_PropertySet const* const pPropertySet,
    socket_wrapper& sock)
{
    SCX_BOOKEND ("send (MI_PropertySet)");
    int rval = socket_wrapper::SUCCESS;
    MI_Uint32 count;
    if (NULL != pPropertySet)
    {
        if (MI_RESULT_OK == MI_PropertySet_GetElementCount (
                pPropertySet, &count))
        {
            SCX_BOOKEND_PRINT ("send count");
            rval = send_item_count (count, sock);
            for (MI_Uint32 i = 0;
                 i < count && socket_wrapper::SUCCESS == rval;
                 ++i)
            {
                MI_Char const* pPropertyName = NULL;
                if (MI_RESULT_OK == MI_PropertySet_GetElementAt (
                        pPropertySet, i, &pPropertyName))
                {
                    SCX_BOOKEND_PRINT ("send property name");
                    rval = send (pPropertyName, sock);
                    if (socket_wrapper::SUCCESS != rval)
                    {
                        SCX_BOOKEND_PRINT ("failed to send property name");
                    }
                }
                else
                {
                    SCX_BOOKEND_PRINT ("failed to get property name");
                    // todo: error
                    rval = EXIT_FAILURE;
                }
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("failed to get property count");
            // todo: error
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("property set is NULL");
        rval = protocol::send_item_count (protocol::NULL_COUNT, sock);
    }
    return rval;
}


} // namespace protocol
