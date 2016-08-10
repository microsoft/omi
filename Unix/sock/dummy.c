/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

void __sock_dummy()
{
    /* This is the only function now in the sock library. some linkers
     * complain if a library has no symbols. Eventually, the sock library
     * will be removed, but to avoid churn, the sock library is left intact.
     */
}
