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

#ifndef _base_format_placeholders_h
#define _base_format_placeholders_h

#ifdef INTLSTR_RC_INC
# define PAL_PRItstr "s"
# define PAL_PRItchr "c"
#elif defined(CONFIG_ENABLE_WCHAR)
# define PAL_PRItstr "S"
# define PAL_PRItchr "C"
#else
# define PAL_PRItstr "s"
# define PAL_PRItchr "c"
#endif

#if defined(_MSC_VER) || defined(INTLSTR_RC_INC)
    # define PAL_PRId64 "I64d"
    # define PAL_PRIu64 "I64u"
    # define PAL_PRIx64 "I64x"
#else
    #define PAL_PRId64 "lld"
    #define PAL_PRIu64 "llu"
    #define PAL_PRIx64 "llx"
#endif

#if defined(_MSC_VER) || defined(INTLSTR_RC_INC)
    /* the format specifiers below follows the documentation of FormatMessage 
    from http://msdn.microsoft.com/en-us/library/windows/desktop/ms679351(v=vs.85).aspx */
    #define Intlstr_UnverifiedPlaceholder(orderNumber, regularFormatSpecifier) \
        "%" #orderNumber "!" regularFormatSpecifier "!"
#else
    /* the format specifiers below follows the specification 
       from http://www.opengroup.org/onlinepubs/009695399/functions/printf.html */
    #define Intlstr_UnverifiedPlaceholder(orderNumber, regularFormatSpecifier) \
        "%" #orderNumber "$" regularFormatSpecifier
#endif

#define Intlstr_d(orderNumber) Intlstr_UnverifiedPlaceholder(orderNumber, "d")
#define Intlstr_x(orderNumber) Intlstr_UnverifiedPlaceholder(orderNumber, "x")
#define Intlstr_tstr(orderNumber) Intlstr_UnverifiedPlaceholder(orderNumber, PAL_PRItstr)
#define Intlstr_tchr(orderNumber) Intlstr_UnverifiedPlaceholder(orderNumber, PAL_PRItchr)

/* Format specifiers that do NOT work and should not be added above:
 *  %f and %g - floating point not supported by FormatMessage
 *       http://msdn.microsoft.com/en-us/library/windows/desktop/ms679351(v=vs.85).aspx explicitly says:
 *      Floating-point format specifiers - e, E, f, and g - are not supported.
 *  %p - apparently not supported by FormatMessage - failed when unit testing
 */

#endif /* _base_format_placeholders_h */
