/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/*
**==============================================================================
**
** Codec Interface (MI) Internal
**
**     This file defines the 'grey' part of management interface, 
**     that is not needed by provider, by may be consumed by c++
**     provider interface and provider manager
**
**==============================================================================
*/

#ifndef _mi_codec_h
#define _mi_codec_h

#include <MI.h>

#if !defined(_MSC_VER)
#include <common/linux/sal.h>
#endif

#if defined(_MSC_VER)
#pragma pack(push,8)
#endif

/* Magic number using internally */
#if defined(_MSC_VER)
#define cCodecMagic ((MI_Uint64)0xFFEEDDCCFFEEDDCC)
#else
#define cCodecMagic ((MI_Uint64)0xFFEEDDCCFFEEDDCCULL)
#endif

#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast(disable:28922)
#endif


/* Binary Serializer Flags */
//#define MI_SERIALIZER_FLAGS_CLASS_DEEP 0x1 // defined in MI.h. flags defined below MUST not conflict with this
#define MI_BINARY_SERIALIZER_FLAGS_INCLUDE_CLASS_REFERENCE  0x2
#define MI_BINARY_SERIALIZER_FLAGS_INCLUDE_CLASS_ID 0x4 
#define MI_BINARY_SERIALIZER_FLAGS_CLASS_NOMETHODS 0x8
#define MI_BINARY_SERIALIZER_FLAGS_CLASS_FLAT 0x10
#define MI_BINARY_SERIALIZER_FLAGS_CLASS_FLAT_NOMETHODS 0x20

/* Supported MOF format */
#define MOFCODEC_FORMAT_V1 MI_T("MI_MOF_CIMV2_EXTV1")
#define MOFCODEC_FORMAT MOFCODEC_FORMAT_V1

/* MOF schema validation option name */
#define MOFCODEC_SCHEMA_VALIDATION_OPTION_NAME          MI_T("SchemaValidation")

/* MOF schema validation option name for ignoring properties from schema*/
#define MOFCODEC_SCHEMA_VALIDATION_OPTION_IGNOREPROPERTYLIST          MI_T("SchemaValidationIgnorePropertyList")

/* MOF schema validation option's value */
#define MOFCODEC_SCHEMA_VALIDATION_DEFAULT              MI_T("Default")
#define MOFCODEC_SCHEMA_VALIDATION_STRICT               MI_T("Strict")
#define MOFCODEC_SCHEMA_VALIDATION_LOOSE                MI_T("Loose")
#define MOFCODEC_SCHEMA_VALIDATION_IGNORE_PROPERTYTYPE  MI_T("IgnorePropertyType")
#define MOFCODEC_SCHEMA_VALIDATION_IGNORE               MI_T("IgnoreSchema")
#define MOFCODEC_SCHEMA_VALIDATION_DEFAULT_IGNORE_PROPERTIES    MI_T("DefaultIgnoreProperties")
#define MOFCODEC_SCHEMA_VALIDATION_STRICT_IGNORE_PROPERTIES   MI_T("StrictIgnoreProperties")



/* MOF error type */
#define MI_RESULT_TYPE_MOF_PARSER MI_T("MOFPARSER")

/* Define a class array structure type */
typedef struct _MI_ClassA
{
    MI_Class** data;
    MI_Uint32 size;
}
MI_ClassA;

typedef struct _Aliases
{
    MI_Uint32 size;
    MI_Uint32 capacity;
    MI_Uint32 pos;
    _Field_size_(capacity) MI_Uint32 *data;
}
Aliases;

/*
**==============================================================================
**
** ExtFunctionTable
**
**==============================================================================
*/

typedef struct _ExtFunctionTable
{
    MI_SerializerFT ft;

    /* The next index to be assigned to an instance alias. */
    MI_Uint32 nextAliasIndex;

    /* Used to generate instance aliases */
    Aliases aliases;
}
ExtFunctionTable;

/*
**==============================================================================
**
** Extended array structure for managing deserialization result
**
**==============================================================================
*/
typedef struct _MI_ExtendedArray
{
    MI_Array arr;
    MI_Uint64 reserved1;
    ptrdiff_t reserved2;
    ptrdiff_t reserved3;
    ptrdiff_t reserved4;
}
MI_ExtendedArray;

typedef void (MI_CALL *MI_ExtendedArray_Delete)(_Inout_ MI_ExtendedArray* self);
typedef struct _MI_ExtendedArrayFT MI_ExtendedArrayFT;
struct _MI_ExtendedArrayFT
{
    MI_ExtendedArray_Delete Delete;
};

/* Define a callback function type that provides included file buffer */
typedef MI_Result (MI_CALL *MI_Deserializer_GetIncludedFileBuffer)(
    _In_opt_ void *context,
    _In_z_ const MI_Char *fileName,
    _Outptr_result_buffer_(*bufferLength) MI_Uint8 **fileBuffer,
    _Out_ MI_Uint32 *bufferLength);

/* Define a callback function type that free the included file buffer */
typedef void (MI_CALL * MI_Deserializer_FreeIncludedFileBuffer)(
    _In_opt_ void *context,
    _In_ MI_Uint8 *Buffer);

typedef MI_Result (MI_CALL *MI_Deserializer_ClassObjectNeededOnId)(
    _In_opt_ void *context,
    _In_ MI_Uint64 classId,
    _Outptr_ MI_Class **requestedClassObject);

typedef MI_Result (MI_CALL *MI_Deserializer_ClassObjectAndId)(
    _In_opt_ void *context,
    _In_ MI_Uint64 classId,
    _In_ MI_Class *classObject);

/* Define a callback function type that retrieve MI_QualifierDecl */
/* Parameter 'decl': Please don't touch name field of decl; */
/*                   Caller needs to fill up all other fields based on the name */
/* If value field is not null, then caller needs to guarantee the value field */
/* is valid till the deserialization complete. */
typedef MI_Result (MI_CALL * MI_Deserializer_QualifierDeclNeeded)(
    _In_opt_ void *context,
    _Inout_ MI_QualifierDecl *decl);

/* Define a structure for deserializer callbacks */
typedef struct _MI_DeserializerCallbacks
{
    /* Class schema callback */
    void * classObjectNeededContext ;
    _In_opt_ MI_Deserializer_ClassObjectNeeded classObjectNeeded  ;

    /* Included file buffer callback */
    void * includedFileContext;
    MI_Deserializer_GetIncludedFileBuffer getIncludedFileContent;
    MI_Deserializer_FreeIncludedFileBuffer freeIncludedFileContent;

    /* instanceResult is reserved, must be NULL */
    /* Instance result callbacks, only needed for instance deserialization */
    void * instanceResultContext;
    MI_OperationCallback_Instance instanceResult;

    /* classResult is reserved, must be NULL */
    /* Class result callbacks, only needed for class deserialization */
    void * classResultContext;
    MI_OperationCallback_Class classResult;

    /* Class schema callback based on class Id */
    void * classObjectNeededOnIdContext;
    MI_Deserializer_ClassObjectNeededOnId classObjectNeededOnId;

    /* **Temporary** callback to return classid for a particular class 
    * This will be used by deserializeClass routine to report Id associated with the class 
    * If this callback is provided, MI_Deserializer_DeserializeClassArray will report all deserialized classes
    * through this callback. No classes will be returned through MI_Deserializer_DeserializeClassArray's output parameter "classObjects" */
    void * classObjectAndIdContext;
    MI_Deserializer_ClassObjectAndId classObjectAndId;

    /* Qualifier declaration callback based on qualifier name */
    void * qualifierDeclNeededContext;
    MI_Deserializer_QualifierDeclNeeded qualifierDeclNeeded;
}
MI_DeserializerCallbacks;

/*
**=============================================================================
**
** MI_DeserializerFT_INTL
**
** Deserialier function table.
**
**=============================================================================
*/
struct _MI_DeserializerFT_INTL
{
    MI_DeserializerFT ft;

    MI_Result (MI_CALL *DeserializeClassArray)(
        _Inout_ MI_Deserializer *deserializer, 
        _In_ MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_ MI_DeserializerCallbacks * callbacks,
        _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer,
        _In_ MI_Uint32 serializedBufferLength,
        _In_opt_ MI_ClassA *classes,
        _In_opt_z_ const MI_Char *serverName,
        _In_opt_z_ const MI_Char *namespaceName,
        _Out_opt_ MI_Uint32 *serializedBufferRead,
        _Outptr_result_maybenull_ MI_ClassA **classObjects,
        _Always_(_Outptr_opt_result_maybenull_) MI_Instance **cimErrorDetails);

    MI_Result (MI_CALL *DeserializeInstanceArray)(
        _Inout_ MI_Deserializer *deserializer,
        _In_ MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_ MI_DeserializerCallbacks * callbacks,
        _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
        _In_ MI_Uint32 serializedBufferLength, 
        _In_opt_ MI_ClassA *classes,
        _Out_opt_ MI_Uint32 *serializedBufferRead,
        _Outptr_result_maybenull_ MI_InstanceA **instanceObjects,
        _Always_(_Outptr_opt_result_maybenull_) MI_Instance **cimErrorDetails);
};

typedef struct _MI_DeserializerFT_INTL MI_DeserializerFT_INTL;

MI_INLINE MI_Boolean MI_Serializer_IsInternal(
    _Inout_ MI_Serializer *serializer)
{
    return (serializer->reserved1 == cCodecMagic);
}

MI_INLINE MI_Boolean MI_Deserializer_IsInternal(
    _Inout_ MI_Deserializer *deserializer)
{
    return (deserializer->reserved1 == cCodecMagic);
}

MI_INLINE MI_Boolean MI_Array_IsInternal(_In_ MI_Array *array)
{
    MI_ExtendedArray* arrex = (MI_ExtendedArray*)array;
#ifdef _PREFAST_
#pragma prefast(suppress:28922)
#endif
    return (arrex && arrex->reserved1 == cCodecMagic);
}

/* TODO:- For portability make all of these macros instead of _INTL functions */
#ifdef MI_Serializer_Close
#undef MI_Serializer_Close
#endif

#define MI_Serializer_Close MI_Serializer_Close_INTL

#ifdef MI_Serializer_SerializeClass
#undef MI_Serializer_SerializeClass
#endif

#define MI_Serializer_SerializeClass MI_Serializer_SerializeClass_INTL 

#ifdef MI_Serializer_SerializeInstance
#undef MI_Serializer_SerializeInstance
#endif

#define MI_Serializer_SerializeInstance MI_Serializer_SerializeInstance_INTL

MI_INLINE MI_Result MI_Serializer_Close_INTL(
    _Inout_ MI_Serializer *serializer)
{
    if(MI_Serializer_IsInternal(serializer))
    {
        return ((MI_SerializerFT*)(serializer->reserved2))->Close(serializer);
    }
    else
    {
        return mi_clientFT->serializerFT->Close(serializer);
    }
}

MI_INLINE MI_Result MI_Serializer_SerializeClass_INTL(
    _Inout_ MI_Serializer *serializer, 
    MI_Uint32 flags, 
    _In_ const MI_Class *classObject, 
   _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded)
{
    if(MI_Serializer_IsInternal(serializer))
    {
        return ((MI_SerializerFT*)(serializer->reserved2))->SerializeClass(serializer, flags, classObject, clientBuffer, clientBufferLength, clientBufferNeeded);
    }
    else
    {
        return mi_clientFT->serializerFT->SerializeClass(serializer, flags, classObject, clientBuffer, clientBufferLength, clientBufferNeeded);
    }
}

MI_INLINE MI_Result MI_Serializer_SerializeInstance_INTL(
   _Inout_ MI_Serializer *serializer, 
   MI_Uint32 flags, 
   _In_ const MI_Instance *instanceObject, 
   _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded)
{
    if(MI_Serializer_IsInternal(serializer))
    {
        return ((MI_SerializerFT*)(serializer->reserved2))->SerializeInstance(serializer, flags, instanceObject, clientBuffer, clientBufferLength, clientBufferNeeded);
    }
    else
    {
        return mi_clientFT->serializerFT->SerializeInstance(serializer, flags, instanceObject, clientBuffer, clientBufferLength, clientBufferNeeded);
    }
}

#ifdef MI_Deserializer_Close
#undef MI_Deserializer_Close
#endif

#define MI_Deserializer_Close MI_Deserializer_Close_INTL

#ifdef MI_Deserializer_DeserializeClass
#undef MI_Deserializer_DeserializeClass
#endif

#define MI_Deserializer_DeserializeClass MI_Deserializer_DeserializeClass_INTL

#ifdef MI_Deserializer_Class_GetClassName
#undef MI_Deserializer_Class_GetClassName
#endif

#define MI_Deserializer_Class_GetClassName MI_Deserializer_Class_GetClassName_INTL

#ifdef MI_Deserializer_Class_GetParentClassName
#undef MI_Deserializer_Class_GetParentClassName
#endif

#define MI_Deserializer_Class_GetParentClassName MI_Deserializer_Class_GetParentClassName_INTL

#ifdef MI_Deserializer_DeserializeInstance
#undef MI_Deserializer_DeserializeInstance
#endif

#define MI_Deserializer_DeserializeInstance MI_Deserializer_DeserializeInstance_INTL

#ifdef MI_Deserializer_Instance_GetClassName
#undef MI_Deserializer_Instance_GetClassName
#endif

#define MI_Deserializer_Instance_GetClassName MI_Deserializer_Instance_GetClassName_INTL

MI_INLINE MI_Result MI_Deserializer_Close_INTL(
    _Inout_ MI_Deserializer *deserializer)
{
    if(MI_Deserializer_IsInternal(deserializer))
    {
        return ((MI_DeserializerFT*)(deserializer->reserved2))->Close(deserializer);
    }
    else
    {
        return mi_clientFT->deserializerFT->Close(deserializer);
    }
}

MI_INLINE MI_Result MI_Deserializer_DeserializeClass_INTL(
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
    if(MI_Deserializer_IsInternal(deserializer))
    {
        return ((MI_DeserializerFT*)(deserializer->reserved2))->DeserializeClass(deserializer, flags, serializedBuffer, serializedBufferLength, parentClass, serverName, namespaceName, classObjectNeeded, classObjectNeededContext, serializedBufferRead, classObject, cimErrorDetails);
    }
    else
    {
        return mi_clientFT->deserializerFT->DeserializeClass(deserializer, flags, serializedBuffer, serializedBufferLength, parentClass, serverName, namespaceName, classObjectNeeded, classObjectNeededContext, serializedBufferRead, classObject, cimErrorDetails);
    }
}

MI_INLINE MI_Result MI_Deserializer_Class_GetClassName_INTL(
    _Inout_ MI_Deserializer *deserializer, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _Out_writes_opt_(*classNameLength) MI_Char *className,
    _Inout_ MI_Uint32 *classNameLength,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    if(MI_Deserializer_IsInternal(deserializer))
    {
        return ((MI_DeserializerFT*)(deserializer->reserved2))->Class_GetClassName(deserializer, serializedBuffer, serializedBufferLength, className, classNameLength, cimErrorDetails);
    }
    else
    {
        return mi_clientFT->deserializerFT->Class_GetClassName(deserializer, serializedBuffer, serializedBufferLength, className, classNameLength, cimErrorDetails);
    }
}


MI_INLINE MI_Result MI_Deserializer_Class_GetParentClassName_INTL(
    _Inout_ MI_Deserializer *deserializer, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _Out_writes_opt_(*parentClassNameLength) MI_Char *parentClassName,
    _Inout_ MI_Uint32 *parentClassNameLength,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    if(MI_Deserializer_IsInternal(deserializer))
    {
        return ((MI_DeserializerFT*)(deserializer->reserved2))->Class_GetParentClassName(deserializer, serializedBuffer, serializedBufferLength, parentClassName, parentClassNameLength, cimErrorDetails);
    }
    else
    {
        return mi_clientFT->deserializerFT->Class_GetParentClassName(deserializer, serializedBuffer, serializedBufferLength, parentClassName, parentClassNameLength, cimErrorDetails);
    }
}

MI_INLINE MI_Result MI_Deserializer_DeserializeInstance_INTL(
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
    if(MI_Deserializer_IsInternal(deserializer))
    {
        return ((MI_DeserializerFT*)(deserializer->reserved2))->DeserializeInstance(deserializer, flags, serializedBuffer, serializedBufferLength, classObjects, numberClassObjects, classObjectNeeded, classObjectNeededContext, serializedBufferRead, instanceObject, cimErrorDetails);
    }
    else
    {
        return mi_clientFT->deserializerFT->DeserializeInstance(deserializer, flags, serializedBuffer, serializedBufferLength, classObjects, numberClassObjects, classObjectNeeded, classObjectNeededContext, serializedBufferRead, instanceObject, cimErrorDetails);
    }    
}


MI_INLINE MI_Result MI_Deserializer_Instance_GetClassName_INTL(
    _Inout_ MI_Deserializer *deserializer, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _Out_writes_opt_(*classNameLength) MI_Char *className,
    _Inout_ MI_Uint32 *classNameLength,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails)
{
    if(MI_Deserializer_IsInternal(deserializer))
    {
        return ((MI_DeserializerFT*)(deserializer->reserved2))->Instance_GetClassName(deserializer, serializedBuffer, serializedBufferLength, className, classNameLength, cimErrorDetails);
    }
    else
    {
        return mi_clientFT->deserializerFT->Instance_GetClassName(deserializer, serializedBuffer, serializedBufferLength, className, classNameLength, cimErrorDetails);
    }    
}


/* API that deserialize one or multiple class(es) from given buffer */
MI_INLINE MI_Result MI_Deserializer_DeserializeClassArray(
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
    if(MI_Deserializer_IsInternal(deserializer))
    {
        return ((MI_DeserializerFT_INTL*)(deserializer->reserved2))->DeserializeClassArray(
            deserializer, flags, options, callbacks, serializedBuffer, serializedBufferLength, classes, serverName, namespaceName, serializedBufferRead, classObjects, cimErrorDetails);
    }
    else
    {
        if (cimErrorDetails)
            *cimErrorDetails = NULL;
        return MI_RESULT_INVALID_PARAMETER;
    }
}

/* API that deserialize one or multiple instance(s) from given buffer */
MI_INLINE MI_Result MI_Deserializer_DeserializeInstanceArray(
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
    if (MI_Deserializer_IsInternal(deserializer))
    {
        return ((MI_DeserializerFT_INTL*)(deserializer->reserved2))->DeserializeInstanceArray(
            deserializer, flags, options, callbacks, serializedBuffer, serializedBufferLength, classes, serializedBufferRead, instanceObjects, cimErrorDetails);
    }
    else
    {
        if (cimErrorDetails)
            *cimErrorDetails = NULL;
        return MI_RESULT_INVALID_PARAMETER;
    }
}

/* Release deserialized class array */
MI_INLINE void _MI_Deserializer_ReleaseArray(_Inout_ MI_Array* array)
{
    if (MI_Array_IsInternal(array))
    {
        MI_ExtendedArray* arr = (MI_ExtendedArray*)array;
        ((MI_ExtendedArrayFT*)(arr->reserved2))->Delete(arr);
    }
}

/* Release deserialized class array */
MI_INLINE void MI_Deserializer_ReleaseClassArray(
    _Inout_ MI_ClassA *classObjects)
{
    _MI_Deserializer_ReleaseArray((MI_Array*)classObjects);
}

/* Release deserialized instance array */
MI_INLINE void MI_Deserializer_ReleaseInstanceArray(
    _Inout_ MI_InstanceA *instanceObjects)
{
    _MI_Deserializer_ReleaseArray((MI_Array*)instanceObjects);
}

/*
**==============================================================================
**
** EXTERNC
** BEGIN_EXTERNC
** END_EXTERNC
**
**==============================================================================
*/

#if defined(__cplusplus)
# define EXTERNC extern "C"
# define BEGIN_EXTERNC extern "C" {
# define END_EXTERNC }
#else
# define EXTERNC /* empty */
# define BEGIN_EXTERNC /* empty */
# define END_EXTERNC /* empty */
#endif

BEGIN_EXTERNC

MI_Result MI_MAIN_CALL MI_Application_NewSerializer_Mof(
    _Inout_ MI_Application *application, 
    MI_Uint32 flags,
    _In_z_ MI_Char *format, 
    _Out_ MI_Serializer *serializer);

MI_Result MI_MAIN_CALL MI_Application_NewDeserializer_Mof(
    _Inout_ MI_Application *application, 
    MI_Uint32 flags,
    _In_z_ MI_Char *format, 
    _Out_ MI_Deserializer *deserializer);

MI_Result MI_MAIN_CALL MI_Application_NewSerializer_Binary(
    _Inout_ MI_Application *application, 
    MI_Uint32 flags,
    _In_z_ MI_Char *format, 
    _Out_ MI_Serializer *serializer);

MI_Result MI_MAIN_CALL MI_Application_NewDeserializer_Binary(
    _Inout_ MI_Application *application, 
    MI_Uint32 flags,
    _In_z_ MI_Char *format, 
    _Out_ MI_Deserializer *deserializer);

END_EXTERNC

#if defined(_MSC_VER)
#pragma pack(pop)
#endif

#ifdef _PREFAST_
#pragma prefast(pop)
#endif

#endif /* _mi_codec_h */
