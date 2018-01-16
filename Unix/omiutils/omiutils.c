/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "omiutils.h"
#include <strings.h>
#include "OMI_Error.h"
#include "OMI_DebugError.h"
#include <assert.h>

static struct { const MI_Char *name; MI_Uint64 id; } 
DeclIdMap[] = {
    { MI_T("MSFT_GUID"), 1 },
    { MI_T("MSFT_ETWEventHeader"), 2 },
    { MI_T("MSFT_ETWEventPayload"), 3 },
    { MI_T("MSFT_ETWExtendedData"), 4 },
    { MI_T("MSFT_ETWEvent"), 5 },
    { MI_T("CIM_Error"), 6 },
    { MI_T("OMI_Error"), 7 },
    { MI_T("OMI_DebugError"), 8 },
    { MI_T("MSFT_CounterValue"), 9 },
    { MI_T("MSFT_FormattedCounterValueReal64"), 10 },
    { MI_T("MSFT_FormattedCounterValueUint32"), 11 },
    { MI_T("MSFT_FormattedCounterValueUint64"), 12 },
    { MI_T("MSFT_RawCounterValue"), 13 },
    { NULL }
};

MI_Uint64 GetClassDeclId(_In_ const MI_ClassDecl* classDecl)
{
    int i = 0;

    for (i=0;DeclIdMap[i].name;++i)
        if (Tcscmp(classDecl->name, DeclIdMap[i].name) == 0)
            return DeclIdMap[i].id;

    //else if //
    if (classDecl->owningClass != (void*)-1)
        return (MI_Uint64)(ptrdiff_t)(void*)classDecl;
    else //if (classDecl->owningClass == -1)
        return 0;
}

/*------------------------------------------------------------------------------
    Creates a new instance of OMI_Error and sets the values of Message, 
    OMI_ErrorCode, OMI_ErrorType and OMI_ErrorCategory properties. 
------------------------------------------------------------------------------*/

static MI_Result MI_CALL CreateOMIError_shared(
    _In_z_ const MI_Char* message,
    MI_Uint32 errorCode, 
    _In_z_ const MI_Char* errorType, 
    MI_Uint16 errorCategory, 
    const MI_ClassDecl *classDecl,
    _Outptr_ MI_Instance **omiError)
{
    MI_Result   result = MI_RESULT_OK;
    OMI_Error *err = NULL;
    MI_Application application = {0};
    *omiError = NULL;

    result = MI_Application_Initialize(0, NULL, omiError, &application);
    if (result != MI_RESULT_OK)
        return result;

    result = MI_Application_NewInstance(&application, classDecl->name, classDecl, (MI_Instance**)&err); 
    if (result == MI_RESULT_OK)
    {
        result = OMI_Error_Set_Message(err, message);
        if (result != MI_RESULT_OK) goto Exit;
        result = OMI_Error_Set_error_Code(err, errorCode);
        if (result != MI_RESULT_OK) goto Exit;
        result = OMI_Error_Set_error_Type(err, errorType); 
        if (result != MI_RESULT_OK) goto Exit;
        result = OMI_Error_Set_error_Category(err, errorCategory);
        if (result != MI_RESULT_OK) goto Exit;
		result = OMI_Error_Set_CIMStatusCode(err, MI_RESULT_FAILED);
        if (result != MI_RESULT_OK) goto Exit;
        *omiError = (MI_Instance*)err;
    }

Exit:
    if ((result != MI_RESULT_OK) && err) MI_Instance_Delete((MI_Instance*)err); 
    MI_Application_Close(&application);
    return result;
}

_Use_decl_annotations_
MI_Result MI_CALL CreateOMIError(
    const MI_Char* message,
    MI_Uint32 errorCode, 
    const MI_Char* errorType, 
    MI_Uint16 errorCategory, 
    MI_Instance **omiError)
{
    return CreateOMIError_shared(
        message, errorCode, errorType, errorCategory,
        &OMI_Error_rtti,
        omiError);
}

_Use_decl_annotations_
MI_Result MI_CALL CreateOMIDebugError(
    const MI_Char* message,
    MI_Uint32 errorCode, 
    const MI_Char* errorType, 
    MI_Uint16 errorCategory, 
    MI_Instance **omiError)
{
    return CreateOMIError_shared(
        message, errorCode, errorType, errorCategory,
        &OMI_DebugError_rtti,
        omiError);
}


static MI_Result MI_CALL CreateOMIError_FromMiResult_shared(
    MI_Result miResult,
    const MI_ClassDecl *classDecl,
    _Outptr_ MI_Instance **omiError)
{
    const MI_Char* message;
    MI_Uint16 errorCategory; 

    switch (miResult)
    {
    case MI_RESULT_OK: 
        assert(0 && "Why would one call CreateOMIError_FromMiResult(MI_RESULT_OK)?");
        message = MI_T("MI_RESULT_OK");
        errorCategory = MI_ERRORCATEGORY_NOT_SPECIFIED;
        break;
    case MI_RESULT_FAILED : 
        message = MI_T("MI_RESULT_FAILED");
        errorCategory = MI_ERRORCATEGORY_NOT_SPECIFIED;
        break;
    case MI_RESULT_ACCESS_DENIED : 
        message = MI_T("MI_RESULT_ACCESS_DENIED");
        errorCategory = MI_ERRORCATEGORY_ACCESS_DENIED;
        break;
    case MI_RESULT_INVALID_NAMESPACE : 
        message = MI_T("MI_RESULT_INVALID_NAMESPACE");
        errorCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_INVALID_PARAMETER : 
        message = MI_T("MI_RESULT_INVALID_PARAMETER");
        errorCategory = MI_ERRORCATEGORY_INVALID_ARGUMENT;
        break;
    case MI_RESULT_INVALID_CLASS : 
        message = MI_T("MI_RESULT_INVALID_CLASS");
        errorCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_NOT_FOUND : 
        message = MI_T("MI_RESULT_NOT_FOUND");
        errorCategory = MI_ERRORCATEGORY_OBJECT_NOT_FOUND;
        break;
    case MI_RESULT_NOT_SUPPORTED : 
        message = MI_T("MI_RESULT_NOT_SUPPORTED");
        errorCategory = MI_ERRORCATEGORY_NOT_IMPLEMENTED;
        break;
    case MI_RESULT_CLASS_HAS_CHILDREN : 
        message = MI_T("MI_RESULT_CLASS_HAS_CHILDREN");
        errorCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;        
    case MI_RESULT_CLASS_HAS_INSTANCES : 
        message = MI_T("MI_RESULT_CLASS_HAS_INSTANCES");
        errorCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_INVALID_SUPERCLASS : 
        message = MI_T("MI_RESULT_INVALID_SUPERCLASS");
        errorCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_ALREADY_EXISTS : 
        message = MI_T("MI_RESULT_ALREADY_EXISTS");
        errorCategory = MI_ERRORCATEGORY_RESOURCE_EXISTS;
        break;
    case MI_RESULT_NO_SUCH_PROPERTY : 
        message = MI_T("MI_RESULT_NO_SUCH_PROPERTY");
        errorCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_TYPE_MISMATCH : 
        message = MI_T("MI_RESULT_TYPE_MISMATCH");
        errorCategory = MI_ERRORCATEGORY_INVALID_TYPE;
        break;
    case MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED : 
        message = MI_T("MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED");
        errorCategory = MI_ERRORCATEGORY_NOT_IMPLEMENTED;
        break;
    case MI_RESULT_INVALID_QUERY : 
        message = MI_T("MI_RESULT_INVALID_QUERY");
        errorCategory = MI_ERRORCATEGORY_INVALID_ARGUMENT;
        break;
    case MI_RESULT_METHOD_NOT_AVAILABLE : 
        message = MI_T("MI_RESULT_METHOD_NOT_AVAILABLE");
        errorCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_METHOD_NOT_FOUND : 
        message = MI_T("MI_RESULT_METHOD_NOT_FOUND");
        errorCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_NAMESPACE_NOT_EMPTY : 
        message = MI_T("MI_RESULT_NAMESPACE_NOT_EMPTY");
        errorCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_INVALID_ENUMERATION_CONTEXT : 
        message = MI_T("MI_RESULT_INVALID_ENUMERATION_CONTEXT");
        errorCategory = MI_ERRORCATEGORY_METADATA_ERROR;
        break;
    case MI_RESULT_INVALID_OPERATION_TIMEOUT : 
        message = MI_T("MI_RESULT_INVALID_OPERATION_TIMEOUT");
        errorCategory = MI_ERRORCATEGORY_INVALID_ARGUMENT;
        break;
    case MI_RESULT_PULL_HAS_BEEN_ABANDONED : 
        message = MI_T("MI_RESULT_PULL_HAS_BEEN_ABANDONED");
        errorCategory = MI_ERRORCATEGORY_OPERATION_STOPPED;
        break;
    case MI_RESULT_PULL_CANNOT_BE_ABANDONED : 
        message = MI_T("MI_RESULT_PULL_CANNOT_BE_ABANDONED");
        errorCategory = MI_ERRORCATEGORY_CLOS_EERROR;
        break;
    case MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED : 
        message = MI_T("MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED");
        errorCategory = MI_ERRORCATEGORY_NOT_IMPLEMENTED;
        break;
    case MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED : 
        message = MI_T("MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED");
        errorCategory = MI_ERRORCATEGORY_NOT_IMPLEMENTED;
        break;
    case MI_RESULT_SERVER_LIMITS_EXCEEDED : 
        message = MI_T("MI_RESULT_SERVER_LIMITS_EXCEEDED");
        errorCategory = MI_ERRORCATEGORY_RESOURCE_BUSY;
        break;
    case MI_RESULT_SERVER_IS_SHUTTING_DOWN : 
        message = MI_T("MI_RESULT_SERVER_IS_SHUTTING_DOWN");
        errorCategory = MI_ERRORCATEGORY_RESOURCE_UNAVAILABLE;
        break;        
    default:
        errorCategory = MI_ERRORCATEGORY_NOT_SPECIFIED;
        message = MI_T("Unrecognized MI_Result");
        break;        
    }

    return CreateOMIError_shared(message, miResult, MI_RESULT_TYPE_MI, errorCategory, classDecl, omiError);
}

_Use_decl_annotations_
MI_Result MI_CALL CreateOMIError_FromMiResult(
    MI_Result miResult,
    MI_Instance **omiError)
{
    return CreateOMIError_FromMiResult_shared(miResult, &OMI_Error_rtti, omiError);
}

_Use_decl_annotations_
MI_Result MI_CALL CreateOMIDebugError_FromMiResult(
    MI_Result miResult,
    MI_Instance **omiError)
{
    return CreateOMIError_FromMiResult_shared(miResult, &OMI_DebugError_rtti, omiError);
}
