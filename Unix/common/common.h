/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _common_h
#define _common_h

#include "config.h"
#include <pal/memory.h>

#if defined(CONFIG_OS_LINUX)
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#endif

/* Define version for omigen:gen.cpp */
#define _MIAPIVERSION 2

#include <MI.h>
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <wchar.h>
# include <linux/sal.h>
#include "localizestr.h"


// Following will be used to limit the buffer size server can accept from provider host.
// This is also used to limit the max size on http transport
#define MAX_ENVELOPE_SIZE   (250*1024)


/*
**==============================================================================
**
** Binary form of version:
**
**==============================================================================
*/

#define CONFIG_VERSION_MASK \
    ((CONFIG_MAJOR << 16) | (CONFIG_MINOR << 8) | CONFIG_REVISION)

/*
**==============================================================================
**
** UNREACHABLE_RETURN
**
**==============================================================================
*/

#if defined(CONFIG_PLATFORM_HPUX_IA64_HP)
# define UNREACHABLE_RETURN(EXPR) EXPR
#else
# define UNREACHABLE_RETURN(EXPR) /* empty */
#endif

/*
**==============================================================================
**
** TRACE macro
**
**==============================================================================
*/

# define TRACE Printf("TRACE: %s(%u)\n", __FILE__, __LINE__)

/*
**==============================================================================
**
** Extended error codes (requires casting).
**
**==============================================================================
*/

#define MI_RESULT_CANCELED ((MI_Result)1000)
#define MI_RESULT_OPEN_FAILED ((MI_Result)1001)
#define MI_RESULT_INVALID_CLASS_HIERARCHY ((MI_Result)1002)
#define MI_RESULT_WOULD_BLOCK ((MI_Result)1003)
#define MI_RESULT_TIME_OUT ((MI_Result)1004)
#define MI_RESULT_IN_PROGRESS ((MI_Result)1005)

/*
**==============================================================================
**
** For testing the array bit of the MI_Type enumeration.
**
**==============================================================================
*/

#define MI_ARRAY_BIT 0x10

/*
**==============================================================================
**
** ATTN: Temporary placeholders for various following argument types (replace
** these later with correct parameters).
**
**==============================================================================
*/

#define __nameSpace ((const MI_Char*)0)
#define __className ((const MI_Char*)0)
#define __methodName ((const MI_Char*)0)

/*
**==============================================================================
**
** Basic type definitions.
**
**==============================================================================
*/

typedef MI_Char* MI_String;
typedef const MI_Char* MI_ConstString;
typedef MI_Char ZChar;

#define ZT MI_T

/*
**==============================================================================
**
** MI_UNUSED
**
**==============================================================================
*/
#define MI_UNUSED(X) ((void)X)

/*
**==============================================================================
**
** EXTERNC
** BEGIN_EXTERNC
** END_EXTERNC
**
**==============================================================================
*/

#if defined(__cplusplus)
# define EXTERNC extern "C"
# define BEGIN_EXTERNC extern "C" {
# define END_EXTERNC }
#else
# define EXTERNC /* empty */
# define BEGIN_EXTERNC /* empty */
# define END_EXTERNC /* empty */
#endif

/*
**==============================================================================
**
** INLINE macro
**
**==============================================================================
*/

#if defined(__GNUC__)
# define INLINE static __inline
#elif defined(sun)
# define INLINE static inline
#elif defined(aix)
# define INLINE __inline
#else
# define INLINE static __inline
#endif

/*
**==============================================================================
**
** FUNCTION_NEVER_RETURNS macro
**
**==============================================================================
*/

# define FUNCTION_NEVER_RETURNS

/* 
**==============================================================================
**
** UINT64_FMT macro
** SINT64_FMT macro
**
**==============================================================================
*/

# define UINT64_FMT "%llu"
# define SINT64_FMT "%lld"
# define UINT64_FMT_T MI_T("%llu")
# define SINT64_FMT_T MI_T("%lld")

/*
**==============================================================================
**
** MI_RETURN(RESULT)
**
**     Macro to return the given RESULT (other modules may override this macro 
**     to add tracing or logging of error return values).
**
**==============================================================================
*/

#define MI_RETURN(RESULT) \
    for (;;) \
    { \
        return RESULT; \
    }

/*
**==============================================================================
**
** MI_RETURN_ERR(RESULT)
**
**     Macro to return when RESULT is not MI_RESULT_OK (other modules may
**     override this macro to add tracing and logging of error return values).
**
**==============================================================================
*/

#define MI_RETURN_ERR(RESULT) \
    for (;;) \
    { \
        MI_Result r = RESULT; \
        if (r != MI_RESULT_OK) \
            return r; \
        break; \
    }

/*
**==============================================================================
**
** PRINTF_FORMAT(N,M)
**
**     Use this macro on functions that support a printf-style format argument.
**     This permits some compilers to check the arguments.
**
**==============================================================================
*/

#if defined(__GNUC__) && (__GNUC__ >= 4)
# define PRINTF_FORMAT(N,M) __attribute__((format(printf, N, M)))
#else
# define PRINTF_FORMAT(N,M) /* empty */
#endif

/*
**==============================================================================
**
**  TIMEOUT FOR CALLS TO select()
**
**     Value, in msec, that different platforms need to fill or empty a
**     communications socket.
**
**==============================================================================
*/

#if defined(CONFIG_PLATFORM_SUNOS_I86PC_SUNPRO)
# define SELECT_BASE_TIMEOUT_MSEC 10
#elif defined(CONFIG_PLATFORM_SUNOS_SPARC_SUNPRO)
# define SELECT_BASE_TIMEOUT_MSEC 10
#elif defined(CONFIG_PLATFORM_HPUX_IA64_HP)
# define SELECT_BASE_TIMEOUT_MSEC 30
#elif defined(CONFIG_PLATFORM_HPUX_PARISC_HP)
# define SELECT_BASE_TIMEOUT_MSEC 30
#elif defined(CONFIG_PLATFORM_AIX_PPC_IBM)
# define SELECT_BASE_TIMEOUT_MSEC 20
#elif defined(LINUX_IX86_GNU) || defined (LINUX_X86_64_GNU)
# define SELECT_BASE_TIMEOUT_MSEC 2
#else
# define SELECT_BASE_TIMEOUT_MSEC 1
#endif

/*
**==============================================================================
**
**  DEBUG_ASSERT()
**
**==============================================================================
*/

#if defined(CONFIG_ENABLE_DEBUG)
# define DEBUG_ASSERT(COND) assert(COND)
#else
# define DEBUG_ASSERT(COND) /* empty */
#endif

/*
**==============================================================================
**
** NULL_FILE macro
**
**==============================================================================
*/

/* null-file - always can be opened/written and always ignored */
# define NULL_FILE "/dev/null"

/*
**==============================================================================
**
**  __FUNCTION__
**
**==============================================================================
*/

#if !defined(CONFIG_HAVE_FUNCTION_MACRO)
#  define __FUNCTION__ "<unknown>"
#endif

/*
**==============================================================================
**
**  CallSite type (used to track site of function invocations when enabled).
**
**==============================================================================
*/

#if defined(CONFIG_ENABLE_DEBUG)

typedef struct _CallSite
{
    const char* file;
    size_t line;
    const char* func;
}
CallSite;

MI_INLINE CallSite MakeCallSite(const char* file, size_t line, const char* func)
{
    CallSite result;
    result.file = file;
    result.line = line;
    result.func = func;
    return result;
}

# define CALLSITE MakeCallSite(__FILE__, __LINE__, __FUNCTION__)

#else /* defined(CONFIG_ENABLE_DEBUG) */

typedef int CallSite;

# define CALLSITE 0

#endif /* !defined(CONFIG_ENABLE_DEBUG) */

/*
**==============================================================================
**
** NAMESPACE_SEPARATOR
**
**     The separator character for namespace names used on disk (note that
**     '/' cannot be used since it is the file system path separator).
**
**==============================================================================
*/

#define NAMESPACE_SEPARATOR '-'

typedef _Null_terminated_ const char* ConstCharPtr;
typedef _Null_terminated_ char* CharPtr;
typedef _Null_terminated_ CharPtr* CharPtrPtr;

typedef _Null_terminated_ const wchar_t* ConstWcharPtr;
typedef _Null_terminated_ wchar_t* WcharPtr;
typedef _Null_terminated_ WcharPtr* WcharPtrPtr;


#define MI_VERSION_GET_MAJOR(VERSION) ((VERSION & 0xFFFF0000) >> 16)
#define MI_VERSION_GET_MINOR(VERSION) ((VERSION & 0x0000FF00) >> 8)
#define MI_VERSION_GET_REVISION(VERSION) (VERSION & 0x000000FF)

/*
**==============================================================================
**
** union MI_ValuePtr
**
**     A union that reflects the types of things that are pointed to by the
**     class, attribute and qualifier _value_ fields present in the structures
**     passed in the callbacks from the MOF compiler.
**
**==============================================================================
*/

typedef union _MI_ValuePtr
{
    MI_Boolean* boolean;
    MI_Uint8* uint8;
    MI_Sint8* sint8;
    MI_Uint16* uint16;
    MI_Sint16* sint16;
    MI_Uint32* uint32;
    MI_Sint32* sint32;
    MI_Uint64* uint64;
    MI_Sint64* sint64;
    MI_Real32* real32;
    MI_Real64* real64;
    MI_Char16* char16;
    MI_Datetime* datetime;
    MI_Char* string;
    MI_Instance* instance;
    MI_Instance* reference;

    MI_BooleanA* booleana;
    MI_Uint8A* uint8a;
    MI_Sint8A* sint8a;
    MI_Uint16A* uint16a;
    MI_Sint16A* sint16a;
    MI_Uint32A* uint32a;
    MI_Sint32A* sint32a;
    MI_Uint64A* uint64a;
    MI_Sint64A* sint64a;
    MI_Real32A* real32a;
    MI_Real64A* real64a;
    MI_Char16A* char16a;
    MI_DatetimeA* datetimea;
    MI_StringA* stringa;
    MI_ReferenceA* referencea;
    MI_InstanceA* instancea;
    MI_Array* array;

    void* generic;

} MI_ValuePtr;

#endif /* _common_h */
