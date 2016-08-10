/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
