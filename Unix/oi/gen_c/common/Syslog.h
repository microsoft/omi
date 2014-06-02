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

#ifndef _OI_Syslog_h_
#define _OI_Syslog_h_

#include "common.h"
#include "OIParser.h"

PAL_BEGIN_EXTERNC

#define OI_MAX_LENGTH 1024

/*
    GenerateEtw

    events - linked list of OI event description
    ident, options, facility - Syslog settings
    target - output file for the generated code
*/
PAL_Boolean GenerateSyslog(
    _In_   OIEvent * events,
    _In_z_ const char * ident,
    _In_z_ const char * options,
    _In_z_ const char * facility,
    _In_z_ const char * target);

PAL_END_EXTERNC

#endif /* _OI_Syslog_h_ */
