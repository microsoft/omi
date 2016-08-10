/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_base_miextras_h
#define _omi_base_miextras_h

#include <common.h>

BEGIN_EXTERNC

MI_Result MI_CALL MI_Instance_Print(
    _In_ const MI_Instance* self,
    _In_ FILE* os,
    MI_Uint32 level);

MI_INLINE MI_Result MI_CALL MI_PostResultWithMessage(
    MI_Context* self,
    MI_Result result,
    const MI_Char* message)
{
    MI_UNREFERENCED_PARAMETER(result);
    return (self->ft->PostError)(
        self,
        result,
        MI_RESULT_TYPE_MI,
        message);
}

MI_INLINE MI_Result MI_CALL MI_PostResultWithError(
    MI_Context* self,
    MI_Result result,
    const MI_Instance* error)
{
    MI_UNREFERENCED_PARAMETER(result);
    return (self->ft->PostCimError)(
        self,
        error);
}

END_EXTERNC

#endif /* _omi_base_miextras_h */
