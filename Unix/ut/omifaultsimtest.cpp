/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "ut.h"

#if defined(CONFIG_ENABLE_FAULTINJECTION)

using namespace TestSystem;

NitsModuleSetup(OMIFaultSimTestSetup)
    NitsTrace(PAL_T("OMIFaultSimTestSetup being run"));
    NitsEnableFaultSimAll();
    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndModuleSetup

NitsCleanup(OMIFaultSimTestSetup)
    NitsTrace(PAL_T("Cleanup of OMIFaultSimTestSetup being run"));
    NitsDisableFaultSimAll();
    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndCleanup

#endif
