/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
# include <string.h>
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
#endif

#include "paths.h"

#define GROUPNAME_SIZE 128

#if defined(CONFIG_POSIX)
static int  s_ignoreAuthCalls = 0;
static PermissionGroups *s_allowedList = NULL;
static PermissionGroups *s_deniedList = NULL;

/* retrieve the home directory of the real user
 *  * caller must free returned pointer
 *   */

const char* GetHomeDir()
{
    char* home = NULL;
    struct passwd *pwd = NULL;

    errno = 0;
    /* getuid() is always successful */
    pwd = getpwuid(getuid());
    if (pwd == NULL)
    {
        return NULL;
    }

    /* copy pw_dir since we do not own pwd */
    home = PAL_Strdup(pwd->pw_dir);

    return (const char*)home;
}


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

int PamCheckUser(
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
        int close_ret = pam_close_session(t,PAM_SILENT);
        pam_end(t,close_ret);
        return -1;
    }

    if (PAM_SUCCESS != pam_acct_mgmt(t, 0))
    {
        int close_ret = pam_close_session(t,PAM_SILENT);
        pam_end(t,close_ret);
        return -1;
    }

    if (PAM_SUCCESS != pam_setcred(t, PAM_ESTABLISH_CRED))
    {
        int close_ret = pam_close_session(t,PAM_SILENT);
        pam_end(t,close_ret);
        return -1;
    }

    int close_ret = pam_close_session(t,PAM_SILENT);
    pam_end(t,close_ret);

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
    int exitCode = 0;

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
        int r = PamCheckUser(user, password);

        exitCode = write(s[1], &r, sizeof(r));
        if (exitCode != -1)
            exitCode = 0;
        close(s[1]);
    }

    _exit(exitCode);
}

/*
    Tests whether last error is EINTR
*/
MI_INLINE int _TestEINTR()
{
    return errno == EINTR;
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

    int r = getpwnam_r(user, &pwd, buf, sizeof(buf), &ppwd);
    if (NULL == ppwd || r != 0)
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

int GetGroupId(
    const char *groupName,
    gid_t *gid)
{
    struct group grbuf;
    char buf[1024];
    struct group* gr;

    if (getgrnam_r(groupName, &grbuf, buf, sizeof(buf), &gr) != 0)
        return -1;

    if (!gr)
        return -1;

    *gid = gr->gr_gid;
    
    return 0;
}

int FormatLogFileName(
    uid_t uid, 
    gid_t gid, 
    const char *libraryName,
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

    if (libraryName)
    {
        Strlcat(path, ".", PAL_MAX_PATH_SIZE);
        Strlcat(path, libraryName, PAL_MAX_PATH_SIZE);
    }        

    Strlcat(path, ".log", PAL_MAX_PATH_SIZE);

    return 0;
}


void DestroyKrb5CredCache(const char *krb5CredCacheSpec)
{
   // Only destroy the cache if it is a FILE: or DIR: Then we just remove it.
}


MI_Boolean ValidateGssCredentials(const char *credFilePath, const char *krb5KeyTablePath, const char *krb5CredCacheSpec, uid_t uid, gid_t gid )
{
    char *cred_dir = NULL;

    MI_UNUSED(krb5CredCacheSpec);

    if (credFilePath)
    {
        cred_dir = PAL_Strdup(credFilePath);
    }
    else 
    {
        cred_dir = PAL_Strdup(krb5KeyTablePath);
    }

    if (!cred_dir)
    {
        // Nothing to delete
        return MI_FALSE;
    }

    char* p = strrchr(cred_dir, '/');
    if (p)
    {
        *p = '\0';
    }

    {
        struct stat buf = {0};
        int rtn = stat(credFilePath, &buf);

        if (rtn < 0)
        {
            // The file not existing is a failure. We said it was there or we wouldn't be here
            //
            goto Err;
        }

        if (buf.st_uid != uid) {
            goto Err;
        }

        if (S_ISDIR(buf.st_mode) || S_ISLNK(buf.st_mode))
        {
            // Not a file? Unlikely, but complain and issue error
            goto Err;
        }

        // Acceptable dir will be user only, no others
        if (!(buf.st_mode & S_IRUSR) || ( buf.st_mode & (S_IRWXG|S_IRWXO)))
        {
            goto Err;
        }
    }

    // Check the permissions on the directory. They need to be read-only owner
        
    {
        struct stat buf = {0};

        int rtn = stat(cred_dir, &buf);
        if (rtn < 0)
        {
            goto Err;
        }

        if (!S_ISDIR(buf.st_mode))
        {
           // Not a directory? Unlikely, but complain and issue error
            goto Err;
        }

        // Acceptable dir will be user only, no others
        if (!(buf.st_mode & S_IRUSR) || ( buf.st_mode & (S_IRWXG|S_IRWXO)))
        {
            goto Err;
        }

        if (buf.st_uid != uid) {
            goto Err;
        }
    }        

    PAL_Free(cred_dir);
    return TRUE;

Err:
    if (cred_dir) 
    {
        PAL_Free(cred_dir);
    }
    return FALSE;

}

#if defined(CONFIG_OS_LINUX) || defined(CONFIG_OS_DARWIN)
static int _SearchPermissionGroups(PermissionGroups *list, gid_t gid)
{
    PermissionGroup *group = list->head;
        
    while (group)
    {
        if (group->gid == gid)
        {
            return 0;
        }
        
        group = group->next;
    }

    return -1;
}

MI_Boolean IsGroupAllowed(gid_t gid)
{
    // if allowedList is null, then always allow
    if (s_allowedList == NULL)
        return MI_TRUE;

    if (_SearchPermissionGroups(s_allowedList, gid) == 0)
        return MI_TRUE;

    return MI_FALSE;
}

MI_Boolean IsGroupDenied(gid_t gid)
{
    // if deniedList is null, then not denied
    if (s_deniedList == NULL)
        return MI_FALSE;

    if (_SearchPermissionGroups(s_deniedList, gid) == 0)
        return MI_TRUE;

    return MI_FALSE;
}
#endif

void SetPermissionGroups(PermissionGroups *allowedList,
                        PermissionGroups *deniedList)
{
    s_allowedList = (allowedList->head) ? allowedList : NULL;
    s_deniedList = (deniedList->head) ? deniedList : NULL;
}

// return 0 = not authorized; 1 = authorized
int IsUserAuthorized(const char *user, gid_t gid)
{
#define MAX_GROUPS 256    
#if defined(CONFIG_OS_DARWIN)
    typedef int group_type;
#else
    typedef gid_t group_type;
#endif
    group_type groups[MAX_GROUPS];
    int ngroups = MAX_GROUPS;
    int i;

#if defined(CONFIG_OS_LINUX) || defined(CONFIG_OS_DARWIN)
    // get list of groups that user belongs to
    if (getgrouplist(user, gid, groups, &ngroups) == -1)
    {
        trace_GetGroupList_Failure(user, ngroups);
        return 0;
    }

    // denied groups has higher priority
    for (i = 0; i<ngroups; ++i)
    {
        if (IsGroupDenied((gid_t)groups[i]))
            return 0;
    }
    for (i = 0; i<ngroups; ++i)
    {
        if (IsGroupAllowed((gid_t)groups[i]))
            return 1;
    }

    // if not on either list, then it's a deny
    return 0;
#else
    // non-supported platforms
    return 1;
#endif
}

void CleanPermissionGroups(PermissionGroups *list)
{
    PermissionGroup *group;
        
    while (list->head)
    {
        group = list->head;
        list->head = group->next;

        PAL_Free(group);
    }
    
    list->tail = NULL;
}

#endif

