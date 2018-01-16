/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef HOOK_BUILD
	#define HOOK_BUILD
#endif

#include <nits/base/nits.h>

void *Shim_HeapAlloc(
    size_t bytes,
    NitsCallSite line)
{
    if (NitsShouldFault(line, NitsAutomatic))
    {
        return NULL;
    }

    return SystemMalloc(bytes);
}

BOOL Shim_SendRequest(
    PCWSTR str,
    NitsCallSite line)
{
    if (NitsShouldFault(line, NitsAutomatic))
    {
        return FALSE;
    }

    return TRUE;
}
