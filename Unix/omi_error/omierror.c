/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

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

struct Pair
{
    MI_Result result;
    const ZChar* str;
};

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

MI_Result FaultString_ToMiResult(const ZChar *faultString, MI_Result *result)
{
    size_t i;
    if (faultString == NULL)
        return MI_RESULT_FAILED;

    for (i = 0; i < MI_COUNT(_pairs); i++)
    {
        if (Tcscmp(faultString, _pairs[i].str) == 0)
        {
            *result = _pairs[i].result;
            return MI_RESULT_OK;
        }
    }
    return MI_RESULT_FAILED;
}

const ZChar* MiResult_ToString(MI_Result result, _Out_writes_z_(len) MI_Char *buffer, MI_Uint32 len)
{
    size_t i;
    const ZChar* str = NULL;

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

    return str;
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
#if defined(macos) || ((_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE)
        int ret = strerror_r(OMI_Code, buffer, len);
        if (ret != 0)
            *buffer = '\0';
        return buffer;
#else
        char *ret = strerror_r(OMI_Code, buffer, len);
        return ret;
#endif

}
#endif /* defined(CONFIG_HAVE_STRERROR_R) */

#if !defined(CONFIG_HAVE_STRERROR_R)
MI_INLINE const MI_Char *Errno_ToString(MI_Uint32 OMI_Code, _Out_writes_z_(len) MI_Char *buffer, MI_Uint32 len)
{
    size_t i;
    struct Pair
    {
        MI_Uint32 result;
        const ZChar* str;
    };
    const ZChar* str = NULL;
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

    return str;
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

    return errorCategory;
}

const MI_Char *ErrnoToString(
    MI_Uint32 OMI_Code,
    _Out_writes_z_(len) MI_Char *buffer,
    MI_Uint32 len)
{
    return Errno_ToString(OMI_Code, buffer, len);
}

