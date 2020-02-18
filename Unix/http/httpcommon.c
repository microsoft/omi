/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "httpcommon.h"
#include <base/base64.h>
#include <base/log.h>
#include <base/memman.h>
#include <pal/format.h>

// 1. In the base versions of OpenSSL 0.9.8 and OpenSSL 1.0.0 (https://github.com/Microsoft/ostc-openssl), SSL_OP_NO_TLSv1_1 and SSL_OP_NO_TLSv1_2 are not defined in the ssl.h header file, 
//    but we need them in order to tell OpenSSL to disable these protocols on later versions of OpenSSL 0.9.8/1.0.0.
// 2. We need these both variables to disable TLS1.1 and TLS1.2 if the customer requests to do so.
// 3. Ideally, we would just build our products against later versions of OpenSSL 0.9.8/1.0.0 which do contain those flags mentioned above, but this could end up being problematic. 
//    If we build against later versions of OpenSSL, then our products may not work for customers who have old versions of OpenSSL installed on their system due to symbol runtime resolution.
// 4. If these flags aren't defined during build time, then even if a customer is using a later version of OpenSSL that does support these flags, 
//    they will not be able to disable TLS v1_1 or v1_2. This was discovered by one of our customers.
#ifndef SSL_OP_NO_TLSv1_1
# define SSL_OP_NO_TLSv1_1                               0x10000000U
#endif
#ifndef SSL_OP_NO_TLSv1_2
# define SSL_OP_NO_TLSv1_2                               0x08000000U
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

MI_Result CreateSSLContext(SSL_CTX **sslContext, SSL_Options sslOptions)
{
    long options = 0;

    *sslContext = SSL_CTX_new(SSLv23_method());
    if (*sslContext == NULL)
    {
        trace_SSL_CannotCreateContext();
        return MI_RESULT_FAILED;
    }

    // Disable SSL and/or TLS if requested
    if ( sslOptions & DISABLE_SSL_V2 )
    {
        options |= SSL_OP_NO_SSLv2;
    }
    if ( sslOptions & DISABLE_SSL_V3 )
    {
        options |= SSL_OP_NO_SSLv3;
    }
    if ( sslOptions & DISABLE_TLS_V1_0 )
    {
        options |= SSL_OP_NO_TLSv1;
    }
    if ( sslOptions & DISABLE_TLS_V1_1 )
    {
        options |= SSL_OP_NO_TLSv1_1;
    }
    if ( sslOptions & DISABLE_TLS_V1_2 )
    {
        options |= SSL_OP_NO_TLSv1_2;
    }
    if ( sslOptions & DISABLE_SSL_COMPRESSION)
    {
#ifdef SSL_OP_NO_COMPRESSION
        options |= SSL_OP_NO_COMPRESSION;
#else
        trace_Http_SslCompressionNotPresent();
#endif
    }
    if ( options != 0)
    { 
        // If options is zero, the operation is a noop. SSL_CTX_set_options only sets, never clears

        MI_Uint32 set_options = SSL_CTX_set_options(*sslContext, options);

        // If we don't get the options we asked for, thats an issue. 

        if ((set_options & options) != options)
        {
            trace_SSL_CannotSetOptions( set_options ^ options );
            return MI_RESULT_FAILED;
        }
    }

    SSL_CTX_set_quiet_shutdown(*sslContext, 1);
    (void)SSL_CTX_set_mode(*sslContext, SSL_MODE_AUTO_RETRY | SSL_MODE_ENABLE_PARTIAL_WRITE);
    SSL_CTX_set_session_cache_mode(*sslContext, SSL_SESS_CACHE_OFF);

    return MI_RESULT_OK;
}

char* GetSslErrorString(
    _Out_ char* buf,
    _In_  size_t bufLength)
{
    unsigned long error = ERR_peek_last_error();

    ERR_error_string_n(error, buf, bufLength);
    return buf;
}

#endif
