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

#include <stdlib.h>
#include <string.h>
#include "strarr.h"
#include <pal/strings.h>
#include "alloc.h"

char** StrArr()
{
    return (char**)PAL_Calloc(1, sizeof(char*));
}

_Use_decl_annotations_
void StrArrCat(CharPtrPtr * self_, ConstCharPtr str)
{
    size_t len;
    CharPtrPtr self = *self_;

    len = StrArrLen(self);
    self = (CharPtrPtr)PAL_Realloc(self, sizeof(char*) * (len + 2));

    if (self)
    {
        CharPtr s = PAL_Strdup(str);
        self[len] = s;
        self[len+1] = NULL;
    }

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26036)
#endif
    /* 
        OACR does not like NULL-ing buffers by using length above, instead it wants us to walk the entire array manually.
        This isn't necessary here. The logic is correct. 
    */
    *self_ = self;
#ifdef _PREFAST_
#pragma prefast (pop)
#endif
}

_Use_decl_annotations_
size_t StrArrLen(CharPtrPtr self)
{
    CharPtrPtr p = self;

    while (*p)
        p++;

    return p - self;
}

_Use_decl_annotations_
void StrArrFree(CharPtrPtr self)
{
    CharPtrPtr p = self;
    while (*p)
        PAL_Free(*p++);

    PAL_Free(self);
}

wchar_t** WcsArr()
{
    return (wchar_t**)PAL_Calloc(1, sizeof(wchar_t*));
}

_Use_decl_annotations_
void WcsArrCat(WcharPtrPtr * self_, ConstWcharPtr str)
{
    size_t len;
    WcharPtrPtr self = *self_;
    
    len = WcsArrLen(self);
    self = (WcharPtrPtr)PAL_Realloc(self, sizeof(wchar_t*) * (len + 2));

    if (self)
    {
        wchar_t* s = PAL_Wcsdup(str);
        self[len] = s;
        self[len+1] = NULL;
    }

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26036)
#endif
    /* 
        OACR does not like NULL-ing buffers by using length above, instead it wants us to walk the entire array manually.
        This isn't necessary here. The logic is correct. 
    */
    *self_ = self;
#ifdef _PREFAST_
#pragma prefast (pop)
#endif
}

_Use_decl_annotations_
size_t WcsArrLen(WcharPtrPtr self)
{
    WcharPtrPtr p = self;

    while (*p)
        p++;

    return p - self;
}

_Use_decl_annotations_
void WcsArrFree(WcharPtrPtr self)
{
    WcharPtrPtr p = self;
    while (*p)
        PAL_Free(*p++);

    PAL_Free(self);
}

_Use_decl_annotations_
ZChar** CloneStringArray(
    const ZChar** data, 
    MI_Uint32 size,
    Batch* batch)
{
    size_t n;
    MI_Uint32 i;
    ZChar* ptr;
    ZChar** array;

    /* Empty arrays are represented by NULL */
    if (!data || size == 0)
        return NULL;

    /* Calculate space for pointer array */
    n = size * sizeof(ZChar*);

    /* Calculate space for strings (add space for zero terminators) */
    for (i = 0; i < size; i++)
    {
        if (!data[i])
        {
            /* Null elements are illegal */
            return NULL;
        }

        n += (Tcslen(data[i]) + 1) * sizeof(ZChar);
    }

    /* Allocate memory */
    array = (ZChar**)BAlloc(batch, n, CALLSITE);

    if (!array)
        return NULL;

    ptr = (ZChar*)&array[size];

    /* Copy the strings */
    for (i = 0; i < size; i++)
    {
        size_t count = Tcslen(data[i]) + 1;
        memcpy(ptr, data[i], count * sizeof(ZChar));
        array[i] = ptr;
        ptr += count;
    }

    return array;
}

