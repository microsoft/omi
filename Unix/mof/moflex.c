/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <pal/palcommon.h>

#if defined(_MSC_VER)

/* warning C4127: conditional expression is constant */
# pragma warning(disable : 4127 )

/* warning C4244: '=' : conversion from '?' to '?', possible loss of data */
# pragma warning(disable : 4244 )
# pragma warning(disable : 4242 )

/* warning C4131: '?' : uses old-style declarator */
# pragma warning(disable : 4131 )

/* warning C4267: '=' : conversion from '?' to '?', possible loss of data */
# pragma warning(disable : 4267)


/* PreFast - reviewed and believed to be false-positive*/

/* warning C6385: Invalid data: accessing '??', the readable size is 'x' bytes, but 'y' bytes might be read: Lines: ... */
# pragma warning(disable : 6385)

/*  warning C6011: Dereferencing NULL pointer '??': Lines: */
# pragma warning(disable : 6011)

#ifdef _PREFAST_
#pragma prefast (disable: 26000)
#pragma prefast (disable: 26001)
#pragma prefast (disable: 28718)
#pragma prefast (disable: 28278)
#endif
#endif /* _MSC_VER */

//#ifdef __cplusplus
//#define input yyinput
//#endif

#include "moflexinc.c"
