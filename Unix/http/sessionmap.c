#include "sessionmap.h"
#include <pal/memory.h>
#include <pal/strings.h>
#include <common.h>

#define ENABLE_TRACING 1
#define FORCE_TRACING 0

#ifdef ENABLE_TRACING
# define TRACING_LEVEL 4
#include <base/result.h>
#include <base/logbase.h>
#include <base/log.h>
#define LOGE2 __LOGE
#define LOGW2 __LOGW
#define LOGD2 __LOGD
#else
# define LOGE2(a)
# define LOGW2(a)
# define LOGD2(a)
# define LOGX2(a)
#endif

typedef struct _SessionBucket
{
    struct _SessionBucket *next;// HashMap usage
    const char* sessionId;      // WS_MAN Session Id 
    size_t hash;                // Hash value for sessionId
    char* cookie;               // MS-WSMAN Cookie
                                // allocated on creation and update.
                                // owned by the bucket
} SessionBucket;

#define SESSIONID_HASH_SEED 1313038763

static size_t _SessionId_Hash(_In_z_ const char* sessionId)
{
    size_t hash = SESSIONID_HASH_SEED;
    if (sessionId)
    {
        const char*p = sessionId;
        while(*p)
        {
            // From strset.c
            hash ^= ((hash << 5) + *p + (hash >> 2));
            p++;
        }
    }
    return hash;
}

static size_t _SessionBucket_GetHash(_In_ const HashBucket *b)
{
    const SessionBucket *bucket = (const SessionBucket*) b;
    return bucket->hash;
}

static int _SessionBucket_Equal(_In_ const HashBucket* b1, _In_ const HashBucket* b2)
{
    const SessionBucket* bucket1 = (const SessionBucket*) b1;
    const SessionBucket* bucket2 = (const SessionBucket*) b2;
    return 
    (
        bucket1->hash == bucket2->hash
        &&
        strcmp(bucket1->sessionId, bucket2->sessionId) == 0
    );
}

static void _SessionBucket_Release(HashBucket *b)
{
    if (b)
    {
        SessionBucket* bucket = (SessionBucket*) b;
        if (bucket->cookie)
        {
            PAL_Free(bucket->cookie);           
        }
        PAL_Free(bucket);
    }
}

/*
    Allocates and inserts a new sessionid entry.
    Parameters:
        self - the SessionMap
        sessionId - the session id
        hash - the has value for the session id produced by _SessionId_Hash

    NOTE: The caller must aquire a WriteLock.
*/
static SessionBucket* _SessionBucket_New(SessionMap *self, _In_z_ const char* sessionId, size_t hash)
{
    // WriteLock expected by the caller.
    SessionBucket* bucket = NULL;
    if (sessionId) do // while (FALSE)
    {
        size_t keyLen = strlen(sessionId);
        size_t size = sizeof(SessionBucket) + keyLen + 1;
        bucket = PAL_Malloc(size);
        if (NULL == bucket)
        {
            LOGE2((ZT("_SessionBucket_New - failed to allocate bucket: %s"), sessionId));
            break;
        }

        memset(bucket, 0, size);
        char* clone = (char*) (((unsigned char*) bucket) + sizeof(SessionBucket));
        strcpy(clone, sessionId);
        bucket->sessionId = clone;
        bucket->hash = hash;
        bucket->cookie = NULL;
        bucket->next = NULL;

        if (HashMap_Insert (&self->map, (HashBucket*) bucket) != 0)
        {
            // Not expecting the bucket to already exist.
            _SessionBucket_Release((HashBucket*) bucket);
            bucket = NULL;
            LOGE2((ZT("_SessionBucket_New - sessionId already exists: %s"), sessionId));
            break;
        }
        LOGD2((ZT("SessionBucket_New - added new session id: %s"), sessionId));
    } while (0);

    return bucket;
}

static BOOL _SessionMap_IsValid(SessionMap* self)
{
    if (NULL == self)
    {
        return FALSE;
    }

    ReadWriteLock_AcquireWrite(&self->lock);

    int result = 0;
    if (SESSIONID_HASH_SEED != self->state)
    {
        const size_t numItems = 64;

        result = HashMap_Init(&self->map, 
            numItems, 
            _SessionBucket_GetHash, 
            _SessionBucket_Equal, 
            _SessionBucket_Release);

        if (0 == result)
        {
            LOGD2((ZT("_SessionMap_IsValid - SessionMap initialized.")));
            self->state = SESSIONID_HASH_SEED;
        }
        else
        {
            LOGE2((ZT("_SessionMap_IsValid - Could not initialize the HashMap.")));
        }
    }
    ReadWriteLock_ReleaseWrite(&self->lock);

    return (0 == result);
}

SessionBucket* _SessionMap_Find(_In_ SessionMap* self, _Out_ SessionBucket* keyBucket, _In_z_ const char* sessionId)
{
    // Read Lock expected.
    keyBucket->sessionId = sessionId;
    keyBucket->hash = _SessionId_Hash(sessionId);
    HashBucket* bucket = HashMap_Find(&self->map, (const HashBucket*) keyBucket);

    if (bucket)
    {
        return (SessionBucket*) bucket;
    }
    return NULL;
}

/*
        Public functions
*/

/*
    NOTE: Currently, there's no clear place to call this.
    The result is the HasMap will be reported as a leak for the 
    allocated hash array.

int SessionMap_Empty(_Out_ SessionMap *self)
{
    if (NULL == self || SESSIONID_HASH_SEED != self->state)
    {
        return -1;
    }
    ReadWriteLock_AcquireWrite(&self->lock);

    self->state = 0;

    HashMap_Destroy(&self->map);
    memset(&self->map, 0, sizeof(HashMap));

    ReadWriteLock_ReleaseWrite(&self->lock);

    return 0;
}
*/


int SessionMap_SetCookie(_In_ SessionMap* self, 
     _In_z_ const char* sessionId,
     _In_opt_z_ const char* sessionCookie)
{
    if (!_SessionMap_IsValid(self) || NULL == sessionId)
    {
        return -1;
    }

    SessionBucket keyBucket = {0};
    int result =0;

    ReadWriteLock_AcquireWrite(&self->lock);
    SessionBucket* item = _SessionMap_Find(self, &keyBucket, sessionId);

    do 
    {
        if (NULL == item)
        {
            if (NULL == sessionCookie)
            {
                // Nothing to do
                break;
            }
            item = _SessionBucket_New(self, sessionId, keyBucket.hash);
            if (NULL == item)
            {
                result = -1;
                break;
            }
        }
        else if (NULL == sessionCookie)
        {
            PAL_Free(item->cookie);
            item->cookie = NULL;
            LOGD2((ZT("SessionMap_SetCookie - Cleared cookie for session id %s"), sessionId));
            break;
        }

        size_t newLen = 0;
        const char* endCookie = Strchr(sessionCookie, ';');
        if (endCookie)
        {
            newLen = endCookie - sessionCookie + 1;
        }
        else
        {
            newLen = Strlen(sessionCookie);
        }

        if (NULL == item->cookie || Strncmp(sessionCookie, item->cookie, newLen) != 0)
        {
            PAL_Free(item->cookie);
            item->cookie = PAL_Malloc(newLen + 1);
            if (NULL == item->cookie)
            {
                result = -1;
                break;
            }
            Strlcpy(item->cookie, sessionCookie, newLen);
            item->cookie[newLen] = 0;
            LOGD2((ZT("SessionMap_SetCookie - Set new cookie for session id %s: %s"), sessionId, item->cookie));
        }
    } while(0);

    ReadWriteLock_ReleaseWrite(&self->lock);

    return result;
}

const char* SessionMap_GetCookie(_In_ SessionMap* self, _In_z_ const char* sessionId)
{
    const char* result = NULL;

    if (sessionId && _SessionMap_IsValid(self))
    {
        SessionBucket keyBucket = {0};
    
        ReadWriteLock_AcquireRead(&self->lock);

        const SessionBucket* item = _SessionMap_Find(self, &keyBucket, sessionId);
        if (NULL != item)
        {
            result = item->cookie;
        }

        ReadWriteLock_ReleaseRead(&self->lock);
    }
    return result;
}

int SessionMap_Remove(_In_ SessionMap* self, _In_z_ const char* sessionId)
{
    if (NULL == sessionId || !_SessionMap_IsValid(self))
    {
        return -1;
    }

    ReadWriteLock_AcquireWrite(&self->lock);

    SessionBucket keyBucket = {0};
    keyBucket.sessionId = sessionId;
    keyBucket.hash = _SessionId_Hash(sessionId);

    int result = HashMap_Remove(&self->map, (const HashBucket*) &keyBucket);
    if (result != 0)
    {
        LOGW2((ZT("SessionMap_Remove - Failed: %s"), sessionId));    
    }
    else
    {
        LOGD2((ZT("SessionMap_Remove - Removed: %s"), sessionId));    
    }

    ReadWriteLock_ReleaseWrite(&self->lock);
    return result;
}

