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
