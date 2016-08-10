/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef __util_h
#define __util_h

#include <MI.h>
#include <stdlib.h>
#include <pal/strings.h>

#if defined(__cplusplus)
# define BEGIN_EXTERNC extern "C" {
# define END_EXTERNC }
#else
# define BEGIN_EXTERNC
# define END_EXTERNC
#endif

BEGIN_EXTERNC

char* TToStr(_Out_writes_z_(size) char* buf, size_t size, _In_z_ const TChar* src);

END_EXTERNC

#endif /* __util_h */
