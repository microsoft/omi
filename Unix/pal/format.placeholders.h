/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _base_format_placeholders_h
#define _base_format_placeholders_h
# define PAL_PRItstr "s"
# define PAL_PRItchr "c"

#if defined(INTLSTR_RC_INC)
    # define PAL_PRId64 "I64d"
    # define PAL_PRIu64 "I64u"
    # define PAL_PRIx64 "I64x"
#else
    #define PAL_PRId64 "lld"
    #define PAL_PRIu64 "llu"
    #define PAL_PRIx64 "llx"
#endif

#if defined(INTLSTR_RC_INC)
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
