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

#include <common.h>

#include <pal/format.h>
#include "user.h"
#include "log.h"

#if defined(CONFIG_POSIX)
# include "credcache.h"
# include <unistd.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# if defined(CONFIG_OS_DARWIN) && defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__  <= 1058
#  include <pam/pam_appl.h>
# else
#  include <security/pam_appl.h>
# endif
# include <signal.h>
# include <sys/wait.h>
# include <sys/socket.h>
# include <sys/un.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
#elif defined(CONFIG_OS_WINDOWS)
#endif

#include "paths.h"

#define GROUPNAME_SIZE 128

#if defined(CONFIG_POSIX)
static int  s_ignoreAuthCalls = 0;
#endif

#if defined(CONFIG_OS_WINDOWS)
/* 
    Validates user name and password;
    Returns:
    '0' if user account is valid and authorized to use CIM server
    '-1' otherwise
*/
int AuthenticateUser(const char* user, const char* password)
{
    MI_UNUSED(user);
    MI_UNUSED(password);
    return 0;
}

/* 
    Validates user's account for correct account name, expiration etc.
    Returns:
    '0' if user account is valid and authorized to use CIM server
    '-1' otherwise
*/
int ValidateUser(const char* user)
{
    MI_UNUSED(user);
    return 0;
}

int LookupUser(const char* user, uid_t* uid, gid_t* gid)
{
    MI_UNUSED(user);
    *uid = -1;
    *gid = -1;
    return 0;
}

int GetUserGidByUid(uid_t uid, gid_t* gid)
{
    MI_UNUSED(uid);
    *gid = -1;
    return 0;
}


int GetUIDByConnection(int fd, uid_t* uid, gid_t* gid)
{
    MI_UNUSED(fd);
    *uid = -1;
    *gid = -1;
    return -1;
}

/*
    Creates file with random data owned by user and RO by user only
    Parameters:
    uid - user ID
    size - number of bytes to write
    path - [out] - resulting file name

    Returns:
    0 if operation was successful; -1 otherwise
*/
_Use_decl_annotations_
int CreateAuthFile(
    uid_t uid, 
    char* content, 
    size_t size, 
    char path[PAL_MAX_PATH_SIZE])
{
    MI_UNUSED(uid);
    MI_UNUSED(size);
    MI_UNUSED(path);
    MI_UNUSED(content);

    return -1;
}

#elif defined(CONFIG_POSIX)

static int GetGroupName(
    gid_t gid,
    char name[GROUPNAME_SIZE]);

static int _authCallback(
    int numMessages,
#if defined(CONFIG_OS_LINUX) || defined(CONFIG_OS_DARWIN) || defined(CONFIG_OS_BSD)
    const struct pam_message** messages,
#else
    struct pam_message** messages,
#endif
    struct pam_response** response,
    void* applicationData)
{
    const char* password = (const char*)applicationData;
    int i;

    /* If zero (or megative) messages, return now */

    if (numMessages <= 0)
    {
        return PAM_CONV_ERR;
    }

    /* Allocate the responses */

    *response = (struct pam_response*)SystemCalloc(
        numMessages, 
        sizeof(struct pam_response));

    if (!*response)
    {
        return PAM_BUF_ERR;
    }

    /* Copy the password to the response messages */

    for (i = 0; i < numMessages; i++)
    {
        if (PAM_PROMPT_ECHO_OFF == messages[i]->msg_style)
        {
            response[i]->resp = (char*)SystemMalloc(PAM_MAX_MSG_SIZE);
            Strlcpy(response[i]->resp, password, PAM_MAX_MSG_SIZE);
            response[i]->resp_retcode = 0;
        }
        else
        {
            return PAM_CONV_ERR;
        }
    }

    return PAM_SUCCESS;
}

static int _PamCheckUser(
    const char* user, 
    const char* password)
{
    struct pam_conv conv;
    pam_handle_t* t = 0;

    memset(&conv, 0, sizeof(conv));

    conv.conv = _authCallback;
    conv.appdata_ptr = (void*)password;

    if (PAM_SUCCESS != pam_start("omi", user, &conv, &t))
        return -1;

    if (PAM_SUCCESS != pam_authenticate(t, 0))
    {
        pam_end(t,0);
        return -1;
    }

    if (PAM_SUCCESS != pam_acct_mgmt(t, 0))
    {
        pam_end(t,0);
        return -1;
    }

    pam_end(t, 0);

    return 0;
}

static int _CreateChildProcess(
    int* fd,
    pid_t* child,
    const char* user, 
    const char* password)
{
    int s[2];
    int fdLimit;

    /* create communication pipe */
    if(0 != socketpair(AF_UNIX, SOCK_STREAM, 0, s))
    {
        trace_SocketPair_Failed();
        return -1;
    }

    *child = fork();

    if (*child < 0)
    {
        close(s[0]);
        close(s[1]);
        return -1;  /* Failed */
    }

    if (*child > 0)
    {
        close(s[1]);
        *fd = s[0];

        return 0;   /* Started */
    }

    /* We are in child process here */

    /* Close all open file descriptors except provided socket
     (Some systems have UNLIMITED of 2^64; limit to something reasonable) */

    fdLimit = getdtablesize();
    if (fdLimit > 2500 || fdLimit < 0)
    {
        fdLimit = 2500;
    }

    /* ATTN: close first 3 also! Left for debugging only */
    {
        int i;
        for (i = 3; i < fdLimit; ++i)
        {
            if (i != s[1])
                close(i);
        }
    }

    /* perform operation in quesiton */
    {
        int r = _PamCheckUser(user, password);

        write(s[1], &r, sizeof(r));
        close(s[1]);
    }

    _exit(0);
}

/*
    Tests whether last error is EINTR
*/
MI_INLINE int _TestEINTR()
{
#if defined(CONFIG_OS_WINDOWS)
    return 0;
#else
    return errno == EINTR;
#endif
}

/* 
    Reads data from file, retry if was interuptted
    Returns:
    'size of the data' readed from the file if success
    '-1' otherwise
*/
int ReadFile(int fd, void* data, size_t size)
{
    int r;
    while ((r = read(fd, data, size)) == -1)
    {
        if (!_TestEINTR()) break;
    }
    return r;
}

/* 
    Validates user name and password;
    Returns:
    '0' if user account is valid and authorized to use CIM server
    '-1' otherwise
*/
int AuthenticateUser(const char* user, const char* password)
{
    int fd = 0;
    pid_t child = 0;
    int r = -1;

    if (s_ignoreAuthCalls)
        return 0;

    /* Verify if user is in cache already */
    if (0 == CredCache_CheckUser(user, password))
        return 0;

    if (0 != _CreateChildProcess(&fd, &child, user, password))
    {
        return -1;
    }

    if (sizeof(int) != ReadFile(fd, &r, sizeof(int)))
    {
        trace_UserAuth_FailedToRead( errno );
        r = -1;
        goto done;
    }

done:
    close(fd);
    /* SIGCHILD HANDLER will take care of pid waiting */
#if 0
    {
        int loc = 0;
        pid_t p = waitpid(child, &loc, 0 /*WNOHANG*/);

        if (p != child)
            LOGW_CHAR(("waitpid returned %d, loc %d",(int)p, loc));
    }
#endif

    /* Add user to cache if auth was ok */
    if (0 == r)
        CredCache_PutUser(user, password);

    return r;
}

/* 
    Validates user's account for correct account name, expiration etc.
    Returns:
    '0' if user account is valid and authorized to use CIM server
    '-1' otherwise
*/
int ValidateUser(const char* user)
{
    if (s_ignoreAuthCalls)
        return 0;

    MI_UNUSED(user);
    return 0;
}

/*
    Disables authentication calls so 'AuthUser' always retunrs 'ok';
    used for unit-test only
*/
void    IgnoreAuthCalls(int flag)
{
    s_ignoreAuthCalls = flag;
}

/*
    Get if authentication calls was ignored or not
    Return value:
    1 - ignored; 0 - not
*/
int IsAuthCallsIgnored()
{
    return s_ignoreAuthCalls;
}

/*
    Looks for user's account and retrieves uid/gid.
    Parameters:
    user - user name
    uid [out] user ID
    gid [out] group ID

    Returns:
    0 if operation was successful; -1 otherwise
*/
int LookupUser(const char* user, uid_t* uid, gid_t* gid)
{
    char buf[1024];
    struct passwd pwd;
    struct passwd* ppwd = 0;

    if (s_ignoreAuthCalls)
        return 0;

    if (0 != getpwnam_r(user, &pwd, buf, sizeof(buf), &ppwd) ||
        !ppwd)
    {
        trace_getpwnamr_Failed(errno);
        return -1;
    }

    *uid = pwd.pw_uid;
    *gid = pwd.pw_gid;
    return 0;
}

int GetUserGidByUid(uid_t uid, gid_t* gid)
{
    /* user name */
    char name[USERNAME_SIZE];

    if (0 != GetUserName(uid, name))
        return -1;

    return LookupUser(name, &uid, gid);
}

/*
    Changes user/group IDs of current process.
    Parameters:
    uid - user ID
    gid - group ID

    Returns:
    0 if operation was successful; -1 otherwise
*/
int SetUser(uid_t uid, gid_t gid)
{
    if (s_ignoreAuthCalls)
        return 0;

    if (setgid(gid) != 0)
    {
        trace_setgid_Failed(errno);
        return -1;
    }

    /*
     * Limit the groups that this user is in to the ones in /etc/groups.
     * Without this it includes the root group if root called Setuser()
     */
    {
        struct passwd pwbuf;
        char buf[1024];
        struct passwd* pw;

        if (getpwuid_r(uid, &pwbuf, buf, sizeof(buf), &pw) != 0 || !pw)
        {
            trace_getpwuidr_Failed(errno);
            return -1;
        }

        if (initgroups(pw->pw_name, gid) != 0)
        {
            trace_initgroups_Failed(errno);
            return -1;
        }
    }

    if (setuid(uid) != 0)
    {
        trace_setuid_Failed(errno);
        return -1;
    }

    return 0;
}

/* 
    Verifies if current process is running as root
    Returns:
    0 - current process is root
    -1 - current process is not root.
*/
int IsRoot()
{
    uid_t uid = geteuid();
    
    return uid == 0 ? 0 : -1;
}

int GetUIDByConnection(int fd, uid_t* uid, gid_t* gid)
{
#if defined(CONFIG_OS_LINUX) || defined(CONFIG_OS_BSD)
    struct ucred credentials;
    socklen_t ucred_size = (socklen_t)sizeof(credentials);

    /*fill in the user data structure */
    if(getsockopt(fd, SOL_SOCKET, SO_PEERCRED, &credentials, &ucred_size))
        return -1;

    /* the process ID of the process on the other side of the socket */
    // credentials.pid;

    /* the effective UID of the process on the other side of the socket  */
    *uid = credentials.uid;

    /* the effective primary GID of the process on the other side of the socket */
    *gid = credentials.gid;

    return 0;
#else

    MI_UNUSED(fd);
    *uid = -1;
    *gid = -1;
    return -1;
#endif
}

/*
    Creates file with random data owned by user and RO by user only
    Parameters:
    uid - user ID
    size - number of bytes to write
    path - [out] - resulting file name

    Returns:
    0 if operation was successful; -1 otherwise
*/
int CreateAuthFile(uid_t uid, char* content, size_t size, char path[PAL_MAX_PATH_SIZE])
{
    static MI_Uint32 counter;

    counter ++;

    /* Format file name as <dir>/<user>.<counter> */
    {
        /* user name */
        char name[USERNAME_SIZE];
        char numBuf[12];
        size_t dummy;

        if (0 != GetUserName(uid, name))
            return -1;

        if (Strlcpy(path, OMI_GetPath(ID_AUTHDIR), PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
            return -1;

        if (Strlcat(path, "/", PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
            return -1;

        if (Strlcat(path, name, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
            return -1;

        if (Strlcat(path, ".", PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
            return -1;

        if (Strlcat(path, Uint32ToStr(numBuf, counter, &dummy), PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
            return -1;
    }

    /* Generate random */
    if (0 != CredCache_GenerateRandom(content, size))
        return -1;

    /* write file */
    unlink(path);

    {
        int fd;

        /* Create auth file */
        fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR);
        if (fd == -1)
        {
            trace_CreateAuthFile_Failed(scs(path));
            return -1;
        }
        if (write(fd, content, size) != (int)size)
        {
            close(fd);
            unlink(path);
            return -1;
        }

        if (0 != fchown(fd, uid, -1))
        {
            trace_ChownAuthFile_Failed(scs(path));
            close(fd);
            unlink(path);
            return -1;
        }

        close(fd);
    }

    return 0;
}

/* 
    Gets username by uid
*/
int GetUserName(
    uid_t uid, 
    char name[USERNAME_SIZE])
{
    struct passwd pwbuf;
    char buf[1024];
    struct passwd* pw;

    if (getpwuid_r(uid, &pwbuf, buf, sizeof(buf), &pw) != 0)
        return -1;

    if (!pw)
        return -1;

    if (Strlcpy(name, pw->pw_name, USERNAME_SIZE) >= USERNAME_SIZE)
        return -1;

    return 0;
}

static int GetGroupName(
    gid_t gid,
    char name[GROUPNAME_SIZE])
{
    struct group grbuf;
    char buf[1024];
    struct group* gr;

    if (getgrgid_r(gid, &grbuf, buf, sizeof(buf), &gr) != 0)
        return -1;

    if (!gr)
        return -1;

    if (Strlcpy(name, gr->gr_name, GROUPNAME_SIZE) >= GROUPNAME_SIZE)
        return -1;

    return 0;
}

int FormatLogFileName(
    uid_t uid, 
    gid_t gid, 
    char path[PAL_MAX_PATH_SIZE])
{
    char user[USERNAME_SIZE];
    char group[GROUPNAME_SIZE];

    if (Strlcpy(path, OMI_GetPath(ID_LOGDIR), PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
        return -1;

    Strlcat(path, "/omiagent.", PAL_MAX_PATH_SIZE);

    /* Append user name */
    if (GetUserName(getuid(), user) == 0)
    {
        Strlcat(path, user, PAL_MAX_PATH_SIZE);
    }
    else
    {
        char buf[11];
        sprintf(buf, "%u", getuid());
        Strlcat(path, buf, PAL_MAX_PATH_SIZE);
    }

    /* Append group name */
    if (GetGroupName(getgid(), group) == 0)
    {
        Strlcat(path, ".", PAL_MAX_PATH_SIZE);
        Strlcat(path, group, PAL_MAX_PATH_SIZE);
    }
    else
    {
        char buf[11];
        sprintf(buf, "%u", getgid());
        Strlcat(path, ".", PAL_MAX_PATH_SIZE);
        Strlcat(path, buf, PAL_MAX_PATH_SIZE);
    }

    Strlcat(path, ".log", PAL_MAX_PATH_SIZE);

    return 0;
}

#endif

