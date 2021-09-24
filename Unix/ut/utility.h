/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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

// time functionality
typedef unsigned long long uint64;
uint64 time_now();

inline unsigned short getUnittestPortNumber()
{
    return 10000 + ((geteuid() % 200) * 200);
}

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
