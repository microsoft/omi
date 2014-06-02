
#include "strings.h"

/* Strlcat and Strlcpy */
#define DEST char
#define SRC char
#define STRLCAT Strlcat
#define STRLCPY Strlcpy
#include "strlcat.h"
#include "strlcpy.h"
#undef STRLCAT
#undef STRLCPY
#undef DEST
#undef SRC

/* Wcslcat and Wcslcpy */
#define DEST wchar_t
#define SRC wchar_t
#define STRLCAT Wcslcat
#define STRLCPY Wcslcpy
#include "strlcat.h"
#include "strlcpy.h"
#undef STRLCAT
#undef STRLCPY
#undef DEST
#undef SRC

/* StrWcslcat and StrWcslcpy */
#define DEST char
#define SRC wchar_t
#define STRLCPY StrWcslcpy
#include "strlcpy.h"
#undef STRLCPY
#undef DEST
#undef SRC

/* WcsStrlcat and WcsStrlcpy */
#define DEST wchar_t
#define SRC char
#define STRLCPY WcsStrlcpy
#include "strlcpy.h"
#undef STRLCPY
#undef DEST
#undef SRC

/* TcsStrlcat and TcsStrlcpy */
#define DEST TChar
#define SRC char
#define STRLCAT TcsStrlcat
#define STRLCPY TcsStrlcpy
#include "strlcat.h"
#include "strlcpy.h"
#undef STRLCAT
#undef STRLCPY
#undef DEST
#undef SRC

// OACR just doesn't get that the length of *result will be in *size
// disabling this warning
#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast (disable: 28196)
#endif

_Post_satisfies_(*size == _String_length_(*result))
void TcsFromUInt64(_Pre_writable_size_(64) PAL_Char buf[64], PAL_Uint64 value, _Outptr_result_z_ const PAL_Char **result, _Out_opt_ size_t* size)
{
    PAL_Char* p;

    p = &buf[63];
    *p = PAL_T('\0');

    do
    {
        *--p = PAL_T('0') + value % 10;
    }
    while (value /= 10);

    *result = p;

    if(size)
    {
        *size = (PAL_Sint32)(&buf[63] - p);
    }
}

#ifdef _MSC_VER
#pragma prefast(pop)
#endif

#if !defined(CONFIG_FAVORSIZE)

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4125 )
#endif

// The following defines string literals for the numbers 0 through 63. The
// first character is the length of the string. The subsequent characters
// are the string literal iteslf.
static const char* _numberStrings[] =
{
    "\0010",
    "\0011",
    "\0012",
    "\0013",
    "\0014",
    "\0015",
    "\0016",
    "\0017",
    "\0018",
    "\0019",
    "\00210",
    "\00211",
    "\00212",
    "\00213",
    "\00214",
    "\00215",
    "\00216",
    "\00217",
    "\00218",
    "\00219",
    "\00220",
    "\00221",
    "\00222",
    "\00223",
    "\00224",
    "\00225",
    "\00226",
    "\00227",
    "\00228",
    "\00229",
    "\00230",
    "\00231",
    "\00232",
    "\00233",
    "\00234",
    "\00235",
    "\00236",
    "\00237",
    "\00238",
    "\00239",
    "\00240",
    "\00241",
    "\00242",
    "\00243",
    "\00244",
    "\00245",
    "\00246",
    "\00247",
    "\00248",
    "\00249",
    "\00250",
    "\00251",
    "\00252",
    "\00253",
    "\00254",
    "\00255",
    "\00256",
    "\00257",
    "\00258",
    "\00259",
    "\00260",
    "\00261",
    "\00262",
    "\00263",
};
#if defined(_MSC_VER)
#pragma warning( pop )
#endif

#endif /* !defined(CONFIG_FAVORSIZE) */

#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast (disable: 28196)
#endif

_Post_satisfies_(*size == _String_length_(*result))
void Uint64ToStr(_Pre_writable_size_(21) char buf[21], PAL_Uint64 value, _Outptr_result_z_ const char **result,  _Out_opt_ size_t* size)
{
    char* p;        
        
#if !defined(CONFIG_FAVORSIZE)

    if (value < 64)
    {
        if(size)
        {
            *size = _numberStrings[value][0];
        }
        *result = &_numberStrings[value][1];
    }

#endif /* !defined(CONFIG_FAVORSIZE)*/

    p = &buf[20];
    *p = '\0';

    do
    {
        *--p = '0' + value % 10;
    }
    while (value /= 10);

    if(size)
    {
        *size = &buf[20] - p;
    }

    *result = p;
}

#ifdef _MSC_VER
#pragma prefast(pop)
#endif


_Use_decl_annotations_
const char* Uint32ToStr(char buf[11], PAL_Uint32 x, size_t* size)
{
    char* p;

#if !defined(CONFIG_FAVORSIZE)

    if (x < 64)
    {
        *size = _numberStrings[x][0];
        return &_numberStrings[x][1];
    }

#endif /* !defined(CONFIG_FAVORSIZE)*/

    p = &buf[10];
    *p = '\0';

    do
    {
        *--p = '0' + x % 10;
    }
    while (x /= 10);

    *size = &buf[10] - p;
    return p;
}

#if defined(CONFIG_ENABLE_WCHAR)
_Use_decl_annotations_
const TChar* Uint32ToZStr(TChar buf[11], PAL_Uint32 x, size_t* size)
{
    TChar* p = &buf[10];
    *p = '\0';

    do
    {
        *--p = '0' + x % 10;
    }
    while (x /= 10);

    *size = &buf[10] - p;
    return p;
}
#endif

#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast (disable: 28196)
#endif

#if defined(CONFIG_ENABLE_WCHAR)

_Post_satisfies_(*size == _String_length_(*result))
void Uint64ToZStr(_Pre_writable_size_(21) TChar buf[21], PAL_Uint64 value, _Outptr_result_z_ const TChar **result,  _Out_opt_ size_t* size)
{
    TChar* p = &buf[20];
    *p = PAL_T('\0');

    do
    {
        *--p = PAL_T('0') + value % 10;
    }
    while (value /= 10);

    if(size)
    {
        *size = &buf[20] - p;
    }
    *result = p;
}
#endif

_Post_satisfies_(*size == _String_length_(*result))
void Sint64ToZStr(_Pre_writable_size_(64) TChar buf[64], PAL_Sint64 value, _Outptr_result_z_ const TChar **result, _Out_opt_ size_t* size)
{
    TChar* p;

    PAL_Boolean isNegative = PAL_FALSE;    
    if(value < 0)
    {
        isNegative = 1;
        value = -value;
    }

    p = &buf[63];
    *p = PAL_T('\0');

    do
    {
        *--p = PAL_T('0') + value % 10;
    }
    while (value /= 10);

    if(isNegative)
    {
        *--p = PAL_T('-');
    }

    if(size)
    {
        *size = (PAL_Sint32)(&buf[63] - p);
    }

    *result = p;
}

#if !defined(CONFIG_HAVE_WCSCASECMP)

int wcsncasecmp(const wchar_t* s1, const wchar_t* s2, size_t n)
{
    wchar_t s1Char, s2Char;
    const wchar_t *end = s1 + n - 1;
    if(!s1 || !s2)
        return -1;

    while(s1 <= end)
    {
        s1Char = PAL_tolower(*s1);
        s2Char = PAL_tolower(*s2);
        if(s1Char != s2Char)
            return (int)(s1Char - s2Char);
        s1++;
        s2++;
    }
    return 0;
}

int wcscasecmp(const wchar_t* s1, const wchar_t* s2)
{
    wchar_t s1Char, s2Char;
    if(!s1 || !s2)
        return -1;

    while(*s1 && *s2)
    {
        s1Char = PAL_tolower(*s1);
        s2Char = PAL_tolower(*s2);
        if(s1Char != s2Char)
            return (int)(s1Char - s2Char);
        s1++;
        s2++;
    }

    return (int)((unsigned int)*s1 - (unsigned int)*s2);    
}
#endif

#if !defined(CONFIG_HAVE_WCSTOLL)
#include <errno.h>

PAL_INLINE int __WcsToll_GetDigitValue(wchar_t c, int b)
{
    int result = -1;
    if(c >= L'0' && c <= L'9')
    {
        result = (int)(c - L'0');
    }
    else if(c >= L'A' && c <= L'Z')
    {
        result = 10 + (int)(c - L'A');
    }
    else if(c >= L'a' && c <= L'z')
    {
        result = 10 + (int)(c - L'a');
    }

    if((result != -1) && (result >= b))
    {
        result = -1;
    }

    return result;
}

long long wcstoll(const wchar_t* s, wchar_t** e, int b)
{
    PAL_Boolean isNegative = PAL_FALSE;
    double value = 0;
    int curDigit = 0;
    
    if(!s)
        goto Error_EINVAL;

    /* rejecting invalid base */
    if((b < 0) || (b == 1) || (b > 36))
        goto Error_EINVAL;

    /* moving past any spaces */
    while(*s && iswspace(*s))
        s++;

    /* Making sure string doesnt end here */
    if(!(*s))
        goto Error_EINVAL;

    /* check if this is -ve number */
    if(*s == L'-')
    {
        isNegative = PAL_TRUE;
        s++;
    }

    /* check if this is +ve number */
    if(*s == L'+')
        s++;

    /* check if this is octal/hex number */
    if(*s == L'0')
    {  
        s++;
        if((*s == L'x') || (*s == L'X'))
        {
            s++;

            if((b == 0) || (b == 16))
                b = 16;
            else
                goto Error_EINVAL;
        }
        else
        {
            if((b == 0) || (b == 8))
                b = 8;
            else
                goto Error_EINVAL;
        }
    }

    /* if base is 0 still; we set it to 10 */
    if(b == 0)
        b = 10;

    if(__WcsToll_GetDigitValue(*s, b) < 0)
        goto Error_EINVAL;

    while(*s)
    {
        curDigit = __WcsToll_GetDigitValue(*s, b);
        if(curDigit < 0)
        {
            goto End;
        }

        value = (value * b) + curDigit;
        
        if(value > PAL_SINT64_MAX)
        {
            goto Error_ERANGE;
        }

        if(isNegative && ((-1) * (value)) < PAL_SINT64_MIN)
        {
            goto Error_ERANGE;
        }

        s++;
    }

    goto End;

Error_EINVAL:    
    errno = EINVAL;
    goto End;
Error_ERANGE:
    errno = ERANGE;
    goto End;
End:
    if(e)
    {        
        *e = (wchar_t *)s;                
    }
    return (long long)value;
}
#endif

#if defined(CONFIG_ENABLE_WCHAR)

/*----------------------------------------------------------------------------*/
/**
Convert a UTF-32 string to a UTF-8 string

Anticipated usage of this is that it will be a 2-pass use where first pass computes the length
and second pass just does the conversion; the firstNonAscii is variable is kind of used as a state variable between the two passes
to optimize conversion of single byte strings; but it is optional if you do not want to use it

\param [in]     utf32  the UTF-32 string
\param [out]    _size  the number of words in the string
\param [inout]  firstNonAscii  the position in utf8 of the first non-ASCII character; 
\param [out]    utf8   the UTF-8 string; NULL for the first (evaluation) pass
\param [in] utf8Size size of the utf8 buffer
\returns        the size of the converted string
*/

#if defined(_MSC_VER)

int ConvertWideCharToUtf8Windows(
            const Utf32Char* utf32,
            size_t utf32Size,
            size_t* firstNonAscii,            
            Utf8Char* utf8,
            int utf8Size)
{        
    int lastError = 0;  
    PAL_UNUSED(firstNonAscii);

    if(utf8 == NULL)
        utf8Size = WideCharToMultiByte(CP_UTF8, 0, utf32, utf32Size, NULL, 0, NULL, NULL);
    else
        utf8Size = WideCharToMultiByte(CP_UTF8, 0, utf32, utf32Size, (LPSTR)utf8, utf8Size, NULL, NULL);

    return utf8Size;
}

#else


int ConvertWideCharToUtf8NonWindows(
            const Utf32Char* utf32,
            size_t utf32Size,
            size_t* firstNonAscii,
            Utf8Char* utf8,
            int utf8Size)
{       
    Utf32Char c;
    Utf8Char* p = utf8;    
    const Utf8Char INVALID_CHAR = '?';
    const Utf32Char CODE_POINT_MAXIMUM_VALUE = 0x10FFFF;
    // turn off the ASCII-only code for the first pass
    size_t firstNonAsciiChar = utf8 == NULL ? 0 : (firstNonAscii ? *firstNonAscii : 0);
    size_t pos = 0;

    PAL_UNUSED(utf8Size);
    
    // do the ASCII-only conversion for the beginning characters on the second pass
    for (pos = 0; pos < firstNonAsciiChar; pos++)
    {
        *p++ = (Utf8Char)*(utf32 + pos);
    }

    // If this is the first pass or firstNonAsciiChar < utf32Size, handle the
    // rest of the string, which includes multi-byte characters.  If the
    // string was found to be pure ASCII on the first pass, this is never
    // executed on the second pass
    if(firstNonAscii) 
        *firstNonAscii = utf32Size;
    for (pos = firstNonAsciiChar; pos < utf32Size; pos++)
    {
        c = *(utf32 + pos);
        if (c < 0x0080)
        {                               // an ASCII character
            if (utf8 != NULL)
                *p = (Utf8Char)c;
            p++;
        }
        else
        {
            if (firstNonAscii)
            {
                if(pos < *firstNonAscii)
                    *firstNonAscii = pos;
            }

            if (c < 0x0800)
            {                           // a 2-byte character
                if (utf8 != NULL)
                {
                    *p = (Utf8Char)((c >> 6) | 0x00C0);
                    *(p + 1) = (Utf8Char)((c & 0x003F) | 0x0080);
                }
                p += 2;
            }
            else if (c <= 0x00010000)
            {                           // a 3-byte character
                if (utf8 != NULL)
                {
                    *p = (Utf8Char)(((c >> 12) & 0x0000000F) | 0x000000E0);
                    *(p + 1) = (Utf8Char)(((c >> 6) & 0x0000003F) | 0x00000080);
                    *(p + 2) = (Utf8Char)((c & 0x0000003F) | 0x00000080);
                }
                p += 3;
            }
            else if(c <= CODE_POINT_MAXIMUM_VALUE)
            {                           // a 4-byte character
                if (utf8 != NULL)
                {
                    *p = (Utf8Char)(((c >> 18) & 0x00000007) | 0x000000F0);
                    *(p + 1) = (Utf8Char)(((c >> 12) & 0x0000003F) | 0x00000080);
                    *(p + 2) = (Utf8Char)(((c >> 6) & 0x0000003F) | 0x00000080);
                    *(p + 3) = (Utf8Char)((c & 0x0000003F) | 0x00000080);
                }
                p += 4;
            }
            else
            {
                if (utf8 != NULL)
                    *p = INVALID_CHAR; /* In this case, if the conversion can not find the character, it will put an invalid character in the result */
                p++;
            }
        }
    }

    return (int)(p - utf8);
}

#endif

int ConvertWideCharToMultiByte(
            const Utf32Char* utf32,
            size_t utf32Size,
            size_t* firstNonAscii,
            Utf8Char* utf8,
            int utf8Size)
{
#if defined(_MSC_VER)
    return ConvertWideCharToUtf8Windows(utf32, utf32Size, firstNonAscii, utf8, utf8Size);
#else
    return ConvertWideCharToUtf8NonWindows(utf32, utf32Size, firstNonAscii, utf8, utf8Size);
#endif
}
#endif
