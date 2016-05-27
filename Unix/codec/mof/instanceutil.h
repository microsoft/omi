/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */


#ifndef _mof_instance_utility_h
#define _mof_instance_utility_h

#include <MI.h>
#include <micodec.h>

BEGIN_EXTERNC

/*
**==============================================================================
**
** Utilities creates instance
**
**==============================================================================
*/
MI_Result MI_CALL Mof_Instance_New(
    _In_ const MI_ClassDecl* classDecl,
    _Outptr_result_maybenull_ MI_Instance **instance);

MI_Result MI_CALL Mof_Instance_InitDynamic(
    _In_z_ const MI_Char* className,
    _In_ MI_Uint32 metaType,
    _Outptr_result_maybenull_ MI_Instance** self);

MI_Result MI_CALL Mof_Instance_Construct(
    _In_ const MI_ClassDecl* classDecl,
    _Out_ MI_Instance* instance);

END_EXTERNC

#endif /* _mof_instance_utility_h */
