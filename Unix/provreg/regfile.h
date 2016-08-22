/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _provreg_regfile_h
#define _provreg_regfile_h

#include <common.h>
#include "provreg.h"

/* Maximum line length */
#define MAX_LINE 1024

BEGIN_EXTERNC

typedef struct _RegClass
{
    /* Same initial members as ListElem */
    struct _RegClass* next;
    struct _RegClass* prev;

    char* name;
    char* refName1;
    char* refName2;

    /* Provider process-hosting model */
    char* hosting;

    /* Registered class type */
    ProvRegType regtype;
}
RegClass;

typedef struct _RegFile
{
    char* library;
    char* script;

#if defined(CONFIG_ENABLE_PREEXEC)

    /* Name of program to be executed before invoking this provider */
    char* preexec;

#endif /* defined(CONFIG_ENABLE_PREEXEC) */

    /* 1 if lifetime of instance is that of context,
     * 0 otherwise
     */
    int instanceLifetimeContext;

    RegClass* classesHead;
    RegClass* classesTail;
    RegClass* extraClassesHead;
    RegClass* extraClassesTail;
}
RegFile;

RegFile* RegFile_New(const char* path);

void RegFile_Delete(RegFile* self);

void RegFile_Print(RegFile* self, FILE* os);

END_EXTERNC

#endif /* _provreg_regfile_h */
