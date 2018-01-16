/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef TEST_BUILD
    #define TEST_BUILD
#endif


#define NITS_EXPORT PAL_EXTERN_C PAL_EXPORT_API

#include <nits/base/nits.h>
#include <string>
#include "Globals.h"
#include <pal/palcommon.h>
#include <pal/strings.h>


using namespace TestSystem;

static NitsResult NITS_CALL ShouldFault(
    NitsCallSite line,
    NitsFaultMode mode)
{
    return GetGlobals().ShouldFault(line, mode);
}

static void NITS_CALL BeginResource(
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

static void NITS_CALL TraceW(
    _In_z_ const wchar_t *text,
           NitsCallSite line,
           NitsFaultMode mode)
{
    Globals &globals = GetGlobals();
    Configuration const &config = globals.GetConfiguration();
    Fault &autoFault = globals.GetAutoFault();

    if (mode == NitsManual || config.traces >= NitsTraceVerbose)
    {
        wostringstream buf;
        if (autoFault.DidFault())
        {
            //Any tracing information that follows an automatic fault should
            //  show the iteration number for debugging purposes.
            buf << L"{fault=" << autoFault.m_iteration << L"} ";
        }
        if (line.id != CallSite_NONE)
        {
            buf << L"[site=" << line.id << L"] ";
        }
        PWSTR wideFile = ConvertStringToW(line.file);
        buf << wideFile << L"(" << line.line << L"): " << ((text != NULL) ? text : L"<NullString>") << L"\n";
        PAL_Char *output = ConvertStringWToPalChar(buf.str().c_str());
        globals.PostPipe(output);
        delete [] output;
        delete [] wideFile;
    }
}

static void NITS_CALL TraceA(
    _In_z_ const char *text,
           NitsCallSite line,
           NitsFaultMode mode)
{
    //TODO: This should be the base logging API that everything else uses.
    //  The underlying cross-proc buffer and log should be ANSI as well.
    PWSTR wideText = ConvertStringToW(text);
    TraceW(wideText, line, mode);
    delete [] wideText;
}

static NitsResult NITS_CALL AssertA(
           int test,
    _In_z_ const char *text,
    _In_z_ const char *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    if (GetGlobals().TestExpression(test != FALSE, mode))
    {
        return (test != FALSE) ? NitsTrue : NitsFalse;
    }

    ostringstream buf;
    buf << "\n\tAssert: " << text <<
       "\n\t\t(" << description << ")";
    TraceA(buf.str().c_str(), line, NitsManual);
    return NitsFalse;
}

static NitsResult NITS_CALL AssertW(
           int test,
    _In_z_ const char *text,
    _In_z_ const wchar_t *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    if (GetGlobals().TestExpression(test != FALSE, mode))
    {
        return (test != FALSE) ? NitsTrue : NitsFalse;
    }

    PSTR ansiDesc = ConvertStringToA(description);
    ostringstream buf;
    buf << "\n\tAssert: " << text <<
           "\n\t\t(" << ansiDesc << ")";
    delete [] ansiDesc;
    TraceA(buf.str().c_str(), line, NitsManual);
    return NitsFalse;
}

static NitsResult NITS_CALL CompareA(
           int lhs,
           int rhs,
    _In_z_ const char *lhsText,
    _In_z_ const char *rhsText,
    _In_z_ const char *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    if (GetGlobals().TestExpression(lhs == rhs, mode))
    {
        return (lhs == rhs) ? NitsTrue : NitsFalse;
    }

    ostringstream buf;
    buf << "\n\tCompare: " << lhsText << " == " << rhsText <<
           "\n\t\tLHS: " << lhs <<
           "\n\t\tRHS: " << rhs <<
           "\n\t\t(" << description << ")";
    TraceA(buf.str().c_str(), line, NitsManual);
    return NitsFalse;
}

static NitsResult NITS_CALL CompareW(
           int lhs,
           int rhs,
    _In_z_ const char *lhsText,
    _In_z_ const char *rhsText,
    _In_z_ const wchar_t *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    if (GetGlobals().TestExpression(lhs == rhs, mode))
    {
        return (lhs == rhs) ? NitsTrue : NitsFalse;
    }

    PSTR ansiDesc = ConvertStringToA(description);
    ostringstream buf;
    buf << "\n\tCompare: " << lhsText << " == " << rhsText <<
           "\n\t\tLHS: " << lhs <<
           "\n\t\tRHS: " << rhs <<
           "\n\t\t(" << ansiDesc << ")";
    TraceA(buf.str().c_str(), line, NitsManual);
    return NitsFalse;
}

static NitsResult ExactComparatorA(
    _In_z_ const char *lhs,
    _In_z_ const char *rhs)
{
    if (!lhs && !rhs)
    {
        return NitsTrue;
    }
    else if (!lhs || !rhs)
    {
        return NitsFalse;
    }
    return Strcasecmp(lhs, rhs) == 0 ? NitsTrue : NitsFalse;
}

static NitsResult ExactComparatorW(
    _In_z_ const wchar_t *lhs,
    _In_z_ const wchar_t *rhs)
{
    if (!lhs && !rhs)
    {
        return NitsTrue;
    }
    else if (!lhs || !rhs)
    {
        return NitsFalse;
    }
    return Wcscasecmp(lhs, rhs) == 0 ? NitsTrue : NitsFalse;
}

static PCWSTR _wcsistr(_In_z_ PCWSTR lhs,
                       _In_z_ PCWSTR rhs)
{
    int len_l = (int)wcslen(lhs);
    int len_r = (int)wcslen(rhs);
    for (int i = 0; i < len_l; i++)
    {
        if (Wcsncasecmp(lhs + i, rhs, len_r) == 0)
        {
            return lhs + i;
        }
    }
    return NULL;
}

static PCSTR _stristr(_In_z_ PCSTR lhs,
                      _In_z_ PCSTR rhs)
{
    int len_l = (int)strlen(lhs);
    int len_r = (int)strlen(rhs);
    for (int i = 0; i < len_l; i++)
    {
        if (Strncasecmp(lhs + i, rhs, len_r) == 0)
        {
            return lhs + i;
        }
    }
    return NULL;
}

static NitsResult SubstringComparatorA(
    _In_z_ const char *lhs,
    _In_z_ const char *rhs)
{
    if (!lhs && !rhs)
    {
        return NitsTrue;
    }
    else if (!lhs || !rhs)
    {
        return NitsFalse;
    }
    return _stristr(lhs, rhs) != NULL ? NitsTrue : NitsFalse;
}

static NitsResult SubstringComparatorW(
    _In_z_ const wchar_t *lhs,
    _In_z_ const wchar_t *rhs)
{
     if (!lhs && !rhs)
    {
        return NitsTrue;
    }
    else if (!lhs || !rhs)
    {
        return NitsFalse;
    }
    return _wcsistr(lhs, rhs) != NULL ? NitsTrue : NitsFalse;
}

static NitsResult NITS_CALL CompareStringA(
    _In_z_ const char *lhs,
    _In_z_ const char *rhs,
    _In_z_ const char *lhsText,
    _In_z_ const char *rhsText,
    _In_z_ const char *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    NitsResult test = ExactComparatorA(lhs, rhs);
    if (GetGlobals().TestExpression(test != NitsFalse, mode))
    {
        return test;
    }

    ostringstream buf;
    buf << "\n\tCompare: " << lhsText << " == " << rhsText <<
           "\n\t\tLHS: " << lhs <<
           "\n\t\tRHS: " << rhs <<
           "\n\t\t(" << description << ")";
    TraceA(buf.str().c_str(), line, NitsManual);
    return NitsFalse;
}

static NitsResult NITS_CALL CompareStringW(
    _In_z_ const wchar_t *lhs,
    _In_z_ const wchar_t *rhs,
    _In_z_ const char *lhsText,
    _In_z_ const char *rhsText,
    _In_z_ const wchar_t *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    NitsResult test = ExactComparatorW(lhs, rhs);
    if (GetGlobals().TestExpression(test != NitsFalse, mode))
    {
        return test;
    }

    PSTR ansiLhs = ConvertStringToA(lhs);
    PSTR ansiRhs = ConvertStringToA(rhs);
    PSTR ansiDesc = ConvertStringToA(description);
    ostringstream buf;
    buf << "\n\tCompare: " << lhsText << " == " << rhsText <<
           "\n\t\tLHS: " << ansiLhs <<
           "\n\t\tRHS: " << ansiRhs <<
           "\n\t\t(" << ansiDesc << ")";
    delete [] ansiLhs;
    delete [] ansiRhs;
    delete [] ansiDesc;
    TraceA(buf.str().c_str(), line, NitsManual);
    return NitsFalse;
}

static NitsResult NITS_CALL CompareSubstringA(
    _In_z_ const char *lhs,
    _In_z_ const char *rhs,
    _In_z_ const char *lhsText,
    _In_z_ const char *rhsText,
    _In_z_ const char *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    NitsResult test = SubstringComparatorA(lhs, rhs);
    if (GetGlobals().TestExpression(test != NitsFalse, mode))
    {
        return test;
    }

    ostringstream buf;
    buf << "\n\tCompare: " << lhsText << " CONTAINS " << rhsText <<
           "\n\t\tLHS: " << lhs <<
           "\n\t\tRHS: " << rhs <<
           "\n\t\t(" << description << ")";
    TraceA(buf.str().c_str(), line, NitsManual);
    return NitsFalse;
}

static NitsResult NITS_CALL CompareSubstringW(
    _In_z_ const wchar_t *lhs,
    _In_z_ const wchar_t *rhs,
    _In_z_ const char *lhsText,
    _In_z_ const char *rhsText,
    _In_z_ const wchar_t *description,
           NitsCallSite line,
           NitsFaultMode mode)
{
    NitsResult test = SubstringComparatorW(lhs, rhs);
    if (GetGlobals().TestExpression(test != NitsFalse, mode))
    {
        return test;
    }

    PSTR ansiLhs = ConvertStringToA(lhs);
    PSTR ansiRhs = ConvertStringToA(rhs);
    PSTR ansiDesc = ConvertStringToA(description);
    ostringstream buf;
    buf << "\n\tCompare: " << lhsText << " CONTAINS " << rhsText <<
           "\n\t\tLHS: " << ansiLhs <<
           "\n\t\tRHS: " << ansiRhs <<
           "\n\t\t(" << ansiDesc << ")";
    delete [] ansiLhs;
    delete [] ansiRhs;
    delete [] ansiDesc;
    TraceA(buf.str().c_str(), line, NitsManual);
    return NitsFalse;
}

static NitsResult NITS_CALL DidFault_()
{
    return GetGlobals().DidFault() ? NitsTrue : NitsFalse;
}

static NitsResult NITS_CALL IsActivated()
{
    return GetGlobals().IsUnittestRunning() ? NitsTrue : NitsFalse;
}

static void NITS_CALL StopReportingIgnoredErrors_()
{
    GetGlobals().StopReportingIgnoredErrors();
}

static int *NITS_CALL GetInt(
    _In_z_ const char *name)
{
    PAL_UNUSED(name);

    return NULL;
}

static const char *NITS_CALL GetStringA(
    _In_z_ const char *name)
{
    PAL_UNUSED(name);

    return NULL;
}

static const wchar_t *NITS_CALL GetStringW(
    _In_z_ const char *name)
{
    PAL_UNUSED(name);

    return NULL;
}

static void NITS_CALL SetInt(
    _In_z_ const char *name,
           int data)
{
    PAL_UNUSED(name);
    PAL_UNUSED(data);
}

static void NITS_CALL SetStringA(
    _In_z_ const char *name,
    _In_z_ const char *data)
{
    PAL_UNUSED(name);
    PAL_UNUSED(data);
}

static void NITS_CALL SetStringW(
    _In_z_ const char *name,
    _In_z_ const wchar_t *data)
{
    PAL_UNUSED(name);
    PAL_UNUSED(data);
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
    _In_z_     const char *id,
               int attempt,
               int timeout)
{
    PAL_UNUSED(function);
    PAL_UNUSED(id);
    PAL_UNUSED(attempt);
    PAL_UNUSED(timeout);

    return NitsFalse;
}

static void NITS_CALL ResetFaults()
{
}

struct Table
{
    unsigned bytes;
    unsigned version;
};

struct TrapData
{
    /* Assumes changes are made only once. */
    /* TODO: Make this work with multiple changes in any order. */
    Shlib *library;
    Table *actual;
    Table *copy;
};

static NitsTrapHandle NITS_CALL OpenTrap(
    _In_z_ const char *binary,
    _In_z_ const char *table,
           unsigned version)
{
    TrapData *data;
    Table *actual;
    Shlib *library = NULL;
    Table *copy;

    PAL_Char *palCharBinary = ConvertStringAToPalChar(binary);
    if(palCharBinary)
    {
        library = Shlib_Open_Injected(palCharBinary, NitsReservedCallSite());
        delete [] palCharBinary;
    }
    if (library == NULL)
    {
        return NULL;
    }

    actual = (Table *)Shlib_Sym(library, table);
    if (actual == NULL)
    {
        Shlib_Close(library);
        return NULL;
    }

    if (actual->version != version)
    {
    	Shlib_Close(library);
        return NULL;
    } 

    copy = (Table *)SystemMalloc(actual->bytes);
    if (copy == NULL)
    {
    	Shlib_Close(library);
        return NULL;
    }

    memcpy(copy, actual, actual->bytes);

    data = (TrapData *)SystemMalloc(sizeof(TrapData));
    if (data == NULL)
    {
        SystemFree(copy);
        Shlib_Close(library);
        return NULL;
    }

    data->library = library;
    data->actual = actual;
    data->copy = copy;
    return data;
}

static const void *NITS_CALL GetTrap(
    _In_ NitsTrapHandle handle,
         unsigned offset)
{
    TrapData *data = (TrapData *)handle;
    Table *actual = data->actual;

    if (actual->bytes < offset + sizeof(void *))
    {
        //TODO: terminate execution.
        return NULL;
    }

    return actual;
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
    PAL_UNUSED(function);

    /* TODO: Logging. */
    TrapData *data = (TrapData *)handle;
    Table *actual = data->actual;

    if (actual->bytes < offset + sizeof(void *))
    {
        //TODO: terminate execution.
        return NULL;
    }

    return actual;
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
    TrapData *data = (TrapData *)handle;
    Table *actual = data->actual;
    Table *copy = data->copy;

    memcpy(actual, copy, actual->bytes);
    SystemFree(copy);
    Shlib_Close(data->library);
    SystemFree(data);
}

int NITS_CALL GetResult()
{
   return (int)GetGlobals().GetResult();
}

NITS_EXPORT_DEF ptrdiff_t NITS_PRESENCE_IMPL = NitsActive;
NITS_EXPORT_DEF NITS_CONST_FT NitsFT NITS_IMPL =
{
    ShouldFault,
    TraceA,
    TraceW,
    AssertA,
    AssertW,
    CompareA,
    CompareW,
    CompareStringA,
    CompareStringW,
    CompareSubstringA,
    CompareSubstringW,
    DidFault_,
    IsActivated,
    StopReportingIgnoredErrors_,
    GetInt,
    GetStringA,
    GetStringW,
    SetInt,
    SetStringA,
    SetStringW,
    SetMode,
    SetFault,
    SetWait,
    Signal,
    Wait,
    ResetFaults,
    BeginResource,
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
    GetResult
};
