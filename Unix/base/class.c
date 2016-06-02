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
#include <base/field.h>
#include <pal/atomic.h>

MI_PropertyDecl * Class_Clone_Property(
    _Inout_ Batch *batch,
    MI_PropertyDecl MI_CONST* property);
MI_MethodDecl * Class_Clone_Method(
    _Inout_ Batch *batch,
    MI_MethodDecl MI_CONST* method,
    const MI_Char *className);

typedef struct _MI_ClassInternal
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

} MI_ClassInternal;


MI_INLINE void GetMIValueFromVoid(MI_Type type, _In_opt_ const void *source, _Out_ MI_Value *value)
{
    if (source == NULL)
    {
        memset(value, 0, sizeof(MI_Value));
        return;
    }

    memcpy(value, source, Type_SizeOf(type));
}

MI_Result MI_CALL Class_New(
    _In_ const MI_ClassDecl *classDecl,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *serverName,
    _Out_ MI_Class **outboundNewClass)
{
    Batch *ourBatch = NULL;
    MI_ClassInternal *newClass = NULL;

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
 * TODO: Not implemented since it is not required right now
 *============================================================================
 */
MI_Result MI_CALL Class_GetParentClass(
    _In_ const MI_Class *self,
    _Outptr_ MI_Class **parentClass)
{
    if ((self == NULL) || (parentClass == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (self->classDecl->superClassDecl)
    {
        if (self->classDecl->superClassDecl->owningClass && (self->classDecl->superClassDecl->owningClass != (MI_Class*)-1))
        {
            return MI_Class_Clone(self->classDecl->superClassDecl->owningClass, parentClass);
        }
        else
        {
            return Class_New(self->classDecl->superClassDecl, self->namespaceName, self->serverName, parentClass);
        }
    }
    else
    {
        return MI_RESULT_INVALID_SUPERCLASS;
   }
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


MI_Result ClassConstructor_New(
    _In_opt_ MI_Class *_parentClass, 
    _In_opt_z_ const MI_Char *namespaceName, /* Not needed if parentClass is passed in */
    _In_opt_z_ const MI_Char *serverName,    /* Not needed if parentClass is passed in */
    _In_z_ const MI_Char *className, 
    MI_Uint32 numberClassQualifiers,         /* number of extra class qualifiers you want to create.  Allowes us to pre-create array of correct size */
    MI_Uint32 numberProperties,              /* number of extra properties you want to create.  Allowes us to pre-create array of correct size */
    MI_Uint32 numberMethods,                 /* number of extra methods you want to create. Allowes us to pre-create array of correct size */
    _Out_ MI_Class **newClass              /* Object that is ready to receive new qualifiers/properties/methods */
    )
{
    Batch* finalBatch;
    MI_Result r = MI_RESULT_OK;
    MI_ClassDecl *classDecl;
    MI_ClassInternal *mi_class;
    MI_ClassInternal *parentClass = (MI_ClassInternal*)_parentClass;

    if ((newClass == NULL) || (className == NULL))
        return MI_RESULT_INVALID_PARAMETER;

    *newClass = NULL;

    //Allocate batch from start of batch
    {
        Batch batch = BATCH_INITIALIZER;

        finalBatch = (Batch*)Batch_Get(&batch, sizeof(Batch));
        if (!finalBatch)
        {
            Batch_Destroy(&batch);
            *newClass = NULL;
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }

        //Copy stack-version of batch over allocated batch
        memcpy(finalBatch, &batch, sizeof(Batch));
    }

    //Allocate class right after batch so we can always get back to
    //batch from class by subtracting sizeof(OAC_Batch) from doc pointer
    mi_class = (MI_ClassInternal*)Batch_Get(finalBatch, sizeof(MI_ClassInternal));
    if (mi_class == NULL)
    {
        r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto cleanup;
    }
    memset(mi_class, 0, sizeof(MI_ClassInternal));

    mi_class->refcount = 1;
    mi_class->batch = finalBatch;
    mi_class->ft = (const MI_ClassFT*)&g_ClassExtendedFTInternal;

    //Allocate MI_ClassDecl
    classDecl = (MI_ClassDecl*) Batch_Get(finalBatch, sizeof(MI_ClassDecl));
    mi_class->classDecl = classDecl;
    if (classDecl == NULL)
    {
        r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto cleanup;
    }

    memset(classDecl, 0, sizeof(MI_ClassDecl));
    classDecl->owningClass = (MI_Class*)mi_class;
    //Copy class name
    classDecl->name = Batch_Tcsdup(finalBatch, className);
    if (classDecl->name == NULL)
    {
        r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto cleanup;
    }

    if (parentClass)
    {
        //Propagate the parent class size
        classDecl->size = parentClass->classDecl->size;
    }
    else
    {
        classDecl->size = sizeof(MI_Instance);
    }

    classDecl->flags = MI_FLAG_CLASS;   //By default it will be a class, but it may become an association or indication via class qualifier

    //Attach parent classDecl to ours and addref parent
    if (parentClass)
    {
        int i;

        //Increment the refcount on the parent class decl
        if (parentClass->classDecl->owningClass && (parentClass->classDecl->owningClass != (void*)-1))
            Atomic_Inc(&((MI_ClassInternal*)parentClass->classDecl->owningClass)->refcount);

        classDecl->superClass = parentClass->classDecl->name;
        classDecl->superClassDecl = parentClass->classDecl;

        //borrow superclass namespace and server name
        mi_class->namespaceName = parentClass->namespaceName;
        mi_class->serverName = parentClass->serverName;

        //All properties and methods are propagated (however they can be overridden!)
        numberProperties += parentClass->classDecl->numProperties;
        numberMethods += parentClass->classDecl->numMethods;
        for (i = 0; i != parentClass->classDecl->numQualifiers; i++)
        {
            //Only qualifiers that are flavor ToSubClass are propagated (however they can be overridden!)
            if( CanQualifierBePropogated(parentClass->classDecl->qualifiers[i]))
            {
                numberClassQualifiers++;
            }
        }
        
        //Abstract can't be inherited. There are bunch of other qualifiers that cna't be intherited
        // But luckliy we define only abstract as part of the flags
        classDecl->flags |= (parentClass->classDecl->flags & (~MI_FLAG_ABSTRACT));
    }
    else
    {
        //Copy namespace
        if (namespaceName)
        {
            mi_class->namespaceName = Batch_Tcsdup(finalBatch, namespaceName);
            if (mi_class->namespaceName == NULL)
            {
                r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                goto cleanup;
            }
        }

        //Copy servername
        if (serverName)
        {
            mi_class->serverName = Batch_Tcsdup(finalBatch, serverName);
            if (mi_class->serverName == NULL)
            {
                r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                goto cleanup;
            }
        }
    }

    //Allocate qualifier array
    if (numberClassQualifiers)
    {
        classDecl->qualifiers = (MI_Qualifier**)Batch_Get(finalBatch, sizeof(MI_Qualifier*)*numberClassQualifiers);
        if (classDecl->qualifiers == NULL)
        {
            r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto cleanup;
        }
        memset(classDecl->qualifiers, 0xFF, sizeof(MI_Qualifier*)*numberClassQualifiers); //Will allow us to determine if array was big enough, kind of

        //Propagate parent qualifiers
        if (parentClass)
        {
            int i;
            for (i = 0; i != parentClass->classDecl->numQualifiers; i++)
            {
                if( CanQualifierBePropogated(parentClass->classDecl->qualifiers[i]))
                {
                    classDecl->qualifiers[classDecl->numQualifiers] = parentClass->classDecl->qualifiers[i];
                    classDecl->numQualifiers++;
                }
            }
        }
    }

    //Allocate property array
    if (numberProperties)
    {
        classDecl->properties = (MI_PropertyDecl**)Batch_Get(finalBatch, sizeof(MI_PropertyDecl*)*numberProperties);
        if (classDecl->properties == NULL)
        {
            r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto cleanup;
        }
        memset(classDecl->properties, 0xFF, sizeof(MI_PropertyDecl*)*numberProperties); //Will allow us to determine if array was big enough, kind of
        
        //Propagate parent properties.  Note that some may get overridden!
        if (parentClass && parentClass->classDecl->numProperties)
        {
            memcpy(classDecl->properties, parentClass->classDecl->properties, parentClass->classDecl->numProperties*sizeof(MI_PropertyDecl*));
            classDecl->numProperties = parentClass->classDecl->numProperties;
            //Now remove the inherited qualifiers if can't be inherited
            {
                MI_Uint32 iCount, jCount;
                for(iCount = 0 ; iCount <classDecl->numProperties; iCount++)
                {
                    if(classDecl->properties[iCount]->numQualifiers)
                    {
                        classDecl->properties[iCount] = Class_Clone_Property(finalBatch, classDecl->properties[iCount]);
                        if (classDecl->properties[iCount] == NULL)
                        {
                            r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                            goto cleanup;
                        }
                        memset(classDecl->properties[iCount]->qualifiers, 0xFF, sizeof(MI_Qualifier*) * classDecl->properties[iCount]->numQualifiers);
                        classDecl->properties[iCount]->numQualifiers = 0;
                        for( jCount = 0 ; jCount <  parentClass->classDecl->properties[iCount]->numQualifiers; jCount++)
                        {
                            if( CanQualifierBePropogated(parentClass->classDecl->properties[iCount]->qualifiers[jCount]))
                            {
                                classDecl->properties[iCount]->qualifiers[classDecl->properties[iCount]->numQualifiers] = 
                                                        parentClass->classDecl->properties[iCount]->qualifiers[jCount];
                                classDecl->properties[iCount]->numQualifiers++;
                            }
                        }
                    }
                }
            }
        }
    }


    //Allocate method array
    if (numberMethods)
    {
        classDecl->methods = (MI_MethodDecl**) Batch_Get(finalBatch, sizeof(MI_MethodDecl*)*numberMethods);
        if (classDecl->methods == NULL)
        {
            r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto cleanup;
        }
        memset(classDecl->methods, 0xFF, sizeof(MI_MethodDecl*)*numberMethods); //Will allow us to determine if array was big enough, kind of

        //Propagate parent methods.  Note that some may get overridden!
        if (parentClass && parentClass->classDecl->numMethods)
        {
            memcpy(classDecl->methods, parentClass->classDecl->methods, parentClass->classDecl->numMethods*sizeof(MI_MethodDecl*));
            classDecl->numMethods = parentClass->classDecl->numMethods;
            //Now remove the inherited qualifiers if can't be inherited
            {
                MI_Uint32 iCount, jCount;
                for(iCount = 0 ; iCount <classDecl->numMethods; iCount++)
                {
                    if(classDecl->methods[iCount]->numQualifiers)
                    {
                        classDecl->methods[iCount] = Class_Clone_Method(finalBatch, classDecl->methods[iCount], classDecl->name);
                        if (classDecl->methods[iCount] == NULL)
                        {
                            r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                            goto cleanup;
                        }
                        memset(classDecl->methods[iCount]->qualifiers, 0xFF, sizeof(MI_Qualifier*) * classDecl->methods[iCount]->numQualifiers);
                        classDecl->methods[iCount]->numQualifiers = 0;
                        for( jCount = 0 ; jCount <  parentClass->classDecl->methods[iCount]->numQualifiers; jCount++)
                        {
                            if( CanQualifierBePropogated(parentClass->classDecl->methods[iCount]->qualifiers[jCount]))
                            {
                                classDecl->methods[iCount]->qualifiers[classDecl->methods[iCount]->numQualifiers] = 
                                                        parentClass->classDecl->methods[iCount]->qualifiers[jCount];
                                classDecl->methods[iCount]->numQualifiers++;
                            }
                        }
                    }
                }
            }            
        }
    }

cleanup:
    if (r != MI_RESULT_OK)
    {
        Batch_Destroy(finalBatch);
    }
    else
    {
        *newClass = (MI_Class*)mi_class;
    }

    return r;
}

/* Helper to retrieve BATCH from class pointer */
MI_INLINE Batch *Class_GetBatchFromClass(_In_ MI_Class *refcountedClass)
{
    MI_ClassInternal *self = (MI_ClassInternal*)refcountedClass;
    if (self)
        return (Batch*) self->batch;
    else
        return NULL;
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


/* Add a qualifier to a ref-counted class.  The qualifier array needs to be pre-created by passing in the number of classQualifiers
    to the Class_New API
*/
static MI_Result _AddClassQualifier(
    _In_ MI_Class *refcountedClass, /* Object created from Class_New only */
    _In_z_ const MI_Char *name,     /* qualifier name */
    MI_Type type,                   /* Type of qualifier */
    MI_Value value,                 /* Value of qualifier */
    MI_Uint32 flavor,               /* Qualifier flags that specify if it is propagated etc. */
    MI_Boolean isArray,
    MI_Uint32 arrayLength,
    _Out_ MI_Uint32 *finalQualifierIndex)
{
    Batch *batch = NULL;
    MI_Class *mi_class = (MI_Class*)refcountedClass;
    
    //Get batch
    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    {
        MI_Uint32 qualifierIndex;
        MI_Qualifier **qualifierLocation;
        MI_Qualifier qualifier;

        memset(&qualifier, 0, sizeof(qualifier));
        qualifier.name = (MI_Char*)name;
        qualifier.type = type;
        qualifier.flavor = flavor;
        qualifier.value = &value;

        if (isArray)
        {
            //convert type to an array
            qualifier.type |= MI_ARRAY;

            //Allocate the array from the batch
            qualifier.value = NULL;
        }

        //See if we are overriding a qualifier first
        for (qualifierIndex = 0; qualifierIndex != mi_class->classDecl->numQualifiers; qualifierIndex++)
        {
            if (Tcscasecmp(name, mi_class->classDecl->qualifiers[qualifierIndex]->name)==0)
            {
                //Got it, this has been overridden.
                break;
            }
        }
        *finalQualifierIndex = qualifierIndex;

        //Get location of entry
        qualifierLocation = &mi_class->classDecl->qualifiers[qualifierIndex];
    
        //Qualifier pointer array values are initialialized to -1.  If not overriden and the next slot is not -1 then we have gone off the end of the array
        if ((qualifierIndex == mi_class->classDecl->numQualifiers) && ((*qualifierLocation) != (void*)-1))
        {
            return MI_RESULT_INVALID_PARAMETER;
        }

        //Pretty sure we have not gone off end of array so clone the qualifier into our batch
        (*qualifierLocation) = Class_Clone_Qualifier(batch, &qualifier);
        if ((*qualifierLocation) == NULL)
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    
        //Successfully added so update qualifier count if needed
        if (qualifierIndex == mi_class->classDecl->numQualifiers)
        {
            mi_class->classDecl->numQualifiers++;
        }

        /* Handle these qualifiers
            #define MI_FLAG_KEY             property, reference, default FALSE
            #define MI_FLAG_IN              parameter, default TRUE
            #define MI_FLAG_OUT             parameter, default FALSE
            #define MI_FLAG_REQUIRED        property, reference, method, parameter, default FALSE
            #define MI_FLAG_STATIC          property, method, default FALSE
            #define MI_FLAG_ABSTRACT        class, association, indication, default FALSE
            #define MI_FLAG_TERMINAL        class, association, indication, default FALSE
            #define MI_FLAG_EXPENSIVE       any, default FALSE
            #define MI_FLAG_STREAM          parameter, default FALSE
         */
        if ((type == MI_BOOLEAN) &&
                        (value.boolean == MI_TRUE))
        {
            if (Tcscasecmp(name, PAL_T("association"))==0)
            {
                mi_class->classDecl->flags &= ~MI_FLAG_ANY;
                mi_class->classDecl->flags |= MI_FLAG_ASSOCIATION;
            }
            else if (Tcscasecmp(name, PAL_T("indication"))==0)
            {
                mi_class->classDecl->flags &= ~MI_FLAG_ANY;
                mi_class->classDecl->flags |= MI_FLAG_INDICATION;
            }
            else if (Tcscasecmp(name, PAL_T("abstract"))==0)
            {
                mi_class->classDecl->flags |= MI_FLAG_ABSTRACT;
            }
            else if (Tcscasecmp(name, PAL_T("terminal"))==0)
            {
                mi_class->classDecl->flags |= MI_FLAG_TERMINAL;
            }
            else if (Tcscasecmp(name, PAL_T("expensive"))==0)
            {
                mi_class->classDecl->flags |= MI_FLAG_EXPENSIVE;
            }
        }
    }
    return MI_RESULT_OK;
}
MI_Result Class_AddClassQualifier(
    _In_ MI_Class *refcountedClass, /* Object created from Class_New only */
    _In_z_ const MI_Char *name,     /* qualifier name */
    MI_Type type,                   /* Type of qualifier */
    MI_Value value,                 /* Value of qualifier */
    MI_Uint32 flavor)               /* Qualifier flags that specify if it is propagated etc. */
{
    MI_Uint32 qualifierIndex;
    return _AddClassQualifier(refcountedClass, name, type, value, flavor, MI_FALSE, 0, &qualifierIndex);
}

static MI_Result _AddValueArray(
    _In_ MI_Class *refcountedClass, 
    MI_Type type, 
    MI_Uint32 numberArrayItems, 
    _Outptr_ MI_Array**arrayValueLocation)
{
    Batch *batch = NULL;
    MI_Uint32 actualArraySize;

    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    type = (MI_Type)(type | MI_ARRAY); //Convert to an array;
    actualArraySize = _CalculateArraySize(type, numberArrayItems);

    //Allovate the array value object
    *arrayValueLocation = (MI_Array*)Batch_Get(batch, sizeof(MI_Array));
    if (*arrayValueLocation == NULL)
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;

    //Allocate the array itself
    (*arrayValueLocation)->size = 0;   //It stays as 0 until items are actually added
    if (actualArraySize)
    {
        (*arrayValueLocation)->data = Batch_Get(batch, actualArraySize);
        if ((*arrayValueLocation)->data == NULL)
        {
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
        memset((*arrayValueLocation)->data, -1, actualArraySize);  //Set to -1
    }
    else
    {
        (*arrayValueLocation)->data = NULL;
    }

    return MI_RESULT_OK;
}
MI_Result Class_AddClassQualifierArray(
    _In_ MI_Class *refcountedClass,/* Object created from Class_New only */
    _In_z_ const MI_Char *name,      /* qualifier name */
    MI_Type type,                    /* Type of qualifier */
    MI_Uint32 flavor,                /* Flavor of qualifier */
    MI_Uint32 numberArrayItems,      /* Number of items in qualifier array */
    _Out_ MI_Uint32 *qualifierIndex)/* this qualifier index */
{
    MI_Result result;
    MI_Value value;

    //Null out the array bits
    memset(&value, 0, sizeof(value));

    type = (MI_Type)(type | MI_ARRAY);
    //Add as a nulled out array
    result = _AddClassQualifier(refcountedClass, name, type, value, flavor, MI_TRUE, numberArrayItems, qualifierIndex);
    if (result != MI_RESULT_OK)
        return result;
    return _AddValueArray(refcountedClass, type, numberArrayItems, (MI_Array**)&refcountedClass->classDecl->qualifiers[*qualifierIndex]->value);
}
/* Add an array item to the array created with call to Class_AddClassQualifierArray
    */
MI_Result Class_AddClassQualifierArrayItem(
    _In_ MI_Class *refcountedClass, /* Object created from Class_New only */
    MI_Uint32 qualifierIndex,         /* qualifier index */
    MI_Value value)                   /* value to add to array */
{
    Batch *batch = NULL;
    MI_Type type; 
    MI_Result result;
    MI_Array *arrayValue;

    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    type = (MI_Type)(refcountedClass->classDecl->qualifiers[qualifierIndex]->type & ~16); //Remove array part of type;

    arrayValue = (MI_Array*)refcountedClass->classDecl->qualifiers[qualifierIndex]->value;

    result = Class_Clone_ArrayValue(batch, type, arrayValue->data, arrayValue->size, &value);
    if (result != MI_RESULT_OK)
        return result;

    //Bump how many array items we have in value
    arrayValue->size++;

    return MI_RESULT_OK;
}

/* Add a element to a ref-counted class.  The element array needs to be pre-created by passing in the number of classProperties
    to the Class_New API
*/
static MI_Result _AddElement(
    _In_ MI_Class *refcountedClass,  /* Object created from Class_New only */
    _In_z_ const MI_Char *name,      /* element name */
    MI_Type type,                    /* Element type */
    MI_Value value,                  /* element default value */
    MI_Uint32 flags,                 /* element flags */
    _In_opt_z_ const MI_Char *associatedClassName, /* EmbeddedInstance class name or reference class name */
    MI_Boolean propagated,
    _In_opt_z_ const MI_Char *originClass,
    MI_Uint32 maxArrayLength,
    MI_Uint32 numberPropertyQualifiers, /* Number of qualifiers this element is going to get.  Allows us to pre-create array of correct size */
    _Out_ MI_Uint32 *elementId)
{
    Batch *batch = NULL;
    MI_Class *mi_class = refcountedClass;

    //Get batch
    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    {
        MI_Uint32 propertyIndex;
        MI_PropertyDecl **propertyLocation = NULL;
        MI_PropertyDecl *parentPropertyLocation = NULL;
        MI_PropertyDecl propertyDecl;
        MI_Uint32 totalParentPropertyQualifiers = 0;

        memset(&propertyDecl, 0, sizeof(propertyDecl));
        propertyDecl.flags = flags|MI_FLAG_PROPERTY;
        propertyDecl.code = Hash(name);
        propertyDecl.name = (MI_Char*)name;
        //propertyDecl.qualifiers
        //propertyDecl.numQualifiers
        propertyDecl.type = type;
        propertyDecl.className = NULL; // This is EmbeddedInstance class name or possibly reference class name
        propertyDecl.subscript = maxArrayLength;
        propertyDecl.offset = mi_class->classDecl->size;    //Size is always how big MI_Instance and all MI_<type>Field properties that follow, offset therefore is that, but then need to update size.
        propertyDecl.origin = mi_class->classDecl->name;
        propertyDecl.propagator = mi_class->classDecl->name;

        if (flags&MI_FLAG_NULL)
        {
            propertyDecl.value = NULL;
        }
        else
        {
            propertyDecl.value = &value;
        }

        if (associatedClassName)
        {
            propertyDecl.className = Batch_Tcsdup(batch, associatedClassName);
            if (propertyDecl.className == NULL)
            {
                return MI_RESULT_SERVER_LIMITS_EXCEEDED;
            }
        }
        if (!propagated && originClass)
        {
            propertyDecl.origin = Batch_Tcsdup(batch, originClass);
            if (propertyDecl.origin == NULL)
            {
                return MI_RESULT_SERVER_LIMITS_EXCEEDED;
            }
            propertyDecl.propagator = propertyDecl.origin;
        }


        //See if we are overriding an element first
        for (propertyIndex = 0; propertyIndex != mi_class->classDecl->numProperties; propertyIndex++)
        {
            if (Tcscasecmp(name, mi_class->classDecl->properties[propertyIndex]->name) == 0)
            {
                propertyDecl.origin = mi_class->classDecl->properties[propertyIndex]->origin;
                //copy qualifiers too.
                break;
            }
        }

        //Get location of property
        propertyLocation = &mi_class->classDecl->properties[propertyIndex];
        parentPropertyLocation = mi_class->classDecl->properties[propertyIndex];

        //Properties pointer array values are initialialized to -1.  If the next slot is not -1 then we have gone off the end of the array
        if ((propertyIndex == mi_class->classDecl->numProperties) && ((*propertyLocation) != (void*)-1))
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
    
        //Allocate property qualifier set array
        //First copy the qualifiers from the parent if any
        if( propertyIndex < mi_class->classDecl->numProperties )
        {
            totalParentPropertyQualifiers = mi_class->classDecl->properties[propertyIndex]->numQualifiers;
            // TODO: there might be other flags that we need to propogate.
            if(mi_class->classDecl->properties[propertyIndex]->flags & MI_FLAG_KEY)
            {
                propertyDecl.flags |= MI_FLAG_KEY;
            }
            if(mi_class->classDecl->properties[propertyIndex]->flags & MI_FLAG_READONLY)
            {
                propertyDecl.flags |= MI_FLAG_READONLY;
            }
        }

        //NOTE: THE ABOVE CODE MUST BE EXECUTED BEFORE CHANGIND PROPERTYLOCATION
        //Pretty sure we have not gone off end of array so clone the property into our batch
        (*propertyLocation) = Class_Clone_Property(batch, &propertyDecl);
        if ((*propertyLocation) == NULL)
        {
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
        

        if ( (numberPropertyQualifiers + totalParentPropertyQualifiers) > 0 )
        {
            (*propertyLocation)->qualifiers = (MI_Qualifier**) Batch_Get(batch, 
                                            sizeof(MI_Qualifier*)*(numberPropertyQualifiers + totalParentPropertyQualifiers ));
            if ((*propertyLocation)->qualifiers == NULL)
            {
                return MI_RESULT_SERVER_LIMITS_EXCEEDED;
            }
            memset((*propertyLocation)->qualifiers, 0xFF, sizeof(MI_Qualifier*)*(numberPropertyQualifiers + totalParentPropertyQualifiers));
            //Now copy the parents qualifiers if any
            if( totalParentPropertyQualifiers )
            {
                int i;
                for (i = 0; i != parentPropertyLocation->numQualifiers; i++)
                {
                    if (CanQualifierBePropogated(parentPropertyLocation->qualifiers[i]))
                    {
                        (*propertyLocation)->qualifiers[(*propertyLocation)->numQualifiers] = parentPropertyLocation->qualifiers[i];
                        (*propertyLocation)->numQualifiers++;
                    }
                }
            }
        }

        //Successfully added property so update proeprty count if necessary
        *elementId = propertyIndex;
        if (propertyIndex == mi_class->classDecl->numProperties)
        {
            mi_class->classDecl->numProperties++;
        }

        mi_class->classDecl->size += sizeof(Field);
    }
    return MI_RESULT_OK;
}
MI_Result Class_AddElement(
    _In_ MI_Class *refcountedClass,  /* Object created from Class_New only */
    _In_z_ const MI_Char *name,      /* element name */
    MI_Type type,                    /* Element type */
    MI_Value value,                  /* element default value */
    MI_Uint32 flags,                 /* element flags */
    _In_opt_z_ const MI_Char *associatedClassName, /* EmbeddedInstance class name or reference class name */
    MI_Boolean propagated,
    _In_opt_z_ const MI_Char *originClass,
    MI_Uint32 numberPropertyQualifiers, /* Number of qualifiers this element is going to get.  Allows us to pre-create array of correct size */
    _Out_ MI_Uint32 *elementId)
{
    return _AddElement(refcountedClass, name, type, value, flags, associatedClassName, propagated, originClass, 0, numberPropertyQualifiers, elementId);
}
MI_Result Class_AddElementArray(
    _In_ MI_Class *refcountedClass,  /* Object created from Class_New only */
    _In_z_ const MI_Char *name,      /* element name */
    MI_Type type,                    /* Element type */
    MI_Uint32 flags,                 /* element flags */
    _In_opt_z_ const MI_Char *associatedClassName, /* EmbeddedInstance class name or reference class name */
    MI_Boolean propagated,
    _In_opt_z_ const MI_Char *originClass,
    MI_Uint32 maxArrayLength,
    MI_Uint32 numberElementQualifiers, /* Number of qualifiers this element is going to get.  Allows us to pre-create array of correct size */
    MI_Uint32 numberPropertyArrayItems,
    _Out_ MI_Uint32 *elementId)
{
    MI_Result result;
    MI_Value value;
    MI_Uint32 nulledFlags;
    
    if (numberPropertyArrayItems == 0)
        nulledFlags = flags | MI_FLAG_NULL;
    else
        nulledFlags = flags;

    //Null out the array bits
    memset(&value, 0, sizeof(value));

    type = (MI_Type)(type | MI_ARRAY);
    //Add as a nulled out array
    result = _AddElement(refcountedClass, name, type, value, nulledFlags, associatedClassName, propagated, originClass, maxArrayLength, numberElementQualifiers, elementId);
    if (result != MI_RESULT_OK)
        return result;

    return _AddValueArray(refcountedClass, type, numberPropertyArrayItems, (MI_Array**)&refcountedClass->classDecl->properties[*elementId]->value);
}

MI_Result Class_AddElementArrayItem(
    _In_ MI_Class *refcountedClass,  /* Object created from Class_New only */
    MI_Uint32 elementId,      
    MI_Value value)                   /* element array item*/
{
    Batch *batch = NULL;
    MI_Type type; 
    MI_Result result;
    MI_Array *arrayValue;

    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    type = (MI_Type)(refcountedClass->classDecl->properties[elementId]->type & ~16); //Remove array part of type;

    arrayValue = (MI_Array*)refcountedClass->classDecl->properties[elementId]->value;

    result = Class_Clone_ArrayValue(batch, type, arrayValue->data, arrayValue->size, &value);
    if (result != MI_RESULT_OK)
        return result;

    //Bump how many array items we have in value
    arrayValue->size++;

    return MI_RESULT_OK;
}

/* Add a element qualifierto a ref-counted class.  The element property qualifier array needs to be pre-created by passing in the correct numberPropertyQualifiers
    to the Class_AddElement API
*/
static MI_Result _AddElementQualifier(
    _In_ MI_Class *refcountedClass, 
    MI_Uint32 elementIndex, 
    _In_z_ const MI_Char *name, 
    MI_Type type, 
    MI_Value value,
    MI_Uint32 flavor,
    MI_Boolean isArray,
    _Out_ MI_Uint32 *qualifierIndex)
{
    Batch *batch = NULL;
    MI_Class *mi_class = refcountedClass;

    //Get batch
    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    {
        MI_PropertyDecl **propertyLocation = &mi_class->classDecl->properties[elementIndex];
        MI_Qualifier **qualifierLocation = NULL;
        MI_Qualifier qualifier;
        MI_Uint32 actualQualifierIndex;

        if ((type == MI_SINT32) && (Tcscasecmp(name, PAL_T("maxlen"))==0))  /* WMIv1 mapping */
        {
            (*propertyLocation)->subscript = value.sint32;
            //continue to add the qualifier
        }
        else if (Tcscasecmp(name, PAL_T("CIMTYPE"))==0) /* WMIv1 mapping */
        {
            //Need to map WMIv1 embedded instance/object CIMTYPE to proper qualifiers
            if (((mi_class->classDecl->properties[elementIndex]->type&~MI_ARRAY) == MI_INSTANCE) && (type == MI_STRING))
            {
                if (Tcscasecmp(value.string, PAL_T("object")) == 0)
                {
                    name = PAL_T("EmbeddedObject");
                    type = MI_BOOLEAN;
                    value.boolean = MI_TRUE;
                    flavor = MI_FLAG_DISABLEOVERRIDE | MI_FLAG_TOSUBCLASS;
                }
                else if (Tcsncasecmp(value.string, PAL_T("object:"), 7) == 0)   //check prefix is object:
                {
                    name = PAL_T("EmbeddedInstance");
                    type = MI_STRING;
                    value.string = value.string + 7;    //move past object: prefix
                }
            }
            else if (((mi_class->classDecl->properties[elementIndex]->type&~MI_ARRAY) == MI_REFERENCE) && (type == MI_STRING))
            {
                //Need to strongly type the reference if relevant
                if (Tcscasecmp(value.string, PAL_T("ref")) == 0)
                {
                    //Weakly typed by default, so can ignore
                    return MI_RESULT_OK;
                }
                else if (Tcsncasecmp(value.string, PAL_T("ref:"), 4) == 0)   //check prefix is object:
                {
                    mi_class->classDecl->properties[elementIndex]->className = Batch_Tcsdup(batch, value.string+4);
                    if (mi_class->classDecl->properties[elementIndex]->className == NULL)
                        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
                    else
                        return MI_RESULT_OK;
                }
            }
            else
            {
                return MI_RESULT_OK;
            }
        }

        memset(&qualifier, 0, sizeof(qualifier));
        qualifier.name = (MI_Char*)name;
        qualifier.type = type;
        qualifier.flavor = flavor;

        if (!isArray)
        {
            qualifier.value = &value;
        }
        //Now check if we already inheriting the qualifier from the parent
        for (actualQualifierIndex = 0; actualQualifierIndex < (*propertyLocation)->numQualifiers; actualQualifierIndex++)
        {
            if (Tcscasecmp(name, (*propertyLocation)->qualifiers[actualQualifierIndex]->name) == 0)
            {
                break;
            }
        }
        qualifierLocation = &(*propertyLocation)->qualifiers[actualQualifierIndex];

        //Qualifier pointer array values are initialialized to -1.  If the next slot is not -1 then we have gone off the end of the array
        if ( (actualQualifierIndex >= (*propertyLocation)->numQualifiers) && ((*qualifierLocation) != (void*)-1))
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
    
        //Pretty sure we have not gone off end of array so clone the qualifier into our batch
        (*qualifierLocation) = Class_Clone_Qualifier(batch, &qualifier);
        if ((*qualifierLocation) == NULL)
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    

        /* Handle these qualifiers
            #define MI_FLAG_KEY             property, reference, default FALSE
            #define MI_FLAG_IN              parameter, default TRUE
            #define MI_FLAG_OUT             parameter, default FALSE
            #define MI_FLAG_REQUIRED        property, reference, method, parameter, default FALSE
            #define MI_FLAG_STATIC          property, method, default FALSE
            #define MI_FLAG_ABSTRACT        class, association, indication, default FALSE
            #define MI_FLAG_TERMINAL        class, association, indication, default FALSE
            #define MI_FLAG_EXPENSIVE       any, default FALSE
            #define MI_FLAG_STREAM          parameter, default FALSE
            #define MI_FLAG_READONLY        parameter, default FALSE
         */
        if ((type == MI_BOOLEAN) &&
                 (value.boolean == MI_TRUE))
        {
            if (Tcscasecmp(name, PAL_T("key"))==0)
                 
            {
                (*propertyLocation)->flags |= MI_FLAG_KEY;
            }
            else if (Tcscasecmp(name, PAL_T("required"))==0)
            {
                (*propertyLocation)->flags |= MI_FLAG_REQUIRED;
            }
            else if (Tcscasecmp(name, PAL_T("static"))==0)
            {
                (*propertyLocation)->flags |= MI_FLAG_STATIC;
            }
            else if (Tcscasecmp(name, PAL_T("expensive"))==0)
            {
                (*propertyLocation)->flags |= MI_FLAG_EXPENSIVE;
            }
            else if (Tcscasecmp(name, PAL_T("read"))==0)
            {
                //If there is no write qualifier, set read-only
                MI_Uint32 qualifierIndex = 0;
                MI_Boolean foundWrite = MI_FALSE;
                for (;qualifierIndex != (*propertyLocation)->numQualifiers; qualifierIndex++)
                {
                    if (Tcscasecmp((*propertyLocation)->qualifiers[qualifierIndex]->name, PAL_T("write"))==0)
                    {
                        foundWrite = MI_TRUE;
                        break;
                    }
                }
                if (!foundWrite)
                    (*propertyLocation)->flags |= MI_FLAG_READONLY;
            }
            else if (Tcscasecmp(name, PAL_T("write"))==0)
            {
                //If readonly is set, turn it off
                (*propertyLocation)->flags &= ~MI_FLAG_READONLY;

            }
        }
        if ((Tcscasecmp(name, PAL_T("embeddedinstance"))==0) && (mi_class->classDecl->properties[elementIndex]->className == NULL))
        {
            // Fix-up the reference class name for embedded instances because someone forgot to set it when adding the actual element
            mi_class->classDecl->properties[elementIndex]->className = Batch_Tcsdup(batch, value.string);
            if (mi_class->classDecl->properties[elementIndex]->className == NULL)
                return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }

        //Successfully added property qualifier so update count
        *qualifierIndex = actualQualifierIndex;
        if(actualQualifierIndex >= (*propertyLocation)->numQualifiers)
        {
            (*propertyLocation)->numQualifiers++;
        }
    }

    return MI_RESULT_OK;
}
MI_Result Class_AddElementQualifier(
    _In_ MI_Class *refcountedClass, 
    MI_Uint32 elementIndex, 
    _In_z_ const MI_Char *name, 
    MI_Type type, 
    MI_Value value,
    MI_Uint32 flavor)
{
    MI_Uint32 qualifierIndex;
    return _AddElementQualifier(refcountedClass, elementIndex, name, type, value, flavor, MI_FALSE, &qualifierIndex);
}

MI_Result Class_AddElementQualifierArray(
    _In_ MI_Class *refcountedClass,  /* Object created from Class_New only */
    MI_Uint32 elementId,               /* element index returned from Class_AddElement */
    _In_z_ const MI_Char *name, 
    MI_Type type, 
    MI_Uint32 flavor,
    MI_Uint32 numberItemsInQualifierArray,
    _Out_ MI_Uint32 *qualifierIndex) 
{
    MI_Result result;
    MI_Value value;

    //Null out the array bits
    memset(&value, 0, sizeof(value));

    type = (MI_Type)(type | MI_ARRAY);
    //Add as a nulled out array
    result = _AddElementQualifier(refcountedClass, elementId, name, type, value, flavor, MI_TRUE, qualifierIndex);
    if (result != MI_RESULT_OK)
        return result;
    return _AddValueArray(refcountedClass, type, numberItemsInQualifierArray, (MI_Array**)&refcountedClass->classDecl->properties[elementId]->qualifiers[*qualifierIndex]->value);
}

MI_Result Class_AddElementQualifierArrayItem(
    _In_ MI_Class *refcountedClass, 
    MI_Uint32 elementIndex, 
    MI_Uint32 qualifierIndex,
    MI_Value value)
{
    Batch *batch = NULL;
    MI_Type type; 
    MI_Result result;
    MI_Array *arrayValue;

    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    type = (MI_Type)(refcountedClass->classDecl->properties[elementIndex]->qualifiers[qualifierIndex]->type & ~16); //Remove array part of type;

    arrayValue = (MI_Array*)refcountedClass->classDecl->properties[elementIndex]->qualifiers[qualifierIndex]->value;

    result = Class_Clone_ArrayValue(batch, type, arrayValue->data, arrayValue->size, &value);
    if (result != MI_RESULT_OK)
        return result;

    //Bump how many array items we have in value
    arrayValue->size++;

    return MI_RESULT_OK;
}

/* Add a method to a refcounted class.  The class method array was precreated by passing numberMethods to Class_New.
    Add the method in the next slot by querying how many methods are currently there.  Don't add more methods than 
    you said you wanted as the array is fixed.
*/
MI_Result Class_AddMethod(
    _In_ MI_Class *refcountedClass, 
    _In_z_ const MI_Char *name, 
    MI_Uint32 flags,    /* Is this needed? */
    MI_Uint32 numberParameters, 
    MI_Uint32 numberQualifiers,
    _Out_ MI_Uint32 *methodId)
{
    Batch *batch = NULL;
    MI_Class *mi_class = refcountedClass;

    //Get batch
    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    {
        MI_Uint32 methodIndex;
        MI_MethodDecl **methodLocation = NULL;
        MI_MethodDecl *parentMethodLocation = NULL;
        MI_MethodDecl methodDecl;
        MI_Uint32 totalParentMethodQualifiers = 0;        

        memset(&methodDecl, 0, sizeof(methodDecl));
        methodDecl.flags = flags|MI_FLAG_METHOD;
        methodDecl.code = Hash(name);
        methodDecl.name = (MI_Char*)name;
        //methodDecl.qualifiers
        //methodDecl.numQualifiers
        //methodDecl.parameters
        //methodDecl.numParameters
        //methodDecl.size - static information, not needed here.  Similar to offset parameters in various places.
        //methodDecl.returnType - Set with parameter 0 of parameters
        methodDecl.origin = mi_class->classDecl->name;
        methodDecl.propagator = mi_class->classDecl->name;
        //methodDecl.schema
        //methodDecl.function

        //See if we are overriding an method first
        for (methodIndex = 0; methodIndex != mi_class->classDecl->numMethods; methodIndex++)
        {
            if (Tcscasecmp(name, mi_class->classDecl->methods[methodIndex]->name) == 0)
            {
                methodDecl.origin = mi_class->classDecl->methods[methodIndex]->origin;
                break;
            }
        }

        //Get location of property
        methodLocation = &mi_class->classDecl->methods[methodIndex];
        parentMethodLocation = mi_class->classDecl->methods[methodIndex];

        //Method pointer array values are initialialized to -1.  If the next slot is not -1 then we have gone off the end of the array
        if ((methodIndex == mi_class->classDecl->numMethods) && ((*methodLocation) != (void*)-1))
        {
            return MI_RESULT_INVALID_PARAMETER;
        }        

        //First prepare to copy the qualifiers from the parent if any.
        if( methodIndex < mi_class->classDecl->numMethods )
        {
            totalParentMethodQualifiers = mi_class->classDecl->methods[methodIndex]->numQualifiers;
            methodDecl.flags |= mi_class->classDecl->methods[methodIndex]->flags;
        }


        //Pretty sure we have not gone off end of array so clone the property into our batch
        (*methodLocation) = Class_Clone_Method(batch, &methodDecl, mi_class->classDecl->name);
        if ((*methodLocation) == NULL)
        {
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
    
        //Allocate method parameter set array
        if ( numberParameters )
        {
            //Parameters are not inherited from the parent.
            (*methodLocation)->parameters = (MI_ParameterDecl**) Batch_Get(batch, 
                                                sizeof(MI_ParameterDecl*)* numberParameters );
            if ((*methodLocation)->parameters == NULL)
            {
                return MI_RESULT_SERVER_LIMITS_EXCEEDED;
            }
            memset((*methodLocation)->parameters, 0xFF, sizeof(MI_ParameterDecl*)* numberParameters );
        }

        //Allocate method qualifier set array
        if ((numberQualifiers + totalParentMethodQualifiers) > 0)
        {
            (*methodLocation)->qualifiers = (MI_Qualifier**) Batch_Get(batch, 
                                            sizeof(MI_Qualifier*)*(numberQualifiers+ totalParentMethodQualifiers));
            if ((*methodLocation)->qualifiers == NULL)
            {
                return MI_RESULT_SERVER_LIMITS_EXCEEDED;
            }
            memset((*methodLocation)->qualifiers, 0xFF, sizeof(MI_Qualifier*)*(numberQualifiers+ totalParentMethodQualifiers));
            if( totalParentMethodQualifiers )
            {
                MI_Uint32 i;
                for( i = 0; i < parentMethodLocation->numQualifiers; i++)
                {
                    if( CanQualifierBePropogated(parentMethodLocation->qualifiers[i] ))
                    {
                        (*methodLocation)->qualifiers[(*methodLocation)->numQualifiers] = parentMethodLocation->qualifiers[i];
                        (*methodLocation)->numQualifiers++;
                    }
                }
            }            
        }

        //Successfully added method so update method count if needed
        *methodId = methodIndex;
        if (methodIndex == mi_class->classDecl->numMethods)
        {
            mi_class->classDecl->numMethods++;
        }
    }

    return MI_RESULT_OK;
}

/* Add a method qualifier to a refcounted class.  The method qualifier array was precreated by passing numberQualifiers to Class_AddMethod.
    Add the qualifier in the next slot by querying how many qualifiers are currently there.  Don't add more qualifiers than
    you said you wanted as the array is fixed
*/
static MI_Result _AddMethodQualifier(
    _In_ MI_Class *refcountedClass, 
    MI_Uint32 methodIndex, 
    _In_z_ const MI_Char *name, 
    MI_Type type, 
    MI_Value value,
    MI_Uint32 flavor,
    MI_Boolean isArray,
    _Out_ MI_Uint32 *qualifierId)
{
    Batch *batch = NULL;
    MI_Class *mi_class = refcountedClass;

    //Get batch
    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    {
        MI_MethodDecl **methodLocation = &mi_class->classDecl->methods[methodIndex];
        MI_Qualifier **qualifierLocation = NULL;
        MI_Qualifier qualifier;
        MI_Uint32 actualQualifierIndex;

        memset(&qualifier, 0, sizeof(qualifier));
        qualifier.name = (MI_Char*)name;
        qualifier.type = type;
        qualifier.flavor = flavor;

        if (!isArray)
        {
            qualifier.value = &value;
        }
        //Now check if we already inheriting the qualifier from the parent
        for (actualQualifierIndex = 0; actualQualifierIndex < (*methodLocation)->numQualifiers; actualQualifierIndex++)
        {
            if (Tcscasecmp(name, (*methodLocation)->qualifiers[actualQualifierIndex]->name) == 0)
            {
                break;
            }
        }
        qualifierLocation = &(*methodLocation)->qualifiers[actualQualifierIndex];
        
    
        //Qualifier pointer array values are initialialized to -1.  If the next slot is not -1 then we have gone off the end of the array
        if ( (actualQualifierIndex >= (*methodLocation)->numQualifiers) && ((*qualifierLocation) != (void*)-1))
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
    
        //Pretty sure we have not gone off end of array so clone the qualifier into our batch
        (*qualifierLocation) = Class_Clone_Qualifier(batch, &qualifier);
        if ((*qualifierLocation) == NULL)
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    

        /* Handle these qualifiers
            #define MI_FLAG_KEY             property, reference, default FALSE
            #define MI_FLAG_IN              parameter, default TRUE
            #define MI_FLAG_OUT             parameter, default FALSE
            #define MI_FLAG_REQUIRED        property, reference, method, parameter, default FALSE
            #define MI_FLAG_STATIC          property, method, default FALSE
            #define MI_FLAG_ABSTRACT        class, association, indication, default FALSE
            #define MI_FLAG_TERMINAL        class, association, indication, default FALSE
            #define MI_FLAG_EXPENSIVE       any, default FALSE
            #define MI_FLAG_STREAM          parameter, default FALSE
         */
        if ((Tcscasecmp(name, PAL_T("required"))==0) &&
            (type == MI_BOOLEAN) &&
            (value.boolean == MI_TRUE))
        {
            (*methodLocation)->flags |= MI_FLAG_REQUIRED;
        }
        else if ((Tcscasecmp(name, PAL_T("static"))==0) &&
                 (type == MI_BOOLEAN) &&
                 (value.boolean == MI_TRUE))
        {
            (*methodLocation)->flags |= MI_FLAG_STATIC;
        }
        else if ((Tcscasecmp(name, PAL_T("expensive"))==0) &&
                 (type == MI_BOOLEAN) &&
                 (value.boolean == MI_TRUE))
        {
            (*methodLocation)->flags |= MI_FLAG_EXPENSIVE;
        }

        
        //qualifierIdadded property qualifier so update count
        *qualifierId = actualQualifierIndex;
        if(actualQualifierIndex >= (*methodLocation)->numQualifiers)
        {
            (*methodLocation)->numQualifiers++;
        }
    }
    return MI_RESULT_OK;
}

MI_Result Class_AddMethodQualifier(
    _In_ MI_Class *refcountedClass, 
    MI_Uint32 methodIndex, 
    _In_z_ const MI_Char *name, 
    MI_Type type, 
    MI_Value value,
    MI_Uint32 flavor)
{
    MI_Uint32 qualifierId;

    return _AddMethodQualifier(refcountedClass, methodIndex, name, type, value, flavor, MI_FALSE, &qualifierId);
}

MI_Result Class_AddMethodQualifierArray(
    _In_ MI_Class *refcountedClass, 
    MI_Uint32 methodIndex, 
    _In_z_ const MI_Char *name, 
    MI_Type type, 
    MI_Uint32 flavor,
    MI_Uint32 numberItemsInArray,
    _Out_ MI_Uint32 *qualifierId)
{
    MI_Result result;
    MI_Value value;

    //Null out the array bits
    memset(&value, 0, sizeof(value));

    type = (MI_Type)(type | MI_ARRAY);
    //Add as a nulled out array
    result = _AddMethodQualifier(refcountedClass, methodIndex, name, type, value, flavor, MI_TRUE, qualifierId);
    if (result != MI_RESULT_OK)
        return result;
    return _AddValueArray(refcountedClass, type, numberItemsInArray, (MI_Array**)&refcountedClass->classDecl->methods[methodIndex]->qualifiers[*qualifierId]->value);
}
        
MI_Result Class_AddMethodQualifierArrayItem(
    _In_ MI_Class *refcountedClass, 
    MI_Uint32 methodIndex, 
    MI_Uint32 qualifierId, 
    MI_Value value)
{
    Batch *batch = NULL;
    MI_Type type; 
    MI_Result result;
    MI_Array *arrayValue;

    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    type = (MI_Type)(refcountedClass->classDecl->methods[methodIndex]->qualifiers[qualifierId]->type & ~16); //Remove array part of type;

    arrayValue = (MI_Array*)refcountedClass->classDecl->methods[methodIndex]->qualifiers[qualifierId]->value;

    result = Class_Clone_ArrayValue(batch, type, arrayValue->data, arrayValue->size, &value);
    if (result != MI_RESULT_OK)
        return result;

    //Bump how many array items we have in value
    arrayValue->size++;

    return MI_RESULT_OK;
}

/* Add a method proeprty to a refcounted class.  The method property array was precreated by passing numberParameters to Class_AddMethod.
    Add the property in the next slot by querying how many qualifiers are currently there.  Don't add more properties than 
    you said you wanted as the array is fixed
*/
MI_Result Class_AddMethodParameter(
    _In_ MI_Class *refcountedClass, 
    MI_Uint32 methodIndex, 
    _In_z_ const MI_Char *name,
    _In_opt_z_ const MI_Char *refClassname,
    MI_Type type, 
    MI_Uint32 flags,
    MI_Uint32 arrayMaxSize,
    MI_Uint32 numberQualifiers,
    _Out_ MI_Uint32 *parameterId)
{
    Batch *batch = NULL;
    MI_Class *mi_class = refcountedClass;

    //Get batch
    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    {
        MI_MethodDecl **methodLocation = &mi_class->classDecl->methods[methodIndex];
        MI_ParameterDecl **parameterLocation = NULL;
        MI_ParameterDecl *previousParameterLocation = NULL;
        MI_ParameterDecl parameterDecl;
        MI_Uint32 actualParameterIndex;    
        MI_Uint32 totalPreviousPropertyQualifiers = 0;        

        memset(&parameterDecl, 0, sizeof(parameterDecl));
        parameterDecl.flags = flags|MI_FLAG_PARAMETER|MI_FLAG_IN;
        parameterDecl.code = Hash(name);
        parameterDecl.name = (MI_Char*)name;
        //parameterDecl.qualifiers
        //parameterDecl.numQualifiers
        parameterDecl.type = type;
        parameterDecl.className = (MI_Char*)refClassname;
        parameterDecl.subscript = arrayMaxSize;
        //parameterDecl.offset
        // TODO: Disabling the propogation for now. WINRM and WMIDCOM behavior is different
        
        //Now check if we already inheriting the parameter from the parent
        for (actualParameterIndex = 0; actualParameterIndex < (*methodLocation)->numParameters; actualParameterIndex++)
        {
            if (Tcscasecmp(name, (*methodLocation)->parameters[actualParameterIndex]->name) == 0)
            {
                break;
            }
        }
        // TODO: Disable next line when the above code is uncommented
        //actualParameterIndex = (*methodLocation)->numParameters;
        previousParameterLocation = (*methodLocation)->parameters[actualParameterIndex];
        parameterLocation = &(*methodLocation)->parameters[actualParameterIndex];
        

        //Properties pointer array values are initialialized to -1.  If the next slot is not -1 then we have gone off the end of the array
        if ( (actualParameterIndex >= (*methodLocation)->numParameters) && ((*parameterLocation) != (void*)-1))
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
        //Count previous qualifiers
        if( actualParameterIndex < (*methodLocation)->numParameters )
        {
            totalPreviousPropertyQualifiers += (*methodLocation)->parameters[actualParameterIndex]->numQualifiers;
        }
    
        //Pretty sure we have not gone off end of array so clone the property into our batch
        (*parameterLocation) = Class_Clone_Parameter(batch, &parameterDecl, mi_class->classDecl->name);
        if ((*parameterLocation) == NULL)
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    
        //Allocate method parameter qualifier set array
        if ((numberQualifiers + totalPreviousPropertyQualifiers) >0)
        {
            (*parameterLocation)->qualifiers = (MI_Qualifier**) Batch_Get(batch, sizeof(MI_Qualifier*)* (numberQualifiers + totalPreviousPropertyQualifiers));
            if ((*parameterLocation)->qualifiers == NULL)
            {
                return MI_RESULT_SERVER_LIMITS_EXCEEDED;
            }
            memset((*parameterLocation)->qualifiers, 0xFF, sizeof(MI_Qualifier*)* (numberQualifiers + totalPreviousPropertyQualifiers));
            //Now copy the previous qualifiers if any. This scenario is mainly used when both {in,Out} qualifiers are specified on a parameter
            if( totalPreviousPropertyQualifiers)
            {
                int i;
                for(i =0 ;i != previousParameterLocation->numQualifiers; i++)
                {
                    if(CanQualifierBePropogated(previousParameterLocation->qualifiers[i]) )
                    {
                        (*parameterLocation)->qualifiers[(*parameterLocation)->numQualifiers] = previousParameterLocation->qualifiers[i];
                        (*parameterLocation)->numQualifiers++;
                    }
                }
            }
        }

        //If first parameter then set method return type in method structure
        if ((*methodLocation)->numParameters == 0)
        {
            (*methodLocation)->returnType = type;
        }

        //Successfully added method parameter so update proeprty count
        *parameterId = actualParameterIndex;
        if(actualParameterIndex >= (*methodLocation)->numParameters)
        {
            (*methodLocation)->numParameters++;
        }
        
    }
    return MI_RESULT_OK;
}
    
/* Add a method property qualifier to a refcounted class.  The method property qualifier array was precreated by passing numberQualifiers to Class_AddMethodProperty.
    Add the qualifier in the next slot by querying how many method property qualifiers are currently there.  Don't add more qualifiers than 
    you said you wanted as the array is fixed
*/
static MI_Result _AddMethodParameterQualifier(
    _In_ MI_Class *refcountedClass, 
    MI_Uint32 methodIndex, 
    MI_Uint32 parameterIndex, 
    _In_z_ const MI_Char *name, 
    MI_Type type, 
    MI_Value value,
    MI_Uint32 flavor,
    MI_Boolean isArray,
    _Out_ MI_Uint32 *qualifierIndex)
{
    Batch *batch = NULL;
    MI_Class *mi_class = refcountedClass;
    *qualifierIndex = 0;

    //Get batch
    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    {
        MI_MethodDecl **methodLocation = &mi_class->classDecl->methods[methodIndex];
        MI_ParameterDecl **parameterLocation = &(*methodLocation)->parameters[parameterIndex];
        MI_Qualifier **qualifierLocation = NULL;
        MI_Qualifier qualifier;
        MI_Uint32 actualQualifierIndex;        

        if (Tcscasecmp(name, PAL_T("CIMTYPE"))==0) /* WMIv1 mapping */
        {
            //Need to map WMIv1 embedded instance/object CIMTYPE to proper qualifiers
            if ((((*parameterLocation)->type&~MI_ARRAY) == MI_INSTANCE) && (type == MI_STRING))
            {
                if (Tcscasecmp(value.string, PAL_T("object")) == 0)
                {
                    name = PAL_T("EmbeddedObject");
                    type = MI_BOOLEAN;
                    value.boolean = MI_TRUE;
                    flavor = MI_FLAG_DISABLEOVERRIDE | MI_FLAG_TOSUBCLASS;
                }
                else if (Tcsncasecmp(value.string, PAL_T("object:"), 7) == 0)   //check prefix is object:
                {
                    name = PAL_T("EmbeddedInstance");
                    type = MI_STRING;
                    value.string = value.string + 7;    //move past object: prefix
                }
            }
            else if ((((*parameterLocation)->type&~MI_ARRAY) == MI_REFERENCE) && (type == MI_STRING))
            {
                //Need to strongly type the reference if relevant
                if (Tcscasecmp(value.string, PAL_T("ref")) == 0)
                {
                    //Weakly typed by default, so can ignore
                    return MI_RESULT_OK;
                }
                else if (Tcsncasecmp(value.string, PAL_T("ref:"), 4) == 0)   //check prefix is object:
                {
                    (*parameterLocation)->className = Batch_Tcsdup(batch, value.string+4);
                    if ((*parameterLocation)->className == NULL)
                        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
                    else
                        return MI_RESULT_OK;
                }
            }
            else
            {
                return MI_RESULT_OK;
            }
        }

        memset(&qualifier, 0, sizeof(qualifier));
        qualifier.name = (MI_Char*)name;
        qualifier.type = type;
        qualifier.flavor = flavor;

        if (!isArray)
        {
            qualifier.value = &value;
        }
        // TODO: Disabling the propogation for now. WINRM and WMIDCOM behavior is different
        
        //Now check if we already inheriting the qualifier from the parent
        for (actualQualifierIndex = 0; actualQualifierIndex < (*parameterLocation)->numQualifiers; actualQualifierIndex++)
        {
            if (Tcscasecmp(name, (*parameterLocation)->qualifiers[actualQualifierIndex]->name) == 0)
            {
                break;
            }
        }
        // TODO: Disable next line when the above code is uncommented
        //actualQualifierIndex = (*parameterLocation)->numQualifiers;        
        qualifierLocation = &(*parameterLocation)->qualifiers[actualQualifierIndex];
        
    
        //Qualifier pointer array values are initialialized to -1.  If the next slot is not -1 then we have gone off the end of the array
        if ( (actualQualifierIndex >= (*parameterLocation)->numQualifiers) && ((*qualifierLocation) != (void*)-1))
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
    
        //Pretty sure we have not gone off end of array so clone the qualifier into our batch
        (*qualifierLocation) = Class_Clone_Qualifier(batch, &qualifier);
        if ((*qualifierLocation) == NULL)
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    

        /* Handle these qualifiers
            #define MI_FLAG_KEY             property, reference, default FALSE
            #define MI_FLAG_IN              parameter, default TRUE
            #define MI_FLAG_OUT             parameter, default FALSE
            #define MI_FLAG_REQUIRED        property, reference, method, parameter, default FALSE
            #define MI_FLAG_STATIC          property, method, default FALSE
            #define MI_FLAG_ABSTRACT        class, association, indication, default FALSE
            #define MI_FLAG_TERMINAL        class, association, indication, default FALSE
            #define MI_FLAG_EXPENSIVE       any, default FALSE
            #define MI_FLAG_STREAM          parameter, default FALSE
         */
        if ((Tcscasecmp(name, PAL_T("in"))==0) &&
            (type == MI_BOOLEAN))
        {
            //IN=trye being default means we have to better handle turning it off
            if (value.boolean == MI_TRUE)
            {
                (*parameterLocation)->flags |= MI_FLAG_IN;
            }
            else
            {
                (*parameterLocation)->flags &= ~MI_FLAG_IN;
            }
        }
        else if ((Tcscasecmp(name, PAL_T("out"))==0) &&
                 (type == MI_BOOLEAN) &&
                 (value.boolean == MI_TRUE))
        {
            (*parameterLocation)->flags |= MI_FLAG_OUT;
        }
        else if ((Tcscasecmp(name, PAL_T("required"))==0) &&
                 (type == MI_BOOLEAN) &&
                 (value.boolean == MI_TRUE))
        {
            (*parameterLocation)->flags |= MI_FLAG_REQUIRED;
        }
        else if ((Tcscasecmp(name, PAL_T("expensive"))==0) &&
                 (type == MI_BOOLEAN) &&
                 (value.boolean == MI_TRUE))
        {
            (*parameterLocation)->flags |= MI_FLAG_EXPENSIVE;
        }
        else if ((Tcscasecmp(name, PAL_T("stream"))==0) &&
                 (type == MI_BOOLEAN) &&
                 (value.boolean == MI_TRUE))
        {
            (*parameterLocation)->flags |= MI_FLAG_STREAM;
        }

        //Successfully added property qualifier so update count
        *qualifierIndex = actualQualifierIndex;
        if(actualQualifierIndex >= (*parameterLocation)->numQualifiers)
        {
            (*parameterLocation)->numQualifiers++;
        }
    }
    return MI_RESULT_OK;
}

MI_Result Class_AddMethodParameterQualifier(
    _In_ MI_Class *refcountedClass, 
    MI_Uint32 methodIndex, 
    MI_Uint32 parameterIndex, 
    _In_z_ const MI_Char *name, 
    MI_Type type, 
    MI_Value value,
    MI_Uint32 flavor)
{
    MI_Uint32 qualifierIndex;
    return _AddMethodParameterQualifier(refcountedClass, methodIndex, parameterIndex, name, type, value, flavor, MI_FALSE, &qualifierIndex);
}
MI_Result Class_AddMethodParameterQualifierArray(
    _In_ MI_Class *refcountedClass, 
    MI_Uint32 methodIndex, 
    MI_Uint32 parameterIndex, 
    _In_z_ const MI_Char *name, 
    MI_Type type, 
    MI_Uint32 flavor,
    MI_Uint32 numberItemsInArray,
    _Out_ MI_Uint32 *qualifierIndex)
{
    MI_Result result;
    MI_Value value;

    //Null out the array bits
    memset(&value, 0, sizeof(value));

    type = (MI_Type)(type | MI_ARRAY); 
    //Add as a nulled out array
    result = _AddMethodParameterQualifier(refcountedClass, methodIndex, parameterIndex, name, type, value, flavor, MI_TRUE, qualifierIndex);
    if (result != MI_RESULT_OK)
        return result;
    return _AddValueArray(refcountedClass, type, numberItemsInArray, (MI_Array**)&refcountedClass->classDecl->methods[methodIndex]->parameters[parameterIndex]->qualifiers[*qualifierIndex]->value);
}

MI_Result Class_AddMethodParameterQualifierArrayItem(
    _In_ MI_Class *refcountedClass, 
    MI_Uint32 methodIndex, 
    MI_Uint32 parameterIndex, 
    MI_Uint32 qualifierIndex,
    MI_Value value)
{
    Batch *batch = NULL;
    MI_Type type; 
    MI_Result result;
    MI_Array *arrayValue;

    batch = Class_GetBatchFromClass(refcountedClass);
    if (batch == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    type = (MI_Type)(refcountedClass->classDecl->methods[methodIndex]->parameters[parameterIndex]->qualifiers[qualifierIndex]->type & ~16); //Remove array part of type;

    arrayValue = (MI_Array*)refcountedClass->classDecl->methods[methodIndex]->parameters[parameterIndex]->qualifiers[qualifierIndex]->value;

    result = Class_Clone_ArrayValue(batch, type, arrayValue->data, arrayValue->size, &value);
    if (result != MI_RESULT_OK)
        return result;

    //Bump how many array items we have in value
    arrayValue->size++;

    return MI_RESULT_OK;
}

/* Delete a refcounted class.  Decrement refcount and if zero release parent class refcount and delete our batch.
 */
MI_Result MI_CALL Class_Delete(
    _In_ MI_Class* self)
{
    MI_ClassInternal *internalSelf = (MI_ClassInternal*) self;
    if (internalSelf && internalSelf->refcount)
    {
        if (Atomic_Dec(&internalSelf->refcount) == 0)
        {
            //Do we own our own classDecl, or does someone else?
            if (internalSelf->classDecl->owningClass != self)
            {
                if (internalSelf->classDecl->owningClass && (internalSelf->classDecl->owningClass != (MI_Class*)-1))
                {
                    //Someone else owns it
                    MI_Class_Delete(internalSelf->classDecl->owningClass);
                }
            }
            else
            {
                /* First need to release parent refcount */
                MI_ClassDecl *rcParent = (MI_ClassDecl*)self->classDecl->superClassDecl;
                if (rcParent && rcParent->owningClass && (rcParent->owningClass != (MI_Class*)-1))
                {
                    Class_Delete(rcParent->owningClass);
                }
            }
            /* Now release ourself */
            Batch_Delete((Batch *)internalSelf->batch);
        }
    }
    return MI_RESULT_OK;
}
    



/*============================================================================
 * Traditional clone where we just copy everything
 *============================================================================
 */
MI_Result MI_CALL Class_FullClone(
    _In_ const MI_Class* self,
    _Outptr_ MI_Class** outboundNewClass)
{
    Batch *batch = NULL;
    MI_ClassInternal *newClass = NULL;

    if (self == NULL || outboundNewClass == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    *outboundNewClass = NULL;
    
    batch = Batch_New(BATCH_MAX_PAGES);
    if (batch == NULL)
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    newClass = Batch_Get(batch, sizeof(MI_Class));
    if (newClass == NULL)
    {
        Batch_Delete(batch);
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    memset(newClass, 0, sizeof(MI_Class));

    newClass->ft = self->ft;
    newClass->batch = batch;

    if (self->namespaceName)
    {
        newClass->namespaceName = Batch_Tcsdup(batch, self->namespaceName);
        if (newClass->namespaceName == NULL)
        {
            Batch_Delete(batch);
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
    }
    if (self->serverName)
    {
        newClass->serverName = Batch_Tcsdup(batch, self->serverName);
        if (newClass->serverName == NULL)
        {
            Batch_Delete(batch);
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
    }
    newClass->classDecl = Class_Clone_ClassDecl(batch, self->classDecl);
    if (newClass->classDecl == NULL)
    {
        Batch_Delete(batch);
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    newClass->classDecl->owningClass = (MI_Class*)newClass;
    newClass->refcount = 1;
    *outboundNewClass = (MI_Class*) newClass;
    return MI_RESULT_OK;
}

/* Clone a refcounted class.  Cloning just requires the refcount to be incremented.
 */
MI_Result MI_CALL Class_Clone(
    _In_ const MI_Class* self,
    _Outptr_ MI_Class** outboundNewClass)
{
    if (self && outboundNewClass)
    {
        MI_ClassInternal *internalSelf = (MI_ClassInternal*)self;

        if (internalSelf->refcount == 0)
        {
            /* Created via construct so do full clone */
            return Class_FullClone(self, outboundNewClass);
        }

        //Bump our refcount
        Atomic_Inc(&internalSelf->refcount);

        /* Return same object */
        *outboundNewClass = (MI_Class*)self;
        
        return MI_RESULT_OK;
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
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
    Class_Delete,
    Class_Clone,
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

