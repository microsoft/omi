/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "parameters.h"
#include "instance.h"

MI_Result Parameters_Init(
    MI_Instance* self,
    const MI_MethodDecl* methodDecl,
    Batch* batch)
{
    return Instance_Construct(self, (const MI_ClassDecl*)methodDecl, batch);
}

MI_Result Parameters_New(
    MI_Instance** self,
    const MI_MethodDecl* methodDecl,
    Batch* batch)
{
    return Instance_New(self, (const MI_ClassDecl*)methodDecl, batch);
}
