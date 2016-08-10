/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_strarr_h
#define _omi_strarr_h

#include <common.h>
#ifdef _MSC_VER
#pragma prefast (disable: 28252)
#pragma prefast (disable: 28253)
#endif
#include <wchar.h>

#include "batch.h"

#if defined(CONFIG_ENABLE_WCHAR)
# define ZArr WcsArr
# define ZArrCat WcsArrCat
# define ZArrLen WcsArrLen
# define ZArrFree WcsArrFree
#else
# define ZArr StrArr
# define ZArrCat StrArrCat
# define ZArrLen StrArrLen
# define ZArrFree StrArrFree
#endif

BEGIN_EXTERNC

/* Allocate an empty null-terminated string array */
char** StrArr();

/* Append a string to the end of the string array */
void StrArrCat(_Inout_ CharPtrPtr * self_, _In_ ConstCharPtr str);

/* Return length of this array */
size_t StrArrLen(_In_ CharPtrPtr self);

/* Free the string array */
void StrArrFree(_Pre_valid_ _Post_ptr_invalid_ CharPtrPtr self);

/* Allocate an empty null-terminated string array */
wchar_t** WcsArr();

/* Append a string to the end of the string array */
void WcsArrCat(_Inout_ WcharPtrPtr * self_, _In_ ConstWcharPtr str);

/* Return length of this array */
size_t WcsArrLen(_In_ WcharPtrPtr self);

/* Free the string array */
void WcsArrFree(_Pre_valid_ _Post_ptr_invalid_ WcharPtrPtr self);

/* Clone string array */
ZChar** CloneStringArray(
    _In_count_(size) const ZChar** data, 
    _In_ MI_Uint32 size,
    _In_ Batch* batch);

END_EXTERNC

#endif /* _omi_strarr_h */
