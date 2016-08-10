/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "instance.h"
#include "class.h"
#include <stdlib.h>
#include <string.h>

static MI_Result MI_CALL _GetClassName(
    _In_ const MI_Instance* self, 
    _Outptr_result_maybenull_z_ const MI_Char** className)
{
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    if (className)
        *className = self->classDecl->name;

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetNameSpace(
    _In_ const MI_Instance* self,
    _Outptr_result_maybenull_z_ const MI_Char** nameSpace)
{
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    if (nameSpace)
        *nameSpace = self->nameSpace;

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetElementCount(
    _In_ const MI_Instance* self,
    _Out_ MI_Uint32* count)
{
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    if (count)
        *count = self->classDecl->numProperties;

    return MI_RESULT_OK;
}

/* The size (in bytes) for each of the given MI_Type */
static size_t _valueSizes[] =
{
    sizeof(MI_Boolean),
    sizeof(MI_Uint8),
    sizeof(MI_Sint8),
    sizeof(MI_Uint16),
    sizeof(MI_Sint16),
    sizeof(MI_Uint32),
    sizeof(MI_Sint32),
    sizeof(MI_Uint64),
    sizeof(MI_Sint64),
    sizeof(MI_Real32),
    sizeof(MI_Real64),
    sizeof(MI_Char16),
    sizeof(MI_Datetime),
    sizeof(MI_Char*),
    sizeof(MI_Instance*),
    sizeof(MI_Instance*),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
    sizeof(MI_Array),
};

static MI_Result MI_CALL _GetElementAt(
    _In_ const MI_Instance* self, 
    MI_Uint32 index,
    _Outptr_result_maybenull_z_ const MI_Char** name,
    _Out_opt_ MI_Value* value,
    _Out_opt_ MI_Type* type,
    _Out_opt_ MI_Uint32* flags)
{
    const MI_PropertyDecl* pd;
    const MI_Uint8* field;
    size_t vsize;

    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    if (!self->classDecl)
        return MI_RESULT_FAILED;

    if (index >= self->classDecl->numProperties)
        return MI_RESULT_FAILED;

    pd = self->classDecl->properties[index];

    if (!pd)
        return MI_RESULT_FAILED;

    if (name)
        *name = pd->name;

    field = (MI_Uint8*)self + pd->offset;
    vsize = _valueSizes[pd->type];

    if (value)
        memcpy(value, field, vsize);

    if (type)
        *type = pd->type;

    if (flags)
    {
        MI_Boolean exists = *(MI_Boolean*)(field + vsize);
        *flags = pd->flags;

        if (!exists)
            *flags |= MI_FLAG_NULL;
    }

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetServerName(
    _In_ const MI_Instance* self,
    _Outptr_result_maybenull_z_ const MI_Char** name)
{
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    if (name)
        *name = self->nameSpace;

    return MI_RESULT_OK;
}

static MI_Result _GetClass(
    _In_ const MI_Instance* self,
    _Outptr_ MI_Class** instanceClass)
{
    MI_Result r;

    if (!self || !instanceClass)
        return MI_RESULT_INVALID_PARAMETER;

    if (!self->classDecl)
        return MI_RESULT_FAILED;

    *instanceClass = (MI_Class*)malloc(sizeof(MI_Class));

    if (!*instanceClass)
        return MI_RESULT_FAILED;

    r = Test_Class_Construct(*instanceClass, self->classDecl);

    if (r != MI_RESULT_OK)
        free(*instanceClass);

    return r;
}

static const MI_InstanceFT _ft =
{
    NULL, /* Clone */
    NULL, /* Destruct */
    NULL, /* Delete */
    NULL, /* IsA */
    _GetClassName,
    NULL, /* SetNameSpace */
    _GetNameSpace,
    _GetElementCount,
    NULL, /* AddElement */
    NULL, /* SetElement */
    NULL, /* SetElementAt */
    NULL, /* GetElement */
    _GetElementAt,
    NULL, /* ClearElement */
    NULL, /* ClearElementAt */
    _GetServerName,
    NULL, /* SetServerName */
    _GetClass,
};


MI_Result Test_Instance_Construct(
    _Out_ MI_Instance* self,
    _In_ const MI_ClassDecl* classDecl)
{
    memset(self, 0, classDecl->size);
    self->ft = &_ft;
    self->classDecl = classDecl;
    return MI_RESULT_OK;
}
