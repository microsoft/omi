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
#include "MyClassForTestingAddedEmbeddedQualifier.h"

void MI_CALL MyClassForTestingAddedEmbeddedQualifier_Load(
    MyClassForTestingAddedEmbeddedQualifier_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyClassForTestingAddedEmbeddedQualifier_Unload(
    MyClassForTestingAddedEmbeddedQualifier_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

