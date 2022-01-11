/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

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

/* StrTcslcat and StrTcslcpy */
#define DEST char
#define SRC TChar
#define STRLCAT StrTcslcat
#define STRLCPY StrTcslcpy
#include "strlcat.h"
#include "strlcpy.h"
#undef STRLCAT
#undef STRLCPY
#undef DEST
#undef SRC

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

#if !defined(CONFIG_FAVORSIZE)

// The following defines string literals for the numbers 0 through 63. The
// first character is the length of the string. The subsequent characters
// are the string literal itself.
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

#endif /* !defined(CONFIG_FAVORSIZE) */

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

