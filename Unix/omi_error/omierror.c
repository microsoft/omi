#include "omierror.h"
#include "OMI_Error.h"
#include <pal/strings.h>
#include <base/instance.h>
#include <pal/format.h>
#include <base/result.h>
#include <pal/atomic.h>
#include "strid_errors.h"
#include <errno.h>

extern MI_CONST MI_ClassDecl OMI_Error_rtti;

MI_INLINE MI_ErrorCategory ErrorCategoryFromMIResult(MI_Uint32 error)
{
    MI_ErrorCategory miCategory = MI_ERRORCATEGORY_NOT_SPECIFIED;
    switch(error)
    {
    case MI_RESULT_OK :
        miCategory = MI_ERRORCATEGORY_NOT_SPECIFIED;
        break;
    case MI_RESULT_FAILED :
        miCategory = MI_ERRORCATEGORY_NOT_SPECIFIED;
        break;
    case MI_RESULT_ACCESS_DENIED :
        miCategory = MI_ERRORCATEGORY_ACCESS_DENIED;
        break;
    case MI_RESULT_INVALID_NAMESPACE :
        miCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_INVALID_PARAMETER :
        miCategory = MI_ERRORCATEGORY_INVALID_ARGUMENT;
        break;
    case MI_RESULT_INVALID_CLASS :
        miCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_NOT_FOUND :
        miCategory = MI_ERRORCATEGORY_OBJECT_NOT_FOUND;
        break;
    case MI_RESULT_NOT_SUPPORTED :
        miCategory = MI_ERRORCATEGORY_NOT_IMPLEMENTED;
        break;
    case MI_RESULT_CLASS_HAS_CHILDREN :
        miCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_CLASS_HAS_INSTANCES :
        miCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_INVALID_SUPERCLASS :
        miCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_ALREADY_EXISTS :
        miCategory = MI_ERRORCATEGORY_RESOURCE_EXISTS;
        break;
    case MI_RESULT_NO_SUCH_PROPERTY :
        miCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_TYPE_MISMATCH :
        miCategory = MI_ERRORCATEGORY_INVALID_TYPE;
        break;
    case MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED :
        miCategory = MI_ERRORCATEGORY_NOT_IMPLEMENTED;
        break;
    case MI_RESULT_INVALID_QUERY :
        miCategory = MI_ERRORCATEGORY_INVALID_ARGUMENT;
        break;
    case MI_RESULT_METHOD_NOT_AVAILABLE :
        miCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_METHOD_NOT_FOUND :
        miCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_NAMESPACE_NOT_EMPTY :
        miCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_INVALID_ENUMERATION_CONTEXT :
        miCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_INVALID_OPERATION_TIMEOUT :
        miCategory = MI_ERRORCATEGORY_INVALID_ARGUMENT;
        break;
    case MI_RESULT_PULL_HAS_BEEN_ABANDONED :
        miCategory = MI_ERRORCATEGORY_OPERATION_STOPPED;
        break;
    case MI_RESULT_PULL_CANNOT_BE_ABANDONED :
        miCategory = MI_ERRORCATEGORY_CLOS_EERROR;
        break;
    case MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED :
        miCategory = MI_ERRORCATEGORY_NOT_IMPLEMENTED;
        break;
    case MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED :
        miCategory = MI_ERRORCATEGORY_NOT_IMPLEMENTED;
        break;
    case MI_RESULT_SERVER_LIMITS_EXCEEDED :
        miCategory = MI_ERRORCATEGORY_RESOURCE_BUSY;
        break;
    case MI_RESULT_SERVER_IS_SHUTTING_DOWN :
        miCategory = MI_ERRORCATEGORY_RESOURCE_UNAVAILABLE;
        break;
    default:
        miCategory = MI_ERRORCATEGORY_NOT_SPECIFIED;
        break;
    }
    return miCategory;
}

const ZChar* MiResult_ToString(MI_Result result, _Out_writes_z_(len) MI_Char *buffer, MI_Uint32 len)
{
    size_t i;
    struct Pair
    {
        MI_Result result;
#if defined (_MSC_VER)
        MI_Uint32 str;
#else
        const ZChar* str;
#endif
    };
#if defined (_MSC_VER)
    MI_Uint32 str = 0;
#else
    const ZChar* str = NULL;
#endif
    static struct Pair _pairs[] =
    {
        { MI_RESULT_OK, STRID_MI_RESULT_OK },
        { MI_RESULT_FAILED, STRID_MI_RESULT_FAILED },
        { MI_RESULT_ACCESS_DENIED, STRID_MI_RESULT_ACCESS_DENIED },
        { MI_RESULT_INVALID_NAMESPACE, STRID_MI_RESULT_INVALID_NAMESPACE },
        { MI_RESULT_INVALID_PARAMETER, STRID_MI_RESULT_INVALID_PARAMETER },
        { MI_RESULT_INVALID_CLASS, STRID_MI_RESULT_INVALID_CLASS },
        { MI_RESULT_NOT_FOUND, STRID_MI_RESULT_NOT_FOUND },
        { MI_RESULT_NOT_SUPPORTED, STRID_MI_RESULT_NOT_SUPPORTED },
        { MI_RESULT_CLASS_HAS_CHILDREN, STRID_MI_RESULT_CLASS_HAS_CHILDREN },
        { MI_RESULT_CLASS_HAS_INSTANCES, STRID_MI_RESULT_CLASS_HAS_INSTANCES },
        { MI_RESULT_INVALID_SUPERCLASS, STRID_MI_RESULT_INVALID_SUPERCLASS },
        { MI_RESULT_ALREADY_EXISTS, STRID_MI_RESULT_ALREADY_EXISTS },
        { MI_RESULT_NO_SUCH_PROPERTY, STRID_MI_RESULT_NO_SUCH_PROPERTY },
        { MI_RESULT_TYPE_MISMATCH, STRID_MI_RESULT_TYPE_MISMATCH },
        { MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED, STRID_MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED },
        { MI_RESULT_INVALID_QUERY, STRID_MI_RESULT_INVALID_QUERY },
        { MI_RESULT_METHOD_NOT_AVAILABLE, STRID_MI_RESULT_METHOD_NOT_AVAILABLE },
        { MI_RESULT_METHOD_NOT_FOUND, STRID_MI_RESULT_METHOD_NOT_FOUND },
        { MI_RESULT_NAMESPACE_NOT_EMPTY, STRID_MI_RESULT_NAMESPACE_NOT_EMPTY },
        { MI_RESULT_INVALID_ENUMERATION_CONTEXT, STRID_MI_RESULT_INVALID_ENUMERATION_CONTEXT },
        { MI_RESULT_INVALID_OPERATION_TIMEOUT, STRID_MI_RESULT_INVALID_OPERATION_TIMEOUT },
        { MI_RESULT_PULL_HAS_BEEN_ABANDONED, STRID_MI_RESULT_PULL_HAS_BEEN_ABANDONED },
        { MI_RESULT_PULL_CANNOT_BE_ABANDONED, STRID_MI_RESULT_PULL_CANNOT_BE_ABANDONED },
        { MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED, STRID_MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED },
        { MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED, STRID_MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED },
        { MI_RESULT_SERVER_LIMITS_EXCEEDED, STRID_MI_RESULT_SERVER_LIMITS_EXCEEDED },
        { MI_RESULT_SERVER_IS_SHUTTING_DOWN, STRID_MI_RESULT_SERVER_IS_SHUTTING_DOWN },
        { MI_RESULT_CANCELED, STRID_MI_RESULT_CANCELED },
        { MI_RESULT_OPEN_FAILED, STRID_MI_RESULT_OPEN_FAILED },
        { MI_RESULT_INVALID_CLASS_HIERARCHY, STRID_MI_RESULT_INVALID_CLASS_HIERARCHY },
        { MI_RESULT_WOULD_BLOCK, STRID_MI_RESULT_WOULD_BLOCK },
        { MI_RESULT_TIME_OUT, STRID_MI_RESULT_TIME_OUT },
    };

    for (i = 0; i < MI_COUNT(_pairs); i++)
    {
        if (result == _pairs[i].result)
        {
            str = _pairs[i].str;
            break;
        }
    }

    buffer[0] = 0;

    if (str == 0)
    {
        /* Not found! */
        return MI_T("");
    }

#if defined (_MSC_VER)
    {
        static HINSTANCE hInstance = 0;
        if (hInstance == 0)
        {
            if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPWSTR)MiResult_ToString, &hInstance) == 0)
                return MI_T("");
        }
        if (LoadStringW(hInstance, str, buffer, len) == 0)
            return MI_T("");

        return buffer;
    }
#else
    return str;
#endif
}

_Success_(return == MI_RESULT_OK)
MI_Result OmiErrorFromWinrmCode(
    _In_opt_ Batch* batch,
    MI_Uint32 Winrm_Code,
    _In_z_ const MI_Char* Message,
    _Outptr_opt_result_maybenull_ OMI_Error **omiError)
{
    MI_Result miResult;
    MI_Char messageId[100];
    const MI_Char *errorMessage;

    if(omiError == NULL)
        return MI_RESULT_OK;

    *omiError = NULL;

    if (Winrm_Code == 0)
    {
        return MI_RESULT_OK;
    }

    miResult = Instance_New((MI_Instance**)omiError, &OMI_Error_rtti, batch);
    if (miResult != MI_RESULT_OK)
        return miResult;

    errorMessage = Message;

    if (Message == NULL)
        Message = errorMessage;

    Stprintf(messageId, sizeof(messageId)/sizeof(messageId[0]), PAL_T("OMI:WINRM:%d"), Winrm_Code);

    if (
        ((miResult = OMI_Error_Set_CIMStatusCode(*omiError, MI_RESULT_FAILED)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_Message(*omiError, Message)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_MessageArguments(*omiError, NULL, 0)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_MessageID(*omiError, messageId)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_Category(*omiError, MI_ERRORCATEGORY_NOT_SPECIFIED)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_Code(*omiError, Winrm_Code)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_ErrorMessage(*omiError, errorMessage)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_Type(*omiError, MI_RESULT_TYPE_WINRM)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OwningEntity(*omiError, PAL_T("OMI:CIMOM"))) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_PerceivedSeverity(*omiError, 7)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_ProbableCause(*omiError, 0)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_ProbableCauseDescription(*omiError, PAL_T("Unknown"))) == MI_RESULT_OK)
        )
    {
    }
    return miResult;
}

_Success_(return == MI_RESULT_OK)
MI_Result OmiErrorFromMiCode(
    _In_opt_ Batch* batch,
    MI_Uint32 OMI_Code,
    _In_z_ const MI_Char* Message,
    _Outptr_opt_result_maybenull_ OMI_Error **omiError)
{
    MI_Result miResult;
    MI_Char messageId[100];
    MI_Char buffer[100];
    const MI_Char *errorMessage;

    if(omiError == NULL)
        return MI_RESULT_OK;

    *omiError = NULL;

    if (OMI_Code == MI_RESULT_OK)
    {
        return MI_RESULT_OK;
    }

    miResult = Instance_New((MI_Instance**)omiError, &OMI_Error_rtti, batch);
    if (miResult != MI_RESULT_OK)
        return miResult;

    errorMessage = MiResult_ToString((MI_Result)OMI_Code, buffer, sizeof(buffer)/sizeof(buffer[0]));

    if (Message == NULL)
        Message = errorMessage;

    Stprintf(messageId, sizeof(messageId)/sizeof(messageId[0]), PAL_T("OMI:MI_Result:%d"), OMI_Code);

    if (
        ((miResult = OMI_Error_Set_CIMStatusCode(*omiError, OMI_Code)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_Message(*omiError, Message)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_MessageArguments(*omiError, NULL, 0)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_MessageID(*omiError, messageId)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_Category(*omiError, ErrorCategoryFromMIResult(OMI_Code))) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_Code(*omiError, OMI_Code)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_ErrorMessage(*omiError, errorMessage)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_Type(*omiError, MI_RESULT_TYPE_MI)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OwningEntity(*omiError, PAL_T("OMI:CIMOM"))) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_PerceivedSeverity(*omiError, 7)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_ProbableCause(*omiError, 0)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_ProbableCauseDescription(*omiError, PAL_T("Unknown"))) == MI_RESULT_OK)
        )
    {
    }
    return miResult;
}


MI_Result MIResultFromErrno(MI_Uint32 errorCode)
{
    MI_Result miResult;

    switch(errorCode)
    {
    case EINVAL:
        miResult = MI_RESULT_INVALID_PARAMETER;
        break;
    case EACCES:
        miResult = MI_RESULT_ACCESS_DENIED;
        break;
    case ENOMEM:
        miResult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        break;
    default:
        miResult = MI_RESULT_FAILED;
        break;
    }
    return miResult;
}
MI_INLINE MI_ErrorCategory ErrorCategoryFromErrno(MI_Uint32 error)
{
    return ErrorCategoryFromMIResult(MIResultFromErrno(error));
}

#if defined(CONFIG_HAVE_STRERROR_R)
MI_INLINE const MI_Char *Errno_ToString(
    MI_Uint32 OMI_Code,
    _Out_writes_z_(len) MI_Char *buffer,
    MI_Uint32 len)
{
# if defined(CONFIG_ENABLE_WCHAR)
    {
        char buf[128];
        char* str;

        if (len > MI_COUNT(buf))
        {
            if (!(str = (char*)PAL_Malloc(len)))
                return MI_T("");
        }
        else
        {
            str = buf;
        }


        *str = '\0';
        strerror_r(OMI_Code, str, len);
        TcsStrlcpy(buffer, str, len);

        if (str != buf)
            PAL_Free(str);

        return buffer;
    }
# else /* defined(CONFIG_ENABLE_WCHAR) */
    {
        *buffer = '\0';
        if (strerror_r(OMI_Code, buffer, len) == (char*)-1)
        {
            /* nothing interesting to do */
        }
        return buffer;
    }
# endif /* defined(CONFIG_ENABLE_WCHAR) */
}
#endif /* defined(CONFIG_HAVE_STRERROR_R) */

#if !defined(CONFIG_HAVE_STRERROR_R)
MI_INLINE const MI_Char *Errno_ToString(MI_Uint32 OMI_Code, _Out_writes_z_(len) MI_Char *buffer, MI_Uint32 len)
{
    size_t i;
    struct Pair
    {
        MI_Uint32 result;
#if defined (_MSC_VER)
        MI_Uint32 str;
#else
        const ZChar* str;
#endif
    };
#if defined (_MSC_VER)
    MI_Uint32 str = 0;
#else
    const ZChar* str = NULL;
#endif
    static struct Pair _pairs[] =
    {
        { EPERM, STRID_EPERM },
        { ENOENT, STRID_ENOENT },
        { ESRCH, STRID_ESRCH },
        { EINTR, STRID_EINTR },
        { EIO, STRID_EIO },
        { ENXIO, STRID_ENXIO },
        { E2BIG, STRID_E2BIG },
        { ENOEXEC, STRID_ENOEXEC },
        { EBADF, STRID_EBADF },
        { ECHILD, STRID_ECHILD },
        { EAGAIN, STRID_EAGAIN },
        { ENOMEM, STRID_ENOMEM },
        { EACCES, STRID_EACCES },
        { EFAULT, STRID_EFAULT },
        { EBUSY, STRID_EBUSY },
        { EEXIST, STRID_EEXIST },
        { EXDEV, STRID_EXDEV },
        { ENODEV, STRID_ENODEV },
        { ENOTDIR, STRID_ENOTDIR },
        { EISDIR, STRID_EISDIR },
        { EINVAL, STRID_EINVAL },
        { ENFILE, STRID_ENFILE },
        { EMFILE, STRID_EMFILE },
        { ENOTTY, STRID_ENOTTY },
        { EFBIG, STRID_EFBIG },
        { ENOSPC, STRID_ENOSPC },
        { ESPIPE, STRID_ESPIPE },
        { EROFS, STRID_EROFS },
        { EMLINK, STRID_EMLINK },
        { EPIPE, STRID_EPIPE },
        { EDOM, STRID_EDOM },
        { ERANGE, STRID_ERANGE },
        { EDEADLK, STRID_EDEADLK },
        { ENAMETOOLONG, STRID_ENAMETOOLONG },
        { ENOLCK, STRID_ENOLCK },
        { ENOSYS, STRID_ENOSYS },
        { EILSEQ, STRID_EILSEQ },
#if defined (_MSC_VER)
        { STRUNCATE, STRID_STRUNCATE }
#endif
    };

    for (i = 0; i < MI_COUNT(_pairs); i++)
    {
        if (OMI_Code == _pairs[i].result)
        {
            str = _pairs[i].str;
            break;
        }
    }

    buffer[0] = 0;

    if (str == 0)
    {
        /* Not found! */
        return MI_T("");
    }

#if defined (_MSC_VER)
    {
        static HINSTANCE hInstance = 0;
        if (hInstance == 0)
        {
            if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPWSTR)Errno_ToString, &hInstance) == 0)
                return MI_T("");
        }
        if (LoadStringW(hInstance, str, buffer, len) == 0)
            return MI_T("");

        return buffer;
    }
#else
    return str;
#endif
}
#endif /* !defined(CONFIG_HAVE_STRERROR_R) */

_Success_(return == MI_RESULT_OK)
MI_Result OmiErrorFromErrno(
    _In_opt_ Batch* batch,
    MI_Uint32 OMI_Code,
    _In_z_ const MI_Char* Message,
    _Outptr_opt_result_maybenull_ OMI_Error **omiError)
{
    MI_Result miResult;
    MI_Char messageId[100];
    MI_Char buffer[100];
    const MI_Char *errorMessage;

    if (omiError == NULL)
        return MI_RESULT_OK;

    *omiError = NULL;

    if (OMI_Code == 0)
        return MI_RESULT_OK;

    miResult = Instance_New((MI_Instance**)omiError, &OMI_Error_rtti, batch);
    if (miResult != MI_RESULT_OK)
        return miResult;

    errorMessage = Errno_ToString(OMI_Code, buffer, sizeof(buffer)/sizeof(buffer[0]));

    if (Message == NULL)
        Message = errorMessage;

    Stprintf(messageId, sizeof(messageId)/sizeof(messageId[0]), PAL_T("CRT errno %d"), OMI_Code);

    if (((miResult = OMI_Error_Set_OMI_Code(*omiError, OMI_Code)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_Type(*omiError, MI_T("ERRNO"))) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_Message(*omiError, Message)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_MessageArguments(*omiError, NULL, 0)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_ErrorMessage(*omiError, errorMessage)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_Category(*omiError, ErrorCategoryFromErrno(OMI_Code))) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_CIMStatusCode(*omiError, MIResultFromErrno(OMI_Code))) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_MessageID(*omiError, messageId)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OwningEntity(*omiError, PAL_T("OMI:CIMOM"))) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_PerceivedSeverity(*omiError, 7)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_ProbableCause(*omiError, 0)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_ProbableCauseDescription(*omiError, PAL_T("Unknown"))) == MI_RESULT_OK))
    {
    }
    return miResult;
}

#if defined(_MSC_VER)

MI_INLINE MI_ErrorCategory ErrorCategoryFromWin32Error(MI_Uint32 error)
{
    MI_ErrorCategory miCategory;
    switch(error)
    {
    case ERROR_GEN_FAILURE:
    default:
        miCategory = MI_ERRORCATEGORY_NOT_SPECIFIED;
        break;
    case ERROR_INVALID_PARAMETER:
        miCategory = MI_ERRORCATEGORY_INVALID_ARGUMENT;
        break;
    case ERROR_INVALID_HANDLE:
    case ERROR_INVALID_DATA:
    case ERROR_BAD_PATHNAME:
    case ERROR_INVALID_ADDRESS:
    case DNS_ERROR_INVALID_IP_ADDRESS:
        miCategory = MI_ERRORCATEGORY_INVALID_DATA;
        break;
    case ERROR_NOT_SUPPORTED:
    case ERROR_CANNOT_COPY:
    case ERROR_CAN_NOT_COMPLETE:
    case ERROR_CANTWRITE:
        miCategory = MI_ERRORCATEGORY_INVALID_OPERATION;
        break;
    case ERROR_BAD_CONFIGURATION:
        miCategory = MI_ERRORCATEGORY_INVALID_RESULT;
        break;

    case ERROR_FILE_NOT_FOUND:
    case ERROR_PATH_NOT_FOUND:
    case ERROR_PROC_NOT_FOUND:
    case ERROR_NO_DATA:
    case ERROR_NOINTERFACE:
    case ERROR_SERVICE_DOES_NOT_EXIST:
    case ERROR_NOT_FOUND:
    case ERROR_NO_SUCH_USER:
    case ERROR_NO_SUCH_GROUP:
    case DNS_ERROR_RCODE_NAME_ERROR:
    case DNS_INFO_NO_RECORDS:
        miCategory = MI_ERRORCATEGORY_OBJECT_NOT_FOUND;
        break;
    case ERROR_CANCELLED:
    case DNS_ERROR_RCODE_SERVER_FAILURE:
        miCategory = MI_ERRORCATEGORY_OPERATION_STOPPED;
        break;
    case WAIT_TIMEOUT:
    case ERROR_CANT_WAIT:
    case ERROR_TIMEOUT:
        miCategory = MI_ERRORCATEGORY_OPERATION_TIMEOUT;
        break;
    case ERROR_ACCESS_DENIED:
        miCategory = MI_ERRORCATEGORY_ACCESS_DENIED;
        break;
    case ERROR_SERVICE_ALREADY_RUNNING:
    case ERROR_SERVICE_CANNOT_ACCEPT_CTRL:
        miCategory = MI_ERRORCATEGORY_RESOURCE_BUSY;
        break;
    case ERROR_ALREADY_EXISTS:
    case ERROR_MORE_DATA:
    case ERROR_OBJECT_NAME_EXISTS:
        miCategory = MI_ERRORCATEGORY_RESOURCE_EXISTS;
        break;
    case ERROR_NOT_ENOUGH_MEMORY:
    case ERROR_NETNAME_DELETED:
    case ERROR_INSUFFICIENT_BUFFER:
    case ERROR_SERVICE_DISABLED:
    case ERROR_SERVICE_NOT_ACTIVE:
    case ERROR_SERVICE_NEVER_STARTED:
        miCategory = MI_ERRORCATEGORY_RESOURCE_UNAVAILABLE;
        break;
    case ERROR_CANTREAD:
        miCategory = MI_ERRORCATEGORY_READ_ERROR;
        break;

    case ERROR_LOGON_FAILURE:
        miCategory = MI_ERRORCATEGORY_AUTHENTICATION_ERROR;
        break;
    }
    return miCategory;
}

MI_INLINE MI_Result ResultFromWin32Error(MI_Uint32 error)
{
    MI_Result result = MI_RESULT_FAILED;
    switch(error)
    {
    case ERROR_FILE_NOT_FOUND :
        result = MI_RESULT_NOT_FOUND;
        break;
    case ERROR_PATH_NOT_FOUND :
        result = MI_RESULT_NOT_FOUND;
        break;
    case ERROR_ACCESS_DENIED:
        result = MI_RESULT_ACCESS_DENIED;
        break;
    case ERROR_INVALID_HANDLE :
        result = MI_RESULT_INVALID_PARAMETER;
        break;
    case ERROR_NOT_ENOUGH_MEMORY :
        result = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        break;
    case ERROR_INVALID_DATA :
        result = MI_RESULT_INVALID_PARAMETER;
        break;
    case ERROR_NOT_SUPPORTED :
        result = MI_RESULT_NOT_SUPPORTED;
        break;
    case ERROR_INVALID_PARAMETER :
        result = MI_RESULT_INVALID_PARAMETER;
        break;
    case ERROR_INSUFFICIENT_BUFFER :
        result = MI_RESULT_INVALID_PARAMETER;
        break;
    case ERROR_PROC_NOT_FOUND :
        result = MI_RESULT_NOT_FOUND;
        break;
    case ERROR_BAD_PATHNAME :
        result = MI_RESULT_INVALID_PARAMETER;
        break;
    case ERROR_ALREADY_EXISTS :
        result = MI_RESULT_ALREADY_EXISTS;
        break;
    case ERROR_NO_DATA :
        result = MI_RESULT_NOT_FOUND;
        break;
    case ERROR_NOINTERFACE :
        result = MI_RESULT_NOT_FOUND;
        break;
    case ERROR_OBJECT_NAME_EXISTS :
        result = MI_RESULT_ALREADY_EXISTS;
        break;
    case ERROR_SERVICE_DOES_NOT_EXIST :
        result = MI_RESULT_NOT_FOUND;
        break;
    case ERROR_NOT_FOUND :
        result = MI_RESULT_NOT_FOUND;
        break;
    case ERROR_NO_SUCH_USER :
        result = MI_RESULT_NOT_FOUND;
        break;
    case ERROR_NO_SUCH_GROUP :
        result = MI_RESULT_NOT_FOUND;
        break;
    case DNS_ERROR_RCODE_NAME_ERROR :
        result = MI_RESULT_NOT_FOUND;
        break;
    case DNS_INFO_NO_RECORDS :
        result = MI_RESULT_NOT_FOUND;
        break;
    default :
        result = MI_RESULT_FAILED;
        break;
    }
    return result;
}

_Success_(return == MI_RESULT_OK)
MI_Result OmiErrorFromWin32(
    _In_opt_ Batch* batch,
    MI_Uint32 OMI_Code,
    _In_z_ const MI_Char* Message,
    _Outptr_opt_result_maybenull_ OMI_Error **omiError)
{
    MI_Result miResult;
    MI_Char messageId[100];
    MI_Char *errorMessage = NULL;
    wchar_t *pMsg;

    if(omiError == NULL)
        return MI_RESULT_OK;

    *omiError = NULL;

    if (OMI_Code == NOERROR)
        return MI_RESULT_OK;

    miResult = Instance_New((MI_Instance**)omiError, &OMI_Error_rtti, batch);
    if (miResult != MI_RESULT_OK)
        return miResult;

    if( FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK,
                    NULL, OMI_Code, 0, (wchar_t*)&pMsg, 1, NULL) == 0 )
    {
        errorMessage = MI_T("");
    }
    else
    {
        errorMessage = pMsg;
    }

    if (Message == NULL)
        Message = errorMessage;

    Stprintf(messageId, sizeof(messageId)/sizeof(messageId[0]), PAL_T("Windows System Error %d"), OMI_Code);

    if (((miResult = OMI_Error_Set_OMI_Code(*omiError, OMI_Code)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_Type(*omiError, MI_RESULT_TYPE_WIN32)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_Message(*omiError, Message)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_MessageArguments(*omiError, NULL, 0)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_ErrorMessage(*omiError, errorMessage)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OMI_Category(*omiError, ErrorCategoryFromWin32Error(OMI_Code))) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_CIMStatusCode(*omiError, ResultFromWin32Error(OMI_Code))) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_MessageID(*omiError, messageId)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_OwningEntity(*omiError, PAL_T("OMI:CIMOM"))) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_PerceivedSeverity(*omiError, 7)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_ProbableCause(*omiError, 0)) == MI_RESULT_OK) &&
        ((miResult = OMI_Error_Set_ProbableCauseDescription(*omiError, PAL_T("Unknown"))) == MI_RESULT_OK))
    {
    }

    if (pMsg)
        LocalFree(pMsg);
    return miResult;
}

#endif

_Success_(return == MI_RESULT_OK)
MI_Result OMI_ErrorFromErrorCode(
    _In_opt_ Batch* batch,
    MI_Uint32 OMI_Code,
    _In_z_ const MI_Char *OMI_Type,
    _In_z_ const MI_Char* OMI_ErrorMessage,
    _Outptr_opt_result_maybenull_ OMI_Error **omiError)
{
    MI_Result miResult;

    if (omiError == NULL)
        return MI_RESULT_OK;

    *omiError = NULL;

    if (Tcscmp(OMI_Type, MI_RESULT_TYPE_MI) == 0)
    {
        miResult = OmiErrorFromMiCode(batch, OMI_Code, OMI_ErrorMessage, omiError);
    }
    else if (Tcscmp(OMI_Type, MI_RESULT_TYPE_ERRNO) == 0)
    {
        miResult = OmiErrorFromErrno(batch, OMI_Code, OMI_ErrorMessage, omiError);
    }
    else if (Tcscmp(OMI_Type, MI_RESULT_TYPE_WINRM) == 0)
    {
        miResult = OmiErrorFromWinrmCode(batch, OMI_Code, OMI_ErrorMessage, omiError);
    }
#if defined(_MSC_VER)
    else if (Tcscmp(OMI_Type, MI_RESULT_TYPE_WIN32) == 0)
    {
        miResult = OmiErrorFromWin32(batch, OMI_Code, OMI_ErrorMessage, omiError);
    }
#endif
    else
        return MI_RESULT_INVALID_PARAMETER;

    if (omiError)
    {
        /* Add some common items not handled in the specific code */
    }
    if (miResult)
    {
        NitsIgnoringError();
    }

    return MI_RESULT_OK;;
}

MI_ErrorCategory ErrorCategoryFromErrorCode(
    MI_Uint32 OMI_Code,
    _In_z_ const MI_Char *OMI_Type)
{
    MI_ErrorCategory errorCategory = MI_ERRORCATEGORY_NOT_SPECIFIED;
    if (Tcscmp(OMI_Type, MI_RESULT_TYPE_MI) == 0)
    {
        errorCategory = ErrorCategoryFromMIResult(OMI_Code);
    }
    else if (Tcscmp(OMI_Type, MI_RESULT_TYPE_ERRNO) == 0)
    {
        errorCategory = ErrorCategoryFromErrno(OMI_Code);
    }
#if defined(_MSC_VER)
    else if (Tcscmp(OMI_Type, MI_RESULT_TYPE_WIN32) == 0)
    {
        errorCategory = ErrorCategoryFromWin32Error(OMI_Code);
    }
#endif

    return errorCategory;
}

const MI_Char *ErrnoToString(
    MI_Uint32 OMI_Code,
    _Out_writes_z_(len) MI_Char *buffer,
    MI_Uint32 len)
{
    return Errno_ToString(OMI_Code, buffer, len);
}

