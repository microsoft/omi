/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef HOOK_BUILD
#define HOOK_BUILD
#endif

#include <wchar.h>
#include <nits/base/nits.h>
#include <pal/format.h>
#include "Shim.h"

# define OutputDebugString(s)

DWORD NotifySEC(int caseNumber, BOOL success)
{
    BOOL sent;
    PCSTR result = success ? "OK" : "FAILED";
    char *str = (char *)_HeapAlloc((sizeof(char)*50), NitsHere());
    if (str == NULL)
    {    
        return ERROR_OUTOFMEMORY;
    }    

    Snprintf(str, 50, "Completed audit number %d, result %s\n", caseNumber, result);

    sent = _SendRequest(str, NitsHere());
    SystemFree(str);

    //Removing this check is a bug.
    if (!sent)
        return ERROR_GEN_FAILURE;

    return NO_ERROR;
}

DWORD DownloadAccounts(PCSTR company)
{
    BOOL sent;
    char *str = (char *)_HeapAlloc((sizeof(char)*50), NitsHere());
    if (str == NULL)
        return ERROR_OUTOFMEMORY;

    OutputDebugString("Downloading accounts...");

    Snprintf(str, 50, "Send accounts for company %s\n", company);
    sent = _SendRequest(str, NitsHere());
    SystemFree(str);

    if (!sent)
        return ERROR_GEN_FAILURE;

    return NO_ERROR;
}

DWORD MakeReports(PCSTR company, int caseNumber)
{
    DWORD error = DownloadAccounts(company);
    if (error) return error;

    OutputDebugString("Making reports...");
    //Do something with account data.

    error = NotifySEC(caseNumber, TRUE);
    if (error) return error;

    return NO_ERROR;
}

DWORD BalanceBooks(PCSTR company, int caseNumber)
{
    DWORD error = DownloadAccounts(company);
    if (error) return error;

    //Do something with account data.

    error = NotifySEC(caseNumber, TRUE);
    if (error) return error;

    return NO_ERROR;
}

