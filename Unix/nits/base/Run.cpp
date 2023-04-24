/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "Run.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <pal/strings.h>
#include <pal/file.h>

using namespace std;
TestSystem::Run g_run;

NITS_EXPORT bool NitsParseArgument(_In_z_ char *str)
{
    bool result = g_run.ParseArgument(str);
    return result;
}

NITS_EXPORT int NitsExecuteRun()
{
    return g_run.Execute();
}

NITS_EXPORT int NitsCheckVersion(int version)
{
    if (TestSystem::SharedMemoryVersion == version)
    {
        return 1;
    }

    Tprintf(PAL_T("ERROR: Shared memory version mismatch. Please unload and update NITS binaries.\n"));
    return 0;
}

class BSTRBuffer
{
public:
    BSTRBuffer(_In_z_ const PAL_Char *text)
    {
        unsigned count = (unsigned)Tcslen(text);
 
        unsigned available = (sizeof(m_data) - sizeof(unsigned))/sizeof(PAL_Char) - 1;
        if (count > available)
        {
            count = available;
        }

        PAL_Char *string = GetBSTR();
        memcpy(string, text, count * sizeof(PAL_Char));
        string[count] = '\0';        
        *reinterpret_cast<unsigned *>(m_data) = count * sizeof(PAL_Char);
    }

    PAL_Char *GetBSTR()
    {    
        return reinterpret_cast<PAL_Char *>(m_data + sizeof(unsigned));
    }
private:
    char m_data[256];
};

using namespace std;
using namespace TestSystem;

bool InstallInjector()
{
    FILE* fp = File_Open(CONFIG_TMPDIR "/NitsInstalled", "wb");    
    if(fp)
    {
        File_Close(fp);
    }
    else
    {
        Tprintf(PAL_T("ERROR: NITS could not be installed\n"));
        return false;
    }

    /* In case this was set, clear it. */
    GetGlobals().m_unload = 0;

    Tprintf(PAL_T("WARNING: Pre-existing processes are not affected by injector. To fix this, reboot.\n"));

    return true;

}

void RemoveInjector()
{
    int result = File_Remove(CONFIG_TMPDIR "/NitsInstalled");
    if(result != 0)
    {
        Tprintf(PAL_T("ERROR:- NITS could not be uninstalled\n"));
    }

    /* When the test run starts, make all the injectors unload. */
    GetGlobals().m_unload = 1;
}


FixtureInvocation::FixtureInvocation(_In_opt_ FixtureInvocation *parentFixtureInvocationParam, 
                                    _In_ BodyProc funcParam, 
                                    _In_ void *selfContextParam,
                                    TestFixtureType fixtureTypeParam):
    parentFixtureInvocation(parentFixtureInvocationParam),
    func(funcParam),
    selfContext(selfContextParam),
    fixtureType(fixtureTypeParam),
    executedInCurrentIteration(false)
{
}

void FixtureInvocation::Execute()
{
    if(executedInCurrentIteration)
    {
        Tprintf(PAL_T("ERROR: Internal logic error, we are executing the same fixture again during fault simulation iteration; Quitting.\n"));
        throw Exception();
    }

    executedInCurrentIteration = true;

    (*func)(selfContext);
}

Run *Run::s_run = NULL;

Run &Run::GetInstance()
{
    if (s_run == NULL)
    {
        throw Exception();
    }

    return *s_run;
}

bool Run::IsValid()
{
    return s_run != NULL;
}

Param::Param(_In_z_ const PAL_Char *name,
             _In_z_ const PAL_Char *value)
    : m_name(Copy(name)),
      m_value(Copy(value))
{
}

Param::~Param()
{
    delete [] m_name;
    delete [] m_value;
}

Module::Module(_In_z_ const PAL_Char *name)
    : m_name(Copy(name)),
      m_library(NULL)
{
}

void Module::Unload()
{
    if(m_library)
    {
#if !defined(aix) && !defined(hpux)
        // Workaround for problems with dlclose on hpux and aix. 
        Shlib_Close(m_library);
#endif
        m_library = NULL;
    }
}

Module::~Module()
{
    delete [] m_name;

    Unload();

    for (DWORD i = 0; i < m_runs.size(); i++)
    {
        delete [] m_runs[i];
    }
}

void Module::SetLibrary(_In_ Shlib *lib)
{
    if (m_library != NULL)
    {
        throw Exception();
    }

    m_library = lib;
}

void Module::AddTest(_In_ Test *test)
{
    m_tests.push_back(test);
}

void Module::AddRun(_In_z_ const PAL_Char *command)
{
    m_runs.push_back(Copy(command));
}

void Module::RunMatchingTests(_In_z_ const PAL_Char * testNameSubstring)
{
    for (size_t i = 0; i < m_tests.size(); i++)
    {
        /* TODO/FIXME - support real wildcards, not just a substring match */
        if (Tcsstr(m_tests[i]->GetName(), testNameSubstring))
        {
            Run::GetInstance().ExecuteTest(m_tests[i], NULL);
        }
    }
}

void Module::RunTests(size_t start)
{
    for (size_t i = start; i < m_tests.size(); i++)
    {
        Run::GetInstance().ExecuteTest(m_tests[i], NULL);
    }
}

size_t Module::Find(_In_z_ const PAL_Char *test) const
{
    for (size_t i = 0; i < m_tests.size(); i++)
    {
        if (EqualsCI(m_tests[i]->GetName(), test))
        {
            return i;
        }
    }

    Tprintf(PAL_T("%T%T%T"), PAL_T("ERROR: Invalid test name '"), test, PAL_T("'\n"));
    return m_tests.size();
}

void Module::RunModuleLevelTests(bool runCleanup)
{            
    // We want to run module level tests once only if
    // 1. we are in isolation mode and we are child process
    // 2. we are in non-isolation mode in which case we will run other tests in the parent process and so we should run module setup here
    if(!(Run::GetInstance().IsChild()))
        return;

    // Find and run moduleSetups if any exist    
    for (size_t i = 0; i < m_tests.size(); i++)
    {
        Test *currentTest = m_tests[i];
        if(currentTest->IsNewInterfaceTest())
        {
            struct RegistrationInfo *r = (struct RegistrationInfo *) (currentTest->m_registration);
            if(ModuleSetupFixture == r->fixtureType)
            {
                if(!runCleanup)
                {
                    currentTest->m_cleanupMode = TestSystem::Test::DeferredCleanup;
                    // running ModuleSetups in isolation doesnt make any sense since 
                    // they are run for the module once anyways and any other test which 
                    // will run in isolation will get its ModuleSetup run in the child process
                    currentTest->m_isolation = false;
                    Run::GetInstance().ExecuteTest(currentTest, NULL, r->fixtureType);
                }
                else
                {
                    Run::GetInstance().ExecuteDeferredCleanup(currentTest);
                }
            }
        }                
    }
}

void Module::Execute()
{
    // Find and run moduleSetups if any exist    
    RunModuleLevelTests(false);

    //Iterate through the list of commands.
    //Parse each command and run relevant tests.
    for (DWORD i = 0; i < m_runs.size(); i++)
    {
        PAL_Char *command = m_runs[i];
        if (command == NULL)
        {
            //Run all tests.
            RunTests(0);
        }
        else if (StartsWith(command, PAL_T("+")))
        {
            //Search for a test and run subsequent tests.
            RunTests(Find(command + 1));
        }
        else if (StartsWith(command, PAL_T("*")))
        {
            RunMatchingTests(command + 1);
        }
        else
        {
            //Run a specific test and/or variation.
            PAL_Char *slash = Tcschr(command, PAL_T('/'));
            PAL_Char *choices = NULL;
            if (slash)
            {
                *slash = '\0';
                choices = slash + 1;
            }

            size_t i = Find(command);
            if (i < m_tests.size())
            {
                 Run::GetInstance().ExecuteTest(m_tests[i], choices);
            }
        }
    }

    // TODO:Find and run moduleCleanups if any exist
    RunModuleLevelTests(true);
}

Run::Run()
    : m_currentTest(NULL),
      m_loadingModule(NULL),
      m_modules(NULL),
      m_params(NULL),
      m_pause(false),
      m_reset(false),
      m_debugger(NULL),
      m_binaryFilter(NULL),
      m_binaryTarget(NULL),
      m_testFilter(NULL),
      m_isolation(false),
      m_child(false),
      m_fault(false),
      m_finished(false),
      m_statistics(NULL),
      m_enabled(true),
      m_flaky(false),
      m_simMode(Manual),
      m_exclusions(NULL),
      m_exclusionsCount(0),
      m_runningFaultInjectionLoop(false),
      m_nextFixtureInvocationToExecute(0)
{
    if (s_run != NULL)
    {
        throw Exception();
    }

    s_run = this;

    m_modules = new vector<Module *>;
    m_params = new vector<Param *>;
    m_bpFault = new vector<int>;
    if (m_modules == NULL || m_params == NULL || m_bpFault == NULL)
    {
        throw Exception();
    }

    memset(&m_config, 0, sizeof(Configuration));
    memset(&m_translatedTestFilter, 0, sizeof(m_translatedTestFilter));
}

Run::~Run()
{
    ClearTestVariationNodes();    

    ClearFixtureInvocations();

    for (DWORD i = 0; i < Modules().size(); i++)
    {
        delete Modules()[i];
    }

    m_loadingModule = NULL;

    for (DWORD i = 0; i < Params().size(); i++)
    {
        delete Params()[i];
    }

    delete m_modules;
    delete m_params;
    delete m_bpFault;
    delete [] m_debugger;
    delete [] m_binaryFilter;
    delete [] m_binaryTarget;
    delete [] m_testFilter;
    delete [] m_wtt;

    s_run = NULL;
}

const PAL_Char *Run::GetParam(_In_z_ const PAL_Char *name) const
{
    for (DWORD i = 0; i < Params().size(); i++)
    {
        if (Tcscasecmp(Params()[i]->m_name, name) == 0)
        {
            return Params()[i]->m_value;
        }
    }

    return NULL;
}

void Run::AddModule(_In_z_ const PAL_Char *name)
{
    Module *p = new Module(name);
    if (p == NULL)
    {
        throw Exception();
    }
    try
    {
        Modules().push_back(p);
    }
    catch(...)
    {
        delete p;
        throw;
    }
    m_loadingModule = p;
}

bool Run::AddParam(_In_z_ const PAL_Char *name, _In_z_ const PAL_Char *value)
{
    for (DWORD i = 0; i < Params().size(); i++)
    {
        if (Equals(Params()[i]->m_name, name))
        {
            Tprintf(PAL_T("%T%T%T"), PAL_T("ERROR: Test parameter '"), name, PAL_T("' defined multiple times.\n"));
            return false;
        }
    }

    Param *p = new Param(name, value);
    if (p == NULL)
    {
        throw Exception();
    }

    Params().push_back(p);
    return true;
}

bool Run::AddRun(_In_z_ const PAL_Char *name, _In_z_ const PAL_Char *test)
{
    if (name[0] == '\0')
        return true;

    //Find out if this module is already loaded.
    Module *match = NULL;
    for (DWORD i = 0; i < Modules().size(); i++)
    {
        if (Equals(Modules()[i]->GetName(), name))
        {
            match = Modules()[i];
            break;
        }
    }
    
    if (match == NULL)
    {
        AddModule(name);
        match = m_loadingModule;

        /* Set m_runLock so that NitsIsActivated() returns true in here. This
         * prevents the test code from thinking that NITS is inactive during
         * initialization. */
        System &system = System::GetInstance();
        Globals &globals = system.GetGlobals();
        bool setRunLock = (Atomic_CompareAndSwap(&globals.m_runLock, 0, 1) == 0);

        Shlib *lib = NULL;

        lib = Shlib_Open_Injected(name, NitsReservedCallSite());

        if (setRunLock)
        {
            Atomic_CompareAndSwap(&globals.m_runLock, 1, 0);
        }


        if(!lib)
        {
            PAL_Char *err;
            err = Shlib_Err(); 
            Tprintf(PAL_T("%T%T%T%T%T"), PAL_T("ERROR: Could not load test module. File='"), tcs(name), PAL_T("', Reason="), tcs(err), PAL_T("\n"));
            if (err)
                Shlib_FreeErr(err);
            return false;
        }

        match->SetLibrary(lib);
    }

    match->AddRun(test);
    return true;
}

void Run::DumpPipe()
{
    System &system = System::GetInstance();
    Globals &globals = system.GetGlobals();
    globals.LockPipe();
    PAL_Char *globalPipe = globals.GetPipe();
    PipeOutputType globalPipeOutputType = globals.GetPipeOutputType();

    static ofstream s_log("nits.log");    
    if(globalPipeOutputType == InfoMessage)
    {
        char buf[Globals::PipeSize];
        int convertCount = Strlen(globalPipe);
        Strlcpy(buf, globalPipe, convertCount + 1);
        buf[convertCount] = PAL_T('\0');

        s_log << buf;
                  
        Tprintf(globalPipe);
        fflush(stdout);
    } 

    globals.EmptyPipe();    
    globals.UnlockPipe();
    globals.AttachDebugger();
}


NITS_EXTERN_C PAL_Uint32 THREAD_API _PipeThread(void* param)
{
    Run &run = Run::GetInstance();
    run.PipeThread();
    return 0;
}

void Run::PipeThread()
{
    System &system = System::GetInstance();
    NamedSem *event = system.GetPipeEvent();

    do {
        DumpPipe();
        NamedSem_TimedWait(event, 200);
    } while (!m_finished);

    DumpPipe();
}

static void TranslateStringList(
    _In_opt_z_ const PAL_Char *source,
    _Out_writes_(bytes) PAL_Char *dest,
    unsigned bytes)
{
    unsigned length;
    unsigned i;

    if (source == NULL)
    {
        dest[0] = PAL_T('\0');
        return;
    }

    length = (unsigned)Tcslen(source);
    size_t toUse = min(length + 1, bytes);
    
    Tcslcpy(dest, source, toUse);

    for (i = 0; i < length && i < bytes; i++)
    {
        if ((dest[i] == PAL_T(';')) ||
            (dest[i] == PAL_T(',')))
        {
            dest[i] = PAL_T('\0');
        }
    }
    dest[bytes - 1] = PAL_T('\0');
}

static Globals g_tempGlobals;

int Run::Execute()
{
    System &system = System::GetInstance();
    Globals &globals = system.GetGlobals();
    m_statistics = globals.GetStatistics();
    Thread pipeThread;
    PAL_Uint32 threadJoinResult = 0;
    memset(&pipeThread, 0, sizeof(Thread));
    
    if (m_config.traces == 0)
    {
        m_config.traces = NitsTraceAllTests;
    }

    if (m_config.mode == 0)
    {
        m_config.mode = NitsTestCompoundFault;
    }

    ptrdiff_t startTicks = CPU_GetTimeStamp();

    // translate ; or , separated list of Filtered switches into \0 separated one
    TranslateStringList(m_testFilter, m_translatedTestFilter, sizeof(m_translatedTestFilter)/sizeof(PAL_Char));

    if (IsParent())
    {        
        TranslateStringList(m_binaryFilter, globals.m_binaryFilter, (sizeof(globals.m_binaryFilter))/sizeof(PAL_Char));
        TranslateStringList(m_binaryTarget, globals.m_binaryTarget, (sizeof(globals.m_binaryTarget))/sizeof(PAL_Char));

        if (!globals.StartRun(m_reset))
        {
            Tprintf(PAL_T("ERROR: Another test run is in progress! Please run \"nits -reset\" to terminate the other run.\n"));
            return 1;
        }

        if (m_reset)
        {
            //Reset globals.
            TranslateStringList(m_binaryFilter, g_tempGlobals.m_binaryFilter, (sizeof(g_tempGlobals.m_binaryFilter))/sizeof(PAL_Char));
            TranslateStringList(m_binaryTarget, g_tempGlobals.m_binaryTarget, (sizeof(g_tempGlobals.m_binaryTarget))/sizeof(PAL_Char));
            g_tempGlobals.StartRun();
            globals = g_tempGlobals;
        }

        if(Thread_CreateJoinable_Injected(&pipeThread, _PipeThread, NULL, NULL, NitsReservedCallSite()) != NO_ERROR)
        {
            globals.StopRun();
            Tprintf(PAL_T("ERROR: Failed to create pipe thread!\n"));
            return 1;
        }
    }
    
    unsigned returnCode = 0;

    //TODO: Reset XML output file here.
    //After this, everybody opens for append.

    for (DWORD i = 0; i < Modules().size(); i++)
    {
        Modules()[i]->Execute();
        Modules()[i]->Unload();
    }

    //TODO: Finish and close XML output file here.    

    if (IsParent())
    {
        if (Modules().size() > 0)
            returnCode = ReportStatistics();

        if (m_pause)
        {
            SetDefaultOptions(); //Mainly used for debugger setting.
            globals.PostPipe(PAL_T("PAUSED: Press ENTER to continue..."));
            fgetc(stdin);
        }

        if (Modules().size() > 0)
        {
            Statistics const &stats = globals.GetStats();
            ptrdiff_t stopTicks = CPU_GetTimeStamp();
            double seconds = float(stopTicks - startTicks) / 1000000.0;
            // double stackTicks = (double)stats.stackTicks / ((double)stats.stackLookups+0.00001);
            ostringstream buf;
            buf << "TOTAL RUNNING TIME: " << seconds << " seconds" << endl
                << "TOTAL FAULT ITERATIONS: " << stats.faultIterations << endl
                << "TOTAL SHOULDFAULT CALLS: " << stats.shouldFaults << endl;
    
            //double percentage = 100.0 * (double)stats.shouldFaultIPCs / ((double)stats.shouldFaults+0.00001);
            //buf << "TOTAL CROSS-PROCESS SHOULDFAULT CALLS: " << stats.shouldFaultIPCs << " (" << percentage << "%)\n"
            buf << "TOTAL STACK PROBES: " << stats.stackLookups << endl
            //    << "AVERAGE TICKS/STACK PROBE: " << stackTicks << endl
                << "TOTAL FRAME PROBES: " << stats.frameLookups << endl;
    
            /*unsigned remaining = stats.frameLookups;
            unsigned target = stats.frameInsertions;
            double percentage = 100.0 * (double)target / remaining;
            buf << "TOTAL FRAME MISSES: " << target << "/" << remaining << " (" << percentage << "%)\n";
    
            remaining -= target;
            target = stats.frameHashHits;
            percentage = 100.0 * (double)target / remaining;
            buf << "REMAINDER, HASH HITS: " << target << "/" << remaining << " (" << percentage << "%)\n";
    
            for (int i = 0; i < 16; i++)
            {
                if (stats.frameHits[i] == 0)
                {
                    continue;
                }
    
                remaining -= target;
                target = stats.frameHits[i];
                percentage = 100.0 * (double)target / remaining;
                buf << "REMAINDER, LEVEL " << i+1 << " CACHE HITS: " << target
                    << "/" << remaining << " (" << percentage << "%)\n";
            }*/
            PAL_Char *postPipeStr = ConvertStringAToPalChar(buf.str().c_str());
            globals.PostPipe(postPipeStr);
            delete [] postPipeStr;
        }

        m_finished = true;

        NamedSem_Post(system.GetPipeEvent(), 1);

        Thread_Join(&pipeThread, &threadJoinResult);

        globals.StopRun();
    }

    for (DWORD i = 0; i < Modules().size(); i++)
        delete Modules()[i];
    Modules().clear();

    return returnCode;
}

void Run::ExecuteDeferredCleanup(_In_ Test *test)
{
    m_currentTest = test; 
    m_currentTest->RunDeferredCleanup();
}

void Run::ExecuteTest(_In_ Test *test, _In_opt_ const PAL_Char *choices,
                      TestFixtureType executeIfTypeIs /* = BodyFixture */)
{    
    if(test->IsNewInterfaceTest())
    {         
        struct RegistrationInfo *r = (struct RegistrationInfo *) (test->m_registration);
        if(executeIfTypeIs != r->fixtureType)
            return;
    }

    m_currentTest = test;    

    //Spawn a child process to run the test for us.
    //Construct the same argument list, but for this particular test.
    ostringstream buf, repro;
    if (m_debugger)
    {
        buf << m_debugger << " ";
        repro << m_debugger << " ";
    }

    buf << "nits.exe -child " << test->GetModule() << ":" << test->GetName();
    repro << "nits.exe " << test->GetModule() << ":" << test->GetName();
    if (choices)
    {
        buf << "/" << choices;
        repro << "/" << choices;
    }

    if (m_config.traces == NitsTraceFailedTests)
    {
        buf << " -trace:FailedTests";
    }
    else if (m_config.traces == NitsTraceWarnedTests)
    {
        buf << " -trace:WarnedTests";
    }
    else if (m_config.traces == NitsTraceAllTests)
    {
        buf << " -trace:AllTests";
    }
    else if (m_config.traces == NitsTraceAsserts)
    {
        buf << " -trace:Asserts";
    }
    else if (m_config.traces == NitsTraceWarnings)
    {
        buf << " -trace:Warnings";
    }
    else if (m_config.traces == NitsTraceIterations)
    {
        buf << " -trace:Iterations";
    }
    else //NitsTraceVerbose.
    {
        buf << " -trace:Verbose";
    }

    if (m_config.mode == NitsTestSkip)
    {
        buf << " -mode:Skip";
    }
    else if (m_config.mode == NitsTestEnable)
    {
        buf << " -mode:Enable";
    }
    else if (m_config.mode == NitsTestIterativeFault)
    {
        buf << " -mode:IterativeFault";
    }
    else if (m_config.mode == NitsTestStackFault)
    {
        buf << " -mode:StackFault";
    }
    else //NitsTestCompoundFault.
    {
        buf << " -mode:CompoundFault";
    }

    if (m_config.breakAssert)
    {
        buf << " -bpassert";
    }

    if (m_config.skipFlakyTests)
    {
        buf << " -skipflaky";
    }

    if (m_fault)
    {
        buf << " -fault";
        repro << " -fault";
    }
    if (m_debugger)
    {
        buf << " -debug:\"" << m_debugger << "\"";
        repro << " -debug:\"" << m_debugger << "\"";
    }

    if(m_testFilter)
    {
        buf << " -match:" << m_testFilter;
    }

    vector<Param *> &params = Params();
    for (size_t i = 0; i < params.size(); i++)
    {
        buf << " +" << params[i]->m_name << ":" << params[i]->m_value;
        repro << " +" << params[i]->m_name << ":" << params[i]->m_value;
    }

    test->Execute(choices);

    if(test->m_deleteMeAfterRun)
    {
        delete test;
    }
}

void Run::SetDefaultOptions()
{
    Globals &globals = GetGlobals();

    m_exclusions = NULL;
    m_exclusionsCount = 0;
    m_enabled = m_config.mode >= NitsTestEnable;
    m_simMode = m_fault ? Automatic : Manual;

    globals.Reset();
    globals.SetConfiguration(m_config);
    if (m_debugger != NULL)
    {
        globals.SetDebugger(m_debugger);
    }
}

void Run::ReportResult()
{
    Test *test = GetCurrentTest();

    const char *results[] = {"[Faulted]",
                        "[Passed] ",
                        "[Skipped]",
                        "[Omitted]",                        
                        "[Killed] ",
                        "[Failed] ",
                        "[Error]  "};

    Globals &globals = GetGlobals();
    Result result = globals.GetResult();
    double seconds = globals.GetRunTime();

    if (result < Faulted || result > Error)
    {
        FatalError();
        return;
    }

    m_statistics[result]++;

    if(test->m_filteredOutByUser)
        return;

    if (result < Killed && globals.GetConfiguration().traces == NitsTraceFailedTests)
    {
        return;
    }
    
    ostringstream buf;
    buf << "\t" << results[result] << " ";
    Buffer wrappedBuf(buf);
    test->PrintName(wrappedBuf, !m_isolation);
    buf << "\t" << seconds;
    buf << "\n";

    //TODO: Dump XML output in addition to stderr.
    PAL_Char *postPipeStr = ConvertStringAToPalChar(buf.str().c_str());
    globals.PostPipe(postPipeStr);
    delete [] postPipeStr;
}

unsigned Run::ReportStatistics()
{
    int passed = m_statistics[Faulted] +
                 m_statistics[Passed];
    int failed = m_statistics[Killed] +
                 m_statistics[Failed] +
                 m_statistics[Error];
    int total = passed + failed;

    const char *results[] = {"Faulted: ",
                                "Passed:  ",
                                "Skipped: ",
                                "Omitted: ",                                                        
                                "Killed:  ",
                                "Failed:  ",
                                "Error:   "};


    //TODO: Include relevant summary information in XML output.
    ostringstream buf;
    buf << "\n\nSummary:\n";
    for (int i = 0; i < ResultCount; i++)
    {
        buf << "\t" << results[i] << "\t" << m_statistics[i] << "\n";
    }

    buf << "\n"
           "\tSuccesses:\t" << passed << "\n"
           "\tFailures:\t" << failed << "\n"
           "\tTotal:\t\t" << total << "\n";
    
    Globals &globals = GetGlobals();
    PAL_Char *postPipeStr = ConvertStringAToPalChar(buf.str().c_str());
    globals.PostPipe(postPipeStr);
    delete [] postPipeStr;
    return failed ? 1 : 0;
}

bool Run::IsSiteExcluded(int site) const
{
    for (int i = 0; i < m_exclusionsCount; i++)
    {
        //ignore everything if exclusions is zero
        if (m_exclusions[i] == 0)
        {
            return true;
        }

        //check for specific exclusion
        if (m_exclusions[i] == site)
        {
            return true;
        }
    }
    
    return false;
}

void Run::SetExclusions(_In_reads_opt_(count) int sites[], int count)
{
    m_exclusions = sites;
    m_exclusionsCount = count;
}

bool Run::ParseArgument(_In_ char *arg)
{
	char *temp = strchr(arg, ':');
	char *second = NULL;

    if (arg[0] != '-' && arg[0] != '+')
    {
        /* This is not an option. Must be a test path. */

        /* Ignore the colon in drive-letter paths. */
        if (temp && (temp[1] == '\\' || temp[1] == '/'))
            temp = strchr(temp + 1, ':');

        /* New test path format matches WinDBG symbol. */
        if (temp == NULL)
            temp = strchr(arg, '!');
    }

    if (temp)
    {
        *temp = '\0';
        second = temp + 1;
    }

    if (!Strcasecmp(arg, "-localinjection"))
    {
        if (!ConfigureLocalInjection())
            return false;
    }
    else if (!Strcasecmp(arg, "-bpassert"))
    {
        m_config.breakAssert = true;
    }
    else if (!Strcasecmp(arg, "-skipflaky"))
    {
        m_config.skipFlakyTests = true;
    }
    else if (!Strcasecmp(arg, "-bpfault"))
    {
        m_config.breakFault = true;
        if (second == NULL)
        {
            Tprintf(PAL_T("ERROR: 'bpfault' option requires an iteration number!\n"));
            return false;
        }

        m_bpFault->push_back(Strtoul(second, 0, 10));
    }
    else if (!Strcasecmp(arg, "-file"))
    {
        //Open file, tokenize, and parse contents.
        if (second == NULL)
        {
            Tprintf(PAL_T("ERROR: 'file' option requires a filename!\n"));
            return false;
        }

        char buf[MAX_PATH];
		Strlcpy(buf, second, MAX_PATH);

        ifstream file(buf);
        if (!file.good())
        {
            Tprintf(PAL_T("%T%T%T"), PAL_T("ERROR: file '"), second, PAL_T("' could not be loaded!\n"));
            return false;
        }
        while (file.good())
        {
            char widebuf[MAX_PATH];

            memset(buf, 0, sizeof(buf));

            file.width(MAX_PATH);
            file >> buf;

            // allow empty lines or commented lines with #
            if (buf[0] == '\0' || buf[0] == '#')
                continue;
            
            int size = Strlcpy(widebuf, buf, MAX_PATH);
            if (size == 0)
            {
                throw Exception();
            }

            if (!ParseArgument(widebuf))
                return false;
        }
    }
    else if (!Strcasecmp(arg, "-filter"))
    {
        if (m_binaryFilter)
            delete [] m_binaryFilter;

        m_binaryFilter = ConvertStringAToPalChar(second);
    }
    else if (!Strcasecmp(arg, "-match"))
    {
        if (m_testFilter)
            delete [] m_testFilter;

        if (!second || (second[0] == '\0'))
        {
            Tprintf(PAL_T("ERROR: '-match' option requires at least one string to match with!\n"));
            return false;
        }

        m_testFilter = ConvertStringAToPalChar(second);
    }
    else if (!Strcasecmp(arg, "-install"))
    {
        if (!InstallInjector())
            return false;
    }
    else if (!Strcasecmp(arg, "-mode"))
    {
        if (!second)
        {
            Tprintf(PAL_T("ERROR: 'mode' option requires a mode to be selected!\n"));
            return false;
        }
        else if (!Strcasecmp(second, "Skip"))
        {
            m_config.mode = NitsTestSkip;
        }
        else if (!Strcasecmp(second, "Enable"))
        {
            m_config.mode = NitsTestEnable;
        }
        else if (!Strcasecmp(second, "IterativeFault"))
        {
            m_config.mode = NitsTestIterativeFault;
        }
        else if (!Strcasecmp(second, "StackFault"))
        {
            m_config.mode = NitsTestStackFault;
        }
        else if (!Strcasecmp(second, "CompoundFault"))
        {
            m_config.mode = NitsTestCompoundFault;
        }
        else
        {
            Tprintf(PAL_T("ERROR: Invalid value for 'mode' option!\n"));
            return false;
        }
    }
    else if (!Strcasecmp(arg, "-pause"))
    {
        m_pause = true;
    }
    else if (!Strcasecmp(arg, "-reset"))
    {
        m_reset = true;
    }
    else if (!Strcasecmp(arg, "-target"))
    {
        if (m_binaryTarget)
            delete [] m_binaryTarget;

        m_binaryTarget = ConvertStringAToPalChar(second);
    }
    else if (!Strcasecmp(arg, "-trace"))
    {
        if (!second || !Strcasecmp(second, "Verbose"))
        {
            m_config.traces = NitsTraceVerbose;
        }
        else if (!Strcasecmp(second, "FailedTests"))
        {
            m_config.traces = NitsTraceFailedTests;
        }
        else if (!Strcasecmp(second, "WarnedTests"))
        {
            m_config.traces = NitsTraceWarnedTests;
        }
        else if (!Strcasecmp(second, "AllTests"))
        {
            m_config.traces = NitsTraceAllTests;
        }
        else if (!Strcasecmp(second, "Asserts"))
        {
            m_config.traces = NitsTraceAsserts;
        }
        else if (!Strcasecmp(second, "Warnings"))
        {
            m_config.traces = NitsTraceWarnings;
        }
        else if (!Strcasecmp(second, "Iterations"))
        {
            m_config.traces = NitsTraceIterations;
        }
        else
        {
            Tprintf(PAL_T("ERROR: Invalid value for 'trace' option!\n"));
            return false;
        }
    }
    else if (!Strcasecmp(arg, "-uninstall"))
    {
        RemoveInjector();
    }
    //V1 compatibility options.
    else if (!Strcasecmp(arg, "-assert"))
    {
    }
    else if (!Strcasecmp(arg, "-noassert"))
    {
        m_config.traces = NitsTraceAllTests;
    }
    else if (!Strcasecmp(arg, "-child"))
    {
        m_child = true;
    }
    else if (!Strcasecmp(arg, "-fault"))
    {
        m_fault = true;

        if (second)
        {
            m_config.breakFault = true;
            m_bpFault->push_back(Strtoul(second, 0, 10));
        }
    }
    else if (!Strcasecmp(arg, "-output"))
    {
        Tprintf(PAL_T("ERROR: 'output' option is not implemented!\n"));
        return false;
    }
    else if (!Strcasecmp(arg, "-skip"))
    {
        m_config.mode = NitsTestSkip;
    }
    else if (!Strcasecmp(arg, "-verbose"))
    {
        m_config.traces = NitsTraceVerbose;
    }
    else if (!Strcasecmp(arg, "-noverbose"))
    {
    }
    else if (!Strncmp(arg, "+", Strlen("+")))
    {
        //Spurious prefast warning.
        if (strlen(arg) < 1)
            throw Exception();

        if ((second == NULL) || (second[0] == '\0'))
        {
            Tprintf(PAL_T("%T%T%T"), PAL_T("ERROR: Custom argument "), arg, PAL_T(" should be of the form +name:value!\n"));
            return false;
        }

        AddParam(ConvertStringAToPalChar(arg+1), ConvertStringAToPalChar(second));
    }
    else
    {
        PAL_Char *palCharArg = ConvertStringAToPalChar(arg);
        PAL_Char *palCharSecond = ConvertStringAToPalChar(second);
        bool addRunSuccess = AddRun(palCharArg, palCharSecond);
        delete [] palCharArg;
        delete [] palCharSecond;
        //Error message already printed.
        if(!addRunSuccess)
            return false;
    }

    return true;
}

PAL_Char *Run::GetTestVariationNodeNames()
{
    ostringstream buf;
    buf << "\t          ";        

    for(size_t i = 0; i < m_currentTestVariationNodes.size(); i++)
    {
        buf << m_currentTestVariationNodes[i]->GetName() << ",";
    }

    buf << "...\n";

    return ConvertStringAToPalChar(buf.str().c_str());
}

// TODO: Move this into PAL
static PAL_Boolean DoesTestMatch(
    _In_ PAL_Char *list,
    _In_z_ const PAL_Char *name)
{
    if (*list == '\0')
        return PAL_TRUE;

    for (;;)
    {
        if (*list == '\0')
            return PAL_FALSE;
        
        if (Tcsstr(name, list))
            return PAL_TRUE;

        list += Tcslen(list) + 1;
    }
}

void Run::AddFixtureInvocation(_In_opt_ BodyProc parentFixtureFuncParam, _In_ BodyProc funcParam, _In_ void *selfContextParam, TestFixtureType fixtureTypeParam)
{    
    FixtureInvocation *parentFixtureInvocation = NULL;
    FixtureInvocation *fixtureInvocation = NULL;

    if(parentFixtureFuncParam != NULL)
    {
        size_t count = m_currentTestFixtureInvocations.size();

        for(size_t i = 0; i < count; i++)
        {
            fixtureInvocation = m_currentTestFixtureInvocations[i];
            if(fixtureInvocation->func == parentFixtureFuncParam)
            {
                parentFixtureInvocation = fixtureInvocation;
                break;
            }
        }

        if(parentFixtureInvocation == NULL)
        {
            Tprintf(PAL_T("ERROR: Internal logic error, cleanup is being run on a switch for which we skipped running setup; Quitting.\n"));
            throw Exception();
        }
    }

    fixtureInvocation = new FixtureInvocation(parentFixtureInvocation, funcParam, selfContextParam, fixtureTypeParam);
    if(fixtureInvocation == NULL)
    {
        Tprintf(PAL_T("ERROR: Out of memory error when adding fixture invocation; Quitting.\n"));
        throw Exception();
    }

    m_currentTestFixtureInvocations.push_back(fixtureInvocation);
}

void Run::ResetFixtureInvocationStateForRerun()
{
    size_t count = m_currentTestFixtureInvocations.size();

    for(size_t i = 0; i < count; i++)
    {
        m_currentTestFixtureInvocations[i]->executedInCurrentIteration = false;
    }

    m_nextFixtureInvocationToExecute = 0;
}

bool Run::DoneExecutingAllFixtureInvocations()
{    
    if(m_nextFixtureInvocationToExecute >= m_currentTestFixtureInvocations.size())
        return true;
    else
        return false;
}

void Run::ExecuteNextFixtureInvocationDuringFaultSim()
{    
    size_t count = m_currentTestFixtureInvocations.size();
    if(m_nextFixtureInvocationToExecute >= count)
        return;

    Globals &globals = GetGlobals();
    Fault &fault = globals.GetAutoFault();    
    FixtureInvocation *fixtureInvocation = NULL;
    fault.Toggle(false);

    if(globals.GetResult() == Passed)
    {
        m_nextFixtureInvocationToExecute++;        
        fixtureInvocation = m_currentTestFixtureInvocations[m_nextFixtureInvocationToExecute - 1];
        if(fixtureInvocation->fixtureType == BodyFixture)
        {
            fault.Toggle(true); // turn on fault injection only for body fixtures
        }

        fixtureInvocation->Execute();

        fault.Toggle(false); 
    }
    else
    {
        for(size_t i = m_nextFixtureInvocationToExecute; i < count; i++)
        {
            fixtureInvocation = m_currentTestFixtureInvocations[i];
            if((fixtureInvocation->parentFixtureInvocation != NULL) && (fixtureInvocation->parentFixtureInvocation->executedInCurrentIteration))
            {
                m_nextFixtureInvocationToExecute = i + 1;
                fixtureInvocation->Execute(); // this can not be a body fixture; it has to be a cleanup
                                              // this will in turn call NitsRunContinuation and from there it will come back to here again
                return;
            }
        }
        m_nextFixtureInvocationToExecute = count;
    }
}

void Run::ClearFixtureInvocations()
{
    size_t count = m_currentTestFixtureInvocations.size();

    for(size_t i = 0; i < count; i++)
    {
        FixtureInvocation *fixtureInvocation = m_currentTestFixtureInvocations[i];
        delete fixtureInvocation;
    }

    m_currentTestFixtureInvocations.clear();    
}

bool Run::CurrentTestMatchesTestFilter()
{    
    size_t count = m_currentTestVariationNodes.size();
    if(count == 0)
        return true;

    if(m_currentTest->IsNewInterfaceTest())
    {
        struct RegistrationInfo *r = (struct RegistrationInfo *) (m_currentTest->m_registration);
        if(r->fixtureType == ModuleSetupFixture)
            return true;
    }

    for(size_t i = 0; i < count; i++)
    {
        if(DoesTestMatch(m_translatedTestFilter, m_currentTestVariationNodes[i]->GetName()))
            return true;
    }
    return false;
}
