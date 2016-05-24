/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <ctype.h>
#include "strset.h"
#include <pal/strings.h>
/* TOLOWER */
/* STRLEN */
/* PRINTF */
#if (MI_CHAR_TYPE == 1)
# define TOLOWER tolower
# define STRLEN strlen
# define PRINTF printf
#else
# define TOLOWER towlower
# define STRLEN wcslen
# define PRINTF wprintf
#endif

#define HASH_SEED_PRIME_NUMBER 1313038763

static MI_Uint32 _MakeToken(
    _In_reads_(len) const MI_Char* str, 
    size_t len)
{
    if (!len)
        return 0;

    return 
        ((MI_Uint32)TOLOWER(str[0])) << 16 |
        ((MI_Uint32)TOLOWER(str[len-1])) << 8 | 
        (MI_Uint32)len;
}

typedef struct StrSetBucket /* derives from HashBucket */
{
    struct StrSetBucket* next;

    /* String value */
    MI_Char* str;

    /* Token for the string value */
    MI_Uint32 token;

    /* Whether item is committed (cannot be undone) */
    MI_Boolean committed;
}
StrSetBucket;

static size_t _Hash(const HashBucket* bucket_)
{
    StrSetBucket* bucket = (StrSetBucket*)bucket_;
    MI_Uint32 h = HASH_SEED_PRIME_NUMBER;
    const MI_Char* p = bucket->str;

    while(*p)
    {
        h ^= ((h << 5) + TOLOWER(*p) + (h >> 2));
        p++;
    }

    return h ^ bucket->token;
}

static int _Equal(
    const HashBucket* bucket1_,
    const HashBucket* bucket2_)
{
    StrSetBucket* bucket1 = (StrSetBucket*)bucket1_;
    StrSetBucket* bucket2 = (StrSetBucket*)bucket2_;

    return 
        bucket1->token == bucket2->token &&
        Tcscasecmp(bucket1->str, bucket2->str) == 0;
}

static void _Release(
    HashBucket* bucket_)
{
    StrSetBucket* bucket = (StrSetBucket*)bucket_;
    PAL_Free(bucket);
}

_Use_decl_annotations_
int StrSet_Init(StrSet* self)
{
    const size_t NUM_LISTS = 1024;

    return HashMap_Init(
        &self->impl, 
        NUM_LISTS,
        _Hash, 
        _Equal, 
        _Release);
}

_Use_decl_annotations_
void StrSet_Destroy(StrSet* self)
{
    HashMap_Destroy(&self->impl);
}

_Use_decl_annotations_
MI_Boolean StrSet_Contains(
    StrSet* self, 
    const MI_Char* str)
{
    StrSetBucket bucket;

    bucket.str = (MI_Char*)str;
    bucket.token = _MakeToken(str, STRLEN(str));

    if (HashMap_Find(&self->impl, (HashBucket*)&bucket))
        return MI_TRUE;

    return MI_FALSE;
}

_Use_decl_annotations_
int StrSet_Add(
    StrSet* self, 
    const MI_Char* str)
{
    StrSetBucket* bucket;
    size_t numBytes;
    size_t len;

    len = STRLEN(str);
    numBytes = (len + 1) * sizeof(MI_Char);
    bucket = (StrSetBucket*)PAL_Malloc(sizeof(StrSetBucket) + numBytes);

    if (!bucket)
        return -1;

    bucket->str = (MI_Char*)(bucket + 1);
    bucket->token = _MakeToken(str, len);
    bucket->committed = MI_FALSE;
    memcpy(bucket->str, str, numBytes);

    if (HashMap_Insert(&self->impl, (HashBucket*)bucket) != 0)
    {
        /* Already exists! */
        PAL_Free(bucket);
        return 1;
    }

    return 0;
}

void StrSet_Commit(
    _Inout_ StrSet* self)
{
    size_t i;

    for (i = 0; i < self->impl.numLists; i++)
    {
        StrSetBucket* p = (StrSetBucket*)self->impl.lists[i];

        for (; p; p = p->next)
        {
            p->committed = MI_TRUE;
        }
    }
}

void StrSet_Undo(
    _Inout_ StrSet* self)
{
    size_t i;

    for (i = 0; i < self->impl.numLists; i++)
    {
        StrSetBucket* p = (StrSetBucket*)self->impl.lists[i];
        StrSetBucket* prev = NULL;

        while (p)
        {
            StrSetBucket* next = p->next;

            if (p->committed)
            {
                prev = p;
            }
            else
            {
                if (prev)
                    prev->next = next;
                else
                    self->impl.lists[i] = (HashBucket*)next;

                PAL_Free(p);
            }

            p = next;
        }
    }
}

#if 0

void StrSet_Dump(
    _In_ const StrSet* self)
{
    size_t i;

    for (i = 0; i < self->impl.numLists; i++)
    {
        const StrSetBucket* p = (const StrSetBucket*)self->impl.lists[i];

        for (; p; p = p->next)
        {
            PRINTF(MI_T("STRSET{%s}\n"), p->str);
        }
    }
}

#endif
