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

                size_t allocSize = 0;
                if (SizeTMult(sizeof(wchar_t), wcharCount, &allocSize) != S_OK ||
                    SizeTAdd(allocSize, sizeof(IntlstrBucket), &allocSize != S_OK))
                {
                    return NULL;
                }

                bucket = (IntlstrBucket*) PAL_Malloc(allocSize);
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
