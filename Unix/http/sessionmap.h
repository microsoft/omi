/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/
#ifndef _omi_sessionmap_h
#define _omi_sessionmap_h

#include <pal/lock.h>
#include <pal/hashmap.h>

typedef struct _SessionMap
{
    size_t state;       // Set to SESSIONID_HASH_SEED when valid.
    ReadWriteLock lock; // serialize access to the map
    HashMap map;
} SessionMap;

#define SESSIONMAP_INIT {0, READWRITELOCK_INITIALIZER, {0}}

/*
    Sets the session cookie for a session id.

    This function adds the session id to the map if it doesn't already exist.
    To clear the session cookie, pass a NULL pointer. Clearning 
    the session cookie does not remove the session from the SessionMap.

    Returns:
        0  if hte session cookie was updated.
        -1 if the SessionMap is NULL or invalid.
*/
int SessionMap_SetCookie(_In_ SessionMap* self, 
     _In_z_ const char* sessionId,
     _In_opt_z_ const char* sessionCookie);

/*
    Gets the session cookie for a session id.

    Returns: 
        The string cookie on success
        A NULL if the session id is not found or,
            the session does not have an associated cookie or,
            the SessionMap is NULL or invalid.
*/
const char* SessionMap_GetCookie(_In_ SessionMap* self, 
    _In_z_ const char* sessionId);

/*
    Removes a session id from the SessionMap.

    Returns: 
        0 if the session id was removed or not found.
        -1 if the SessionMap is NULL or invalid.

    If the session id was not found, the SessionMap is unchanged.
*/
int SessionMap_Remove(_In_ SessionMap* self, 
    _In_z_ const char* sessionId);

#endif /* _omi_sessionmap_h */
