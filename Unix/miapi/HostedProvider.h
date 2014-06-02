/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */
#ifndef __hostedprovider_h_
#define __hostedprovider_h_

#include <MI.h>

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL HostedProvider_Create(
    _In_  MI_Application *application,
    _In_z_  const MI_Char * namespaceName,
    _In_z_  const MI_Char * providerName,
    _In_  MI_MainFunction mi_Main,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_ MI_HostedProvider *hostedProvider);

MI_Result MI_CALL HostedProvider_Close(
        _In_  MI_HostedProvider *hostedProvider);

MI_Result MI_CALL HostedProvider_GetApplication(
        _In_  MI_HostedProvider *hostedProvider,
        _Out_ MI_Application *application);
#endif /* __hostedprovider_h_ */

