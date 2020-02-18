/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "intlstr.h"

#include <assert.h>
#include <pal/intsafe.h>

    #include <pal/format.h>
    #include <pal/strings.h>

    #if defined(CONFIG_ENABLE_GETTEXT)

    #include <libintl.h>
    #include <stdarg.h>
    #include <pal/hashmap.h>
    #include <pal/once.h>
    #include <pal/lock.h>

        _Use_decl_annotations_
        const PAL_Char* _Intlstr_GetString_GetText(const char* domain_name, int id, const char* msgid)
        {
            char* localizedString;

            PAL_UNUSED(id);

            localizedString = dgettext(domain_name, msgid);
            if (localizedString == NULL)
            {
                /* TODO/FIXME - OI diagnostics */
                return NULL;
            }

            return localizedString;
        }

        PAL_Char* _Intlstr_FormatString_gettext_and_snprintf(const char* domain_name, int id, const char* msgid, ...)
        {
            PAL_Char* templateString = NULL;
            PAL_Char* resultString = NULL;
            va_list ap;

            va_start(ap, msgid);

            templateString = _Intlstr_GetString_GetText(domain_name, id, msgid);
            if (!templateString)
            {
                /* TODO/FIXME - OI diagnostics */
                goto CleanUp;
            }

            resultString = Vstprintf_StrDup(templateString, ap);
            if (!resultString)
            {
                /* TODO/FIXME - OI diagnostics */
                goto CleanUp;
            }

        CleanUp:
            va_end(ap);
            return resultString;
        }

    #endif /* ?defined(CONFIG_ENABLE_GETTEXT) */
