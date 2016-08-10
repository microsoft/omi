/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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

