/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "pidfile.h"

#if defined(CONFIG_POSIX)
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
#endif

#include "paths.h"

#if defined(CONFIG_POSIX)

int PIDFile_OpenWrite()
{
    int fd;

    /* Open the PID file */
    fd = open(OMI_GetPath(ID_PIDFILE), O_WRONLY|O_CREAT|O_TRUNC, 0640);
    if (fd == -1)
    {
        /* Possibly errno=EWOULDBLOCK */
        return -1;
    }

    /* Obtain an exclusive write lock */
    if (lockf(fd, F_LOCK, 0) != 0)
    {
        close(fd);
        return -1;
    }

    /* Write PID into file */
    {
        char buf[16];
        int n = sprintf(buf, "%d\n", getpid());

        if (write(fd, buf, n) != n)
        {
            close(fd);
            return -1;
        }
    }

    return fd;
}

int PIDFile_Delete()
{
    int pid;

    /* Only process owner can delete the PID file */
    if (PIDFile_Read(&pid) != 0 || pid != getpid())
        return -1;

    if (unlink(OMI_GetPath(ID_PIDFILE)) != 0)
        return -1;

    return 0;
}

int PIDFile_Read(int* pid)
{
    int fd;
    
    /* Open PID File */
    fd = open(OMI_GetPath(ID_PIDFILE), O_RDONLY);
    if (fd == -1)
        return -1;

    /* Read PID from file */
    {
        char buf[16];
        ssize_t n;
        
        /* Read PID file into buffer */
        n = read(fd, buf, sizeof(buf));
        if (n < 1)
        {
            close(fd);
            return -1;
        }

        /* Null-terminate buffer */
        buf[n] = '\0';

        /* Convert buffer to PID */
        {
            char* end = 0;
            unsigned long x = strtoul(buf, &end, 10);

            if (!end || *end != '\n')
            {
                close(fd);
                return -1;
            }

            if (pid)
                *pid = (int)x;
        }
    }

    close(fd);
    return 0;
}

int PIDFile_Signal(int sig)
{
    int pid;

    /* Get PID  form PIDFILE */
    if (PIDFile_Read(&pid) != 0)
        return -1;

    /* Send a SIGTERM to the server */
    if (kill(pid, sig) != 0)
        return -1;

    return 0;
}

int PIDFile_IsRunning()
{
    int pid;
    int fd;

    /* Open the PID file for write */
    if ((fd = open(OMI_GetPath(ID_PIDFILE), O_WRONLY | O_NONBLOCK, 0640)) == -1)
    {
        return -1;
    }

    /* If able to obtain exclusive write lock, PID file is stale */
    {
        int r = lockf(fd, F_TEST, 0);

        /* Successful exclusive lock (PID file is stale) */
        if (r == 0)
        {
            /* Remove stale PID file */
            unlink(OMI_GetPath(ID_PIDFILE));

            close(fd);
            return -1;
        }

        close(fd);
    }

    /* Fail if PIDFILE does not exist */
    if (access(OMI_GetPath(ID_PIDFILE), R_OK) != 0)
    {
        return -1;
    }

    /* Read PID form PIDFILE */
    if (PIDFile_Read(&pid) != 0)
        return -1;

    /* Test process to see if it is running */
    if (kill(pid, 0) == 0)
        return 0;

    /* Process it not running */
    return -1;
}

#endif /* defined(CONFIG_POSIX) */
