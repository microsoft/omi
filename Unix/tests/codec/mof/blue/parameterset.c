/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "parameterset.h"
#include "qualifierset.h"
#include <ctype.h>
#if !defined(_MSC_VER)
#include <common/linux/sal.h>
#endif
#if (MI_CHAR_TYPE == 1)
# define STRCASECMP strcasecmp
# define STRLEN strlen
#elif defined(_MSC_VER)
# define STRCASECMP _wcsicmp
# define STRLEN wcslen
#else
#include <wchar.h>
# define STRCASECMP wcscasecmp
# define STRLEN wcslen
#endif

MI_INLINE MI_Uint32 _Hash(const MI_Char* name)
{
    MI_Uint32 n = (MI_Uint32)STRLEN(name);

    if (n == 0)
        return 0;

    return 
        tolower((MI_Uint8)name[0]) << 16 |
        tolower((MI_Uint8)name[n-1]) << 8 | 
        n;
}

static MI_Result _GetParameterAt(
    _In_ const MI_ParameterSet* self,
    MI_Uint32 index,
    _Deref_post_z_ const MI_Char** name,
    _Out_ MI_Type *type,
    _Outptr_opt_result_maybenull_z_ MI_Char** referenceClass,
    _Out_ MI_QualifierSet *qualifierSet)
{
    MI_ParameterDecl* pd;

    /* Adjust index to skip over 'MIReturn' pseudo-parameter */
    index++;

    /* Check parameters */
    if (!self || !name || !type || !qualifierSet)
        return MI_RESULT_INVALID_PARAMETER;

    /* Check out-of-bounds error */
    if (index >= self->reserved1)
        return MI_RESULT_FAILED;

    /* Set output parameters */
    pd = ((MI_ParameterDecl**)self->reserved2)[index];
    *name = pd->name;
    *type = pd->type;

    if (referenceClass)
        *referenceClass = (MI_Char*)pd->className;

    /* Construct the qualifier set */
    (*qualifierSet).ft = &g_qualifierSetFT;
    (*qualifierSet).reserved1 = pd->numQualifiers;
    (*qualifierSet).reserved2 = (ptrdiff_t) pd->qualifiers;

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetMethodReturnType(
    _In_ const MI_ParameterSet* self,
    _Out_ MI_Type* returnType,
    _Out_ MI_QualifierSet* qualifierSet)
{
    const MI_ParameterDecl* pd;

    /* Check parameters */
    if (!self || !returnType || !qualifierSet)
        return MI_RESULT_INVALID_PARAMETER;

    /* There must be at least one parameter */
    if (self->reserved1 == 0)
        return MI_RESULT_FAILED;

    /* Set output parameters */
    pd = ((MI_ParameterDecl**)self->reserved2)[0];
    *returnType = pd->type;

    /* Construct the qualifier set */
    (*qualifierSet).ft = &g_qualifierSetFT;
    (*qualifierSet).reserved1 = pd->numQualifiers;
    (*qualifierSet).reserved2 = (ptrdiff_t)pd->qualifiers;

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetParameterCount(
    _In_ const MI_ParameterSet* self,
    _Out_ MI_Uint32* count)
{
    if (!self || !count)
        return MI_RESULT_INVALID_PARAMETER;
    
    *count = (MI_Uint32)self->reserved1;

    if (*count != 0)
    {
        /* Don't count the "MIReturn" pseudo-parameter */
        (*count)--;
    }

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetParameter(
    _In_ const MI_ParameterSet* self,
    _In_z_ const MI_Char* name,
    _Out_ MI_Type* type,
    _Outptr_opt_result_maybenull_z_ MI_Char** referenceClass,
    _Out_ MI_QualifierSet* qualifierSet,
    _Out_ MI_Uint32* index)
{
    MI_Uint32 i;
    MI_Uint32 code;

    /* Check parameters */
    if (!self || !name || !type || !qualifierSet || !index)
        return MI_RESULT_INVALID_PARAMETER;

    code = _Hash(name);

    /* Begin one past 'MIReturn' pseudo-parameter */
    for (i = 1; i < self->reserved1; i++)
    {
        const MI_ParameterDecl* pd = ((MI_ParameterDecl**)self->reserved2)[i];

        if (pd->code == code && STRCASECMP(name, pd->name) == 0)
        {
            MI_Result r;
            MI_Char* tname = NULL;

            r = _GetParameterAt(
                self, 
                i, 
                (const MI_Char**)&tname, 
                type, referenceClass, qualifierSet);

            if (r == MI_RESULT_OK)
                *index = (i-1);

            return r;
        }
    }

    return MI_RESULT_NOT_FOUND;
}

const MI_ParameterSetFT g_parameterSetFT =
{
    _GetMethodReturnType,
    _GetParameterCount,
    _GetParameterAt,
    _GetParameter
};
