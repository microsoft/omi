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
