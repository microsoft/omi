/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <MI.h>

/* Dummy function to reference exported symbols from miapi library */
void __miapi_dummy(void** p1, void** p2)
{
    *p1 = (void*)mi_clientFT_V1;
    *p2 = (void*)MI_Application_Initialize;
}
