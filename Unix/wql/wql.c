/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "wql.h"
#include <ctype.h>

#ifndef _MSC_VER
#include <pthread.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pal/strings.h>
#include <base/classdecl.h>
#include <base/helpers.h>
#include <pal/format.h>
#include "wqlyacc.h"
#include "state.h"
#include "like.h"

extern int wqlparse();
extern void WQL_ResetParser();

WQL_State wqlstate;

#ifdef _MSC_VER
/* TODO: Fix this otherwise we are not thread safe */
static void _Lock() {  }
static void _Unlock() {  }
#else
static pthread_mutex_t _mutex = PTHREAD_MUTEX_INITIALIZER;
static void _Lock() { pthread_mutex_lock(&_mutex); }
static void _Unlock() { pthread_mutex_unlock(&_mutex); }
#endif

void* wqlmalloc(size_t size)
{
    return Batch_Get(wqlstate.wql->batch, size);
}

ZChar* wqlstrdup(const ZChar * str)
{
    return Batch_Tcsdup(wqlstate.wql->batch, str);
}

WQL* WQL_Parse(
    const ZChar* text, 
    Batch* batch,
    WQL_Dialect dialect)
{
    WQL* self = NULL;
    int deleteBatch;

    /* Acquire mutex to synchronize access to global Lex/Yacc state */
    _Lock();

    /* Create batch if none */
    if (!batch)
    {
        batch = Batch_New(BATCH_MAX_PAGES);

        if (!batch)
        {
            _Unlock();
            return NULL;
        }

        deleteBatch = 1;
    }
    else
    {
        deleteBatch = 0;
    }

    /* Allocate the WQL object */
    {
        self = (WQL*)Batch_GetClear(batch, sizeof(WQL));

        if (!self)
        {
            if (deleteBatch)
                Batch_Delete(batch);

            _Unlock();
            return NULL;
        }
    }

    /* Set the dialect */
    self->dialect = dialect;

    /* Initialize WQL object */
    self->batch = batch;
    self->deleteBatch = deleteBatch;
    self->text = Batch_Tcsdup(batch, text);

    if (!self->text)
    {
        if (deleteBatch)
            Batch_Delete(batch);

        _Unlock();
        return NULL;
    }

    /* Initialize global parser state */
    memset(&wqlstate, 0, sizeof(WQL_State));
    wqlstate.text = self->text;
    wqlstate.size = (int)Tcslen(text);
    wqlstate.wql = self;
    wqlstate.ptr = text;

    /* Parse the text */
    wqlparse();

    /* Reset global parser states */
    WQL_ResetParser();

    /* Get return status */
    if (wqlstate.status != 0)
    {
        WQL_Delete(self);
        self = NULL;
    }

    /* Clear global parser state */
    memset(&wqlstate, 0, sizeof(WQL_State));

    _Unlock();
    return self;
}

WQL* WQL_Clone(const WQL* self, Batch* batch)
{
    WQL* result;
    int deleteBatch;
    size_t i;

    /* Check for null parameter */
    if (!self)
        return NULL;

    /* Create batch if none */
    if (!batch)
    {
        batch = Batch_New(BATCH_MAX_PAGES);

        if (!batch)
            return NULL;

        deleteBatch = 1;
    }
    else
        deleteBatch = 0;

    /* Allocate the WQL object */
    {
        result = (WQL*)Batch_GetClear(batch, sizeof(WQL));

        if (!result)
            goto failed;
    }

    /* Initialize batch fields */
    result->batch = batch;
    result->deleteBatch = deleteBatch;

    /* Clone properties */
    {
        for (i = 0; i < self->nproperties; i++)
        {
            result->properties[i] = Batch_Tcsdup(batch, self->properties[i]);

            if (!result->properties[i])
                goto failed;
        }

        result->nproperties = self->nproperties;
    }

    /* Clone classname */
    if (self->className)
    {
        result->className = Batch_Tcsdup(batch, self->className);

        if (!result->className)
            goto failed;
    }

    /* Clone symbols */
    {
        for (i = 0; i < self->nsymbols; i++)
        {
            result->symbols[i] = self->symbols[i];

            if (self->symbols[i].type == WQL_TYPE_IDENTIFIER ||
                self->symbols[i].type == WQL_TYPE_STRING)
            {
                if (self->symbols[i].value.string)
                {
                    result->symbols[i].value.string = 
                        Batch_Tcsdup(batch, self->symbols[i].value.string);

                    if (!result->symbols[i].value.string)
                        goto failed;
                }
            }
        }

        result->nsymbols = self->nsymbols;
    }

    /* Clone text */
    if (self->text)
    {
        result->text = Batch_Tcsdup(batch, self->text);

        if (!result->text)
            goto failed;
    }

    return result;

failed:

    if (deleteBatch)
        Batch_Delete(batch);

    return NULL;
}

void WQL_Delete(WQL* self)
{
    if (self->deleteBatch)
        Batch_Delete(self->batch);
}

/* YACC calls this function to report errors */
void wqlerror(const char * msg)
{
    MI_UNUSED(msg);
    wqlstate.status = -1;
}

MI_Boolean WQL_ContainsProperty(
    const WQL* wql,
    const ZChar* propertyName)
{
    size_t i;

    if (wql->nproperties == 0)
        return MI_TRUE;

    for (i = 0; i < wql->nproperties; i++)
    {
        if (Tcscmp(propertyName, wql->properties[i]) == 0)
            return MI_TRUE;
    }

    /* Not found! */
    return MI_FALSE;
}

int _ValidateLookup(
    const ZChar* name, 
    const ZChar* embeddedClassName, 
    const ZChar* embeddedPropertyName, 
    WQL_Symbol* symbol, 
    Batch* batch,
    void* data)
{
    const MI_ClassDecl* cd = (const MI_ClassDecl*)data;
    const MI_PropertyDecl* pd;

#if 0
    printf("_ValidateLookup(): {%s}{%s}{%s}\n", 
        name, embeddedClassName, embeddedPropertyName);
#endif

    MI_UNUSED(batch);

    /* Check for null parameters */
    if (!name || !symbol || !data)
        return -1;

    /* Handle ISA operation */
    if (name && embeddedClassName && !embeddedPropertyName)
    {
        symbol->type = WQL_TYPE_BOOLEAN;
        symbol->value.boolean = MI_TRUE;
        return 0;
    }

    /* Lookup the property with this name */
    {
        pd = ClassDecl_FindPropertyDecl(cd, name);

        if (!pd)
            return -1;
    }

    /* Convert to symbol */
    switch (pd->type)
    {
        case MI_BOOLEAN:
            symbol->type = WQL_TYPE_BOOLEAN;
            symbol->value.boolean = 0;
            return 0;
        case MI_UINT8:
        case MI_SINT8:
        case MI_UINT16:
        case MI_SINT16:
        case MI_UINT32:
        case MI_SINT32:
        case MI_UINT64:
        case MI_SINT64:
        case MI_CHAR16:
            symbol->type = WQL_TYPE_INTEGER;
            symbol->value.integer = 0;
            return 0;
        case MI_REAL32:
        case MI_REAL64:
            symbol->type = WQL_TYPE_REAL;
            symbol->value.real = 0.0;
            return 0;
        case MI_DATETIME:
        case MI_STRING:
            symbol->type = WQL_TYPE_STRING;
            symbol->value.string = MI_T("");
            return 0;
        case MI_INSTANCE:
            /* Use WQL_TYPE_ANY since the type of the embedded instance property
             * cannot be deterined.
             */
            symbol->type = WQL_TYPE_ANY;
            return 0;
        default:
            break;
    }

    /* Unknown token type */
    return -1;
}

int WQL_Validate(const WQL* self, const MI_ClassDecl* cd)
{
    size_t i;

    /* Verify that properties in SELECT list exist in class declaration */
    for (i = 0; i < self->nproperties; i++)
    {
        if (!ClassDecl_FindPropertyDecl(cd, self->properties[i]))
            return -1;
    }

    /* Perform mock evaluation to find non-existent properties and
     * property-literal mismatches.
     */
    if (WQL_Eval(self, _ValidateLookup, (void*)cd) == -1)
    {
        return -1;
    }

    return 0;
}

static int _FixupTypeAux(WQL_Symbol* sym, WQL_Type type)
{
    if (sym->type != WQL_TYPE_STRING)
        return -1;

    if (type == WQL_TYPE_REAL)
    {
        ZChar* end = NULL;
        sym->value.real = Tcstod(sym->value.string, &end);

        if (end == sym->value.string)
            return -1;

        if (*end != '\0')
            return -1;

        sym->type = WQL_TYPE_REAL;
        return 0;
    }
    else if (type == WQL_TYPE_INTEGER)
    {
        ZChar* end = NULL;
        sym->value.integer = Tcstoll(sym->value.string, &end, 10);

        if (end == sym->value.string)
            return -1;

        if (*end != '\0')
            return -1;

        sym->type = WQL_TYPE_INTEGER;
        return 0;
    }
    else if (type == WQL_TYPE_BOOLEAN)
    {
        if (Tcscasecmp(sym->value.string, PAL_T("true")) == 0)
            sym->value.boolean = 1;
        else if (Tcscasecmp(sym->value.string, PAL_T("false")) == 0)
            sym->value.boolean = 0;
        else
            return -1;

        sym->type = WQL_TYPE_BOOLEAN;
        return 0;
    }

    return -1;
}

/* 
 * If the types of the two symbols are incompatible, then if either symbol 
 * is a string, attempt to convert it to the type of the other symbol. For
 * example, the string will be converted to a real, integer, or boolean.
 */
static int _FixupType(WQL_Symbol* lhs, WQL_Symbol* rhs)
{
    if (lhs->type == rhs->type)
        return 0;

    if (lhs->type == WQL_TYPE_STRING)
    {
        return _FixupTypeAux(lhs, rhs->type);
    }
    else if (rhs->type == WQL_TYPE_STRING)
    {
        return _FixupTypeAux(rhs, lhs->type);
    }

    return -1;
}

/*
**-----------------------------------------------------------------------------
** @brief   See if a string matches a template string
**
** @param   [in] s1 - one string
** @param   [in] s1 - another string
**
** @returns 0 for a match, > 0 for s1 > s2; < 0 for s1 < s2
**-----------------------------------------------------------------------------
*/

static int _Compare(const WQL_Symbol* s1, const WQL_Symbol* s2)
{
    switch (s1->type)
    {
        case WQL_TYPE_BOOLEAN:
        {
            return s1->value.boolean - s2->value.boolean;
        }
        case WQL_TYPE_INTEGER:
        {
            if (s1->value.integer < s2->value.integer)
                return -1;
            else if (s1->value.integer > s2->value.integer)
                return 1;
            else
                return 0;
        }
        case WQL_TYPE_REAL:
        {
            if (s1->value.real < s2->value.real)
                return -1;
            else if (s1->value.real > s2->value.real)
                return 1;
            else
                return 0;
        }
        case WQL_TYPE_STRING:
        {
            return Tcscasecmp(s1->value.string, s2->value.string);
        }
        default:
            return -1;
    }
}

static int _CompareLike(const WQL_Symbol* s1, const WQL_Symbol* s2)
{
    const ZChar* pattern;
    const ZChar* string;

    if (s1->type != WQL_TYPE_STRING || s2->type != WQL_TYPE_STRING)
        return -1;

    string = s1->value.string;
    pattern = s2->value.string;

    if (WQL_MatchLike(pattern, string, '\0'))
        return 0;
    else
        return -1;
}

extern int WQL_Eval(
    const WQL* wql, 
    WQL_Lookup lookup,
    void* data)
{
    size_t i;
    WQL_Symbol symbols[WQL_MAX_SYMBOLS];
    size_t nsymbols = 0;

    if (!wql || !wql->className || !lookup)
        return -1;

    /* Return success if there is no WHERE clause */
    if (wql->nsymbols == 0)
        return 0;

    /* Perform postfix evaluation */
    for (i = 0; i < wql->nsymbols; i++)
    {
        const WQL_Symbol* sym = &wql->symbols[i];
        WQL_Type type = sym->type;

        if (nsymbols >= WQL_MAX_SYMBOLS)
            return -1;

        switch (type)
        {
            case WQL_TYPE_AND:
            case WQL_TYPE_OR:
            {
                if (nsymbols < 2)
                    return -1;

                {
                    WQL_Symbol s2 = symbols[--nsymbols];
                    WQL_Symbol s1 = symbols[--nsymbols];
                    WQL_Symbol s;
                    int f;

                    memset(&s, '\0', sizeof(s));

                    if (s1.type != WQL_TYPE_BOOLEAN)
                        return -1;
                    if (s2.type != WQL_TYPE_BOOLEAN)
                        return -1;

                    s.type = WQL_TYPE_BOOLEAN;

                    if (type == WQL_TYPE_OR)
                        f = (s1.value.boolean || s2.value.boolean);
                    else
                        f = (s1.value.boolean && s2.value.boolean);

                    s.value.boolean = f ? 1 : 0;
                    symbols[nsymbols++] = s;
                }

                break;
            }
            case WQL_TYPE_NOT:
            {
                if (nsymbols < 1)
                    return -1;
                {
                    WQL_Symbol s1 = symbols[--nsymbols];
                    WQL_Symbol s;

                    memset(&s, '\0', sizeof(s));

                    if (s1.type != WQL_TYPE_BOOLEAN)
                        return -1;

                    s.type = WQL_TYPE_BOOLEAN;
                    s.value.boolean = (!s1.value.boolean) ? 1 : 0;
                    symbols[nsymbols++] = s;
                }

                break;
            }
            case WQL_TYPE_EQ:
            case WQL_TYPE_NE:
            case WQL_TYPE_LT:
            case WQL_TYPE_LE:
            case WQL_TYPE_GT:
            case WQL_TYPE_GE:
            case WQL_TYPE_LIKE:
            {
                if (nsymbols < 2)
                    return -1;
                {
                    WQL_Symbol s2 = symbols[--nsymbols];
                    WQL_Symbol s1 = symbols[--nsymbols];
                    WQL_Symbol s;
                    int r;
                    int f;

                    memset(&s, '\0', sizeof(s));

                    /* This type only returned by _ValidateLookup() */
                    if (s2.type == WQL_TYPE_ANY || s1.type == WQL_TYPE_ANY)
                    {
                        return 0;
                    }

                    /* If either operand is null */
                    if (s1.type == WQL_TYPE_NULL || s2.type == WQL_TYPE_NULL)
                    {
                        /* Set flag non-zero if both operands are null */
                        int bothNull =
                            (s1.type==WQL_TYPE_NULL && s2.type==WQL_TYPE_NULL);

                        if (type == WQL_TYPE_EQ || type == WQL_TYPE_LIKE)
                        {
                            s.type = WQL_TYPE_BOOLEAN;
                            s.value.boolean = bothNull ? 1 : 0;
                            symbols[nsymbols++] = s;
                            break;
                        }
                        else if (type == WQL_TYPE_NE)
                        {
                            s.type = WQL_TYPE_BOOLEAN;
                            s.value.boolean = bothNull ? 0 : 1;
                            symbols[nsymbols++] = s;
                            break;
                        }
                        else
                            return -1;
                    }
                    else
                    {

                        if (type == WQL_TYPE_LIKE)
                            r = _CompareLike(&s1, &s2);
                        else
                        {
                            WQL_Symbol lhs = s1;
                            WQL_Symbol rhs = s2;

                            if (lhs.type != rhs.type)
                            {
                                if (_FixupType(&lhs, &rhs) != 0)
                                    return -1;
                            }

                            r = _Compare(&lhs, &rhs);
                        }

                        switch (type)
                        {
                            case WQL_TYPE_EQ:
                            case WQL_TYPE_LIKE:
                                f = (r == 0);
                                break;
                            case WQL_TYPE_NE:
                                f = (r != 0);
                                break;
                            case WQL_TYPE_LT:
                                f = (r < 0);
                                break;
                            case WQL_TYPE_LE:
                                f = (r <= 0);
                                break;
                            case WQL_TYPE_GT:
                                f = (r > 0);
                                break;
                            case WQL_TYPE_GE:
                                f = (r >= 0);
                                break;
                            default:
                                f = 0;
                                break;
                        }

                        s.type = WQL_TYPE_BOOLEAN;
                        s.value.boolean = f ? 1 : 0;
                        symbols[nsymbols++] = s;
                    }
                }
                break;
            }
            case WQL_TYPE_IDENTIFIER:
            {
                WQL_Symbol tmp;

                memset(&tmp, 0, sizeof(WQL_Symbol));

                if ((*lookup)(
                    sym->value.string, 
                    sym->value.embeddedClassName, 
                    sym->value.embeddedPropertyName, 
                    &tmp, 
                    wql->batch, 
                    data) != 0)
                {
                    return -1;
                }

                if (tmp.type != WQL_TYPE_BOOLEAN &&
                    tmp.type != WQL_TYPE_INTEGER &&
                    tmp.type != WQL_TYPE_REAL &&
                    tmp.type != WQL_TYPE_STRING &&
                    tmp.type != WQL_TYPE_NULL &&
                    tmp.type != WQL_TYPE_ANY)
                {
                    return -1;
                }
                symbols[nsymbols++] = tmp;
                break;
            }
            case WQL_TYPE_BOOLEAN:
            case WQL_TYPE_INTEGER:
            case WQL_TYPE_REAL:
            case WQL_TYPE_STRING:
            case WQL_TYPE_NULL:
            case WQL_TYPE_ANY:
                symbols[nsymbols++] = *sym;
                break;

            case WQL_TYPE_ISA:
            {
                WQL_Symbol s2;
                WQL_Symbol s1;

                if (nsymbols < 2)
                    return -1;

                s2 = symbols[--nsymbols];
                s1 = symbols[--nsymbols];

                if (s1.type != WQL_TYPE_STRING)
                    return -1;

                if (s2.type != WQL_TYPE_STRING)
                    return -1;

                /* Ask lookup() to perform ISA operation */
                {
                    WQL_Symbol tmp = s2;

                    if ((*lookup)(
                        s1.value.string, /* Embedded property name */
                        s2.value.string, /* Embedded class name */
                        NULL,
                        &tmp, 
                        wql->batch, 
                        data) != 0)
                    {
                        return -1;
                    }

                    symbols[nsymbols++] = tmp;
                }
                break;
            }
        }
    }

    /* There should be exactly 1 symbol left on stack */
    if (nsymbols != 1)
        return -1;

    /* There should be exactly 1 symbol left on stack */
    /* Final token on stack should be boolean */
    if (symbols[0].type != WQL_TYPE_BOOLEAN)
        return -1;

    /* Return '0' for equal, '1' for not-equal */
    if (symbols[0].value.boolean)
        return 0;
    else
        return 1;
}

int WQL_LookupInstanceProperty(
    const ZChar* name, 
    const ZChar* embeddedClassName, 
    const ZChar* embeddedPropertyName, 
    WQL_Symbol* symbol, 
    Batch* batch,
    void* data)
{
    const MI_Instance* instance = (const MI_Instance*)data;
    MI_Result r;
    MI_Value value;
    MI_Type type;
    MI_Uint32 flags;

#if 0
    printf("WQL_LookupInstanceProperty{%s}{%s}{%s}\n", 
        name, embeddedClassName, embeddedPropertyName);
#endif

    /* Check for null parameters */
    if (!name || !symbol || !data)
        return -1;

    /* Lookup the property with this name */
    r = __MI_Instance_GetElement(instance, name, &value, &type, &flags, 0);

    /* Fail if not found */
    if (r != MI_RESULT_OK)
        return -1;

    /* Handle ISA opeartion and ISA check for gets on embedded properties:
     * For example: SourceInstance.CIM_StorageVolume.OperationalStatus
     */
    if (embeddedClassName)
    {
        const MI_ClassDecl* cd;
        MI_Boolean isa = MI_FALSE;

        if (type != MI_INSTANCE || !value.instance)
            return -1;

        /* Perform ISA check */

        for (cd = value.instance->classDecl; cd; cd = cd->superClassDecl)
        {
            if (Tcscmp(cd->name, embeddedClassName) == 0)
            {
                isa = MI_TRUE;
                break;
            }
        }

        /* If lookup was called just to perform an ISA check */

        if (!embeddedPropertyName)
        {
            symbol->type = WQL_TYPE_BOOLEAN;
            symbol->value.boolean = isa;
            return 0;
        }

        /* If lookup was called to get an embedded intance property */

        if (embeddedPropertyName && !isa)
        {
            /* Class was wrong type */
            return -1;
        }
    }

    /* Handle get embedded instance property */

    if (embeddedPropertyName)
    {
        if (type != MI_INSTANCE || !value.instance)
            return -1;

        r = __MI_Instance_GetElement(
            value.instance, 
            embeddedPropertyName, 
            &value, 
            &type, 
            &flags, 0);

        if (r != MI_RESULT_OK)
            return -1;
    }

    /* Handle null case */
    if (flags & MI_FLAG_NULL)
    {
        symbol->type = WQL_TYPE_NULL;
        return 0;
    }

    /* Convert to symbol */
    switch (type)
    {
        case MI_BOOLEAN:
        {
            symbol->type = WQL_TYPE_BOOLEAN;
            symbol->value.boolean = value.boolean;
            return 0;
        }
        case MI_UINT8:
        {
            symbol->type = WQL_TYPE_INTEGER;
            symbol->value.integer = (MI_Sint64)value.uint8;
            return 0;
        }
        case MI_SINT8:
        {
            symbol->type = WQL_TYPE_INTEGER;
            symbol->value.integer = (MI_Sint64)value.sint8;
            return 0;
        }
        case MI_UINT16:
        case MI_CHAR16:
        {
            symbol->type = WQL_TYPE_INTEGER;
            symbol->value.integer = (MI_Sint64)value.uint16;
            return 0;
        }
        case MI_SINT16:
        {
            symbol->type = WQL_TYPE_INTEGER;
            symbol->value.integer = (MI_Sint64)value.sint16;
            return 0;
        }
        case MI_UINT32:
        {
            symbol->type = WQL_TYPE_INTEGER;
            symbol->value.integer = (MI_Sint64)value.uint32;
            return 0;
        }
        case MI_SINT32:
        {
            symbol->type = WQL_TYPE_INTEGER;
            symbol->value.integer = (MI_Sint64)value.sint32;
            return 0;
        }
        case MI_UINT64:
        {
            /* ATTN: note that MAX(MI_Uint64) cannot be represented */
            symbol->type = WQL_TYPE_INTEGER;
            symbol->value.integer = (MI_Sint64)value.uint64;
            return 0;
        }
        case MI_SINT64:
        {
            symbol->type = WQL_TYPE_INTEGER;
            symbol->value.integer = (MI_Sint64)value.sint64;
            return 0;
        }
        case MI_REAL32:
        {
            symbol->type = WQL_TYPE_REAL;
            symbol->value.real = (MI_Real32)value.real32;
            return 0;
        }
        case MI_REAL64:
        {
            symbol->type = WQL_TYPE_REAL;
            symbol->value.real = value.real64;
            return 0;
        }
        case MI_DATETIME:
        {
            ZChar buf[26];
            DatetimeToStr(&value.datetime, buf);
            symbol->type = WQL_TYPE_STRING;
            symbol->value.string = Batch_Tcsdup(batch, buf);
            if (!symbol->value.string)
                return -1;
            else
                return 0;
        }
        case MI_STRING:
        {
            symbol->type = WQL_TYPE_STRING;
            symbol->value.string = Batch_Tcsdup(batch, value.string);
            if (!symbol->value.string)
                return -1;
            else
                return 0;
        }

        /* These types are not permitted in WQL WHERE clauses */
        case MI_REFERENCE:
        case MI_INSTANCE:
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
            return -1;
    }

    /* Not found */
    return -1;
}
