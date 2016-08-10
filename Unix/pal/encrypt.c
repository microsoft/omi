/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "encrypt.h"

#if defined(_MSC_VER)
#include <wincrypt.h>
#endif

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

#if defined (_MSC_VER)
    if (inbufferLength%CRYPTPROTECTMEMORY_BLOCK_SIZE)
    {
        realOutBufferNeeded += (CRYPTPROTECTMEMORY_BLOCK_SIZE-(inbufferLength%CRYPTPROTECTMEMORY_BLOCK_SIZE));
    }
#endif

    *outbufferLengthNeeded = realOutBufferNeeded;

    if (inbuffer == NULL)
        return -1;

    if (outbufferLength < realOutBufferNeeded)
        return -2;

    if (outbuffer == NULL)
        return -1;

    memcpy(outbuffer, inbuffer, inbufferLength);

#if defined(_MSC_VER)
    if (!CryptProtectMemory(outbuffer, realOutBufferNeeded, CRYPTPROTECTMEMORY_SAME_PROCESS))
    {
        //printf("error = %u\n", GetLastError());
        SecureZeroMemory(outbuffer, outbufferLength);
        return -1;
    }
#endif
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

#if defined (_MSC_VER)
    if (inbufferLength%CRYPTPROTECTMEMORY_BLOCK_SIZE)
    {
        *outbufferLengthNeeded += (CRYPTPROTECTMEMORY_BLOCK_SIZE-(inbufferLength%CRYPTPROTECTMEMORY_BLOCK_SIZE));
        return -1;
    }
#endif


    if (inbuffer == NULL)
        return -1;

    if (outbufferLength < realOutBufferNeeded)
        return -2;

    if (outbuffer == NULL)
        return -1;

    memcpy(outbuffer, inbuffer, inbufferLength);

#if defined(_MSC_VER)
    if (!CryptUnprotectMemory(outbuffer, realOutBufferNeeded, CRYPTPROTECTMEMORY_SAME_PROCESS))
    {
        SecureZeroMemory(outbuffer, outbufferLength);
        return -1;
    }
#endif
    return 0;
}
