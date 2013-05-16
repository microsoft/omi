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

#ifndef _omi_lib_h
#define _omi_lib_h

#include "config.h"
#include <common.h>
#include "strings.h"

BEGIN_EXTERNC

void Lib_Format(
    _Pre_writable_size_(MAX_PATH_SIZE) char path[MAX_PATH_SIZE],
    const char* dirName,
    const char* shortName);

void* Lib_Open(
    const char* path);

MI_Result Lib_Close(
    void* handle);

void* Lib_Sym(
    void* handle,
    const char* symbol);

char* Lib_Err();

void Lib_Free(
    _Pre_valid_ _Post_ptr_invalid_ CharPtr err);

END_EXTERNC

#endif /* _omi_lib_h */
