/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#ifndef TEST_BUILD
#define TEST_BUILD
#endif

#include <signal.h>
#include <vector>
#include <sstream>

#include <pal/palcommon.h>

#ifndef NITS_EXPORT
# define NITS_EXPORT PAL_EXTERN_C PAL_EXPORT_API
#endif

#include "nits.h"
#include "Frame.h"

#include <pal/atomic.h>
#include <pal/sleep.h>
#include <pal/sem.h>
#include <pal/cpu.h>
#include <pal/shmem.h>
#include <pal/shlib.h>
#include <pal/thread.h>
#include <pal/format.h>

#define NITS_TRACING_LOCATION L"Microsoft\\NITS"

#define WPP_USE_NTDLL_FUNCTIONS
#define WPP_CONTROL_GUIDS \
    WPP_DEFINE_CONTROL_GUID(NITS,(95bef1fc,d949,42d0,951a,ff1af27a6549), \
        WPP_DEFINE_BIT(TestLifetime)     \
        )

PAL_INLINE void Atomic_Lock(
    _Inout_ volatile ptrdiff_t* dest)
{
    while (Atomic_Swap(dest, 1) == 1)
        while (*dest)
            ;
}

PAL_INLINE void Atomic_Unlock(
    _Inout_ volatile ptrdiff_t* dest)
{
    Atomic_Swap(dest, 0);
}


enum NitsTraceLevel
{
    NitsTraceFailedTests = 1,   //Shows nothing except failed test cases.
    NitsTraceWarnedTests = 2,   //Shows test cases with warnings.
    NitsTraceAllTests    = 3,   //Shows all test cases.
    NitsTraceAsserts     = 3,   //Shows individual asserts.
    NitsTraceWarnings    = 4,   //Shows individual asserts/warnings.
    NitsTraceIterations  = 5,   //Shows fault injection iterations.
    NitsTraceVerbose     = 6    //Shows product and other traces.
};

enum {
    CallSite_NONE = -1,   //Anonymous call site.
    CallSite_ALL = -2     //Automatic fault loops.
};

struct Configuration
{
    NitsTraceLevel traces;
    NitsTestMode mode;
    //NitsIsolationMode isolation;
    //NitsResourceScope scope;
    bool breakAssert;
    bool breakFault;
    bool skipFlakyTests;
};

struct Statistics
{
    unsigned faultIterations;
    unsigned shouldFaults;
    unsigned currentTestProcess;
    unsigned frameLookups;
    unsigned frameInsertions;
    unsigned frameHashHits;
    unsigned frameHits[16];
    unsigned stackLookups;
    unsigned stackTicks;
};

namespace TestSystem
{

using namespace std;

bool StartsWith(_In_z_ const PAL_Char * str, _In_z_ const PAL_Char * prefix);
bool Equals(_In_z_ const PAL_Char * str, _In_z_ const PAL_Char * target);
bool EqualsCI(_In_z_ const PAL_Char * str, _In_z_ const PAL_Char * target);

PAL_Char *Copy(_In_opt_z_ const PAL_Char * str);

class Exception
{
public:
    Exception(_In_ const PAL_Char * message = PAL_T("")) : m_message(message) {}

    const PAL_Char * GetMessage() const {return m_message;}
private:
    const PAL_Char * m_message;
};

inline void FatalError() {throw Exception();}

//Used for defining wostringstream objects in nits.h.
//Avoids public header file dependency on STL.
class Buffer
{
public:
    Buffer(ostringstream &data) : m_data(data) {}

    operator ostringstream &() {return m_data;}

    ostringstream &m_data;

    Buffer(const Buffer&);
    Buffer& operator=( const Buffer& );
};

//Used for defining vector objects in nits.h.
//Avoids public header file dependency on STL.
class ChildList
{
public:
    operator vector<Switch *> const &() const {return m_list;}
    operator vector<Switch *> &() {return m_list;}

    vector<Switch *> m_list;
};

enum SharedStatus
{
    Unloaded = 0,
    Loading,
    Loaded
};

struct Mapping
{
    PAL_Char *m_name;

    Shmem *m_mapping;
    ptrdiff_t volatile *m_status; //Initialization spinlock.

    void *m_data;            //Shared data section.
    long m_bytes;            //Length of data section.

    void *m_copy;            //Initial data values.

    DWORD Initialize(_In_reads_bytes_(bytes) void const *context, long bytes);

    void Reset();
};

class Fault
{
public:
    enum {
        FileSize = 256
    };

    Fault();

    void Reset(int site, int iteration, bool breakOnFault);
    bool ShouldFault(CallSite const &site);
    bool DidFault() const {return m_faulted;}
    void Toggle(bool enabled); 
    CallSite GetFaultedSite() const;

    int m_site;
    int m_iteration;
    volatile ptrdiff_t m_attempt;
    volatile ptrdiff_t m_lock;

    bool m_break;
    bool volatile m_faulted;
    bool volatile m_filtered;
    int m_hit;
    int m_line;
    char m_file[FileSize];

    //Used for filtering causal anomalies.
    ThreadID m_mainThread;
    ptrdiff_t m_minimumAttemptDifferentThread;
    ptrdiff_t m_firstAttemptDifferentThread;
    ptrdiff_t m_faultedAttempt;
};

struct InjectorTarget
{
    void *signalSemaphore;
    void *waitSemaphore;
    void *lockSemaphore;
    ptrdiff_t process;
};

static const int InjectorListSize = 1024;
static const int SharedMemoryVersion = 3; //Increment after each change to Globals.

enum PipeOutputType
{
    NoMessage,
    InfoMessage,
    WttLogTestStart,
    WttLogTestEnd
};

//Internal self-relative data structure.
//Propagates test commands and state across processes.
class Globals
{
public:
    int m_version; //Used to match against SharedMemoryVersion.
    int m_unload;  //Triggers the injector to self-unload everywhere.

    enum {
        PipeSize = 1024,
        StringSize = 256
    };

    Globals();
    ~Globals();

    bool IsUnittestRunning();
    bool StartRun(bool force = false);
    void StopRun();
    void CheckRun();                    //Makes sure the test process is alive.

    void Reset();                       //Erases test status.
    void AttachDebugger();
    void CheckDebugger();
    void SetFault(int site,
                  int attempt,
                  HRESULT error,
                  _In_z_ const PAL_Char * event);
    Fault &GetAutoFault() {return m_simAuto;}

    NitsResult TestExpression(bool test, NitsFaultMode mode);
    NitsResult ShouldFault(CallSite const &site, NitsFaultMode mode);
    NitsResult DidFault();

    void StopReportingIgnoredErrors()
    {
        //This function has no effect if the fault already happened.
        //The purpose is to indicate that *future* faults are purposefully ignored.
        if (!DidFault())
            m_stopReportingIgnoredErrors = true;
    }
    bool ShouldReportIgnoredErrors() {return !m_stopReportingIgnoredErrors;}
    void ResetIgnoredErrorReporting() {m_stopReportingIgnoredErrors = false;}

    HRESULT GetFaultError() const {return m_faultError;}
    Result GetResult() const {return m_result;}
    Configuration const &GetConfiguration() const {return m_config;}
    void SetConfiguration(Configuration const &config) {m_config = config;}
    Statistics &GetStats() {return m_stats;}
    int *GetStatistics() {return m_statistics;}

    void SetResult(Result result) {m_result = result;}
    void SetDebugger(_In_z_ const PAL_Char * debugger);

    void **GetStackTrace() {return m_stackTrace;}

    void SetRunTime(double seconds) {m_runTimeInSeconds = seconds;}
    double GetRunTime() {return m_runTimeInSeconds;}

#if defined(CONFIG_HAVE_BACKTRACE)
    FrameCache m_frames;
#endif

public:
    void PostPipe(_In_z_ const PAL_Char * text, PipeOutputType outputType = InfoMessage);    //Adds text to out-of-proc buffer.
    void DumpPipe();                    //Dumps pipe to stderr.
    bool IsPipeEmpty();
    void LockPipe();
    void UnlockPipe();
    void EmptyPipe();
    PAL_Char *GetPipe() { return m_pipe; }
    PipeOutputType GetPipeOutputType() { return m_pipeOutputType; }
    ptrdiff_t volatile m_runLock;    //PID of test run in progress.    
private:
    ptrdiff_t volatile m_attachLock; //PID of process being attached to debugger.
    ptrdiff_t volatile m_pipeLock;   //Pipe synchronization.
    long m_pipeChars;           //Buffer size used.    

    bool m_stopReportingIgnoredErrors;

    Configuration m_config;
    Statistics m_stats;

    Result m_result;            //Current test result.

public:
    Fault m_simAuto;
    Fault m_simManual;

    PAL_Char m_binaryFilter[1024];
    PAL_Char m_binaryTarget[1024];
    InjectorTarget m_injectors[InjectorListSize];
private:

    int m_statistics[ResultCount];

    HRESULT m_faultError;
    PAL_Char m_faultEvent[Event::MaxName];
    PAL_Char m_pipe[PipeSize];
    PAL_Char m_debugger[1024];   //Used for automatic debugger attaching.

    void *m_stackTrace[50];
    double m_runTimeInSeconds;
    PipeOutputType m_pipeOutputType;
};

class System
{
public:
    static System &GetInstance() {return s_system;}

    System();
    ~System();

    NamedSem *GetPipeEvent() const {return (NamedSem *)&m_pipeEvent;}
    Globals const &GetGlobals() const;
    Globals &GetGlobals();
    Mapping &GetMapping(_In_z_ const PAL_Char * name);
    void ResetClientMappings();
private:
    NamedSem m_pipeEvent;
    Globals *m_globals;
    vector<Mapping> m_mappings;
    static System s_system;
};

inline Globals &GetGlobals() {return System::GetInstance().GetGlobals();}

}; //namespace TestSystem

/*
**==============================================================================
**
** Conversion functions between Ansi/WideChar/PAL_Char strings
**
**==============================================================================
*/
PWSTR ConvertStringToW(_In_opt_z_ const char *buf);
PSTR ConvertStringToA(_In_opt_z_ const wchar_t *buf);
PAL_Char *ConvertStringAToPalChar(_In_opt_z_ const char *buf);
PAL_Char *ConvertStringWToPalChar(_In_opt_z_ const wchar_t *buf);
char *ConvertPalCharToStringA(_In_opt_z_ const PAL_Char *buf);

#define MyDebugBreak raise(SIGTRAP)

#endif // ndef __GLOBALS_H__
