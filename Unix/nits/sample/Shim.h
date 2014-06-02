//*****************************************************************************
//	Copyright (C) 2003 Microsoft Corporation
//  All rights reserved.
//*****************************************************************************

void *Shim_HeapAlloc(
    size_t bytes,
    NitsCallSite line);

BOOL Shim_SendRequest(
    PCWSTR str,
    NitsCallSite line);

#define _HeapAlloc(bytes, line) Shim_HeapAlloc(bytes, line)
#define _SendRequest(str, line) Shim_SendRequest(str, line)
