/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#define HOOK_BUILD

#include <stdio.h>
#include <stdlib.h>
#include <nits/base/nits.h>
#include <pal/sem.h>
#include <pal/atomic.h>
#include <pal/strings.h>
#include <pal/process.h>
#include <pal/thread.h>
#include <pal/shlib.h>
#include <pal/file.h>

#if defined(ENABLE_UNITTESTING)

void SignalInjector()
{
    PAL_Char nameSignal[128] = PAL_T(CONFIG_SEMNAMELOCALPREFIX) PAL_T("NitsInjectorIn_");
    PAL_Char nameWait[128] = PAL_T(CONFIG_SEMNAMELOCALPREFIX) PAL_T("NitsInjectorOut_");
    PAL_Char nameLock[128] = PAL_T(CONFIG_SEMNAMELOCALPREFIX) PAL_T("NitsInjectorLock_");
    NamedSem semaphore;
    NamedSem lockSemaphore;    
    PAL_Char conversionBuf[64] = PAL_T("");
    const PAL_Char *convertedStr = NULL;
    size_t convertedSize = 0;
    // int waitSemValue = 0;
    int waitMilliSeconds = 100;    
    int waitForLockMilliSeconds = 500;
    waitForLockMilliSeconds = 1000;

    TcsFromUInt64(conversionBuf, Process_ID(), &convertedStr, &convertedSize);
    Tcscat(nameSignal, 128, convertedStr);
    Tcscat(nameWait, 128, convertedStr);
    Tcscat(nameLock, 128, convertedStr);

    if(NamedSem_Open_Injected(&lockSemaphore, SEM_USER_ACCESS_ALLOW_ALL, 0, nameLock, 0, NitsReservedCallSite()) != 0)
    {
        //printf("\nlock semaphore can not be opened\n");
        /* The injector isn't there. */
        return;
    }

    if(NamedSem_TimedWait(&lockSemaphore, waitForLockMilliSeconds) != 0)
    {
    	// could not acquire lock to the injector; some further shouldFault call will attempt to
        NamedSem_Close(&lockSemaphore);
    	return;
    }

    //printf("\nopening signal semaphore\n");
    if(NamedSem_Open_Injected(&semaphore, SEM_USER_ACCESS_ALLOW_ALL, 0, nameSignal, 0, NitsReservedCallSite()) != 0)
    {
    	//printf("\nsignal semaphore can not be opened\n");
        /* The injector isn't there. */
        goto End;
    }

    NamedSem_Post(&semaphore, 1);
    NamedSem_Close(&semaphore);

    //printf("\n opening wait semaphore\n");
    if(NamedSem_Open_Injected(&semaphore, SEM_USER_ACCESS_ALLOW_ALL, 0, nameWait, 0, NitsReservedCallSite()) != 0)
    {
    	//printf("\nwait semaphore can not be opened\n");
        /* The injector isn't there. */
        goto End;
    }

    /* Use a short timeout to prevent undesired behavior. In the worst
     * case, the injector thread will be starved and the patching will
     * happen later. */

    // NamedSem_GetValue(&semaphore, &waitSemValue);
    // printf("\nWait semaphore value was %d\n", waitSemValue);
    // for non-windows the wait required is greater; this looks like a problem with the timedwait of namedsem; 
    // TODO: look at why greater wait is required
    waitMilliSeconds = 1000;
    NamedSem_TimedWait(&semaphore, waitMilliSeconds);

    //printf("\ncame out of wait for the semaphore\n");
    NamedSem_Close(&semaphore);

End:
    NamedSem_Post(&lockSemaphore, 1);
    NamedSem_Close(&lockSemaphore);
    return;
}

Shlib* nitsinj_handle = NULL;
int (NITS_CALL *NitsStartInjectorFunc)(void);
void (NITS_CALL *NitsStopInjectorFunc)(void);

static void ATEXIT_API unloadInjector(void)
{
    if(nitsinj_handle)
    {
        NitsStopInjectorFunc();
        Shlib_Close(nitsinj_handle);
    }
}

void LoadInjector(_In_z_ const PAL_Char *injectorLibName)
{
    int result = 0;
    void* func = NULL;

    if (nitsinj_handle)
    {
        goto End;
    }
           
    nitsinj_handle = Shlib_Open_Injected(injectorLibName, NitsReservedCallSite());
    if (!nitsinj_handle)
    {
        goto End;
    }

    func = Shlib_Sym(nitsinj_handle, "NitsStartInjector");
    if (func == NULL)
        goto Unload;

    NitsStartInjectorFunc = (int (NITS_CALL *)(void))func;

    func = Shlib_Sym(nitsinj_handle, "NitsStopInjector");
    if (func == NULL)
        goto Unload;

    NitsStopInjectorFunc = (void (NITS_CALL *)(void))func;

    result = NitsStartInjectorFunc();
    if (result != 0)
        goto Unload;

    atexit(unloadInjector);
End:
   return;
Unload:
   Shlib_Close(nitsinj_handle);
   nitsinj_handle = NULL;
   return;
}

// Nits Installation reads the nitsinj.dll name from registry key on windows
// On linux, we use the file based mechanism where we require that NitsInstalled file is present
// at specific location. The windows way of doing this was required so that we are fine with layermap tool
void LoadInjectorIfRequired()
{    
    FILE* fp = File_Open(CONFIG_TMPDIR "/NitsInstalled", "rb");
    if(fp)
    {
        PAL_Char injectorLibName[NAME_MAX];
        TcsStrlcpy(injectorLibName, CONFIG_LIBDIR "/libnitsinj.so", NAME_MAX);

        LoadInjector(injectorLibName);
        File_Close(fp);        
    }
}

#endif

void CheckInjector()
{
    /* The injector might not know we are here.
     * Open up the injector refresh semaphore for this process.
     * Then signal it once and wait for the NitsFT to be patched. */    
    if (Atomic_CompareAndSwap(&NITS_PRESENCE_STUB, NitsPresenceUnknown, NitsStubbedOut) == NitsPresenceUnknown)    
    {                
#if defined(ENABLE_UNITTESTING)
        // on linux; if we are not building to run unittests, 
        // in that case this will be a no-op and all further calls will bail out since
        // NITS_PRESENCE_STUB will be NitsStubbedOut after we get here.
        LoadInjectorIfRequired();        
        SignalInjector();
#endif
        /* Re-enter through the function table. This should be patched! */
    }
    else
    {
    	//printf("\nsignalSent was already 1\n");
    }

    /* The function table should be unchanged. The caller will attempt to
     * replace itself with the simple stub, since the check is complete. */
}

static NitsResult NITS_CALL ShouldFault_Checked(
    NitsCallSite line,
    NitsFaultMode mode)
{
    NitsCallSite reservedCallsite = NitsReservedCallSite();
    if(line.id == reservedCallsite.id)
    {
        return NitsFalse;    
    }
    
    //printf("\nshouldfault checked\n");
    CheckInjector();
    //printf("\nfunction got replaced = %d\n", NITS.ShouldFault != ShouldFault_Checked);    
    return NitsShouldFault(line, mode);
}

static void NITS_CALL BeginResource_Checked(
    _In_ void *resource,
         int type,
         NitsResourceScope scope,
         NitsCallSite line)
{
    CheckInjector();    
    NitsBeginResource(resource, type, scope, line);
}

static void NITS_CALL ChangeResource(
    _In_ void *resource,
         int type,
         NitsResourceScope scope,
         NitsCallSite line)
{
    PAL_UNUSED(resource);
    PAL_UNUSED(type);
    PAL_UNUSED(scope);
    PAL_UNUSED(line);
}

static void NITS_CALL EndResource(
    _In_ void *resource,
         int type,
         NitsCallSite line)
{
    PAL_UNUSED(resource);
    PAL_UNUSED(type);
    PAL_UNUSED(line);
}

static void NITS_CALL TraceA(
    _In_z_ const char *text,
           NitsCallSite line,
           NitsFaultMode mode)
{
    PAL_UNUSED(text);
    PAL_UNUSED(line);
    PAL_UNUSED(mode);
}

static void NITS_CALL TraceW(
    _In_z_ const wchar_t *text,
           NitsCallSite line,
           NitsFaultMode mode)
{
    PAL_UNUSED(text);
    PAL_UNUSED(line);
    PAL_UNUSED(mode);
}

static NitsResult NITS_CALL AssertA_Checked(
           int test,
    _In_z_ const char *text,
    _In_z_ const char *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    CheckInjector();    
    return (ShouldCallNITSTable ? NITS.AssertA(test, text, description, line, mode) : NitsTrue);
}

static NitsResult NITS_CALL AssertW_Checked(
           int test,
    _In_z_ const char *text,
    _In_z_ const wchar_t *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    CheckInjector();
    
    return (ShouldCallNITSTable ? NITS.AssertW(test, text, description, line, mode) : NitsTrue);
}

static NitsResult NITS_CALL CompareA_Checked(
           int lhs,
           int rhs,
    _In_z_ const char *lhsText,
    _In_z_ const char *rhsText,
    _In_z_ const char *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    CheckInjector();    
    return (ShouldCallNITSTable ? NITS.CompareA(lhs, rhs, lhsText, rhsText, description, line, mode) : NitsTrue);
}


static NitsResult NITS_CALL CompareW_Checked(
           int lhs,
           int rhs,
    _In_z_ const char *lhsText,
    _In_z_ const char *rhsText,
    _In_z_ const wchar_t *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    CheckInjector();    
    return (ShouldCallNITSTable ? NITS.CompareW(lhs, rhs, lhsText, rhsText, description, line, mode) : NitsTrue);
}


static NitsResult NITS_CALL CompareStringA_Checked(
    _In_z_ const char *lhs,
    _In_z_ const char *rhs,
    _In_z_ const char *lhsText,
    _In_z_ const char *rhsText,
    _In_z_ const char *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    CheckInjector();    
    return (ShouldCallNITSTable ? NITS.CompareStringA(lhs, rhs, lhsText, rhsText, description, line, mode) : NitsTrue);
}

static NitsResult NITS_CALL CompareStringW_Checked(
    _In_z_ const wchar_t *lhs,
    _In_z_ const wchar_t *rhs,
    _In_z_ const char *lhsText,
    _In_z_ const char *rhsText,
    _In_z_ const wchar_t *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    CheckInjector();
    return (ShouldCallNITSTable ? NITS.CompareStringW(lhs, rhs, lhsText, rhsText, description, line, mode) : NitsTrue);
}

static NitsResult NITS_CALL CompareSubstringA_Checked(
    _In_z_ const char *lhs,
    _In_z_ const char *rhs,
    _In_z_ const char *lhsText,
    _In_z_ const char *rhsText,
    _In_z_ const char *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    CheckInjector();    
    return (ShouldCallNITSTable ? NITS.CompareSubstringA(lhs, rhs, lhsText, rhsText, description, line, mode) : NitsTrue);
}

static NitsResult NITS_CALL CompareSubstringW_Checked(
    _In_z_ const wchar_t *lhs,
    _In_z_ const wchar_t *rhs,
    _In_z_ const char *lhsText,
    _In_z_ const char *rhsText,
    _In_z_ const wchar_t *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    CheckInjector();    
    return (ShouldCallNITSTable ? NITS.CompareSubstringW(lhs, rhs, lhsText, rhsText, description, line, mode) : NitsTrue);
}

static NitsResult NITS_CALL DidFault()
{
    return NitsFalse;
}

static NitsResult NITS_CALL IsActivated_Checked()
{
    CheckInjector();    
    return NitsIsActivated();
}

static void NITS_CALL StopReportingIgnoredErrors()
{
}

static int *NITS_CALL GetInt_Checked(
    _In_z_ const char *name)
{
    CheckInjector();    
    return NitsGetInt(name);
}

static const char *NITS_CALL GetStringA_Checked(
    _In_z_ const char *name)
{
    CheckInjector();    
    return NitsGetStringA(name);
}

static const wchar_t *NITS_CALL GetStringW_Checked(
    _In_z_ const char *name)
{
    CheckInjector();    
    return NitsGetStringW(name);
}

static void NITS_CALL SetInt_Checked(
    _In_z_ const char *name,
           int data)
{
    CheckInjector();    
    if(ShouldCallNITSTable) NITS.SetInt(name, data);
}

static void NITS_CALL SetStringA_Checked(
    _In_z_ const char *name,
    _In_z_ const char *data)
{
    CheckInjector();    
    if(ShouldCallNITSTable) NITS.SetStringA(name, data);
}

static void NITS_CALL SetStringW_Checked(
    _In_z_ const char *name,
    _In_z_ const wchar_t *data)
{
    CheckInjector();    
    if(ShouldCallNITSTable) NITS.SetStringW(name, data);
}

static void NITS_CALL SetMode(
    NitsTestMode mode) 
{
    PAL_UNUSED(mode);
}

static void NITS_CALL SetFault(
    _In_opt_z_ const char *function,
    _In_z_     const char *id,
               int attempt)
{
    PAL_UNUSED(function);
    PAL_UNUSED(id);
    PAL_UNUSED(attempt);
}

static void NITS_CALL SetWait(
    _In_opt_z_ const char *function,
    _In_z_     const char *id,
               int attempt,
    _In_z_     const char *event)
{
    PAL_UNUSED(function);
    PAL_UNUSED(id);
    PAL_UNUSED(attempt);
    PAL_UNUSED(event);
}

static void NITS_CALL Signal(
    _In_z_ const char *event)
{
    PAL_UNUSED(event);
}

static NitsResult NITS_CALL Wait(
    _In_opt_z_ const char *function,
    _In_z_    const char *id,
               int attempt,
               int timeout)
{
    PAL_UNUSED(function);
    PAL_UNUSED(id);
    PAL_UNUSED(attempt);
    PAL_UNUSED(timeout);

    return NitsTrue;
}

static void NITS_CALL ResetFaults()
{
}

static NitsTrapHandle NITS_CALL OpenTrap(
    _In_z_ const char *binary,
    _In_z_ const char *table,
           unsigned version)
{
    PAL_UNUSED(binary);
    PAL_UNUSED(table);
    PAL_UNUSED(version);

    return 0;
}

static const void *NITS_CALL GetTrap(
    _In_ NitsTrapHandle handle,
         unsigned offset)
{
    PAL_UNUSED(handle);
    PAL_UNUSED(offset);

    return 0;
}

static const void *NITS_CALL NextTrap(
    _In_z_ const char *table,
           unsigned offset)
{
    PAL_UNUSED(table);
    PAL_UNUSED(offset);

    return 0;
}

static void *NITS_CALL SetTrap(
    _In_ NitsTrapHandle handle,
    _In_ void *function,
         unsigned offset)
{
    PAL_UNUSED(handle);
    PAL_UNUSED(function);
    PAL_UNUSED(offset);

    return 0;
}

static void NITS_CALL CopyTrap(
    _In_z_ const char *table,
    _In_z_ const char *from,
    _In_z_ const char *to)
{
    PAL_UNUSED(table);
    PAL_UNUSED(from);
    PAL_UNUSED(to);
}

static void NITS_CALL CloseTrap(
    _In_ NitsTrapHandle handle)
{
    PAL_UNUSED(handle);
}

NITS_DLLEXPORT ptrdiff_t NITS_PRESENCE_STUB = NitsPresenceUnknown;
NITS_DLLEXPORT NITS_CONST_FT NitsFT NITS_STUB =
{
    ShouldFault_Checked,
    TraceA,
    TraceW,
    AssertA_Checked,
    AssertW_Checked,
    CompareA_Checked,
    CompareW_Checked,
    CompareStringA_Checked,
    CompareStringW_Checked,
    CompareSubstringA_Checked,
    CompareSubstringW_Checked,
    DidFault,
    IsActivated_Checked,
    StopReportingIgnoredErrors,
    GetInt_Checked,
    GetStringA_Checked,
    GetStringW_Checked,
    SetInt_Checked,
    SetStringA_Checked,
    SetStringW_Checked,
    SetMode,
    SetFault,
    SetWait,
    Signal,
    Wait,
    ResetFaults,
    BeginResource_Checked,
    ChangeResource,
    EndResource,
    NULL,
    NULL,
    NULL,
    OpenTrap,
    GetTrap,
    NextTrap,
    SetTrap,
    CopyTrap,
    CloseTrap,
};
