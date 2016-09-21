/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _instance_h
#define _instance_h

#include <MI.h>

#ifdef __cplusplus
extern "C" {
#endif

MI_Result Test_Instance_Construct(
    _Out_ MI_Instance* self,
    _In_ const MI_ClassDecl* classDecl);

#ifdef __cplusplus
}
#endif

#endif /* _instance_h */
