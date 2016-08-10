/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "palcommon.h"


_Success_(return == 0)
int EncryptData(
    _In_bytecount_(inbufferLength) const void *inbuffer, 
    PAL_Uint32 inbufferLength, 
    _Out_writes_bytes_to_opt_(outbufferLength, *outbufferLengthNeeded) void *outbuffer, 
    PAL_Uint32 outbufferLength, 
    _When_(return == -2, _Out_) _When_(return == 0, _Out_)  PAL_Uint32 *outbufferLengthNeeded);

_Success_(return == 0)
int DecryptData(
    _In_bytecount_(inbufferLength) const void *inbuffer, 
    PAL_Uint32 inbufferLength, 
    _Out_writes_bytes_to_opt_(outbufferLength, *outbufferLengthNeeded) void *outbuffer, 
    PAL_Uint32 outbufferLength, 
    _When_(return == -2, _Out_) _When_(return == 0, _Out_) PAL_Uint32 *outbufferLengthNeeded);
