/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_file_h
#define _pal_file_h

#include <stdio.h>

#include "palcommon.h"

PAL_BEGIN_EXTERNC

FILE* File_Open(
    _In_z_ const char* path,
    _In_z_ const char* mode);

void File_Close(FILE* fp);

int File_Remove(
    _In_z_ const char* path);

int File_Touch(
    _In_z_ const char* path);

int File_Copy(
    _In_z_ const char* src,
    _In_z_ const char* dest);

PAL_END_EXTERNC

#endif /* _pal_file_h */
