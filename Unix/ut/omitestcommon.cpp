/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
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

