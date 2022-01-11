/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef __NITS_H__
#define __NITS_H__

#include <pal/palcommon.h>

/*
 * NITS Integrated Test System
 * --------------------------
 * Contains public definitions for test infrastructure.
 */

/*
 * Build Instructions
 * ------------------
 * There are five ways to link to NITS:
 *  1) <default>:
 *          -All test macros are no-ops and NitsCallSite is minimized.
 *          -It is not possible to hook anything at runtime.
 *  2) HOOK_BUILD:
 *          -Test macros call NitsFT stubs, which are exported traps.
 *          -Link to pal.lib on windows and libpal.a elsewhere, which contains the stubs.
 *          -NitsCallSite is minimized but still functional.
 *          -Use the -trap option to hook selected binaries.
 *  3) DEBUG_BUILD:
 *          -Test macros call NitsFT stubs, which are exported traps.
 *          -Link to pal.lib on windows and libpal.a elsewhere, which contains the stubs.
 *          -NitsCallSite is fully functional, with file and line information.
 *          -Use the -trap option to hook selected binaries.
 *  4) TEST_BUILD:
 *          -Test macros call the NITS implementation through DLL linkage.
 *          -NitsCallSite is fully functional, with file and line information.
 *          -The -trap option has no effect.
 *          -Link against nitsdll.lib (nitsdll.dll) on windows and libnits.so elsewhere.
 *          -Run nits.exe with desired binaries as arguments.
 *  5) LIB_BUILD:
 *          -Test macros call the NITS implementation through static linkage.
 *          -The -trap option has no effect.
 *          -Link against nitsbase.lib or libnitsbase.a elsewhere.
 *          -Call <TBD> API to run tests.
     */

#define NITS_DLLEXPORT PAL_EXPORT_API
#define NITS_DLLIMPORT PAL_IMPORT_API    
#define NITS_CALL PAL_CALL    

    /* DEFAULT BUILD OPTIONS */
#define NITS_STUB_ONLY
    /* END DEFAULT BUILD OPTIONS */
    
#if defined(HOOK_BUILD) && !defined(TEST_BUILD) && !defined(LIB_BUILD)
    #undef NITS_STUB_ONLY
    #define NITS_LINKAGE NITS_DLLEXPORT
#endif /* HOOK_BUILD */
    
#if defined(DEBUG_BUILD) && !defined(TEST_BUILD) && !defined(LIB_BUILD)
    #undef NITS_STUB_ONLY
    #define NITS_LINKAGE NITS_DLLEXPORT
#endif /* DEBUG_BUILD */
    
#ifdef TEST_BUILD
    #undef NITS_STUB_ONLY
    #define NITS_LINKAGE NITS_DLLIMPORT
#endif /* TEST_BUILD */
    
#ifdef LIB_BUILD
    #undef NITS_STUB_ONLY
    #define NITS_LINKAGE
#endif /* LIB_BUILD */

#define NITS_EXTERN_C PAL_EXTERN_C

#ifdef NITS_INTERNAL
# define NITS_EXPORT PAL_EXTERN_C PAL_EXPORT_API
#endif

#ifndef NITS_EXPORT
    #define NITS_EXPORT NITS_EXTERN_C NITS_LINKAGE
#endif /* !NITS_EXPORT */

#define NITS_EXPORT_DEF PAL_EXPORT_API

#ifndef NITS_CONST_FT
    #define NITS_CONST_FT volatile
#endif /* !NITS_CONST_FT */

#ifndef NITS_STUB_ONLY
    typedef struct _NitsCallSite
    {
        const char *function;           /* Undecorated function name. */
        const char *file;               /* File name. */
        int line;                       /* Line number. */
        int id;                         /* Arbitrary site identifier. */
    } NitsCallSite;
    
    PAL_INLINE NitsCallSite NitsMakeCallSite(
                   int id,
        _In_opt_z_ const char *function,
        _In_opt_z_ const char *file,
                   int line)
    {
        NitsCallSite cs;
        cs.function = function;
        cs.file = file;
        cs.line = line;
        cs.id = id;
        return cs;
    }
    
#define NitsNamedCallSite(id)  NitsMakeCallSite(id, __FUNCTION__, __FILE__, __LINE__)
#define NitsHere()             NitsMakeCallSite(-1, __FUNCTION__, __FILE__, __LINE__)
#define NitsReservedCallSite() NitsMakeCallSite(-3, NULL, NULL, 0)
#define TSITE(id)              NitsMakeCallSite(id, NULL, __FILE__, __LINE__)
#define TLINE                  NitsMakeCallSite(-1, NULL, __FILE__, __LINE__)
    
#else /* NITS_STUB_ONLY */
    
    typedef int NitsCallSite;
    PAL_INLINE NitsCallSite NitsMakeCallSite(
                   int id,
        _In_opt_z_ const char *function,
        _In_opt_z_ const char *file,
                   int line)
    {
        NitsCallSite cs = {0};
        return cs;
    }
    
#define NitsNamedCallSite(id) 0
#define NitsReservedCallSite() 0
#define NitsHere()            0
#define TSITE(id)   0
#define TLINE       0
    
#endif /* NITS_STUB_ONLY */

/*
 * This version of the interface works on a plain C compiler.
 */

/*
 * NITS Fault Injection Modes
 * --------------------------
 * Used to enable or disable fault injection.
 *  -Automatic: Enabled.
 *  -Manual:    Disabled.
 * Also used to control whether tracing/assert functions are active during
 * fault injection.
 *  -Automatic: Silenced if a fault was automatically injected.
 *  -Manual:    Always triggers regardless of the fault injection state.
 */
typedef enum _NitsFaultMode
{
    NitsAutomatic   = 0,
    NitsManual      = 1
} NitsFaultMode;

/*
 * NITS Call Sites
 * ---------------
 * This construct indicates where a particular event or message came from.
 * May be traced to the console, to logs, or appear in the debugger.
 *
 */

/*
 * NITS v2 API
 * ---------------
 * This section contains the NITS v2 interfaces. All functions in the NitsFT
 * may be called from product or test binaries in either C or C++, but the C++
 * wrapper classes (yet to be defined) are only available in a C++ environment.
 *
 * The NITS function table only exists on test-instrumented builds. Product
 * code should use the macros below that compile to nothing on non-instrumented
 * builds.
 *
 */
typedef enum _NitsResult
{
    NitsFalse = 0,
    NitsTrue  = 1
} NitsResult;

/*
 * NitsResourceScope
 * -----------------
 * Determines the level of strictness for leak detection using
 * NitsBeginResource, NitsChangeResource, and NitsEndResource. Each resource
 * defines its own scope. The user also selects a maximum level of strictness
 * on the command line. Each test case may also define its own maximum level of
 * strictness if desired.
 *
 *  NitsDisabledScope: Command-line default. Disables all checking. No
 *      constraints.
 *
 *  NitsProcessScope: Relaxed. Detects leaks when the containing process exits
 *      or the current test run terminates. Cannot distinguish between
 *      activities occurring in the same process.  
 *
 *  NitsCleanupScope: Permissive. Also detects leaks when all body and setup
 *      fixtures have exited. Can distinguish between test cases, except cases
 *      sharing fixtures with NitsShared.
 *
 *  NitsFixtureScope: Restrictive. Also detects leaks when the containing
 *      fixture exits. Can distinguish between fault injection iterations.
 *
 *  TODO: Resource tracking is not yet implemented.
 */
typedef struct _NitsResourceScope *NitsResourceScope;
#define NitsDisabledScope ((NitsResourceScope)2)
#define NitsProcessScope ((NitsResourceScope)3)
#define NitsCleanupScope ((NitsResourceScope)4)
#define NitsFixtureScope ((NitsResourceScope)5)

#ifndef NITS_STUB_ONLY
/*
 * NitsTestMode
 * ------------
 * Determines the level of robustness used in a test case. Each test case
 * defines its own mode. The user also selects a maximum mode on the command
 * line, which prevents the more robust modes from being used for the entire
 * test run.
 *
 *  NitsTestOmit: Does not exist. Reports nothing.
 *
 *  NitsTestSkip: Temporarily disabled, or not applicable to the current
 *      machine. Reports Skipped.
 *
 *  NitsTestEnable: Runs normally, without fault injection.
 *
 *  NitsTestIterativeFault: Runs normally, then faults one call site at a time,
 *      in order. Hits any single-fault scenario, but very slow.
 *
 *  NitsTestStackFault: Runs normally, then faults one call site at a time,
 *      based on a stack frame database. This hits most issues that iterative
 *      fault injection hits, but not all. Much faster.
 *
 *  NitsTestCompoundFault: Command-line default. Runs normally, then faults
 *      arbitrary combinations of call sites, based on a stack frame database.
 *      Iterative fault injection does not hit these errors.
 *
 *  TODO: NitsTestCompoundFault is not yet implemented. Currently the same as
 *  NitsTestStackFault.
 */

typedef struct _NitsTestMode *NitsTestMode;
#define NitsTestOmit ((NitsTestMode)6)
#define NitsTestSkip ((NitsTestMode)7)
#define NitsTestEnable ((NitsTestMode)8)
#define NitsTestIterativeFault ((NitsTestMode)9)
#define NitsTestStackFault ((NitsTestMode)10)
#define NitsTestCompoundFault ((NitsTestMode)11)

/*
 * NitsIsolationMode
 * -----------------
 * Determines the level of isolation used in a test case. Each test case
 * defines its own mode. The user also selects a minimum level of isolation on
 * the command line, which prevents the less isolated modes from being used for
 * the entire test run.
 *
 *  NitsIsolated: Runs in a separate child process. Use this for tests that
 *      can't clean up properly. Avoid this setting wherever possible.
 *
 *  NitsDedicated: Runs in the same process, and all setup/cleanup code runs for
 *      each test case.
 *
 *  NitsShared: Command-line default. Setup/cleanup of each test case may be
 *      shared with other test cases that allow it.
 *
 *  TODO: NitsShared is not yet implemented. Currently the same as NitsDedicated.
 */
typedef struct _NitsIsolationMode *NitsIsolationMode;
#define NitsIsolated ((NitsIsolationMode)12)
#define NitsDedicated ((NitsIsolationMode)13)
#define NitsShared ((NitsIsolationMode)14)

/*
 * NitsTrapHandle
 * ----------
 * Used for accessing trap tables dynamically at runtime.
 */
typedef void *NitsTrapHandle;

typedef struct _NitsFT
{
    /*
     * ShouldFault
     * -----------
     * Determines if the current call site should return an error regardless of
     * its actual ability to complete successfully. Used for manual and
     * automatic fault injection.
     */
    NitsResult (NITS_CALL *ShouldFault)(
        NitsCallSite line,
        NitsFaultMode mode);

    /*
     * Trace
     * -----
     * Logs a string and the call site where it came from.
     */
    void (NITS_CALL *TraceA)(
        _In_z_ const char *text,
               NitsCallSite line,
               NitsFaultMode mode);

    /*
     * Assert
     * ------
     * Tests a boolean assertion of the form test != 0 and traces diagnostic
     * information when this is not true.
     */
    NitsResult (NITS_CALL *AssertA)(
               int test,
        _In_z_ const char *text,
        _In_z_ const char *description,
               NitsCallSite line,
               NitsFaultMode mode);

    /*
     * Compare
     * -------
     * Tests an integer assertion of the form lhs == rhs and traces diagnostic
     * information when this is not true.
     */
    NitsResult (NITS_CALL *CompareA)(
               int lhs,
               int rhs,
        _In_z_ const char *lhsText,
        _In_z_ const char *rhsText,
        _In_z_ const char *description,
               NitsCallSite line,
               NitsFaultMode mode);

    /*
     * CompareString
     * -------------
     * Tests a string assertion of the form lhs == rhs and traces
     * diagnostic information when this is not true.
     */
    NitsResult (NITS_CALL *CompareStringA)(
        _In_z_ const char *lhs,
        _In_z_ const char *rhs,
        _In_z_ const char *lhsText,
        _In_z_ const char *rhsText,
        _In_z_ const char *description,
               NitsCallSite line,
               NitsFaultMode mode);

    /*
     * CompareSubstring
     * ----------------
     * Tests a string assertion of the form lhs CONTAINS rhs and traces
     * diagnostic information when this is not true.
     */
    NitsResult (NITS_CALL *CompareSubstringA)(
        _In_z_ const char *lhs,
        _In_z_ const char *rhs,
        _In_z_ const char *lhsText,
        _In_z_ const char *rhsText,
        _In_z_ const char *description,
               NitsCallSite line,
               NitsFaultMode mode);

    /*
     * DidFault
     * --------
     * Allows tests to determine if a fault was automatically injected or not.
     * This helps tests be more precise about detecting ignored errors.
     */
    NitsResult (NITS_CALL *DidFault)();

    /*
     * IsActivated
     * -----------
     * Returns NitsTrue if the current binary is participating in a unit test
     *  run, NitsFalse otherwise.
     */
    NitsResult (NITS_CALL *IsActivated)();

    /*
     * StopReportingIgnoredErrors
     * --------------------------
     * All locations after this point in the unit test will not be validated
     *  to ensure they result in a failure. Use sparingly. Sometimes helps with
     *  suppressing spurious timing-related warnings.
     */
    void (NITS_CALL *StopReportingIgnoredErrors)();
    
    /*
     * GetInt
     * ------
     * Retrieves a named integer parameter by reference. The caller may read
     * and write to this location anytime during the current test fixture.
     */
    int *(NITS_CALL *GetInt)(
        _In_z_ const char *name);

    /*
     * GetString
     * ---------
     * Retrieves a named string parameter. The caller may read this buffer
     * anytime during the current test fixture, but must call GetString again
     * to see the latest value.
     */
    const char *(NITS_CALL *GetStringA)(
        _In_z_ const char *name);

    /*
     * SetInt
     * ------
     * Sets a named integer parameter. When the current fixture exits, it
     * automatically resets to its previous value. 
     */
    void (NITS_CALL *SetInt)(
        _In_z_ const char *name,
               int data);

    /*
     * SetString
     * ---------
     * Sets a named string parameter. When the current fixture exits, it
     * automatically resets to its previous value. 
     */
    void (NITS_CALL *SetStringA)(
        _In_z_ const char *name,
        _In_z_ const char *data);

    /*
     * SetMode
     * -------
     * Changes the test mode of the current test case. May be called during
     * setup to enable or disable the test, or during the body to enable or
     * disable fault injection. This is considered in conjunction with all the
     * fixtures that declare a test mode; the least aggressive setting will be
     * used.
     */
    void (NITS_CALL *SetMode)(
        NitsTestMode mode); 

    /*
     * SetFault
     * --------
     * Configures a call site for manual fault injection. When ShouldFault is
     * called from the site the Nth time, ShouldFault returns NitsTrue. Use
     * attempt=1 for the first attempt. Multiple calls to SetFault with
     * different site/attempt combinations are cumulative.
     *
     * N.B. Tests using manual fault injection can still be run under automatic
     * fault injection, if the test checks for a specific error.
     */
    void (NITS_CALL *SetFault)(
        _In_opt_z_ const char *function,
        _In_z_     const char *id,
                   int attempt);

    /*
     * SetWait
     * -------
     * Configures a call site for manual thread blocking. When ShouldFault is
     * called from the site the Nth time, the thread will wait for Signal to be
     * called on the given event name, if it has not been called already.
     * Multiple calls to SetWait with different site/attempt combinations are
     * cumulative.
     *
     * N.B. Use this with Signal and Wait to simulate race conditions.
     * N.B. This can be used with automatic fault injection if the test doesn't
     * become unresponsive or take too long.
     */
    void (NITS_CALL *SetWait)(
        _In_opt_z_ const char *function,
        _In_z_     const char *id,
                   int attempt,
        _In_z_     const char *event);

    /*
     * Signal
     * ------
     * Manually unblocks all threads forced to wait on the given event name.
     * This also affects threads that have not yet waited. This action cannot
     * be undone except through ResetFaults. Multiple calls with different
     * event names are cumulative.
     *
     * N.B. Use Wait to efficiently determine when to call Signal.
     */
    void (NITS_CALL *Signal)(
        _In_z_ const char *event);

    /*
     * Wait
     * ----
     * Blocks until ShouldFault is called from the given call site the Nth
     * time, according to attempt. If this has already happened since the last
     * call to ResetFaults, returns NitsTrue immediately. Otherwise, if the
     * timeout (in milliseconds) elapses, returns NitsFalse. If no SetWait or
     * SetFault exists for this site and attempt, returns NitsFalse
     * immediately.
     *
     * N.B. This function helps avoid sleeps & timeouts in test code.
     * N.B. Use a short timeout when automatic fault injection is used.
     */
    NitsResult (NITS_CALL *Wait)(
        _In_opt_z_ const char *function,
        _In_z_     const char *id,
                   int attempt,
                   int timeout);

    /*
     * ResetFaults
     * -----------
     * Resets manually configured fault injection. This removes settings from
     * all previous calls to SetFault, SetWait, and Signal. This has no effect
     * on automatic fault injection or data from SetInt/SetString.
     */
    void (NITS_CALL *ResetFaults)();

    /*
     * BeginResource
     * -------------
     * Annotates the allocation of any uniquely identified resource. The type
     * is an arbitrary classification defined by the application. Verifies that
     * the resource does not currently exist.
     */
    void (NITS_CALL *BeginResource)(
        _In_ void *resource,
             int type,
             NitsResourceScope scope,
             NitsCallSite line);

    /*
     * ChangeResource
     * --------------
     * Changes the scope of an existing resource. Verifies that the resource
     * currently exists.
     */
    void (NITS_CALL *ChangeResource)(
        _In_ void *resource,
             int type,
             NitsResourceScope scope,
             NitsCallSite line);

    /*
     * EndResource
     * -----------
     * Annotates the deallocation of a previously identified resource. When
     * resource tracking is enabled, NITS uses this information to detect
     * leaks. Verifies that the resource exists.
     */
    void (NITS_CALL *EndResource)(
        _In_ void *resource,
             int type,
             NitsCallSite line);

    void *unused1;
    void *unused2;
    void *unused3;

    /*
     * OpenTrap
     * --------
     * Loads a trap table from a given binary into memory. Returns a handle
     * that must be passed to CloseTrap.
     */
    NitsTrapHandle (NITS_CALL *OpenTrap)(
        _In_z_ const char *binary,
        _In_z_ const char *table,
               unsigned version);

    /*
     * GetTrap
     * -------
     * Retrieves a loaded trap table, and validates that a given offset is in
     * range. If the trap table is too small, GetTrap generates a fatal error.
     */
    const void *(NITS_CALL *GetTrap)(
        _In_ NitsTrapHandle handle,
             unsigned offset);

    /*
     * LastTrap
     * --------
     * During the execution of a trap, retrieves the table it replaced.
     * Generates a fatal error if the current thread is not inside the context
     * of a replaced trap.
     */
    const void *(NITS_CALL *LastTrap)(
        _In_z_ const char *table,
               unsigned offset);

    /*
     * SetTrap
     * -------
     * Prepares to edit a loaded trap table. Validates that the given offset is
     * in range, otherwise generates a fatal error. The caller (the NitsSetTrap
     * macro) then performs the edit using the returned table address.
     */
    void *(NITS_CALL *SetTrap)(
        _In_ NitsTrapHandle handle,
        _In_ void *function,
             unsigned offset);

    /*
     * CopyTrap
     * --------
     * Replaces the value of the "from" trap with the value of the "to" trap in
     * all participating processes containing the "from" trap, including
     * processes that haven't been created yet. This operation is never
     * reversed, but stops affecting more processes once the test completes.
     */
    void (NITS_CALL *CopyTrap)(
        _In_z_ const char *table,
        _In_z_ const char *from,
        _In_z_ const char *to);

    /*
     * CloseTrap
     * ---------
     * Releases a loaded trap table and restores its original values. The
     * binary could be unloaded.
     */
    void (NITS_CALL *CloseTrap)(
        _In_ NitsTrapHandle handle);

    /*
     * TestResult
     * --------
     * Allows tests to determine if a fault was automatically injected or not.
     * This helps tests be more precise about detecting ignored errors.
     */
    int (NITS_CALL *GetResult)();

} NitsFT;

#include <stddef.h>
#define OffsetOfField(table, field) offsetof(table##FT, field)

/*
* Used to keep track of whether NITS table should be used to implement NITS API functions
* If NITS injector is present and has patched the NITS stub with actual NITS API, Or if presence of NITS is unknown, 
* then the NITS table will be used
* If it is known that NITS injector is not present or the stub has not been patched by NITS injector 
* then the NITS table will not be used to implement the API functions
*/
typedef enum _NitsPresence
{
    NitsPresenceUnknown = 0, // initial state in stub when no NITS api calls have been made and
                            // injector has not patched the stub table either
    NitsStubbedOut  = 1,    // state when some NITS api call is made and stub is has signalled injector
                            // to patch its NITS api table; or when that is done and it is decided that 
                            // NITS API in this stub will act as a no-op
    NitsActive  = 2        // state when injector has patched the stub NITS API table with
                            // actual NITS implementation i.e. unittests are running at this time
                            // all NITS calls go into the NITS framework implementation at that time
} NitsPresence;

#if (defined(HOOK_BUILD) || defined(DEBUG_BUILD)) && !defined(TEST_BUILD) && !defined(LIB_BUILD)
#define NITS NITS_STUB
#define NITS_PRESENCE NITS_PRESENCE_STUB
#else
#define NITS NITS_IMPL
#define NITS_PRESENCE NITS_PRESENCE_IMPL
#endif

NITS_EXPORT NITS_CONST_FT NitsFT NITS;
NITS_EXPORT ptrdiff_t NITS_PRESENCE;

#define ShouldCallNITSTable \
    (NITS_PRESENCE != NitsStubbedOut)

#define NITS_UNUSED(X) ((void)X)

#define NitsShouldFault(line, mode) \
    (ShouldCallNITSTable ? NITS.ShouldFault(line, mode) : NitsFalse)
#define NitsBeginResource(resource, type, scope, line) \
    (ShouldCallNITSTable ? NITS.BeginResource(resource, type, scope, line) : NITS_UNUSED(NITS))
#define NitsChangeResource(resource, type, scope, line) \
    (ShouldCallNITSTable ? NITS.ChangeResource(resource, type, scope, line) : NITS_UNUSED(NITS))
#define NitsEndResource(resource, type, line) \
    (ShouldCallNITSTable ? NITS.EndResource(resource, type, line) : NITS_UNUSED(NITS))
#define NitsTraceExA(text, line, mode) \
    (ShouldCallNITSTable ? NITS.TraceA(text, line, mode) : NITS_UNUSED(NITS))
#define NitsTraceExW(text, line, mode) \
    (ShouldCallNITSTable ? NITS.TraceW(text, line, mode) : NITS_UNUSED(NITS))
#define NitsAssertExA(test, description, line, mode) \
    (ShouldCallNITSTable ? NITS.AssertA(!!(test), #test, description, line, mode) : NitsTrue)
#define NitsAssertExW(test, description, line, mode) \
    (ShouldCallNITSTable ? NITS.AssertW(!!(test), #test, description, line, mode) : NitsTrue)
#define NitsCompareExA(lhs, rhs, description, line, mode) \
    (ShouldCallNITSTable ? NITS.CompareA(lhs, rhs, #lhs, #rhs, description, line, mode) : NitsTrue)
#define NitsCompareExW(lhs, rhs, description, line, mode) \
    (ShouldCallNITSTable ? NITS.CompareW(lhs, rhs, #lhs, #rhs, description, line, mode) : NitsTrue)
#define NitsCompareStringExA(lhs, rhs, description, line, mode) \
    (ShouldCallNITSTable ? NITS.CompareStringA(lhs, rhs, #lhs, #rhs, description, line, mode) : NitsTrue)
#define NitsCompareStringExW(lhs, rhs, description, line, mode) \
    (ShouldCallNITSTable ? NITS.CompareStringW(lhs, rhs, #lhs, #rhs, description, line, mode) : NitsTrue)
#define NitsCompareSubstringExA(lhs, rhs, description, line, mode) \
    (ShouldCallNITSTable ? NITS.CompareSubstringA(lhs, rhs, #lhs, #rhs, description, line, mode) : NitsTrue)
#define NitsCompareSubstringExW(lhs, rhs, description, line, mode) \
    (ShouldCallNITSTable ? NITS.CompareSubstringW(lhs, rhs, #lhs, #rhs, description, line, mode) : NitsTrue)
#define NitsDidFault() \
    (ShouldCallNITSTable ? NITS.DidFault() : NitsFalse)
#define NitsIsActivated() \
    (ShouldCallNITSTable ? NITS.IsActivated() : NitsFalse)
#define NitsStopReportingIgnoredErrors() \
    NITS.StopReportingIgnoredErrors()
#define NitsGetInt(name) \
    (ShouldCallNITSTable ? NITS.GetInt(#name) : NULL)
#define NitsGetStringA(name) \
    (ShouldCallNITSTable ? NITS.GetStringA(#name) : NULL)
#define NitsGetStringW(name) \
    (ShouldCallNITSTable ? NITS.GetStringW(#name) : NULL)
#define NitsSetInt(name, data) \
    (ShouldCallNITSTable ? NITS.SetInt(#name, data) : NITS_UNUSED(NITS))
#define NitsSetStringA(name, data) \
    (ShouldCallNITSTable ? NITS.SetStringA(#name, data) : NITS_UNUSED(NITS))
#define NitsSetStringW(name, data) \
    (ShouldCallNITSTable ? NITS.SetStringW(#name, data) : NITS_UNUSED(NITS))
#define NitsSetMode(mode) \
    (ShouldCallNITSTable ? NITS.SetMode(mode) : NITS_UNUSED(NITS))
#define NitsSetFault(function, id, attempt) \
    (ShouldCallNITSTable ? NITS.SetFault(#function, #id, attempt) : NITS_UNUSED(NITS))
#define NitsSetWait(function, id, attempt, event) \
    (ShouldCallNITSTable ? NITS.SetWait(#function, #id, attempt, #event) : NITS_UNUSED(NITS))
#define NitsSignal(event) \
    (ShouldCallNITSTable ? NITS.Signal(#event) : NITS_UNUSED(NITS))
#define NitsWait(function, id, attempt, timeout) \
    (ShouldCallNITSTable ? NITS.Wait(#function, #id, attempt, timeout) : NitsTrue)
#define NitsResetFaults() \
    (ShouldCallNITSTable ? NITS.ResetFaults() : NITS_UNUSED(NITS))
#define NitsRegisterFixture(name, contextType, proc, spec, count, type) \
    NITS.RegisterFixture(#name, #contextType, proc, spec, count, type)
#define NitsSetContext(proc, context) \
    NITS.SetContext(proc, context)
#define NitsGo() \
    NITS.Go(__COUNTER__)
#define NitsTestResult() \
    NITS.GetResult()

#define NitsOpenTrap(binary, table) \
    NITS.OpenTrap(binary, #table, table##version)
#define NitsCloseTrap(handle) \
    NITS.CloseTrap(handle)

#define NitsGetTrap(handle, table, field) \
    ((const table##FT *)NITS.GetTrap(handle, OffsetOfField(table, field)))->field
#define NitsLastTrap(table, field) \
    ((const table##FT *)NITS.LastTrap(#table, OffsetOfField(table, field)))->field
#define NitsSetTrap(handle, table, field, function) \
    ((table##FT *)NITS.SetTrap(handle, (void *)function, OffsetOfField(table, field)))->field = function
#define NitsCopyTrap(table, from, to) \
    NITS.CopyTrap(#table, from, to)

#else /* NITS_STUB_ONLY */

#define NitsShouldFault(line, mode) NitsFalse
#define NitsBeginResource(resource, type, scope, line)
#define NitsChangeResource(resource, type, scope, line)
#define NitsEndResource(resource, type, line)
#define NitsTraceExA(text, line, mode)
#define NitsTraceExW(text, line, mode)
#define NitsAssertExA(test, description, line, mode) NitsTrue
#define NitsAssertExW(test, description, line, mode) NitsTrue
#define NitsCompareExW(lhs, rhs, description, line, mode) NitsTrue
#define NitsCompareExA(lhs, rhs, description, line, mode) NitsTrue
#define NitsCompareStringExA(lhs, rhs, description, line, mode) NitsTrue
#define NitsCompareStringExW(lhs, rhs, description, line, mode) NitsTrue
#define NitsCompareSubstringExA(lhs, rhs, description, line, mode) NitsTrue
#define NitsCompareSubstringExW(lhs, rhs, description, line, mode) NitsTrue
#define NitsDidFault() NitsFalse
#define NitsIsActivated() NitsFalse
#define NitsStopReportingIgnoredErrors()
#define NitsGetInt(name) 0
#define NitsGetStringA(name) 0
#define NitsGetStringW(name) 0
#define NitsSetInt(name, data)
#define NitsSetStringA(name, data)
#define NitsSetStringW(name, data)
#define NitsSetMode(mode)
#define NitsSetFault(function, id, attempt)
#define NitsSetWait(function, id, attempt, event)
#define NitsSignal(event)
#define NitsWait(function, id, attempt, timeout) NitsFalse
#define NitsResetFaults()
#define NitsRegisterFixture(name, contextType, proc, spec, count, type)
#define NitsSetContext(proc, context)
#define NitsGo(currentFixture)

#define NitsOpenTrap(binary, table) 0
#define NitsCloseTrap(handle) 

#define NitsGetTrap(handle, table, field) 0
#define NitsLastTrap(table, field) 0
#define NitsSetTrap(handle, table, field, function) 0
#define NitsCopyTrap(table, from, to)
#define NitsTestResult()

#endif /* NITS_STUB_ONLY */

#define NitsTrapTable(table, ver) \
    static const unsigned table##version = ver; \
    typedef struct _##table##FTversion { \
        unsigned data[ver + 1]; \
    } table##FTversion; \
    typedef struct _##table##FT table##FT; \
    struct _##table##FT { \
        unsigned bytes; \
        unsigned version;
#define NitsEndTrapTable };
#define NitsTrapExport(table) \
    NITS_EXTERN_C NITS_DLLEXPORT NITS_CONST_FT table##FT table;
#define NitsTrapImport(table) \
    NITS_EXTERN_C NITS_DLLIMPORT NITS_CONST_FT table##FT table;

#define NitsTrapValue(table)                             \
    NITS_DLLEXPORT NITS_CONST_FT table##FT table = {     \
        sizeof(table##FT),                                      \
        (sizeof(table##FTversion)/sizeof(unsigned)-1),

#define NitsEndTrapValue };

#define NitsTraceEx             NitsTraceExA
#define NitsAssertEx            NitsAssertExA
#define NitsCompareEx           NitsCompareExA
#define NitsCompareStringEx     NitsCompareStringExA
#define NitsCompareSubstringEx  NitsCompareSubstringExA
#define NitsGetString           NitsGetStringA
#define NitsSetString           NitsSetStringW

#define NitsIgnoringError() \
    NitsAssert(!NitsDidFault(), PAL_T("Ignoring error deliberately"));

#define NitsTrace(text) \
    NitsTraceEx(text, TLINE, NitsAutomatic)
#define NitsAssert(text, description) \
    NitsAssertEx(text, description, TLINE, NitsAutomatic)
#define NitsAssertOrReturn(expression, description) \
  { if (!(NitsAssert(expression, description))) { NitsReturn; }}
    
#define NitsCompare(lhs, rhs, description) \
    NitsCompareEx(lhs, rhs, description, TLINE, NitsAutomatic)
#define NitsCompareString(lhs, rhs, description) \
    NitsCompareStringEx(lhs, rhs, description, TLINE, NitsAutomatic)
#define NitsCompareSubstring(lhs, rhs, description) \
    NitsCompareSubstringEx(lhs, rhs, description, TLINE, NitsAutomatic)

/* Some of the old V1 macros for semi-compatibility. */
#define TSTRACE(text, site) \
    NitsTraceEx(text, site, NitsAutomatic)
#define TSASSERT(test, description, site) \
    NitsAssertEx(test, description, site, NitsAutomatic)
#define TSINT(lhs, rhs, description, site) \
    NitsCompareEx(lhs, rhs, description, site, NitsAutomatic)
#define TSSTRING(lhs, rhs, description, site) \
    NitsCompareStringEx(lhs, rhs, description, site, NitsAutomatic)
#define TSSUBSTRING(str, sub, description, site) \
    NitsCompareSubstringEx(str, sub, description, site, NitsAutomatic)

#define TTRACE NitsTrace
#define TASSERT NitsAssert
#define TINT NitsCompare
#define TSTRING NitsCompareString
#define TSUBSTRING NitsCompareSubstring

#ifndef __cplusplus
#define TCOMPARE TINT
#define TSCOMPARE TSINT
#endif

/* Everything after this point is the old NITS v1 interface. */

#ifdef __cplusplus
/*
 * Test Declaration Instructions
 * -----------------------------
 * Tests are defined as a hierarchy of setting switches and a body. Each test
 *  choice contains setup and cleanup code. The setup code modifies test
 *  settings and registers child switches. Macros allow easy definition of
 *  setup code, and cleanup code is simply defined as function pointers.
 *
 * Each switch operates as either a group (AND) or a choice (OR):
 *  Groups: Runs setup/cleanup for all subtrees.
 *  Choices: Runs setup/cleanup for one subtree at a time, rerunning the test
 *      for each subtree.
 */

namespace TestSystem
{
//TODO: Deprecate this macro. It needs C++ due to overloading.
#define TSCOMPARE(lhs, rhs, description, site) \
    TestSystem::Compare(lhs, rhs, #lhs, #rhs, description, site)
#define TCOMPARE(lhs, rhs, description) \
    TSCOMPARE(lhs, rhs, description, NitsHere())
    
//TODO: Remove this and all references.
#define TABORT(test, description) \
    if (!TASSERT(test, description)) throw description;

static const NitsFaultMode Automatic = NitsAutomatic;
static const NitsFaultMode Manual = NitsManual;

//Wrapper for source file locations.
//Includes an optional ID used in fault sim commands.
typedef NitsCallSite CallSite;

#ifdef NITS_STUB_ONLY
//Public build stubs.

inline NitsResult Compare(int lhs,
                    int rhs,
                    _In_ PCSTR lhsText,
                    _In_ PCSTR rhsText,
                    _In_ PCSTR description,
                    NitsCallSite line,
                    NitsFaultMode mode = NitsAutomatic)
{
    return NitsTrue;
}

inline NitsResult Compare(_In_ PCSTR lhs,
                    _In_ PCSTR rhs,
                    _In_ PCSTR lhsText,
                    _In_ PCSTR rhsText,
                    _In_ PCSTR description,
                    NitsCallSite line,
                    NitsFaultMode mode = NitsAutomatic)
{
    return NitsTrue;
}

inline bool ShouldFault(CallSite const &site,
                        NitsFaultMode mode = NitsAutomatic)
{
    return false;
}

inline bool DidFault()
{
    return false;
}

inline void StopReportingIgnoredErrors()
{
}

inline DWORD GetFaultWin32() {return S_OK;}

inline bool IsUnittestRunning() {return false;}

#else
//Private build interfaces.

#define TGROUP(name) \
    NITS_EXTERN_C void Setup_##name(TestSystem::Switch &); \
    TestSystem::Switch name(stringify(name), Setup_##name, true); \
    void Setup_##name

#define TCHOICE(name) \
    NITS_EXTERN_C void Setup_##name(TestSystem::Switch &); \
    TestSystem::Switch name(stringify(name), Setup_##name, false); \
    void Setup_##name

#define TSETUP(name, body) \
    NITS_EXTERN_C void Setup_##name(TestSystem::Switch &); \
    TestSystem::Test name(stringify(name), Setup_##name, body); \
    void Setup_##name

#define TTEST(name) \
    NITS_EXTERN_C void Setup_##name(TestSystem::Switch &) {} \
    NITS_EXTERN_C void Body_##name(TestSystem::Switch &); \
    TestSystem::Test name(stringify(name), Setup_##name, Body_##name); \
    void Body_##name

#define TSET_ISOLATION(test) \
    extern TestSystem::Test test; \
    TestSystem::SetIsolation Isolate_##test(test);

#define TSET_TIMEOUT(test, seconds) \
    extern TestSystem::Test test; \
    TestSystem::SetTimeout Timeout_##test(test, seconds);

#define NitsTestSetTimeout(test, seconds) \
    extern TestSystem::Test fixture_##test; \
    TestSystem::SetTimeout Timeout_##fixture_##test(fixture_##test, seconds);

#define NitsTestSetIsolation(test) \
    extern TestSystem::Test fixture_##test; \
    TestSystem::SetIsolation Isolate_##fixture_##test(fixture_##test);

class Test;
class Event;
class Buffer;
class ChildList;

//Test result codes.
//Faulted, Passed, and Skipped results are shown only in verbose mode.
enum Result
{
    Faulted = 0,    //Passed with successful fault simulation.
    Passed,         //No failed asserts or test errors.
    Skipped,        //Test was not run.
    Omitted,        //test choice was asked to be omitted by the test writer    
    Killed,         //The test took too long and was killed.
    Failed,         //An assert failed, but no test errors.
    Error,          //Test code is not working properly.
    ResultCount
};


//Shared Memory API
//------------------
//Safely creates memory spaces shared across processes.
//Objects within these spaces MUST be self-relative.

//Creates and copies an application context into shared memory.
//Multiple calls with the same name and size retrieve the existing context.
//Synchronized to prevent any caller from seeing partially copied contexts.
NITS_EXPORT DWORD NITS_CALL Initialize(_In_z_ const PAL_Char * name,
                          _In_reads_bytes_(bytes) void const *context,
                          _Outptr_result_bytebuffer_(bytes) void **shared,
                          long bytes);

//Using the template form is recommended.
/*template <typename T>
inline DWORD Initialize(_In_ const PAL_Char * name,
                        _In_ T const &context,
                        __deref_out T *&shared)
{
    void **temp = reinterpret_cast<void **>(&shared);
    return Initialize(name, &context, temp, sizeof(T));
}*/

//Tracing and Assertion API
//-------------------------
//Contains functions for tracing, assertions, and comparisons.

//Integer comparison test.
inline NitsResult Compare(int lhs,
                      int rhs,
                      _In_ const char *lhsText,
                      _In_ const char *rhsText,
                      _In_ const char *description,
                      NitsCallSite line,
                      NitsFaultMode mode = Automatic)
{
    return NITS.CompareA(lhs, rhs, lhsText, rhsText, description, line, mode);
}

//String-comparison test.
inline NitsResult Compare(_In_ const char *lhs,
                      _In_ const char *rhs,
                      _In_ const char *lhsText,
                      _In_ const char *rhsText,
                      _In_ const char *description,
                      NitsCallSite line,
                      NitsFaultMode mode = NitsAutomatic)
{
    return NITS.CompareStringA(lhs, rhs, lhsText, rhsText, description, line, mode);
}


template <typename T>
class SharedMemory
{
public:
    SharedMemory(_In_z_ const PAL_Char * name)
        : m_shared(NULL)
    {
        T context;
        void **temp = reinterpret_cast<void **>(&m_shared);
        DWORD error = Initialize(name, &context, temp, sizeof(T));
        TSCOMPARE(error, NO_ERROR, "Failed to create shared memory!", TLINE);
    };

    bool IsValid() const {return m_shared != NULL;}

    operator T *() {return m_shared;}
    operator T const *() const {return m_shared;}

    T const *operator *() const {return m_shared;}
    T const *operator ->() const {return m_shared;}
    T *operator *() {return m_shared;}
    T *operator ->() {return m_shared;}
private:
    T *m_shared;
};

//Fault Simulation API
//--------------------
//Functions for simulating faults and propagating error codes.

//Returns true if a fault should be simulated.
//Simulated thread delays occur synchronously during this function.
//Passing 'Manual' mode excludes this call from automatic fault sim loops.
inline NitsResult ShouldFault(CallSite const &site,
                          NitsFaultMode mode = NitsAutomatic)
{
    return NitsShouldFault(site, mode);
}

inline NitsResult DidFault()
{
    return NitsDidFault();
}

inline void StopReportingIgnoredErrors()
{
    return NitsStopReportingIgnoredErrors();
}

//Retrieves the simulated error.
NITS_EXPORT DWORD NITS_CALL GetFaultWin32();

inline NitsResult IsUnittestRunning()
{
    return NitsIsActivated();
}

class Switch;

NITS_EXPORT void NITS_CALL NitsSwitchCreate(
    _Inout_ Switch *test,
    _In_ const PAL_Char * name,
    _In_ void (NITS_CALL *setup)(Switch &),
    bool group);

NITS_EXPORT void NITS_CALL NitsSwitchDelete(
    _Inout_ Switch *test);

NITS_EXPORT void NITS_CALL NitsSetTeardownSwitch(
        _Inout_ Switch *test, Switch *teardownSwitch, int isCleanup);

NITS_EXPORT void ** NITS_CALL NitsGetInitArray(_Inout_ Switch *test);

NITS_EXPORT int NITS_CALL NitsIsSplitFixture(_In_ Switch *test);

NITS_EXPORT void NITS_CALL NitsSwitchChild(
    _Inout_ Switch *test,
    _In_ Switch &child);

NITS_EXPORT bool NITS_CALL NitsSwitchGetEnabled(
    _Inout_ Switch const *test);

NITS_EXPORT void NITS_CALL NitsSwitchSetFaultMode(
    _Inout_ Switch *test,
    NitsFaultMode mode);

NITS_EXPORT void NITS_CALL NitsSwitchSetEnabled(
    _Inout_ Switch *test,
    bool enabled);

NITS_EXPORT void NITS_CALL NitsSwitchSetFlaky(
    _Inout_ Switch *test,
    bool enabled);

NITS_EXPORT void NITS_CALL NitsSwitchFaultExclude(
    _Inout_ Switch *test,
    _In_reads_opt_(count) int sites[],
    int count);

NITS_EXPORT void NITS_CALL NitsSwitchFaultOff(
    _Inout_ Switch *test);

NITS_EXPORT void NITS_CALL NitsSwitchFaultHresult(
    _Inout_ Switch *test,
    int site,
    HRESULT error,
    int attempt = 0);

NITS_EXPORT void NITS_CALL NitsSwitchFaultError(
    _Inout_ Switch *test,
    int site,
    DWORD error,
    int attempt = 0);

NITS_EXPORT void NITS_CALL NitsSwitchFaultWait(
    _Inout_ Switch *test,
    int site,
    _In_ Event const &event,
    int attempt = 0);

class SetIsolation;
class SetTimeout;
class Test;

NITS_EXPORT void NITS_CALL NitsTestSetIsolationHelper(
    _In_ Test &test);

NITS_EXPORT void NITS_CALL NitsTestSetTimeoutHelper(
    _In_ Test &test,
    int seconds);

NITS_EXPORT void NITS_CALL NitsTestCreate(
    _Inout_ Test *test,
    _In_ const PAL_Char * name,
    _In_ void (NITS_CALL *setup)(Switch &),
    _In_ void (NITS_CALL *body)(Switch &),
    bool deleteMeAfterRun = false);

/* Only test code in nits process can call this to get parameter passed to the nits command-line */
NITS_EXPORT const PAL_Char *NITS_CALL NitsTestGetParam(_In_z_ const PAL_Char *paramName);

/* Only test code in nits process can call this to enable faultsim for all tests from this point */
NITS_EXPORT void NITS_CALL NitsEnableFaultSimAll();

/* Only test code in nits process can call this to disable faultsim for all tests from this point */
NITS_EXPORT void NITS_CALL NitsDisableFaultSimAll();

NITS_EXTERN_C typedef void (NITS_CALL *Proc)(Switch &test);

//Test Configuration API
//----------------------
//Tests are declared as Switch and Test objects.
//Each test has a hierarchy of Switch objects declared using Child().
//The setup function must always declare the same children in order.
class Switch
{
public:    

    Switch(_In_ const PAL_Char * name, _In_ Proc setup, bool group) {NitsSwitchCreate(this, name, setup, group);}


        // start:- functions for new interface

    Switch(_In_ const PAL_Char * name, _In_ Proc setup, _In_ void *(NITS_CALL *regFunc)(), _In_ Proc cleanup)
        {
                NitsSwitchCreate(this, name, setup, true);

                SetCleanup(cleanup);
                
                m_registration = regFunc();

                // the new interface tests will override the IsGroup flag here since it can be known only after the regFunc is called for the test
                m_choice = (!IsSplitFixture()) ? Switch::AllChildren : 0;               
        }

        void SetTeardownSwitch(Switch *teardownSwitch, int isCleanup) { NitsSetTeardownSwitch(this, teardownSwitch, isCleanup); }

        void **GetInitArray() { return NitsGetInitArray(this); };

        int IsSplitFixture() { return NitsIsSplitFixture(this); };

        void SetDryRun(int isDryRun) { m_dryRunToFindChildren = isDryRun; }
                
        int IsDryRunToIdentifyChildren() { return m_dryRunToFindChildren; }

    PAL_Boolean IsBodyFixture();

    PAL_Boolean IsModuleSetupFixture();

        // this is to enable a test to set the type of switch as Group or Choice at the time of test body setup being run
    void SetGroup(int group){ m_choice = group ? Switch::AllChildren : 0; }

        Switch *GetFirstSelectedChild();

        int IsNewInterfaceTest() { return (m_registration != 0); };
        
        // end:- functions for new interface    
        
    ~Switch() {NitsSwitchDelete(this);}

        
    const PAL_Char * GetName() const {return m_name;}
    bool IsGroup() const {return m_choice == AllChildren;}
        
    bool IsChoice() const {return !IsGroup();}
    bool IsChildSelected(int index) const;
    bool IsActive() const {return m_refs > 0;}

    void Child(_In_ Switch &child) {NitsSwitchChild(this, child);}     //Registers a child Switch.
    void SetCleanup(_In_ Proc cleanup) {m_cleanup = cleanup;} //Runs cleanup() after the test body.
    bool GetEnabled() const {return NitsSwitchGetEnabled(this);}

    //Sets parameters for this test only.
    //Overrides command line options.
    void SetFaultMode(NitsFaultMode mode) {NitsSwitchSetFaultMode(this, mode);}
    void SetEnabled(bool enabled) {NitsSwitchSetEnabled(this, enabled);}
    void SetFlaky(bool enabled) {NitsSwitchSetFlaky(this, enabled);}
    
    //Ignores certain call sites during automatic fault simulation.
    //Overwrites existing exclusion list.
    void FaultExclude(_In_reads_opt_(count) int sites[], int count) {NitsSwitchFaultExclude(this, sites, count);}

    //Manual fault simulation configuration methods.
    void FaultOff() {NitsSwitchFaultOff(this);}
    void FaultError(int site, DWORD error, int attempt = 0) {NitsSwitchFaultError(this, site, error, attempt);}
    void FaultWait(int site, _In_ Event const &event, int attempt = 0) {NitsSwitchFaultWait(this, site, event, attempt);}
//protected:
    void RunSetup();
    void RunCleanup();
        
    void PrintChoices(Buffer &buf);
    bool SelectChoices(_Inout_z_ PAL_Char * &choices);
    bool Next();
    void Reset();

//private:
    enum {
        AllChildren = -1
    };

        enum SwitchState
        {
                NotRunYet,
                RunOnce,
                CleanupRun
        };
        
    const PAL_Char *  m_name;     //Test name from source and command line.
    Proc    m_setup;    //Runs before the test body.
    Proc    m_cleanup;  //Runs after the test body.
    long   m_choice;   //Which child is currently selected?
    unsigned long m_index;    //Tracks Child() calls.
    int     m_refs;     //Number of RunSetup() calls.
    ChildList *m_children;

        // members for new interface
        void *m_registration; // used to hook up new interface to nits engine
        
        Switch *m_prevLayerContinuation; // used in new interface to provide a node an ability to reach its child node down the tree(tree is upside down;)

        Switch *m_sameLayerContinuation; // used in new interface to provide a node an ability to reach its sibling node at the same layer of the tree

        Switch *m_prevSwitchOnSelectedTestStack; // used to implement NitsIsSelected
        
        Switch *m_rootSwitch; // the root node from which the test should begin for this set of choices; this will be NULL for everyone except the test body from where the test starts

        int m_dryRunToFindChildren; // to identify this phase and not run the body automatically in this phase; used when identifying children in specific choice based run

        int m_notRunInCurrentTestChoice; // to keep track of which setup we ran so that during cleanup we can run only those Cleanup routines for which setups were run

        int m_someoneCalledOmit; // this is set only in the test body switch and indicates that someone called Omit in the test

    int m_filteredOutByUser; // filtered out with -match switch by the user; set only in test body to indicate that test should not execute any of the fixtures

        int m_switchState; // this is set to indicate that this fixture has been run once in current test choice so it should not be run again to ensure virtual inheritance model

    bool m_markedForRerunInFaultSimulation; // This is to implement functionality of letting users chose whether they want only test body to be rerun during fault simulation loop or 
                                            // they want to rerun entire fixture tree under current fixture.
                                            // TODO: Currently this functionality is supported only for test fixtures i.e. to rerun entire test tree including all setups, in future this should be extended
                                            // at level of individual setup/split fixtures so that user can have more granular way of choosing this                                            
};

class SetIsolation
{
public:
    SetIsolation(_In_ Test &test) {NitsTestSetIsolationHelper(test);}
};

class SetTimeout
{
public:
    SetTimeout(_In_ Test &test, int seconds) {NitsTestSetTimeoutHelper(test, seconds);}
};
    

typedef Switch ITest;

class Test : public Switch
{
public:
    friend class SetIsolation;
    friend class SetTimeout;

    Test(_In_ const PAL_Char * name,
         _In_ Proc setup,
         _In_ Proc body,
         bool deleteMeAfterRun = false) : Switch(name, setup, true) {NitsTestCreate(this, name, setup, body, deleteMeAfterRun);}

    Test(_In_ const PAL_Char * name,
         _In_ Proc setup,
         _In_ Proc body,
         _In_ void *(NITS_CALL *regFunc)(),
         _In_ Proc cleanup) : Switch(name, setup, regFunc, cleanup)
        {
                NitsTestCreate(this, name, setup, body);
        }
                
    ~Test() {}

    const PAL_Char * GetModule() const {return m_module;}
    bool GetIsolation() const {return m_isolation;}
    int GetTimeout() const {return m_timeout;}

    void PrintName(Buffer &buf, bool choices = true);

    void Execute(_In_opt_z_ const PAL_Char * choices); //Called by test framework.
//private:
    void RunVariation();

        void ContinueProcessingAfterSetup(); // calls body as needed

        void ContinueProcessingAfterBody(); // calls cleanup as needed

    void RerunFixturesMarkedForFaultSim(); // reruns all fixtures till this fixture for fault simulation

    void RunFaultInjectionLoop(); 

    void RunBody();

    void RunDeferredCleanup(); // only done in case of new interface tests like ModuleSetup tests or in future suite setup tests

    static int s_nextTimeout;
    static bool s_nextIsolation;

    const PAL_Char * m_module;
    Proc   m_body;
    int    m_timeout; //Seconds.
    bool   m_isolation;

    bool m_deleteMeAfterRun;// this is used if the test fixture was created on heap and needs to be deleted after its execution
    
        ptrdiff_t m_startTicks;

        enum TestRunState
        {
                BodyYetToRun,        
                BodyRan,
        BodySkippedDueToFailedSetup,
                PartAfterBodyRan
        };

    long m_testRunState;

    // this determines whether the test should run cleanup immediately after the body is done
    // or should it be deferred till later in which case the framework will run it explicitly
    enum CleanupMode
    {
        ImmediateCleanup, // this mode will run the cleanup immediately after the test body
        DeferredCleanup // this will defer the cleanup after the test body and let it be run later
    };

    long m_cleanupMode; 
};

class Event;
NITS_EXPORT void NITS_CALL NitsEventCreate(
    _Inout_ Event *event,
    _In_z_ const PAL_Char * name,
    NitsFaultMode mode); //Ignored if the event already exists.

NITS_EXPORT void NITS_CALL NitsEventDelete(
    _Inout_ Event *event);

//Cross-process named event.
//Used for test synchronization, simulated thread delays.
class Event
{
public:
    enum {
        MaxName = 64
    };

    Event(_In_z_ const PAL_Char * name,
          NitsFaultMode mode = Automatic) {NitsEventCreate(this, name, mode);}
    ~Event() {NitsEventDelete(this);}

    operator HANDLE() const {return m_handle;}
    operator const PAL_Char *() const {return m_name;}
//private:
    HANDLE m_handle;
    const PAL_Char * m_name;

private:
    Event(Event const &);
    void operator = (Event const &);
};

#endif /* !NITS_STUB_ONLY */

} //namespace TestSystem

#ifndef NITS_STUB_ONLY

/************************NEW_INTERFACE_START ******************************************/

enum TestFixtureType
{
    SetupFixture,
    SplitFixture,
    BodyFixture,
    CleanupFixture,
    CrashFixture,
    ModuleSetupFixture
};

PAL_BEGIN_EXTERNC

// this is for registering fixtures
struct RegistrationInfo
{
        void *selfContext; // during a test run, this will keep the pointer to structure created for this registered structure 
        void *selfStruct; // during a test run, this will keep the pointer to structure created inside selfContext
        int countOfLinks; // number of times specific registrationinfo got created in the test because of same fixture getting inherited through different paths; will be used during destruction
        int selfContextSize; // size of the selfContext 
        int selfStructSize; // size of the structure which is contained in the selfContext
        int numberOfParents;
        TestSystem::Switch **parentArray;
        TestSystem::Switch *cleanupSwitch;
        TestSystem::Switch *crashSwitch;        
        void *(*creationFunc)();
        void (*initFunc)(void *, void *);
        void (*bodyFunc)(void *);
        void (*cleanupFunc)(void *);
        enum TestFixtureType fixtureType;
        void **arrayOfInitializers;
};

typedef void (*BodyProc)(void *);

PAL_END_EXTERNC

NITS_EXPORT void NITS_CALL NitsSetRegistrationInfo(struct RegistrationInfo *r, 
                                                int selfContextSize, 
                                                int selfStructSize,                                             
                                                int numberOfParents,
                                                TestSystem::Switch **parentArray, 
                                                void *(*creationFunc)(), 
                                                void (*initFunc)(void *, void *), 
                                                void (*bodyFunc)(void *),
                                                void (*cleanupFunc)(void *),
                                                enum TestFixtureType fixtureType, 
                                                void **arrayOfInitializers);
// this will be provided by nits engine to create a fixture or struct
// this function is supposed to either create a new or use an already created(to enforce virtual inheritance) and return back the pointer to it
// in case the isFixture flag is true; it is a fixture and else it is a struct that the fixture consists of
// for now it is multiple inheritance; to be changed to virtual one by having a map of <string of typename, ptr to memory allocated for the type>
NITS_EXPORT void NITS_CALL NitsCreateStruct(TestSystem::Switch &myFixture, void **selfContext, void **selfStruct);

NITS_EXPORT void NITS_CALL NitsDestroyStruct(TestSystem::Switch &myFixture);

NITS_EXPORT void * NITS_CALL NitsGetSelfStruct(TestSystem::Switch &myFixture);

NITS_EXPORT void NITS_CALL NitsBody_NewInterfaceTest(TestSystem::Switch &test);

NITS_EXPORT void NITS_CALL NitsSetup_NewInterfaceTest(TestSystem::Switch &test);

NITS_EXPORT void NITS_CALL NitsCleanup_NewInterfaceTest(TestSystem::Switch &test);

NITS_EXPORT void NITS_CALL NitsRunContinuation(TestSystem::Switch &test);

NITS_EXPORT int NitsIsFixtureSelectedSoFar(TestSystem::Switch &currentSwitch, TestSystem::Switch &searchSwitch);

NITS_EXPORT void NITS_CALL NitsOmit(TestSystem::Switch &currentSwitch);

NITS_EXPORT int NITS_CALL NitsAreWeInOmitMode();

NITS_EXPORT int NITS_CALL NitsIsTestFiltered();

NITS_EXPORT int NITS_CALL NitsIsTestEnabled();

#define NitsNotRunInCurrentTestChoice() ((NitsAreWeInOmitMode()) || (NitsIsTestFiltered()) || (!NitsIsTestEnabled()))

#define NitsNotRunCleanupInCurrentTestChoice() ((NitsIsTestFiltered()) || (!NitsIsTestEnabled()))

NITS_EXPORT void NITS_CALL NitsFaultSimMarkForRerunTillThisFixture(TestSystem::Switch &currentTest); // marks all the test tree upto this point for rerun; currently supported only in test fixtures

#define NitsFaultSimMarkForRerun { NitsFaultSimMarkForRerunTillThisFixture(*currentSwitch); }

// not sure how to define an empty struct in c; compiler does not allow it; even the typedef struct _EmptyStruct EmptyStruct; does not work
struct EmptyStruct
{
        int placeHolder;
};

NITS_EXPORT struct EmptyStruct sEmptyStruct;

#define FALSE 0
#define TRUE 1

#define WideStr(x) W_(x)
#define W_(x) L ## x

#define addQuotes_(input) #input
#define addQuotes(input) addQuotes_(input)

#define stringify(s) PAL_T(addQuotes(s))

#define TypeOfFixture(name) struct context_##name
#define EndCurlyBrace };

#define NitsContext() _NitsContext
#define DeclarationPartOfFixture(name) \
    TypeOfFixture(name) {
#define DeclarePtrFor(type0) \
                 struct type0 *_##type0;
        
#define DeclareCtxPtrFor(type1) \
                struct  context_##type1 *_##type1;
        
#define DeclareContextPtr1(type0, type1) \
                DeclarePtrFor(type0) DeclareCtxPtrFor(type1)

#define DeclareContextPtr2(type0, type1, type2) \
        DeclareContextPtr1(type0, type1) DeclareCtxPtrFor(type2)

#define DeclareContextPtr3(type0, type1, type2, type3) \
        DeclareContextPtr2(type0, type1, type2) DeclareCtxPtrFor(type3)

#define DeclareContextPtr4(type0, type1, type2, type3, type4) \
        DeclareContextPtr3(type0, type1, type2, type3) DeclareCtxPtrFor(type4)

#define DeclareContextPtr5(type0, type1, type2, type3, type4, type5) \
        DeclareContextPtr4(type0, type1, type2, type3, type4) DeclareCtxPtrFor(type5)

#define StructInit(name, type0) \
void *StructInit_##name(struct type0 s)\
{\
        void *pStruct = SystemMalloc(sizeof(struct type0));\
        memcpy(pStruct, &s, sizeof(struct type0));\
        return pStruct;\
}

#define FwdDeclareFixtureFunctions(name, type0) \
NITS_EXTERN_C void *Create_##name();\
NITS_EXTERN_C void Init_##name(void *context, void *initValues);\
NITS_EXTERN_C void name(TypeOfFixture(name) *_NitsContext);\
NITS_EXTERN_C void CleanupFunc_##name(void *context);\
NITS_EXTERN_C void *StructInit_##name(struct type0 s);

#if defined(USE_ALLOCATOR) && defined(__cplusplus)
class AllocChecker
{
public:
    AllocChecker(int check, const char* file, size_t line, const char* func) :
        m_check(check), m_file(file), m_line(line), m_func(func)
    {
        m_blocks = PAL_GetBlocksAllocated();
    }

    ~AllocChecker()
    {
        if (m_check)
            PAL_CheckBlocksAllocated(m_blocks, m_file, m_line, m_func);
    }

private:
    int m_check;
    size_t m_blocks;
    const char* m_file;
    size_t m_line;
    const char* m_func;
};
#endif /* defined(USE_ALLOCATOR) && defined(__cplusplus) */

/* Macros that check for memory leaks (before/after each test) */
#if defined(USE_ALLOCATOR) && defined(__cplusplus)
# define DefineAllocChecker(fixtureType) \
    AllocChecker _ac_(strcmp(#fixtureType, "BodyFixture") == 0, __FILE__, __LINE__, __FUNCTION__)
#else
# define DefineAllocChecker(fixtureType) /* empty */
#endif

#define DeclareFixtureBody(name, type0, fixtureType) \
        void name(TypeOfFixture(name) *_NitsContext) { DefineAllocChecker(fixtureType); TestSystem::Switch *currentSwitch = &fixture_##name; if(NitsIsSplitFixture(&(fixture_##name))) {_NitsContext->_##type0 = ((struct type0 *) (NitsGetSelfStruct(fixture_##name)));} if (NitsNotRunInCurrentTestChoice()) NitsReturn;

#define InitYourself(name, type0)\
if(!AmISplitFixture(name)) \
{\
TypeOfFixture(name) *typedContext = (TypeOfFixture(name) *) (context);\
if(initValues != 0)\
{\
        memcpy(typedContext->_##type0, initValues, sizeof(struct type0));\
}\
}

#define MyInitArray(name) (fixture_##name.GetInitArray())

#define DeclareTypedContext(name)\
        TypeOfFixture(name) *typedContext = (TypeOfFixture(name) *)(context);

#define NitsEndFixture \
        NitsReturn; }

#define NitsDeclFixture0(name, type0)\
    DeclarationPartOfFixture(name) \
    DeclarePtrFor(type0) \
    EndCurlyBrace \
    FwdDeclareFixtureFunctions(name, type0)

#define NitsDefFixture0(name, type0, fixtureType)\
StructInit(name, type0)\
void *NITS_CALL Register_##name()\
{\
        struct RegistrationInfo *r = (struct RegistrationInfo *)(SystemMalloc(sizeof(struct RegistrationInfo)));\
        NitsSetRegistrationInfo(r, sizeof(TypeOfFixture(name)), sizeof(struct type0), 0, 0, Create_##name, Init_##name,((BodyProc)(name)), CleanupFunc_##name, fixtureType, 0);\
        return r;\
}\
void *Create_##name()\
{\
        TypeOfFixture(name) *context;\
        void *p_##type0;\
        NitsCreateStruct(fixture_##name, (void **)&context, &p_##type0);\
        context->_##type0 = (struct type0 *)(p_##type0);\
        return context;\
}\
void Init_##name(void *context, void *initValues)\
{\
        InitYourself(name, type0)\
}\
void CleanupFunc_##name(void *context)\
{\
    ((void)context); \
        NitsDestroyStruct(fixture_##name);\
}\
DeclareFixtureBody(name, type0, fixtureType)

#define NitsDeclFixture1(name, type0, type1)\
    DeclarationPartOfFixture(name)\
    DeclareContextPtr1(type0, type1)\
    EndCurlyBrace \
    FwdDeclareFixtureFunctions(name, type0)

#define NitsDefFixture1(name, type0, type1, initType1, fixtureType) \
StructInit(name, type0)\
void *Create_##name()\
{\
        TypeOfFixture(type1) *p_##type1 = (TypeOfFixture(type1) *)(Create_##type1());\
        void *p_##type0;\
        TypeOfFixture(name) *context;\
        NitsCreateStruct(fixture_##name, (void **)&context, &p_##type0);\
        context->_##type0 = (struct type0 *)(p_##type0);\
        context->_##type1 = p_##type1;\
        return context;\
}\
void Init_##name(void *context, void *initValues)\
{\
        Init_##type1(((struct context_##name *)(context))->_##type1, MyInitArray(name)[0]);\
        InitYourself(name, type0)\
}\
void *NITS_CALL Register_##name()\
{\
        struct RegistrationInfo *r = (struct RegistrationInfo *)(SystemMalloc(sizeof(struct RegistrationInfo)));\
        void **initArray = (void **)SystemMalloc(sizeof(void *));\
    if (initArray == 0) return 0; \
        TestSystem::Switch **parentArray = (TestSystem::Switch **) SystemMalloc(sizeof(TestSystem::Switch *));\
    if (parentArray == 0) return 0; \
        NitsSetRegistrationInfo(r, sizeof(TypeOfFixture(name)), sizeof(struct type0), 1, parentArray, Create_##name, Init_##name,((BodyProc)(name)), CleanupFunc_##name, fixtureType, initArray);\
        initArray[0] = StructInit_##type1(initType1);\
        parentArray[0] = &(fixture_##type1);\
        return r;\
}\
void CleanupFunc_##name(void *context)\
{\
        DeclareTypedContext(name)\
        CleanupFunc_##type1(typedContext->_##type1);\
        NitsDestroyStruct(fixture_##name);\
}\
DeclareFixtureBody(name, type0, fixtureType)

#define AmISplitFixture(name) (NitsIsSplitFixture(&(fixture_##name)))

#define NitsDeclFixture2(name, type0, type1, type2) \
    DeclarationPartOfFixture(name)\
    DeclareContextPtr2(type0, type1, type2)\
    EndCurlyBrace \
    FwdDeclareFixtureFunctions(name, type0)

#define NitsDefFixture2(name, type0, type1, initType1, type2, initType2, fixtureType) \
StructInit(name, type0)\
void *Create_##name()\
{\
        TypeOfFixture(type1) *p_##type1 = (TypeOfFixture(type1) *)(Create_##type1());\
        TypeOfFixture(type2) *p_##type2 = (TypeOfFixture(type2) *)(Create_##type2());\
        void *p_##type0;\
        TypeOfFixture(name) *context;\
        NitsCreateStruct(fixture_##name, (void **)&context, &p_##type0);\
        context->_##type0 = (struct type0 *)(p_##type0);\
        context->_##type1 = p_##type1;\
        context->_##type2 = p_##type2;\
        return context;\
}\
void Init_##name(void *context, void *initValues)\
{\
        Init_##type1(((struct context_##name *)(context))->_##type1, AmISplitFixture(name) ? initValues : MyInitArray(name)[0]);\
        Init_##type2(((struct context_##name *)(context))->_##type2, AmISplitFixture(name) ? initValues : MyInitArray(name)[1]);\
        InitYourself(name, type0)\
}\
void *NITS_CALL Register_##name()\
{\
        struct RegistrationInfo *r = (struct RegistrationInfo *)(SystemMalloc(sizeof(struct RegistrationInfo)));\
        void **initArray = (void **)SystemMalloc(2*sizeof(void *));\
    if (initArray == 0) return 0; \
        TestSystem::Switch **parentArray = (TestSystem::Switch **) SystemMalloc(2*sizeof(TestSystem::Switch *));\
    if (parentArray == 0) return 0; \
        NitsSetRegistrationInfo(r, sizeof(TypeOfFixture(name)), sizeof(struct type0), 2, parentArray, Create_##name, Init_##name,((BodyProc)(name)), CleanupFunc_##name, fixtureType, initArray);\
        initArray[0] = StructInit_##type1(initType1);\
        initArray[1] = StructInit_##type2(initType2);\
        parentArray[0] = &(fixture_##type1);\
        parentArray[1] = &(fixture_##type2);\
        return r;\
}\
void CleanupFunc_##name(void *context)\
{\
        DeclareTypedContext(name)\
        CleanupFunc_##type2(typedContext->_##type2);\
        CleanupFunc_##type1(typedContext->_##type1);\
        NitsDestroyStruct(fixture_##name);\
}\
DeclareFixtureBody(name, type0, fixtureType)

#define NitsDeclFixture3(name, type0, type1, type2, type3) \
    DeclarationPartOfFixture(name)\
    DeclareContextPtr3(type0, type1, type2, type3)\
    EndCurlyBrace \
    FwdDeclareFixtureFunctions(name, type0)

#define NitsDefFixture3(name, type0, type1, initType1, type2, initType2, type3, initType3, fixtureType) \
StructInit(name, type0)\
void *Create_##name()\
{\
        TypeOfFixture(type1) *p_##type1 = (TypeOfFixture(type1) *)(Create_##type1());\
        TypeOfFixture(type2) *p_##type2 = (TypeOfFixture(type2) *)(Create_##type2());\
        TypeOfFixture(type3) *p_##type3 = (TypeOfFixture(type3) *)(Create_##type3());\
        void *p_##type0;\
        TypeOfFixture(name) *context;\
        NitsCreateStruct(fixture_##name, (void **)&context, &p_##type0);\
        context->_##type0 = (struct type0 *)(p_##type0);\
        context->_##type1 = p_##type1;\
        context->_##type2 = p_##type2;\
        context->_##type3 = p_##type3;\
        return context;\
}\
void Init_##name(void *context, void *initValues)\
{\
        Init_##type1(((struct context_##name *)(context))->_##type1, AmISplitFixture(name) ? initValues : MyInitArray(name)[0]);\
        Init_##type2(((struct context_##name *)(context))->_##type2, AmISplitFixture(name) ? initValues : MyInitArray(name)[1]);\
        Init_##type3(((struct context_##name *)(context))->_##type3, AmISplitFixture(name) ? initValues : MyInitArray(name)[2]);\
        InitYourself(name, type0)\
}\
void *NITS_CALL Register_##name()\
{\
        struct RegistrationInfo *r = (struct RegistrationInfo *)(SystemMalloc(sizeof(struct RegistrationInfo)));\
        void **initArray = (void **)SystemMalloc(3*sizeof(void *));\
    if (initArray == 0) return 0; \
        TestSystem::Switch **parentArray = (TestSystem::Switch **) SystemMalloc(3*sizeof(TestSystem::Switch *));\
    if (parentArray == 0) return 0; \
        NitsSetRegistrationInfo(r, sizeof(TypeOfFixture(name)), sizeof(struct type0), 3, parentArray, Create_##name, Init_##name,((BodyProc)(name)), CleanupFunc_##name, fixtureType, initArray);\
        initArray[0] = StructInit_##type1(initType1);\
        initArray[1] = StructInit_##type2(initType2);\
        initArray[2] = StructInit_##type3(initType3);\
        parentArray[0] = &(fixture_##type1);\
        parentArray[1] = &(fixture_##type2);\
        parentArray[2] = &(fixture_##type3);\
        return r;\
}\
void CleanupFunc_##name(void *context)\
{\
        DeclareTypedContext(name)\
        CleanupFunc_##type3(typedContext->_##type3);\
        CleanupFunc_##type2(typedContext->_##type2);\
        CleanupFunc_##type1(typedContext->_##type1);\
        NitsDestroyStruct(fixture_##name);\
}\
DeclareFixtureBody(name, type0, fixtureType)

#define NitsDeclFixture4(name, type0, type1, type2, type3, type4) \
DeclarationPartOfFixture(name)\
DeclareContextPtr4(type0, type1, type2, type3, type4)\
EndCurlyBrace \
FwdDeclareFixtureFunctions(name, type0)

#define NitsDefFixture4(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4, fixtureType) \
StructInit(name, type0)\
void *Create_##name()\
{\
        TypeOfFixture(type1) *p_##type1 = (TypeOfFixture(type1) *)(Create_##type1());\
        TypeOfFixture(type2) *p_##type2 = (TypeOfFixture(type2) *)(Create_##type2());\
        TypeOfFixture(type3) *p_##type3 = (TypeOfFixture(type3) *)(Create_##type3());\
        TypeOfFixture(type4) *p_##type4 = (TypeOfFixture(type4) *)(Create_##type4());\
        void *p_##type0;\
        TypeOfFixture(name) *context;\
        NitsCreateStruct(fixture_##name, (void **)&context, &p_##type0);\
        context->_##type0 = (struct type0 *)(p_##type0);\
        context->_##type1 = p_##type1;\
        context->_##type2 = p_##type2;\
        context->_##type3 = p_##type3;\
        context->_##type4 = p_##type4;\
        return context;\
}\
void Init_##name(void *context, void *initValues)\
{\
        Init_##type1(((struct context_##name *)(context))->_##type1, AmISplitFixture(name) ? initValues : MyInitArray(name)[0]);\
        Init_##type2(((struct context_##name *)(context))->_##type2, AmISplitFixture(name) ? initValues : MyInitArray(name)[1]);\
        Init_##type3(((struct context_##name *)(context))->_##type3, AmISplitFixture(name) ? initValues : MyInitArray(name)[2]);\
        Init_##type4(((struct context_##name *)(context))->_##type4, AmISplitFixture(name) ? initValues : MyInitArray(name)[3]);\
        InitYourself(name, type0)\
}\
void *NITS_CALL Register_##name()\
{\
        struct RegistrationInfo *r = (struct RegistrationInfo *)(SystemMalloc(sizeof(struct RegistrationInfo)));\
        void **initArray = (void **)SystemMalloc(4*sizeof(void *));\
    if (initArray == 0) return 0; \
    TestSystem::Switch **parentArray = (TestSystem::Switch **) SystemMalloc(4*sizeof(TestSystem::Switch *));\
    if (parentArray == 0) return 0; \
        NitsSetRegistrationInfo(r, sizeof(TypeOfFixture(name)), sizeof(struct type0), 4, parentArray, Create_##name, Init_##name,((BodyProc)(name)), CleanupFunc_##name, fixtureType, initArray);\
        initArray[0] = StructInit_##type1(initType1);\
        initArray[1] = StructInit_##type2(initType2);\
        initArray[2] = StructInit_##type3(initType3);\
        initArray[3] = StructInit_##type4(initType4);\
        parentArray[0] = &(fixture_##type1);\
        parentArray[1] = &(fixture_##type2);\
        parentArray[2] = &(fixture_##type3);\
        parentArray[3] = &(fixture_##type4);\
        return r;\
}\
void CleanupFunc_##name(void *context)\
{\
        DeclareTypedContext(name)\
        CleanupFunc_##type4(typedContext->_##type4);\
        CleanupFunc_##type3(typedContext->_##type3);\
        CleanupFunc_##type2(typedContext->_##type2);\
        CleanupFunc_##type1(typedContext->_##type1);\
        NitsDestroyStruct(fixture_##name);\
}\
DeclareFixtureBody(name, type0, fixtureType)

#define NitsDeclFixture5(name, type0, type1, type2, type3, type4, type5) \
    DeclarationPartOfFixture(name)\
    DeclareContextPtr5(type0, type1, type2, type3, type4, type5)\
    EndCurlyBrace \
    FwdDeclareFixtureFunctions(name, type0)

#define NitsDefFixture5(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4, type5, initType5, fixtureType) \
StructInit(name, type0)\
void *Create_##name()\
{\
        TypeOfFixture(type1) *p_##type1 = (TypeOfFixture(type1) *)(Create_##type1());\
        TypeOfFixture(type2) *p_##type2 = (TypeOfFixture(type2) *)(Create_##type2());\
        TypeOfFixture(type3) *p_##type3 = (TypeOfFixture(type3) *)(Create_##type3());\
        TypeOfFixture(type4) *p_##type4 = (TypeOfFixture(type4) *)(Create_##type4());\
        TypeOfFixture(type5) *p_##type5 = (TypeOfFixture(type5) *)(Create_##type5());\
        void *p_##type0;\
        TypeOfFixture(name) *context;\
        NitsCreateStruct(fixture_##name, (void **)&context, &p_##type0);\
        context->_##type0 = (struct type0 *)(p_##type0);\
        context->_##type1 = p_##type1;\
        context->_##type2 = p_##type2;\
        context->_##type3 = p_##type3;\
        context->_##type4 = p_##type4;\
        context->_##type5 = p_##type5;\
        return context;\
}\
void Init_##name(void *context, void *initValues)\
{\
        Init_##type1(((struct context_##name *)(context))->_##type1, AmISplitFixture(name) ? initValues : MyInitArray(name)[0]);\
        Init_##type2(((struct context_##name *)(context))->_##type2, AmISplitFixture(name) ? initValues : MyInitArray(name)[1]);\
        Init_##type3(((struct context_##name *)(context))->_##type3, AmISplitFixture(name) ? initValues : MyInitArray(name)[2]);\
        Init_##type4(((struct context_##name *)(context))->_##type4, AmISplitFixture(name) ? initValues : MyInitArray(name)[3]);\
        Init_##type5(((struct context_##name *)(context))->_##type5, AmISplitFixture(name) ? initValues : MyInitArray(name)[4]);\
        InitYourself(name, type0)\
}\
void *NITS_CALL Register_##name()\
{\
        struct RegistrationInfo *r = (struct RegistrationInfo *)(SystemMalloc(sizeof(struct RegistrationInfo)));\
        void **initArray = (void **)SystemMalloc(5*sizeof(void *));\
    if (initArray == 0) return 0; \
        TestSystem::Switch **parentArray = (TestSystem::Switch **) SystemMalloc(5*sizeof(TestSystem::Switch *));\
    if (parentArray == 0) return 0; \
        NitsSetRegistrationInfo(r, sizeof(TypeOfFixture(name)), sizeof(struct type0), 5, parentArray, Create_##name, Init_##name,((BodyProc)(name)), CleanupFunc_##name, fixtureType, initArray);\
        initArray[0] = StructInit_##type1(initType1);\
        initArray[1] = StructInit_##type2(initType2);\
        initArray[2] = StructInit_##type3(initType3);\
        initArray[3] = StructInit_##type4(initType4);\
        initArray[4] = StructInit_##type5(initType5);\
        parentArray[0] = &(fixture_##type1);\
        parentArray[1] = &(fixture_##type2);\
        parentArray[2] = &(fixture_##type3);\
        parentArray[3] = &(fixture_##type4);\
        parentArray[4] = &(fixture_##type5);\
        return r;\
}\
void CleanupFunc_##name(void *context)\
{\
        DeclareTypedContext(name)\
        CleanupFunc_##type5(typedContext->_##type5);\
        CleanupFunc_##type4(typedContext->_##type4);\
        CleanupFunc_##type3(typedContext->_##type3);\
        CleanupFunc_##type2(typedContext->_##type2);\
        CleanupFunc_##type1(typedContext->_##type1);\
        NitsDestroyStruct(fixture_##name);\
}\
DeclareFixtureBody(name, type0, fixtureType)

// due to some reason it is not letting me pass the Cleanup/Crash as strings and use them in generating the function names
// TODO: fix this in future and only have one macro e.g. NitsFixtureTeardown
#define NitsFixtureCleanup(name)\
void *NITS_CALL Register_Cleanup_##name();\
TestSystem::Switch fixture_cleanup_##name(stringify(name), NitsSetup_NewInterfaceTest, Register_Cleanup_##name, NitsCleanup_NewInterfaceTest);\
void Cleanup_##name(TypeOfFixture(name) *_NitsContext);\
void *NITS_CALL Register_Cleanup_##name()\
{\
        struct RegistrationInfo *r = (struct RegistrationInfo *)(SystemMalloc(sizeof(struct RegistrationInfo)));\
        NitsSetRegistrationInfo(r, 0, 0, 0, 0, 0, 0,((BodyProc)(Cleanup_##name)), 0, CleanupFixture, 0);\
        fixture_##name.SetTeardownSwitch(&(fixture_cleanup_##name), 1);\
        return r;\
}\
void Cleanup_##name(TypeOfFixture(name) *_NitsContext) { TestSystem::Switch *currentSwitch = &fixture_cleanup_##name; if(NitsNotRunCleanupInCurrentTestChoice()) NitsReturn;
        
#define NitsFixtureCrash(name)\
void *NITS_CALL Register_Crash_##name();\
TestSystem::Switch fixture_crash_##name(stringify(name), NitsSetup_NewInterfaceTest, Register_Crash_##name, NitsCleanup_NewInterfaceTest);\
void Crash_##name(TypeOfFixture(name) *_NitsContext);\
void *NITS_CALL Register_Crash_##name()\
{\
        struct RegistrationInfo *r = (struct RegistrationInfo *)(SystemMalloc(sizeof(struct RegistrationInfo)));\
        NitsSetRegistrationInfo(r, 0, 0, 0, 0, 0, 0,((BodyProc)(Crash_##name)), 0, CrashFixture, 0);\
        fixture_##name.SetTeardownSwitch(&(fixture_crash_##name), 0);\
        return r;\
}\
void Crash_##name(TypeOfFixture(name) *_NitsContext) { TestSystem::Switch *currentSwitch = &fixture_crash_##name; if(NitsNotRunCleanupInCurrentTestChoice()) NitsReturn;

#define CommonPartOfBodyFixture(name)\
        void *NITS_CALL Register_##name();\
        TestSystem::Test fixture_##name(stringify(name), NitsSetup_NewInterfaceTest, NitsBody_NewInterfaceTest, Register_##name, NitsCleanup_NewInterfaceTest);

#define CommonPartOfSetupFixture(name, type0)\
        void *NITS_CALL Register_##name();\
        CommonPartOfSetupFixtureDef(name, type0)

#define CommonPartOfSetupFixtureDecl(name, type0)\
    void *NITS_CALL Register_##name();\
    NITS_EXTERN_C struct type0 name##Defaults;\
    NITS_EXTERN_C TestSystem::Switch fixture_##name;

#define CommonPartOfSetupFixtureDef(name, type0)\
    struct type0 name##Defaults = {0};\
    TestSystem::Switch fixture_##name(stringify(name), NitsSetup_NewInterfaceTest, Register_##name, NitsCleanup_NewInterfaceTest);

#define NitsFixture0(name, type0, fixtureType) \
        NitsDeclFixture0(name, type0)\
        NitsDefFixture0(name, type0, fixtureType)

#define NitsFixture1(name, type0, type1, initType1, fixtureType) \
        NitsDeclFixture1(name, type0, type1)\
        NitsDefFixture1(name, type0, type1, initType1, fixtureType)

#define NitsFixture2(name, type0, type1, initType1, type2, initType2, fixtureType) \
    NitsDeclFixture2(name, type0, type1, type2) \
    NitsDefFixture2(name, type0, type1, initType1, type2, initType2, fixtureType)

#define NitsFixture3(name, type0, type1, initType1, type2, initType2, type3, initType3, fixtureType) \
    NitsDeclFixture3(name, type0, type1, type2, type3) \
    NitsDefFixture3(name, type0, type1, initType1, type2, initType2, type3, initType3, fixtureType)

#define NitsFixture4(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4, fixtureType) \
    NitsDeclFixture4(name, type0, type1, type2, type3, type4) \
    NitsDefFixture4(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4, fixtureType)

#define NitsFixture5(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4, type5, initType5, fixtureType) \
    NitsDeclFixture5(name, type0, type1, type2, type3, type4, type5) \
    NitsDefFixture5(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4, type5, initType5, fixtureType)

/****************************************************************
* NITS NEW INTERFACE 
* Purpose is to make easier composing tests from fixtures by providing easy way to inherit from multiple fixtures
* Also includes the simple interface where you do not need to compose out of other fixtures
***************************************************************/

#define NitsEmptyStruct EmptyStruct
#define NitsEmptyValue sEmptyStruct

#define NitsEndSetup NitsEndFixture

#define NitsEndSplit NitsEndFixture

#define NitsEndTest NitsEndFixture

#define NitsEndCleanup NitsEndFixture

#define NitsEndCrash NitsEndFixture

#define NitsEndModuleSetup NitsEndFixture

#define NitsReturn \
    { NitsRunContinuation(*currentSwitch); return; }

#define NitsDeclSetup0(name, type0) \
        CommonPartOfSetupFixtureDecl(name, type0) \
        NitsDeclFixture0(name, type0)

#define NitsDefSetup0(name, type0) \
    CommonPartOfSetupFixtureDef(name, type0) \
    NitsDefFixture0(name, type0, SetupFixture)

#define NitsSetup0(name, type0) \
    NitsDeclSetup0(name, type0) \
    NitsDefSetup0(name, type0)

#define NitsDeclSetup1(name, type0, type1) \
        CommonPartOfSetupFixtureDecl(name, type0)\
        NitsDeclFixture1(name, type0, type1)

#define NitsDefSetup1(name, type0, type1, initType1) \
        CommonPartOfSetupFixtureDef(name, type0)\
        NitsDefFixture1(name, type0, type1, initType1, SetupFixture)

#define NitsSetup1(name, type0, type1, initType1) \
    NitsDeclSetup1(name, type0, type1) \
    NitsDefSetup1(name, type0, type1, initType1)

#define NitsDeclSetup2(name, type0, type1, type2) \
        CommonPartOfSetupFixtureDecl(name, type0)\
        NitsDeclFixture2(name, type0, type1, type2)

#define NitsDefSetup2(name, type0, type1, initType1, type2, initType2) \
        CommonPartOfSetupFixtureDef(name, type0)\
        NitsDefFixture2(name, type0, type1, initType1, type2, initType2, SetupFixture)

#define NitsSetup2(name, type0, type1, initType1, type2, initType2) \
        NitsDeclSetup2(name, type0, type1, type2) \
        NitsDefSetup2(name, type0, type1, initType1, type2, initType2)

#define NitsDeclSetup3(name, type0, type1, type2, type3) \
        CommonPartOfSetupFixtureDecl(name, type0)\
        NitsDeclFixture3(name, type0, type1, type2, type3)

#define NitsDefSetup3(name, type0, type1, initType1, type2, initType2, type3, initType3) \
        CommonPartOfSetupFixtureDef(name, type0)\
        NitsDefFixture3(name, type0, type1, initType1, type2, initType2, type3, initType3, SetupFixture)

#define NitsSetup3(name, type0, type1, initType1, type2, initType2, type3, initType3) \
        NitsDeclSetup3(name, type0, type1, type2, type3) \
        NitsDefSetup3(name, type0, type1, initType1, type2, initType2, type3, initType3)

#define NitsDeclSetup4(name, type0, type1, type2, type3, type4) \
        CommonPartOfSetupFixtureDecl(name, type0)\
        NitsDeclFixture4(name, type0, type1, type2, type3, type4)

#define NitsDefSetup4(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4) \
        CommonPartOfSetupFixtureDef(name, type0)\
        NitsDefFixture4(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4, SetupFixture)

#define NitsSetup4(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4) \
        NitsDeclSetup4(name, type0, type1, type2, type3, type4) \
        NitsDefSetup4(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4)

#define NitsDeclSetup5(name, type0, type1, type2, type3, type4, type5) \
        CommonPartOfSetupFixtureDecl(name, type0)\
        NitsDeclFixture5(name, type0, type1, type2, type3, type4, type5)

#define NitsDefSetup5(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4, type5, initType5) \
        CommonPartOfSetupFixtureDef(name, type0)\
        NitsDefFixture5(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4, type5, initType5, SetupFixture)

#define NitsSetup5(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4, type5, initType5) \
        NitsDeclSetup5(name, type0, type1, type2, type3, type4, type5) \
        NitsDefSetup5(name, type0, type1, initType1, type2, initType2, type3, initType3, type4, initType4, type5, initType5)

#define NitsDeclSplit2(name, type0, type1, type2) \
        CommonPartOfSetupFixtureDecl(name, type0)\
        NitsDeclFixture2(name, type0, type1, type2)

#define NitsDefSplit2(name, type0, type1, type2) \
        CommonPartOfSetupFixtureDef(name, type0)\
        NitsDefFixture2(name, type0, type1, type1##Defaults, type2, type2##Defaults, SplitFixture)

#define NitsSplit2(name, type0, type1, type2) \
        NitsDeclSplit2(name, type0, type1, type2) \
        NitsDefSplit2(name, type0, type1, type2)

#define NitsDeclSplit3(name, type0, type1, type2, type3) \
        CommonPartOfSetupFixtureDecl(name, type0)\
        NitsDeclFixture3(name, type0, type1, type2, type3)

#define NitsDefSplit3(name, type0, type1, type2, type3) \
        CommonPartOfSetupFixtureDef(name, type0)\
        NitsDefFixture3(name, type0, type1, NitsEmptyValue, type2, NitsEmptyValue, type3, NitsEmptyValue, SplitFixture)

#define NitsSplit3(name, type0, type1, type2, type3) \
        NitsDeclSplit3(name, type0, type1, type2, type3) \
        NitsDefSplit3(name, type0, type1, type2, type3)

#define NitsDeclSplit4(name, type0, type1, type2, type3, type4) \
        CommonPartOfSetupFixtureDecl(name, type0)\
        NitsDeclFixture4(name, type0, type1, type2, type3, type4)       

#define NitsDefSplit4(name, type0, type1, type2, type3, type4) \
        CommonPartOfSetupFixtureDef(name, type0)\
        NitsDefFixture4(name, type0, type1, NitsEmptyValue, type2, NitsEmptyValue, type3, NitsEmptyValue, type4, NitsEmptyValue, SplitFixture)  

#define NitsSplit4(name, type0, type1, type2, type3, type4) \
        NitsDeclSplit4(name, type0, type1, type2, type3, type4)\
        NitsDefSplit4(name, type0, type1, type2, type3, type4)

#define NitsDeclSplit5(name, type0, type1, type2, type3, type4, type5) \
        CommonPartOfSetupFixtureDecl(name, type0)\
        NitsDeclFixture5(name, type0, type1, type2, type3, type4, type5)

#define NitsDefSplit5(name, type0, type1, type2, type3, type4, type5) \
        CommonPartOfSetupFixtureDef(name, type0)\
        NitsDefFixture5(name, type0, type1, NitsEmptyValue, type2, NitsEmptyValue, type3, NitsEmptyValue, type4, NitsEmptyValue, type5, NitsEmptyValue, SplitFixture)

#define NitsSplit5(name, type0, type1, type2, type3, type4, type5) \
        NitsDeclSplit5(name, type0, type1, type2, type3, type4, type5) \
        NitsDefSplit5(name, type0, type1, type2, type3, type4, type5)

#define NitsTest0(name) \
        CommonPartOfBodyFixture(name)\
        NitsFixture0(name, EmptyStruct, BodyFixture)

#define NitsTest1(name, type1, initType1) \
        CommonPartOfBodyFixture(name)\
        NitsFixture1(name, EmptyStruct, type1, initType1, BodyFixture)

#define NitsTest2(name, type1, initType1, type2, initType2) \
        CommonPartOfBodyFixture(name)\
        NitsFixture2(name, EmptyStruct, type1, initType1, type2, initType2, BodyFixture)

#define NitsTest3(name, type1, initType1, type2, initType2, type3, initType3) \
        CommonPartOfBodyFixture(name)\
        NitsFixture3(name, EmptyStruct, type1, initType1, type2, initType2, type3, initType3, BodyFixture)

#define NitsTest4(name, type1, initType1, type2, initType2, type3, initType3, type4, initType4) \
        CommonPartOfBodyFixture(name)\
        NitsFixture4(name, EmptyStruct, type1, initType1, type2, initType2, type3, initType3, type4, initType4, BodyFixture)

#define NitsTest5(name, type1, initType1, type2, initType2, type3, initType3, type4, initType4, type5, initType5) \
        CommonPartOfBodyFixture(name)\
        NitsFixture5(name, EmptyStruct, type1, initType1, type2, initType2, type3, initType3, type4, initType4, type5, initType5, BodyFixture)

#define NitsDeclSetup(name) \
        NitsDeclSetup0(name, EmptyStruct)

#define NitsDefSetup(name)\
        NitsDefSetup0(name, EmptyStruct)

#define NitsSetup(name) \
        NitsSetup0(name, NitsEmptyStruct)

#define NitsTest(name) \
        NitsTest0(name)

#define NitsTestWithSetup(name, setup) \
        NitsTest1(name, setup, NitsEmptyValue)

#define NitsTestWithInitializableSetup(name, setup, setupInit) \
        NitsTest1(name, setup, setupInit)

/*
* NitsModuleSetup lets you define test code which will be run only once per test module at the beginning of the module test run
* There can be multiple ModuleSetups in a test library and order in which they run is compiler specific
* You can define NitsCleanup with same name for each NitsModuleSetup and it will be run at the end of the module run
* In case of -isolate switch usage, each child process running unittest runs this NitsModuleSetup and any NitsCleanup defined on it once
*/
#define NitsModuleSetup(name) \
    CommonPartOfBodyFixture(name) \
    NitsFixture0(name, EmptyStruct, ModuleSetupFixture)

#define NitsCleanup(name) \
        NitsFixtureCleanup(name)

#define NitsCrash(name) \
        NitsFixtureCrash(name)

#define NitsIsFixtureSelected(child) (NitsIsFixtureSelectedSoFar(*currentSwitch, fixture_##child))

#define NitsOmitAndReturn { NitsOmit(*currentSwitch); NitsReturn; }

#define NitsEnableFaultSim currentSwitch->SetFaultMode(TestSystem::Automatic)
#define NitsDisableFaultSim currentSwitch->SetFaultMode(TestSystem::Manual)

#define NitsSetFaultMode(mode) NitsSwitchSetFaultMode(currentSwitch, mode)

#define NitsSetEnabled(enabled) NitsSwitchSetEnabled(currentSwitch, enabled)

#define NitsSetFlaky(enabled) NitsSwitchSetFlaky(currentSwitch, enabled)

#define NitsFaultExclude(sites, count) NitsSwitchFaultExclude(currentSwitch, sites, count)

#define NitsFaultOff NitsSwitchFaultOff(currentSwitch)

#define NitsFaultHResultError(site, error) NitsSwitchFaultHresult(currentSwitch, site, error)

#define NitsFaultHResultErrorOnAttempt(site, error, attempt) NitsSwitchFaultHresult(currentSwitch, site, error, attempt)

#define NitsFaultError(site, error) NitsSwitchFaultError(currentSwitch, site, error)

#define NitsFaultErrorOnAttempt(site, error, attempt) NitsSwitchFaultError(currentSwitch, site, error, attempt)

#define NitsFaultWait(site, event) NitsSwitchFaultWait(currentSwitch, site, event)

#define NitsFaultWaitOnAttempt(site, event, attempt) NitsSwitchFaultWait(currentSwitch, site, event, attempt)


// TODO:Get the following syntax to work
// plan is to use the current fixture syntax and define a function with three labels for setup/body/cleanup and 
// have all the setup/body/cleanup fixtures call into that function which will go to a specific label depending on
// who is calling it
/*
NitsTestGroup(foo)
  NitsTestGroupSetup
        //setup
  NitsEndSetup
  NitsTestGroupBody
        //body
  NitsEndBody
  NitsTestGroupCleanup
        //cleanup
  NitsEndCleanup
NitsEndTestGroup

*/
#endif //undef NITS_STUB_ONLY

#endif /* __cplusplus */
#endif /* __NITS_H__ */
