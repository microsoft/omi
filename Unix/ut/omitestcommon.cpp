/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "ut.h"
#include <base/log.h>
#include <base/paths.h>
#include <pal/strings.h>
#include <pal/sleep.h>
#include <iostream>

using namespace TestSystem;


NitsModuleSetup(OMITestSetup)
    NitsTrace(PAL_T("OMITestSetup being run"));
    if(NitsTestGetParam(PAL_T("logstderr")))
    {
        Log_OpenStdErr();
    }
    else
    {
        PAL_Char finalPath[PAL_MAX_PATH_SIZE];

        /* Create name and Open the log file */

        if((CreateLogFileNameWithPrefix("omitest", finalPath) != 0) ||
            (Log_Open(finalPath) != MI_RESULT_OK))
        {        
            NitsTrace(PAL_T("failed to open log file; routing output to stderr"));
            Log_OpenStdErr();
        }
    }

    const PAL_Char *loglevelParam = NitsTestGetParam(PAL_T("loglevel"));
    if(loglevelParam && Log_SetLevelFromPalCharString(loglevelParam) != 0)
    {
        NitsTrace(PAL_T("loglevel parameter invalid; not setting loglevel"));
        NitsAssert(PAL_FALSE, PAL_T("loglevel parameter invalid"));
    }

    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndModuleSetup

NitsCleanup(OMITestSetup)


    NitsTrace(PAL_T("Cleanup of OMITestSetup being run"));
    Log_Close();

#if defined(USE_ALLOCATOR)
    Sleep_Milliseconds(100);
    fflush(stdout);
    std::cout << std::flush;
    PAL_DumpAllocList();
#endif /* defined(USE_ALLOCATOR) */

    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndCleanup

