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

#ifndef _ut_utility_h
#define _ut_utility_h

#include <vector>
#include <string>
#include "ut.h"
#include <common.h>

#if defined(CONFIG_POSIX)
# include <unistd.h>
#elif defined(CONFIG_OS_WINDOWS)
#endif

namespace ut
{
// collection of utility functions


static inline int _StrToFalse(const char*)
{
    return 0;
}

bool readFileContent( const std::string& file, std::vector< unsigned char >& content );

bool writeFileContent( const std::string& file, const std::vector< unsigned char >& content );

// looks for a file; 
// start_dir - can be null (use curent directory); should be provided if test is playing with current directory
// sub_directory - related to unittet directory - for example "tools/mof"
// file - file name
// reutrns file if found or ASSERTs otherwise
std::string findSampleFile(const char* start_dir, const char* sub_directory, const char* file);


// compare two files; return true if they match; asserts otherwise
bool compareFiles( const char* generatedFile, const char* sampleFile, bool ignore_win_cr = true );

inline bool compareFiles(
    const std::string& generatedFile, 
    const std::string& sampleFile, 
    bool ignore_win_cr = true)
{
    return compareFiles(
        generatedFile.c_str(), sampleFile.c_str(), ignore_win_cr);
}

// copy 'src' to 'tgt'; return true if successful
bool copyFile( const char* targetFile, const char* sourceFile );

inline bool copyFile(
    const std::string& destFile, 
    const std::string& srcFile)
{
    return copyFile(destFile.c_str(), srcFile.c_str());
}

void removeIfExist( const char* file );


// sleep - all variations
void sleep_sec(MI_Uint64 sec);
void sleep_ms(MI_Uint64 ms_sec);

// time funcitonality
#if defined(_MSC_VER)
typedef unsigned __int64 uint64;
#else
typedef unsigned long long uint64;
#endif
uint64 time_now();

#if defined(_MSC_VER)
inline unsigned short getUnittestPortNumber()
{
    return 21718;
}
#else
inline unsigned short getUnittestPortNumber()
{
    return 10000 + ((geteuid() % 200) * 200);
}
#endif

inline unsigned short getUnittestPortNumberWSMANHTTP()
{
    std::string v;

    if (ut::testGetAttr("skipServer", v))
    {
        return 7778;
    }

    return getUnittestPortNumber() + 198;
}
inline unsigned short getUnittestPortNumberWSMANHTTPS()
{
    return getUnittestPortNumber() + 197;
}

};

#endif /* _ut_utility_h */
