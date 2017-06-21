/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/
#include <config.h>
#if AUTHORIZATION
#if defined(macos)
#include <GSS/GSS.h>
#else
#include <gssapi/gssapi.h>
#include <krb5.h>
#endif
#endif
#include <dlfcn.h>
#include <pal/once.h>
#include <base/base.h>
#include <base/base64.h>
#include <base/paths.h>
#include <pal/lock.h>
#include <pal/dir.h>
#include <xml/xml.h>
#include <assert.h>
#include <ctype.h>
#include "httpcommon.h"
#include "httpclient.h"
#include <sock/addr.h>
#include <sock/sock.h>
#include <sock/selector.h>

#include "httpcommon.h"

//#define GSS_USE_IOV 1

#define ENABLE_TRACING 1
#define FORCE_TRACING  1

#if GSS_USE_IOV && !defined(macos)
#include "httpkrb5.h"
#endif

#if !defined(GSS_IO_BUFFER_TYPE_PADDING)
#define GSS_IOV_BUFFER_TYPE_PADDING 9 // For the mac, this is normally in the header file
                                      // /System/Library/Frameworks/GSS.framework/Headers/gssapi.h which is included in the 
                                      // GSS framework headers directory. However, its not coming through, and when it is included
                                      // directly, there are a large number of duplicate declarations. Its one number, and its
                                      //  not going to change so I just define it here. For linux, it is located in /usr/include/gssapi/gssapi_ext.h
                                      //  which we don't include because it isn't present on some platforms.  Same logic
#endif

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
#undef EWOULDBLOCK
#endif

#define EWOULDBLOCK 0

#ifdef EINPROGRESS
#undef EINPROGRESS
#endif

#define EINPROGRESS 0

#define ERR_get_error() 0
#define ERR_error_string_n(c,a,b) a[0]=0
#define SSL_accept(c) 0
#define SSL_connect(c) 0

#endif


#if !defined(KRB5_CALLCOV)
#define KRB5_CALLCONV
#endif


#ifdef ENABLE_TRACING
# define TRACING_LEVEL 4
#include <base/log.h>
#endif


#define HTTP_LONGEST_ERROR_DESCRIPTION 50

#include "httpclient_private.h"

// dlsyms from the dlopen. These entry points are very useful, but not always supported 
// in every platform. So we dynamically load them as use them as available.

typedef OM_uint32 KRB5_CALLCONV (*Gss_Acquire_Cred_With_Password_Func )(
                             OM_uint32 *,        /* minor_status */
                             const gss_name_t,   /* desired_name */
                             const gss_buffer_t, /* password */
                             OM_uint32,          /* time_req */
                             const gss_OID_set,  /* desired_mechs */
                             gss_cred_usage_t,   /* cred_usage */
                             gss_cred_id_t *,    /* output_cred_handle */
                             gss_OID_set *,      /* actual_mechs */
                             OM_uint32 *);       /* time_rec */

typedef OM_uint32 KRB5_CALLCONV (*Gss_Set_Neg_Mechs_Func)(
                             OM_uint32 *,        /* minor_status */
                             gss_cred_id_t,      /* cred_handle */
                             const gss_OID_set); /* mech_set */

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

typedef OM_uint32 KRB5_CALLCONV (*Gss_Inquire_Cred_Func)(OM_uint32 * minor_status,
                                      const gss_cred_id_t cred_handle,
                                      gss_name_t * name,
                                      OM_uint32  * lifetime_rec,
                                      gss_cred_usage_t * cred_usage,  
                                      gss_OID_set      * mechanisms); 

typedef OM_uint32 KRB5_CALLCONV (*Gss_Release_Buffer_Func)(OM_uint32 * minor_status, gss_buffer_t buffer);
typedef OM_uint32 KRB5_CALLCONV (*Gss_Release_Cred_Func)(OM_uint32 * minor_status, gss_cred_id_t * cred_handle);
typedef OM_uint32 KRB5_CALLCONV (*Gss_Release_Name_Func)(OM_uint32 * minor_status, gss_name_t * name);

#if GSS_USE_IOV
typedef OM_uint32 KRB5_CALLCONV (*Gss_Unwrap_Func_Iov)(OM_uint32 * minor_status,
                            const gss_ctx_id_t context_handle,
                            const gss_buffer_t input_message_buffer,
                            int *conf_state, gss_qop_t * qop_state,
                            gss_iov_buffer_desc *iov, int iov_cnt );

typedef OM_uint32 KRB5_CALLCONV (*Gss_Wrap_Func_Iov)(OM_uint32 * minor_status,
                            const gss_ctx_id_t context_handle,
                            int conf_req_flag,
                            gss_qop_t qop_req,
                            int *conf_state,
                            gss_iov_buffer_desc *iov, int iov_cnt );

typedef OM_uint32 KRB5_CALLCONV (*Gss_Release_Iov_Buffer_Func)(OM_uint32 * minor_status, gss_iov_buffer_desc *iov, int iov_cnt );

#endif

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

#if !defined(macos)
typedef krb5_error_code KRB5_CALLCONV
(*krb5InitContextFn)(krb5_context *context);

typedef krb5_error_code KRB5_CALLCONV
(*krb5ParseNameFn)(krb5_context context, const char *name,
                krb5_principal *principal_out);

typedef krb5_error_code KRB5_CALLCONV
(*krb5GetInitCredsPasswordFn)(krb5_context context, krb5_creds *creds,
                             krb5_principal client, const char *password,
                             /*krb5_prompter_fct*/ void * prompter, void *data, // Mac deprecates krb5_prompter_fct for some reason
                             krb5_deltat start_time,
                             const char *in_tkt_service,
                             krb5_get_init_creds_opt *k5_gic_options);

typedef krb5_error_code KRB5_CALLCONV
(*krb5VerifyInitCredsFn)(krb5_context context, krb5_creds *creds,
                       krb5_principal server, krb5_keytab keytab,
                       krb5_ccache *ccache,
                       krb5_verify_init_creds_opt *options);

typedef void KRB5_CALLCONV
(*krb5FreePrincipalFn)(krb5_context context, krb5_principal val);

typedef void KRB5_CALLCONV
(*krb5FreeCredContentsFn)(krb5_context context, krb5_creds *val);
#endif

typedef enum { NOT_LOADED = 0, LOADING, LOADED } LoadState;

typedef struct _Gss_Extensions 
{
    LoadState gssLibLoaded;  /* Default is NOT_LOADED */
    void *libHandle;

    /* Optional entry points */
    Gss_Acquire_Cred_With_Password_Func gssAcquireCredwithPassword;
    Gss_Set_Neg_Mechs_Func              gssSetNegMechs;
    /* Mandatory entry points */
    Gss_Accept_Sec_Context_Func Gss_Accept_Sec_Context;
    Gss_Acquire_Cred_Func       Gss_Acquire_Cred;
    Gss_Delete_Sec_Context_Func Gss_Delete_Sec_Context;
    Gss_Display_Name_Func       Gss_Display_Name;
    Gss_Display_Status_Func     Gss_Display_Status;
    Gss_Import_Name_Func        Gss_Import_Name;
    Gss_Init_Sec_Context_Func   Gss_Init_Sec_Context;
    Gss_Inquire_Context_Func    Gss_Inquire_Context;
    Gss_Inquire_Cred_Func       Gss_Inquire_Cred;
    Gss_Release_Buffer_Func     Gss_Release_Buffer;
    Gss_Release_Cred_Func       Gss_Release_Cred;
    Gss_Release_Name_Func       Gss_Release_Name;
    Gss_Unwrap_Func             Gss_Unwrap;
    Gss_Wrap_Func               Gss_Wrap;
#if GSS_USE_IOV
    Gss_Unwrap_Func_Iov         Gss_Unwrap_Iov;
    Gss_Wrap_Func_Iov           Gss_Wrap_Iov;
    Gss_Release_Iov_Buffer_Func Gss_Release_Iov_Buffer;
#endif

    gss_OID Gss_Nt_Service_Name;
    gss_OID Gss_Nt_HostBased_Service_Name;
    gss_OID Gss_Krb5_Nt_Principal_Name;
    gss_OID Gss_C_Nt_User_Name;

#if !defined(macos)
    krb5InitContextFn          krb5InitContext;
    krb5ParseNameFn            krb5ParseName;
    krb5GetInitCredsPasswordFn krb5GetInitCredsPassword;
    krb5VerifyInitCredsFn      krb5VerifyInitCreds;
    krb5FreePrincipalFn        krb5FreePrincipal;
    krb5FreeCredContentsFn     krb5FreeCredContents;
#endif
} Gss_Extensions;

static Gss_Extensions _g_gssClientState = { 0 };
static struct _Once    g_once_state = ONCE_INITIALIZER;

static const char GSS_LIBRARY_NAME[] = CONFIG_GSSLIB;
static const char KRB5_LIBRARY_NAME[] = CONFIG_KRB5LIB;


MI_Boolean Gss_Oid_Equal(const gss_OID poid1, const gss_OID poid2) 

{
    if (poid1->length != poid2->length)
    { 
        return MI_FALSE;
    }

    if (memcmp(poid1->elements, poid2->elements, poid1->length) != 0)
    {
        return MI_FALSE;
    }

    return MI_TRUE;
}

/*
 * Credentials are expected to live in the file ~/.omi/ntlmcred.
 * If the environment variable NTLM_USER_FILE is set, it is respected.
 * If not, the environment variable is set internally
 * Either way, the directory the creds file is in must be user-only
 *
 * So: NTLM_USER_FILE is set? -> we use the file specified by it if the permissions are right.
 *                   not set? -> we use ~/.omi/ntlmcred if the permissions are right.
 *
 * If neither condition is true, error
 */

static
_Success_(return == 0) int _ValidateClientCredentials(HttpClient_SR_SocketData *context)
{
   HttpClient* client = (HttpClient*)context->base.data;
   char *ntlm_user_file = getenv("NTLM_USER_FILE");
   char *cred_dir       = NULL;
   char *cred_file_path = NULL;

   static Probable_Cause_Data AUTH_ERROR_CRED_DIR = {
              ERROR_ACCESS_DENIED,
              WSMAN_CIMERROR_PROBABLE_CAUSE_AUTHENTICATION_FAILURE,
              MI_T("credentials directory ~/.omi cannot be opened"),
              NULL
       };

   static Probable_Cause_Data AUTH_ERROR_CRED_FILE = {
              ERROR_ACCESS_DENIED,
              WSMAN_CIMERROR_PROBABLE_CAUSE_AUTHENTICATION_FAILURE,
              MI_T("credentials file and directory does not exist"),
              NULL 
       };

   static Probable_Cause_Data AUTH_ERROR_CRED_DIR_PERMS = {
              ERROR_ACCESS_DENIED,
              WSMAN_CIMERROR_PROBABLE_CAUSE_AUTHENTICATION_FAILURE,
              MI_T("credentials file directory permissions must be user-only"),
              NULL 
       };

   static Probable_Cause_Data AUTH_ERROR_CRED_FILE_PERMS = {
              ERROR_ACCESS_DENIED,
              WSMAN_CIMERROR_PROBABLE_CAUSE_AUTHENTICATION_FAILURE,
              MI_T("credentials file permissions must be user-only"),
              NULL 
       };

   static Probable_Cause_Data OUT_OF_MEMORY_ERROR = {
              ERROR_INTERNAL_ERROR,
              WSMAN_CIMERROR_SERVER_LIMITS_EXCEEDED,
              MI_T("out of memory"),
              NULL 
       };



    switch(context->authType)
    {
    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
        break;

    default:
        return 0;
    }

    if (!ntlm_user_file)
    {
        const static char OMI_DIR_NAME[] = "/.omi";
        const static int  OMI_DIR_NAME_LEN = (sizeof(OMI_DIR_NAME)-1)/sizeof(char);  // the division is a noop, but present if we ever use wide chars
        const static char NTLM_CRED_FILE_NAME[] = "/ntlmcred";
        const static int  NTLM_CRED_FILE_NAME_LEN = (sizeof(NTLM_CRED_FILE_NAME)-1)/sizeof(char);

        const char *home_dir = GetHomeDir(); // GetHomeDir mallocs the info
        if (!home_dir)
        {
            // When would this happen???
            // Anyway, it will fail if it does
            trace_getHomeDir_Failed();
            return -1;
        }

        int  homedir_len = strlen(home_dir);

        cred_dir  = PAL_Malloc(homedir_len+OMI_DIR_NAME_LEN+1);
        if (!cred_dir)
        {
            PAL_Free((void*)home_dir);
            client->probableCause = &OUT_OF_MEMORY_ERROR;
            goto Err;
        }
        
        {
            char *pstr = cred_dir;
            strcpy(pstr, home_dir);
            pstr += homedir_len;
            strcpy(pstr, OMI_DIR_NAME);
        }
        PAL_Free((void*)home_dir);

        cred_file_path = PAL_Malloc(homedir_len+OMI_DIR_NAME_LEN+NTLM_CRED_FILE_NAME_LEN+1);
        if (!cred_file_path)
        {
            client->probableCause = &OUT_OF_MEMORY_ERROR;
            goto Err;
        }
        
        {
            char *pstr = cred_file_path;
            strcpy(pstr, cred_dir);
            pstr += strlen(cred_dir);
            strcpy(pstr, NTLM_CRED_FILE_NAME);
        }
    }
    else
    {
        cred_file_path = PAL_Strdup(ntlm_user_file);
        if (!cred_file_path)
        {
            client->probableCause = &OUT_OF_MEMORY_ERROR;
            goto Err;
        }

        cred_dir = PAL_Strdup(ntlm_user_file);
        if (!cred_dir)
        {
            client->probableCause = &OUT_OF_MEMORY_ERROR;
            goto Err;
        }

        char* p = strrchr(cred_dir, '/');
        if (p)
        {
            *p = '\0';
        }

    }
     
    // Check to see the file exists and has the right permissions 
        
    {
        struct stat buf = {0};
        int rtn = stat(cred_file_path, &buf);

        if (rtn < 0)
        {
           if (ntlm_user_file)
           {
               // If we said it exists via the env variable it needs to be there.
               
               client->probableCause = &AUTH_ERROR_CRED_DIR;
               goto Err;
           }
           else 
           {
               // If we never said it was there and there is no ~/.omi/ntlmcred file,
               // then the creds come from winbind. Thats fine. 
               //
               PAL_Free(cred_file_path);
               PAL_Free(cred_dir);
               return 0;
           }
        }

        if (S_ISDIR(buf.st_mode) || S_ISLNK(buf.st_mode))
        {
           // Not a file? Unlikely, but complain and issue error
            client->probableCause = &AUTH_ERROR_CRED_FILE;
            goto Err;
        }

        // Acceptable dir will be user only, no others
        if (!(buf.st_mode & S_IRUSR) || ( buf.st_mode & (S_IRWXG|S_IRWXO)))
        {
            client->probableCause = &AUTH_ERROR_CRED_FILE_PERMS;
            goto Err;
        }
    }

    // Check the permissions on the directory. They need to be read-only owner
        
    {
        struct stat buf = {0};

        int rtn = stat(cred_dir, &buf);
        if (rtn < 0)
        {
            client->probableCause = &AUTH_ERROR_CRED_FILE;
            goto Err;
        }

        if (!S_ISDIR(buf.st_mode))
        {
           // Not a directory? Unlikely, but complain and issue error
            client->probableCause = &AUTH_ERROR_CRED_FILE;
            goto Err;
        }

        // Acceptable dir will be user only, no others
        if (!(buf.st_mode & S_IRUSR) || ( buf.st_mode & (S_IRWXG|S_IRWXO)))
        {
            client->probableCause = &AUTH_ERROR_CRED_DIR_PERMS;
            goto Err;
        }
    }        

    setenv("NTLM_USER_FILE", cred_file_path, 1);

    PAL_Free(cred_file_path);
    PAL_Free(cred_dir);
    return 0;

Err: 

    trace_NtlmCredFileInvalid(cred_file_path);

    // Return probable cause in the context
    if (cred_file_path && cred_file_path != ntlm_user_file ) 
    {
        PAL_Free(cred_file_path);
    }

    if (cred_dir)
    {
        PAL_Free(cred_dir);
    }

    return -1;
}


static void
_GssUnloadLibrary()

{
    dlclose(_g_gssClientState.libHandle);
    _g_gssClientState.libHandle = NULL;
    _g_gssClientState.gssSetNegMechs = NULL;
    _g_gssClientState.gssAcquireCredwithPassword = NULL;
    _g_gssClientState.gssLibLoaded = NOT_LOADED;

}

static _Success_(return == 0) int _GssClientInitLibrary( _In_ void* data, _Outptr_result_maybenull_ void** value)

{

    HttpClient_SR_SocketData *context = (HttpClient_SR_SocketData *)data;

#if HEIMDAL
    static const char *GSS_NT_USER_NAME_REF    = "__gss_c_nt_user_name_oid_desc";
    static const char *GSS_NT_SERVICE_NAME_REF = "__gss_c_nt_hostbased_service_oid_desc";
#else
    static const char *GSS_NT_USER_NAME_REF    = "gss_nt_user_name";
    static const char *GSS_NT_SERVICE_NAME_REF = "gss_nt_service_name_v2";
#endif


   // Reserve the state to prevent race conditions

   if (_g_gssClientState.gssLibLoaded != NOT_LOADED)
   {
       return TRUE;
   }
   _g_gssClientState.gssLibLoaded = LOADING;

#ifdef aix
   void *libhandle =  dlopen(GSS_LIBRARY_NAME, RTLD_NOW | RTLD_MEMBER);
#else
   void *libhandle =  dlopen(GSS_LIBRARY_NAME, RTLD_NOW | RTLD_GLOBAL);
#endif
   void *fn_handle = NULL;

   trace_HTTP_LoadingGssApi(CONFIG_GSSLIB);

   if (libhandle)
   {
       fn_handle = dlsym(libhandle, "gss_acquire_cred_with_password" );

       if (!fn_handle)
       {
           // Log a warning
       }
       _g_gssClientState.gssAcquireCredwithPassword = ( Gss_Acquire_Cred_With_Password_Func )fn_handle;

       fn_handle = dlsym(libhandle, "gss_set_neg_mechs" );

       if (!fn_handle)
       {
           // Log a warning
       }

       _g_gssClientState.gssSetNegMechs  = ( Gss_Set_Neg_Mechs_Func )fn_handle;


        fn_handle = dlsym(libhandle, "gss_accept_sec_context");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_accept_sec_context");
            goto failed;
        }
        _g_gssClientState.Gss_Accept_Sec_Context = (Gss_Accept_Sec_Context_Func)fn_handle;


        fn_handle = dlsym(libhandle, "gss_acquire_cred");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_acquire_cred");
            goto failed;
        }
        _g_gssClientState.Gss_Acquire_Cred = (Gss_Acquire_Cred_Func)fn_handle;

        fn_handle = dlsym(libhandle, "gss_delete_sec_context");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_delete_sec_context");
            goto failed;
        }
        _g_gssClientState.Gss_Delete_Sec_Context = (Gss_Delete_Sec_Context_Func)fn_handle;

        fn_handle = dlsym(libhandle, "gss_display_name");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_display_name");
            goto failed;
        }
        _g_gssClientState.Gss_Display_Name = (Gss_Display_Name_Func)fn_handle;

        fn_handle = dlsym(libhandle, "gss_display_status");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_display_status");
            goto failed;
        }
        _g_gssClientState.Gss_Display_Status = (Gss_Display_Status_Func)fn_handle;

        fn_handle = dlsym(libhandle, "gss_import_name");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_import_name");
            goto failed;
        }
        _g_gssClientState.Gss_Import_Name = (Gss_Import_Name_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_init_sec_context");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_init_sec_context");
            goto failed;
        }
        _g_gssClientState.Gss_Init_Sec_Context = (Gss_Init_Sec_Context_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_inquire_context");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_inquire_context");
            goto failed;
        }
        _g_gssClientState.Gss_Inquire_Context  = (Gss_Inquire_Context_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_inquire_cred");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_inquire_cred");
            goto failed;
        }
        _g_gssClientState.Gss_Inquire_Cred  = (Gss_Inquire_Cred_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_release_buffer");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_release_buffer");
            goto failed;
        }
        _g_gssClientState.Gss_Release_Buffer = (Gss_Release_Buffer_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_release_cred");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_release_cred");
            goto failed;
        }
        _g_gssClientState.Gss_Release_Cred = (Gss_Release_Cred_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_release_name");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_release_name");
            goto failed;
        }
        _g_gssClientState.Gss_Release_Name = (Gss_Release_Name_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_unwrap");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_unwrap");
            goto failed;
        }
        _g_gssClientState.Gss_Unwrap = (Gss_Unwrap_Func) fn_handle;

        fn_handle = dlsym(libhandle, "gss_wrap");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_wrap");
            goto failed;
        }
        _g_gssClientState.Gss_Wrap   = (Gss_Wrap_Func) fn_handle;

#if GSS_USE_IOV
#if defined(macos)
        fn_handle = dlsym(libhandle, "__ApplePrivate_gss_unwrap_iov");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_unwrap_iov");
        }
        _g_gssClientState.Gss_Unwrap_Iov = (Gss_Unwrap_Func_Iov) fn_handle;

        fn_handle = dlsym(libhandle, "__ApplePrivate_gss_wrap_iov");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_wrap_iov");
        }
        _g_gssClientState.Gss_Wrap_Iov = (Gss_Wrap_Func_Iov) fn_handle;

        fn_handle = dlsym(libhandle, "__ApplePrivate_gss_release_iov_buffer");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_release_iov_buffer");
        }
        _g_gssClientState.Gss_Release_Iov_Buffer = (Gss_Release_Iov_Buffer_Func) fn_handle;
#else
        fn_handle = dlsym(libhandle, "gss_unwrap_iov");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_unwrap_iov");
        }
        _g_gssClientState.Gss_Unwrap_Iov = (Gss_Unwrap_Func_Iov) fn_handle;

        fn_handle = dlsym(libhandle, "gss_wrap_iov");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_wrap_iov");
        }
        _g_gssClientState.Gss_Wrap_Iov = (Gss_Wrap_Func_Iov) fn_handle;

        fn_handle = dlsym(libhandle, "gss_release_iov_buffer");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("gss_release_iov_buffer");
        }
        _g_gssClientState.Gss_Release_Iov_Buffer = (Gss_Release_Iov_Buffer_Func) fn_handle;
#endif        
#endif        

        fn_handle = dlsym(libhandle, GSS_NT_SERVICE_NAME_REF);
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent(GSS_NT_SERVICE_NAME_REF);
            goto failed;
        }
#if HEIMDAL
        _g_gssClientState.Gss_Nt_Service_Name  = (gss_OID)fn_handle;
#else
        _g_gssClientState.Gss_Nt_Service_Name  = *(gss_OID*)fn_handle;
#endif

        fn_handle = dlsym(libhandle, GSS_NT_USER_NAME_REF);
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent(GSS_NT_USER_NAME_REF);
            goto failed;
        }

#if HEIMDAL
       _g_gssClientState.Gss_C_Nt_User_Name  = (gss_OID)fn_handle;
#else
       _g_gssClientState.Gss_C_Nt_User_Name  = *(gss_OID*)fn_handle;
#endif

        fn_handle = dlsym(libhandle, "GSS_C_NT_HOSTBASED_SERVICE");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("GSS_C_NT_HOSTBASED_SERVICE");
            goto failed;
        }
#if HEIMDAL
       _g_gssClientState.Gss_Nt_HostBased_Service_Name  = (gss_OID)fn_handle;
#else
       _g_gssClientState.Gss_Nt_HostBased_Service_Name  = *(gss_OID*)fn_handle;
#endif

        fn_handle = dlsym(libhandle, "GSS_KRB5_NT_PRINCIPAL_NAME");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("GSS_KRB5_NT_PRINCIPAL_NAME");
            goto failed;
        }
#if HEIMDAL
       _g_gssClientState.Gss_Krb5_Nt_Principal_Name = (gss_OID)fn_handle;
#else
       _g_gssClientState.Gss_Krb5_Nt_Principal_Name = *(gss_OID*)fn_handle;
#endif
       _g_gssClientState.libHandle    = libhandle;
       _g_gssClientState.gssLibLoaded = LOADED;
        PAL_Atexit(_GssUnloadLibrary);
      
        libhandle =  dlopen(KRB5_LIBRARY_NAME, RTLD_NOW | RTLD_GLOBAL);

        fn_handle = dlsym(libhandle, "krb5_init_context");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("krb5_init_context");
            goto failed;
        }
#if !defined(macos)
        _g_gssClientState.krb5InitContext = (krb5InitContextFn)fn_handle;

        fn_handle = dlsym(libhandle, "krb5_parse_name");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("krb5_parse_name");
            goto failed;
        }
        _g_gssClientState.krb5ParseName = (krb5ParseNameFn) fn_handle;

        fn_handle = dlsym(libhandle, "krb5_get_init_creds_password");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("krb5_get_init_creds_password");
            goto failed;
        }
        _g_gssClientState.krb5GetInitCredsPassword = (krb5GetInitCredsPasswordFn) fn_handle;

        fn_handle = dlsym(libhandle, "krb5_verify_init_creds");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("krb5_verify_init_creds");
            goto failed;
        }
        _g_gssClientState.krb5VerifyInitCreds = (krb5VerifyInitCredsFn) fn_handle;

        fn_handle = dlsym(libhandle, "krb5_free_principal");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("krb5_free_principal");
            goto failed;
        }
        _g_gssClientState.krb5FreePrincipal = (krb5FreePrincipalFn) fn_handle;

        fn_handle = dlsym(libhandle, "krb5_free_cred_contents");
        if (!fn_handle)
        {
            trace_HTTP_GssFunctionNotPresent("krb5_free_cred_contents");
            goto failed;
        }
        _g_gssClientState.krb5FreeCredContents = (krb5FreeCredContentsFn) fn_handle;
#endif

       return _ValidateClientCredentials(context) == 0;
       //return TRUE;
   }

   failed:
       trace_HTTP_LoadGssFailed("client, in dlopen" );
       _g_gssClientState.gssAcquireCredwithPassword = NULL;
       _g_gssClientState.gssSetNegMechs             = NULL;
       _g_gssClientState.libHandle                  = NULL;
       _g_gssClientState.gssLibLoaded = NOT_LOADED;
       return FALSE;
}




//#define ENCRYPT_DECRYPT 1
//#define AUTHORIZATION 1

#define MAX_ERROR_SIZE 200

void _WriteTraceFile(PathID id, const void *data, size_t size);

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

#if AUTHORIZATION

static void _getStatusMsg(OM_uint32 status_code, int status_type, gss_buffer_t statusString)
{
    OM_uint32 message_context;
    OM_uint32 min_status;

    message_context = 0;

    do {
        (*_g_gssClientState.Gss_Display_Status)(&min_status,
                           status_code, status_type, GSS_C_NO_OID, &message_context, statusString);
    } while (message_context != 0);
}

static void _ReportError(HttpClient_SR_SocketData * self, const char *msg,
                         OM_uint32 major_status, OM_uint32 minor_status)
{
    HttpClient *client = (HttpClient *) self->base.data;

    OM_uint32 min_stat = 0;

    gss_buffer_desc major_err = { 0 };
    gss_buffer_desc minor_err = { 0 };
    int  msglen = 0;
    char *pmsg = NULL;


    if (major_status != 0)
    {
        _getStatusMsg(major_status, GSS_C_GSS_CODE, &major_err);
        _getStatusMsg(minor_status, GSS_C_MECH_CODE, &minor_err);
    }

    trace_HTTP_ClientAuthFailed(major_err.value, minor_err.value);
    msglen = strlen(msg);
    client->probableCause = (Probable_Cause_Data*)PAL_Malloc(sizeof(Probable_Cause_Data)+msglen+major_err.length+minor_err.length+5);

    client->probableCause->alloc_p           = (void*)client->probableCause;
    client->probableCause->type = ERROR_ACCESS_DENIED;
    client->probableCause->probable_cause_id = WSMAN_CIMERROR_PROBABLE_CAUSE_AUTHENTICATION_FAILURE;
    client->probableCause->description       = (MI_Char *)(client->probableCause+1);

    self->errMsg = (MI_Char *)(client->probableCause+1);
    pmsg = self->errMsg;
    memcpy(pmsg, msg, msglen);
    pmsg += msglen;
    if (major_err.length > 0)
    {
        *pmsg++ = ' ';
        memcpy(pmsg, major_err.value, major_err.length);
        pmsg += major_err.length;
    }
    if (minor_err.length > 0)
    {
        *pmsg++ = ' ';
        memcpy(pmsg, minor_err.value, minor_err.length);
        pmsg += minor_err.length;
    }
    *pmsg++ = '\0';

    (*_g_gssClientState.Gss_Release_Buffer)(&min_stat, &major_err);
    (*_g_gssClientState.Gss_Release_Buffer)(&min_stat, &minor_err);
}


#if ENCRYPT_DECRYPT

/*
 * Decrypts encrypted data in the data packet. Returns new header (with original content type and content length)
 * and the new data. releases the page. 
 * Returns true if it performed a change, false otherwise
 */

MI_Boolean HttpClient_DecryptData(_In_ HttpClient_SR_SocketData * handler, _Out_ HttpClientResponseHeader * pHeaders, _Out_ Page ** pData)
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
    int flags = (int)handler->negoFlags&(GSS_C_INTEG_FLAG|GSS_C_CONF_FLAG);
    uint32_t sig_len = 0;
    //uint32_t sig_flags = 0;

    int original_content_length = 0;
    char original_content_type_save[1024] = { 0 };  // Longest possible content type?
    char original_encoding_save[64] = { 0 };

    char *original_content_type = NULL;
    char *original_encoding = NULL;

    MI_Boolean done = FALSE;
    static const char ENCRYPTED_SEGMENT[] = "Encrypted Boundary";
    static const size_t ENCRYPTED_SEGMENT_LEN = MI_COUNT(ENCRYPTED_SEGMENT) - 1;

    static const char ORIGINAL_CONTENT[] = "OriginalContent:";
    static const size_t ORIGINAL_CONTENT_LEN = MI_COUNT(ORIGINAL_CONTENT) - 1;

    static const char TYPE_FIELD[] = "type=";
    static const size_t TYPE_FIELD_LEN = MI_COUNT(TYPE_FIELD) - 1;

    static const char CHARSET_FIELD[] = "charset=";
    static const size_t CHARSET_FIELD_LEN = MI_COUNT(CHARSET_FIELD) - 1;

    static const char LENGTH_FIELD[] = "length=";
    static const size_t LENGTH_FIELD_LEN = MI_COUNT(LENGTH_FIELD) - 1;

    static const char CONTENT_TYPE[] = "Content-Type";
    static const size_t CONTENT_TYPE_LEN = MI_COUNT(CONTENT_TYPE) - 1;

    static const char CONTENT_LENGTH[] = "Content-Length";
    static const size_t CONTENT_LENGTH_LEN = MI_COUNT(CONTENT_LENGTH) - 1;

    static const char OCTET_STREAM[] = "application/octet-stream";
    static const size_t OCTET_STREAM_LEN = MI_COUNT(OCTET_STREAM) - 1;

    static const char APPLICATION_SPNEGO[] = "application/HTTP-SPNEGO-session-encrypted";   // 2do: compare to header protocol
    static const size_t APPLICATION_SPNEGO_LEN = MI_COUNT(APPLICATION_SPNEGO) - 1;

    static const char APPLICATION_KERBEROS[] = "application/HTTP-Kerberos-session-encrypted";
    static const size_t APPLICATION_KERBEROS_LEN = MI_COUNT(APPLICATION_KERBEROS) - 1;

    static const char MULTIPART_ENCRYPTED[] = "multipart/encrypted";
    static const size_t MULTIPART_ENCRYPTED_LEN = MI_COUNT(MULTIPART_ENCRYPTED) - 1;

    const char *content_type = NULL;
    const char *content_len_str = NULL;

    //char *char_set = NULL;

    if (!pHeaders)
    {
        trace_HTTP_CryptInvalidArg(__FUNCTION__, "pHeaders == NULL");
        return FALSE;
    }

    int i = 0;
    for (i = 0; i < pHeaders->sizeHeaders; i++ )
    {
        if (strncasecmp(pHeaders->headers[i].name, CONTENT_TYPE, CONTENT_TYPE_LEN) == 0)
        {
            content_type = pHeaders->headers[i].value;
        }
        else if (strncasecmp(pHeaders->headers[i].name, CONTENT_LENGTH, CONTENT_LENGTH_LEN) == 0)
        {
            content_len_str = pHeaders->headers[i].value;
        }
    }

    if (!content_type)
    {
       // Not encrypted
       //
       return FALSE;
    }

    if (!(strncasecmp(content_type, MULTIPART_ENCRYPTED, MULTIPART_ENCRYPTED_LEN) == 0))
    {
        // Then its not encrypted. our job is done

        return TRUE;
    }

    if (!handler->authContext)
    {
        trace_HTTP_CryptInvalidArg(__FUNCTION__, "context == NULL");
        return FALSE;
    }

    if (!pData)
    {
        trace_HTTP_CryptInvalidArg(__FUNCTION__, "pdata == NULL");
        return FALSE;
    }

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

        if (Strncasecmp(segp, ENCRYPTED_SEGMENT, ENCRYPTED_SEGMENT_LEN) == 0)
        {
            // Skip the boundary
            while (!('\n' == scanp[0] && '\r' == scanp[-1]) && scanp < scanlimit) scanp++;
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

                    linep += CONTENT_TYPE_LEN;
                    while (isspace(*linep) && linep < linelimit)
                    {
                        linep++;
                    }

                    if (':' == *linep && linep < linelimit)
                    {
                        linep++;
                    }

                    while (isspace(*linep) && linep < linelimit)
                    {
                        linep++;
                    }

                    if (Strncasecmp(linep, OCTET_STREAM, OCTET_STREAM_LEN) == 0)
                    {

                        sig_len = *(uint32_t *) (linelimit + 2);
                        sig_len = ByteSwapToWindows32(sig_len);

                        input_buffer.length = original_content_length+sig_len;
                        input_buffer.value = linelimit + 2  // skip crlf
                                                       + 4; // skip signature len

                        done = TRUE;
                        break;
                    }
                    else if (Strncasecmp(linep, APPLICATION_SPNEGO, APPLICATION_SPNEGO_LEN) == 0)
                    {
                        // Should be application/HTTP-SPNEGO-session-encrypted for spnego

                    }
                    else if (Strncasecmp(linep, APPLICATION_KERBEROS, APPLICATION_KERBEROS_LEN) == 0)
                    {
                        // Should be application/HTTP-Kerberos-session-encrypted for kerberos

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
                            while (';' != *linep && *linep && linep < linelimit)
                                linep++;
                            linep++;
                        }
                        else if (Strncasecmp(linep, TYPE_FIELD, TYPE_FIELD_LEN) == 0)
                        {
                            linep += TYPE_FIELD_LEN;
                            original_content_type = linep;
                            while (';' != *linep && *linep && linep < linelimit)
                            {
                                linep++;
                            }
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
                else if (*scanp == '-' && scanp[1] == '-')
                {    

                    // Start of new segment

                    break;
                }    
                else
                {
                    // Bogus

                    while (!('\n' == scanp[0] && '\r' == scanp[-1]) && *scanp != '-' && scanp < scanlimit && !done)
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

    maj_stat = (*_g_gssClientState.Gss_Unwrap)(&min_stat, (gss_ctx_id_t) handler->authContext, &input_buffer, &output_buffer, &flags, NULL);
    if (GSS_S_COMPLETE != maj_stat)
    {
        _ReportError(handler, "gss_unwrap", maj_stat, min_stat);
        return FALSE;
    }
    // Here is where we replace the pData page, replace the headers on content-type and content size

    // We can just copy the data into the buffer directly, since the decrypted data is guaranteed
    // to be smaller than the encrypted data plus header

    page->u.s.size = output_buffer.length;
    memcpy(page + 1, output_buffer.value, output_buffer.length);

    char *buffer_p = (char *)(page + 1) + output_buffer.length;

    // We know we have the additional room in the page because the string was in the page already
    memcpy(buffer_p, original_content_type, strlen(original_content_type) + 1);
    original_content_type = buffer_p;

    buffer_p += strlen(original_content_type) + 1;  // Include the null
    memcpy(buffer_p, original_encoding, strlen(original_encoding) + 1);

    (*_g_gssClientState.Gss_Release_Buffer)(&min_stat, &output_buffer);

    // In oroder for this to work, we must leave the original page allocated, and leave it to the 
    // caller to free the original data and recvBuffer

    for (i = 0; i < pHeaders->sizeHeaders; i++ )
    {
        char **pvalue = NULL;

        pvalue = (char**)(&pHeaders->headers[i].value);
        if (strncasecmp(pHeaders->headers[i].name, CONTENT_TYPE, CONTENT_TYPE_LEN) == 0)
        {
            *pvalue = (char*)original_content_type;
        }
        else if (strncasecmp(pHeaders->headers[i].name, CONTENT_LENGTH, CONTENT_LENGTH_LEN) == 0)
        {
            *pvalue = (char*)content_len_str;
        }
    }

    return MI_TRUE;
}

/*
 * Encrypts data in the data packet. Returns new header (with original content type and content length)
 * and the new data. releases the page. 
 */

MI_Boolean
HttpClient_EncryptData(_In_ HttpClient_SR_SocketData * handler, _Out_ Page **pHeader, _Out_ Page ** pData)

{
    HttpClient* client = (HttpClient*)handler->base.data;
    char numbuf[11] = { 0 };
    const char *pnum = NULL;
    size_t str_len = 0;

    static const char MULTIPART_ENCRYPTED_SPNEGO[] = "multipart/encrypted;"
        "protocol=\"application/HTTP-SPNEGO-session-encrypted\";" "boundary=\"Encrypted Boundary\"\r\n";

    static const char MULTIPART_ENCRYPTED_KERBEROS[] = "multipart/encrypted;"
        "protocol=\"application/HTTP-Kerberos-session-encrypted\";" "boundary=\"Encrypted Boundary\"\r\n";

    static const char ENCRYPTED_BOUNDARY[] = "--Encrypted Boundary\r\n";
    static const size_t ENCRYPTED_BOUNDARY_LEN = MI_COUNT(ENCRYPTED_BOUNDARY) - 1;  // do not count the null

    static const char ENCRYPTED_SPNEGO_BODY_CONTENT_TYPE[] = "Content-Type: application/HTTP-SPNEGO-session-encrypted\r\n";
    static const size_t ENCRYPTED_SPNEGO_BODY_CONTENT_TYPE_LEN = MI_COUNT(ENCRYPTED_SPNEGO_BODY_CONTENT_TYPE) - 1;

    static const char ENCRYPTED_KERBEROS_BODY_CONTENT_TYPE[] = "Content-Type: application/HTTP-Kerberos-session-encrypted\r\n";
    static const size_t ENCRYPTED_KERBEROS_BODY_CONTENT_TYPE_LEN = MI_COUNT(ENCRYPTED_KERBEROS_BODY_CONTENT_TYPE) - 1;

    static const char ORIGINAL_CONTENT[] = "OriginalContent: type=";
    static const size_t ORIGINAL_CONTENT_LEN = MI_COUNT(ORIGINAL_CONTENT) - 1;

    static const char ORIGINAL_CHARSET[] = ";charset=";
    static const size_t ORIGINAL_CHARSET_LEN = MI_COUNT(ORIGINAL_CHARSET) - 1;

    static const char ORIGINAL_LENGTH[] = ";Length=";   // Plus crlf
    static const size_t ORIGINAL_LENGTH_LEN = MI_COUNT(ORIGINAL_LENGTH) - 1;

    static const char ENCRYPTED_OCTET_CONTENT_TYPE[] = "Content-Type: application/octet-stream\r\n";
    static const size_t ENCRYPTED_OCTET_CONTENT_TYPE_LEN = MI_COUNT(ENCRYPTED_OCTET_CONTENT_TYPE) - 1;

    static const char TRAILER_BOUNDARY[] = "--Encrypted Boundary--\r\n";
    static const size_t TRAILER_BOUNDARY_LEN = MI_COUNT(TRAILER_BOUNDARY) - 1;

    int needed_data_size = 0;

    // We encrypted every byte that was there. Success

    if (!pData)
    {
        return MI_TRUE;
    }

    if (!*pData)
    {
        return MI_TRUE;
    }

    if (!handler->isPrivate)
    {
        // We are not encrypting, so we are done;
        return MI_TRUE;
    }

    char *MULTIPART_ENCRYPTED;
    int  MULTIPART_ENCRYPTED_LEN;
    char *ENCRYPTED_BODY_CONTENT_TYPE;
    size_t ENCRYPTED_BODY_CONTENT_TYPE_LEN;

    const static Probable_Cause_Data AUTH_ERROR_ENCRYPT_UNAVAILABLE = {
          ERROR_ACCESS_DENIED,
          WSMAN_CIMERROR_PROBABLE_CAUSE_AUTHENTICATION_FAILURE,
          MI_T("Encryption available only in Kerberos or SPNEGO authentication"),
          NULL
    };

    switch(handler->authType)
    {
    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
        ENCRYPTED_BODY_CONTENT_TYPE = (char*)ENCRYPTED_SPNEGO_BODY_CONTENT_TYPE;
        ENCRYPTED_BODY_CONTENT_TYPE_LEN = (size_t)ENCRYPTED_SPNEGO_BODY_CONTENT_TYPE_LEN;
        MULTIPART_ENCRYPTED = (char*)MULTIPART_ENCRYPTED_SPNEGO;
        MULTIPART_ENCRYPTED_LEN = MI_COUNT(MULTIPART_ENCRYPTED_SPNEGO)-1;
        break;

    case AUTH_METHOD_KERBEROS:
        ENCRYPTED_BODY_CONTENT_TYPE     = (char*)ENCRYPTED_KERBEROS_BODY_CONTENT_TYPE;
        ENCRYPTED_BODY_CONTENT_TYPE_LEN = (size_t)ENCRYPTED_KERBEROS_BODY_CONTENT_TYPE_LEN;
        MULTIPART_ENCRYPTED = (char*)MULTIPART_ENCRYPTED_KERBEROS;
        MULTIPART_ENCRYPTED_LEN = MI_COUNT(MULTIPART_ENCRYPTED_KERBEROS)-1;
        break;

    default:
        trace_Wsman_UnsupportedAuthentication("Unknown");
        client->probableCause = (Probable_Cause_Data *)&AUTH_ERROR_ENCRYPT_UNAVAILABLE;
        return MI_FALSE;
    }

#define PAD_16_BYTES(x) (((x)+0xf)&~0xf)

    char *original_content_type = NULL;
    char *original_encoding = NULL;
    char *original_host_header  = NULL;
    char *poriginal_data = (char *)(*pData + 1);
    int host_header_len         = 0;
    int original_content_len = (*pData)->u.s.size; // We allocate extra space for this to be OK.
    int pad_from = original_content_len;

    // We manually pad because gss and sspi don't agree on padding
    original_content_len = PAD_16_BYTES(original_content_len);
    memset(poriginal_data+pad_from, 0, (original_content_len-pad_from));

    gss_buffer_desc input_buffer = { original_content_len, poriginal_data };
    gss_buffer_desc output_buffer = { 0 };
    OM_uint32 min_stat, maj_stat;
    int out_flags;
    OM_uint32 signature_length = 16;  // NTLM_SIGNATURE_LENGTH

    char *alloced_data = NULL;  // We will have a leak if we don't free the memory we alloc for the output buffer. 

    Page *pNewData = NULL;
    int orig_hdr_len = 0;
    Page *pNewHeaderPage = NULL;
    char *pNewHeader = NULL;
    char *phdr = NULL;
    char *psrc = NULL;
    char *pdst = NULL;
    int siglen = 16;
    char *buffp = NULL;

    Page *pOriginalDataPage = *pData;
    Page *pOriginalHeaderPage = *pHeader;
#if GSS_USE_IOV 

    gss_iov_buffer_desc iov[4] = {{0}};
    int num_iov;
    if (_g_gssClientState.Gss_Wrap_Iov && handler->selectedMech == AUTH_MECH_KERBEROS)
    {
        // We can get here either by requesting Kerberos directly, or negotiating it via Spnego
        // Either way, MIT gss_wrap and SSPI EncryptMessage don't get along.
        //
        iov[0].type = GSS_IOV_BUFFER_TYPE_HEADER     | GSS_IOV_BUFFER_FLAG_ALLOCATE;
        iov[1].type = GSS_IOV_BUFFER_TYPE_DATA;
        iov[1].buffer.length = original_content_len;
        iov[1].buffer.value  = poriginal_data;
        iov[2].type = GSS_IOV_BUFFER_TYPE_PADDING  | GSS_IOV_BUFFER_FLAG_ALLOCATE;
        num_iov = 3;

        maj_stat = (*_g_gssClientState.Gss_Wrap_Iov)(&min_stat, handler->authContext, (handler->negoFlags & GSS_C_CONF_FLAG),
                            GSS_C_QOP_DEFAULT, &out_flags, iov, num_iov);
        if (maj_stat != GSS_S_COMPLETE)
        {
            _ReportError(handler, "gss_wrap failed", maj_stat, min_stat);
            goto Error;
        }

        signature_length = iov[0].buffer.length;

        output_buffer.length = (iov[0].buffer.length+
                                iov[1].buffer.length+
                                iov[2].buffer.length );

        alloced_data = PAL_Malloc(output_buffer.length); // We retain this so we can tell we alloced it, not gss
        if (!alloced_data)
        {
            _ReportError(handler, "Encrypt: allocation failed", 0, 0);
            goto Error;
        }
        output_buffer.value = alloced_data;
    
        char *outbufp = output_buffer.value;
        if (iov[0].buffer.length)
        {
            memcpy(outbufp, iov[0].buffer.value, iov[0].buffer.length);
            outbufp += iov[0].buffer.length;
        }
    
        if (iov[1].buffer.length)
        {
            memcpy(outbufp, iov[1].buffer.value, iov[1].buffer.length);
            outbufp += iov[1].buffer.length;
        }
        if (iov[2].buffer.length)
        {
            memcpy(outbufp, iov[2].buffer.value, iov[2].buffer.length);
            outbufp += iov[2].buffer.length;
        }

        (*_g_gssClientState.Gss_Release_Iov_Buffer)(&min_stat, iov, num_iov);
    }
    else 
    {
        if (handler->selectedMech == AUTH_MECH_NTLMSSP)
        {
            //  We are here because gss_wrap_iov is not implemented in gss-ntlmssp. 
            //  If we aren't doing NTLM I'm not sure how we would figure out the signature length
            
             signature_length = 16;  // NTLM_SIGNATURE_LENGTH
        }
        maj_stat = (*_g_gssClientState.Gss_Wrap)(&min_stat, handler->authContext, (handler->negoFlags & GSS_C_CONF_FLAG),
                        GSS_C_QOP_DEFAULT, &input_buffer, &out_flags, &output_buffer);
        if (maj_stat != GSS_S_COMPLETE)
        {
            _ReportError(handler, "gss_wrap failed", maj_stat, min_stat);
            goto Error;
        }
    }
#else
    maj_stat = (*_g_gssClientState.Gss_Wrap)(&min_stat, handler->authContext, (handler->negoFlags & GSS_C_CONF_FLAG),
                        GSS_C_QOP_DEFAULT, &input_buffer, &out_flags, &output_buffer);
    if (maj_stat != GSS_S_COMPLETE)
    {
        _ReportError(handler, "gss_wrap failed", maj_stat, min_stat);
        goto Error;
    }

#endif                                    

    // clone the header

    orig_hdr_len = strlen((char*)(*pHeader+1));

    // Could be less mem, but not by much and this doesnt require two passes
    pNewHeaderPage = PAL_Malloc(MULTIPART_ENCRYPTED_LEN + orig_hdr_len + 100 + sizeof(Page));
    if (!pNewHeaderPage)
    {
        _ReportError(handler, "alloc failed for pHewHeader", 0, 0);
        goto Error;
    }
    pNewHeaderPage->u.s.size = (MULTIPART_ENCRYPTED_LEN + orig_hdr_len + 100);

    pNewHeader = (char *)(pNewHeaderPage+1);
    // The host header need not be at the end
    phdr = Strcasestr((char*)(*pHeader+1), "Host:");
    original_host_header = phdr;
    phdr = strchr(phdr, '\r');
    phdr+=2;
    
    host_header_len = phdr-original_host_header;

    phdr = Strcasestr((char*)(*pHeader+1), "Content-Type:");
    phdr = strchr(phdr, ':');
    phdr++;

    while (isspace(*phdr))
    {
        phdr++;
    }
    original_content_type = phdr;
    phdr = strchr(phdr, ';');
    *phdr++ = '\0';

    phdr = Strcasestr(phdr, "charset=");
    phdr = strchr(phdr, '=');
    phdr++;

    original_encoding = phdr;
    phdr = strchr(phdr, '\r');
    *phdr++ = '\0';

    pnum = Uint32ToStr(numbuf, original_content_len, &str_len);

    // Figure out the data size
    needed_data_size = ENCRYPTED_BOUNDARY_LEN +
                       ENCRYPTED_BODY_CONTENT_TYPE_LEN +
                       ORIGINAL_CONTENT_LEN +
                       ORIGINAL_CHARSET_LEN +
                       ORIGINAL_LENGTH_LEN +
                       str_len +
                       strlen(original_encoding) +
                       strlen(original_content_type) +
                       2 +  // 2 for \r\n
                       ENCRYPTED_BOUNDARY_LEN +
                       ENCRYPTED_OCTET_CONTENT_TYPE_LEN +
                       4 + // dword signaturelength
                       output_buffer.length + // Length includes the signature
                       TRAILER_BOUNDARY_LEN;

    // Copy the first part of the original header

    psrc = (char*)(*pHeader+1);
    pdst = pNewHeader;

    // First replace the original content length

    phdr = Strcasestr((char*)(*pHeader+1), "Content-Length:");
    phdr = strchr(phdr, ':');
    phdr++;
    for (; psrc < phdr; psrc++, pdst++)
        *pdst = *psrc;
    pnum = Uint32ToStr(numbuf, needed_data_size, &str_len);
    memcpy(pdst, pnum, str_len);
    pdst += str_len;

    psrc = strchr(phdr, '\r');
    for (; psrc < original_content_type; psrc++, pdst++)
    {
         *pdst = *psrc;
    }

    memcpy(pdst, MULTIPART_ENCRYPTED, MULTIPART_ENCRYPTED_LEN);
    pdst += MULTIPART_ENCRYPTED_LEN;
    memcpy(pdst, original_host_header, host_header_len);
    pdst += host_header_len; 
    *pdst++ = '\r';
    *pdst++ = '\n';


//    PAL_Free(*pHeader); We hav no way of knowing how the pHeader got there
    pNewHeaderPage->u.s.size = pdst - pNewHeader;
    *pHeader = pNewHeaderPage;

    pNewData = PAL_Malloc(needed_data_size+sizeof(Page));
    if (!pNewData)
    {
        trace_HTTP_AuthMallocFailed("pNewData in Http_EcryptData");
         _ReportError(handler, "Encrypt: allocation failed", 0, 0);
        goto Error;
    }

    pNewData->u.s.size = needed_data_size;
    pNewData->u.s.next = 0;
    buffp = (char *)(pNewData + 1);

    memcpy(buffp, ENCRYPTED_BOUNDARY, ENCRYPTED_BOUNDARY_LEN);
    buffp += ENCRYPTED_BOUNDARY_LEN;

    memcpy(buffp, ENCRYPTED_BODY_CONTENT_TYPE, ENCRYPTED_BODY_CONTENT_TYPE_LEN);
    buffp += ENCRYPTED_BODY_CONTENT_TYPE_LEN;

    memcpy(buffp, ORIGINAL_CONTENT, ORIGINAL_CONTENT_LEN);
    buffp += ORIGINAL_CONTENT_LEN;

    memcpy(buffp, original_content_type, strlen(original_content_type));
    buffp += strlen(original_content_type);

    memcpy(buffp, ORIGINAL_CHARSET, ORIGINAL_CHARSET_LEN);
    buffp += ORIGINAL_CHARSET_LEN;

    memcpy(buffp, original_encoding, strlen(original_encoding));
    buffp += strlen(original_encoding);

    memcpy(buffp, ORIGINAL_LENGTH, ORIGINAL_LENGTH_LEN);
    buffp += ORIGINAL_LENGTH_LEN;

    pnum = Uint32ToStr(numbuf, original_content_len, &str_len);
    memcpy(buffp, pnum, str_len);
    buffp += str_len;

    memcpy(buffp, "\r\n", 2);
    buffp += 2;

    memcpy(buffp, ENCRYPTED_BOUNDARY, ENCRYPTED_BOUNDARY_LEN);
    buffp += ENCRYPTED_BOUNDARY_LEN;

    memcpy(buffp, ENCRYPTED_OCTET_CONTENT_TYPE, ENCRYPTED_OCTET_CONTENT_TYPE_LEN);
    buffp += ENCRYPTED_OCTET_CONTENT_TYPE_LEN;

    siglen = ByteSwapToWindows32(signature_length);

    memcpy(buffp, &siglen, 4);
    buffp += 4;

    memcpy(buffp, output_buffer.value, output_buffer.length);
    buffp += output_buffer.length;

    memcpy(buffp, TRAILER_BOUNDARY, TRAILER_BOUNDARY_LEN);
    buffp += TRAILER_BOUNDARY_LEN;

    pNewData->u.s.size = buffp-(char*)(pNewData+1);

    *pData = pNewData;

    if (alloced_data)
    {
         PAL_Free(alloced_data);
    }
    else
    {
        (*_g_gssClientState.Gss_Release_Buffer)(&min_stat, &output_buffer);
    }

    return MI_TRUE;

Error:
    if (alloced_data)
    {
         PAL_Free(alloced_data);
         alloced_data = NULL;
    }
    else
    {
        (*_g_gssClientState.Gss_Release_Buffer)(&min_stat, &output_buffer);
    }
    if (pNewData)
    {
        PAL_Free(pNewData);
        pNewData = NULL;
    }
    if (pNewHeaderPage)
    {
        PAL_Free(pNewHeaderPage);
        pNewHeaderPage = NULL;
    }
    *pData   = pOriginalDataPage;
    *pHeader = pOriginalHeaderPage;

#if GSS_USE_IOV
    (*_g_gssClientState.Gss_Release_Iov_Buffer)(&min_stat, iov, 2);
#endif
    return MI_FALSE;
}

#endif
/* 
 *  Based on the authorisation type, we create an auth clause for the Http response header. 
 *  The response token is converted to base 64.  
 *
 *  An assumption is made that the protocol text values are single byte (UTF8).
 *
 */

static char *_BuildClientGssAuthHeader(_In_ struct _HttpClient_SR_SocketData
                                       *self, gss_buffer_t token, _Out_ MI_Uint32 * pResultLen)
{
    static const MI_Char AUTH_PREFIX_NEGOTIATE[] = ZT("Authorization: Negotiate ");
    static const MI_Char AUTH_PREFIX_KERBEROS[] = ZT("Authorization: Kerberos ");

    const MI_Char *prefix = NULL;
    int prefix_len = 0;

    struct _EncodeContext encode_context = { 0 };

    switch (self->authType)
    {
    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
        prefix = AUTH_PREFIX_NEGOTIATE;
        prefix_len = MI_COUNT(AUTH_PREFIX_NEGOTIATE) - 1;   // Dont want to count the null
        break;

    case AUTH_METHOD_KERBEROS:
        prefix = AUTH_PREFIX_KERBEROS;
        prefix_len = MI_COUNT(AUTH_PREFIX_KERBEROS) - 1;    // Dont want to count the null
        break;

    default:
        trace_Wsman_UnsupportedAuthentication("Unknown");
        return NULL;
    }

    encode_context.size = 0;
    encode_context.pdata = NULL;

    // Call once to estimate the size.
    int rslt = Base64Enc(token->value, token->length, EncodeSizeCallback,
                         &encode_context);

    // Then we allocate the data  and add the extra

    encode_context.pdata = PAL_Malloc(encode_context.size + prefix_len + 1);
    encode_context.size = prefix_len;

    memcpy(encode_context.pdata, prefix, prefix_len);

    // Call again to copy the data
    if (rslt >= 0)
    {
        rslt = Base64Enc(token->value, token->length, EncodePlaceCallback, &encode_context);
    }

    encode_context.pdata[encode_context.size] = '\0';

    if (pResultLen)
    {
        *pResultLen = encode_context.size;
    }
    return encode_context.pdata;
}


static int _Base64DecCallback(const void *data, size_t length, void *callbackData)
{
    gss_buffer_t decoded_data = (gss_buffer_t) callbackData;
    const unsigned char *new_decoded_data = (const unsigned char *)data;

    memcpy((char *)decoded_data->value + decoded_data->length, new_decoded_data, length);
    decoded_data->length += length;

    return 0;
}

/*
**==============================================================================
*/

/*
      Converts the SPNEGO authorization header string to an opaque gss token

*/

static int _getInputToken(_In_ struct _HttpClient_SR_SocketData * self,  const char *authorization, gss_buffer_t token)
{
    const char *auth = authorization;
    int token_length = 0;

    switch (self->authType)
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

    
    token_length = strlen(auth);
    if (token_length <= 0)
    { 
       return -1;
    }

    token->value = (unsigned char *)PAL_Malloc(token_length);
    if (!token->value)
    {
        return -1;
    }
    memset(token->value, 0, strlen(auth));
    token->length = 0;

    int decodedSize = Base64Dec((const void *)auth, strlen(auth), _Base64DecCallback, token);

    if (decodedSize <= 0)
    {
        trace_Base64Dec_Failed();
        return -2;
    }
    return 0;
}

#endif

/* 
 *  Based on the authorisation type, we create an auth clause for the Http response header. 
 *  The response token is converted to base 64.  
 *
 *  An assumption is made that the protocol text values are single byte (UTF8).
 *
 */

static char *_BuildBasicAuthHeader(_In_ struct _HttpClient_SR_SocketData *self, MI_Uint32 * pStatus)
{

    static const char AUTHORIZE_HEADER_BASIC[] = "Authorization: Basic ";
    const MI_Uint32 AUTHORIZE_HEADER_BASIC_LEN = Strlen(AUTHORIZE_HEADER_BASIC);

    char *authUsernamePassword; /* <username>:<password> in ansi ready for base64-encoding */
    MI_Uint32 authUsernamePasswordLength;

    struct _EncodeContext encode_context = { 0 };

    /* Convert username and password into format needed for auth "<username>:<password>" as ANSI string */
    authUsernamePasswordLength = Strlen(self->username) + 1 /* : */  + Strlen(self->password);
    authUsernamePassword = (char *)PAL_Malloc(authUsernamePasswordLength + 1);
    if (authUsernamePassword == NULL)
    {
        *pStatus = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        return NULL;
    }
    Strlcpy(authUsernamePassword, self->username, authUsernamePasswordLength + 1);
    Strlcat(authUsernamePassword, ":", authUsernamePasswordLength + 1);
    Strlcat(authUsernamePassword, self->password, authUsernamePasswordLength + 1);

    /* Now we need to base64 encode the username:password string. We may as well
     * put the result in the final buffer
     */

    encode_context.size = 0;
    encode_context.pdata = NULL;

    // Call once to estimate the size.
    if (Base64Enc
        (authUsernamePassword, authUsernamePasswordLength,
         EncodeSizeCallback, &encode_context) == -1)
    {
        PAL_Free(authUsernamePassword);
        *pStatus = MI_RESULT_FAILED;
        return NULL;
    }
    // Then we allocate the data  and add the extra

    encode_context.pdata = PAL_Malloc(encode_context.size + AUTHORIZE_HEADER_BASIC_LEN + 1);

    Strlcpy(encode_context.pdata, AUTHORIZE_HEADER_BASIC, AUTHORIZE_HEADER_BASIC_LEN + 1);
    encode_context.size = AUTHORIZE_HEADER_BASIC_LEN;

    // Call again to copy the data
    if (Base64Enc
        (authUsernamePassword, authUsernamePasswordLength,
         EncodePlaceCallback, &encode_context) == -1) 
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

#if AUTHORIZATION


/*
 * _WriteAuthRequest writes a reply to the server's reply to an auth request 
 * issued in HttpClient_RequestAuthorization. SPNEGO and kerberos may require 
 * a number of iterations of this, as many as five.  
 *
 * Returns:
 *    TRUE  if the transfer completed
 *    FALSE otherwise
 *
 * The transfer is retried as often as needed for the transfer, but no partial transfers are allowed.
 * The socket is assumed to be drained before the transfer is requested.
 *
 */

static MI_Boolean _WriteAuthRequest(HttpClient_SR_SocketData * handler, const char *pRequest, int requestLen)

{
    size_t sent, total_sent;
    total_sent = 0;

    trace_HTTP_SendNextAuthReply();
    if (!pRequest)
    {
        return FALSE;
    }

    if (!handler->ssl)
    {
        MI_Result rslt;

        do
        {
            rslt = Sock_Write(handler->base.sock, pRequest, requestLen, &sent);
        }
        while (rslt == MI_RESULT_WOULD_BLOCK);

        if (FORCE_TRACING || ((total_sent > 0) && handler->enableTracing))
        {
            _WriteTraceFile(ID_HTTPCLIENTSENDTRACEFILE, pRequest, sent);
        }
        return rslt == MI_RESULT_OK;
    }

    do
    {
        sent = 0;
        sent = SSL_write(handler->ssl, pRequest, requestLen);

        if (sent == 0)
        {
            trace_Socket_ConnectionClosed(handler);
            return FALSE;

        }
        else if ((int)sent < 0)
        {
            switch (SSL_get_error(handler->ssl, sent))
            {

             // These do not happen. We have already drained the socket
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
    while (total_sent < requestLen);

    if (FORCE_TRACING || ((total_sent > 0) && handler->enableTracing))
    {
        _WriteTraceFile(ID_HTTPCLIENTSENDTRACEFILE, pRequest, total_sent);
    }

    return TRUE;
}

/*
 *  Evaluates the response header returned by the server . 
 *
 *  If the context is established returns complete, return no request header and PRT_CONTINUE
 *  If the context needs another round trip, return PRT_RETURN_TRUE and a request header for the return request
 *  If the context errors out,  return no request header and PRT_CONTINUE
 *
 */

Http_CallbackResult
HttpClient_NextAuthRequest(_In_ struct _HttpClient_SR_SocketData * self, _In_ const char *pResponseHeader, _Out_ const char **pRequestHeader, _Out_ size_t *pRequestLen)

{
    static const char POST_HEADER[] = "POST /wsman/ HTTP/1.1\r\n"\
                                      "Connection: Keep-Alive\r\n"\
                                      "Content-Length: 0\r\n"\
                                      "Content-Type: application/soap+xml;charset=UTF-8\r\n";

    static const size_t POST_HEADER_LEN = MI_COUNT(POST_HEADER)-1;

    
    const gss_OID_desc mechset_avail_elems[] = {
        { 6, "\053\006\001\005\005\002" },                  // Spnego
        { 10, "\x2b\x06\x01\x04\x01\x82\x37\x02\x02\x0a" }, // ntlm
        { 9, "\052\206\110\206\367\022\001\002\002" }      // mech_krb5
    };
    const gss_OID_set_desc mechset_avail = { 3, (gss_OID) mechset_avail_elems };
    
    const gss_OID_desc mechset_krb5_elems[] = { 
        { 9, "\052\206\110\206\367\022\001\002\002" }      // mech_krb5
    };
    
    const gss_OID_set_desc mechset_krb5 = { 1, (gss_OID) mechset_krb5_elems };
    
    OM_uint32 maj_stat = 0;
    OM_uint32 min_stat = 0;
    gss_ctx_id_t context_hdl = GSS_C_NO_CONTEXT;
    gss_buffer_desc input_token, output_token;
    gss_OID_set mechset = NULL;
    gss_name_t target_name = (gss_name_t) self->targetName;
    gss_OID chosen_mech = NULL;

    if (!pRequestHeader)
    {
        // complain here

        return PRT_RETURN_FALSE;
    }    

    switch (self->authType)
    {
    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
        mechset = (gss_OID_set) & mechset_avail;
        break;
    
    case AUTH_METHOD_KERBEROS:
        mechset = (gss_OID_set) & mechset_krb5;
        break;
    
    default:

        // We shouldn't be here in basic auth

        return PRT_RETURN_FALSE;
    }
    
    if (self->authContext)
    {
        context_hdl = (gss_ctx_id_t) self->authContext;
    }
    // This is an auth in progress, generate new request 
    
    self->authorizing  = TRUE;
    self->isAuthorized = FALSE;

    if (_getInputToken(self, pResponseHeader, &input_token) != 0)
    {
        _ReportError(self, "Authorization failed", maj_stat, min_stat);
        self->authorizing = FALSE;
        self->isAuthorized = FALSE;
        return PRT_RETURN_FALSE;
    }

    if (self->isPrivate)
    {
        self->negoFlags = (GSS_C_INTEG_FLAG | GSS_C_CONF_FLAG);
        if (self->authType == AUTH_METHOD_KERBEROS)
        {
            self->negoFlags |= (GSS_C_REPLAY_FLAG | GSS_C_MUTUAL_FLAG);
        }
    }

    // (void)DecodeToken(&input_token);
    maj_stat = (*_g_gssClientState.Gss_Init_Sec_Context)(&min_stat, self->cred, &context_hdl, target_name, mechset->elements, self->negoFlags,   // flags
                                    0,  // time_req,
                                    GSS_C_NO_CHANNEL_BINDINGS,  // input_chan_bindings,
                                    &input_token, &chosen_mech, /* mech type */
                                    &output_token, &self->negoFlags, NULL);   /* time_rec */
    
    if (chosen_mech)
    {
        const gss_OID_desc mech_krb5   = { 9, "\052\206\110\206\367\022\001\002\002" };
        const gss_OID_desc mech_ntlm   = {10, "\x2b\x06\x01\x04\x01\x82\x37\x02\x02\x0a" };

        if (Gss_Oid_Equal(chosen_mech, (gss_OID)&mech_krb5)) {
            self->selectedMech = AUTH_MECH_KERBEROS;
        }
        else if (Gss_Oid_Equal(chosen_mech, (gss_OID)&mech_ntlm))
        {
            self->selectedMech = AUTH_MECH_NTLMSSP;
        }
        else
        {
            self->selectedMech = AUTH_MECH_UNSUPPORTED;
        }
    }    
    else 
    {
        self->selectedMech = AUTH_MECH_NONE;
    }
    
    // self->negoFlags = ret_flags;
    
    PAL_Free(input_token.value);
    
    if (maj_stat == GSS_S_COMPLETE)
    {

        // If the result is complete, then we are done and can 
        // send whatever request is pending, if any

  
        trace_HTTP_AuthComplete();
        self->encrypting   = (self->negoFlags & (GSS_C_INTEG_FLAG | GSS_C_CONF_FLAG)) == (GSS_C_CONF_FLAG | GSS_C_INTEG_FLAG);       // All data transfered will be encrypted.
        self->readyToSend  = TRUE;
        self->authorizing  = FALSE;
        self->isAuthorized = TRUE;

        *pRequestHeader = NULL;
        return PRT_CONTINUE;
    }
    else if (maj_stat == GSS_S_CONTINUE_NEEDED)
    {

        // Continue needed means we need to create a request header for sending

        MI_Uint32 header_len = 0;
        char *auth_header = _BuildClientGssAuthHeader(self, &output_token, &header_len);
    
        /* create header page */

        char *request_header = PAL_Malloc(POST_HEADER_LEN+header_len+5+strlen(self->hostHeader));
        char *requestp = request_header;

        memcpy(requestp, POST_HEADER, POST_HEADER_LEN);
        requestp += POST_HEADER_LEN;

        strcpy(requestp, self->hostHeader);
        requestp += strlen(self->hostHeader);

        memcpy(requestp, auth_header, header_len);
        requestp += header_len;

        *requestp++ = '\r';
        *requestp++ = '\n';
        *requestp++ = '\r';
        *requestp++ = '\n';
        *requestp   = '\0';

        *pRequestHeader = request_header;
        *pRequestLen    = (requestp - request_header);
    
        (void)(*_g_gssClientState.Gss_Release_Buffer)(&min_stat, &output_token);
    
        return PRT_RETURN_TRUE;
    }
    else {
        _ReportError(self, "Access Denied", maj_stat, min_stat);
    
        *pRequestHeader = NULL;

        return PRT_RETURN_FALSE;
    }
}


/*
 * Verify the username and password given. Without this check gss will use default credentials rather than
 * fail the authentication if given a bogus username and password.
 */
static int
_Krb5VerifyInitCreds(const char *principalName, const char *password)
{
#if !defined(macos)
    krb5_error_code ret;
    krb5_creds creds;
    krb5_principal client_princ = NULL;

    krb5_context context;

    ret = (*_g_gssClientState.krb5InitContext)(&context);
    if (ret)
        goto cleanup;

    memset(&creds, 0, sizeof(creds));
    ret = (*_g_gssClientState.krb5ParseName)(context, principalName, &client_princ);
    if (ret)
        goto cleanup;

    ret = (*_g_gssClientState.krb5GetInitCredsPassword)(context, &creds, client_princ,
                                   password, NULL, NULL, 0, NULL, NULL);
    if (ret)
        goto cleanup;
    ret = (*_g_gssClientState.krb5VerifyInitCreds)(context, &creds, NULL, NULL, NULL, NULL);

cleanup:
    (*_g_gssClientState.krb5FreePrincipal)(context, client_princ);
    (*_g_gssClientState.krb5FreeCredContents)(context, &creds);
    return ret;
#else
    return 0;
#endif
}



static char *_BuildInitialGssAuthHeader(_In_ HttpClient_SR_SocketData * self, MI_Uint32 * status)
{
    char *rslt = NULL;

    const gss_OID_desc mechset_krb5_elems[] = { 
        { 9, "\052\206\110\206\367\022\001\002\002" }      // mech_krb5
    };

    const gss_OID_set_desc mechset_krb5 = { 1, (gss_OID) mechset_krb5_elems };

    // The list attached to the spnego token 

    const gss_OID_desc mechset_avail_elems[] = {
        { 6, "\053\006\001\005\005\002" },                  // Spnego
        { 10, "\x2b\x06\x01\x04\x01\x82\x37\x02\x02\x0a" }, // ntlm
        { 9, "\052\206\110\206\367\022\001\002\002" }      // mech_krb5
    };
    const gss_OID_set_desc mechset_avail = { 3, (gss_OID) mechset_avail_elems };

    //static const char WSMAN_PROTOCOL[] = "WSMAN/";

   
    OM_uint32 maj_stat, min_stat;

    // const char *protocol = WSMAN_PROTOCOL;
    // const MI_Uint32 protocol_len = MI_COUNT(WSMAN_PROTOCOL) - 1;    // The count includes a null

    gss_ctx_id_t context_hdl = GSS_C_NO_CONTEXT;
    gss_cred_id_t cred = GSS_C_NO_CREDENTIAL;
    gss_name_t gss_username = GSS_C_NO_NAME;
    gss_name_t target_name = GSS_C_NO_NAME;
    gss_OID    target_name_type = NULL;


    // Ensure the GSS lib is loaded

    if (!Once_Invoke(&g_once_state, _GssClientInitLibrary, self)) 
    {
        // We have a problem. 
        trace_HTTP_LoadGssFailed("");
        return FALSE;
    }

    gss_buffer_desc output_token;
    gss_OID_set mechset = NULL;

    if (self->authContext)
    {

        // release any old context handle

        context_hdl = (gss_ctx_id_t) self->authContext;
        (*_g_gssClientState.Gss_Delete_Sec_Context)(&min_stat, &context_hdl, NULL);
        self->authContext = NULL;
    }

    switch (self->authType)
    {
    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
        mechset = (gss_OID_set) & mechset_avail;
        target_name_type =  _g_gssClientState.Gss_Nt_Service_Name;
        if (self->isPrivate)
        {
            self->negoFlags = (GSS_C_INTEG_FLAG | GSS_C_CONF_FLAG |  GSS_C_REPLAY_FLAG | GSS_C_MUTUAL_FLAG);
        }
        else 
        {
            self->negoFlags = GSS_C_MUTUAL_FLAG;
        }
        break;

    case AUTH_METHOD_KERBEROS:
        mechset = (gss_OID_set) & mechset_krb5;
        target_name_type = _g_gssClientState.Gss_Krb5_Nt_Principal_Name;
        if (self->isPrivate)
        {
            self->negoFlags = (GSS_C_INTEG_FLAG | GSS_C_CONF_FLAG |  GSS_C_REPLAY_FLAG | GSS_C_MUTUAL_FLAG);
        }
        else 
        {
            self->negoFlags = GSS_C_MUTUAL_FLAG;
        }

        // Check the username and password
        if (self->username != NULL)
        { int retval = 0;

            char buffer[1024];
            char *bufp = &buffer[0];

            strcpy(bufp, self->username);
            bufp += strlen(self->username);

            if (self->user_domain)
            {
                *bufp++ = '@';
                strcpy(bufp, self->user_domain);
                bufp += strlen(self->user_domain);
                *bufp = '\0';
            }

            retval = _Krb5VerifyInitCreds(buffer, self->password);
            if (retval != 0 ) 
            {
#if !defined(macos)
                _ReportError(self, "Kerberos verify cred with password failed", GSS_S_NO_CRED, (OM_uint32)KRB5KRB_AP_ERR_BADMATCH );
#endif
                return NULL;
            }
        }

        break;

    default:
        trace_Wsman_UnsupportedAuthentication("Unknown");
        return NULL;
    }

    // Get a credential, either with the username/passwd

    if (self->username != NULL)
    {
        gss_buffer_desc buf;
        char buffer[1024];
        char *bufp = &buffer[0];

        strcpy(bufp, self->username);
        bufp += strlen(self->username);

        if (strncasecmp(self->user_domain, self->hostname, strlen(self->user_domain)) != 0)
        {
            if (self->user_domain)
            {
                *bufp++ = '@';
                strcpy(bufp, self->user_domain);
                bufp += strlen(self->user_domain);
            }
            buf.value = buffer;
            buf.length = bufp-buffer;
        }
        buf.value = buffer;
        buf.length = bufp-buffer;

        maj_stat = (*_g_gssClientState.Gss_Import_Name)(&min_stat, &buf, _g_gssClientState.Gss_C_Nt_User_Name, &gss_username);

        if (maj_stat != GSS_S_COMPLETE)
        {
            _ReportError(self, "Could not import name ", maj_stat, min_stat);
            return NULL;
        }
        if (self->password != NULL)
        {

            if (!_g_gssClientState.gssAcquireCredwithPassword )
            {
                trace_HTTP_GssFunctionNotPresent("gss_acquire_creD_with_password");
            }
            else
            {
                buf.value = self->password;
                buf.length = self->passwordLen;
    
                maj_stat = (*_g_gssClientState.gssAcquireCredwithPassword )(
                                                          &min_stat,
                                                          gss_username,
                                                          &buf, 0,
                                                          mechset, GSS_C_INITIATE, &cred, NULL, NULL);
                if (maj_stat != GSS_S_COMPLETE)
                {
                    _ReportError(self, "acquiring creds with password failed", maj_stat, min_stat);
                    if (maj_stat == GSS_S_NO_CRED)
                    {
                         // If we have a password given to us, we can't forgive the cred being wrong.
                         // If the mech simply doesn't have the entry point we have to tolerate it.
                         // But very few modern platforms are in that position.
                         return NULL;
                    }

                    maj_stat = (*_g_gssClientState.Gss_Acquire_Cred)(&min_stat, gss_username, 0,
                                            mechset, GSS_C_INITIATE, &cred, NULL, NULL);

                    if (maj_stat != GSS_S_COMPLETE)
                    {
                        _ReportError(self,
                                 "acquiring creds with username only failed", maj_stat, min_stat);
                        (*_g_gssClientState.Gss_Release_Name)(&min_stat, &gss_username);
                         return NULL;
                    }
                }
            }
        }
        else
        {
            if (gss_username != GSS_C_NO_NAME)
            {
                maj_stat = (*_g_gssClientState.Gss_Acquire_Cred)(&min_stat, gss_username, 0,
                                            mechset, GSS_C_INITIATE, &cred, NULL, NULL);
                if (maj_stat != GSS_S_COMPLETE)
                {
                    _ReportError(self,
                                 "acquiring creds with username only failed", maj_stat, min_stat);
                    (*_g_gssClientState.Gss_Release_Name)(&min_stat, &gss_username);
                    return NULL;
                }
            }
        }
    }
    else {
        maj_stat = (*_g_gssClientState.Gss_Acquire_Cred)(&min_stat,
                                    gss_username, 0, mechset, GSS_C_INITIATE, &cred, NULL, NULL);
        if (maj_stat != GSS_S_COMPLETE)
        {
            _ReportError(self, "acquiring anonymous creds failed", maj_stat, min_stat);
            (*_g_gssClientState.Gss_Release_Name)(&min_stat, &gss_username);
            return NULL;
        }
    }

    if ((self->authType == AUTH_METHOD_NEGOTIATE) ||
        (self->authType == AUTH_METHOD_NEGOTIATE_WITH_CREDS))
    {

        // Add the list of available mechs to the credential 

        if (_g_gssClientState.gssSetNegMechs)
        {
            maj_stat = (*_g_gssClientState.gssSetNegMechs)(&min_stat, cred, (gss_OID_set)&mechset_avail);
            if (maj_stat != GSS_S_COMPLETE)
            {
                _ReportError(self, "setting neg mechs", maj_stat, min_stat);
                (*_g_gssClientState.Gss_Release_Name)(&min_stat, &gss_username);
                (*_g_gssClientState.Gss_Release_Cred)(&min_stat, &cred);
                return NULL;
            }
        }
        else
        {
            // Print info that we could not set neg mechs
        }
    }

    // Figure out the target name

    {   // Start with the fdqn
        gss_buffer_desc buff = { 0 };

        struct addrinfo hints, *info;
        int gai_result;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;    /*either IPV4 or IPV6 */
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_CANONNAME;

        if ((gai_result = getaddrinfo(self->hostname, "http", &hints, &info)) != 0)
        {
            trace_HTTP_GetAddrInfoError(gai_strerror(gai_result));
            return NULL;
        }

        { char  protocol[] = "http/";
          int   protocol_len = MI_COUNT(protocol)-1;

            buff.length = protocol_len + strlen(info->ai_canonname);
            buff.value = PAL_Malloc(buff.length + 1);
            char *bufp = (char*)buff.value;
    
            memset(buff.value, 0, buff.length+1);
            memcpy(buff.value, protocol, protocol_len);
            bufp += protocol_len;
    
            memcpy(bufp, info->ai_canonname, strlen(info->ai_canonname));
            bufp += strlen(info->ai_canonname);
            *bufp++ = '\0';
        }

        ((MI_Char *) buff.value)[buff.length] = 0; 

        // 2DO: If we dont have an fdqn we will use the addr

        freeaddrinfo(info);

        maj_stat = (*_g_gssClientState.Gss_Import_Name)(&min_stat, &buff, target_name_type, &target_name);
        if (maj_stat != GSS_S_COMPLETE)
        {
            _ReportError(self, "parsing name", maj_stat, min_stat);
            goto Done;
        }
    }

    if (self->isPrivate)
    {
        self->negoFlags = (GSS_C_INTEG_FLAG | GSS_C_CONF_FLAG |  GSS_C_REPLAY_FLAG | GSS_C_MUTUAL_FLAG);
    }

    maj_stat = (*_g_gssClientState.Gss_Init_Sec_Context)(&min_stat, cred, &context_hdl, target_name, mechset->elements, self->negoFlags, 
                                    0,  // time_req,
                                    GSS_C_NO_CHANNEL_BINDINGS,  // input_chan_bindings,
                                    GSS_C_NO_BUFFER, NULL, &output_token, &self->negoFlags, 0);   // time_req

    if (maj_stat == GSS_S_CONTINUE_NEEDED)
    {
        MI_Uint32 header_len = 0;

        // Expected

        *status = GSS_S_CONTINUE_NEEDED;
        trace_HTTP_AuthContinue();


        rslt = _BuildClientGssAuthHeader(self, &output_token, &header_len);

        self->authContext = context_hdl;
        self->targetName = target_name;
        self->authorizing = TRUE;
        self->cred = (void *)cred;
    }
    else if (maj_stat == GSS_S_COMPLETE)
    {
        MI_Uint32 header_len = 0;
        
        // Kerberos will be completed here, probably. But we need to build an auth header
        // for key exchange

        if (output_token.length > 0)
        {
            // We need to build an auth header    
            rslt = _BuildClientGssAuthHeader(self, &output_token, &header_len);
        }    

        // If the result is complete, then we are done and can
        // send whatever request is pending, if any
        *status = GSS_S_COMPLETE;

        // If the result is complete, then we are done and can 
        // send whatever request is pending, if any

        trace_HTTP_AuthComplete();

        if ((self->authType == AUTH_METHOD_KERBEROS) && 
            ((self->negoFlags  & (GSS_C_INTEG_FLAG | GSS_C_CONF_FLAG)) == (GSS_C_INTEG_FLAG | GSS_C_CONF_FLAG)) &&
            (!(self->negoFlags & GSS_C_PROT_READY_FLAG))) 
        {    
            // We may be in complete, but we are not ready to encrypt so we short cirtuit isAuthorised
            self->authContext = context_hdl;
            self->targetName = target_name;
            self->authorizing = TRUE;
            self->cred = (void *)cred;
        }
        else 
        {        
            self->encrypting   = (self->negoFlags & (GSS_C_INTEG_FLAG | GSS_C_CONF_FLAG)) == (GSS_C_CONF_FLAG | GSS_C_INTEG_FLAG);       // All data transfered will be encrypted.
            self->readyToSend  = TRUE;
            self->authorizing  = FALSE;
            self->isAuthorized = TRUE;
            self->cred = (void *)cred;
        }    

        // *pRequestHeader = NULL;

        return rslt;

    }
    else {
        // Unexpected here
        _ReportError(self, "Authorization failed", maj_stat, min_stat);
    }

    (*_g_gssClientState.Gss_Release_Name)(&min_stat, &gss_username);

 Done:
    return rslt;
}

#endif

Http_CallbackResult HttpClient_RequestAuthorization(_In_ struct _HttpClient_SR_SocketData *handler, const char **pAuthHeader)
{
   MI_Uint32 status = 0;

    // Create and send the auth header
    // The client side of the authorisation dance.

    // We do the gss_init_sec_context, rinse and repeat 

    switch (handler->authType)
    {
    case AUTH_METHOD_BASIC:

        handler->authorizing = TRUE;

        if (pAuthHeader)
        {
            *pAuthHeader = _BuildBasicAuthHeader(handler, &status);
            if (!*pAuthHeader)
            {
                goto AuthFailed;
            }
        }
        // And that should do it.

        return PRT_CONTINUE;

#if AUTHORIZATION
    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
    case AUTH_METHOD_KERBEROS:
        
        if (pAuthHeader)
        {
            *pAuthHeader = _BuildInitialGssAuthHeader(handler, &status);
            if (!*pAuthHeader)
            {
                goto AuthFailed;
            }
            else 
            {
                if (handler->isAuthorized)
                {
                    return PRT_RETURN_TRUE;
                }
            }                
        }

        return PRT_CONTINUE;
#endif

    default:
         goto AuthFailed;
    }

AuthFailed:

    return PRT_RETURN_FALSE;
}



/*
 *
 *   HttpClient_IsAuthorized 
 *
 *   Handles authentication replies from the server, after HttpClient_RequestAuthorization sends the initial 
 *   request.
 *
 *   If a reply is needed, sends the reply on the same thread. 
 *
 *   Returns :
 *       PRT_CONTINUE     : Continue with the transaction
 *       PRT_RETURN_TRUE  : Retry the transaction
 *       PRT_RETURN_FALSE : The transaction has failed
 *
 */

Http_CallbackResult HttpClient_IsAuthorized(_In_ struct _HttpClient_SR_SocketData * self)

{
    static const char AUTHENTICATE[] = "WWW-Authenticate";
    static const MI_Uint32 AUTHENTICATE_LEN = MI_COUNT(AUTHENTICATE);

    //HttpClient* client = (HttpClient*)self->base.data;
    HttpClientResponseHeader *pheaders = &self->recvHeaders;
    char *auth_header = NULL;

    int i = 0;

    // For unit test
    if (IsAuthCallsIgnored())
    {
        self->authorizing = FALSE;
        self->isAuthorized = TRUE;
        return PRT_CONTINUE;
    }

    for (; i < pheaders->sizeHeaders; i++)
    {
        if (Strncasecmp(pheaders->headers[i].name, AUTHENTICATE, AUTHENTICATE_LEN) == 0)
        {
            auth_header = (char *)pheaders->headers[i].value;
            break;
        }

    }

    switch (self->authType)
    {
    case AUTH_METHOD_BASIC:

        // If the auth failed, we get a list of available auth methods. They will show up as WWW-Authenticate 
        // but no data after the method. We don't need to look at return header, though. We either 
        // authenticated or not. Basic must be reauthenticated every request so there is no state
        // or reply. Encryption is not possible in basic auth

        switch (pheaders->httpError)
        {
        case HTTP_ERROR_CODE_BAD_REQUEST:
        case HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR:
        case HTTP_ERROR_CODE_OK:
        case HTTP_ERROR_CODE_NOT_SUPPORTED:

            // We authorise broken error codes because of the possibility of
            // error content, eg post mortem dump info 

            self->authorizing = FALSE;
            self->isAuthorized = TRUE;
            self->encrypting   = FALSE;
            self->readyToSend  = TRUE;
            return PRT_CONTINUE;

        case HTTP_ERROR_CODE_UNAUTHORIZED:
        case 409:          // proxy unauthorised
        default:
            {
                HttpClient* client = (HttpClient*)self->base.data;
                self->authorizing  = FALSE;
                self->isAuthorized = FALSE;
                self->encrypting   = FALSE;
                self->readyToSend  = FALSE;
    
                #define BASIC_AUTH_FAIL_MSG "Basic Authorization failed for user "
                int msglen = MI_COUNT(BASIC_AUTH_FAIL_MSG)-1;
                int username_len = strlen(self->username);
                char *pmsg = NULL;
    
                client->probableCause = (Probable_Cause_Data*)PAL_Malloc(sizeof(Probable_Cause_Data)+msglen+strlen(self->username)+3);
                client->probableCause->alloc_p           = (void*)client->probableCause;
                client->probableCause->type = ERROR_ACCESS_DENIED;
                client->probableCause->probable_cause_id = WSMAN_CIMERROR_PROBABLE_CAUSE_AUTHENTICATION_FAILURE;
                client->probableCause->description       = (MI_Char *)(client->probableCause+1);
                
                self->errMsg = (char*)(client->probableCause+1);
                pmsg = self->errMsg;
                memcpy(pmsg, BASIC_AUTH_FAIL_MSG, msglen);
                pmsg += msglen;
                memcpy(pmsg, self->username, username_len);
                pmsg += username_len;
                *pmsg++ ='\0';
    
                return PRT_RETURN_FALSE;
            }
        }


    case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
    case AUTH_METHOD_NEGOTIATE:
    case AUTH_METHOD_KERBEROS:

#if AUTHORIZATION
        if (!auth_header)
        {
            switch (pheaders->httpError)
            {
            case HTTP_ERROR_CODE_OK:
                self->encrypting   = (self->negoFlags & (GSS_C_INTEG_FLAG | GSS_C_CONF_FLAG)) == (GSS_C_CONF_FLAG | GSS_C_INTEG_FLAG);       // All data transfered will be encrypted.
                self->readyToSend  = TRUE;
                self->authorizing = FALSE;
                self->isAuthorized = TRUE;
                return PRT_CONTINUE;

            case HTTP_ERROR_CODE_BAD_REQUEST:
            case HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR:
            case HTTP_ERROR_CODE_NOT_SUPPORTED:

                // We authorise broken error codes because of the possibility of 
                // error content, eg post mortem dump info

                self->readyToSend  = TRUE;
                self->authorizing = FALSE;
                self->isAuthorized = TRUE;
                return PRT_CONTINUE;

            case HTTP_ERROR_CODE_UNAUTHORIZED:
            case 409:          // proxy unauthorised
            default:
                self->readyToSend  = TRUE;
                self->authorizing = FALSE;
                self->isAuthorized = FALSE;
                return PRT_RETURN_FALSE;
            }
        }
        else {
            Http_CallbackResult r;
            // When we say response here we mean the response to their response.
            char *reply = NULL;
            size_t reply_len = 0;

            r = HttpClient_NextAuthRequest(self, auth_header, (const char**)&reply, &reply_len);
            switch (r)
            {
            case PRT_CONTINUE:

                // If we have a pending request, then we need to set up for send

                if (self->verb)
                {
                    self->sendHeader =  _CreateHttpHeader(self->verb, self->uri, self->contentType, NULL, self->hostHeader, NULL, self->data? self->data->u.s.size: 0);
                    self->sendPage   =  self->data;

                    self->verb        = NULL;
                    self->uri         = NULL;
                    self->contentType = NULL;
                    self->data        = NULL;

                    // Force it into a write state so we can send the original request

                    self->base.mask &= ~SELECTOR_READ;
                    self->base.mask |= SELECTOR_WRITE;
                    self->recvingState = RECV_STATE_HEADER;
                }     
                return r;

            case PRT_RETURN_FALSE:

                // We had an error

                return r;

            case PRT_RETURN_TRUE:
                 // We need to go around again.
                 if (reply)
                 {
                     self->base.mask |= SELECTOR_WRITE;
                     self->base.mask &= ~SELECTOR_READ;
                 
                     self->sentSize = 0;
                     self->sendingState = RECV_STATE_HEADER;
     
                     if (!_WriteAuthRequest(self, reply, reply_len))
                     {
                         trace_SendIN_IO_thread_HttpSocket_WriteFailed();
                     }
     
                     // Force it into read state so we can get the next header
                     self->base.mask &= ~SELECTOR_WRITE;
                     self->base.mask |= SELECTOR_READ;
                     self->recvingState = RECV_STATE_HEADER;
     
                     PAL_Free(reply);
                     reply = NULL;
                 }
                 else
                 {    
                     if (self->verb)
                     {
                         self->sendHeader =  _CreateHttpHeader(self->verb, self->uri, self->contentType, NULL, self->hostHeader, 
                                                               NULL, self->data? self->data->u.s.size: 0);
                         self->sendPage   =  self->data;

                         self->verb        = NULL;
                         self->uri         = NULL;
                         self->contentType = NULL;
                         self->data        = NULL;

                         // Force it into a write state so we can send the original request

                         self->base.mask &= ~SELECTOR_READ;
                         self->base.mask |= SELECTOR_WRITE;
                         self->recvingState = RECV_STATE_HEADER;
                     }     

                 }
                     
                return r;
            default:
                return PRT_RETURN_FALSE;
            }    

            // unreachable     return r;
        }
#endif
        // unreachable return PRT_RETURN_FALSE;

    default:
        return PRT_RETURN_FALSE;

    }
}
