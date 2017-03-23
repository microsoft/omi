/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */

#ifndef _XML_DESERIALIZER_H_
#define _XML_DESERIALIZER_H_

#include <MI.h>

BEGIN_EXTERNC

MI_Result MI_CALL XmlDeserializer_Create(
    _Inout_ MI_Application *application, 
    MI_Uint32 flags,
    _In_z_ MI_Char *format, 
    _Out_ MI_Deserializer *deserializer);

MI_Result MI_CALL XmlDeserializer_Close(
    _Inout_ MI_Deserializer *deserializer);

MI_Result MI_CALL XmlDeserializer_DeserializeClass(
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
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result MI_CALL XmlDeserializer_Class_GetClassName(
    _Inout_ MI_Deserializer *deserializer, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _Out_writes_opt_(*classNameLength) MI_Char *className,
    _Inout_ MI_Uint32 *classNameLength,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result MI_CALL XmlDeserializer_Class_GetParentClassName(
    _Inout_ MI_Deserializer *deserializer, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _Out_writes_opt_(*parentClassNameLength) MI_Char *parentClassName,
    _Inout_ MI_Uint32 *parentClassNameLength,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result MI_CALL XmlDeserializer_DeserializeInstance(
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
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails);

MI_Result MI_CALL XmlDeserializer_Instance_GetClassName(
    _Inout_ MI_Deserializer *deserializer, 
    _In_reads_(serializedBufferLength) MI_Uint8 *serializedBuffer, 
    MI_Uint32 serializedBufferLength, 
    _Out_writes_opt_(*classNameLength) MI_Char *className,
    _Inout_ MI_Uint32 *classNameLength,
    _Outptr_opt_result_maybenull_ MI_Instance **cimErrorDetails);

END_EXTERNC

#endif /* _XML_DESERIALIZER_H_ */
