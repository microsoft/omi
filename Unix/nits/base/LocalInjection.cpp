/*
 * Copyright (C) 2011 Microsoft Corporation
 * All rights reserved.
 */

#include "Run.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <pal/shlib.h>
#include <pal/strings.h>

using namespace std;

namespace TestSystem 
{
    Shlib* nitsinj_handle = NULL;
    int (NITS_CALL *NitsStartInjectorFunc)(void);
    void (NITS_CALL *NitsStopInjectorFunc)(void);

    NITS_EXTERN_C void ATEXIT_API unload()
    {
        if(nitsinj_handle)
        {
            NitsStopInjectorFunc();
            Shlib_Close(nitsinj_handle);
        }
    }

    bool ConfigureLocalInjection()
    {
#ifdef _MSC_VER
        const PAL_Char *injectorLibName = PAL_T("nitsinj.dll");
#else
        PAL_Char injectorLibName[NAME_MAX];
        TcsStrlcpy(injectorLibName, CONFIG_LIBDIR "/libnitsinj.so", NAME_MAX);
#endif

        if (nitsinj_handle)
        {
            Tprintf(PAL_T("ERROR: nits injection already loaded\n"));
            return false;
        }
        
        nitsinj_handle = Shlib_Open_Injected(injectorLibName, NitsReservedCallSite());
        if (!nitsinj_handle)
        {
            Tprintf(PAL_T("ERROR: could not load nits injection library\n"));
            return false;
        }

        void* func = NULL;
        int result = 0;

        func = Shlib_Sym(nitsinj_handle, "NitsStartInjector");
        if (func == NULL)
            goto Unload;

        NitsStartInjectorFunc = (int (NITS_CALL *)(void))func;

        func = Shlib_Sym(nitsinj_handle, "NitsStopInjector");
        if (func == NULL)
            goto Unload;

        NitsStopInjectorFunc = (void (NITS_CALL *)(void))func;

        result = NitsStartInjectorFunc();
        if (result != 0)
            goto Unload;

        PAL_Atexit(unload);

        return true;

    Unload:
        Tprintf(PAL_T("ERROR: could not load nits injection library\n"));
        Shlib_Close(nitsinj_handle);
        nitsinj_handle = NULL;
        return false;
    }
}

