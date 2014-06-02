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
