/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _base_hashmap_h
#define _base_hashmap_h

#include "palcommon.h"

PAL_BEGIN_EXTERNC

typedef struct _HashBucket
{
    struct _HashBucket* next;
} HashBucket;

typedef size_t (*HashMapHashProc)(const HashBucket* bucket);
typedef int (*HashMapEqualProc)(_In_ const HashBucket* bucket1, _In_ const HashBucket* bucket2);
typedef void (*HashMapReleaseProc)(_In_ HashBucket* bucket1);

typedef struct _HashMap
{
    /* Array of poitners to hash lists */
    HashBucket** lists;
    size_t numLists;
    PAL_Boolean listsOwnedByHashMap;

    /* User-defined hash function */
    HashMapHashProc hash;

    /* User-defined euqal function (returns non-zeroif equal) */
    HashMapEqualProc equal;

    /* User-defined function to release a hash bucket */
    HashMapReleaseProc release;
}
HashMap;

typedef struct _HashMapIterator
{
    size_t      index;
    HashBucket *current;
}
HashMapIterator;

/* returns:
   -  0 : success
   - <0 : out of memory
*/
int HashMap_Init(
    _Out_ HashMap* self,
    size_t numLists,
    _In_ HashMapHashProc hash,
    _In_ HashMapEqualProc equal,
    _In_ HashMapReleaseProc release);

/* to be used with preallocated bucket list
   (avoiding an extra allocation/deallocation can help boost performance in some scenarios) */
void HashMap_Construct(
    _Out_ HashMap* self,
    size_t numLists,
    _Out_writes_(numLists) void** buckets,
    _In_ HashMapHashProc hash,
    _In_ HashMapEqualProc equal,
    _In_ HashMapReleaseProc release);

void HashMap_Destroy(
    _In_ _Post_invalid_ HashMap* self);

/* returns:
   -  non-null : found
   -  null     : key not present
*/
_Ret_maybenull_ HashBucket* HashMap_Find(
    _In_ HashMap* self,
    _In_ const HashBucket* keyBucket);

/* returns:
   -  0 : inserted the new item
   -  1 : the item is already present (and HashMap was not modified)

   (there are no failure paths / no other return value is possible)
*/
int HashMap_Insert(
    _In_ HashMap* self,
    _Pre_notnull_ HashBucket* bucket);

/* returns:
   -  0 : success
   - -1 : key not found - hashmap remains unchanged.
*/
int HashMap_Remove(
    _In_ HashMap* self,
    _In_ const HashBucket* keyBucket);

void HashMap_BeginIteration(
    _In_ HashMap* self,
    _Out_ HashMapIterator* iterator);

/* iterates through hash table entries.
   - iterator must be zero initialized
*/
_Ret_maybenull_
const HashBucket* HashMap_Iterate(
    _In_ HashMap* self,
    _Inout_ HashMapIterator* iterator);

/*
   Returns one element from the hash table. May be invoked
   multiple times (e.g. if you remove the element), returning
   null when empty.

   *iter should be zero initialized before first call
*/
_Ret_maybenull_
const HashBucket* HashMap_Top(
    _In_ HashMap* self,
    _Inout_ size_t *iter);

PAL_INLINE size_t HashMap_HashProc_AnsiString(_In_ _Null_terminated_ const char *source)
{
    /* fnv1-a hash, lowercase */
    size_t h = 2166136261u;

    for( ; *source; source++)
    {
        PAL_Char c = *source;
        h ^= c;
        h *= 16777619;
    }
    return h;
}

PAL_INLINE size_t HashMap_HashProc_PalStringCaseInsensitive(_In_ _Null_terminated_ const PAL_Char *source)
{
    /* fnv1-a hash, lowercase */
    size_t h = 2166136261u;

    for( ; *source; source++)
    {
        PAL_Char c = *source;
        h ^= PAL_tolower(c);
        h *= 16777619;
    }
    return h;
}

PAL_END_EXTERNC

#endif /* _base_hashmap_h */
