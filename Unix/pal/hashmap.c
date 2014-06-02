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

#include "hashmap.h"

int HashMap_Init(
    _Out_ HashMap* self,
    size_t numLists,
    _In_ HashMapHashProc hash,
    _In_ HashMapEqualProc equal,
    _In_ HashMapReleaseProc release)
{
    /* Allocate array of hash chains */

    self->lists = SystemCalloc(numLists, sizeof(HashBucket*));
    if (!self->lists)
        return -1;
    self->listsOwnedByHashMap = PAL_TRUE;

    /* Save the function arguments */

    self->numLists = numLists;
    self->hash = hash;
    self->equal = equal;
    self->release = release;

    return 0;
}

void HashMap_Construct(
    _Out_ HashMap* self,
    size_t numLists,
    _Out_writes_(numLists) void** buckets,
    _In_ HashMapHashProc hash,
    _In_ HashMapEqualProc equal,
    _In_ HashMapReleaseProc release)
{
    /* Remember pointer to the array of hash chains */

    self->lists = (HashBucket**) buckets;
    memset(self->lists, 0, sizeof(void*) * numLists);
    self->listsOwnedByHashMap = PAL_FALSE;

    /* Save the function arguments */

    self->numLists = numLists;
    self->hash = hash;
    self->equal = equal;
    self->release = release;
}

void HashMap_Destroy(
    _In_ _Post_invalid_ HashMap* self)
{
    size_t i;

    for (i = 0; i < self->numLists; i++)
    {
        HashBucket* p;

        for (p = self->lists[i]; p; )
        {
            HashBucket* next = p->next;
            self->release(p);
            p = next;
        }
    }

    if (self->listsOwnedByHashMap)
    {
        SystemFree(self->lists);
    }
}

_Ret_maybenull_ HashBucket* HashMap_Find(
    _In_ HashMap* self,
    _In_ const HashBucket* keyBucket)
{
    size_t index;
    HashBucket* p;

    /* Hash the key */

    index = self->hash(keyBucket) % self->numLists;

    /* Search for matching bucket */

    for (p = self->lists[index]; p; p = p->next)
    {
        if (self->equal(p, keyBucket))
        {
            return p;
        }
    }

    /* Not found */
    return 0;
}

int HashMap_Insert(
    _In_ HashMap* self,
    _Pre_notnull_ HashBucket* bucket)
{
    size_t index;
    HashBucket* p;

    /* Hash the key */

    index = self->hash(bucket) % self->numLists;

    /* Search for matching bucket */

    for (p = self->lists[index]; p; p = p->next)
    {
        if (self->equal(p, bucket))
        {
            /* Already exists */
            return 1;
        }
    }

    /* Insert at front of hash list */

    bucket->next = self->lists[index];
    self->lists[index] = bucket;

    return 0;
}

int HashMap_Remove(
    _In_ HashMap* self,
    _In_ const HashBucket* keyBucket)
{
    size_t index;
    HashBucket* p;

    /* Hash the key */

    index = self->hash(keyBucket) % self->numLists;

    /* Search for matching bucket */
    {
        HashBucket* prev = 0;

        for (p = self->lists[index]; p; p = p->next)
        {
            if (self->equal(p, keyBucket))
            {
                if (prev)
                    prev->next = p->next;
                else
                    self->lists[index] = p->next;

                self->release(p);
                return 0;
            }

            prev = p;
        }
    }

    /* Not found */
    return -1;
}

void HashMap_BeginIteration(
    _In_ HashMap* self,
    _Out_ HashMapIterator* iterator)
{
    if (self->numLists > 0) 
    {
        iterator->index = 0;
        iterator->current = self->lists[0];
    } 
    else 
    {
        iterator->index = 0;
        iterator->current = NULL;
    }
}

_Ret_maybenull_ 
const HashBucket* HashMap_Iterate(
    _In_ HashMap* self,
    _Inout_ HashMapIterator* iterator)
{
    const HashBucket *result;

    if (iterator->index >= self->numLists)
        return NULL;

    while (!iterator->current) 
    {
        size_t index = ++iterator->index;

        if (index >= self->numLists)
            return NULL;

        iterator->current = self->lists[index];
    }

    result = iterator->current;
    iterator->current = result->next;

    return result;
}

_Ret_maybenull_ 
const HashBucket* HashMap_Top(
    _In_ HashMap* self,
    _Inout_ size_t *iter)
{
    for (; *iter < self->numLists; ++*iter)
    {
        HashBucket *bucket = self->lists[*iter];
        if (bucket)
        {
            return bucket;
        }
    }
    return NULL;
}

