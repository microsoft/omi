#include <string.h>
#include <stdlib.h>
#include "class.h"
#include "qualifierset.h"
#include "parameterset.h"

#if (MI_CHAR_TYPE == 1)
# define STRCASECMP strcasecmp
#elif defined(_MSC_VER)
# define STRCASECMP _wcsicmp
#else
# define STRCASECMP wcscasecmp
#endif

void GetValueFromVoid(
    MI_Type type, 
    _In_opt_ const void *source, 
    _Out_ MI_Value *value)
{
    memset(value, 0, sizeof(MI_Value));

    if (!source)
        return;

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

/*
**==============================================================================
**
** struct _MI_Class
** {
**     const MI_ClassFT* ft;
**     MI_CONST MI_ClassDecl* classDecl;
**     MI_CONST MI_Char* namespaceName;
**     MI_CONST MI_Char* serverName;
**     ptrdiff_t reserved[4];
** };
**
**==============================================================================
*/

static MI_Result MI_CALL _GetClassName(
    _In_ const MI_Class* self,
    _Outptr_result_maybenull_z_ const MI_Char** className)
{
    *className = self->classDecl->name;
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetNameSpace(
    _In_ const MI_Class* self,
    _Outptr_result_maybenull_z_ const MI_Char** nameSpace)
{
    (void)self;
    (void)nameSpace;
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _GetServerName(
    _In_ const MI_Class* self,
    _Outptr_result_maybenull_z_ const MI_Char** serverName)
{
    (void)self;
    (void)serverName;
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _GetElementCount(
    _In_ const MI_Class* self,
    _Out_ MI_Uint32* count)
{
    *count = self->classDecl->numProperties;
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetElement(
    _In_      const MI_Class* self,
    _In_z_    const MI_Char* name,
    _Out_opt_ MI_Value* value,
    _Out_opt_ MI_Boolean* valueExists,
    _Out_opt_ MI_Type* type,
    _Outptr_opt_result_maybenull_z_ MI_Char** referenceClass,
    _Out_opt_ MI_QualifierSet* qualifierSet,
    _Out_opt_ MI_Uint32* flags,
    _Out_opt_ MI_Uint32* index)
{
    (void)self;
    (void)name;
    (void)value;
    (void)valueExists;
    (void)type;
    (void)referenceClass;
    (void)qualifierSet;
    (void)flags;
    (void)index;
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _GetElementAt(
    _In_ const MI_Class* self,
    MI_Uint32 index,
    _Outptr_opt_result_maybenull_z_ const MI_Char** name,
    _Out_opt_ MI_Value* value,
    _Out_opt_ MI_Boolean* valueExists,
    _Out_opt_ MI_Type* type,
    _Outptr_opt_result_maybenull_z_ MI_Char** referenceClass,
    _Out_opt_ MI_QualifierSet* qualifierSet,
    _Out_opt_ MI_Uint32* flags)
{
    const MI_ClassDecl* cd = self->classDecl;
    const MI_PropertyDecl* pd;

    (void)value;
    (void)valueExists;
    (void)type;
    (void)referenceClass;
    (void)qualifierSet;
    (void)flags;

    /* Get i-th property */
    {
        if (index >= cd->numProperties)
            return MI_RESULT_FAILED;

        pd = cd->properties[index];
    }

    /* Get name */
    if (name)
        *name = pd->name;

    /* Get value */
    if (value)
    {
        GetValueFromVoid(pd->type, pd->value, value);
    }

    if (valueExists)
    {
        *valueExists = pd->value ? MI_TRUE : MI_FALSE;
    }

    /* Get type */
    if (type)
        *type = pd->type;

    /* Get referenceClass */
    if (referenceClass)
        *referenceClass = (MI_Char*)pd->className;

    /* Get qualifierSet */
    if (qualifierSet)
    {
        qualifierSet->ft = &g_qualifierSetFT;
        qualifierSet->reserved1 = pd->numQualifiers;
        qualifierSet->reserved2 = (ptrdiff_t)pd->qualifiers;
    }

    /* Get flags */
    if (flags)
    {
        *flags = pd->flags;
    }

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetClassQualifierSet(
    _In_ const MI_Class* self,
    _Out_opt_ MI_QualifierSet* qualifierSet)
{
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    if (qualifierSet)
    {
        qualifierSet->ft = &g_qualifierSetFT;
        qualifierSet->reserved1 = self->classDecl->numQualifiers;
        qualifierSet->reserved2 = (ptrdiff_t)self->classDecl->qualifiers;
    }

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetMethodCount(
    _In_ const MI_Class* self,
    _Out_ MI_Uint32* count)
{
    *count = self->classDecl->numMethods;
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetMethodAt(
    _In_ const MI_Class* self,
    MI_Uint32 index,
    _Outptr_result_z_ const MI_Char** name,
    _Out_opt_ MI_QualifierSet* qualifierSet,
    _Out_opt_ MI_ParameterSet* parameterSet)
{
    const MI_ClassDecl* cd = self->classDecl;
    const MI_MethodDecl* md;

    /* Check for out-of-bounds index */
    if (index >= cd->numProperties)
        return MI_RESULT_FAILED;

    /* Get i-th method*/
    md = cd->methods[index];

    /* Get name */
    if (name)
        *name = md->name;

    /* Get qualifier set */
    if (qualifierSet)
    {

        qualifierSet->reserved1 = md->numQualifiers;
        qualifierSet->reserved2 = (ptrdiff_t)md->qualifiers;
        qualifierSet->ft = &g_qualifierSetFT;
    }

    /* Get parameter set */
    if (parameterSet)
    {
        parameterSet->reserved1 = md->numParameters;
        parameterSet->reserved2 = (ptrdiff_t)md->parameters;
        parameterSet->ft = &g_parameterSetFT;
    }

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetMethod(
    _In_ const MI_Class* self,
    _In_z_ const MI_Char* name,
    _Out_opt_ MI_QualifierSet* qualifierSet,
    _Out_opt_ MI_ParameterSet* parameterSet,
    _Out_opt_ MI_Uint32* index)
{
    (void)self;
    (void)name;
    (void)qualifierSet;
    (void)parameterSet;
    (void)index;
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _GetParentClassName(
    _In_ const MI_Class* self,
    _Outptr_result_maybenull_z_ const MI_Char** name)
{
    (void)self;
    (void)name;
    *name = self->classDecl->superClass;
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetParentClass(
    _In_ const MI_Class* self,
    _Outptr_ MI_Class** parentClass)
{
    MI_Result r;

    if (!self || !parentClass || !self->classDecl)
        return MI_RESULT_INVALID_PARAMETER;

    if (!self->classDecl->superClassDecl)
        return MI_RESULT_INVALID_SUPERCLASS;

    *parentClass = (MI_Class*)malloc(sizeof(MI_Class));

    if (!*parentClass)
        return MI_RESULT_FAILED;

    r = Test_Class_Construct(*parentClass, self->classDecl->superClassDecl);

    if (r != MI_RESULT_OK)
        free(*parentClass);

    return r;
}

static MI_Result MI_CALL _Delete(
    _Inout_ MI_Class* self)
{
    if (self)
        free(self);

    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _Clone(
    _In_ const MI_Class* self,
    _Outptr_ MI_Class** newClass)
{
    (void)self;
    (void)newClass;
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_ClassFT _ft =
{
    _GetClassName,
    _GetNameSpace,
    _GetServerName,
    _GetElementCount,
    _GetElement,
    _GetElementAt,
    _GetClassQualifierSet,
    _GetMethodCount,
    _GetMethodAt,
    _GetMethod,
    _GetParentClassName,
    _GetParentClass,
    _Delete,
    _Clone,
};

MI_Result Test_Class_Construct(
    _Out_ MI_Class* self,
    _In_ const MI_ClassDecl* classDecl)
{
    memset(self, 0, sizeof(*self)) ;
    self->ft = &_ft;
    self->classDecl = (MI_ClassDecl*)classDecl;
    return MI_RESULT_OK;
}
