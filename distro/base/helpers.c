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

#include <ctype.h>
#include "helpers.h"
#include "types.h"
#include "strings.h"
#include "alloc.h"
#include <io/io.h>

static const ZChar* _ParseNumber(const ZChar* p, unsigned long* n)
{
    ZChar* end;

    *n = Ztoul(p, &end, 10);

    if (end == p)
        return NULL;

    return end;
}

static const ZChar* _ParseDecimalPart(
    const ZChar* p,
    unsigned long* n)
{
    ZChar* end;
    int i;
    ZChar buf[7];

    Ztoul(p, &end, 10);

    if (end == p)
    {
        /* Zero decimal part */
        *n = 0;
        return p;
    }

    for (i = 0; i < 6 && p != end; i++, p++)
        buf[i] = *p;

    for (; i < 6; i++)
        buf[i] = '0';

    buf[6] = '\0';

    *n = Ztoul(buf, NULL, 10);

    return end;
}

static int _ParseWSManDuration(const ZChar* str, MI_Datetime* x)
{
    const ZChar* p = str;
    int foundT = 0;
    unsigned long years = 0;
    unsigned long months = 0;
    unsigned long days = 0;
    unsigned long hours = 0;
    unsigned long minutes = 0;
    unsigned long seconds = 0;
    unsigned long microseconds = 0;

    /* xs:duration: PnYnMnDTnHnMnS */
    if (*p != 'P')
        return -1;

    /* [xs:duration]
     *
     * Format: "PnYnMnDTnHnMnS", where
     *     P - period (required)
     *     nY - number of years
     *     nM - number of month
     *     nD - number of days
     *     ZT - start of time section (required for the following)
     *     nH - number of hours
     *     nM - number of minutes
     *     nS - number of seconds
     *
     * Examples:
     *     -P10D (rejected)
     *     -P1347M (rejected)
     *     P5Y
     *     P5Y2M10D
     *     P5Y2M10DT15H
     *     PT15H
     *     P1347Y
     *     P1347M
     *     P1Y2MT2H
     *     P0Y1347M
     *     P0Y1347M0D
     *     P1Y2M3DT10H30M
     *
     * Illegal:
     *     P-1347M (rejected)
     *     P1Y2MT (tolerated)
     */

    p++;

    while (*p)
    {
        unsigned long n = 0;

        if (*p == 'T')
        {
            foundT = 1;
            p++;
        }
        else if (foundT)
        {
            p = _ParseNumber(p, &n);

            if (!p)
                break;

            switch (*p)
            {
                case 'H':
                    hours = n;
                    break;
                case 'M':
                    minutes = n;
                    break;
                case 'S':
                    seconds = n;
                    break;
                case '.':
                {
                    p++;
                    p = _ParseDecimalPart(p, &microseconds);

                    if (*p != 'S')
                        return -1;

                    seconds = n;
                    break;
                }
                default:
                    return -1;
            }

            p++;
        }
        else
        {
            p = _ParseNumber(p, &n);

            if (!p)
                break;

            switch (*p)
            {
                case 'Y':
                    years = n;
                    break;
                case 'M':
                    months = n;
                    break;
                case 'D':
                    days = n;
                    break;
                default:
                    return -1;
            }

            p++;
        }
    }

    /* ATTN: check for overflow */

    /* Normalize seconds (possibly increasing minutes) */
    minutes += seconds / 60;
    seconds = seconds % 60;

    /* Normalize minutes (possibly increasing hours) */
    hours += minutes / 60;
    minutes = minutes % 60;

    /* Normalize hours (possibly increasing days) */
    days += hours / 24;
    hours = hours % 24;

    /* Approximate days from years-months-days */
    days += years * 365;
    days += years / 4;
    days += months * 30;
    days += months / 2;

    /* Set CIM datetime fields */
    x->isTimestamp = MI_FALSE;
    x->u.interval.days = (unsigned int)days;
    x->u.interval.hours = (unsigned int)hours;
    x->u.interval.minutes = (unsigned int)minutes;
    x->u.interval.seconds = (unsigned int)seconds;
    x->u.interval.microseconds = microseconds;

    return (p && *p == '\0') ? 0 : -1;
}

static const ZChar* _ParseWSManUTC(const ZChar* str, MI_Datetime* x)
{
    const ZChar* p = str;
    unsigned long utcHours = 0;
    unsigned long utcMinutes = 0;
    long utcSign = 0; /* '1' is positive, '-1' is negative */

    if (*p == 'Z')
    {
        p++;
        return p;
    }
    else if (*p == '+' || *p == '-')
    {
        /* Parse UTC "HH:SS" */
        const ZChar* end;

        utcSign = (*p == '-') ? -1 : 1;

        p++;
        end = _ParseNumber(p, &utcHours);

        if (!end || (end - p) != 2)
            return NULL;

        p = end;

        if (*p != ':')
            return NULL;

        p++;
        end = _ParseNumber(p, &utcMinutes);

        if (!end || (end - p) != 2)
            return NULL;

        p = end;
    }
    else
    {
        return NULL;
    }

    /* Set CIM datetime fields */
    x->u.timestamp.utc = utcSign * ((utcHours * 60) + utcMinutes);

    return p;
}

static const ZChar* _ParseWSManDate(const ZChar* str, MI_Datetime* x)
{
    const ZChar* p = str;
    unsigned long year = 0;
    unsigned long month = 0;
    unsigned long day = 0;

    /* Parse YYYY */
    {
        const ZChar* end = _ParseNumber(p, &year);

        if (!end || (end - p) != 4)
            return NULL;

        p = end;
    }

    /* Expect '-' */
    if (*p++ != '-')
        return NULL;

    /* Parse MM */
    {
        const ZChar* end = _ParseNumber(p, &month);

        if (!end || (end - p) != 2)
            return NULL;

        p = end;
    }

    /* Expect '-' */
    if (*p++ != '-')
        return NULL;

    /* Parse DD */
    {
        const ZChar* end = _ParseNumber(p, &day);

        if (!end || (end - p) != 2)
            return NULL;

        p = end;
    }

    /* Set CIM datetime fields */
    memset(x, 0, sizeof(MI_Datetime));
    x->isTimestamp = MI_TRUE;
    x->u.timestamp.year = (unsigned int)year;
    x->u.timestamp.month = (unsigned int)month;
    x->u.timestamp.day = (unsigned int)day;

    /* Parse UTC part */
    if (*p == 'Z' || *p == '+' || *p == '-')
    {
        p = _ParseWSManUTC(p, x);

        if (!p)
            return NULL;
    }

    return p;
}

static const ZChar* _ParseWSManTime(const ZChar* str, MI_Datetime* x)
{
    const ZChar* p = str;
    unsigned long hour = 0;
    unsigned long minute = 0;
    unsigned long second = 0;
    unsigned long microseconds = 0;

    /* Parse "HH" */
    {
        const ZChar* end = _ParseNumber(p, &hour);

        if (!end || (end - p) != 2)
            return NULL;

        p = end;
    }

    /* Expect ':' */
    if (*p++ != ':')
        return NULL;

    /* Parse "MM" */
    {
        const ZChar* end = _ParseNumber(p, &minute);

        if (!end || (end - p) != 2)
            return NULL;

        p = end;
    }

    /* Expect ":" */
    if (*p++ != ':')
        return NULL;

    /* Parse "SS" */
    {
        const ZChar* end = _ParseNumber(p, &second);

        if (!end || (end - p) != 2)
            return NULL;

        p = end;
    }

    /* Parse decimal part */
    if (*p == '.')
    {
        p++;
        p = _ParseDecimalPart(p, &microseconds);

        if (!p)
            return NULL;
    }

    /* Set CIM datetime fields */
    x->isTimestamp = MI_TRUE;
    x->u.timestamp.hour = (unsigned int)hour;
    x->u.timestamp.minute = (unsigned int)minute;
    x->u.timestamp.second = (unsigned int)second;
    x->u.timestamp.microseconds = (unsigned int)microseconds;

    /* Parse UTC part */
    if (*p == 'Z' || *p == '+' || *p == '-')
    {
        p = _ParseWSManUTC(p, x);

        if (!p)
            return NULL;
    }

    return p;
}

int ParseWSManDatetime(const ZChar* str, MI_Datetime* x)
{
    const ZChar* p = str;

    /* Clear datetime */
    memset(x, 0, sizeof(MI_Datetime));

    /* negative xs:duration */
    if (*p == '-')
    {
        /* Negative intervals not supported by CIM */
        return -1;
    }

    /* xs:duration: "PnYnMnDTnHnMnS" */
    if (*p == 'P')
    {
        return _ParseWSManDuration(str, x);
    }

    /* xs:date: "YYYY-MM-DD" plus UTC */
    if (isdigit(p[0]) && isdigit(p[1]) && isdigit(p[2]) && isdigit(p[3]))
    {
        p = _ParseWSManDate(str, x);

        if (!p)
            return -1;

        if (*p == '\0')
            return 0;

        /* xs:time "HH:MM:SS" plus UTC */
        if (*p == 'T')
        {
            p++;
            p = _ParseWSManTime(p, x);

            if (!p)
                return -1;

            if (*p == '\0')
                return 0;
        }
    }

    /* xs:time: "HH:MM:SS" plus UTC */
    if (isdigit(p[0]) && isdigit(p[1]) && p[2] == ':')
    {
        p = _ParseWSManTime(str, x);

        if (!p)
            return -1;

        if (*p == '\0')
            return 0;
    }

    /* Failed */
    return -1;
}

_Use_decl_annotations_
void FormatWSManDatetime(const MI_Datetime* x, ZChar buffer[64])
{
    int n = 64;

    *buffer = '\0';

    if (x->isTimestamp)
    {
        /* Example output: "2010-12-31T12:30:03.123456+06:00" */
        int haveDate;
        int haveTime;
        ZChar tmpbuf[64];

        haveDate = x->u.timestamp.year || x->u.timestamp.month ||
            x->u.timestamp.day;

        haveTime = x->u.timestamp.hour || x->u.timestamp.minute ||
            x->u.timestamp.second || x->u.timestamp.microseconds;

        if (haveDate)
        {
            Szprintf(tmpbuf, MI_COUNT(tmpbuf), ZT("%04u-%02u-%02u"),
                x->u.timestamp.year,
                x->u.timestamp.month,
                x->u.timestamp.day);
            Zlcat(buffer, tmpbuf, n);
        }

        if (haveTime || !haveDate)
        {
            if (haveDate)
                Zlcat(buffer, ZT("T"), n);

            Szprintf(tmpbuf, MI_COUNT(tmpbuf), ZT("%02u:%02u:%02u"),
                x->u.timestamp.hour,
                x->u.timestamp.minute,
                x->u.timestamp.second);
            Zlcat(buffer, tmpbuf, n);

            if (x->u.timestamp.microseconds)
            {
                Szprintf(tmpbuf, MI_COUNT(tmpbuf), ZT(".%06u"),
                    x->u.timestamp.microseconds);
                Zlcat(buffer, tmpbuf, n);
            }

        }

        if (x->u.timestamp.utc > 0)
        {
            Szprintf(tmpbuf, MI_COUNT(tmpbuf), ZT("+%02u:%02u"),
                x->u.timestamp.utc / 60, x->u.timestamp.utc % 60);
            Zlcat(buffer, tmpbuf, n);
        }
        else if (x->u.timestamp.utc < 0)
        {
            Szprintf(tmpbuf, MI_COUNT(tmpbuf), ZT("-%02u:%02u"),
                -x->u.timestamp.utc / 60, -x->u.timestamp.utc % 60);
            Zlcat(buffer, tmpbuf, n);
        }
    }
    else
    {
        ZChar tmpbuf[64];

        /* Example: "P1Y1M22DT10H11M12S" */

        Zlcat(buffer, ZT("P"), n);

        if (x->u.interval.days)
        {
            Szprintf(tmpbuf, MI_COUNT(tmpbuf), ZT("%uD"), x->u.interval.days);
            Zlcat(buffer, tmpbuf, n);
        }

        if (x->u.interval.hours || x->u.interval.minutes ||
            x->u.interval.seconds || x->u.interval.microseconds)
        {
            Zlcat(buffer, ZT("T"), n);
        }

        if (x->u.interval.hours)
        {
            Szprintf(tmpbuf, MI_COUNT(tmpbuf), ZT("%uH"), x->u.interval.hours);
            Zlcat(buffer, tmpbuf, n);
        }

        if (x->u.interval.minutes)
        {
            Szprintf(tmpbuf, MI_COUNT(tmpbuf), ZT("%uM"), x->u.interval.minutes);
            Zlcat(buffer, tmpbuf, n);
        }

        if (x->u.interval.seconds && x->u.interval.microseconds)
        {
            Szprintf(tmpbuf, MI_COUNT(tmpbuf), ZT("%u.%06uS"),
                x->u.interval.seconds, x->u.interval.microseconds);
            Zlcat(buffer, tmpbuf, n);
        }
        else if (x->u.interval.seconds && !x->u.interval.microseconds)
        {
            Szprintf(tmpbuf, MI_COUNT(tmpbuf), ZT("%uS"), x->u.interval.seconds);
            Zlcat(buffer, tmpbuf, n);
        }
        else if (!x->u.interval.seconds && x->u.interval.microseconds)
        {
            Szprintf(tmpbuf, MI_COUNT(tmpbuf), ZT("0.%06uS"),
                x->u.interval.microseconds);
            Zlcat(buffer, tmpbuf, n);
        }
    }
}

static int _StrToU32(const ZChar* s, size_t offset, size_t size, MI_Uint32* x)
{
    ZChar buf[64];
    ZChar* end;

    if (size >= MI_COUNT(buf))
        return -1;

    memcpy(buf, &s[offset], size * sizeof(ZChar));
    buf[size] = '\0';

    *x = (MI_Uint32)Ztoul(buf, &end, 10);

    if (*end != '\0')
        return -1;

    /* Success */
    return 0;
}

int StrToChar16(const ZChar* str, MI_Char16* x)
{
    ZChar* end;
    *x = (MI_Char16)Ztoul(str, &end, 0);

    if (*end != '\0')
        return -1;

    return 0;
}

int StrToDatetime(const ZChar* s, MI_Datetime* x)
{
    if (Zlen(s) != 25)
        return -1;

    memset(x, 0, sizeof(MI_Datetime));

    if (s[21] == '+' || s[21] == '-')
    {
        MI_Uint32 utc;

        /* It must be a timestamp (YYYYMMDDHHMMSS.MMMMMMSUTC) */
        if (_StrToU32(s, 0, 4, &x->u.timestamp.year) != 0 ||
            _StrToU32(s, 4, 2, &x->u.timestamp.month) != 0 ||
            _StrToU32(s, 6, 2, &x->u.timestamp.day) != 0 ||
            _StrToU32(s, 8, 2, &x->u.timestamp.hour) != 0 ||
            _StrToU32(s, 10, 2, &x->u.timestamp.minute) != 0 ||
            _StrToU32(s, 12, 2, &x->u.timestamp.second) != 0 ||
            s[14] != '.' ||
            _StrToU32(s, 15, 6, &x->u.timestamp.microseconds) != 0 ||
            _StrToU32(s, 22, 3, &utc) != 0)
        {
            return -1;
        }

        if (s[21] == '+')
             x->u.timestamp.utc = (MI_Sint32)utc;
        else
             x->u.timestamp.utc = -(MI_Sint32)utc;

        x->isTimestamp = 1;
    }
    else if (s[21] == ':')
    {
        /* It must be an interval (DDDDDDDDHHMMSS.MMMMMM:000) */
        if (_StrToU32(s, 0, 8, &x->u.interval.days) != 0 ||
            _StrToU32(s, 8, 2, &x->u.interval.hours) != 0 ||
            _StrToU32(s, 10, 2, &x->u.interval.minutes) != 0 ||
            _StrToU32(s, 12, 2, &x->u.interval.seconds) != 0 ||
            s[14] != '.' ||
            _StrToU32(s, 15, 6, &x->u.interval.microseconds) != 0 ||
            s[22] != '0' || s[23] != '0' || s[24] != '0')
        {
            return -1;
        }

        x->isTimestamp = 0;
    }
    else
        return -1;

    return 0;
}

static int _ParseDatetime(const ZChar* str, MI_Datetime* x)
{
    if (StrToDatetime(str, x) == 0)
        return 0;

    if (ParseWSManDatetime(str, x) == 0)
        return 0;

    return -1;
}

int StrToBoolean(const ZChar* str, MI_Boolean* x)
{
    if (Zcasecmp(str, ZT("true")) == 0)
        *x = MI_TRUE;
    else if (Zcasecmp(str, ZT("false")) == 0)
        *x = MI_FALSE;
    else
        return -1;

    return 0;
}

int StrToUint8(const ZChar* str, MI_Uint8* x)
{
    ZChar* end;
    *x = (MI_Uint8)Ztoul(str, &end, 0);

    if (*end != '\0')
        return -1;

    return 0;
}

int StrToSint8(const ZChar* str, MI_Sint8* x)
{
    ZChar* end;
    *x = (MI_Sint8)Ztol(str, &end, 0);

    if (*end != '\0')
        return -1;

    return 0;
}

int StrToUint16(const ZChar* str, MI_Uint16* x)
{
    ZChar* end;
    *x = (MI_Uint16)Ztoul(str, &end, 0);

    if (*end != '\0')
        return -1;

    return 0;
}

int StrToSint16(const ZChar* str, MI_Sint16* x)
{
    ZChar* end;
    *x = (MI_Sint16)Ztol(str, &end, 0);

    if (*end != '\0')
        return -1;

    return 0;
}

int StrToUint32(const ZChar* str, MI_Uint32* x)
{
    ZChar* end;
    *x = (MI_Uint32)Ztoul(str, &end, 0);

    if (*end != '\0')
        return -1;

    return 0;
}

int StrToSint32(const ZChar* str, MI_Sint32* x)
{
    ZChar* end;
    *x = (MI_Sint32)Ztol(str, &end, 0);

    if (*end != '\0')
        return -1;

    return 0;
}

int StrToUint64(const ZChar* str, MI_Uint64* x)
{
    ZChar* end;
    *x = (MI_Uint64)Ztoull(str, &end, 0);

    if (*end != '\0')
        return -1;

    return 0;
}

int StrToSint64(const ZChar* str, MI_Sint64* x)
{
    ZChar* end;
    *x = (MI_Sint64)Ztoll(str, &end, 0);

    if (*end != '\0')
        return -1;

    return 0;
}

int StrToReal32(const ZChar* str, MI_Real32* x)
{
    ZChar* end;
    *x = (MI_Real32)Ztod(str, &end);

    if (*end != '\0')
        return -1;

    return 0;
}

int StrToReal64(const ZChar* str, MI_Real64* x)
{
    ZChar* end;
    *x = (MI_Real64)Ztod(str, &end);

    if (*end != '\0')
        return -1;

    return 0;
}

typedef int (*StrToType)(const ZChar* str, void* x);

static StrToType _converters[] =
{
    (StrToType)StrToBoolean,
    (StrToType)StrToUint8,
    (StrToType)StrToSint8,
    (StrToType)StrToUint16,
    (StrToType)StrToSint16,
    (StrToType)StrToUint32,
    (StrToType)StrToSint32,
    (StrToType)StrToUint64,
    (StrToType)StrToSint64,
    (StrToType)StrToReal32,
    (StrToType)StrToReal64,
    (StrToType)StrToChar16,
    (StrToType)_ParseDatetime,
    NULL, /* STRING */
    NULL, /* REFERENCE */
    NULL, /* INSTANCE */
};

MI_Result MI_CALL Instance_SetElementFromString(
    MI_Instance* self,
    const ZChar* name,
    const ZChar* str)
{
    /* ATTN: check for integer value truncation (see use of Ztol) */
    /* ATTN: implement array types! */
    /* ATTN: implement instance and reference types! */
    MI_Type type;
    MI_Value value;

    /* Check arguments */
    if (!self || !name || !str)
    {
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);
    }

    /* Obtain type of named property */
    {
        MI_Result r = MI_Instance_GetElement(self, name, NULL, &type,
            NULL, NULL);

        if (r != MI_RESULT_OK)
        {
            return r;
        }
    }

    /* If type is array and value is string,
        try to create a single item array from this string
    */
    if (0 != (MI_ARRAY_BIT & type))
    {
        return Instance_SetElementFromStringA(self, name, &str, 1);
    }


    /* Convert string to value */
    if (type == MI_STRING)
    {
        value.string = (ZChar*)str;
    }
    else
    {
        StrToType func = _converters[Type_ScalarOf(type)];

        if (func)
        {
            if ((*func)(str, &value) != 0)
                MI_RETURN(MI_RESULT_FAILED);
        }
        else
        {
            MI_RETURN(MI_RESULT_FAILED);
        }
    }

    MI_RETURN(MI_Instance_SetElement(self, name, &value, type, 0));
}

MI_Result MI_CALL Instance_SetElementFromStringA(
    MI_Instance* self_,
    const ZChar* name,
    const ZChar** data,
    MI_Uint32 size)
{
    Instance* self = (Instance*)self_;
    MI_Type type = MI_BOOLEAN;
    MI_Value v;
    MI_Result result = MI_RESULT_OK;
    MI_Uint32 flags = 0;

    /* Clear value first */
    memset(&v, 0, sizeof(v));

    /* Check arguments */
    if (!self || !name || !data)
    {
        /* return instead of goto failed: 'v' is not initialized yet */
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* Obtain type of named property */
    if (MI_Instance_GetElement(self_, name, NULL, &type, NULL, NULL))
    {
        /* return instead of goto failed: 'v' is not initialized yet */
        return MI_RESULT_FAILED;
    }

    /* Allocate array (allocate extra element for possible empty array) */
    if (type == MI_STRINGA)
    {
        v.array.data = (ZChar**)data;
        v.array.size = size;
    }
    else
    {
        MI_Uint32 esize = (MI_Uint32)Type_SizeOf(Type_ScalarOf(type));
        v.array.data = BAlloc(self->batch, (size + 1) * esize, CALLSITE);

        if (!v.array.data)
        {
            result = MI_RESULT_FAILED;
            goto done;
        }

        v.array.size = size;
        flags |= MI_FLAG_ADOPT;
    }

    /* Convert string to array */

    if (type != MI_STRINGA)
    {
        StrToType func = _converters[Type_ScalarOf(type)];
        char* ptr = v.array.data;
        MI_Uint32 i;

        if (!func)
        {
            result = MI_RESULT_FAILED;
            goto done;
        }

        for (i = 0; i < size; i++)
        {
            if ((*func)(data[i], ptr) != 0)
            {
                result = MI_RESULT_FAILED;
                goto done;
            }

            ptr += Type_SizeOf(Type_ScalarOf(type));
        }
    }

    if (MI_Instance_SetElement(self_, name, &v, type, flags))
    {
        result = MI_RESULT_FAILED;
        goto done;
    }

done:

    if (result && v.array.data && type != MI_STRINGA)
        BFree(self->batch, v.array.data, CALLSITE);

    return result;
}

MI_Result MI_CALL Instance_GetValue(
    MI_Instance* self,
    const ZChar* name,
    void* value,
    MI_Type type)
{
    MI_Result r;
    MI_Value v;
    MI_Type t;
    MI_Uint32 f;

    r = MI_Instance_GetElement(self, name, &v, &t, &f, NULL);

    if (r != MI_RESULT_OK)
        MI_RETURN(r);

    if (t != type)
        MI_RETURN(MI_RESULT_TYPE_MISMATCH);

    if (f & MI_FLAG_NULL)
        MI_RETURN(MI_RESULT_NOT_FOUND);

    if (!value)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    memcpy(value, &v, Type_SizeOf(type));

    MI_RETURN(MI_RESULT_OK);
}

_Use_decl_annotations_
void DatetimeToStr(const MI_Datetime* x, ZChar buf[26])
{
    if (x->isTimestamp)
    {
        const ZChar FMT[] =  MI_T("%04d%02d%02d%02d%02d%02d.%06d%c%03d");
        MI_Sint32 utc = x->u.timestamp.utc;
        Szprintf(buf, 26, FMT,
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
        Szprintf(buf, 26, FMT,
            x->u.interval.days,
            x->u.interval.hours,
            x->u.interval.minutes,
            x->u.interval.seconds,
            x->u.interval.microseconds);
    }
}
