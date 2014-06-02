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

using namespace TestSystem;

using namespace TestSystem;
#include <base/log.h>

// client tests run over MI API and do not use the OMITestSetup defined in omitestcommon.cpp
// since the MI dll has its own logging story where it opens the log
// and closes it in the end; so the NitsModuleSetup should not interfere with that
// only thing needed is to set the loglevel as passed in
// additionally; it does not let you set the logstderr at the module level since
// the log is open and closed on every application open/close which overwrites output redirection to stderr
NitsModuleSetup(OMICliTestSetup)
    NitsTrace(PAL_T("MIApiTestSetup being run"));

    const PAL_Char *loglevelParam = NitsTestGetParam(PAL_T("loglevel"));
    if(loglevelParam && Log_SetLevelFromPalCharString(loglevelParam) != 0)
    {
        NitsTrace(PAL_T("loglevel parameter invalid; not setting loglevel"));
        NitsAssert(PAL_FALSE, PAL_T("loglevel parameter invalid"));
    }

    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndModuleSetup
