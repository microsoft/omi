/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "Run.h"
#include <iostream>
#include <pal/palcommon.h>
#include <pal/strings.h>

using namespace std;
using namespace TestSystem;

#define IsSetupFixture(fixtureType) ((fixtureType == SetupFixture) || (fixtureType == SplitFixture))

NITS_EXPORT void NITS_CALL NitsSwitchCreate(
    _Inout_ Switch *test,
    _In_ const PAL_Char * name,
    _In_ void (NITS_CALL *setup)(Switch &),
    bool group)
{
    test->m_name = name;
    test->m_setup = setup;
    test->m_cleanup = NULL;
    test->m_choice = group ? Switch::AllChildren : 0;
    test->m_index = 0;
    test->m_refs = 0;
    test->m_children = new ChildList;
    test->m_registration = NULL;
    test->m_prevLayerContinuation = NULL;
    test->m_sameLayerContinuation = NULL;
    test->m_prevSwitchOnSelectedTestStack = NULL;
    test->m_rootSwitch = NULL;
    test->m_dryRunToFindChildren = 0;
    test->m_someoneCalledOmit = 0;
    test->m_filteredOutByUser = 0;
    test->m_notRunInCurrentTestChoice = 0;
    test->m_switchState = TestSystem::Switch::NotRunYet;
    test->m_markedForRerunInFaultSimulation = false;

    if (test->m_children == NULL)
    {
        FatalError();
    }
}

NITS_EXPORT void NITS_CALL NitsSwitchDelete(
    _Inout_ Switch *test)
{
    struct RegistrationInfo *r = (struct RegistrationInfo *) (test->m_registration);
    int count = 0;
    delete test->m_children;
    if(r)
    {
        if(r->arrayOfInitializers)
        {
            while(count < r->numberOfParents)
            {
                SystemFree(r->arrayOfInitializers[count]);
                count++;
            }
            SystemFree(r->arrayOfInitializers);
        }

        if(r->parentArray)
        {
            SystemFree(r->parentArray);
        }
        
        SystemFree(r);
    }
}

NITS_EXPORT void NITS_CALL NitsSetTeardownSwitch(_Inout_ Switch *test, Switch *teardownSwitch, int isCleanup)
{
    if(test->m_registration)
    {
        struct RegistrationInfo *r = (struct RegistrationInfo *) (test->m_registration);
        if(isCleanup)
        {
            r->cleanupSwitch = teardownSwitch;
        }
        else
        {
            r->crashSwitch = teardownSwitch;
        }
    }
}

NITS_EXPORT void ** NITS_CALL NitsGetInitArray(_Inout_ Switch *test)
{
    if(!test->IsNewInterfaceTest())
        return NULL;
    
    struct RegistrationInfo *r = (struct RegistrationInfo *) (test->m_registration);

    return r->arrayOfInitializers;
}

NITS_EXPORT int NITS_CALL NitsIsSplitFixture(_In_ Switch *test)
{
    if(!test->IsNewInterfaceTest())
        return 0;
    
    struct RegistrationInfo *r = (struct RegistrationInfo *) (test->m_registration);    

    return (r->fixtureType == SplitFixture);
}

PAL_Boolean Switch::IsBodyFixture()
{
    if(!IsNewInterfaceTest())
        return PAL_FALSE;

    struct RegistrationInfo *r = (struct RegistrationInfo *) (m_registration);

    return ((r->fixtureType == BodyFixture) || (r->fixtureType == ModuleSetupFixture));
}

PAL_Boolean Switch::IsModuleSetupFixture()
{
    if(!IsNewInterfaceTest())
        return PAL_FALSE;

    struct RegistrationInfo *r = (struct RegistrationInfo *) (m_registration);

    return (r->fixtureType == ModuleSetupFixture);
}

bool Switch::IsChildSelected(int index) const
{
    return IsGroup() || index == m_choice;
}

//Registers and runs child switches from setup().
//Caller must not change the child sequence when repeating its own variations.
NITS_EXPORT void NITS_CALL NitsSwitchChild(
    _Inout_ Switch *test,
    _In_ Switch &child)
{
    vector<Switch *> &list = *test->m_children;

    if (test->m_index == list.size())
    {
        //Register a new child.
        list.push_back(&child);
    }
    else if (list[test->m_index] != &child)
    {
        //Caller previously registered children in a different order!
        FatalError();
    }

    if (test->IsChildSelected(test->m_index++))
    {
        child.RunSetup();
    }
}

NITS_EXPORT bool NITS_CALL NitsSwitchGetEnabled(
    _Inout_ Switch const *test)
{
    PAL_UNUSED(test);
    return Run::GetInstance().GetEnabled();
}

NITS_EXPORT void NITS_CALL NitsSwitchSetFaultMode(
    _Inout_ Switch *test,
    NitsFaultMode mode)
{
    PAL_UNUSED(test);

    Run::GetInstance().SetFaultMode(mode);
}

NITS_EXPORT void NITS_CALL NitsSwitchSetEnabled(
    _Inout_ Switch *test,
    bool enabled)
{
    PAL_UNUSED(test);

    Run::GetInstance().SetEnabled(enabled);
}

NITS_EXPORT void NITS_CALL NitsSwitchSetFlaky(
    _Inout_ Switch *test,
    bool flaky)
{
    PAL_UNUSED(test);

    Run::GetInstance().SetFlaky(flaky);
}

NITS_EXPORT void NITS_CALL NitsSwitchFaultExclude(
    _Inout_ Switch *test,
    _In_reads_opt_(count) int sites[],
    int count)
{
    PAL_UNUSED(test);

    Run::GetInstance().SetExclusions(sites, count);
}

NITS_EXPORT void NITS_CALL NitsSwitchFaultOff(
    _Inout_ Switch *test)
{
    PAL_UNUSED(test);

    GetGlobals().SetFault(CallSite_NONE, 0, S_OK, PAL_T(""));
}

NITS_EXPORT void NITS_CALL NitsSwitchFaultHresult(
    _Inout_ Switch *test,
    int site,
    HRESULT error,
    int attempt)
{
    PAL_UNUSED(test);

    GetGlobals().SetFault(site, attempt, error, PAL_T(""));
}

NITS_EXPORT void NITS_CALL NitsSwitchFaultError(
    _Inout_ Switch *test,
    int site,
    DWORD error,
    int attempt)
{
    PAL_UNUSED(test);

    GetGlobals().SetFault(site, attempt, HRESULT_FROM_WIN32(error), PAL_T(""));
}

NITS_EXPORT void NITS_CALL NitsSwitchFaultWait(
    _Inout_ Switch *test,
    int site,
    _In_ Event const &event,
    int attempt)
{
    PAL_UNUSED(test);

    GetGlobals().SetFault(site, attempt, S_OK, event);
}

NITS_EXPORT const PAL_Char *NITS_CALL NitsTestGetParam(_In_z_ const PAL_Char *paramName)
{
    return Run::GetInstance().GetParam(paramName);
}

NITS_EXPORT void NITS_CALL NitsEnableFaultSimAll()
{
    Run::GetInstance().SetGlobalFaultSimBehavior(true);
}

NITS_EXPORT void NITS_CALL NitsDisableFaultSimAll()
{
    Run::GetInstance().SetGlobalFaultSimBehavior(false);
}

void Switch::RunSetup()
{
    if (++m_refs > 1)
    {
        if (IsChoice())
        {
            //Sanity check: choices must NOT have multiple parents.
            //This causes confusion when choosing children.
            throw Exception();
        }

        return;
    }

    //The setup call registers and calls children through Child().
    //Child call order is determined by setup.
    m_setup(*this);
}

void Switch::RunCleanup()
{
    if (m_refs <= 0)
    {
        throw Exception();
    }

    if (--m_refs > 0)
    {
        return;
    }
    
    //Shut down the parent first.
    //Then shut down children that called setup, in reverse order.
    if (m_cleanup)
    {
        m_cleanup(*this);
    }

    while (m_index > 0)
    {
        vector<Switch *> &list = *m_children;
        Switch &child = *list[--m_index];
        if (IsChildSelected(m_index))
        {
            child.RunCleanup();
        }
    }
}

Switch *Switch::GetFirstSelectedChild()
{
    vector<Switch *> &list = *m_children;
    int index = 0;
    int sizeOfChildrenList = (int)list.size();
    
    while (index < sizeOfChildrenList)
    {
        if (IsChildSelected(index))
        {
            return list[index];
        }
        index++;
    }

    return NULL;
}

void Switch::Reset()
{
    if (IsChoice())
    {
        m_choice = 0;
    }

    if (m_index != 0 || m_refs > 0)
    {
        throw Exception();
    }

    //TODO: Is this really necessary?
    vector<Switch *> &list = *m_children;
    for (DWORD i = 0; i < list.size(); i++)
    {
        list[i]->Reset();
    }

    m_prevLayerContinuation = NULL;
    m_sameLayerContinuation = NULL;
    m_prevSwitchOnSelectedTestStack = NULL;
    m_rootSwitch = NULL;
    m_switchState = TestSystem::Switch::NotRunYet;

    list.clear(); //Allows a later test to declare different children.
}

bool Switch::Next()
{
    vector<Switch *> &list = *m_children;
    if (IsGroup())
    {
        //Lexicographic search.
        //Start with the lowest-order "digit" and increment.
        //If that is done, reset and move to the next-order "digit".
        for (int i = (int)list.size() - 1; i >= 0; i--)
        {
            Switch &child = *list[i];
            if (child.Next())
            {
                return true;
            }
            
            child.Reset();
        }

        return false;
    }
    else
    {
        if (list.size() == 0)
        {
            //Choice nodes with no children run like a group node.
            return false;
        }

        //Iterative search.
        //Each child contains at least one position.
        Switch &child = *list[m_choice];
        if (child.Next())
        {
            return true;
        }

        child.Reset();
        return ((unsigned long)(++m_choice)) < list.size();
    }
}

void Switch::PrintChoices(Buffer &data)
{
    ostringstream &buf = data;
    vector<Switch *> &list = *m_children;
    if (IsChoice())
    {
        if (list.size() > 0)
        {
            buf << "/" << list[m_choice]->GetName();
            list[m_choice]->PrintChoices(data);
        }
    }
    else for (DWORD i = 0; i < list.size(); i++)
    {
        list[i]->PrintChoices(data);
    }
}

bool Switch::SelectChoices(_Inout_z_ PAL_Char * &choices)
{
    vector<Switch *> &list = *m_children;

    //NOTE: Have to run setup at least once to discover children.
    if (list.size() == 0)
    {
        RunSetup();
        RunCleanup();
    }

    //Recursively traverse the choices and groups.
    if (IsChoice())
    {
        PAL_Char *item = choices;
        PAL_Char *slash = Tcschr(choices, PAL_T('/'));
        if (slash)
        {
            //Advance to next choice.
            *slash = PAL_T('\0');
            choices = slash + 1;
        }
        else
        {
            //No more choices. Just advance to the end.
            choices += Tcslen(choices);
        }

        for (DWORD i = 0; i < list.size(); i++)
        {
            if (Equals(list[i]->GetName(), item))
            {
                m_choice = i;
                return list[i]->SelectChoices(choices);
            }
        }

        //Choice was not found.
        return false;
    }
    else
    {
        for (DWORD i = 0; i < list.size(); i++)
        {
            if (!list[i]->SelectChoices(choices))
            {
                return false;
            }
        }

        return true;
    }
}

NITS_EXPORT void NITS_CALL NitsTestCreate(
    _Inout_ Test *test,
    _In_ const PAL_Char * name,
    _In_ void (NITS_CALL *setup)(Switch &),
    _In_ void (NITS_CALL *body)(Switch &),
    bool deleteMeAfterRun /* = false */)
{
    PAL_UNUSED(name);
    PAL_UNUSED(setup);
    PAL_UNUSED(body);

    test->m_body = body;
    test->m_deleteMeAfterRun = deleteMeAfterRun;    

    if (!Run::IsValid())
    {
        return;
    }

    Module *module = Run::GetInstance().GetCurrentModule();
    if (module == NULL)
    {
        return;
    }

    test->m_module = module->GetName();
    module->AddTest(test);

    test->m_timeout = test->s_nextTimeout;
    test->m_isolation = test->s_nextIsolation;

    test->s_nextTimeout = 60;
    test->s_nextIsolation = false;
    test->m_startTicks = 0;
    test->m_testRunState = TestSystem::Test::BodyYetToRun;
    test->m_cleanupMode = TestSystem::Test::ImmediateCleanup;
}

NITS_EXPORT void NITS_CALL NitsFaultSimMarkForRerunTillThisFixture(TestSystem::Switch &currentSwitch)
{
    currentSwitch.m_markedForRerunInFaultSimulation = true;
}

void Test::PrintName(Buffer &data, bool choices)
{
    ostringstream &buf = data;    
    buf << GetModule() 
        << ":" 
        << GetName();
    if (choices)
    {
        PrintChoices(data);
    }
}

void Test::RunDeferredCleanup()
{
    RunCleanup();
    struct RegistrationInfo *myRegistration = (struct RegistrationInfo *)(m_registration);
    myRegistration->cleanupFunc(myRegistration->selfContext);
}

void Test::Execute(_In_opt_z_ const PAL_Char * choices)
{
    Reset();
    Run &run = Run::GetInstance();
    run.SetDefaultOptions();
    
    
    if(!IsNewInterfaceTest() && (m_cleanupMode == DeferredCleanup))
    {
        Tprintf(PAL_T("ERROR: Only new interface tests can run deferred cleanup"));
        throw Exception();        
    }    

    if (choices == NULL)
    {
        do {            
            RunVariation();
        }
        while (Next());
    }
    else
    {
    	PAL_Char *temp = Copy(choices);
    	PAL_Char *temp2 = temp;
        SetDryRun(1);
        bool success = SelectChoices(temp2) && temp2[0] == L'\0';
        SetDryRun(0);
        delete [] temp;

        if (!success)
        {
            Tprintf(PAL_T("%T%T%T"), PAL_T("ERROR: Invalid test variation '"), choices, PAL_T("'\n"));
            return;
        }

        RunVariation();
    }
}

void Test::RerunFixturesMarkedForFaultSim()
{
    Run &run = Run::GetInstance();
    RegistrationInfo *myRegistration = (RegistrationInfo *)(m_registration);
    run.SetFaultInjectionLoopStatus(true);
    run.ResetFixtureInvocationStateForRerun();
    myRegistration->initFunc(myRegistration->selfContext, 0);
    run.ExecuteNextFixtureInvocationDuringFaultSim();
    if(!run.DoneExecutingAllFixtureInvocations())
    {
        Tprintf(PAL_T("ERROR: Some fixture in this test has a return statement; please change that to NitsReturn"));
        throw Exception();
    }
    run.SetFaultInjectionLoopStatus(false);
}

void Test::RunFaultInjectionLoop()
{
    Globals &globals = GetGlobals();    

    Fault &fault = globals.GetAutoFault();
    bool failTest = false;

    int tempSwitchState = m_switchState;
    
    bool runFaultInjection = Run::GetInstance().GetFaultMode() == Automatic &&
        (globals.GetConfiguration().mode >= NitsTestIterativeFault) && 
        (IsModuleSetupFixture() == PAL_FALSE);

    Configuration const &config = Run::GetInstance().GetConfiguration();

    bool filteringDetected = false;
	ptrdiff_t limit = 0;

    if (!runFaultInjection || 
        globals.GetResult() != Passed)
    {
        return;
    }

    enum
    {
        MainThreadOnly,
        IncreasingAttemptOnly,
        Delayed
    } state;

    state = MainThreadOnly;
    globals.m_simAuto.m_minimumAttemptDifferentThread = INT_MAX;

    //Automatic fault simulation loop.
    for (int i = 1; true; i++)
    {
        globals.ResetIgnoredErrorReporting();
        if (state == Delayed)
        {
            //When filtering is disabled, threads from previous iterations
            //  might interfere with us. Wait some time for them to go away.
            Sleep_Milliseconds(10);
        }

        //Do NOT reset globals here, or information from setup will be erased.
        //Set automatic fault sim parameters.
        bool faultBP = false;

        if (config.breakFault)
        {
            vector<int> const &list = Run::GetInstance().GetFaultBreakpointList();
            for (unsigned j = 0; j < list.size(); j++)
            {
                if (list[j] == i)
                {
                    faultBP = true;
                    break;
                }
            }
        }
        globals.SetResult(Passed);
        fault.Reset(CallSite_ALL, i, faultBP);

        ostringstream buf;
        buf << "Starting fault simulation iteration #" << i << "...";
        NitsTraceExA(buf.str().c_str(), TLINE, NitsAutomatic);
        globals.GetStats().faultIterations++;

        // making switch state NotRunYet so that running the body does not skip the body
        m_switchState = NotRunYet;

        if(!m_markedForRerunInFaultSimulation)
        {
            m_body(*this);
        }
        else
        {
            RerunFixturesMarkedForFaultSim();
        }

        // putting the state back to what it was before we started fault sim so that further code path continues from the place where fault sim started
        m_switchState = tempSwitchState;
            
        if (globals.m_simAuto.m_filtered)
        {
            filteringDetected = true;
        }

        if (state == MainThreadOnly)
        {
            limit = max(limit, globals.m_simAuto.m_firstAttemptDifferentThread);
            globals.m_simAuto.m_firstAttemptDifferentThread = 0;
        }
        else if (state == IncreasingAttemptOnly)
        {
            limit = max(limit, globals.m_simAuto.m_faultedAttempt + 1);
            globals.m_simAuto.m_minimumAttemptDifferentThread = limit;
            globals.m_simAuto.m_firstAttemptDifferentThread = 0;
        }

        if (globals.GetResult() == Failed)
        {
            if (fault.DidFault())
            {
                //Expected behavior.
                //Proceed to the next iteration.
                continue;
            }

            //The test hit asserts before the fault was simulated.
            //Stop here and report failure.
            failTest = true;
            NitsTraceEx(PAL_T("UNEXPECTED FAULT SIM FAILURE"), NitsHere(), NitsManual);
        }
        else if (globals.GetResult() == Error)
        {
            //Asserts attempted to fail fault sim.
            //Don't abort the test.
            failTest = true;
            continue;
        }
        else if (globals.GetResult() != Passed)
        {
            throw Exception();
        }

        //The test body passed.
        //This may or may not be expected.
        if (!fault.DidFault())
        {
            if (filteringDetected)
            {
                if (state == MainThreadOnly)
                {
                    //Rerun with all threads, using the calculated limit.
                    globals.m_simAuto.m_minimumAttemptDifferentThread = limit;
                    state = IncreasingAttemptOnly;
                }
                else if (state == IncreasingAttemptOnly)
                {
                    //Need to rerun with delays and without filtering.
                    globals.m_simAuto.m_minimumAttemptDifferentThread = 0;
                    state = Delayed;
                }
                filteringDetected = false;
                continue;
            }

            //Loop complete.
            fault.Reset(CallSite_NONE, 0, false);
            globals.SetResult(failTest ? Failed : Faulted);
            return;
        }

        if (Run::GetInstance().IsSiteExcluded(fault.m_hit) ||
            !globals.ShouldReportIgnoredErrors())
        {
            //The test expected faults not to propagate properly here.
            continue;
        }

        //This iteration should not have succeeded.
        //Report the problem and continue running the test.
        failTest = true;
        if (GetGlobals().GetConfiguration().traces >= NitsTraceAsserts)
        {
            NitsTraceEx(PAL_T("UNEXPECTED FAULT SIM SUCCESS"),
                    fault.GetFaultedSite(), NitsManual);
        }
        if (config.breakAssert)
        {
            MyDebugBreak;
        }
    }
}

void Test::ContinueProcessingAfterBody()
{
    if(m_testRunState == PartAfterBodyRan)
        return;

    long prevTestRunState = m_testRunState;

    m_testRunState = PartAfterBodyRan;

    Globals &globals = GetGlobals();
    Run &run = Run::GetInstance();

    if (globals.GetResult() == Error)
    {
        //Asserts attempted to fail fault sim.
        //During the regular body this is an ordinary failure.
        if(prevTestRunState != BodySkippedDueToFailedSetup)
        {
            globals.SetResult(Failed);
        }
    }
    else if (globals.GetResult() == Skipped && Run::GetInstance().GetEnabled())
    {
        if(!NitsNotRunInCurrentTestChoice())
        {
            //No asserts were attempted and the test wasn't disabled.
            globals.SetResult(Error);
            NitsAssert(0, PAL_T("The test case contains no assertions!"));
        }
        else
        {            
            globals.SetResult((m_filteredOutByUser) ? Skipped : Omitted);
        }
    }

    // if we are marked for rerunning entire tree under this node, dont run fault injection here 
    // in that case run it at the end after running all cleanups
    if(!m_markedForRerunInFaultSimulation)
    {
        RunFaultInjectionLoop();
    }

	ostringstream testName;

	Buffer wrappedTestName(testName);
    PrintName(wrappedTestName, true);

    Result temp = globals.GetResult();
    globals.SetResult(Skipped);

    if(m_cleanupMode == TestSystem::Test::ImmediateCleanup)
    {
        RunCleanup();
    }

    NitsNotRunInCurrentTestChoice();
    
    if (globals.GetResult() == Failed)
    {
        globals.SetResult(Error);
    }
    else
    {
        globals.SetResult(temp);
    }

    if(m_markedForRerunInFaultSimulation)
    {
        RunFaultInjectionLoop();
    }

    ptrdiff_t stopTicks = CPU_GetTimeStamp();
    double seconds = float(stopTicks - m_startTicks) / 1000000.0;
    globals.SetRunTime(seconds);

    run.ReportResult();    
}

static void FilterOutTestIfRequired()
{    
    Run &run = Run::GetInstance();
    if(!(run.CurrentTestMatchesTestFilter()))
    {        
        run.GetCurrentTest()->m_filteredOutByUser = 1; 
        GetGlobals().SetResult(Skipped);
    }
}

void Test::ContinueProcessingAfterSetup()
{
    if(m_testRunState == BodyRan)
        return;

    m_testRunState = BodyRan;
    
    Globals &globals = GetGlobals();
    Run &run = Run::GetInstance();
    ostringstream testName;

    Buffer wrappedTestName(testName);
    PrintName(wrappedTestName, true);
    
    FilterOutTestIfRequired();    

    if ((globals.GetConfiguration().traces >= NitsTraceAllTests) && 
        (!m_filteredOutByUser))
    {        
        ostringstream buf;
        buf << "\t          " << testName.str().c_str() << "...\n";

        PAL_Char *postPipeStr = ConvertStringAToPalChar(buf.str().c_str());
        globals.PostPipe(postPipeStr);
        delete [] postPipeStr;
    }

    if (globals.GetResult() == Failed)
    {
        globals.SetResult(Error);
        m_testRunState = BodySkippedDueToFailedSetup;
    }
    else if (globals.GetResult() == Passed)
    {
        globals.SetResult(Skipped);
    }

    BOOL testEnabled = TRUE;
    if (!run.GetEnabled())
    {
        testEnabled = FALSE;
    }
    if (globals.GetConfiguration().skipFlakyTests)
    {
        if (run.GetFlaky())
        {
            testEnabled = FALSE;
        }
    }

    if (testEnabled &&
            globals.GetResult() == Skipped)
    {
        RunBody();
        
        if(m_testRunState == BodyRan)
        {
            if(!IsNewInterfaceTest())
            {
                ContinueProcessingAfterBody();
            }
            else
            {
                // we do not want test writers to use "return;" to exit the test fixtures, we want them to use "NitsReturn;"
                // if they use "return;" then we hit this code path where the Setup is not followed by a continuation function call leading to the body and so on.
                // so if we hit this code path when running new interface tests, we should error out
                Tprintf(PAL_T("ERROR: Some fixture in this test has a return statement; please change that to NitsReturn"));
                throw Exception();
            }            
        }
    }
    else
    {
        ContinueProcessingAfterBody();
    }
}

void Test::RunVariation()
{
    Run &run = Run::GetInstance();

    run.ClearTestVariationNodes();

    run.ClearFixtureInvocations();

    //Copy settings from command line options.
    run.SetDefaultOptions();

    m_startTicks = CPU_GetTimeStamp();

    m_testRunState = BodyYetToRun;
    m_prevLayerContinuation = NULL;
    m_sameLayerContinuation = NULL;
    m_prevSwitchOnSelectedTestStack = NULL;
    m_someoneCalledOmit = 0;
    m_filteredOutByUser = 0;
    m_switchState = TestSystem::Switch::NotRunYet;
    
    //Status is 'Skipped'.
    RunSetup();

    if(m_testRunState == BodyYetToRun)
    {    
        vector<Switch *> &list = *(m_children);
        // if it is not new interface test or there were no children registered then we will continue from here since setup would not have ran continuation
        if(!IsNewInterfaceTest() || (list.size() == 0))
        {            
            ContinueProcessingAfterSetup();
        }
        else
        {
            // we do not want test writers to use "return;" to exit the test fixtures, we want them to use "NitsReturn;"
            // if they use "return;" then we hit this code path where the Setup is not followed by a continuation function call leading to the body and so on.
            // so if we hit this code path when running new interface tests, we should error out
            throw Exception();
        }
    }
}


void Test::RunBody()
{
    Globals &globals = GetGlobals();
    
    //N.B. When nits.exe is running tests in-proc, we need to bootstrap
    //  the debugger before the test. Otherwise, the test could call
    //  LoadLibrary, and CheckDebugger() could get called inside the
    //  loader lock of our process, which can prevent us from actually
    //  creating the debugger process indefinitely.
    globals.CheckDebugger();

    globals.m_simAuto.m_firstAttemptDifferentThread = 0;
    globals.m_simAuto.m_minimumAttemptDifferentThread = 0;
    globals.m_simAuto.m_mainThread = Thread_ID();
    globals.m_simAuto.m_faultedAttempt = 0;

    //Run the regular test body.
    m_body(*this);
}

int Test::s_nextTimeout = 60;
bool Test::s_nextIsolation = false;

NITS_EXPORT void NITS_CALL NitsTestSetIsolationHelper(_In_ Test &test)
{
    PAL_UNUSED(test);

    Test::s_nextIsolation = true;
}

NITS_EXPORT void NITS_CALL NitsTestSetTimeoutHelper(_In_ Test &test, int seconds)
{
    PAL_UNUSED(test);

    Test::s_nextTimeout = seconds;
}

NITS_EXPORT void NITS_CALL NitsSetRegistrationInfo(struct RegistrationInfo *r, 
                        int selfContextSize, 
                        int selfStructSize,                         
						int numberOfParents,
						Switch **parentArray, 
						void *(*creationFunc)(), 
						void (*initFunc)(void *, void *), 
						void (*bodyFunc)(void *),
						void (*cleanupFunc)(void *),
						enum TestFixtureType fixtureType, 
						void **arrayOfInitializers)
{
	r->selfContext = 0;
	r->selfStruct = 0;    
    r->countOfLinks = 0;
	r->selfContextSize = selfContextSize;
	r->selfStructSize = selfStructSize;    
	r->numberOfParents = numberOfParents;
	r->parentArray = parentArray;
	r->creationFunc = creationFunc;
	r->initFunc = initFunc;
	r->bodyFunc = bodyFunc;
	r->cleanupFunc = cleanupFunc;
	r->fixtureType = fixtureType;
	r->arrayOfInitializers = arrayOfInitializers;		
	r->cleanupSwitch = 0;
	r->crashSwitch = 0;
}

NITS_EXPORT void NITS_CALL NitsCreateStruct(TestSystem::Switch &myFixture, void **selfContext, void **selfStruct)
{
	struct RegistrationInfo *myFixtureRegistration = (struct RegistrationInfo *) (myFixture.m_registration);

    // this should not happen
    if(!selfContext || !selfStruct)
        return;

    // this is for virtual inheritance kind of semantics; if there is already a structure allocated through one route in inheritance, we will not allocate it again but use the same one
    if(myFixtureRegistration->countOfLinks > 0)
    {
        *selfContext = myFixtureRegistration->selfContext;
        *selfStruct = myFixtureRegistration->selfStruct;
    }
    else
    {
        int isSplitFixture = (myFixtureRegistration->fixtureType == SplitFixture);
        // for splitfixtures, the context comes from their parents; they do not have a context; 
        // pointer adjustment is done during the call of the splitfixture by walking back the call chain
        *selfContext = SystemMalloc(myFixtureRegistration->selfContextSize);
        *selfStruct = (isSplitFixture ? 0 : SystemMalloc(myFixtureRegistration->selfStructSize));
        myFixtureRegistration->selfContext = *selfContext;
        myFixtureRegistration->selfStruct = *selfStruct;
    }
    (myFixtureRegistration->countOfLinks)++;
}

NITS_EXPORT void NITS_CALL NitsDestroyStruct(TestSystem::Switch &myFixture)
{
	struct RegistrationInfo *myFixtureRegistration = (struct RegistrationInfo *) (myFixture.m_registration);
    (myFixtureRegistration->countOfLinks)--;

    if(myFixtureRegistration->countOfLinks == 0)
    {
        SystemFree(myFixtureRegistration->selfContext);

        if(myFixtureRegistration->fixtureType != SplitFixture)
        {
            SystemFree(myFixtureRegistration->selfStruct);
        }
        myFixtureRegistration->selfContext = 0;
        myFixtureRegistration->selfStruct = 0;
    }
}

NITS_EXPORT void * NITS_CALL NitsGetSelfStruct(TestSystem::Switch &myFixture)
{
	struct RegistrationInfo *myFixtureRegistration = (struct RegistrationInfo *) (myFixture.m_registration);

    return myFixtureRegistration->selfStruct;
}

NITS_EXPORT void NITS_CALL NitsBody_NewInterfaceTest(TestSystem::Switch &test)
{
	struct RegistrationInfo *testRegistration = (struct RegistrationInfo *) (test.m_registration);

    FilterOutTestIfRequired();

    if(test.m_switchState == TestSystem::Switch::NotRunYet)
    {
        test.m_switchState = TestSystem::Switch::RunOnce;
        if(!test.IsModuleSetupFixture())
        {
            Run::GetInstance().AddFixtureInvocation(NULL, testRegistration->bodyFunc, testRegistration->selfContext, testRegistration->fixtureType);
        }
    	testRegistration->bodyFunc(testRegistration->selfContext);
    }
    else
    {
        NitsRunContinuation(test);
    }
}

NITS_EXPORT void NITS_CALL NitsSetup_NewInterfaceTest(TestSystem::Switch &test)
{
	struct RegistrationInfo *testRegistration = (struct RegistrationInfo *) (test.m_registration);
	int parentCount = 0;
	Switch *currentParent = 0;
    // when doing dryRun, it is needed only to make engine aware of children; so skip all other steps.
    int isDryRun = Run::GetInstance().GetCurrentTest()->IsDryRunToIdentifyChildren();// test.IsDryRunToIdentifyChildren();
    
    if(test.IsBodyFixture() ||
		IsSetupFixture(testRegistration->fixtureType))
	{	
        if(!isDryRun)
        {
            Run::GetInstance().AddTestVariationNode(&test);
        }

		if(test.IsBodyFixture() && !isDryRun)
		{
			if(testRegistration->selfContext == 0)
			{
				// this creationFunc will recurse through the entire test structure and create selfContext for each node following the virtual inheritance way of creating common node only once
				// TODO: implement multiple inheritance; will the common nodes need to register switches multiple times; who will create those switches?
				testRegistration->creationFunc();
			}
			// the initFunc is passed in the created context and a NULL for the initValues since the test itself does not provide any init values; the initFunc is supposed zero out its structure if init values are not provided.
			testRegistration->initFunc(testRegistration->selfContext, 0);

            test.m_sameLayerContinuation = 0;

            test.m_prevLayerContinuation = &test;
		}

		if(testRegistration->parentArray != 0)
		{
			while(parentCount < testRegistration->numberOfParents)
			{
				// register the child by calling Test.Child; this helps the test engine identify children/pick up the current chain of children to be run in this iteration
				currentParent = testRegistration->parentArray[parentCount];
                                
                // in both test setup and body cases, you need continuation switch set to your currentParent; 
                // but in SetupFixture case the continuation is the body of this current testRegistration whereas in 
                // in BodyFixture case continuation is the ContinueProcessingAfterSetup
                if(!isDryRun)
                {
                    currentParent->m_sameLayerContinuation = 0;
                        
                    if(test.IsGroup() && (parentCount >= 1))
                    {
                        Switch *prevParent = testRegistration->parentArray[parentCount - 1];
                        prevParent->m_sameLayerContinuation = currentParent;
                    }

                    // this helps with multiple inheritance; if some other fixture already put the prevLayerContinuationLink into current parent, that is sufficient; the second link is not required
                    if(currentParent->m_prevLayerContinuation == 0)
                    {
                        currentParent->m_prevLayerContinuation = &test;
                    }
                }
                    
    			test.Child(*currentParent);	            
                
				parentCount++;
			}

            // once we found what is the root node in current iteration; invoke its body; that will keep calling continuation till we run the test body and cleanup by nesting them on the same stack
            if(!isDryRun && test.IsBodyFixture() && (test.m_rootSwitch != 0))
            {
                (test.m_rootSwitch)->m_prevSwitchOnSelectedTestStack = 0;
    			NitsBody_NewInterfaceTest(*(test.m_rootSwitch));
                test.m_rootSwitch = 0;                
            }
		}
        else
        {
            if(!isDryRun)
            {
                // when we reach the root of the tree; run the body of the fixture
        		if(IsSetupFixture(testRegistration->fixtureType))
        		{
            		Switch *continuationSwitch = test.m_prevLayerContinuation;
            		while(continuationSwitch)
                    {
                        if(continuationSwitch->m_prevLayerContinuation == 0 || (continuationSwitch->m_prevLayerContinuation == continuationSwitch))
                        {
                            break;
                        }
                        continuationSwitch = continuationSwitch->m_prevLayerContinuation;
                    }

                    if (continuationSwitch == NULL)
                    {
                        FatalError();
                        return;
                    }

                    // only first root node i.e. when m_rootSwitch = 0 does this assignment; others do not since the first one will continue to run others
                    if(continuationSwitch->m_rootSwitch == 0)
                    {
                        continuationSwitch->m_rootSwitch = &test;
                    }
        		}
            }
        }
	}
}

NITS_EXPORT void NITS_CALL NitsCleanup_NewInterfaceTest(TestSystem::Switch &test)
{
	struct RegistrationInfo *testRegistration = (struct RegistrationInfo *) (test.m_registration);

    if(Run::GetInstance().GetCurrentTest()->IsDryRunToIdentifyChildren())
        return;
    
    struct RegistrationInfo *cleanupRegistration = (struct RegistrationInfo *) ((testRegistration->cleanupSwitch) ? testRegistration->cleanupSwitch->m_registration : 0);
    
    if(cleanupRegistration && !(test.m_notRunInCurrentTestChoice))
    {
        if(test.m_switchState == TestSystem::Switch::RunOnce)
        {
            test.m_switchState = TestSystem::Switch::CleanupRun;
            if(!test.IsModuleSetupFixture())
            {
                Run::GetInstance().AddFixtureInvocation(testRegistration->bodyFunc, cleanupRegistration->bodyFunc, testRegistration->selfContext, cleanupRegistration->fixtureType);
            }
            cleanupRegistration->bodyFunc(testRegistration->selfContext);
        }
    }

    test.m_switchState = TestSystem::Switch::NotRunYet;
    test.m_notRunInCurrentTestChoice = 0;
}

NITS_EXPORT void NITS_CALL NitsRunContinuation(TestSystem::Switch &test)
{
    Run &run = Run::GetInstance();
    if(run.InMiddleOfFaultInjectionLoop())
    {
        run.ExecuteNextFixtureInvocationDuringFaultSim();
        return;
    }

    Globals &globals = GetGlobals();    

    if((globals.GetResult() == Failed) ||
        (globals.GetResult() == Error))
    {
        // if we already failed/error'd out then 
        // we should continue processing after setup
        // if it is a body; it will fall through and execute cleanups after this
        struct RegistrationInfo *testRegistration = (struct RegistrationInfo *) (test.m_registration);
        if(IsSetupFixture(testRegistration->fixtureType))
        {
            Run::GetInstance().GetCurrentTest()->ContinueProcessingAfterSetup();
            return;
        }
    }

    TestSystem::Switch *continuationSwitch = test.m_sameLayerContinuation;
    struct RegistrationInfo *continuationRegistration = 0;
    
    // this will get run now or it will go to its parent; so we should reset it to avoid infinite loop if any
    test.m_sameLayerContinuation = NULL;

    while(continuationSwitch)
    {
        continuationRegistration = (struct RegistrationInfo *) (continuationSwitch->m_registration);
        
        if(continuationRegistration->parentArray == 0)
        {
            continuationSwitch->m_prevSwitchOnSelectedTestStack = &test;
            continuationSwitch->m_notRunInCurrentTestChoice = NitsNotRunInCurrentTestChoice();
            if(continuationRegistration->fixtureType == SplitFixture)
            {
                continuationRegistration->selfStruct = NitsGetSelfStruct(test);
            }
            NitsBody_NewInterfaceTest(*continuationSwitch);
            // continuationRegistration->bodyFunc(continuationRegistration->selfContext);
            return;
        }
        else
        {
            Switch *tempSwitch = continuationSwitch;

            // make sure same layer continuation for tempSwitch parentArray is setup appropriately

            int parentCount = 1;
            Switch *currentParent = 0, *prevParent = 0;
            struct RegistrationInfo *tempSwitchRegistration = (struct RegistrationInfo *) (tempSwitch->m_registration);                        
            if(tempSwitch->IsGroup())
            {
                while(parentCount < tempSwitchRegistration->numberOfParents)
                {
                    currentParent = tempSwitchRegistration->parentArray[parentCount];

                    currentParent->m_sameLayerContinuation = 0;                        

                    prevParent = tempSwitchRegistration->parentArray[parentCount - 1];

                    prevParent->m_sameLayerContinuation = currentParent;

                    if(currentParent->m_prevLayerContinuation == 0)
                    {
                        currentParent->m_prevLayerContinuation = tempSwitch;
                    }                        			

                    parentCount++;
                }
            }

            // Now go and execute the first selected child of tempSwitch
            continuationSwitch = continuationSwitch->GetFirstSelectedChild();
            if(continuationSwitch && (continuationSwitch->m_prevLayerContinuation != tempSwitch))
            {
                // this helps with multiple inheritance; before going to the next parent; 
                // you set the prevLayerContinuation to yourself so that when it comes down, it does not go the current prevLayer instead comes back to you
                continuationSwitch->m_prevLayerContinuation = tempSwitch;
            }
        }
    }

    continuationSwitch = test.m_prevLayerContinuation;

    if(continuationSwitch)
    {
        continuationRegistration = (struct RegistrationInfo *) (continuationSwitch->m_registration);

        if(IsSetupFixture(continuationRegistration->fixtureType))
        {
            continuationSwitch->m_prevSwitchOnSelectedTestStack = &test;
            continuationSwitch->m_notRunInCurrentTestChoice = NitsNotRunInCurrentTestChoice();
            if(continuationRegistration->fixtureType == SplitFixture)
            {
                continuationRegistration->selfStruct = NitsGetSelfStruct(test);
            }            
            NitsBody_NewInterfaceTest(*continuationSwitch);
            // continuationRegistration->bodyFunc(continuationRegistration->selfContext);
        }
        else if(continuationSwitch->IsBodyFixture())
        {
            TestSystem::Test *continuationTest = (TestSystem::Test *)continuationSwitch;
            
            if(continuationTest->m_testRunState == TestSystem::Test::BodyYetToRun)
            {
                continuationSwitch->m_prevSwitchOnSelectedTestStack = &test;
                continuationSwitch->m_notRunInCurrentTestChoice = NitsNotRunInCurrentTestChoice();
                continuationTest->ContinueProcessingAfterSetup();
            }
            else if(continuationTest->m_testRunState == TestSystem::Test::BodyRan)
            {
                continuationTest->ContinueProcessingAfterBody();

                if(continuationTest->m_cleanupMode == TestSystem::Test::ImmediateCleanup)
                {
                    // the main thread which was running body and possibly faultsim will then call clean up on the test related context objects
                    // this is separate from the cleanup functions explicitly defined by the user to clean up the stuff the user wants to.
                    continuationRegistration->cleanupFunc(continuationRegistration->selfContext);
                }
            }            
        }
    }
}

NITS_EXPORT int NITS_CALL NitsIsFixtureSelectedSoFar(TestSystem::Switch &currentSwitch, TestSystem::Switch &searchSwitch)
{
    Switch *currentNode = &currentSwitch;
    
    while(currentNode->m_prevSwitchOnSelectedTestStack)
    {
        if(currentNode->m_prevSwitchOnSelectedTestStack == &searchSwitch)
            return 1;

        currentNode = currentNode->m_prevSwitchOnSelectedTestStack;
    }

    return 0;
}

#define FIXTURE_STRING PAL_T("Fixture ")
#define OMITTED_MESSAGE PAL_T(" omitted the test choice\n")

NITS_EXPORT void NITS_CALL NitsOmit(TestSystem::Switch &currentSwitch)
{
    Run::GetInstance().GetCurrentTest()->m_someoneCalledOmit = 1;
    GetGlobals().SetResult(Skipped);

    int totalLen = (int)(Tcslen(FIXTURE_STRING) + Tcslen(currentSwitch.GetName()) + Tcslen(OMITTED_MESSAGE)) + 1;
    PAL_Char *outString = (PAL_Char *)(SystemMalloc(totalLen*sizeof(PAL_Char)));
    if(outString)
    {
    	Tcslcpy(outString, FIXTURE_STRING, totalLen);
    	Tcscat(outString, totalLen, currentSwitch.GetName());
    	Tcscat(outString, totalLen, OMITTED_MESSAGE);
    	GetGlobals().PostPipe(outString);
        SystemFree(outString);
    }
    else
    {
    	GetGlobals().PostPipe(PAL_T("Some Fixture omitted the test choice"));
    }    
}

NITS_EXPORT int NITS_CALL NitsAreWeInOmitMode()
{    
    return (Run::GetInstance().GetCurrentTest()->m_someoneCalledOmit);
}

NITS_EXPORT int NITS_CALL NitsIsTestFiltered()
{
    return (Run::GetInstance().GetCurrentTest()->m_filteredOutByUser);
}

NITS_EXPORT int NITS_CALL NitsIsTestEnabled()
{
    return (Run::GetInstance().GetCurrentTest()->GetEnabled());
}

NITS_EXPORT_DEF struct EmptyStruct sEmptyStruct = {0};

