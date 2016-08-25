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
#include <gssapi/gssapi.h> 
#include <gssapi/gssapi_ext.h> 
#include <base/base.h>
#include <base/base64.h>
#include <base/paths.h>
#include <pal/lock.h>
#include <xml/xml.h>
#include <assert.h>
#include <ctype.h>
#include "httpcommon.h"
#include "httpclient.h"
#include <sock/addr.h>
#include <sock/sock.h>
#include <sock/selector.h>

#include "httpcommon.h"

// #define ENABLE_TRACING 1
#define FORCE_TRACING  1

#ifdef CONFIG_POSIX
#include <openssl/ssl.h>
#include <openssl/err.h>
#else
/* ssl not supported in this configuration; just make compiler happy */
typedef void SSL;
typedef void SSL_CTX;
#define SSL_CTX_free(c)
#define SSL_new(c) 0
#define SSL_free(c)
#define SSL_set_connect_state(c)
#define SSL_set_fd(c,a) (a==a)
#define SSL_read(c,a,b) 0
#define SSL_write(c,a,b) 0
#define SSL_get_error(c,e) e
#define SSL_ERROR_WANT_WRITE 0
#define SSL_ERROR_WANT_READ 1
#define SSL_ERROR_SYSCALL 2

#ifdef EWOULDBLOCK
# undef EWOULDBLOCK
#endif

#define EWOULDBLOCK 0

#ifdef EINPROGRESS
# undef EINPROGRESS
#endif

#define EINPROGRESS 0

#define ERR_get_error() 0
#define ERR_error_string_n(c,a,b) a[0]=0
#define SSL_accept(c) 0
#define SSL_connect(c) 0

#endif

//static gss_OID_desc gss_c_nt_user_name = {10, (void *)"\x2a\x86\x48\x86\xf7\x12\x01\x02\x01\x01"}; 
//gss_OID      GSS_C_NT_USER_NAME = &gss_c_nt_user_name;

#define HTTP_LONGEST_ERROR_DESCRIPTION 50

#include "httpclient_private.h"



void _WriteTraceFile(PathID id, const void* data, size_t size);


extern gss_OID gss_nt_service_name;


/* 
   Convert the gss_buffer_t token to a WWW-Authorization string suitable for the http response header
 */

struct _EncodeContext {
    int size;
    char *pdata;
};

static int EncodeSizeCallback(
                   const char* data,
                   size_t size,
                   void* callbackData)
{
   struct _EncodeContext *p_encode_context = (struct _EncodeContext *)callbackData;
   
   p_encode_context->size += size;
 
   return 0;
}

static int EncodePlaceCallback(
                   const char* data,
                   size_t size,
                   void* callbackData)
{
   struct _EncodeContext *p_encode_context = (struct _EncodeContext *)callbackData;
   

   memcpy(p_encode_context->pdata+p_encode_context->size, data, size);
   p_encode_context->size += size;
   return 0;
}


/* 
 *  Based on the authorisation type, we create an auth clause for the Http response header. 
 *  The response token is converted to base 64.  
 *
 *  An assumption is made that the protocol text values are single byte (UTF8).
 *
 */

static char *_BuildClientGssAuthHeader(_In_  struct _HttpClient_SR_SocketData *self, 
                                                gss_buffer_t token,
                                          _Out_ MI_Uint32 *pResultLen)

{   
   static const MI_Char AUTH_PREFIX_NEGOTIATE[] = ZT("Authorization: Negotiate ");
   static const MI_Char AUTH_PREFIX_KERBEROS[]  = ZT("Authorization: Kerberos ");

   const MI_Char *prefix = NULL;
   int  prefix_len = 0;

   struct _EncodeContext encode_context = {0};


    switch(self->authType) {
    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
        prefix     = AUTH_PREFIX_NEGOTIATE;
        prefix_len = MI_COUNT(AUTH_PREFIX_NEGOTIATE)-1; // Dont want to count the null
        break;

    case AUTH_METHOD_KERBEROS:
        prefix     = AUTH_PREFIX_KERBEROS;
        prefix_len = MI_COUNT(AUTH_PREFIX_KERBEROS)-1; // Dont want to count the null
        break;

    default:
        trace_Wsman_UnsupportedAuthentication("Unknown");
        return NULL;
    }

    encode_context.size    = 0;
    encode_context.pdata   = NULL;

    // Call once to estimate the size.
    int rslt = Base64Enc( token->value, token->length, EncodeSizeCallback, &encode_context);

       // Then we allocate the data  and add the extra

    encode_context.pdata = PAL_Malloc(encode_context.size+ prefix_len+1);
    encode_context.size  = prefix_len;

    memcpy(encode_context.pdata, prefix, prefix_len);

    // Call again to copy the data
    if (rslt >= 0) {
        rslt = Base64Enc( token->value, token->length, EncodePlaceCallback, &encode_context);
    }

    encode_context.pdata[encode_context.size] = '\0';

    if (pResultLen) {
       *pResultLen = encode_context.size;
    }
    return encode_context.pdata;
}


#if 0
static gss_buffer_t _getPrincipalName( gss_ctx_id_t pContext )

{
    // Now we have established context. All lines below are for getting source user name in form of username@DOMAIN.COM (I got it capitalized, yes)
    gss_name_t  srcName = NULL;
    //gss_name_t  targetName = NULL;
    OM_uint32   lifetime;
    OM_uint32   ctxFlags = 0;

    OM_uint32   maj_status;
    OM_uint32   min_status;
    gss_buffer_t buff = PAL_Malloc(sizeof(gss_buffer_desc));

    memset(buff, 0, sizeof(gss_buffer_desc));

    maj_status = gss_inquire_context(&min_status, pContext, &srcName, /*&targetName*/NULL, &lifetime, NULL, &ctxFlags, NULL, NULL);
    if (maj_status != GSS_S_COMPLETE)
    {
        // Complain
        goto Done;
    }
    
    if (srcName != NULL)
    { 
        maj_status = gss_display_name(&min_status, srcName, buff, NULL);
        if (maj_status != GSS_S_COMPLETE)
        {
            // Complain
            goto Done;
        }
        maj_status = gss_release_name(&min_status, &srcName);
    }
    else {
      fprintf(stderr, "srcName == NULL\n");
    }
    
Done: 

    return buff;
}

#endif 

static void _displayStatus(OM_uint32 status_code, int status_type)
{
    OM_uint32 message_context;
    OM_uint32 min_status;
    gss_buffer_desc status_string;

    message_context = 0;

    do {
        gss_display_status(
           &min_status,
           status_code,
           status_type,
           GSS_C_NO_OID,
           &message_context,
           &status_string);

        fprintf(stderr, "%.*s\n",
           (int)status_string.length,
           (char *)status_string.value);

        gss_release_buffer(&min_status, &status_string);

    } while (message_context != 0);
}

static void _ReportError(HttpClient_SR_SocketData* self, const char *msg, OM_uint32 major_status, OM_uint32 minor_status)
{
    _displayStatus(major_status, GSS_C_GSS_CODE);
    _displayStatus(minor_status, GSS_C_MECH_CODE);
}


static int _Base64DecCallback(
    const void* data,
    size_t length,
    void* callbackData)
{
    gss_buffer_t decoded_data = (gss_buffer_t)callbackData;
    const unsigned char* new_decoded_data = (const unsigned char*)data;
    
    memcpy(decoded_data->value + decoded_data->length, new_decoded_data, length);
    decoded_data->length += length;
    
    return 0;
}

/*
**==============================================================================
*/


/*
      Converts the SPNEGO authorization header string to an opaque gss token

*/

static int _getInputToken(const char* authorization, gss_buffer_t token)
{
        const char *spnegoToken = authorization + AUTHENTICATION_NEGOTIATE_LENGTH + 1;

        token->value = (unsigned char*)PAL_Malloc(strlen(spnegoToken));
        if (!token->value)
        {
            return -1;
        }
        memset(token->value, 0, strlen(spnegoToken));
        token->length = 0;

        int decodedSize = Base64Dec((const void *)spnegoToken, strlen(spnegoToken), _Base64DecCallback, token);

        if ( decodedSize <= 0 )
        {
            trace_Base64Dec_Failed();
            return -2;
        }
        return 0;
}



/* 
 *  Based on the authorisation type, we create an auth clause for the Http response header. 
 *  The response token is converted to base 64.  
 *
 *  An assumption is made that the protocol text values are single byte (UTF8).
 *
 */

static char *_BuildBasicAuthHeader( _In_ struct _HttpClient_SR_SocketData *self, MI_Uint32 *pStatus)

{   

    static const char AUTHORIZE_HEADER_BASIC[] =  "Authorization: Basic ";
    const MI_Uint32 AUTHORIZE_HEADER_BASIC_LEN = Strlen(AUTHORIZE_HEADER_BASIC);

    char *authUsernamePassword; /* <username>:<password> in ansi ready for base64-encoding */
    MI_Uint32 authUsernamePasswordLength;

    struct _EncodeContext encode_context = {0};

    /* Convert username and password into format needed for auth "<username>:<password>" as ANSI string */
    authUsernamePasswordLength = Strlen(self->username) + 1 /* : */ + Strlen(self->password);
    authUsernamePassword = (char*) PAL_Malloc(authUsernamePasswordLength + 1);
    if (authUsernamePassword == NULL)
    {
        *pStatus = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        return NULL;
    }
    Strlcpy(authUsernamePassword, self->username, authUsernamePasswordLength+1);
    Strlcat(authUsernamePassword, ":", authUsernamePasswordLength+1);
    Strlcat(authUsernamePassword, self->password, authUsernamePasswordLength+1);

    /* Now we need to base64 encode the username:password string. We may as well
     * put the result in the final buffer
     */

    encode_context.size    = 0;
    encode_context.pdata   = NULL;

    // Call once to estimate the size.
    if(Base64Enc( authUsernamePassword, authUsernamePasswordLength, EncodeSizeCallback, &encode_context) == -1)
    {
        PAL_Free(authUsernamePassword);
        *pStatus = MI_RESULT_FAILED;
        return NULL;
    }

    // Then we allocate the data  and add the extra

    encode_context.pdata = PAL_Malloc(encode_context.size+AUTHORIZE_HEADER_BASIC_LEN+1);

    Strlcpy(encode_context.pdata, AUTHORIZE_HEADER_BASIC, AUTHORIZE_HEADER_BASIC_LEN+1);
    encode_context.size = AUTHORIZE_HEADER_BASIC_LEN;

    // Call again to copy the data
    if(Base64Enc( authUsernamePassword, authUsernamePasswordLength, EncodePlaceCallback, &encode_context) == -1)
    {
        PAL_Free(authUsernamePassword);
        PAL_Free(encode_context.pdata);
        *pStatus = MI_RESULT_FAILED;
        return NULL;
    }

    encode_context.pdata[encode_context.size] = '\0';

    /* Free up extra memory and set out parameter. We are done. */
    PAL_Free(authUsernamePassword);
    return (char *)encode_context.pdata;
}




static char *_BuildInitialGssAuthHeader( _In_ HttpClient_SR_SocketData* self, MI_Uint32 *status )

{ 
   char *rslt = NULL;

   const gss_OID_desc mech_krb5   = { 9, "\052\206\110\206\367\022\001\002\002" };
   const gss_OID_desc mech_spnego = { 6, "\053\006\001\005\005\002" };
   const gss_OID_desc mech_iakerb = { 6, "\053\006\001\005\002\005" };
   const gss_OID_desc mech_ntlm   = {10, "\x2b\x06\x01\x04\x01\x82\x37\x02\x02\x0a" };
   // gss_OID_set_desc mechset_krb5 = { 1, &mech_krb5 };
   // gss_OID_set_desc mechset_iakerb = { 1, &mech_iakerb };
   const gss_OID_set_desc mechset_spnego = { 1, (gss_OID)&mech_spnego };

   const gss_OID_desc mechset_krb5_elems[] = { mech_krb5,
                                               mech_iakerb
                                             };

   const gss_OID_set_desc mechset_krb5   = { 2, (gss_OID)mechset_krb5_elems };

   // The list attached to the spnego token 

   const gss_OID_desc mechset_avail_elems[] = { 
                                                mech_ntlm, // For now we start with ntlm
                                                mech_krb5,
                                                mech_iakerb,
                                              };
   const gss_OID_set_desc mechset_avail    = { 3, (gss_OID)mechset_avail_elems };


   static const char WSMAN_PROTOCOL[] = "WSMAN/";

   OM_uint32 maj_stat, min_stat;

   const char   *protocol     = WSMAN_PROTOCOL;
   const MI_Uint32  protocol_len = MI_COUNT(WSMAN_PROTOCOL)-1; // The count includes a null

   gss_ctx_id_t context_hdl = GSS_C_NO_CONTEXT;
   gss_cred_id_t       cred = GSS_C_NO_CREDENTIAL;
   gss_name_t  gss_username = GSS_C_NO_NAME;
   gss_name_t  target_name  = GSS_C_NO_NAME;

   gss_buffer_desc output_token;
   gss_OID_set mechset = NULL;
   OM_uint32 ret_flags = 0;


   if (self->authContext) {

       // release any old context handle

       context_hdl = (gss_ctx_id_t)self->authContext;
       gss_delete_sec_context(&min_stat, &context_hdl, NULL);
       self->authContext = NULL;
   }

   switch(self->authType) {
   case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
   case AUTH_METHOD_NEGOTIATE:
       mechset    = (gss_OID_set)&mechset_spnego;
       break;

   case AUTH_METHOD_KERBEROS:
       mechset    = (gss_OID_set)&mechset_krb5;
       break;

   default:
       trace_Wsman_UnsupportedAuthentication("Unknown");
       return NULL;
   }

   // Get a credential, either with the username/passwd

   if (self->username != NULL)
   {
       gss_buffer_desc buf;

       buf.value  = self->username;
       buf.length = Strlen(self->username);

       maj_stat = gss_import_name(&min_stat, &buf, 
                                  GSS_C_NT_USER_NAME,
                                  &gss_username);

       if (maj_stat != GSS_S_COMPLETE) {
           _ReportError(self, "Could not import name ", maj_stat, min_stat);
           return NULL;
       }

       if (self->password != NULL)
       {

           buf.value  = self->password;
           buf.length = self->passwordLen;

           maj_stat = gss_acquire_cred_with_password(&min_stat,
                                                 gss_username,
                                                 &buf, 0,
                                                 mechset, GSS_C_INITIATE,
                                                 &cred, NULL, NULL);
           if (maj_stat != GSS_S_COMPLETE) 
           {
               _ReportError(self, "acquiring creds with password failed", maj_stat, min_stat);
               gss_release_name(&min_stat, &gss_username);
               return NULL;
           }
       } 
       else 
       {
           if (gss_username != GSS_C_NO_NAME)
           {
               maj_stat = gss_acquire_cred(&min_stat,
                                   gss_username, 0,
                                   mechset, GSS_C_INITIATE,
                                   &cred, NULL, NULL);
               if (maj_stat != GSS_S_COMPLETE) 
               {
                   _ReportError(self, "acquiring creds with username only failed", maj_stat, min_stat);
                   gss_release_name(&min_stat, &gss_username);
                   return NULL;
               }
           }
       }
   }
   else 
   {
       maj_stat = gss_acquire_cred(&min_stat,
                                   gss_username, 0,
                                   mechset, GSS_C_INITIATE,
                                   &cred, NULL, NULL);
       if (maj_stat != GSS_S_COMPLETE) 
       {
           _ReportError(self, "acquiring anonymous creds failed", maj_stat, min_stat);
           gss_release_name(&min_stat, &gss_username);
           return NULL;
       }
   }

   if ((self->authType == AUTH_METHOD_NEGOTIATE) ||
       (self->authType == AUTH_METHOD_NEGOTIATE_WITH_CREDS)) {

       // Add the list of available mechs to the credential 

       maj_stat = gss_set_neg_mechs(&min_stat, cred, (const gss_OID_set )&mechset_avail);
       if (maj_stat != GSS_S_COMPLETE) {
           _ReportError(self, "setting neg mechs", maj_stat, min_stat);
           gss_release_name(&min_stat, &gss_username);
           gss_release_cred(&min_stat, &cred);
           return NULL;
       }
   }

   gss_release_name(&min_stat, &gss_username);


   // Figure out the target name
   

   { // Start with the fdqn
        gss_buffer_desc buff = {0};

        struct addrinfo hints, *info;
        int gai_result;
        
        char hostname[1024];
        hostname[1023] = '\0';

        gethostname(hostname, 1023);
        
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC; /*either IPV4 or IPV6*/
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_CANONNAME;
        
        if ((gai_result = getaddrinfo(hostname, "http", &hints, &info)) != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_result));
            exit(1);
        }
        
        /*
        for(p = info; p != NULL; p = p->ai_next) {
            printf("hostname: %s\n", p->ai_canonname);
        }
        */

        // 2DO: Pay attention to character size and convert if necessary

        buff.length = protocol_len+strlen(info->ai_canonname);
        buff.value  = PAL_Malloc(buff.length+1);
        memcpy(buff.value, protocol, protocol_len);
        memcpy(((MI_Char*)buff.value)+protocol_len, info->ai_canonname, strlen(info->ai_canonname));

        ((MI_Char*)buff.value)[buff.length] = 0;  // converts to 8 or 16 bit char
        
        // 2DO: If we dont have an fdqn we will use the addr
        
        freeaddrinfo(info);

        maj_stat = gss_import_name(&min_stat, &buff,
                                   (gss_OID) gss_nt_service_name,
                                   &target_name);
        if (maj_stat != GSS_S_COMPLETE) {
            _ReportError(self, "parsing name", maj_stat, min_stat);
            goto Done;
        }
    }

    maj_stat = gss_init_sec_context (
                 &min_stat,
                 cred,
                 &context_hdl,
                 target_name,
                 mechset->elements,
                 0,                // flags
                 0,                // time_req,
                 GSS_C_NO_CHANNEL_BINDINGS,   // input_chan_bindings,
                 GSS_C_NO_BUFFER,
                 NULL,
                 &output_token,
                 &ret_flags,
                 0);               // time_req

    if (maj_stat == GSS_S_CONTINUE_NEEDED) 
    {
        MI_Uint32 header_len = 0;

        // Expected

        *status = GSS_S_CONTINUE_NEEDED;
        
        rslt = _BuildClientGssAuthHeader(self, &output_token, &header_len);

        self->authContext = context_hdl;
        self->targetName  = target_name;
        self->authorizing = TRUE;
        self->cred = (void*)cred;
    }
    else if (maj_stat == GSS_S_COMPLETE)
    {
        // Unexpected here

        *status = GSS_S_COMPLETE;
    }
    else 
    {
        // Unexpected here
    }


Done:
    return rslt;
}




Http_CallbackResult HttpClient_RequestAuthorization( _In_ struct _HttpClient_SR_SocketData *self, const char **pAuthHeader )

{ MI_Uint32 status = 0;

    // Create and send the auth header
    // The client side of the authorisation dance.

    // We do the gss_init_sec_context, rinse and repeat 

    switch(self->authType)
    {
    case AUTH_METHOD_BASIC:

 
        self->authorizing = TRUE;

        if (pAuthHeader) {
            *pAuthHeader = _BuildBasicAuthHeader(self, &status);
        }
 
        // And that should do it.

        return PRT_CONTINUE;

    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
    case AUTH_METHOD_KERBEROS:
        if (pAuthHeader) {
            *pAuthHeader = _BuildInitialGssAuthHeader(self, &status);
            if (!*pAuthHeader ) {

                // We cant even get out of the starting gate. This would be because we dont have either mechs or creds

                return PRT_RETURN_FALSE;
            }

        }

        return PRT_CONTINUE;

    default:
        return PRT_RETURN_FALSE;
    }
}







Http_CallbackResult HttpClient_IsAuthorized( _In_ struct _HttpClient_SR_SocketData *self )

{
    static const char AUTHENTICATE[] = "WWW-Authenticate"; 
    static const MI_Uint32 AUTHENTICATE_LEN = MI_COUNT(AUTHENTICATE);

    //HttpClient* client = (HttpClient*)self->base.data;
    HttpClientResponseHeader  *pheaders = &self->recvHeaders;
    //Http_CallbackResult r;
    char *auth_header = NULL;
   
    for (int i = 0; i < pheaders->sizeHeaders; i++ )
    {
        if (Strncasecmp(pheaders->headers[i].name, AUTHENTICATE, AUTHENTICATE_LEN) == 0) {
            auth_header = (char*)pheaders->headers[i].value;
            break;
        }

    }

    switch (self->authType ) {
    case AUTH_METHOD_BASIC:

        // If the auth failed, we get a list of available auth methods. They will show up as WWW-Authenticate 
        // but no data after the method

        if (!auth_header)
        {
            switch(pheaders->httpError)
            {
            case HTTP_ERROR_CODE_BAD_REQUEST:
            case HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR:
            case HTTP_ERROR_CODE_OK:
            case HTTP_ERROR_CODE_NOT_SUPPORTED:

                // We authorise broken error codes because of the possibility of 
                // error content, eg post mortem dump info

                self->authorizing  = FALSE;
                self->isAuthorized = TRUE;
                return PRT_CONTINUE;

            case HTTP_ERROR_CODE_UNAUTHORIZED:
            case 409: // proxy unauthorised
            default:

                self->authorizing  = FALSE;
                self->isAuthorized = FALSE;
                return PRT_RETURN_FALSE;
            }
        }
        else 
        {
             
        }

        return PRT_CONTINUE;

    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
    case AUTH_METHOD_KERBEROS:

        if (!auth_header) 
        {
            switch(pheaders->httpError)
            {
            case HTTP_ERROR_CODE_BAD_REQUEST:
            case HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR:
            case HTTP_ERROR_CODE_OK:
            case HTTP_ERROR_CODE_NOT_SUPPORTED:

                // We authorise broken error codes because of the possibility of 
                // error content, eg post mortem dump info

                self->authorizing  = FALSE;
                self->isAuthorized = TRUE;
                return PRT_CONTINUE;

            case HTTP_ERROR_CODE_UNAUTHORIZED:
            case 409: // proxy unauthorised
            default:

                self->authorizing  = FALSE;
                self->isAuthorized = FALSE;
                return PRT_RETURN_FALSE;
            }
        }
        else 
        {
            const gss_OID_desc mech_krb5   = { 9, "\052\206\110\206\367\022\001\002\002" };
            const gss_OID_desc mech_spnego = { 6, "\053\006\001\005\005\002" };
            const gss_OID_desc mech_iakerb = { 6, "\053\006\001\005\002\005" };
            // const gss_OID_desc mech_ntlm   = {10, "\x2b\x06\x01\x04\x01\x82\x37\x02\x02\x0a" };
            // gss_OID_set_desc mechset_krb5 = { 1, &mech_krb5 };
            // gss_OID_set_desc mechset_iakerb = { 1, &mech_iakerb };
            const gss_OID_set_desc mechset_spnego = { 1, (gss_OID)&mech_spnego };

            const gss_OID_desc mechset_krb5_elems[] = { mech_krb5,
                                                        mech_iakerb
                                                      };

            const gss_OID_set_desc mechset_krb5   = { 2, (gss_OID)mechset_krb5_elems };

            OM_uint32 maj_stat, min_stat;
            gss_ctx_id_t context_hdl = GSS_C_NO_CONTEXT;
            gss_buffer_desc input_token, output_token;
            gss_OID_set mechset = NULL;
            OM_uint32 ret_flags = 0;
            gss_name_t target_name = (gss_name_t)self->targetName;
            gss_cred_id_t     cred = (gss_cred_id_t)self->cred;

            switch(self->authType) {
            case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
            case AUTH_METHOD_NEGOTIATE:
                mechset    = (gss_OID_set)&mechset_spnego;
                break;

            case AUTH_METHOD_KERBEROS:
                mechset    = (gss_OID_set)&mechset_krb5;
                break;

            default:
                // Cant get here except by corruption
                break;
            }
 
            if (self->authContext) {
                context_hdl = (gss_ctx_id_t)self->authContext;
            }

            // If this is a mutual auth in progress, generate new request 

            self->authorizing  = TRUE;
            self->isAuthorized = FALSE;

            if (_getInputToken(auth_header, &input_token) != 0)
            {
                self->authorizing  = FALSE;
                self->isAuthorized = FALSE;
                return PRT_CONTINUE;
            }

            // (void)DecodeToken(&input_token);
            maj_stat = gss_init_sec_context(&min_stat,
                                            cred, 
                                            &context_hdl,
                                            target_name,
                                            mechset->elements,
                                            0,                // flags
                                            0,                // time_req,
                                            GSS_C_NO_CHANNEL_BINDINGS,   // input_chan_bindings,
                                            &input_token, 
                                            NULL, /* mech type */
                                            &output_token, 
                                            &ret_flags,
                                            NULL);  /* time_rec */

            PAL_Free(input_token.value);

            if ((maj_stat == GSS_S_CONTINUE_NEEDED) ||
               (maj_stat == GSS_S_COMPLETE))
            {
                Http_CallbackResult r;
                Page *data = self->data;
                MI_Uint32 header_len = 0;
                char *auth_header =  _BuildClientGssAuthHeader(self, &output_token, &header_len);

                /* create header page */
                self->sendHeader =
                    _CreateHttpHeader(self->verb, self->uri, self->contentType, auth_header, data ? data->u.s.size : 0); 
                if (data != NULL)
                {
                    self->sendPage = data;
                    self->data = 0;
                }
                else
                    self->sendPage = NULL;

                /* set status to failed, until we know more details */
 
                self->status = MI_RESULT_FAILED;
                self->sentSize = 0;
                self->sendingState = RECV_STATE_HEADER;
                self->base.mask |= SELECTOR_WRITE;

                r = _WriteClientHeader(self);
                while (PRT_CONTINUE == r && self->sendPage) {

                    // If there is data to be sent, loop WriteClientData until it 
                    // says true or false. Continue means there was an E_WOULD_BLOCK

                    r = _WriteClientData(self);
                }

                if (auth_header) {
                    PAL_Free(auth_header);
                }

                // Then we are Successful. If the 
                if (maj_stat == GSS_S_COMPLETE)
                {
                    self->authorizing  = FALSE;
                    self->isAuthorized = TRUE;
                    return PRT_RETURN_TRUE;
                }
                else 
                {
                    return PRT_RETURN_TRUE;
                }
            }
            else {
                // Handle errors
            }
        }
        return PRT_RETURN_FALSE;


#ifdef NOTYET
                    if (token_ptr != GSS_C_NO_BUFFER)
                        free(recv_tok.value);
        
                    if (output_token.length != 0) {
                        if (verbose)
                            printf("Sending init_sec_context token (size=%d)...",
                                   (int) send_tok.length);
                        if ((s, v1_format ? 0 : TOKEN_CONTEXT, &send_tok) <
                            0) {
                            (void) gss_release_buffer(&min_stat, &send_tok);
                            (void) gss_release_name(&min_stat, &target_name);
                            return -1;
                        }
                    }
                    (void) gss_release_buffer(&min_stat, &output_token);
        
                    if (maj_stat != GSS_S_COMPLETE
                        && maj_stat != GSS_S_CONTINUE_NEEDED) {
                        display_status("initializing context", maj_stat,
                                       init_sec_min_stat);
                        (void) gss_release_name(&min_stat, &target_name);
                        if (*gss_context != GSS_C_NO_CONTEXT)
                            gss_delete_sec_context(&min_stat, gss_context,
                                                   GSS_C_NO_BUFFER);
                        return -1;
                    }
        
                    if (maj_stat == GSS_S_CONTINUE_NEEDED) {
                        if (verbose)
                            printf("continue needed...");
                        if (recv_token(s, &token_flags, &recv_tok) < 0) {
                            (void) gss_release_name(&min_stat, &target_name);
                            return -1;
                        }
                        token_ptr = &recv_tok;
                    }
                    if (verbose)
                        printf("\n");
                    return PRT_RETURN_FALSE;
                }
            }
            
            return PRT_RETURN_FALSE;
        }
#endif

    default:
         return PRT_CONTINUE;

    }
}
