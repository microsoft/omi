/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _OI_FileGen_h_
#define _OI_FileGen_h_

#include "common.h"
#include "OIParser.h"

PAL_BEGIN_EXTERNC

#define OI_MAX_LENGTH 1024

/*
    GenerateFile

    target - output file for the generated code
*/
PAL_Boolean GenerateFile(
    _In_   OIEvent * events,
    _In_z_ const char * target);

PAL_END_EXTERNC

#endif /* _OI_FileGen_h_ */
