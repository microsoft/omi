/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */
#include <Windows.h>
#include <state.h>
#include <mofyacc.h>
#include <mofparser.h>

HMODULE g_hModule = NULL;

BOOL WINAPI DllMain(    
    __in HINSTANCE hInstance,
    __in ULONG ulReason,
    __reserved LPVOID pvReserved)
{
    (pvReserved);
    if (DLL_PROCESS_ATTACH == ulReason)
    {
        DisableThreadLibraryCalls(hInstance);
        g_hModule = hInstance;
        GlobalInitialize();
    }
    else if (DLL_PROCESS_DETACH == ulReason)
    {
        GlobalFinalize();
    }
    return TRUE;
}
