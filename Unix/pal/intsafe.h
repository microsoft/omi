#ifndef _intsafe_h
#define _intsafe_h

#include "palcommon.h"

PAL_BEGIN_EXTERNC

#define INTSAFE_E_ARITHMETIC_OVERFLOW   ((HRESULT)0x80070216L)  // 0x216 = 534 = ERROR_ARITHMETIC_OVERFLOW
#define _SIZE_T_ERROR   0xffffffff

#ifndef SIZE_MAX
# ifdef PAL_64BIT
#  define SIZE_MAX (18446744073709551615UL)
# else
#  define SIZE_MAX (4294967295U)
# endif
#endif

PAL_INLINE HRESULT
SizeTAdd(
    _In_ size_t Augend,
    _In_ size_t Addend,
    _Out_ _Deref_out_range_(==, Augend + Addend) size_t* pResult)
{
    HRESULT hr;

    if ((Augend + Addend) >= Augend)
    {
        *pResult = (Augend + Addend);
        hr = S_OK;
    }
    else
    {
        *pResult = _SIZE_T_ERROR;
        hr = INTSAFE_E_ARITHMETIC_OVERFLOW;
    }
    return hr;
}

PAL_INLINE HRESULT
SizeTMult(
    _In_ size_t Multiplicand,
    _In_ size_t Multiplier,
    _Out_ _Deref_out_range_(==, Multiplicand * Multiplier) size_t* pResult)
{
    HRESULT hr;
    if (Multiplier == 0 || Multiplicand == 0 || Multiplicand <= SIZE_MAX / Multiplier)
    {
        *pResult = Multiplicand * Multiplier;
        hr = S_OK;
    }
    else
    {
        *pResult = _SIZE_T_ERROR;
        hr = INTSAFE_E_ARITHMETIC_OVERFLOW;
    }
    return  hr;
}

PAL_END_EXTERNC

#endif /* _intsafe_h */
