/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/


#ifndef __FRAME_H__
#define __FRAME_H__

#ifndef _MSC_VER
#include "../../common/linux/sal.h"
#endif

#include "config.h"

#if defined(CONFIG_HAVE_BACKTRACE)

//Process-Independent Stack Frames
//--------------------------------
//Represents a single stack frame.
struct Frame
{
    unsigned key;
};

//Intra-Process Module Mapping
//----------------------------
//Maps process-local code addresses into Frame objects.
struct LocalModule
{
    size_t base;
    size_t end;
};

struct GlobalModule
{
    unsigned base;
    unsigned size;
    char name[MAX_PATH];
};

//Stack Frame Cache
//---------------------------------
//Efficiently gathers and checks fault injection information for large numbers
//of stack frames across a test run.
class FrameCache
{
public:
    //Call this function only if willing to generate more faults!
    bool ShouldFault(ptrdiff_t limit, ptrdiff_t attempt, _Out_ bool &filtered);

    //Call at the beginning of the test run to reset history.
    void Reset();

private:
    enum {
        CacheSize = 65536, //Must be a power of 2.
        CacheLastSection = CacheSize / 2,
        ModuleCount = 1024,
        DesiredFrames = 32,
        SkippedFrames = 4,
        ModuleChunk = 4194304,
        ModuleChunkMask = ModuleChunk - 1,
        HashSize = 8192, //Must be a power of 2.
        HashMask = HashSize - 1
    };

    unsigned m_dataUsed;
    unsigned m_modulesUsed;
    unsigned m_addressUsed;
    unsigned m_startMask;
    volatile ptrdiff_t m_spinlock;

    //Intended for cross-process shared memory use.
    GlobalModule m_modules[ModuleCount];
    Frame        m_data[CacheSize];

    //Process-local hash table.
    static size_t s_hash[HashSize];

    //Process-local module data.
    static LocalModule s_modules[ModuleCount];

    unsigned TranslateAddress(_In_ void *pointer);
    unsigned FindModule(_In_z_ char *name, unsigned size);

    void InsertRecord(unsigned key);

    bool FindRecord(unsigned key);

    void MergeRecords(int low, int src, int size);

    bool BinarySearch(unsigned key, int low, int high);
};

#endif

#endif
