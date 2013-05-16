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

#ifndef _omi_header_h
#define _omi_header_h

#include "config.h"
#include <common.h>
#include <base/batch.h>

BEGIN_EXTERNC

/* 
**==============================================================================
** 
** Header:
**
**     All protocol messages start with this header. The size of this header
**     should be a multiple of 8 (to ensure that the body that follows is
**     aligned on an 8-byte boundary).
**
**==============================================================================
*/

#define PROTOCOL_MAGIC 0xB1A87E2F

#define PROTOCOL_VERSION CONFIG_VERSION_MASK

#define PROTOCOL_HEADER_MAX_PAGES 64

typedef struct _HeaderBase
{
    /* Magic number (can be used to detect endianess of request) */
    MI_Uint32 magic;

    /* Version number of protocol */
    MI_Uint32 version;

    /* Type of message */
    MI_Uint32 msgType;

    /* batch information 0-64 */
    MI_Uint32 pageCount;

    void*     originalMessagePointer;
    /*ATTN pointer has to be padded to 64 bit for 32/64 compatability */

    /* A correlation identifier borne by matching request and response */
    MI_Uint64 msgID;
}
HeaderBase;

typedef struct _Header
{
    HeaderBase  base;

    /* folowed by */
    Header_BatchInfoItem     batchInfo[PROTOCOL_HEADER_MAX_PAGES]; 
}
Header;



END_EXTERNC

#endif /* _omi_header_h */
