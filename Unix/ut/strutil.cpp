/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "ut.h"
#include "strutil.h"

using namespace std;

namespace ut
{

std::string StrToChar(const String& str)
{
    string res;

    res.resize(str.size());
    for (size_t i = 0; i < str.size(); i++)
    {
        res[i] = (char)str[i];
    }
    return res;
}

void StringToArray(const ZChar* str, std::vector<String>& res, ZChar delim /*= ','*/)
{
    String line = str;
    String::size_type pos = line.find( delim );

    while ( pos != String::npos ){
        res.push_back(line.substr( 0, pos ));
        line.erase( 0, pos + 1 );
        pos = line.find( delim );
    }
    
    // last item - if it's not empty
    if (!line.empty() )
        res.push_back( line );
}

String ArrayToString(const std::vector<String>& ar)
{
    String res;

    for (size_t i = 0; i < ar.size(); i++)
    {
        res += ar[i];

        if ((i+1) < ar.size())
            res += ZT(",");
    }

    return res;
}

}

