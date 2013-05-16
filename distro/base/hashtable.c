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

#include "hashtable.h"

int HashTable_Init(
    HashTable* self,
    size_t numLists,
    size_t (*hash)(const HashBucket* bucket),
    int (*equal)(const HashBucket* bucket1, const HashBucket* bucket2),
    void (*release)(HashBucket* bucket))
{
    /* Allocate array of hash chains */

    self->lists = calloc(1, sizeof(HashBucket*) * numLists);

    if (!self->lists)
        return -1;

    /* Save the function arguments */

    self->numLists = numLists;
    self->hash = hash;
    self->equal = equal;
    self->release = release;

    return 0;
}

void HashTable_Destroy(
    HashTable* self)
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

    free(self->lists);
}

HashBucket* HashTable_Find(
    HashTable* self,
    const HashBucket* keyBucket)
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

int HashTable_Insert(
    HashTable* self,
    HashBucket* bucket)
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

int HashTable_Remove(
    HashTable* self,
    const HashBucket* keyBucket)
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
