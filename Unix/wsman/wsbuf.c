/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <common.h>
#include "wsbuf.h"
#include <base/log.h>
#include <base/result.h>
#include <base/instance.h>
#include <pal/strings.h>
#include <base/field.h>
#include <base/messages.h>
#include <base/helpers.h>
#include <pal/sleep.h>
#include <pal/format.h>
#include <base/base64.h>
#include <xmlserializer/xmlserializer.h>
#include <omi_error/omierror.h>


#if defined(WSBUF_DISABLE_INLINING)
# include "wsbufinline.h"
#endif

#if 0
#define ENABLE_TRACING
#endif

#ifdef  ENABLE_TRACING
#define PRINTF(a)printf a
#else
#define PRINTF(a)
#endif

#define XML_CR ZT("\n")

/*
**==============================================================================
**
** Local datatypes:
**
**==============================================================================
*/
typedef struct _BUF_FaultItem
{
    const ZChar* action;
    MI_Uint32 actionSize;
    const char* code; /* sender/receiver */
    const char* subCode; /* wsa:XXX */
    const ZChar* defaultText;
}
BUF_FaultItem;

typedef struct _BUF_CIMErrorItem
{
    WSBUF_FAULT_CODE faultCode;
    const ZChar* description;
}
BUF_CIMErrorItem;

/*
**==============================================================================
**
** Forward declarations:
**
**==============================================================================
*/
static MI_Result _PackInstance(
    WSBuf* buf,
    UserAgent userAgent,
    const MI_Instance* instance,
    MI_Boolean(*filterProperty)(const ZChar* name, void* data),
    void* filterPropertyData,
    const MI_ClassDecl* castToClassDecl,
    MI_Uint32 flags,
    MI_Boolean embedded,
    const ZChar* propName,
    MI_Uint32 *lastPrefixIndex,
    const ZChar* parentNSPrefix); //optional

static MI_Result _PackEPR(
    WSBuf* buf,
    UserAgent userAgent,
    const MI_Instance* instance,
    MI_Uint32 flags);

/*
**==============================================================================
**
** Static data:
**
**==============================================================================
*/

static const BUF_FaultItem s_faults[] = {
    /* WSBUF_FAULT_INTERNAL_ERROR */
    {
        LIT(ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/fault")),
        "SOAP-ENV:Receiver",
        "wsman:InternalError",
        ZT("The service cannot comply with the request due to internal processing errors.")
    },
    /* WSBUF_FAULT_NOT_SUPPORTED */
    {
        LIT(ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/fault")),
        "SOAP-ENV:Sender",
        "wsman:UnsupportedFeature",
        ZT("not supported")
    },
    /* WSBUF_FAULT_NOT_UNDERSTOOD */
    {
        LIT(ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing/fault")),
        "SOAP-ENV:MustUnderstand",
        0,
        ZT("Header not understood")
    },
    /* WSBUF_FAULT_DESTINATION_UNREACHABLE */
    {
        LIT(ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing/fault")),
        "SOAP-ENV:Sender",
        "wsa:DestinationUnreachable",
        ZT("No route can be determined to reach the destination role defined by the Addressing To header.")
    },
    /* WSBUF_FAULT_ACCESS_DENIED */
    {
        LIT(ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/fault")),
        "SOAP-ENV:Sender",
        "wsman:AccessDenied",
        ZT("The sender was not authorized to access the resource.")
    },
    /* WSBUF_FAULT_ENCODING_LIMIT */
    {
        LIT(ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/fault")),
        "SOAP-ENV:Sender",
        "wsman:EncodingLimit",
        ZT("An internal encoding limit was exceeded in a request or would be violated if the message were processed.")
    },
    /* WSBUF_FAULT_INVALID_EXPIRATION_TIME */
    {
        LIT(ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/fault")),
        "SOAP-ENV:Sender",
        "wsman:InvalidExpirationTime",
        ZT("The request specified an invalid expiration time that cannot be supported (zero or in the past).")
    },
    /* WSBUF_FAULT_UNSUPPORTED_EXPIRATION_TIME */
    {
        LIT(ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/fault")),
        "SOAP-ENV:Sender",
        "wsman:UnsupportedExpirationTime",
        ZT("Only xs:duration expiration values are supported.")
    },
    /* WSBUF_FAULT_TIMED_OUT */
    {
        LIT(ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/fault")),
        "SOAP-ENV:Receiver",
        "wsman:TimedOut",
        ZT("The operation has timed out.")
    },
    /* WSBUF_FAULT_INVALID_MESSAGE_INFORMATION_HEADER */
    {
        LIT(ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing/fault")),
        "SOAP-ENV:Sender",
        "wsa:InvalidMessageInformationHeader",
        ZT("The request specified an invalid header property.")
    },
    /* WSBUF_FAULT_INVALID_HEARTBEAT */
    {
        LIT(ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/faultDetail/Heartbeats")),
        "SOAP-ENV:Sender",
        "wsman:UnsupportedFeature",
        ZT("The request specified an invalid heartbeat.")
    },
    /* WSBUF_FAULT_ACTION_NOT_SUPPORTED */
    {
        LIT(ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing/fault")),
        "SOAP-ENV:Sender",
        "wsa:ActionNotSupported",
        ZT("The request specified an unsupported action.")
    },
    /* WSBUF_FAULT_CONNECTION_RETRY_NOT_SUPPORTED */
    {
        LIT(ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/faultDetail/DeliveryRetries")),
        "SOAP-ENV:Sender",
        "wsman:UnsupportedFeature",
        ZT("Connection retry is not supported.")
    },
    /* WSBUF_FAULT_BOOKMARK_INVALID_FORMAT */
    {
        LIT(ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/faultDetail/InvalidFormat")),
        "SOAP-ENV:Sender",
        "wsman:InvalidBookmark",
        ZT("Bookmark must be non-empty if specified.")
    }
};

static const BUF_CIMErrorItem   s_cimerrors[] = {
    /* MI_RESULT_OK = 0, */
    {
        0,
        0
    },
    /* MI_RESULT_FAILED = 1, */
    {
        WSBUF_FAULT_INTERNAL_ERROR,
        ZT("CIM ERROR:FAILED: A general error occurred, not covered by a more specific error code.")
    },

    /* MI_RESULT_ACCESS_DENIED = 2, */
    {
        WSBUF_FAULT_ACCESS_DENIED,
        ZT("CIM ERROR:ACCESS_DENIED: Access to a CIM resource is not available to the client.")
    },

    /* MI_RESULT_INVALID_NAMESPACE = 3, */
    {
        WSBUF_FAULT_DESTINATION_UNREACHABLE,
        ZT("CIM ERROR:INVALID_NAMESPACE: The target namespace does not exist.")
    },

    /* MI_RESULT_INVALID_PARAMETER  = 4,*/
    {
        WSBUF_FAULT_INTERNAL_ERROR,
        ZT("CIM ERROR:INVALID_PARAMETER: One or more parameter values passed to the method are not valid.")
    },

    /* MI_RESULT_INVALID_CLASS = 5, */
    {
        WSBUF_FAULT_DESTINATION_UNREACHABLE,
        ZT("CIM ERROR:INVALID_CLASS: The specified class does not exist.")
    },

    /* MI_RESULT_NOT_FOUND = 6,*/
    {
        WSBUF_FAULT_DESTINATION_UNREACHABLE,
        ZT("CIM ERROR:NOT_FOUND: The requested object cannot be found.")
    },

    /* MI_RESULT_NOT_SUPPORTED = 7, */
    {
        WSBUF_FAULT_NOT_SUPPORTED,
        ZT("CIM ERROR:NOT_SUPPORTED: The requested operation is not supported.")
    }

#if 0
    /* The operation cannot be invoked because the class has subclasses. */
    MI_RESULT_CLASS_HAS_CHILDREN = 8,

    /* The operation cannot be invoked because the class has instances. */
    MI_RESULT_CLASS_HAS_INSTANCES = 9,

    /* The operation cannot be invoked because the superclass does not exist. */
    MI_RESULT_INVALID_SUPERCLASS = 10,

    /* The operation cannot be invoked because an object already exists. */
    MI_RESULT_ALREADY_EXISTS = 11,

    /* The specified property does not exist. */
    MI_RESULT_NO_SUCH_PROPERTY = 12,

    /* The value supplied is not compatible with the type. */
    MI_RESULT_TYPE_MISMATCH = 13,

    /* The query language is not recognized or supported. */
    MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED = 14,

    /* The query is not valid for the specified query language. */
    MI_RESULT_INVALID_QUERY = 15,

    /* The extrinsic method cannot be invoked. */
    MI_RESULT_METHOD_NOT_AVAILABLE = 16,

    /* The specified extrinsic method does not exist. */
    MI_RESULT_METHOD_NOT_FOUND = 17,

    /* The specified namespace is not empty. */
    MI_RESULT_NAMESPACE_NOT_EMPTY = 20,

    /* The enumeration identified by the specified context is invalid. */
    MI_RESULT_INVALID_ENUMERATION_CONTEXT = 21,

    /* The specified operation timeout is not supported by the CIM Server. */
    MI_RESULT_INVALID_OPERATION_TIMEOUT = 22,

    /* The Pull operation has been abandoned. */
    MI_RESULT_PULL_HAS_BEEN_ABANDONED = 23,

    /* The attempt to abandon a concurrent Pull operation failed. */
    MI_RESULT_PULL_CANNOT_BE_ABANDONED = 24,

    /* Using a filter in the enumeration is not supported by the CIM server. */
    MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED = 25,

    /* The CIM server does not support continuation on error. */
    MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED = 26,

    /* The operation failed because server limits were exceeded. */
    MI_RESULT_SERVER_LIMITS_EXCEEDED = 27,

    /* The CIM server is shutting down and cannot process the operation. */
    MI_RESULT_SERVER_IS_SHUTTING_DOWN = 28
#endif
};

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4125 )
#endif

/* Encodings for special XML characters */
static const ZChar* s_specialCharEncodings[128] =
{
    ZT("\004&#0;"),
    ZT("\004&#1;"),
    ZT("\004&#2;"),
    ZT("\004&#3;"),
    ZT("\004&#4;"),
    ZT("\004&#5;"),
    ZT("\004&#6;"),
    ZT("\004&#7;"),
    ZT("\004&#8;"),
    ZT("\004&#9;"),
    ZT("\005&#10;"),
    ZT("\005&#11;"),
    ZT("\005&#12;"),
    ZT("\005&#13;"),
    ZT("\005&#14;"),
    ZT("\005&#15;"),
    ZT("\005&#16;"),
    ZT("\005&#17;"),
    ZT("\005&#18;"),
    ZT("\005&#19;"),
    ZT("\005&#20;"),
    ZT("\005&#21;"),
    ZT("\005&#22;"),
    ZT("\005&#23;"),
    ZT("\005&#24;"),
    ZT("\005&#25;"),
    ZT("\005&#26;"),
    ZT("\005&#27;"),
    ZT("\005&#28;"),
    ZT("\005&#29;"),
    ZT("\005&#30;"),
    ZT("\005&#31;"),
    ZT("\001 "),
    ZT("\001!"),
    ZT("\006&quot;"),
    ZT("\001#"),
    ZT("\001$"),
    ZT("\001%"),
    ZT("\005&amp;"),
    ZT("\006&apos;"),
    ZT("\001("),
    ZT("\001)"),
    ZT("\001*"),
    ZT("\001+"),
    ZT("\001,"),
    ZT("\001-"),
    ZT("\001."),
    ZT("\001/"),
    ZT("\0010"),
    ZT("\0011"),
    ZT("\0012"),
    ZT("\0013"),
    ZT("\0014"),
    ZT("\0015"),
    ZT("\0016"),
    ZT("\0017"),
    ZT("\0018"),
    ZT("\0019"),
    ZT("\001:"),
    ZT("\001;"),
    ZT("\004&lt;"),
    ZT("\001="),
    ZT("\004&gt;"),
    ZT("\001?"),
    ZT("\001@"),
    ZT("\001A"),
    ZT("\001B"),
    ZT("\001C"),
    ZT("\001D"),
    ZT("\001E"),
    ZT("\001F"),
    ZT("\001G"),
    ZT("\001H"),
    ZT("\001I"),
    ZT("\001J"),
    ZT("\001K"),
    ZT("\001L"),
    ZT("\001M"),
    ZT("\001N"),
    ZT("\001O"),
    ZT("\001P"),
    ZT("\001Q"),
    ZT("\001R"),
    ZT("\001S"),
    ZT("\001T"),
    ZT("\001U"),
    ZT("\001V"),
    ZT("\001W"),
    ZT("\001X"),
    ZT("\001Y"),
    ZT("\001Z"),
    ZT("\001["),
    ZT("\001\\"),
    ZT("\001]"),
    ZT("\001^"),
    ZT("\001_"),
    ZT("\001`"),
    ZT("\001a"),
    ZT("\001b"),
    ZT("\001c"),
    ZT("\001d"),
    ZT("\001e"),
    ZT("\001f"),
    ZT("\001g"),
    ZT("\001h"),
    ZT("\001i"),
    ZT("\001j"),
    ZT("\001k"),
    ZT("\001l"),
    ZT("\001m"),
    ZT("\001n"),
    ZT("\001o"),
    ZT("\001p"),
    ZT("\001q"),
    ZT("\001r"),
    ZT("\001s"),
    ZT("\001t"),
    ZT("\001u"),
    ZT("\001v"),
    ZT("\001w"),
    ZT("\001x"),
    ZT("\001y"),
    ZT("\001z"),
    ZT("\001{"),
    ZT("\001|"),
    ZT("\001}"),
    ZT("\001~"),
    ZT("\006&#127;"),
};

#if defined(_MSC_VER)
#pragma warning( pop )
#endif

#if (MI_CHAR_TYPE == 1)
/* This table idnetifies special XML characters. */
static const char s_specialChars[256] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};
#endif

/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/
MI_INLINE MI_Boolean _Field_GetExists(
    const void* field,
    MI_Type type)
{
    return Field_GetExists((const Field*)field, type);
}

static MI_Result _ReallocPage(
    WSBuf* buf,
    MI_Uint32 newSize)
{
    Page* new_page;

    /* round up to next 1k */
#define WSMAN_BUF_CAPACITY 1024
    newSize = ((newSize + WSMAN_BUF_CAPACITY)/ WSMAN_BUF_CAPACITY)* WSMAN_BUF_CAPACITY;
    new_page = (Page*)PAL_Realloc(buf->page, sizeof(Page)+ newSize);

    if (!new_page)
        return MI_RESULT_FAILED;

    buf->page = new_page;
    buf->page->u.s.size = newSize;
    return MI_RESULT_OK;
}

#if 0
#if (MI_CHAR_TYPE == 1)
#define FIRST_HIGH_SURROGATE  0xD800
#define LAST_HIGH_SURROGATE   0xDBFF

static void _UTF16toUTF8(
    MI_Char16 c,
    char* s)
{
    static const MI_Uint8 firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
    MI_Uint8* tgt = (MI_Uint8*)s;
    MI_Uint32 numberOfBytes;

    /* not a valid single char */
    if (c >= FIRST_HIGH_SURROGATE
        && c <= LAST_HIGH_SURROGATE)
    {
        s[0] = '?';
        s[1] = 0;
        return;
    }

    if (c < 0x80)
    {
        numberOfBytes = 1;
    }
    else if (c < 0x800)
    {
        numberOfBytes = 2;
    }
    else
    {
        numberOfBytes = 3;
    }

    tgt += numberOfBytes;

    switch (numberOfBytes)
    {
        case 3:
        *--tgt = (MI_Uint8)((c | 0x80)& 0xBF);
        c >>= 6;
        case 2:
        *--tgt = (MI_Uint8)((c | 0x80)& 0xBF);
        c >>= 6;
        case 1:
        *--tgt =  (MI_Uint8)(c | firstByteMark[numberOfBytes]);
    }
}
#endif
#endif

/*
**==============================================================================
**
** Public API:
**
**==============================================================================
*/

MI_Result WSBuf_Init(
    WSBuf* buf,
    MI_Uint32 initialSize)
{
    buf->page = (Page*)PAL_Malloc(sizeof(Page)+ initialSize);
    buf->position = 0;

    if (!buf->page)
    {
        return MI_RESULT_FAILED;
    }

    buf->page->u.s.size = initialSize;
    buf->page->u.s.next = 0;
    /* Put empty string inside */
    ((ZChar*)(buf->page +1))[0] = 0;
    return MI_RESULT_OK;
}

MI_Result WSBuf_Destroy(
    WSBuf* buf)
{
    if (buf->page)
        PAL_Free(buf->page);

    return MI_RESULT_OK;
}

Page* WSBuf_StealPage(
    WSBuf* buf)
{
    Page* res = buf->page;

    if (!res)
        return 0;

    buf->page = 0;
    res->u.s.size = buf->position;
    buf->position = 0;

    return res;
}

MI_Result WSBuf_AddUint32(
    WSBuf* buf,
    MI_Uint32 x)
{
    ZChar tmp[12];
    size_t size;
    const ZChar* s = Uint32ToZStr(tmp, x, &size);
    return WSBuf_AddLit(buf, s, (MI_Uint32)size);
}

MI_Result __WSBuf_AddLit(
    WSBuf* buf,
    const ZChar* str,
    MI_Uint32 size)
{
    MI_Uint32 n = (size + 1)* sizeof(ZChar);

    /* Extend buffer (WSBuf_AddLit determined it was too small)*/
    if (_ReallocPage(buf, n + buf->position)!= MI_RESULT_OK)
        return MI_RESULT_FAILED;

    /* Add string */
    {
        char* data = ((char*)(buf->page+1))+ buf->position;
        memcpy(data, str, n - sizeof(ZChar));
        ((ZChar*)data)[size] = 0;

        buf->position += n - sizeof(ZChar);
    }

    return MI_RESULT_OK;
}

MI_Result WSBuf_AddStartTag(
    WSBuf* buf,
    const ZChar* tag,
    MI_Uint32 size)
{
    /* Add 2 bytes for "<" and ">" */
    MI_Uint32 n = (size + 1 + 2)* sizeof(ZChar);

    /* Extend buffer (WSBuf_AddLit determined it was too small)*/
    if (_ReallocPage(buf, n + buf->position)!= MI_RESULT_OK)
        return MI_RESULT_FAILED;

    /* Add string */
    {
        ZChar* data = (ZChar*)(((char*)(buf->page+1))+ buf->position);
        data[0] = '<';
        memcpy(data + 1, tag, n - sizeof(ZChar));
        data[size + 1] = '>';
        data[size + 2] = 0;

        buf->position += n - sizeof(ZChar);
    }

    return MI_RESULT_OK;
}

MI_Result WSBuf_AddEndTag(
    WSBuf* buf,
    const ZChar* tag,
    MI_Uint32 size)
{
    /* Add 3 bytes for "</" and ">" */
    MI_Uint32 n = (size + 1 + 3)* sizeof(ZChar);

    /* Extend buffer (WSBuf_AddLit determined it was too small)*/
    if (_ReallocPage(buf, n + buf->position)!= MI_RESULT_OK)
        return MI_RESULT_FAILED;

    /* Add string */
    {
        ZChar* data = (ZChar*)(((char*)(buf->page+1))+ buf->position);
        data[0] = '<';
        data[1] = '/';
        memcpy(data + 2, tag, n - sizeof(ZChar));
        data[size + 2] = '>';
        data[size + 3] = 0;

        buf->position += n - sizeof(ZChar);
    }

    return MI_RESULT_OK;
}

/* Add string with proper xml encoding */
MI_Result WSBuf_AddString(
    WSBuf* buf,
    const ZChar* str)
{
#if (MI_CHAR_TYPE == 1)

    /* Process leading non-special characters in the hope that little will
     * be left over to be encoded the expensive way below this block.
     */
    {
        const unsigned char* start = (const unsigned char*)str;
        const unsigned char* p = start;

        while (!s_specialChars[*p])
            p++;

        if (p != start)
        {
            if (WSBuf_AddLit(buf, (const char*)start, (MI_Uint32)(p - start)))
                return MI_RESULT_FAILED;

            str = (const char*)p;
        }

        if (!*str)
            return MI_RESULT_OK;
    }

#endif

    /* Now encode what remains (starting with first special char hit above)*/
    {
        /*MI_Uint32 size = (MI_Uint32)((MI_Strlen(str)+ 1)*sizeof(ZChar));*/
        ZChar* start = (ZChar*)(((char*)(buf->page +1))+ buf->position);
        ZChar* pos = start;
        ZChar* end = (ZChar*)(((char*)(buf->page +1))+ buf->page->u.s.size);
        /* Add reamingin characters (next character is special)*/
        while (*str)
        {
            const ZChar* item;
            size_t size_chars;
            MI_Uint32 c = (MI_Uint32)(MI_Sint16)*str;

            /* if c is ascii ?*/
            if (c < 128)
            {
                /* First byte is the length */
                item = s_specialCharEncodings[c] + 1;
                size_chars = s_specialCharEncodings[c][0];
            }
            else
            {
                item = str;
                size_chars = 1;
            }

            /* Extend buffer if needed */
            if ((size_t)(end - pos)<= (size_chars + 1))
            {
                size_t current_pos =
                    (pos - ((ZChar*)(buf->page +1)))* sizeof(ZChar);

                if (_ReallocPage(buf, (MI_Uint32)(buf->page->u.s.size + size_chars * sizeof(ZChar)))!= MI_RESULT_OK)
                    return MI_RESULT_FAILED;

                pos = (ZChar*)(((char*)(buf->page +1))+ current_pos);
                end = (ZChar*)(((char*)(buf->page +1))+ buf->page->u.s.size);
            }

            if (1 == size_chars)
                *pos = *item;
            else
                memcpy(pos, item, size_chars * sizeof(ZChar));

            pos += size_chars;
            str++;
        }

        buf->position = (MI_Uint32)((pos - ((ZChar*)(buf->page +1)))* sizeof(ZChar));

        /* put \0 at the end */
        ((ZChar*)(((char*)(buf->page +1))+ buf->position))[0] = 0;

        return MI_RESULT_OK;
    }
}

#if defined(CONFIG_ENABLE_WCHAR)
MI_Result WSBuf_AddCharLit(
    WSBuf* buf,
    const char* str,
    MI_Uint32 size_)
{
    MI_Uint32 size = (MI_Uint32)((size_ + 1)*sizeof(ZChar));

    /* Extend buffer if needed */
    if (size + buf->position > buf->page->u.s.size &&
        _ReallocPage(buf, size + buf->position)!= MI_RESULT_OK)
        return MI_RESULT_FAILED;

    {
        ZChar* data = (ZChar*)(((char*)(buf->page +1))+ buf->position);
        MI_Uint32 i;

        for (i = 0; i < size_; i++)
        {
            *data++ = *str++;
        }
        buf->position += size - sizeof(ZChar);
    }

    return MI_RESULT_OK;
}
#endif /* defined(CONFIG_ENABLE_WCHAR)*/

MI_Result WSBuf_AddVerbatim(
    WSBuf* buf,
    const void* data,
    MI_Uint32 size)
{
    size_t newSize = buf->position + size;

    /* Extend buffer if needed */
    if (newSize > buf->page->u.s.size)
    {
        if (_ReallocPage(buf, newSize)!= MI_RESULT_OK)
            return MI_RESULT_FAILED;
    }

    {
        void* pos = ((char*)(buf->page + 1))+ buf->position;
        memcpy(pos, data, size);
        buf->position += size;
    }

    return MI_RESULT_OK;
}

#if defined(CONFIG_ENABLE_WCHAR)
MI_Result WSBuf_AddCharStringNoEncoding(
    WSBuf* buf,
    const char* str)
{
    return WSBuf_AddCharLit(buf, str, (MI_Uint32)strlen(str));
}
#endif /* defined(CONFIG_ENABLE_WCHAR)*/

/* Callback to tag writer:
    allows to write properties for both values/EPRs with the same routine */
typedef MI_Result (*PropertyTagWriter)(
    WSBuf* buf,
    const ZChar* name,
    MI_Boolean start,
    MI_Uint32 flags,
    const ZChar* nsPrefix);

static MI_Result PackCimErrorXsiType(
    WSBuf* buf,
    MI_Uint32 nameLength,
    const ZChar* name)
{
    if (((nameLength == 13) && (Tcscmp(name, ZT("CIMStatusCode")) == 0)) ||
            ((nameLength == 12) && (Tcscmp(name, ZT("OMI_Category")) == 0)) ||
            ((nameLength == 8) && (Tcscmp(name, ZT("OMI_Code")) == 0)) ||
            ((nameLength == 17) && (Tcscmp(name, ZT("PerceivedSeverity")) == 0)) ||
            ((nameLength == 13) && (Tcscmp(name, ZT("ProbableCause")) == 0)))
    {
        if (MI_RESULT_OK != WSBuf_AddLit(buf, LIT(ZT(" xsi:type=\"cim:cimUnsignedInt\""))))
        {
            return MI_RESULT_FAILED;
        }
    }
    else
    if (((nameLength == 7) && (Tcscmp(name, ZT("Message")) == 0)) ||
        ((nameLength == 16) && (Tcscmp(name, ZT("MessageArguments")) == 0)) ||
        ((nameLength == 9) && (Tcscmp(name, ZT("MessageID")) == 0)) ||
        ((nameLength == 16) && (Tcscmp(name, ZT("OMI_ErrorMessage")) == 0)) ||
        ((nameLength == 8) && (Tcscmp(name, ZT("OMI_Type")) == 0)) ||
        ((nameLength == 12) && (Tcscmp(name, ZT("OwningEntity")) == 0)) ||
        ((nameLength == 24) && (Tcscmp(name, ZT("ProbableCauseDescription")) == 0)))
    {
        if (MI_RESULT_OK != WSBuf_AddLit(buf, LIT(ZT(" xsi:type=\"cim:cimString\""))))
        {
            return MI_RESULT_FAILED;
        }
    }
    return MI_RESULT_OK;
}

INLINE MI_Result PropertyTagWriter_PropStart(
    WSBuf* buf,
    const ZChar* name,
    MI_Uint32 flags,
    const ZChar* nsPrefix)
{
    MI_Uint32 n = (MI_Uint32)Tcslen(name);

    if (WSBuf_AddLit1(buf, '<') != MI_RESULT_OK ||
        WSBuf_AddStringNoEncoding(buf, nsPrefix) != MI_RESULT_OK ||
        WSBuf_AddLit1(buf, ':') != MI_RESULT_OK ||
        MI_RESULT_OK != WSBuf_AddLit(buf, name, n))
    {
        return MI_RESULT_FAILED;
    }
    if (flags & WSMAN_IsCimError)
    {
        if (MI_RESULT_OK != PackCimErrorXsiType(buf, n, name))
        {
            return MI_RESULT_FAILED;
        }
    }
    if (MI_RESULT_OK != WSBuf_AddLit1(buf,'>'))
    {
        return MI_RESULT_FAILED;
    }
    return MI_RESULT_OK;
}

INLINE MI_Result PropertyTagWriter_PropEnd(
    WSBuf* buf,
    const ZChar* name,
    MI_Uint32 flags,
    const ZChar* nsPrefix)
{
    MI_Uint32 n = (MI_Uint32)Tcslen(name);

    if (WSBuf_AddLit2(buf, '<', '/') != MI_RESULT_OK ||
        WSBuf_AddStringNoEncoding(buf, nsPrefix) != MI_RESULT_OK ||
        WSBuf_AddLit1(buf, ':') != MI_RESULT_OK ||
        MI_RESULT_OK != WSBuf_AddLit(buf, name, n)||
        MI_RESULT_OK != WSBuf_AddLit2(buf, '>', '\n'))
    {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

static MI_Result PropertyTagWriter_Prop(
    WSBuf* buf,
    const ZChar* name,
    MI_Boolean start,
    MI_Uint32 flags,
    const ZChar* nsPrefix)
{
    if (start)
        return PropertyTagWriter_PropStart(buf, name, flags, nsPrefix);
    else
        return PropertyTagWriter_PropEnd(buf, name, flags, nsPrefix);
}

static MI_Result PropertyTagWriter_EPR(
    WSBuf* buf,
    const ZChar* name,
    MI_Boolean start,
    MI_Uint32 flags,
    const ZChar* nsPrefix) //ignored
{
    if (start)
    {
        if (MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT("<wsman:Selector Name=\"")))||
            MI_RESULT_OK != WSBuf_AddStringNoEncoding(buf,name)||
            MI_RESULT_OK != WSBuf_AddLit2(buf, '"', '>')
           )
            return MI_RESULT_FAILED;
    }
    else
    {
        if (MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT("</wsman:Selector>")XML_CR))
           )
            return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

static MI_Result _PackFieldNil(
    WSBuf* buf,
    const ZChar* name,
    MI_Type type,
    MI_Uint32 flags,
    const ZChar* parentNSPrefix)
{
    if (WSBuf_AddLit1(buf, '<') != MI_RESULT_OK ||
        WSBuf_AddStringNoEncoding(buf, parentNSPrefix) != MI_RESULT_OK ||
        WSBuf_AddLit1(buf, ':') != MI_RESULT_OK ||
        MI_RESULT_OK != WSBuf_AddStringNoEncoding(buf,name))
        return MI_RESULT_FAILED;

    trace_Wsman_PackFieldNil( ((flags & WSMAN_UsePreciseArrays) != 0) );
    // adding msft specific attributes
    if (((flags & WSMAN_UsePreciseArrays) != 0) && (type & MI_ARRAY_BIT))
    {
        if(MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT(" msftwinrm:IsNullArray=\"true\""))))
            return MI_RESULT_FAILED;
    }

    if(MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT(" xsi:nil=\"true\""))))
        return MI_RESULT_FAILED;

    if (flags & WSMAN_IsCimError)
    {
        MI_Uint32 n = (MI_Uint32)Tcslen(name);

        if (MI_RESULT_OK != PackCimErrorXsiType(buf, n, name))
        {
            return MI_RESULT_FAILED;
        }
    }
    if (MI_RESULT_OK != WSBuf_AddLit(buf, LIT(ZT("/>")XML_CR)))
    {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

static int _Base64Callback(
    const char* data,
    size_t size,
    void* callbackData)
{
    WSBuf* buf = callbackData;
    return WSBuf_AddCharLit(buf, data, size)== MI_RESULT_OK ? 0 : -1;
}

static MI_Result _PackFieldOctetString(
    WSBuf* buf,
    const ZChar* name,
    const MI_Uint8* data,
    size_t size,
    const ZChar* nsPrefix)
{
    /* Validate first 4 bytes which contain the length then remove them */
    {
        size_t length = 0;

        if (size < 4)
            return MI_RESULT_FAILED;

        length |= ((size_t)data[0]) << 24;
        length |= ((size_t)data[1]) << 16;
        length |= ((size_t)data[2]) << 8;
        length |= data[3];

        if (length != size)
            return MI_RESULT_FAILED;

        data += 4;
        size -= 4;
    }

    if (WSBuf_AddLit1(buf, '<') != MI_RESULT_OK ||
        WSBuf_AddStringNoEncoding(buf, nsPrefix) != MI_RESULT_OK ||
        WSBuf_AddLit1(buf, ':') != MI_RESULT_OK)
        return MI_RESULT_FAILED;

    if (WSBuf_AddStringNoEncoding(buf, name)!= MI_RESULT_OK)
        return MI_RESULT_FAILED;

    if (WSBuf_AddLit(buf,
        LIT(ZT(" xsi:type=\"cim:cimBase64Binary\">")))!= MI_RESULT_OK)
    {
        return MI_RESULT_FAILED;
    }

    if (Base64Enc(data, size, _Base64Callback, buf)!= 0)
        return MI_RESULT_FAILED;

    if (PropertyTagWriter_PropEnd(buf, name, 0, nsPrefix)!= MI_RESULT_OK)
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

static MI_Result _PackFieldString(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    const ZChar* value,
    MI_Uint32 flags,
    const ZChar* nsPrefix)
{
    if (MI_RESULT_OK != writer(buf,name,MI_TRUE, flags, nsPrefix)||
        MI_RESULT_OK != WSBuf_AddString(buf,value)||
        MI_RESULT_OK != writer(buf,name,MI_FALSE, flags, nsPrefix)
       )
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

static MI_Result _PackFieldStringLit(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    const ZChar* value,
    MI_Uint32 valueSize,
    MI_Uint32 flags,
    const ZChar* nsPrefix)
{
    if (MI_RESULT_OK != writer(buf,name,MI_TRUE, flags, nsPrefix)||
        MI_RESULT_OK != WSBuf_AddLit(buf,value,valueSize)||
        MI_RESULT_OK != writer(buf,name,MI_FALSE, flags, nsPrefix)
       )
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

static MI_Result _PackFieldEmbeddedInstance(
    UserAgent userAgent,
    WSBuf* buf,
    const ZChar* name,
    const MI_Instance* value,
    MI_Uint32 flags,
    MI_Uint32 *lastPrefixIndex,
    const ZChar* parentNSPrefix)
{
    if (MI_RESULT_OK != _PackInstance(
        buf,
        userAgent,
        value,
        NULL,
        NULL,
        0,
        WSMAN_ObjectFlag | flags,
        MI_TRUE,
        name,
        lastPrefixIndex,
        parentNSPrefix))
    {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

static MI_Result _PackFieldRef(
    WSBuf* buf,
    PropertyTagWriter writer,
    UserAgent userAgent,
    const ZChar* name,
    const MI_Instance* value,
    MI_Uint32 flags,
    const ZChar* nsPrefix)
{
    if (MI_RESULT_OK != writer(buf,name, MI_TRUE, 0, nsPrefix)||
        MI_RESULT_OK != _PackEPR(buf, userAgent, value, flags)||
        MI_RESULT_OK != writer(buf,name, MI_FALSE, 0, nsPrefix)
       )
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

static MI_Result _PackFieldUint32(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    MI_Uint32 value,
    MI_Uint32 flags,
    const ZChar* nsPrefix)
{
    ZChar tmp[11];
    size_t size;
    const ZChar* str = Uint32ToZStr(tmp, value, &size);
    return _PackFieldStringLit(buf,writer, name, str, (MI_Uint32)size, flags, nsPrefix);
}

static MI_Result _PackFieldUint64(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    MI_Uint64 value,
    MI_Uint32 flags,
    const ZChar* nsPrefix)
{
    ZChar tmp[21];
    size_t size;
    const ZChar* str = NULL;
    Uint64ToZStr(tmp, value, &str, &size);
    return _PackFieldStringLit(buf, writer, name, str, (MI_Uint32)size, flags, nsPrefix);
}

static MI_Result _PackFieldSint32(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    MI_Sint32 value,
    MI_Uint32 flags,
    const ZChar* nsPrefix)
{
    ZChar s[24];

    MI_Sint32 size = Stprintf(s, MI_COUNT(s), ZT("%d"), value);
    return _PackFieldStringLit(buf,writer,name,s,size, flags, nsPrefix);
}

static MI_Result _PackFieldSint64(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    MI_Sint64 value,
    MI_Uint32 flags,
    const ZChar* nsPrefix)
{
    ZChar s[24];

    MI_Sint32 size = Stprintf(s, MI_COUNT(s), SINT64_FMT_T, value);
    return _PackFieldStringLit(buf,writer,name,s,size,flags, nsPrefix);
}

static MI_Result _PackFieldReal64(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    MI_Real64 value,
    MI_Uint32 flags,
    const ZChar* nsPrefix)
{
    ZChar s[24];

    /* Use DBL_DIG=15 for precision. Check MSDN DBL_DIG */
    MI_Sint32 size = Stprintf(s, MI_COUNT(s), ZT("%.15g"), value);
    return _PackFieldStringLit(buf,writer,name,s,size,flags, nsPrefix);
}

static MI_Result _PackFieldDatetime(
    WSBuf* buf,
    UserAgent userAgent,
    PropertyTagWriter writer,
    const ZChar* name,
    const MI_Datetime* p,
    MI_Uint32 flags,
    const ZChar* nsPrefix)
{
    ZChar tmp[64];
    const ZChar* tag = NULL;
    FormatWSManDatetime(p, tmp);

    if (writer(buf,name,MI_TRUE, flags, nsPrefix)!= MI_RESULT_OK)
        return MI_RESULT_FAILED;

    if (userAgent == USERAGENT_WINRM)
    {
        tag = p->isTimestamp ? ZT("cim:Datetime"): ZT("cim:Interval");
        WSBuf_AddStartTag(buf, tag, 12);
    }

    if (WSBuf_AddLit(buf, tmp, (MI_Uint32)Tcslen(tmp))!= MI_RESULT_OK)
        return MI_RESULT_FAILED;

    if (userAgent == USERAGENT_WINRM)
        WSBuf_AddEndTag(buf, tag, 12);

    if (writer(buf, name, MI_FALSE, flags, nsPrefix)!= MI_RESULT_OK)
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

static MI_Result _PackValue(
    WSBuf* buf,
    UserAgent userAgent,
    PropertyTagWriter writer,
    const ZChar* name,
    const void* field,
    MI_Type type,
    MI_Uint32 flags,
    MI_Uint32 *lastPrefixIndex,
    const ZChar* parentNSPrefix)
{
    switch(type)
    {
        case MI_BOOLEAN:
        {
            MI_Boolean* f = (MI_Boolean*)field;

            if (*f)
                return _PackFieldStringLit(buf,writer,name,LIT(ZT("TRUE")),flags, parentNSPrefix);
            else
                return _PackFieldStringLit(buf, writer, name, LIT(ZT("FALSE")), flags, parentNSPrefix);
        }
        case MI_UINT8:
        {
            MI_Uint8* f = (MI_Uint8*)field;

            return _PackFieldUint32(buf, writer, name, *f, flags, parentNSPrefix);
        }
        case MI_UINT16:
        {
            MI_Uint16* f = (MI_Uint16*)field;

            return _PackFieldUint32(buf, writer, name, *f, flags, parentNSPrefix);
        }
        case MI_UINT32:
        {
            MI_Uint32* f = (MI_Uint32*)field;

            return _PackFieldUint32(buf, writer, name, *f, flags, parentNSPrefix);
        }
        case MI_UINT64:
        {
            MI_Uint64* f = (MI_Uint64*)field;

            return _PackFieldUint64(buf, writer, name, *f, flags, parentNSPrefix);
        }
        case MI_SINT8:
        {
            MI_Sint8* f = (MI_Sint8*)field;

            return _PackFieldSint32(buf, writer, name, *f, flags, parentNSPrefix);
        }
        case MI_SINT16:
        {
            MI_Sint16* f = (MI_Sint16*)field;

            return _PackFieldSint32(buf, writer, name, *f, flags, parentNSPrefix);
        }
        case MI_SINT32:
        {
            MI_Sint32* f = (MI_Sint32*)field;

            return _PackFieldSint32(buf,writer,name,*f, flags, parentNSPrefix);
        }
        case MI_SINT64:
        {
            MI_Sint64* f = (MI_Sint64*)field;

            return _PackFieldSint64(buf, writer, name, *f, flags, parentNSPrefix);
        }
        case MI_REAL32:
        {
            MI_Real32* f = (MI_Real32*)field;

            return _PackFieldReal64(buf, writer, name, *f, flags, parentNSPrefix);
        }
        case MI_REAL64:
        {
            MI_Real64* f = (MI_Real64*)field;

            return _PackFieldReal64(buf, writer, name, *f, flags, parentNSPrefix);
        }
        case MI_DATETIME:
        {
            MI_Datetime* f = (MI_Datetime*)field;

            return _PackFieldDatetime(buf, userAgent, writer, name, &*f, flags, parentNSPrefix);
        }
        case MI_CHAR16:
        {
            MI_Char16* f = (MI_Char16*)field;
#if 0
#if (MI_CHAR_TYPE == 1)
            char s[6];
            memset(s,0,sizeof(s));

            _UTF16toUTF8(*f,s);
#else
            /* whcar_t -
            steal page will translate it */
            wchar_t s[2] = {0, 0};

            s[0] = *f;
#endif

            /* ATTN: convert it to utf8 and encode as a string */
            return _PackFieldString(buf,writer,name,s, flags, parentNSPrefix);
#else
            return _PackFieldUint32(buf, writer, name, (MI_Uint32)*f, flags, parentNSPrefix);
#endif
        }
        case MI_INSTANCE:
        {
            MI_Instance** f = (MI_Instance**)field;

            return _PackFieldEmbeddedInstance(userAgent, buf, name, *f, flags, lastPrefixIndex, parentNSPrefix);
        }
        case MI_REFERENCE:
        {
            MI_Instance** f = (MI_Instance**)field;

            return _PackFieldRef(buf, writer, userAgent, name, *f, flags, parentNSPrefix);
        }
        case MI_STRING:
        {
            MI_String* f = (MI_String*)field;

            return _PackFieldString(buf, writer, name, *f, flags, parentNSPrefix);
        }
        default:
            break;
    }

    return MI_RESULT_OK;
}

static MI_Result _PackField(
    WSBuf* buf,
    UserAgent userAgent,
    PropertyTagWriter writer,
    const ZChar* name,
    const void* field,
    MI_Type type,
    MI_Boolean isOctetString,
    MI_Uint32 flags,
    MI_Uint32 *lastPrefixIndex,
    const ZChar* parentNSPrefix)
{
    /* Check if value is null */
    if (!_Field_GetExists(field, type))
        return _PackFieldNil(buf, name, type, flags, parentNSPrefix);

    /* Check if type is array:
        Arrays are encoded the same way regular instances are
        with repeating instance as many times as many elements are in array */
    if (type & MI_ARRAY_BIT)
    {
        if (isOctetString && type == MI_UINT8A)
        {
            MI_Uint8AField* f = (MI_Uint8AField*)field;
            return _PackFieldOctetString(buf, name, f->value.data,
                f->value.size, parentNSPrefix);
        }

        /* ATTN: STRING OctetString not handled! */

        {
            MI_ArrayField* f = (MI_ArrayField*)field;
            MI_Uint32 i;
            MI_Type stype = type & ~MI_ARRAY_BIT;
            char* currentValue = (char*)f->value.data;

            for (i = 0; i < f->value.size; i++)
            {
                if (_PackValue(
                    buf,
                    userAgent,
                    writer,
                    name,
                    currentValue,
                    stype,
                    flags,
                    lastPrefixIndex,
                    parentNSPrefix)!= MI_RESULT_OK)
                {
                    return MI_RESULT_FAILED;
                }

                currentValue += Type_SizeOf(stype);
            }

            return MI_RESULT_OK;
        }
    }

    return _PackValue(buf, userAgent, writer, name, field, type, flags, lastPrefixIndex, parentNSPrefix);
}

static MI_Result _PackEPR(
    WSBuf* buf,
    UserAgent userAgent,
    const MI_Instance* instance,
    MI_Uint32 flags)
{
    Instance* self = Instance_GetSelf( instance );
    const MI_ClassDecl* cd = self->classDecl;
    MI_Uint32 i;

    /* Put EPR header */
    if (MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT("<wsa:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:Address>")XML_CR
            ZT("<wsa:ReferenceParameters>")XML_CR
            ZT("<wsman:ResourceURI>http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/")))||
        MI_RESULT_OK != WSBuf_AddStringNoEncoding(buf,cd->name)||
        MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT("</wsman:ResourceURI>")XML_CR
            ZT("<wsman:SelectorSet>")XML_CR)))
        return MI_RESULT_FAILED;

    /* namespace (if present)*/
    if (self->nameSpace)
    {
        WSBuf_AddLit(buf, LIT(ZT("<wsman:Selector Name=\"__cimnamespace\">")));
        WSBuf_AddStringNoEncoding(buf, self->nameSpace);
        WSBuf_AddLit(buf, LIT(ZT("</wsman:Selector>")));
    }

    /* Put properties */
    for (i = 0; i < cd->numProperties; i++)
    {
        const MI_PropertyDecl* pd = cd->properties[i];
        const void* value = (char*)self + pd->offset;
        MI_Uint32 tmpLastPrefixIndex = 0;

        if ((pd->flags & MI_FLAG_KEY)== 0)
            continue;

        /* skip null values */
        if (!_Field_GetExists(value,(MI_Type)pd->type))
            continue;

        if (_PackValue(
            buf,
            userAgent,
            PropertyTagWriter_EPR,
            pd->name, value,
            (MI_Type)pd->type,
            flags,
            &tmpLastPrefixIndex,
            NULL) != MI_RESULT_OK)
        {
            return MI_RESULT_FAILED;
        }
    }

    /* close EPR */
    if (MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT("</wsman:SelectorSet>")XML_CR
            ZT("</wsa:ReferenceParameters>")XML_CR)))
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

static MI_Boolean TestOctetStringQualifier(
    const MI_PropertyDecl* pd)
{
    size_t i;

    for (i = 0; i < pd->numQualifiers; i++)
    {
        const MI_Qualifier* q = pd->qualifiers[i];

        if (Tcscasecmp(q->name, ZT("OctetString"))== 0
            && q->type == MI_BOOLEAN
            && q->value)
        {
            return *((const MI_Boolean*)q->value);
        }
    }

    return MI_FALSE;
}

#define WSMAN_SchemaFlagMask 0xf00
MI_Result WSBuf_ClassToBuf(_In_ const MI_Class *classObject,
                                MI_Uint32 flags,
                                Batch* batch,
                                void** ptrOut,
                                MI_Uint32* sizeOut)
{
    WSBuf buf;
    Page* page;

    MI_Result result = MI_RESULT_OK;
    MI_Application mi_application = MI_APPLICATION_NULL;
    MI_Serializer mi_serializer;
    MI_Uint32 bufferLenForSerialization = 0;

    // in future flags will be converted to the actual flags needed for serialization; for now just pass 0
    MI_UNREFERENCED_PARAMETER(flags);

    result = XmlSerializer_Create(&mi_application, 0, ZT("MI_XML"), &mi_serializer);
    if(result != MI_RESULT_OK)
        return result;

    trace_XmlSerializer_SerializeClass(flags & WSMAN_SchemaFlagMask);

    // pass 1 to compute the total needed length for serializing the class
    XmlSerializer_SerializeClass(&mi_serializer, flags & WSMAN_SchemaFlagMask, classObject, NULL, 0, &bufferLenForSerialization);

    // this was just length computation; we will get MI_RESULT_FAILED from here but the bufferLenForSerialization will have the needed length
    // we will just check whether even length returned was 0; in that case we fail immediately
    // but if we get non-zero length required, we will go ahead and allocate the necessary buffer and then do the serialization again to see if it succeeds.
    if(bufferLenForSerialization == 0)
    {
        result = MI_RESULT_FAILED;
        goto End;
    }

    // allocating the needed size buffer before pass 2
    result = WSBuf_Init(&buf, bufferLenForSerialization);

    if (MI_RESULT_OK != result)
        goto End;

    // pass 2 to serialize the class into allocated buffer
    result = XmlSerializer_SerializeClass(&mi_serializer, flags & WSMAN_SchemaFlagMask, classObject, ((MI_Uint8*)(buf.page +1)), bufferLenForSerialization, &bufferLenForSerialization);

    if(result != MI_RESULT_OK)
    {
        WSBuf_Destroy(&buf);
        goto End;
    }

    // directly assigning the position since we already know how much we wrote in serialization
    buf.position = bufferLenForSerialization;
    page = WSBuf_StealPage(&buf);
    Batch_AttachPage(batch, page);

    *ptrOut = page + 1;

    *sizeOut = (MI_Uint32)page->u.s.size;
    result = MI_RESULT_OK;

End:
    XmlSerializer_Close(&mi_serializer);
    return result;
}

static MI_Result _PackInstance(
    WSBuf* buf,
    UserAgent userAgent,
    const MI_Instance* instance,
    MI_Boolean (*filterProperty)(const ZChar* name, void* data),
    void* filterPropertyData,
    const MI_ClassDecl* castToClassDecl,
    MI_Uint32 flags,
    MI_Boolean embedded,
    const ZChar* propName,
    MI_Uint32 *lastPrefixIndex,
    const ZChar* parentNSPrefix) //optional
{
    Instance* self = Instance_GetSelf( instance );
    const MI_ClassDecl* cd = castToClassDecl ? castToClassDecl : self->classDecl;
    MI_Uint32 i;
    const ZChar* name;

    /* Check for null arguments */
    if (!self || !buf)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* For Object & EPR, add <Item> tag */
    if (!embedded &&
        ((flags & WSMAN_ObjectAndEPRFlag)== WSMAN_ObjectAndEPRFlag))
    {
        if (MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT("<wsman:Item>")XML_CR)))
            return MI_RESULT_FAILED;
    }

    /* If object was requested */
    if ((flags & WSMAN_ObjectFlag)== WSMAN_ObjectFlag)
    {
        const ZChar* cn;
        const ZChar* elementName;
        ZChar nsPrefix[12];  // p followed by index and

        //GeneratePrefix
        {
            MI_Uint32 used = 1;
            nsPrefix[0] = ZT('p');

            if (*lastPrefixIndex)
            {
                used += Stprintf(nsPrefix + 1, 11, ZT("%d"), *lastPrefixIndex);
            }

            if (used > 11)  // should never happen
                return MI_RESULT_FAILED;

            nsPrefix[used] = ZT('\0');
            (*lastPrefixIndex)++;
        }

        if ((cd->flags & MI_FLAG_METHOD) && ((MI_MethodDecl*)cd)->propagator)
            cn = ((MI_MethodDecl*)cd)->propagator;
        else
            cn = cd->name;

        elementName = propName ? propName : cn;

        /* <p:propName ... type='class_Type> */
        if ((flags & WSMAN_IsCimError) == 0)
        {
            if (WSBuf_AddLit1(buf, '<') != MI_RESULT_OK ||
                WSBuf_AddStringNoEncoding(buf, parentNSPrefix ? parentNSPrefix:nsPrefix) != MI_RESULT_OK ||
                WSBuf_AddLit1(buf, ':') != MI_RESULT_OK ||
                WSBuf_AddStringNoEncoding(buf, elementName) != MI_RESULT_OK)
            {
                return MI_RESULT_FAILED;
            }

            /* If parameters, append "_OUTPUT" suffix */

#ifndef DISABLE_SHELL
            if (flags & WSMAN_IsShellOperation)
            {
                if (Tcscmp(elementName, MI_T("Stream")) == 0)
                {
                    MI_Value value;
                    MI_Type type;
                    MI_Uint32 flags;

                    /* commandId is an optional attribute */
                    if (MI_Instance_GetElement(instance, MI_T("commandId"), &value, &type, &flags, 0) == MI_RESULT_OK &&
                        (flags & MI_FLAG_NULL) == 0)
                    {
                        if (WSBuf_AddStringNoEncoding(buf, MI_T(" CommandId=\"")) != MI_RESULT_OK ||
                            WSBuf_AddStringNoEncoding(buf, value.string) != MI_RESULT_OK ||
                            WSBuf_AddLit1(buf, '"') != MI_RESULT_OK)
                        {
                            return MI_RESULT_FAILED;
                        }
                    }

                    /* End attribute is optional and only needed if we are at endOfStream */
                    if (MI_Instance_GetElement(instance, MI_T("endOfStream"), &value, &type, &flags, 0) == MI_RESULT_OK &&
                        (flags & MI_FLAG_NULL) == 0 &&
                        value.boolean)
                    {
                        if (WSBuf_AddStringNoEncoding(buf, MI_T(" End=\"true\"")) != MI_RESULT_OK )
                        {
                            return MI_RESULT_FAILED;
                        }
                    }

                    /* stream name is mandatory attribute*/
                    if (MI_Instance_GetElement(instance, MI_T("streamName"), &value, &type, &flags, 0) == MI_RESULT_OK &&
                        (flags & MI_FLAG_NULL) == 0 )
                    {
                        if (WSBuf_AddStringNoEncoding(buf, MI_T(" Name=\"")) != MI_RESULT_OK ||
                            WSBuf_AddStringNoEncoding(buf, value.string) != MI_RESULT_OK ||
                            WSBuf_AddLit1(buf, '"') != MI_RESULT_OK)
                        {
                            return MI_RESULT_FAILED;
                        }
                    }
                }
                else if (Tcscmp(elementName, MI_T("CommandState")) == 0)
                {
                    MI_Value value;
                    MI_Type type;
                    MI_Uint32 flags;

                    /* commandId is a mandatory attribute */
                    if (MI_Instance_GetElement(instance, MI_T("commandId"), &value, &type, &flags, 0) == MI_RESULT_OK &&
                        (flags & MI_FLAG_NULL) == 0)
                    {
                        if (WSBuf_AddStringNoEncoding(buf, MI_T(" CommandId=\"")) != MI_RESULT_OK ||
                            WSBuf_AddStringNoEncoding(buf, value.string) != MI_RESULT_OK ||
                            WSBuf_AddLit1(buf, '"') != MI_RESULT_OK)
                        {
                            return MI_RESULT_FAILED;
                        }
                    }

                    /* State is a mandatory attribute */
                    if (MI_Instance_GetElement(instance, MI_T("state"), &value, &type, &flags, 0) == MI_RESULT_OK &&
                        (flags & MI_FLAG_NULL) == 0)
                    {
                        if (WSBuf_AddStringNoEncoding(buf, MI_T(" State=\"")) != MI_RESULT_OK ||
                            WSBuf_AddStringNoEncoding(buf, value.string) != MI_RESULT_OK ||
                            WSBuf_AddLit1(buf, '"') != MI_RESULT_OK)
                        {
                            return MI_RESULT_FAILED;
                        }
                    }

                    /* ExitCode is optional attribute and only present if the command has finished */
                    if (MI_Instance_GetElement(instance, MI_T("ExitCode"), &value, &type, &flags, 0) == MI_RESULT_OK &&
                        (flags & MI_FLAG_NULL) == 0 )
                    {
                        if (WSBuf_AddStringNoEncoding(buf, MI_T(" ExitCode=\"")) != MI_RESULT_OK ||
                            WSBuf_AddUint32(buf, value.uint32) != MI_RESULT_OK ||
                            WSBuf_AddLit1(buf, '"') != MI_RESULT_OK)
                        {
                            return MI_RESULT_FAILED;
                        }
                    }
                }
                else if (WSBuf_AddStringNoEncoding(buf, ZT("Response")) != MI_RESULT_OK)
                {
                    return MI_RESULT_FAILED;
                }      }
            else
#endif
            if (cd->flags & MI_FLAG_METHOD)
            {
                if (WSBuf_AddStringNoEncoding(buf, ZT("_OUTPUT")) != MI_RESULT_OK)
                {
                    return MI_RESULT_FAILED;
                }
            }


#ifndef DISABLE_SHELL
            if (flags & WSMAN_IsShellOperation)
            {
                if (WSBuf_AddLit(buf, LIT(ZT(" xmlns:"))) != MI_RESULT_OK ||
                        WSBuf_AddStringNoEncoding(buf, nsPrefix) != MI_RESULT_OK ||
                        WSBuf_AddLit(buf, LIT(ZT("=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell"))) != MI_RESULT_OK ||
                        WSBuf_AddLit2(buf, '"', '\n') != MI_RESULT_OK)
                {
                    return MI_RESULT_FAILED;
                }
            }
            else
#endif
            {
                if (WSBuf_AddLit(buf, LIT(ZT(" xmlns:"))) != MI_RESULT_OK ||
                        WSBuf_AddStringNoEncoding(buf, nsPrefix) != MI_RESULT_OK ||
                        WSBuf_AddLit(buf, LIT(ZT("=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/"))) != MI_RESULT_OK ||
                        WSBuf_AddStringNoEncoding(buf, cn) != MI_RESULT_OK ||
                        WSBuf_AddLit2(buf, '"', '\n') != MI_RESULT_OK)
                {
                    return MI_RESULT_FAILED;
                }
                if (embedded)
                {
                    if (WSBuf_AddLit(buf,LIT(ZT(" xsi:type=\""))) != MI_RESULT_OK ||
                        WSBuf_AddStringNoEncoding(buf, nsPrefix) != MI_RESULT_OK ||
                        WSBuf_AddLit1(buf, ':') != MI_RESULT_OK ||
                        WSBuf_AddStringNoEncoding(buf,cn) != MI_RESULT_OK ||
                        MI_RESULT_OK != WSBuf_AddLit(buf,ZT("_Type\""), 6))
                    {
                        return MI_RESULT_FAILED;
                    }
                }
            }


            if (WSBuf_AddLit2(buf, '>', '\n') != MI_RESULT_OK)
                return MI_RESULT_FAILED;
        }

        /* Put properties */
        for (i = 0; i < cd->numProperties; i++)
        {
            const MI_PropertyDecl* pd = cd->properties[i];
            const void* value = (char*)self + pd->offset;
            MI_Boolean isOctetString = MI_FALSE;

            if (filterProperty &&
                (*filterProperty)(pd->name, filterPropertyData))
            {
                continue;
            }

            /* Search for OctetString qualifier */

            if (pd->type == MI_UINT8A || pd->type == MI_STRINGA)
                isOctetString = TestOctetStringQualifier(pd);

            /* Skip non-out params; rename 'MIReturn' to  'ReturnValue' */

            name = pd->name;

            if (pd->flags & MI_FLAG_PARAMETER)
            {
                if (!(pd->flags & MI_FLAG_OUT))
                    continue;

                if (name[0] == 'M' && Tcscmp(name, ZT("MIReturn")) == 0)
                {
#ifndef DISABLE_SHELL
                    if (flags & WSMAN_IsShellOperation)
                        continue;
#endif

                    name = ZT("ReturnValue");
                }
            }

#ifndef DISABLE_SHELL
            if (flags & WSMAN_IsShellOperation)
            {
                if (Tcscmp(elementName, ZT("Stream")) == 0)
                {
                    if (Tcscmp(name, ZT("commandId")) == 0 ||
                        Tcscmp(name, ZT("streamName")) == 0 ||
                        Tcscmp(name, ZT("endOfStream")) == 0)
                    {
                        /* These were added as attributes */
                        continue;
                    }
                    else if (Tcscmp(name, ZT("data")) == 0)
                    {
                        MI_StringField *field = (MI_StringField*) value;
                        if (field->exists &&
                            WSBuf_AddStringNoEncoding(buf, field->value) != MI_RESULT_OK)
                        {
                            return MI_RESULT_FAILED;
                        }
                        break; /* There should be nothing else so we may as wel exit loop */
                    }
                }
                else if (Tcscmp(elementName, ZT("CommandState")) == 0)
                {

                    /* All properties are added as attributes */
                    break;
                }
                else if ((Tcscmp(cn, ZT("Connect")) == 0) && (Tcscmp(name, ZT("connectResponseXml")) == 0))
                {
                    /* Need to add this field directly as it is already an xml element */
                    MI_StringField *field = (MI_StringField*) value;
                    if (field->exists &&
                        WSBuf_AddStringNoEncoding(buf, field->value) != MI_RESULT_OK)
                    {
                        return MI_RESULT_FAILED;
                    }
                    break;
                }
            }
#endif

            /* Pack the field */

            if (_PackField(
                buf,
                userAgent,
                PropertyTagWriter_Prop,
                name,
                value,
                (MI_Type)pd->type,
                isOctetString,
                flags, lastPrefixIndex, nsPrefix)!= MI_RESULT_OK)
            {
                return MI_RESULT_FAILED;
            }
        }

        /* </p:elementName> */
        if ((flags & WSMAN_IsCimError) == 0)
        {
            if (WSBuf_AddLit2(buf, '<', '/') != MI_RESULT_OK ||
                WSBuf_AddStringNoEncoding(buf, parentNSPrefix ? parentNSPrefix : nsPrefix) != MI_RESULT_OK ||
                WSBuf_AddLit1(buf, ':') != MI_RESULT_OK ||
                WSBuf_AddStringNoEncoding(buf, elementName) != MI_RESULT_OK)
            {
                return MI_RESULT_FAILED;
            }

#ifndef DISABLE_SHELL
            if (flags & WSMAN_IsShellOperation)
            {
                if (Tcscmp(elementName, MI_T("Stream")) != 0 &&
                    Tcscmp(elementName, MI_T("CommandState")) != 0 &&
                    WSBuf_AddStringNoEncoding(buf, ZT("Response")) != MI_RESULT_OK)
                {
                    return MI_RESULT_FAILED;
                }
            }
            else
#endif
            if ((cd->flags & MI_FLAG_METHOD) &&
                WSBuf_AddStringNoEncoding(buf, ZT("_OUTPUT")) != MI_RESULT_OK)
            {
                return MI_RESULT_FAILED;
            }

            if (WSBuf_AddLit2(buf, '>', '\n') != MI_RESULT_OK)
                return MI_RESULT_FAILED;
        }
    }

    /* If EPR was requested */
    if (!embedded &&
        ((flags & WSMAN_EPRFlag)== WSMAN_EPRFlag))
    {
        if (MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT("<wsa:EndpointReference>")XML_CR))||
            MI_RESULT_OK != _PackEPR(buf, userAgent, instance, flags)||
            MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT("</wsa:EndpointReference>")XML_CR)))
            return MI_RESULT_FAILED;
    }

    /* If EPR was requested */
    if ((flags & WSMAN_CreatedEPRFlag)== WSMAN_CreatedEPRFlag)
    {
        if (MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT("<wxf:ResourceCreated>")XML_CR))||
            MI_RESULT_OK != _PackEPR(buf, userAgent, instance, flags)||
            MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT("</wxf:ResourceCreated>")XML_CR)))
            return MI_RESULT_FAILED;
    }

    /* For Object & EPR, add </Item> tag */
    if (!embedded &&
        ((flags & WSMAN_ObjectAndEPRFlag)== WSMAN_ObjectAndEPRFlag))
    {
        if (MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT("</wsman:Item>")XML_CR)))
            return MI_RESULT_FAILED;
    }


    return MI_RESULT_OK;
}

MI_Result WSBuf_InstanceToBuf(
    UserAgent userAgent,
    const MI_Instance* instance,
    MI_Boolean (*filterProperty)(const ZChar* name, void* data),
    void* filterPropertyData,
    const MI_ClassDecl* castToClassDecl,
    Batch* batch,
    MI_Uint32 flags,
    void** ptrOut,
    MI_Uint32* sizeOut)
{
    WSBuf buf;
    MI_Result r;
    Page* page;
    MI_Uint32 lastPrefixIndex = 0;

    r = WSBuf_Init(&buf,1024);

    if (MI_RESULT_OK != r)
        return r;

    // Passing NULL as the PropName as this is not embeddedInstance
    // As the second last parameter is MI_FALSE
    r = _PackInstance(&buf, userAgent, instance, filterProperty,
        filterPropertyData, castToClassDecl, flags, MI_FALSE, NULL, &lastPrefixIndex, NULL);

    if (MI_RESULT_OK != r)
    {
        WSBuf_Destroy(&buf);
        return r;
    }

    page = WSBuf_StealPage(&buf);
    Batch_AttachPage(batch, page);

    *ptrOut = page + 1;
    *sizeOut = (MI_Uint32)page->u.s.size;
    return MI_RESULT_OK;
}

_Use_decl_annotations_
void WSBuf_GenerateMessageID(
    ZChar msgID[WS_MSG_ID_SIZE])
{
    //WS-Management qualifies the use of wsa:MessageID and wsa:RelatesTo as follows:
    //R5.4.6.4-1: The MessageID and RelatesTo URIs may be of any format, as long as they are valid
    //URIs according to RFC 3986. Two URIs are considered different even if the characters in the
    //URIs differ only by case.
    //The following two formats are endorsed by this specification. The first is considered a best
    //practice because it is backed by RFC 4122:
    //urn:uuid:xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
    //or
    //uuid:xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
    //In these formats, each x is an uppercase or lowercase hexadecimal digit (lowercase is required
    //by RFC 4122); there are no spaces or other tokens. The value may be a DCE-style universally
    //unique identifier (UUID)with provable uniqueness properties in this format, however, it is not
    //necessary to have provable uniqueness properties in the URIs used in the wsa:MessageID and
    //wsa:RelatesTo headers.
    //Regardless of format, the URI should not exceed the maximum defined in R13.1-6.
    //UUIDs have a numeric meaning as well as a string meaning, and this can lead to confusion. A UUID
    //in lowercase is a different URI from the same UUID in uppercase. This is because URIs are case1619
    //tive. If a UUID is converted to its decimal equivalent the case of the original characters is lost.
    //WS-Management works with the URI value itself, not the underlying decimal equivalent
    //representation. Services are free to interpret the URI in any way, but are not allowed to alter the case
    //usage when repeating the message or any of the MessageID values in subsequent messages.
    //The RFC 4122 requires the digits to be lowercase, which is the responsibility of the client. The service
    //simply processes the values as URI values and is not required to analyze the URI for correctness or
    //compliance. The service replicates the client usage in the wsa:RelatesTo reply header and is not
    //allowed to alter the case usage.
    //R5.4.6.4-2: The MessageID should be generated according to any algorithm that ensures that no
    //two MessageIDs are repeated. Because the value is treated as case-sensitive (R5.4.6.4-1),
    //confusion can arise if the same value is reused differing only in case. As a result, the service shall
    //not create or employ MessageID values that differ only in case. For any message transmitted by
    //the service, the MessageID shall not be reused.

    static MI_Uint64  s1, s2;

    if (!s1)
        PAL_Time(&s1);

    s2++;

    /* ADC */
    if (!s2)
        s1++;

    Stprintf(msgID, WS_MSG_ID_SIZE,
        ZT("uuid:%08X-%04X-%04X-%04X-%08X%04X"),
        (MI_Uint32)(s1 & 0xFFFFFFFF),
        (MI_Uint32)((s1 >> 32)& 0xFFFF),
        (MI_Uint32)((s1 >> 48)& 0xFFFF),
        (MI_Uint32)((s2 >> 48)& 0xFFFF),
        (MI_Uint32)(s2 & 0xFFFFFFFF),
        (MI_Uint32)((s2 >> 32)& 0xFFFF));
}

MI_Result WSBuf_CreateSoapResponseHeader(
    WSBuf* buf,
    const ZChar* action,
    MI_Uint32 actionSize,
    const ZChar* relatesTo)
{
    ZChar msgID[WS_MSG_ID_SIZE];

    /* Response header */
    if (MI_RESULT_OK != WSBuf_AddLit(buf,
        LIT(
        ZT("<SOAP-ENV:Envelope ")
        ZT("xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" ")
        ZT("xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ")
        ZT("xmlns:wsen=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\" ")
        ZT("xmlns:e=\"http://schemas.xmlsoap.org/ws/2004/08/eventing\" ")
        ZT("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ")
        ZT("xmlns:wsmb=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\" ")
        ZT("xmlns:wsman=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" ")
        ZT("xmlns:wxf=\"http://schemas.xmlsoap.org/ws/2004/09/transfer\" ")
        ZT("xmlns:cim=\"http://schemas.dmtf.org/wbem/wscim/1/common\" ")
        ZT("xmlns:msftwinrm=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\" ")
        /* ZT("xmlns:xml=\"http://www.w3.org/XML/1998/namespace\" ")*/
        ZT("xmlns:wsmid=\"http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd\">")
        XML_CR
        ZT("<SOAP-ENV:Header>")XML_CR
        ZT("<wsa:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:To>")XML_CR
        ZT("<wsa:Action>"))))
    {
        goto failed;
    }

    if (MI_RESULT_OK != WSBuf_AddLit(buf, action, actionSize))
        goto failed;

    if (MI_RESULT_OK != WSBuf_AddLit(buf,
            LIT(ZT("</wsa:Action>")XML_CR
            ZT("<wsa:MessageID>"))))
        goto failed;

    /* Generate new uniqueue msg id */
    WSBuf_GenerateMessageID(msgID);

    if (MI_RESULT_OK != WSBuf_AddLit(buf, msgID, WS_MSG_ID_SIZE - 1))
        goto failed;

    if (MI_RESULT_OK != WSBuf_AddLit(buf,
        LIT(ZT("</wsa:MessageID>")XML_CR)))
        goto failed;

    if (relatesTo)
    {
        if (MI_RESULT_OK != WSBuf_AddLit(buf,
            LIT(ZT("<wsa:RelatesTo>"))))
            goto failed;

        if (MI_RESULT_OK != WSBuf_AddStringNoEncoding(buf, relatesTo))
            goto failed;

        if (MI_RESULT_OK != WSBuf_AddLit(buf,
            LIT(ZT("</wsa:RelatesTo>")XML_CR)))
            goto failed;
    }

    return MI_RESULT_OK;

failed:
    return MI_RESULT_FAILED;
}

Page* WSBuf_CreateFaultResponsePage(
    WSBUF_FAULT_CODE faultCode,
    const ZChar* notUnderstoodTag,
    const ZChar* requestMessageID,
    const PostResultMsg* message)
{
    WSBuf   outBuf;
    const BUF_FaultItem* fault;
    const ZChar* textToSend;

    if (((MI_Uint32)faultCode)>= MI_COUNT(s_faults))
    {
        fault = s_faults + 0; /* internal error */
    }
    else
    {
        fault = s_faults + (MI_Uint32)faultCode;
    }

    /* prepare soap response with error */
    if (WSBuf_Init(&outBuf, 1024)!= MI_RESULT_OK)
        return 0;

    /* fault header */
    if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(&outBuf,
        fault->action, fault->actionSize, requestMessageID))
        goto failed;

    if (notUnderstoodTag)
    {
        if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<SOAP-ENV:NotUnderstood qname=\""))))
            goto failed;

        if (MI_RESULT_OK != WSBuf_AddStringNoEncoding(
            &outBuf,
            notUnderstoodTag))
        {
            goto failed;
        }

        if (MI_RESULT_OK != WSBuf_AddLit3(&outBuf, '"', '/', '>'))
            goto failed;
    }

    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(
        ZT("</SOAP-ENV:Header>")XML_CR XML_CR
        ZT("<SOAP-ENV:Body>")XML_CR
        ZT("<SOAP-ENV:Fault>")XML_CR
        ZT("<SOAP-ENV:Code>")XML_CR
        ZT("<SOAP-ENV:Value>"))))
        goto failed;

    if (MI_RESULT_OK != WSBuf_AddCharStringNoEncoding(&outBuf, fault->code))
        goto failed;
        //SOAP-ENV:Sender

    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(ZT("</SOAP-ENV:Value>")XML_CR)))
        goto failed;

    if (fault->subCode)
    {
        if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
            LIT(ZT("<SOAP-ENV:Subcode>")XML_CR
            ZT("<SOAP-ENV:Value>"))))
            goto failed;

        if (MI_RESULT_OK != WSBuf_AddCharStringNoEncoding(
            &outBuf,
            fault->subCode))
        {
            goto failed;
        }

        if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
            LIT(ZT("</SOAP-ENV:Value>")XML_CR
            ZT("</SOAP-ENV:Subcode>")XML_CR)))
            goto failed;
    }

    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(ZT("</SOAP-ENV:Code>")XML_CR
        ZT("<SOAP-ENV:Reason>")XML_CR
        ZT("<SOAP-ENV:Text xml:lang=\"en-US\">"))))
        goto failed;

    textToSend = fault->defaultText;

    if (message->errorMessage)
    {
        textToSend = message->errorMessage;
    }

    if (MI_RESULT_OK != WSBuf_AddString(&outBuf, textToSend))
    {
        goto failed;
    }

    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(ZT("</SOAP-ENV:Text>")XML_CR
        ZT("</SOAP-ENV:Reason>")XML_CR)))
    {
        goto failed;
    }

    if (message->result == (MI_Result) ERROR_WSMAN_SERVICE_STREAM_DISCONNECTED)
    {
        /* This is a specific shell error that needs special treatment. Ideally we would marshal the
         * error type across such that we can handle each of them related to the WinRM errors. We
         * only have 1 right now so this works!
         */
        if ((MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                        LIT(ZT("<SOAP-ENV:Detail>")
                            ZT("<p:WSManFault xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsmanfault\" Code=\"")
                           )
                        )))
        {
            goto failed;
        }

        if (MI_RESULT_OK != WSBuf_AddUint32(&outBuf, message->result))
            goto failed;

        if (MI_RESULT_OK != WSBuf_AddLit(&outBuf, LIT(ZT("\">"))))
        {
            goto failed;
        }

        if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
            LIT(ZT("<p:Message xsi:type=\"cim:cimString\">"))))
        {
            goto failed;
        }

        if (MI_RESULT_OK != WSBuf_AddString(&outBuf, textToSend))
        {
            goto failed;
        }

        if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
            LIT(ZT("</p:Message>")XML_CR)))
        {
            goto failed;
        }
        if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                    LIT(ZT("</p:WSManFault>")
                        ZT("</SOAP-ENV:Detail>"))))
        {
            goto failed;
        }
    }
    else if ((message->result != MI_RESULT_OK) || (NULL != message->packedInstancePtr))
    {
        if ((MI_RESULT_OK != WSBuf_AddLit(&outBuf, LIT(ZT("<SOAP-ENV:Detail>")XML_CR ZT("<p:")))) ||
            (MI_RESULT_OK != WSBuf_AddString(&outBuf, (message->cimErrorClassName?message->cimErrorClassName:ZT("OMI_Error")))) ||
            (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                                          LIT(ZT(" wsmb:IsCIM_Error=\"true\" ")
                                              ZT("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ")
                                              ZT("xmlns:wsmb=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\" ")
                                              ZT("xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/OMI_Error\" ")
                                              ZT("xmlns:cim=\"http://schemas.dmtf.org/wbem/wscim/1/common\">")))))
        {
            goto failed;
        }

        if (message->packedInstancePtr)
        {
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf, message->packedInstancePtr, message->packedInstanceSize/sizeof(MI_Char)))
            {
                goto failed;
            }
        }
        else
        {
            /* Create OMI_Error from the error code and string passed in */

            // CIM_Error:CIMStatusCode
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<p:CIMStatusCode xsi:type=\"cim:cimUnsignedInt\">"))))
            {
                goto failed;
            }

            if (MI_RESULT_OK != WSBuf_AddUint32(&outBuf, message->result))
                goto failed;

            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("</p:CIMStatusCode>")XML_CR)))
            {
                goto failed;
            }

            // CIM_Error:Message
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<p:Message xsi:type=\"cim:cimString\">"))))
            {
                goto failed;
            }

            if (MI_RESULT_OK != WSBuf_AddString(&outBuf, textToSend))
            {
                goto failed;
            }

            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("</p:Message>")XML_CR)))
            {
                goto failed;
            }

            // CIM_Error:MessageArguments
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<p:MessageArguments xsi:type=\"cim:cimString\"></p:MessageArguments>"))))
            {
                goto failed;
            }

            //  CIM_Error:MessageID
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<p:MessageID xsi:type=\"cim:cimString\">OMI:MI_Result:"))))
            {
                goto failed;
            }

            if (MI_RESULT_OK != WSBuf_AddUint32(&outBuf, message->result))
                goto failed;

            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("</p:MessageID>")XML_CR)))
            {
                goto failed;
            }

            //OMI_Category - uint32
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<p:OMI_Category xsi:type=\"cim:cimUnsignedInt\">"))))
            {
                goto failed;
            }

            if (MI_RESULT_OK != WSBuf_AddUint32(&outBuf, ErrorCategoryFromErrorCode(message->result, PAL_T("MI"))))
                goto failed;

            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("</p:OMI_Category>")XML_CR)))
            {
                goto failed;
            }

            //OMI_Code - uint32
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<p:OMI_Code xsi:type=\"cim:cimUnsignedInt\">"))))
            {
                goto failed;
            }

            if (MI_RESULT_OK != WSBuf_AddUint32(&outBuf, message->result))
                goto failed;

            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("</p:OMI_Code>")XML_CR)))
            {
                goto failed;
            }

            //OMI_ErrorMessage - string
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<p:OMI_ErrorMessage xsi:type=\"cim:cimString\">"))))
            {
                goto failed;
            }

            if (MI_RESULT_OK != WSBuf_AddString(&outBuf, textToSend))
            {
                goto failed;
            }

            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("</p:OMI_ErrorMessage>")XML_CR)))
            {
                goto failed;
            }


            //OMI_Type - string
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<p:OMI_Type xsi:type=\"cim:cimString\">MI</p:OMI_Type>"))))
            {
                goto failed;
            }

            // CIM_Error:OwningEntity
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<p:OwningEntity xsi:type=\"cim:cimString\">OMI:CIMOM</p:OwningEntity>"))))
            {
                goto failed;
            }

            // CIM_Error:PerceivedSeverity
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<p:PerceivedSeverity xsi:type=\"cim:cimUnsignedInt\">7</p:PerceivedSeverity>"))))
            {
                goto failed;
            }

            // CIM_Error:ProbableCause
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<p:ProbableCause xsi:type=\"cim:cimUnsignedInt\">0</p:ProbableCause>"))))
            {
                goto failed;
            }

            // CIM_Error:ProbableCauseDescription
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
                LIT(ZT("<p:ProbableCauseDescription xsi:type=\"cim:cimString\">Unknown</p:ProbableCauseDescription>"))))
            {
                goto failed;
            }
        }


        if ((MI_RESULT_OK != WSBuf_AddLit(&outBuf, LIT(ZT("</p:"))) ||
            (MI_RESULT_OK != WSBuf_AddString(&outBuf, (message->cimErrorClassName?message->cimErrorClassName:ZT("OMI_Error")))) ||
            (MI_RESULT_OK != WSBuf_AddLit(&outBuf, LIT(ZT(">") XML_CR ZT("</SOAP-ENV:Detail>")XML_CR)))))
        {
            goto failed;
        }
    }

    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(ZT("</SOAP-ENV:Fault>")XML_CR
        ZT("</SOAP-ENV:Body>")XML_CR
        ZT("</SOAP-ENV:Envelope>")XML_CR)))
    {
        goto failed;
    }

    return WSBuf_StealPage(&outBuf);

failed:

    WSBuf_Destroy(&outBuf);
    return 0;
}

Page* WSBuf_CreateReleaseResponsePage(
    const ZChar* requestMessageID)
{
    WSBuf   outBuf;

    /* prepare soap response with error */
    if (WSBuf_Init(&outBuf, 1024)!= MI_RESULT_OK)
        return 0;

    /* fault header */
    if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(&outBuf,
        LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/enumeration/ReleaseResponse")),
        requestMessageID))
        goto failed;

    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(
        ZT("</SOAP-ENV:Header>")XML_CR XML_CR
        ZT("<SOAP-ENV:Body/>")XML_CR
        ZT("</SOAP-ENV:Envelope>")XML_CR)))
        goto failed;

    return WSBuf_StealPage(&outBuf);

failed:

    WSBuf_Destroy(&outBuf);
    return 0;
}

WSBUF_FAULT_CODE WSBuf_CIMErrorToWSFault(
    MI_Uint32 cimErrorCode,
    const ZChar** description)
{
    MI_Uint32 index = cimErrorCode < MI_COUNT(s_cimerrors)? cimErrorCode : MI_RESULT_FAILED;

    if (description)
        *description = s_cimerrors[index].description;

    return s_cimerrors[index].faultCode;
}

// Add <tag attributes>
MI_Result WSBuf_AddStartTagWithAttrs(
    WSBuf* buf,
    const ZChar* tag,
    MI_Uint32 tagSize,
    const ZChar* attributes,
    MI_Uint32 attributesSize)
{
    if (!tag || tagSize == 0)
    {
        return MI_RESULT_FAILED;
    }

    if (!attributes || attributesSize == 0)
    {
        return WSBuf_AddStartTag(buf, tag, tagSize);
    }

    if (MI_RESULT_OK != WSBuf_AddLit(buf, LIT(ZT("<"))) ||
        MI_RESULT_OK != WSBuf_AddLit(buf, tag, tagSize) ||
        MI_RESULT_OK != WSBuf_AddLit(buf, LIT(ZT(" "))) ||
        MI_RESULT_OK != WSBuf_AddLit(buf, attributes, attributesSize) ||
        MI_RESULT_OK != WSBuf_AddLit(buf, LIT(ZT(">"))))
    {
        return MI_RESULT_FAILED;
    }
    return MI_RESULT_OK;

    // speed version
/*
    // Add 3 bytes for "<" , " ", and ">"
    MI_Uint32 n = tagSize + 1 + 3 + attributesSize;
    ZChar *element = (ZChar*)SystemMalloc(n * sizeof(ZChar));

    element[0] = '<';
    memcpy(element + 1, tag, tagSize * sizeof(ZChar));
    element[tagSize + 1] = ' ';
    memcpy(element + tagSize + 2, attributes, attributeSize * sizeof(ZChar));
    element[n-2] = '>';
    element[n-1] = 0;

    MI_Result result =  WSBuf_AddLit(buf, element, n);
    SystemFree(element);
    
    return result;
*/
}

// Add <tag attributes/>
MI_Result WSBuf_AddTag(
    WSBuf* buf,
    const ZChar* tag,
    MI_Uint32 tagSize,
    const ZChar* attributes,
    MI_Uint32 attributesSize)
{
    if (!tag || tagSize == 0 || !attributes || attributesSize == 0)
    {
        return MI_RESULT_FAILED;
    }

    if (MI_RESULT_OK != WSBuf_AddLit(buf, LIT(ZT("<"))) ||
        MI_RESULT_OK != WSBuf_AddLit(buf, tag, tagSize) ||
        MI_RESULT_OK != WSBuf_AddLit(buf, LIT(ZT(" "))) ||
        MI_RESULT_OK != WSBuf_AddLit(buf, attributes, attributesSize) ||
        MI_RESULT_OK != WSBuf_AddLit(buf, LIT(ZT("/>"))))
    {
        return MI_RESULT_FAILED;
    }
    return MI_RESULT_OK;
}

// Add <tag mustUnderstand="true">
MI_Result WSBuf_AddStartTagMustUnderstand(
    WSBuf* buf,
    const ZChar* tag,
    MI_Uint32 tagSize)
{
    return WSBuf_AddStartTagWithAttrs(buf, tag, tagSize, LIT(ZT("s:mustUnderstand=\"true\"")));
}

//Create header for the packet 
static MI_Result WSBuf_CreateRequestHeader(WSBuf* buf, const WsmanCliHeaders* cliHeaders )
{
    ZChar msgID[WS_MSG_ID_SIZE];
    WSBuf_GenerateMessageID(msgID);
    
    // Envelope
    if (MI_RESULT_OK != WSBuf_AddStartTagWithAttrs(buf,
                                                   LIT(ZT("s:Envelope")),
                                                   LIT(ZT("xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" ")
                                                       ZT("xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ")
                                                       ZT("xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" ")
                                                       ZT("xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\" "))))
    {
        goto failed;
    }


    // Header section
    if (MI_RESULT_OK != WSBuf_AddStartTag (buf, LIT(ZT("s:Header"))))
    {
        goto failed;
    }

    if (MI_RESULT_OK != WSBuf_AddStartTag(buf, LIT(ZT("a:To"))) ||
        MI_RESULT_OK != WSBuf_AddStartTagMustUnderstand(buf, LIT(ZT("a:Address"))) || 
        MI_RESULT_OK != WSBuf_AddStringNoEncoding(buf, cliHeaders->toAddress) ||
        MI_RESULT_OK != WSBuf_AddEndTag(buf, LIT( ZT("a:Address"))) ||
        MI_RESULT_OK != WSBuf_AddEndTag(buf, LIT( ZT("a:To"))))
    { 
        goto failed;
    }
    
    // resource uri
    if (cliHeaders->resourceUri)
    {
        if (MI_RESULT_OK != WSBuf_AddStartTagMustUnderstand(buf, LIT(ZT("w:ResourceURI"))) || 
            MI_RESULT_OK != WSBuf_AddStringNoEncoding(buf, cliHeaders->resourceUri) ||
            MI_RESULT_OK != WSBuf_AddEndTag(buf, LIT(ZT("w:ResourceURI"))))
        {
            goto failed;
        }            
    }

    // replyto 
    if (MI_RESULT_OK != WSBuf_AddStartTag(buf, LIT(ZT("a:ReplyTo"))) ||
        MI_RESULT_OK != WSBuf_AddStartTagMustUnderstand(buf, LIT(ZT("a:Address"))) || 
        MI_RESULT_OK != WSBuf_AddLit(buf, LIT(ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous"))) ||
        MI_RESULT_OK != WSBuf_AddEndTag(buf, LIT( ZT("a:Address"))) ||
        MI_RESULT_OK != WSBuf_AddEndTag(buf, LIT(ZT("a:ReplyTo"))))
    {
        goto failed;
    }
    
    // action
    if (MI_RESULT_OK != WSBuf_AddStartTag(buf, LIT(ZT("a:Action"))) ||
        MI_RESULT_OK != WSBuf_AddStringNoEncoding(buf, cliHeaders->action) ||        
        MI_RESULT_OK != WSBuf_AddEndTag(buf, LIT(ZT("a:Action"))))
    {
        goto failed; 
    }
        
    // max envelope size 
    if (MI_RESULT_OK != WSBuf_AddStartTagMustUnderstand(buf, LIT(ZT("w:MaxEnvelopeSize"))) || 
        MI_RESULT_OK != WSBuf_AddUint32(buf, cliHeaders->maxEnvelopeSize) ||
        MI_RESULT_OK != WSBuf_AddEndTag(buf, LIT(ZT("w:MaxEnvelopeSize"))))
    {
        goto failed;
    }

    // message id 
    if (MI_RESULT_OK != WSBuf_AddStartTag(buf, LIT(ZT("a:MessageID"))) ||
        MI_RESULT_OK != WSBuf_AddLit(buf, msgID, WS_MSG_ID_SIZE -1) ||
        MI_RESULT_OK != WSBuf_AddEndTag(buf, LIT(ZT("a:MessageID"))))
    {
        goto failed;
    }

    // OperationTimeout - optional
    if (cliHeaders->operationTimeout)
    {
        ZChar interval[64];
        if (cliHeaders->operationTimeout->isTimestamp)
        {
            goto failed;
        }

        FormatWSManDatetime(cliHeaders->operationTimeout, interval);

        if (MI_RESULT_OK != WSBuf_AddStartTag(buf, LIT(ZT("w:OperationTimeout"))) ||
            MI_RESULT_OK != WSBuf_AddStringNoEncoding(buf, interval) || 
            MI_RESULT_OK != WSBuf_AddEndTag(buf, LIT(ZT("w:OperationTimeout"))))
        {
            goto failed;
        }
    }

    // locale - optional 
    if (cliHeaders->locale != NULL)
    {
        ZChar lang[64];
        Stprintf(lang, MI_COUNT(lang), ZT("xml:lang=\"%s\" s:mustUnderstand=\"false\""), cliHeaders->locale);

        if (MI_RESULT_OK != WSBuf_AddTag(buf, LIT(ZT("w:Locale")), lang, (MI_Uint32)Tcslen(lang)))
        {
            goto failed; 
        }
    }

    // data locale - optional 
    if (cliHeaders->datalocale != NULL)
    {
        ZChar lang[64];
        Stprintf(lang, MI_COUNT(lang), ZT("xml:lang=\"%s\" s:mustUnderstand=\"false\""), cliHeaders->datalocale);

        if (MI_RESULT_OK != WSBuf_AddTag(buf, LIT(ZT("p:DataLocale")), lang, (MI_Uint32)Tcslen(lang)))
        {
            goto failed; 
        }
    }

    // TODO - selector set 
/*
    if (MI_RESULT_OK != WSBuf_AddLit(buf, LIT(ZT("<w:SelectorSet>"))) ||
        MI_RESULT_OK != _PackRequestSelector(buf, userAgent, instance, cliHeaders->flags))
    {
        goto failed;
    }
*/
    
    // end Header 
    if (MI_RESULT_OK != WSBuf_AddEndTag(buf, LIT( ZT("s:Header"))))
    {
        goto failed;
    }

    return MI_RESULT_OK;       
    
 failed:
    return MI_RESULT_FAILED;    

}

MI_Result GetMessageRequest(
    WSBuf* buf,                            
    const WsmanCliHeaders *header)
{
    if (!buf || !header)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (MI_RESULT_OK != WSBuf_CreateRequestHeader(buf, header))
    {
        goto failed;
    }

    // Empty body and end envelope
    if (MI_RESULT_OK != WSBuf_AddStartTag(buf, LIT(ZT("s:Body"))) ||
        MI_RESULT_OK != WSBuf_AddEndTag(buf, LIT(ZT("s:Body"))) ||
        MI_RESULT_OK != WSBuf_AddEndTag(buf, LIT(ZT("s:Envelope"))))
    {
        goto failed; 
    }
        
    return MI_RESULT_OK;         

failed:
    return MI_RESULT_FAILED;
}


