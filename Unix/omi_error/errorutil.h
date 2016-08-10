/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_error_errorutil_h
#define _omi_error_errorutil_h

#include "config.h"
#include <string.h>
#include <common.h>
#include <base/messages.h>

BEGIN_EXTERNC

//------------------------------------------------------------------------------
// Create PostResultMsg and serialize the error instance based on request message format
//
// Arguments:
//  req     -- Request message
//  err      -- error object. It is optional;
//  errmsg -- final error message that needs to be posted, it is optional; If will be ignored if
//              err argument was NOT null
//  r        -- final result code; If will be ignored if err argument was NOT null
//
// Return:
//      NULL if failed; Otherwise success
//------------------------------------------------------------------------------
PostResultMsg* PostResultMsg_NewAndSerialize(
    _In_ Message* req,
    _In_opt_ const MI_Instance* err,
    _In_opt_z_ const MI_Char* errmsg,
    _In_z_ const MI_Char *errorType,
    _In_ MI_Uint32 r);

END_EXTERNC

#endif /* _omi_error_errorutil_h */
