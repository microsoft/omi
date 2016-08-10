/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _QualifierDecls_h
#define _QualifierDecls_h

#ifndef MI_CHAR_TYPE
# define MI_CHAR_TYPE 1
#endif

#include <MI.h>
#include <cstddef>

//==============================================================================
//
// Standard qualifier declarations
//
//==============================================================================

extern MI_QualifierDecl* g_qualifierDecls[];
extern size_t g_numQualifierDecls;

#endif /* _QualifierDecls_h */
