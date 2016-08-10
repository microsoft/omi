/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _tests_indication_util_h
#define _tests_indication_util_h

#include <indication/indimgr/cimbase.h>

BEGIN_EXTERNC

class CimBaseAutoRelease
{
public:
    CimBaseAutoRelease(_In_ CimBase* obj);
    ~CimBaseAutoRelease();

private:
    CimBaseAutoRelease(const CimBaseAutoRelease&);
    CimBaseAutoRelease& operator=(const CimBaseAutoRelease&);
    CimBase* m_cimbase;
};

typedef struct _StringTagElement
{
    MI_ConstString element;
    MI_Uint32 tag;
    MI_Uint32 reserved1;
}StringTagElement;

/*
 *   Return value:
 *      0 - string NOT in array
 *      > 0 - string in array, and return number of times searched
 */
MI_Uint32 IsInArray(
    _In_z_ MI_ConstString str,
    _Inout_count_(size) StringTagElement* strarr,
    _In_ MI_Uint32 size);

/*
 *   Return value:
 *      NULL - string NOT in array
 *      Non-NULL - string in array, and return the element
 */
StringTagElement* IsInArrayEx(
    _In_z_ MI_ConstString str,
    _Inout_count_(size) StringTagElement* strarr,
    _In_ MI_Uint32 size);

END_EXTERNC

#endif /* _tests_indication_util_h */

