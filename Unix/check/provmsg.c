/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <stdio.h>

#include <base/messages.h>

void PrintProviderMsg( _In_ Message* msg)
{
    MessagePrint(msg, stdout);
}
