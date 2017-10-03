/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_http_httpcommon_h
#define _omi_http_httpcommon_h

#include <stddef.h>

#include "config.h"
#include <common.h>
#include <base/batch.h>
#include <base/interaction.h>
#include <sock/selector.h>
#include <base/paths.h>
#ifdef CONFIG_POSIX
# include <openssl/ssl.h>
# include <openssl/err.h>
#endif

BEGIN_EXTERNC

/* NTLM error codes */
enum ntlm_err_code {
    ERR_BASE = 0x4E540000, /* base error space at 'NT00' */
    ERR_DECODE,
    ERR_ENCODE,
    ERR_CRYPTO,
    ERR_NOARG,
    ERR_BADARG,
    ERR_NONAME,
    ERR_NOSRVNAME,
    ERR_NOUSRNAME,
    ERR_BADLMLVL,
    ERR_IMPOSSIBLE,
    ERR_BADCTX,
    ERR_WRONGCTX,
    ERR_WRONGMSG,
    ERR_REQNEGFLAG,
    ERR_FAILNEGFLAGS,
    ERR_BADNEGFLAGS,
    ERR_NOSRVCRED,
    ERR_NOUSRCRED,
    ERR_BADCRED,
    ERR_NOTOKEN,
    ERR_NOTSUPPORTED,
    ERR_NOTAVAIL,
    ERR_NAMETOOLONG,
    ERR_NOBINDINGS,
    ERR_TIMESKEW,
    ERR_EXPIRED,
    ERR_KEYLEN,
    ERR_NONTLMV1,
    ERR_NOUSRFOUND,
    ERR_LAST
};

/* HTTP Error codes */
#define HTTP_ERROR_CODE_OK                          200
#define HTTP_ERROR_CODE_BAD_REQUEST                 400
#define HTTP_ERROR_CODE_UNAUTHORIZED                401
#define HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR       500
#define HTTP_ERROR_CODE_NOT_SUPPORTED               501
/*
**==============================================================================
**
** Authentication progress state, digested auth type
**
**==============================================================================
*/

typedef enum _AuthMethod {
     AUTH_METHOD_UNSUPPORTED = -1,
     AUTH_METHOD_NONE = 0,
     AUTH_METHOD_BASIC,
     AUTH_METHOD_NEGOTIATE,
     AUTH_METHOD_NEGOTIATE_WITH_CREDS,
     AUTH_METHOD_KERBEROS,
     AUTH_METHOD_DIGEST,
     AUTH_METHOD_NTLMDOMAIN,
     AUTH_METHOD_CLIENTCERTS,
     AUTH_METHOD_CREDSSP,
     AUTH_METHOD_ISSUER_CERTS,
     AUTH_METHOD_BYPASS
} AuthMethod;

typedef enum _AuthMechanism {
     AUTH_MECH_UNSUPPORTED = -1,
     AUTH_MECH_NONE = 0,
     AUTH_MECH_KERBEROS,
     AUTH_MECH_NTLMSSP
} AuthMechanism;

/*
**==============================================================================
**
** Define supported Authentication and other related fields.
**
**==============================================================================
*/
#define AUTHENTICATION_NEGOTIATE        "Negotiate" /* Used for kerberos or ntlm authentication */
#define AUTHENTICATION_NEGOTIATE_LENGTH 9
#define AUTHENTICATION_KERBEROS         "Kerberos" /* Used for kerberos only authentication, no fallback */
#define AUTHENTICATION_KERBEROS_LENGTH  8
#define AUTHENTICATION_BASIC            "Basic"
#define AUTHENTICATION_BASIC_LENGTH     5 /*This is the length of "Basic"*/
#define HTTP_WWWAUTHENTICATE_BASIC      "WWW-Authenticate: Basic realm=\"WSMAN\""
#define HTTP_WWWAUTHENTICATE_NEGOTIATE  "WWW-Authenticate: Negotiate realm=\"WSMAN\""
#define HTTP_WWWAUTHENTICATE_KERBEROS   "WWW-Authenticate: Kerberos realm=\"WSMAN\""

/* ************************************************ */
/*                  Datatypes                       */
/* ************************************************ */
typedef struct _Http Http;

/* HTTP options.
    mostly used for unit-testing; default values
    are hard-coded but can be overwritten by 
    unit-tests/config modules   */
typedef struct _HttpOptions
{
    /* timeout for network delays and keep-alive;
    note: http does not have timeout for server/provider processing */
    MI_Uint64   timeoutUsec;

    /* Enable tracing of HTTP input and output */
    MI_Boolean enableTracing;
}
HttpOptions;

typedef struct _AuthOptionHttp
{
    unsigned int allowBasic :1;
    unsigned int allowNego: 1;
    unsigned int allowKrb5: 1;
    unsigned int requireEncrypt: 1;
}
AuthOptionHttp;

/* SSL_Options.
    Allows SSL or TLS to be individually disabled, or to disable
    both protocols, based on omiserver.conf and omicli.conf */
typedef enum _SSL_Options
{
    // Must be bits so these can be specified individually or together
    DISABLE_SSL_V2 = 0x01,
    DISABLE_SSL_V3 = 0x02,
    DISABLE_TSL_V1_0 = 0x04,
    DISABLE_TSL_V1_1 = 0x08,
    DISABLE_TSL_V1_2 = 0x10,
    DISABLE_SSL_COMPRESSION = 0x20
}
SSL_Options;

//------------------------------------------------------------------------------------------------------------------

/* 60 sec timeout */
#define DEFAULT_HTTP_OPTIONS  { (60 * 1000000), MI_FALSE }

MI_Result Http_New_Server(
    _Out_       Http**              selfOut,
    _In_        Selector*           selector,               /*optional, maybe NULL*/
    _In_        unsigned short      http_port,              /* 0 to disable */
    _In_        unsigned short      https_port,             /* 0 to disable */
    _In_opt_z_  const char*         sslCipherSuite,         /* NULL to disable */
    _In_        SSL_Options         sslOptions,             /* 0 for default options */
    _In_        OpenCallback        callbackOnNewConnection,
    _In_opt_    void*               callbackData,
    _In_opt_    const HttpOptions*  options,                /* Sets http options (mostly unit-test support) */
    _In_        AuthOptionHttp*     authOptionHttp);

MI_Result Http_Delete(
    Http* self);

MI_Result Http_Run(
    Http* self,
    MI_Uint64 timeoutUsec);

//------------------------------------------------------------------------------------------------------------------
// Auxiliary methods

MI_Boolean ParseAuthorization(
    _Inout_     HttpHeaders*    recvHeaders,
    _In_        CharPtr         value );

void ParseContentType(
    _Inout_     HttpHeaders*    recvHeaders,
    _In_        CharPtr         value );
    
#ifdef CONFIG_POSIX

MI_Result CreateSSLContext(SSL_CTX **sslContext, SSL_Options sslOptions);

char* GetSslErrorString(
    _Out_       char* buf,
    _In_        size_t bufLen);

#endif


void _WriteTraceFile(PathID id, const void* data, size_t size);

END_EXTERNC

#endif /* _omi_http_httpcommon_h */
