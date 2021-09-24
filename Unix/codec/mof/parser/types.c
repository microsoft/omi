/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "base/naming.h"
#include "mofcommon.h"
#include "types.h"
#include "ptrarray.h"
#include "buffer.h"
#include "utility.h"
#include <pal/format.h>
#include <pal/strings.h>
#include <nits/base/nits.h>

#if (MI_CHAR_TYPE == 1)
#define SZprintf Snprintf
#else
#define SZprintf Swprintf
#endif

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
        PTR = ((TYPE##A*)Batch_Get(state->batch, \
            sizeof(TYPE##A) + sizeof(TYPE) * (SIZE))); \
        PTR->data = (TYPE*)(PTR + 1); \
        PTR->size = SIZE; \
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

const MI_Char* _getTypeName_MI(MI_Type type)
{
    switch (type)
    {
        case MI_BOOLEAN:
            return MI_T("BOOLEAN");
        case MI_UINT8:
            return MI_T("UINT8");
        case MI_SINT8:
            return MI_T("SINT8");
        case MI_UINT16:
            return MI_T("UINT16");
        case MI_SINT16:
            return MI_T("SINT16");
        case MI_UINT32:
            return MI_T("UINT32");
        case MI_SINT32:
            return MI_T("SINT32");
        case MI_UINT64:
            return MI_T("UINT64");
        case MI_SINT64:
            return MI_T("SINT64");
        case MI_REAL32:
            return MI_T("REAL32");
        case MI_REAL64:
            return MI_T("REAL64");
        case MI_CHAR16:
            return MI_T("CHAR16");
        case MI_DATETIME:
            return MI_T("DATETIME");
        case MI_STRING:
            return MI_T("STRING");
        case MI_REFERENCE:
            return MI_T("REFERENCE");
        case MI_INSTANCE:
            return MI_T("INSTANCE");
        case MI_BOOLEANA:
            return MI_T("BOOLEAN[]");
        case MI_UINT8A:
            return MI_T("UINT8[]");
        case MI_SINT8A:
            return MI_T("SINT8[]");
        case MI_UINT16A:
            return MI_T("UINT16[]");
        case MI_SINT16A:
            return MI_T("SINT16[]");
        case MI_UINT32A:
            return MI_T("UINT32[]");
        case MI_SINT32A:
            return MI_T("SINT32[]");
        case MI_UINT64A:
            return MI_T("UINT64[]");
        case MI_SINT64A:
            return MI_T("SINT64[]");
        case MI_REAL32A:
            return MI_T("REAL32[]");
        case MI_REAL64A:
            return MI_T("REAL64[]");
        case MI_CHAR16A:
            return MI_T("CHAR16[]");
        case MI_DATETIMEA:
            return MI_T("DATETIME[]");
        case MI_STRINGA:
            return MI_T("STRING[]");
        case MI_REFERENCEA:
            return MI_T("REFERENCE[]");
        case MI_INSTANCEA:
            return MI_T("INSTANCE[]");
        default:
            return MI_T("UNKNOWN");
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
    const MI_Char* p, 
    size_t n, 
    MI_Uint32* result)
{
    MI_Char buf[9];
    MI_Char* end;

    if (n > 8)
        return -1;

    memcpy(buf, p, n * sizeof(MI_Char));
    buf[n] = '\0';

    *result = (MI_Uint32)Tcstoul(buf, &end, 10);

    if (*end != '\0')
        return -1;

    return 0;
}

typedef struct _Flag
{
    const MI_Char* name;
    MI_Uint32 flag;
}
Flag;

static Flag _flags[] =
{
    { MI_T("CLASS"), MI_FLAG_CLASS },
    { MI_T("METHOD"), MI_FLAG_METHOD },
    { MI_T("PROPERTY"), MI_FLAG_PROPERTY },
    { MI_T("PARAMETER"), MI_FLAG_PARAMETER },
    { MI_T("ASSOCIATION"), MI_FLAG_ASSOCIATION },
    { MI_T("INDICATION"), MI_FLAG_INDICATION },
    { MI_T("REFERENCE"), MI_FLAG_REFERENCE },

    { MI_T("KEY"), MI_FLAG_KEY },
    { MI_T("IN"), MI_FLAG_IN },
    { MI_T("OUT"), MI_FLAG_OUT },
    { MI_T("REQUIRED"), MI_FLAG_REQUIRED },
    { MI_T("STATIC"), MI_FLAG_STATIC },
    { MI_T("ABSTRACT"), MI_FLAG_ABSTRACT },
    { MI_T("TERMINAL"), MI_FLAG_TERMINAL },
    { MI_T("EXPENSIVE"), MI_FLAG_EXPENSIVE },
    { MI_T("STREAM"), MI_FLAG_STREAM },
    { MI_T("READ"), MI_FLAG_READONLY },

    { MI_T("ENABLEOVERRIDE"), MI_FLAG_ENABLEOVERRIDE },
    { MI_T("DISABLEOVERRIDE"), MI_FLAG_DISABLEOVERRIDE },
    { MI_T("RESTRICTED"), MI_FLAG_RESTRICTED},
    { MI_T("TOSUBCLASS"), MI_FLAG_TOSUBCLASS},
    { MI_T("TRANSLATABLE"), MI_FLAG_TRANSLATABLE},
};

static size_t _flagsSize = MI_COUNT(_flags);
static int _ValidateHMS(
    void * mofstate,
    MI_Uint32 hour,
    MI_Uint32 minute,
    MI_Uint32 second)
{
    int error = -1;
    MI_Char* invalidName = MI_T("");
    MI_Uint32 invalidValue = 0;
    MOF_State* state = (MOF_State *)mofstate;
    do
    {
        if (hour > 23)
        {
            invalidName = MI_T("hour");
            invalidValue = hour;
            break;
        }
        if (minute > 59)
        {
            invalidName = MI_T("minute");
            invalidValue = minute;
            break;
        }
        if (second > 59)
        {
            invalidName = MI_T("second");
            invalidValue = second;
            break;
        }
        error = 0;
    }
    while(0);
    if (error != 0)
    {
        yyerrorf(state->errhandler, ID_INITIALIZER_OUT_OF_RANGE_DATETIMEVALUE, 
            "", invalidValue, invalidName);
    }
    return error;
}

static MI_Boolean _IsLeapYear(
    MI_Uint32 year)
{
    if (year % 400 == 0) return MI_TRUE;
    if (year % 100 == 0) return MI_FALSE;
    if (year % 4 == 0) return MI_TRUE;
    return MI_FALSE;
}

static int _ValidateYMDU(
    void * mofstate,
    MI_Uint32 year,
    MI_Uint32 month,
    MI_Uint32 day,
    MI_Uint32 utc)
{
    int error = -1;
    MI_Char* invalidName = MI_T("");
    MI_Uint32 invalidValue = 0;
    MOF_State* state = (MOF_State *)mofstate;
    do
    {
        MI_Uint32 maxday = 31;
        if (year > 9999)
        {
            invalidName = MI_T("year");
            invalidValue = year;
            break;
        }
        if (month < 1 || month > 12)
        {
            invalidName = MI_T("month");
            invalidValue = month;
            break;
        }
        switch(month)
        {
        case 2:
            maxday = (MI_TRUE == _IsLeapYear(year)) ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            maxday = 30;
            break;
        }
        if (day < 1 || day > maxday)
        {
            invalidName = MI_T("day");
            invalidValue = day;
            break;
        }
        if (utc > 999)
        {
            invalidName = MI_T("utc");
            invalidValue = utc;
            break;
        }
        error = 0;
    }
    while(0);
    if (error != 0)
    {
        yyerrorf(state->errhandler, ID_INITIALIZER_OUT_OF_RANGE_DATETIMEVALUE, 
            "", invalidValue, invalidName);
    }
    return error;
}

static int _StrToDatetime(void * mofstate,
                          const MI_Char* str,
                          MI_Datetime* result)
{
    const MI_Char* p = str;

    /* Check arguments */
    if (!str || !result)
        return -1;

    /* Datetime strings must be exactly 25 bytes long */
    if (Tcslen(p) != 25)
        return -1;

    if (p[21] == ':')
    {
        /* DDDDDDDDHHMMSS.MMMMMM:000 */
        MI_Uint32 dddddddd;
        MI_Uint32 hh;
        MI_Uint32 mm;
        MI_Uint32 ss;
        MI_Uint32 mmmmmm;

        if (_ParseUint32(p, 8, &dddddddd) != 0)
            return -1;
        if (_ParseUint32(p + 8, 2, &hh) != 0)
            return -1;
        if (_ParseUint32(p + 10, 2, &mm) != 0)
            return -1;
        if (_ParseUint32(p + 12, 2, &ss) != 0)
            return -1;
        if (p[14] != '.')
            return -1;
        if (_ParseUint32(p + 15, 6, &mmmmmm) != 0)
            return -1;
        if (p[22] != '0' || p[23] != '0' || p[24] != '0')
            return -1;

        /* Validate each field is legal or not */
        if (_ValidateHMS(mofstate, hh, mm, ss) != 0)
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

        if (_ParseUint32(p, 4, &yyyy) != 0)
            return -1;
        if (_ParseUint32(p + 4, 2, &MM) != 0)
            return -1;
        if (_ParseUint32(p + 6, 2, &dd) != 0)
            return -1;
        if (_ParseUint32(p + 8, 2, &hh) != 0)
            return -1;
        if (_ParseUint32(p + 10, 2, &mm) != 0)
            return -1;
        if (_ParseUint32(p + 12, 2, &ss) != 0)
            return -1;
        if (p[14] != '.')
            return -1;
        if (_ParseUint32(p + 15, 6, &mmmmmm) != 0)
            return -1;
        s = p[21];
        if (s != '-' && s != '+')
            return -1;
        if (_ParseUint32(p + 22, 3, &utc) != 0)
            return -1;

        /* Validate each field is legal or not */
        if (_ValidateYMDU(mofstate, yyyy, MM, dd, utc) != 0)
            return -1;
        if (_ValidateHMS(mofstate, hh, mm, ss) != 0)
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

static int _CheckRange(
    void * mofstate,
    MI_Sint64 x, MI_Type type)
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
    MOF_State * state = (MOF_State *)mofstate;

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
    yyerrorf(state->errhandler, ID_INITIALIZER_OUT_OF_RANGE, 
        "initializer out of range: " SINT64_FMT, x);
    return -1;

unexpected:
    yyerrorf(state->errhandler, ID_INTERNAL_ERROR, "internal error: %s(%u)", __FILE__, __LINE__);
    return -1;
}

/* Check whether a instance is of the type 'classname' or derived classes */
static int _IsInstanceOfClass(
    _In_ void * mofstate,
    _In_ MI_Instance * inst,
    _In_z_ MI_Char * destpropertyclassname)
{
    MOF_State * state = (MOF_State *)mofstate;
    const MI_ClassDecl * clsdecl = inst->classDecl;
    while (clsdecl && clsdecl->name)
    {
        if (Tcscasecmp(clsdecl->name, destpropertyclassname) == 0)
            return 0;
        clsdecl = clsdecl->superClassDecl;
    }
    yyerrorf(state->errhandler,
        ID_INVALID_EMBEDDEDPROPERTYVALUE_WRONG_TYPE,
        "",
        inst->classDecl->name,
        destpropertyclassname);
    return -1;
}

static int _PromoteValue(
    void * mofstate,
    MI_Uint32 sourceType,
    MI_PropertyDecl *destpropertydecl,
    MI_Boolean * embeddedpropertyError,
    void** value)
{
    MI_Uint32 i;
    MOF_State * state = (MOF_State *)mofstate;
    MI_Uint32 destType = destpropertydecl->type;
    *embeddedpropertyError = MI_FALSE;

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
                    MI_Sint64 x = *p;

                    if (_CheckRange(state, x, MI_UINT8) != 0)
                        return -1;

                    *q = (MI_Uint8)x;
                    *value = q; 
                    return 0;
                }
                case MI_SINT8:
                {
                    MI_Sint8* q = MALLOC_T(MI_Sint8, 1);
                    MI_Sint64 x = *p;

                    if (_CheckRange(state, x, MI_SINT8) != 0)
                        return -1;

                    *q = (MI_Sint8)x;
                    *value = q; 
                    return 0;
                }
                case MI_UINT16:
                {
                    MI_Uint16* q = MALLOC_T(MI_Uint16, 1);
                    MI_Sint64 x = *p;

                    if (_CheckRange(state, x, MI_UINT16) != 0)
                        return -1;

                    *q = (MI_Uint16)x;
                    *value = q; 
                    return 0;
                }
                case MI_SINT16:
                {
                    MI_Sint16* q = MALLOC_T(MI_Sint16, 1);
                    MI_Sint64 x = *p;

                    if (_CheckRange(state, x, MI_SINT16) != 0)
                        return -1;

                    *q = (MI_Sint16)x;
                    *value = q; 
                    return 0;
                }
                case MI_UINT32:
                {
                    MI_Uint32* q = MALLOC_T(MI_Uint32, 1);
                    MI_Sint64 x = *p;

                    if (_CheckRange(state, x, MI_UINT32) != 0)
                        return -1;

                    *q = (MI_Uint32)x;
                    *value = q; 
                    return 0;
                }
                case MI_SINT32:
                {
                    MI_Sint32* q = MALLOC_T(MI_Sint32, 1);
                    MI_Sint64 x = *p;

                    if (_CheckRange(state, x, MI_SINT32) != 0)
                        return -1;

                    *q = (MI_Sint32)x;
                    *value = q; 
                    return 0;
                }
                case MI_UINT64:
                {
                    MI_Uint64* q = MALLOC_T(MI_Uint64, 1);
                    MI_Sint64 x = *p;

                    if (_CheckRange(state, x, MI_UINT64) != 0)
                        return -1;

                    *q = (MI_Uint64)x;
                    *value = q; 
                    return 0;
                }
                case MI_SINT64:
                {
                    return 0;
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
                    *q = (MI_Real32)*p;
                    *value = q; 
                    return 0;
                }
                case MI_REAL64:
                {
                    return 0;
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
            switch (destType)
            {
                case MI_STRING:
                {
                    return 0;
                }
                case MI_DATETIME:
                {
                    void * pstringvalue = *value;
                    const MI_Char* p = *((const MI_Char**)pstringvalue);
                    MI_Datetime* q = MALLOC_T(MI_Datetime, 1);

                    if (_StrToDatetime(mofstate, p, q) != 0)
                        return -1;

                    *value = q; 
                    return 0;
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

                    for (i = 0; i < p->size; i++)
                    {
                        MI_Sint64 x = p->data[i];

                        if (_CheckRange(state, x, MI_UINT8) != 0)
                            return -1;

                        q->data[i] = (MI_Uint8)x;
                    }

                    *value = q;
                    return 0;
                }
                case MI_SINT8A:
                {
                    MI_Sint8A* q;
                    NEW_ARRAY_T(q, MI_Sint8, p->size);

                    for (i = 0; i < p->size; i++)
                    {
                        MI_Sint64 x = p->data[i];

                        if (_CheckRange(state, x, MI_SINT8) != 0)
                            return -1;

                        q->data[i] = (MI_Sint8)x;
                    }

                    *value = q;
                    return 0;
                }
                case MI_UINT16A:
                {
                    MI_Uint16A* q;
                    NEW_ARRAY_T(q, MI_Uint16, p->size);

                    for (i = 0; i < p->size; i++)
                    {
                        MI_Sint64 x = p->data[i];

                        if (_CheckRange(state, x, MI_UINT16) != 0)
                            return -1;

                        q->data[i] = (MI_Uint16)x;
                    }

                    *value = q;
                    return 0;
                }
                case MI_SINT16A:
                {
                    MI_Sint16A* q;
                    NEW_ARRAY_T(q, MI_Sint16, p->size);

                    for (i = 0; i < p->size; i++)
                    {
                        MI_Sint64 x = p->data[i];

                        if (_CheckRange(state, x, MI_SINT16) != 0)
                            return -1;

                        q->data[i] = (MI_Sint16)x;
                    }

                    *value = q;
                    return 0;
                }
                case MI_UINT32A:
                {
                    MI_Uint32A* q;
                    NEW_ARRAY_T(q, MI_Uint32, p->size);

                    for (i = 0; i < p->size; i++)
                    {
                        MI_Sint64 x = p->data[i];

                        if (_CheckRange(state, x, MI_UINT32) != 0)
                            return -1;

                        q->data[i] = (MI_Uint32)x;
                    }

                    *value = q;
                    return 0;
                }
                case MI_SINT32A:
                {
                    MI_Sint32A* q;
                    NEW_ARRAY_T(q, MI_Sint32, p->size);

                    for (i = 0; i < p->size; i++)
                    {
                        MI_Sint64 x = p->data[i];

                        if (_CheckRange(state, x, MI_SINT32) != 0)
                            return -1;

                        q->data[i] = (MI_Sint32)x;
                    }

                    *value = q;
                    return 0;
                }
                case MI_UINT64A:
                {
                    MI_Uint64A* q;
                    NEW_ARRAY_T(q, MI_Uint64, p->size);

                    for (i = 0; i < p->size; i++)
                    {
                        MI_Sint64 x = p->data[i];

                        if (_CheckRange(state, x, MI_UINT64) != 0)
                            return -1;

                        q->data[i] = (MI_Uint64)x;
                    }

                    *value = q;
                    return 0;
                }
                case MI_SINT64A:
                {
                    return 0;
                }
                default:
                {
                    /* For empty array, just create another empty array and return */
                    if (p->size == 0)
                    {
                        MI_Uint64A* q;
                        NEW_ARRAY_T(q, MI_Uint64, p->size);
                        q->data = NULL;
                        *value = q;
                        return 0;
                    }
                    return -1;
                }
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

                    for (i = 0; i < p->size; i++)
                    {
                        q->data[i] = (MI_Real32)p->data[i];
                    }

                    *value = q; 
                    return 0;
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

            switch (destType)
            {
                case MI_STRINGA:
                {
                    return 0;
                }
                case MI_DATETIMEA:
                {
                    MI_DatetimeA* q;
                    NEW_ARRAY_T(q, MI_Datetime, p->size);

                    for (i = 0; i < p->size; i++)
                    {
                        if (_StrToDatetime(mofstate, p->data[i], &q->data[i]) != 0)
                            return -1;
                    }

                    *value = q; 
                    return 0;
                }
                default:
                    return -1;
            }
        }
        case MI_INSTANCE:
        case MI_REFERENCE:
            switch (destType)
            {
            case MI_INSTANCE:
            case MI_REFERENCE:
                {
                    MI_Instance * inst = *(*(MI_Instance***)value);
                    if (destpropertydecl->className)
                    {
                        *embeddedpropertyError = MI_TRUE;
                        return _IsInstanceOfClass(state, inst, destpropertydecl->className);
                    }
                    return 0;
                }
            }
            break;
        case MI_INSTANCEA:
        case MI_REFERENCEA:
            switch (destType)
            {
            case MI_INSTANCEA:
            case MI_REFERENCEA:
                {
                    const MI_InstanceA * insta = *(const MI_InstanceA**)value;
                    MI_Char *destclassname = destpropertydecl->className;
                    if (destclassname)
                    {
                        *embeddedpropertyError = MI_TRUE;
                        for (i = 0; i < insta->size; i++)
                        {
                            if (_IsInstanceOfClass(state, insta->data[i], destclassname) != 0)
                                return -1;
                        }
                    }
                    return 0;
                }
            }
            break;
        default:
            break;
    }

    return -1;
}

int InitializerToValue(
    void * mofstate,
    MOF_Initializer* self, 
    MI_Uint32 /*MI_Type*/ type,
    void** value)
{
    /* ATTN: this function could check integer truncation and sign errors */
    /* ATTN: handle case where ZChar is wchar_t */
    size_t i;
    MOF_State * state = (MOF_State *)mofstate;

    /* Check arguments */
    if (!self || !value)
        return -1;

    *value = NULL;

    /* Verify that there is at least one element */
    if (self->size == 0)
    {
        MI_Sint64A* p;
        NEW_ARRAY_T(p, MI_Sint64, self->size);
        p->data = NULL;
        *value = p; 
        return 0;
    }

    /* Verify that array is homogeneous (all elements have same type) */
    for (i = 1; i < self->size; i++)
    {
        if (self->data[0].type != self->data[i].type)
            return -1;
    }

    /* Verify that scalars have exactly 1 initializer */
    if (!self->isArray && self->size != 1)
        return -1;

    /* Convert to a Statik value */
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

                        for (i = 0; i < self->size; i++)
                        {
                            MI_Sint64 x = self->data[i].value.integer;
                            if (0 != _CheckRange(state, x, MI_UINT8))
                                return -1;

                            p->data[i] = (MI_Uint8)x;
                        }

                        *value = p; 
                        return 0;
                    }
                    case MI_SINT8A:
                    {
                        MI_Sint8A* p;
                        NEW_ARRAY_T(p, MI_Sint8, self->size);

                        for (i = 0; i < self->size; i++)
                        {
                            MI_Sint64 x = self->data[i].value.integer;
                            if (0 != _CheckRange(state, x, MI_SINT8))
                                return -1;

                            p->data[i] = (MI_Sint8)x;
                        }

                        *value = p; 
                        return 0;
                    }
                    case MI_UINT16A:
                    {
                        MI_Uint16A* p;
                        NEW_ARRAY_T(p, MI_Uint16, self->size);

                        for (i = 0; i < self->size; i++)
                        {
                            MI_Sint64 x = self->data[i].value.integer;
                            if (0 != _CheckRange(state, x, MI_UINT16))
                                return -1;

                            p->data[i] = (MI_Uint16)x;
                        }

                        *value = p; 
                        return 0;
                    }
                    case MI_SINT16A:
                    {
                        MI_Sint16A* p;
                        NEW_ARRAY_T(p, MI_Sint16, self->size);

                        for (i = 0; i < self->size; i++)
                        {
                            MI_Sint64 x = self->data[i].value.integer;
                            if (0 != _CheckRange(state, x, MI_SINT16))
                                return -1;

                            p->data[i] = (MI_Sint16)x;
                        }

                        *value = p; 
                        return 0;
                    }
                    case MI_UINT32A:
                    {
                        MI_Uint32A* p;
                        NEW_ARRAY_T(p, MI_Uint32, self->size);

                        for (i = 0; i < self->size; i++)
                        {
                            MI_Sint64 x = self->data[i].value.integer;
                            if (0 != _CheckRange(state, x, MI_UINT32))
                                return -1;

                            p->data[i] = (MI_Uint32)x;
                        }

                        *value = p; 
                        return 0;
                    }
                    case MI_SINT32A:
                    {
                        MI_Sint32A* p;
                        NEW_ARRAY_T(p, MI_Sint32, self->size);

                        for (i = 0; i < self->size; i++)
                        {
                            MI_Sint64 x = self->data[i].value.integer;
                            if (0 != _CheckRange(state, x, MI_SINT32))
                                return -1;

                            p->data[i] = (MI_Sint32)x;
                        }

                        *value = p; 
                        return 0;
                    }
                    case MI_UINT64A:
                    {
                        MI_Uint64A* p;
                        NEW_ARRAY_T(p, MI_Uint64, self->size);

                        for (i = 0; i < self->size; i++)
                        {
                            MI_Sint64 x = self->data[i].value.integer;
                            if (0 != _CheckRange(state, x, MI_UINT64))
                                return -1;

                            p->data[i] = (MI_Uint64)x;
                        }

                        *value = p; 
                        return 0;
                    }
                    case MI_SINT64A:
                    {
                        MI_Sint64A* p;
                        NEW_ARRAY_T(p, MI_Sint64, self->size);

                        for (i = 0; i < self->size; i++)
                        {
                            MI_Sint64 x = self->data[i].value.integer;
                            if (0 != _CheckRange(state, x, MI_SINT64))
                                return -1;

                            p->data[i] = (MI_Sint64)x;
                        }

                        *value = p; 
                        return 0;
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

                        for (i = 0; i < self->size; i++)
                        {
                            p->data[i] = (MI_Real32)
                                self->data[i].value.real;
                        }

                        *value = p; 
                        return 0;
                    }
                    case MI_REAL64A:
                    {
                        MI_Real64A* p;
                        NEW_ARRAY_T(p, MI_Real64, self->size);

                        for (i = 0; i < self->size; i++)
                        {
                            p->data[i] = (MI_Real64)
                                self->data[i].value.real;
                        }

                        *value = p; 
                        return 0;
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

                        for (i = 0; i < self->size; i++)
                        {
                            p->data[i] = (MI_Char16)
                                self->data[i].value.character;
                        }

                        *value = p; 
                        return 0;
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

                        for (i = 0; i < self->size; i++)
                        {
                            p->data[i] = self->data[i].value.string;
                            self->data[i].value.string = NULL;
                        }

                        *value = p; 
                        return 0;
                    }
                    case MI_DATETIMEA:
                    {
                        MI_DatetimeA* p;
                        NEW_ARRAY_T(p, MI_Datetime, self->size);

                        for (i = 0; i < self->size; i++)
                        {
                            if (_StrToDatetime(mofstate,
                                self->data[i].value.string, 
                                &p->data[i]) != 0)
                            {
                                return -1;
                            }
                            self->data[i].value.string = NULL;
                        }

                        *value = p; 
                        return 0;
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

                        for (i = 0; i < self->size; i++)
                        {
                            p->data[i] = (MI_Boolean)
                                self->data[i].value.boolean;
                        }

                        *value = p; 
                        return 0;
                    }
                    default:
                        return -1;
                }
            }
            case TOK_NULL:
            {
                *value = NULL;
                return 0;
            }
            case TOK_ALIAS_IDENTIFIER:
            {
                switch (type)
                {
                    case MI_INSTANCEA:
                    case MI_REFERENCEA:
                    {
                        MI_InstanceA* arr;
                        arr = (MI_InstanceA*)Batch_Get(state->batch, sizeof(MI_InstanceA) + sizeof(MI_Instance*)*self->size);
                        arr->data = (MI_Instance**)(arr + 1);
                        arr->size = self->size;
                        for (i = 0; i < self->size; i++)
                        {
                            const MI_Char* alias = self->data[i].value.string;
                            const MI_InstanceAliasDecl *decl = FindInstanceAliasDecl(state, alias);
                            if (!decl)
                            {
                                yyerrorf(state->errhandler, ID_UNDEFINED_INSTANCE_ALIAS,
                                    "",
                                    tcs(alias));
                                return -1;
                            }
                            arr->data[i] = decl->decl->instance;
                            decl->decl->refs++;
                        }
                        *value = arr; 
                        return 0;
                    }
                    default:
                        return -1;
                }
                break;
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
                        MI_Sint64 x = self->data->value.integer;
                        if (0 != _CheckRange(state, x, MI_UINT8))
                            return -1;

                        *p = (MI_Uint8)x;
                        *value = p; 
                        return 0;
                    }
                    case MI_SINT8:
                    {
                        MI_Sint8* p = MALLOC_T(MI_Sint8, 1);
                        MI_Sint64 x = self->data->value.integer;
                        if (0 != _CheckRange(state, x, MI_SINT8))
                            return -1;

                        *p = (MI_Sint8)x;
                        *value = p; 
                        return 0;
                    }
                    case MI_UINT16:
                    {
                        MI_Uint16* p = MALLOC_T(MI_Uint16, 1);
                        MI_Sint64 x = self->data->value.integer;
                        if (0 != _CheckRange(state, x, MI_UINT16))
                            return -1;

                        *p = (MI_Uint16)x;
                        *value = p; 
                        return 0;
                    }
                    case MI_SINT16:
                    {
                        MI_Sint16* p = MALLOC_T(MI_Sint16, 1);
                        MI_Sint64 x = self->data->value.integer;
                        if (0 != _CheckRange(state, x, MI_SINT16))
                            return -1;

                        *p = (MI_Sint16)x;
                        *value = p; 
                        return 0;
                    }
                    case MI_UINT32:
                    {
                        MI_Uint32* p = MALLOC_T(MI_Uint32, 1);
                        MI_Sint64 x = self->data->value.integer;
                        if (0 != _CheckRange(state, x, MI_UINT32))
                            return -1;

                        *p = (MI_Uint32)x;
                        *value = p; 
                        return 0;
                    }
                    case MI_SINT32:
                    {
                        MI_Sint32* p = MALLOC_T(MI_Sint32, 1);
                        MI_Sint64 x = self->data->value.integer;
                        if (0 != _CheckRange(state, x, MI_SINT32))
                            return -1;

                        *p = (MI_Sint32)x;
                        *value = p; 
                        return 0;
                    }
                    case MI_UINT64:
                    {
                        MI_Uint64* p = MALLOC_T(MI_Uint64, 1);
                        MI_Sint64 x = self->data->value.integer;
                        if (0 != _CheckRange(state, x, MI_UINT64))
                            return -1;

                        *p = (MI_Uint64)x;
                        *value = p; 
                        return 0;
                    }
                    case MI_SINT64:
                    {
                        MI_Sint64* p = MALLOC_T(MI_Sint64, 1);
                        MI_Sint64 x = self->data->value.integer;
                        if (0 != _CheckRange(state, x, MI_SINT64))
                            return -1;

                        *p = (MI_Sint64)x;
                        *value = p; 
                        return 0;
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
                        *p = (MI_Real32)self->data->value.real;
                        *value = p; 
                        return 0;
                    }
                    case MI_REAL64:
                    {
                        MI_Real64* p = MALLOC_T(MI_Real64, 1);
                        *p = (MI_Real64)self->data->value.real;
                        *value = p; 
                        return 0;
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
                        *p = (MI_Char16)self->data->value.character;
                        *value = p; 
                        return 0;
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
                        MI_Char *p = self->data->value.string;
                        MI_Char **pp = (MI_Char **)Batch_Get(state->batch, sizeof(MI_Char*));
                        if (!pp)
                        {
                            yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
                            return -1;
                        }
                        self->data->value.string = NULL;
                        *pp = p;
                        *value = pp; 
                        return 0;
                    }
                    case MI_DATETIME:
                    {
                        MI_Datetime *p = MALLOC_T(MI_Datetime, 1);

                        if (_StrToDatetime(mofstate, self->data->value.string, p) != 0)
                        {
                            return -1;
                        }

                        self->data->value.string = NULL;
                        *value = p; 
                        return 0;
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
                        *p = (MI_Boolean)self->data->value.boolean;
                        *value = p; 
                        return 0;
                    }
                    default:
                        return -1;
                }
                break;
            }
            case TOK_NULL: {
                *value = NULL;
                return 0;
            }
            case TOK_ALIAS_IDENTIFIER:
            {
                switch (type)
                {
                    case MI_INSTANCE:
                    case MI_REFERENCE:
                    {
                        MI_Instance* inst;
                        const MI_Char* alias = self->data->value.string;
                        const MI_InstanceAliasDecl *decl = FindInstanceAliasDecl(state, alias);
                        if (!decl)
                        {
                            yyerrorf(state->errhandler, ID_UNDEFINED_INSTANCE_ALIAS,
                                "undefined alias : '%s'",
                                tcs(alias));
                            return -1;
                        }
                        self->data->value.string = NULL;
                        inst = decl->decl->instance;
                        decl->decl->refs++;

                        {
                            MI_Instance **pp = (MI_Instance **)Batch_Get(state->batch, sizeof(MI_Instance *));
                            if (!pp)
                            {
                                yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
                                return -1;
                            }
                            *pp = inst;
                            *value = pp;
                        }
                        return 0;
                    }
                    default:
                        return -1;
                }
                break;
            }
            default:
                return -1;
        }
    }

    UNREACHABLE_RETURN( return 0; )
}

void ReleaseInitializer(
    void * mofstate,
    MOF_Initializer* init)
{
    MI_UNREFERENCED_PARAMETER(mofstate);
    if (init)
    {
        if (init->data)
        {
            size_t i;

            for (i = 0; i < init->size; i++)
            {
                if (init->data[i].type == TOK_STRING_VALUE)
                {
                }
                //MOF_Free(state, init->data[i].value.string);
            }
            //MOF_Free(state, init->data);
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
            Zfprintf(file, MI_T(" %s"), tcs(_flags[i].name));
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
    Zfprintf(file, MI_T("name: %s\n"), tcs(self->name));

    /* type */
    _indent(level, file);
    fprintf(file,"type: %s\n", _getTypeName((MI_Type)self->type));

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

static void _DatetimeToStr(const MI_Datetime* x, _Pre_writable_size_(26) MI_Char buf[26])
{
    if (x->isTimestamp)
    {
        const ZChar FMT[] =  MI_T("%04d%02d%02d%02d%02d%02d.%06d%c%03d");
        MI_Sint32 utc = x->u.timestamp.utc;
        SZprintf(buf, 26, FMT,
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
        const ZChar FMT[] = MI_T("%08u%02u%02u%02u.%06u:000");
        SZprintf(buf, 26, FMT,
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
                MI_Char buf[26];
                _DatetimeToStr((const MI_Datetime*)value, buf);
                Zfprintf(file, MI_T(" %s"), buf);
                break;
            }
            case MI_STRING:
            {
                Zfprintf(file, MI_T(" %s"), tcs(((const MI_Char*)value)));
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
                    Zfprintf(file, MI_T("%s"), tcs(arr->data[i]));

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

const MI_QualifierDecl* _FindQualifierDeclarationIntl(
    _In_ MOF_QualifierDeclList * list,
    _In_z_ const MI_Char* name)
{
    size_t i;
    for (i = 0; i < list->size; i++)
    {
        if (Tcscasecmp(list->data[i]->name, name) == 0)
            return list->data[i];
    }
    return NULL;
}

_Use_decl_annotations_
const MI_QualifierDecl* FindQualifierDeclaration(
    void * mofstate,
    const MI_Char* name)
{
    MOF_State * state = (MOF_State *)mofstate;
    const MI_QualifierDecl* decl = _FindQualifierDeclarationIntl(&state->qualifierDecls, name);

    if (decl == NULL)
    {
        /* Not found, fall back to global qualifiers */
        if (g_d.inited)
        {
            decl = _FindQualifierDeclarationIntl(&g_d.qualifierDecls, name);
        }
    }

    if ((decl == NULL) && state->parser->param.callbacks.qualifierDeclNeeded)
    {
        /* Fallback to callback */
        MI_Result r;
        MI_QualifierDecl* qdecl = (MI_QualifierDecl*)Batch_GetClear(
            state->batch, sizeof(MI_QualifierDecl));
        if (decl == NULL)
        {
            yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
        }
        qdecl->name = (MI_Char*)name;
        r = state->parser->param.callbacks.qualifierDeclNeeded(
            state->parser->param.callbacks.qualifierDeclNeededContext,
            qdecl);
        if (r == MI_RESULT_OK)
        {
            /* Add the declaration for future use */
            if (Codec_PtrArray_Append(state, (PtrArray*)&state->qualifierDecls, qdecl) != 0)
                return NULL;
            decl = qdecl;
        }
    }
    return decl;
}

int AddQualifierDeclaration(
    void * mofstate,
    MI_QualifierDecl* qd)
{
    MOF_State * state = (MOF_State *)mofstate;
    if (_FindQualifierDeclarationIntl(&state->qualifierDecls, qd->name))
    {
        yyerrorf(state->errhandler, ID_QUALIFIER_ALREADY_DECLARED, 
            "qualifier already declared: '%T'", 
            tcs(qd->name));
        return -1;
    }

    /* Validate some qualifiers */
    if (Tcscasecmp(qd->name, MI_T("MaxValue")) == 0 && qd->type != MI_SINT64)
    {
        yyerrorf(state->errhandler, ID_WRONG_TYPE_FOR_QUALIFIER, 
            "wrong type for standard %T qualifier", MI_T("MaxValue"));
        return -1;
    }
    else if (Tcscasecmp(qd->name, MI_T("MinValue")) == 0 && qd->type != MI_SINT64)
    {
        yyerrorf(state->errhandler, ID_WRONG_TYPE_FOR_QUALIFIER, 
            "wrong type for standard %T qualifier", MI_T("MinValue"));
        return -1;
    }
    else if (Tcscasecmp(qd->name, MI_T("MinLen")) == 0 && qd->type != MI_UINT32)
    {
        yyerrorf(state->errhandler, ID_WRONG_TYPE_FOR_QUALIFIER, 
            "wrong type for standard %T qualifier", MI_T("MinLen"));
        return -1;
    }
    else if (Tcscasecmp(qd->name, MI_T("MaxLen")) == 0 && qd->type != MI_UINT32)
    {
        yyerrorf(state->errhandler, ID_WRONG_TYPE_FOR_QUALIFIER, 
            "wrong type for standard %T qualifier", MI_T("MaxLen"));
        return -1;
    }

    /* Add the declaration */
    return Codec_PtrArray_Append(state, (PtrArray*)&state->qualifierDecls, qd);
}

/* Add string to hash table */
const MI_ClassDecl* _FindClassDeclFromHash(
    _In_ void * mofstate,
    _In_z_ const MI_Char* name)
{
    MOF_State * state = (MOF_State *)mofstate;
    if(state->classDeclsHash.nodes)
    {
        MI_Uint32 pos = StringHash_Find(&state->classDeclsHash, name);
        if (pos != HASH_INVALID_POS)
        {
            _Analysis_assume_(pos < state->classDecls.size);
            return state->classDecls.data[pos];
        }
    }
    return NULL;
}

/* Add string to hash table */
int _AddClasDeclToHash(
    _In_ void * mofstate,
    _In_ MI_ClassDecl* cd,
    _In_ MI_Uint32 pos)
{
    MOF_State * state = (MOF_State *)mofstate;
    int c = StringHash_Add(state->batch, &state->classDeclsHash, pos, cd->code, cd->name);
    if (c != 0)
    {
        yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
    }
    return c;
}

int _InitializeSchemaHash(_In_ void * mofstate,
    _In_ MOF_CODEC_PARAM *p)
{
    MI_Uint32 i;
    MOF_State * state = (MOF_State *)mofstate;
    int c = StringHash_Init(state->batch, &p->schemasHash);
    if (c != 0)
    {
        yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
        return -1;
    }
    for (i = 0; i < p->schemas->size; i++)
    {
        if (p->schemas->data[i])
        {
            const MI_Char* name = p->schemas->data[i]->classDecl->name;
            c = StringHash_Add(state->batch, &p->schemasHash, i, Hash(name), name);
            if (c != 0)
            {
                yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
                return -1;
            }
        }
    }
    return 0;
}

const MI_ClassDecl* FindClassDeclBufferOnly(
    void * mofstate,
    const MI_Char* name)
{
    MI_Uint32 i;
    MOF_State * state = (MOF_State *)mofstate;
    const MI_ClassDecl * decl = NULL;
    if (state->classDecls.size > HASH_THRESHOLD)
    {
        decl = _FindClassDeclFromHash(state, name);
    }
    else
    {
        for (i = 0; i < state->classDecls.size; i++)
        {
            if (Tcscasecmp(state->classDecls.data[i]->name, name) == 0)
            {
                decl = state->classDecls.data[i];
                break;
            }
        }
    }
    state->internalstate.isClassDeclFromBuffer = (decl) ? MI_TRUE : MI_FALSE;
    return decl;
}

const MI_ClassDecl* FindClassDecl(
    void * mofstate,
    const MI_Char* name)
{
    MI_Uint32 i;
    MOF_State * state = (MOF_State *)mofstate;
    const MI_ClassDecl * decl = FindClassDeclBufferOnly(state, name);
    if (decl) return decl;
    /* Not found, fallback to input schemas */
    {
        MOF_CODEC_PARAM *p = &state->parser->param;
        MI_ClassA * schemas = p->schemas;
        if (schemas)
        {
            if (p->schemas->size > HASH_THRESHOLD)
            {
                if (!p->schemasHash.nodes ) 
                {
                    /* Hash table is not initialized yet*/
                    if (_InitializeSchemaHash(mofstate, p) != 0)
                        return NULL;
                }
                /* Search hash table */
                {
                    MI_Uint32 pos = StringHash_Find(&p->schemasHash, name);
                    if (pos != HASH_INVALID_POS)
                        return schemas->data[pos]->classDecl;
                }
            }
            else
            {
                for (i = 0; i < schemas->size; i++)
                {
                    if (schemas->data[i])
                    {
                        if (Tcscasecmp(schemas->data[i]->classDecl->name, name) == 0)
                            return schemas->data[i]->classDecl;
                    }
                }
            }
        }
    }

    /* Not found, fallback to classobjectneeded classes cache */
    for (i = 0; i < state->parser->classaObjectNeeded.size; i++)
    {
        MI_ClassDecl *decl = state->parser->classaObjectNeeded.data[i]->classDecl;
        if (Tcscasecmp(decl->name, name) == 0)
            return decl;
    }

    /* Fall back to callback */
    if (state->parser->param.callbacks.classObjectNeeded)
    {
        MI_Class * c = NULL;
        MI_Result r = state->parser->param.callbacks.classObjectNeeded(
            state->parser->param.callbacks.classObjectNeededContext,
            state->parser->param.serverName,
            state->parser->param.namespaceName,
            name,
            &c);
        if( r == MI_RESULT_OK)
        {
            if ((c == NULL)|| (Tcscasecmp(c->classDecl->name, name) != 0))
            {
                /* Not find the class */
                if (c) MI_Class_Delete(c);
                return NULL;
            }
            /* parser now hold a reference to the MI_Class */
            if (Codec_PtrArray_Append(state, (PtrArray*)&state->parser->classaObjectNeeded, c)  != 0)
                return NULL;
            return c->classDecl;
        }
    }
    return NULL;
}

int AddClassDecl(
    void * mofstate,
    MI_ClassDecl* cd)
{
    MOF_State * state = (MOF_State *)mofstate;
    cd->code = Hash(cd->name);
    if (FindClassDeclBufferOnly(state, cd->name))
    {
        yyerrorf(state->errhandler, ID_CLASS_ALREADY_DEFINED, "class already declared: \"%T\"", 
            tcs(cd->name));
        return -1;
    }

    /* Add the declaration */
    if (Codec_PtrArray_Append(state, (PtrArray*)&state->classDecls, cd) != 0)
        return -1;

    /* Add the declaration to hash table */
    if (state->classDecls.size == HASH_THRESHOLD)
    {
        /* Initialize hash */
        MI_Uint32 i =0;
        if (StringHash_Init(state->batch, &state->classDeclsHash) != 0)
        {
            yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
            return -1;
        }
        for(; i < state->classDecls.size; i++)
        {
            if (_AddClasDeclToHash(state, state->classDecls.data[i], i)!=0)
                return -1;
        }
    }
    else if (state->classDecls.size > HASH_THRESHOLD)
    {
        return _AddClasDeclToHash(state, cd, state->classDecls.size - 1);
    }
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
    Zfprintf(file, MI_T("name: %s\n"), tcs(self->name));

    /* type */
    _indent(level, file);
    fprintf(file, "type: %s\n", _getTypeName((MI_Type)self->type));

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
    Zfprintf(file, MI_T("name: %s\n"), tcs(self->name));

    /* type */
    _indent(level, file);
    fprintf(file, "type: %s\n", _getTypeName((MI_Type)self->type));

    /* className */
    if (self->className)
    {
        _indent(level, file);
        Zfprintf(file, MI_T("className: %s\n"), tcs(self->className));
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
    Zfprintf(file, MI_T("name: %s\n"), tcs(self->name));

    /* type */
    _indent(level, file);
    fprintf(file, "type: %s\n", _getTypeName((MI_Type)self->type));

    /* subscript */
    _indent(level, file);
    fprintf(file,"subscript: %u\n", self->subscript);

    /* className */
    if (self->className)
    {
        _indent(level, file);
        Zfprintf(file, MI_T("className: %s\n"), tcs(self->className));
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
        Zfprintf(file, MI_T("origin: %s\n"), tcs(self->origin));
    }

    /* propagator */
    if (self->propagator)
    {
        _indent(level, file);
        Zfprintf(file, MI_T("propagator: %s\n"), tcs(self->propagator));
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
    Zfprintf(file, MI_T("name: %s\n"), tcs(self->name));

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
        Zfprintf(file, MI_T("origin: %s\n"), tcs(self->origin));
    }

    /* propagator */
    if (self->propagator)
    {
        _indent(level, file);
        Zfprintf(file, MI_T("propagator: %s\n"), tcs(self->propagator));
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

_Use_decl_annotations_
MI_PropertyDecl* FindProperty(
    MOF_PropertyList* self,
    const MI_Char* name)
{
    MI_Uint32 i;

    if (!self)
        return NULL;

    for (i = 0; i < self->size; i++)
    {
        if (Tcscasecmp(self->data[i]->name, name) == 0)
            return self->data[i];
    }

    /* Not found */
    return NULL;
}

_Use_decl_annotations_
MI_ParameterDecl* FindParameter(
    MOF_ParameterList* self,
    const MI_Char* name)
{
    size_t i;

    if (!self)
        return NULL;

    for (i = 0; i < self->size; i++)
    {
        if (Tcscasecmp(self->data[i]->name, name) == 0)
            return self->data[i];
    }

    /* Not found */
    return NULL;
}

_Use_decl_annotations_
MI_MethodDecl* FindMethod(
    MOF_MethodList* self,
    const ZChar* name)
{
    size_t i;

    if (!self)
        return NULL;

    for (i = 0; i < self->size; i++)
    {
        if (Tcscasecmp(self->data[i]->name, name) == 0)
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
    Zfprintf(file, MI_T("name: %s\n"), tcs(self->name));

    /* superClass  */
    _indent(level, file);
    Zfprintf(file, MI_T("superClass: %s\n"), tcs(self->superClass));

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
    Zfprintf(file, MI_T("name: %s\n"), tcs(self->name));

    /* size */
    _indent(level, file);
    fprintf(file,"size: %u\n", self->size);

    /* properties */
    if (self->properties)
        _PrintProperties(self->properties, self->numProperties, level, file);

    /* qualifiers */
    if (self->qualifiers)
        _PrintQualifiers(self->qualifiers, self->numQualifiers, level, file);

    /* Footer */
    level--;
    _indent(level, file);
    fprintf(file,"}\n");
}

MI_Uint32 GetQualFlags(
    void * mofstate,
    MI_Qualifier** qualifiers,
    size_t numQualifiers)
{
    MI_Uint32 flags = 0;
    size_t i;
    MOF_State * state = (MOF_State *)mofstate;

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
                if (Tcscasecmp(q->name, _flags[j].name) == 0)
                {
                    MI_Boolean* p = (MI_Boolean*)q->value;

                    if (p && *p)
                        flags |= _flags[j].flag;
                }
            }
        }

        if (q->type == MI_STRING &&
            Tcscasecmp(q->name, MI_T("EmbeddedInstance")) == 0)
        {
            MOF_EmbeddedInstance* p;

            /* Create line-address pair */
            {
                p = CALLOC_T(MOF_EmbeddedInstance, 1);

                if (!p)
                {
                    yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
                    return 0;
                }

                p->qualifier = (MI_Qualifier*)q;
                p->line = state->buf.lineNo;
            }

            /* Append to 'lines' list */
            if (Codec_PtrArray_Append(state, (PtrArray*)(void*)&state->embeddedInstanceList, p) != 0)
                return 0;
        }
    }

    return flags;
}

void* NewTrueValue(
    void * mofstate)
{
    MOF_State * state = (MOF_State *)mofstate;
    MI_Boolean* p = (MI_Boolean*)Batch_Get(state->batch, sizeof(MI_Boolean));

    if (!p)
        return NULL;

    *p = 1;
    return p;
}

static MI_Uint32 _FindPropertyDecl(
    MOF_PropertyList* self,
    const MI_Char* name)
{
    MI_Uint32 i;

    for (i = 0; i < self->size; i++)
    {
        if (Tcscasecmp(self->data[i]->name, name) == 0)
            return i;
    }

    /* Not found! */
    return MOF_NOT_FOUND;
}

static MI_Uint32 _FindMethodDecl(
    MOF_MethodList* self,
    const MI_Char* name)
{
    MI_Uint32 i;

    for (i = 0; i < self->size; i++)
    {
        if (Tcscasecmp(self->data[i]->name, name) == 0)
            return i;
    }

    /* Not found! */
    return MOF_NOT_FOUND;
}

MI_Uint32 _FindQualifierPos(
    MOF_QualifierList* self,
    const MI_Char* name)
{
    MI_Uint32 i;

    for (i = 0; i < self->size; i++)
    {
        if (Tcscasecmp(self->data[i]->name, name) == 0)
            return i;
    }

    /* Not found! */
    return MOF_NOT_FOUND;
}

_Use_decl_annotations_
MI_Qualifier* FindQualifier(
    MOF_QualifierList* self, 
    const MI_Char* name)
{
    size_t i;

    if (!self)
        return NULL;

    for (i = 0; i < self->size; i++)
    {
        if (Tcscasecmp(self->data[i]->name, name) == 0)
            return self->data[i];
    }

    /* Not found! */
    return NULL;
}

_Use_decl_annotations_
MI_Boolean IsEmbeddedQualifier(const MI_Char* name)
{
    if (Tcscasecmp(name, MI_T("EmbeddedInstance")) == 0)
    {
        return MI_TRUE;
    }
    if (Tcscasecmp(name, MI_T("EmbeddedObject")) == 0)
    {
        return MI_TRUE;
    }
    return MI_FALSE;
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
MI_Boolean Identical(
    void * mofstate,
    const void* v1, const void* v2, MI_Type type)
{
    MOF_State * state = (MOF_State *)mofstate;

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
            return Tcscmp(*(MI_Char**)v1, *(MI_Char**)v2) == 0;
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
                if (Tcscmp(a1->data[i], a2->data[i]) != 0)
                    return 0;
            }

            return 1;
        }
        default:
        {
            yyerrorf(state->errhandler, ID_INTERNAL_ERROR, "internal error: %s(%u)",
                __FILE__, __LINE__);
            return 0;
        }
    }
}

/*
**==============================================================================
**
** _FindEmbeddedQualifier()
**
**     It searches and returns "EmbeddedInstance" and "EmbeddedObject" qualifier
**     as well.
**==============================================================================
*/
static int _FindEmbeddedQualifier(
    _In_reads_(numQualifiers_) MI_Qualifier** qualifiers_,
    _In_ MI_Uint32 numQualifiers_,
    _Outptr_result_maybenull_ MI_Qualifier** embeddedQualifer)
{
    MI_Uint32 i;
    *embeddedQualifer = NULL;
    for (i = 0; i < numQualifiers_; i++)
    {
        if (IsEmbeddedQualifier(qualifiers_[i]->name))
        {
            *embeddedQualifer = qualifiers_[i];
            break;
        }
    }
    return 0;
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
**     Propation is performed using the MI_Qualifier.flavor whose bits may be
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
    void * mofstate,
    const MI_Char* className,
    const MI_Char* featureName,
    MI_Qualifier** derived,
    MI_Uint32 numDerived,
    MI_Qualifier** inherited,
    MI_Uint32 numInherited,
    MI_Qualifier*** qualifiers_,
    MI_Uint32* numQualifiers_)
{
    MOF_QualifierList qualifierList = PTRARRAY_INITIALIZER;
    MI_Uint32 i;
    MOF_State * state = (MOF_State *)mofstate;

    /* Propagate non-restricted inherited qualifiers */
    for (i = 0; i < numInherited; i++)
    {
        MI_Qualifier* q = inherited[i];

        if (!(q->flavor & MI_FLAG_RESTRICTED))
        {
            q->flavor = SetDefaultFlavors(q->flavor);
            if (Codec_PtrArray_Append(state, (PtrArray*)(void*)&qualifierList, q) != 0)
                return -1;
        }
    }

    /* Apply derived qualifiers */
    for (i = 0; i < numDerived; i++)
    {
        MI_Qualifier* q = derived[i];
        MI_Uint32 pos = _FindQualifierPos(&qualifierList, q->name);

        if (pos == MOF_NOT_FOUND)
        {
            q->flavor = SetDefaultFlavors(q->flavor);
            if (Codec_PtrArray_Append(state, (PtrArray*)(void*)&qualifierList, q) != 0)
                return -1;
        }
        else
        {
            _Analysis_assume_(qualifierList.data);

            /* If DisableOverride flavor, then disallow value change */
            if (qualifierList.data[pos]->flavor & MI_FLAG_DISABLEOVERRIDE &&
                !Identical(state, qualifierList.data[pos]->value, q->value, (MI_Type)q->type))
            {
                if (featureName)
                {
                    yyerrorf(state->errhandler, ID_ILLEGAL_QUALIFIER_OVERRIDE,
                        "illegal qualifier override: %T.%T.%T",
                        tcs(className), 
                        tcs(featureName), 
                        tcs(q->name));
                }
                else
                {
                    yyerrorf(state->errhandler, ID_ILLEGAL_QUALIFIER_OVERRIDE, 
                        "illegal qualifier override: %T.%T.%T",
                        MI_T(""),
                        tcs(className), 
                        tcs(q->name));
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
    void * mofstate,
    MI_ClassDecl* cd)
{
    size_t i, j;
    MOF_PropertyList propertySet = PTRARRAY_INITIALIZER;
    MOF_State * state = (MOF_State *)mofstate;

    /* First inherit properties from finalized super class */
    if (cd->superClass)
    {
        const MI_ClassDecl* super;
        
        /* Retrieve the super class */
        super = FindClassDecl(state, cd->superClass);

        if (!super)
        {
            yyerrorf(state->errhandler,
                ID_UNDEFINED_CLASS,
                "Undefined class: '%T'", 
                tcs(cd->superClass));
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
                state,
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

            //MOF_Free(state, cd->qualifiers);
            cd->qualifiers = qualifiers;
            cd->numQualifiers = numQualifiers;
            cd->flags |= GetQualFlags(state, cd->qualifiers, cd->numQualifiers);
        }

        /* Clone the superclass property array */
        for (i = 0; i < super->numProperties; i++)
        {
            if (Codec_PtrArray_Append(state, (PtrArray*)(void*)&propertySet, 
                super->properties[i]) != 0)
                return -1;
        }
    }

    /* Now append local properties (overriding as necessary) */
    for (i = 0; i < cd->numProperties; i++)
    {
        MI_PropertyDecl* pd = cd->properties[i];
        MI_Uint32 pos;
        MI_Qualifier* embeddedQualifier = NULL;

        /* Set hash code value to propertydecl if not has */
        if (pd->code == 0)
        {
            pd->code = Hash(pd->name);
        }

        /* Set MI_PropertyDecl.propagator */
        pd->propagator = Batch_Tcsdup(state->batch, cd->name);

        /* Set NULL flag to property */
        if (!(pd->flags & MI_FLAG_NULL) && !pd->value)
        {
            pd->flags |= MI_FLAG_NULL;
        }

        /* See if the property is already in the list */

        pos = _FindPropertyDecl(&propertySet, pd->name);

        if (pos == MOF_NOT_FOUND)
        {
            /* set default flavor to qualifers */
            for (j = 0; j < pd->numQualifiers; j++)
            {
                pd->qualifiers[j]->flavor = SetDefaultFlavors(pd->qualifiers[j]->flavor);
            }

            /* First time this property has been seen in hierarchy */
            pd->origin = Batch_Tcsdup(state->batch, cd->name);

            if (Codec_PtrArray_Append(state, (PtrArray*)(void*)&propertySet, pd) != 0)
                return -1;
        }
        else
        {
            MI_Qualifier** qualifiers;
            MI_Uint32 numQualifiers;

            /* This property overrides an inherited property */
            _Analysis_assume_(propertySet.data);

            if (_FinalizeQualifiers(
                state,
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

            // MOF_Free(state, pd->qualifiers);
            pd->qualifiers = qualifiers;
            pd->numQualifiers = numQualifiers;
            pd->flags |= GetQualFlags(state, qualifiers, numQualifiers);

            pd->origin = Batch_Tcsdup(state->batch, 
                propertySet.data[pos]->origin);

            /* Use the superclass casing for the property name */
            pd->name = propertySet.data[pos]->name;
            propertySet.data[pos] = pd;
        }
        _FindEmbeddedQualifier(pd->qualifiers, pd->numQualifiers, &embeddedQualifier);
        if (embeddedQualifier)
        {
            if (pd->type == MI_STRING)
            {
                pd->type = MI_INSTANCE;
            }
            else if (pd->type == MI_STRINGA)
            {
                pd->type = MI_INSTANCEA;
            }
            else
            {
                yyerrorf(state->errhandler,
                    ID_PROPERTY_QUALIFIER_INCOMPATIBLE,
                    "", /*unused parameter*/
                    embeddedQualifier->name,
                    pd->name,
                    _getTypeName_MI((MI_Type)pd->type));
                return -1;
            }

            if (embeddedQualifier->type == MI_STRING)
            {
                pd->className = *(MI_Char**)embeddedQualifier->value;
            }
        }
    }

    /* Replace local property list with aggregate property list */
    //MOF_Free(state, cd->properties);
    cd->properties = propertySet.data;
    cd->numProperties = propertySet.size;

    return 0;
}

static int _VerifyClassKeys(
    void * mofstate,
    const MI_ClassDecl* cd)
{
    MI_Uint32 i;
    const MI_ClassDecl* super;
    MI_Boolean superDefinedKeys = MI_FALSE;
    MOF_State * state = (MOF_State *)mofstate;

    /* If no super class, no validation needed */
    if (!cd->superClass)
        return 0;

        
    /* Retrieve the super class */
    super = FindClassDecl(state, cd->superClass);

    if (!super)
    {
        yyerrorf(state->errhandler, ID_UNDEFINED_CLASS, "undefined class: '%T'", 
            tcs(cd->superClass));
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
            if (Tcscasecmp(pd->name, super->properties[pos]->name) != 0)
                continue;

            foundInBase = MI_TRUE;

            /* new property is a key */
            if (pd->flags & MI_FLAG_KEY)
            {
                if ((super->properties[pos]->flags & MI_FLAG_KEY) == 0)
                {
                    yyerrorf(state->errhandler, ID_KEY_MUTATION_ERROR, 
                        "", /*unused*/
                        tcs(pd->name),
                        tcs(cd->name));
                    return -1;
                }
            }

            /* compare prop type */
            if ((pd->flags & MI_FLAG_KEY) != 0 ||
                (super->properties[pos]->flags & MI_FLAG_KEY) != 0)
            {
                if (pd->type != super->properties[pos]->type)
                {
                    yyerrorf(state->errhandler, ID_KEY_TYPE_MUTATION_ERROR, 
                        "", /*unused*/
                        tcs(pd->name),
                        tcs(cd->name));
                    return -1;
                }

            }

        }

        if (!foundInBase && (pd->flags & MI_FLAG_KEY) != 0)
        {
            yyerrorf(state->errhandler, ID_KEY_STRUCTURE_MUTATION_ERROR,
                "", 
                tcs(pd->name),
                tcs(cd->name));
            return -1;
        }
    }

    return 0;
}

static int _FinalizeClassMethods(
    void * mofstate,
    MI_ClassDecl* cd)
{
    size_t i, k;
    MOF_MethodList methodList = PTRARRAY_INITIALIZER;
    MOF_State * state = (MOF_State *)mofstate;

    /* First inherit methods from finalized super class */
    if (cd->superClass)
    {
        const MI_ClassDecl* super;
        
        /* Retrieve the super class */
        super = FindClassDecl(state, cd->superClass);

        if (!super)
        {
            yyerrorf(state->errhandler, ID_UNDEFINED_CLASS,
                "", 
                tcs(cd->superClass));
            return -1;
        }

        /* Propagate class qualifiers */
        {
            MI_Qualifier** qualifiers = NULL;
            MI_Uint32 numQualifiers = 0;

            /* This method overrides an inherited method */
            if (_FinalizeQualifiers(
                state,
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

            //MOF_Free(state, cd->qualifiers);
            cd->qualifiers = qualifiers;
            cd->numQualifiers = numQualifiers;
            cd->flags |= GetQualFlags(state, cd->qualifiers, cd->numQualifiers);
        }

        /* Clone the superclass method array */
        for (i = 0; i < super->numMethods; i++)
        {
            if (Codec_PtrArray_Append(state, (PtrArray*)(void*)&methodList, 
                super->methods[i]) != 0)
                return -1;
        }
    }

    /* Now append local methods (overriding as necessary) */
    for (i = 0; i < cd->numMethods; i++)
    {
        MI_MethodDecl* md = cd->methods[i];
        MI_Uint32 pos;

        /* Set hash code value to methoddecl if not has */
        if (md->code == 0)
        {
            md->code = Hash(md->name);
        }

        /* Set MI_MethodDecl.propagator */
        md->propagator = Batch_Tcsdup(state->batch, cd->name);

        /* See if the method is already in the list */

        pos = _FindMethodDecl(&methodList, md->name);

        if (pos == MOF_NOT_FOUND)
        {
            /* set default flavor to qualifers */
            for (k = 0; k < md->numQualifiers; k++)
            {
                md->qualifiers[k]->flavor = SetDefaultFlavors(md->qualifiers[k]->flavor);
            }

            /* First time this method has been seen in hierarchy */
            md->origin = Batch_Tcsdup(state->batch, cd->name);

            if (Codec_PtrArray_Append(state, (PtrArray*)(void*)&methodList, md) != 0)
                return -1;
        }
        else
        {
            MI_Qualifier** qualifiers;
            MI_Uint32 numQualifiers;

            _Analysis_assume_(methodList.data);

            /* This method overrides an inherited method */
            if (_FinalizeQualifiers(
                state,
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

            md->qualifiers = qualifiers;
            md->numQualifiers = numQualifiers;
            md->flags |= GetQualFlags(state, qualifiers, numQualifiers);

            md->origin = Batch_Tcsdup(state->batch, 
                methodList.data[pos]->origin);

            /* Use the superclass casing for the method name */
            md->name = methodList.data[pos]->name;
            methodList.data[pos] = md;
        }

        {
            size_t j;
            for(j = 0; j < md->numParameters; j++)
            {
                MI_Qualifier* embeddedQualifier = NULL;
                MI_ParameterDecl *pdecl = md->parameters[j];

                /* Set hash code value to parameterdecl if not has */
                if (pdecl->code == 0)
                {
                    pdecl->code = Hash(pdecl->name);
                }

                /* set default flavor to qualifers */
                for (k = 0; k < pdecl->numQualifiers; k++)
                {
                    pdecl->qualifiers[k]->flavor = SetDefaultFlavors(pdecl->qualifiers[k]->flavor);
                }

                pdecl->flags |= GetQualFlags(state, pdecl->qualifiers, pdecl->numQualifiers);

                _FindEmbeddedQualifier(pdecl->qualifiers, pdecl->numQualifiers, &embeddedQualifier);
                if (embeddedQualifier)
                {
                    if (pdecl->type == MI_STRING)
                    {
                        pdecl->type = MI_INSTANCE;
                    }
                    else if (pdecl->type == MI_STRINGA)
                    {
                        pdecl->type = MI_INSTANCEA;
                    }
                    else
                    {
                        yyerrorf(state->errhandler,
                            ID_PROPERTY_QUALIFIER_INCOMPATIBLE,
                            "",
                            embeddedQualifier->name,
                            pdecl->name,
                            _getTypeName_MI((MI_Type)pdecl->type));
                        return -1;
                    }

                    if (embeddedQualifier->type == MI_STRING)
                    {
                        pdecl->className = *(MI_Char**)embeddedQualifier->value;
                    }
                }
            }
        }

        /* Finalize method decl size and parameter offset */
        _FinalizeMethodSize(md);
    }

    /* Replace local method list with aggregate method list */
    //MOF_Free(state, cd->methods);
    cd->methods = methodList.data;
    cd->numMethods = methodList.size;

    return 0;
}

int FinalizeClass(
    void * mofstate,
    MI_ClassDecl* cd)
{
    MOF_State * state = (MOF_State *)mofstate;
    /* 
        Verify keys structure: 
        - derived class maynot introduce new keys or
            change key type if base class defined keys
    */
    if (_VerifyClassKeys(state, cd) != 0)
        return -1;

    /* Perform property propagation */
    if (_FinalizeClassProperties(state, cd) != 0)
        return -1;

    /* Perform method propagation */
    if (_FinalizeClassMethods(state, cd) != 0)
        return -1;

    if (_FinalizeClassSize(cd) != 0)
        return -1;

    return 0;
}

MI_Boolean IgnoreFinalizedInstance( _In_ MOF_State * state, const MI_Char *className)
{
    MI_Uint32 i;
    for(i=0; i< state->parser->param.ignorePropertyList.size; i++)
    {
        /*it will be the following format {"className:*","className2:prop1:prop2}*/
        MI_Char* thisIgnoreElement = state->parser->param.ignorePropertyList.data[i];
        MI_Char *delimData = Tcschr(thisIgnoreElement, MI_T(':'));
        // Process if we have valid data specified.
        if( !(delimData == NULL || *delimData == MI_T('\0') || (delimData+1) == NULL || *(delimData+1) == MI_T('\0')))
        {
            size_t classSize = delimData - thisIgnoreElement;
            // Check if we found a match. Assumption is that we will not have multiple entry for the same class, if we have we
            // will honor first one only. (Eg : OMI_BaseResource:*,OMI_BaseResource:prop1:prop2 -> in this case, we honor just the first one i.e OMI_Baseresource:*)
            if (Tcsncasecmp(thisIgnoreElement, className, classSize) == 0)
            {
                //If we have to ignore full instance
                if( *(delimData+1) == MI_T('*'))
                {
                    return MI_TRUE;
                }
                return MI_FALSE;
            }
        }
    }
    return MI_FALSE;
}

static MI_Char ** _CloneIgnorePropertyList(void *mofstate,
    const MI_Char* data,
    MI_Uint32 *propertyCount)
{
    size_t n = 0;
    MI_Char** array = NULL;
    MI_Char* ptr = (MI_Char*)data;
    MI_Char *delimData = NULL;
    MI_Uint32 elemCount = 0;
    MOF_State * state = (MOF_State *)mofstate;
    MI_Uint32 i = 0;

    /* Empty arrays are represented by NULL */
    if (!data || !propertyCount)
        return NULL;

    *propertyCount = 0;
    /* Calculate space for strings (add space for zero terminators) */
    do
    {
        delimData = Tcschr(ptr, MI_T(':'));
        if (delimData != NULL)
        {
            //Memory for the pointer
            n += sizeof(MI_Char*);
            //Memory for the object itself
            n += (delimData - ptr) + 1;
            ptr = delimData + 1;
        }
        else
        {
            //last element
            n += sizeof(MI_Char*);
            n += Tcslen(ptr) + 1;
        }
        elemCount++;
    } while (delimData != NULL && ptr != NULL);
    *propertyCount = elemCount;
    array = (MI_Char**)MALLOC_T(MI_Char*, elemCount);
    if (array == NULL)
    {
        return NULL;
    }
    ptr = (MI_Char*)data;
    for (i = 0; i < elemCount; i++)
    {
        delimData = Tcschr(ptr, MI_T(':'));
        if (NULL == delimData)
        {
            n = Tcslen(ptr) +1;
            array[i] = (MI_Char*)MALLOC_T(MI_Char, n);
            if (array[i] == NULL)
            {
                return NULL;
            }
            memcpy(array[i], ptr, n * sizeof(MI_Char));
            array[i][n - 1] = MI_T('\0');
        }
        else
        {
            n = (delimData - ptr) + 1;
            array[i] = (MI_Char*)MALLOC_T(MI_Char, n);
            if (array[i] == NULL)
            {
                return NULL;
            }
            memcpy(array[i], ptr, n * sizeof(MI_Char));
            array[i][n - 1] = MI_T('\0');
            ptr = delimData + 1;
        }
    }
    return array;
}

MI_INLINE MI_Boolean ProcessProperty(MI_Uint32 state, _In_z_ MI_Char* p, _In_reads_opt_(ignorePropertyCount) const MI_Char **ignorePropertyList, MI_Uint32 ignorePropertyCount)
{
    if (ignorePropertyList == NULL || *ignorePropertyList == NULL || p == NULL || ignorePropertyCount <=1)
    {
        return MI_TRUE;
    }
    
    if( state == SCHEMA_CHECK_DEFAULT_IGNORE_PROPERTIES ||
        state == SCHEMA_CHECK_STRICT_IGNORE_PROPERTIES)
    {
        MI_Uint32 i;
        /*First element in the property list is the className*/
        for( i=1; i< ignorePropertyCount; i++)
        {
            if(Tcscasecmp(p, ignorePropertyList[i]) == 0 )
            {
                return MI_FALSE;
            }
        }
    }
    return MI_TRUE;
}

int FinalizeInstance(
    void * mofstate,
    MI_InstanceDecl* id)
{
    const MI_ClassDecl* cd;
    MI_Char **ignorePropertyList = NULL;
    MI_Uint32 ignorePropertyCount = 0;
    MI_Uint32 i;
    MI_Uint32 j;
    MOF_State * state = (MOF_State *)mofstate;
    MI_Boolean validClassDecl = MI_TRUE;
    MI_Instance *inst = NULL;
    MI_Result r = MI_RESULT_OK;
    MI_Boolean isClassDeclFromBuffer = MI_FALSE;
    MI_Uint32 schemaCheckOption = state->parser->param.schemacheck;
    if (state->parser->param.ignorePropertyList.size == 0)
    {
        if (schemaCheckOption == SCHEMA_CHECK_DEFAULT_IGNORE_PROPERTIES)
            schemaCheckOption = SCHEMA_CHECK_IGNORE;
        else if (schemaCheckOption == SCHEMA_CHECK_STRICT_IGNORE_PROPERTIES)
        {
            schemaCheckOption = SCHEMA_CHECK_STRICT;
        }
    }
    /* Find the class declaration for this instance */
    {
        cd = FindClassDecl(state, id->name);
        if (!cd)
        {
            /* Process according to schema check option */
            switch (schemaCheckOption)
            {
            case SCHEMA_CHECK_DEFAULT:
            case SCHEMA_CHECK_IGNORE_PROPERTYTYPE:
            case SCHEMA_CHECK_STRICT:
            case SCHEMA_CHECK_LOOSE:
                {
                    yyerrorf(state->errhandler, ID_UNDEFINED_CLASS, "", id->name);
                    return -1;
                }
                break;
            case SCHEMA_CHECK_IGNORE:   
            case SCHEMA_CHECK_DEFAULT_IGNORE_PROPERTIES:                  
            case SCHEMA_CHECK_STRICT_IGNORE_PROPERTIES:                
                {
                    yywarnf(state->errhandler, ID_UNDEFINED_CLASS, "", id->name);
                    validClassDecl = MI_FALSE;
                }
                break;
            }
        }
        isClassDeclFromBuffer = state->internalstate.isClassDeclFromBuffer;
        id->decl = cd;
    }

    /*check if we need to ignore the instance*/
    if ((schemaCheckOption == SCHEMA_CHECK_DEFAULT_IGNORE_PROPERTIES ||
        schemaCheckOption == SCHEMA_CHECK_STRICT_IGNORE_PROPERTIES) &&
       IgnoreFinalizedInstance(state, id->name))
    {
        id->instance = NULL;
        return 0;
    }
    if (cd)
    {
        /* For each instance property */
        for (i = 0; i < id->numProperties; i++)
        {
            MI_PropertyDecl* p = id->properties[i];
            MI_PropertyDecl* q = NULL;

            /* Find the class property with the same name */
            {
                for (j = 0; j < cd->numProperties; j++)
                {
                    if (Tcscasecmp(cd->properties[j]->name, p->name) == 0)
                    {
                        q = cd->properties[j];
                        break;
                    }
                }

                if (!q)
                {
                    /* Process according to schema check option */
                    switch (schemaCheckOption)
                    {
                    case SCHEMA_CHECK_DEFAULT:
                    case SCHEMA_CHECK_IGNORE_PROPERTYTYPE:
                    case SCHEMA_CHECK_STRICT:
                        {
                            yyerrorf(state->errhandler, ID_UNDEFINED_PROPERTY, "", p->name);
                            return -1;
                        }
                        break;
                    case SCHEMA_CHECK_LOOSE:
                    case SCHEMA_CHECK_IGNORE:
                        {
                            yywarnf(state->errhandler, ID_UNDEFINED_PROPERTY, "", p->name);
                            validClassDecl = MI_FALSE;
                        }
                        break;
                    case SCHEMA_CHECK_DEFAULT_IGNORE_PROPERTIES:                  
                    case SCHEMA_CHECK_STRICT_IGNORE_PROPERTIES:      
                        {
                            yywarnf(state->errhandler, ID_UNDEFINED_PROPERTY, "", p->name);
                        }
                        break;
                    }
                }
            }

            if (q)
            {
                /* Promote instance property (to the type given by class property) */
                MI_Boolean embeddedpropertyError;
                if (_PromoteValue(state, p->type, q, &embeddedpropertyError, &p->value) != 0)
                {
                    // check return value from _PromoteValue
                    if (state->parser->param.schemacheck & SCHEMA_CHECK_IGNORE_PROPERTYTYPE)
                    {
                        yywarnf(state->errhandler, ID_CONVERT_PROPERTY_VALUE_FAILED,
                            "",
                            p->name,
                            _getTypeName_MI((MI_Type)p->type),
                            _getTypeName_MI((MI_Type)q->type));
                        validClassDecl = MI_FALSE;
                    }
                    else
                    {
                        if (MI_TRUE != embeddedpropertyError)
                        {
                            yyerrorf(state->errhandler, ID_CONVERT_PROPERTY_VALUE_FAILED,
                                "",
                                p->name,
                                _getTypeName_MI((MI_Type)p->type),
                                _getTypeName_MI((MI_Type)q->type));
                        }
                        return -1;
                    }
                }
                else
                {
                    /* Assume type of class property if success */
                    p->type = q->type;
                }
            }
        }
    }

    /* create instance base on instance decl */
    if (validClassDecl)
    {
        const MI_ClassDecl *newDecl = id->decl;
        if(isClassDeclFromBuffer)
        {
            r = state->onNewClassDecl(state->onNewClassDeclData,
                id->decl, (MI_ClassDecl**)&newDecl);
        }
        if (r == MI_RESULT_OK)
        {
            if (newDecl != id->decl) id->decl = newDecl;
            r = state->Instance_New(newDecl, &inst);
#ifdef TEST_BUILD
            TASSERT(r == MI_RESULT_OK, L"Ignore out of memory error in unit test fault injection.");
#endif
        }
    }
    else
    {
        r = state->Instance_InitDynamic(id->name, MI_FLAG_CLASS, &inst);
#ifdef TEST_BUILD
        TASSERT(r == MI_RESULT_OK, L"Ignore out of memory error in unit test fault injection.");
#endif
    }

    if (r != MI_RESULT_OK)
    {
        yyerrorf(state->errhandler, ID_MI_CREATEINSTANCE_FAILED,
            "",
            tcs(id->name),
            r);
        return -1;
    }
    if (state->parser->param.ignorePropertyList.size != 0)
    {
        /* If we are running in ignore property mode, get a list of properties that we want to ignore*/
        for (i = 0; i < state->parser->param.ignorePropertyList.size; i++)
        {
            /*it will be the following format {"className:*","className2:prop1:prop2}*/
            MI_Char *delimData = Tcschr(state->parser->param.ignorePropertyList.data[i], MI_T(':'));
            // Process if we have valid data specified.
            if (!(delimData == NULL || *delimData == MI_T('\0') || (delimData + 1) == NULL || *(delimData + 1) == MI_T('\0')))
            {
                size_t classSize = delimData - state->parser->param.ignorePropertyList.data[i];
                // Check if we found a match. Assumption is that we will not have multiple entry for the same class, if we have we
                // will honor first one only.
                if (Tcsncasecmp(state->parser->param.ignorePropertyList.data[i], id->name, classSize) == 0)
                {
                    ignorePropertyList = _CloneIgnorePropertyList(state, state->parser->param.ignorePropertyList.data[i], &ignorePropertyCount);
                    if (ignorePropertyList == NULL)
                    {
                        yyerrorf(state->errhandler, ID_MI_CREATEINSTANCE_FAILED,
                            "",
                            tcs(state->parser->param.ignorePropertyList.data[i]),
                            r);
                        return -1;
                    }
                    break;
                }

            }
        }
    }

    /* For each instance property */
    for (i = 0; i < id->numProperties; i++)
    {
        MI_PropertyDecl* p = id->properties[i];
        MI_Value *value = (MI_Value*)(p->value);
        if (ProcessProperty(state->parser->param.schemacheck, p->name, (const MI_Char**) ignorePropertyList, ignorePropertyCount))
        {
            if (validClassDecl)
            {
                r = MI_Instance_SetElement(inst, p->name, value, (MI_Type)p->type, 0);
#ifdef TEST_BUILD
                TASSERT(r == MI_RESULT_OK, L"Ignore out of memory error in unit test fault injection.");
#endif
                if (r != MI_RESULT_OK)
                {
                    yyerrorf(state->errhandler, ID_MI_SET_PROPERTY_FAILED,
                        "",
                        tcs(p->name),
                        r);
                    return -1;
                }
            }
            else
            {
                r = MI_Instance_AddElement(inst, p->name, value, (MI_Type)p->type, 0);
#ifdef TEST_BUILD
                TASSERT(r == MI_RESULT_OK, L"Ignore out of memory error in unit test fault injection.");
#endif
                if (r != MI_RESULT_OK)
                {
                    yyerrorf(state->errhandler, ID_MI_ADD_PROPERTY_FAILED,
                        "",
                        tcs(p->name),
                        r);
                    return -1;
                }
            }
        }
    }
    
    /* create instance successfully */
    id->instance = inst;
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
        else
            r |= MI_FLAG_TOSUBCLASS;
    }

    /* MI_FLAG_ENABLEOVERRIDE | MI_FLAG_DISABLEOVERRIDE */
    if (!(r & MI_FLAG_ENABLEOVERRIDE) && !(r & MI_FLAG_DISABLEOVERRIDE))
    {
        if (baseFlavor & MI_FLAG_DISABLEOVERRIDE)
            r |= MI_FLAG_DISABLEOVERRIDE;
        else
            r |= MI_FLAG_ENABLEOVERRIDE;
    }

    /* MI_FLAG_TRANSLATABLE */
    if (!(r & MI_FLAG_TRANSLATABLE))
    {
        if (baseFlavor & MI_FLAG_TRANSLATABLE)
            r |= MI_FLAG_TRANSLATABLE;
    }

    return r;
}

MI_Uint32 SetDefaultFlavors(MI_Uint32 flavor)
{
    MI_Uint32 r = flavor;

    /* MI_FLAG_TOSUBCLASS | MI_FLAG_RESTRICTED */
    if (!(r & MI_FLAG_TOSUBCLASS) && !(r & MI_FLAG_RESTRICTED))
    {
        r |= MI_FLAG_TOSUBCLASS;
    }

    /* MI_FLAG_ENABLEOVERRIDE | MI_FLAG_DISABLEOVERRIDE */
    if (!(r & MI_FLAG_ENABLEOVERRIDE) && !(r & MI_FLAG_DISABLEOVERRIDE))
    {
        r |= MI_FLAG_ENABLEOVERRIDE;
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

int CheckScope(
    void * mofstate,
    MI_Uint32 scope,
    MOF_QualifierList* qualifiers)
{
    size_t i;
    MOF_State * state = (MOF_State *)mofstate;

    if (!qualifiers)
        return 0;

    for (i = 0; i < qualifiers->size; i++)
    {
        const MI_Qualifier* q = qualifiers->data[i];
        const MI_QualifierDecl* qd;

        /* Find qualifier declaration */
        qd = FindQualifierDeclaration(state, q->name);

        if (!qd)
        {
            yyerrorf(state->errhandler, ID_UNKNOWN_QUALIFIER, "", tcs(q->name));
            return -1;
        }

        if (Tcscasecmp(q->name, MI_T("Association")) == 0)
        {
            if (!(scope & MI_FLAG_CLASS))
            {
                yyerrorf(state->errhandler, ID_ILLEGAL_SCOPE_FOR_QUALIFIER, 
                    "", 
                    tcs(q->name));
                return -1;
            }

            scope |= MI_FLAG_ASSOCIATION;
        }
        else if (Tcscasecmp(q->name, MI_T("Indication")) == 0)
        {
            if (!(scope & MI_FLAG_CLASS))
            {
                yyerrorf(state->errhandler, ID_ILLEGAL_SCOPE_FOR_QUALIFIER, 
                    "", 
                    tcs(q->name));
                return -1;
            }

            scope |= MI_FLAG_INDICATION;
        }
        else if ((qd->scope & scope) == 0)
        {
            yyerrorf(state->errhandler, ID_ILLEGAL_SCOPE_FOR_QUALIFIER, 
                "", 
                tcs(q->name));
            return -1;
        }
    }

    return 0;
}

static int _CheckMinValue(
    void * mofstate,
    const MI_PropertyDecl* pd,
    const MI_Qualifier* q)
{
    MI_Sint64 r;
    MI_Uint32 i;
    MOF_State * state = (MOF_State *)mofstate;
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
    yyerrorf(state->errhandler, 
        ID_PROPERTY_CONSTRAINT_FAILURE,
        "",
        tcs(pd->name), 
        tcs(q->name));
    return -1;

incompatibleError:
    yyerrorf(state->errhandler, 
        ID_PROPERTY_QUALIFIER_INCOMPATIBLE,
        "",
        tcs(q->name), 
        tcs(pd->name),
        _getTypeName_MI((MI_Type)pd->type));
    return -1;
}

static int _CheckMaxValue(
    void * mofstate,
    const MI_PropertyDecl* pd,
    const MI_Qualifier* q)
{
    MI_Sint64 r;
    MI_Uint32 i;
    MOF_State * state = (MOF_State *)mofstate;
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
    yyerrorf(state->errhandler, 
        ID_PROPERTY_CONSTRAINT_FAILURE,
        "",
        tcs(pd->name), 
        tcs(q->name));
    return -1;

incompatibleError:
    yyerrorf(state->errhandler, 
        ID_PROPERTY_QUALIFIER_INCOMPATIBLE,
        "",
        tcs(q->name), 
        tcs(pd->name),
        _getTypeName_MI((MI_Type)pd->type));
    return -1;
}

static int _CheckMaxLen(
    void * mofstate,
    const MI_PropertyDecl* pd,
    const MI_Qualifier* q)
{
    MI_Uint32 r;
    MI_Uint32 i;
    MOF_State * state = (MOF_State *)mofstate;
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
            if (Tcslen(s) > r)
                goto constraintError;
            break;
        }
        case MI_STRINGA:
        {
            MI_StringA x = *((MI_StringA*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if (Tcslen(x.data[i]) > r)
                    goto constraintError;
            }
            break;
        }
        default:
            goto incompatibleError;
    }

    return 0;

constraintError:
    yyerrorf(state->errhandler, 
        ID_PROPERTY_CONSTRAINT_FAILURE,
        "",
        tcs(pd->name), 
        tcs(q->name));
    return -1;

incompatibleError:
    yyerrorf(state->errhandler, 
        ID_PROPERTY_QUALIFIER_INCOMPATIBLE,
        "", 
        tcs(q->name), 
        tcs(pd->name),
        _getTypeName_MI((MI_Type)pd->type));
    return -1;
}

static int _CheckMinLen(
    void * mofstate,
    const MI_PropertyDecl* pd,
    const MI_Qualifier* q)
{
    MI_Uint32 r;
    MI_Uint32 i;
    MOF_State * state = (MOF_State *)mofstate;

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
            if (Tcslen(s) < r)
                goto constraintError;
            break;
        }
        case MI_STRINGA:
        {
            MI_StringA x = *((MI_StringA*)pd->value);

            for (i = 0; i < x.size; i++)
            {
                if (Tcslen(x.data[i]) < r)
                    goto constraintError;
            }
            break;
        }
        default:
            goto incompatibleError;
    }

    return 0;

constraintError:
    yyerrorf(state->errhandler, 
        ID_PROPERTY_CONSTRAINT_FAILURE,
        "",
        tcs(pd->name), 
        tcs(q->name));
    return -1;

incompatibleError:
    yyerrorf(state->errhandler, 
        ID_PROPERTY_QUALIFIER_INCOMPATIBLE, 
        "",
        tcs(q->name), 
        tcs(pd->name),
        _getTypeName_MI((MI_Type)pd->type));
    return -1;
}

int CheckPropertyValueConstraints(
    void * mofstate,
    const MI_PropertyDecl* pd)
{
    MI_Uint32 i;
    MOF_State * state = (MOF_State *)mofstate;
    /* Check constraint qualifiers against the property value */
    for (i = 0; i < pd->numQualifiers; i++)
    {
        const MI_Qualifier* q = pd->qualifiers[i];

        if (Tcscasecmp(q->name, MI_T("MaxValue")) == 0 && q->value)
        {
            if (_CheckMaxValue(state, pd, q) != 0)
                return -1;
        }
        else if (Tcscasecmp(q->name, MI_T("MinValue")) == 0 && q->value)
        {
            if (_CheckMinValue(state, pd, q) != 0)
                return -1;
        }
        else if (Tcscasecmp(q->name, MI_T("MaxLen")) == 0 && q->value)
        {
            if (_CheckMaxLen(state, pd, q) != 0)
                return -1;
        }
        else if (Tcscasecmp(q->name, MI_T("MinLen")) == 0 && q->value)
        {
            if (_CheckMinLen(state, pd, q) != 0)
                return -1;
        }
        else if (Tcscasecmp(q->name, MI_T("Override")) == 0 && q->value &&
            q->type == MI_STRING)
        {
            if (!(Tcscasecmp(pd->name, (MI_Char*)q->value) == 0))
            {
                yyerrorf(state->errhandler, 
                    ID_OVERRIDE_QUALIFIER_NAME_MISMATCH, 
                    "",
                    (MI_Char*)q->value,
                    pd->name);
                //TODO: test case validate this
            }
        }
    }

    /* Success! */
    return 0;
}

MI_Type InitializerToType(const MOF_Initializer* initializer)
{
    if (initializer->isArray)
    {
        if (initializer->data == NULL)
            return MI_SINT64A;

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
            case TOK_ALIAS_IDENTIFIER:
                return MI_INSTANCEA;
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
            case TOK_ALIAS_IDENTIFIER:
                return MI_INSTANCE;
        }
    }

    /* Unreachable */
    return MI_BOOLEAN;
}

/* Add string to hash table */
const MI_InstanceAliasDecl* _FindInstanceAliasFromHash(
    _In_ void * mofstate,
    _In_z_ const MI_Char* name)
{
    MOF_State * state = (MOF_State *)mofstate;
    if(state->instanceAliasesHash.nodes)
    {
        MI_Uint32 pos = StringHash_Find(&state->instanceAliasesHash, name);
        if (pos != HASH_INVALID_POS)
        {
            _Analysis_assume_(pos < state->instanceAliases.size);
            return state->instanceAliases.data[pos];
        }
    }
    return NULL;
}

/* Add string to hash table */
int _AddInstanceAliasDeclToHash(
    _In_ void * mofstate,
    _In_ MI_InstanceAliasDecl* aid,
    _In_ MI_Uint32 pos)
{
    MOF_State * state = (MOF_State *)mofstate;
    MI_Uint32 code = Hash(aid->name);
    int c = StringHash_Add(state->batch, &state->instanceAliasesHash, pos, code, aid->name);
    if (c != 0)
    {
        yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
    }
    return c;
}

int AddInstanceAliasDecl(
    void * mofstate,
    MI_InstanceAliasDecl * aid)
{
    MOF_State * state = (MOF_State *)mofstate;
    /* Add the declaration */
    if (Codec_PtrArray_Append(state, (PtrArray*)&state->instanceAliases, aid) != 0)
        return -1;

    /* Add the declaration to hash table */
    if (state->instanceAliases.size == HASH_THRESHOLD)
    {
        /* Initialize hash */
        MI_Uint32 i =0;
        if (StringHash_Init(state->batch, &state->instanceAliasesHash) != 0)
        {
            yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
            return -1;
        }
        for(; i < state->instanceAliases.size; i++)
        {
            if (_AddInstanceAliasDeclToHash(state, state->instanceAliases.data[i], i)!=0)
                return -1;
        }
    }
    else if (state->instanceAliases.size > HASH_THRESHOLD)
    {
        return _AddInstanceAliasDeclToHash(state, aid, state->instanceAliases.size - 1);
    }
    return 0;
}

const MI_InstanceAliasDecl* FindInstanceAliasDecl(
    void * mofstate,
    const MI_Char* name)
{
    size_t i;
    MOF_State * state = (MOF_State *)mofstate;
    if (state->instanceAliases.size > HASH_THRESHOLD)
    {
        return _FindInstanceAliasFromHash(state, name);
    }
    else
    {
        for (i = 0; i < state->instanceAliases.size; i++)
        {
            if (Tcscasecmp(state->instanceAliases.data[i]->name, name) == 0)
                return state->instanceAliases.data[i];
        }
    }
    /* Not found */
    return NULL;
}

int AddInstanceDecl(
    void * mofstate,
    MI_InstanceDecl* id)
{
    MOF_State * state = (MOF_State *)mofstate;
    if (id == NULL)
    {
        return 0;
    }
    /* Add the declaration */
    if (Codec_PtrArray_Append(state, (PtrArray*)&state->instanceDecls, id) != 0)
        return -1;

    if (id->alias)
    {
        const MI_InstanceAliasDecl *d = FindInstanceAliasDecl(state, id->alias);
        if (d)
        {
            yyerrorf(state->errhandler, ID_ALIAS_DECL_ALREADY_DEFINED, 
                "", 
                tcs(id->alias),
                d->lineno);
            return -1;
        }
        {
            MI_InstanceAliasDecl *aid = CALLOC_T(MI_InstanceAliasDecl, 1);
            if (!aid)
            {
                yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
                return -1;
            }
            aid->decl = id;
            aid->lineno = state->lastAliasDeclLineNo;
            aid->id = 0;
            aid->name = id->alias;
            return AddInstanceAliasDecl(mofstate, aid);
        }
    }
    return 0;
}

#define INCLUDE_FILE_DEPTH 128

int MOF_State_PushBuffer(
    _In_ void *mofstate,
    _In_reads_bytes_(len) MI_Uint8 *buf,
    _In_ MI_Uint32 len )
{
    MOF_State * state = (MOF_State *)mofstate;
    /* Check for stack overflow. */
    if (state->bufTop >= INCLUDE_FILE_DEPTH)
    {
        yyerrorf(state->errhandler, ID_MOF_STACK_OVERFLOW, "MOF file stack overflow");
        return -1;
    }

    if (state->bufStack == 0)
    {
        state->bufStack = (MOF_Buffer*)Batch_Get(state->batch, INCLUDE_FILE_DEPTH*sizeof(MOF_Buffer));
        if (!state->bufStack)
        {
            yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
            return -1;
        }
    }
    /* Push old buf to stack */
    state->bufStack[state->bufTop++] = state->buf;
    {
        MI_Result r = mof_setupbuffer(buf, len, state->batch, &state->buf);
        if (r == MI_RESULT_SERVER_LIMITS_EXCEEDED)
        {
            yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "");
            return -1;
        }
        else if (r == MI_RESULT_NOT_SUPPORTED)
        {
            yyerrorf(state->errhandler, ID_INTERNAL_ERROR, "internal error: %s(%u)", __FILE__, __LINE__);
            return -1;
        }
    }
    return 0;
}

int MOF_State_PopBuffer(void *mofstate)
{
    MOF_State * state = (MOF_State *)mofstate;
    /* Check for stack underflow. */
    if (state->bufTop == 0)
    {
        yyerrorf(state->errhandler, ID_MOF_STACK_UNDERFLOW, "MOF file stack underflow");
        return -1;
    }

    /* Release included file content */
    if (state->parser->param.callbacks.freeIncludedFileContent)
    {
        state->parser->param.callbacks.freeIncludedFileContent(
            state->parser->param.callbacks.includedFileContext,
            (MI_Uint8*)state->buf.buf);
    }

    /* Restore previous buffer */
    state->bufTop--;
    state->buf = state->bufStack[state->bufTop];
    return 0;
}

_Use_decl_annotations_
int openIncludeFile(void *mofstate, const MI_Char* path)
{
    MOF_State * state = (MOF_State *)mofstate;
    if (state->parser->param.callbacks.getIncludedFileContent)
    {
        MI_Uint8 * buffer;
        MI_Uint32 length;
        MI_Result r = state->parser->param.callbacks.getIncludedFileContent(
            state->parser->param.callbacks.includedFileContext,
            path,
            &buffer,
            &length);
        if (r != MI_RESULT_OK)
        {
            /* Ignore the failure and later parser will fail if have undefined symbol */
            yywarnf(state->errhandler, ID_FAILED_TO_READ_INCLUDE_FILE, "", path);
            return 0;
        }
        return MOF_State_PushBuffer(state, buffer, length);
    }
    /* It is fine if caller does not support loading included mof */
    return 0;
}


_Use_decl_annotations_
int closeIncludeFile(void *mofstate)
{
    int r;
    MOF_State * state = (MOF_State *)mofstate;
    if (state->bufTop == 0) return 0;
    r = MOF_State_PopBuffer(mofstate);
    /* return 1 means the poped buffer is valid */
    if (r == 0) return 1;
    return r;
}

MI_Uint32 _GetPropertySize(_In_ MI_Type t)
{
    switch(t)
    {
    case MI_BOOLEAN:
        return sizeof(MI_ConstBooleanField);
    case MI_UINT8:
        return sizeof(MI_ConstUint8Field);
    case MI_SINT8:
        return sizeof(MI_ConstSint8Field);
    case MI_UINT16:
        return sizeof(MI_ConstUint16Field);
    case MI_SINT16:
        return sizeof(MI_ConstSint16Field);
    case MI_UINT32:
        return sizeof(MI_ConstUint32Field);
    case MI_SINT32:
        return sizeof(MI_ConstSint32Field);
    case MI_UINT64:
        return sizeof(MI_ConstUint64Field);
    case MI_SINT64:
        return sizeof(MI_ConstSint64Field);
    case MI_REAL32:
        return sizeof(MI_ConstReal32Field);
    case MI_REAL64:
        return sizeof(MI_ConstReal64Field);
    case MI_CHAR16:
        return sizeof(MI_ConstChar16Field);
    case MI_DATETIME:
        return sizeof(MI_ConstDatetimeField);
    case MI_STRING:
        return sizeof(MI_ConstStringField);
    case MI_REFERENCE:
        return sizeof(MI_ConstReferenceField);
    case MI_INSTANCE:
        return sizeof(MI_ConstInstanceField);
    case MI_BOOLEANA:
        return sizeof(MI_ConstBooleanAField);
    case MI_UINT8A:
        return sizeof(MI_ConstUint8AField);
    case MI_SINT8A:
        return sizeof(MI_ConstSint8AField);
    case MI_UINT16A:
        return sizeof(MI_ConstUint16AField);
    case MI_SINT16A:
        return sizeof(MI_ConstSint16AField);
    case MI_UINT32A:
        return sizeof(MI_ConstUint32AField);
    case MI_SINT32A:
        return sizeof(MI_ConstSint32AField);
    case MI_UINT64A:
        return sizeof(MI_ConstUint64AField);
    case MI_SINT64A:
        return sizeof(MI_ConstSint64AField);
    case MI_REAL32A:
        return sizeof(MI_ConstReal32AField);
    case MI_REAL64A:
        return sizeof(MI_ConstReal64AField);
    case MI_CHAR16A:
        return sizeof(MI_ConstChar16AField);
    case MI_DATETIMEA:
        return sizeof(MI_ConstDatetimeAField);
    case MI_STRINGA:
        return sizeof(MI_ConstStringAField);
    case MI_REFERENCEA:
        return sizeof(MI_ConstReferenceAField);
    case MI_INSTANCEA:
        return sizeof(MI_ConstInstanceAField);
    }
    return 0;
}

_Use_decl_annotations_
int _FinalizeClassSize(MI_ClassDecl *decl)
{
    MI_Uint32 offset = sizeof(MI_Instance);
    MI_Uint32 i = 0;
    for (; i < decl->numProperties; i++)
    {
        decl->properties[i]->offset = offset;
        offset += _GetPropertySize((MI_Type)decl->properties[i]->type);
    }
    decl->size = offset;
    return 0;
}

_Use_decl_annotations_
int _FinalizeMethodSize(MI_MethodDecl *decl)
{
    MI_Uint32 offset = sizeof(MI_Instance);
    MI_Uint32 i = 0;
    for (; i < decl->numParameters; i++)
    {
        decl->parameters[i]->offset = offset;
        offset += _GetPropertySize((MI_Type)decl->parameters[i]->type);
    }
    decl->size = offset;
    return 0;
}

_Use_decl_annotations_
MI_ParameterDecl ** CreateParameterSet(
    void * mofstate,
    MI_ParameterDecl ** oldParameters,
    MI_Uint32 numOldParameters,
    MI_Type methodReturnType)
{
    MOF_State * state = (MOF_State *)mofstate;
    MI_ParameterDecl *retDecl;
    MI_ParameterDecl **pd = (MI_ParameterDecl **)Batch_GetClear(
        state->batch,
        sizeof(MI_ParameterDecl*)*(numOldParameters+1));
    if (!pd)
    {
        yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
        return NULL;
    }
    retDecl = (MI_ParameterDecl *)Batch_GetClear(
        state->batch,
        sizeof(MI_ParameterDecl));
    if (!retDecl)
    {
        yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
        return NULL;
    }
    if (numOldParameters > 0)
    {
        memcpy(pd + 1, oldParameters, sizeof(MI_ParameterDecl*)*numOldParameters);
    }
    retDecl->flags = MI_FLAG_PARAMETER|MI_FLAG_OUT;
    retDecl->name = MI_T("MIReturn");
    retDecl->code = Hash(retDecl->name);
    retDecl->type = methodReturnType;
    *pd = retDecl;
    return pd;
}

