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

#include <common.h>
#include "wsbuf.h"
#include <base/log.h>
#include <base/result.h>
#include <base/instance.h>
#include <base/strings.h>
#include <base/field.h>
#include <base/messages.h>
#include <base/helpers.h>
#include <base/time.h>
#include <io/io.h>
#include <base/base64.h>

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
    MI_Boolean (*filterProperty)(const ZChar* name, void* data),
    void* filterPropertyData,
    const MI_ClassDecl* castToClassDecl,
    MI_Uint32 flags,
    MI_Boolean embedded,
    const ZChar* propName);

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
    new_page = (Page*)realloc(buf->page, sizeof(Page)+ newSize);

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
    buf->page = (Page*)malloc(sizeof(Page)+ initialSize);
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
        free(buf->page);

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
    MI_Uint32 flags);

INLINE MI_Result PropertyTagWriter_PropStart(
    WSBuf* buf,
    const ZChar* name,
    MI_Uint32 flags)
{
    MI_Uint32 n = (MI_Uint32)Zlen(name);

    if (MI_RESULT_OK != WSBuf_AddLit3(buf, '<', 'p', ':')||
        MI_RESULT_OK != WSBuf_AddLit(buf, name, n))
    {
        return MI_RESULT_FAILED;
    }
    if ((flags & WSMAN_IsCimError) && (n == 13) && (Zcmp(name, ZT("CIMStatusCode")) == 0) &&
        (MI_RESULT_OK != WSBuf_AddLit(buf, LIT(ZT(" xsi:type=\"cim:cimUnsignedInt\"")))))
    {
        return MI_RESULT_FAILED;
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
    MI_Uint32 flags)
{
    MI_Uint32 n = (MI_Uint32)Zlen(name);

    if (MI_RESULT_OK != WSBuf_AddLit4(buf, '<', '/', 'p', ':')||
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
    MI_Uint32 flags)
{
    if (start)
        return PropertyTagWriter_PropStart(buf, name, flags);
    else
        return PropertyTagWriter_PropEnd(buf, name, flags);
}

static MI_Result PropertyTagWriter_EPR(
    WSBuf* buf,
    const ZChar* name,
    MI_Boolean start,
    MI_Uint32 flags)
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
    MI_Uint32 flags)
{
    if (MI_RESULT_OK != WSBuf_AddLit3(buf, '<', 'p', ':')||
        MI_RESULT_OK != WSBuf_AddStringNoEncoding(buf,name)||
        MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT(" xsi:nil=\"true\"/>")XML_CR)))
        return MI_RESULT_FAILED;

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
    size_t size)
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

    if (WSBuf_AddLit3(buf, '<', 'p', ':')!= MI_RESULT_OK)
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

    if (PropertyTagWriter_PropEnd(buf, name, 0)!= MI_RESULT_OK)
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

static MI_Result _PackFieldString(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    const ZChar* value)
{
    if (MI_RESULT_OK != writer(buf,name,MI_TRUE, 0)||
        MI_RESULT_OK != WSBuf_AddString(buf,value)||
        MI_RESULT_OK != writer(buf,name,MI_FALSE, 0)
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
    MI_Uint32 flags)
{
    if (MI_RESULT_OK != writer(buf,name,MI_TRUE, flags)||
        MI_RESULT_OK != WSBuf_AddLit(buf,value,valueSize)||
        MI_RESULT_OK != writer(buf,name,MI_FALSE, flags)
       )
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

static MI_Result _PackFieldEmbeddedInstance(
    UserAgent userAgent,
    WSBuf* buf,
    const ZChar* name,
    const MI_Instance* value,
    MI_Uint32 flags)
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
        name))
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
    MI_Uint32 flags)
{
    if (MI_RESULT_OK != writer(buf,name, MI_TRUE, 0)||
        MI_RESULT_OK != _PackEPR(buf, userAgent, value, flags)||
        MI_RESULT_OK != writer(buf,name, MI_FALSE, 0)
       )
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}

static MI_Result _PackFieldUint32(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    MI_Uint32 value,
    MI_Uint32 flags)
{
    ZChar tmp[11];
    size_t size;
    const ZChar* str = Uint32ToZStr(tmp, value, &size);
    return _PackFieldStringLit(buf,writer, name, str, (MI_Uint32)size, flags);
}

static MI_Result _PackFieldUint64(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    MI_Uint64 value,
    MI_Uint32 flags)
{
    ZChar tmp[21];
    size_t size;
    const ZChar* str = Uint64ToZStr(tmp, value, &size);
    return _PackFieldStringLit(buf, writer, name, str, (MI_Uint32)size, flags);
}

static MI_Result _PackFieldSint32(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    MI_Sint32 value,
    MI_Uint32 flags)
{
    ZChar s[24];

    MI_Sint32 size = Szprintf(s, MI_COUNT(s), ZT("%d"), value);
    return _PackFieldStringLit(buf,writer,name,s,size, flags);
}

static MI_Result _PackFieldSint64(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    MI_Sint64 value,
    MI_Uint32 flags)
{
    ZChar s[24];

    MI_Sint32 size = Szprintf(s, MI_COUNT(s), SINT64_FMT_T, value);
    return _PackFieldStringLit(buf,writer,name,s,size,flags);
}

static MI_Result _PackFieldReal64(
    WSBuf* buf,
    PropertyTagWriter writer,
    const ZChar* name,
    MI_Real64 value,
    MI_Uint32 flags)
{
    ZChar s[24];

    MI_Sint32 size = Szprintf(s, MI_COUNT(s), ZT("%g"), value);
    return _PackFieldStringLit(buf,writer,name,s,size,flags);
}

static MI_Result _PackFieldDatetime(
    WSBuf* buf,
    UserAgent userAgent,
    PropertyTagWriter writer,
    const ZChar* name,
    const MI_Datetime* p,
    MI_Uint32 flags)
{
    ZChar tmp[64];
    const ZChar* tag = NULL;
    FormatWSManDatetime(p, tmp);

    if (writer(buf,name,MI_TRUE, flags)!= MI_RESULT_OK)
        return MI_RESULT_FAILED;

    if (userAgent == USERAGENT_WINRM)
    {
        tag = p->isTimestamp ? ZT("cim:Datetime"): ZT("cim:Interval");
        WSBuf_AddStartTag(buf, tag, 12);
    }

    if (WSBuf_AddLit(buf, tmp, (MI_Uint32)Zlen(tmp))!= MI_RESULT_OK)
        return MI_RESULT_FAILED;

    if (userAgent == USERAGENT_WINRM)
        WSBuf_AddEndTag(buf, tag, 12);

    if (writer(buf, name, MI_FALSE, flags)!= MI_RESULT_OK)
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
    MI_Uint32 flags)
{
    switch(type)
    {
        case MI_BOOLEAN:
        {
            MI_Boolean* f = (MI_Boolean*)field;

            if (*f)
                return _PackFieldStringLit(buf,writer,name,LIT(ZT("TRUE")),flags);
            else
                return _PackFieldStringLit(buf,writer,name,LIT(ZT("FALSE")),flags);
        }
        case MI_UINT8:
        {
            MI_Uint8* f = (MI_Uint8*)field;

            return _PackFieldUint32(buf,writer,name,*f, flags);
        }
        case MI_UINT16:
        {
            MI_Uint16* f = (MI_Uint16*)field;

            return _PackFieldUint32(buf,writer,name,*f, flags);
        }
        case MI_UINT32:
        {
            MI_Uint32* f = (MI_Uint32*)field;

            return _PackFieldUint32(buf,writer,name,*f, flags);
        }
        case MI_UINT64:
        {
            MI_Uint64* f = (MI_Uint64*)field;

            return _PackFieldUint64(buf,writer,name,*f, flags);
        }
        case MI_SINT8:
        {
            MI_Sint8* f = (MI_Sint8*)field;

            return _PackFieldSint32(buf,writer,name,*f, flags);
        }
        case MI_SINT16:
        {
            MI_Sint16* f = (MI_Sint16*)field;

            return _PackFieldSint32(buf,writer,name,*f, flags);
        }
        case MI_SINT32:
        {
            MI_Sint32* f = (MI_Sint32*)field;

            return _PackFieldSint32(buf,writer,name,*f, flags);
        }
        case MI_SINT64:
        {
            MI_Sint64* f = (MI_Sint64*)field;

            return _PackFieldSint64(buf,writer,name,*f, flags);
        }
        case MI_REAL32:
        {
            MI_Real32* f = (MI_Real32*)field;

            return _PackFieldReal64(buf,writer,name,*f, flags);
        }
        case MI_REAL64:
        {
            MI_Real64* f = (MI_Real64*)field;

            return _PackFieldReal64(buf,writer,name,*f, flags);
        }
        case MI_DATETIME:
        {
            MI_Datetime* f = (MI_Datetime*)field;

            return _PackFieldDatetime(buf, userAgent, writer, name, &*f, flags);
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
            return _PackFieldString(buf,writer,name,s);
#else
            return _PackFieldUint32(buf,writer,name,(MI_Uint32)*f, flags);
#endif
        }
        case MI_INSTANCE:
        {
            MI_Instance** f = (MI_Instance**)field;

            return _PackFieldEmbeddedInstance(userAgent, buf, name, *f, flags);
        }
        case MI_REFERENCE:
        {
            MI_Instance** f = (MI_Instance**)field;

            return _PackFieldRef(buf, writer, userAgent, name,*f, flags);
        }
        case MI_STRING:
        {
            MI_String* f = (MI_String*)field;

            return _PackFieldString(buf,writer,name,*f);
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
    MI_Uint32 flags)
{
    /* Check if value is null */
    if (!_Field_GetExists(field, type))
        return _PackFieldNil(buf, name, flags);

    /* Check if type is array:
        Arrays are encoded the same way regular instances are
        with repeating instance as many times as many elements are in array */
    if (type & MI_ARRAY_BIT)
    {
        if (isOctetString && type == MI_UINT8A)
        {
            MI_Uint8AField* f = (MI_Uint8AField*)field;
            return _PackFieldOctetString(buf, name, f->value.data,
                f->value.size);
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
                    flags)!= MI_RESULT_OK)
                {
                    return MI_RESULT_FAILED;
                }

                currentValue += Type_SizeOf(stype);
            }

            return MI_RESULT_OK;
        }
    }

    return _PackValue(buf, userAgent, writer, name, field, type, flags);
}

static MI_Result _PackEPR(
    WSBuf* buf,
    UserAgent userAgent,
    const MI_Instance* instance,
    MI_Uint32 flags)
{
    Instance* self = (Instance*)instance;
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
    }

    /* Put properties */
    for (i = 0; i < cd->numProperties; i++)
    {
        const MI_PropertyDecl* pd = cd->properties[i];
        const void* value = (char*)self + pd->offset;

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
            flags)!= MI_RESULT_OK)
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

        if (Zcasecmp(q->name, ZT("OctetString"))== 0
            && q->type == MI_BOOLEAN
            && q->value)
        {
            return *((const MI_Boolean*)q->value);
        }
    }

    return MI_FALSE;
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
    const ZChar* propName)
{
    Instance* self = (Instance*)instance;
    const MI_ClassDecl* cd = castToClassDecl ? castToClassDecl : self->classDecl;
    MI_Uint32 i;
    const ZChar* name;

    /* Check for null arguments */
    if (!self || !buf)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* For Object & EPR, add <Item> tag */
    if ((flags & WSMAN_ObjectAndEPRFlag)== WSMAN_ObjectAndEPRFlag)
    {
        if (MI_RESULT_OK != WSBuf_AddLit(buf,LIT(ZT("<wsman:Item>")XML_CR)))
            return MI_RESULT_FAILED;
    }

    /* If object was requested */
    if ((flags & WSMAN_ObjectFlag)== WSMAN_ObjectFlag)
    {
        const ZChar* cn;
        const ZChar* elementName;

        if ((cd->flags & MI_FLAG_METHOD) && ((MI_MethodDecl*)cd)->propagator)
            cn = ((MI_MethodDecl*)cd)->propagator;
        else
            cn = cd->name;

        elementName = propName ? propName : cn;

        /* <p:propName ... type='class_Type> */
        if ((flags & WSMAN_IsCimError) == 0)
        {
            if (WSBuf_AddLit3(buf, '<', 'p', ':') != MI_RESULT_OK ||
                WSBuf_AddStringNoEncoding(buf, elementName) != MI_RESULT_OK)
            {
                return MI_RESULT_FAILED;
            }

            /* If parameters, append "_OUTPUT" suffix */

            if ((cd->flags & MI_FLAG_METHOD) &&
                WSBuf_AddStringNoEncoding(buf, ZT("_OUTPUT")) != MI_RESULT_OK)
            {
                return MI_RESULT_FAILED;
            }

            if (WSBuf_AddLit(
                buf,
                LIT(ZT(" xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/"))) != MI_RESULT_OK ||
                WSBuf_AddStringNoEncoding(buf, cn) != MI_RESULT_OK ||
                WSBuf_AddLit2(buf, '"', '\n') != MI_RESULT_OK)
            {
                return MI_RESULT_FAILED;
            }

            if (embedded)
            {
                if (WSBuf_AddLit(buf,LIT(ZT(" xsi:type=\""))) != MI_RESULT_OK ||
                    WSBuf_AddStringNoEncoding(buf,cn) != MI_RESULT_OK ||
                    MI_RESULT_OK != WSBuf_AddLit(buf,ZT("_Type\""), 6))
                {
                    return MI_RESULT_FAILED;
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

                if (name[0] == 'M' && Zcmp(name, ZT("MIReturn"))== 0)
                    name = ZT("ReturnValue");
            }

            /* Pack the field */

            if (_PackField(
                buf,
                userAgent,
                PropertyTagWriter_Prop,
                name,
                value,
                (MI_Type)pd->type,
                isOctetString,
                flags)!= MI_RESULT_OK)
            {
                return MI_RESULT_FAILED;
            }
        }

        /* </p:elementName> */
        if ((flags & WSMAN_IsCimError) == 0)
        {
            if (WSBuf_AddLit4(buf, '<', '/', 'p', ':') != MI_RESULT_OK ||
                WSBuf_AddStringNoEncoding(buf,elementName) != MI_RESULT_OK)
            {
                return MI_RESULT_FAILED;
            }

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
    if ((flags & WSMAN_EPRFlag)== WSMAN_EPRFlag)
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
    if ((flags & WSMAN_ObjectAndEPRFlag)== WSMAN_ObjectAndEPRFlag)
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

    r = WSBuf_Init(&buf,1024);

    if (MI_RESULT_OK != r)
        return r;

    // Passing NULL as the PropName as this is not embeddedInstance
    // As the second last parameter is MI_FALSE
    r = _PackInstance(&buf, userAgent, instance, filterProperty,
        filterPropertyData, castToClassDecl, flags, MI_FALSE, NULL);

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
        Time_Now(&s1);

    s2++;

    /* ADC */
    if (!s2)
        s1++;

    Szprintf(msgID, WS_MSG_ID_SIZE,
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
        ZT("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ")
        ZT("xmlns:wsmb=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\" ")
        ZT("xmlns:wsman=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" ")
        ZT("xmlns:wxf=\"http://schemas.xmlsoap.org/ws/2004/09/transfer\" ")
        ZT("xmlns:cim=\"http://schemas.dmtf.org/wbem/wscim/1/common\" ")
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

    if ((message->result != MI_RESULT_OK) || (NULL != message->packedInstancePtr))
    {
        if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
            LIT(ZT("<SOAP-ENV:Detail>")XML_CR)))
        {
            goto failed;
        }

        if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
            LIT(ZT("<p:CIM_Error wsmb:IsCIM_Error=\"true\" ")
            ZT("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ")
            ZT("xmlns:wsmb=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\" ")
            ZT("xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/CIM_Error\" ")
            ZT("xmlns:cim=\"http://schemas.dmtf.org/wbem/wscim/1/common\">"))))
        {
            goto failed;
        }

        if (message->packedInstancePtr)
        {
            if (MI_RESULT_OK != WSBuf_AddLit(&outBuf, message->packedInstancePtr, message->packedInstanceSize))
            {
                goto failed;
            }
        }
        else
        {
            /* Create CIM Error from the error code and string passed in */

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
        }

        if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
            LIT(ZT("</p:CIM_Error>")XML_CR
            ZT("</SOAP-ENV:Detail>")XML_CR)))
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
