/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_user_h
#define _omi_user_h

#include <common.h>
#include <pal/strings.h>
#if defined(CONFIG_POSIX)
#include <pwd.h>
#else
typedef int uid_t;
typedef int gid_t;

MI_INLINE uid_t geteuid() {return 0;}
MI_INLINE gid_t getegid() {return 0;}

#endif

BEGIN_EXTERNC

/* 
    Validates user name and password;
    Returns:
    '0' if user account is valid and authorized to use CIM server
    '-1' otherwise
*/
int AuthenticateUser(const char* user, const char* password);

/* 
    Validates user's account for correct account name, expiration etc.
    Returns:
    '0' if user account is valid and authorized to use CIM server
    '-1' otherwise
*/
int ValidateUser(const char* user);

/*
    Looks for user's account and retrieves uid/gid.
    Parameters:
    user - user name
    uid [out] user ID
    gid [out] group ID

    Returns:
    0 if operation was successful; -1 otherwise
*/
int LookupUser(const char* user, uid_t* uid, gid_t* gid);

/*
    retrieves gid for user specified by uid.
    Parameters:
    uid user ID
    gid [out] group ID

    Returns:
    0 if operation was successful; -1 otherwise
*/
int GetUserGidByUid(uid_t uid, gid_t* gid);

/*
    Retrieves uid/gid from fd if supported by platform
    Parameters:
    fd - socket discritptor (must be connected domain socket fd)
    uid [out] user ID
    gid [out] group ID

    Returns:
    0 if operation was successful; -1 otherwise

*/
int GetUIDByConnection(int fd, uid_t* uid, gid_t* gid);

/*
    Creates file with random data owned by user and RO by user only
    Parameters:
    uid - user ID
    content - [out] pointer to a buffer for random data
    size - number of bytes to write
    path - [out] - resulting file name

    Returns:
    0 if operation was successful; -1 otherwise
*/
int CreateAuthFile(uid_t uid, _In_reads_(size) char* content, size_t size, _Pre_writable_size_(PAL_MAX_PATH_SIZE) char path[PAL_MAX_PATH_SIZE]);

#if defined(CONFIG_POSIX)
/*
    Formats log file name as
    <log-dir>/omiagent.<user>.<group>.log
    Parameters:
    uid user ID
    gid group ID
    path [out] formatted file name

    Returns:
    0 - if success; -1 otherwise
*/
int FormatLogFileName(uid_t uid, gid_t gid, char path[PAL_MAX_PATH_SIZE]);

/*
    Disables authentication calls so 'AuthUser' always retunrs 'ok';
    used for unit-test only
    Parameters:
    flag - '1' to ignore atuh; 0 to perform auth calls normally
*/
void    IgnoreAuthCalls(int flag);

/*
    Get if authentication calls was ignored or not
    Return value:
    1 - ignored; 0 - not
*/
int IsAuthCallsIgnored();

/*
    Changes user/group IDs of current process.
    Parameters:
    uid - user ID
    gid - group ID

    Returns:
    0 if operation was successful; -1 otherwise
*/
int SetUser(uid_t uid, gid_t gid);

/* 
    Verifies if current process is running as root
    Returns:
    0 - current process is root
    -1 - current process is not root.
*/
int IsRoot();

const char* GetHomeDir();

/* 
    Gets username by uid
*/
#define USERNAME_SIZE 128
int GetUserName(
    uid_t uid, 
    char name[USERNAME_SIZE]);

MI_Boolean ValidateGssCredentials(const char *credFilePath, const char *krb5KeyTablePath, const char *krb5CredCacheSpec, uid_t uid, gid_t gid );
void DestroyKrb5CredCache(const char *krb5CredCacheSpec);
#endif

int PamCheckUser(
    const char* user, 
    const char* password);

int ReadFile(int fd, void *data, size_t size);

END_EXTERNC

#endif /* _omi_user_h */
