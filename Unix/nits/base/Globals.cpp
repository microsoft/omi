//*****************************************************************************
//  Copyright (C) 2007 Microsoft Corporation
//  All rights reserved.
//*****************************************************************************
#include "Globals.h"
#include <iostream>
#include <fstream>
#ifdef _MSC_VER
    #include <strsafe.h>
    #include <aclapi.h>
    #include <Globals.tmh>
#elif defined(CONFIG_HAVE_BACKTRACE)
#  include <execinfo.h>
#endif

#include <pal/strings.h>
#include <pal/process.h>

using namespace std;
using namespace TestSystem;

struct SharedSegmentHeader
{
    union
    {
        ptrdiff_t status;
        double doubleAlignment;
    };
};

PWSTR ConvertStringToW(_In_opt_z_ const char *buf)
{
    if(buf == NULL)
        return NULL;

#ifdef _MSC_VER
    int size = MultiByteToWideChar(CP_THREAD_ACP, 0, buf, -1, NULL, NULL);
    if (size == 0)
    {
        throw Exception();
    }
#else
    int size = mbstowcs(0, buf, 0);
#endif

#ifdef _MSC_VER
    PWSTR widebuf = new wchar_t[size];
    size = MultiByteToWideChar(CP_THREAD_ACP, 0,
            buf, -1, widebuf, size);
    if (size == 0)
    {
        delete [] widebuf;
        throw Exception();
    }
#else
    PWSTR widebuf = new wchar_t[size + 1];
    size = mbstowcs(widebuf, buf, size);
#endif

#ifndef _MSC_VER
    if(size == 0)
    {
        widebuf[0] = L'\0';
    }
    else
    {
    	widebuf[size] = L'\0';
    }
#endif

    return widebuf;
}

PSTR ConvertStringToA(_In_opt_z_ const wchar_t *buf)
{
    if(buf == NULL)
        return NULL;

#ifdef _MSC_VER
	int size = WideCharToMultiByte(CP_THREAD_ACP, 0, buf, -1, NULL, NULL, NULL, NULL);
    if (size == 0)
    {
        throw Exception();
    }
#else
	int size = wcstombs(NULL, buf, 0);
#endif

#ifdef _MSC_VER
    PSTR ansibuf = new char[size];
    size = WideCharToMultiByte(CP_THREAD_ACP, 0, buf, -1, ansibuf, size, NULL, NULL);
    if (size == 0)
    {
        delete [] ansibuf;
        throw Exception();
    }
#else
    PSTR ansibuf = new char[size + 1];
    size = wcstombs(ansibuf, buf, size + 1);
#endif

#ifndef _MSC_VER
    if(size == 0)
    {
        ansibuf[0] = '\0';
    }
    else
    {
    	ansibuf[size] = '\0';
    }
#endif

    return ansibuf;
}

PAL_Char *ConvertStringWToPalChar(_In_opt_z_ const wchar_t *buf)
{
    if(buf == NULL)
        return NULL;

#ifdef CONFIG_ENABLE_WCHAR
	return Copy(buf);
#else
	return ConvertStringToA(buf);
#endif
}

PAL_Char *ConvertStringAToPalChar(_In_opt_z_ const char *buf)
{
    if(buf == NULL)
        return NULL;

#ifdef CONFIG_ENABLE_WCHAR
	return ConvertStringToW(buf);
#else
	return Copy(buf);
#endif
}

char *ConvertPalCharToStringA(_In_opt_z_ const PAL_Char *buf)
{
    if(buf == NULL)
        return NULL;

#ifdef CONFIG_ENABLE_WCHAR
    return ConvertStringToA(buf);
#else
    return Copy(buf);
#endif

}

namespace TestSystem
{
bool StartsWith(_In_z_ const PAL_Char * str, _In_z_ const PAL_Char * prefix)
{
    return Tcsncmp(str, prefix, Tcslen(prefix)) == 0;
}

bool Equals(_In_z_ const PAL_Char * str, _In_z_ const PAL_Char * target)
{
    return Tcscmp(str, target) == 0;
}

bool EqualsCI(_In_z_ const PAL_Char * str, _In_z_ const PAL_Char * target)
{
    return Tcscasecmp(str, target) == 0;
}

PAL_Char *Copy(_In_opt_z_ const PAL_Char * str)
{
    if (str == NULL)
    {
        return NULL;
    }

    size_t length = Tcslen(str);
    PAL_Char *copy = new PAL_Char[length + 1];
    if (copy == NULL)
    {
        throw Exception();
    }
    Tcslcpy(copy, str, length + 1);

    return copy;
}

} //namespace TestSystem

#ifdef _MSC_VER
NITS_EXPORT void NitsEventCreate(
    _Inout_ Event *event,
    _In_z_ const PAL_Char * name,
    NitsFaultMode mode)
{
    event->m_handle = NULL;
    event->m_name = name;

    if (Tcslen(name) > Event::MaxName)
    {
        FatalError();
    }

    event->m_handle = CreateEvent(&g_SecurityAttributes, mode == Manual, FALSE, name);
    if (event->m_handle == NULL)
    {
        FatalError();
    }
}

NITS_EXPORT void NitsEventDelete(
    _Inout_ Event *event)
{
    if (event->m_handle)
    {
        CloseHandle(event->m_handle);
        event->m_handle = NULL;
    }
}

#endif

DWORD Mapping::Initialize(_In_reads_bytes_(bytes) void const *context, long bytes)
{
    if (m_bytes == 0)
    {
        m_bytes = bytes;

        m_copy = SystemMalloc(m_bytes);

        if (m_copy == NULL)
            throw Exception();

        memcpy(m_copy, context, m_bytes);
    }
    else if (m_bytes != bytes)
    {
        return ERROR_INVALID_PARAMETER;
    }

    if (m_mapping == NULL)
    {
        m_mapping = (Shmem *) SystemMalloc(sizeof(Shmem));
        if(m_mapping == NULL)
            return ERROR_OUTOFMEMORY;
        int res = Shmem_Open(m_mapping, m_name, SHMEM_ACCESS_READWRITE, SHMEM_USER_ACCESS_ALLOW_ALL, m_bytes + sizeof(SharedSegmentHeader));

        if(res != NO_ERROR)
        {
            return res;
        }
    }

    if (m_status == NULL)
    {
        //Memory is zeroed for the first process. m_status is Unloaded.
        //In that case, m_state is Unloaded.
        m_status = reinterpret_cast<ptrdiff_t *>(Shmem_Map(m_mapping, SHMEM_ACCESS_READWRITE, 0, m_bytes + sizeof(SharedSegmentHeader)));
        if (m_status == NULL)
        {
#ifdef _MSC_VER
        	return GetLastError();
#else
        	return ERROR_OUTOFMEMORY;
#endif
        }

        m_data = reinterpret_cast<ptrdiff_t *>((char*)m_status + sizeof(SharedSegmentHeader));
        if (Atomic_CompareAndSwap(m_status, Unloaded, Loading) == Unloaded)
        {
            memcpy(m_data, context, m_bytes);
            *m_status = Loaded;
        }
    }

    while (*m_status != Loaded)
    {
        Sleep_Milliseconds(10);
    }

    return NO_ERROR;
}

void Mapping::Reset()
{
    memcpy(m_data, m_copy, m_bytes);
}

Fault::Fault() : m_lock(0)
{
    Reset(CallSite_NONE, 0, false);

    m_mainThread = Thread_ID();
    m_minimumAttemptDifferentThread = 0;
}

void Fault::Toggle(bool enabled)
{
    m_site = (enabled ? CallSite_ALL : CallSite_NONE);
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

bool Fault::ShouldFault(CallSite const &site)
{
    if (m_site == CallSite_NONE)
    {
        return false;
    }

    if (m_site != CallSite_ALL && m_site != site.id)
    {
        return false;
    }

    Atomic_Lock(&m_lock);

    ptrdiff_t attempt = Atomic_Inc(&m_attempt);
#if defined(CONFIG_HAVE_BACKTRACE)

    if (m_site == CallSite_ALL && GetGlobals().GetConfiguration().mode >= NitsTestStackFault)
    {
        bool filtered = false;
        ptrdiff_t limit = 0;
        ThreadID currentThread = Thread_ID();
        if (!Thread_Equal(&currentThread, &m_mainThread))
        {
            //Faults from other threads are more tightly controlled.
            //Attempts earlier than the given limit should be filtered out.
            limit = m_minimumAttemptDifferentThread;
            if (m_firstAttemptDifferentThread == 0)
            {
                m_firstAttemptDifferentThread = attempt;
            }
        }
        if (m_faulted || !GetGlobals().m_frames.ShouldFault(limit, attempt, filtered))
        {
            if (filtered)
            {
                m_filtered = true;
            }
            Atomic_Unlock(&m_lock);
            return false;
        }
    }
    else
#endif
    {
        if (m_iteration != 0 && m_iteration != attempt)
        {
            Atomic_Unlock(&m_lock);
            return false;
        }
    }

    m_faulted = true;

    Atomic_Unlock(&m_lock);

    NitsTraceEx(PAL_T("Simulating fault"), site, NitsAutomatic);

#ifdef _MSC_VER
    DoTraceMessage(TestLifetime, L"Simulating fault!");
#endif
    //Update the last fault hit.
    m_hit = site.id;
    m_line = site.line;
    m_faultedAttempt = attempt;
    PCSTR temp = site.file;

#ifdef _MSC_VER
    CaptureStackBackTrace(3, 50, GetGlobals().GetStackTrace(), NULL);
#elif defined(CONFIG_HAVE_BACKTRACE)
    backtrace(GetGlobals().GetStackTrace(), 50);
#else
    /* ATTN: backtrace collection is not implemented! */
#endif
    //Truncate the beginning of the string.
    int length = (int)strlen(temp);
    int limit = FileSize - 1;
    if (length > limit)
    {
        temp += length - limit;
    }

    Strlcpy(m_file, temp, FileSize);

    if (m_break)
    {
        MyDebugBreak;
    }

    return true;
}

CallSite Fault::GetFaultedSite() const
{
    return NitsMakeCallSite(m_hit, NULL, m_file, m_line);
}

Globals::Globals()
    : m_version(SharedMemoryVersion),
      m_unload(0),
      m_runLock(0),
      m_attachLock(0),
      m_pipeLock(FALSE),
      m_pipeChars(0),
      m_pipeOutputType(NoMessage)
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

bool Globals::StartRun(bool force)
{
    m_version = SharedMemoryVersion;

    CheckRun();

    DWORD pid = Process_ID();
    if (force)
    {
        Atomic_Swap(&m_runLock, pid);
    }
    else if (Atomic_CompareAndSwap(&m_runLock, 0, pid) != 0)
    {
        return false;
    }

    for (int i = 0; i < ResultCount; i++)
    {
        m_statistics[i] = 0;
    }

#if defined(CONFIG_HAVE_BACKTRACE)
    m_frames.Reset();
#endif

    memset(&m_stats, 0, sizeof(m_stats));

    // injection is disabled on linux for now
#ifdef _MSC_VER
    //Enable all privileges to capture SeDebugPrivilege.
    HANDLE token;
    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);

    DWORD length = 0;
    TOKEN_USER tu;
    GetTokenInformation(token, TokenPrivileges, &tu, sizeof(TOKEN_USER), &length);

#pragma prefast(push)
#pragma prefast(disable: 26000)
    char *buffer = (char *)SystemMalloc(length);
    char *previous = (char *)SystemMalloc(length);
    GetTokenInformation(token, TokenPrivileges, buffer, length, &length);

    memcpy(previous, buffer, length);
    TOKEN_PRIVILEGES *list = (TOKEN_PRIVILEGES *)buffer;
    for (unsigned i = 0; i < list->PrivilegeCount; i++)
        list->Privileges[i].Attributes |= SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(token, FALSE, list, 0, NULL, NULL);

    for (int i = 0; i < InjectorListSize; i++)
    {
        InjectorTarget *target = m_injectors + i;
        if (target->process == 0)
            continue;

        HANDLE p = OpenProcess(PROCESS_DUP_HANDLE, FALSE, (DWORD)target->process);
        if (p == NULL)
        {
            /* This process is not accessible. Remove the entry. */
            target->process = 0;
            continue;
        }

        HANDLE sem;
        HANDLE lockSem;

        if (!DuplicateHandle(p, target->lockSemaphore, GetCurrentProcess(), &lockSem, 0, FALSE, DUPLICATE_SAME_ACCESS))
        {
            target->process = 0;
            CloseHandle(p);
            continue;
        }

        // lock semaphore acts as a lock to access signal/wait semaphore;
        // if you can not acquire it; then skip the rest of the part
        // a subsequent call from a product stub will attempt the patching anyways
        if(WaitForSingleObject(lockSem, 100) != WAIT_OBJECT_0)
        {
            CloseHandle(lockSem);
            CloseHandle(p);
            continue;
        }

        if (!DuplicateHandle(p, target->signalSemaphore, GetCurrentProcess(), &sem, 0, FALSE, DUPLICATE_SAME_ACCESS))
        {
            ReleaseSemaphore(lockSem, 1, NULL);
            CloseHandle(lockSem);
            CloseHandle(p);
            target->process = 0;
            continue;
        }

        /* Kick the signalSemaphore for each injector. */
        ReleaseSemaphore(sem, 1, NULL);
        CloseHandle(sem);

        if (!DuplicateHandle(p, target->waitSemaphore, GetCurrentProcess(), &sem, 0, FALSE, DUPLICATE_SAME_ACCESS))
        {
            ReleaseSemaphore(lockSem, 1, NULL);
            CloseHandle(lockSem);
            CloseHandle(p);
            target->process = 0;
            continue;
        }

        /* Wait on the waitSemaphore for each injector. */
        WaitForSingleObject(sem, 100);
        CloseHandle(sem);

        ReleaseSemaphore(lockSem, 1, NULL);
        CloseHandle(lockSem);

        CloseHandle(p);
    }

    //Restore privileges back to the way they were.
    SystemFree(buffer);
    SystemFree(previous);
    list = (TOKEN_PRIVILEGES *)previous;
    AdjustTokenPrivileges(token, FALSE, list, 0, NULL, NULL);
    CloseHandle(token);
#pragma prefast(pop)
#else
    PAL_Char nameSignal[128] = PAL_T(CONFIG_SEMNAMELOCALPREFIX) PAL_T("NitsInjectorIn_");
    PAL_Char nameWait[128] = PAL_T(CONFIG_SEMNAMELOCALPREFIX) PAL_T("NitsInjectorOut_");
    PAL_Char nameLock[128] = PAL_T(CONFIG_SEMNAMELOCALPREFIX) PAL_T("NitsInjectorLock_");
    NamedSem semaphore;
    NamedSem lockSemaphore;
    PAL_Char conversionBuf[64] = PAL_T("");
    const PAL_Char *convertedStr = NULL;
    size_t convertedSize = 0;

    for (int i = 0; i < InjectorListSize; i++)
    {
        InjectorTarget *target = m_injectors + i;
        if (target->process == 0)
            continue;

        TcsFromUInt64(conversionBuf, target->process, &convertedStr, &convertedSize);
        Tcscat(nameLock, 128, convertedStr);

        if(NamedSem_Open_Injected(&lockSemaphore, SEM_USER_ACCESS_ALLOW_ALL, 0, nameLock, 0, NitsReservedCallSite()) != 0)
        {
            target->process = 0;
            continue;
        }

        if(NamedSem_TimedWait(&lockSemaphore, 500) != 0)
        {
            NamedSem_Close(&lockSemaphore);
            continue;
        }

        TcsFromUInt64(conversionBuf, target->process, &convertedStr, &convertedSize);
        Tcscat(nameSignal, 128, convertedStr);

        if(NamedSem_Open_Injected(&semaphore, SEM_USER_ACCESS_ALLOW_ALL, 0, nameSignal, 0, NitsReservedCallSite()) != 0)
        {
            target->process = 0;
            NamedSem_Post(&lockSemaphore, 1);
            NamedSem_Close(&lockSemaphore);
            continue;
        }

        NamedSem_Post(&semaphore, 1);
        NamedSem_Close(&semaphore);

        TcsFromUInt64(conversionBuf, target->process, &convertedStr, &convertedSize);
        Tcscat(nameWait, 128, convertedStr);

        if(NamedSem_Open_Injected(&semaphore, SEM_USER_ACCESS_ALLOW_ALL, 0, nameWait, 0, NitsReservedCallSite()) != 0)
        {
            target->process = 0;
            NamedSem_Post(&lockSemaphore, 1);
            NamedSem_Close(&lockSemaphore);
            continue;
        }

        NamedSem_TimedWait(&semaphore, 500);

        NamedSem_Close(&semaphore);

        NamedSem_Post(&lockSemaphore, 1);
        NamedSem_Close(&lockSemaphore);
    }
#endif
    return true;

}

void Globals::StopRun()
{
    m_runLock = 0;
}

void Globals::CheckRun()
{
    if ((m_runLock == 0) || (m_runLock == (long)(Process_ID())) )
    {
        return;
    }

#ifdef _MSC_VER
    HANDLE h = OpenProcess(SYNCHRONIZE, FALSE, (DWORD)m_runLock);
    if (h == NULL)
    {
        DWORD err = GetLastError();
        //Access denied likely means some test didn't call RevertToSelf!
        if (err != ERROR_ACCESS_DENIED)
        {
            Tprintf(PAL_T("%T%d%T"), PAL_T("WARNING: Previous test process (PID "), m_runLock, PAL_T(") exited abnormally!\n"));
            StopRun();
        }
    }
    else
    {
        CloseHandle(h);
    }
#endif
}

void Globals::LockPipe()
{
    Atomic_Lock(&m_pipeLock);
}

void Globals::UnlockPipe()
{
    Atomic_Unlock(&m_pipeLock);
}

void Globals::EmptyPipe()
{
    m_pipeChars = 0;
    m_pipe[0] = '\0';
    m_pipeOutputType = NoMessage;
}

void Globals::PostPipe(_In_z_ const PAL_Char * text, PipeOutputType outputType)
{
    CheckRun();

    NamedSem *event = System::GetInstance().GetPipeEvent();

    size_t length = Tcslen(text);
    PAL_Char *end = m_pipe + PipeSize - 1;

#if defined(_MSC_VER)
# pragma warning(disable : 4127)
#endif

    while (true)
    {
        if (!m_runLock)
        {
            //Don't post unless there is someone reading.
            return;
        }

        LockPipe();

        //Append as much text as we can to the pipe.
        PAL_Char *buffer = m_pipe + m_pipeChars;
        size_t available = end - buffer;
        size_t toUse = min(length, available);

        _Analysis_assume_(sizeof(text)==(toUse * sizeof(PAL_Char)));
        memcpy(buffer, text, toUse * sizeof(PAL_Char));
        m_pipeChars += (unsigned int)toUse;
        m_pipe[m_pipeChars] = '\0';
        m_pipeOutputType = outputType;

        UnlockPipe();


        //Wake up the pipe thread.
        NamedSem_Post(event, 1);

#ifdef _MSC_VER
        if (IsDebuggerPresent())
        {
            //Issuing interactive debugger commands starves the pipe thread.
            //Make this synchronous in that case.
            while (m_pipeChars > 0)
            {
                Sleep_Milliseconds(10);
            }
        }
#endif
        if (length == toUse)
        {
            return;
        }

        text += toUse;
        length -= toUse;
        Sleep_Milliseconds(10);
    }
}

bool Globals::IsPipeEmpty()
{
    bool pipeEmpty;
    LockPipe();
    pipeEmpty = (m_pipeOutputType == NoMessage);
    UnlockPipe();
    return pipeEmpty;
}

void Globals::AttachDebugger()
{
#ifdef _MSC_VER
    //See if another process wants a debugger attached.
    if (m_attachLock)
    {
        wostringstream buf;
        buf << m_debugger << L" -p " << m_attachLock;

        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        memset(&pi, 0, sizeof(pi));

        si.dwFlags |= STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_SHOWMINNOACTIVE;

        PWSTR temp = Copy(buf.str().c_str());
        if (!CreateProcess(NULL, temp, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
        {
            Tprintf(PAL_T("%T%d%T"), PAL_T("ERROR: Failed to attach debugger! Error="), GetLastError(), PAL_T("\n"));
            GetGlobals().SetResult(Error);
        }
        else
        {
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
        }
        delete [] temp;

        m_attachLock = 0;
    }
#endif
}

void Globals::CheckDebugger()
{
#ifdef _MSC_VER
    if (Equals(m_debugger, PAL_T("")) || IsDebuggerPresent())
    {
        return;
    }

    //The debugger needs to be attached.
    //This will happen on the pipe thread of the master nits.exe process.
    CheckRun();
    if (!m_runLock)
    {
        //The pipe thread is not there!
        return;
    }

    PAL_Uint32 pid = Process_ID();
    while (Atomic_CompareAndSwap(&m_attachLock, 0, pid) != 0)
    {
        Sleep_Milliseconds(10);
    }

    //The pipe thread clears m_attachLock once the command is executed.
    //Wait for the debugger to attach.
    while (!IsDebuggerPresent())
    {
        Sleep_Milliseconds(10);
    }
#endif
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

#ifdef _MSC_VER
    m_faultError = HRESULT_FROM_WIN32(ERROR_OUTOFMEMORY);
#else
    m_faultError = ERROR_OUTOFMEMORY;
#endif
    m_faultEvent[0] = L'\0';
    m_debugger[0] = L'\0';
}

void Globals::SetFault(int site,
                       int attempt,
                       HRESULT error,
                       _In_z_ const PAL_Char * event)
{
    m_simManual.Reset(site, attempt, false);
    m_faultError = error;
    Tcslcpy(m_faultEvent, event, Event::MaxName);
}

void Globals::SetDebugger(_In_z_ const PAL_Char * debugger)
{
    Tcslcpy(m_debugger, debugger, 1024);
}

//Returns 'true' if caller should return.
//Caller always returns the value of 'test'.
NitsResult Globals::TestExpression(bool test, NitsFaultMode mode)
{
    if (test)
    {
        //Assertion succeeded. Update state and return.
        if (m_result == Skipped)
        {
            m_result = Passed;
        }
        return NitsTrue;
    }

    if (mode == NitsManual)
    {
        //This was not an expected fault simulation failure.
        //Fails the test even if running fault sim loops.
        m_result = Error;
    }
    else if (m_result != Error)
    {
        //Don't overwrite Error with Failed.
        m_result = Failed;
    }

    if (mode == Automatic && m_simAuto.DidFault())
    {
        //Asserts are expected after automatic faults.
        return NitsTrue;
    }

    if (m_config.breakAssert)
    {
        MyDebugBreak;
    }

    //Determine if failed asserts are being shown.
    return m_config.traces >= NitsTraceAsserts ? NitsFalse : NitsTrue;
}

NitsResult Globals::ShouldFault(CallSite const &site, NitsFaultMode mode)
{
    NitsCallSite reservedCallsite = NitsReservedCallSite();
    if(site.id == reservedCallsite.id)
    {
        return NitsFalse;
    }

    CheckDebugger();

    if (m_runLock == 0)
    {
        return NitsFalse;
    }

    GetStats().shouldFaults++;

    //if (m_runLock != Process_ID())
    //{
    //    GetStats().shouldFaultIPCs++;
    //}

    //Check for manual faults first.
    if (m_simManual.ShouldFault(site))
    {
    	// TODO: this should be replaced by PAL equivalent but this can wait
#ifdef _MSC_VER
        //Check for simulated thread delay.
        if (m_faultEvent[0] != '\0')
        {
            Event event(m_faultEvent);
            WaitForSingleObject(event, INFINITE);
        }
#endif
        return NitsTrue;
    }

    return (mode == Automatic && m_simAuto.ShouldFault(site)) ? NitsTrue : NitsFalse;
}

NitsResult Globals::DidFault()
{
    return m_simAuto.DidFault() ? NitsTrue : NitsFalse;
}

bool Globals::IsUnittestRunning()
{
    return m_runLock != 0;
}

static Globals g_tempGlobals;

System::System()
    : m_globals(NULL)
{
    const PAL_Char pipeEventName[] = PAL_T(CONFIG_SEMNAMEGLOBALPREFIX) PAL_T( "NitsPipeEvent");
    const PAL_Char mappingName[] = PAL_T(CONFIG_SEMNAMEGLOBALPREFIX) PAL_T( "NitsGlobalData");

    g_tempGlobals.m_version = SharedMemoryVersion;

    DWORD initError = Initialize(mappingName, &g_tempGlobals, reinterpret_cast<void **>(&m_globals), sizeof(Globals));
    if (NO_ERROR != initError)
    {
        Tprintf(PAL_T("%T%d%T"), PAL_T("ERROR: Failed to load shared memory with error"), initError, PAL_T("Please run NITS elevated!\n"));
        throw Exception();
        return;
    }

    if(NamedSem_Open_Injected(&m_pipeEvent, SEM_USER_ACCESS_ALLOW_ALL, 0, pipeEventName, NAMEDSEM_FLAG_CREATE, NitsReservedCallSite()) != 0)
    {
        throw Exception();
        return;
    }

    GetGlobals().CheckDebugger();
}

System::~System()
{
    NamedSem_Close(&m_pipeEvent);

    NamedSem_Destroy(&m_pipeEvent);

    for (DWORD i = 0; i < m_mappings.size(); i++)
    {
        Mapping &p = m_mappings[i];
        delete [] p.m_name;

#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast(disable: 6001)
#endif
        Shmem_Unmap(p.m_mapping, const_cast<ptrdiff_t *>(p.m_status), p.m_bytes + sizeof(SharedSegmentHeader));
        Shmem_Close(p.m_mapping);
        SystemFree(p.m_mapping);

        if(p.m_copy != NULL)
        {
            SystemFree(p.m_copy);
        }
#ifdef _MSC_VER
#pragma prefast(pop)
#endif

    }
}

Mapping &System::GetMapping(_In_z_ const PAL_Char * name)
{
    int size = (int)m_mappings.size();
    for (int i = 0; i < size; i++)
    {
        if (Equals(m_mappings[i].m_name, name))
        {
            return m_mappings[i];
        }
    }

    Mapping temp = {Copy(name), NULL, NULL, NULL, 0, NULL};
    m_mappings.push_back(temp);
    return m_mappings[size];
}

void System::ResetClientMappings()
{
    int size = (int)m_mappings.size();

    const PAL_Char globalMappingName[] = PAL_T(CONFIG_SEMNAMEGLOBALPREFIX) PAL_T("NitsGlobalData");

    for (int i = 0; i < size; i++)
    {
        if (!Equals(m_mappings[i].m_name, globalMappingName))
        {
            m_mappings[i].Reset();
        }
    }
}

Globals const &System::GetGlobals() const
{
    Globals *nothing = NULL;
    if (m_globals == NULL)
    {
        //This happens inside asserts in the SharedMemory helper.
        //The globals haven't been set up yet.
        //The assertion code avoids dereferencing the globals in this case.
#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast(disable:6011)
#endif
        return *nothing;
#ifdef _MSC_VER
#pragma prefast(pop)
#endif
    }

    return *m_globals;
}

Globals &System::GetGlobals()
{
    Globals *nothing = NULL;
    if (m_globals == NULL)
    {
        //This happens inside asserts in the SharedMemory helper.
        //The globals haven't been set up yet.
        //The assertion code avoids dereferencing the globals in this case.
#ifdef _MSC_VER
#pragma prefast(push)
#pragma prefast(disable:6011)
#endif
        return *nothing;
#ifdef _MSC_VER
#pragma prefast(pop)
#endif
    }

    return *m_globals;
}
