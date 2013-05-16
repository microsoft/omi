#include "wql.h"

#ifndef _MSC_VER
#include <pthread.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <base/strings.h>
#include <base/classdecl.h>
#include <base/helpers.h>
#include <io/io.h>
#include "wqlyacc.h"
#include "state.h"

extern int wqlparse();

WQL_State wqlstate;

#ifndef _MSC_VER
static pthread_mutex_t _mutex = PTHREAD_MUTEX_INITIALIZER;
static void _Lock() { pthread_mutex_lock(&_mutex); }
static void _Unlock() { pthread_mutex_unlock(&_mutex); }
#endif

void* wqlmalloc(size_t size)
{
    return Batch_Get(wqlstate.wql->batch, size);
}

MI_Char* wqlstrdup(const MI_Char * str)
{
    return Batch_Zdup(wqlstate.wql->batch, str);
}

WQL* WQL_Parse(const MI_Char* text, Batch* batch)
{
    WQL* self = NULL;
    int deleteBatch;

    /* Acquire mutex to synchronize access to global Lex/Yacc state */
    _Lock();

    /* Create batch if none */
    if (!batch)
    {
        batch = Batch_New(64);

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

    /* Initialize WQL object */
    self->batch = batch;
    self->deleteBatch = deleteBatch;
    self->text = Batch_Zdup(batch, text);

    /* Initialize global parser state */
    memset(&wqlstate, 0, sizeof(WQL_State));
    wqlstate.text = self->text;
    wqlstate.size = (int)Zlen(text);
    wqlstate.wql = self;
    wqlstate.ptr = text;

    /* Parse the text */
    wqlparse();

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
        batch = Batch_New(64);

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
            result->properties[i] = Batch_Zdup(batch, self->properties[i]);

            if (!result->properties[i])
                goto failed;
        }

        result->nproperties = self->nproperties;
    }

    /* Clone classname */
    if (self->className)
    {
        result->className = Batch_Zdup(batch, self->className);

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
                        Batch_Zdup(batch, self->symbols[i].value.string);

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
        result->text = Batch_Zdup(batch, self->text);

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
    const MI_Char* propertyName)
{
    size_t i;

    if (wql->nproperties == 0)
        return MI_TRUE;

    for (i = 0; i < wql->nproperties; i++)
    {
        if (Zcasecmp(propertyName, wql->properties[i]) == 0)
            return MI_TRUE;
    }

    /* Not found! */
    return MI_FALSE;
}

int _ValidateLookup(
    const MI_Char* name,
    WQL_Symbol* symbol,
    Batch* batch,
    void* data)
{
    const MI_ClassDecl* cd = (const MI_ClassDecl*)data;
    const MI_PropertyDecl* pd;

    MI_UNUSED(batch);

    /* Check for null parameters */
    if (!name || !symbol || !data)
        return -1;

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
        return -1;

    return 0;
}

//-----------------------------------------------------------------------------
// @brief   See if a string matches a template string
//
// @param   [in] s1 - one string
// @param   [in] s1 - another string
//
// @returns 0 for a match, > 0 for s1 > s2; < 0 for s1 < s2
//-----------------------------------------------------------------------------
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
            return Zcasecmp(s1->value.string, s2->value.string);
        }
        default:
            return -1;
    }
}

//-----------------------------------------------------------------------------
// @brief   See if a string matches a template string
//
// @param   [in] s1 - the string to test
// @param   [in] s2 - the template string.  This string contains characters
//                    and the '_' wildcdard character.  The match is
//                    case-insensitive using the "C" locale.  Both '\0'
//                    and unescaped '%' are considered end characters for the
//                    template string.
//
// @returns 0 for a match, 1 for a mismatch
//-----------------------------------------------------------------------------
static int _StrCaseCmpLike(const char* Str, const char* Templ)
{
    int Ch;                             // a character from the template string
    int Ch2;                            // a character from the source string

    while (*Str != '\0' && *Templ != '\0' && *Templ != '%')
    {
        Ch2 = toupper((int)(unsigned char)*Str);
        Ch = toupper((int)(unsigned char)*Templ);
        if (Ch == '\\')
        {                               // '\' escapes the next character, if not a NUL
            Templ++;
            Ch = toupper((int)(unsigned char)*Templ);
            if (Ch == '\0')
            {
                return 0;               // '\' at end: error--no match
            }
        }

        // if the template and source don't match and if the template wasn't a wildcard
        // there was no match
        if (Ch2 != Ch && Ch != '_')
        {
            return 1;
        }

        // advance
        Str++;
        Templ++;
    }

    // if at the end of either string, done
    // if at the end of both strings, there was a match.  If at
    // the end of the source and at a wildcard in the template, there
    // was also a match.
    if ((*Str == '\0' && *Templ == '\0') || *Templ == '%')
    {
        return 0;
    }

    // if at the end of one string only, there was no match
    return 1;
}

//-----------------------------------------------------------------------------
// @brief   See if a string matches a template string
//
// @param   [in] str - the string to test
// @param   [in] templ - the template string.  This string contains characters
//                       and the '_'and '%" wildcdard characters.  The template
//                       string is broken into sections bracketed by '%" characters
//                       and a match is found if the sections between '%" characters
//                       occur, nonoverlapping, in order in the source string.
//                       Each section is compared using case-insensitive comparison
//                       using the "C" locale and the single-character wildcard '-'.
//
// @returns 0 for a match, 1 for a mismatch
//-----------------------------------------------------------------------------
static int _CompareLike(const WQL_Symbol* s1, const WQL_Symbol* s2)
{
    char* Str;                         // the source string
    char* Templ;                       // the template string
    const char* SectBeg;               // ptr. to the beginning of a subsection
    const char* SectEnd;               // ptr. to the end of a subsection
    int Ch;                            // a character from the template string

    if (s1->type != WQL_TYPE_STRING)
    {
        return -1;
    }

    Str = s1->value.string;
    Templ = s2->value.string;

    // find the first wildcard char.
    SectBeg = strchr(Templ, '%');

    // if no wildcard characters, the string matches if the part from here to the end matches
    if (SectBeg == NULL)
    {
        return _StrCaseCmpLike(Str, Templ);
    }

    // if there is a string before the first '%", be sure the source string matches it
    if (SectBeg != Templ)
    {
        if (_StrCaseCmpLike(Str, Templ) != 0)
        {
            return 1;
        }
    }

    // loop through segments, the items between wildcard characters
    while (*Str != '\0' && *SectBeg != '\0')
    {
        SectBeg++;

        // handle '%' and '_' at the beginning of the segment
        for ( ; *SectBeg == '%' || *SectBeg == '_'; SectBeg++)
        {
            // if '%" at the end of the source string, there is a match
            // for '_' at the end, there is no match
            if (*Str == '\0')
            {
                return *SectBeg == '%' ? 0 : 1;
            }

            // advance past one source string char. for '_'
            if (*SectBeg == '_')
            {
                Str++;
            }
        }

        // if at the end of the template string, this '%" matches the
        // remainder of the string.
        if (*SectBeg == '\0')
        {
            return 0;
        }

        // find the next '%'
        SectEnd = strchr(SectBeg, '%');

        // if no more '%', the string matches if the part from here to the end matches
        if (SectEnd == NULL)
        {
            SectEnd = SectBeg + strlen(SectBeg);
        }

        // find the first matching character in any potential matching substring
        Ch = toupper((int)(unsigned char)*SectBeg);
        for ( ; ; )
        {
            while (toupper((int)(unsigned char)*Str) != Ch)
            {
                // if we ran out of source, no match
                if (*Str == '\0')
                {
                    return 1;
                }
                Str++;
            }

            // see if the substring whose first character matched the template matches in its entirety
            if (_StrCaseCmpLike(Str, SectBeg) == 0)
            {
                break;
            }

            // if no match, move to the next character in the source string
            Str++;
        }

        // there was a matching substring; move to next segment of the source and template strings
        Str += SectEnd - SectBeg;
        SectBeg = SectEnd;
    }

    // if we got here, see if we got to the end of both strings
    // if at the end of both strings, there was a match
    if (*Str == '\0' && (*SectBeg == '\0' || (*SectBeg == '%' && *(SectBeg + 1) == '\0')))
    {
        return 0;
    }

    // if at the end of only one string, there was no match
    return 1;
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
                        /* Reject type mismatch */
                        if (s1.type != s2.type)
                            return -1;

                        if (type == WQL_TYPE_LIKE)
                        {
                            r = _CompareLike(&s1, &s2);
                        }
                        else
                        {
                            r = _Compare(&s1, &s2);
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

                if ((*lookup)(sym->value.string, &tmp, wql->batch, data) != 0)
                    return -1;

                if (tmp.type != WQL_TYPE_BOOLEAN &&
                    tmp.type != WQL_TYPE_INTEGER &&
                    tmp.type != WQL_TYPE_REAL &&
                    tmp.type != WQL_TYPE_STRING &&
                    tmp.type != WQL_TYPE_NULL)
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
                symbols[nsymbols++] = *sym;
                break;
        }
    }

    /* There should be exactly 1 symbol left on stack */
    if (nsymbols != 1)
        return -1;

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
    const MI_Char* name,
    WQL_Symbol* symbol,
    Batch* batch,
    void* data)
{
    const MI_Instance* instance = (const MI_Instance*)data;
    MI_Result r;
    MI_Value value;
    MI_Type type;
    MI_Uint32 flags;

    /* Check for null parameters */
    if (!name || !symbol || !data)
        return -1;

    /* Lookup the property with this name */
    r = __MI_Instance_GetElement(instance, name, &value, &type, &flags, 0);

    /* Fail if not found */
    if (r != MI_RESULT_OK)
        return -1;

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
            MI_Char buf[26];
            DatetimeToStr(&value.datetime, buf);
            symbol->type = WQL_TYPE_STRING;
            symbol->value.string = Batch_Zdup(batch, buf);
            return 0;
        }
        case MI_STRING:
        {
            symbol->type = WQL_TYPE_STRING;
            symbol->value.string = Batch_Zdup(batch, value.string);
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
