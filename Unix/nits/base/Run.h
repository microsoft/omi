/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef __RUN_H__
#define __RUN_H__

#include "Globals.h"

namespace TestSystem
{

using namespace std;

bool ConfigureLocalInjection();

class Param
{
public:
    Param(_In_z_ const PAL_Char * name, _In_z_ const PAL_Char * value);
    ~Param();

    const PAL_Char * m_name;
    const PAL_Char * m_value;
};

class Module
{
public:
    Module(_In_z_ const PAL_Char * name);
    ~Module();

    const PAL_Char * GetName() const {return m_name;}

    void AddTest(_In_ Test *test);
    void AddRun(_In_z_ const PAL_Char * command);
    void Execute();

    void SetLibrary(_In_ Shlib *lib);
    void Unload();
private:
    size_t Find(_In_z_ const PAL_Char * test) const;
    void RunTests(size_t start);
    void RunMatchingTests(_In_z_ const PAL_Char * testNameSubstring);
    void RunModuleLevelTests(bool runCleanup);

    const PAL_Char * m_name;
    Shlib *m_library;      //Freed after the test run.
    vector<Test *> m_tests; //List of all tests in this module.
    vector<PAL_Char *> m_runs;  //List of selected tests to run.
};

NITS_EXPORT bool NitsParseArgument(_In_z_ char *str);
NITS_EXPORT int NitsExecuteRun();
NITS_EXTERN_C PAL_Uint32 THREAD_API _PipeThread(void* param);

// Represents the info needed to invoke a fixture
// used internally inside NITS to run fault simulation loop
class FixtureInvocation
{
public:
    FixtureInvocation(_In_opt_ FixtureInvocation *parentFixtureInvocationParam, _In_ BodyProc funcParam, _In_ void *selfContextParam, TestFixtureType fixtureTypeParam);

    void Execute();

    FixtureInvocation *parentFixtureInvocation; // this will be NULL for all fixtures except Cleanup
                                                // for cleanup fixture it will be used to keep track of the fixture for which this is Cleanup
    BodyProc func;
    void *selfContext;
    TestFixtureType fixtureType;
    bool executedInCurrentIteration;
};

class Run
{
public:
    static Run &GetInstance();
    static bool IsValid();

    Run();
    ~Run();

    Module *GetCurrentModule() const {return m_loadingModule;}
    Test *GetCurrentTest() const {return m_currentTest;}

    void AddTestVariationNode(Switch *mySwitch) { m_currentTestVariationNodes.push_back(mySwitch); }
    void ClearTestVariationNodes() { m_currentTestVariationNodes.clear(); }

    void AddFixtureInvocation(_In_opt_ BodyProc parentFixtureFuncParam, _In_ BodyProc funcParam, _In_ void *selfContextParam, TestFixtureType fixtureTypeParam); // adds fixture invocation, for cleanups, links fixture invocation to the parent
    void ClearFixtureInvocations(); // cleans up the fixture invocations 

    void ResetFixtureInvocationStateForRerun(); // resets the executedInCurrentIteration to false for all fixture invocations
    void ExecuteNextFixtureInvocationDuringFaultSim(); // looks at current result state from globals and decides what the next fixture invocation should be

    PAL_Char *GetTestVariationNodeNames();
    bool CurrentTestMatchesTestFilter();

    const PAL_Char * GetParam(_In_z_ const PAL_Char * name) const;
    const PAL_Char * GetDebugger() const {return m_debugger;}
    bool GetEnabled() const {return m_enabled;}
    bool GetFlaky() const {return m_flaky;}
    NitsFaultMode GetFaultMode() const {return m_simMode;}
    vector<int> const &GetFaultBreakpointList() const {return *m_bpFault;}
    Configuration const &GetConfiguration() const {return m_config;}

    bool IsParent() const {return !m_child;}
    bool IsChild() const {return m_child || !m_isolation;}
    bool IsSiteExcluded(int id) const;

    int  Execute();
    void ExecuteTest(_In_ Test *test, _In_opt_ const PAL_Char * choices, TestFixtureType executeIfTypeIs = BodyFixture);
    
    void ExecuteDeferredCleanup(_In_ Test *test);

    void SetDefaultOptions();
    void SetEnabled(bool enabled) {m_enabled = enabled;}
    void SetFlaky(bool flaky) {m_flaky = flaky;}
    void SetFaultMode(NitsFaultMode mode) {m_simMode = mode;}
    void SetExclusions(_In_reads_opt_(count) int sites[], int count);
    void ReportResult();
    bool ParseArgument(_In_ PSTR arg);
    void PipeThread();

    void SetGlobalFaultSimBehavior(bool enabled) { m_fault = enabled; };

    void SetFaultInjectionLoopStatus(bool running) { m_runningFaultInjectionLoop = running; }
    bool InMiddleOfFaultInjectionLoop() { return m_runningFaultInjectionLoop; };
    bool DoneExecutingAllFixtureInvocations();
private:
    static Run *s_run;

    void AddModule(_In_z_ const PAL_Char * name);
    bool AddParam(_In_z_ const PAL_Char * name, _In_z_ const PAL_Char * value);
    bool AddRun(_In_z_ const PAL_Char * name, _In_z_ const PAL_Char * test);    
    void DumpPipe();
    unsigned ReportStatistics();

    vector<Module *> &Modules() {return *m_modules;}
    vector<Param *> &Params() {return *m_params;}
    vector<Module *> const &Modules() const {return *m_modules;}
    vector<Param *> const &Params() const {return *m_params;}    

    Test *m_currentTest;
    vector<Switch *> m_currentTestVariationNodes;
    // used to record all fixture invocations in the current test starting from 
    // topmost setup to all cleanups
    // this will be used to play back the test during fault simulation loop
    vector<FixtureInvocation *> m_currentTestFixtureInvocations;    
    
    Module *m_loadingModule;
    vector<Module *> *m_modules;
    vector<Param *> *m_params;

    //New options from command line.
    vector<int> *m_bpFault;     //List of fault iterations to break on.
    Configuration m_config;
    bool m_pause;               //Wait for input after testing?
    bool m_reset;               //Ignore existing test runs.
    const PAL_Char * m_debugger;          //Debug command line.
    const PAL_Char * m_binaryFilter;      //Semicolon-separated list; processes must contain one or more.
    const PAL_Char * m_binaryTarget;      //Semicolon-separated list of binaries to trap.

    // for filtering functionality based on fixture names
    const PAL_Char *m_testFilter;
    PAL_Char m_translatedTestFilter[1024];

    //Old options from command line.
    bool m_isolation;           //Run tests in child process?
    bool m_child;               //Run as child process?
    bool m_fault;               //Run automatic fault sim (affects V1 tests only!).
    const PAL_Char * m_wtt;               //WTT log file.

    bool m_finished;            //Stops pipe thread.

    int *m_statistics;
#if !defined(macos) && !defined(freebsd) // Mac and FreeBSD says this is not used
    int m_faultIterations;      //Cumulative fault injection iteration total.
#endif

    //TODO: Deprecate all these variables.
    //Run-time options set by Test object.
    bool m_enabled;             //If false, skips the test body.
    bool m_flaky;               //If true, skips the test body only if nits was called with parameter "-skipflaky".
    NitsFaultMode m_simMode;    //Default to Auto/Manual fault sim.

    int *m_exclusions;          //Sites waived during auto fault sim.
    int m_exclusionsCount;

    bool m_runningFaultInjectionLoop;

    size_t m_nextFixtureInvocationToExecute; // keeps track of what should be the next fixture invocation to be executed after current one returns
};

} //namespace TestSystem;

#endif // ndef __RUN_H__
