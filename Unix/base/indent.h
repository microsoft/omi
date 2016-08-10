/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_indent_h
#define _omi_indent_h

#include "config.h"
#include <common.h>
#include <stdio.h>

BEGIN_EXTERNC

void Indent(FILE* os, size_t level);

END_EXTERNC

#endif /* _omi_indent_h */
