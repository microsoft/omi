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

#ifndef _base_hashtable_h
#define _base_hashtable_h

#include "config.h"
#include <common.h>

BEGIN_EXTERNC

typedef struct _HashBucket
{
    struct _HashBucket* next;
}
HashBucket;

typedef struct _HashTable
{
    /* Array of poitners to hash lists */
    HashBucket** lists;
    size_t numLists;

    /* User-defined hash function */
    size_t (*hash)(const HashBucket* bucket);

    /* User-defined euqal function (returns non-zeroif equal) */
    int (*equal)(const HashBucket* bucket, const HashBucket* bucket2);

    /* User-defined function to release a hash bucket */
    void (*release)(HashBucket* bucket);
}
HashTable;

int HashTable_Init(
    HashTable* self,
    size_t numLists,
    size_t (*hash)(const HashBucket* bucket),
    int (*equal)(const HashBucket* bucket1, const HashBucket* bucket2),
    void (*release)(HashBucket* bucket));

void HashTable_Destroy(
    HashTable* self);

HashBucket* HashTable_Find(
    HashTable* self,
    const HashBucket* keyBucket);

int HashTable_Insert(
    HashTable* self,
    HashBucket* bucket);

int HashTable_Remove(
    HashTable* self,
    const HashBucket* keyBucket);

END_EXTERNC

#endif /* _base_hashtable_h */
