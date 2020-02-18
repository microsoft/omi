/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "strings.h"

#include <pal/palcommon.h>
#include <pal/format.h>
#include <pal/strings.h>

#include <stdio.h>
#include <stdlib.h>

void testDisplay(_In_z_ const PAL_Char* testname, _In_z_ const PAL_Char* string)
{
    Tprintf(
        PAL_T("%") PAL_T(PAL_PRItstr) PAL_T(": string = >>>%") PAL_T(PAL_PRItstr) PAL_T("<<<\n"), 
        tcs(testname), 
        tcs(string));
}

void reportError(_In_z_ const PAL_Char* testname)
{
    Tprintf(
        PAL_T("%") PAL_T(PAL_PRItstr) PAL_T(": error\n"), 
        tcs(testname));
}

_Success_(return == 0)
int testSimpleString()
{
    int ret = 0;
/**************************************************************
 * EXAMPLE 1 - CONSUMING LOCALIZED STRING (no placeholders)
 *
 * - Intellisense in WinIde works fine when typing Intlstr_Simp<ctrl-space> 
 * - Intlstr_Free called afterwards in a common function above
 */
    Intlstr intlstr = Intlstr_Null;
    intlstr = Intlstr_SimpleString(); /* <- GETTING THE STRING */
    if (intlstr.str == NULL) /* <- RESOURCES MISSING?  OOM? */
    {
        reportError(PAL_T("SimpleString"));
        ret = 1;
        goto CleanUp;
    }
    testDisplay(PAL_T("SimpleString"), tcs(intlstr.str));

CleanUp:
    Intlstr_Free(intlstr); /* <- FREEING THE STRING */
    return ret;
}

_Success_(return == 0)
int testFormattedIntegers()
{
    int ret = 0;

/**************************************************************
 * EXAMPLE 2 - FORMATTING LOCALIZED STRING (integer placeholders)
 *
 * - Intellisense in WinIde works fine when typing Intlstr_Reord<ctrl-space> + shows types/names of placeholders 
 * - Need to free the string afterwards via Intlstr_FreeFormattedString
 */
    Intlstr intlstr = Intlstr_Null;
    intlstr = Intlstr_ReorderablePlaceholders(123, 456); /* <- FORMATTING THE STRING */
    if (intlstr.str == NULL) /* <- RESOURCES MISSING?  OOM? */
    {
        reportError(PAL_T("FormattedIntegers"));
        ret = 1;
        goto CleanUp;
    }
    testDisplay(PAL_T("FormattedIntegers"), tcs(intlstr.str));

CleanUp:
    Intlstr_Free(intlstr); /* <- FREEING THE STRING */
    return ret;
}

_Success_(return == 0)
int testFormattedStrings()
{
    int ret = 0;

/**************************************************************
 * EXAMPLE 3 - FORMATTING LOCALIZED STRING (string placeholders)
 *
 * - Intellisense in WinIde works fine when typing Intlstr_Reord<ctrl-space> + shows types/names of placeholders 
 * - Need to free the string afterwards via Intlstr_FreeFormattedString
 */
    Intlstr intlstr = Intlstr_Null;
    intlstr = Intlstr_StringPlaceholders(PAL_T("foo"), PAL_T("bar")); /* <- FORMATTING THE STRING */
    if (intlstr.str == NULL) /* <- RESOURCES MISSING?  OOM? */
    {
        reportError(PAL_T("FormattedStrings"));
        ret = 1;
        goto CleanUp;
    }
    testDisplay(PAL_T("FormattedStrings"), tcs(intlstr.str));

CleanUp:
    Intlstr_Free(intlstr); /* <- FREEING THE STRING */
    return ret;
}

/* for now please ignore the gettext-related code below (i.e. includes, setlocale, bindtextdomain) */
#include <libintl.h>
#include <locale.h>
int main() {
    setlocale(LC_MESSAGES, "" /* empty string means => use environment variables */);
    bindtextdomain("pal_intlstr_sample.exe", "./");
    testSimpleString();
    testFormattedIntegers();
    testFormattedStrings();
    return 0;
}

