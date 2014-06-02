//*****************************************************************************
//    Copyright (C) 2011 Microsoft Corporation
//  All rights reserved.
//*****************************************************************************

#include <nits/base/nits.h>

NITS_EXTERN_C NITS_DLLEXPORT int DoSomething()
{
    int i = 0;
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
        return i;

    i = i + 1;

    if (NitsShouldFault(NitsHere(), NitsAutomatic))
        return i;

    i = i + 2;

    return i;
}
