#include <micodec.h>
#include <ctype.h>
#include <stdlib.h>
#if defined(_MSC_VER)
#ifndef CONFIG_OS_WINDOWS
#define CONFIG_OS_WINDOWS
#endif
#endif
#include <base/memman.h>
#include "buf.h"
#include "strset.h"
#include <pal/strings.h>

#ifdef _PREFAST_
#include <wctype.h>
# pragma prefast (push)
# pragma prefast (disable: 28252)
# pragma prefast (disable: 28253)
#endif

#include <string.h>

#ifdef _PREFAST_
# pragma prefast (pop)
#endif

#define UNUSED(X) ((void)X)

/*
**==============================================================================
**
** Limitations:
**
**     (*) In several places this implementation depends on the internal
**         classDecl and not entirely on the MI_Class_* interface. This is
**         unavoidable since the following are unknown for many elements:
**
**             (*) Whether properties are local or not.
**             (*) What the flag values are for many elements (parameters).
**             (*) The metaelement type for a class (Association/Indication).
**
**     (*) The serialization flag 'MI_SERIALIZER_FLAGS_CLASS_DEEP' only works
**         for subclasses (and not for embedded instances and references). This
**         information is not visible through the interface.
**
**     (*) These flags could result in duplicate clases in output:
**             MI_SERIALIZER_FLAGS_CLASS_DEEP
**             MI_SERIALIZER_FLAGS_INSTANCE_WITH_CLASS
**
**==============================================================================
*/

/*
**==============================================================================
**
** T()
** LIT()
**
**==============================================================================
*/

#if (MI_CHAR_TYPE == 1)
# define T(STR) STR
#else
# define __T(STR) L ## STR
# define T(STR) __T(STR)
#endif

#define LIT(STR) T(STR), ((sizeof(T(STR))/sizeof(T(STR)[0]))-1)

/*
**==============================================================================
**
** RETERR()
**
**==============================================================================
*/

/* Without this trick, MSC complains that the while condition is constant */
MI_INLINE unsigned int s_reterr_false() 
{
    return 0; 
}

#define RETERR(RESULT) \
    do \
    { \
        MI_Result __r__ = RESULT; \
        if (__r__ != MI_RESULT_OK) \
        { \
            return __r__; \
        } \
    } \
    while (s_reterr_false())


/*
**==============================================================================
**
** SNPRINTF()
**
**==============================================================================
*/

#if defined(_MSC_VER)
# define SNPRINTF swprintf_s
#else
#if defined(MI_CHAR_TYPE) && (MI_CHAR_TYPE == 2)
#include <wchar.h>
# define SNPRINTF swprintf
#else
# define SNPRINTF snprintf
#endif
#endif

/*
**==============================================================================
**
** LLU - "%llu" format specifier
** LLD - "%lld" format specifier
**
**==============================================================================
*/

#if defined(_MSC_VER)
# define LLU T("%I64u")
# define LLD T("%I64d")
#else
# define LLU T("%llu")
# define LLD T("%lld")
#endif

/*
**==============================================================================
**
** ExtFunctionTable
**
**==============================================================================
*/

static MI_Boolean _IsArrayType(MI_Type type)
{
    return ((MI_Uint32)type & (MI_Uint32)MI_ARRAY) ? MI_TRUE : MI_FALSE;
}

/*
**==============================================================================
**
** Aliases
**
**     This type maintains an array of alias indices and the pos of the 
**     current one.
**
**==============================================================================
*/

#define ALIASES_DEFAULT_SIZE 64

MI_Result Aliases_Initialize(_Inout_ Aliases* aliases)
{
    memset(aliases, 0, sizeof(Aliases));
    aliases->data = (MI_Uint32*)malloc(sizeof(MI_Uint32)*ALIASES_DEFAULT_SIZE);
    if (!aliases->data)
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    aliases->capacity = ALIASES_DEFAULT_SIZE;
    return MI_RESULT_OK;
}

void Aliases_Finalize(_Frees_ptr_opt_ Aliases* aliases)
{
#ifdef _PREFAST_
# pragma prefast (push)
# pragma prefast (disable: 6001)
#endif
    if (aliases && aliases->data)
        free(aliases->data);
#ifdef _PREFAST_
# pragma prefast (pop)
#endif
}

MI_Result Aliases_PutIndex(_Inout_ Aliases* aliases,
    MI_Uint32 index)
{
    if (aliases->size == aliases->capacity)
    {
        MI_Uint32 newsize = aliases->capacity * 2;
        aliases->data = (MI_Uint32*)MemoryRealloc((void**)&aliases->data,  newsize*sizeof(MI_Uint32));
        if (!aliases->data)
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        aliases->capacity = newsize;
    }
    aliases->data[aliases->size++] = index;
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** _DatetimeToStr()
**
**==============================================================================
*/

#define DATETIME_STR_SIZE 26

static void _DatetimeToStr(
    _In_ const MI_Datetime* x, 
    _Pre_writable_size_(DATETIME_STR_SIZE) MI_Char buf[DATETIME_STR_SIZE])
{
    if (x->isTimestamp)
    {
        const MI_Char FMT[] =  T("%04d%02d%02d%02d%02d%02d.%06d%c%03d");
        MI_Sint32 utc = x->u.timestamp.utc;
        SNPRINTF(buf, DATETIME_STR_SIZE, FMT,
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
        const MI_Char FMT[] = T("%08u%02u%02u%02u.%06u:000");
        SNPRINTF(buf, DATETIME_STR_SIZE, FMT,
            x->u.interval.days,
            x->u.interval.hours,
            x->u.interval.minutes,
            x->u.interval.seconds,
            x->u.interval.microseconds);
    }
}


/*
**==============================================================================
**
** _scalarSizes[]
**
**==============================================================================
*/

static unsigned char _scalarSizes[] =
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
    sizeof(MI_Char*),
    sizeof(MI_Instance*),
    sizeof(MI_Instance*),
};

/*
**==============================================================================
**
** _typeNames[]
**
**==============================================================================
*/

static const MI_Char* _typeNames[32] =
{
    MI_T("\007Boolean"),
    MI_T("\005Uint8"),
    MI_T("\005Sint8"),
    MI_T("\006Uint16"),
    MI_T("\006Sint16"),
    MI_T("\006Uint32"),
    MI_T("\006Sint32"),
    MI_T("\006Uint64"),
    MI_T("\006Sint64"),
    MI_T("\006Real32"),
    MI_T("\006Real64"),
    MI_T("\006Char16"),
    MI_T("\010Datetime"),
    MI_T("\006String"),
    NULL, /* reference */
    NULL, /* instance */
    MI_T("\007Boolean"),
    MI_T("\005Uint8"),
    MI_T("\005Sint8"),
    MI_T("\006Uint16"),
    MI_T("\006Sint16"),
    MI_T("\006Uint32"),
    MI_T("\006Sint32"),
    MI_T("\006Uint64"),
    MI_T("\006Sint64"),
    MI_T("\006Real32"),
    MI_T("\006Real64"),
    MI_T("\006Char16"),
    MI_T("\010Datetime"),
    MI_T("\006String"),
    NULL, /* reference */
    NULL, /* instance */
};

/*
**==============================================================================
**
** _PutChar()
**
**==============================================================================
*/

static MI_Result _PutChar(
    _Inout_ Buf* out, 
    MI_Char c)
{
    switch (c)
    {
        case '\b':
            RETERR(Buf_Put(out, LIT("\\b")));
            break;
        case '\t':
            RETERR(Buf_Put(out, LIT("\\t")));
            break;
        case '\n':
            RETERR(Buf_Put(out, LIT("\\n")));
            break;
        case '\f':
            RETERR(Buf_Put(out, LIT("\\f")));
            break;
        case '\r':
            RETERR(Buf_Put(out, LIT("\\r")));
            break;
        case '\"':
            RETERR(Buf_Put(out, LIT("\\\"")));
            break;
        case '\'':
            RETERR(Buf_Put(out, LIT("\\'")));
            break;
        case '\\':
            RETERR(Buf_Put(out, LIT("\\\\")));
            break;
        default:
        {
            if (isprint(c))
            {
                RETERR(Buf_PutC(out, c));
            }
            else
            {
                MI_Char buf[7];

#if (MI_CHAR_TYPE == 1)
                const MI_Char FMT[] = "\\X%02X";
#else
                const MI_Char FMT[] = L"\\X%04X";
#endif
                int n = SNPRINTF(buf, MI_COUNT(buf), FMT, c);
                RETERR(Buf_Put(out, buf, n));
            }

            break;
        }
    }

    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** _PutString()
**
**==============================================================================
*/

static MI_Result _PutString(
    _Inout_ Buf* out, 
    _In_z_ const MI_Char* str)
{
    while (*str)
    {
        RETERR(_PutChar(out, *str));
        str++;
    }

    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** _PutScalarValue()
**
**==============================================================================
*/

static MI_Result _PutScalarValue(
    _Inout_ Buf* out, 
    _In_ const MI_Value* value, 
    MI_Type type,
    _Inout_ Aliases* aliases)
{
    MI_Result r = MI_RESULT_OK;
    MI_Char buf[64];

    switch (type)
    {
        case MI_BOOLEAN:
        {
            if (value->boolean)
                r = Buf_Put(out, LIT("True"));
            else
                r = Buf_Put(out, LIT("False"));
            break;
        }
        case MI_UINT8:
        {
            int n = SNPRINTF(buf, MI_COUNT(buf), T("%u"), value->uint8);
            r = Buf_Put(out, buf, n);
            break;
        }
        case MI_SINT8:
        {
            int n = SNPRINTF(buf, MI_COUNT(buf), T("%d"), value->sint8);
            r = Buf_Put(out, buf, n);
            break;
        }
        case MI_UINT16:
        {
            int n = SNPRINTF(buf, MI_COUNT(buf), T("%u"), value->uint16);
            r = Buf_Put(out, buf, n);
            break;
        }
        case MI_SINT16:
        {
            int n = SNPRINTF(buf, MI_COUNT(buf), T("%d"), value->sint16);
            r = Buf_Put(out, buf, n);
            break;
        }
        case MI_UINT32:
        {
            int n = SNPRINTF(buf, MI_COUNT(buf), T("%u"), value->uint32);
            r = Buf_Put(out, buf, n);
            break;
        }
        case MI_SINT32:
        {
            int n = SNPRINTF(buf, MI_COUNT(buf), T("%d"), value->sint32);
            r = Buf_Put(out, buf, n);
            break;
        }
        case MI_UINT64:
        {
            int n = SNPRINTF(buf, MI_COUNT(buf), LLU, value->uint64);
            r = Buf_Put(out, buf, n);
            break;
        }
        case MI_SINT64:
        {
            int n = SNPRINTF(buf, MI_COUNT(buf), LLD, value->sint64);
            r = Buf_Put(out, buf, n);
            break;
        }
        case MI_REAL32:
        {
            int n = SNPRINTF(buf, MI_COUNT(buf), T("%.23E"), value->real32);
            r = Buf_Put(out, buf, n);
            break;
        }
        case MI_REAL64:
        {
            int n = SNPRINTF(buf, MI_COUNT(buf), T("%.52E"), value->real64);
            r = Buf_Put(out, buf, n);
            break;
        }
        case MI_CHAR16:
        {
            RETERR(Buf_Put(out, LIT("\'")));
            RETERR(_PutChar(out, value->char16));
            RETERR(Buf_Put(out, LIT("\'")));
            break;
        }
        case MI_DATETIME:
        {
            _DatetimeToStr(&value->datetime, buf);
            RETERR(Buf_Put(out, LIT("\"")));
            RETERR(Buf_Put(out, buf, DATETIME_STR_SIZE-1));
            RETERR(Buf_Put(out, LIT("\"")));
            break;
        }
        case MI_STRING:
        {
            RETERR(Buf_Put(out, LIT("\"")));
            RETERR(_PutString(out, value->string));
            RETERR(Buf_Put(out, LIT("\"")));
            break;
        }
        case MI_REFERENCE:
        case MI_INSTANCE:
        {
            int n;
            MI_Char buf[11];

            if (aliases->pos >= aliases->size)
                return MI_RESULT_FAILED;

            RETERR(Buf_Put(out, LIT("$Alias")));
            n = SNPRINTF(buf, MI_COUNT(buf), T("%08X"), 
                aliases->data[aliases->pos]);
            RETERR(Buf_Put(out, buf, n));
            aliases->pos++;
            break;
        }
        default:
        {
            r = MI_RESULT_FAILED;
            break;
        }
    }

    return r;
}

/*
**==============================================================================
**
** _PutValue()
**
**==============================================================================
*/

static MI_Result _PutValue(
    _Inout_ Buf* out, 
    _In_ const MI_Value* value, 
    MI_Type type,
    _Inout_ Aliases* aliases)
{
    switch (type)
    {
        case MI_BOOLEAN:
        case MI_UINT8:
        case MI_SINT8:
        case MI_UINT16:
        case MI_SINT16:
        case MI_UINT32:
        case MI_SINT32:
        case MI_UINT64:
        case MI_SINT64:
        case MI_REAL32:
        case MI_REAL64:
        case MI_CHAR16:
        case MI_DATETIME:
        case MI_STRING:
        case MI_REFERENCE:
        case MI_INSTANCE:
        {
            RETERR(_PutScalarValue(out, value, type, aliases));
            break;
        }
        case MI_BOOLEANA:
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
        case MI_CHAR16A:
        case MI_DATETIMEA:
        case MI_STRINGA:
        case MI_REFERENCEA:
        case MI_INSTANCEA:
        {
            MI_Uint32 i;
            MI_Type stype = (MI_Type)((MI_Uint32)type & 0x0000000F);
            size_t ssize = _scalarSizes[(MI_Uint32)stype];
            MI_Uint8* sdata = value->array.data;

            /* Put opening brace */

            RETERR(Buf_Put(out, LIT("{")));

            /* Put comma-separated elements */

            for (i = 0; i < value->array.size; i++)
            {
                MI_Value svalue;

#ifdef _PREFAST_
# pragma prefast (push)
# pragma prefast (disable: 26015)
#endif
                memcpy(&svalue, sdata, ssize);
#ifdef _PREFAST_
# pragma prefast (pop)
#endif

                /* Put the value */
                RETERR(_PutScalarValue(out, &svalue, stype, aliases));

                /* Put the comma if not the last element */

                if (i + 1 != value->array.size)
                    RETERR(Buf_Put(out, LIT(", ")));

                sdata += ssize;
            }

            /* Put closing brace */

            RETERR(Buf_Put(out, LIT("}")));
        }
    }

    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** _PutDependentInstances()
**
**     Serialize the embedded instances and reference instances as instance
**     aliases.
**
**==============================================================================
*/

static MI_Result _PutInstance(
    _Inout_ Buf* out,
    _Inout_ ExtFunctionTable* eft,
    _In_ const MI_Instance *instance,
    MI_Uint32 serializeFlags,
    MI_Boolean keysOnly,
    MI_Boolean addAlias,
    MI_Boolean nestedCall,
    _Out_opt_ MI_Uint32* aliasIndex);

static MI_Result _PutDependentInstances(
    _Inout_ Buf* out,
    _Inout_ ExtFunctionTable* eft,
    _In_ const MI_Instance *instance,
    MI_Uint32 serializeFlags,
    MI_Boolean keysOnly)
{
    MI_Uint32 numProperties;
    MI_Uint32 i;

    /* Get number of properties */
    RETERR(MI_Instance_GetElementCount(instance, &numProperties));

    /* Serialize REFERENCE and INSTANCE dependencies */

    for (i = 0; i < numProperties; i++)
    {
        const MI_Char* name;
        MI_Value value;
        MI_Type type;
        MI_Uint32 flags;

        RETERR(MI_Instance_GetElementAt(
            instance,
            i,
            &name,
            &value,
            &type,
            &flags));

        /* Skip null properties */

        if (flags & MI_FLAG_NULL)
            continue;

        /* Skip serialization of keys if requested */

        if (keysOnly && !(flags & MI_FLAG_KEY))
            continue;

        /* Serialize dependent REFERENCE and INSTANCE properties */

        if (type == MI_REFERENCE || type == MI_INSTANCE)
        {
            MI_Uint32 aliasIndex;

            if (!value.instance) 
                continue;

            /* Only put keys for referenes */

            RETERR(_PutInstance(
                out, 
                eft, 
                value.instance, 
                serializeFlags,
                (type == MI_REFERENCE) ? MI_TRUE : MI_FALSE, /* keysOnly */
                MI_TRUE,  /* addAlias */
                MI_TRUE, /* nestedCall */
                &aliasIndex));

            RETERR(Aliases_PutIndex(&eft->aliases, aliasIndex));
        }
        else if (type == MI_INSTANCEA)
        {
            MI_Uint32 i;

            if (!value.instancea.data)
                continue;

            for (i = 0; i < value.instancea.size; i++)
            {
                MI_Uint32 aliasIndex;

                /* Ignore NULL instance */
                if (!value.instancea.data[i]) 
                    continue;

                RETERR(_PutInstance(
                    out, 
                    eft, 
                    value.instancea.data[i], 
                    serializeFlags,
                    MI_FALSE, /* keysOnly */
                    MI_TRUE,  /* addAlias */
                    MI_TRUE, /* nestedCall */
                    &aliasIndex));

                RETERR(Aliases_PutIndex(&eft->aliases, aliasIndex));
            }
        }
    }

    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** _PutInstance()
**
*==============================================================================
*/

static MI_Result _PutClass(
    _Inout_ Buf* out,
    _Inout_ ExtFunctionTable* eft,
    _In_ const MI_Class* clss,
    MI_Uint32 serializeFlags);

static MI_Result _PutInstance(
    _Inout_ Buf* out,
    _Inout_ ExtFunctionTable* eft,
    _In_ const MI_Instance *instance,
    MI_Uint32 serializeFlags,
    MI_Boolean keysOnly,
    MI_Boolean addAlias,
    MI_Boolean nestedCall,
    _Out_opt_ MI_Uint32* aliasIndex)
{
    MI_Uint32 numProperties;
    MI_Uint32 i;
    MI_Uint32 orgAliasSize;

    if (aliasIndex)
        *aliasIndex = 0;

    /* Serialize the class (if requested) but not for embedded instances and
     * references.
     */

    if (serializeFlags & MI_SERIALIZER_FLAGS_INSTANCE_WITH_CLASS &&
        !nestedCall)
    {
        MI_Class* clss;

        RETERR(MI_Instance_GetClass(instance, &clss));

        if (_PutClass(out, eft, clss, serializeFlags) != MI_RESULT_OK)
        {
            MI_Class_Delete(clss);
            return MI_RESULT_FAILED;
        }

        MI_Class_Delete(clss);
    }

    /* remember original size */

    orgAliasSize = eft->aliases.size;

    /* Put dependent instances (embedded and references) */

    RETERR(_PutDependentInstances(
        out, 
        eft, 
        instance,
        serializeFlags,
        keysOnly));

    /* Put 'instance of' header */

    RETERR(Buf_Put(out, LIT("instance of ")));

    /* Put classname */
    {
        const MI_Char* className = NULL;
        RETERR(MI_Instance_GetClassName(instance, &className));
        RETERR(Buf_PutStr(out, className));
    }

    /* For aliases only */

    if (addAlias)
    {
        int n;
        MI_Char buf[11];

        RETERR(Buf_Put(out, LIT(" as $Alias")));
        n = SNPRINTF(buf, MI_COUNT(buf), T("%08X"), eft->nextAliasIndex);
        RETERR(Buf_Put(out, buf, n));

        if (aliasIndex)
            *aliasIndex = eft->nextAliasIndex++;
    }

    /* Get number of properties */

    RETERR(MI_Instance_GetElementCount(instance, &numProperties));

    /* Put opening brace */

    RETERR(Buf_Put(out, LIT("\n{\n")));

    /* set pos for accessing aliases */

    eft->aliases.pos = orgAliasSize;

    /* Serialize each property */

    for (i = 0; i < numProperties; i++)
    {
        const MI_Char* name;
        MI_Value value;
        MI_Type type;
        MI_Uint32 flags;

        RETERR(MI_Instance_GetElementAt(
            instance,
            i,
            &name,
            &value,
            &type,
            &flags));

        /* Skip serialization of keys if requested */

        if (keysOnly && !(flags & MI_FLAG_KEY))
        {
            continue;
        }

        /* Skip serialization of null properties */

        if (flags & MI_FLAG_NULL)
            continue;

        /* ATTN: MOF CIMV2 rejects empty brace initialization of arrays */
        /* Skip serialization of empty or null arrays */

        /*if (_IsArrayType(type))
        {
            if (value.array.size == 0 || value.array.data == NULL)
                continue;
        }*/

        /* Put indent */
        RETERR(Buf_Put(out, LIT("    ")));

        /* Put property name */
        RETERR(Buf_PutStr(out, name));

        /* Put equal */
        RETERR(Buf_Put(out, LIT(" = ")));

        /* Put the value */
        RETERR(_PutValue(out, &value, type, &eft->aliases));

        /* Put semicolon */
        RETERR(Buf_Put(out, LIT(";")));

        /* Put newline */
        RETERR(Buf_Put(out, LIT("\n")));
    }

    /* Put closing brace */

    RETERR(Buf_Put(out, LIT("};\n\n")));

    /* restore size */
    eft->aliases.size = orgAliasSize;

    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** _IsLocalProperty()
**
*==============================================================================
*/

static MI_Boolean _IsLocalProperty(
    _In_ const MI_Class* self,
    MI_Uint32 index,
    MI_Uint32 flags)
{
    const MI_ClassDecl* cd = self->classDecl;

    (void)flags;

    if (cd && index < cd->numProperties)
    {
        const MI_PropertyDecl* pd = self->classDecl->properties[index];

        /* If property is self-propagated, it is local */
        if (pd && Tcscasecmp(pd->propagator, cd->name) == 0)
            return MI_TRUE;
    }

    return MI_FALSE;
}

/*
**==============================================================================
**
** _IsLocalMethod()
**
*==============================================================================
*/

static MI_Boolean _IsLocalMethod(
    _In_ const MI_Class* self,
    MI_Uint32 index,
    MI_Uint32 flags)
{
    const MI_ClassDecl* cd = self->classDecl;

    (void)flags;

    if (cd && index < cd->numMethods)
    {
        const MI_MethodDecl* pd = self->classDecl->methods[index];

        /* If method is self-propagated, it is local */
        if (pd && Tcscasecmp(pd->propagator, cd->name) == 0)
            return MI_TRUE;
    }

    return MI_FALSE;
}

/*
**==============================================================================
**
** _PutQualifiers()
**
*==============================================================================
*/

/* If this macro is defined, flag qualifiers are emitted in upper case and
 * qualifier-list qualifiers are emitted in camel notation. This makes it 
 * easy to recognize during testing and debugging where the qualifier was
 * derived from (from the 'flags' field or from the 'qualifierList' field).
 */
#define EMIT_UPPERCASE_FLAG_QUALIFIERS

static MI_Result _PutQualifiers(
    _Inout_ Buf* out,
    MI_Uint32 flags,
    _In_ const MI_QualifierSet* qset,
    MI_Boolean indent)
{
    MI_Uint32 count;
    MI_Uint32 i;
    typedef struct _Info
    {
        const MI_Char* name;
        size_t len;
        MI_Uint32 flag;
    }
    Info;
    static const Info info[] = 
    {
#if defined(EMIT_UPPERCASE_FLAG_QUALIFIERS)
        { LIT("KEY"), MI_FLAG_KEY },
        { LIT("IN"), MI_FLAG_IN },
        { LIT("OUT"), MI_FLAG_OUT },
        { LIT("REQUIRED"), MI_FLAG_REQUIRED },
        { LIT("STATIC"), MI_FLAG_STATIC },
        { LIT("ABSTRACT"), MI_FLAG_ABSTRACT },
        { LIT("TERMINAL"), MI_FLAG_TERMINAL },
        { LIT("EXPENSIVE"), MI_FLAG_EXPENSIVE },
        { LIT("STREAM"), MI_FLAG_STREAM },
#else
        { LIT("Key"), MI_FLAG_KEY },
        { LIT("In"), MI_FLAG_IN },
        { LIT("Out"), MI_FLAG_OUT },
        { LIT("Required"), MI_FLAG_REQUIRED },
        { LIT("Static"), MI_FLAG_STATIC },
        { LIT("Abstract"), MI_FLAG_ABSTRACT },
        { LIT("Terminal"), MI_FLAG_TERMINAL },
        { LIT("Expensive"), MI_FLAG_EXPENSIVE },
        { LIT("Stream"), MI_FLAG_STREAM },
#endif
    };
    MI_Uint32 qmask = 0;
    MI_Uint32 qcount = 0;

    RETERR(MI_QualifierSet_GetQualifierCount(qset, &count));

    /* Bail out if there are no qualifiers */
    if (count == 0)
    {
        const MI_Uint32 MASK =
            MI_FLAG_KEY | 
            MI_FLAG_IN | 
            MI_FLAG_OUT | 
            MI_FLAG_REQUIRED |
            MI_FLAG_STATIC | 
            MI_FLAG_ABSTRACT | 
            MI_FLAG_TERMINAL |
            MI_FLAG_EXPENSIVE | 
            MI_FLAG_STREAM;

        if ((flags & MASK) == 0)
            return MI_RESULT_OK;
    }

    /* Indent? */
    if (indent)
        RETERR(Buf_Put(out, LIT("    ")));

    /* Put opening bracket */
    RETERR(Buf_Put(out, LIT("[")));

    /* Put In(False) qualifier (for parameters only) */

    if ((flags & MI_FLAG_PARAMETER) && !(flags & MI_FLAG_IN))
    {
        if (qcount)
            RETERR(Buf_Put(out, LIT(", ")));

#if defined(EMIT_UPPERCASE_FLAG_QUALIFIERS)
        Buf_Put(out, LIT("IN(False)"));
#else
        Buf_Put(out, LIT("In(False)"));
#endif
        qcount++;
        qmask |= MI_FLAG_IN;
    }

    /* Put flag qualifiers */

    for (i = 0; i < MI_COUNT(info); i++)
    {
        if (flags & info[i].flag)
        {
            if (qcount)
                RETERR(Buf_Put(out, LIT(", ")));

            RETERR(Buf_Put(out, info[i].name, info[i].len));
            qcount++;
            qmask |= info[i].flag;
        }
    }

    /* Put ordinary qualifiers */
    for (i = 0; i < count; i++)
    {
        const MI_Char* qname;
        MI_Type qtype;
        MI_Uint32 qflags;
        MI_Value qvalue;
        Aliases aliases = { 0, 0, 0, NULL };
        MI_Boolean found = MI_FALSE;
        MI_Uint32 j;

        /* Get the qualifier value */
        RETERR(MI_QualifierSet_GetQualifierAt(
            qset,
            i,
            &qname,
            &qtype,
            &qflags,
            &qvalue));

        if (!qname)
            return MI_RESULT_FAILED;

        /* Skip this qualifier if already emitted as part of flags above */
        for (j = 0; j < MI_COUNT(info); j++)
        {
            if (Tcscasecmp(qname, info[j].name) == 0 && (info[j].flag & qmask))
            {
                found = MI_TRUE;
                break;
            }
        }

        if (found)
            continue;

        /* Put comma */
        if (qcount)
            RETERR(Buf_Put(out, LIT(", ")));

        /* Put the qualifier name */
        RETERR(Buf_PutStr(out, qname));

        /* Put value (expect for boolean trues, where true is implicit) */
        if (!(qtype == MI_BOOLEAN && qvalue.boolean))
        {
            /* Put opening parenthesis for non-arrays */
            if (!_IsArrayType(qtype))
                RETERR(Buf_Put(out, LIT("(")));

            /* Put the qualifier value */
            RETERR(_PutValue(out, &qvalue, qtype, &aliases));

            /* Put closing parenthesis for non-arrays */
            if (!_IsArrayType(qtype))
                RETERR(Buf_Put(out, LIT(")")));
        }

        qcount++;
    }

    RETERR(Buf_Put(out, LIT("]\n")));

    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** _PutType()
**
*==============================================================================
*/

static MI_Result _PutType(
    _Inout_ Buf* out,
    MI_Type type,
    _In_z_ const MI_Char* referenceClass)
{
    const MI_Char* p = _typeNames[(size_t)type];

    if (p)
    {
        RETERR(Buf_Put(out, &p[1], p[0]));
        RETERR(Buf_PutC(out, ' '));
    }
    else if (type == MI_REFERENCE || type == MI_REFERENCEA)
    {
        if (!referenceClass)
            return MI_RESULT_FAILED;

        RETERR(Buf_PutStr(out, referenceClass));
        RETERR(Buf_Put(out, LIT(" REF ")));
    }
    else if (type == MI_INSTANCE || type == MI_INSTANCEA)
    {
        /* ATTN: Emit EmbeddedInstance() qualifier */
        RETERR(Buf_Put(out, LIT("String ")));
    }

    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** _GetMethodFlags()
**
*==============================================================================
*/

static MI_Uint32 _GetMethodFlags(
    _In_ const MI_Class* clss,
    MI_Uint32 methodIndex)
{
    const MI_ClassDecl* cd = clss->classDecl;
    const MI_MethodDecl* md;

    if (!cd)
        return 0;

    if (methodIndex >= cd->numMethods)
        return 0;

    md = cd->methods[methodIndex];

    if (!md)
        return 0;

    return md->flags;
}
/*
**==============================================================================
**
** _GetParameterFlags()
**
*==============================================================================
*/

static MI_Uint32 _GetParameterFlags(
    _In_ const MI_Class* clss,
    MI_Uint32 methodIndex,
    MI_Uint32 parameterIndex)
{
    const MI_ClassDecl* cd = clss->classDecl;
    const MI_MethodDecl* md;
    const MI_ParameterDecl* pd;

    if (!cd)
        return 0;

    /* Skip over 'MIReturn' pseudo-parameter */    
    parameterIndex++;

    if (methodIndex >= cd->numMethods)
        return 0;

    md = cd->methods[methodIndex];

    if (!md)
        return 0;

    if (parameterIndex >= md->numParameters)
        return 0;

    pd = md->parameters[parameterIndex];

    if (!pd)
        return 0;

    return pd->flags;
}

/*
**==============================================================================
**
** _PutClass()
**
*==============================================================================
*/

static MI_Result _PutClass(
    _Inout_ Buf* out,
    _Inout_ ExtFunctionTable* eft,
    _In_ const MI_Class* clss,
    MI_Uint32 serializeFlags)
{
    MI_Uint32 i;
    const MI_Char* classname;

    /* Get the classname */

    RETERR(MI_Class_GetClassName(clss, &classname));

    /* Put the super class first */
    if (serializeFlags & MI_SERIALIZER_FLAGS_CLASS_DEEP)
    {
        MI_Class* superClass;
        MI_Result r;

        r = MI_Class_GetParentClass(clss, &superClass);

        if (r == MI_RESULT_OK)
        {
            r = _PutClass(out, eft, superClass, serializeFlags);
            MI_Class_Delete(superClass);
            RETERR(r);
        }
        else if (r != MI_RESULT_INVALID_SUPERCLASS)
        {
            return r;
        }
    }

    /* Put the class qualifiers */
    {
        MI_QualifierSet qset;
        MI_Uint32 flags = clss->classDecl ? clss->classDecl->flags : 0;
        RETERR(MI_Class_GetClassQualifierSet(clss, &qset));
        RETERR(_PutQualifiers(
            out, 
            flags, 
            &qset, 
            MI_FALSE));
    }

    /* Put 'class CLASSNAME' header */
    {
        const MI_Char* cn = NULL;
        RETERR(MI_Class_GetClassName(clss, &cn));
        RETERR(Buf_Put(out, LIT("class ")));
        RETERR(Buf_PutStr(out, cn));
    }

    /* Put superclass name (if any) */
    {
        const MI_Char* scn = NULL;

        if (MI_Class_GetParentClassName(clss, &scn) == MI_RESULT_OK && scn)
        {
            RETERR(Buf_Put(out, LIT(" : ")));
            RETERR(Buf_PutStr(out, scn));
        }
    }

    /* Put opening brace */
    RETERR(Buf_Put(out, LIT("\n{\n")));

    /* Put the properties */
    {
        MI_Uint32 elementCount;

        /* Get number of elements */
        RETERR(MI_Class_GetElementCount(clss, &elementCount));

        /* Put each property */
        for (i = 0; i < elementCount; i++)
        {
            const MI_Char* name = NULL;
            MI_Value value;
            MI_Boolean valueExists = MI_FALSE;
            MI_Type type = MI_BOOLEAN;
            MI_Char* referenceClass = NULL;
            MI_QualifierSet qset;
            MI_Uint32 flags = 0;

            /* Clear all this memory in case GetElementAt() fails to set them */
            memset(&value, 0, sizeof(value));
            memset(&qset, 0, sizeof(qset));

            /* Get next element */
            RETERR(MI_Class_GetElementAt(
                clss,
                i,
                &name,
                &value,
                &valueExists,
                &type,
                &referenceClass,
                &qset,
                &flags));

            /* Fail is name is null */
            if (!name)
                return MI_RESULT_FAILED;

            /* Determine whether feature is local */
            if (!_IsLocalProperty(clss, i, flags))
            {
                continue;
            }

            /* Put the qualifiers */
            RETERR(_PutQualifiers(
                out, 
                flags, 
                &qset, 
                MI_TRUE));

            /* Put the type */
            RETERR(Buf_Put(out, LIT("    ")));
            RETERR(_PutType(out, type, referenceClass));

            /* Put property name */
            RETERR(Buf_PutStr(out, name));

            /* Put array subscript (if any) */
            if (_IsArrayType(type))
            {
                RETERR(Buf_Put(out, LIT("[]")));
            }

            /* Put the value (if any) */
            if (valueExists)
            {
                Aliases aliases = { 0, 0, 0, NULL };
                RETERR(Buf_Put(out, LIT(" = ")));
                RETERR(_PutValue(out, &value, type, &aliases));
            }

            /* Put semicolon and newline */
            RETERR(Buf_Put(out, LIT(";\n")));
        }
    }

    /* Put the methods */
    {
        MI_Uint32 methodCount;

        /* Get number of methods */
        RETERR(MI_Class_GetMethodCount(clss, &methodCount));

        /* Put each method */
        for (i = 0; i < methodCount; i++)
        {
            const MI_Char* name = NULL;
            MI_QualifierSet qset;
            MI_QualifierSet qset2;
            MI_ParameterSet pset;
            MI_Uint32 flags = 0;
            MI_Type returnType;

            memset(&qset, 0, sizeof(qset));
            memset(&qset2, 0, sizeof(qset2));
            memset(&pset, 0, sizeof(pset));

            /* Get next method */
            RETERR(MI_Class_GetMethodAt(
                clss,
                i,
                &name,
                &qset,
                &pset));

            /* Fail if name is null */
            if (!name)
                return MI_RESULT_FAILED;

            /* Determine whether feature is local */
            if (!_IsLocalMethod(clss, i, flags))
            {
                continue;
            }

            /* Get flags for this method (if classDecl non-null) */
            flags = _GetMethodFlags(clss, i);

            /* ATTN: no way to get EmbeddedInstance classname here! */

            /* Put the qualifiers */
            RETERR(_PutQualifiers(
                out, 
                flags, 
                &qset, 
                MI_TRUE));

            /* Get the return type */
            RETERR(MI_ParameterSet_GetMethodReturnType(
                &pset,
                &returnType,
                &qset2));

            /* Array return types are not legal in MOF */
            if (_IsArrayType(returnType))
            {
                return MI_RESULT_FAILED;
            }

            /* Put the return type */
            RETERR(Buf_Put(out, LIT("    ")));
            RETERR(_PutType(out, returnType, NULL));

            /* Put method name */
            RETERR(Buf_PutStr(out, name));

            /* Put opening parenthesis */
            RETERR(Buf_Put(out, LIT("(")));

            /* Put the parameters */
            {
                MI_Uint32 parameterCount;
                MI_Uint32 j;

                RETERR(MI_ParameterSet_GetParameterCount(
                    &pset,
                    &parameterCount));

                for (j = 0; j < parameterCount; j++)
                {
                    const MI_Char* name;
                    MI_Type type;
                    MI_Char* referenceClass;
                    MI_QualifierSet parameterQualifierSet;
                    MI_Uint32 parameterFlags = 0;

                    /* Get next parameter */
                    RETERR(MI_ParameterSet_GetParameterAt(
                        &pset,
                        j,
                        &name,
                        &type,
                        &referenceClass,
                        &parameterQualifierSet));

                    if (!name)
                        return MI_RESULT_FAILED;

                    /* Get the parameter flags */
                    parameterFlags = _GetParameterFlags(clss, i, j);

                    /* Put the qualifiers */
                    RETERR(Buf_PutC(out, '\n'));
                    RETERR(Buf_Put(out, LIT("    ")));
                    RETERR(_PutQualifiers(
                        out, 
                        parameterFlags,
                        &parameterQualifierSet,
                        MI_TRUE));

                    /* Put type */
                    RETERR(Buf_Put(out, LIT("        ")));
                    RETERR(_PutType(out, type, referenceClass));

                    /* Put name */
                    RETERR(Buf_PutStr(out, name));

                    /* Put array subscript (if any) */
                    if (_IsArrayType(type))
                    {
                        RETERR(Buf_Put(out, LIT("[]")));
                    }

                    if (j + 1 != parameterCount)
                        RETERR(Buf_Put(out, LIT(",")));
                }
            }

            /* Put closing parenthesis */
            RETERR(Buf_Put(out, LIT(");\n")));
        }
    }

    /* Put closing brace */
    RETERR(Buf_Put(out, LIT("};\n\n")));

    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Function-Table Methods
**
**==============================================================================
*/

static MI_Result MI_CALL _Serializer_Close(
    _Inout_ MI_Serializer *serializer)
{
    ExtFunctionTable* eft;

    if (!serializer)
        return MI_RESULT_INVALID_PARAMETER;

    if (serializer->reserved1 != cCodecMagic)
        return MI_RESULT_INVALID_PARAMETER;

    eft = (ExtFunctionTable*)(serializer->reserved2);

    if (!eft)
        return MI_RESULT_FAILED;

    Aliases_Finalize(&eft->aliases);

    free(eft);

    memset(serializer, 0, sizeof(MI_Serializer));

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _Serializer_SerializeClass(
    _Inout_ MI_Serializer *serializer, 
    MI_Uint32 flags, 
    _In_ const MI_Class *clss, 
   _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded)
{
    Buf out;
    ExtFunctionTable* eft;

    /* Check arguments */

    if (!serializer || !clss || (!clientBuffer && clientBufferLength))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* Check the magic number */

    if (serializer->reserved1 != cCodecMagic)
        return MI_RESULT_FAILED;

    /* Extract the extended function table */

    eft = (ExtFunctionTable*)(serializer->reserved2);

    if (!eft)
        return MI_RESULT_FAILED;

    /* Construct Buf */

    if (Buf_Construct(
        &out, 
        (MI_Char*)clientBuffer,
        clientBufferLength / sizeof(MI_Char)) != 0)
    {
        return MI_RESULT_FAILED;
    }

    /* Put the class */
    {
        MI_Result r = _PutClass(
            &out, 
            eft,
            clss,
            flags);

        if (r != MI_RESULT_OK)
        {
            Buf_Destruct(&out);
            return r;
        }
    }

    /* Set clientBufferNeeded */

    if (clientBufferNeeded)
        *clientBufferNeeded = (MI_Uint32)(out.size * sizeof(MI_Char));

    /* Write the output string */

    if (out.size * sizeof(MI_Char) > clientBufferLength)
    {
        Buf_Destruct(&out);
        return MI_RESULT_FAILED;
    }

    Buf_Destruct(&out);
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _Serializer_SerializeInstance(
   _Inout_ MI_Serializer *serializer, 
   MI_Uint32 flags, 
   _In_ const MI_Instance *instance, 
   _Out_writes_bytes_(clientBufferLength) MI_Uint8 *clientBuffer,
    MI_Uint32 clientBufferLength,
   _Inout_ MI_Uint32 *clientBufferNeeded)
{
    Buf out;
    ExtFunctionTable* eft;

    UNUSED(flags);

    /* Check arguments */

    if (!serializer || !instance || (!clientBuffer && clientBufferLength))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* Check the magic number */

    if (serializer->reserved1 != cCodecMagic)
        return MI_RESULT_FAILED;

    /* Extract the extended function table */

    eft = (ExtFunctionTable*)(serializer->reserved2);

    if (!eft)
        return MI_RESULT_FAILED;

    /* Construct Buf */

    if (Buf_Construct(
        &out, 
        (MI_Char*)clientBuffer,
        clientBufferLength / sizeof(MI_Char)) != 0)
    {
        return MI_RESULT_FAILED;
    }

    /* Put the instance */
    {
        MI_Result r = _PutInstance(
            &out, 
            eft, 
            instance,
            flags,
            MI_FALSE, /* keysOnly */
            MI_FALSE, /* addAlias */
            MI_FALSE, /* nestedCall */
            NULL);

        if (r != MI_RESULT_OK)
        {
            Buf_Destruct(&out);
            return r;
        }
    }

    /* Set clientBufferNeeded */

    if (clientBufferNeeded)
        *clientBufferNeeded = (MI_Uint32)(out.size * sizeof(MI_Char));

    /* Write the output string */

    if (out.size * sizeof(MI_Char) > clientBufferLength)
    {
        Buf_Destruct(&out);
        return MI_RESULT_FAILED;
    }

    Buf_Destruct(&out);
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Function Table
**
**==============================================================================
*/

static MI_SerializerFT _Serializer_ft =
{
    _Serializer_Close,
    _Serializer_SerializeClass,
    _Serializer_SerializeInstance
};

/*
**==============================================================================
**
** Public Functions
**
**==============================================================================
*/

MI_Result MI_MAIN_CALL MI_Application_NewSerializer_Mof(
    _Inout_ MI_Application *application, 
    MI_Uint32 flags,
    _In_z_ MI_Char *format, 
    _Out_ MI_Serializer *serializer)
{
    UNUSED(application);

    /* Check for MOF format */
    if (!format)
        return MI_RESULT_NOT_SUPPORTED;

    /* Check flags parameter */
    if (flags != 0)
        return MI_RESULT_INVALID_PARAMETER;

    /* Verify that serializer parameter is not null */
    if (!serializer)
        return MI_RESULT_INVALID_PARAMETER;

    /* MI_Serializer.reserved1 */
    serializer->reserved1 = cCodecMagic;

    /* MI_Serializer.reserved2 */
    {
        ExtFunctionTable* eft = 
            (ExtFunctionTable*)malloc(sizeof(ExtFunctionTable));

        if (!eft)
            return MI_RESULT_FAILED;

        eft->ft = _Serializer_ft;
        eft->nextAliasIndex = 0;

        {
            MI_Result r = Aliases_Initialize(&eft->aliases);
            if (r != MI_RESULT_OK)
            {
                free(eft);
                memset(serializer, 0, sizeof(MI_Serializer));
                return r;
            }
        }
        serializer->reserved2 = (ptrdiff_t)eft;
    }

    return MI_RESULT_OK;
}
