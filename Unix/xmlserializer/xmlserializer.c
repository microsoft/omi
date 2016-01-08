/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */
#include <stdio.h>
#include <common.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <base/log.h>
#include <base/helpers.h>
#include <base/class.h>
#include <base/instance.h>
#include <base/types.h>
#include <base/field.h>
#include "xmlserializer.h"

//******************************************XMLSERIALIZER Creation/Deletion************************

/* Create serializer object */
MI_Result MI_CALL XmlSerializer_Create(
    _In_ MI_Application *application,
    MI_Uint32 flags,
    _In_z_ MI_Char *format,
    _Out_ MI_Serializer *serializer)
{
    if ((application == NULL) || (flags != 0) || (format == NULL) || (serializer == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (Tcscmp(format, PAL_T("MI_XML")) != 0) //TODO: Case sensitive?
    {
        return MI_RESULT_NOT_SUPPORTED;
    }
    memset(serializer, 0, sizeof(*serializer));

    return MI_RESULT_OK;
}

/* Close serializer object */
MI_Result MI_CALL XmlSerializer_Close(
    _Inout_ MI_Serializer *serializer)
{
    return MI_RESULT_OK;
}

//******************************************Class/Instance Serialization logic************************
#define IsOptionTrue(flags, option) ((flags & (option)) != 0)
#define SERIALIZE_NO_ESCAPE 0

//Length of string literal
#define WCSLEN(string) ((sizeof(string)/sizeof(string[0]))-1)

/* Preferred write mechanism for string literal to the buffer.  We do sizeof string which is a compile-time calculation. */
#define WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferUsed, bufferToWrite, escapingDepth, result) WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferUsed, bufferToWrite, WCSLEN(bufferToWrite), escapingDepth, result)

/* Preferred write mechanism as we don't need to Tcslen the buffer to write */
static void WriteBuffer_StringWithLength(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferNeeded, _In_reads_z_(bufferToWriteLength) const MI_Char *bufferToWrite, MI_Uint32 bufferToWriteLength, MI_Uint32 escapingDepth, _Inout_ MI_Result *result);

/* Don't use unless we really don't know the length as we will Tcslen the buffer to write */
#define WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferUsed, bufferToWrite, escapingDepth, result) WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferUsed, bufferToWrite, Tcslen(bufferToWrite), escapingDepth, result)

/* writes the textual version of MI_Type */
static void WriteBuffer_MiType(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferUsed, MI_Type type, MI_Uint32 escapingDepth, _Inout_ MI_Result *result);

/* writes the textual version of MI_Array based on MI_Type. */
static void WriteBuffer_MiValueArray(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferUsed, MI_Type type, _In_ const MI_Array *value, MI_Uint32 escapingDepth, _Inout_ MI_Result *result);

/* writes the textual version of MI_Value based on MI_Type. */
static void WriteBuffer_MiValue(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferUsed, MI_Type type, _In_opt_ const MI_Value *value, MI_Boolean includeTags, MI_Uint32 escapingDepth, _Inout_ MI_Result *result);

/* writes the textual version of MI_Qualifier array. */
static void WriteBuffer_MiQualifierSet(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferUsed, _In_ const MI_QualifierSet *qualifierSet, MI_Uint32 flagsToSerializeAsQualifiers, MI_Boolean isQualOnInheritedElement, _Inout_ MI_Result *result);
static void WriteBuffer_MiParamPropertyQualifierSet(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferUsed, _In_ const MI_QualifierSet *qualifierSet, MI_Uint32 flagsToSerializeAsQualifiers, MI_Boolean isQualOnInheritedElement, MI_Boolean isEmbeddedProperty, _In_opt_ const MI_Char *referenceClassForEmbeddedProperty, _Inout_ MI_Result *result);
static void WriteBuffer_EmbeddedPropertyQualifier(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferNeeded, _In_opt_ const MI_Char *referenceClassForEmbeddedProperty, _Inout_ MI_Result *result);

static void WriteBuffer_MiFlagQualifiers(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,MI_Uint32 clientBufferLength,_Inout_ MI_Uint32 *clientBufferNeeded,MI_Uint32 flagsToSerializeAsQualifiers,_Inout_ MI_Result *result);

/* writes the textual version of %CIMName. (name="name") */
static void WriteBuffer_CimName(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferUsed, _In_z_ const MI_Char* name, MI_Uint32 escapingDepth, _Inout_ MI_Result *result);

static void WriteBuffer_Uint32(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferNeeded, MI_Uint32 number, _Inout_ MI_Result *result);

static void WriteBuffer_SerializeClass(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferNeeded, MI_Uint32 flags, _In_ const MI_Class *miClass, _In_opt_z_ const MI_Char *namespaceName,_In_opt_z_ const MI_Char *serverName,_Out_ MI_Result *result);
static void WriteBuffer_RecurseInstanceClass(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferNeeded, MI_Uint32 flags, _In_ const MI_Class *miClass, _In_opt_z_ const MI_Char *namespaceName,_In_opt_z_ const MI_Char *serverName,_Inout_ const MI_Char *writtenClasses[50], _Inout_ MI_Uint32 *writtenClassCount, _Out_ MI_Result *result);
static void WriteBuffer_InstanceEmbeddedClass(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferNeeded, MI_Uint32 serializeFlags, _In_ const MI_Instance *instance, _Inout_ const MI_Char *writtenClasses[50], _Inout_ MI_Uint32 *writtenClassCount, _Out_ MI_Result *result);
static void WriteBuffer_Instance(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,MI_Uint32 clientBufferLength,_Inout_ MI_Uint32 *clientBufferNeeded,_In_ const MI_Instance *instance,MI_Uint32 escapingDepth, _Out_ MI_Result *result);
static void WriteBuffer_InstanceReference(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,MI_Uint32 clientBufferLength,_Inout_ MI_Uint32 *clientBufferNeeded,_In_opt_z_ const MI_Char *namespaceName, _In_opt_z_ const MI_Char *serverName, _In_ const MI_Instance *refValue, MI_Uint32 escapingDepth, _Inout_ MI_Result *result);

static void WriteBuffer_MiPropertyDecls(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer, MI_Uint32 clientBufferLength, _Inout_ MI_Uint32 *clientBufferNeeded, _In_ const MI_Class *miClass, MI_Uint32 flags, _In_z_ const MI_Char *className,_In_opt_z_ const MI_Char *namespaceName, _In_opt_z_ const MI_Char *serverName , _In_opt_ const char *instanceStart, MI_Uint32 escapingDepth, _Inout_ MI_Result *result);

//Write an instance parameter MI_<type>Field
static void WriteBuffer_MiTypeField(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,MI_Uint32 clientBufferLength,_Inout_ MI_Uint32 *clientBufferNeeded,MI_Type type,_In_ const char *fieldValue, MI_Uint32 escapingDepth, _Inout_ MI_Result *result);

//Write an instance array parameter MI_ArrayField
static void WriteBuffer_MiArrayField(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,MI_Uint32 clientBufferLength,_Inout_ MI_Uint32 *clientBufferNeeded,MI_Type type,_In_ MI_ArrayField *arrayField, MI_Uint32 escapingDepth, _Inout_ MI_Result *result);

static void WriteBuffer_NAMESPACEPATH(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,MI_Uint32 clientBufferLength,_Inout_ MI_Uint32 *clientBufferNeeded,_In_z_ const MI_Char *namespaceName, _In_z_ const MI_Char *serverName, MI_Uint32 escapingDepth, _Inout_ MI_Result *result);
static void WriteBuffer_LOCALNAMESPACEPATH(_Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,MI_Uint32 clientBufferLength,_Inout_ MI_Uint32 *clientBufferNeeded,_In_z_ const MI_Char *namespaceName, MI_Uint32 escapingDepth, _Inout_ MI_Result *result);

static void WriteBuffer_Instance(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
    _In_ const MI_Instance *instance_,
    MI_Uint32 escapingDepth,
   _Out_ MI_Result *result)
{
    // No one is using OSC_Instance structure inside OMI/WinOMI;
    // so I am assuming all instances here are going to be MI_Instances
    // so getting rid of this OSC_Instance from the reused code and replacing it with MI_Instance
    // in the future if someone adds OSC_Instance in OMI/WinOMI then add this back
    // MI_Instance *instance = (MI_Instance*)((OSC_Instance*)instance_)->self;  //In case this is dynamic instance point to the real one, otherwise it points to ourself!
    const MI_Instance *instance = instance_;
    MI_Class classOfInstance = MI_CLASS_NULL;
    const MI_Char *classNameOfInstance = NULL;

    *result = MI_RESULT_OK;

    *result = MI_Instance_GetClassExt(instance, &classOfInstance);

    *result = GetClassExtendedFt(&classOfInstance)->GetClassName(&classOfInstance, &classNameOfInstance);
    
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<INSTANCE"), escapingDepth, result);

    /* %ClassName; */
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" CLASSNAME=\""), escapingDepth, result);
    if(classNameOfInstance)
    {
        WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, classNameOfInstance, escapingDepth, result);
    }
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\""), escapingDepth, result);

    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(">"), escapingDepth, result);

    /* PROPERTY|PROPERTY.ARRAY|PROPERTY.REFERENCE */
    // casting done since it does not compile on non-windows
    WriteBuffer_MiPropertyDecls(clientBuffer, clientBufferLength, clientBufferNeeded, &classOfInstance, MI_TRUE, classNameOfInstance, instance->nameSpace, instance->serverName, (char*)instance, escapingDepth, result);

    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</INSTANCE>"), escapingDepth, result);
}

static void WriteBuffer_RecurseInstanceClass(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    MI_Uint32 flags,
    _In_ const MI_Class *miClass, 
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *serverName,
    _Inout_ const MI_Char *writtenClasses[50],
    _Inout_ MI_Uint32 *writtenClassCount,
   _Out_ MI_Result *result)
{
    MI_Uint32 loop;
    const MI_Char *miClassName = NULL;
    const MI_Char *miParentClassName = NULL;
    MI_Class miParentClass;

    *result = MI_RESULT_OK;
    /* %CIMName; */
    *result = GetClassExtendedFt(miClass)->GetClassName(miClass, &miClassName);

    /* Have we already written this class? */
    for (loop = 0; loop != *writtenClassCount; loop++)
    {
#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast (disable: 26007)
#endif
        if (Tcscasecmp(writtenClasses[loop], miClassName)==0)
#ifdef _MSC_VER
#pragma prefast(pop)
#endif
        {
            return; /*We have already written this class so we are done */
        }
    }

    /* %SuperClass; */
    GetClassExtendedFt(miClass)->GetParentClassName(miClass, &miParentClassName);
    if (miParentClassName)
    {
        GetClassExtendedFt(miClass)->GetParentClassExt(miClass, &miParentClass);
        WriteBuffer_RecurseInstanceClass(clientBuffer, clientBufferLength, clientBufferNeeded, flags, &miParentClass, namespaceName, serverName, writtenClasses, writtenClassCount, result);
    }
    if (*writtenClassCount == 50)
    {
        *result = MI_RESULT_FAILED; /*Overrite error in this case as this is very fatal!*/
        return;
    }
    
    /* Add name to list so we know we have written it already */
    writtenClasses[*writtenClassCount] = miClassName;
    (*writtenClassCount)++;

    /* Now we can serialize the class */
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<VALUE.OBJECT>"), SERIALIZE_NO_ESCAPE, result);
    /* Wmi serializer marks the flag 0 here, so removing the serializeDeep flag */
    WriteBuffer_SerializeClass(clientBuffer, clientBufferLength, clientBufferNeeded, (flags & ~(MI_SERIALIZER_FLAGS_CLASS_DEEP)), miClass, namespaceName, serverName, result);
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</VALUE.OBJECT>"), SERIALIZE_NO_ESCAPE, result);
}

static void WriteBuffer_InstanceEmbeddedClass(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    MI_Uint32 serializeFlags,
    _In_ const MI_Instance *instance,
    _Inout_ const MI_Char *writtenClasses[50],
    _Inout_ MI_Uint32 *writtenClassCount,
    _Out_ MI_Result *result)
{
    MI_Uint32 loop;
    *result = MI_RESULT_OK;
    for (loop = 0; loop != instance->classDecl->numProperties; loop++)
    {
        const MI_Char *name;
        MI_Value value;
        MI_Type type;
        MI_Uint32 flags;
        MI_Result tmpresult;

        if ((instance->classDecl->properties[loop]->type != MI_INSTANCE) &&
            (instance->classDecl->properties[loop]->type != MI_REFERENCE) && 
            (instance->classDecl->properties[loop]->type != MI_INSTANCEA) &&
            (instance->classDecl->properties[loop]->type != MI_REFERENCEA))
            continue;

        tmpresult = MI_Instance_GetElementAt(instance, loop, &name, &value, &type, &flags);
        if (tmpresult != MI_RESULT_OK)
        {
            *result = tmpresult; //overwrite as something serious happened
        }
        else
        {
            MI_Instance **embeddedInstance = NULL;
            MI_Uint32 embeddedInstanceCount = 0;
            MI_Uint32 embeddedInstanceLoop = 0;

            if (instance->classDecl->properties[loop]->type & MI_ARRAY)
            {
                MI_Array *instanceArray = (MI_Array*)&value.instancea;
                embeddedInstance = (MI_Instance**)instanceArray->data;
                embeddedInstanceCount = instanceArray->size;
            }
            else
            {
                embeddedInstance = &value.instance;
                embeddedInstanceCount = 1;
            }

            for (;embeddedInstanceLoop != embeddedInstanceCount; embeddedInstanceLoop++)
            {
                //Dump this class
                const MI_Char *namespaceName = NULL;
                const MI_Char *serverName = NULL;
                MI_Class classOfInstance = MI_CLASS_NULL;
                if (flags & MI_FLAG_NULL)
                    continue;

                if ((embeddedInstance[embeddedInstanceLoop]->nameSpace && (instance->nameSpace == NULL)) ||
                    (instance->nameSpace  && embeddedInstance[embeddedInstanceLoop]->nameSpace && (Tcscasecmp(instance->nameSpace, embeddedInstance[embeddedInstanceLoop]->nameSpace) != 0)))
                {
                    namespaceName = embeddedInstance[embeddedInstanceLoop]->nameSpace;
                }
                if ((embeddedInstance[embeddedInstanceLoop]->serverName && (instance->serverName == NULL)) ||
                    (instance->serverName  && embeddedInstance[embeddedInstanceLoop]->serverName && (Tcscasecmp(instance->serverName, embeddedInstance[embeddedInstanceLoop]->serverName) != 0)))
                {
                    serverName = embeddedInstance[embeddedInstanceLoop]->serverName;
                }
                MI_Instance_GetClassExt(embeddedInstance[embeddedInstanceLoop], &classOfInstance);
                WriteBuffer_RecurseInstanceClass(clientBuffer, clientBufferLength, clientBufferNeeded, serializeFlags, &classOfInstance, namespaceName, serverName, writtenClasses, writtenClassCount, result);

                //Recurse in case it has any embedded classes
                WriteBuffer_InstanceEmbeddedClass(clientBuffer, clientBufferLength, clientBufferNeeded, serializeFlags, embeddedInstance[embeddedInstanceLoop], writtenClasses, writtenClassCount, result);
            }
        }
    }
}

static void WriteBuffer_SerializeClass(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    MI_Uint32 flags,
    _In_ const MI_Class *miClass,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *serverName,
    _Out_ MI_Result *result)
{
    const MI_Char *miClassName = NULL;
    const MI_Char *miParentClassName = NULL;
    MI_QualifierSet qualifierSet;
    MI_Uint32 numQualifiers = 0;

    *result = MI_RESULT_OK;
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<CLASS"), SERIALIZE_NO_ESCAPE, result);

    /* %CIMName; */
    *result = GetClassExtendedFt(miClass)->GetClassName(miClass, &miClassName);
    if(miClassName)
    {
        WriteBuffer_CimName(clientBuffer, clientBufferLength, clientBufferNeeded, miClassName, SERIALIZE_NO_ESCAPE, result);
    }

    /* %SuperClass; */
    GetClassExtendedFt(miClass)->GetParentClassName(miClass, &miParentClassName);
    if (miParentClassName)
    {
        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" SUPERCLASS=\""), SERIALIZE_NO_ESCAPE, result);
        WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, miParentClassName, SERIALIZE_NO_ESCAPE, result);
        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\""), SERIALIZE_NO_ESCAPE, result);
    }

    /* %DERIVATION; */
    if(IsOptionTrue(flags, MI_SERIALIZER_FLAGS_INCLUDE_INHERITANCE_HIERARCHY))
    {
        const MI_Class *currentClass = miClass;
        MI_Class currentSuperClass;
        MI_Uint32 countOfClasses = 0;

        GetClassExtendedFt(currentClass)->GetParentClassExt(currentClass, &currentSuperClass);

        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" DERIVATION=\""), SERIALIZE_NO_ESCAPE, result);
        while(miParentClassName)
        {
            trace_XmlSerializer_CurrentParent(tcs(miParentClassName));

            // before writing first superclassname; you would not need a separator otherwise you will
            if(countOfClasses != 0)
            {
                // preventing infinite loop
                if(countOfClasses == 0xFFFFFFFF)
                {
                    *result = MI_RESULT_FAILED;
                    return;
                }

                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(","), SERIALIZE_NO_ESCAPE, result);
            }

#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast (disable: 26018)
#endif
            // write the super class name in the list
            WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, miParentClassName, SERIALIZE_NO_ESCAPE, result);

#ifdef _MSC_VER
#pragma prefast(pop)
#endif

            // clear out the classname we just wrote
            miParentClassName = NULL;

            // go up one level in the parent chain
            currentClass = &currentSuperClass;

            // if there is still a superclass, get its name
            if(GetClassExtendedFt(currentClass)->GetParentClassExt(currentClass, &currentSuperClass) == MI_RESULT_OK)
            {
                *result = GetClassExtendedFt(&currentSuperClass)->GetClassName(&currentSuperClass, &miParentClassName);
            }

            countOfClasses++;
        }

        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\""), SERIALIZE_NO_ESCAPE, result);
    }

    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(">"), SERIALIZE_NO_ESCAPE, result);

    /* QUALIFIERS */
    if(IsOptionTrue(flags, MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS))
    {
        MI_Uint32 classFlags = 0;
        GetClassExtendedFt(miClass)->GetClassQualifierSet(miClass, &qualifierSet);
        GetQualifierSetFt(&qualifierSet)->GetQualifierCount(&qualifierSet, &numQualifiers);
        GetClassExtendedFt(miClass)->GetClassFlagsExt(miClass, &classFlags);
        WriteBuffer_MiQualifierSet(clientBuffer, clientBufferLength, clientBufferNeeded, &qualifierSet, classFlags, MI_FALSE, result);
    }

    /* PROPERTY|PROPERTY.ARRAY|PROPERTY.REFERENCE */
    WriteBuffer_MiPropertyDecls(clientBuffer, clientBufferLength, clientBufferNeeded, miClass, flags, miClassName, namespaceName, serverName, NULL, SERIALIZE_NO_ESCAPE, result);

    /* METHOD */
    {
        MI_Uint32 methodCount;
        MI_Uint32 totalMethodCount;
        MI_Uint32 parameterCount;
        const MI_Char *methodName = NULL;
        MI_QualifierSet methodQualifierSet;
        MI_ParameterSet parameterSet;
        MI_Uint32 methodParameterCount;
        const MI_Char *parameterName = NULL;
        MI_Type parameterType;
        MI_Uint32 parameterSubscript;
        MI_Char *referenceClass = NULL;
        MI_Char *methodOriginClass = NULL;
        MI_Char *methodPropagatorClass = NULL;
        MI_QualifierSet parameterQualifierSet;
        MI_Uint32 methodFlags = 0;
        MI_Uint32 parameterFlags = 0;        

        GetClassExtendedFt(miClass)->GetMethodCount(miClass, &totalMethodCount);

        for (methodCount = 0; methodCount != totalMethodCount; methodCount++)
        {
            MI_Boolean isInheritedElement = MI_FALSE;

            GetClassExtendedFt(miClass)->GetMethodAtExt(miClass, methodCount, &methodName, &methodOriginClass, &methodPropagatorClass, &methodQualifierSet, &parameterSet, &methodFlags);

            /* If not serializing deep and we are not the propagator of the property then we need to skip this one */
            if (!IsOptionTrue(flags, MI_SERIALIZER_FLAGS_CLASS_DEEP | MI_SERIALIZER_FLAGS_INCLUDE_INHERITED_ELEMENTS) && methodPropagatorClass && Tcscmp(methodPropagatorClass, miClassName)!=0)
            {
                continue;
            }
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<METHOD"), SERIALIZE_NO_ESCAPE, result);

            /* %CIMName; */
            WriteBuffer_CimName(clientBuffer, clientBufferLength, clientBufferNeeded, methodName, SERIALIZE_NO_ESCAPE, result);

            GetParameterSetExtendedFt(&parameterSet)->GetParameterCount(&parameterSet, &methodParameterCount);

            GetParameterSetExtendedFt(&parameterSet)->GetMethodReturnType(&parameterSet, &parameterType, &parameterQualifierSet);

            /* %CIMType; */
            WriteBuffer_MiType(clientBuffer, clientBufferLength, clientBufferNeeded, (MI_Type)(parameterType&~MI_ARRAY), SERIALIZE_NO_ESCAPE, result);

            /* %ClassOrigin;  */
            if (IsOptionTrue(flags, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN) &&
                methodOriginClass)
            {
                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" CLASSORIGIN=\""), SERIALIZE_NO_ESCAPE, result);
                WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, methodOriginClass, SERIALIZE_NO_ESCAPE, result);
                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\""), SERIALIZE_NO_ESCAPE, result);
            }
            /* %Propagated;  */
            if (methodPropagatorClass &&
                (Tcscasecmp(methodPropagatorClass, miClassName) != 0))
            {
                isInheritedElement = MI_TRUE;
                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" PROPAGATED=\"true\""), SERIALIZE_NO_ESCAPE, result);
            }

            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(">"), SERIALIZE_NO_ESCAPE, result);

            /* QUALIFIERS */
            if(IsOptionTrue(flags, MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS))
            {
                WriteBuffer_MiQualifierSet(clientBuffer, clientBufferLength, clientBufferNeeded, &methodQualifierSet, methodFlags, isInheritedElement, result);
            }

            /* even though this loop starts from 0, the GetParameterAt method increments the index passed to it so we will get the parameters from the index 1 */
            for (parameterCount = 0; parameterCount < methodParameterCount; parameterCount++)
            {
                GetParameterSetExtendedFt(&parameterSet)->GetParameterAtExt(&parameterSet, parameterCount, &parameterName, &parameterType,
                            &parameterSubscript, &referenceClass, &parameterQualifierSet, &parameterFlags);

                /* Start of PARAMETER | PARAMETER.REFERENCE | PARAMETER_ARRAY | PARAMETER.REFARRAY  */
                if (parameterType == MI_REFERENCE)
                {
                    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<PARAMETER.REFERENCE"), SERIALIZE_NO_ESCAPE, result);
                }
                else if (parameterType == MI_REFERENCEA)
                {
                    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<PARAMETER.REFARRAY"), SERIALIZE_NO_ESCAPE, result);
                }
                else if (parameterType & MI_ARRAY)
                {
                    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<PARAMETER.ARRAY"), SERIALIZE_NO_ESCAPE, result);
                }
                else
                {
                    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<PARAMETER"), SERIALIZE_NO_ESCAPE, result);
                }
                /* %CIMName; */
                WriteBuffer_CimName(clientBuffer, clientBufferLength, clientBufferNeeded, parameterName, SERIALIZE_NO_ESCAPE, result);

                if ((parameterType != MI_REFERENCE) &&
                    (parameterType != MI_REFERENCEA))
                {
                    /* %CIMType; -- PARAMETER and PARAMETER.ARRAY */
                    WriteBuffer_MiType(clientBuffer, clientBufferLength, clientBufferNeeded, parameterType, SERIALIZE_NO_ESCAPE, result);
                }
                else if (referenceClass)
                {
                    /* %ReferenceClass; -- PROPERTY.REFERENCE and PROPERTY.REFARRAY*/
                    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" REFERENCECLASS=\""), SERIALIZE_NO_ESCAPE, result);
                    WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, referenceClass, SERIALIZE_NO_ESCAPE, result);
                    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\""), SERIALIZE_NO_ESCAPE, result);
                }

                if ((parameterType & MI_ARRAY) &&
                    (parameterSubscript != 0))
                {
                    /* %ArraySize; -- PROPERTY.ARRAY and PROPERTY.REFARRAY */
                    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" ARRAYSIZE=\""), SERIALIZE_NO_ESCAPE, result);
                    WriteBuffer_Uint32(clientBuffer, clientBufferLength, clientBufferNeeded, parameterSubscript, result);
                    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\""), SERIALIZE_NO_ESCAPE, result);
                }

                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(">"), SERIALIZE_NO_ESCAPE, result);

                /* QUALIFIERS */
                if(IsOptionTrue(flags, MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS))
                {
                    WriteBuffer_MiParamPropertyQualifierSet(clientBuffer, clientBufferLength, clientBufferNeeded, &parameterQualifierSet, parameterFlags, MI_FALSE, ((parameterType&~MI_ARRAY) == MI_INSTANCE), referenceClass, result);
                }

                /* End of PARAMETER | PARAMETER.REFERENCE | PARAMETER_ARRAY | PARAMETER.REFARRAY  */
                if (parameterType == MI_REFERENCE)
                {
                    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</PARAMETER.REFERENCE>"), SERIALIZE_NO_ESCAPE, result);
                }
                else if (parameterType == MI_REFERENCEA)
                {
                    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</PARAMETER.REFARRAY>"), SERIALIZE_NO_ESCAPE, result);
                }
                else if (parameterType & MI_ARRAY)
                {
                    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</PARAMETER.ARRAY>"), SERIALIZE_NO_ESCAPE, result);
                }
                else
                {
                    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</PARAMETER>"), SERIALIZE_NO_ESCAPE, result);
                }
            }
            
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</METHOD>"), SERIALIZE_NO_ESCAPE, result);
        }
    }

    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</CLASS>"), SERIALIZE_NO_ESCAPE, result);
}

static void WriteBuffer_MiPropertyDecls(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
   _In_ const MI_Class *miClass,
   MI_Uint32 flags,
   _In_z_ const MI_Char *className,
   _In_opt_z_ const MI_Char *namespaceName,
   _In_opt_z_ const MI_Char *serverName,
   _In_opt_ const char *instanceStart,
   MI_Uint32 escapingDepth,
   _Inout_ MI_Result *result)
{
    MI_Uint32 propertyCount;
    MI_Uint32 totalPropertyCount;
    MI_Value propertyValue;
    MI_Type propertyType;
    MI_Uint32 propertyFlags;
    MI_Uint32 propertySubscript;
    MI_Uint32 propertyOffset;
    MI_QualifierSet propertyQualifierSet;
    const MI_Char *propertyName = NULL;
    MI_Char *propertyReferenceClass = NULL;
    MI_Char *propertyOriginClass = NULL;
    MI_Char *propertyPropagatorClass = NULL;

    GetClassExtendedFt(miClass)->GetElementCount(miClass, &totalPropertyCount);

    /* PROPERTY|PROPERTY.ARRAY|PROPERTY.REFERENCE */
    for (propertyCount = 0; propertyCount != totalPropertyCount; propertyCount++)
    {
        MI_Boolean propertyValueExists = MI_TRUE;
        MI_Boolean propertyValueExistsInDecl = MI_TRUE;
        MI_Boolean isInheritedElement = MI_FALSE;
    
        GetClassExtendedFt(miClass)->GetElementAtExt(miClass, propertyCount, &propertyName, &propertyValue, &propertyValueExistsInDecl,
                    &propertyType, &propertySubscript, &propertyOffset , &propertyReferenceClass, &propertyOriginClass, &propertyPropagatorClass, &propertyQualifierSet, &propertyFlags);

	MI_Instance_GetElementAt((MI_Instance*)instanceStart, propertyCount, &propertyName, &propertyValue, &propertyType, &propertyFlags);

        /* If not serializing deep and we are not the propagator of the property then we need to skip this one */
        //MI_SERIALIZER_FLAGS_CLASS_DEEP
        if (!IsOptionTrue(flags, MI_SERIALIZER_FLAGS_CLASS_DEEP | MI_SERIALIZER_FLAGS_INCLUDE_INHERITED_ELEMENTS)
            && propertyPropagatorClass && Tcscmp(propertyPropagatorClass, className)!=0)
        {
            continue;
        }
        else
        {
            trace_XmlSerializer_WriteBuffer_MiPropertyDecls(tcs(className), tcs(propertyPropagatorClass), tcs(propertyName));
        }

        if (propertyType & MI_ARRAY)
        {
            if (propertyType == MI_REFERENCEA)
            {
                //Properties of type referenceArray cannot be supported.  It is not CIM compliant
                //Overwrite error as this is a hard error.
                *result = MI_RESULT_NOT_SUPPORTED;
                return;
            }
            else
            {
                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<PROPERTY.ARRAY"), escapingDepth, result);
            }
        }
        else if (propertyType == MI_REFERENCE)
        {
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<PROPERTY.REFERENCE"), escapingDepth, result);
        }
        else
        {
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<PROPERTY"), escapingDepth, result);
        }

        /* %CIMName; */
        WriteBuffer_CimName(clientBuffer, clientBufferLength, clientBufferNeeded, propertyName, escapingDepth, result);

        if ((propertyType != MI_REFERENCE) &&
            (propertyType != MI_REFERENCEA))
        {
            /* %CIMType; -- not REFERENCE */
            WriteBuffer_MiType(clientBuffer, clientBufferLength, clientBufferNeeded, propertyType, escapingDepth, result);
        }
        else if (!instanceStart &&
                 propertyReferenceClass &&
                 (propertyType == MI_REFERENCE))
        {
            /* %ReferenceClass; -- REFERENCE only and for classes only */
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" REFERENCECLASS=\""), escapingDepth, result);
            WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, propertyReferenceClass, escapingDepth, result);
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\""), escapingDepth, result);
        }

        /* %ArraySize; -- property arays */
        if ((propertyType & MI_ARRAY) && propertySubscript)
        {
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" ARRAYSIZE=\""), escapingDepth, result);
            WriteBuffer_Uint32(clientBuffer, clientBufferLength, clientBufferNeeded, propertySubscript, result);
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\""), escapingDepth, result);
        }

        /* %ClassOrigin; --implied if it is in the same class? */
        if (IsOptionTrue(flags, MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN) &&
            !instanceStart && propertyOriginClass)            
        {
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" CLASSORIGIN=\""), escapingDepth, result);
            WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, propertyOriginClass, escapingDepth, result);
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\""), escapingDepth, result);
        }

        /* %Propagated; -- false is default, so only needed if it is true */
        if (!instanceStart && propertyPropagatorClass && (Tcscmp(propertyPropagatorClass, className) != 0))
        {
            isInheritedElement = MI_TRUE;
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" PROPAGATED=\"true\""), escapingDepth, result);
        }
        /* %EmbeddedObject; -- type=MI_INSTANCE/MI_INSTANCEA for instances only, class does not have this--class has qualifier */
        if (instanceStart &&
            ((propertyType == MI_INSTANCE) ||
            (propertyType == MI_INSTANCEA)))
        {
            if (propertyReferenceClass == NULL)
            {
                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" EmbeddedObject=\"object\""), escapingDepth, result);
            }
            else
            {
                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" EmbeddedObject=\"instance\" EmbeddedClassName=\""), escapingDepth, result);
                WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, propertyReferenceClass, escapingDepth, result);
                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\""), escapingDepth, result);
            }
        }
        /* MODIFIED is our own attribute that handles the property flag MI_FLAG_NOT_MODIFIED.  It is only relevant for instances. */
        if (instanceStart)
        {
            MI_Uint32 flag = Field_GetFlagsExt(propertyType, (Field *)(instanceStart+propertyOffset));

            if ((flag & MI_FLAG_NOT_MODIFIED) == 0)
            {
                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" MODIFIED=\"TRUE\""), escapingDepth, result);
            }
            if (flag & MI_FLAG_NULL)
            {
                propertyValueExists = MI_FALSE;
            }            
        }

        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(">"), escapingDepth, result);

        /* QUALIFIERS -- class only*/
        if (!instanceStart && IsOptionTrue(flags, MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS))
        {        
            if ((propertyFlags & MI_FLAG_PROPERTY) == 0)
            {
                //Dynamic classes do not have qualifiers, only flags.  They don't even mark a property as being a property!

                //If this is a dynanic instance and this is property is an embedded instance then we need to fabricate a EmbeddedObject qualifier otherwise
                //deserialization will think it is a string
                if ((propertyType&~MI_ARRAY) == MI_INSTANCE)
                {
                    WriteBuffer_EmbeddedPropertyQualifier(clientBuffer, clientBufferLength, clientBufferNeeded, propertyReferenceClass, result);
                }

                WriteBuffer_MiFlagQualifiers(clientBuffer, clientBufferLength, clientBufferNeeded, propertyFlags, result);
            }
            else
            {
                WriteBuffer_MiParamPropertyQualifierSet(clientBuffer, clientBufferLength, clientBufferNeeded, &propertyQualifierSet, propertyFlags, isInheritedElement, ((propertyType&~MI_ARRAY) == MI_INSTANCE), propertyReferenceClass, result);
            }
        }

        /* Values and closing element */
        if (propertyType & MI_ARRAY)
        {
            if (propertyType == MI_REFERENCEA)
            {
                //Property arrays are not supported in CIM or in serialization.
                //This is a hard error overwriting any other error that may be there.
                *result = MI_RESULT_NOT_SUPPORTED;
                return;
            }
            else
            {
                /* VALUE.ARRAY*/
                if (instanceStart)
                {
#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast (disable: 26007)
#endif
                    if (propertyValueExists)
                        WriteBuffer_MiArrayField(clientBuffer, clientBufferLength, clientBufferNeeded, propertyType, (MI_ArrayField*)(&propertyValue), escapingDepth, result);
#ifdef _MSC_VER
#pragma prefast(pop)
#endif
                }
                else
                {
                    if (propertyValueExistsInDecl && ((propertyType & MI_FLAG_NULL) == 0))
                        WriteBuffer_MiValueArray(clientBuffer, clientBufferLength, clientBufferNeeded, propertyType, (MI_Array*)(&propertyValue), SERIALIZE_NO_ESCAPE, result);
                }

                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</PROPERTY.ARRAY>"), escapingDepth, result);
            }
        }
        else if (propertyType == MI_REFERENCE)
        {
            MI_Instance *refValue = NULL;
            if (instanceStart)
            {
                MI_Instance *realInst = (MI_Instance*)((Instance*)instanceStart)->self; /* Get real pointer in case it is a dynamic instance */
                char *realInstPtr = (char*) realInst;
                
                MI_ReferenceField *field = (MI_ReferenceField *)(realInstPtr+propertyOffset);

                refValue = field->value;

            }
            else
            {
                if (propertyValueExistsInDecl)
                {
                    refValue = propertyValue.instance;
                }
            }

            if (refValue)
            {
                WriteBuffer_InstanceReference(clientBuffer, clientBufferLength, clientBufferNeeded, namespaceName, serverName, refValue, escapingDepth, result);
            }
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</PROPERTY.REFERENCE>"), escapingDepth, result);
        }
        else
        {
            /* VALUE */
            if (instanceStart)
            {
		if (!(propertyFlags & MI_FLAG_NULL))
		{
		    WriteBuffer_MiTypeField(clientBuffer, clientBufferLength, clientBufferNeeded, propertyType, (char*)&propertyValue, escapingDepth, result);
		}
            }
            else
            {
                if(propertyValueExistsInDecl)
                    WriteBuffer_MiValue(clientBuffer, clientBufferLength, clientBufferNeeded, propertyType, (MI_Value*)(&propertyValue), MI_TRUE, SERIALIZE_NO_ESCAPE, result);
            }

            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</PROPERTY>"), escapingDepth, result);
        }
    }
}

MI_INLINE void WriteBuffer_NoneEscapedChar(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
   _In_ const MI_Char charToWrite,
   _Inout_ MI_Result *result)
{
    MI_Uint32 origBufferNeeded = *clientBufferNeeded;
    (*clientBufferNeeded)+=sizeof(MI_Char);
    if ((*result==MI_RESULT_OK) && (*clientBufferNeeded <= clientBufferLength))
    {
        ((MI_Char*)clientBuffer)[origBufferNeeded/sizeof(MI_Char)] = charToWrite;
    }
    else if (*result == MI_RESULT_OK)
    {
        //If error has not already been set then set it now
        *result = MI_RESULT_FAILED;
    }
}
static void WriteBuffer_Char(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
   _In_ const MI_Char charToWrite,
   MI_Uint32 escapingDepth, //0 means no escaping
   _Inout_ MI_Result *result)
{
    static const struct
    {
        const MI_Char* str;
        size_t len;
    } _encode[] =
    {
        { PAL_T("&#0;"), 4 },
        { PAL_T("&#1;"), 4 },
        { PAL_T("&#2;"), 4 },
        { PAL_T("&#3;"), 4 },
        { PAL_T("&#4;"), 4 },
        { PAL_T("&#5;"), 4 },
        { PAL_T("&#6;"), 4 },
        { PAL_T("&#7;"), 4 },
        { PAL_T("&#8;"), 4 },
        { PAL_T("&#9;"), 4 },
        { PAL_T("&#10;"), 5 },
        { PAL_T("&#11;"), 5 },
        { PAL_T("&#12;"), 5 },
        { PAL_T("&#13;"), 5},
        { PAL_T("&#14;"), 5 },
        { PAL_T("&#15;"), 5 },
        { PAL_T("&#16;"), 5 },
        { PAL_T("&#17;"), 5 },
        { PAL_T("&#18;"), 5 },
        { PAL_T("&#19;"), 5 },
        { PAL_T("&#20;"), 5 },
        { PAL_T("&#21;"), 5 },
        { PAL_T("&#22;"), 5 },
        { PAL_T("&#23;"), 5 },
        { PAL_T("&#24;"), 5 },
        { PAL_T("&#25;"), 5 },
        { PAL_T("&#26;"), 5 },
        { PAL_T("&#27;"), 5 },
        { PAL_T("&#28;"), 5 },
        { PAL_T("&#29;"), 5 },
        { PAL_T("&#30;"), 5 },
        { PAL_T("&#31;"), 5 },
        { NULL, 0 },
        { NULL, 0 },
        { PAL_T("&quot;"), 6 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { PAL_T("&amp;"), 5 },
        { PAL_T("&apos;"), 6 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { PAL_T("&lt;"), 4 },
        { NULL, 0 },
        { PAL_T("&gt;"), 4 }
    };

    if ((escapingDepth == 0) ||
        (charToWrite > L'>') ||
        (_encode[(unsigned int)charToWrite].str == NULL))
    {
        WriteBuffer_NoneEscapedChar(clientBuffer, clientBufferLength, clientBufferNeeded, charToWrite, result);
    }
    else
    {
        WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded, _encode[(unsigned int)charToWrite].str, _encode[(unsigned int)charToWrite].len, escapingDepth-1, result);
    }
}

/* Preferred write mechanism as we don't need to Tcslen the buffer to write */
static void WriteBuffer_StringWithLength(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
   _In_reads_z_(bufferToWriteLength) const MI_Char *bufferToWrite,
   MI_Uint32 bufferToWriteLength,
   MI_Uint32 escapingDepth, //0 or SERIALIZE_NO_ESCAPE means no escaping
   _Inout_ MI_Result *result)
{
    if (escapingDepth == 0)
    {
        MI_Uint32 origBufferNeeded = *clientBufferNeeded;
        (*clientBufferNeeded) += (bufferToWriteLength * sizeof(MI_Char));
        if ((*result==MI_RESULT_OK) && (*clientBufferNeeded <= clientBufferLength))
        {
            memcpy(clientBuffer + origBufferNeeded, bufferToWrite, bufferToWriteLength * sizeof(MI_Char));
        }
        else if (*result == MI_RESULT_OK)
        {
            //If error has not already been set then set it now
            *result = MI_RESULT_FAILED;
        }
    }
    else
    {
        MI_Uint32 loop;
        for (loop = 0; loop != bufferToWriteLength; loop++)
        {
            WriteBuffer_Char(clientBuffer, clientBufferLength, clientBufferNeeded, bufferToWrite[loop], escapingDepth, result);
        }
    }
}

/* writes the textual version of MI_Type */
static void WriteBuffer_MiType(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
   MI_Type type,
   MI_Uint32 escapingDepth,
   _Inout_ MI_Result *result)
{
    static struct _mapping { const MI_Char *typeString; MI_Uint32 typeStringLength; } mapping[] =
    {
        {PAL_T("boolean"), WCSLEN(PAL_T("boolean")) },
        {PAL_T("uint8"),  WCSLEN(PAL_T("uint8")) },
        {PAL_T("sint8"),  WCSLEN(PAL_T("sint8")) },
        {PAL_T("uint16"), WCSLEN(PAL_T("uint16")) },
        {PAL_T("sint16"), WCSLEN(PAL_T("sint16")) },
        {PAL_T("uint32"), WCSLEN(PAL_T("uint32")) },
        {PAL_T("sint32"), WCSLEN(PAL_T("sint32")) },
        {PAL_T("uint64"), WCSLEN(PAL_T("uint64")) },
        {PAL_T("sint64"), WCSLEN(PAL_T("sint64")) },
        {PAL_T("real32"), WCSLEN(PAL_T("real32")) },
        {PAL_T("real64"), WCSLEN(PAL_T("real64")) },
        {PAL_T("char16"), WCSLEN(PAL_T("char16")) },
        {PAL_T("datetime"),  WCSLEN(PAL_T("datetime")) },
        {PAL_T("string"), WCSLEN(PAL_T("string")) },
        {PAL_T("unused"), WCSLEN(PAL_T("unused")) },   /* Reference, not used */
        {PAL_T("string"), WCSLEN(PAL_T("string")) }     /* Instance is encoded as a string */
    };
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" TYPE=\""), escapingDepth, result);
    if ((type&~MI_ARRAY) >= sizeof(mapping)/sizeof(mapping[0]))
    {
        WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("unknown"), WCSLEN(PAL_T("unknown")), SERIALIZE_NO_ESCAPE, result);
    }
    else
    {
        WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded, mapping[type&~MI_ARRAY].typeString, mapping[type&~MI_ARRAY].typeStringLength, SERIALIZE_NO_ESCAPE, result);
    }
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\""), escapingDepth, result);
}

/* writes the textual version of MI_Array based on MI_Type. */
static void WriteBuffer_MiValueArray(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
   MI_Type type,
   _In_ const MI_Array *arrayValue,
   MI_Uint32 escapingDepth,
   _Inout_ MI_Result *result)
{
    MI_Uint32 index;
    MI_Type scalarType = (MI_Type)(type&~MI_ARRAY);
    char* ptr;

    if (arrayValue == NULL)
        return;

    ptr = (char*)arrayValue->data;

    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<VALUE.ARRAY>"),escapingDepth, result);
    for(index = 0; index != arrayValue->size; index++)
    {
        WriteBuffer_MiValue(clientBuffer, clientBufferLength, clientBufferNeeded, scalarType, (MI_Value*)ptr, MI_TRUE, escapingDepth, result);

        ptr += Type_SizeOf(scalarType);
    }
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</VALUE.ARRAY>"),escapingDepth, result);
}

/* writes the textual version of MI_Value based on MI_Type. */
static void WriteBuffer_MiValue(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
   MI_Type type,
   _In_opt_ const MI_Value *value,
   MI_Boolean includeTags,
   MI_Uint32 escapingDepth,
   _Inout_ MI_Result *result)
{
    // MI_Char stringbuffer[_CVTBUFSIZE];
    TChar strBufForUnsignedConversion[21];
    TChar strBufForSignedConversion[64];
    const TChar *convertedBuffer = NULL;
    TChar strBufForDatetimeConversion[26];
    size_t convertedSize = 0;

    if (value == NULL)
        return;

    strBufForSignedConversion[0] = PAL_T('\0');
    if (includeTags)
        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<VALUE>"), escapingDepth, result);

    switch(type)
    {
    case MI_BOOLEAN:
    {
        MI_Boolean boolValue = value->boolean;
        if (boolValue)
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("true"), SERIALIZE_NO_ESCAPE, result);
        else
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("false"), SERIALIZE_NO_ESCAPE, result);
        break;
    }
    case MI_UINT8:
        Uint64ToZStr(strBufForUnsignedConversion, value->uint8, &convertedBuffer, &convertedSize);
        WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded,
                        convertedBuffer, convertedSize,
                        SERIALIZE_NO_ESCAPE, result);
        break;
    case MI_SINT8:
        Sint64ToZStr(strBufForSignedConversion, value->sint8, &convertedBuffer, &convertedSize);
        WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded,
                        convertedBuffer, convertedSize,
                        SERIALIZE_NO_ESCAPE, result);
        break;
    case MI_UINT16:
        Uint64ToZStr(strBufForUnsignedConversion, value->uint16, &convertedBuffer, &convertedSize);
        WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded,
                            convertedBuffer, convertedSize,
                            SERIALIZE_NO_ESCAPE, result);
        break;
    case MI_SINT16:
        Sint64ToZStr(strBufForSignedConversion, value->sint16, &convertedBuffer, &convertedSize);
        WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded,
            convertedBuffer, convertedSize,
            SERIALIZE_NO_ESCAPE, result);
        break;
    case MI_UINT32:
        Uint64ToZStr(strBufForUnsignedConversion, value->uint32, &convertedBuffer, &convertedSize); 
        WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded,
                        convertedBuffer, convertedSize,
                        SERIALIZE_NO_ESCAPE, result);
        break;
    case MI_SINT32:
        Sint64ToZStr(strBufForSignedConversion, value->sint32, &convertedBuffer, &convertedSize);
        WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded,
                        convertedBuffer, convertedSize,
                        SERIALIZE_NO_ESCAPE, result);
        break;
    case MI_UINT64:
        Uint64ToZStr(strBufForUnsignedConversion, value->uint64, &convertedBuffer, &convertedSize);
        WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded,
                        convertedBuffer, convertedSize,
                        SERIALIZE_NO_ESCAPE, result);
        break;
    case MI_SINT64:
        Sint64ToZStr(strBufForSignedConversion, value->sint64, &convertedBuffer, &convertedSize);
        WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded,
                            convertedBuffer, convertedSize,
                            SERIALIZE_NO_ESCAPE, result);
        break;
    case MI_REAL32:
    {
#if defined(_MSC_VER)		
        unsigned int old_exponent_format = _set_output_format(_TWO_DIGIT_EXPONENT);		
#endif
        Stprintf(strBufForSignedConversion, MI_COUNT(strBufForSignedConversion), PAL_T("%.7e"), (double)value->real32);
#if defined(_MSC_VER)		        
        _set_output_format(old_exponent_format);
#endif
        WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, strBufForSignedConversion, SERIALIZE_NO_ESCAPE, result);
        break;
    }
    case MI_REAL64:
    {
#if defined(_MSC_VER)		
		unsigned int old_exponent_format = _set_output_format(_TWO_DIGIT_EXPONENT); 	
#endif
        Stprintf(strBufForSignedConversion, MI_COUNT(strBufForSignedConversion), PAL_T("%.16e"), (double)value->real64);
        
#if defined(_MSC_VER)		        
        _set_output_format(old_exponent_format);
#endif        
        WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, strBufForSignedConversion, SERIALIZE_NO_ESCAPE, result);
        break;
    }
    case MI_CHAR16:
        // We decided to encode the MI_Char16 as number itself since if we do not then we have to encode this differently when the MI_Char is char as opposed to when it is wchar_t
        // OMI instance serialization also uses the same logic so this makes it consistent with that
        // WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded, (const MI_Char *)&value->char16, 1, escapingDepth+1, result);
        Uint64ToZStr(strBufForUnsignedConversion, value->char16, &convertedBuffer, &convertedSize);

        WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded,
                        convertedBuffer, convertedSize, 
                        SERIALIZE_NO_ESCAPE, result);
        break;
    case MI_DATETIME:
        {
            const MI_Datetime* p = (const MI_Datetime*)value;

            DatetimeToStr(p, strBufForDatetimeConversion);

            WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, strBufForDatetimeConversion, SERIALIZE_NO_ESCAPE, result);

            break;
        }
    case MI_STRING:
        WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, value->string, escapingDepth+1, result);
        break;
    //case MI_REFERENCE: /* Other code paths handle this */
    //  break;
    case MI_INSTANCE:
        WriteBuffer_Instance(clientBuffer, clientBufferLength, clientBufferNeeded, (MI_Instance*)value->instance, escapingDepth+1, result);

        break;
    default:
        *result = MI_RESULT_FAILED;
    }
    if (includeTags)
        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</VALUE>"), escapingDepth, result);
}

static struct _FlagQualifiers
{
    MI_Uint32 flag;
    const MI_Char *name;

} sFlagQualifiers[] =
{
    { MI_FLAG_KEY, PAL_T("key") },
    { MI_FLAG_REQUIRED, PAL_T("required") },
    { MI_FLAG_STATIC, PAL_T("static") },
    { MI_FLAG_EXPENSIVE, PAL_T("expensive") },
    { MI_FLAG_READONLY, PAL_T("read") },
    { MI_FLAG_IN, PAL_T("in") },
    { MI_FLAG_OUT, PAL_T("out") },
    { MI_FLAG_ABSTRACT, PAL_T("abstract") },
    { MI_FLAG_TERMINAL, PAL_T("terminal") },
    { MI_FLAG_ASSOCIATION, PAL_T("association") },
    { MI_FLAG_INDICATION, PAL_T("indication") },
    // { MI_FLAG_STREAM, PAL_T("stream") },
};

static MI_Uint32 sFlagQualifierCount = sizeof(sFlagQualifiers)/sizeof(sFlagQualifiers[0]);

/* writes the textual version of MI_Qualifier flags. */
static void WriteBuffer_MiFlagQualifiers(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
   MI_Uint32 flagsToSerializeAsQualifiers,   
   _Inout_ MI_Result *result)
{
    MI_Value value;
    MI_Uint32 index;

    value.boolean = MI_TRUE;

    for (index = 0; index != sFlagQualifierCount; index++)
    {
        if (flagsToSerializeAsQualifiers & sFlagQualifiers[index].flag)
        {
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<QUALIFIER"), SERIALIZE_NO_ESCAPE, result);

            /* %CIMName; */
            WriteBuffer_CimName(clientBuffer, clientBufferLength, clientBufferNeeded, sFlagQualifiers[index].name, SERIALIZE_NO_ESCAPE, result);

            /* %CIMType; */
            WriteBuffer_MiType(clientBuffer, clientBufferLength, clientBufferNeeded, MI_BOOLEAN, SERIALIZE_NO_ESCAPE, result);


            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(">"), SERIALIZE_NO_ESCAPE, result);

            /* VALUE */
            WriteBuffer_MiValue(clientBuffer, clientBufferLength, clientBufferNeeded, MI_BOOLEAN, &value, MI_TRUE, SERIALIZE_NO_ESCAPE, result);

            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</QUALIFIER>"), SERIALIZE_NO_ESCAPE, result);
        }
    }
}

// this function looks up the qualifiername in the sQualifierFlags list and
// resets the corresponding flag from the given flags bitmask.
// this could use a hash table lookup but not adding complexity
// since it is a very small table so the lookup will be constant time
static void ResetFlagForQualifier(_Inout_ MI_Uint32 *flags, const MI_Char *qualifierName)
{
    MI_Uint32 index;

    // assumption is that flags has to be non-null
    if(flags == NULL)
	{
        return;
	}

    for (index = 0; index != sFlagQualifierCount; index++)
    {
        if(Tcscasecmp(qualifierName, sFlagQualifiers[index].name) == 0)
        {
            *flags = *flags & (~(sFlagQualifiers[index].flag));
            break;
        }
    }
}

static void WriteBuffer_EmbeddedPropertyQualifier(
     _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
     MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
      _In_opt_ const MI_Char *referenceClassForEmbeddedProperty,
     _Inout_ MI_Result *result)
{
    MI_Type type;
    MI_Value value;
    const MI_Char *qualifierName = NULL;

    if(referenceClassForEmbeddedProperty == NULL)
    {
        type = MI_BOOLEAN;    
        value.boolean = MI_TRUE;
        qualifierName = PAL_T("EmbeddedObject");
    }
    else
    {
        type = MI_STRING;
        value.string = (MI_Char *)referenceClassForEmbeddedProperty;
        qualifierName = PAL_T("EmbeddedInstance");
    }
    
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<QUALIFIER"), SERIALIZE_NO_ESCAPE, result);
    
    /* %CIMName; */
    WriteBuffer_CimName(clientBuffer, clientBufferLength, clientBufferNeeded, qualifierName, SERIALIZE_NO_ESCAPE, result);
    
    /* %CIMType; */
    WriteBuffer_MiType(clientBuffer, clientBufferLength, clientBufferNeeded, type, SERIALIZE_NO_ESCAPE, result);    
    
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(">"), SERIALIZE_NO_ESCAPE, result);
    
    /* VALUE -- embedded instance class name or true for embedded object */
    WriteBuffer_MiValue(clientBuffer, clientBufferLength, clientBufferNeeded, type, &value, MI_TRUE, SERIALIZE_NO_ESCAPE, result);
    
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</QUALIFIER>"), SERIALIZE_NO_ESCAPE, result);

}

static void WriteBuffer_MiQualifierSet(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
   _In_ const MI_QualifierSet *qualifierSet,
   MI_Uint32 flagsToSerializeAsQualifiers,
   MI_Boolean isQualOnInheritedElement,
   _Inout_ MI_Result *result)
{
    WriteBuffer_MiParamPropertyQualifierSet(clientBuffer, clientBufferLength, clientBufferNeeded, qualifierSet, flagsToSerializeAsQualifiers, isQualOnInheritedElement, MI_FALSE, NULL, result);
}

static void WriteBuffer_MiParamPropertyQualifierSet(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
   _In_ const MI_QualifierSet *qualifierSet,
   MI_Uint32 flagsToSerializeAsQualifiers,
   MI_Boolean isQualOnInheritedElement,
   MI_Boolean isEmbeddedProperty,
   _In_opt_ const MI_Char *referenceClassForEmbeddedProperty,   
   _Inout_ MI_Result *result)
{
    MI_Uint32 index;
    MI_Uint32 qualifierCount = 0;
    const MI_Char *qualifierName = NULL;
    MI_Type qualifierType;
    MI_Uint32 qualifierFlags;
    MI_Value qualifierValue;
    MI_Boolean embeddedPropertyQualifierSpecified = 0;

    if(qualifierSet)
    {
        GetQualifierSetFt(qualifierSet)->GetQualifierCount(qualifierSet, &qualifierCount);
    }

    for (index = 0; index != qualifierCount; index++)
    {
        GetQualifierSetFt(qualifierSet)->GetQualifierAt(qualifierSet, index, &qualifierName, &qualifierType, &qualifierFlags, &qualifierValue);

        // Restricted qualifier should not be sent on inherited elements
        if (isQualOnInheritedElement && (qualifierFlags & MI_FLAG_RESTRICTED))
            continue;

        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<QUALIFIER"), SERIALIZE_NO_ESCAPE, result);

        /* %CIMName; */
        WriteBuffer_CimName(clientBuffer, clientBufferLength, clientBufferNeeded, qualifierName, SERIALIZE_NO_ESCAPE, result);

        ResetFlagForQualifier(&flagsToSerializeAsQualifiers, qualifierName);

        // for embeddedProperties, we will see if an explicit EmbeddedObject/EmbeddedInstance qualifier was specified, if it was not
        // we will fabricate it here after the end of the loop
        if(isEmbeddedProperty)
        {
            if(referenceClassForEmbeddedProperty == NULL)
            {
                if(Tcscasecmp(qualifierName, PAL_T("EmbeddedObject")) == 0)
                {
                    embeddedPropertyQualifierSpecified = 1;
                }
            }
            else
            {
                if(Tcscasecmp(qualifierName, PAL_T("EmbeddedInstance")) == 0)
                {
                    embeddedPropertyQualifierSpecified = 1;
                }
            }
        }

        /* %CIMType; */
        WriteBuffer_MiType(clientBuffer, clientBufferLength, clientBufferNeeded, qualifierType, SERIALIZE_NO_ESCAPE, result);

        /* %Propagated; TODO*/

        /* %QualifierFlavor; */
        /* OVERRIDABLE defaults to TRUE so only set if FALSE */
        if (qualifierFlags & MI_FLAG_DISABLEOVERRIDE)
        {
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" OVERRIDABLE=\"false\""), SERIALIZE_NO_ESCAPE, result);
        }
        /* TOSUBCLASS defaults to TRUE, so only add if not set */
        if (qualifierFlags & MI_FLAG_RESTRICTED)
        {
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" TOSUBCLASS=\"false\""), SERIALIZE_NO_ESCAPE, result);
        }
        if (qualifierFlags & MI_FLAG_TRANSLATABLE)
        {
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" TRANSLATABLE=\"true\""), SERIALIZE_NO_ESCAPE, result);
        }

        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(">"), SERIALIZE_NO_ESCAPE, result);

        /* VALUE | VALUE.ARRAY */
        if (qualifierType & MI_ARRAY)
        {
            WriteBuffer_MiValueArray(clientBuffer, clientBufferLength, clientBufferNeeded, (MI_Type)qualifierType, (MI_Array*)(&qualifierValue), SERIALIZE_NO_ESCAPE, result);
        }
        else
        {
            WriteBuffer_MiValue(clientBuffer, clientBufferLength, clientBufferNeeded, (MI_Type)qualifierType, &qualifierValue, MI_TRUE, SERIALIZE_NO_ESCAPE, result);
        }

        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</QUALIFIER>"), SERIALIZE_NO_ESCAPE, result);
    }

    // code to fabricate embedded qualifier
    if(isEmbeddedProperty && !embeddedPropertyQualifierSpecified)
    {
        WriteBuffer_EmbeddedPropertyQualifier(clientBuffer, clientBufferLength, clientBufferNeeded, referenceClassForEmbeddedProperty, result);
    }

    WriteBuffer_MiFlagQualifiers(clientBuffer, clientBufferLength, clientBufferNeeded, flagsToSerializeAsQualifiers, result);
}


/* writes the textual version of %CIMName. (name="name") */
static void WriteBuffer_CimName(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
   _In_z_ const MI_Char* name,
    MI_Uint32 escapingDepth,
   _Inout_ MI_Result *result)
{
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(" NAME=\""), escapingDepth, result);
    WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, name, escapingDepth, result);
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\""), escapingDepth, result);
}

static void WriteBuffer_Uint32(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded,
   MI_Uint32 number,
   _Inout_ MI_Result *result)
{
    // MI_Char stringbuffer[_CVTBUFSIZE];
    TChar strBufForUnsignedConversion[21];
    size_t convertedSize = 0;
    const TChar *convertedBuffer = NULL;
    
    Uint64ToZStr(strBufForUnsignedConversion, number, &convertedBuffer, &convertedSize);

    WriteBuffer_StringWithLength(clientBuffer, clientBufferLength, clientBufferNeeded,
                    convertedBuffer, convertedSize,
                    SERIALIZE_NO_ESCAPE, result);
}

MI_INLINE MI_Boolean _Exists(MI_Type type, const void* field)
{
    return *((MI_Boolean*)((char*)field + Type_SizeOf(type)));
}

static void WriteBuffer_MiTypeField(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    MI_Type type,
    _In_ const char *fieldValue,
    MI_Uint32 escapingDepth,
    _Inout_ MI_Result *result)
{
#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast (disable: 26007)
#endif
        WriteBuffer_MiValue(clientBuffer, clientBufferLength, clientBufferNeeded, type, (MI_Value*)fieldValue, MI_TRUE, escapingDepth, result);
#ifdef _MSC_VER
#pragma prefast(pop)
#endif
}

static void WriteBuffer_MiArrayField(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    MI_Type type,
    _In_ MI_ArrayField *arrayField,
    MI_Uint32 escapingDepth,
    _Inout_ MI_Result *result
   )
{
    MI_Uint32 index;
    MI_Type scalarType = (MI_Type)(type&~MI_ARRAY);
    char* ptr = (char*)arrayField->value.data;

    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<VALUE.ARRAY>"), escapingDepth, result);
    if (ptr)
    {        
	for(index = 0; index != arrayField->value.size; index++)
	{
	    WriteBuffer_MiValue(clientBuffer, clientBufferLength, clientBufferNeeded, scalarType, (MI_Value*)ptr, MI_TRUE, escapingDepth, result);
	    
	    ptr += Type_SizeOf(scalarType);
	}
    }
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</VALUE.ARRAY>"), escapingDepth, result);
}

static void WriteBuffer_LOCALNAMESPACEPATH_Internal(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    _In_z_ const MI_Char *namespaceName,
    MI_Uint32 escapingDepth,
    _Inout_ MI_Result *result)
{
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<NAMESPACE NAME=\""), escapingDepth, result);
    WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, namespaceName, escapingDepth, result);
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\"/>"), escapingDepth, result);
}

static void WriteBuffer_LOCALNAMESPACEPATH(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    _In_z_ const MI_Char *namespaceName,
    MI_Uint32 escapingDepth,
    _Inout_ MI_Result *result)
{
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<LOCALNAMESPACEPATH>"), escapingDepth, result);
    {
        MI_Uint32 uNamespaceLength = Tcslen(namespaceName) + 1;
        // add fault sim shim for all malloc calls in omi
        MI_Char * tNamespace = (MI_Char *)malloc(sizeof(MI_Char)*uNamespaceLength);
        MI_Char * pCurrentNamespace;
        const MI_Char * pSearch;
        if (tNamespace == NULL)
        {
            *result = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            return;
        }
        pCurrentNamespace = tNamespace;
        pSearch = namespaceName;
        // suppose namespaceName could be "a\\b/c\\d//e"
        while(*pSearch != L'\0')
        {
            if (*pSearch == L'/' || *pSearch == L'\\')
            {
                if (pCurrentNamespace != tNamespace)
                {
#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast (disable: 26001)
#endif
                    // write terminator
                    *pCurrentNamespace = L'\0';
#ifdef _MSC_VER
#pragma prefast(pop)
#endif
                    // the namespace part is not empty, write this part to local NAMESPACE
                    WriteBuffer_LOCALNAMESPACEPATH_Internal(clientBuffer, clientBufferLength, clientBufferNeeded, tNamespace, escapingDepth, result);
                    // reset pCurrentNamespace
                    pCurrentNamespace = tNamespace;
                }
            }
            else
            {
                *pCurrentNamespace = *pSearch;
                pCurrentNamespace++;
            }
            pSearch ++;
        }
        if (pCurrentNamespace != tNamespace)
        {
            // write terminator
            *pCurrentNamespace = L'\0';
            // the namespace part is not empty, write this part to local NAMESPACE
            WriteBuffer_LOCALNAMESPACEPATH_Internal(clientBuffer, clientBufferLength, clientBufferNeeded, tNamespace, escapingDepth, result);
        }
        free(tNamespace);
    }
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</LOCALNAMESPACEPATH>"), escapingDepth, result);
}
static void WriteBuffer_NAMESPACEPATH(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    _In_z_ const MI_Char *namespaceName,
    _In_z_ const MI_Char *serverName,
    MI_Uint32 escapingDepth,
    _Inout_ MI_Result *result)
{
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<NAMESPACEPATH><HOST>"), escapingDepth, result);
    WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, serverName, escapingDepth, result);
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</HOST>"), escapingDepth, result);
    WriteBuffer_LOCALNAMESPACEPATH(clientBuffer, clientBufferLength, clientBufferNeeded, namespaceName, escapingDepth, result);
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</NAMESPACEPATH>"), escapingDepth, result);
}

static void WriteBuffer_INSTANCENAME_single(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    _In_ const MI_Instance *refValue,
    MI_Type type,
    _In_ MI_Value *value,
    MI_Uint32 escapingDepth,
    _Inout_ MI_Result *result)
{
    if (type == MI_REFERENCE)
    {
        const MI_Char *namespaceName = NULL;
        const MI_Char *serverName = NULL;
        if ((value->instance->nameSpace && (refValue->nameSpace == NULL)) ||
            (refValue->nameSpace  && value->instance->nameSpace && (Tcscasecmp(refValue->nameSpace, value->instance->nameSpace) != 0)))
        {
            namespaceName = value->instance->nameSpace;
        }
        if ((value->instance->serverName && (refValue->serverName == NULL)) ||
            (refValue->serverName  && value->instance->serverName && (Tcscasecmp(refValue->serverName, value->instance->serverName) != 0)))
        {
            serverName = value->instance->serverName;
        }
        WriteBuffer_InstanceReference(clientBuffer, clientBufferLength, clientBufferNeeded, namespaceName, serverName, value->reference, escapingDepth, result);
    }
    else
    {
        switch(type)
        {
        case MI_BOOLEAN:
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<KEYVALUE VALUETYPE=\"boolean\""), escapingDepth, result);
            break;
        case MI_DATETIME:
        case MI_STRING:
        case MI_CHAR16:
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<KEYVALUE VALUETYPE=\"string\""), escapingDepth, result);
            break;
        default:
            WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<KEYVALUE VALUETYPE=\"numeric\""), escapingDepth, result);
            break;
        }
        WriteBuffer_MiType(clientBuffer, clientBufferLength, clientBufferNeeded, (MI_Type)type, escapingDepth, result);

        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T(">"), escapingDepth, result);

        WriteBuffer_MiValue(clientBuffer, clientBufferLength, clientBufferNeeded, type, value, MI_FALSE, escapingDepth, result);

        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</KEYVALUE>"), escapingDepth, result);
    }
}
static void WriteBuffer_INSTANCENAME(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    _In_ const MI_Instance *refValue,
    MI_Uint32 escapingDepth,
    _Inout_ MI_Result *result)
{
    /* Need to count keys to determine if we need to use KEYBINDING [more than 1 key] or (KEYVALUE|VALUE.REFERENCE) [only 1 key] */
    MI_Uint32 keyCount = 0;
    MI_Uint32 propertyIndex;
    MI_Uint32 totalPropertyCount = 0;
    MI_Class classOfRefValue = MI_CLASS_NULL;
    const MI_Char *classNameOfRefValue = NULL;
    MI_Uint32 propertyFlags;

    *result = MI_Instance_GetClassExt(refValue, &classOfRefValue);

    *result = GetClassExtendedFt(&classOfRefValue)->GetClassName(&classOfRefValue, &classNameOfRefValue);

    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<INSTANCENAME CLASSNAME=\""), escapingDepth, result);
    if(classNameOfRefValue)
    {
        WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, classNameOfRefValue, escapingDepth, result);
    }
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\">"), escapingDepth, result);

    GetClassExtendedFt(&classOfRefValue)->GetElementCount(&classOfRefValue, &totalPropertyCount);
    
    for (propertyIndex = 0;propertyIndex != totalPropertyCount; propertyIndex++)
    {
        GetClassExtendedFt(&classOfRefValue)->GetElementAtExt(&classOfRefValue, propertyIndex, NULL, NULL, NULL,
                                                NULL, NULL, NULL, NULL, NULL, NULL, NULL, &propertyFlags);    
        
        if (propertyFlags & MI_FLAG_KEY)
        {
            keyCount++;
        }
    }

    for (propertyIndex = 0;propertyIndex != totalPropertyCount; propertyIndex++)
    {
        GetClassExtendedFt(&classOfRefValue)->GetElementAtExt(&classOfRefValue, propertyIndex, NULL, NULL, NULL,
                                                NULL, NULL, NULL, NULL, NULL, NULL, NULL, &propertyFlags);    

        if (propertyFlags & MI_FLAG_KEY)
        {
            const MI_Char *name;
            MI_Value value;
            MI_Type type;
            MI_Uint32 flags;
            MI_Result tmpResult = MI_Instance_GetElementAt(refValue, propertyIndex, &name, &value, &type, &flags);
            if (tmpResult != MI_RESULT_OK)
            {
                *result = tmpResult;
                return;
            }

            if (keyCount == 1)
            {
                WriteBuffer_INSTANCENAME_single(clientBuffer, clientBufferLength, clientBufferNeeded, refValue, type, &value, escapingDepth, result);
            }
            else
            {
                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<KEYBINDING NAME=\""), escapingDepth, result);
                WriteBuffer_String(clientBuffer, clientBufferLength, clientBufferNeeded, name, escapingDepth, result);
                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("\">"), escapingDepth, result);
                WriteBuffer_INSTANCENAME_single(clientBuffer, clientBufferLength, clientBufferNeeded, refValue, type, &value, escapingDepth, result);
                WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</KEYBINDING>"), escapingDepth, result);
            }
        }
    }
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</INSTANCENAME>"), escapingDepth, result);
}

static void WriteBuffer_LOCALINSTANCEPATH(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    _In_z_ const MI_Char *namespaceName,
    _In_ const MI_Instance *refValue,
    MI_Uint32 escapingDepth,
    _Inout_ MI_Result *result)
{
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<LOCALINSTANCEPATH>"), escapingDepth, result);
    WriteBuffer_LOCALNAMESPACEPATH(clientBuffer, clientBufferLength, clientBufferNeeded, namespaceName, escapingDepth, result);
    WriteBuffer_INSTANCENAME(clientBuffer, clientBufferLength, clientBufferNeeded, refValue, escapingDepth, result);
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</LOCALINSTANCEPATH>"), escapingDepth, result);
}

static void WriteBuffer_INSTANCEPATH(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    _In_z_ const MI_Char *namespaceName,
    _In_z_ const MI_Char *serverName,
    _In_ const MI_Instance *refValue,
    MI_Uint32 escapingDepth,
    _Inout_ MI_Result *result)
{
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<INSTANCEPATH>"), escapingDepth, result);
    WriteBuffer_NAMESPACEPATH(clientBuffer, clientBufferLength, clientBufferNeeded, namespaceName, serverName, escapingDepth, result);
    WriteBuffer_INSTANCENAME(clientBuffer, clientBufferLength, clientBufferNeeded, refValue, escapingDepth, result);
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</INSTANCEPATH>"), escapingDepth, result);
}
static void WriteBuffer_InstanceReference(
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded,
    _In_opt_z_ const MI_Char *_namespaceName,
    _In_opt_z_ const MI_Char *_serverName,
    _In_ const MI_Instance *refInstance_,
    MI_Uint32 escapingDepth,
    _Inout_ MI_Result *result)
{
    const MI_Char *namespaceName = NULL;
    const MI_Char *serverName = NULL;
    // No one is using OSC_Instance structure inside OMI/WinOMI;
    // so I am assuming all instances here are going to be MI_Instances
    // so getting rid of this OSC_Instance from the reused code and replacing it with MI_Instance
    // in the future if someone adds OSC_Instance in OMI/WinOMI then add this back
    //MI_Instance *refInstance = (MI_Instance*)(((Instance*)refInstance_)->self);  //In case this is dynamic instance point to the real one, otherwise it points to ourself!
    const MI_Instance *refInstance = refInstance_;

    if ((_namespaceName && refInstance->nameSpace && (Tcscasecmp(_namespaceName, refInstance->nameSpace)!=0)) ||
             (!_namespaceName && refInstance->nameSpace))
    {
        namespaceName = refInstance->nameSpace;
    }
    if ((_serverName && refInstance->serverName && (Tcscasecmp(_serverName, refInstance->serverName)!=0)) ||
             (!_serverName && refInstance->serverName))
    {
        serverName = refInstance->serverName;
    }

    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<VALUE.REFERENCE>"), escapingDepth, result);
    if (serverName && namespaceName)
    {
        WriteBuffer_INSTANCEPATH(clientBuffer, clientBufferLength, clientBufferNeeded, namespaceName, serverName, refInstance, escapingDepth, result);
    }
    else if (namespaceName)
    {
        WriteBuffer_LOCALINSTANCEPATH(clientBuffer, clientBufferLength, clientBufferNeeded, namespaceName, refInstance, escapingDepth, result);
    }
    else
    {
        WriteBuffer_INSTANCENAME(clientBuffer, clientBufferLength, clientBufferNeeded, refInstance, escapingDepth, result);
    }
    WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</VALUE.REFERENCE>"), escapingDepth, result);
}

/* Serialize class api; assumes the MI_Class is setup with right function table using Class_Construct*/
MI_Result MI_CALL XmlSerializer_SerializeClassEx(
    _Inout_ MI_Serializer *serializer,
    MI_Uint32 flags,
    _In_ const MI_Class *classObject,
   _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded)
{
    MI_Result result = MI_RESULT_OK;

    MI_Uint32 validFlags = MI_SERIALIZER_FLAGS_CLASS_DEEP | MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN |
                MI_SERIALIZER_FLAGS_INCLUDE_INHERITANCE_HIERARCHY |
                MI_SERIALIZER_FLAGS_INCLUDE_INHERITED_ELEMENTS |
                MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS;

    if (((flags != 0) && (flags & ~validFlags)) ||
        (classObject == NULL) || (clientBufferNeeded == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    *clientBufferNeeded = 0;

    WriteBuffer_SerializeClass(clientBuffer, clientBufferLength, clientBufferNeeded, flags, classObject, classObject->namespaceName, classObject->serverName, &result);

    return result;
}

/* Wrapper method to accomendate WSMAN flags in using the API */
MI_Result MI_CALL XmlSerializer_SerializeClass(
    _Inout_ MI_Serializer *serializer, 
    MI_Uint32 flags, 
    _In_ const MI_Class *classObject, 
    _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
    _Inout_ MI_Uint32 *clientBufferNeeded)
{
    // Default flags
    MI_Uint32 newFlags = flags;

    return XmlSerializer_SerializeClassEx(serializer, newFlags, classObject, clientBuffer, clientBufferLength, clientBufferNeeded);
}

/* Serialize instance api */
MI_Result MI_CALL XmlSerializer_SerializeInstanceEx(
   _Inout_ MI_Serializer *serializer, 
   MI_Uint32 flags, 
   _In_ const MI_Instance *_instanceObject, 
   _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded)
{
    MI_Result result = MI_RESULT_OK;

    MI_Uint32 validFlags = MI_SERIALIZER_FLAGS_INSTANCE_WITH_CLASS | MI_SERIALIZER_FLAGS_INCLUDE_CLASS_ORIGIN |
                MI_SERIALIZER_FLAGS_INCLUDE_INHERITANCE_HIERARCHY |
                MI_SERIALIZER_FLAGS_INCLUDE_INHERITED_ELEMENTS |
                MI_SERIALIZER_FLAGS_INCLUDE_QUALIFIERS;

    if ((serializer == NULL) || ((flags != 0) && (flags & ~validFlags)) || (_instanceObject == NULL) || (clientBufferNeeded == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    *clientBufferNeeded = 0;

    if (flags & MI_SERIALIZER_FLAGS_INSTANCE_WITH_CLASS)
    {
        const MI_Char *writtenClasses[50] = {NULL};
        MI_Class classOfInstance = MI_CLASS_NULL;
        MI_Uint32 writtenClassCount = 0;
        writtenClasses[0] = L'\0';


        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<CIM CIMVERSION=\"2.6.0\" DTDVERSION=\"2.3.1\"><DECLARATION><DECLGROUP>"), SERIALIZE_NO_ESCAPE, &result);
        if (_instanceObject->nameSpace && _instanceObject->serverName)
        {
            WriteBuffer_NAMESPACEPATH(clientBuffer, clientBufferLength, clientBufferNeeded, _instanceObject->nameSpace, _instanceObject->serverName, SERIALIZE_NO_ESCAPE, &result);
        }
        else if (_instanceObject->nameSpace)
        {
            WriteBuffer_LOCALNAMESPACEPATH(clientBuffer, clientBufferLength, clientBufferNeeded, _instanceObject->nameSpace, SERIALIZE_NO_ESCAPE, &result);
        }

        //Loop through classes

        MI_Instance_GetClassExt(_instanceObject, &classOfInstance);
        WriteBuffer_RecurseInstanceClass(clientBuffer, clientBufferLength, clientBufferNeeded, flags, &classOfInstance, _instanceObject->nameSpace, _instanceObject->serverName, writtenClasses, &writtenClassCount, &result);

        //Loop through embedded object classes
        {
            WriteBuffer_InstanceEmbeddedClass(clientBuffer, clientBufferLength, clientBufferNeeded, flags, _instanceObject, writtenClasses, &writtenClassCount, &result);
        }

        //Instance VALUE.OBJECT
        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("<VALUE.OBJECT>"), SERIALIZE_NO_ESCAPE, &result);
    }

    //Starting at level 0, if it gets an embedded object it will be incremented for that (recursively)
    //Note that SERIALIZE_NO_ESCAPE == 0, but wanted this to be symbolic that it is starting at 0.
    WriteBuffer_Instance(clientBuffer, clientBufferLength, clientBufferNeeded, _instanceObject, 0, &result);

    if (flags & MI_SERIALIZER_FLAGS_INSTANCE_WITH_CLASS)
    {
        WriteBuffer_StringLiteral(clientBuffer, clientBufferLength, clientBufferNeeded, PAL_T("</VALUE.OBJECT></DECLGROUP></DECLARATION></CIM>"), SERIALIZE_NO_ESCAPE, &result);
    }
    return result;
}

/* Wrapper method to accomendate WSMAN flags in using the API */
MI_Result MI_CALL XmlSerializer_SerializeInstance(
   _Inout_ MI_Serializer *serializer, 
   MI_Uint32 flags, 
   _In_ const MI_Instance *_instanceObject, 
   _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded)
{
    // Default flags
    MI_Uint32 newFlags = flags;

    return XmlSerializer_SerializeInstanceEx(serializer, newFlags, _instanceObject, clientBuffer, clientBufferLength, clientBufferNeeded);
}

