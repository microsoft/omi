/*
 * Copyright (C) 2011 Microsoft Corporation
 * All rights reserved.
 */
#ifdef _MSC_VER
    #include <sal.h>
#endif
#include "stdlib.h"
#include "string.h"
#include <nits/base/Globals.h>
#include <iostream>
#include <iomanip>
using namespace std;

#ifdef _MSC_VER
# define CDECLAPI __cdecl
#else
# define CDECLAPI
#endif

extern "C" NITS_DLLIMPORT int NitsExecuteRun();
extern "C" NITS_DLLIMPORT int NitsParseArgument(_In_z_ char *str);
extern "C" NITS_DLLIMPORT int NitsCheckVersion(int version);

static void PrintUsage()
{
    Tprintf(   PAL_T("NITS Integrated Test System\n")
                 PAL_T("------------------------------------------\n\n")
                 PAL_T("Usage: nits [option|test]*\n")
                 PAL_T("\nV2 Options:\n")
                 PAL_T("\t-bpassert\t\tBreaks on all failed asserts.\n")
                 PAL_T("\t-bpfault:number\t\tBreaks on a fault injection iteration.\n")
#ifdef _MSC_VER
                 PAL_T("\t-debug:name\t\tAttach debugger to child processes.\n")
#endif
                 PAL_T("\t-file:name.txt\t\tAppends file to command line.\n")
#ifdef _MSC_VER
                 PAL_T("\t-filter:binaries\tInjector must find one of these binaries (semicolon or comma-separated, *binaryName indicates any binary with binaryName as substring).\n")
                 PAL_T("\t-install\t\tEnables loading of nitsinj.dll in all processes running binaries linked against nitsstub.\n")
#else
                 PAL_T("\t-filter:binaries\tInjector must find one of these binaries (comma-separated).\n")
                 PAL_T("\t-install\t\tEnables loading of libnitsinj.so in all processes running binaries linked against nitsstub.\n")
#endif

                 PAL_T("\t-mode:Skip\t\tExplores test tree and skips everything.\n")
                 PAL_T("\t-mode:Enable\t\tRuns without fault injection.\n")
                 PAL_T("\t-mode:IterativeFault\tFaults all single-fault locations.\n")
                 PAL_T("\t-mode:StackFault\tOptimized single-fault scenarios.\n")
                 PAL_T("\t-mode:CompoundFault\t(Default) Multiple-fault scenarios.\n")
                 PAL_T("\t-pause\t\t\tWaits for input after running.\n")
                 PAL_T("\t-reset\t\t\tIgnores a test run in progress.\n")
                 PAL_T("\t-skipflaky\t\tSkips executing flaky tests.\n")
#ifdef _MSC_VER
                 PAL_T("\t-target:binaries\tDynamic injection on specific binaries (semicolon or comma-separated, *binaryName indicates any binary with binaryName as substring).\n")
#else
                 PAL_T("\t-target:binaries\tDynamic injection on specific binaries (comma-separated, *binaryName indicates any binary with binaryName as substring).\n")
#endif
                 PAL_T("\t-trace:FailedTests\tFailed tests only.\n")
                 PAL_T("\t-trace:WarnedTests\tShows failed and warned tests.\n")
                 PAL_T("\t-trace:AllTests\t\t(Default) Shows all test cases.\n")
                 PAL_T("\t-trace:Asserts\t\tShows failed asserts.\n")
                 PAL_T("\t-trace:Warnings\t\tShows failed asserts/warnings.\n")
                 PAL_T("\t-trace:Iterations\tShows fault injection iterations.\n")
                 PAL_T("\t-trace:Verbose\t\tShows product and other traces.\n")                 
#ifdef _MSC_VER
                 PAL_T("\t-localinjection\tLoads nitsinj.dll manually, supporting no-install fault injection. NOTE: Does not work with -isolate!\n")                 
#else
                 PAL_T("\t-localinjection\tLoads nitsinj.dll manually, supporting no-install fault injection.\n")                 
#endif
                 PAL_T("\t-uninstall\t\tRemoves nitsinj.dll injection from all processes running binaries linked against nitsstub.\n")
                 PAL_T("\nV1 Compatibility Options:\n")
                 PAL_T("\t-assert\t\tShows failed asserts. Default.\n")
                 PAL_T("\t-noassert\t\tHides failed asserts.\n")
                 PAL_T("\t-child\t\tInternal use only.\n")
                 PAL_T("\t-fault\t\tAutomatic fault simulation.\n")
                 PAL_T("\t-fault:number\tBreaks at a fault sim iteration.\n")
#ifdef _MSC_VER
                 PAL_T("\t-isolate\tIsolates tests in child processes.\n")
#endif
                 PAL_T("\t-output:file\tDumps XML output to file.\n")
                 PAL_T("\t-skip\t\tValidates setup/cleanup code only.\n")
                 PAL_T("\t-trace\t\tShows test traces.\n")
                 PAL_T("\t-verbose\tShows successful tests. Default.\n")
                 PAL_T("\t-noverbose\tHides successful tests.\n")
#ifdef _MSC_VER
                 PAL_T("\t-wtt:file\tLogs WTT results to a file.\n")
#endif
                 PAL_T("\t+name:value\tSets test parameter 'name' to 'value'.\n")
                 PAL_T("\nTests:\n")
#ifdef _MSC_VER
                 PAL_T("\tmodule.dll\t\tRuns all tests in a module.\n")
                 PAL_T("\tmodule.dll:+testname\t\tRuns all tests starting *after* the specified test.\n")
                 PAL_T("\tmodule.dll:*testnameSubstring\t\tRuns all tests matching the pattern.\n")
                 PAL_T("\tmodule.dll:testname\t\tRuns all variations of a specific test.\n")
                 PAL_T("\tmodule.dll:testname/choices\tRuns a specific test variation.\n")
#else
                 PAL_T("\tlibmodule.so\t\tRuns all tests in a module.\n")
                 PAL_T("\tlibmodule.so:+testname\t\tRuns all tests starting *after* the specified test.\n")
                 PAL_T("\tlibmodule.so:*testnameSubstring\t\tRuns all tests matching the pattern.\n")
                 PAL_T("\tlibmodule.so:testname\t\tRuns all variations of a specific test.\n")
                 PAL_T("\tlibmodule.so:testname/choices\tRuns a specific test variation.\n")
#endif
                 PAL_T("\t-match:testFixtureNameSubstring\tRuns tests only if they contain fixture names matching the pattern (semicolon or comma-separated).\n")
                 PAL_T("\nResults:\n")
                 PAL_T("\tFaulted:\tPassed with fault simulation.\n")
                 PAL_T("\tPassed: \tPassed without fault simulation.\n")
                 PAL_T("\tSkipped:\tThe test body was not run.\n")
                 PAL_T("\tKilled: \tIsolation mode: the test was killed.\n")
                 PAL_T("\t\t\tNOTE: Killed tests may fail to clean up properly.\n")
                 PAL_T("\tFailed: \tTest assertions failed while running the test.\n")
                 PAL_T("\tError:  \tSetup/cleanup failed, or no asserts were attempted.\n"));
}

int CDECLAPI main(int argc, _In_reads_(argc) char *argv[])
{
    int result = 0;

    if (!NitsCheckVersion(TestSystem::SharedMemoryVersion))
    {
        result = 1;
        goto end;
    }

    /* Accomodate nits -? and nits /? */
    if (argc == 1)
    {
        PrintUsage();
        result = 0;
        goto end;
    }
    else if (argc == 2 && argv[1][0] != '\0' && argv[1][1] == '?' && argv[1][2] == '\0')
    {
        PrintUsage();
        result = 0;
        goto end;
    }

    for (int count = 1; count < argc; count++)
        if (!NitsParseArgument(argv[count]))
        {
            // ensure errors are flushed to console.            
            result = 1;
            goto end;
        }
    
    result = NitsExecuteRun();       

end:
    fflush(stdout);
    return result;
}

