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

#include "process.h"

#if defined(CONFIG_POSIX)
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
#elif defined(CONFIG_OS_WINDOWS)
# include <windows.h>
# include <process.h>
#endif

#include "paths.h"

typedef struct _ProcessSelf
{
#if defined(CONFIG_OS_WINDOWS)
    HANDLE handle;
#else
    int pid;
#endif
}
ProcessSelf;

_Use_decl_annotations_
int Process_StartChild(Process* self_, ConstCharPtr path, CharPtrPtr argv)
{
    ProcessSelf* self = (ProcessSelf*)self_;

#if defined(CONFIG_OS_WINDOWS)

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    BOOL b;
    char cmd[PAL_MAX_PATH_SIZE];
    wchar_t wcmd[PAL_MAX_PATH_SIZE];

    memset(&wcmd, 0, PAL_MAX_PATH_SIZE * sizeof(wchar_t));
    memset(&cmd, 0, PAL_MAX_PATH_SIZE * sizeof(char));

    /* Initialize process info */
    memset(&pi, 0, sizeof(pi));

    /* Initialize startup info */
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(STARTUPINFO);

    /* Build command line */
    {
        char** p = argv;
        size_t n;
        
        n = Strlcpy(cmd, path, PAL_MAX_PATH_SIZE);
        if (n >= PAL_MAX_PATH_SIZE)
            return -1;

        if (!*p)
            return -1;

        p++;
		
        while (*p)
        {
            n = Strlcat(cmd, " ", PAL_MAX_PATH_SIZE);
            if (n >= PAL_MAX_PATH_SIZE)
                return -1;

            n = Strlcat(cmd, *p++, PAL_MAX_PATH_SIZE);
            if (n >= PAL_MAX_PATH_SIZE)
                return -1;
        }
    }

    /* Convert path to wcs */
    {
        size_t i;

        for (i = 0; i < PAL_MAX_PATH_SIZE; i++)
            wcmd[i] = cmd[i];
    }

    /* Create the process */
    b = CreateProcess(
        NULL, /* applicationName */
        wcmd, /*  commandLine */
        NULL, /* processAttributes */
        NULL, /* threadAttributew */
        TRUE, /* inheritHandles */
        0, /* creationFlags */
        NULL, /* creationFlags */
        NULL, /* currentDirectory */
        &si, /* startupInfo */
        &pi); /* processInfo */

    if (!b)
        return -1;

#if 0
    CloseHandle(pi.hProcess);
#endif
    CloseHandle(pi.hThread);

    self->handle = pi.hProcess;
    return 0;

#elif defined(CONFIG_POSIX)

    int pid = fork();

    if (pid == 0)
    {
        /* Child */
        execv(path, argv);
        exit(1);
    }
    else if (pid > 0)
    {
        /* Parent */
        self->pid = pid;
        return 0;
    }
    else
    {
        /* Fork failed */
        self->pid = -1;
        return -1;
    }
#else
# error "unsupported"
#endif
}

int Process_StopChild(Process* self_)
{
#if defined(CONFIG_OS_WINDOWS)

    ProcessSelf* self = (ProcessSelf*)self_;
    BOOL b;

    b = TerminateProcess(self->handle, 0);

    if (!b)
        return -1;

    return 0;

#elif defined(CONFIG_POSIX)

    ProcessSelf* self = (ProcessSelf*)self_;
    int status;
    int numWaits = 0;

    /* Terminate the process */
    if (kill(self->pid, SIGTERM) != 0)
    {
        perror("PROCESS_STOPCHILD: ");
        return -1;
    }

try_again:
    if (waitpid(self->pid, &status, 0) == -1)
    {
        // EINTR is common in waitpid() and doesn't necessarily indicate faulure.
        //       Give the system 10 times to see if the pid cleanly exits.
        if (10 < numWaits && errno == EINTR)
        {
            numWaits++;
            goto try_again;
        }

        return -1;
    }

    return 0;

#else
# error "unsupported"
#endif
}

#if defined(CONFIG_POSIX)
int Process_Daemonize()
{
    int pid;

    /* Fork for the first time */
    pid = fork();
    if (pid == -1)
        return -1;

    /* If parent, then exit; let child live on. */
    if (pid > 0)
	exit(0);

    /* Become the session leader (return if this fails) */
    if (setsid() == -1)
        return -1;

    /* Fork a second time */
    pid = fork();
    if (pid == -1)
	return -1;

    /* If parent (first child), then exit; let second child live one */
    if (pid > 0)
        exit(0);

    /* Close all file descriptors inherited by this process */
#if 0
    {
        int i;
        for (i = 0; i < 64 ; i++)
            close(i);
    }
#else
    close(0);
    close(1);
    close(2);
#endif

    /* Tie stdin to /dev/null */
    open("/dev/null", O_RDONLY);

    /* Tie stdout to /dev/null */
    open("/dev/null", O_RDWR);

    /* Tie stderr to /dev/null */
    open("/dev/null", O_RDWR);

    /* Set root directory as current directory */
#if 0
    chdir("/");
#endif

    return 0;
}

int SetSignalHandler(int sig, void (*handler)(int))
{
    struct sigaction sig_acts;

    sig_acts.sa_handler = handler;
    sigfillset(&(sig_acts.sa_mask));
    sig_acts.sa_flags = 0;

    return sigaction(sig, &sig_acts, NULL);
}

#endif /* defined(CONFIG_POSIX) */
