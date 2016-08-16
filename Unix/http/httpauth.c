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
#include "httpcommon.h"
#include "http_private.h"

#define FORCE_TRACING 1


//static gss_OID_desc gss_c_nt_user_name = {10, (void *)"\x2a\x86\x48\x86\xf7\x12\x01\x02\x01\x01"}; 
//gss_OID      GSS_C_NT_USER_NAME = &gss_c_nt_user_name;

#define HTTP_LONGEST_ERROR_DESCRIPTION 50
void _WriteTraceFile(PathID id, const void* data, size_t size);



static MI_Boolean _WriteAuthResponse( Http_SR_SocketData* handler, const unsigned char *pResponse, int responseLen)
{

/*    "SOAPAction: http://schemas.xmlsoap.org/ws/2004/08/addressing/fault\r\n"\ */

    size_t sent, total_sent;
    total_sent = 0;

    if (!pResponse) {
        return FALSE;
    }

    do {
        sent = 0;
        sent = SSL_write(handler->ssl, pResponse, responseLen);

        if ( sent == 0 ) 
        {
           // Connection is closed

           return FALSE;
        
        }
        else if (sent < 0) {
            switch (SSL_get_error(handler->ssl, sent))
            {

            // These do not happen. We havfe already drained the socket
            // before we got here. 

            case SSL_ERROR_WANT_WRITE:
                trace_SSLWrite_UnexpectedSysError(SSL_ERROR_WANT_WRITE);
                return FALSE;

            case SSL_ERROR_WANT_READ:
                trace_SSLWrite_UnexpectedSysError(SSL_ERROR_WANT_READ);
                return FALSE;

            // This would happen routinely
            case SSL_ERROR_SYSCALL:
                if (EAGAIN == errno ||
                    EWOULDBLOCK == errno ||
                    EINPROGRESS == errno)

                    // If e_would_block we just retry in the loop.

                    break;

                trace_SSLWrite_UnexpectedSysError(errno);
                return FALSE;

            default:
                break;
            }
        }

        total_sent += sent;

    } while(total_sent < responseLen);

    if (FORCE_TRACING || ((total_sent > 0) && handler->enableTracing))
    {
        _WriteTraceFile(ID_HTTPSENDTRACEFILE, pResponse, total_sent);
    }

    // if (handler->sentSize < buf_size)
    //     return PRT_RETURN_TRUE;

    // handler->sendingState = RECV_STATE_CONTENT;


    return TRUE;
}




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

static void _report_error(OM_uint32 major_status, OM_uint32 minor_status)
{
    _displayStatus(major_status, GSS_C_GSS_CODE);
    _displayStatus(minor_status, GSS_C_MECH_CODE);
}


static int _check_gsserr(const char* msg, OM_uint32 major_status, OM_uint32 minor_status)
{
    if (GSS_ERROR(major_status))
    {
        fprintf(stderr, "%s\n", msg);
        _report_error(major_status, minor_status);
        return 1;
    }
    return 0;
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

static void _SendAuthResponse(Http_SR_SocketData* sendSock, const unsigned char *pResponse, int responseLen )

{
    DEBUG_ASSERT( sendSock );

    /* validate handler */

    sendSock->handler.mask |= SELECTOR_WRITE;
    sendSock->handler.mask &= ~SELECTOR_READ;

    sendSock->sentSize = 0;
    sendSock->sendingState = RECV_STATE_HEADER;

    if( !_WriteAuthResponse(sendSock, pResponse, responseLen) )
    {
        trace_SendIN_IO_thread_HttpSocket_WriteFailed();
    }


    // Probably not going to happen, but anything sent after
    // an auth header is ignored.
    if (sendSock->sendPage)
    {
        PAL_Free(sendSock->sendPage);
        sendSock->sendPage = 0;
    }

    if (sendSock->recvPage)
    {
        PAL_Free(sendSock->recvPage);
        sendSock->sendPage = 0;
    }

    // Force it into read state so we can get the next header
    sendSock->handler.mask &= ~SELECTOR_WRITE;
    sendSock->handler.mask |= SELECTOR_READ;

    
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
    unsigned char *pdata;
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

static unsigned char *_BuildAuthResponse( _In_ const char *pProtocol, const int httpStatus, const gss_buffer_t token, _Out_ int *pResultLen)
{   

   static const char *HEADER_SERVER_ERROR = "HTTP/1.1 500 Internal Server Error\r\n" \
                                            "\r\nContent-Length: 0\r\n"\
                                            "\r\n";

   static const char *HEADER_UNAUTHORIZED = "HTTP/1.1 401 Unauthorized\r\n" \
                                            "\r\nContent-Length: 0\r\n"\
                                            "\r\n";

   static const char *HEADER_START_NEGO = "HTTP/1.1 401 Unauthorized\r\n" \
                                     "WWW-Authenticate: ";

   static const char *HEADER_START_SUCCESS = "HTTP/1.1 200 Success\r\n" \
                                     "WWW-Authenticate: ";
   
   static const char *HEADER_TAIL = "\r\nContent-Length: 0\r\n"\
                                    "\r\n";
 
   //const int HEADER_START_SUCCESS_LEN = strlen(HEADER_START_SUCCESS);
   //const int HEADER_START_NEGO_LEN = strlen(HEADER_START_NEGO);
   const int HEADER_TAIL_LEN  = strlen(HEADER_TAIL);

   // This may in future say Nego, Kerberos, or Ntlm

   int protocol_len = strlen(pProtocol);

   const char *header_start = NULL;
   int header_start_len = 0;

   struct _EncodeContext encode_context = {0};


   switch(httpStatus) {
   case HTTP_ERROR_CODE_OK:
       header_start = HEADER_START_SUCCESS;
       header_start_len = strlen(HEADER_START_SUCCESS);
       break;

   case HTTP_ERROR_CODE_UNAUTHORIZED:
       header_start = HEADER_START_NEGO;
       header_start_len = strlen(HEADER_START_NEGO);
       break;

   default:
   case HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR:
       {
           *pResultLen = strlen(HEADER_SERVER_ERROR);

           unsigned char *pdata = PAL_Malloc(*pResultLen+1);
           memcpy(pdata, HEADER_SERVER_ERROR, *pResultLen);
           pdata[*pResultLen] = '\0';
          
           return pdata;
       }
       break;
   }

   encode_context.size    = 0;
   encode_context.pdata   = NULL;

   if (!token)
   {
       encode_context.size = strlen(HEADER_UNAUTHORIZED);
       encode_context.pdata = PAL_Malloc(*pResultLen+1);
       memcpy(encode_context.pdata, HEADER_SERVER_ERROR, encode_context.size);
       encode_context.pdata[encode_context.size] = '\0';
   }
   else {
       // Call once to estimate the size.
       int rslt = Base64Enc( token->value, token->length, EncodeSizeCallback, &encode_context);

       // Then we allocate the data  and add the extra

       encode_context.pdata = PAL_Malloc(encode_context.size+  // The encoded data size
                                     header_start_len+     // 
                                     protocol_len+1+       // eg, "Negotiate" plus a space to separate it from the auth token
                                     HEADER_TAIL_LEN
                                     +1);                  // NULL

       memcpy(encode_context.pdata, header_start, header_start_len);
       memcpy(encode_context.pdata+header_start_len, pProtocol, protocol_len);
       memcpy(encode_context.pdata+header_start_len+protocol_len, " ", 1);

       encode_context.size  = header_start_len+protocol_len+1;
   
       // Call again to copy the data
       if (rslt >= 0) {
           rslt = Base64Enc( token->value, token->length, EncodePlaceCallback, &encode_context);
       }

       memcpy(encode_context.pdata+encode_context.size, HEADER_TAIL, HEADER_TAIL_LEN);
       encode_context.size += HEADER_TAIL_LEN;
       encode_context.pdata[encode_context.size] = '\0';

   }

   if (pResultLen) {
       *pResultLen = encode_context.size;
   }
   return encode_context.pdata;
}


int BuildInitalAuthResponse(Http_SR_SocketData* handler)
{
   // 2Do. 
   return -1;
}



MI_Boolean IsClientAuthorized( _In_ Http_SR_SocketData* handler)

{ 
  MI_Boolean authorised = FALSE;
  HttpHeaders* headers = &handler->recvHeaders;
  static const char *RESPONSE_HEADER_UNAUTH_FMT = "HTTP/1.1 401 Unauthorized\r\n" \
                                                  "Content-Length: 0\r\n"\
                                                  "\r\n";

  static const char *RESPONSE_HEADER_BAD_REQUEST = "HTTP/1.1 400 Bad Request\r\n" \
                                                  "Content-Length: 0\r\n"\
                                                  "\r\n";

  const char *protocol_p = NULL;
  unsigned char *auth_response = NULL;
  int            response_len  = 0;

    if (!headers) {
        handler->httpErrorCode = HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR;
        goto Done;
    }

    if(Strncasecmp(headers->authorization, AUTHENTICATION_BASIC, AUTHENTICATION_BASIC_LENGTH) == 0)
    {
        if (!headers->username || !headers->password ||
            0 != AuthenticateUser(headers->username, headers->password))
        {
            handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED; 
            handler->authFailed = TRUE;

            _SendAuthResponse(handler, auth_response, response_len);  
            return FALSE; 
        }

        if (0 != LookupUser(headers->username, &handler->authInfo.uid, &handler->authInfo.gid))
        {
            trace_GetUserUidGid_Failed(headers->username);

            handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED; 
            handler->authFailed = TRUE;
            _SendAuthResponse(handler, auth_response, response_len);  
            return FALSE; 
        }
        
        handler->httpErrorCode = 0; // Let the request do the error code
        handler->isAuthorised = TRUE;
        return TRUE;
    }
    else 
    {
        const gss_OID_desc mech_krb5   = { 9, "\052\206\110\206\367\022\001\002\002" };
        const gss_OID_desc mech_spnego = { 6, "\053\006\001\005\005\002" };
        const gss_OID_desc mech_iakerb = { 6, "\053\006\001\005\002\005" };
        //const gss_OID_desc mech_ntlm   = {10, "\x2b\x06\x01\x04\x01\x82\x37\x02\x02\x0a" };
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
 
        if (handler->pAuthContext) {
            context_hdl = (gss_ctx_id_t)handler->pAuthContext;
        }

        if (Strncasecmp(headers->authorization, AUTHENTICATION_NEGOTIATE, AUTHENTICATION_NEGOTIATE_LENGTH) == 0)
        {
            // OM_uint32 flags = GSS_C_REPLAY_FLAG | GSS_C_SEQUENCE_FLAG | GSS_C_MUTUAL_FLAG;
            // gss_OID mech_type;
    
            protocol_p = AUTHENTICATION_NEGOTIATE;
            mechset    = (gss_OID_set)&mechset_spnego;
    
        }
        else if (Strncasecmp(headers->authorization, AUTHENTICATION_KERBEROS, AUTHENTICATION_KERBEROS_LENGTH) == 0)
        {
            // OM_uint32 flags = GSS_C_REPLAY_FLAG | GSS_C_SEQUENCE_FLAG | GSS_C_MUTUAL_FLAG;
            // gss_OID mech_type;
    
            protocol_p = AUTHENTICATION_KERBEROS;
            mechset    = (gss_OID_set)&mechset_krb5;
    
        }
        else
        {
            trace_Wsman_UnsupportedAuthentication(headers->authorization);
            handler->httpErrorCode = HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR;
            goto Done;
        }

        if (_getInputToken(headers->authorization, &input_token) != 0)
        {
            handler->httpErrorCode = HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR; 
            goto Done;
        }
            
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

Done:
    return authorised;
}




#ifdef NOTYET
MI_Boolean requestServerAuthorization(
                               _In_    struct _WSMAN_ConnectionData*   selfCD,
                               _In_    const HttpHeaders*      headers,
                               _Out_   WSMAN_AUTH_RESULT*      result)

{
    return FALSE;
}


#endif
