/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "ut.h"
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>

#ifdef ZT
#undef ZT
#endif

using namespace std;

namespace ut
{

static FILE* File_Open(const char* path, const char* mode)
{
    return fopen(path, mode);
}


bool readFileContent( const std::string& file, std::vector< unsigned char >& content )
{
    FILE* f = File_Open(file.c_str(), "r");
    if ( !f )
        return false;

    content.resize( 1024 * 64 );
    size_t res = fread(&content[0], 1, content.size(), f );
    fclose(f);
    content.resize( res );
    return true;
}


bool writeFileContent( const std::string& file, const std::vector< unsigned char >& content )
{
    if (content.empty())
        return false;

    FILE* f = File_Open(file.c_str(), "w");
    if ( !f )
        return false;

    size_t res = fwrite(&content[0], 1, content.size(), f );
    fclose(f);
    return res == content.size();
}


// looks for a file; 
// start_dir - can be null (use curent directory); should be provided if test is playing with current directory
// sub_directory - related to unittet directory - for example "tools/mof"
// file - file name
std::string findSampleFile(const char* start_directory, const char* sub_directory, const char* file)
{
    string starting_dir( start_directory ? (string(start_directory) + "/") : string());

    string res = starting_dir + file;

    if ( access(res.c_str(), F_OK) == 0 )
      return res;

    res = starting_dir + string(sub_directory);
    res += file;

    if ( access(res.c_str(), F_OK) == 0 )
      return res;

    res = starting_dir + "../../../../unittest/" + sub_directory;
    res += file;

    if ( access(res.c_str(), F_OK) == 0 )
      return res;

    UT_ASSERT_FAILED_MSG( string(string("file not found: ") + file).c_str() );
    return string();
}


static void removeAllCharsFromArray(vector< unsigned char >& content, unsigned char c)
{
    for( size_t i = 0; i < content.size(); )
    {
        if ( content[i] == c )
            content.erase(content.begin() + i);
        else
            i++;
    }
}

// compare two files; return true if they match; asserts otherwise
bool compareFiles( const char* file1, const char* file2, bool ignore_win_cr /* = true */ )
{
    vector< unsigned char > content1, content2;

    UT_ASSERT(readFileContent( file1, content1 ));
    UT_ASSERT(readFileContent( file2, content2 ));

    if ( ignore_win_cr )
    {
        removeAllCharsFromArray(content1, '\r');
        removeAllCharsFromArray(content2, '\r');
    }

    if ( content1 != content2 )
    {
#if defined(CONFIG_POSIX)
        string cmd = "diff ";
        cmd += file1;
        cmd += " ";
        cmd += file2;
        UT_ASSERT(system(cmd.c_str()) != -1);
#endif
        UT_ASSERT_FAILED_MSG( string(
            string("files ") + file1 + " and " + file2 + " are different" ).c_str() );
    }
    return true;
}

// copy 'src' to 'tgt'; return true if successful
bool copyFile( const char* targetFile, const char* sourceFile )
{
    vector< unsigned char > content;
    UT_ASSERT(readFileContent( sourceFile, content ));
    UT_ASSERT(writeFileContent( targetFile, content ));
    return true;
}

// removes file if it exists
void removeIfExist( const char* file )
{
    if ( access(file, F_OK) == 0 )
        UT_ASSERT( 0 == remove(file) );
}

void sleep_sec(MI_Uint64 sec)
{
    sleep_ms(sec * 1000);
}

void sleep_ms(MI_Uint64 ms_sec)
{
    struct timespec rqtp;

    rqtp.tv_sec = static_cast<long>(ms_sec/1000);
    rqtp.tv_nsec = static_cast<long>((ms_sec%1000)*1000*1000);

    nanosleep(&rqtp, NULL);
}

uint64 time_now()
{
    struct timeval tv;
    struct timezone tz;
    memset(&tv, 0, sizeof(tv));
    memset(&tz, 0, sizeof(tz));

    if (gettimeofday(&tv, &tz) != 0)
        return 0;

    return ((MI_Uint64)tv.tv_sec * (MI_Uint64)1000000 + (MI_Uint64)tv.tv_usec);
}

}
