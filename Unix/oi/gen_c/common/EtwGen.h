/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
