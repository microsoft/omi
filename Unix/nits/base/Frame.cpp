#include "config.h"

#if defined(CONFIG_HAVE_BACKTRACE)

#define PSAPI_VERSION 2

#ifdef _MSC_VER
    #include <windows.h>
    #include <psapi.h>
    #include <strsafe.h>
#else
    #include <execinfo.h>
    #include <dlfcn.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

#include "Globals.h"
#include "Frame.h"
#include <pal/strings.h>

using namespace TestSystem;

LocalModule FrameCache::s_modules[FrameCache::ModuleCount];
size_t FrameCache::s_hash[HashSize];

void FrameCache::Reset()
{
	m_spinlock = 0;
    m_dataUsed = 0;
    m_modulesUsed = 0;
    m_addressUsed = 0;
    m_startMask = 0;
}

bool FrameCache::ShouldFault(ptrdiff_t limit, ptrdiff_t attempt, _Out_ bool &filtered)
{
    Atomic_Lock(&m_spinlock);

    //unsigned __int64 start = ReadTimeStampCounter();
    int count = 0;
    void **stackFrames = NULL;
#ifdef _MSC_VER
    void *actualStackFrames[DesiredFrames];
    count = CaptureStackBackTrace(SkippedFrames, DesiredFrames, actualStackFrames, NULL);
    stackFrames = actualStackFrames;
#else
    // backtrace does not let you specify skippedFrames, so here I am grabbing (SkippedFrames + DesiredFrames) 
    // and then skipping the unneeded frames myself to have same behaviour both on windows and non-windows 
    void *actualStackFrames[SkippedFrames + DesiredFrames];
    count = backtrace(actualStackFrames, DesiredFrames + SkippedFrames);
    stackFrames = actualStackFrames + SkippedFrames;
    count = count - SkippedFrames;
#endif

    bool shouldFault = false;
    filtered = false;

    GetGlobals().GetStats().stackLookups++;
    GetGlobals().GetStats().frameLookups += count;

    //Process-local frame hash (avoids translation).
    int newCount = 0;
    for (int i = 0; i < count; i++)
    {
        size_t address = reinterpret_cast<size_t>(stackFrames[i]);
        int hash = static_cast<int>(address & HashMask);
        if (s_hash[hash] != address)
        {
            //Don't update the table yet.
            //We may or may not actually fault this location.
            stackFrames[newCount++] = reinterpret_cast<void *>(address);
        }
    }
    GetGlobals().GetStats().frameHashHits += (count - newCount);
    count = newCount;

    for (int i = 0; i < count; i++)
    {
        size_t address = reinterpret_cast<size_t>(stackFrames[i]);
        int hash = static_cast<int>(address & HashMask);
        unsigned key = TranslateAddress(stackFrames[i]);
        if (!FindRecord(key))
        {
            //If the attempt number is less than the previous one,
            //  then this could be orphaned code.
            if (attempt >= limit)
            {
                //Make sure the process-local hash table is updated.
                s_hash[hash] = address;
                shouldFault = true;
                InsertRecord(key);
            }
            else
            {
                filtered = true;
            }
        }
        else
        {
            //Make sure the process-local hash table is updated.
            s_hash[hash] = address;
        }
    }

    //unsigned __int64 stop = ReadTimeStampCounter();
    //GetGlobals().GetStats().stackTicks += static_cast<unsigned>(stop - start);
    Atomic_Unlock(&m_spinlock);
    return shouldFault;
}

unsigned FrameCache::TranslateAddress(_In_ void *pointer)
{
    size_t address = reinterpret_cast<size_t>(pointer);
    unsigned i;

    //First check already known address ranges.
    for (i = 0; i < m_modulesUsed; i++)
    {
        LocalModule &local = s_modules[i];
        if (address >= local.base && address < local.end)
        {
            break;
        }
    }

    if (i == m_modulesUsed)
    {
    	char buffer[MAX_PATH] = "<unknown>";
    	DWORD sizeOfImage = 0;
    	void *baseOfDll = 0;
#ifdef _MSC_VER
        //Determine which module name this address belongs to.
        HMODULE handle;
        MODULEINFO info;

        if (!GetModuleHandleEx(
                    GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                    GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                    reinterpret_cast<LPCTSTR>(address),
                    &handle))
        {
            return 0;
        }

        GetModuleFileNameA(handle, buffer, sizeof(buffer));
        K32GetModuleInformation(GetCurrentProcess(), handle, &info, sizeof(info));
        sizeOfImage = info.SizeOfImage;
        baseOfDll = info.lpBaseOfDll;
#else
        Dl_info myDlInfo;        
        if(!dladdr(pointer, &myDlInfo))
        {
        	return 0;
        }
        Strlcpy(buffer, myDlInfo.dli_fname, MAX_PATH);
        baseOfDll = myDlInfo.dli_fbase;
        struct stat dli_fname_stat;
        if(stat(buffer, &dli_fname_stat) != 0)
        {
        	return 0;
        }
        sizeOfImage = (DWORD)dli_fname_stat.st_size;

#endif
        i = FindModule(buffer, sizeOfImage);
        LocalModule &local = s_modules[i];
        local.base = reinterpret_cast<size_t>(baseOfDll);

#ifdef _MSC_VER
        local.end = local.base + sizeOfImage;
#else
        // on non-windows we have not found a way to get exact range of library loaded addresses in memory so it is better to  
        // keep updating the local.end as we know an address at a time. Also the current assumption here is that if a shared lib is loaded between addresses x to x + y
        // then there is no other shared library loaded in between (x, x+y) range; if this does not hold good; then we could be in trouble with the windows based approach of having local.base and local.end
        if(local.end < address)
        {
            local.end = address;
        }
#endif
    }

    LocalModule &local = s_modules[i];
    GlobalModule &module = m_modules[i];
    size_t diff = address - local.base;
    unsigned offset = static_cast<unsigned>(diff);
    return offset + module.base;
}

unsigned FrameCache::FindModule(_In_z_ char *name, unsigned size)
{
    for (unsigned i = 0; i < m_modulesUsed; i++)
    {
        //N.B. This comparison must be case-insensitive.
        //  GetModuleFileName returns names with different cases.
        GlobalModule &module = m_modules[i];
        if (Strcasecmp(name, module.name) == 0 && size == module.size)
        {
            return i;
        }
    }

    if (m_modulesUsed == ModuleCount)
    {
        throw Exception();
    }

    //Not found, so create a new GlobalModule.
    unsigned i = m_modulesUsed++;
    GlobalModule &module = m_modules[i];
    Strlcpy(module.name, name, MAX_PATH);

    module.base = m_addressUsed;
    module.size = size;
    m_addressUsed += size;
    return i;
}

bool FrameCache::FindRecord(unsigned key)
{
    unsigned level = 0;

    //The cache has no record in slot 0.
    //Bit i (0-15) in m_dataUsed indicates that slots [2^i, 2*2^i) are in use.
    unsigned sections = m_dataUsed;
    for (unsigned mask = m_startMask; sections != 0; mask >>= 1)
    {
        if ((sections & mask) == 0)
        {
            continue;
        }

        sections &= ~mask;
        if (BinarySearch(key, mask, mask + mask))
        {
            GetGlobals().GetStats().frameHits[level]++;
            return true;
        }

        level++;
    }

    return false;
}

bool FrameCache::BinarySearch(unsigned key, int low, int high)
{
    while (low < high - 1)
    {
        int middle = (low + high) >> 1;
#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast(disable:26001)
#endif
        if (key >= m_data[middle].key)
#ifdef _MSC_VER
#pragma prefast(pop)
#endif
        {
            low = middle;
        }
        else
        {
            high = middle;
        }
    }

    //Four possible outcomes:
    //1) key > everything. low == originalHigh - 1.
    //2) key < everything. high == originalLow + 1.
    //3) key is between two nodes.
    //4) key matches data[low].
    //
    //Total number of comparisons is 1 + log N.
    return key == m_data[low].key;
}

void FrameCache::InsertRecord(unsigned key)
{
    GetGlobals().GetStats().frameInsertions++;

    //Bump the count.
    //This determines which sections will be merged.
    if (m_dataUsed == CacheSize - 1)
    {
        //The cache is full.
        //Discard the bottom half completely.
        m_dataUsed = CacheLastSection;
    }

    unsigned oldCount = m_dataUsed++;

    //Determine the section to merge into.
    int low = m_dataUsed & ~oldCount;

    if (static_cast<unsigned>(low) > m_startMask)
    {
        m_startMask = low;
    }

    //Insert the record in the first slot in the merged range.
    m_data[low].key = key;

    for (int src = 1; src != low; src += src)
    {
        MergeRecords(low, src, src); 
    }
}

void FrameCache::MergeRecords(int low, int src, int size)
{
    //Merges [low, low+size) and [src, src+size) into [low, low+2*size).
    //Always copy from high to low.
    int cursor1 = low + size - 1;
    int cursor2 = src + size - 1;
    for (int dest = low + size + size - 1; dest >= low; dest--)
    {
        if (cursor2 < src)
        {
            //Optimization. The remaining items are already in place!
            return;
        }

        if (cursor1 < low ||
            m_data[cursor1].key <= m_data[cursor2].key)
        {
            m_data[dest] = m_data[cursor2--];
        }
        else
        {
            m_data[dest] = m_data[cursor1--];
        }
    }
}
#endif
