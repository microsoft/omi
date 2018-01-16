/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "qualifierset.h"
#include <string.h>
#include <common/linux/sal.h>

#if (MI_CHAR_TYPE == 1)
# define STRCASECMP strcasecmp
#else
#include <wchar.h>

#if !defined(CONFIG_HAVE_WCSCASECMP)
// defined in pal/strings
int wcscasecmp(const wchar_t* s1, const wchar_t* s2);
#endif

# define STRCASECMP wcscasecmp
#endif

extern void GetValueFromVoid(
    MI_Type type, 
    _In_opt_ const void *source, 
    _Out_ MI_Value *value);

static MI_Result MI_CALL _GetQualifierCount(
    _In_ const MI_QualifierSet* self, 
    _Out_ MI_Uint32* count)
{
    if (!self || !count)
        return MI_RESULT_INVALID_PARAMETER;

    *count = (MI_Uint32)self->reserved1;
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetQualifierAt(
    _In_ const MI_QualifierSet* self,
    MI_Uint32 index,
    _Deref_post_z_ const MI_Char** name,
    _Out_ MI_Type* qualifierType,
    _Out_ MI_Uint32* qualifierFlags,
    _Out_ MI_Value* qualifierValue)
{
    MI_Qualifier** qd;

    if (!self || !name || !qualifierType || !qualifierFlags || !qualifierValue)
        return MI_RESULT_INVALID_PARAMETER;

    if (index >= self->reserved1)
        return MI_RESULT_NOT_FOUND;

    qd = (MI_Qualifier**)self->reserved2;
    *name = qd[index]->name;
    *qualifierType = qd[index]->type;
    *qualifierFlags = qd[index]->flavor ;

    GetValueFromVoid(qd[index]->type, qd[index]->value, qualifierValue);
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetQualifier(
    _In_ const MI_QualifierSet *self,
    _In_z_ const MI_Char *name,
    _Out_ MI_Type *qualifierType,
    _Out_ MI_Uint32 *qualifierFlags,
    _Out_ MI_Value *qualifierValue,
    _Out_ MI_Uint32 *index)
{
    MI_Uint32 i;

    if (!self || 
        !name || 
        !qualifierType || 
        !qualifierFlags || 
        !qualifierValue ||
        !index)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
  
    for (i = 0; i < self->reserved1; i++)
    {
        MI_Qualifier** qualifierDecls = (MI_Qualifier**)self->reserved2;

        if (STRCASECMP(name, qualifierDecls[i]->name) == 0)
        {
            MI_Result r;
            MI_Char *tmpName = NULL;

            r = _GetQualifierAt(
                self, 
                i, 
                (const MI_Char**)&tmpName, 
                qualifierType, 
                qualifierFlags, 
                qualifierValue);

            if (r == MI_RESULT_OK)
                *index = i;

            return r;
        }
    }

    return MI_RESULT_NOT_FOUND;
}

const MI_QualifierSetFT g_qualifierSetFT =
{
    _GetQualifierCount,
    _GetQualifierAt,
    _GetQualifier
};
