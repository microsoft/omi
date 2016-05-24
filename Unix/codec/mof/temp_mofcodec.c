/*
 * Copyright (C) 2012 Microsoft Corporation
 * All rights reserved.
 */




#include <micodec.h>
#include "codecimpl.h"


#ifdef _PREFAST_
# pragma prefast (push)
# pragma prefast (disable: 28252)
# pragma prefast (disable: 28253)
#endif

#include <pal/strings.h>

#ifdef _PREFAST_
# pragma prefast (pop)
#endif

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif

/* Maximum allowed buffer size */
const MI_Uint32 MAX_BUFFER_SIZE = 50*1024*1024;

MI_INLINE MI_Result MI_CALL MI_Deserializer_Close_MOF(
    _Inout_ MI_Deserializer *deserializer)
{
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MI_Deserializer_Class_GetClassName_MOF(
    _Inout_ MI_Deserializer *deserializer, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _Out_writes_opt_(*classNameLength) MI_Char *className,
    _Inout_ MI_Uint32 *classNameLength,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return MI_RESULT_NOT_SUPPORTED;
}


MI_INLINE MI_Result MI_CALL MI_Deserializer_Class_GetParentClassName_MOF(
    _Inout_ MI_Deserializer *deserializer, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _Out_writes_opt_(*parentClassNameLength) MI_Char *parentClassName,
    _Inout_ MI_Uint32 *parentClassNameLength,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return MI_RESULT_NOT_SUPPORTED;
}

MI_INLINE MI_Result MI_CALL MI_Deserializer_Instance_GetClassName_MOF(
    _Inout_ MI_Deserializer *deserializer, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _Out_writes_opt_(*classNameLength) MI_Char *className,
    _Inout_ MI_Uint32 *classNameLength,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    return MI_RESULT_NOT_SUPPORTED;
}


/* API that deserialize one or multiple class(es) from given buffer */
MI_INLINE MI_Result MI_CALL MI_Deserializer_DeserializeClassArray_MOF(
    _Inout_ MI_Deserializer *deserializer, 
    _In_ MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_ MI_DeserializerCallbacks * callbacks,
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer,
    _In_ MI_Uint32 serializedBufferLength,
    _In_opt_ MI_ClassA *classes,
    _In_opt_z_ const MI_Char *serverName  ,
    _In_opt_z_ const MI_Char *namespaceName,
    _Out_opt_ MI_Uint32 *serializedBufferRead,
    _Outptr_result_maybenull_ MI_ClassA **classObjects,
    _Always_(_Outptr_opt_result_maybenull_) MI_Instance **cimErrorDetails)
{
    MI_MofCodec codec;
    MI_Result r;
    memset(&codec, 0, sizeof(MI_MofCodec));
    *classObjects = NULL;
    if (cimErrorDetails)
    {
        *cimErrorDetails = NULL;
    }
    if (serializedBufferRead)
    {
        *serializedBufferRead = 0;
    }

    /* setup error handler on codec */
    MI_MofCodec_SetupErrorHandler(&codec);

    if (flags != 0)
    {
        MI_MofCodec_ParameterIsNonZero(&codec, MI_T("flags"));
        r = MI_RESULT_INVALID_PARAMETER;
        goto Return;
    }
    if (serializedBuffer == NULL)
    {
        MI_MofCodec_ParameterIsNull(&codec, MI_T("serializedBuffer"));
        r = MI_RESULT_INVALID_PARAMETER;
        goto Return;
    }
    if ((serializedBufferLength < 4) || (serializedBufferLength > MAX_BUFFER_SIZE))
    {
        MI_MofCodec_ParameterOutOfRange(&codec, MI_T("serializedBufferLength"), 4, MAX_BUFFER_SIZE, serializedBufferLength);
        r = MI_RESULT_INVALID_PARAMETER;
        goto Return;
    }
    r = MI_MofCodec_Init(flags, options, callbacks, serializedBuffer, serializedBufferLength, classes, serverName, namespaceName, DeserializeClassArray, &codec);
    if (r != MI_RESULT_OK)
    {
        goto Return;
    }
    r = MI_MofCodec_Deserialize(&codec);
    if (r != MI_RESULT_OK)
    {
        goto Return;
    }
    if (codec.classObjects)
    {
        *classObjects = codec.classObjects;
    }

Return:
    if (r != MI_RESULT_OK)
    {
        if (cimErrorDetails && codec.errorInstance)
        {
            *cimErrorDetails = codec.errorInstance;
            codec.errorInstance = NULL;
        }
    }
    if (serializedBufferRead)
    {
        *serializedBufferRead = codec.bufferreadlength;
    }
    MI_MofCodec_Delete(&codec);
    return r;
}

/* API that deserialize one or multiple instance(s) from given buffer */
MI_INLINE MI_Result MI_CALL MI_Deserializer_DeserializeInstanceArray_MOF(
    _Inout_ MI_Deserializer *deserializer,
    _In_ MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_ MI_DeserializerCallbacks * callbacks,
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    _In_ MI_Uint32 serializedBufferLength, 
    _In_opt_ MI_ClassA *classes,
    _Out_opt_ MI_Uint32 *serializedBufferRead,
    _Outptr_result_maybenull_ MI_InstanceA **instanceObjects,
    _Always_(_Outptr_opt_result_maybenull_) MI_Instance **cimErrorDetails)
{
    MI_MofCodec codec;
    MI_Result r;
    memset(&codec, 0, sizeof(MI_MofCodec));
    *instanceObjects = NULL;
    if (cimErrorDetails)
    {
        *cimErrorDetails = NULL;
    }
    if (serializedBufferRead)
    {
        *serializedBufferRead = 0;
    }

    /* setup error handler on codec */
    MI_MofCodec_SetupErrorHandler(&codec);

    if (flags != 0)
    {
        MI_MofCodec_ParameterIsNonZero(&codec, MI_T("flags"));
        r = MI_RESULT_INVALID_PARAMETER;
        goto Return;
    }
    if (serializedBuffer == NULL)
    {
        MI_MofCodec_ParameterIsNull(&codec, MI_T("serializedBuffer"));
        r = MI_RESULT_INVALID_PARAMETER;
        goto Return;
    }
    if ((serializedBufferLength < 4) || (serializedBufferLength > MAX_BUFFER_SIZE))
    {
        MI_MofCodec_ParameterOutOfRange(&codec, MI_T("serializedBufferLength"), 4, MAX_BUFFER_SIZE, serializedBufferLength);
        r = MI_RESULT_INVALID_PARAMETER;
        goto Return;
    }
    r = MI_MofCodec_Init(flags, options, callbacks, serializedBuffer, serializedBufferLength, classes, NULL, NULL, DeserializeInstanceArray, &codec);
    if (r != MI_RESULT_OK)
    {
        goto Return;
    }
    r = MI_MofCodec_Deserialize(&codec);
    if (r != MI_RESULT_OK)
    {
        goto Return;
    }
    if (codec.instanceObjects)
    {
        *instanceObjects = codec.instanceObjects;
    }

Return:
    if (r != MI_RESULT_OK)
    {
        if (cimErrorDetails && codec.errorInstance)
        {
            *cimErrorDetails = codec.errorInstance;
            codec.errorInstance = NULL;
        }
    }
    if (serializedBufferRead)
    {
        *serializedBufferRead = codec.bufferreadlength;
    }
    MI_MofCodec_Delete(&codec);
    return r;
}

MI_INLINE MI_Result MI_CALL MI_Deserializer_DeserializeClass_MOF(
    _Inout_ MI_Deserializer *deserializer, 
    MI_Uint32 flags, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength,
    _In_opt_ MI_Class *parentClass, 
    _In_opt_z_ const MI_Char *serverName,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_ MI_Deserializer_ClassObjectNeeded classObjectNeeded,
    _In_opt_ void *classObjectNeededContext,
    _Out_opt_ MI_Uint32 *serializedBufferRead,
    _Outptr_opt_result_maybenull_ MI_Class **classObject,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    MI_Result r;
    MI_DeserializerCallbacks cb;
    MI_ClassA parentclassarray;
    MI_ClassA *pParentclassarray = NULL;
    MI_ClassA* resultclassarray;
    memset(&cb, 0, sizeof(MI_DeserializerCallbacks));

    if (parentClass)
    {
        parentclassarray.data = &parentClass;
        parentclassarray.size = 1;
        pParentclassarray = &parentclassarray;
    }

    cb.classObjectNeeded = classObjectNeeded;
    cb.classObjectNeededContext = classObjectNeededContext;

    if (classObject)
    {
        *classObject = NULL;
    }

    r = MI_Deserializer_DeserializeClassArray_MOF(deserializer,
        flags,
        NULL,
        &cb,
        serializedBuffer,
        serializedBufferLength,
        pParentclassarray,
        serverName,
        namespaceName,
        serializedBufferRead,
        &resultclassarray,
        cimErrorDetails);
    if (r != MI_RESULT_OK)
    {
        return r;
    }

    {
        MI_MofCodec codec;
        memset(&codec, 0, sizeof(MI_MofCodec));
        /* setup error handler on codec */
        MI_MofCodec_SetupErrorHandler(&codec);
        if (resultclassarray)
        {
            if (resultclassarray->size > 1)
            {
                MI_MofCodec_InvalidResultClassCount(&codec);
                if (cimErrorDetails && codec.errorInstance)
                {
                    *cimErrorDetails = codec.errorInstance;
                    codec.errorInstance = NULL;
                }
                r = MI_RESULT_FAILED;
            }
            else if (classObject && (resultclassarray->size == 1))
            {
                *classObject = resultclassarray->data[0];
                resultclassarray->data[0] = NULL;
            }
        }
        MI_MofCodec_Delete(&codec);
    }
    MI_Deserializer_ReleaseClassArray(resultclassarray);
    return r;
}

MI_INLINE MI_Result MI_CALL MI_Deserializer_DeserializeInstance_MOF(
    _Inout_ MI_Deserializer *deserializer, 
    MI_Uint32 flags, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _In_reads_opt_(numberClassObjects) MI_Class **classObjects, 
    MI_Uint32 numberClassObjects,
    _In_opt_ MI_Deserializer_ClassObjectNeeded classObjectNeeded,
    _In_opt_ void *classObjectNeededContext,
    _Out_opt_ MI_Uint32 *serializedBufferRead,
    _Outptr_opt_result_maybenull_ MI_Instance **instanceObject,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    MI_Result r;
    MI_DeserializerCallbacks cb;
    MI_ClassA classarray;
    MI_InstanceA* resultinstancearray;
    memset(&cb, 0, sizeof(MI_DeserializerCallbacks));

    classarray.data = classObjects;
    classarray.size = numberClassObjects;

    cb.classObjectNeeded = classObjectNeeded;
    cb.classObjectNeededContext = classObjectNeededContext;

    if (instanceObject)
    {
        *instanceObject = NULL;
    }

    r = MI_Deserializer_DeserializeInstanceArray_MOF(deserializer,
        flags,
        NULL,
        &cb,
        serializedBuffer,
        serializedBufferLength,
        &classarray,
        serializedBufferRead,
        &resultinstancearray,
        cimErrorDetails);
    if (r != MI_RESULT_OK)
    {
        return r;
    }

    {
        MI_MofCodec codec;
        memset(&codec, 0, sizeof(MI_MofCodec));
        /* setup error handler on codec */
        MI_MofCodec_SetupErrorHandler(&codec);

        if (resultinstancearray)
        {
            if (resultinstancearray->size > 1)
            {
                MI_MofCodec_InvalidResultInstanceCount(&codec);
                if (cimErrorDetails && codec.errorInstance)
                {
                    *cimErrorDetails = codec.errorInstance;
                    codec.errorInstance = NULL;
                }
                r = MI_RESULT_FAILED;
            }
            else if (instanceObject && (resultinstancearray->size == 1))
            {
                *instanceObject = resultinstancearray->data[0];
                resultinstancearray->data[0] = NULL;
            }
        }
        MI_MofCodec_Delete(&codec);
    }
    MI_Deserializer_ReleaseInstanceArray(resultinstancearray);
    return r;
}

const MI_DeserializerFT_INTL _deserializerMofFT =
{
    {
        MI_Deserializer_Close_MOF,
        MI_Deserializer_DeserializeClass_MOF,
        MI_Deserializer_Class_GetClassName_MOF,
        MI_Deserializer_Class_GetParentClassName_MOF,
        MI_Deserializer_DeserializeInstance_MOF,
        MI_Deserializer_Instance_GetClassName_MOF,
    },
    MI_Deserializer_DeserializeClassArray_MOF,
    MI_Deserializer_DeserializeInstanceArray_MOF,
};


MI_Result MI_MAIN_CALL MI_Application_NewDeserializer_Mof(
    _Inout_ MI_Application *application, 
    MI_Uint32 flags,
    _In_z_ MI_Char *format, 
    _Out_ MI_Deserializer *deserializer)
{
    if (application == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (flags != 0)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (format == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    if(deserializer == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (Tcscasecmp(format, MOFCODEC_FORMAT) != 0)
    {
        return MI_RESULT_NOT_SUPPORTED;
    }
    memset(deserializer, 0, sizeof(MI_Deserializer));
    deserializer->reserved1 = cCodecMagic;
    deserializer->reserved2 = (ptrdiff_t)&_deserializerMofFT;
    return MI_RESULT_OK;
}

