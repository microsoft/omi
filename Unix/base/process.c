/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
#endif

#include "paths.h"

typedef struct _ProcessSelf
{
    int pid;
}
ProcessSelf;

_Use_decl_annotations_
int Process_StartChild(Process* self_, ConstCharPtr path, CharPtrPtr argv)
{
    ProcessSelf* self = (ProcessSelf*)self_;

#if defined(CONFIG_POSIX)

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
#if defined(CONFIG_POSIX)

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
        // EINTR is common in waitpid() and doesn't necessarily indicate failure.
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
