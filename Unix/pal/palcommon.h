#ifndef _pal_palcommon_h
#define _pal_palcommon_h

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#if defined(_MSC_VER)
#    include <windows.h>
#    include <windef.h>
#    include <windows.h>
#    include <strsafe.h>
#else
#    include "../../common/linux/sal.h"
#endif

#include <limits.h>

#ifndef NAME_MAX
#  define NAME_MAX 255
#endif

/*
**==============================================================================
**
**  Windows-specific types.  Defined here for PAL on Non-Windows platforms.
**
**==============================================================================
*/

#ifdef _MSC_VER
    #ifndef WIN32_FROM_HRESULT
        #define WIN32_FROM_HRESULT(hr) (HRESULT_FACILITY(hr) == FACILITY_WIN32 ? HRESULT_CODE(hr) : hr)
    #endif
#else
    #define WIN32_FROM_HRESULT(hr) hr
    #define HRESULT_FROM_WIN32(error) error
    typedef unsigned long DWORD, *LPDWORD;
    typedef int BOOL;
    typedef unsigned long HRESULT;
    typedef const wchar_t *PCWSTR;
    typedef wchar_t *PWSTR;
    typedef const char *PCSTR;
    typedef char *PSTR;
    typedef void *PVOID;
    typedef PVOID HANDLE;
    #define NO_ERROR 0
    #define INFINITE 0xFFFFFFFF
    #define WINAPI
    #define S_OK 0
    #define ERROR_GEN_FAILURE 31
    #define TRUE 1
    #define FALSE 0
    #define ERROR_INVALID_PARAMETER 87
    #define ERROR_OUTOFMEMORY 14
    #define MAX_PATH 0x00000104
    typedef unsigned long long uint64;
#endif

/*
**==============================================================================
**
** Including config.h
**
**==============================================================================
*/
#if defined(_MSC_VER)
#    include <pal/config.h>
#else
#    include "config.h"
#endif

/*
**==============================================================================
**
**  __FUNCTION__
**
**==============================================================================
*/

#if !defined(CONFIG_HAVE_FUNCTION_MACRO)
# if !defined(_MSC_VER) && !defined(__FUNCTION__)
#  define __FUNCTION__ "<unknown>"
# endif
#endif

/*
**==============================================================================
**
** PAL_32BIT
** PAL_64BIT
**
**==============================================================================
*/
#if defined(__GNUC__)
# if defined(__i386__)
# define PAL_32BIT
# elif defined(__x86_64__)
# define PAL_64BIT
# elif defined(__ppc__)
# define PAL_32BIT
# elif defined(__ppc64__)
# define PAL_64BIT
# elif ((ULONG_MAX) == (UINT_MAX) && (ULONG_MAX == 0xFFFFFFFF))
# define PAL_32BIT
# else
# define PAL_64BIT
# endif
#elif defined(_MSC_VER)
# if defined(_WIN64)
# define PAL_64BIT
# else
# define PAL_32BIT
# endif
#elif ((ULONG_MAX) == (UINT_MAX) && (ULONG_MAX == 0xFFFFFFFF))
# define PAL_32BIT
#else
# define PAL_64BIT
#endif

/*
**==============================================================================
**
** PAL_CALL macro
**
**==============================================================================
*/
#ifdef _MSC_VER
# define PAL_CALL __stdcall
#else
# define PAL_CALL
#endif

/*
**==============================================================================
**
** PAL_EXPORT_API, PAL_IMPORT_API macros
**
**==============================================================================
*/

#if defined(_MSC_VER)
# define PAL_EXPORT_API __declspec(dllexport)
# define PAL_IMPORT_API __declspec(dllimport)
#elif defined(__GNUC__)
# define PAL_EXPORT_API __attribute__((visibility("default")))
# define PAL_IMPORT_API /* empty */
#elif defined(sun)
# define PAL_EXPORT_API __global
# define PAL_IMPORT_API /* empty */
#else
# define PAL_EXPORT_API /* empty */
# define PAL_IMPORT_API /* empty */
#endif

/*
**==============================================================================
**
** PAL_BEGIN_EXTERNC
** PAL_END_EXTERNC
**
**==============================================================================
*/

#if defined(__cplusplus)
# define PAL_BEGIN_EXTERNC extern "C" {
# define PAL_END_EXTERNC }
#else
# define PAL_BEGIN_EXTERNC
# define PAL_END_EXTERNC
#endif

/*
**==============================================================================
**
** PAL_EXTERN_C
**
**==============================================================================
*/
#ifdef __cplusplus
# define PAL_EXTERN_C extern "C"
#else
# define PAL_EXTERN_C extern
#endif /* __cplusplus */

/*
**==============================================================================
**
** PAL_INLINE macro
**
**==============================================================================
*/

#if defined(_MSC_VER)
# define PAL_INLINE static __inline
#elif defined(__GNUC__)
# define PAL_INLINE static __inline
#elif defined(sun)
# define PAL_INLINE static inline
#elif defined(__PPC)
# define PAL_INLINE __inline__
#else
# define PAL_INLINE static __inline
#endif

/*
**==============================================================================
**
** PAL string
**
**==============================================================================
*/

#if defined(CONFIG_ENABLE_WCHAR)
typedef wchar_t PAL_Char;
#else
typedef char PAL_Char;
#endif

typedef PAL_Char TChar;

/*
**==============================================================================
**
** PAL_T()
**
**==============================================================================
*/

#if defined(CONFIG_ENABLE_WCHAR)
# define __PAL_T(STR) L ## STR
# define PAL_T(STR) __PAL_T(STR)
#else
# define PAL_T(STR) STR
#endif

/*
**==============================================================================
**
** PAL_UNUSED
**
**==============================================================================
*/

#define PAL_UNUSED(X) ((void)X)

/*
**==============================================================================
**
** PAL_HAVE_POSIX
**
**==============================================================================
*/

#if defined(linux) || defined(sun) || defined(hpux) || defined(aix)
# define PAL_HAVE_POSIX
#endif

/*
**==============================================================================
**
** PAL_HAVE_PTHREADS
**
**==============================================================================
*/

#if defined(linux) | defined(sun) | defined(hpux) | defined(aix)
# define PAL_HAVE_PTHREADS
#endif

/*
**==============================================================================
**
** Basic types
**
**==============================================================================
*/

typedef unsigned char PAL_Uint8;
#define PAL_UINT8_MAX (UCHAR_MAX)

typedef signed char PAL_Sint8;
#define PAL_SINT8_MIN (SCHAR_MIN)
#define PAL_SINT8_MAX (SCHAR_MAX)

typedef unsigned short PAL_Uint16;
#define PAL_UINT16_MAX (USHRT_MAX)

typedef signed short PAL_Sint16;
#define PAL_SINT16_MIN (SHRT_MIN)
#define PAL_SINT16_MAX (SHRT_MAX)

typedef unsigned int PAL_Uint32;
#define PAL_UINT32_MAX (UINT_MAX)

typedef signed int PAL_Sint32;
#define PAL_SINT32_MIN (INT_MIN)
#define PAL_SINT32_MAX (INT_MAX)

#if defined(_MSC_VER)
typedef unsigned __int64 PAL_Uint64;
typedef signed __int64 PAL_Sint64;
#else
typedef unsigned long long PAL_Uint64;
typedef signed long long PAL_Sint64;
#endif
#define PAL_UINT64_MIN ((PAL_Uint64)                    0ULL)
#define PAL_UINT64_MAX ((PAL_Uint64) 18446744073709551615ULL)
#define PAL_SINT64_MIN ((PAL_Sint64) (-9223372036854775807LL - 1LL))
#define PAL_SINT64_MAX ((PAL_Sint64)   9223372036854775807LL      )

typedef unsigned char PAL_Boolean;

#define PAL_TRUE ((PAL_Boolean)1)
#define PAL_FALSE ((PAL_Boolean)0)

/*
**==============================================================================
**
** Function calling conventions
**
**==============================================================================
*/

#ifdef _MSC_VER
# define PAL_CDECLAPI __cdecl
#else
# define PAL_CDECLAPI
#endif

#define ATEXIT_API PAL_CDECLAPI

/*
**==============================================================================
**
** SAL Notation for non-Windows platforms
**
**==============================================================================
*/

#if !defined(_MSC_VER)

# ifndef _In_
#  define _In_
# endif

# ifndef _Out_
#  define _Out_
# endif

# ifndef _Inout_
#  define _Inout_
# endif

# ifndef _Return_type_success_
#  define _Return_type_success_(x)
# endif

# ifndef _Acquires_lock_
#  define _Acquires_lock_(x)
# endif

# ifndef _Releases_lock_
#  define _Releases_lock_(x)
# endif

# ifndef _In_z_
#  define _In_z_
# endif

# ifndef _Post_z_
#  define _Post_z_
# endif

# ifndef _Out_writes_
#  define _Out_writes_(size)
# endif

# ifndef _Out_writes_z_
#  define _Out_writes_z_(size)
# endif

# ifndef _Null_terminated_
#  define _Null_terminated_
# endif

# ifndef _Use_decl_annotations_
#  define _Use_decl_annotations_
# endif

# ifndef _Out_opt_
#  define _Out_opt_
# endif

# ifndef _Deref_post_z_
#  define _Deref_post_z_
# endif

# ifndef _Inout_updates_z_
#  define _Inout_updates_z_(count)
# endif

# ifndef _Inout_opt_z_
#  define _Inout_opt_z_
# endif

# ifndef _Deref_prepost_opt_z_
#  define _Deref_prepost_opt_z_
# endif

# ifndef _In_opt_
#  define _In_opt_
# endif

# ifndef _In_opt_z_
#  define _In_opt_z_
# endif

# ifndef _Ret_maybenull_
#  define _Ret_maybenull_
# endif

# ifndef _Check_return_
#  define _Check_return_
# endif

# ifndef _Must_inspect_result_
#  define _Must_inspect_result_
# endif

# ifndef _Frees_ptr_opt_
#  define _Frees_ptr_opt_
# endif

# ifndef _Frees_ptr_
#  define _Frees_ptr_
# endif

# ifndef _Const_
#  define _Const_
# endif

# ifndef _Post_writable_byte_size
#  define _Post_writable_byte_size(size)
# endif

# ifndef _Analysis_assume_
#  define _Analysis_assume_(expr)
# endif

# ifndef _Always_
#  define _Always_(expr)
# endif

# ifndef _Outptr_
#  define _Outptr_
# endif

# ifndef _Outptr_result_buffer_
#  define _Outptr_result_buffer_(size)
# endif

# ifndef _Outptr_result_nullonfailure_
#  define _Outptr_result_nullonfailure_
# endif

# ifndef  _Maybenull_
#  define _Maybenull_
# endif

# ifndef _Notnull_
#  define _Notnull_
# endif

# ifndef _Valid_
#  define _Valid_
# endif

# ifndef _Analysis_noreturn_
#  define _Analysis_noreturn_
# endif

# ifndef _Ret_writes_maybenull_z_
#  define _Ret_writes_maybenull_z_(count)
# endif

# ifndef _String_length_
#  define _String_length_(str)
# endif

# ifndef _Success_
#  define _Success_
# endif

# ifndef _Field_range_
#  define _Field_range_(min, max)
# endif

# ifndef _In_range_
#  define _In_range_(min, max)
# endif

# ifndef _Field_size_
#  define _Field_size_(count)
# endif

# ifndef _Field_size_opt_
#  define _Field_size_opt_(count)
# endif

# ifndef _Field_size_full_opt_
#  define _Field_size_full_opt_(count)
# endif

# ifndef _Field_size_bytes_opt_
#  define _Field_size_bytes_opt_(size)
# endif

# ifndef _Readable_elements_
#  define _Readable_elements_(count)
# endif

# ifndef _Writable_elements_
#  define _Writable_elements_(count)
# endif

# ifndef _Struct_size_bytes_
#  define _Struct_size_bytes_(size)
# endif

# ifndef _At_
#  define _At_(target, annotation)
# endif

# ifndef _Pre_satisfies_
#  define _Pre_satisfies_(expr)
# endif

# ifndef _On_failure_
#  define _On_failure_(expr)
# endif

# ifndef _In_bytecount_
#  define _In_bytecount_(size)
# endif

# ifndef _Out_writes_bytes_to_opt_
#  define _Out_writes_bytes_to_opt_(buffLen, bufferNeeded)
# endif

# ifndef _When_
#  define _When_(expr, annotation)
# endif

# ifndef _Analysis_assume_nullterminated_
#  define _Analysis_assume_nullterminated_(expr)
# endif


#endif /* !defined(_MSC_VER) */

/*
**==============================================================================
**
** PAL_MAX_PATH_SIZE
**
**==============================================================================
*/

#define PAL_MAX_PATH_SIZE 1024

/*
**==============================================================================
**
** PAL_COUNT
**
**==============================================================================
*/

#ifdef _MSC_VER
# define PAL_COUNT(ARR) _countof(ARR)
#else
# define PAL_COUNT(ARR) (sizeof(ARR) / sizeof(ARR[0]))
#endif

/*
**==============================================================================
**
** PAL_Timestamp (equivalent to MI_Timestamp)
**
**     Represents a timestamp as described in the CIM Infrastructure
**     specification
**
**     [1] MI_ee DSP0004 (http://www.dmtf.org/standards/published_documents)
**
**==============================================================================
*/

typedef struct _PAL_Timestamp
{
    /* YYYYMMDDHHMMSS.MMMMMMSUTC */
    PAL_Uint32 year;
    PAL_Uint32 month;
    PAL_Uint32 day;
    PAL_Uint32 hour;
    PAL_Uint32 minute;
    PAL_Uint32 second;
    PAL_Uint32 microseconds;
    PAL_Sint32 utc;
}
PAL_Timestamp;

/*
**==============================================================================
**
** struct PAL_Interval (equivalent to MI_Interval)
**
**     Represents an interval as described in the CIM Infrastructure
**     specification. This structure is padded to have the same length
**     as a MI_Timestamp structure.
**
**     [1] MI_ee DSP0004 (http://www.dmtf.org/standards/published_documents)
**
**==============================================================================
*/

typedef struct _PAL_Interval
{
    /* DDDDDDDDHHMMSS.MMMMMM:000 */
    PAL_Uint32 days;
    PAL_Uint32 hours;
    PAL_Uint32 minutes;
    PAL_Uint32 seconds;
    PAL_Uint32 microseconds;
    PAL_Uint32 __padding1;
    PAL_Uint32 __padding2;
    PAL_Uint32 __padding3;
}
PAL_Interval;

/*
**==============================================================================
**
** struct PAL_Datetime (equivalent to MI_Datetime)
**
**     Represents a CIM datetime type as described in the CIM Infrastructure
**     specification. It contains a union of PAL_Timestamp and PAL_Interval.
**
**==============================================================================
*/

typedef struct _PAL_Datetime
{
    PAL_Uint32 isTimestamp;
    union
    {
        PAL_Timestamp timestamp;
        PAL_Interval interval;
    }
    u;
}
PAL_Datetime;

/*
**==============================================================================
**
** PAL_PREFETCH
**
**==============================================================================
*/

#if defined(_MSC_VER)
# define PAL_PREFETCH(p) ReadForWriteAccess(p)
#elif defined(CONFIG_HAVE_BUILTIN_PREFETCH)
# define PAL_PREFETCH(p) (__builtin_prefetch((const void*)p),*(p))
#else
# define PAL_PREFETCH(p) (*p)
#endif

/*
**==============================================================================
**
** PAL_STATIC_ASSERT
**
** Example usage:
**   PAL_STATIC_ASSERT(sizeof(MI_CompositeDisposable) == sizeof(CompositeDisposable))
**   (ensures that size of a public struct (with 3 reserved ptrdiff_t fields)
**    is the same as size of an internal struct)
**==============================================================================
*/

#define PAL_STATIC_ASSERT(condition) \
    typedef char _static_assert ## __LINE__ [(condition) ? 1 : -1]

/*
**==============================================================================
**
** PAL_tolower (same as tolower from C89's <ctype.h>, but operating on PAL_Char)
**
**==============================================================================
*/

PAL_INLINE PAL_Char PAL_tolower(PAL_Char c)
{
    if ((PAL_T('A') <= c) && (c <= PAL_T('Z')))
        c = (PAL_Char) ((int) (unsigned char) c + (PAL_T('a') - PAL_T('A')));
    return c;
}

/*
**==============================================================================
**
** va_copy and other non-C89 helpers for vararg handling
**
**==============================================================================
*/

#if defined(CONFIG_HAVE_VA_COPY)
    #define PAL_va_copy(dest, source) va_copy(dest, source)
#else
    #define PAL_va_copy(dest, source) ((dest) = (source))
#endif

PAL_BEGIN_EXTERNC

#if defined(_MSC_VER)
extern SECURITY_DESCRIPTOR g_SecurityDescriptor;
extern SECURITY_ATTRIBUTES g_SecurityAttributes;
#endif

PAL_END_EXTERNC

/*
**==============================================================================
**
** SystemMalloc()
** SystemCalloc()
** SystemRealloc()
** SystemFree()
** SystemStrdup()
** SystemWcsdup()
**
**==============================================================================
*/

PAL_BEGIN_EXTERNC

PAL_INLINE void* SystemMalloc(
    size_t size)
{
    return malloc(size);
}

PAL_INLINE void* SystemCalloc(
    size_t count,
    size_t size)
{
    return calloc(count, size);
}

PAL_INLINE void* SystemRealloc(
    void* ptr,
    size_t size)
{
    return realloc(ptr, size);
}

PAL_INLINE void SystemFree(
    void* ptr)
{
    free(ptr);
}

PAL_INLINE char* SystemStrdup(
    const char* str)
{
# if defined(_MSC_VER)
    return _strdup(str);
# else
    return strdup(str);
# endif
}


PAL_INLINE wchar_t* SystemWcsdup(
    const wchar_t* str)
{
# if defined(_MSC_VER)
    return _wcsdup(str);
# else
#  if defined(CONFIG_HAVE_WCSDUP)
    extern wchar_t* wcsdup(const wchar_t* str);
    return wcsdup(str);
#  else
    size_t len = wcslen(str);
    wchar_t* ptr = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
    if(ptr)
        memcpy(ptr, str, (len + 1) * sizeof(wchar_t));
    return ptr;
#  endif
# endif
}

PAL_END_EXTERNC

/*
**==============================================================================
**
** USE_ALLOCATOR
** USE_PAL_ATEXIT
**
**==============================================================================
*/

#if defined(CONFIG_ENABLE_DEBUG) && defined(CONFIG_OS_LINUX)
# define USE_ALLOCATOR
# define USE_PAL_ATEXIT
#endif

/*
**==============================================================================
**
** No Allocator:
**
**==============================================================================
*/

#if !defined(USE_ALLOCATOR)

# define PAL_Malloc SystemMalloc
# define PAL_Calloc SystemCalloc
# define PAL_Realloc SystemRealloc
# define PAL_Free SystemFree
# define PAL_Strdup SystemStrdup
# define PAL_Wcsdup SystemWcsdup

# if defined(CONFIG_ENABLE_WCHAR)
#  define PAL_Tcsdup SystemWcsdup
# else
#  define PAL_Tcsdup SystemStrdup
# endif

#endif /* !defined(USE_ALLOCATOR) */

/*
**==============================================================================
**
** Allocator:
**
**==============================================================================
*/

#if defined(USE_ALLOCATOR)

PAL_BEGIN_EXTERNC

# define ENABLE_ALLOC_FAULT_INJECTION
# define PAL_ALLOC_CALLSITE __FILE__, __LINE__, __FUNCTION__

typedef struct _AllocStats
{
    /* Number of bytes currently allocated */
    size_t usage;

    /* Peak memory usage (in bytes) */
    size_t peakUsage;

    /* Number of times memory was allocated */
    size_t numAllocs;

    /* Number of times memory was freed */
    size_t numFrees;
}
AllocStats;

AllocStats PAL_GetAllocStats();

void PAL_DumpAllocStats();

void PAL_DumpAllocList();

void PAL_DumpAllocInfo();

size_t PAL_GetBlocksAllocated();

void PAL_CheckBlocksAllocated(
    size_t oldBlocksAllocated,
    const char* file,
    size_t line,
    const char* function);

# define PAL_Malloc(size) __PAL_Malloc(PAL_ALLOC_CALLSITE, size)
void* __PAL_Malloc(
    const char* file,
    size_t line,
    const char* func,
    size_t size);

# define PAL_Calloc(count, size) __PAL_Calloc(PAL_ALLOC_CALLSITE, count, size)
void* __PAL_Calloc(
    const char* file,
    size_t line,
    const char* func,
    size_t count,
    size_t size);

# define PAL_Realloc(ptr, size) __PAL_Realloc(PAL_ALLOC_CALLSITE, ptr, size)
void* __PAL_Realloc(
    const char* file,
    size_t line,
    const char* func,
    void* ptr,
    size_t size);

# define PAL_Free(ptr) __PAL_Free(PAL_ALLOC_CALLSITE, ptr)
void __PAL_Free(
    const char* file,
    size_t line,
    const char* func,
    void* ptr);

#define PAL_Strdup(str) __PAL_Strdup(PAL_ALLOC_CALLSITE, str)
char* __PAL_Strdup(
    const char* file,
    size_t line,
    const char* func,
    const char* str);

#define PAL_Wcsdup(str) __PAL_Wcsdup(PAL_ALLOC_CALLSITE, str)
wchar_t* __PAL_Wcsdup(
    const char* file,
    size_t line,
    const char* func,
    const wchar_t* str);

#define PAL_Tcsdup(str) __PAL_Tcsdup(PAL_ALLOC_CALLSITE, str)
PAL_Char* __PAL_Tcsdup(
    const char* file,
    size_t line,
    const char* func,
    const PAL_Char* str);

PAL_END_EXTERNC

#endif /* defined(USE_ALLOCATOR) */

#if 0
# define malloc __malloc_undefined__
# define calloc __calloc_undefined__
# define realloc __realloc_undefined__
# define free __free_undefined__
# define strdup __strdup_undefined__
# define wcsdup __wcsdup_undefined__
#endif

/*
**==============================================================================
**
** PAL_Atexit()
** PAL_AtexitCall()
**
**==============================================================================
*/

#if defined(USE_PAL_ATEXIT)

# define PAL_ATEXIT_MAX 32

PAL_BEGIN_EXTERNC

/* Install an at-exit function (to be called on exit() */
int PAL_Atexit(void (*func)());

/* Call all the at-exit funcs now */
int PAL_AtexitCall();

PAL_END_EXTERNC

#else /* defined(USE_PAL_ATEXIT) */
# define PAL_Atexit atexit
#endif /* defined(USE_PAL_ATEXIT) */

#endif /* _pal_palcommon_h */
