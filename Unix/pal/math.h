/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <math.h>

#ifndef _pal_math_h
#define _pal_math_h

#include <pal/palcommon.h>

#if __STDC_VERSION__ >= 199901L
#   define PAL_ISNAN(x) (isnan(x))
#   define PAL_ISINF(x) (isinf(x))
#   define PAL_NAN() (NAN)
#   define PAL_INF() (INFINITY)
#else
    PAL_INLINE int PAL_ISNAN(double x)
    {
        return (x != x);
    }
    PAL_INLINE int PAL_ISINF(double x)
    {
        return (!PAL_ISNAN(x) && PAL_ISNAN(x - x));
    }
    PAL_INLINE double PAL_NAN(void)
    {
        double zero = 0.0;
        return 0.0 / ((zero - zero) * zero);
    }
    PAL_INLINE double PAL_INF(void)
    {
        double zero = 0.0;
        return 1.0 / ((zero - zero) * zero);
    }
#endif

#endif /* _pal_math_h */
