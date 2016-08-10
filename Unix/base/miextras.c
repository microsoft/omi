/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "miextras.h"
#include "instance.h"

MI_Result MI_CALL MI_Instance_Print(
    _In_ const MI_Instance* self,
    _In_ FILE* os,
    MI_Uint32 level)
{
    return Instance_Print(self, os, level, MI_TRUE, MI_FALSE);
}


MI_Result MI_CALL MI_Class_Print(
    _In_ const MI_Instance* self,
    _In_ FILE* os,
    MI_Uint32 level)
{
    return Instance_Print(self, os, level, MI_TRUE, MI_TRUE);
}

