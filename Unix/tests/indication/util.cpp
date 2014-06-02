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

#include "util.h"
#include <pal/strings.h>

CimBaseAutoRelease::CimBaseAutoRelease(_In_ CimBase* obj):
    m_cimbase(obj)
{
    DEBUG_ASSERT(obj);
}

CimBaseAutoRelease::~CimBaseAutoRelease()
{
    if (m_cimbase)
    {
        CimBase_Release(m_cimbase);
        m_cimbase = NULL;
    }
}

_Use_decl_annotations_
MI_Uint32 IsInArray(
    MI_ConstString str,
    StringTagElement* strarr,
    MI_Uint32 size)
{
    StringTagElement* ste = IsInArrayEx(str, strarr, size);
    return (ste) ? ste->tag : 0;
}

_Use_decl_annotations_
StringTagElement* IsInArrayEx(
    MI_ConstString str,
    StringTagElement* strarr,
    MI_Uint32 size)
{
    for(MI_Uint32 i = 0; i < size; i++)
    {
        if (Tcscasecmp(strarr[i].element, str) == 0)
        {
            strarr[i].tag++;
            return &(strarr[i]);
        }
    }
    return NULL;
}

