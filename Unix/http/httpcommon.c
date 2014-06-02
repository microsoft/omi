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

#include "httpcommon.h"
#include <base/base64.h>
#include <base/log.h>
#include <base/memman.h>
#include <pal/format.h>
#ifdef CONFIG_POSIX
# include <openssl/ssl.h>
# include <openssl/err.h>
#endif

static int _Base64DecCallback(
    const void* data, 
    size_t size, 
    void* callbackData)
{
    char** str = (char**)callbackData;
    size_t i;

    for (i = 0; i < size; i++)
    {
        **str = ((unsigned char*)data)[i];
        (*str)++;
    }

    return 0;
}

MI_Boolean _DecodeBasicAuth(
    _In_ HttpHeaders* recvHeaders,
    _In_z_ const char * src,
    _Out_writes_z_(tgtSize) _Null_terminated_ char * tgt,
    _In_ size_t tgtSize)
{
    char* startBuffer = tgt;
    MI_UNREFERENCED_PARAMETER(tgtSize);
    /* skip spaces in value */

    while (src[0] == ' ' || src[0] == '\t')
        src++;

    /* Decode the password */

    if (Base64Dec(src, strlen(src), _Base64DecCallback, &tgt) == -1)
    {
        trace_Base64Dec_Failed();
        return MI_FALSE;
    }
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26015)
#pragma prefast (disable: 26018)
#endif
    *tgt = 0;
#ifdef _PREFAST_
#pragma prefast (pop)
#endif
    /* decoded string has format: <uersname>[:<password>] */
    recvHeaders->username = startBuffer;
    startBuffer = strchr(startBuffer, ':');

    if ( startBuffer )
    {
        *startBuffer = 0;
        recvHeaders->password = startBuffer + 1;
        MemoryLock((void*)recvHeaders->password, strlen(recvHeaders->password));
    }

    return MI_TRUE; 
}

MI_Boolean ParseAuthorization(
    _Inout_     HttpHeaders*    recvHeaders,
    _In_        CharPtr         value )
{
    if (Strncasecmp(value, AUTHENTICATION_BASIC, AUTHENTICATION_BASIC_LENGTH) == 0)
    {
        /* since decoded string is smaller, performing decoding 
         * inplace; for source skip 'Basic ' part (6 chars) 
         */

        char * authvalue = value;
        size_t i;

        /*
        Set authorization value in the header. 
        We need to do that because in wsman layer an http 401 error will be thrown 
        if the authentication is not supported
        */
        recvHeaders->authorization = AUTHENTICATION_BASIC;

        for (i = 0; i < 6; ++i)
        {
            if (*authvalue == 0)
            {
                trace_Base64_DecodeErrorInBasic(scs(value));
                return MI_FALSE;
            }
            authvalue++;
        }

        if (!_DecodeBasicAuth(recvHeaders, authvalue, value, strlen(value)))
        {
            trace_Base64_DecodeErrorInBasic(scs(value));
            return MI_FALSE;
        }
    }
    else    /* unknown authorization type */
    {
        recvHeaders->authorization = value;
    }
    
    return MI_TRUE;
}

void ParseContentType(
    _Inout_     HttpHeaders*    recvHeaders,
    _In_        CharPtr         value )
{
    recvHeaders->contentType = value;

    /* find attribute list */
    while (value[0] != 0 && value[0] != ';')
        value++;

    /* Check if attribute list was provided */
    if (value[0] == 0)
        return;

    /* terminate type/subtype; move to attributes list */
    value[0] = 0;
    value++;

    /* skip spaces in value */
    while (value[0] == ' ' || value[0] == '\t')
        value++;

    /* find charset attribute (if present) */
    if (Strncasecmp(value,"charset=",8) != 0)
        return;

    /* skip 8 chars */
    {
        size_t i;
        for(i = 0; *value != 0 && i < 8; i++)
        {
            value++;
        }
    }

    recvHeaders->charset = value;

    /* can be enclosed in quotes */
    if (value[0] == '"')
    {
        /* skip '"' */
        recvHeaders->charset++;
        value++;
        value = strchr(value, '"');
        if (value)
            *value = 0;
        else
            recvHeaders->charset = 0;
    }
    else
    {
        /*skip trialing spaces */
        while (value[0] != 0 && value[0] != ' ' && value[0] != '\t')
            value++;

        *value = 0;
    }
}

#ifdef CONFIG_POSIX

char* GetSslErrorString(
    _Out_ char* buf,
    _In_  size_t bufLength)
{
    unsigned long error = ERR_peek_last_error();

    ERR_error_string_n(error, buf, bufLength);
    return buf;
}

#endif
