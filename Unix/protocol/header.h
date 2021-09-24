/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
    /* Magic number (can be used to detect endianness of request) */
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
    MI_Uint64 operationId;
}
HeaderBase;

typedef struct _Header
{
    HeaderBase  base;

    /* followed by */
    Header_BatchInfoItem     batchInfo[PROTOCOL_HEADER_MAX_PAGES]; 
}
Header;



END_EXTERNC

#endif /* _omi_header_h */
