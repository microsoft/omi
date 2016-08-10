/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include "ABC_ManagedSystemElement.h"

void MI_CALL ABC_ManagedSystemElement_Load(
    ABC_ManagedSystemElement_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_ManagedSystemElement_Unload(
    ABC_ManagedSystemElement_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

