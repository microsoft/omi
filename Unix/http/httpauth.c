/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <config.h>
#if ( AUTHORIZATION == 1 )
#if defined(is_macos)
#include <GSS/GSS.h>
#else
#include <gssapi/gssapi.h>
#endif
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <base/base.h>
#include <base/base64.h>
#include <base/paths.h>
#include <base/credcache.h>
#include <base/random.h>
#include <pal/lock.h>
#include <pal/once.h>
#include <xml/xml.h>
#include <protocol/protocol.h>
#include "httpcommon.h"
#include "http_private.h"

#define FORCE_TRACING 0
// #define ENCRYPT_DECRYPT 1
// #define AUTHORIZATION 1

#if !defined(KRB5_CALLCOV)
#define KRB5_CALLCONV
#endif

#define MAX_ERROR_STRING_SIZE  256
#define TIMESTAMP_SIZE 128
int GetTimeStamp(_Pre_writable_size_(TIMESTAMP_SIZE) char buf[TIMESTAMP_SIZE]);
static void _report_error(OM_uint32 major_status, OM_uint32 minor_status, const char *msg);
    
// dlsyms from the dlopen

typedef OM_uint32 KRB5_CALLCONV(*Gss_Acquire_Cred_With_Password_Func) (
            OM_uint32 *,        /* minor_status */
            const gss_name_t,   /* desired_name */
            const gss_buffer_t, /* password */
            OM_uint32,          /* time_req */
            const gss_OID_set,  /* desired_mechs */
            gss_cred_usage_t,   /* cred_usage */
            gss_cred_id_t *,    /* output_cred_handle */
            gss_OID_set *,      /* actual_mechs */
            OM_uint32 *);       /* time_rec */

typedef OM_uint32 KRB5_CALLCONV (*Gss_Accept_Sec_Context_Func)(OM_uint32 * minor_status,
                                      gss_ctx_id_t * context_handle,
                                      const gss_cred_id_t acceptor_cred_handle,
                                      const gss_buffer_t input_token_buffer,
                                      const gss_channel_bindings_t input_chan_bindings,
                                      gss_name_t * src_name,
                                      gss_OID * mech_type,
                                      gss_buffer_t output_token,
                                      OM_uint32 * ret_flags, 
                                      OM_uint32 * time_rec,
                                      gss_cred_id_t * delegated_cred_handle );

typedef OM_uint32 KRB5_CALLCONV (*Gss_Acquire_Cred_Func) (OM_uint32 * minor_status,
                                 const gss_name_t desired_name,
                                 OM_uint32 time_req,
                                 const gss_OID_set desired_mechs,
                                 gss_cred_usage_t cred_usage,
                                 gss_cred_id_t * output_cred_handle,
                                 gss_OID_set * actual_mechs, OM_uint32 * time_rec );

typedef OM_uint32 KRB5_CALLCONV (*Gss_Delete_Sec_Context_Func)(OM_uint32 * minor_status,
                                      gss_ctx_id_t * context_handle,
                                      gss_buffer_t output_token );

typedef OM_uint32 KRB5_CALLCONV (*Gss_Display_Name_Func)(OM_uint32 * minor_status,
                                const gss_name_t input_name,
                                gss_buffer_t output_name_buffer,
                                gss_OID * output_name_type);

typedef OM_uint32 KRB5_CALLCONV (*Gss_Display_Status_Func)( OM_uint32 * minor_status,
                                   OM_uint32 status_value,
                                   int status_type,
                                   const gss_OID mech_type,
                                   OM_uint32 * message_context, 
                                   gss_buffer_t status_string);

typedef OM_uint32 KRB5_CALLCONV (*Gss_Import_Name_Func)(OM_uint32 * minor_status,
                               const gss_buffer_t input_name_buffer,
                               const gss_OID input_name_type, 
                               gss_name_t * output_name);

typedef OM_uint32 KRB5_CALLCONV (*Gss_Init_Sec_Context_Func)(OM_uint32 * minor_status,
                                      const gss_cred_id_t initiator_cred_handle,
                                      gss_ctx_id_t * context_handle,
                                      const gss_name_t target_name,
                                      const gss_OID mech_type,
                                      OM_uint32 req_flags,
                                      OM_uint32 time_req,
                                      const gss_channel_bindings_t input_chan_bindings,
                                      const gss_buffer_t input_token,
                                      gss_OID * actual_mech_type,
                                      gss_buffer_t output_token,
                                      OM_uint32 * ret_flags, OM_uint32 * time_rec);

typedef OM_uint32 KRB5_CALLCONV (*Gss_Inquire_Context_Func)(OM_uint32 * minor_status,
                                      const gss_ctx_id_t context_handle,
                                      gss_name_t * src_name,
                                      gss_name_t * targ_name,
                                      OM_uint32 * lifetime_rec,
                                      gss_OID * mech_type,
                                      OM_uint32 * ctx_flags,
                                      int *locally_initiated, int *open);

typedef OM_uint32 KRB5_CALLCONV (*Gss_Release_Buffer_Func)(OM_uint32 * minor_status, gss_buffer_t buffer);
typedef OM_uint32 KRB5_CALLCONV (*Gss_Release_Cred_Func)(OM_uint32 * minor_status, gss_cred_id_t * cred_handle);
typedef OM_uint32 KRB5_CALLCONV (*Gss_Release_Name_Func)(OM_uint32 * minor_status, gss_name_t * name);

typedef OM_uint32 KRB5_CALLCONV (*Gss_Unwrap_Func)(OM_uint32 * minor_status,
                            const gss_ctx_id_t context_handle,
                            const gss_buffer_t input_message_buffer,
                            gss_buffer_t output_message_buffer,
                            int *conf_state, gss_qop_t * qop_state);

typedef OM_uint32 KRB5_CALLCONV (*Gss_Wrap_Func)(OM_uint32 * minor_status,
                          const gss_ctx_id_t context_handle,
                          int conf_req_flag,
                          gss_qop_t qop_req,
                          const gss_buffer_t input_message_buffer,
                          int *conf_state, gss_buffer_t output_message_buffer);

typedef enum { NOT_LOADED = 0, LOADING, LOADED } LoadState;

typedef struct _Gss_Extensions {
    LoadState gssLibLoaded;     /* Default is NOT_LOADED */
    void *libHandle;
    /* Optional Funcs */
    Gss_Acquire_Cred_With_Password_Func gssAcquireCredwithPassword;
    /* Mandatory Funcs */
    Gss_Accept_Sec_Context_Func Gss_Accept_Sec_Context;
    Gss_Acquire_Cred_Func       Gss_Acquire_Cred;
    Gss_Delete_Sec_Context_Func Gss_Delete_Sec_Context;
    Gss_Display_Name_Func       Gss_Display_Name;
    Gss_Display_Status_Func     Gss_Display_Status;
    Gss_Import_Name_Func        Gss_Import_Name;
    Gss_Init_Sec_Context_Func   Gss_Init_Sec_Context;
    Gss_Inquire_Context_Func    Gss_Inquire_Context;
    Gss_Release_Buffer_Func     Gss_Release_Buffer;
    Gss_Release_Cred_Func       Gss_Release_Cred;
    Gss_Release_Name_Func       Gss_Release_Name;
    Gss_Unwrap_Func             Gss_Unwrap;
    Gss_Wrap_Func               Gss_Wrap;
} Gss_Extensions;

static Gss_Extensions _g_gssState = { 0 };

static struct _Once g_once_state = ONCE_INITIALIZER;
static const char GSS_LIBRARY_NAME[] = CONFIG_GSSLIB;

static const char RESPONSE_HEADER_UNAUTH_FMT[] =
    "HTTP/1.1 401 Unauthorized\r\n" "Content-Length: 0\r\n"
    "WWW-Authenticate: Basic realm=\"WSMAN\"\r\n"       \
    "WWW-Authenticate: Negotiate\r\n"                   \
    "WWW-Authenticate: Kerberos\r\n" "\r\n";
static const int RESPONSE_HEADER_UNAUTH_FMT_LEN = MI_COUNT(RESPONSE_HEADER_UNAUTH_FMT)-1;

void _GssUnloadLibrary()
{
    dlclose(_g_gssState.libHandle);
    _g_gssState.libHandle = NULL;
    _g_gssState.gssAcquireCredwithPassword = NULL;
    _g_gssState.gssLibLoaded = NOT_LOADED;
}

static _Success_(return == 0)
int _GssInitLibrary(_In_ void *data, _Outptr_result_maybenull_ void **value)
{

    // Reserve the state to prevent race conditions

    if (_g_gssState.gssLibLoaded != NOT_LOADED)
    {
        return TRUE;
    }
    _g_gssState.gssLibLoaded = LOADING;

#ifdef aix
   void *libhandle =  dlopen(GSS_LIBRARY_NAME, RTLD_NOW | RTLD_MEMBER);
#else
   void *libhandle =  dlopen(GSS_LIBRARY_NAME, RTLD_NOW | RTLD_GLOBAL);
#endif
    void *fn_handle = NULL;

    trace_HTTP_LoadingGssApi(CONFIG_GSSLIB);
    if (libhandle)
    {
        fn_handle = dlsym(libhandle, "gss_acquire_cred_with_password");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_acquire_cred_with_password");
        }
        _g_gssState.gssAcquireCredwithPassword = (Gss_Acquire_Cred_With_Password_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_accept_sec_context");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_accept_sec_context");
            goto failed;
        }
        _g_gssState.Gss_Accept_Sec_Context = (Gss_Accept_Sec_Context_Func)fn_handle;


        fn_handle = dlsym(libhandle, "gss_acquire_cred");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_acquire_cred");
            goto failed;
        }
        _g_gssState.Gss_Acquire_Cred = (Gss_Acquire_Cred_Func)fn_handle;

        fn_handle = dlsym(libhandle, "gss_delete_sec_context");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_delete_sec_context");
            goto failed;
        }
        _g_gssState.Gss_Delete_Sec_Context = (Gss_Delete_Sec_Context_Func)fn_handle;

        fn_handle = dlsym(libhandle, "gss_display_name");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_display_name");
            goto failed;
        }
        _g_gssState.Gss_Display_Name = (Gss_Display_Name_Func)fn_handle;

        fn_handle = dlsym(libhandle, "gss_display_status");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_display_status");
            goto failed;
        }
        _g_gssState.Gss_Display_Status = (Gss_Display_Status_Func)fn_handle;

        fn_handle = dlsym(libhandle, "gss_import_name");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_import_name");
            goto failed;
        }
        _g_gssState.Gss_Import_Name = (Gss_Import_Name_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_init_sec_context");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_init_sec_context");
            goto failed;
        }
        _g_gssState.Gss_Init_Sec_Context = (Gss_Init_Sec_Context_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_inquire_context");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_inquire_context");
            goto failed;
        }
        _g_gssState.Gss_Inquire_Context  = (Gss_Inquire_Context_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_release_buffer");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_release_buffer");
            goto failed;
        }
        _g_gssState.Gss_Release_Buffer = (Gss_Release_Buffer_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_release_cred");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_release_cred");
            goto failed;
        }
        _g_gssState.Gss_Release_Cred = (Gss_Release_Cred_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_release_name");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_release_name");
            goto failed;
        }
        _g_gssState.Gss_Release_Name = (Gss_Release_Name_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_unwrap");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_unwrap");
            goto failed;
        }
        _g_gssState.Gss_Unwrap = (Gss_Unwrap_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_wrap");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_wrap");
            goto failed;
        }
        _g_gssState.Gss_Wrap   = (Gss_Wrap_Func) fn_handle;


        _g_gssState.gssLibLoaded = LOADED;
//       PAL_Atexit(_GssUnloadLibrary);

        return TRUE;
    }

    failed:
        trace_HTTP_LoadGssFailed("in dlopen");
        _g_gssState.gssAcquireCredwithPassword = NULL;
        _g_gssState.gssLibLoaded = NOT_LOADED;
        return FALSE;

}

#define HTTP_LONGEST_ERROR_DESCRIPTION 50
void _WriteTraceFile(PathID id, const void *data, size_t size);

#if ENCRYPT_DECRYPT

static const char ENCRYPTED_SEGMENT[]   = "Encrypted Boundary";
#define ENCRYPTED_SEGMENT_LEN (MI_COUNT(ENCRYPTED_SEGMENT)-1)
static const char ORIGINAL_CONTENT[]    = "OriginalContent:";
#define ORIGINAL_CONTENT_LEN     (MI_COUNT(ORIGINAL_CONTENT)-1)
static const char TYPE_FIELD[]          = "type=";
#define TYPE_FIELD_LEN           (MI_COUNT(TYPE_FIELD)-1)
static const char CHARSET_FIELD[]       = "charset=";
#define CHARSET_FIELD_LEN        (MI_COUNT(CHARSET_FIELD)-1)
static const char LENGTH_FIELD[]        = "length=";
#define LENGTH_FIELD_LEN         (MI_COUNT(LENGTH_FIELD)-1)
static const char CONTENT_TYPE[]        = "Content-Type:";
#define CONTENT_TYPE_LEN         (MI_COUNT(CONTENT_TYPE)-1)
static const char OCTET_STREAM[]        = "application/octet-stream";
#define OCTET_STREAM_LEN         (MI_COUNT(OCTET_STREAM)-1)
static const char APPLICATION_SPNEGO[]  = "application/HTTP-SPNEGO-session-encrypted"; 
#define APPLICATION_SPNEGO_LEN   (MI_COUNT(APPLICATION_SPNEGO)-1)
static const char APPLICATION_KERBEROS[]= "application/HTTP-Kerberos-session-encrypted";
#define APPLICATION_KERBEROS_LEN (MI_COUNT(APPLICATION_KERBEROS)-1)
static const char MULTIPART_ENCRYPTED[] = "multipart/encrypted";
#define MULTIPART_ENCRYPTED_LEN  (MI_COUNT(MULTIPART_ENCRYPTED)-1)
/*
 * Decrypts encrypted data in the data packet. Returns new header (with original content type and content length)
 * and the new data. releases the page. 
 * Returns true if it performed a change, false otherwise
 */

MI_Boolean Http_DecryptData(_In_ Http_SR_SocketData * handler, _Out_ HttpHeaders * pHeaders, _Out_ Page ** pData)
{
    OM_uint32 maj_stat = 0;
    OM_uint32 min_stat = 0;
    gss_buffer_desc input_buffer = { 0 };
    gss_buffer_desc output_buffer = { 0 };
    Page *page = NULL;
    char *scanlimit = NULL;
    char *scanp = NULL;
    char *segp = NULL;
    char *linep = NULL;
    char *linelimit = NULL;
    int flags = (int)handler->negFlags;
    uint32_t sig_len = 0;
    //uint32_t sig_flags = 0;

    int original_content_length = 0;
    char original_content_type_save[1024] = { 0 };  // Longest possible content type?
    char original_encoding_save[64] = { 0 };

    char *original_content_type = NULL;
    char *original_encoding = NULL;

    MI_Boolean done = FALSE;

    if (!pHeaders)
    {
        trace_HTTP_CryptInvalidArg(__FUNCTION__, "pHeaders == NULL");
        return FALSE;
    }

    if (!pHeaders->contentType)
    {
        trace_HTTP_CryptInvalidArg(__FUNCTION__, "pHeaders->contentType == NULL");
        return FALSE;
    }

    if (!(strncasecmp(pHeaders->contentType, MULTIPART_ENCRYPTED, MULTIPART_ENCRYPTED_LEN) == 0))
    {
        // Then its not encrypted. our job is done

        return TRUE;
    }

    if (!handler->pAuthContext)
    {
        trace_HTTP_CryptInvalidArg(__FUNCTION__, "context == NULL");
        return FALSE;
    }

    if (!pData)
    {
        trace_HTTP_CryptInvalidArg(__FUNCTION__, "pdata == NULL");
        return FALSE;
    }

    handler->encryptedTransaction = TRUE;

    page = *pData;
    input_buffer.length = page->u.s.size;
    input_buffer.value = (void *)(page + 1);

    // Check the data for the original size and content type, and the start of the encrypted data

    scanp = (char *)(page + 1) + 1;
    scanlimit = ((char *)page) + page->u.s.size;
    segp = scanp;
    linep = scanp;
    while (scanp < scanlimit && !done)
    {
        if ('-' == scanp[0] && '-' == scanp[-1])
        {
            // Start of a segment. But which one?
            segp = ++scanp;
        }

        if (Strncasecmp(segp, ENCRYPTED_SEGMENT, (MI_COUNT(ENCRYPTED_SEGMENT)-1)) == 0)
        {
            // Skip the boundary
            while (!('\n' == scanp[0] && '\r' == scanp[-1]) && scanp < scanlimit)
            {    
                scanp++;
            }    
            scanp++;            // ski[p the final \n

            // Which line
            while (!('\n' == scanp[0] && '\r' == scanp[-1]) && scanp < scanlimit && !done)
            {
                // Skip to the end of the line

                linep = scanp;

                if (Strncasecmp(linep, CONTENT_TYPE, CONTENT_TYPE_LEN) == 0)
                {
                    // Content-Type: application/HTTP-SPNEGO-session-encrypted | Content-Type: application/octet-stream

                    // Scan to the end of the line

                    while (!('\n' == scanp[0] && '\r' == scanp[-1]) && scanp < scanlimit && !done)
                    {    
                        scanp++;
                    }
                    linelimit = scanp - 1;

                    linep += CONTENT_TYPE_LEN - 1;
                    while (isspace(*linep) && linep < linelimit)
                        linep++;

                    if (':' == *linep && linep < linelimit)
                        linep++;

                    while (isspace(*linep) && linep < linelimit)
                        linep++;

                    if (Strncasecmp(linep, OCTET_STREAM, OCTET_STREAM_LEN) == 0)
                    {

                        // The encrypted data is sent as a 4 byte signature length, 16 byte signature,
                        // 4 byte message length, then message. gss_unwrap doesn't like that so we need to 
                        // verify the sig ourselves

                        sig_len = *(uint32_t *) (linelimit + 2);
                        sig_len = ByteSwapFromWindows32(sig_len);

                        input_buffer.length = original_content_length + sig_len;

                        input_buffer.value = linelimit + 2 +    // skip crlf
                            4;  // skip signature len

                        done = TRUE;
                        break;
                    }
                    else if (Strncasecmp(linep, APPLICATION_SPNEGO, APPLICATION_SPNEGO_LEN) == 0)
                    {
                        // Should be application/HTTP-SPNEGO-session-encrypted

                    }
                    else if (Strncasecmp(linep, APPLICATION_KERBEROS, APPLICATION_KERBEROS_LEN) == 0)
                    {
                        // Should be application/HTTP-Kerberos-session-encrypted

                    }
                    else
                    {
                        // Bogus.
                    }
                    scanp = linelimit + 2;
                }
                else if (Strncasecmp(linep, ORIGINAL_CONTENT, ORIGINAL_CONTENT_LEN) == 0)
                {
                    while (!('\n' == scanp[0] && '\r' == scanp[-1]) && scanp < scanlimit && !done)
                        scanp++;

                    linelimit = scanp - 1;

                    linep += ORIGINAL_CONTENT_LEN;
                    do
                    {

                        while ((isspace(*linep) || ';' == *linep) && linep < linelimit)
                            linep++;
                        if (Strncasecmp(linep, LENGTH_FIELD, LENGTH_FIELD_LEN) == 0)
                        {
                            linep += LENGTH_FIELD_LEN;
                            original_content_length = atoi(linep);
                            while (';' != *linep && linep < linelimit)
                                linep++;
                            linep++;
                        }
                        else if (Strncasecmp(linep, TYPE_FIELD, TYPE_FIELD_LEN) == 0)
                        {
                            linep += TYPE_FIELD_LEN;
                            original_content_type = linep;
                            while (';' != *linep && linep < linelimit)
                                linep++;
                            *linep++ = '\0';
                            memcpy(original_content_type_save, original_content_type, linep - original_content_type);
                            original_content_type = original_content_type_save;
                        }
                        else if (Strncasecmp(linep, CHARSET_FIELD, CHARSET_FIELD_LEN) == 0)
                        {
                            linep += CHARSET_FIELD_LEN;
                            original_encoding = linep;
                            while (';' != *linep && linep < linelimit)
                                linep++;
                            *linep++ = '\0';
                            memcpy(original_encoding_save, original_encoding, linep - original_encoding);
                            original_encoding = original_encoding_save;
                        }

                    }
                    while (linep < linelimit);

                    scanp = linelimit + 2;
                }
                else
                {
                    // Bogus

                    while (!('\n' == scanp[0] && '\r' == scanp[-1]) && scanp < scanlimit && !done)
                        scanp++;
                    scanp++;
                }
            }

        }
        ++scanp;
    }

    if (!done)
    {
        return FALSE;
    }
    // Alloc the new data page based on the original content size

    maj_stat = (*_g_gssState.Gss_Unwrap)(&min_stat, (gss_ctx_id_t) handler->pAuthContext, &input_buffer, &output_buffer, &flags, NULL);
    if (GSS_S_COMPLETE != maj_stat)
    {
        _report_error(maj_stat, min_stat, "gss_unwrap");
        return FALSE;
    }
    // Here is where we replace the pData page, replace the headers on content-type and content size

    // We can just copy the data into the buffer directly, since the decrypted data is guaranteed
    // to be smaller than the encrypted data plus header


    char *buffer_p = (char *)(page + 1) + output_buffer.length;

    // We know we have the additional room in the page because the string was in the page already
    //  Move the header info to the end of the buffer and put the decrypted data at the front.
    //
    memcpy(buffer_p, original_content_type, strlen(original_content_type) + 1);
    pHeaders->contentType = buffer_p;

    buffer_p += strlen(original_content_type)+1;  // Include the null

    memcpy(buffer_p, original_encoding, strlen(original_encoding) + 1);
    pHeaders->charset = buffer_p;

    pHeaders->contentLength = original_content_length;

    page->u.s.size = output_buffer.length;
    memcpy(page + 1, output_buffer.value, output_buffer.length);
    (*_g_gssState.Gss_Release_Buffer)(&min_stat, &output_buffer);

    return MI_TRUE;
}

/*
 * Encrypts data in the data packet. Returns new header (with original content type and content length)
 * and the new data. releases the page. 
 */

static const char ENCRYPTED_BOUNDARY[]                   = "--Encrypted Boundary\r\n";
#define ENCRYPTED_BOUNDARY_LEN                   (MI_COUNT(ENCRYPTED_BOUNDARY) - 1)
static const char ENCRYPTED_BODY_CONTENT_TYPE_SPNEGO[]   = "Content-Type: application/HTTP-SPNEGO-session-encrypted\r\n";
#define ENCRYPTED_BODY_CONTENT_TYPE_SPNEGO_LEN   (MI_COUNT(ENCRYPTED_BODY_CONTENT_TYPE_SPNEGO) - 1)
static const char ENCRYPTED_BODY_CONTENT_TYPE_KERBEROS[] = "Content-Type: application/HTTP-Kerberos-session-encrypted\r\n";
#define ENCRYPTED_BODY_CONTENT_TYPE_KERBEROS_LEN (MI_COUNT(ENCRYPTED_BODY_CONTENT_TYPE_KERBEROS) - 1)
static const char ORIGINAL_CONTENT_WITH_TYPE[]           = "OriginalContent: type=";
#define ORIGINAL_CONTENT_WITH_TYPE_LEN           (MI_COUNT(ORIGINAL_CONTENT_WITH_TYPE) - 1)
static const char ORIGINAL_LENGTH[]                      = ";Length=";   // Plus crlf
#define ORIGINAL_LENGTH_LEN                      (MI_COUNT(ORIGINAL_LENGTH) - 1)
static const char ENCRYPTED_OCTET_CONTENT_TYPE[]         = "Content-Type: application/octet-stream\r\n";
#define ENCRYPTED_OCTET_CONTENT_TYPE_LEN         (MI_COUNT(ENCRYPTED_OCTET_CONTENT_TYPE) - 1)
static const char TRAILER_BOUNDARY[]                     = "--Encrypted Boundary--\r\n";
#define TRAILER_BOUNDARY_LEN                     (MI_COUNT(TRAILER_BOUNDARY) - 1)
MI_Boolean 
Http_EncryptData(_In_ Http_SR_SocketData *handler, int contentLen, int contentTypeLen, char *contentType, _Out_ Page ** pData)

{
    int needed_data_size = 0;

    int    body_content_len = 0;
    char * body_content     = NULL;

    // We encrypted every byte that was there. Success

    if (!pData)
    {
        return MI_TRUE;
    }

    if (!*pData)
    {
        return MI_TRUE;
    }

    if (!handler->encryptedTransaction)
    {

        // We are not encrypting, so we are done;

        return MI_TRUE;
    }

    char *poriginal_data        = (char *)(*pData + 1);

    switch(handler->httpAuthType)
    {
    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
        body_content     = (char*)ENCRYPTED_BODY_CONTENT_TYPE_SPNEGO;
        body_content_len = ENCRYPTED_BODY_CONTENT_TYPE_SPNEGO_LEN;
        break;
    
    case AUTH_METHOD_KERBEROS:
        body_content     = (char*)ENCRYPTED_BODY_CONTENT_TYPE_KERBEROS;
        body_content_len = ENCRYPTED_BODY_CONTENT_TYPE_KERBEROS_LEN;
        break;
    
    default:
        trace_Wsman_UnsupportedAuthentication("Unknown");
        return MI_FALSE;
    }

    gss_buffer_desc input_buffer = { contentLen, poriginal_data };
    gss_buffer_desc output_buffer = { 0 };
    OM_uint32 min_stat, maj_stat;
    int out_flags;

    maj_stat = (*_g_gssState.Gss_Wrap)(&min_stat, handler->pAuthContext, handler->negFlags| GSS_C_REPLAY_FLAG,    // GSS_C_INTEG_FLAG and or GSS_C_PRIV_FLAG
                        GSS_C_QOP_DEFAULT, &input_buffer, &out_flags, &output_buffer);

    if (maj_stat != GSS_S_COMPLETE)
    {
        _report_error(maj_stat, min_stat, "gss_wrap failed");
        (*_g_gssState.Gss_Release_Buffer)(&min_stat, &output_buffer);
        return MI_FALSE;
    }

    // We need to get the proper length from the token. The signature is added in the wrapping process and 
    // should represent any difference unless there is some kind of padding added.
    int signature_length = output_buffer.length-input_buffer.length;

    char numbuf[11] = { 0 };

    size_t  content_len_strlen = 0;
    const char *pcontent_len_str = Uint32ToStr(numbuf, contentLen, &content_len_strlen);

    // Figure out the data size
    needed_data_size = ENCRYPTED_BOUNDARY_LEN + // --Encrypted Boundary\r\n
                       body_content_len +
                                                // Content-Type: application/HTTP-Kerberos-session-encrypted\r\n
                       ORIGINAL_CONTENT_WITH_TYPE_LEN + ORIGINAL_LENGTH_LEN + contentTypeLen + content_len_strlen + 2 +
                                                // OriginalContent: type=application/soap+xml;charset=UTF-8;Length=1273\r\n
                       ENCRYPTED_BOUNDARY_LEN + // --Encrypted Boundary\r\n
                                                // Content-Type: application/octet-stream\r\n
                       ENCRYPTED_OCTET_CONTENT_TYPE_LEN +
                       4 +                      // dword signaturelength
                       output_buffer.length +   // <signature> <encrypted data>
                       TRAILER_BOUNDARY_LEN +   // --Encrypted Boundary--\r\n
                       2;                       // \r\n

    if (needed_data_size + sizeof(Page) > HTTP_ALLOCATION_LIMIT)
    {
        (*_g_gssState.Gss_Release_Buffer)(&min_stat, &output_buffer);
        trace_Http_Malloc_Error(needed_data_size + sizeof(Page));
        return MI_FALSE;
    }

    Page *pNewData = PAL_Malloc(needed_data_size+sizeof(Page));
    if (!pNewData)
    {
        (*_g_gssState.Gss_Release_Buffer)(&min_stat, &output_buffer);
        trace_HTTP_AuthMallocFailed("pNewData in Http_EcryptData");
        return MI_FALSE;
    }

    char *buffp = (char *)(pNewData + 1);

    memcpy(buffp, ENCRYPTED_BOUNDARY, ENCRYPTED_BOUNDARY_LEN);
    buffp += ENCRYPTED_BOUNDARY_LEN;

    memcpy(buffp, body_content, body_content_len);
    buffp += body_content_len;

    memcpy(buffp, ORIGINAL_CONTENT_WITH_TYPE, ORIGINAL_CONTENT_WITH_TYPE_LEN);
    buffp += ORIGINAL_CONTENT_WITH_TYPE_LEN;

    memcpy(buffp, contentType, contentTypeLen);
    buffp += contentTypeLen;

    memcpy(buffp, ORIGINAL_LENGTH, ORIGINAL_LENGTH_LEN);
    buffp += ORIGINAL_LENGTH_LEN;

    memcpy(buffp, pcontent_len_str, content_len_strlen);
    buffp += content_len_strlen;

    memcpy(buffp, "\r\n", 2);
    buffp += 2;

    memcpy(buffp, ENCRYPTED_BOUNDARY, ENCRYPTED_BOUNDARY_LEN);
    buffp += ENCRYPTED_BOUNDARY_LEN;

    memcpy(buffp, ENCRYPTED_OCTET_CONTENT_TYPE, ENCRYPTED_OCTET_CONTENT_TYPE_LEN);
    buffp += ENCRYPTED_OCTET_CONTENT_TYPE_LEN;

    int siglen = ByteSwapToWindows32(signature_length);

    memcpy(buffp, &siglen, 4);
    buffp += 4;

    memcpy(buffp, output_buffer.value, output_buffer.length);
    buffp += output_buffer.length;

    memcpy(buffp, TRAILER_BOUNDARY, TRAILER_BOUNDARY_LEN);
    buffp += TRAILER_BOUNDARY_LEN;
    *buffp++ = '\r';
    *buffp++ = '\n';

    pNewData->u.s.size = buffp-(char*)(pNewData+1);
    pNewData->u.s.next = 0;
    *pData = pNewData;
    (*_g_gssState.Gss_Release_Buffer)(&min_stat, &output_buffer);

    return MI_TRUE;

}

#endif

static MI_Boolean _WriteAuthResponse(Http_SR_SocketData * handler, const char *pResponse, int responseLen)
{

/*    "SOAPAction: http://schemas.xmlsoap.org/ws/2004/08/addressing/fault\r\n"\ */

    size_t sent, total_sent;
    total_sent = 0;

    if (!pResponse)
    {
        return FALSE;
    }

    if (!handler->ssl)
    {
        MI_Result rslt;

        do
        {
            rslt = Sock_Write(handler->handler.sock, pResponse, responseLen, &sent);
        }
        while (rslt == MI_RESULT_WOULD_BLOCK);

        if (FORCE_TRACING || ((total_sent > 0) && handler->enableTracing))
        {
            char startTime[TIMESTAMP_SIZE]={'\0'};
            GetTimeStamp(startTime);
            _WriteTraceFile(ID_HTTPSENDTRACEFILE, &startTime, strlen(startTime));
            _WriteTraceFile(ID_HTTPSENDTRACEFILE, pResponse, sent);
        }
        return rslt == MI_RESULT_OK;
    }

    do
    {
        sent = 0;
        sent = SSL_write(handler->ssl, pResponse, responseLen);

        if (sent == 0)
        {
            trace_Socket_ConnectionClosed(ENGINE_TYPE, handler);
            return FALSE;

        }
        else if ((int)sent < 0)
        {
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
                if (EAGAIN == errno || EWOULDBLOCK == errno || EINPROGRESS == errno)
                    // If e_would_block we just retry in the loop.

                    break;

                trace_SSLWrite_UnexpectedSysError(errno);
                return FALSE;

            default:
                break;
            }
        }

        total_sent += sent;

    }
    while (total_sent < responseLen);

    if (FORCE_TRACING || ((total_sent > 0) && handler->enableTracing))
    {
        char startTime[TIMESTAMP_SIZE]={'\0'};
        GetTimeStamp(startTime);
        _WriteTraceFile(ID_HTTPSENDTRACEFILE, &startTime, strlen(startTime));
        _WriteTraceFile(ID_HTTPSENDTRACEFILE, pResponse, total_sent);
    }
    // if (handler->sentSize < buf_size)
    //     return PRT_RETURN_TRUE;

    // handler->sendingState = RECV_STATE_CONTENT;

    return TRUE;
}

/*
**==============================================================================
*/

static void _SendAuthResponse(Http_SR_SocketData * sendSock, const char *pResponse, int responseLen)
{
    DEBUG_ASSERT(sendSock);

    /* validate handler */

    sendSock->handler.mask |= SELECTOR_WRITE;
    sendSock->handler.mask &= ~SELECTOR_READ;

    sendSock->sentSize = 0;
    sendSock->sendingState = RECV_STATE_HEADER;

    trace_HTTP_SendNextAuthReply();
    if (!_WriteAuthResponse(sendSock, pResponse, responseLen))
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

#if AUTHORIZATION
static gss_buffer_t _getPrincipalName(gss_ctx_id_t pContext)
{
    // Now we have established context. All lines below are for getting source user name in form of username@DOMAIN.COM (I got it capitalized, yes)
    gss_name_t srcName = NULL;
    //gss_name_t  targetName = NULL;
    OM_uint32 lifetime;
    OM_uint32 ctxFlags = 0;

    OM_uint32 maj_status;
    OM_uint32 min_status;
    gss_buffer_t buff = PAL_Malloc(sizeof(gss_buffer_desc));

    memset(buff, 0, sizeof(gss_buffer_desc));

    maj_status = (*_g_gssState.Gss_Inquire_Context)(&min_status, pContext, &srcName,
                                     /*&targetName */ NULL, &lifetime, NULL,
                                     &ctxFlags, NULL, NULL);
    if (maj_status != GSS_S_COMPLETE)
    {
        _report_error(maj_status, min_status, "gss_inquire_context");
        goto Done;
    }

    if (srcName != NULL)
    {
        maj_status = (*_g_gssState.Gss_Display_Name)(&min_status, srcName, buff, NULL);
        if (maj_status != GSS_S_COMPLETE)
        {
            _report_error(maj_status, min_status, "gss_display_name");
            goto Done;
        }
        maj_status = (*_g_gssState.Gss_Release_Name)(&min_status, &srcName);
    }
    else
    {
#ifdef DEBUG
        fprintf(stderr, "srcName == NULL\n");
#endif
        _report_error(maj_status, min_status, "gss_display_name");
        goto Done;
    }

  Done:

    return buff;
}

static void _displayStatus(OM_uint32 status_code, int status_type)
{
    //   const gss_OID_desc mech_krb5   = { 9, "\052\206\110\206\367\022\001\002\002" };
    //   const gss_OID_desc mech_spnego = { 6, "\053\006\001\005\005\002" };
    //   const gss_OID_desc mech_iakerb = { 6, "\053\006\001\005\002\005" };
    const gss_OID_desc mech_ntlm = { 10, "\x2b\x06\x01\x04\x01\x82\x37\x02\x02\x0a" };

    OM_uint32 message_context;
    OM_uint32 min_status;
    gss_buffer_desc status_string;

    message_context = 0;

    do
    {
        (* _g_gssState.Gss_Display_Status)(&min_status, status_code, status_type, (gss_OID) & mech_ntlm, &message_context, &status_string);
        trace_HTTP_GssStatus((int)status_string.length, (char *)status_string.value, min_status);
        (* _g_gssState.Gss_Release_Buffer)(&min_status, &status_string);

    }
    while (message_context != 0);
}

static void _report_error(OM_uint32 major_status, OM_uint32 minor_status, const char *msg)
{
    // gssntlm_display_Error should work, but doesnt give very good messages sometimes
    const char *ntlm_err_string; 

    switch(minor_status) 
    {
    default:    
        ntlm_err_string = NULL;
        break;
    case ERR_DECODE:
        ntlm_err_string = "Failed to decode data";
        break;
    case ERR_ENCODE:
        ntlm_err_string = "Failed to encode data";
        break;
    case ERR_CRYPTO:
        ntlm_err_string = "Crypto routine failure";
        break;
    case ERR_NOARG:
        ntlm_err_string = "A required argument is missing";
        break;
    case ERR_BADARG:
        ntlm_err_string = "Invalid value in argument";
        break;
    case ERR_NONAME:
        ntlm_err_string = "Name is empty";
        break;
    case ERR_NOSRVNAME:
        ntlm_err_string = "Not a server name";
        break;
    case ERR_NOUSRNAME:
        ntlm_err_string = "Not a user name";
        break;
    case ERR_BADLMLVL:
        ntlm_err_string = "Bad LM compatibility Level";
        break;
    case ERR_IMPOSSIBLE:
        ntlm_err_string = "An impossible error occurred";
        break;
    case ERR_BADCTX:
        ntlm_err_string = "Invalid or incomplete context";
        break;
    case ERR_WRONGCTX:
        ntlm_err_string = "Wrong context type";
        break;
    case ERR_WRONGMSG:
        ntlm_err_string = "Wrong message type";
        break;
    case ERR_REQNEGFLAG:
        ntlm_err_string = "A required Negotiate flag was not provided";
        break;
    case ERR_FAILNEGFLAGS:
        ntlm_err_string = "Failed to negotiate a common set of flags";
        break;
    case ERR_BADNEGFLAGS:
        ntlm_err_string = "Invalid combinations of negotiate flags";
        break;
    case ERR_NOSRVCRED:
        ntlm_err_string = "Not a server credential type";
        break;
    case ERR_NOUSRCRED:
        ntlm_err_string = "Not a user credential type";
        break;
    case ERR_BADCRED:
        ntlm_err_string = "Invalid or unknown credential";
        break;
    case ERR_NOTOKEN:
        ntlm_err_string = "Empty or missing token";
        break;
    case ERR_NOTSUPPORTED:
        ntlm_err_string = "Feature not supported";
        break;
    case ERR_NOTAVAIL:
        ntlm_err_string = "Feature not available. Winbind was unable to look up credentials for user";
        break;
    case ERR_NAMETOOLONG:
        ntlm_err_string = "Name is too long";
        break;
    case ERR_NOBINDINGS:
        ntlm_err_string =  "Required channel bingings are not available";
        break;
    case ERR_TIMESKEW:
        ntlm_err_string = "Server and client clocks are too far apart";
        break;
    case ERR_EXPIRED:
        ntlm_err_string = "Expired";
        break;
    case ERR_KEYLEN:
        ntlm_err_string = "Invalid key length";
        break;
    case ERR_NONTLMV1:
        ntlm_err_string = "NTLM version 1 not allowed";
        break;
    case ERR_NOUSRFOUND:
        ntlm_err_string = "User not found";
        break;
    };


    if (!msg)
    {
        msg = "";
    }

    /* _displayStatus(major_status, GSS_C_GSS_CODE); */

    if (ntlm_err_string)
    {
        trace_HTTP_GssNtlmStatus(ntlm_err_string, msg);
    }
    else
    {
        trace_HTTP_GssError(msg);
        _displayStatus(minor_status, GSS_C_MECH_CODE);
    }
}

static char g_MinErrorString[MAX_ERROR_STRING_SIZE] = { 0 };
static char g_MajErrorString[MAX_ERROR_STRING_SIZE] = { 0 };


static const OM_uint32 GSS_GENERIC_MINOR_ERROR_MIN = (0x861b6d00UL);
static const OM_uint32 GSS_GENERIC_MINOR_ERROR_MAX = (0x861b6d13UL);

static __inline__ _Bool isSpnegoError(OM_uint32 errcode)

{
    static const OM_uint32 GSS_SPNEGO_MINOR_ERROR_MIN = (0x20000000UL);
    static const OM_uint32 GSS_SPNEGO_MINOR_ERROR_MAX = (0x20000005UL);

    if (errcode >= GSS_SPNEGO_MINOR_ERROR_MIN &&
        errcode <= GSS_SPNEGO_MINOR_ERROR_MAX )
    {
        return TRUE;
    }

    if (errcode >= GSS_GENERIC_MINOR_ERROR_MIN &&
        errcode <= GSS_GENERIC_MINOR_ERROR_MAX )
    {
        return TRUE;
    }
    return FALSE;
}



static __inline__ _Bool isKrb5Error(OM_uint32 errcode)

{
    static const OM_uint32 GSS_KRB5_MINOR_ERROR_MIN = (0x25ea100);
    static const OM_uint32 GSS_KRB5_MINOR_ERROR_MAX = (0x25ea110);

    if (errcode >= GSS_KRB5_MINOR_ERROR_MIN &&
        errcode <= GSS_KRB5_MINOR_ERROR_MAX )
    {
        return TRUE;
    }

    if (errcode >= GSS_GENERIC_MINOR_ERROR_MIN &&
        errcode <= GSS_GENERIC_MINOR_ERROR_MAX )
    {
        return TRUE;
    }
    return FALSE;
}

static __inline__ _Bool isMajorError(OM_uint32 errcode)
{
    switch(errcode) 
    {
    case 0x10000: // GSS_S_BAD_MECH
    case 0x20000: // GSS_S_BAD_NAME
    case 0x30000: // GSS_S_BAD_NAMETYPE
    case 0x40000: // GSS_S_BAD_BINDINGS
    case 0x50000: // GSS_S_BAD_STATUS
    case 0x60000: // GSS_S_BAD_SIG
    case 0x70000: // GSS_S_NO_CRED
    case 0x80000: // GSS_S_NO_CONTEXT
    case 0x90000: // GSS_S_DEFECTIVE_TOKEN
    case 0xa0000: // GSS_S_DEFECTIVE_CREDENTIAL
    case 0xb0000: // GSS_S_CREDENTIALS_EXPIRED
    case 0xc0000: // GSS_S_CONTEXT_EXPIRED
    case 0xd0000: // GSS_S_FAILURE
    case 0xe0000: // GSS_S_BAD_QOP
    case 0xf0000: // GSS_S_UNAUTHORIZED
    case 0x100000: // GSS_S_UNAVAILABLE
    case 0x110000: // GSS_S_DUPLICATE_ELEMENT
    case 0x120000: // GSS_S_NAME_NOT_MN
    case 0x130000: // GSS_S_BAD_MECH_ATTR
        return TRUE;
    default:
        return FALSE;
    }

}


static __inline__ void traceSupplementaryInfo(OM_uint32 code)
{

    if (code & GSS_S_DUPLICATE_TOKEN)
    {
        trace_HTTP_SupplimentaryInfo("GSS_S_DUPLICATE_TOKEN");
    }
    if (code & GSS_S_OLD_TOKEN )
    {
        trace_HTTP_SupplimentaryInfo("GSS_S_OLD_TOKEN");
    }
    if (code & GSS_S_UNSEQ_TOKEN )
    {
        trace_HTTP_SupplimentaryInfo("GSS_S_UNSEQ_TOKEN");
    }
    if (code & GSS_S_GAP_TOKEN)
    {
        trace_HTTP_SupplimentaryInfo("GSS_S_GAP_TOKEN");
    }

}


static __inline__ const char *_StatusString(OM_uint32 status )
{ 
    const char *ntlm_err_string; 

    switch(status) 
    {
    default:    
        ntlm_err_string = NULL;
        break;
    case ERR_DECODE:
        ntlm_err_string = "Failed to decode data";
        break;
    case ERR_ENCODE:
        ntlm_err_string = "Failed to encode data";
        break;
    case ERR_CRYPTO:
        ntlm_err_string = "Crypto routine failure";
        break;
    case ERR_NOARG:
        ntlm_err_string = "A required argument is missing";
        break;
    case ERR_BADARG:
        ntlm_err_string = "Invalid value in argument";
        break;
    case ERR_NONAME:
        ntlm_err_string = "Name is empty";
        break;
    case ERR_NOSRVNAME:
        ntlm_err_string = "Not a server name";
        break;
    case ERR_NOUSRNAME:
        ntlm_err_string = "Not a user name";
        break;
    case ERR_BADLMLVL:
        ntlm_err_string = "Bad LM compatibility Level";
        break;
    case ERR_IMPOSSIBLE:
        ntlm_err_string = "An impossible error occurred";
        break;
    case ERR_BADCTX:
        ntlm_err_string = "Invalid or incomplete context";
        break;
    case ERR_WRONGCTX:
        ntlm_err_string = "Wrong context type";
        break;
    case ERR_WRONGMSG:
        ntlm_err_string = "Wrong message type";
        break;
    case ERR_REQNEGFLAG:
        ntlm_err_string = "A required Negotiate flag was not provided";
        break;
    case ERR_FAILNEGFLAGS:
        ntlm_err_string = "Failed to negotiate a common set of flags";
        break;
    case ERR_BADNEGFLAGS:
        ntlm_err_string = "Invalid combinations of negotiate flags";
        break;
    case ERR_NOSRVCRED:
        ntlm_err_string = "Not a server credential type";
        break;
    case ERR_NOUSRCRED:
        ntlm_err_string = "Not a user credential type";
        break;
    case ERR_BADCRED:
        ntlm_err_string = "Invalid or unknown credential";
        break;
    case ERR_NOTOKEN:
        ntlm_err_string = "Empty or missing token";
        break;
    case ERR_NOTSUPPORTED:
        ntlm_err_string = "Feature not supported";
        break;
    case ERR_NOTAVAIL:
        ntlm_err_string = "Feature not available. Winbind was unable to look up credentials for user";
        break;
    case ERR_NAMETOOLONG:
        ntlm_err_string = "Name is too long";
        break;
    case ERR_NOBINDINGS:
        ntlm_err_string =  "Required channel bingings are not available";
        break;
    case ERR_TIMESKEW:
        ntlm_err_string = "Server and client clocks are too far apart";
        break;
    case ERR_EXPIRED:
        ntlm_err_string = "Expired";
        break;
    case ERR_KEYLEN:
        ntlm_err_string = "Invalid key length";
        break;
    case ERR_NONTLMV1:
        ntlm_err_string = "NTLM version 1 not allowed";
        break;
    case ERR_NOUSRFOUND:
        ntlm_err_string = "User not found";
        break;
    };

    if (ntlm_err_string)
    {
        return ntlm_err_string;
    }
    else
    {
        const gss_OID_desc mech_krb5   = { 9, "\052\206\110\206\367\022\001\002\002" };
        const gss_OID_desc mech_spnego = { 6, "\053\006\001\005\005\002" };
        //const gss_OID_desc mech_iakerb = { 6, "\053\006\001\005\002\005" };
        // const gss_OID_desc mech_ntlm = { 10, "\x2b\x06\x01\x04\x01\x82\x37\x02\x02\x0a" };
        gss_OID mech = NULL;

        OM_uint32 message_context;
        OM_uint32 min_status;
        gss_buffer_desc status_string;

        message_context = 0;

        if (isMajorError(status))
        {
            mech = NULL;
            do
            {
                (* _g_gssState.Gss_Display_Status)(&min_status, status, GSS_C_MECH_CODE, mech, &message_context, &status_string);
                memcpy(&g_MajErrorString[0], status_string.value, status_string.length < MAX_ERROR_STRING_SIZE? status_string.length : MAX_ERROR_STRING_SIZE  );
                (* _g_gssState.Gss_Release_Buffer)(&min_status, &status_string);

            }
            while (message_context != 0);

            return g_MajErrorString;
        }
        else if (isSpnegoError(status))
        {
            mech = (gss_OID)&mech_spnego;
        }
        else if (isKrb5Error(status))
        {
            mech = (gss_OID)&mech_krb5;
        }
        else 
        {
            // Out of ideas. If it is an unknown minor error, krb5 is as good as anything
            //
            mech = (gss_OID)&mech_krb5;
        }

        do
        {
            (* _g_gssState.Gss_Display_Status)(&min_status, status, GSS_C_MECH_CODE, mech, &message_context, &status_string);
            // Bug: we might see multi line error text. If so, we will only get the last line
            memcpy(&g_MinErrorString[0], status_string.value, status_string.length < MAX_ERROR_STRING_SIZE? status_string.length : MAX_ERROR_STRING_SIZE  );
            (* _g_gssState.Gss_Release_Buffer)(&min_status, &status_string);

        }
        while (message_context != 0);
        return g_MinErrorString;
    }
}
static int _check_gsserr(const char *msg, OM_uint32 major_status, OM_uint32 minor_status)
{
    if (GSS_ERROR(major_status))
    {
        trace_HTTP_GssError(msg);
        _report_error(major_status, minor_status, "");
        return 1;
    }
    return 0;
}

static int _Base64DecCallback(const void *data, size_t length, void *callbackData)
{
    gss_buffer_t decoded_data = (gss_buffer_t) callbackData;
    const char *new_decoded_data = (const char *)data;

    memcpy((char *)decoded_data->value + decoded_data->length, new_decoded_data, length);
    decoded_data->length += length;

    return 0;
}

/*
Converts the SPNEGO authorization header string to an opaque gss token

*/

static int _getInputToken(_In_ struct _Http_SR_SocketData * self,  const char *authorization, gss_buffer_t token)
{
    const char *auth = authorization;

    switch (self->httpAuthType)
    {
    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
        auth += AUTHENTICATION_NEGOTIATE_LENGTH + 1;
        break;
    
    case AUTH_METHOD_KERBEROS:
        auth += AUTHENTICATION_KERBEROS_LENGTH + 1;
        break;
    
    default:

        // traceUnknownAuthType
        return -1;
    }

    int auth_len = strlen(auth);
    token->value = (unsigned char *)PAL_Malloc(auth_len);
    if (!token->value)
    {
        return -1;
    }
    memset(token->value, 0, auth_len);
    token->length = 0;

    int decodedSize = Base64Dec((const void *)auth, auth_len, _Base64DecCallback, token);

    if (decodedSize <= 0)
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
    char *pdata;
};

static int EncodeSizeCallback(const char *data, size_t size, void *callbackData)
{
    struct _EncodeContext *p_encode_context = (struct _EncodeContext *)callbackData;

    p_encode_context->size += size;

    return 0;
}

static int EncodePlaceCallback(const char *data, size_t size, void *callbackData)
{
    struct _EncodeContext *p_encode_context = (struct _EncodeContext *)callbackData;

    memcpy(p_encode_context->pdata + p_encode_context->size, data, size);
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

static char *_BuildAuthResponse(_In_ const char *pProtocol,
                                         const int httpStatus, const gss_buffer_t token, _Out_ int *pResultLen)
{

    static const char HEADER_SERVER_ERROR[] = "HTTP/1.1 500 Internal Server Error\r\n" "\r\nContent-Length: 0\r\n" "\r\n";
    static const int  HEADER_SERVER_ERROR_LEN = MI_COUNT(HEADER_SERVER_ERROR)-1;

    static const char HEADER_UNAUTHORIZED[] = "HTTP/1.1 401 Unauthorized\r\n" "\r\nContent-Length: 0\r\n" "\r\n";
    static const int  HEADER_UNAUTHORIZED_LEN = MI_COUNT(HEADER_UNAUTHORIZED)-1;

    static const char HEADER_START_NEGO[] = "HTTP/1.1 401 Unauthorized\r\n" "WWW-Authenticate: ";
    static const int  HEADER_START_NEGO_LEN = MI_COUNT(HEADER_START_NEGO)-1;

    static const char HEADER_START_SUCCESS[] = "HTTP/1.1 200 Success\r\n" "WWW-Authenticate: ";
    static const int  HEADER_START_SUCCESS_LEN = MI_COUNT(HEADER_START_SUCCESS)-1;

    static const char HEADER_TAIL[] = "\r\nContent-Length: 0\r\n" "\r\n";
    static const int  HEADER_TAIL_LEN = MI_COUNT(HEADER_TAIL)-1;

    static const char HEADER_START_AUTH_ONLY[] = "WWW-Authenticate: ";
    static const int  HEADER_START_AUTH_ONLY_LEN = MI_COUNT(HEADER_START_AUTH_ONLY)-1;

    //const int HEADER_START_SUCCESS_LEN = strlen(HEADER_START_SUCCESS);
    //const int HEADER_START_NEGO_LEN = strlen(HEADER_START_NEGO);

    // This may in future say Nego, Kerberos, or Ntlm

    int protocol_len = strlen(pProtocol);

    const char *header_start = NULL;
    int header_start_len = 0;
    int header_tail_len  = 0;

    struct _EncodeContext encode_context = { 0 };

    switch (httpStatus)
    {
    case 0: // We will add the header info later. Just build a WWW-Authenticate: 
        header_start = HEADER_START_AUTH_ONLY;
        header_start_len = HEADER_START_AUTH_ONLY_LEN;
        header_tail_len  = 0;
        break; 

    case HTTP_ERROR_CODE_OK:
        header_start = HEADER_START_SUCCESS;
        header_start_len = HEADER_START_SUCCESS_LEN;
        header_tail_len  = HEADER_TAIL_LEN;
        break;

    case HTTP_ERROR_CODE_UNAUTHORIZED:
        header_start = HEADER_START_NEGO;
        header_start_len = HEADER_START_NEGO_LEN;
        header_tail_len  = HEADER_TAIL_LEN;
        break;

    default:
    case HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR:
        {
            *pResultLen = HEADER_SERVER_ERROR_LEN;

            char *pdata = PAL_Malloc(*pResultLen + 1);
            memcpy(pdata, HEADER_SERVER_ERROR, *pResultLen);
            pdata[*pResultLen] = '\0';

            header_tail_len  = HEADER_TAIL_LEN;
            return pdata;
        }
        break;
    }

    encode_context.size = 0;
    encode_context.pdata = NULL;

    if (!token)
    {
        encode_context.size = HEADER_UNAUTHORIZED_LEN;
        encode_context.pdata = PAL_Malloc(*pResultLen + 1);
        memcpy(encode_context.pdata, HEADER_SERVER_ERROR, encode_context.size);
        encode_context.pdata[encode_context.size] = '\0';
    }
    else
    {
        // Call once to estimate the size.
        int rslt = Base64Enc(token->value, token->length, EncodeSizeCallback,
                             &encode_context);

        // Then we allocate the data  and add the extra

        encode_context.pdata = PAL_Malloc(encode_context.size + // The encoded data size
                                          header_start_len +    // 
                                          protocol_len + 1 +    // eg, "Negotiate" plus a space to separate it from the auth token
                                          header_tail_len + 1); // NULL

        memcpy(encode_context.pdata, header_start, header_start_len);
        memcpy(encode_context.pdata + header_start_len, pProtocol, protocol_len);
        memcpy(encode_context.pdata + header_start_len + protocol_len, " ", 1);

        encode_context.size = header_start_len + protocol_len + 1;

        // Call again to copy the data
        if (rslt >= 0)
        {
            rslt = Base64Enc(token->value, token->length, EncodePlaceCallback, &encode_context);
        }

        memcpy(encode_context.pdata + encode_context.size, HEADER_TAIL, HEADER_TAIL_LEN);
        encode_context.size += HEADER_TAIL_LEN;
        encode_context.pdata[encode_context.size] = '\0';

    }

    if (pResultLen)
    {
        *pResultLen = encode_context.size;
    }
    return encode_context.pdata;
}

#endif

void Deauthorize(_In_ Http_SR_SocketData * handler)
{
#if defined(AUTHORIZATION)
    OM_uint32 maj_stat, min_stat;
#endif

    // Reinit all of the handler authorisation state.

    handler->authFailed = FALSE;
    handler->isAuthorised = FALSE;
    if (handler->pAuthContext)
    {
        // Tear down the context. The function will set to null

#if defined(AUTHORIZATION)
        gss_ctx_id_t hdl = handler->pAuthContext;
        maj_stat = (* _g_gssState.Gss_Delete_Sec_Context)(&min_stat, &hdl, NULL);
        if (maj_stat != GSS_S_COMPLETE)
        {
             // 2do: Not clear what to do here
             // I'm going to procede anyway.
        }
#endif
        handler->pAuthContext = hdl;
    }
    if (handler->pVerifierCred)
    {
        (* _g_gssState.Gss_Release_Cred)(&min_stat, handler->pVerifierCred);
        handler->pVerifierCred = NULL;
    }    

    handler->httpAuthType = AUTH_METHOD_UNSUPPORTED;
    handler->encryptedTransaction = FALSE;

    handler->negFlags = 0;
    handler->authInfo.uid = -1;
    handler->authInfo.gid = -1;
}

static MI_Result _ServerAuthenticateCallback(PamCheckUserResp *msg)
{
    MI_Result r;
    char *auth_response = NULL;
    int response_len = 0;

    Http_SR_SocketData *handler = (Http_SR_SocketData*)(uintptr_t)msg->handle;
    HttpHeaders *headers = &handler->recvHeaders;

    if (!msg->result)
    {
        handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
        auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
        response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

        trace_HTTP_UserAuthFailed("server determined that user is not authorized");
        handler->authFailed = TRUE;

        _SendAuthResponse(handler, auth_response, response_len);
        goto Done;
    }

    /* Add user to cache if auth was ok */
    CredCache_PutUser(headers->username, headers->password);

    if (0 != LookupUser(headers->username, &handler->authInfo.uid, &handler->authInfo.gid))
    {
        trace_GetUserUidGid_Failed(headers->username);
        
        handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
        auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
        response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

        trace_HTTP_UserAuthFailed("basic auth user creds not present");
        handler->authFailed = TRUE;
        _SendAuthResponse(handler, auth_response, response_len);
        goto Done;
    }

    if (1 != IsUserAuthorized(headers->username, handler->authInfo.gid))
    {
        trace_Authorization_Failed(headers->username);
        
        handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
        auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
        response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

        trace_HTTP_UserAuthFailed("basic auth user authorization failed");
        handler->authFailed = TRUE;
        _SendAuthResponse(handler, auth_response, response_len);
        goto Done;
    }

    handler->httpErrorCode = 0; // Let the request do the error code
    handler->isAuthorised = TRUE;

    // Resume selector processing of this socket
    handler->handler.mask |= SELECTOR_READ;
    Selector_Wakeup(handler->http->selector, MI_TRUE);

    r = Process_Authorized_Message(handler);
    if (MI_RESULT_OK != r)
    {
        return MI_RESULT_FAILED;
    }

Done:
    handler->recvPage = 0;
    handler->receivedSize = 0;
    memset(&handler->recvHeaders, 0, sizeof(handler->recvHeaders));
    handler->recvingState = RECV_STATE_HEADER;

    return MI_RESULT_OK;
}

Http_CallbackResult IsClientAuthorized(_In_ Http_SR_SocketData * handler)
{
    Http_CallbackResult authorised = PRT_RETURN_FALSE;
    HttpHeaders *headers = &handler->recvHeaders;

    static const char RESPONSE_HEADER_AUTHORIZED[] = "HTTP/1.1 200 Success\r\n" "Content-Length: 0\r\n" "\r\n";
    static const int  RESPONSE_HEADER_AUTHORIZED_LEN = MI_COUNT(RESPONSE_HEADER_AUTHORIZED)-1;
#if AUTHORIZATION
    static const char RESPONSE_HEADER_BAD_REQUEST[] = "HTTP/1.1 400 Bad Request\r\n" "Content-Length: 0\r\n" "\r\n";
    static const int  RESPONSE_HEADER_BAD_REQUEST_LEN = MI_COUNT(RESPONSE_HEADER_BAD_REQUEST)-1;
    OM_uint32 flags = 0;
    const char *protocol_p = NULL;
#endif

    char *auth_response = NULL;
    int response_len = 0;

    if (IsAuthCallsIgnored())
    {
        handler->httpErrorCode = 0; // We let the transaction set the error code
        handler->isAuthorised = TRUE;
        return PRT_RETURN_TRUE;
    }

    if (!headers)
    {
        handler->httpErrorCode = HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR;
        goto Done;
    }

    if (Strncasecmp(headers->authorization, AUTHENTICATION_BASIC, AUTHENTICATION_BASIC_LENGTH) == 0)
    {
        handler->httpAuthType = AUTH_METHOD_BASIC;
        if (!headers->username || !headers->password)
        {
            handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
            auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
            response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

            trace_HTTP_UserAuthFailed("missing user name or password");
            handler->authFailed = TRUE;

            _SendAuthResponse(handler, auth_response, response_len);
            return PRT_RETURN_FALSE;
        }

        if (0 == IsRoot())
        {
            if (0 != AuthenticateUser(headers->username, headers->password))
            {
                handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
                auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
                response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

                trace_HTTP_UserAuthFailed("user not authenticated");
                handler->authFailed = TRUE;
                
                _SendAuthResponse(handler, auth_response, response_len);
                return PRT_RETURN_FALSE;
            }
        }
        else
        {
            /* Verify if user is in cache already */
            if (0 != CredCache_CheckUser(headers->username, headers->password))
            {
                trace_AskServerToAuthenticate();

                // Stop selector processing of this socket
                handler->handler.mask &= ~SELECTOR_READ;

                if (0 != AskServerToAuthenticate(headers->username, 
                                                 headers->password, 
                                                 (MI_Uint64)(uintptr_t)handler,
                                                 _ServerAuthenticateCallback))
                {
                    handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
                    auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
                    response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

                    trace_HTTP_UserAuthFailed("failed to ask server to authenticate");
                    handler->authFailed = TRUE;

                    _SendAuthResponse(handler, auth_response, response_len);
                    return PRT_RETURN_FALSE;
                }
                return PRT_CONTINUE;
            }
        }

        if (0 != LookupUser(headers->username, &handler->authInfo.uid, &handler->authInfo.gid))
        {
            trace_GetUserUidGid_Failed(headers->username);

            handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
            auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
            response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

            trace_HTTP_UserAuthFailed("basic auth user creds not present");
            handler->authFailed = TRUE;
            _SendAuthResponse(handler, auth_response, response_len);
            return PRT_RETURN_FALSE;
        }

        if (1 != IsUserAuthorized(headers->username, handler->authInfo.gid))
        {
            trace_Authorization_Failed(headers->username);
        
            handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
            auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
            response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

            trace_HTTP_UserAuthFailed("basic auth user authorization failed");
            handler->authFailed = TRUE;
            _SendAuthResponse(handler, auth_response, response_len);
            goto Done;
        }

        handler->httpErrorCode = 0; // Let the request do the error code
        handler->isAuthorised = TRUE;
        return PRT_RETURN_TRUE;
    }
#ifdef AUTHORIZATION
    else
    {
        const gss_OID_desc mechset_avail_elems[] = {
            { 6, "\053\006\001\005\005\002" },                  // Spnego
            { 10, "\x2b\x06\x01\x04\x01\x82\x37\x02\x02\x0a" }, // ntlm
            { 9, "\052\206\110\206\367\022\001\002\002" },      // krb5
            { 6, "\053\006\001\005\002\005" } // mech_iakerb
        };
        const gss_OID_set_desc mechset_avail = { 4, (gss_OID) mechset_avail_elems };

        const gss_OID_desc mechset_krb5_elems[] = {
            { 9, "\052\206\110\206\367\022\001\002\002" },      // krb5
            { 6, "\053\006\001\005\002\005" }                   // mech_iakerb
        };

        const gss_OID_set_desc mechset_krb5 = { 2, (gss_OID) mechset_krb5_elems };

        OM_uint32 maj_stat, min_stat;
        gss_ctx_id_t context_hdl = GSS_C_NO_CONTEXT;
        gss_buffer_desc input_token, output_token;
        gss_OID_set mechset = NULL;

        // Ensure the GSS lib is loaded

        if (!Once_Invoke(&g_once_state, _GssInitLibrary, NULL))
        {
            trace_HTTP_LoadGssFailed("");
            return PRT_RETURN_FALSE;
        }

        if (handler->pAuthContext)
        {
            context_hdl = (gss_ctx_id_t) handler->pAuthContext;
        }

        if (Strncasecmp(headers->authorization, AUTHENTICATION_NEGOTIATE, AUTHENTICATION_NEGOTIATE_LENGTH) == 0)
        {
            // OM_uint32 flags = GSS_C_REPLAY_FLAG | GSS_C_SEQUENCE_FLAG | GSS_C_MUTUAL_FLAG;
            // gss_OID mech_type;

            protocol_p = AUTHENTICATION_NEGOTIATE;
            handler->httpAuthType = AUTH_METHOD_NEGOTIATE;
            mechset = (gss_OID_set) & mechset_avail;

        }
        else if (Strncasecmp(headers->authorization, AUTHENTICATION_KERBEROS, AUTHENTICATION_KERBEROS_LENGTH) == 0)
        {
            // OM_uint32 flags = GSS_C_REPLAY_FLAG | GSS_C_SEQUENCE_FLAG | GSS_C_MUTUAL_FLAG;
            // gss_OID mech_type;

            protocol_p = AUTHENTICATION_KERBEROS;
            handler->httpAuthType = AUTH_METHOD_KERBEROS;
            mechset = (gss_OID_set) & mechset_krb5;
        }
        else
        {
            trace_Wsman_UnsupportedAuthentication(headers->authorization);
            handler->httpErrorCode = HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR;
            auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
            response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

            handler->authFailed = TRUE;

            _SendAuthResponse(handler, auth_response, response_len);
            return PRT_RETURN_FALSE;
        }

        if (_getInputToken(handler, headers->authorization, &input_token) != 0)
        {
            trace_HTTP_InvalidAuthToken();
            handler->httpErrorCode = HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR;
            auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
            response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

            handler->authFailed = TRUE;

            _SendAuthResponse(handler, auth_response, response_len);
            return PRT_RETURN_FALSE;
        }

        if (handler->httpErrorCode == 0)
        {
            gss_cred_id_t verifier_cred_handle = GSS_C_NO_CREDENTIAL;

            /* Get acceptor cred for principal. */
            maj_stat = (*_g_gssState.Gss_Acquire_Cred)(&min_stat, GSS_C_NO_NAME, GSS_C_INDEFINITE, mechset, GSS_C_ACCEPT, &verifier_cred_handle, NULL, NULL); // Name needs to not be null?
            if (_check_gsserr("gss_acquire_cred(acceptor) ", maj_stat, min_stat))
            {
                handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
                auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
                response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

                handler->authFailed = TRUE;

                _SendAuthResponse(handler, auth_response, response_len);
                return PRT_RETURN_FALSE;
            }
            else 
            {
                handler->pVerifierCred = (void*)verifier_cred_handle;
            }   
        }
        // (void)DecodeToken(&input_token);
        maj_stat = (*_g_gssState.Gss_Accept_Sec_Context)(&min_stat,    // ok
                                          &context_hdl, // ok
                                          (gss_cred_id_t)handler->pVerifierCred,  // acceptor_cred_handle
                                          &input_token, // Base64 decoded the SPNEGO token
                                          GSS_C_NO_CHANNEL_BINDINGS,    //input_channel_bindings (more security?)
                                          NULL, // client_name / src_name
                                          NULL, // mech_type optional Security mechanism used
                                          &output_token,    // ok
                                          &flags,   // flags are retained in the handler for the use of gss_wrap and gss_unwrap
                                          NULL, // time_rec number of seconds for which the context will remain valid
                                          NULL);    // deleg_cred

        handler->pAuthContext = context_hdl;

        PAL_Free(input_token.value);

        if (maj_stat == GSS_S_COMPLETE)
        {
            /* We are authenticated, now need to be authorised */

            trace_HTTP_AuthComplete();
            traceSupplementaryInfo(maj_stat);

            gss_buffer_t user_name = _getPrincipalName(context_hdl);
#define MAX_HOSTNAME_LEN 256
            static char hostname[MAX_HOSTNAME_LEN] = { 0 };
            char *username = (char *)user_name->value;

            int ret = gethostname(hostname, MAX_HOSTNAME_LEN);
            if (ret == 0)
            {
                if (Strncasecmp(hostname, (char *)username, strlen(hostname)) == 0)
                {

                    // If the domain is this machine, we can strip the domain name and do a local lookup

                    char *p = memchr(user_name->value, '\\',
                                     user_name->length);
                    if (p)
                    {
                        username = ++p;
                    }
                }
            }

            if (0 != LookupUser(username, &handler->authInfo.uid, &handler->authInfo.gid))
            {

                // After all that, it would be weird for this to fail, but it is possible
                // on a misconfigured system. either way, if its not there its not there.

                trace_GetUserUidGid_Failed(headers->username);

                handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
                handler->authFailed = TRUE;
                auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
                response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

                _SendAuthResponse(handler, auth_response, response_len);

                (* _g_gssState.Gss_Delete_Sec_Context)(&min_stat, &context_hdl, NULL);

                handler->pAuthContext = NULL;
                handler->authFailed   = TRUE;

                if (handler->pVerifierCred)
                {    
                    (* _g_gssState.Gss_Release_Cred)(&min_stat, handler->pVerifierCred);
                    handler->pVerifierCred = NULL;
                }

                (* _g_gssState.Gss_Release_Buffer)(&min_stat, user_name);
                PAL_Free(user_name);

                goto Done;
            }
            else 
            {
                if (1 != IsUserAuthorized(username, handler->authInfo.gid))
                {
                    trace_Authorization_Failed(username);
                    
                    handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
                    auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
                    response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

                    trace_HTTP_UserAuthFailed("NTLM/Kerberos user authorization failed");
                    handler->authFailed = TRUE;
                    _SendAuthResponse(handler, auth_response, response_len);

                    (* _g_gssState.Gss_Delete_Sec_Context)(&min_stat, &context_hdl, NULL);

                    handler->pAuthContext = NULL;

                    if (handler->pVerifierCred)
                    {    
                        (* _g_gssState.Gss_Release_Cred)(&min_stat, handler->pVerifierCred);
                        handler->pVerifierCred = NULL;
                    }

                    (* _g_gssState.Gss_Release_Buffer)(&min_stat, user_name);
                    PAL_Free(user_name);

                    goto Done;
                }
                
                (* _g_gssState.Gss_Release_Buffer)(&min_stat, user_name);
                handler->negFlags = flags;

                PAL_Free(user_name);

                handler->isAuthorised = TRUE;
                if (headers->contentLength == 0)
                {
                    // Apparently we were just authorising the connection so far and the request is 
                    //  yet to come. Treat this in the same way as a continue except succeed
                    
                    handler->httpErrorCode = HTTP_ERROR_CODE_OK;
                    if (output_token.length != 0)
                    {
                        auth_response = _BuildAuthResponse(protocol_p, handler->httpErrorCode, &output_token, &response_len);
                        if (auth_response == NULL)
                        {
                            trace_HTTP_CannotBuildAuthResponse();
                            handler->httpErrorCode = HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR;
                        }
                        (*_g_gssState.Gss_Release_Buffer)(&min_stat, &output_token);
        
                        _SendAuthResponse(handler, auth_response, response_len);
                        PAL_Free(auth_response);
                    }
                    else 
                    {
                        // If we are doing a key exchange we send our key back after success

                        if (output_token.length > 0 )
                        {
                            auth_response = _BuildAuthResponse(protocol_p, handler->httpErrorCode, &output_token, &response_len);
                            if (auth_response == NULL)
                            {
                                trace_HTTP_CannotBuildAuthResponse();
                                handler->httpErrorCode = HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR;
                            }
                            (*_g_gssState.Gss_Release_Buffer)(&min_stat, &output_token);
                            _SendAuthResponse(handler, auth_response, response_len);
                            PAL_Free(auth_response);
                        }
                        else 
                        {
                            auth_response = (char *)RESPONSE_HEADER_AUTHORIZED;
                            response_len  = RESPONSE_HEADER_AUTHORIZED_LEN;
                            _SendAuthResponse(handler, auth_response, response_len);
                        }
                    }
                    return PRT_RETURN_FALSE;
                }
                else
                {
                    handler->httpErrorCode = 0; // We let the transaction set the error code
                    if (output_token.length > 0 )
                    {
                        handler->pSendAuthHeader = _BuildAuthResponse(protocol_p, 
                                                                      handler->httpErrorCode, &output_token,
                                                                      &handler->sendAuthHeaderLen);
                        if (handler->pSendAuthHeader == NULL)
                        {
                            trace_HTTP_CannotBuildAuthResponse();
                            handler->httpErrorCode = HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR;
                        }
                        (*_g_gssState.Gss_Release_Buffer)(&min_stat, &output_token);
                    }
                    return PRT_RETURN_TRUE;
                }
            }
        }
        else if (GSS_ERROR(maj_stat))
        {
            trace_HTTP_ClientAuthFailed(_StatusString(maj_stat), _StatusString(min_stat));

            if (GSS_ERROR(maj_stat) == GSS_S_NO_CRED ||
                GSS_ERROR(maj_stat) == GSS_S_FAILURE || GSS_ERROR(maj_stat) == GSS_S_UNAUTHORIZED)
            {

                // Unauthorised

                handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
                auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
                response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

                // Problem : 2do complain
                handler->authFailed = TRUE;

            }
            else
            {
                handler->httpErrorCode = HTTP_ERROR_CODE_BAD_REQUEST;
                auth_response = (char *)RESPONSE_HEADER_BAD_REQUEST;
                response_len  = RESPONSE_HEADER_BAD_REQUEST_LEN;
            }

            _SendAuthResponse(handler, auth_response, response_len);
            (* _g_gssState.Gss_Release_Buffer)(&min_stat, &output_token);
            return PRT_RETURN_FALSE;
        }
        else if (maj_stat & GSS_S_CONTINUE_NEEDED)
        {
            trace_HTTP_AuthContinue();
            handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
            if (output_token.length != 0)
            {
                auth_response = _BuildAuthResponse(protocol_p, handler->httpErrorCode, &output_token, &response_len);
                if (auth_response == NULL)
                {

                    // Problem : 2do complain into trace file
                    handler->httpErrorCode = HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR;
                }
                (*_g_gssState.Gss_Release_Buffer)(&min_stat, &output_token);

                _SendAuthResponse(handler, auth_response, response_len);
                PAL_Free(auth_response);
                return PRT_RETURN_FALSE;
            }
            else
            {

                gss_buffer_t user_name = _getPrincipalName(context_hdl);
#define MAX_HOSTNAME_LEN 256
                static char hostname[MAX_HOSTNAME_LEN] = { 0 };
                char *username = (char *)user_name->value;

                int ret = gethostname(hostname, MAX_HOSTNAME_LEN);
                if (ret == 0)
                {
                    if (Strncasecmp(hostname, (char *)username, strlen(hostname)) == 0)
                    {

                        // If the domain is this machine, we can strip the domain name and do a local lookup

                        char *p = memchr(user_name->value,
                                         '\\',
                                         user_name->length);
                        if (p)
                        {
                            username = ++p;
                        }
                    }
                }

                if (0 != LookupUser(username, &handler->authInfo.uid, &handler->authInfo.gid))
                {

                    // After all that, it would be weird for this to fail, but it is possible
                    // on a misconfigured system. either way, if its not there its not there.

                    trace_GetUserUidGid_Failed(headers->username);

                    handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
                    handler->authFailed = TRUE;
                    auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
                    response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

                    _SendAuthResponse(handler, auth_response, response_len);
                    (*_g_gssState.Gss_Delete_Sec_Context)(&min_stat, &context_hdl, NULL);

                    handler->pAuthContext = NULL;
                    handler->authFailed = TRUE;

                    (* _g_gssState.Gss_Release_Cred)(&min_stat, handler->pVerifierCred);
                    handler->pVerifierCred = NULL;

                    (* _g_gssState.Gss_Release_Buffer)(&min_stat, user_name);
                    goto Done;
                }

                if (1 != IsUserAuthorized(username, handler->authInfo.gid))
                {
                    trace_Authorization_Failed(username);
                    
                    handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
                    auth_response = (char *)RESPONSE_HEADER_UNAUTH_FMT;
                    response_len  = RESPONSE_HEADER_UNAUTH_FMT_LEN;

                    trace_HTTP_UserAuthFailed("NTLM/Kerberos user authorization failed (2)");
                    handler->authFailed = TRUE;
                    _SendAuthResponse(handler, auth_response, response_len);
                    (*_g_gssState.Gss_Delete_Sec_Context)(&min_stat, &context_hdl, NULL);
                    
                    handler->pAuthContext = NULL;
                    
                    (* _g_gssState.Gss_Release_Cred)(&min_stat, handler->pVerifierCred);
                    handler->pVerifierCred = NULL;

                    (* _g_gssState.Gss_Release_Buffer)(&min_stat, user_name);
                    goto Done;
                }

                (* _g_gssState.Gss_Release_Buffer)(&min_stat, user_name);

                handler->httpErrorCode = 0; // We let the transaction set the error code
                handler->isAuthorised = TRUE;
                return PRT_RETURN_TRUE;
            }
        }
    }
#endif

  Done:
    return authorised;
}


void HttpAuth_Close(_In_ Handler *handlerIn)
{
   Http_SR_SocketData* handler = FromOffset( Http_SR_SocketData, handler, handlerIn );
   gss_ctx_id_t context_hdl = handler->pAuthContext;
   OM_uint32 min_stat = 0;

   if(handlerIn)
   {
       if (_g_gssState.Gss_Release_Cred && handler->pVerifierCred )
       {
             (*_g_gssState.Gss_Release_Cred)(&min_stat, handler->pVerifierCred);
             handler->pVerifierCred = NULL;
       }

       if (_g_gssState.Gss_Delete_Sec_Context && context_hdl) 
       {
           handler->pAuthContext = NULL;
           (*_g_gssState.Gss_Delete_Sec_Context)(&min_stat, &context_hdl, NULL);
       }
   }
}

MI_Result Process_Authorized_Message(
    Http_SR_SocketData* handler)
{
    HttpRequestMsg* msg;

#if ENCRYPT_DECRYPT
    if (!Http_DecryptData(handler, &handler->recvHeaders, &handler->recvPage) )
    {
        // Failed decrypt. No encryption counts as success. So this is an error in the decrpytion, probably
        // bad credential

        return MI_RESULT_FAILED;
    }
    else
    {
        if (FORCE_TRACING || handler->enableTracing)
        {
            char startTime[TIMESTAMP_SIZE]={'\0'};
            GetTimeStamp(startTime);
            char after_decrypt[] = "\n------------ After Decryption ---------------\n";
            char after_decrypt_end[] = "\n-------------- End Decrypt ------------------\n";
            _WriteTraceFile(ID_HTTPRECVTRACEFILE, &startTime, strlen(startTime));
            _WriteTraceFile(ID_HTTPRECVTRACEFILE, &after_decrypt, sizeof(after_decrypt));
            _WriteTraceFile(ID_HTTPRECVTRACEFILE, (char *)(handler->recvPage+1), handler->recvPage->u.s.size);
            _WriteTraceFile(ID_HTTPRECVTRACEFILE, &after_decrypt_end, sizeof(after_decrypt_end));
        }
    }
#endif

    AuthInfo_Copy(&handler->recvHeaders.authInfo, &handler->authInfo);
    msg = HttpRequestMsg_New(handler->recvPage, &handler->recvHeaders);

    if( NULL == msg )
    {
        trace_HTTP_RequestAllocFailed( handler );

        if (handler->recvPage)
        {
            PAL_Free(handler->recvPage);
            handler->recvPage = NULL; /* clearing this out so that caller does not double-free it */
        }

        return MI_RESULT_FAILED;
    }

    handler->requestIsBeingProcessed = MI_TRUE;

    // the page will be owned by receiver of this message
    DEBUG_ASSERT( NULL == handler->request );
    handler->request = msg;
    Strand_ScheduleAux( &handler->strand, HTTPSOCKET_STRANDAUX_NEWREQUEST );

    return MI_RESULT_OK;
}
