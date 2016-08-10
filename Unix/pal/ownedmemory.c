/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <pal/ownedmemory.h>
#include <pal/hashmap.h>
#include <pal/lock.h>

static Lock s_ownedMemoryLock = LOCK_INITIALIZER;
static HashMap _ownedMemoryHashmap;
static PAL_Boolean _ownedMemoryInitialized = PAL_FALSE;

/*
**==============================================================================
**
** OwnedMemory hash implementation
**
**==============================================================================
*/

typedef struct _OwnedMemoryBucket /* derives from HashBucket */
{
    struct _OwnedMemoryBucket* next;
    void *key;
}
OwnedMemoryBucket;

static size_t _OwnedMemoryHash(
    const HashBucket* bucket_)
{
    OwnedMemoryBucket* bucket = (OwnedMemoryBucket*)bucket_;	
    void *key = bucket->key;
    size_t h = (size_t)key >> 4;
    return h;
}

static int _OwnedMemoryEqual(
    const HashBucket* bucket1_,
    const HashBucket* bucket2_)
{
    OwnedMemoryBucket* bucket1 = (OwnedMemoryBucket*)bucket1_;
    OwnedMemoryBucket* bucket2 = (OwnedMemoryBucket*)bucket2_;
    return (bucket1->key == bucket2->key);
}

static void _OwnedMemoryRelease(
    HashBucket* bucket_)
{
    OwnedMemoryBucket* bucket = (OwnedMemoryBucket*)bucket_;

    PAL_Free(bucket->key);
    PAL_Free(bucket);
}

/*
* Called by atexit handler
*/
static void ATEXIT_API _OwnedMemory_DeInitialize(void)
{
    Lock_Acquire(&s_ownedMemoryLock);
    
    if(_ownedMemoryInitialized)
    {
        HashMap_Destroy(&_ownedMemoryHashmap);
    }
    
    Lock_Release(&s_ownedMemoryLock);
}

/*
* Assumes that it is called under lock
*/
PAL_Boolean _OwnedMemory_Initialize()
{
    int result = 0;

    if(!_ownedMemoryInitialized)
    {
        result = HashMap_Init(
            &_ownedMemoryHashmap, 
            64, 
            _OwnedMemoryHash, 
            _OwnedMemoryEqual, 
            _OwnedMemoryRelease);

        if(result == 0)
        {
            PAL_Atexit(_OwnedMemory_DeInitialize);

            _ownedMemoryInitialized = PAL_TRUE;
        }
    }

    return (result == 0);
}

/*
* Initializes HashMap if not done so yet
* allocates a hash bucket, allocates new memory; stores the bucket in hashmap
* returns the new memory ptr
*/
void *OwnedMemory_Alloc(size_t length)
{
    OwnedMemoryBucket* bucket = NULL;
    void *newMemory = NULL;

    Lock_Acquire(&s_ownedMemoryLock);
    if(!_OwnedMemory_Initialize())
        goto end;

    bucket = (OwnedMemoryBucket*)PAL_Calloc(1, sizeof(OwnedMemoryBucket));
    if(!bucket)
        goto end;

    newMemory = PAL_Calloc(1, length);

    if(!newMemory)
    {
        PAL_Free(bucket);
        goto end;
    }
    bucket->key = newMemory;

    if(HashMap_Insert(&_ownedMemoryHashmap, (HashBucket *) bucket) != 0)
    {
        /* this will never happen since same memory location will not be returned 
        on two allocations unless first one is freed by the user explicitly 
        giving the error to the user by returning NULL in this case */
        PAL_Free(bucket);
        PAL_Free(newMemory);
        newMemory = NULL;
    }

end:
    Lock_Release(&s_ownedMemoryLock);

    return newMemory;
}

/*
* Attempts to remove the ptr from the hash map and free it; 
* returns whether it succeeded in doing so or not
*/
int OwnedMemory_Free(void *ptr)
{
    int result = 0;
    OwnedMemoryBucket bucket;
    bucket.key = ptr;

    Lock_Acquire(&s_ownedMemoryLock);

    result = HashMap_Remove(&_ownedMemoryHashmap, (const HashBucket *) &bucket);

    Lock_Release(&s_ownedMemoryLock);

    return result;
}
