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

#ifndef _omi_return_h
#define _omi_return_h

#include "config.h"
#include <stdio.h>
#include <common.h>
#include <nits/base/nits.h>

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
        break; \
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
