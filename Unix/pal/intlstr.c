/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#include "intlstr.h"

#include <assert.h>

#if defined(_MSC_VER)

    #include <windows.h>

    _Use_decl_annotations_
    const PAL_Char* _Intlstr_GetString_LoadString(HINSTANCE hInstance, UINT uID)
    {
        int err;
        LPTSTR lpBuffer;

        err = LoadString(hInstance, uID, (LPTSTR)&lpBuffer, 0);
        if (err == 0)
        {
            /* TODO/FIXME - OI diagnostics */
            return NULL;
        }

        return lpBuffer;
    }

    _Use_decl_annotations_
    PAL_Char* _Intlstr_FormatString_FormatMessage(HINSTANCE hInstance, UINT uID, ...)
    {
        DWORD result;
        int err;
        LPTSTR lpTemplate;
        LPTSTR lpFormattedString;
        va_list ap; 

        err = LoadString(hInstance, uID, (LPTSTR)&lpTemplate, 0);
        if (err == 0)
        {
            /* TODO/FIXME - OI diagnostics */
            return NULL;
        }

        va_start(ap, uID); 
        result = FormatMessage(
            /* TODO/FIXME - FORMAT_MESSAGE_FROM_HMODULE can in theory help avoid the LoadString above, but I couldn't get it to work... */
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_STRING, 
            lpTemplate, 
            0, /* dwMessageId;  ignored when FORMAT_MESSAGE_FROM_STRING is used */
            0, /* dwLanguageId; ignored when FORMAT_MESSAGE_FROM_STRING is used */
            (LPTSTR)&lpFormattedString,
            0, /* nSize - maximum size of buffer to allocate;  0 means no limit */
            &ap);
        va_end(ap); 
        if (result == 0)
        {
            /* TODO/FIXME - OI diagnostics */
            return NULL;
        }

        return lpFormattedString;
    }

#else /* !defined(_MSC_VER) */

    #include <pal/format.h>
    #include <pal/strings.h>

    #if defined(CONFIG_ENABLE_GETTEXT)

    #include <libintl.h>
    #include <stdarg.h>
    #include <pal/hashmap.h>
    #include <pal/once.h>
    #include <pal/lock.h>

        #if defined(CONFIG_ENABLE_WCHAR)

            typedef struct _IntlstrBucket {
                HashBucket      bucket;
                int id;
                const char* domain_name;
                PAL_Char text[1];
            } IntlstrBucket;

            static size_t Intlstr_HashMapHashProc(const HashBucket* untypedBucket)
            {
                IntlstrBucket* bucket = (IntlstrBucket*)untypedBucket;
                return (size_t)bucket->id ^ HashMap_HashProc_AnsiString(bucket->domain_name);
            }

            static int Intlstr_HashMapEqualProc(_In_ const HashBucket* untypedBucket1, _In_ const HashBucket* untypedBucket2)
            {
                IntlstrBucket* bucket1 = (IntlstrBucket*)untypedBucket1;
                IntlstrBucket* bucket2 = (IntlstrBucket*)untypedBucket2;
                return (bucket1->id == bucket2->id) &&
                    (0 == strcmp(bucket1->domain_name, bucket2->domain_name));
            }

            static void Intlstr_HashMapReleaseProc(_In_ HashBucket* untypedBucket)
            {
                PAL_UNUSED(untypedBucket);
            }

            static Once g_intlStr_once = ONCE_INITIALIZER;
            static HashMap g_intlStr_hashmap;
            static ReadWriteLock g_intlStr_lock;

            static void ATEXIT_API _Intlstr_OnceCleanup(void)
            {
                HashMap_Destroy(&g_intlStr_hashmap);
            }

            _Success_(return == 0) int _Intlstr_OnceInit(void* data, _Outptr_result_maybenull_ void** value)
            {
                int result = 0;

                *value = NULL;

                ReadWriteLock_Init(&g_intlStr_lock);

                result = HashMap_Init(
                    &g_intlStr_hashmap, 
                    32, /* initial number of buckets */
                    Intlstr_HashMapHashProc,
                    Intlstr_HashMapEqualProc,
                    Intlstr_HashMapReleaseProc);

                if (result == 0)
                {
                    result = PAL_Atexit(_Intlstr_OnceCleanup);
                }

                return result;
            }

        #endif /* ?defined(CONFIG_ENABLE_WCHAR) */

        _Use_decl_annotations_
        const PAL_Char* _Intlstr_GetString_GetText(const char* domain_name, int id, const char* msgid)
        {
        #if defined(CONFIG_ENABLE_WCHAR)
            IntlstrBucket* bucket;

            if (0 != Once_Invoke(&g_intlStr_once, _Intlstr_OnceInit, NULL))
            {
                /* TODO/FIXME - OI diagnostics */
                return NULL;
            }

            {
                IntlstrBucket referenceBucket;
                referenceBucket.id = id;
                referenceBucket.domain_name = domain_name;
                ReadWriteLock_AcquireRead(&g_intlStr_lock);
                bucket = (IntlstrBucket*) HashMap_Find(&g_intlStr_hashmap, (HashBucket*) &referenceBucket);
                ReadWriteLock_ReleaseRead(&g_intlStr_lock);
            }

            if (bucket == NULL)
            {
                size_t wcharCount;
                size_t copiedCount;
                int insertResult;

                char* localizedString = dgettext(domain_name, msgid);
                if (localizedString == NULL)
                {
                    /* TODO/FIXME - OI diagnostics */
                    return NULL;
                }

                wcharCount = mbstowcs(NULL, localizedString, 0);
                if (wcharCount == ((size_t)-1))
                {
                    /* TODO/FIXME - OI diagnostics */
                    return NULL;
                }
                if ((((size_t)(-1)) - sizeof(IntlstrBucket) / 2) < wcharCount)
                {
                    /* TODO/FIXME - OI diagnostics */
                    return NULL;
                }

                bucket = (IntlstrBucket*) PAL_Malloc(sizeof(IntlstrBucket) + sizeof(wchar_t) * wcharCount);
                if (!bucket)
                {
                    /* TODO/FIXME - OI diagnostics */
                    return NULL;
                }
                bucket->id = id;
                bucket->domain_name = domain_name;

                copiedCount = mbstowcs(bucket->text, localizedString, wcharCount + 1);
                assert(copiedCount == wcharCount);

                ReadWriteLock_AcquireWrite(&g_intlStr_lock);
                insertResult = HashMap_Insert(&g_intlStr_hashmap, (HashBucket*) bucket);
                if (insertResult == 1) /* already exists? => use the old one / discard the new one */
                {
                    IntlstrBucket* oldBucket = (IntlstrBucket*) HashMap_Find(&g_intlStr_hashmap, (HashBucket*) bucket);
                    assert(oldBucket != NULL);
                    PAL_Free(bucket);
                    bucket = oldBucket;
                }
                ReadWriteLock_ReleaseWrite(&g_intlStr_lock);
            }

            return bucket->text;
        #else /* !defined(CONFIG_ENABLE_WCHAR) */
            char* localizedString;
            
            PAL_UNUSED(id);

            localizedString = dgettext(domain_name, msgid);
            if (localizedString == NULL)
            {
                /* TODO/FIXME - OI diagnostics */
                return NULL;
            }

            return localizedString;
        #endif /* ?defined(CONFIG_ENABLE_WCHAR) */
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

#endif /* ?defined(_MSC_VER) */
