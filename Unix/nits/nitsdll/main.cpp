//*****************************************************************************
//  Copyright (C) 2007 Microsoft Corporation
//  All rights reserved.
//*****************************************************************************
#include "../base/Globals.h"

#ifdef _MSC_VER
#include <main.tmh>

BOOL WINAPI DllMain(_In_ HINSTANCE instance, _In_ DWORD reason, PVOID)
{
    switch( reason ) 
    { 
        case DLL_PROCESS_ATTACH:
            //
            // Next, we disable all thread attach and detach messages to minimize our working set
            //
            if ( !DisableThreadLibraryCalls ( instance ) ) 
            {
                return FALSE;
            }

            WPP_INIT_TRACING(NITS_TRACING_LOCATION);
            break;
        case DLL_PROCESS_DETACH:
            WPP_CLEANUP();
            break;
    }

    return TRUE;
}
#endif
