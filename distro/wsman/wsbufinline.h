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

#ifndef _omi_wsman_wsbufinline_h
#define _omi_wsman_wsbufinline_h

/* add literal string to the buffer;
 * skip encoding of special characters;
 * length of the string is provided;
 * see LIT() macro
 */
#if !defined(WSBUF_DISABLE_INLINING)
INLINE
#endif
MI_Result WSBuf_AddLit(
    WSBuf* buf,
    const ZChar* str,
    MI_Uint32 size)
{
    MI_Uint32 n;
    n = size * sizeof(ZChar);

    if (n + buf->position < buf->page->u.s.size)
    {
        char* data = (char*)(buf->page + 1) + buf->position;
        memcpy(data, str, n);
        ((ZChar*)data)[size] = 0;

        buf->position += n;
        return MI_RESULT_OK;
    }

    /* Expand buffer and add string */
    return __WSBuf_AddLit(buf, str, size);
}

#if !defined(WSBUF_DISABLE_INLINING)
INLINE
#endif
MI_Result WSBuf_AddLit1(
    WSBuf* buf,
    ZChar c1)
{
# if !defined(CONFIG_FAVORSIZE)

    const MI_Uint32 SIZE = sizeof(c1);

    if (SIZE + buf->position < buf->page->u.s.size)
    {
        ZChar* data = (ZChar*)(((char*)(buf->page + 1)) + buf->position);
        data[0] = c1;
        data[1] = '\0';
        buf->position += SIZE;
        return MI_RESULT_OK;
    }

# endif
    return __WSBuf_AddLit(buf, &c1, 1);
}

#if !defined(WSBUF_DISABLE_INLINING)
INLINE
#endif
MI_Result WSBuf_AddLit2(
    WSBuf* buf,
    ZChar c1,
    ZChar c2)
{
# if !defined(CONFIG_FAVORSIZE)

    const MI_Uint32 SIZE = 2 * sizeof(c1);

    if (SIZE + buf->position < buf->page->u.s.size)
    {
        ZChar* data = (ZChar*)(((char*)(buf->page + 1)) + buf->position);
        data[0] = c1;
        data[1] = c2;
        data[2] = '\0';
        buf->position += SIZE;
        return MI_RESULT_OK;
    }

# endif

    {
        ZChar str[2];
        str[0] = c1;
        str[1] = c2;
        return __WSBuf_AddLit(buf, str, 2);
    }
}

#if !defined(WSBUF_DISABLE_INLINING)
INLINE
#endif
MI_Result WSBuf_AddLit3(
    WSBuf* buf,
    ZChar c1,
    ZChar c2,
    ZChar c3)
{
# if !defined(CONFIG_FAVORSIZE)

    const MI_Uint32 SIZE = 3 * sizeof(c1);

    if (SIZE + buf->position < buf->page->u.s.size)
    {
        ZChar* data = (ZChar*)(((char*)(buf->page + 1)) + buf->position);
        data[0] = c1;
        data[1] = c2;
        data[2] = c3;
        data[3] = '\0';
        buf->position += SIZE;
        return MI_RESULT_OK;
    }

# endif

    {
        ZChar str[3];
        str[0] = c1;
        str[1] = c2;
        str[2] = c3;
        return __WSBuf_AddLit(buf, str, 3);
    }
}

#if !defined(WSBUF_DISABLE_INLINING)
INLINE
#endif
MI_Result WSBuf_AddLit4(
    WSBuf* buf,
    ZChar c1,
    ZChar c2,
    ZChar c3,
    ZChar c4)
{
# if !defined(CONFIG_FAVORSIZE)

    const MI_Uint32 SIZE = 4 * sizeof(c1);

    if (SIZE + buf->position < buf->page->u.s.size)
    {
        ZChar* data = (ZChar*)(((char*)(buf->page + 1)) + buf->position);
        data[0] = c1;
        data[1] = c2;
        data[2] = c3;
        data[3] = c4;
        data[4] = '\0';
        buf->position += SIZE;
        return MI_RESULT_OK;
    }

# endif

    {
        ZChar str[4];
        str[0] = c1;
        str[1] = c2;
        str[2] = c3;
        str[3] = c4;
        return __WSBuf_AddLit(buf, str, 4);
    }
}

/* add string to the buffer; skip encoding of special characters
    typically used with const strings or already encoded values */
#if !defined(WSBUF_DISABLE_INLINING)
INLINE
#endif
MI_Result WSBuf_AddStringNoEncoding(
    WSBuf* buf,
    const ZChar* str)
{
    return WSBuf_AddLit(buf, str, (MI_Uint32)Zlen(str));
}

#endif /* _omi_wsman_wsbufinline_h */
