/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */

#ifdef _MSC_VER
#include <windows.h>
#endif

#include <MI.h>
#include "consts.h"

/* Current DLL handle */
HMODULE g_hModule = NULL;
/* Global lock used for delay initializing resource(s) */
CRITICAL_SECTION g_cs;

void InitializeGlobalData()
{
    InitializeCriticalSection(&g_cs);
}

void FinalizeGlobalData()
{
    FinalizeTestData();
    DeleteCriticalSection(&g_cs);
}

BOOL WINAPI DllMain(    
    __in HINSTANCE hInstance,
    __in ULONG ulReason,
    __reserved LPVOID pvReserved)
{
    MI_UNREFERENCED_PARAMETER(pvReserved);
    if (DLL_PROCESS_ATTACH == ulReason)
    {
        DisableThreadLibraryCalls(hInstance);
        g_hModule = hInstance;
        InitializeGlobalData();
    }
    else if (DLL_PROCESS_DETACH == ulReason)
    {
        FinalizeGlobalData();
    }
    return TRUE;
}
