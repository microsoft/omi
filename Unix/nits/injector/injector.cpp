/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <nits/base/Globals.h>
#include <stdio.h>
#include <pal/palcommon.h>
#include <pal/process.h>
#include <pal/strings.h>
#include <iostream>
#include <fstream>

using namespace std;

struct SharedSegmentHeader
{
    union
    {
        ptrdiff_t status;
        double doubleAlignment;
    };
};

PAL_Char *Copy(_In_opt_z_ const PAL_Char * str)
{
    if (str == NULL)
    {
        return NULL;
    }

    int length = (int)Tcslen(str);
    PAL_Char *copy = new PAL_Char[length + 1];

    if(!copy)
    {
        return NULL;
    }
    
    Tcslcpy(copy, str, length + 1);

    return copy;
}

PSTR ConvertStringToA(_In_opt_z_ const wchar_t *buf)
{
    if(buf == NULL)
        return NULL;

    int size = wcstombs(NULL, buf, 0);
    if (size == 0)
    {
        return NULL;
    }

    PSTR ansibuf = new char[size + 1];
    size = wcstombs(ansibuf, buf, size + 1);
    if (size == 0)
    {
        delete [] ansibuf;
        return NULL;
    }
    else
    {
        ansibuf[size] = '\0';
    }

    return ansibuf;
}

PWSTR ConvertStringToW(_In_opt_z_ const char *buf)
{
    if(buf == NULL)
        return NULL;

    int size = mbstowcs(0, buf, 0);
    if (size == 0)
    {
        return NULL;
    }

    PWSTR widebuf = new wchar_t[size + 1];
    size = mbstowcs(widebuf, buf, size);
    if (size == 0)
    {
        delete [] widebuf;
        return NULL;
    }
    else
    {
        widebuf[size] = L'\0';
    }

    return widebuf;
}

char *ConvertPalCharToStringA(_In_opt_z_ const PAL_Char *buf)
{
    return Copy(buf);
}

PAL_Char *ConvertStringAToPalChar(_In_opt_z_ const char *buf)
{
    if(buf == NULL)
        return NULL;
    return Copy(buf);
}

namespace TestSystem {

Fault::Fault() : m_lock(0)
{
    Reset(CallSite_NONE, 0, false);

    m_mainThread = Thread_ID();;
    m_minimumAttemptDifferentThread = 0;
}

void Fault::Reset(int site, int iteration, bool breakOnFault)
{
    m_site = site;
    m_iteration = iteration;
    m_attempt = 0;

    m_break = breakOnFault;
    m_faulted = false;
    m_filtered = false;
    m_hit = CallSite_NONE;
    m_line = 0;
    m_file[0] = '\0';

    m_faultedAttempt = 0;
    m_firstAttemptDifferentThread = 0;
}

Globals::Globals()
    : m_version(SharedMemoryVersion),
      m_runLock(0),
      m_attachLock(0),
      m_pipeLock(FALSE),
      m_pipeChars(0)
{
    m_pipe[0] = '\0';
    m_debugger[0] = '\0';
    m_binaryFilter[0] = '\0';
    m_binaryTarget[0] = '\0';

    for (int i = 0; i < InjectorListSize; i++)
        m_injectors[i].process = 0;

    Reset();

    for (int i = 0; i < ResultCount; i++)
    {
        m_statistics[i] = 0;
    }
}

Globals::~Globals()
{
}

void Globals::Reset()
{
    m_result = Skipped;

    m_stopReportingIgnoredErrors = false;

    m_config.traces = NitsTraceAllTests;
    m_config.mode = NitsTestCompoundFault;
    m_config.breakFault = false;
    m_config.breakAssert = false;
    m_config.skipFlakyTests = false;

    m_simAuto.Reset(CallSite_NONE, 0, false);
    m_simManual.Reset(CallSite_NONE, 0, false);

    m_faultError = HRESULT_FROM_WIN32(ERROR_OUTOFMEMORY);
    m_faultEvent[0] = L'\0';
    m_debugger[0] = L'\0';
    m_binaryFilter[0] = '\0';
    m_binaryTarget[0] = '\0';
}

} //namespace TestSystem

static void PatchBinary(
    _In_z_ PAL_Char *binary)
{
    Shlib *library = NULL;
    Shlib *framework;
    NitsFT *target;
    NitsFT *source;
    ptrdiff_t *targetNitsPresence = NULL;

    //printf("\nPatching binary %s\n", binary);
    
    library = Shlib_Open_Injected(binary, NitsReservedCallSite());

    if (library == NULL)
    {
        return;
    }

    target = (NitsFT *)Shlib_Sym(library, "NITS_STUB");
    if (target == NULL)
    {
        Shlib_Close(library);
        return;
    }

    targetNitsPresence = (ptrdiff_t *)Shlib_Sym(library, "NITS_PRESENCE_STUB");
    if (targetNitsPresence == NULL)
    {
        Shlib_Close(library);
        return;
    }

    framework = Shlib_Open_Injected(PAL_T("libnits.so"), NitsReservedCallSite());
    if (framework == NULL)
    {
        return;
    }

    source = (NitsFT *)Shlib_Sym(framework, "NITS_IMPL");
    if (source == NULL)
    {
        Shlib_Close(library);
        return;
    }

    memcpy(target, source, sizeof(NitsFT));

    Atomic_Swap(targetNitsPresence, NitsActive);

    Shlib_Close(library);
}

static unsigned DoesBinaryMatch(
    _In_ PAL_Char *list,
    _In_z_ PAL_Char *name)
{
    for (;;)
    {
        if (*list == '\0')
            return FALSE;
        
        // This is to enable specifying a substring of the 
        // target string; it is useful when all your target dll have some common substring
        if(*list == PAL_T('*'))
        {
            list++;
            if(Tcsstr(name, list))
                return TRUE;
        }
        else if (Tcscasecmp(list, name) == 0)
            return TRUE;

        list += Tcslen(list) + 1;
    }
}

typedef struct _LoadedModule
{
    PAL_Char *modulePath;
    PAL_Char *moduleBaseName;
} LoadedModule;

BOOL EnumProcessModulesHelper(
        _Out_writes_bytes_(cb) LoadedModule *lphModule,
        _In_ DWORD cb,
        _Out_ LPDWORD lpcbNeeded)
{
    char buf[MAX_PATH] = "/proc/";
    DWORD count = 0;
    DWORD maxCount = cb / sizeof(LoadedModule);

    ostringstream s;
    string convertedString;
    s << Process_ID();
    convertedString = s.str();
    Strlcpy(buf + 6, convertedString.c_str(), MAX_PATH - 6);
    Strlcpy(buf + Strlen(buf), "/maps", 6);
    
    ifstream file(buf);

    if (!file.good())
    {
        Tprintf(PAL_T("ERROR: maps file could not be loaded for current process"));
        return FALSE;
    }
    while (file.good() && (count < maxCount))
    {
        char *startOfPath = NULL;
        PAL_Char *nextFwdSlash = NULL;
        PAL_Char *currentBaseName = NULL;
        lphModule[count].modulePath = NULL;
        lphModule[count].moduleBaseName = NULL;
        file.width(MAX_PATH);
        file >> buf;
        startOfPath = strchr(buf, '/');
        if(startOfPath)
        {
            lphModule[count].modulePath = ConvertStringAToPalChar(startOfPath);
            if(lphModule[count].modulePath == NULL)
            {
                Tprintf(PAL_T("ERROR: could not allocate memory while enumerating modules"));
                return FALSE;
            }

            currentBaseName = lphModule[count].modulePath;
            nextFwdSlash = Tcschr(currentBaseName, PAL_T('/'));
            while(nextFwdSlash && nextFwdSlash[1] != PAL_T('\0'))
            {
                currentBaseName = nextFwdSlash + 1;
                nextFwdSlash = Tcschr(currentBaseName, PAL_T('/'));
            }
            lphModule[count].moduleBaseName = currentBaseName;

            count++;
        }
    }

    *lpcbNeeded = count * sizeof(LoadedModule);
    return TRUE;
}

DWORD GetModuleBaseNameHelper(
        _In_opt_ LoadedModule hModule,
        _Out_writes_z_(nSize) PAL_Char *lpBaseName,
        _In_ DWORD nSize)
{
    if(hModule.moduleBaseName == NULL)
        return 0;

    return Tcslcpy(lpBaseName, hModule.moduleBaseName, nSize);
}

void ProcessPatches(TestSystem::Globals *globals)
{
    if (globals->m_runLock == 0)
        return;

    unsigned isMatch = 0;
    /* Sweep through the list of loaded modules. */
    LoadedModule modules[200];
    DWORD size = 0;
    unsigned count = 0;
    unsigned i;
    PAL_Char name[MAX_PATH];

    if (EnumProcessModulesHelper(modules, sizeof(modules), &size) == FALSE)
    {
        return;
    }

    count = size / sizeof(LoadedModule);

    if (globals->m_binaryFilter[0] == '\0')
    {
        /* There is no filter. Match target binaries in any process. */
        isMatch = 1;
    }
    else for (i = 0; i < count; i++)
    {
        if(GetModuleBaseNameHelper(modules[i], name, MAX_PATH) == 0)
            continue;
        
        if (DoesBinaryMatch(globals->m_binaryFilter, name))
        {
            /* Found one of the filter modules. */
            isMatch = 1;
            break;
        }
    }

    if (isMatch == 0)
        goto Cleanup;

    for (i = 0; i < count; i++)
    {
        if(GetModuleBaseNameHelper(modules[i], name, MAX_PATH) == 0)
            continue;
        
        if (DoesBinaryMatch(globals->m_binaryTarget, name))
        {
            /* Found a target module. Trap this! */
            PatchBinary(name);
        }
    }
    
Cleanup:
    if(count != 0)
    {
        for(i = 0; i < count; i++)
        {
            if(modules[i].modulePath != NULL)
            {
                delete [] (modules[i].modulePath);
            }
        }
    }
    return;
}

static TestSystem::Globals g_tempGlobals;

static volatile ptrdiff_t g_signalSemaphoreDeleted = 0;
static NamedSem g_signalSemaphore;
static PAL_Boolean g_signalSemaphoreInitialized = PAL_FALSE;
static NamedSem g_waitSemaphore;
static PAL_Boolean g_waitSemaphoreInitialized = PAL_FALSE;
static NamedSem g_lockSemaphore;
static PAL_Boolean g_lockSemaphoreInitialized = PAL_FALSE;
static TestSystem::Globals *g_globals = NULL;
static TestSystem::InjectorTarget *g_injectorTarget = NULL;
static Shmem g_mapping;
volatile ptrdiff_t *g_status = NULL;
static volatile ptrdiff_t s_injectorStopping;

PAL_Boolean TryMarkingSignalSemaphoreForDeletion()
{
    return (Atomic_CompareAndSwap(&g_signalSemaphoreDeleted, 0, 1) == 0);
}

void MarkSignalSemaphoreAlive()
{
    Atomic_Swap(&g_signalSemaphoreDeleted, 0);
}

unsigned long InjectorSetup()
{
    void *start;
    size_t bytes = sizeof(TestSystem::Globals) + sizeof(SharedSegmentHeader);
    PAL_Char nameSignal[128] = PAL_T(CONFIG_SEMNAMELOCALPREFIX) PAL_T("NitsInjectorIn_");
    PAL_Char nameWait[128] = PAL_T(CONFIG_SEMNAMELOCALPREFIX) PAL_T("NitsInjectorOut_");
    PAL_Char conversionBuf[64] = PAL_T("");    
    const PAL_Char *convertedStr = NULL;
    size_t convertedSize = 0;
    // the lock semaphore is kept non-windows only since the issue with the injector is not observed on windows
    PAL_Char nameLock[128] = PAL_T(CONFIG_SEMNAMELOCALPREFIX) PAL_T("NitsInjectorLock_");    

    const PAL_Char globalMappingName[] = PAL_T(CONFIG_SHMNAMEGLOBALPREFIX) PAL_T("NitsGlobalData");

    s_injectorStopping = 0;

    MarkSignalSemaphoreAlive();
    
    if(Shmem_Open(&g_mapping, globalMappingName, SHMEM_ACCESS_READWRITE, SHMEM_USER_ACCESS_ALLOW_ALL, bytes) != NO_ERROR)
    {
        return ERROR_OUTOFMEMORY;
    }
    
    start = Shmem_Map(&g_mapping, SHMEM_ACCESS_READWRITE, 0, bytes);
    if (start == NULL)
    {
        return ERROR_OUTOFMEMORY;
    }

    /* The shared memory is mapped. Make sure the contents are initialized. */
    g_status = (ptrdiff_t *)start;
    g_globals = (TestSystem::Globals *)((char*)g_status + sizeof(SharedSegmentHeader));
    if (Atomic_CompareAndSwap(g_status, TestSystem::Unloaded, TestSystem::Loading) == TestSystem::Unloaded)
    {
        memcpy(g_globals, &g_tempGlobals, sizeof(TestSystem::Globals));
        *g_status = TestSystem::Loaded;
    }

    while (*g_status != TestSystem::Loaded)
    {
        Sleep_Milliseconds(10);
    }

    /* The shared memory space is now initialized. */
    /* Set up the semaphores used to trigger patching. */

    if (g_globals->m_version != TestSystem::SharedMemoryVersion)
    {
        g_globals = NULL;
        return 0;
    }

    TcsFromUInt64(conversionBuf, Process_ID(), &convertedStr, &convertedSize);
    Tcscat(nameSignal, 128, convertedStr);
    Tcscat(nameWait, 128, convertedStr);
    
    /* The semaphre signalled by the product to us. */
    g_signalSemaphoreInitialized = (0 == NamedSem_Open_Injected(&g_signalSemaphore, SEM_USER_ACCESS_ALLOW_ALL, 0, nameSignal, NAMEDSEM_FLAG_CREATE, NitsReservedCallSite()));

    /* The product waits on this semaphre to continue execution. */
    g_waitSemaphoreInitialized = (0 == NamedSem_Open_Injected(&g_waitSemaphore, SEM_USER_ACCESS_ALLOW_ALL, 0, nameWait, NAMEDSEM_FLAG_CREATE, NitsReservedCallSite()));

    Tcscat(nameLock, 128, convertedStr);

    /* The product or unittest framework use this as a locking mechanism to access the wait and signal semaphore */
    g_lockSemaphoreInitialized = (0 == NamedSem_Open_Injected(&g_lockSemaphore, SEM_USER_ACCESS_ALLOW_ALL, 1, nameLock, NAMEDSEM_FLAG_CREATE, NitsReservedCallSite()));

    /* Register the handles with the harness. */
    for (int i = 0; i < TestSystem::InjectorListSize; i++)
    {
        TestSystem::InjectorTarget *target = g_globals->m_injectors + i;

        if (target->process != 0)
            continue;

        if (Atomic_CompareAndSwap(&target->process, 0, Process_ID()) != 0)
            continue;

        g_injectorTarget = target;
        break;
    }

    return 0;
}

void CloseSemaphoreIfRequired(PAL_Boolean *initialized, NamedSem *semaphore)
{
    if(*initialized)
    {
        NamedSem_Close(semaphore);
        NamedSem_Destroy(semaphore);
        *initialized = PAL_FALSE;
    }
}

void Unload()
{
    if(g_injectorTarget != NULL)
    {
        /* Unregister with the harness. */
        Atomic_CompareAndSwap(&(g_injectorTarget->process), Process_ID(), 0);
    }

    if(g_status)
    {
        g_injectorTarget = NULL;
        Shmem_Unmap(&g_mapping, const_cast<ptrdiff_t *>(g_status), sizeof(TestSystem::Globals) + sizeof(SharedSegmentHeader));
        Shmem_Close(&g_mapping);
    }

    CloseSemaphoreIfRequired(&g_waitSemaphoreInitialized, &g_waitSemaphore);
    CloseSemaphoreIfRequired(&g_lockSemaphoreInitialized, &g_lockSemaphore);
    // either we or the NitsStopInjectorFunc will close signal semaphore
    // the function is to see who wins the race
    if(TryMarkingSignalSemaphoreForDeletion())
    {
        CloseSemaphoreIfRequired(&g_signalSemaphoreInitialized, &g_signalSemaphore);        
    }
    //printf("\nUnloading injector\n");
}


NITS_EXTERN_C PAL_Uint32 THREAD_API InjectorProc(_In_ void * param)
{
    PAL_UNUSED(param);

    if (g_globals == NULL || g_injectorTarget == NULL)
    {
        //printf("\nUnloading injector since globals is null\n");
        Unload();
        return 0;
    }

    for(;;)
    {
        int waitResult = NamedSem_TimedWait(&g_signalSemaphore, 10000);

        if (g_globals->m_unload ||
            g_globals->m_version != TestSystem::SharedMemoryVersion ||
            g_injectorTarget->process != (long)Process_ID() ||
            s_injectorStopping)
        {
            NamedSem_Post(&g_waitSemaphore, 1);
            Unload();
            //printf("\nUnloading injector since globals told it to\n");
            return 0;
        }

        // if the wait timed out, no need to patch; just go back to wait
        if(waitResult != 0)
        {
            continue;
        }

        ProcessPatches(g_globals);

        NamedSem_Post(&g_waitSemaphore, 1);
    }
}

PAL_BEGIN_EXTERNC

static volatile ptrdiff_t s_injectorRefs = 0;
static Thread s_injectorThread;

#define INJECTOR_STOPPED  0
#define INJECTOR_STARTING 1
#define INJECTOR_STOPPING 2
#define INJECTOR_RUNNING  3

NITS_DLLEXPORT int NITS_CALL NitsStartInjector(void)
{
    int result;
    ptrdiff_t oldRefs;
    ptrdiff_t newRefs;
    ptrdiff_t swapRefs;

    for (;;)
    {
        oldRefs = PAL_PREFETCH(&s_injectorRefs);

        if (oldRefs >= INJECTOR_RUNNING)
            newRefs = oldRefs + 1;
        else if (oldRefs == INJECTOR_STOPPED)
            newRefs = INJECTOR_STARTING;
        else
        {
            // this is a rare code path which occurs if two product binaries at the same time try to load the injector
            // and in that case one of them wins the race to set the s_injectorRefs to INJECTOR_STARTING
            // this is very quick transient state till the other thread sets the refs to INJECTOR_RUNNING which is few statements below in this function
            // not doing this leads to this thread not leaving the cpu for anyone else and slows down the process and the machine
            Sleep_Milliseconds(10);
            continue;
        }

        swapRefs = Atomic_CompareAndSwap(&s_injectorRefs, oldRefs, newRefs);
        if (swapRefs == oldRefs)
            break;        
    }

    if (newRefs != INJECTOR_STARTING)
        return 0;

    result = InjectorSetup();
    if (result)
        goto Fail;

    result = Thread_CreateJoinable_Injected(&s_injectorThread, InjectorProc, NULL, NULL, NitsReservedCallSite());
    if (result)
        goto Fail;

    s_injectorRefs = INJECTOR_RUNNING;
    return 0;

Fail:
    s_injectorRefs = INJECTOR_STOPPED;
    return result;
}

NITS_DLLEXPORT void NITS_CALL NitsStopInjector(void)
{
    ptrdiff_t oldRefs;
    ptrdiff_t newRefs;
    ptrdiff_t swapRefs;

    for (;;)
    {
        oldRefs = PAL_PREFETCH(&s_injectorRefs);

        if (oldRefs > INJECTOR_RUNNING)
            newRefs = oldRefs - 1;
        else if (oldRefs == INJECTOR_RUNNING)
            newRefs = INJECTOR_STOPPING;
        else if (oldRefs == INJECTOR_STOPPED)
            abort();
        else        
            continue;        

        swapRefs = Atomic_CompareAndSwap(&s_injectorRefs, oldRefs, newRefs);
        if (swapRefs == oldRefs)
            break;
    }

    if (newRefs != INJECTOR_STOPPING)
        return;

    s_injectorStopping = 1;

    // if injector has already called Unload and ended InjectorProc
    // in that case we dont need to post signalsemaphore
    // in other case we will post it since that will make the thread end quicker
    PAL_Boolean markedForDeletion = TryMarkingSignalSemaphoreForDeletion();
    if(markedForDeletion)
    {
        NamedSem_Post(&g_signalSemaphore, 1);
    }

    PAL_Uint32 result = 0;

    Thread_Join(&s_injectorThread, &result);

    Thread_Destroy(&s_injectorThread);
    
    if(markedForDeletion)
    {
        CloseSemaphoreIfRequired(&g_signalSemaphoreInitialized, &g_signalSemaphore);        
    }

    s_injectorRefs = INJECTOR_STOPPED;
}

PAL_END_EXTERNC

