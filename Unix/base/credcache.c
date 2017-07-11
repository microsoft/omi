/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "credcache.h"
#include "log.h"
#include <pal/sleep.h>

#if defined (CONFIG_POSIX)
# include <openssl/evp.h>
# include <openssl/rand.h>

/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/
/* how long entry in cache is valid */
#define CRED_CACHE_TIME_TO_KEEP_USEC     (((MI_Uint64)120) * 1000000)
/* since pre-defined structures are used, user name is limited in size */
#define CRED_USER_NAME_MAX_LEN  32
/* Max hash length (sha512) */
#define CRED_HASH_MAX_LEN       64
/* Salt size */
#define CRED_SALT_SIZE          16
/* Max entries in cache (number of simultaneously identified users) */
#define CRED_ITEMS_MAX          4


typedef struct _CredItem
{
    char user[CRED_USER_NAME_MAX_LEN];
    unsigned char hash[CRED_HASH_MAX_LEN];
    MI_Uint64   timestamp;
} CredItem;

static unsigned char s_salt[CRED_SALT_SIZE];
static CredItem s_cache[CRED_ITEMS_MAX];
static int s_init;
static int s_initAttempted;
static const EVP_MD* s_md;
static MI_Uint64    s_expirationTime_us = CRED_CACHE_TIME_TO_KEEP_USEC;

static int _Init()
{
    /* Avoid mulitple attempts to init if it failed */
    if (s_initAttempted)
        return -1;

    s_initAttempted = 1;

    /* Initialize salt */
    if (0 == RAND_load_file("/dev/urandom", 1024))
    {
        trace_FailedLoadDevUrandom();
        return -1;
    }

    if (0 == RAND_bytes(s_salt, sizeof(s_salt)))
    {
        trace_FailedInitSalt();
        return -1;
    }

    /* Find digest */
    OpenSSL_add_all_digests();

    /* Find digest, starting with strongest */
    if (!(s_md = EVP_get_digestbyname("sha512")) &&
        !(s_md = EVP_get_digestbyname("sha384")) &&
        !(s_md = EVP_get_digestbyname("sha256")) &&
        !(s_md = EVP_get_digestbyname("sha224")) &&
        !(s_md = EVP_get_digestbyname("sha1")))
    {
        trace_NoDigestAvailable();
        return -1;
    }

    s_init = 1;
    return 0;
}

/* Calculates hash:
    uses 3 parts:
    - user name
    - pwd
    - salt
    this way hash values are unique per user, per startup sequence
    */
static void _Hash(
    const char* data1,
    int size1,
    const char* data2,
    int size2,
    unsigned char hash[CRED_HASH_MAX_LEN])
{
    // Interface change in SSL v1.1: Detect and use suitable code
#if OPENSSL_VERSION_NUMBER <= 0x100fffffL // SSL 1.0.x or lower?
    EVP_MD_CTX ctx;
    unsigned int hashSize = CRED_HASH_MAX_LEN;

    EVP_DigestInit(&ctx, s_md);
    EVP_DigestUpdate(&ctx, data1, size1);
    EVP_DigestUpdate(&ctx, data2, size2);
    EVP_DigestUpdate(&ctx, s_salt, sizeof(s_salt));
    EVP_DigestFinal(&ctx, hash, &hashSize);
#else
    EVP_MD_CTX *ctx;
    unsigned int hashSize = CRED_HASH_MAX_LEN;

    ctx = EVP_MD_CTX_new();
    EVP_DigestInit(ctx, s_md);
    EVP_DigestUpdate(ctx, data1, size1);
    EVP_DigestUpdate(ctx, data2, size2);
    EVP_DigestUpdate(ctx, s_salt, sizeof(s_salt));
    EVP_DigestFinal(ctx, hash, &hashSize);
    EVP_MD_CTX_free(ctx);
#endif
}

/* Find position to add/update user:
    if user is already in cache, it returns this position,
    otherwise if empty item available - retunrs it,
    otherwise retunrs oldest element */
static int _FindUserEmptyOldest(
    const char* user)
{
    int posEmpty = -1, posOldest = 0, pos;
    MI_Uint64 timestampOldest = s_cache[0].timestamp;

    for (pos = 0; pos < MI_COUNT(s_cache); pos++)
    {
        /* Did we find user? */
        if (strcmp(user,s_cache[pos].user) == 0)
            return pos;

        /* Is it empty? */
        if (0 == s_cache[pos].user[0])
        {
            posEmpty = pos;
        }
        else if (-1 == posEmpty)
        {
            /* Is it oldest with no epmty? */
            if (timestampOldest > s_cache[pos].timestamp)
            {
                timestampOldest = s_cache[pos].timestamp;
                posOldest = pos;
            }
        }
    }

    if (-1 != posEmpty)
        return posEmpty;

    return posOldest;
}

/* Find position with given user:
    Returns:
    user posiiton if found; -1 otherwise
*/
static int _Find(
    const char* user)
{
    int pos;

    for (pos = 0; pos < MI_COUNT(s_cache); pos++)
    {
        /* Did we find user? */
        if (strcmp(user,s_cache[pos].user) == 0)
            return pos;
    }

    return -1;
}

/* 
    Adds user name and password into cache
*/
void CredCache_PutUser(const char* user, const char* password)
{
    int pos;
    int userLen;

    if (!s_init && 0 != _Init())
    {
        return;
    }

    /* Check if user name is too long for cache */
    userLen = strlen(user);
    if (userLen >= CRED_USER_NAME_MAX_LEN)
        return;

    /* find position for user */
    pos = _FindUserEmptyOldest(user);

    /* timestamp */
    if (PAL_TRUE != PAL_Time(&s_cache[pos].timestamp))
        return;

    /* user name */
    strcpy(s_cache[pos].user, user);

    /* hash */
    _Hash(user, userLen, password, strlen(password), s_cache[pos].hash);
}

/* 
    Checks if user credentials matches the one in cache
    Returns:
    '0' if user account matches entry in cache
    '-1' if user is not in cache, if password does not match or
        record expired
*/
int CredCache_CheckUser(const char* user, const char* password)
{
    int pos;
    unsigned char hash[CRED_HASH_MAX_LEN];
    MI_Uint64 now;

    /* 'no' if not initialized */
    if (!s_init)
        return -1;

    /* Does user exisit in cache */
    if (-1 == (pos = _Find(user)))
        return -1;

    /* Is it expired? */
    if (PAL_TRUE != PAL_Time(&now))
        return -1;

    if (s_cache[pos].timestamp + s_expirationTime_us < now)
        return -1;

    /* Hash matches? */
    memset(hash, 0, sizeof(hash));
    _Hash(user, strlen(user), password, strlen(password), hash);

    assert(pos < MI_COUNT(s_cache));

    if (0 != memcmp(hash, s_cache[pos].hash, sizeof(hash)))
        return -1;

    /* Credentials are valid */
    return 0;
}

/* Unit-test support - updating expiration timeout */
void CredCache_SetExpirationTimeout(MI_Uint64 expirationTimeUS)
{
    if (expirationTimeUS)
        s_expirationTime_us = expirationTimeUS;
    else
        s_expirationTime_us = CRED_CACHE_TIME_TO_KEEP_USEC;
}

/* Unit-test support mostly - clear all cached items */
void CredCache_Clean()
{
    memset(s_cache, 0, sizeof(s_cache));
}

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
    size_t  size)
{

    /* Initialize if needed */
    if (!s_init && 0 != _Init())
    {
        return -1;
    }

    if (0 == RAND_bytes((unsigned char*)buf, size))
    {
        trace_FailedToProduceRandomData();
        return -1;
    }

    return 0;
}

#endif /* defined(CONFIG_POSIX) */
