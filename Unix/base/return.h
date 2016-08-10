/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_return_h
#define _omi_return_h

#include "config.h"
#include <stdio.h>
#include <common.h>
#include <nits/base/nits.h>
#include <pal/intsafe.h>

/*
**==============================================================================
**
** This file defines two tracing macros:
**
**     MI_RETURN(EXPR)
**     MI_RETURN_ERR(EXPR)
**
** These override the macros with the same names in MI.h and add printf
** tracing on onon-zero MI_Result objects (those not equal to MI_RESULT_OK).
** Functions that use these macros can enable tracing of bad return values
** by simply including this file.
**
**==============================================================================
*/

#if defined(MI_RETURN)
# undef MI_RETURN
#endif

#define MI_RETURN(EXPR) \
    for (;;) \
    { \
        MI_Result __r = EXPR; \
        NitsCompare(__r, MI_RESULT_OK, PAL_T("Failed"));\
        return __r; \
    }

#if defined(MI_RETURN_ERR)
# undef MI_RETURN_ERR
#endif

#define MI_RETURN_ERR(EXPR) \
    for (;;) \
    { \
        MI_Result r = EXPR; \
        if (r != MI_RESULT_OK) \
        { \
            NitsCompare(r, MI_RESULT_OK, PAL_T("Failed")); \
            return r; \
        } \
        break; \
    }

#endif /* _omi_return_h */
