/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_parameters_h
#define _omi_parameters_h

#include "config.h"
#include <common.h>
#include "batch.h"

BEGIN_EXTERNC

MI_Result Parameters_Init(
    MI_Instance* self,
    const MI_MethodDecl* methodDecl,
    Batch* batch);

MI_Result Parameters_New(
    MI_Instance** self,
    const MI_MethodDecl* methodDecl,
    Batch* batch);

END_EXTERNC

#endif /* _omi_parameters_h */
