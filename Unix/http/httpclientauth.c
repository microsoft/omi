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
#define FORCE_TRACING 

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
        maj_status = gss_display_name(&min_status, srcName, buff, &GSS_C_NT_USER_NAME);
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

static void _ReportError(HttpClient_SR_SocketData*self, const char *msg, OM_uint32 major_status, OM_uint32 minor_status)
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

static void _SendAuthRequest(HttpClient_SR_SocketData* sendSock, const unsigned char *pResponse, int responseLen )

{
}

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
   Convert the gss_buffer_t token to a WWW-Authorization string suitable for the http response header
 */

struct _EncodeContext {
    int size;
    MI_Char *pdata;
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
   

   memcpy(p_encode_context->pdata+p_encode_context->size, data, size*sizeof(MI_Char));
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

static unsigned char *_BuildBasicAuthHeader( _In_ struct _HttpClient_SR_SocketData *self)

{   
#define AUTHORIZE_HEADER_BASIC "Authorization: Basic "

    static const MI_Uint32  AUTHORIZE_HEADER_BASIC_LEN = strlen(AUTHORIZE_HEADER_BASIC);

    char *authUsernamePassword; /* <username>:<password> in ansi ready for base64-encoding */
    MI_Uint32 authUsernamePasswordLength;

    struct _EncodeContext encode_context = {0};

    /* Convert username and password into format needed for auth "<username>:<password>" as ANSI string */
    authUsernamePasswordLength = Tcslen(self->username) + 1 /* : */ + Tcslen(self->password);
    authUsernamePassword = (char*) PAL_Malloc(authUsernamePasswordLength + 1);
    if (authUsernamePassword == NULL)
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    StrTcslcpy(authUsernamePassword, self->username, authUsernamePasswordLength+1);
    Strlcat(authUsernamePassword, ":", authUsernamePasswordLength+1);
    StrTcslcat(authUsernamePassword, self->password, authUsernamePasswordLength+1);

    /* Now we need to base64 encode the username:password string. We may as well
     * put the result in the final buffer
     */

    encode_context.size    = 0;
    encode_context.pdata   = NULL;

    // Call once to estimate the size.
    if(Base64Enc( authUsernamePassword, authUsernamePasswordLength, EncodeSizeCallback, &encode_context) == -1)
    {
        PAL_Free(authUsernamePassword);
        return MI_RESULT_FAILED;
    }

    // Then we allocate the data  and add the extra

    encode_context.pdata = PAL_Malloc( (encode_context.size+AUTHORIZE_HEADER_BASIC_LEN+1)*sizeof(MI_Char));

    StrTcslcpy(encode_context.pdata, AUTHORIZE_HEADER_BASIC, AUTHORIZE_HEADER_BASIC_LEN+1);
    encode_context.size = AUTHORIZE_HEADER_BASIC_LEN;

    // Call again to copy the data
    if(Base64Enc( authUsernamePassword, authUsernamePasswordLength, EncodePlaceCallback, &encode_context) == -1)
    {
        PAL_Free(authUsernamePassword);
        PAL_Free(encode_context.pdata);
        return MI_RESULT_FAILED;
    }

    encode_context.pdata[encode_context.size] = '\0';

    /* Free up extra memory and set out parameter. We are done. */
    PAL_Free(authUsernamePassword);
    return encode_context.pdata;
}



static MI_Char *_BuildInitialGssAuthHeader( _In_ HttpClient_SR_SocketData* self)

{ 
  MI_Boolean authorised = FALSE;

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

        const gss_OID_desc mechset_avail_elems[] = { mech_krb5,
                                                     mech_iakerb,
                                                     mech_ntlm
                                                   };
        const gss_OID_set_desc mechset_avail    = { 3, (gss_OID)mechset_avail_elems };

        OM_uint32 maj_stat, min_stat;
        gss_ctx_id_t context_hdl = GSS_C_NO_CONTEXT;
        gss_cred_id_t       cred = GSS_C_NO_CREDENTIAL;
        gss_name_t  gss_username = GSS_C_NO_NAME;

        gss_buffer_desc input_token, output_token;
        gss_OID_set mechset = NULL;
 
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
            buf.length = strlen(self->username);

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
                if (maj_stat != GSS_C_CONTINUE) 
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
                    if (maj_stat != GSS_C_CONTINUE) 
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
            if (maj_stat != GSS_C_CONTINUE) 
            {
                _ReportError(self, "acquiring anonymous creds failed", maj_stat, min_stat);
                gss_release_name(&min_stat, &gss_username);
                return NULL;
            }
        }

        if ((self->authType == AUTH_METHOD_NEGOTIATE) ||
            (self->authType == AUTH_METHOD_NEGOTIATE_WITH_CREDS)) {

            // Add the list of available mechs to the credential 

            maj_stat = gss_set_neg_mechs(&min_stat, cred, &mechset_avail);
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
             struct addrinfo hints, *info, *p;
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
             
             for(p = info; p != NULL; p = p->ai_next) {
                 printf("hostname: %s\n", p->ai_canonname);
             }
             
             freeaddrinfo(info);

             // If we dont have an fdqn we will use the addr

         }

       
#if 0
        if (handler->httpErrorCode == 0) {
           #if 0
            gss_OID_desc pref_oids[2];
            gss_OID_set_desc pref_mechs;

     
            /* Make the initiator prefer IAKERB and offer krb5 as an alternative. */
    
            pref_oids[0] = mech_iakerb;
            pref_oids[1] = mech_krb5;
            pref_mechs.count = 2;
            pref_mechs.elements = pref_oids;
           #endif
            gss_cred_id_t verifier_cred_handle = GSS_C_NO_CREDENTIAL;
            gss_OID_set actual_mechs = GSS_C_NO_OID_SET;
            /* Get acceptor cred for principal. */
            maj_stat = gss_acquire_cred(&min_stat, GSS_C_NO_NAME, GSS_C_INDEFINITE,
                                     mechset, GSS_C_ACCEPT,
                                     &verifier_cred_handle, &actual_mechs, NULL); // Name needs to not be null?
            if (_check_gsserr("gss_acquire_cred(acceptor)", maj_stat, min_stat)) {
                handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
                auth_response = (unsigned char *)RESPONSE_HEADER_UNAUTH_FMT;
                response_len  = strlen(RESPONSE_HEADER_UNAUTH_FMT);

                // Problem : 2do complain
                handler->authFailed = TRUE;

                _SendAuthResponse(handler, auth_response, response_len);  
                return FALSE; 
            }
        }

        maj_stat = gss_accept_sec_context(
              &min_stat,           // ok
              &context_hdl,        // ok
              GSS_C_NO_CREDENTIAL, // acceptor_cred_handle
              &input_token,        // Base64 decoded the SPNEGO token
              GSS_C_NO_CHANNEL_BINDINGS, //input_channel_bindings (more security?)
              NULL,                      // client_name / src_name
              NULL,                      // mech_type optional Security mechanism used
              &output_token,        // ok
              NULL, //&flags,               // Unsure 
              NULL,                 // time_rec number of seconds for which the context will remain valid
              NULL);                // deleg_cred

        handler->pAuthContext = context_hdl;
          
        PAL_Free(input_token.value);

        if (maj_stat == GSS_S_COMPLETE)
        {
            /* We are authorised */
            gss_buffer_t user_name = _getPrincipalName( context_hdl );

            if (0 != LookupUser(user_name->value, &handler->authInfo.uid, &handler->authInfo.gid))
            {

                // After all that, it would be weird for this to fail, but it is possible
                // on a misconfigured system. either way, if its not there its not there.

                trace_GetUserUidGid_Failed(headers->username);

                handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED; 
                handler->authFailed = TRUE;
                auth_response = (unsigned char *)RESPONSE_HEADER_UNAUTH_FMT;
                response_len  = strlen(RESPONSE_HEADER_UNAUTH_FMT);

                _SendAuthResponse(handler, auth_response, response_len);  
                gss_delete_sec_context(&min_stat, &context_hdl, NULL);

                handler->pAuthContext = NULL;
                handler->authFailed   = TRUE;

                gss_release_buffer(&min_stat, user_name);
                PAL_Free(user_name);

                goto Done;
            }
    
            gss_release_buffer(&min_stat, user_name);

            PAL_Free(user_name);

            handler->httpErrorCode = 0;  // We let the transaction set the error code
            handler->isAuthorised = TRUE;
            return TRUE;

        }
        else if (GSS_ERROR(maj_stat))
        {
            _report_error(maj_stat, min_stat);

            if (GSS_ERROR(maj_stat) == GSS_S_NO_CRED ||
                GSS_ERROR(maj_stat) == GSS_S_FAILURE ||
                GSS_ERROR(maj_stat) == GSS_S_UNAUTHORIZED)
            {

                // Unauthorised

                handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
                auth_response = (unsigned char *)RESPONSE_HEADER_UNAUTH_FMT;
                response_len  = strlen(RESPONSE_HEADER_UNAUTH_FMT);

                // Problem : 2do complain
                handler->authFailed = TRUE;

            }
            else
            {
                handler->httpErrorCode = HTTP_ERROR_CODE_BAD_REQUEST; 
                auth_response = (unsigned char *)RESPONSE_HEADER_BAD_REQUEST;
                response_len  = strlen(RESPONSE_HEADER_BAD_REQUEST);
            }

            _SendAuthResponse(handler, auth_response, response_len);  
            gss_release_buffer(&min_stat, &output_token);
            return FALSE; 
        }
        else if (maj_stat & GSS_S_CONTINUE_NEEDED) {
            handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
            if (output_token.length != 0)
            {
                auth_response = _BuildAuthResponse(protocol_p, handler->httpErrorCode, &output_token, &response_len);
                if ( auth_response == NULL ) {

                    // Problem : 2do complain into trace file
                    handler->httpErrorCode = HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR;
                        }
                gss_release_buffer(&min_stat, &output_token);

                _SendAuthResponse(handler, auth_response, response_len);  
                PAL_Free(auth_response);
                return FALSE; 

            }
            else {
                 
                gss_buffer_t user_name = _getPrincipalName( context_hdl );

                if (0 != LookupUser(user_name->value, &handler->authInfo.uid, &handler->authInfo.gid))
                {

                    // After all that, it would be weird for this to fail, but it is possible
                    // on a misconfigured system. either way, if its not there its not there.

                    trace_GetUserUidGid_Failed(headers->username);

                    handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED; 
                    handler->authFailed = TRUE;
                    auth_response = (unsigned char *)RESPONSE_HEADER_UNAUTH_FMT;
                    response_len  = strlen(RESPONSE_HEADER_UNAUTH_FMT);

                    _SendAuthResponse(handler, auth_response, response_len);  
                    gss_delete_sec_context(&min_stat, &context_hdl, NULL);

                    handler->pAuthContext = NULL;
                    handler->authFailed   = TRUE;

                    gss_release_buffer(&min_stat, user_name);
                    goto Done;
                }
        
                gss_release_buffer(&min_stat, user_name);

                handler->httpErrorCode = 0;  // We let the transaction set the error code
                handler->isAuthorised = TRUE;
                return TRUE;
            }
        }
    }

#endif
Done:
    return authorised;
}




Http_CallbackResult HttpClient_RequestAuthorization( _In_ struct _HttpClient_SR_SocketData *self, const MI_Char **pAuthHeader )

{

    // Create and send the auth header
    // The client side of the authorisation dance.

    // We do the gss_init_sec_context, rinse and repeat 

    switch(self->authType)
    {
    case AUTH_METHOD_BASIC:
 
        self->authorizing = TRUE;

        if (pAuthHeader) {
            *pAuthHeader = _BuildBasicAuthHeader(self);
        }
 
        // And that should do it.

        return PRT_RETURN_TRUE;

    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
    case AUTH_METHOD_KERBEROS:
        if (pAuthHeader) {
            *pAuthHeader = _BuildInitialGssAuthHeader(self);
            if (!*pAuthHeader) {

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
    HttpClient* client = (HttpClient*)self->base.data;
    HttpClientResponseHeader  *pheaders = &self->recvHeaders;
    Http_CallbackResult r;
   

    switch (self->authType ) {
    case AUTH_METHOD_BASIC:
        return PRT_CONTINUE;

    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
    case AUTH_METHOD_KERBEROS:

        switch(pheaders->httpError) {
        case 500:
        case 200:
        default:
            self->authorizing  = FALSE;
            self->isAuthorized = TRUE;
            return PRT_CONTINUE;

        case 400:
        case 401:
        case 409: {

                OM_uint32 maj_stat, min_stat;
                gss_ctx_id_t context_hdl = GSS_C_NO_CONTEXT;
                gss_buffer_desc input_token, output_token;
                gss_OID_set mechset = NULL;
     
                if (self->authContext) {
                    context_hdl = (gss_ctx_id_t)self->authContext;
                }

                // If this is a mutual auth in progress, generate new request 

                self->authorizing  = TRUE;
                self->isAuthorized = FALSE;

                if (_getInputToken(pheaders, &input_token) != 0)
                {
                    self->authorizing  = FALSE;
                    self->isAuthorized = FALSE;
                    return PRT_CONTINUE;
                }
                else 
                {
#ifdef NOTYET
                    maj_stat = gss_init_sec_context(&min_stat,
                                                    cred, context_hdl,
                                                    target_name, mechset.elements,
                                                    gss_flags, 0,
                                                    NULL, /* channel bindings */
                                                    token_ptr, NULL, /* mech type */
                                                    &output_token, ret_flags,
                                                    NULL);  /* time_rec */
        
                    if (maj_stat == GSS_S_COMPLETE) {
                         
                        // Then we are Successful. 

                         
                    }
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
#endif
                    return PRT_RETURN_FALSE;
                }
            }
            
            return PRT_RETURN_FALSE;
        }


    default:
         return PRT_CONTINUE;

    }
}
