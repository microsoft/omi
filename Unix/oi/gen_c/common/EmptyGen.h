/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _OI_EmptyGen_h_
#define _OI_EmptyGen_h_

#include "common.h"
#include "OIParser.h"

PAL_BEGIN_EXTERNC

/*
    GenerateEmpty

    target - output file for the generated code

    Generates empty code, no string binary payload, 
    empty collapsable function that compilers will helpfully completely do away with!
*/
PAL_Boolean GenerateEmpty(
    _In_   OIEvent * events,
    _In_z_ const char * target);

PAL_END_EXTERNC

#endif /* _OI_EmptyGen_h_ */
