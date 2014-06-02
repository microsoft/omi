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

