/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_credcache_h
#define _omi_credcache_h

#include <common.h>
#include <pal/strings.h>

#if defined(CONFIG_POSIX)

BEGIN_EXTERNC

/* 
    Adds user name and password into cache
*/
void CredCache_PutUser(const char* user, const char* password);

/* 
    Checks if user credentials matches the one in cache
    Returns:
    '0' if user account matches entry in cache
    '-1' if user is not in cache, if password does not match or
        record expired
*/
int CredCache_CheckUser(const char* user, const char* password);

/* Unit-test support - updating expiration timeout */
void CredCache_SetExpirationTimeout(MI_Uint64 expirationTimeUS);
/* Unit-test support mostly - clear all cached items */
void CredCache_Clean();

/* security-related utility */
/*
    Generates crypto-suitable random data
    Parameters:
    buf - buffer for random data
    size - number of bytes to generate

    Returns:
    0 - success
    -1 - failed
*/
int CredCache_GenerateRandom(
    char* buf,
    size_t  size);

END_EXTERNC

#else
#endif

#endif /* _omi_credcache_h */
