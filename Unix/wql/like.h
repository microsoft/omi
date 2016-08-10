/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _wql_like_h
#define _wql_like_h

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

MI_Boolean WQL_MatchLike(
    _In_z_ const ZChar* pattern,
    _In_z_ const ZChar* string,
    ZChar escape);

#ifdef __cplusplus
}
#endif

#endif /* _wql_like_h */

