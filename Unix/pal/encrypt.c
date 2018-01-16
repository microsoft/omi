/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "encrypt.h"

_Success_(return == 0)
int EncryptData(
    _In_bytecount_(inbufferLength) const void *inbuffer, 
    PAL_Uint32 inbufferLength, 
    _Out_writes_bytes_to_opt_(outbufferLength, *outbufferLengthNeeded) void *outbuffer, 
    PAL_Uint32 outbufferLength, 
    _When_(return == -2, _Out_) _When_(return == 0, _Out_)  PAL_Uint32 *outbufferLengthNeeded)
{
    PAL_Uint32 realOutBufferNeeded = inbufferLength;

    if (outbufferLengthNeeded == NULL)
        return -1;

    *outbufferLengthNeeded = realOutBufferNeeded;

    if (inbuffer == NULL)
        return -1;

    if (outbufferLength < realOutBufferNeeded)
        return -2;

    if (outbuffer == NULL)
        return -1;

    memcpy(outbuffer, inbuffer, inbufferLength);

    return 0;
}



_Success_(return == 0)
int DecryptData(
    _In_bytecount_(inbufferLength) const void *inbuffer, 
    PAL_Uint32 inbufferLength, 
    _Out_writes_bytes_to_opt_(outbufferLength, *outbufferLengthNeeded) void *outbuffer, 
    PAL_Uint32 outbufferLength, 
    _When_(return == -2, _Out_) _When_(return == 0, _Out_)  PAL_Uint32 *outbufferLengthNeeded)
{
    PAL_Uint32 realOutBufferNeeded = inbufferLength;

    if (outbufferLengthNeeded == NULL)
        return -1;

    *outbufferLengthNeeded = realOutBufferNeeded;

    if (inbuffer == NULL)
        return -1;

    if (outbufferLength < realOutBufferNeeded)
        return -2;

    if (outbuffer == NULL)
        return -1;

    memcpy(outbuffer, inbuffer, inbufferLength);

    return 0;
}
