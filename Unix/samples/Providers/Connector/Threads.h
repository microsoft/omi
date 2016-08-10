/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _Threads_h
#define _Threads_h

/* Dummy thread routines */

typedef struct _Lock { int dummy; } LockType;

static int CreateThread(void (*Function)(void* arg), void* arg) { return -1; }

static void Sleep(long msec) { }

static void Lock(LockType* lock) { }

static void Unlock(LockType* lock) { }

#endif /* _Threads_h */
