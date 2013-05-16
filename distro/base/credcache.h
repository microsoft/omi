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

#ifndef _omi_credcache_h
#define _omi_credcache_h

#include <common.h>
#include "strings.h"
#if defined(CONFIG_POSIX)
#else
#endif

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
    buf - bufer for random data
    size - number of bytes to generate

    Returns:
    0 - success
    -1 - failed
*/
int CredCache_GenerateRandom(
    char* buf,
    size_t  size);

END_EXTERNC

#endif /* _omi_credcache_h */
