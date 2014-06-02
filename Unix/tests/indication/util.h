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

