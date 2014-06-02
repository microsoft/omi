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

#ifndef _OI_EtwGen_h_
#define _OI_EtwGen_h_

#include "common.h"
#include "OIParser.h"

BEGIN_EXTERNC

typedef struct _SigBucket
{
    struct _SigBucket* next;
    char* key;
    ULONGLONG value;
}
SigBucket;

typedef struct _Buckets
{
    SigBucket * tasks;
    SigBucket * opcodes;
    SigBucket * keywords;
}
Buckets;

/*
    GenerateEtw

    events - linked list of OI event description
    providerId - GUID
    target - output file for the generated code
*/
MI_Boolean GenerateEtw(
    _In_   OIEvent * events,
    _In_   Buckets * set,
    _In_z_ char * providerId,
    _In_z_ char * target);

MI_Boolean GenerateTaskOpcodeKeywords(
    _In_ OIEvent * events,
    _In_ Buckets * set
    );

/*
Does not release the object itself!
Just cleans up its contents.
*/
void CleanupBuckets(_In_ Buckets * set);

END_EXTERNC

#endif /* _OI_EtwGen_h_ */
