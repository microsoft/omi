/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
