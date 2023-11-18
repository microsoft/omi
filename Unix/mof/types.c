/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "types.h"
#include "ptrarray.h"
#include "config.h"
#include "mofyacc.h"
#include "buffer.h"
#include "state.h"
#include <base/helpers.h>

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 28719)
#endif

#define MI_STRINGMAXLEN 24

/*
**==============================================================================
**
** Local definitions
**
**==============================================================================
*/

#define NEW_ARRAY_T(PTR, TYPE, SIZE)  \
    for (;;) \
    { \
        PTR = ((TYPE##A*)MOF_Malloc(&state.heap, \
            sizeof(TYPE##A) + sizeof(TYPE) * (SIZE))); \
        if(PTR) \
        { \
            PTR->data = (TYPE*)(PTR + 1); \
            PTR->size = SIZE; \
        } \
        break; \
    }

const char* _getTypeName(MI_Type type)
{
    switch (type)
    {
        case MI_BOOLEAN:
            return "BOOLEAN";
        case MI_UINT8:
            return "UINT8";
        case MI_SINT8:
            return "SINT8";
        case MI_UINT16:
            return "UINT16";
        case MI_SINT16:
            return "SINT16";
        case MI_UINT32:
            return "UINT32";
        case MI_SINT32:
            return "SINT32";
        case MI_UINT64:
            return "UINT64";
        case MI_SINT64:
            return "SINT64";
        case MI_REAL32:
            return "REAL32";
        case MI_REAL64:
            return "REAL64";
        case MI_CHAR16:
            return "CHAR16";
        case MI_DATETIME:
            return "DATETIME";
        case MI_STRING:
            return "STRING";
        case MI_REFERENCE:
            return "REFERENCE";
        case MI_INSTANCE:
            return "INSTANCE";
        case MI_BOOLEANA:
            return "BOOLEAN[]";
        case MI_UINT8A:
            return "UINT8[]";
        case MI_SINT8A:
            return "SINT8[]";
        case MI_UINT16A:
            return "UINT16[]";
        case MI_SINT16A:
            return "SINT16[]";
        case MI_UINT32A:
            return "UINT32[]";
        case MI_SINT32A:
            return "SINT32[]";
        case MI_UINT64A:
            return "UINT64[]";
        case MI_SINT64A:
            return "SINT64[]";
        case MI_REAL32A:
            return "REAL32[]";
        case MI_REAL64A:
            return "REAL64[]";
        case MI_CHAR16A:
            return "CHAR16[]";
        case MI_DATETIMEA:
            return "DATETIME[]";
        case MI_STRINGA:
            return "STRING[]";
        case MI_REFERENCEA:
            return "REFERENCE[]";
        case MI_INSTANCEA:
            return "INSTANCE[]";
        default:
            return "UNKNOWN";
    }
}

static size_t _typeSizes[] =
{
    sizeof(MI_Boolean),
    sizeof(MI_Uint8),
    sizeof(MI_Sint8),
    sizeof(MI_Uint16),
    sizeof(MI_Sint16),
    sizeof(MI_Uint32),
    sizeof(MI_Sint32),
    sizeof(MI_Uint64),
    sizeof(MI_Sint64),
    sizeof(MI_Real32),
    sizeof(MI_Real64),
    sizeof(MI_Char16),
    sizeof(MI_Datetime),
    sizeof(MI_String),
    sizeof(void*), /* reference */
    sizeof(void*), /* instance */
};

static int _ParseUint32(
    const char* p,
    size_t n,
    MI_Boolean asterisks,
    MI_Uint32* result)
{
    char buf[9];
    char* end;
    size_t i;

    if (n > 8)
        return -1;

    memcpy(buf, p, n);
    buf[n] = '\0';

    if (asterisks && buf[0] == '*')
    {
        for (i = 1; i < n; i++)
        {
            if (buf[i] != '*')
                return -1;
        }
        *result = 0;
        return 0;
    }
    *result = (MI_Uint32)strtoul(buf, &end, 10);

    if (*end != '\0')
        return -1;

    return 0;
}

typedef struct _Flag
{
    const char* name;
    MI_Uint32 flag;
}
Flag;

static Flag _flags[] =
{
    { "CLASS", MI_FLAG_CLASS },
    { "METHOD", MI_FLAG_METHOD },
    { "PROPERTY", MI_FLAG_PROPERTY },
    { "PARAMETER", MI_FLAG_PARAMETER },
    { "ASSOCIATION", MI_FLAG_ASSOCIATION },
    { "INDICATION", MI_FLAG_INDICATION },
    { "REFERENCE", MI_FLAG_REFERENCE },

    { "KEY", MI_FLAG_KEY },
    { "IN", MI_FLAG_IN },
    { "OUT", MI_FLAG_OUT },
    { "REQUIRED", MI_FLAG_REQUIRED },
    { "STATIC", MI_FLAG_STATIC },
    { "ABSTRACT", MI_FLAG_ABSTRACT },
    { "TERMINAL", MI_FLAG_TERMINAL },
    { "EXPENSIVE", MI_FLAG_EXPENSIVE },
    { "STREAM", MI_FLAG_STREAM },

    { "ENABLEOVERRIDE", MI_FLAG_ENABLEOVERRIDE },
    { "DISABLEOVERRIDE", MI_FLAG_DISABLEOVERRIDE },
    { "RESTRICTED", MI_FLAG_RESTRICTED},
    { "TOSUBCLASS", MI_FLAG_TOSUBCLASS},
    { "TOINSTANCE", MI_FLAG_TOINSTANCE},
    { "TRANSLATABLE", MI_FLAG_TRANSLATABLE},
};

static size_t _flagsSize = MI_COUNT(_flags);

static int _StrToDatetime(const char* str, MI_Datetime* result)
{
    const char* p = str;

    /* Check arguments */
    if (!str || !result)
        return -1;

    /* Datetime strings must be exactly 25 bytes long */
    if (strlen(p) != 25)
        return -1;

    if (p[21] == ':')
    {
        /* DDDDDDDDHHMMSS.MMMMMM:000 */
        MI_Uint32 dddddddd;
        MI_Uint32 hh;
        MI_Uint32 mm;
        MI_Uint32 ss;
        MI_Uint32 mmmmmm;

        if (_ParseUint32(p, 8, MI_FALSE, &dddddddd) != 0)
            return -1;
        if (_ParseUint32(p + 8, 2, MI_FALSE, &hh) != 0)
            return -1;
        if (_ParseUint32(p + 10, 2, MI_FALSE, &mm) != 0)
            return -1;
        if (_ParseUint32(p + 12, 2, MI_FALSE, &ss) != 0)
            return -1;
        if (p[14] != '.')
            return -1;
        if (_ParseUint32(p + 15, 6, MI_TRUE, &mmmmmm) != 0)
            return -1;
        if (p[22] != '0' || p[23] != '0' || p[24] != '0')
            return -1;

        /* Set the fields */
        result->u.interval.days = dddddddd;
        result->u.interval.hours = hh;
        result->u.interval.minutes = mm;
        result->u.interval.seconds = ss;
        result->u.interval.microseconds = mmmmmm;
        result->isTimestamp = 0;
    }
    else
    {
        /* Any field may be replaced with asterisks, which indicates
           a repetitive time, that is, every year on a certain day or
           every certain day of any month. For time zones, "+***"
           means use the local time zone. In this implementation, this
           is only useful for the year, month, and day fields, because
           the asterisk fields are returned as 0, which is a valid hour,
           minute, second, micorosecond and time zone ("+***" becomes
           "+000", which is UTC). If support for repetitive times
           in these fields is needed, perhaps the non time zone
           fields in MI_DateTime::u.timestamp can be made signed
           and set to -1 when asterisks are seen.
         */

        /* YYYYMMDDHHMMSS.MMMMMMSUTC */
        MI_Uint32 yyyy;
        MI_Uint32 MM;
        MI_Uint32 dd;
        MI_Uint32 hh;
        MI_Uint32 mm;
        MI_Uint32 ss;
        MI_Uint32 mmmmmm;
        MI_Uint32 s;
        MI_Uint32 utc;

        if (_ParseUint32(p, 4, MI_TRUE, &yyyy) != 0)
            return -1;
        if (_ParseUint32(p + 4, 2, MI_TRUE, &MM) != 0)
            return -1;
        if (_ParseUint32(p + 6, 2, MI_TRUE, &dd) != 0)
            return -1;
        if (_ParseUint32(p + 8, 2, MI_TRUE, &hh) != 0)
            return -1;
        if (_ParseUint32(p + 10, 2, MI_TRUE, &mm) != 0)
            return -1;
        if (_ParseUint32(p + 12, 2, MI_TRUE, &ss) != 0)
            return -1;
        if (p[14] != '.')
            return -1;
        if (_ParseUint32(p + 15, 6, MI_TRUE, &mmmmmm) != 0)
            return -1;
        s = p[21];
        if (s != '-' && s != '+')
            return -1;
        if (_ParseUint32(p + 22, 3, MI_TRUE, &utc) != 0)
            return -1;

        /* Set the result */
        result->u.timestamp.year = yyyy;
        result->u.timestamp.month = MM;
        result->u.timestamp.day = dd;
        result->u.timestamp.hour = hh;
        result->u.timestamp.minute = mm;
        result->u.timestamp.second = ss;
        result->u.timestamp.microseconds = mmmmmm;

        if (s == '-')
            result->u.timestamp.utc = -((MI_Sint16)utc);
        else
            result->u.timestamp.utc = (MI_Uint16)utc;

        result->isTimestamp = 1;
    }

    return 0;
}

static void _indent(size_t n, FILE* file)
{
    size_t i;

    for (i = 0; i < n; i++)
        fprintf(file,"    ");
}

static int _CheckRange(MI_Sint64 x, MI_Type type)
{
    static const MI_Sint64 _UINT8_MIN = 0;
    static const MI_Sint64 _UINT8_MAX = 255;
    static const MI_Sint64 _SINT8_MIN = -128;
    static const MI_Sint64 _SINT8_MAX = 127;
    static const MI_Sint64 _SINT16_MIN = -32768;
    static const MI_Sint64 _SINT16_MAX = 32767;
    static const MI_Sint64 _UINT16_MIN = 0;
    static const MI_Sint64 _UINT16_MAX = 65535;
    static const MI_Sint64 _SINT32_MIN = -2147483647-1;
    static const MI_Sint64 _SINT32_MAX = 2147483647;
    static const MI_Sint64 _UINT32_MIN = 0;
    static const MI_Sint64 _UINT32_MAX = 4294967295U;
    /* ATTN: commented out until 
    static const MI_Sint64 _SINT64_MIN = -MI_LL(9223372036854775807)- MI_LL(1);
    static const MI_Sint64 _SINT64_MAX = MI_LL(9223372036854775807);
    static const MI_Sint64 _UINT64_MIN = 0;
    static const MI_Sint64 _UINT64_MAX = MI_ULL(9223372036854775807);
    */

    switch (type)
    {
        case MI_UINT8:
        {
            if (x < _UINT8_MIN || x > _UINT8_MAX)
                goto error;
            break;
        }
        case MI_SINT8:
        {
            if (x < _SINT8_MIN || x > _SINT8_MAX)
                goto error;
            break;
        }
        case MI_UINT16:
        {
            if (x < _UINT16_MIN || x > _UINT16_MAX)
                goto error;
            break;
        }
        case MI_SINT16:
        {
            if (x < _SINT16_MIN || x > _SINT16_MAX)
                goto error;
            break;
        }
        case MI_UINT32:
        {
            if (x < _UINT32_MIN || x > _UINT32_MAX)
                goto error;
            break;
        }
        case MI_SINT32:
        {
            if (x < _SINT32_MIN || x > _SINT32_MAX)
                goto error;
            break;
        }
        case MI_UINT64:
        case MI_SINT64:
            /* since 'x' is sint64 type, it's impossible to validate 64 bit types for ranges */
            break;

        default:
            goto unexpected;
    }

    return 0;

error:
    yyerrorf(ID_INITIALIZER_OUT_OF_RANGE, 
        "initializer out of range: " SINT64_FMT, x);
    return -1;

unexpected:
    yyerrorf(ID_INTERNAL_ERROR, "internal error: %s(%u)", __FILE__, __LINE__);
    return -1;
}

/*
**==============================================================================
**
** Public definitions
**
**==============================================================================
*/

void yyerrorf(int id, const char *format, ...)
{
        char buf[1024];
        int n;
        va_list ap;
        memset(&ap, 0, sizeof(ap));

        MI_UNUSED(id);

        if (state.path)
            n = Snprintf(buf, sizeof(buf), "%s(%u): ", state.path, 
                state.line);
        else
            n = 0;

        va_start(ap, format);
        Vsnprintf(buf + n, sizeof(buf) - n, format, ap);
        va_end(ap);

        PtrArray_Append(&state.errors, MOF_Strdup(&state.heap, buf));

        if (state.errorCallback)
            (*state.errorCallback)(buf, NULL, state.errorCallbackData);
}

void yyerror(const char* msg)
{
    /* There is no way to inject a localization string identifier before
     * calling this function (it is called from generated code). So instead,
     * we map the set of known strings to identifiers below.
     */
    if (strcmp(msg, "syntax error") == 0)
    {
        yyerrorf(ID_SYNTAX_ERROR, "%s", msg);
    }
    else if (strcmp(msg, "yacc stack overflow") == 0)
    {
        yyerrorf(ID_PARSER_STACK_OVERFLOW, "%s", msg);
    }
    else
    {
        yyerrorf(ID_INTERNAL_ERROR, "%s", msg);
    }
}

void yywarnf(int id, const char *format, ...)
{
        char buf[1024];
        int n;
        va_list ap;
        memset(&ap, 0, sizeof(ap));

        MI_UNUSED(id);

        n = Snprintf(buf, sizeof(buf), "%s(%u): ", state.path, 
            state.line);
        va_start(ap, format);
        Vsnprintf(buf + n, sizeof(buf) - n, format, ap);
        va_end(ap);

        if (state.warningCallback)
            (*state.warningCallback)(buf, NULL, state.warningCallbackData);

        PtrArray_Append(&state.warnings, MOF_Strdup(&state.heap, buf));
}

static int _PromoteValue(
    MI_Uint32 sourceType,
    MI_Uint32 destType,
    void** value)
{
    MI_Uint32 i;

    /* Nothing to do if value is null */
    if (*value == NULL)
        return 0;

    /* Convert from sourceType to destType */
    switch (sourceType)
    {
        case MI_BOOLEAN:
        {
            if (destType != sourceType)
            {
                return -1;
            }

            return 0;
        }
        case MI_SINT64:
        {
            const MI_Sint64* p = *((const MI_Sint64**)value);

            switch (destType)
            {
                case MI_UINT8:
                {
                    MI_Uint8* q = MALLOC_T(MI_Uint8, 1);
                    if (q)
                    {
                        MI_Sint64 x = *p;

                        if (_CheckRange(x, MI_UINT8) != 0)
                            return -1;

                        *q = (MI_Uint8)x;
                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_SINT8:
                {
                    MI_Sint8* q = MALLOC_T(MI_Sint8, 1);
                    if (q)
                    {
                        MI_Sint64 x = *p;

                        if (_CheckRange(x, MI_SINT8) != 0)
                            return -1;

                        *q = (MI_Sint8)x;
                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_UINT16:
                {
                    MI_Uint16* q = MALLOC_T(MI_Uint16, 1);
                    if (q)
                    {
                        MI_Sint64 x = *p;

                        if (_CheckRange(x, MI_UINT16) != 0)
                            return -1;

                        *q = (MI_Uint16)x;
                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_SINT16:
                {
                    MI_Sint16* q = MALLOC_T(MI_Sint16, 1);
                    if (q)
                    {
                        MI_Sint64 x = *p;

                        if (_CheckRange(x, MI_SINT16) != 0)
                            return -1;

                        *q = (MI_Sint16)x;
                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_UINT32:
                {
                    MI_Uint32* q = MALLOC_T(MI_Uint32, 1);
                    if (q)
                    {
                        MI_Sint64 x = *p;

                        if (_CheckRange(x, MI_UINT32) != 0)
                            return -1;

                        *q = (MI_Uint32)x;
                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_SINT32:
                {
                    MI_Sint32* q = MALLOC_T(MI_Sint32, 1);
                    if (q)
                    {
                        MI_Sint64 x = *p;

                        if (_CheckRange(x, MI_SINT32) != 0)
                            return -1;

                        *q = (MI_Sint32)x;
                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_UINT64:
                {
                    MI_Uint64* q = MALLOC_T(MI_Uint64, 1);
                    if (q)
                    {
                        MI_Sint64 x = *p;

                        if (_CheckRange(x, MI_UINT64) != 0)
                            return -1;

                        *q = (MI_Uint64)x;
                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_SINT64:
                {
                    return 0;
                }
                case MI_STRING:
                {
                    char Buf[24];
                    MI_Char* q;
                    MI_Sint64 x = *p;
   
                    if (x < 0)
                    {
                        sprintf(Buf, "%ld", (long)x);
                    }
                    else
                    {
                        sprintf(Buf, "%lu", (unsigned long)x);
                    }
                    q = MALLOC_T(MI_Char, strlen(Buf) + 1);
                    if (q)
                    {
                        strcpy(q, Buf);
                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                default:
                {
                    return -1;
                }
            }
        }
        case MI_REAL64:
        {
            const MI_Real64* p = *((const MI_Real64**)value);

            switch (destType)
            {
                case MI_REAL32:
                {
                    MI_Real32* q = MALLOC_T(MI_Real32, 1);
                    if (q)
                    {
                        *q = (MI_Real32)*p;
                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_REAL64:
                {
                    return 0;
                }
                case MI_STRING:
                {
                    char Buf[MI_STRINGMAXLEN];
                    MI_Char* q;
                    MI_Real64 x = *p;
                    snprintf(Buf, MI_STRINGMAXLEN, "%g",x);
                    q = MALLOC_T(MI_Char, strlen(Buf) + 1);
                    if (q)
                    {
                        strcpy(q, Buf);
                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                default:
                {
                    return -1;
                }
            }
        }
        case MI_CHAR16:
        {
            if (destType != sourceType)
                return -1;

            return 0;
        }
        case MI_STRING:
        {
            const char* p = *((const char**)value);

            switch (destType)
            {
                case MI_STRING:
                case MI_INSTANCE:
                case MI_REFERENCE:
                {
                    return 0;
                }
                case MI_DATETIME:
                {
                    MI_Datetime* q = MALLOC_T(MI_Datetime, 1);
                    if (q)
                    {
                        if (_StrToDatetime(p, q) != 0)
                            return -1;

                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                default:
                {
                    return -1;
                }
            }
        }
        case MI_BOOLEANA:
        {
            if (destType != sourceType)
                return -1;

            return 0;
        }
        case MI_SINT64A:
        {
            const MI_Sint64A* p = *((const MI_Sint64A**)value);
            
            switch (destType)
            {
                case MI_UINT8A:
                {
                    MI_Uint8A* q;
                    NEW_ARRAY_T(q, MI_Uint8, p->size);
                    if (q)
                    {
                        for (i = 0; i < p->size; i++)
                        {
                            MI_Sint64 x = p->data[i];

                            if (_CheckRange(x, MI_UINT8) != 0)
                                return -1;

                            q->data[i] = (MI_Uint8)x;
                        }

                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_SINT8A:
                {
                    MI_Sint8A* q;
                    NEW_ARRAY_T(q, MI_Sint8, p->size);
                    if (q)
                    {
                        for (i = 0; i < p->size; i++)
                        {
                            MI_Sint64 x = p->data[i];

                            if (_CheckRange(x, MI_SINT8) != 0)
                                return -1;

                            q->data[i] = (MI_Sint8)x;
                        }

                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_UINT16A:
                {
                    MI_Uint16A* q;
                    NEW_ARRAY_T(q, MI_Uint16, p->size);
                    if (q)
                    {
                        for (i = 0; i < p->size; i++)
                        {
                            MI_Sint64 x = p->data[i];

                            if (_CheckRange(x, MI_UINT16) != 0)
                                return -1;

                            q->data[i] = (MI_Uint16)x;
                        }

                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_SINT16A:
                {
                    MI_Sint16A* q;
                    NEW_ARRAY_T(q, MI_Sint16, p->size);
                    if (q)
                    {
                        for (i = 0; i < p->size; i++)
                        {
                            MI_Sint64 x = p->data[i];

                            if (_CheckRange(x, MI_SINT16) != 0)
                                return -1;

                            q->data[i] = (MI_Sint16)x;
                        }

                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_UINT32A:
                {
                    MI_Uint32A* q;
                    NEW_ARRAY_T(q, MI_Uint32, p->size);
                    if (q)
                    {
                        for (i = 0; i < p->size; i++)
                        {
                            MI_Sint64 x = p->data[i];

                            if (_CheckRange(x, MI_UINT32) != 0)
                                return -1;

                            q->data[i] = (MI_Uint32)x;
                        }

                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_SINT32A:
                {
                    MI_Sint32A* q;
                    NEW_ARRAY_T(q, MI_Sint32, p->size);

                    if (q)
                    {
                        for (i = 0; i < p->size; i++)
                        {
                            MI_Sint64 x = p->data[i];

                            if (_CheckRange(x, MI_SINT32) != 0)
                                return -1;

                            q->data[i] = (MI_Sint32)x;
                        }
                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_UINT64A:
                {
                    MI_Uint64A* q;
                    NEW_ARRAY_T(q, MI_Uint64, p->size);
                    if (q)
                    {
                        for (i = 0; i < p->size; i++)
                        {
                            MI_Sint64 x = p->data[i];

                            if (_CheckRange(x, MI_UINT64) != 0)
                                return -1;

                            q->data[i] = (MI_Uint64)x;
                        }

                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_SINT64A:
                {
                    return 0;
                }
                case MI_STRINGA:
                {
                    char Buf[24];
                    MI_StringA* q;
                    NEW_ARRAY_T(q, MI_String, p->size);
                    if (q)
                    {
                        for (i = 0; i < p->size; i++)
                        {
                            MI_Sint64 x = p->data[i];
                            if (x < 0)
                            {
                                sprintf(Buf, "%ld", (long)x);
                            }
                            else
                            {
                                sprintf(Buf, "%lu", (unsigned long)x);
                            }
                            strcpy(q->data[i], Buf);
                        }

                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                default:
                    return -1;
            }
        }
        case MI_REAL64A:
        {
            const MI_Real64A* p = *((const MI_Real64A**)value);

            switch (destType)
            {
                case MI_REAL64A:
                {
                    return 0;
                }
                case MI_REAL32A:
                {
                    MI_Real32A* q;
                    NEW_ARRAY_T(q, MI_Real32, p->size);
                    if (q)
                    {
                        for (i = 0; i < p->size; i++)
                        {
                            q->data[i] = (MI_Real32)p->data[i];
                        }

                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                case MI_STRINGA:
                {
                    char Buf[MI_STRINGMAXLEN];
                    MI_StringA* q;
                    NEW_ARRAY_T(q, MI_String, p->size);
                    if (q)
                    {
                        for (i = 0; i < p->size; i++)
                        {
                            MI_Real64 x = p->data[i];
                            snprintf(Buf, MI_STRINGMAXLEN, "%g",x);
                            strcpy(q->data[i], Buf);
                        }

                        *value = q;
                        return 0;
                    }
                    else
                    {
                        return -1;
                    }
                }
                default:
                    return -1;
            }
        }
        case MI_CHAR16A:
        {
            if (destType != sourceType)
                return -1;

            return 0;
        }
        case MI_STRINGA:
        {
            const MI_StringA* p = *((const MI_StringA**)value);
            if(p)
            {
                switch (destType)
                {
                    case MI_STRINGA:
                    case MI_INSTANCEA:
                    case MI_REFERENCEA:
                    {
                        return 0;
                    }
                    case MI_DATETIMEA:
                    {
                        MI_DatetimeA* q;
                        NEW_ARRAY_T(q, MI_Datetime, p->size);
                        if (q)
                        {
                            for (i = 0; i < p->size; i++)
                            {
                                if (_StrToDatetime(p->data[i], &q->data[i]) != 0)
                                    return -1;
                            }

                            *value = q;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    default:
                        return -1;
                }
            }
            else
            {
                return -1;
            }
        }
        default:
            break;
    }

    return -1;
}

int InitializerToValue(
    MOF_Initializer* self,
    MI_Uint32 /*MI_Type*/ type,
    void** value)
{
    /* ATTN: this function could check integer truncation and sign errors */
    /* ATTN: handle case where ZChar is wchar_t */
    size_t i;

    /* Check arguments */
    if (!self || !value)
        return -1;

    *value = NULL;

    /* Early out for a zero-length array */
    if (self->size == 0)
        return 0;

    /* Verify that array is homogeneous (all elements have same type) */
    for (i = 1; i < self->size; i++)
    {
        if (self->data[0].type != self->data[i].type)
            return -1;
    }

    /* Verify that scalars have exactly 1 initializer */
    if (!self->isArray && self->size != 1)
        return -1;

    /* Convert to a static value */
    if (self->isArray)
    {
        switch (self->data[0].type)
        {
            case TOK_INTEGER_VALUE:
            {
                switch (type)
                {
                    case MI_UINT8A:
                    {
                        MI_Uint8A* p;
                        NEW_ARRAY_T(p, MI_Uint8, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                MI_Sint64 x = self->data[i].value.integer;
                                if (0 != _CheckRange(x, MI_UINT8))
                                    return -1;

                                p->data[i] = (MI_Uint8)x;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_SINT8A:
                    {
                        MI_Sint8A* p;
                        NEW_ARRAY_T(p, MI_Sint8, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                MI_Sint64 x = self->data[i].value.integer;
                                if (0 != _CheckRange(x, MI_SINT8))
                                    return -1;

                                p->data[i] = (MI_Sint8)x;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_UINT16A:
                    {
                        MI_Uint16A* p;
                        NEW_ARRAY_T(p, MI_Uint16, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                MI_Sint64 x = self->data[i].value.integer;
                                if (0 != _CheckRange(x, MI_UINT16))
                                    return -1;

                                p->data[i] = (MI_Uint16)x;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_SINT16A:
                    {
                        MI_Sint16A* p;
                        NEW_ARRAY_T(p, MI_Sint16, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                MI_Sint64 x = self->data[i].value.integer;
                                if (0 != _CheckRange(x, MI_SINT16))
                                    return -1;

                                p->data[i] = (MI_Sint16)x;
                            }
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_UINT32A:
                    {
                        MI_Uint32A* p;
                        NEW_ARRAY_T(p, MI_Uint32, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                MI_Sint64 x = self->data[i].value.integer;
                                if (0 != _CheckRange(x, MI_UINT32))
                                    return -1;

                                p->data[i] = (MI_Uint32)x;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_SINT32A:
                    {
                        MI_Sint32A* p;
                        NEW_ARRAY_T(p, MI_Sint32, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                MI_Sint64 x = self->data[i].value.integer;
                                if (0 != _CheckRange(x, MI_SINT32))
                                    return -1;

                                p->data[i] = (MI_Sint32)x;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_UINT64A:
                    {
                        MI_Uint64A* p;
                        NEW_ARRAY_T(p, MI_Uint64, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                MI_Sint64 x = self->data[i].value.integer;
                                if (0 != _CheckRange(x, MI_UINT64))
                                    return -1;

                                p->data[i] = (MI_Uint64)x;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_SINT64A:
                    {
                        MI_Sint64A* p;
                        NEW_ARRAY_T(p, MI_Sint64, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                MI_Sint64 x = self->data[i].value.integer;
                                if (0 != _CheckRange(x, MI_SINT64))
                                    return -1;

                                p->data[i] = (MI_Sint64)x;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_STRINGA:
                    {
                        char Buf[24];
                        MI_StringA* p;
                        NEW_ARRAY_T(p, MI_String, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                if (self->data->value.integer < 0)
                                {
                                    sprintf(Buf, "%ld", (long)self->data->value.integer);
                                }
                                else
                                {
                                    sprintf(Buf, "%lu", (unsigned long)self->data->value.integer);
                                }
                                p->data[i] = MALLOC_T(MI_Char, strlen(Buf) + 1);
                                strcpy(p->data[i], Buf);
                            }
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    default:
                        return -1;
                }
            }
            case TOK_REAL_VALUE:
            {
                switch (type)
                {
                    case MI_REAL32A:
                    {
                        MI_Real32A* p;
                        NEW_ARRAY_T(p, MI_Real32, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                p->data[i] = (MI_Real32)self->data[i].value.real;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_REAL64A:
                    {
                        MI_Real64A* p;
                        NEW_ARRAY_T(p, MI_Real64, self->size);
                        if (p)
                        {

                            for (i = 0; i < self->size; i++)
                            {
                                p->data[i] = (MI_Real64)
                                    self->data[i].value.real;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_STRINGA:
                    {
                        char Buf[MI_STRINGMAXLEN];
                        MI_StringA* p;
                        NEW_ARRAY_T(p, MI_String, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                snprintf(Buf, MI_STRINGMAXLEN, "%g",self->data->value.real);
                                p->data[i] = MALLOC_T(MI_Char, strlen(Buf) + 1);
                                strcpy(p->data[i], Buf);
                            }
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    default:
                        return -1;
                }
                break;
            }
            case TOK_CHAR_VALUE:
            {
                switch (type)
                {
                    case MI_CHAR16A:
                    {
                        MI_Char16A* p;
                        NEW_ARRAY_T(p, MI_Char16, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                p->data[i] = (MI_Char16)self->data[i].value.character;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    default:
                        return -1;
                }
                break;
            }
            case TOK_STRING_VALUE:
            {
                switch (type)
                {
                    case MI_STRINGA:
                    {
                        MI_StringA* p;
                        NEW_ARRAY_T(p, MI_String, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                p->data[i] = self->data[i].value.string;
                                self->data[i].value.string = NULL;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_DATETIMEA:
                    {
                        MI_DatetimeA* p;
                        NEW_ARRAY_T(p, MI_Datetime, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                if (_StrToDatetime(self->data[i].value.string,
                                    &p->data[i]) != 0)
                                {
                                    MOF_Free(&state.heap, p);
                                    return -1;
                                }

                                MOF_Free(&state.heap, self->data[i].value.string);
                                self->data[i].value.string = NULL;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    default:
                        return -1;
                }
                break;
            }
            case TOK_BOOLEAN_VALUE:
            {
                switch (type)
                {
                    case MI_BOOLEANA:
                    {
                        MI_BooleanA* p;
                        NEW_ARRAY_T(p, MI_Boolean, self->size);
                        if (p)
                        {
                            for (i = 0; i < self->size; i++)
                            {
                                p->data[i] = (MI_Boolean)
                                    self->data[i].value.boolean;
                            }

                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    default:
                        return -1;
                }
            }
            case TOK_INSTANCE:
            case TOK_NULL:
            {
                *value = NULL;
                return 0;
            }
            default:
                return -1;
        }
    }
    else
    {
        switch (self->data->type)
        {
            case TOK_INTEGER_VALUE:
            {
                switch (type)
                {
                    case MI_UINT8:
                    {
                        MI_Uint8* p = MALLOC_T(MI_Uint8, 1);
                        if (p)
                        {
                            MI_Sint64 x = self->data->value.integer;
                            if (0 != _CheckRange(x, MI_UINT8))
                                return -1;

                            *p = (MI_Uint8)x;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_SINT8:
                    {
                        MI_Sint8* p = MALLOC_T(MI_Sint8, 1);
                        if (p)
                        {
                            MI_Sint64 x = self->data->value.integer;
                            if (0 != _CheckRange(x, MI_SINT8))
                                return -1;

                            *p = (MI_Sint8)x;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_UINT16:
                    {
                        MI_Uint16* p = MALLOC_T(MI_Uint16, 1);
                        if (p)
                        {
                            MI_Sint64 x = self->data->value.integer;
                            if (0 != _CheckRange(x, MI_UINT16))
                                return -1;

                            *p = (MI_Uint16)x;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_SINT16:
                    {
                        MI_Sint16* p = MALLOC_T(MI_Sint16, 1);
                        if (p)
                        {
                            MI_Sint64 x = self->data->value.integer;
                            if (0 != _CheckRange(x, MI_SINT16))
                                return -1;

                            *p = (MI_Sint16)x;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_UINT32:
                    {
                        MI_Uint32* p = MALLOC_T(MI_Uint32, 1);
                        if (p)
                        {
                            MI_Sint64 x = self->data->value.integer;
                            if (0 != _CheckRange(x, MI_UINT32))
                                return -1;

                            *p = (MI_Uint32)x;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_SINT32:
                    {
                        MI_Sint32* p = MALLOC_T(MI_Sint32, 1);
                        if (p)
                        {
                            MI_Sint64 x = self->data->value.integer;
                            if (0 != _CheckRange(x, MI_SINT32))
                                return -1;

                            *p = (MI_Sint32)x;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_UINT64:
                    {
                        MI_Uint64* p = MALLOC_T(MI_Uint64, 1);
                        if (p)
                        {
                            MI_Sint64 x = self->data->value.integer;
                            if (0 != _CheckRange(x, MI_UINT64))
                                return -1;

                            *p = (MI_Uint64)x;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_SINT64:
                    {
                        MI_Sint64* p = MALLOC_T(MI_Sint64, 1);
                        if (p)
                        {
                            MI_Sint64 x = self->data->value.integer;
                            if (0 != _CheckRange(x, MI_SINT64))
                                return -1;

                            *p = (MI_Sint64)x;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_STRING:
                    {
                        char Buf[24];
                        MI_Char* p;
                        if (self->data->value.integer < 0)
                        {
                            sprintf(Buf, "%ld", (long)self->data->value.integer);
                        }
                        else
                        {
                            sprintf(Buf, "%lu", (unsigned long)self->data->value.integer);
                        }
                        p = MALLOC_T(MI_Char, strlen(Buf) + 1);
                        if (p)
                        {
                            strcpy(p, Buf);
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    default:
                        return -1;
                }
                break;
            }
            case TOK_REAL_VALUE:
            {
                switch (type)
                {
                    case MI_REAL32:
                    {
                        MI_Real32* p = MALLOC_T(MI_Real32, 1);
                        if (p)
                        {
                            *p = (MI_Real32)self->data->value.real;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_REAL64:
                    {
                        MI_Real64* p = MALLOC_T(MI_Real64, 1);
                        if (p)
                        {
                            *p = (MI_Real64)self->data->value.real;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_STRING:
                    {
                        char Buf[MI_STRINGMAXLEN];
                        MI_Char* p;
                        snprintf(Buf, MI_STRINGMAXLEN, "%g",self->data->value.real);
                        p = MALLOC_T(MI_Char, strlen(Buf) + 1);
                        if (p)
                        {
                            strcpy(p, Buf);
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    default:
                        return -1;
                }
                break;
            }
            case TOK_CHAR_VALUE:
            {
                switch (type)
                {
                    case MI_CHAR16:
                    {
                        MI_Char16* p = MALLOC_T(MI_Char16, 1);
                        if (p)
                        {
                            *p = (MI_Char16)self->data->value.character;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    default:
                        return -1;
                }
                break;
            }
            case TOK_STRING_VALUE:
            {
                switch (type)
                {
                    case MI_STRING:
                    {
                        char *p;
                        p = self->data->value.string;
                        if (p)
                        {
                            self->data->value.string = NULL;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    case MI_DATETIME:
                    {
                        MI_Datetime *p = MALLOC_T(MI_Datetime, 1);

                        if (p)
                        {
                            if (_StrToDatetime(self->data->value.string, p) != 0)
                            {
                                MOF_Free(&state.heap, p);
                                return -1;
                            }

                            MOF_Free(&state.heap, self->data->value.string);
                            self->data->value.string = NULL;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    default:
                        return -1;
                }
                break;
            }
            case TOK_BOOLEAN_VALUE:
            {
                switch (type)
                {
                    case MI_BOOLEAN:
                    {
                        MI_Boolean* p = MALLOC_T(MI_Boolean, 1);
                        if (p)
                        {
                            *p = (MI_Boolean)self->data->value.boolean;
                            *value = p;
                            return 0;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    default:
                        return -1;
                }
                break;
            }
            case TOK_INSTANCE:
            case TOK_NULL:
            {
                *value = NULL;
                return 0;
            }
            default:
                return -1;
        }
    }

    UNREACHABLE_RETURN( return 0; )
}
void ReleaseInitializer(
    MOF_Initializer* init)
{
    if (init)
    {
        if (init->data)
        {
            size_t i;

            for (i = 0; i < init->size; i++)
            {
                if (init->data[i].type == TOK_STRING_VALUE)
                    MOF_Free(&state.heap, init->data[i].value.string);
            }

            MOF_Free(&state.heap, init->data);
        }
    }
}

static void _PrintFlags(MI_Uint32 flags, size_t level, FILE* file)
{
    size_t i;

    _indent(level, file);
    fprintf(file,"flags:");

    for (i = 0; i < _flagsSize; i++)
    {
        if (_flags[i].flag & flags)
            fprintf(file," %s", scs(_flags[i].name));
    }

    fprintf(file,"\n");
}

void MOF_PrintQualifierDecl(
    const MI_QualifierDecl* self, 
    FILE* file)
{
    size_t level = 0;

    /* Header */
    _indent(level, file);
    fprintf(file,"MI_QualifierDecl\n");
    _indent(level, file);
    fprintf(file,"{\n");
    level++;

    /* name  */
    _indent(level, file);
    fprintf(file,"name: %s\n", scs(self->name));

    /* type */
    _indent(level, file);
    fprintf(file,"type: %s\n", _getTypeName(self->type));

    /* scope */
    {
        _indent(level, file);
        fprintf(file,"scope:");

        if (self->flavor == MI_FLAG_ANY)
            fprintf(file,"ANY\n");
        else
        {
            if (self->scope & MI_FLAG_ASSOCIATION)
                fprintf(file," ASSOCIATION");
            if (self->scope & MI_FLAG_CLASS)
                fprintf(file," CLASS");
            if (self->scope & MI_FLAG_INDICATION)
                fprintf(file," INDICATION");
            if (self->scope & MI_FLAG_METHOD)
                fprintf(file," METHOD");
            if (self->scope & MI_FLAG_PARAMETER)
                fprintf(file," PARAMETER");
            if (self->scope & MI_FLAG_PROPERTY)
                fprintf(file," PROPERTY");
            if (self->scope & MI_FLAG_REFERENCE)
                fprintf(file," REFERENCE");

            fprintf(file,"\n");
        }
    }

    /* subscript */

    _indent(level, file);
    fprintf(file,"subscript: %u\n", self->subscript);

    /* flavor */
    {
        _indent(level, file);
        fprintf(file,"flavor:");

        if (self->flavor & MI_FLAG_ENABLEOVERRIDE)
            fprintf(file," ENABLEOVERRIDE");
        if (self->flavor & MI_FLAG_DISABLEOVERRIDE)
            fprintf(file," DISABLEOVERRIDE");
        if (self->flavor & MI_FLAG_RESTRICTED)
            fprintf(file," RESTRICTED");
        if (self->flavor & MI_FLAG_TOSUBCLASS)
            fprintf(file," TOSUBCLASS");
        if (self->flavor & MI_FLAG_TOINSTANCE)
            fprintf(file," TOINSTANCE");
        if (self->flavor & MI_FLAG_TRANSLATABLE)
            fprintf(file," TRANSLATABLE");

        fprintf(file,"\n");
    }

    /* value */
    _indent(level, file);
    fprintf(file,"value: ");
    PrintValue(self->value, self->type, file);
    fprintf(file,"\n");

    level--;
    _indent(level, file);
    fprintf(file,"}\n");
}

static void _DatetimeToStr(const MI_Datetime* x, _Pre_writable_size_(26) char buf[26])
{
    if (x->isTimestamp)
    {
        const ZChar FMT[] =  "%04d%02d%02d%02d%02d%02d.%06d%c%03d";
        MI_Sint32 utc = x->u.timestamp.utc;
        Snprintf(buf, 26, FMT,
            x->u.timestamp.year,
            x->u.timestamp.month,
            x->u.timestamp.day,
            x->u.timestamp.hour,
            x->u.timestamp.minute,
            x->u.timestamp.second,
            x->u.timestamp.microseconds,
            utc < 0 ? '-' : '+',
            utc < 0 ? -utc : utc);
    }
    else
    {
        const ZChar FMT[] = "%08u%02u%02u%02u.%06u:000";
        Snprintf(buf, 26, FMT,
            x->u.interval.days,
            x->u.interval.hours,
            x->u.interval.minutes,
            x->u.interval.seconds,
            x->u.interval.microseconds);
    }
}

void PrintValue(const void* value, MI_Type type, FILE* file)
{
    if (!value) 
    {
        fprintf(file,"NULL");
        return;
    }
    else 
    {
        switch (type)
        {
            case MI_BOOLEAN:
            {
                const MI_Boolean* p = (const MI_Boolean*)value;
                fprintf(file,"%s", *p ? "true" : "false");
                break;
            }
            case MI_SINT8:
            {
                fprintf(file,"%d", *((const MI_Sint8*)value));
                break;
            }
            case MI_UINT8:
            {
                fprintf(file,"%u", *((const MI_Uint8*)value));
                break;
            }
            case MI_SINT16:
            {
                fprintf(file,"%d", *((const MI_Sint16*)value));
                break;
            }
            case MI_UINT16:
            {
                fprintf(file,"%u", *((const MI_Uint16*)value));
                break;
            }
            case MI_SINT32:
            {
                fprintf(file,"%d", *((const MI_Sint32*)value));
                break;
            }
            case MI_UINT32:
            {
                fprintf(file,"%u", *((const MI_Uint32*)value));
                break;
            }
            case MI_SINT64:
            {
                fprintf(file, SINT64_FMT, *((const MI_Sint64*)value));
                break;
            }
            case MI_UINT64:
            {
                fprintf(file, UINT64_FMT, *((const MI_Uint64*)value));
                break;
            }
            case MI_REAL32:
            {
                fprintf(file,"%g", *((const MI_Real32*)value));
                break;
            }
            case MI_REAL64:
            {
                fprintf(file,"%g", *((const MI_Real64*)value));
                break;
            }
            case MI_CHAR16:
            {
                fprintf(file,"%u", *((const MI_Char16*)value));
                break;
            }
            case MI_DATETIME:
            {
                char buf[26];
                _DatetimeToStr((const MI_Datetime*)value, buf);
                fprintf(file, "%s", buf);
                break;
            }
            case MI_STRING:
            {
                fprintf(file,"%s", scs(((const char*)value)));
                break;
            }
            case MI_BOOLEANA:
            case MI_SINT8A:
            case MI_UINT8A:
            case MI_SINT16A:
            case MI_UINT16A:
            case MI_SINT32A:
            case MI_UINT32A:
            case MI_SINT64A:
            case MI_UINT64A:
            case MI_REAL32A:
            case MI_REAL64A:
            case MI_CHAR16A:
            case MI_DATETIMEA:
            {
                MI_BooleanA* arr = (MI_BooleanA*)value;
                char* ptr = (char*)arr->data;
                MI_Uint32 i;

                fprintf(file,"{");

                for (i = 0; i < arr->size; i++)
                {
                    MI_Type stype = type & ~MI_ARRAY_BIT;
                    PrintValue(ptr, stype, file);
#ifdef _PREFAST_
    #pragma prefast (push)
    #pragma prefast (disable: 26014)
#endif          
                    ptr += _typeSizes[stype];
#ifdef _PREFAST_
        #pragma prefast (pop)
#endif          

                    if (i + 1 != arr->size)
                        fprintf(file,", ");
                }
                fprintf(file,"}");
                break;
            }
            case MI_STRINGA:
            {
                MI_StringA* arr = (MI_StringA*)value;
                MI_Uint32 i;

                fprintf(file,"{");

                for (i = 0; i < arr->size; i++)
                {
                    fprintf(file,"%s", scs(arr->data[i]));

                    if (i + 1 != arr->size)
                        fprintf(file,", ");
                }

                fprintf(file,"}");
                break;
            }
            default:
                break;
        }
    }
}

const MI_QualifierDecl* FindQualifierDeclaration(const char* name)
{
    size_t i;

    for (i = 0; i < state.qualifierDecls.size; i++)
    {
        if (Strcasecmp(state.qualifierDecls.data[i]->name, name) == 0)
            return state.qualifierDecls.data[i];
    }

    /* Not found */
    return NULL;
}

int AddQualifierDeclaration(MI_QualifierDecl* qd)
{
    if (FindQualifierDeclaration(qd->name))
    {
        yyerrorf(ID_QUALIFIER_ALREADY_DECLARED, 
            "qualifier already declared: \"%s\"", 
            scs(qd->name));
        return -1;
    }

    /* Validate some qualifiers */
    if (Strcasecmp(qd->name, "MaxValue") == 0 && qd->type != MI_SINT64)
    {
        yyerrorf(ID_WRONG_TYPE_FOR_QUALIFIER, 
            "wrong type for standard %s qualifier", "MaxValue");
        return -1;
    }
    else if (Strcasecmp(qd->name, "MinValue") == 0 && qd->type != MI_SINT64)
    {
        yyerrorf(ID_WRONG_TYPE_FOR_QUALIFIER, 
            "wrong type for standard %s qualifier", "MinValue");
        return -1;
    }
    else if (Strcasecmp(qd->name, "MinLen") == 0 && qd->type != MI_UINT32)
    {
        yyerrorf(ID_WRONG_TYPE_FOR_QUALIFIER, 
            "wrong type for standard %s qualifier", "MinLen");
        return -1;
    }
    else if (Strcasecmp(qd->name, "MaxLen") == 0 && qd->type != MI_UINT32)
    {
        yyerrorf(ID_WRONG_TYPE_FOR_QUALIFIER, 
            "wrong type for standard %s qualifier", "MaxLen");
        return -1;
    }

    /* Add the declaration */
    PtrArray_Append((PtrArray*)&state.qualifierDecls, qd);
    return 0;
}

const MI_ClassDecl* FindClassDecl(const char* name)
{
    size_t i;

    for (i = 0; i < state.classDecls.size; i++)
    {
        if (Strcasecmp(state.classDecls.data[i]->name, name) == 0)
            return state.classDecls.data[i];
    }

    /* Not found */
    return NULL;
}

int AddClassDecl(MI_ClassDecl* qd)
{
    if (FindClassDecl(qd->name))
    {
        yyerrorf(ID_CLASS_ALREADY_DEFINED, "class already declared: \"%s\"", 
            scs(qd->name));
        return -1;
    }

    /* Add the declaration */
    PtrArray_Append((PtrArray*)&state.classDecls, qd);
    return 0;
}

void PrintQualifier(const MI_Qualifier* self, size_t level, FILE* file)
{
    if (!self)
        return;

    /* Header */
    _indent(level, file);
    fprintf(file,"MI_Qualifier\n");
    _indent(level, file);
    fprintf(file,"{\n");
    level++;

    /* name  */
    _indent(level, file);
    fprintf(file,"name: %s\n", scs(self->name));

    /* type */
    _indent(level, file);
    fprintf(file,"type: %s\n", _getTypeName(self->type));

    /* flavor */

    _indent(level, file);
    fprintf(file,"flavor:");

    if (self->flavor & MI_FLAG_ENABLEOVERRIDE)
        fprintf(file," ENABLEOVERRIDE");
    if (self->flavor & MI_FLAG_DISABLEOVERRIDE)
        fprintf(file," DISABLEOVERRIDE");
    if (self->flavor & MI_FLAG_RESTRICTED)
        fprintf(file," RESTRICTED");
    if (self->flavor & MI_FLAG_TOSUBCLASS)
        fprintf(file," TOSUBCLASS");
    if (self->flavor & MI_FLAG_TOINSTANCE)
        fprintf(file," TOINSTANCE");
    if (self->flavor & MI_FLAG_TRANSLATABLE)
        fprintf(file," TRANSLATABLE");

    fprintf(file,"\n");

    /* value */
    _indent(level, file);
    fprintf(file,"value: ");
    PrintValue(self->value, self->type, file);
    fprintf(file,"\n");

    /* Footer */
    level--;
    _indent(level, file);
    fprintf(file,"}\n");
}

static void _PrintQualifiers(
    MI_Qualifier** qualifiers, 
    size_t numQualifiers,
    size_t level, 
    FILE* file)
{
    size_t i;

    _indent(level, file);
    fprintf(file,"qualifiers\n");
    _indent(level, file);
    fprintf(file,"{\n");
    level++;

    for (i = 0; i < numQualifiers; i++)
        PrintQualifier(qualifiers[i], level, file);

    level--;
    _indent(level, file);
    fprintf(file,"}\n");
}

void PrintParameter(const MI_ParameterDecl* self, size_t level, FILE* file)
{
    if (!self)
        return;

    _indent(level, file);
    fprintf(file,"MI_ParameterDecl\n");
    _indent(level, file);
    fprintf(file,"{\n");
    level++;

    /* flags */
    _PrintFlags(self->flags, level, file);

    /* name  */
    _indent(level, file);
    fprintf(file,"name: %s\n", scs(self->name));

    /* type */
    _indent(level, file);
    fprintf(file,"type: %s\n", _getTypeName(self->type));

    /* className */
    if (self->className)
    {
        _indent(level, file);
        fprintf(file,"className: %s\n", scs(self->className));
    }

    /* subscript */
    _indent(level, file);
    fprintf(file,"subscript: %u\n", self->subscript);

    /* offset */
    _indent(level, file);
    fprintf(file,"offset: %u\n", self->offset);

    /* qualifiers */
    if (self->qualifiers)
        _PrintQualifiers(self->qualifiers, self->numQualifiers, level, file);

    level--;
    _indent(level, file);
    fprintf(file,"}\n");
}

static void _PrintParameters(
    MI_ParameterDecl** parameters, 
    size_t numParameters,
    size_t level, 
    FILE* file)
{
    size_t i;

    _indent(level, file);
    fprintf(file,"parameters\n");
    _indent(level, file);
    fprintf(file,"{\n");
    level++;

    for (i = 0; i < numParameters; i++)
        PrintParameter(parameters[i], level, file);

    level--;
    _indent(level, file);
    fprintf(file,"}\n");
}

void PrintProperty(const MI_PropertyDecl* self, size_t level, FILE* file)
{
    if (!self)
        return;

    _indent(level, file);
    fprintf(file,"MI_PropertyDecl\n");
    _indent(level, file);
    fprintf(file,"{\n");
    level++;

    /* flags */
    _PrintFlags(self->flags, level, file);

    /* name  */
    _indent(level, file);
    fprintf(file,"name: %s\n", scs(self->name));

    /* type */
    _indent(level, file);
    fprintf(file,"type: %s\n", _getTypeName(self->type));

    /* subscript */
    _indent(level, file);
    fprintf(file,"subscript: %u\n", self->subscript);

    /* className */
    if (self->className)
    {
        _indent(level, file);
        fprintf(file,"className: %s\n", scs(self->className));
    }

    /* offset */
    _indent(level, file);
    fprintf(file,"offset: %u\n", self->offset);

    /* qualifiers */
    if (self->qualifiers)
        _PrintQualifiers(self->qualifiers, self->numQualifiers, level, file);

    /* origin */
    if (self->origin)
    {
        _indent(level, file);
        fprintf(file,"origin: %s\n", scs(self->origin));
    }

    /* propagator */
    if (self->propagator)
    {
        _indent(level, file);
        fprintf(file,"propagator: %s\n", scs(self->propagator));
    }

    /* value */
    _indent(level, file);
    fprintf(file,"value: ");
    PrintValue(self->value, self->type, file);
    fprintf(file,"\n");

    level--;
    _indent(level, file);
    fprintf(file,"}\n");
}

static void _PrintProperties(
    MI_PropertyDecl** properties, 
    size_t numProperties,
    size_t level, 
    FILE* file)
{
    size_t i;

    _indent(level, file);
    fprintf(file,"properties\n");
    _indent(level, file);
    fprintf(file,"{\n");
    level++;

    for (i = 0; i < numProperties; i++)
        PrintProperty(properties[i], level, file);

    level--;
    _indent(level, file);
    fprintf(file,"}\n");
}

void PrintMethod(const MI_MethodDecl* self, size_t level, FILE* file)
{
    /*flags:name:type:size:parameters:qualifiers:origin:propagator*/

    if (!self)
        return;

    _indent(level, file);
    fprintf(file,"MI_MethodDecl\n");
    _indent(level, file);
    fprintf(file,"{\n");
    level++;

    /* flags */
    _PrintFlags(self->flags, level, file);

    /* name  */
    _indent(level, file);
    fprintf(file,"name: %s\n", scs(self->name));

    /* size */
    _indent(level, file);
    fprintf(file,"size: %u\n", self->size);

    /* parameters */
    if (self->parameters)
        _PrintParameters(self->parameters, self->numParameters, level, file);

    /* origin */
    if (self->origin)
    {
        _indent(level, file);
        fprintf(file,"origin: %s\n", scs(self->origin));
    }

    /* propagator */
    if (self->propagator)
    {
        _indent(level, file);
        fprintf(file,"propagator: %s\n", scs(self->propagator));
    }

    level--;
    _indent(level, file);
    fprintf(file,"}\n");
}

static void _PrintMethods(
    MI_MethodDecl** methods, 
    size_t numMethods,
    size_t level, 
    FILE* file)
{
    size_t i;

    _indent(level, file);
    fprintf(file,"methods\n");
    _indent(level, file);
    fprintf(file,"{\n");
    level++;

    for (i = 0; i < numMethods; i++)
        PrintMethod(methods[i], level, file);

    level--;
    _indent(level, file);
    fprintf(file,"}\n");
}

MI_PropertyDecl* FindProperty(
    MOF_PropertyList* self,
    const char* name)
{
    MI_Uint32 i;

    if (!self)
        return NULL;

    for (i = 0; i < self->size; i++)
    {
        if (Strcasecmp(self->data[i]->name, name) == 0)
            return self->data[i];
    }

    /* Not found */
    return NULL;
}

MI_ParameterDecl* FindParameter(
    MOF_ParameterList* self,
    const char* name)
{
    size_t i;

    if (!self)
        return NULL;

    for (i = 0; i < self->size; i++)
    {
        if (Strcasecmp(self->data[i]->name, name) == 0)
            return self->data[i];
    }

    /* Not found */
    return NULL;
}

MI_MethodDecl* FindMethod(
    MOF_MethodList* self,
    const char* name)
{
    size_t i;

    if (!self)
        return NULL;

    for (i = 0; i < self->size; i++)
    {
        if (Strcasecmp(self->data[i]->name, name) == 0)
            return self->data[i];
    }

    /* Not found */
    return NULL;
}

void MOF_PrintClassDecl(
    const MI_ClassDecl* self,
    FILE* file)
{
    size_t level = 0;

    if (!self)
        return;

    /* Header */
    _indent(level, file);
    fprintf(file,"MI_ClassDecl\n");
    _indent(level, file);
    fprintf(file,"{\n");
    level++;

    /* flags */
    _PrintFlags(self->flags, level, file);

    /* name  */
    _indent(level, file);
    fprintf(file,"name: %s\n", scs(self->name));

    /* superClass  */
    _indent(level, file);
    fprintf(file,"superClass: %s\n", scs(self->superClass));

    /* size */
    _indent(level, file);
    fprintf(file,"size: %u\n", self->size);

    /* properties */
    if (self->properties)
        _PrintProperties(self->properties, self->numProperties, level, file);

    /* methods */
    if (self->methods)
        _PrintMethods(self->methods, self->numMethods, level, file);

    /* qualifiers */
    if (self->qualifiers)
        _PrintQualifiers(self->qualifiers, self->numQualifiers, level, file);

    /* Footer */
    level--;
    _indent(level, file);
    fprintf(file,"}\n");
}

void MOF_PrintInstanceDecl(
    const MI_InstanceDecl* self,
    FILE* file)
{
    size_t level = 0;

    if (!self)
        return;

    /* Header */
    _indent(level, file);
    fprintf(file,"MI_InstanceDecl\n");
    _indent(level, file);
    fprintf(file,"{\n");
    level++;

    /* flags */
    _PrintFlags(self->flags, level, file);

    /* name  */
    _indent(level, file);
    fprintf(file,"name: %s\n", scs(self->name));

    /* size */
    _indent(level, file);
    fprintf(file,"size: %u\n", self->size);

    /* properties */
    if (self->properties)
        _PrintProperties((MI_PropertyDecl**)self->properties, (size_t)self->numProperties, level, file);

    /* qualifiers */
    if (self->qualifiers)
        _PrintQualifiers((MI_Qualifier**)self->qualifiers, (size_t)self->numQualifiers, level, file);

    /* Footer */
    level--;
    _indent(level, file);
    fprintf(file,"}\n");
}

MI_Uint32 GetQualFlags(
    MI_Qualifier** qualifiers,
    size_t numQualifiers)
{
    MI_Uint32 flags = 0;
    size_t i;

    if (!qualifiers)
        return 0;

    for (i = 0; i < numQualifiers; i++)
    {
        const MI_Qualifier* q = qualifiers[i];

        if (q->type == MI_BOOLEAN)
        {
            size_t j;

            for (j = 0; j < _flagsSize; j++)
            {
                if (Strcasecmp(q->name, _flags[j].name) == 0)
                {
                    MI_Boolean* p = (MI_Boolean*)q->value;

                    if (p && *p)
                        flags |= _flags[j].flag;
                }
            }
        }

        if (q->type == MI_STRING &&
            Strcasecmp(q->name, "EmbeddedInstance") == 0)
        {
            MOF_EmbeddedInstance* p;

            /* Create line-address pair */
            {
                p = CALLOC_T(MOF_EmbeddedInstance, 1);

                if (!p)
                {
                    yyerrorf(ID_OUT_OF_MEMORY, "out of memory");
                    return 0;
                }

                p->qualifier = (void*)q;
                p->line = state.line;
            }

            /* Append to 'lines' list */
            if (PtrArray_Append(
                (PtrArray*)(void*)&state.embeddedInstanceList, p) != 0)
            {
                yyerrorf(ID_OUT_OF_MEMORY, "out of memory");
                return 0;
            }
        }
    }

    return flags;
}

void* NewTrueValue()
{
    MI_Boolean* p = (MI_Boolean*)MOF_Malloc(&state.heap, sizeof(MI_Boolean));

    if (!p)
        return NULL;

    *p = 1;
    return p;
}

static MI_Uint32 _FindPropertyDecl(
    MOF_PropertyList* self,
    const char* name)
{
    MI_Uint32 i;

    for (i = 0; i < self->size; i++)
    {
        if (Strcasecmp(self->data[i]->name, name) == 0)
            return i;
    }

    /* Not found! */
    return MOF_NOT_FOUND;
}

static MI_Uint32 _FindMethodDecl(
    MOF_MethodList* self,
    const char* name)
{
    MI_Uint32 i;

    for (i = 0; i < self->size; i++)
    {
        if (Strcasecmp(self->data[i]->name, name) == 0)
            return i;
    }

    /* Not found! */
    return MOF_NOT_FOUND;
}

MI_Uint32 _FindQualifierPos(
    MOF_QualifierList* self,
    const char* name)
{
    MI_Uint32 i;

    for (i = 0; i < self->size; i++)
    {
        if (Strcasecmp(self->data[i]->name, name) == 0)
            return i;
    }

    /* Not found! */
    return MOF_NOT_FOUND;
}

MI_Qualifier* FindQualifier(
    MOF_QualifierList* self, 
    const char* name)
{
    size_t i;

    if (!self)
        return NULL;

    for (i = 0; i < self->size; i++)
    {
        if (Strcasecmp(self->data[i]->name, name) == 0)
            return self->data[i];
    }

    /* Not found! */
    return NULL;
}

/*
**==============================================================================
**
** Identical
**
**     Compares two values to determine whether they are identical. Returns
**     a non-zero value if they are identical.
**
**==============================================================================
*/
MI_Boolean Identical(const void* v1, const void* v2, MI_Type type)
{
    if (v1 == NULL && v2 == NULL)
        return 1;

    if (v1  == NULL && v2 != NULL)
        return 0;

    if (v1 != NULL && v2 == NULL)
        return 0;

    switch (type)
    {
        case MI_BOOLEAN:
            return *((MI_Boolean*)v1) == *((MI_Boolean*)v2);
        case MI_UINT8:
            return *((MI_Uint8*)v1) == *((MI_Uint8*)v2);
        case MI_SINT8:
            return *((MI_Sint8*)v1) == *((MI_Sint8*)v2);
        case MI_UINT16:
            return *((MI_Uint16*)v1) == *((MI_Uint16*)v2);
        case MI_SINT16:
            return *((MI_Sint16*)v1) == *((MI_Sint16*)v2);
        case MI_UINT32:
            return *((MI_Uint32*)v1) == *((MI_Uint32*)v2);
        case MI_SINT32:
            return *((MI_Sint32*)v1) == *((MI_Sint32*)v2);
        case MI_UINT64:
            return *((MI_Uint64*)v1) == *((MI_Uint64*)v2);
        case MI_SINT64:
            return *((MI_Sint64*)v1) == *((MI_Sint64*)v2);
        case MI_REAL32:
            return *((MI_Real32*)v1) == *((MI_Real32*)v2);
        case MI_REAL64:
            return *((MI_Real64*)v1) == *((MI_Real64*)v2);
        case MI_CHAR16:
            return *((MI_Char16*)v1) == *((MI_Char16*)v2);
        case MI_DATETIME:
            return memcmp((MI_Datetime*)v1, (MI_Datetime*)v2, 
                sizeof(MI_Datetime)) == 0;
        case MI_STRING:
            return strcmp((char*)v1, (char*)v2) == 0;
        case MI_BOOLEANA:
        case MI_UINT8A:
        case MI_SINT8A:
        case MI_UINT16A:
        case MI_SINT16A:
        case MI_UINT32A:
        case MI_SINT32A:
        case MI_UINT64A:
        case MI_SINT64A:
        case MI_CHAR16A:
        case MI_DATETIMEA:
        {
            MI_BooleanA* a1 = (MI_BooleanA*)v1;
            MI_BooleanA* a2 = (MI_BooleanA*)v2;
#ifdef _PREFAST_
    #pragma prefast (push)
    #pragma prefast (disable: 26014)
#endif          
            MI_Uint32 elementSize = (MI_Uint32)_typeSizes[type & ~MI_ARRAY_BIT];
#ifdef _PREFAST_
    #pragma prefast (pop)
#endif          

            if (a1->size != a2->size)
                return 0;

            if (memcmp(a1->data, a2->data, a1->size * elementSize) != 0)
                return 0;

            return 1;
        }
        case MI_REAL32A:
        {
            MI_Real32A* a1 = (MI_Real32A*)v1;
            MI_Real32A* a2 = (MI_Real32A*)v2;
            MI_Uint32 i;

            if (a1->size != a2->size)
                return 0;

            for (i = 0; i < a1->size; i++)
            {
                if (a1->data[i] != a2->data[i])
                    return 0;
            }

            return 1;
        }
        case MI_REAL64A:
        {
            MI_Real64A* a1 = (MI_Real64A*)v1;
            MI_Real64A* a2 = (MI_Real64A*)v2;
            MI_Uint32 i;

            if (a1->size != a2->size)
                return 0;

            for (i = 0; i < a1->size; i++)
            {
                if (a1->data[i] != a2->data[i])
                    return 0;
            }

            return 1;
        }
        case MI_STRINGA:
        {
            MI_StringA* a1 = (MI_StringA*)v1;
            MI_StringA* a2 = (MI_StringA*)v2;
            MI_Uint32 i;

            if (a1->size != a2->size)
                return 0;

            for (i = 0; i < a1->size; i++)
            {
                if (strcmp(a1->data[i], a2->data[i]) != 0)
                    return 0;
            }

            return 1;
        }
        default:
        {
            yyerrorf(ID_INTERNAL_ERROR, "internal error: %s(%u)",
                __FILE__, __LINE__);
            return 0;
        }
    }
}

/*
**==============================================================================
**
** _FinalizeQualifiers()
**
**     This function performs qualifier propagation (from an inherited feature
**     to a derived feature). It operates according to the flavor given by each
**     qualifier. See the CIM infrastructure specification for a complete
**     discussion of qualifier propagation.
**
**     The algorithm works as follows. A new empty qualifier list is created.
**     Next non-restricted inherited qualifiers are appended to this list.
**     Finally derived qualifiers are applied to the list. Qualifiers not
**     already in the list are appended. Qualifiers already in the list are
**     overriden.
**
**     Propagation is performed using the MI_Qualifier.flavor whose bits may be
**     masked by these macros.
**
**         MI_FLAG_ENABLEOVERRIDE
**         MI_FLAG_DISABLEOVERRIDE
**         MI_FLAG_RESTRICTED
**         MI_FLAG_TOSUBCLASS
**
**==============================================================================
*/
static int _FinalizeQualifiers(
    const char* className,
    const char* featureName,
    MI_Qualifier** derived,
    MI_Uint32 numDerived,
    MI_Qualifier** inherited,
    MI_Uint32 numInherited,
    MI_Qualifier*** qualifiers_,
    MI_Uint32* numQualifiers_)
{
    MOF_QualifierList qualifierList = PTRARRAY_INITIALIZER;
    MI_Uint32 i;

    /* Propagate non-restricted inherited qualifiers */
    for (i = 0; i < numInherited; i++)
    {
        MI_Qualifier* q = inherited[i];

        if (!(q->flavor & MI_FLAG_RESTRICTED))
        {
            if (PtrArray_Append((PtrArray*)(void*)&qualifierList, q) != 0)
            {
                yyerrorf(ID_OUT_OF_MEMORY, "out of memory");
                return -1;
            }
        }
    }

    /* Apply derived qualifiers */
    for (i = 0; i < numDerived; i++)
    {
        MI_Qualifier* q = derived[i];
        MI_Uint32 pos = _FindQualifierPos(&qualifierList, q->name);

        if (pos == MOF_NOT_FOUND)
        {
            if (PtrArray_Append((PtrArray*)(void*)&qualifierList, q) != 0)
            {
                yyerrorf(ID_OUT_OF_MEMORY, "out of memory");
                return -1;
            }
        }
        else
        {
            _Analysis_assume_(qualifierList.data);

            /* If DisableOverride flavor, then disallow value change */
            if (qualifierList.data[pos]->flavor & MI_FLAG_DISABLEOVERRIDE &&
                !Identical(qualifierList.data[pos]->value, q->value, q->type))
            {
                if (featureName)
                {
                    yyerrorf(ID_ILLEGAL_QUALIFIER_OVERRIDE,
                        "illegal qualifier override: %s.%s.%s",
                        scs(className), 
                        scs(featureName), 
                        scs(q->name));
                }
                else
                {
                    yyerrorf(ID_ILLEGAL_QUALIFIER_OVERRIDE, 
                        "illegal qualifier override: %s.%s.%s",
                        "",
                        scs(className), 
                        scs(q->name));
                }
                return -1;
            }

            q->flavor = PropagateFlavors(q->flavor, 
                qualifierList.data[pos]->flavor);
            qualifierList.data[pos] = q;
        }
    }

    *qualifiers_ = qualifierList.data;
    *numQualifiers_ = qualifierList.size;

    return 0;
}

static int _FinalizeClassProperties(
    MI_ClassDecl* cd)
{
    size_t i;
    MOF_PropertyList propertySet = PTRARRAY_INITIALIZER;

    /* First inherit properties from finalized super class */
    if (cd->superClass)
    {
        const MI_ClassDecl* super;
        
        /* Retrieve the super class */
        super = FindClassDecl(cd->superClass);

        if (!super)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", 
                scs(cd->superClass));
            return -1;
        }

        /* Use the superclass casing for this class name */
        cd->superClass = super->name;

        /* Propagate class qualifiers */
        {
            MI_Qualifier** qualifiers = NULL;
            MI_Uint32 numQualifiers = 0;

            /* This property overrides an inherited property */
            if (_FinalizeQualifiers(
                cd->name,
                NULL,
                cd->qualifiers,
                cd->numQualifiers,
                super->qualifiers,
                super->numQualifiers,
                &qualifiers,
                &numQualifiers) != 0)
            {
                return -1;
            }

            MOF_Free(&state.heap, cd->qualifiers);
            cd->qualifiers = qualifiers;
            cd->numQualifiers = numQualifiers;
            cd->flags |= GetQualFlags(cd->qualifiers, cd->numQualifiers);
        }

        /* Clone the superclass property array */
        for (i = 0; i < super->numProperties; i++)
        {
            if (PtrArray_Append((PtrArray*)(void*)&propertySet, 
                super->properties[i]) != 0)
            {
                yyerrorf(ID_OUT_OF_MEMORY, "out of memory");
                return -1;
            }
        }
    }

    /* Now append local properties (overriding as necessary) */
    for (i = 0; i < cd->numProperties; i++)
    {
        MI_PropertyDecl* pd = cd->properties[i];
        MI_Uint32 pos;

        /* Set MI_PropertyDecl.propagator */
        pd->propagator = MOF_Strdup(&state.heap, cd->name);

        /* See if the property is already in the list */

        pos = _FindPropertyDecl(&propertySet, pd->name);

        if (pos == MOF_NOT_FOUND)
        {
            /* First time this property has been seen in hierarchy */
            pd->origin = MOF_Strdup(&state.heap, cd->name);

            PtrArray_Append((PtrArray*)(void*)&propertySet, pd);
        }
        else
        {
            MI_Qualifier** qualifiers;
            MI_Uint32 numQualifiers;

            /* This property overrides an inherited property */
            _Analysis_assume_(propertySet.data);

            if (_FinalizeQualifiers(
                cd->name,
                pd->name,
                pd->qualifiers,
                pd->numQualifiers,
                propertySet.data[pos]->qualifiers,
                propertySet.data[pos]->numQualifiers,
                &qualifiers,
                &numQualifiers) != 0)
            {
                return -1;
            }

            MOF_Free(&state.heap, pd->qualifiers);
            pd->qualifiers = qualifiers;
            pd->numQualifiers = numQualifiers;
            pd->flags |= GetQualFlags(qualifiers, numQualifiers);

            pd->origin = MOF_Strdup(&state.heap, 
                propertySet.data[pos]->origin);

            /* Use the superclass casing for the property name */
            pd->name = propertySet.data[pos]->name;

            propertySet.data[pos] = pd;
        }
    }

    /* Replace local property list with aggregate property list */
    MOF_Free(&state.heap, cd->properties);
    cd->properties = propertySet.data;
    cd->numProperties = propertySet.size;

    return 0;
}

static int _VerifyClassKeys(
    const MI_ClassDecl* cd)
{
    MI_Uint32 i;
    const MI_ClassDecl* super;
    MI_Boolean superDefinedKeys = MI_FALSE;

    /* If no super class, no validation needed */
    if (!cd->superClass)
        return 0;

        
    /* Retrieve the super class */
    super = FindClassDecl(cd->superClass);

    if (!super)
    {
        yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", 
            scs(cd->superClass));
        return -1;
    }

    /* Check if super class defined keys */
    for (i = 0; i < super->numProperties; i++)
    {
        if (super->properties[i]->flags & MI_FLAG_KEY)
        {
            superDefinedKeys = MI_TRUE;
            break;
        }
    }

    /* If super class does not have keys no extra check needed */
    if (!superDefinedKeys)
        return 0;

    /* Now append local properties (overriding as necessary) */
    for (i = 0; i < cd->numProperties; i++)
    {
        MI_PropertyDecl* pd = cd->properties[i];
        MI_Uint32 pos;
        MI_Boolean foundInBase = MI_FALSE;

        for (pos = 0; pos < super->numProperties; pos++)
        {
            if (Strcasecmp(pd->name, super->properties[pos]->name) != 0)
                continue;

            foundInBase = MI_TRUE;

            /* new property is a key */
            if (pd->flags & MI_FLAG_KEY)
            {
                if ((super->properties[pos]->flags & MI_FLAG_KEY) == 0)
                {
                    yyerrorf(ID_KEY_MUTATION_ERROR, 
                        "property \"%s\" defined as [key] in class \"%s\", "
                        "but was not key in base class", 
                        scs(pd->name),
                        scs(cd->name));
                    return -1;
                }
            }

            /* compare prop type */
            if ((pd->flags & MI_FLAG_KEY) != 0 ||
                (super->properties[pos]->flags & MI_FLAG_KEY) != 0)
            {
                if (pd->type != super->properties[pos]->type)
                {
                    yyerrorf(ID_KEY_TYPE_MUTATION_ERROR, 
                        "key property \"%s\" re-defined with different type "
                        "in class \"%s\"", 
                        scs(pd->name),
                        scs(cd->name));
                    return -1;
                }

            }

        }

        if (!foundInBase && (pd->flags & MI_FLAG_KEY) != 0)
        {
            yyerrorf(ID_KEY_STRUCTURE_MUTATION_ERROR,
                "new key property \"%s\" is introduced by class \"%s\"", 
                scs(pd->name),
                scs(cd->name));
            return -1;
        }
    }

    return 0;
}

static int _FinalizeClassMethods(
    MI_ClassDecl* cd)
{
    size_t i;
    MOF_MethodList methodList = PTRARRAY_INITIALIZER;

    /* First inherit methods from finalized super class */
    if (cd->superClass)
    {
        const MI_ClassDecl* super;
        
        /* Retrieve the super class */
        super = FindClassDecl(cd->superClass);

        if (!super)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", 
                scs(cd->superClass));
            return -1;
        }

        /* Propagate class qualifiers */
        {
            MI_Qualifier** qualifiers = NULL;
            MI_Uint32 numQualifiers = 0;

            /* This method overrides an inherited method */
            if (_FinalizeQualifiers(
                cd->name,
                NULL,
                cd->qualifiers,
                cd->numQualifiers,
                super->qualifiers,
                super->numQualifiers,
                &qualifiers,
                &numQualifiers) != 0)
            {
                return -1;
            }

            MOF_Free(&state.heap, cd->qualifiers);
            cd->qualifiers = qualifiers;
            cd->numQualifiers = numQualifiers;
            cd->flags |= GetQualFlags(cd->qualifiers, cd->numQualifiers);
        }

        /* Clone the superclass method array */
        for (i = 0; i < super->numMethods; i++)
        {
            if (PtrArray_Append((PtrArray*)(void*)&methodList, 
                super->methods[i]) != 0)
            {
                yyerrorf(ID_OUT_OF_MEMORY, "out of memory");
                return -1;
            }
        }
    }

    /* Now append local methods (overriding as necessary) */
    for (i = 0; i < cd->numMethods; i++)
    {
        MI_MethodDecl* md = cd->methods[i];
        MI_Uint32 pos;

        /* Set MI_MethodDecl.propagator */
        md->propagator = MOF_Strdup(&state.heap, cd->name);

        /* See if the method is already in the list */

        pos = _FindMethodDecl(&methodList, md->name);

        if (pos == MOF_NOT_FOUND)
        {
            /* First time this method has been seen in hierarchy */
            md->origin = MOF_Strdup(&state.heap, cd->name);

            PtrArray_Append((PtrArray*)(void*)&methodList, md);
        }
        else
        {
            MI_Qualifier** qualifiers;
            MI_Uint32 numQualifiers;

            _Analysis_assume_(methodList.data);

            /* This method overrides an inherited method */
            if (_FinalizeQualifiers(
                cd->name,
                md->name,
                md->qualifiers,
                md->numQualifiers,
                methodList.data[pos]->qualifiers,
                methodList.data[pos]->numQualifiers,
                &qualifiers,
                &numQualifiers) != 0)
            {
                return -1;
            }

            MOF_Free(&state.heap, md->qualifiers);
            md->qualifiers = qualifiers;
            md->numQualifiers = numQualifiers;
            md->flags |= GetQualFlags(qualifiers, numQualifiers);

            md->origin = MOF_Strdup(&state.heap, 
                methodList.data[pos]->origin);

            /* Use the superclass casing for the method name */
            md->name = methodList.data[pos]->name;

            methodList.data[pos] = md;
        }
    }

    /* Replace local method list with aggregate method list */
    MOF_Free(&state.heap, cd->methods);
    cd->methods = methodList.data;
    cd->numMethods = methodList.size;

    return 0;
}

static MI_Boolean _HasRefs(
    const MI_ClassDecl* cd)
{
    size_t i;

    for (i = 0; i < cd->numProperties; i++)
    {
        MI_PropertyDecl* pd = cd->properties[i];

        if (pd->type == MI_REFERENCE)
        {
            return MI_TRUE;
        }
    }

    return MI_FALSE;
}

int FinalizeClass(MI_ClassDecl* cd)
{
    /* 
        Verify keys structure: 
        - derived class maynot introduce new keys or
            change key type if base class defined keys
    */
    if (_VerifyClassKeys(cd) != 0)
        return -1;

    /* Perform property propagation */
    if (_FinalizeClassProperties(cd) != 0)
        return -1;

    /* Perform method propagation */
    if (_FinalizeClassMethods(cd) != 0)
        return -1;

    /* Perform association and reference check */
    if (!(cd->flags & MI_FLAG_ASSOCIATION) && _HasRefs(cd))
    {
        yywarnf(ID_INVALID_REFERENCE, 
             "class \"%s\" has at least one reference property but no 'Association' qualifier",  
             scs(cd->name));
    }

    /* Check schema prefix in classname */
    if (strchr(cd->name, '_') == NULL)
    {
        yywarnf(ID_NON_STANDARD_COMPLIANT_CLASSNAME, 
                "classname \"%s\" has no schema prefix e.g. prefix \"CIM_\" in classname \"CIM_Device\"",
                scs(cd->name));
    }

    return 0;
}

int FinalizeInstance(MI_InstanceDecl* id)
{
    const MI_ClassDecl* cd;
    MI_Uint32 i;
    MI_Uint32 j;

    /* Find the class declaration for this instance */
    {
        cd = FindClassDecl(id->name);

        if (!cd)
        {
            yyerrorf(ID_UNDEFINED_CLASS, "undefined class: \"%s\"", id->name);
            return -1;
        }
    }

    /* For each instance property */
    for (i = 0; i < id->numProperties; i++)
    {
        MI_PropertyDecl* p = (MI_PropertyDecl*)id->properties[i];
        MI_PropertyDecl* q = NULL;

        /* Find the class property with the same name */
        {
            for (j = 0; j < cd->numProperties; j++)
            {
                if (Strcasecmp(cd->properties[j]->name, p->name) == 0)
                {
                    q = cd->properties[j];
                    break;
                }
            }

            if (!q)
            {
                yyerrorf(ID_UNDEFINED_PROPERTY, "undefined property: \"%s\"", 
                    p->name);
                return -1;
            }
        }

        /* Promote instance property (to the type given by class property) */
        if (_PromoteValue(p->type, q->type, (void**)&p->value) != 0)
        {
            yyerrorf(ID_INVALID_INITIALIZER, "invalid initializer: \"%s\"",
                p->name);
            return -1;
        }

        /* Assume type of class property if not instance or reference */
        if (q->type != MI_INSTANCE &&
            q->type != MI_REFERENCE &&
            q->type != MI_INSTANCEA &&
            q->type != MI_REFERENCEA)
            p->type = q->type;
    }

    return 0;
}

MI_Uint32 PropagateFlavors(MI_Uint32 flavor, MI_Uint32 baseFlavor)
{
    MI_Uint32 r = flavor;

    /* Only propagate these non-default flavors: 
     *     MI_FLAG_RESTRICTED
     *     MI_FLAG_DISABLEOVERRIDE
     *     MI_FLAG_TRANSLATABLE
     */

    /* MI_FLAG_TOSUBCLASS | MI_FLAG_RESTRICTED */
    if (!(r & MI_FLAG_TOSUBCLASS) && !(r & MI_FLAG_RESTRICTED))
    {
        if (baseFlavor & MI_FLAG_RESTRICTED)
            r |= MI_FLAG_RESTRICTED;
    }

    /* MI_FLAG_ENABLEOVERRIDE | MI_FLAG_DISABLEOVERRIDE */
    if (!(r & MI_FLAG_ENABLEOVERRIDE) && !(r & MI_FLAG_DISABLEOVERRIDE))
    {
        if (baseFlavor & MI_FLAG_DISABLEOVERRIDE)
            r |= MI_FLAG_DISABLEOVERRIDE;
    }

    /* MI_FLAG_TRANSLATABLE */
    if (!(r & MI_FLAG_TRANSLATABLE))
    {
        if (baseFlavor & MI_FLAG_TRANSLATABLE)
            r |= MI_FLAG_TRANSLATABLE;
    }

    return r;
}

#if 0
static void _PrintBits(MI_Uint32 mask)
{
    MI_Uint32 i = 31;

    while (i)
    {
        if ((1 << i) & mask)
            printf("1");
        else
            printf("0");

        i--;
    }

    printf("\n");
}
#endif

int CheckScope(MI_Uint32 scope, MOF_QualifierList* qualifiers)
{
    size_t i;

    if (!qualifiers)
        return 0;

    for (i = 0; i < qualifiers->size; i++)
    {
        const MI_Qualifier* q = qualifiers->data[i];
        const MI_QualifierDecl* qd;

        /* Find qualifier declaration */
        qd = FindQualifierDeclaration(q->name);

        if (!qd)
        {
            yyerrorf(ID_UNKNOWN_QUALIFIER, "unknown qualifier: \"%s\"", 
                scs(q->name));
            return -1;
        }

        if (Strcasecmp(q->name, "Association") == 0)
        {
            if (!(scope & MI_FLAG_CLASS))
            {
                yyerrorf(ID_ILLEGAL_SCOPE_FOR_QUALIFIER, 
                    "illegal scope for qualifier: \"%s\"", 
                    scs(q->name));
                return -1;
            }

            scope |= MI_FLAG_ASSOCIATION;
        }
        else if (Strcasecmp(q->name, "Indication") == 0)
        {
            if (!(scope & MI_FLAG_CLASS))
            {
                yyerrorf(ID_ILLEGAL_SCOPE_FOR_QUALIFIER, 
                    "illegal scope for qualifier: \"%s\"", 
                    scs(q->name));
                return -1;
            }

            scope |= MI_FLAG_INDICATION;
        }
        else if ((qd->scope & scope) == 0)
        {
            yyerrorf(ID_ILLEGAL_SCOPE_FOR_QUALIFIER, 
                "illegal scope for qualifier: \"%s\"", 
                scs(q->name));
            return -1;
        }
    }

    return 0;
}

static int _CheckMinValue(const MI_PropertyDecl* pd, const MI_Qualifier* q)
{
    MI_Sint64 r;
    MI_Uint32 i;

    switch (pd->type)
    {
        case MI_UINT8:
        case MI_SINT8:
        case MI_UINT16:
        case MI_SINT16:
        case MI_UINT32:
        case MI_SINT32:
        case MI_UINT64:
        case MI_REAL32:
        case MI_REAL64:
        case MI_SINT64:
        case MI_UINT8A:
        case MI_SINT8A:
        case MI_UINT16A:
        case MI_SINT16A:
        case MI_UINT32A:
        case MI_SINT32A:
        case MI_UINT64A:
        case MI_SINT64A:
        case MI_REAL32A:
        case MI_REAL64A:
            break;
        default:
            goto incompatibleError;
    }

    if (!q->value || !pd->value)
        return 0;

    r = *((MI_Sint64*)q->value);

    switch (pd->type)
    {
        case MI_UINT8:
        {
            MI_Uint8 x = *((MI_Uint8*)pd->value);
            if ((MI_Sint64)x < r)
                goto constraintError;
            break;
        }
        case MI_SINT8:
        {
            MI_Sint8 x = *((MI_Sint8*)pd->value);
            if ((MI_Sint64)x < r)
                goto constraintError;
            break;
        }
        case MI_UINT16:
        {
            MI_Uint16 x = *((MI_Uint16*)pd->value);
            if ((MI_Sint64)x < r)
                goto constraintError;
            break;
        }
        case MI_SINT16:
        {
            MI_Sint16 x = *((MI_Sint16*)pd->value);
            if ((MI_Sint64)x < r)
                goto constraintError;
            break;
        }
        case MI_UINT32:
        {
            MI_Uint32 x = *((MI_Uint32*)pd->value);
            if ((MI_Sint64)x < r)
                goto constraintError;
            break;
        }
        case MI_SINT32:
        {
            MI_Sint32 x = *((MI_Sint32*)pd->value);
            if ((MI_Sint64)x < r)
                goto constraintError;
            break;
        }
        case MI_UINT64:
        {
            MI_Uint64 x = *((MI_Uint64*)pd->value);
            if ((MI_Sint64)x < r)
                goto constraintError;
            break;
        }
        case MI_SINT64:
        {
            MI_Sint64 x = *((MI_Sint64*)pd->value);
            if ((MI_Sint64)x < r)
                goto constraintError;
            break;
        }
        case MI_REAL32:
        {
            MI_Real32 x = *((MI_Real32*)pd->value);
            if (x < (MI_Real32)r)
                goto constraintError;
            break;
        }
        case MI_REAL64:
        {
            MI_Real64 x = *((MI_Real64*)pd->value);
            if (x < (MI_Real64)r)
                goto constraintError;
            break;
        }
        case MI_UINT8A:
        {
            MI_Uint8A x = *((MI_Uint8A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Uint8)x.data[i] < r)
                    goto constraintError;
            }
            break;
        }
        case MI_SINT8A:
        {
            MI_Sint8A x = *((MI_Sint8A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Sint8)x.data[i] < r)
                    goto constraintError;
            }
            break;
        }
        case MI_UINT16A:
        {
            MI_Uint16A x = *((MI_Uint16A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Uint16)x.data[i] < r)
                    goto constraintError;
            }
            break;
        }
        case MI_SINT16A:
        {
            MI_Sint16A x = *((MI_Sint16A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Sint16)x.data[i] < r)
                    goto constraintError;
            }
            break;
        }
        case MI_UINT32A:
        {
            MI_Uint32A x = *((MI_Uint32A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Uint32)x.data[i] < r)
                    goto constraintError;
            }
            break;
        }
        case MI_SINT32A:
        {
            MI_Sint32A x = *((MI_Sint32A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Sint32)x.data[i] < r)
                    goto constraintError;
            }
            break;
        }
        case MI_UINT64A:
        {
            MI_Uint64A x = *((MI_Uint64A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Sint64)x.data[i] < r)
                    goto constraintError;
            }
            break;
        }
        case MI_SINT64A:
        {
            MI_Sint64A x = *((MI_Sint64A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Sint64)x.data[i] < r)
                    goto constraintError;
            }
            break;
        }
        case MI_REAL32A:
        {
            MI_Real32A x = *((MI_Real32A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if (x.data[i] < (MI_Real32)r)
                    goto constraintError;
            }
            break;
        }
        case MI_REAL64A:
        {
            MI_Real64A x = *((MI_Real64A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if (x.data[i] < (MI_Real64)r)
                    goto constraintError;
            }
            break;
        }
        default:
            goto incompatibleError;
    }

    return 0;

constraintError:
    yyerrorf(
        ID_PROPERTY_CONSTRAINT_FAILURE,
        "value for property \"%s\" fails constraint given by \"%s\" qualifier", 
        scs(pd->name), 
        scs(q->name));
    return -1;

incompatibleError:
    yyerrorf(
        ID_PROPERTY_QUALIFIER_INCOMPATIBLE,
        "%s qualifier applied to incompatible property: %s", 
        scs(q->name), 
        scs(pd->name));
    return -1;
}

static int _CheckMaxValue(const MI_PropertyDecl* pd, const MI_Qualifier* q)
{
    MI_Sint64 r;
    MI_Uint32 i;

    switch (pd->type)
    {
        case MI_UINT8:
        case MI_SINT8:
        case MI_UINT16:
        case MI_SINT16:
        case MI_UINT32:
        case MI_SINT32:
        case MI_UINT64:
        case MI_REAL32:
        case MI_REAL64:
        case MI_SINT64:
        case MI_UINT8A:
        case MI_SINT8A:
        case MI_UINT16A:
        case MI_SINT16A:
        case MI_UINT32A:
        case MI_SINT32A:
        case MI_UINT64A:
        case MI_SINT64A:
        case MI_REAL32A:
        case MI_REAL64A:
            break;
        default:
            goto incompatibleError;
    }

    if (!q->value || !pd->value)
        return 0;

    r = *((MI_Sint64*)q->value);

    switch (pd->type)
    {
        case MI_UINT8:
        {
            MI_Uint8 x = *((MI_Uint8*)pd->value);
            if ((MI_Sint64)x > r)
                goto constraintError;
            break;
        }
        case MI_SINT8:
        {
            MI_Sint8 x = *((MI_Sint8*)pd->value);
            if ((MI_Sint64)x > r)
                goto constraintError;
            break;
        }
        case MI_UINT16:
        {
            MI_Uint16 x = *((MI_Uint16*)pd->value);
            if ((MI_Sint64)x > r)
                goto constraintError;
            break;
        }
        case MI_SINT16:
        {
            MI_Sint16 x = *((MI_Sint16*)pd->value);
            if ((MI_Sint64)x > r)
                goto constraintError;
            break;
        }
        case MI_UINT32:
        {
            MI_Uint32 x = *((MI_Uint32*)pd->value);
            if ((MI_Sint64)x > r)
                goto constraintError;
            break;
        }
        case MI_SINT32:
        {
            MI_Sint32 x = *((MI_Sint32*)pd->value);
            if ((MI_Sint64)x > r)
                goto constraintError;
            break;
        }
        case MI_UINT64:
        {
            MI_Uint64 x = *((MI_Uint64*)pd->value);
            if (x > (MI_Uint64)r)
                goto constraintError;
            break;
        }
        case MI_SINT64:
        {
            MI_Sint64 x = *((MI_Sint64*)pd->value);
            if ((MI_Sint64)x > r)
                goto constraintError;
            break;
        }
        case MI_REAL32:
        {
            MI_Real32 x = *((MI_Real32*)pd->value);
            if (x > (MI_Real32)r)
                goto constraintError;
            break;
        }
        case MI_REAL64:
        {
            MI_Real64 x = *((MI_Real64*)pd->value);
            if (x > (MI_Real64)r)
                goto constraintError;
            break;
        }
        case MI_UINT8A:
        {
            MI_Uint8A x = *((MI_Uint8A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Uint8)x.data[i] > r)
                    goto constraintError;
            }
            break;
        }
        case MI_SINT8A:
        {
            MI_Sint8A x = *((MI_Sint8A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Sint8)x.data[i] > r)
                    goto constraintError;
            }
            break;
        }
        case MI_UINT16A:
        {
            MI_Uint16A x = *((MI_Uint16A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Uint16)x.data[i] > r)
                    goto constraintError;
            }
            break;
        }
        case MI_SINT16A:
        {
            MI_Sint16A x = *((MI_Sint16A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Sint16)x.data[i] > r)
                    goto constraintError;
            }
            break;
        }
        case MI_UINT32A:
        {
            MI_Uint32A x = *((MI_Uint32A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Uint32)x.data[i] > r)
                    goto constraintError;
            }
            break;
        }
        case MI_SINT32A:
        {
            MI_Sint32A x = *((MI_Sint32A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Sint32)x.data[i] > r)
                    goto constraintError;
            }
            break;
        }
        case MI_UINT64A:
        {
            MI_Uint64A x = *((MI_Uint64A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Sint64)x.data[i] > r)
                    goto constraintError;
            }
            break;
        }
        case MI_SINT64A:
        {
            MI_Sint64A x = *((MI_Sint64A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if ((MI_Sint64)x.data[i] > r)
                    goto constraintError;
            }
            break;
        }
        case MI_REAL32A:
        {
            MI_Real32A x = *((MI_Real32A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if (x.data[i] > (MI_Real32)r)
                    goto constraintError;
            }
            break;
        }
        case MI_REAL64A:
        {
            MI_Real64A x = *((MI_Real64A*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if (x.data[i] > (MI_Real64)r)
                    goto constraintError;
            }
            break;
        }
        default:
            goto incompatibleError;
    }

    return 0;

constraintError:
    yyerrorf(
        ID_PROPERTY_CONSTRAINT_FAILURE,
        "value for property \"%s\" fails constraint given by \"%s\" qualifier",
        scs(pd->name), 
        scs(q->name));
    return -1;

incompatibleError:
    yyerrorf(
        ID_PROPERTY_QUALIFIER_INCOMPATIBLE,
        "%s qualifier applied to incompatible property: %s", 
        scs(q->name), 
        scs(pd->name));
    return -1;
}

static int _CheckMaxLen(const MI_PropertyDecl* pd, const MI_Qualifier* q)
{
    MI_Uint32 r;
    MI_Uint32 i;

    if (pd->type != MI_STRING && pd->type != MI_STRINGA)
        goto incompatibleError;

    if (!q->value || !pd->value)
        return 0;

    r = *((MI_Uint32*)q->value);

    switch (pd->type)
    {
        case MI_STRING:
        {
            const ZChar* s = (const ZChar*)pd->value;
            if (strlen(s) > r)
                goto constraintError;
            break;
        }
        case MI_STRINGA:
        {
            MI_StringA x = *((MI_StringA*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if (strlen(x.data[i]) > r)
                    goto constraintError;
            }
            break;
        }
        default:
            goto incompatibleError;
    }

    return 0;

constraintError:
    yyerrorf(
        ID_PROPERTY_CONSTRAINT_FAILURE,
        "value for property \"%s\" fails constraint given by \"%s\" qualifier",
        scs(pd->name), 
        scs(q->name));
    return -1;

incompatibleError:
    yyerrorf(
        ID_PROPERTY_QUALIFIER_INCOMPATIBLE,
        "%s qualifier applied to incompatible property: %s", 
        scs(q->name), 
        scs(pd->name));
    return -1;
}

static int _CheckMinLen(const MI_PropertyDecl* pd, const MI_Qualifier* q)
{
    MI_Uint32 r;
    MI_Uint32 i;

    if (pd->type != MI_STRING && pd->type != MI_STRINGA)
        goto incompatibleError;

    if (!q->value || !pd->value)
        return 0;

    r = *((MI_Uint32*)q->value);

    switch (pd->type)
    {
        case MI_STRING:
        {
            const ZChar* s = (const ZChar*)pd->value;
            if (strlen(s) < r)
                goto constraintError;
            break;
        }
        case MI_STRINGA:
        {
            MI_StringA x = *((MI_StringA*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if (strlen(x.data[i]) < r)
                    goto constraintError;
            }
            break;
        }
        default:
            goto incompatibleError;
    }

    return 0;

constraintError:
    yyerrorf(
        ID_PROPERTY_CONSTRAINT_FAILURE,
        "value for property \"%s\" fails constraint given by \"%s\" qualifier", 
        scs(pd->name), 
        scs(q->name));
    return -1;

incompatibleError:
    yyerrorf(
        ID_PROPERTY_QUALIFIER_INCOMPATIBLE, 
        "%s qualifier applied to incompatible property: %s", 
        scs(q->name), 
        scs(pd->name));
    return -1;
}

int CheckPropertyValueConstraints(const MI_PropertyDecl* pd)
{
    MI_Uint32 i;

    /* Check constraint qualifiers against the property value */
    for (i = 0; i < pd->numQualifiers; i++)
    {
        const MI_Qualifier* q = pd->qualifiers[i];

        if (Strcasecmp(q->name, "MaxValue") == 0 && q->value)
        {
            if (_CheckMaxValue(pd, q) != 0)
                return -1;
        }
        else if (Strcasecmp(q->name, "MinValue") == 0 && q->value)
        {
            if (_CheckMinValue(pd, q) != 0)
                return -1;
        }
        else if (Strcasecmp(q->name, "MaxLen") == 0 && q->value)
        {
            if (_CheckMaxLen(pd, q) != 0)
                return -1;
        }
        else if (Strcasecmp(q->name, "MinLen") == 0 && q->value)
        {
            if (_CheckMinLen(pd, q) != 0)
                return -1;
        }
        else if (Strcasecmp(q->name, "Override") == 0 && q->value &&
            q->type == MI_STRING)
        {
            if (!(Strcasecmp(pd->name, (char*)q->value) == 0))
            {
                yyerrorf(
                    ID_OVERRIDE_QUALIFIER_NAME_MISMATCH, 
                    "name given by Override qualifier (\"%s\") does "
                    "not match property name (\"%s\")", (char*)q->value,
                    pd->name);
            }
        }
    }

    /* Success! */
    return 0;
}

int ResolveEmbeddedInstanceQualifier(const MOF_EmbeddedInstance* ei)
{
    const char* cn;
    MI_Qualifier* q = ei->qualifier;

    if (q->type != MI_STRING || Strcasecmp(q->name, "EmbeddedInstance") != 0)
    {
        yyerrorf(ID_INTERNAL_ERROR, "internal error: %s(%u)", __FILE__, 
            __LINE__);
        return -1;
    }

    cn = (const char*)q->value;

    if (cn)
    {
        const MI_ClassDecl* cd = FindClassDecl(cn);

        if (!cd)
        {
            state.line = ei->line;
            yyerrorf(
                ID_UNDEFINED_CLASS_IN_EMBEDDEDINSTANCE_QUALIFIER,
                "Undefined class in EmbeddedInstance qualifier: %s", cn);
            return -1;
        }

        /* Use the original casing for the classname */
        q->value = cd->name;
    }

    return 0;
}

int PerformPostProcessing()
{
    MI_Uint32 i;

    for (i = 0; i < state.embeddedInstanceList.size; i++)
    {
        if (0 != ResolveEmbeddedInstanceQualifier(state.embeddedInstanceList.data[i]))
            return -1;
    }

    return 0;
}

MI_Type InitializerToType(const MOF_Initializer* initializer)
{
    if (initializer->isArray)
    {
        if (initializer->size == 0)
            return MI_STRINGA;
        switch (initializer->data[0].type)
        {
            case TOK_INTEGER_VALUE:
                return MI_SINT64A;
            case TOK_REAL_VALUE:
                return MI_REAL64A;
            case TOK_CHAR_VALUE:
                return MI_CHAR16A;
            case TOK_STRING_VALUE:
                return MI_STRINGA;
            case TOK_BOOLEAN_VALUE:
                return MI_BOOLEANA;
            case TOK_NULL:
                return MI_STRINGA;
        }
    }
    else
    {
        switch (initializer->data[0].type)
        {
            case TOK_INTEGER_VALUE:
                return MI_SINT64;
            case TOK_REAL_VALUE:
                return MI_REAL64;
            case TOK_CHAR_VALUE:
                return MI_CHAR16;
            case TOK_STRING_VALUE:
                return MI_STRING;
            case TOK_BOOLEAN_VALUE:
                return MI_BOOLEAN;
            case TOK_NULL:
                return MI_STRING;
        }
    }

    /* Unreachable */
    return MI_BOOLEAN;
}

int AddInstanceDecl(MI_InstanceDecl* id)
{
    /* Add the declaration */
    PtrArray_Append((PtrArray*)&state.instanceDecls, id);
    return 0;
}

#ifdef _PREFAST_
#pragma prefast (pop)
#endif
