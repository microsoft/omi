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

#ifndef _provreg_regfile_h
#define _provreg_regfile_h

#include <common.h>

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
}
RegClass;

typedef struct _RegFile
{
    char* library;
    RegClass* classesHead;
    RegClass* classesTail;
}
RegFile;

RegFile* RegFile_New(const char* path);

void RegFile_Delete(RegFile* self);

void RegFile_Print(RegFile* self, FILE* os);

END_EXTERNC

#endif /* _provreg_regfile_h */
