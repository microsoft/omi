#ifndef _intsafe_h
#define _intsafe_h

#include "palcommon.h"

PAL_BEGIN_EXTERNC

PAL_INLINE HRESULT
SizeTAdd(
    _In_ size_t Augend,
    _In_ size_t Addend,
    _Out_ size_t* pResult)
{
    *pResult = (Augend + Addend);
    return S_OK;
}

PAL_INLINE HRESULT
SizeTMult(
    _In_ size_t Multiplicand,
    _In_ size_t Multiplier,
    _Out_ size_t* pResult)
{
    *pResult = Multiplicand * Multiplier;
    return S_OK;
}

PAL_END_EXTERNC

#endif /* _intsafe_h */
