/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "preexec.h"
#include <common.h>
#include <base/base.h>
#include <pal/strings.h>
#include <base/paths.h>
#include <base/strarr.h>

#if defined(CONFIG_POSIX)
# include <pthread.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
#endif

/*
**==============================================================================
**
** Local Definitions:
**
**==============================================================================
*/


static void _BlockSIGCHLD()
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);
}

static void _UnblockSIGCHLD()
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_UNBLOCK, &set, NULL);
}

typedef struct _Bucket /* derives from HashBucket */
{
    struct _Bucket* next;
    char* key;
}
Bucket;

static size_t _Hash(
    const HashBucket* bucket_)
{
    Bucket* bucket = (Bucket*)bucket_;
    size_t h = 0;
    char* key = bucket->key;

    while (*key)
        h += 5 * *key++;

    return h;
}

static int _Equal(
    const HashBucket* bucket1_,
    const HashBucket* bucket2_)
{
    Bucket* bucket1 = (Bucket*)bucket1_;
    Bucket* bucket2 = (Bucket*)bucket2_;
    return strcmp(bucket1->key, bucket2->key) == 0;
}

static void _Release(
    HashBucket* bucket_)
{
    Bucket* bucket = (Bucket*)bucket_;
    PAL_Free(bucket->key);
    PAL_Free(bucket);
}

static MI_Boolean _Contains(
    HashMap* self,
    const char* key)
{
    Bucket bucket;
    bucket.key = (char*)key;
    return HashMap_Find(self, (const HashBucket*)&bucket) ? MI_TRUE : MI_FALSE;
}

static int _Insert(
    HashMap* self,
    const char* key)
{
    Bucket* bucket = (Bucket*)PAL_Calloc(1, sizeof(Bucket));

    if (!bucket)
        return -1;

    bucket->key = PAL_Strdup(key);

    if (!bucket->key)
    {
        PAL_Free(bucket);
        return -1;
    }

    if (HashMap_Insert(self, (HashBucket*)bucket) != 0)
    {
        PAL_Free(bucket);
        PAL_Free(bucket->key);
        return -1;
    }

    return 0;
}

/*
**==============================================================================
**
** Public Definitions:
**
**==============================================================================
*/

int PreExec_Construct(
    PreExec* self)
{
    const size_t NUMLISTS = 32;
    memset(self, 0, sizeof(*self));

    if (HashMap_Init(&self->cache, NUMLISTS, _Hash, _Equal, _Release) != 0)
        return -1;

    return 0;
}

void PreExec_Destruct(
    PreExec* self)
{
    HashMap_Destroy(&self->cache);
}



/*
 * Run on the engine.
 *
 * Checks against the agent scoreboarda (the hashmap in preexec) to see if we 
 * need to execute the preexec, if any. 
 *  
 * Return 0  if not needed and we can proceed.
 *        >0 if we dispatched a request to the server from the engine
 *        <0 if we had an error in the execution of the dispatch (not the from the preexec).
 */

int PreExec_CheckExec(
    PreExec* self,
    const char* programPath,
    uid_t uid,
    uid_t gid)
{
    char key[PAL_MAX_PATH_SIZE];
    char uidBuf[11];
    const char* uidStr;
    char gidBuf[11];
    const char* gidStr;

    /* If no pre-exec program, nothing to do */
    if (programPath == NULL)
        return 0;

    /* Form the UID string */
    {
        size_t dummy;
        uidStr = Uint32ToStr(uidBuf, (PAL_Uint32)uid, &dummy);
    }

    /* Form the GID string */
    {
        size_t dummy;
        gidStr = Uint32ToStr(gidBuf, (PAL_Uint32)gid, &dummy);
    }

    /* Form a hash key from PREEXEC+UID+GID */
    {
        key[0] = '\0';
        Strlcat(key, programPath, PAL_MAX_PATH_SIZE);
        Strlcat(key, "+", PAL_MAX_PATH_SIZE);
        Strlcat(key, uidStr, PAL_MAX_PATH_SIZE);
        Strlcat(key, "+", PAL_MAX_PATH_SIZE);
        Strlcat(key, gidStr, PAL_MAX_PATH_SIZE);
    }

    /* If key already in cache, then return without doing anything */
    {
        static pthread_mutex_t s_mutex = PTHREAD_MUTEX_INITIALIZER;

        pthread_mutex_lock(&s_mutex);

        if (_Contains(&self->cache, key))
        {
            pthread_mutex_unlock(&s_mutex);
            return 0;
        }

        /* Add key to cache */
        _Insert(&self->cache, key);
        pthread_mutex_unlock(&s_mutex);
    }

    return 1;
}





/*
 * Run on the server:
 *   
 */

int PreExec_ExecuteOnServer(
    void * contextptr, 
    const char *programPath, 
    uid_t uid, 
    gid_t gid)
{
    /* Execute and wait on the pre-exec program to exit
     * We will return -errno as the error if the child process has issues
     * which can be propagated back to the engine
     */

    _BlockSIGCHLD();
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            _UnblockSIGCHLD();
            trace_PreExecFailed(programPath);
            return -1;
        }
        else if (pid == 0) {
            /* Child Process here... */
            const char *uidStr;
            const char *gidStr;
            char uidBuf[11];
            char gidBuf[11];
            char path[PAL_MAX_PATH_SIZE];

            /* Form the UID string */
            {
                size_t dummy;
                uidStr = Uint32ToStr(uidBuf, (PAL_Uint32)uid, &dummy);
            }
        
            /* Form the GID string */
            {
                size_t dummy;
                gidStr = Uint32ToStr(gidBuf, (PAL_Uint32)gid, &dummy);
            }

            /* If programPath is relative, form the full path of the pre-exec program */
            {
                path[0] = '\0';
                if (*programPath != '/')
                {
                    const char* bindir = OMI_GetPath(ID_BINDIR);

                    if (bindir != NULL)
                    {
                        Strlcpy(path, bindir, PAL_MAX_PATH_SIZE);
                        Strlcat(path, "/", PAL_MAX_PATH_SIZE);
                    }
                }

                Strlcat(path, programPath, PAL_MAX_PATH_SIZE);
            }

            /* Close any open file descriptors */
            int fd;
            int n = getdtablesize();
    
            if (n > 2500 || n < 0)
            {
                n = 2500;
            }
    
            /* Leave stdin(0), stdout(1), stderr(2) open (for debugging) */
            for (fd = 3; fd < n; ++fd)
            {
                close(fd);
            }

            dup2(STDOUT_FILENO, STDOUT_FILENO);
            dup2(STDERR_FILENO, STDERR_FILENO);

            /* Execute the program */
            int r = execl(
                path,   /* path of program */
                path,   /* argv[0] */
                uidStr, /* argv[1] */
                gidStr, /* argv[2] */
                NULL);

            if (r < 0)
            {
                /* return -errno on error */
                r = -errno;
            }
        
            _exit(r); 
        }
        else 
        {
            pid_t r;
            int status;

            /* Parent Process */
            r = waitpid(pid, &status, 0);

            if (r != pid || WEXITSTATUS(status) != 0)
            {
                _UnblockSIGCHLD();
                trace_PreExecFailed(programPath);
                return -1;
            }
            _UnblockSIGCHLD();
            return status;
        }
    }

    /* unreachable */
}

