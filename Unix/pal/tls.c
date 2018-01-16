/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "tls.h"

_Return_type_success_(return == 0) int TLS_Init_Injected(
    _Out_ TLS* self,
    NitsCallSite cs)
{
    if (NitsShouldFault(cs, NitsAutomatic))
        return -1;

    return pthread_key_create(&self->key, NULL) == 0 ? 0 : -1;
}
