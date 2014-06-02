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

//==============================================================================
//
// strutil.h : provides helper macro/classes for statik string wrappers
//
//==============================================================================

#ifndef _strutil_h
#define _strutil_h

#include <string>
#include <vector>
#include <MI.h>

namespace ut
{
#if (MI_CHAR_TYPE == 1)
    typedef std::string String;
#else
    typedef std::wstring String;
#endif

    // primitive converion of ZChar to char - mostly for debugging printouts
    std::string StrToChar(const String& str);

    // array <--> string converions like "A,B,C" <-> ["A","B","C"]
    void StringToArray(
        const ZChar* str, 
        std::vector<String>& res, 
        ZChar delim = ',');

    String ArrayToString(
        const std::vector<String>& ar);
};

#endif /* _strutil_h */
