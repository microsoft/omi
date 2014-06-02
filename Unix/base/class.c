/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */
#include "class.h"
#include <base/types.h>
#include <pal/strings.h>
#include <base/batch.h>
#include "naming.h"
#include <base/instance.h>
#include <pal/atomic.h>

extern const MI_ClassExtendedFTInternal g_ClassExtendedFTInternal;
extern const MI_ParameterSetExtendedFTInternal g_parameterExtendedFTInternal;
extern const MI_QualifierSetFT g_qualifierFT;

typedef struct _MI_RCClass
{
    /* public properties from MI_Class */
    const MI_ClassFT *ft;
    MI_CONST MI_ClassDecl *classDecl;
    MI_CONST MI_Char *namespaceName;
    MI_CONST MI_Char *serverName;

    /* Reserved properties */
    Batch *batch;
    ptrdiff_t refcount;
    ptrdiff_t reserved3;
    ptrdiff_t reserved4;

} MI_RCClass;


void GetMIValueFromVoid(MI_Type type, _In_opt_ const void *source, _Out_ MI_Value *value)
{
    memset(value, 0, sizeof(MI_Value));
    if (source == NULL)
    {
        return;
    }

    switch(type)
    {
    case MI_BOOLEAN:
        value->boolean = *(MI_Boolean*)source;
        break;
    case MI_UINT8:
        value->uint8 = *(MI_Uint8*)source;
        break;
    case MI_SINT8:
        value->sint8 = *(MI_Sint8*)source;
        break;
    case MI_UINT16:
        value->uint16 = *(MI_Uint16*)source;
        break;
    case MI_SINT16:
        value->sint16 = *(MI_Sint16*)source;
        break;
    case MI_UINT32:
        value->uint32 = *(MI_Uint32*)source;
        break;
    case MI_SINT32:
        value->sint32 = *(MI_Sint32*)source;
        break;
    case MI_UINT64:
        value->uint64 = *(MI_Uint64*)source;
        break;
    case MI_SINT64:
        value->sint64 = *(MI_Sint64*)source;
        break;
    case MI_REAL32:
        value->real32 = *(MI_Real32*)source;
        break;
    case MI_REAL64:
        value->real64 = *(MI_Real64*)source;
        break;
    case MI_CHAR16:
        value->char16 = *(MI_Char16*)source;
        break;
    case MI_DATETIME:
        value->datetime = *(MI_Datetime*)source;
        break;
    case MI_STRING:
        value->string = *(MI_Char**)source;
        break;
    case MI_REFERENCE:
        value->reference = *(MI_Instance**)source;
        break;
    case MI_INSTANCE:
        value->instance = *(MI_Instance**)source;
        break;
    case MI_BOOLEANA:
        value->booleana = *(MI_BooleanA*)source;
        break;
    case MI_UINT8A:
        value->uint8a = *(MI_Uint8A*)source;
        break;
    case MI_SINT8A:
        value->sint8a = *(MI_Sint8A*)source;
        break;
    case MI_UINT16A:
        value->uint16a = *(MI_Uint16A*)source;
        break;
    case MI_SINT16A:
        value->sint16a = *(MI_Sint16A*)source;
        break;
    case MI_UINT32A:
        value->uint32a = *(MI_Uint32A*)source;
        break;
    case MI_SINT32A:
        value->sint32a = *(MI_Sint32A*)source;
        break;
    case MI_UINT64A:
        value->uint64a = *(MI_Uint64A*)source;
        break;
    case MI_SINT64A:
        value->sint64a = *(MI_Sint64A*)source;
        break;
    case MI_REAL32A:
        value->real32a = *(MI_Real32A*)source;
        break;
    case MI_REAL64A:
        value->real64a = *(MI_Real64A*)source;
        break;
    case MI_CHAR16A:
        value->char16a = *(MI_Char16A*)source;
        break;
    case MI_DATETIMEA:
        value->datetimea = *(MI_DatetimeA*)source;
        break;
    case MI_STRINGA:
        value->stringa = *(MI_StringA*)source;
        break;
    case MI_REFERENCEA:
        value->referencea = *(MI_ReferenceA*)source;
        break;
    case MI_INSTANCEA:
        value->instancea = *(MI_InstanceA*)source;
        break;
    }
}

MI_Result MI_CALL Class_New(
    _In_ const MI_ClassDecl *classDecl,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *serverName,
    _Out_ MI_Class **outboundNewClass)
{
    Batch *ourBatch = NULL;
    MI_RCClass *newClass = NULL;

    if (classDecl == NULL || outboundNewClass == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *outboundNewClass = NULL;
    if(ourBatch == NULL)
    {
        ourBatch = Batch_New(BATCH_MAX_PAGES);
        if (ourBatch == NULL)
        {
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
    }    
    
    newClass = Batch_GetClear(ourBatch, sizeof(MI_Class));
    if (newClass == NULL)
    {
        Batch_Delete(ourBatch);
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    if (namespaceName)
    {
        newClass->namespaceName = Batch_Tcsdup(ourBatch, namespaceName);
        if (newClass->namespaceName == NULL)
        {
            Batch_Delete(ourBatch);
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
    }
    if (serverName)
    {
        newClass->serverName = Batch_Tcsdup(ourBatch, serverName);
        if (newClass->serverName == NULL)
        {
            Batch_Delete(ourBatch);
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
    }
    newClass->ft = (MI_ClassFT*)(&g_ClassExtendedFTInternal);
    newClass->batch = ourBatch;    
    newClass->classDecl = Class_Clone_ClassDecl(ourBatch, classDecl);
    if (newClass->classDecl == NULL)
    {
        Batch_Delete(ourBatch);

        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    newClass->classDecl->owningClass = (MI_Class*)newClass;
    newClass->refcount = 1;
    *outboundNewClass = (MI_Class*) newClass;
    return MI_RESULT_OK;
}

static MI_Uint32 _CalculateArraySize(MI_Type type, MI_Uint32 numberItems)
{
    return  Type_SizeOf(type&~MI_ARRAY) * numberItems;
}


/*============================================================================
 * 
 *============================================================================
 */
MI_Array* Class_Clone_Array(
    _Inout_ Batch *batch,
    MI_Type type, 
    _In_ const MI_Array *array)
{
    MI_Array *newArray = Batch_Get(batch, sizeof(MI_Array));
    MI_Uint32 arraySize = 0;
    MI_Uint32 arrayLoop = 0;
    if (newArray == NULL)
    {
        return NULL; /* Returning NULL causes whole batch to destruct */
    }
    newArray->size = array->size;

    arraySize = _CalculateArraySize(type, array->size);

    newArray->data = Batch_Get(batch, arraySize);
    if (newArray->data == NULL)
    {
        return NULL; /* Returning NULL causes whole batch to destruct */
    }
    switch(type)
    {
    case MI_BOOLEANA:
    case MI_UINT8A:
    case MI_SINT8A:
    case MI_UINT16A:
    case MI_SINT16A:
    case MI_UINT32A:
    case MI_SINT32A:
    case MI_UINT64A:
    case MI_SINT64A:
    case MI_REAL32A:
    case MI_REAL64A:
    case MI_CHAR16A:
    case MI_DATETIMEA:
        memcpy(newArray->data, array->data, arraySize);
        break;
    case MI_STRINGA:
        for (;arrayLoop != array->size; arrayLoop++)
        {
            if (((MI_Char**)(array->data))[arrayLoop])
            {
                ((MI_Char**)(newArray->data))[arrayLoop] = Batch_Tcsdup(batch, ((MI_Char**)(array->data))[arrayLoop]);
                if (((MI_Char**)(newArray->data))[arrayLoop] == NULL)
                {
                    return NULL; /* Returning NULL causes whole batch to destruct */
                }
            }
        }
        break;
    case MI_REFERENCEA:
    case MI_INSTANCEA:
        for (;arrayLoop != array->size; arrayLoop++)
        {
            if (((MI_Instance**)(newArray->data))[arrayLoop])
            {
                if (Instance_Clone(((MI_Instance**)(array->data))[arrayLoop], &((MI_Instance**)(newArray->data))[arrayLoop], batch) != MI_RESULT_OK)
                {
                    return NULL; /* Returning NULL causes whole batch to destruct */
                }
            }
        }
        break;
    default:
        break;
    }

    return newArray;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result Class_Clone_ArrayValue(
    _Inout_ Batch *batch,
    MI_Type type, 
    _In_ void *destinationArrayStart,
    MI_Uint32 arrayLocation,
    _In_ const void *oldValueLocation)
{
    switch(type)
    {
    case MI_BOOLEAN:
        ((MI_Boolean*)destinationArrayStart)[arrayLocation] = *(MI_Boolean*)oldValueLocation;
        break;
    case MI_UINT8:
        ((MI_Uint8*)destinationArrayStart)[arrayLocation] = *(MI_Uint8*)oldValueLocation;
        break;
    case MI_SINT8:
        ((MI_Sint8*)destinationArrayStart)[arrayLocation] = *(MI_Sint8*)oldValueLocation;
        break;
    case MI_UINT16:
        ((MI_Uint16*)destinationArrayStart)[arrayLocation] = *(MI_Uint16*)oldValueLocation;
        break;
    case MI_SINT16:
        ((MI_Sint16*)destinationArrayStart)[arrayLocation] = *(MI_Sint16*)oldValueLocation;
        break;
    case MI_UINT32:
        ((MI_Uint32*)destinationArrayStart)[arrayLocation] = *(MI_Uint32*)oldValueLocation;
        break;
    case MI_SINT32:
        ((MI_Sint32*)destinationArrayStart)[arrayLocation] = *(MI_Sint32*)oldValueLocation;
        break;
    case MI_UINT64:
        ((MI_Uint64*)destinationArrayStart)[arrayLocation] = *(MI_Uint64*)oldValueLocation;
        break;
    case MI_SINT64:
        ((MI_Sint64*)destinationArrayStart)[arrayLocation] = *(MI_Sint64*)oldValueLocation;
        break;
    case MI_REAL32:
        ((MI_Real32*)destinationArrayStart)[arrayLocation] = *(MI_Real32*)oldValueLocation;
        break;
    case MI_REAL64:
        ((MI_Real64*)destinationArrayStart)[arrayLocation] = *(MI_Real64*)oldValueLocation;
        break;
    case MI_CHAR16:
        ((MI_Char16*)destinationArrayStart)[arrayLocation] = *(MI_Char16*)oldValueLocation;
        break;
    case MI_DATETIME:
        ((MI_Datetime*)destinationArrayStart)[arrayLocation] = *(MI_Datetime*)oldValueLocation;
        break;
    case MI_STRING:
        {
            MI_Char *string = NULL;
            if (*(MI_Char**)oldValueLocation)
            {
                string = Batch_Tcsdup(batch, *(MI_Char**)oldValueLocation);
                if (string == NULL)
                {
                    return MI_RESULT_SERVER_LIMITS_EXCEEDED; /* Returning error causes whole batch to destruct */
                }
            }
            ((MI_String*)destinationArrayStart)[arrayLocation] = string;
        }
        break;
    case MI_REFERENCE:
    case MI_INSTANCE:
        {
            MI_Instance *instance = NULL;

            if (*(MI_Char**)oldValueLocation)
            {
                if (Instance_Clone(*(MI_Instance**)oldValueLocation, &instance, batch) != MI_RESULT_OK)
                {
                    return MI_RESULT_SERVER_LIMITS_EXCEEDED; /* Returning error causes whole batch to destruct */
                }
            }
            ((MI_Instance**)destinationArrayStart)[arrayLocation] = instance;
        }
        break;
    case MI_BOOLEANA:
    case MI_UINT8A:
    case MI_SINT8A:
    case MI_UINT16A:
    case MI_SINT16A:
    case MI_UINT32A:
    case MI_SINT32A:
    case MI_UINT64A:
    case MI_SINT64A:
    case MI_REAL32A:
    case MI_REAL64A:
    case MI_CHAR16A:
    case MI_DATETIMEA:
    case MI_STRINGA:
    case MI_REFERENCEA:
    case MI_INSTANCEA:
        return MI_RESULT_INVALID_PARAMETER;
        break;
    }

    return MI_RESULT_OK;;
}

/*============================================================================
 * 
 *============================================================================
 */
void* Class_Clone_Value(
    _Inout_ Batch *batch,
    MI_Type type, 
    _In_ const void *value)
{
    void *newValue = NULL;

    switch(type)
    {
    case MI_BOOLEAN:
        newValue = Batch_Get(batch, sizeof(MI_Boolean));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Boolean*)newValue = *(MI_Boolean*)value;
        break;
    case MI_UINT8:
        newValue = Batch_Get(batch, sizeof(MI_Uint8));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Uint8*)newValue = *(MI_Uint8*)value;
        break;
    case MI_SINT8:
        newValue = Batch_Get(batch, sizeof(MI_Sint8));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Sint8*)newValue = *(MI_Sint8*)value;
        break;
    case MI_UINT16:
        newValue = Batch_Get(batch, sizeof(MI_Uint16));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Uint16*)newValue = *(MI_Uint16*)value;
        break;
    case MI_SINT16:
        newValue = Batch_Get(batch, sizeof(MI_SINT16));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Sint16*)newValue = *(MI_Sint16*)value;
        break;
    case MI_UINT32:
        newValue = Batch_Get(batch, sizeof(MI_Uint32));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Uint32*)newValue = *(MI_Uint32*)value;
        break;
    case MI_SINT32:
        newValue = Batch_Get(batch, sizeof(MI_Sint32));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Sint32*)newValue = *(MI_Sint32*)value;
        break;
    case MI_UINT64:
        newValue = Batch_Get(batch, sizeof(MI_Uint64));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Uint64*)newValue = *(MI_Uint64*)value;
        break;
    case MI_SINT64:
        newValue = Batch_Get(batch, sizeof(MI_Sint64));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Sint64*)newValue = *(MI_Sint64*)value;
        break;
    case MI_REAL32:
        newValue = Batch_Get(batch, sizeof(MI_Real32));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Real32*)newValue = *(MI_Real32*)value;
        break;
    case MI_REAL64:
        newValue = Batch_Get(batch, sizeof(MI_Real64));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Real64*)newValue = *(MI_Real64*)value;
        break;
    case MI_CHAR16:
        newValue = Batch_Get(batch, sizeof(MI_Char16));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Char16*)newValue = *(MI_Char16*)value;
        break;
    case MI_DATETIME:
        newValue = Batch_Get(batch, sizeof(MI_Datetime));
        if (newValue == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        *(MI_Datetime*)newValue = *(MI_Datetime*)value;
        break;
    case MI_STRING:
        {
            MI_Char *string = NULL;
            MI_Char **pointerToString = NULL;

            pointerToString =  (MI_Char**)Batch_Get(batch, sizeof(MI_Char**));
            if (pointerToString == NULL)
            {
                return NULL; /* Returning NULL causes whole batch to destruct */
            }
            string = Batch_Tcsdup(batch, *(MI_Char**)value);
            if (string == NULL)
            {
                return NULL; /* Returning NULL causes whole batch to destruct */
            }
            *pointerToString = string;

            newValue = pointerToString;
        }
        break;
    case MI_REFERENCE:
    case MI_INSTANCE:
        {
            MI_Instance *instance = NULL;
            MI_Instance **pointerToInstance= NULL;

            pointerToInstance =  (MI_Instance**)Batch_Get(batch, sizeof(MI_Instance**));
            if (pointerToInstance == NULL)
            {
                return NULL; /* Returning NULL causes whole batch to destruct */
            }
            if (Instance_Clone(*(MI_Instance**)value, &instance, batch) != MI_RESULT_OK)
            {
                return NULL; /* Returning NULL causes whole batch to destruct */
            }
            *pointerToInstance = instance;

            newValue = pointerToInstance;
        }
        break;
    case MI_BOOLEANA:
    case MI_UINT8A:
    case MI_SINT8A:
    case MI_UINT16A:
    case MI_SINT16A:
    case MI_UINT32A:
    case MI_SINT32A:
    case MI_UINT64A:
    case MI_SINT64A:
    case MI_REAL32A:
    case MI_REAL64A:
    case MI_CHAR16A:
    case MI_DATETIMEA:
    case MI_STRINGA:
    case MI_REFERENCEA:
    case MI_INSTANCEA:
        newValue = Class_Clone_Array(batch, type, (MI_Array*)value);
        break;
    }

    return newValue;
}
/*============================================================================
 * 
 *============================================================================
 */
MI_Qualifier * Class_Clone_Qualifier(
    _Inout_ Batch *batch,
    MI_Qualifier MI_CONST* qualifier)
{
    MI_Qualifier *newQualifier = Batch_Get(batch, sizeof(MI_Qualifier));
    if (newQualifier == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    memset(newQualifier, 0, sizeof(*newQualifier));
    newQualifier->name = Batch_Tcsdup(batch, qualifier->name);
    if (newQualifier->name == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    newQualifier->type = qualifier->type;
    newQualifier->flavor = qualifier->flavor;
    if (qualifier->value)
    {
        newQualifier->value = Class_Clone_Value(batch, qualifier->type, qualifier->value);
        if (newQualifier->value == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
    }
    else
    {
        newQualifier->value = NULL;
    }

    return newQualifier;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Qualifier MI_CONST* MI_CONST* Class_Clone_Qualifiers(
    _Inout_ Batch *batch,
    MI_Qualifier MI_CONST* MI_CONST* qualifiers,
    MI_Uint32 numQualifiers)
{
    MI_Qualifier **newQualifiers = Batch_Get(batch, sizeof(MI_Qualifier*)*numQualifiers);
    MI_Uint32 qualifierIndex = 0;
    if (newQualifiers == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    for (;qualifierIndex != numQualifiers; qualifierIndex++)
    {
        newQualifiers[qualifierIndex] = Class_Clone_Qualifier(batch, qualifiers[qualifierIndex]);
        if (newQualifiers[qualifierIndex] == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
    }

    return newQualifiers;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_PropertyDecl * Class_Clone_Property(
    _Inout_ Batch *batch,
    MI_PropertyDecl MI_CONST* property)
{
    MI_PropertyDecl *newProperty = Batch_Get(batch, sizeof(MI_PropertyDecl));
    if (newProperty == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    memset(newProperty, 0, sizeof(*newProperty));
    newProperty->flags = property->flags;
    newProperty->code = property->code;
    newProperty->name = Batch_Tcsdup(batch, property->name);
    if (newProperty->name == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    if (property->qualifiers && property->numQualifiers)
    {
        newProperty->qualifiers = Class_Clone_Qualifiers(batch, property->qualifiers, property->numQualifiers);
        if (newProperty->qualifiers == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
        newProperty->numQualifiers = property->numQualifiers;
    }
    newProperty->type = property->type;
    if (property->className)
    {
        newProperty->className = Batch_Tcsdup(batch, property->className); /* embedded/reference stringly typed class name */
        if (newProperty->className == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
    }
    newProperty->subscript = property->subscript;
    newProperty->offset = property->offset;
    if (property->origin)
    {
        newProperty->origin = Batch_Tcsdup(batch, property->origin);
        if (newProperty->origin == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
    }
    if (property->propagator)
    {
        newProperty->propagator = Batch_Tcsdup(batch, property->propagator);
        if (newProperty->propagator == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
    }
    if (((property->flags & MI_FLAG_NULL) != MI_FLAG_NULL) && property->value)
    {
        newProperty->value = Class_Clone_Value(batch, property->type, property->value);
        if (newProperty->value == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
    }
    else
    {
        newProperty->value = NULL;
    }
    return newProperty;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_PropertyDecl MI_CONST* MI_CONST* Class_Clone_Properties(
    _Inout_ Batch *batch,
    MI_PropertyDecl MI_CONST* MI_CONST* properties,
    MI_Uint32 numProperties)
{
    MI_PropertyDecl **newProperties = Batch_Get(batch, sizeof(MI_PropertyDecl*)*numProperties);
    MI_Uint32 propertyIndex = 0;
    if (newProperties == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    for (;propertyIndex != numProperties; propertyIndex++)
    {
        newProperties[propertyIndex] = Class_Clone_Property(batch, properties[propertyIndex]);
        if (newProperties[propertyIndex] == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
    }

    return newProperties;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_ParameterDecl * Class_Clone_Parameter(
    _Inout_ Batch *batch,
    MI_ParameterDecl MI_CONST* parameter,
    const MI_Char *className)
{
    MI_ParameterDecl *newParameter = Batch_Get(batch, sizeof(MI_ParameterDecl));
    if (newParameter == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    memset(newParameter, 0, sizeof(*newParameter));
    newParameter->flags = parameter->flags;
    newParameter->code = parameter->code;
    newParameter->name = Batch_Tcsdup(batch, parameter->name);
    if (newParameter->name == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    if (parameter->qualifiers && parameter->numQualifiers)
    {
        newParameter->qualifiers = Class_Clone_Qualifiers(batch, parameter->qualifiers, parameter->numQualifiers);
        if (newParameter->qualifiers == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
        newParameter->numQualifiers = parameter->numQualifiers;
    }
    newParameter->type = parameter->type;
    if (parameter->className)
    {
        newParameter->className = Batch_Tcsdup(batch, parameter->className);
        if (newParameter->className == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
    }
    newParameter->subscript = parameter->subscript;
    newParameter->offset = parameter->offset;

    return newParameter;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_ParameterDecl MI_CONST* MI_CONST* Class_Clone_Parameters(
    _Inout_ Batch *batch,
    MI_ParameterDecl MI_CONST* MI_CONST* parameters,
    MI_Uint32 numParameters,
    const MI_Char *className)
{
    MI_ParameterDecl **newParameters = Batch_Get(batch, sizeof(MI_ParameterDecl*)*numParameters);
    MI_Uint32 parameterIndex = 0;
    if (newParameters == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    for (;parameterIndex != numParameters; parameterIndex++)
    {
        newParameters[parameterIndex] = Class_Clone_Parameter(batch, parameters[parameterIndex], className);
        if (newParameters[parameterIndex] == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
    }

    return newParameters;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_MethodDecl * Class_Clone_Method(
    _Inout_ Batch *batch,
    MI_MethodDecl MI_CONST* method,
    const MI_Char *className)
{
    MI_MethodDecl *newMethod = Batch_Get(batch, sizeof(MI_MethodDecl));
    if (newMethod == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    memset(newMethod, 0, sizeof(*newMethod));
    newMethod->flags = method->flags;
    newMethod->code = method->code;
    newMethod->name = Batch_Tcsdup(batch, method->name);
    if (newMethod->name == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    if (method->qualifiers && method->numQualifiers)
    {
        newMethod->qualifiers = Class_Clone_Qualifiers(batch, method->qualifiers, method->numQualifiers);
        if (newMethod->qualifiers == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
        newMethod->numQualifiers = method->numQualifiers;
    }
    if (method->parameters && method->numParameters)
    {
        newMethod->parameters = Class_Clone_Parameters(batch, method->parameters, method->numParameters, className);
        if (newMethod->parameters == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
        newMethod->numParameters = method->numParameters;
    }
    newMethod->size = method->size;
    newMethod->returnType = method->returnType;
    if (method->origin)
    {
        newMethod->origin = Batch_Tcsdup(batch, method->origin);
        if (newMethod->origin == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
    }
    if (method->propagator)
    {
        newMethod->propagator = Batch_Tcsdup(batch, method->propagator);
        if (newMethod->propagator == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
    }
    /* Leave owning schema NULL otherwise we would need to potentially clone that and every other class in there */
    newMethod->schema = NULL;
    newMethod->function = method->function;
    return newMethod;
}
/*============================================================================
 * 
 *============================================================================
 */
MI_MethodDecl MI_CONST* MI_CONST* Class_Clone_Methods(
    _Inout_ Batch *batch,
    MI_MethodDecl MI_CONST* MI_CONST* methods,
    MI_Uint32 numMethod,
    const MI_Char *className)
{
    MI_MethodDecl **newMethods = Batch_Get(batch, sizeof(MI_MethodDecl*)*numMethod);
    MI_Uint32 methodIndex = 0;
    if (newMethods == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    for (;methodIndex != numMethod; methodIndex++)
    {
        newMethods[methodIndex] = Class_Clone_Method(batch, methods[methodIndex], className);
        if (newMethods[methodIndex] == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
    }

    return newMethods;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_ClassDecl* Class_Clone_ClassDecl(
    _Inout_ Batch *batch,
    _In_ const MI_ClassDecl *classDecl)
{
    MI_ClassDecl *newClassDecl = Batch_Get(batch, sizeof(MI_ClassDecl));
    if (newClassDecl == NULL)
    {
        return NULL;  /* Returning NULL causes whole batch to destruct */
    }
    memset(newClassDecl, 0, sizeof(MI_ClassDecl));

    newClassDecl->flags = classDecl->flags;
    newClassDecl->code = classDecl->code;
    newClassDecl->name = Batch_Tcsdup(batch, classDecl->name);
    if (newClassDecl->name == NULL)
    {
        return NULL; /* Returning NULL causes whole batch to destruct */
    }
    if (classDecl->qualifiers && classDecl->numQualifiers)
    {
        newClassDecl->qualifiers = Class_Clone_Qualifiers(batch, classDecl->qualifiers, classDecl->numQualifiers);
        if (newClassDecl->qualifiers == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
        newClassDecl->numQualifiers = classDecl->numQualifiers;
    }
    if (classDecl->properties && classDecl->numProperties)
    {
        newClassDecl->properties = Class_Clone_Properties(batch, classDecl->properties, classDecl->numProperties);
        if (newClassDecl->properties == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
        newClassDecl->numProperties = classDecl->numProperties;
    }
    newClassDecl->size = classDecl->size;
    if (classDecl->superClass)
    {
        newClassDecl->superClass = Batch_Tcsdup(batch, classDecl->superClass);
        if (newClassDecl->superClass == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
    }
    if (classDecl->superClassDecl)
    {
        newClassDecl->superClassDecl = Class_Clone_ClassDecl(batch, classDecl->superClassDecl);
        if (newClassDecl->superClassDecl == NULL)
        {
            return NULL; /* Returning NULL causes whole batch to destruct */
        }
        if (classDecl->superClassDecl->owningClass != 0)
            newClassDecl->superClassDecl->owningClass = (MI_Class*)-1;
    }
    if (classDecl->methods && classDecl->numMethods)
    {
        newClassDecl->methods = Class_Clone_Methods(batch, classDecl->methods, classDecl->numMethods, classDecl->name);
        if (newClassDecl->methods == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
        newClassDecl->numMethods = classDecl->numMethods;
    }
    /* Leave owning schema NULL otherwise we would need to potentially clone that and every other class in there */
    newClassDecl->providerFT = classDecl->providerFT;

    return newClassDecl;
}



/*============================================================================
 * 
 *============================================================================
 */
MI_EXTERN_C MI_Result MI_CALL Class_Construct(MI_Class* self, const MI_ClassDecl* classDecl)
{
    if ((self == NULL) || (classDecl == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;    
    }

    memset(self, 0, sizeof(MI_Class));

    self->classDecl = (MI_CONST MI_ClassDecl *)classDecl;
    self->ft = (MI_ClassFT *)(&g_ClassExtendedFTInternal);

    return MI_RESULT_OK;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL Class_GetClassName(
    _In_ const MI_Class* self, 
    _Outptr_result_maybenull_z_ const MI_Char** className)
{
    if ((self == NULL) || (className == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *className = self->classDecl->name;

    return MI_RESULT_OK;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL Class_GetNameSpace(
    _In_ const MI_Class* self, 
    _Outptr_result_maybenull_z_ const MI_Char** nameSpace)
{
    if ((self == NULL) || (nameSpace == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *nameSpace = self->namespaceName;

    return MI_RESULT_OK;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL Class_GetServerName(
    _In_ const MI_Class* self, 
    _Outptr_result_maybenull_z_ const MI_Char** serverName)
{
    if ((self == NULL) || (serverName == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *serverName = self->serverName;
    
    return MI_RESULT_OK;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL Class_GetElementCount(
    _In_ const MI_Class* self,
    _Out_ MI_Uint32* count)
{
    if ((self == NULL) || (count == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    *count = self->classDecl->numProperties;
    
    return MI_RESULT_OK;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL Class_GetElement(
    _In_      const MI_Class* self, 
    _In_z_    const MI_Char* name,
    _Out_opt_ MI_Value* value,
    _Out_opt_ MI_Boolean* valueExists,
    _Out_opt_ MI_Type* type,
    _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
    _Out_opt_ MI_QualifierSet *qualifierSet,
    _Out_opt_ MI_Uint32* flags,
    _Out_opt_ MI_Uint32* index)
{
    MI_Uint32 ourIndex;
    MI_Uint32 code;

    if ((self == NULL) || (name == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    code = Hash(name);

    for (ourIndex = 0; ourIndex < self->classDecl->numProperties; ourIndex++)
    {
        if (self->classDecl->properties[ourIndex]->code == code && Tcscasecmp(name, self->classDecl->properties[ourIndex]->name) == 0)
        {
            MI_Result result;

            result = MI_Class_GetElementAt(self, ourIndex, NULL, value, valueExists, type, referenceClass, qualifierSet, flags);
            if ((result == MI_RESULT_OK) && index)
            {
                *index = ourIndex;
            }
            return result;
        }
    }
    return MI_RESULT_NO_SUCH_PROPERTY;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL Class_GetElementAt(
    _In_ const MI_Class* self, 
    MI_Uint32 index,
    _Outptr_result_maybenull_z_ const MI_Char** name,
    _Out_opt_ MI_Value* value,
    _Out_opt_ MI_Boolean* valueExists,
    _Out_opt_ MI_Type* type,
    _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
    _Out_opt_ MI_QualifierSet *qualifierSet,
    _Out_opt_ MI_Uint32* flags)
{
    const MI_PropertyDecl *propertyDecl;

    if (self == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (index >= self->classDecl->numProperties)
    {
        return MI_RESULT_NO_SUCH_PROPERTY;
    }
    propertyDecl = self->classDecl->properties[index];
    if (name)
    {
        *name = propertyDecl->name;
    }
    if (valueExists)
    {
        *valueExists = (propertyDecl->value != NULL);
    }
    if (value)
    {
        GetMIValueFromVoid(propertyDecl->type, propertyDecl->value, value);
    }
    if (type)
    {
        *type = (MI_Type) propertyDecl->type;
    }
    if (referenceClass)
    {
        *referenceClass = propertyDecl->className;
    }
    if (qualifierSet)
    {
        qualifierSet->ft = &g_qualifierFT;
        qualifierSet->reserved1 = propertyDecl->numQualifiers;
        qualifierSet->reserved2 = (ptrdiff_t)propertyDecl->qualifiers;
    }
    if (flags)
    {
        *flags = propertyDecl->flags;
    }

    return MI_RESULT_OK;
}

/*============================================================================
 *
 *============================================================================
 */
MI_Result MI_CALL Class_GetClassFlagsExt(
            _In_ const MI_Class* self,
            _Out_ MI_Uint32* flags)
{
    if ((self == NULL) || (flags == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    *flags = self->classDecl->flags;

    return MI_RESULT_OK;
}

/*============================================================================
 *
 *============================================================================
 */
MI_Result MI_CALL Class_GetElementAtExt(
    _In_ const MI_Class* self,
    MI_Uint32 index,
    _Outptr_opt_result_maybenull_z_ const MI_Char** name,
    _Out_opt_ MI_Value* value,
    _Out_opt_ MI_Boolean* valueExists,
    _Out_opt_ MI_Type* type,
    _Out_opt_ MI_Uint32* subscript,
    _Out_opt_ MI_Uint32* offset,
    _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
    _Outptr_opt_result_maybenull_z_ MI_Char **originClass,
    _Outptr_opt_result_maybenull_z_ MI_Char **propagatorClass,
    _Out_opt_ MI_QualifierSet *qualifierSet,
    _Out_opt_ MI_Uint32* flags)
{
    const MI_PropertyDecl *propertyDecl;

    MI_Result result = Class_GetElementAt(self, index, name, value, valueExists, type, referenceClass, qualifierSet, flags);

    if(result != MI_RESULT_OK)
    {
        return result;
    }

    propertyDecl = self->classDecl->properties[index];

    if(subscript)
    {
        *subscript = propertyDecl->subscript;
    }

    if(offset)
    {
        *offset = propertyDecl->offset;
    }

    if(originClass)
    {
        *originClass = propertyDecl->origin;
    }

    if(propagatorClass)
    {
        *propagatorClass = propertyDecl->propagator;
    }

    return MI_RESULT_OK;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL Class_GetClassQualifierSet(
    _In_ const MI_Class* self, 
    _Out_opt_ MI_QualifierSet *qualifierSet
    )
{
    if ((self == NULL) ||
        (qualifierSet == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    qualifierSet->ft = &g_qualifierFT;
    qualifierSet->reserved1 = self->classDecl->numQualifiers;
    qualifierSet->reserved2 = (ptrdiff_t) self->classDecl->qualifiers;

    return MI_RESULT_OK;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL Class_GetMethodCount(
    _In_ const MI_Class* self,
    _Out_ MI_Uint32* count)
{
    if ((self == NULL) || (count == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    *count = self->classDecl->numMethods;

    return MI_RESULT_OK;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL Class_GetMethodAt(
    _In_ const MI_Class *self,
    MI_Uint32 index,
    _Outptr_result_z_ const MI_Char **name,
    _Out_opt_ MI_QualifierSet *qualifierSet,
    _Out_opt_ MI_ParameterSet *parameterSet
    )
{
    const MI_MethodDecl * methodDecl;

    if ((self == NULL) || (name == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (index >= self->classDecl->numMethods)
    {
        return MI_RESULT_METHOD_NOT_FOUND;
    }
    methodDecl = self->classDecl->methods[index];

    *name = methodDecl->name;

    if (qualifierSet)
    {
        const MI_QualifierSetFT **ft = (const MI_QualifierSetFT**)&qualifierSet->ft;
        *ft = &g_qualifierFT;
        qualifierSet->reserved1 = methodDecl->numQualifiers;
        qualifierSet->reserved2 = (ptrdiff_t) methodDecl->qualifiers;
    }
    if (parameterSet)
    {
        const MI_ParameterSetFT **ft = (const MI_ParameterSetFT**)&parameterSet->ft;
        *ft = (MI_ParameterSetFT *)(&g_parameterExtendedFTInternal);
        parameterSet->reserved1 = methodDecl->numParameters;
        parameterSet->reserved2 = (ptrdiff_t) methodDecl->parameters;
    }
    return MI_RESULT_OK;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL Class_GetMethodAtExt(
    _In_ const MI_Class *self,
    MI_Uint32 index,
    _Outptr_result_z_ const MI_Char **name,
    _Outptr_opt_result_maybenull_z_ MI_Char **originClass,
    _Outptr_opt_result_maybenull_z_ MI_Char **propagatorClass,
    _Out_opt_ MI_QualifierSet *qualifierSet,
    _Out_opt_ MI_ParameterSet *parameterSet,
    _Out_opt_ MI_Uint32* flags
    )
{
    const MI_MethodDecl * methodDecl;

    MI_Result result = Class_GetMethodAt(self, index, name, qualifierSet, parameterSet);

    if(result != MI_RESULT_OK)
    {
        return result;
    }

    methodDecl = self->classDecl->methods[index];

    if(originClass)
    {
        *originClass = methodDecl->origin;
    }

    if(propagatorClass)
    {
        *propagatorClass = methodDecl->propagator;
    }

    if(flags)
    {
        *flags = methodDecl->flags;
    }

    return MI_RESULT_OK;
}

/*============================================================================
 *
 *============================================================================
 */
MI_Result MI_CALL Class_GetMethod(
    _In_ const MI_Class *self,
    _In_z_ const MI_Char *name,
    _Out_opt_ MI_QualifierSet *qualifierSet,
    _Out_opt_ MI_ParameterSet *parameterSet,
    _Out_opt_ MI_Uint32 *index
    )
{
    MI_Uint32 ourIndex;
    MI_Uint32 code;

    if ((self == NULL) || (name == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    code = Hash(name);

    for (ourIndex = 0; ourIndex < self->classDecl->numMethods; ourIndex++)
    {
        if (self->classDecl->methods[ourIndex]->code == code && Tcscasecmp(name, self->classDecl->methods[ourIndex]->name) == 0)
        {
            MI_Result result;
            const MI_Char *tmpName = NULL;

            result = MI_Class_GetMethodAt(self, ourIndex, &tmpName, qualifierSet, parameterSet);
            if ((result == MI_RESULT_OK) && index)
            {
                *index = ourIndex;
            }
            return result;
        }
    }
    return MI_RESULT_METHOD_NOT_FOUND;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL Class_GetParentClassName(
    _In_ const MI_Class *self,
    _Outptr_result_maybenull_z_ const MI_Char **name)
{
    if ((self == NULL) || (name == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    *name = self->classDecl->superClass;

    if (self->classDecl->superClass)
    {
        return MI_RESULT_OK;
    }
    else
    {
        return MI_RESULT_INVALID_SUPERCLASS;
    }
}

/*============================================================================
 * Not implemented since it is not required right now
 *============================================================================
 */
MI_Result MI_CALL Class_GetParentClass(
    _In_ const MI_Class *self,
    _Outptr_ MI_Class **parentClass)
{
    return MI_RESULT_FAILED;
}

/*============================================================================
 *
 *============================================================================
 */
MI_Result MI_CALL GetParentClassExt(
            _In_ const MI_Class* self,
            _Out_ MI_Class *parentClass)
{
    if ((self == NULL) || (parentClass == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    if(self->classDecl->superClassDecl)
    {
        return Class_Construct(parentClass, self->classDecl->superClassDecl);
    }
    else
    {
        return MI_RESULT_INVALID_SUPERCLASS;
    }
}

/*============================================================================
 * Not implemented since it is not required right now; contract is Delete should never fail; so returning MI_RESULT_OK
 *============================================================================
 */
MI_Result MI_CALL Class_RCDelete(
    _In_ MI_Class* self_)
{
    MI_RCClass *self = (MI_RCClass*) self_;
    if(self->refcount)
    {
        /* We were created from a _New, not a construct */
        if (Atomic_Dec(&self->refcount) == 0)
        {
            if (self->batch)
                Batch_Delete(self->batch);
        }
    }
    return MI_RESULT_OK;
}

/*============================================================================
 * Not implemented since it is not required right now
 *============================================================================
 */
MI_Result MI_CALL Class_RCClone(
    _In_ const MI_Class* self_,
    _Outptr_ MI_Class** outboundNewClass)
{
    MI_RCClass *self = (MI_RCClass*) self_;
    if (self->refcount == 0)
    {
        /* Created via construct so don't support clone */
        return MI_RESULT_FAILED;
    }
    else
    {
        /* Created via _New so we are refcounted */
        *outboundNewClass = (MI_Class*) self_;
        Atomic_Inc(&self->refcount);
        return MI_RESULT_OK;
    }
        
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL ParameterSet_GetParameterCount(
    _In_ const MI_ParameterSet *self, 
    _Out_ MI_Uint32 *count)
{
    if (self && count)
    {
        *count = (MI_Uint32)self->reserved1;
        if (*count != 0)
        {
            (*count)--; /* Adjust for return type that is parameter[0] */
        }
        return MI_RESULT_OK;
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result _ParameterSet_GetParameterAt(
    _In_ const MI_ParameterSet *self,
    MI_Uint32 index,
    _Outptr_result_z_ const MI_Char **name,
    _Out_ MI_Type *parameterType,
    _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
    _Out_ MI_QualifierSet *qualifierSet)
{
    MI_ParameterDecl **parameterDecl;

    if ((self == NULL) || (name == NULL) || (parameterType == NULL) || (qualifierSet == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    
    if (index >= self->reserved1)
    {
        /* index too high */
        return MI_RESULT_NOT_FOUND;
    }

    parameterDecl = (MI_ParameterDecl**) self->reserved2;
    *name = parameterDecl[index]->name;
    *parameterType = parameterDecl[index]->type;
    (*qualifierSet).ft = &g_qualifierFT;
    (*qualifierSet).reserved1 = parameterDecl[index]->numQualifiers;
    (*qualifierSet).reserved2 = (ptrdiff_t) parameterDecl[index]->qualifiers;
    if (referenceClass)
    {
        *referenceClass = parameterDecl[index]->className;
    }
    return MI_RESULT_OK;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL ParameterSet_GetMethodReturnType(
    _In_ const MI_ParameterSet *self, 
    _Out_ MI_Type *returnType, 
    _Out_ MI_QualifierSet *qualifierSet)
{
    const MI_Char *name = NULL;
    MI_Char *referenceClassName = NULL;

    /* Return details are always at parameter[0] */
    return _ParameterSet_GetParameterAt(self, 0, &name, returnType, &referenceClassName, qualifierSet);
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL ParameterSet_GetParameterAt(
    _In_ const MI_ParameterSet *self,
    MI_Uint32 index,
    _Outptr_result_z_ const MI_Char **name,
    _Out_ MI_Type *parameterType,
    _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
    _Out_ MI_QualifierSet *qualifierSet)
{
    /* Return details are always at parameter[0] and can only be accessed through ParameterSet_GetMethodReturnType so 
      skip over it. Count was adjusted to compensate in ParameterSet_GetParameterCount to remove return item */
    index++;

    return _ParameterSet_GetParameterAt(self, index, name, parameterType, referenceClass, qualifierSet);
}

/*============================================================================
 *
 *============================================================================
 */
MI_Result MI_CALL ParameterSet_GetParameterAtExt(
    _In_ const MI_ParameterSet *self,
    MI_Uint32 index,
    _Outptr_result_z_ const MI_Char **name,
    MI_Type *parameterType,
    _Out_opt_ MI_Uint32* subscript,
    _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
    _Out_ MI_QualifierSet *qualifierSet,
    _Out_opt_ MI_Uint32* flags)
{
    MI_ParameterDecl **parameterDecl;
    MI_Result result = ParameterSet_GetParameterAt(self, index, name, parameterType, referenceClass, qualifierSet);

    if(result != MI_RESULT_OK)
    {
        return result;
    }

    /* Return details are always at parameter[0] and can only be accessed through ParameterSet_GetMethodReturnType so
          skip over it. Count was adjusted to compensate in ParameterSet_GetParameterCount to remove return item */
    index++;

    parameterDecl = (MI_ParameterDecl**) self->reserved2;

    if(subscript)
    {
        *subscript = parameterDecl[index]->subscript;
    }

    if(flags)
    {
        *flags = parameterDecl[index]->flags;
    }

    return MI_RESULT_OK;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL ParameterSet_GetParameter(
    _In_ const MI_ParameterSet *self,
    _In_z_ const MI_Char *name,
    _Out_ MI_Type *parameterType,
    _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
    _Out_ MI_QualifierSet *qualifierSet,
    _Out_ MI_Uint32 *index)
{
    MI_Uint32 myIndex;
    MI_Uint32 code;

    if ((self == NULL) || (name == NULL) || (parameterType == NULL) || (qualifierSet == NULL) || (index == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    code = Hash(name);
    
    /* Remember, skipping over return type that is parameter[0] */
    for (myIndex = 1; myIndex < self->reserved1; myIndex++)
    {
        MI_ParameterDecl **parameterDecl = (MI_ParameterDecl**) self->reserved2;
        if (parameterDecl[myIndex]->code == code && Tcscasecmp(name, parameterDecl[myIndex]->name) == 0)
        {
            MI_Result tmpResult;
            const MI_Char *tmpName = NULL;
            tmpResult = _ParameterSet_GetParameterAt(self, myIndex, &tmpName, parameterType, referenceClass, qualifierSet);
            if (tmpResult == MI_RESULT_OK)
            {
                *index = (myIndex-1);
            }
            return tmpResult;
        }
    }

    return MI_RESULT_NOT_FOUND;
}


/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL QualifierSet_GetQualifierCount(
    _In_ const MI_QualifierSet *self, 
    _Out_ MI_Uint32 *count)
{
    if ((self == NULL) || (count == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *count = (MI_Uint32) self->reserved1;
    return MI_RESULT_OK;
}

/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL QualifierSet_GetQualifierAt(
    _In_ const MI_QualifierSet *self,
    MI_Uint32 index,
    _Outptr_result_z_ const MI_Char **name,
    _Out_ MI_Type *qualifierType,
    _Out_ MI_Uint32 *qualifierFlags,    /* scope information */
    _Out_ MI_Value *qualifierValue
    )
{
    MI_Qualifier **qualifierDecl;

    if ((self == NULL) || (name == NULL) || (qualifierType == NULL) || (qualifierFlags == NULL) || (qualifierValue == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    if (index >= self->reserved1)
    {
        return MI_RESULT_NOT_FOUND;
    }

    qualifierDecl = (MI_Qualifier**) self->reserved2;
    *name = qualifierDecl[index]->name;
    *qualifierType = qualifierDecl[index]->type;

    *qualifierFlags = qualifierDecl[index]->flavor ;
    GetMIValueFromVoid(qualifierDecl[index]->type, qualifierDecl[index]->value, qualifierValue);

    return MI_RESULT_OK;
}

    
/*============================================================================
 * 
 *============================================================================
 */
MI_Result MI_CALL QualifierSet_GetQualifier(
    _In_ const MI_QualifierSet *self,
    _In_z_ const MI_Char *name,
    _Out_ MI_Type *qualifierType,
    _Out_ MI_Uint32 *qualifierFlags,    /* scope information */
    _Out_ MI_Value *qualifierValue,
    _Out_ MI_Uint32 *index
    )
{
    MI_Uint32 myIndex;

    if ((self == NULL) || (name == NULL) || (qualifierType == NULL) || (qualifierFlags == NULL) || (qualifierValue == NULL) || (index == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
  
    for (myIndex = 0; myIndex < self->reserved1; myIndex++)
    {
        MI_Qualifier **qualifierDecl = (MI_Qualifier**) self->reserved2;
        if (Tcscasecmp(name, qualifierDecl[myIndex]->name) == 0)
        {
            MI_Result tmpResult;
            const MI_Char *tmpName = NULL;
            tmpResult = QualifierSet_GetQualifierAt(self, myIndex, &tmpName, qualifierType, qualifierFlags, qualifierValue);
            if (tmpResult == MI_RESULT_OK)
            {
                *index = myIndex;
            }
            return tmpResult;
        }
    }

    return MI_RESULT_NOT_FOUND;
}

/*Qualifier can be propogated only if 
    1) It has ToSubClass qualifier
    2) It it not restricted. WMIV1 has no mechanism to tell if a qualifier is restricted, hence
        we are building the list of qualifiers we know are restricted. Note in future DMTF might introduce 
        some more standard qualifiers which are not covered in this list.
*/

MI_Char *restrictedQualifier[] = { 
                                    ZT("Abstract"), 
                                    ZT("Deprecated"),
                                    ZT("Experimental"),
                                    ZT("Override"),
                                    ZT("Version"),
                                    ZT("ClassVersion")
                                 };
MI_Boolean CanQualifierBePropogated( _In_ MI_Qualifier *qualifier)
{
    if(qualifier->flavor & MI_FLAG_TOSUBCLASS )
    {
        MI_Uint32 iCount;
        //Additional verification for other qualifiers.
        for(iCount = 0 ; iCount < (sizeof(restrictedQualifier)/sizeof(MI_Char*));iCount++)
        {
            if(Tcscasecmp(qualifier->name, restrictedQualifier[iCount]) == 0 )
            {
                return MI_FALSE;
            }
        }
        return MI_TRUE;        
    }
    return MI_FALSE;
}

const MI_ClassExtendedFTInternal g_ClassExtendedFTInternal =
{
    Class_GetClassName,
    Class_GetNameSpace,
    Class_GetServerName,
    Class_GetElementCount,
    Class_GetElement,
    Class_GetElementAt,
    Class_GetClassQualifierSet,
    Class_GetMethodCount,
    Class_GetMethodAt,
    Class_GetMethod,
    Class_GetParentClassName,
    Class_GetParentClass,
    Class_RCDelete,
    Class_RCClone,
    Class_GetClassFlagsExt,
    GetParentClassExt,
    Class_GetElementAtExt,
    Class_GetMethodAtExt    
};

const MI_QualifierSetFT g_qualifierFT = 
{
    QualifierSet_GetQualifierCount,
    QualifierSet_GetQualifierAt,
    QualifierSet_GetQualifier
};

const MI_ParameterSetExtendedFTInternal g_parameterExtendedFTInternal =
{
    ParameterSet_GetMethodReturnType,
    ParameterSet_GetParameterCount,
    ParameterSet_GetParameterAt,
    ParameterSet_GetParameter,
    ParameterSet_GetParameterAtExt    
};

