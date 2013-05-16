/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not
** use this file except in compliance with the License. You may obtain a copy
** of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
** MERCHANTABLITY OR NON-INFRINGEMENT.
**
** See the Apache 2 License for the specific language governing permissions
** and limitations under the License.
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
    return (self->ft->PostCimError)(
        self,
        error);
}

END_EXTERNC

#endif /* _omi_base_miextras_h */
