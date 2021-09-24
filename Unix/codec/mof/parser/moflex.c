/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "mofcommon.h"
#include "mofyacc.h"
#include "utility.h"
#include "types.h"
#include "buffer.h"

/*=============================================================================
**
** Helper function mark last token start line and char position
**
=============================================================================*/
void _mof_buffer_marktokenstart(
    _Inout_ MOF_Buffer * buf)
{
    buf->llineNo = buf->lineNo;
    buf->lcharPosOfLine = buf->charPosOfLine;
}

void _mof_buffer_resettokenstart(
    _Inout_ MOF_Buffer * buf)
{
    buf->llineNo = 0;
    buf->lcharPosOfLine = 0;
}

/*=============================================================================
**
** Helper function, get escaped char
**
=============================================================================*/
int _mof_getescapedchar(int c, _Out_ char * ec)
{
    switch (c)
    {
        case 'r':
            *ec = '\r';
            break;
        case 'n':
            *ec = '\n';
            break;
        case 't':
            *ec = '\t';
            break;
        case 'f':
            *ec = '\f';
            break;
        case 'b':
            *ec = '\b';
            break;
        case '\"':
            *ec = '"';
            break;
        case '\'':
            *ec = '\'';
            break;
        case '\\':
            *ec = '\\';
            break;
        default:
            *ec = 0;
            return -1;
    }
    return 0;
}

/*=============================================================================
**
** Helper function, gets invalid token string for creating error instance
**
=============================================================================*/
MI_Char* _mof_gettokenstring(
    _In_ MOF_State *state,
    _In_ MOF_StringLen *r,
    _In_ MI_Char c)
{
    MI_Uint32 len = MI_COUNT(state->buffer) - 2; /*1 for c, 1 for null terminator*/
    MOF_Encoding e = {0};
    MI_Uint32 i = 0;
    e.u = state->buf.e.u;
    e.t = (e.u) ? UNI : ANSI;
    if (c) state->buffer[i++] = c;
    while (i < len && i < r->len)
    {
        state->buffer[i++] = (MI_Char)mof_getchar(e, r->str.data);
        r->str.data = mof_nextcharofbuf(e.u, r->str.data);
    }
    state->buffer[i] = 0;
    return state->buffer;
}


/*=============================================================================
**
** Get identifier value
** Ignore the localization string for now
=============================================================================*/
int mof_getidentifiervalue(_Inout_ MOF_State * state, _Inout_ MOF_StringLen *r)
{
    size_t len = 0;
    if (state->buf.e.u)
    {
        len = r->len;
    }
    else
    {
        char * str = (char *)Batch_Get(state->batch, r->len + 1);
        if (!str)
        {
            yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
            return -1;
        }
        memcpy(str, r->str.data, r->len);
        str[r->len] = 0;
        r->str.data = str;
        len = r->len;
    }
    state->ystate.moflval.string = (MI_Char*)Batch_Get(state->batch, (len + 1) * sizeof(MI_Char));
    if (!state->ystate.moflval.string)
    {
        yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
        return -1;
    }
    if (state->buf.e.u)
    {
        memcpy(state->ystate.moflval.string, r->str.str, sizeof(MI_Char)* len);
    }
    else
    {
        memcpy(state->ystate.moflval.string, r->str.str, sizeof(MI_Char) * len);
    }
    state->ystate.moflval.string[len] = L'\0';

#if 0
    if (state->buf.u)
    {
        wchar_t * wstr = (wchar_t *)Batch_GetClear(state->batch, (r->len + 1)*sizeof(wchar_t));
        if (!wstr)
        {
            yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
            return -1;
        }
        memcpy(wstr, r->str.data, (r->len)*sizeof(wchar_t));
        r->str.data = wstr;
        // Ignore the locale for now
        len = wcstombs(NULL, r->str.wstr, 0);
    }
    else
    {
        len = r->len;
    }
    state->ystate.moflval.string = (MI_Char*)Batch_Get(state->batch, (len + 1) * sizeof(MI_Char));
    if (!state->ystate.moflval.string)
    {
        yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
        return -1;
    }
    if (state->buf.u)
    {
        wcstombs(state->ystate.moflval.string, r->str.wstr, len);
    }
    else
    {
        memcpy(state->ystate.moflval.string, r->str.str, sizeof(MI_Char)* len);
    }
    state->ystate.moflval.string[len] = '\0';
#endif    
    return 0;
}


/*=============================================================================
**
** Get keyword token or identifier token
**
=============================================================================*/
int mof_getidentifier(_Inout_ MOF_State * state, _Inout_ MOF_StringLen *r)
{
    const MOF_Token * ptoken = (state->buf.e.u) ? _cwtokens : _catokens;
    MI_Boolean first = MI_TRUE;
    mof_getcode(state->buf.e.u, r);

    while (ptoken->str.data != NULL)
    {
        if (ptoken->code == r->code)
        {
            if (mof_ncasecmp(state->buf.e.u, ptoken->str.data, r->str.data, r->len) == 0)
            {
                int token = ptoken->token;
                if (token == TOK_BOOLEAN_VALUE)
                {
                    state->ystate.moflval.boolean = first;
                }
                return token;
            }
        }
        first = MI_FALSE;
        ptoken ++;
    }

    /* Cannot find keyword token, it is an identifier */
    {
        int ret = mof_getidentifiervalue(state, r);
        if (ret == 0) return TOK_IDENT;
        else return ret;
    }
}


/*=============================================================================
**
** Get #pragma token
**
=============================================================================*/
int mof_getpragma(_Inout_ MOF_State * state, _Inout_ MOF_StringLen *r)
{
    const MOF_Token * ptoken = (state->buf.e.u) ? &_cwPragmaToken : &_caPragmaToken;
    mof_getcode(state->buf.e.u, r);

    if (ptoken->code == r->code)
    {
        if (mof_ncasecmp(state->buf.e.u, ptoken->str.data, r->str.data, r->len) == 0)
        {
            return ptoken->token;
        }
    }
    yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INVALID_TOKEN, "",
        _mof_gettokenstring(state, r, (MI_Char)'#'));
    return TOK_ERROR;
}

/*=============================================================================
**
** Append char to buffer
**
=============================================================================*/
int mof_bufferappend(MOF_State *state, Buffer* self, const void* data)
{
    return (state->buf.e.u) ?
        Buffer_Append(state, self, data, sizeof(wchar_t)) : 
        Buffer_Append(state, self, data, sizeof(char));
}


/*=============================================================================
**
** Parse literal string
**
=============================================================================*/
int mof_parseliteralstring(_Inout_ MOF_State * state)
{
    Buffer buf = BUFFER_INITIALIZER;
    MOF_Buffer * mb = &(state->buf);
    wchar_t nullterm = L'\0';
    size_t n = 0;
    void * bufToAppend;
    char chr;
    wchar_t wchr;

    _mof_buffer_marktokenstart(mb);

    /* Skip " character */
    mof_nextchar(mb);

    /* Scan until the closing " is found */
    for (;;)
    {
        if (mof_eof(mb) || mof_isdoublequotes(mb->e, mb->cur))
            break;

        bufToAppend = mb->cur;

        /* if backslash, get next character */
        if (mof_isbackslash(mb->e, mb->cur))
        {
            int c = mof_nextcharn(mb, &n);
            char ec;
            unsigned long escapedchar;
            int r;
            if (mof_eof(mb))
                break;

            /* Parse escaped HEX char \xXXXX */
            if (c == 'x' || c == 'X')
            {
                int len = 0;
                MI_Boolean incompletechar = MI_FALSE;
                char hexbuf[5 * sizeof(wchar_t)] = {0};
                void *hexdata = hexbuf;
                while(mof_neof(mb) && (len < 4))
                {
                    c = mof_nextchar(mb);
                    if (mof_isdoublequotes(mb->e, mb->cur))
                    {
                        incompletechar = MI_TRUE;
                        break;
                    }
                    hexdata = mof_setchar(mb->e.u, hexdata, c);
                    len ++;
                }
                if (incompletechar || (len != 4) || mof_eof(mb))
                {
                    yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INCOMPLETE_ESCAPED_CHAR16_VALUE,
                        "",
                        mb->llineNo,
                        mb->lcharPosOfLine);
                    return TOK_ERROR;
                }
                /* convert HEX string to integer */
                {
                    unsigned long chr = 0;
                    MI_Boolean res;
                    mof_setchar(mb->e.u, hexdata, 0);
                    res = mof_isvalidhexstring(state->buf.e.u, hexbuf, (size_t)len);
                    if (res == MI_TRUE)
                    {
                        res = mof_strtoul(state->buf.e.u,
                            hexbuf,
                            16,
                            NULL,
                            &chr);
                    }
                    if (MI_FALSE == res)
                    {
                        yyerrorf(state->errhandler, ID_ILLEGAL_HEX_CHARACTER, "", (MI_Char*)hexbuf);
                        return TOK_ERROR;
                    }
                    escapedchar = chr;
                }
            }
            else
            {
                /* Parse escaped char other than HEX char */
                r = _mof_getescapedchar(c, &ec);
                escapedchar = ec;
                if (r != 0)
                {
                    yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INVALID_ESCAPED_CHAR, "", c);
                    return TOK_ERROR;
                }
            }

            if (mb->e.u)
            {
                if (mb->e.t == UTF16BE || mb->e.t == UNIBE)
                {
                    /* Might not work on non-windows platform */
                    wchar_t w = (wchar_t)escapedchar;
                    wchr = (w << 8) + (w >> 8);
                }
                else
                {
                    wchr = (wchar_t)escapedchar;
                }
                bufToAppend = &wchr;
            }
            else
            {
                chr = (char)escapedchar;
                bufToAppend = &chr;
            }
        }

        /* Append character to buffer */
        if (mof_bufferappend(state, &buf, bufToAppend) != 0)
        {
            yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
            return TOK_ERROR;
        }
        mof_nextcharn(mb, &n);
    }
    if (mof_eof(mb))
    {
        yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INCOMPLETE_STRING_VALUE, "",
            mb->llineNo, mb->lcharPosOfLine);
        return TOK_ERROR;
    }

    /* Skip closing " character */
    mof_nextchar(mb);

    /* Append zero-terminator */
    if (mof_bufferappend(state, &buf, &nullterm) != 0)
    {
        yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
        return TOK_ERROR;
    }
    n++;

    /* Copy listeral string and return */
    {
        int ret;
        MOF_StringLen r;
        r.len = n;
        r.str.data = buf.data;
        if (mof_converttoUTF16LE(state, &r) != 0)
        {
            return TOK_ERROR;
        }
        ret = mof_getidentifiervalue(state, &r);
        if (ret == 0) return TOK_STRING_VALUE;
        else return ret;
    }
}

/*=============================================================================
**
** Return single char as TOKENs
**
=============================================================================*/
int mof_returnsinglechar(MOF_State *state, int c)
{
    mof_nextchar(&(state->buf));
    return c;
}

/*=============================================================================
**
** Parse char16 value, following are the supported RegularExpression(s)
**
**     EscapedChar     \'\\[rntfb\"\'\\]\'
**     SimpleChar      \'[^\']\'
**     HexChar         \'\\[xX][A-Fa-f0-9]+\'
**
=============================================================================*/
int mof_getChar16(MOF_State * state)
{
    MOF_Buffer * mb = &(state->buf);
    int c;
    int firstc = mof_nextchar(mb);
    _mof_buffer_marktokenstart(mb);
    switch(firstc)
    {
        case '\'': /* Double quote '' is invalid */
            {
                yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INVALID_CHAR16_VALUE, "", MI_T("''"));
                return TOK_ERROR;
            }
            break;
        case '\\': /* Escaped char16 value */
        {
            int secondc;
            MOF_StringLen r = {{0}};
            c = mof_nextchar(mb);
            r.str.data = mb->cur;
            while(c != '\'' && mof_neof(mb))
            {
                c = mof_nextchar(mb);
            }
            r.len = mof_offset(mb->e.u, r.str.data, mb->cur);
            if (mof_eof(mb))
            {
                yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INCOMPLETE_ESCAPED_CHAR16_VALUE,
                    "",
                    mb->llineNo,
                    mb->lcharPosOfLine);
                return TOK_ERROR;
            }
            if (mof_converttoUTF16LE(state, &r) != 0)
            {
                return TOK_ERROR;
            }

            /* skip closing quote */
            mof_nextchar(mb);

            secondc = mof_getchar(mb->e, r.str.data);
            if (secondc == 'x' ||secondc == 'X') // hex char
            {
                if (r.len > 5)
                {
                    yyerrorf(state->errhandler, ID_ILLEGAL_HEX_CHARACTER, "",
                        _mof_gettokenstring(state, &r, 0));
                    return TOK_ERROR;
                }
                /* convert HEX string to integer */
                {
                    wchar_t ew = L'\'';
                    char ea = '\'';
                    unsigned long chr = 0;
                    void * hexdata = mof_nextcharofbuf(mb->e.u, r.str.data);
                    MI_Boolean res = mof_isvalidhexstring(state->buf.e.u, hexdata, r.len - 1);
                    if (res == MI_TRUE)
                    {
                        res = mof_strtoul(state->buf.e.u,
                            hexdata,
                            16,
                            mb->e.u ? (void*)&ew : (void*)&ea,
                            &chr);
                    }
                    if (!res)
                    {
                        yyerrorf(state->errhandler, ID_ILLEGAL_HEX_CHARACTER, "",
                            _mof_gettokenstring(state, &r, 0));
                        return TOK_ERROR;
                    }
                    state->ystate.moflval.character = (MI_Char16) chr;
                }
                return TOK_CHAR_VALUE;
            }
            else
            {
                if (r.len != 1)
                {
                    yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INVALID_ESCAPED_CHAR16_VALUE,
                        "",
                       _mof_gettokenstring(state, &r, 0),
                       r.len);
                    return TOK_ERROR;
                }
                c = mof_getchar(mb->e, r.str.data);
                {
                    char ec;
                    int r = _mof_getescapedchar(c, &ec);
                    if (r == 0)
                    {
                        state->ystate.moflval.character = (MI_Char16)ec;
                    }
                    else
                    {
                        yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INVALID_ESCAPED_CHAR, "", c);
                        return TOK_ERROR;
                    }
                }
            }
            return TOK_CHAR_VALUE;
        }
        break;
        default:
        {
            MI_Char buf[3] = {0};
            MI_Boolean invalid = MI_FALSE;
            buf[0] = (MI_Char)mof_getchar(mb->e, mb->cur);
            c = mof_nextchar(mb);
            if(mof_eof(mb))
            {
                invalid = MI_TRUE;
                buf[1] = 0;
            }
            else if (c != '\'')
            {
                invalid = MI_TRUE;
                c = mof_nextchar(mb);
                buf[1] = (MI_Char)c;
                buf[2] = 0;
            }

            if (invalid)
            {
                yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INVALID_CHAR16_VALUE, "",
                    buf);
                return TOK_ERROR;
            }

            /* valid Char16 value, skip closing quote */
            mof_nextchar(mb);
            state->ystate.moflval.character = (MI_Char16)firstc;
            return TOK_CHAR_VALUE;
        }
        break;
    }
}


/*=============================================================================
**
** Define regular expression & type for supported number(s)
**
=============================================================================*/

typedef enum _NUMBER_TYPE
{
    REAL,
    HEX,
    DECIMAL,
    OCTAL,
    BINARY
}NUMBER_TYPE;

static MOF_StringLen _canumberpattern[] =
{
    {{"[0-9]*.[0-9]+([eE][+-]?[0-9]+"}, 31, REAL},
    {{"0[xX][A-Fa-f0-9]+"}, 17, HEX},
    {{"[1-9][0-9]*"}, 11, DECIMAL},
    {{"0"}, 1, DECIMAL},
    {{"0[0-7]+"}, 7, OCTAL},
    {{"[+-]?[01]+[Bb]"}, 14, BINARY},
    {{0}, 0, 0},
};

static MOF_StringLen _cwnumberpattern[] =
{
    {{L"[0-9]*.[0-9]+([eE][+-]?[0-9]+"}, 31, REAL},
    {{L"0[xX][A-Fa-f0-9]+"}, 17, HEX},
    {{L"[1-9][0-9]*"}, 11, DECIMAL},
    {{L"0"}, 1, DECIMAL},
    {{L"0[0-7]+"}, 7, OCTAL},
    {{L"[+-]?[01]+[Bb]"}, 14, BINARY},
    {{0}, 0, 0},
};

/*=============================================================================
**
** Parse Number value, following are the supported RegularExpression(s)
**
**    RealValue       [+-]?[0-9]*.[0-9]+([eE][+-]?[0-9]+)?
**    HexValue        [+-]?0[xX][A-Fa-f0-9]+
**    DecimalValue    [+-]?[1-9][0-9]*
**                    [+-]?0
**    OctalValue      [+-]?0[0-7]+
**    BinaryValue     [+-]?[01]+[Bb]
**
=============================================================================*/
int mof_getnumber(MOF_State * state, MI_Boolean sign)
{
    MOF_Buffer * mb = &(state->buf);
    int token = TOK_ERROR;
    int c = mof_getchar(mb->e, mb->cur);
    MI_Boolean isnumber = MI_TRUE;
    void * start = mb->cur;
    while (isnumber && mof_neof(mb))
    {
        switch(c)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
        case '+':
        case '-':
        case 'x':
        case 'X':
            c = mof_nextchar(mb);
            break;
        default:
            if (('a' <= c && c <= 'f') || ('A' <= c && c <= 'F'))
            {
                c = mof_nextchar(mb);
            }
            else
            {
                isnumber = MI_FALSE;
            }
            break;
        }
    }
    {
        size_t length = mof_offset(mb->e.u, start, mb->cur);
        if (length == 0)
        {
             yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INVALID_NUMBER_VALUE, "",
                MI_T("empty number string"));
            return token;
        }
        else
        {
            MOF_StringLen data;
            MOF_StringLen * ps = (mb->e.u) ? _cwnumberpattern : _canumberpattern;
            data.str.data = start;
            data.len = length;
            while (ps->str.data)
            {
                MOF_Encoding em;
                em.u = mb->e.u;
                em.t = (em.u) ? UNI :ANSI;
                if (mof_converttoUTF16LE(state, &data) != 0)
                {
                    return TOK_ERROR;
                }
                if (mof_match(em, &data, ps))
                {
                    if (!sign)
                    {
                        data.str.data = mof_getprevcharpos(mb->e.u, data.str.data);
                        data.len += 1;
                    }
                    mof_getidentifiervalue(state, &data);
                    break;
                }
                ps ++;
            }
            if (!ps->str.data)
            {
                yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INVALID_NUMBER_VALUE, "",
                    _mof_gettokenstring(state, &data, 0));
                return token;
            }
            else
            {
                switch(ps->code)
                {
                case REAL:
                    {
                        token = TOK_REAL_VALUE;
                        state->ystate.moflval.real = mof_strtod(sizeof(MI_Char) == sizeof(wchar_t), state->ystate.moflval.string);//memory is from batch
                    }
                    break;
                case DECIMAL:
                    {
                        token = TOK_INTEGER_VALUE;
                        errno = 0;
                        if (!sign)
                            state->ystate.moflval.integer = (MI_Sint64)mof_strtoll(sizeof(MI_Char) == sizeof(wchar_t), state->ystate.moflval.string, NULL, 10);
                        else
                            state->ystate.moflval.integer = (MI_Sint64)mof_strtoull(sizeof(MI_Char) == sizeof(wchar_t), state->ystate.moflval.string, NULL, 10);

                        if (errno == ERANGE)
                        {
                            yyerrorf(state->errhandler, ID_INTEGER_OVERFLOW, "integer overflow");
                            return TOK_ERROR;
                        }
                    }
                    break;
                case OCTAL:
                    {
                        token = TOK_INTEGER_VALUE;
                        errno = 0;
                        if (sign)
                            state->ystate.moflval.integer = (MI_Sint64)mof_strtoll(sizeof(MI_Char) == sizeof(wchar_t), state->ystate.moflval.string, NULL, 8);
                        else
                            state->ystate.moflval.integer = (MI_Sint64)mof_strtoull(sizeof(MI_Char) == sizeof(wchar_t), state->ystate.moflval.string, NULL, 8);
    
                        if (errno == ERANGE)
                        {
                            yyerrorf(state->errhandler, ID_INTEGER_OVERFLOW, "integer overflow");
                            return TOK_ERROR;
                        }
                    }
                    break;
                case HEX:
                    {
                        token = TOK_INTEGER_VALUE;
                        errno = 0;
                        if (sign)
                            state->ystate.moflval.integer = (MI_Sint64)mof_strtoll(sizeof(MI_Char) == sizeof(wchar_t), state->ystate.moflval.string, NULL, 16);
                        else
                            state->ystate.moflval.integer = (MI_Sint64)mof_strtoull(sizeof(MI_Char) == sizeof(wchar_t), state->ystate.moflval.string, NULL, 16);
    
                        if (errno == ERANGE)
                        {
                            yyerrorf(state->errhandler, ID_INTEGER_OVERFLOW, "integer overflow");
                            return TOK_ERROR;
                        }
                    }
                    break;
                case BINARY:
                    {
                        wchar_t* end;
                        token = TOK_INTEGER_VALUE;
                        if (sign)
                            state->ystate.moflval.integer = (MI_Sint64)mof_strtoll(sizeof(MI_Char) == sizeof(wchar_t), state->ystate.moflval.string, (void**)&end, 2);
                        else
                            state->ystate.moflval.integer = (MI_Sint64)mof_strtoull(sizeof(MI_Char) == sizeof(wchar_t), state->ystate.moflval.string, (void**)&end, 2);

                        if (*end != L'B' && *end != L'b')
                        {
                            yyerrorf(state->errhandler, ID_ILLEGAL_BINARY_LITERAL, "");
                            return TOK_ERROR;
                        }
                        if (errno == ERANGE)
                        {
                            yyerrorf(state->errhandler, ID_INTEGER_OVERFLOW, "integer overflow");
                            return TOK_ERROR;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
    return token;
}

/*
**==============================================================================
**
** Check whether current char is a TOKEN
** Chars can be token such as '=', etc..
**
**==============================================================================
*/
int mof_getsinglechartoken(MOF_State * state)
{
    MOF_Buffer * mb = &(state->buf);
    int c = mof_getchar(mb->e, mb->cur);
    if (0 <= c && c < 256)
    {
        if ((scTable[(unsigned char)c] & TOKEN_SINGLE_CHAR_FLAG) == TOKEN_SINGLE_CHAR_FLAG)
            return mof_returnsinglechar(state, c);
    }
    return -1;
}

/*
**==============================================================================
**
** Skip one comment
**
**==============================================================================
*/
int mof_skipcomment(MOF_State *state)
{
    MOF_Buffer * mb = &(state->buf);
    int c = mof_nextchar(mb);
    _mof_buffer_marktokenstart(mb);

    if (c == '*')
    {
        /* Skip C-style comments. */
        int prevc = 0;
        c = mof_nextchar(mb);
        while(mof_neof(mb))
        {
            /* Scan end of comment */
            if (prevc == '*' && c == '/')
                break;

            prevc = c;
            c = mof_nextchar(mb);
        }
        if (mof_eof(mb))
        {
            yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INVALID_COMMENT, "",
                mb->llineNo, mb->lcharPosOfLine);
            return TOK_ERROR;
        }
    }
    else if (c == '/')
    {
        int c;
        c = mof_nextchar(mb);

        /* Ignore all characters on current line */
        while (mof_neof(mb))
        {
            if (c == '\n')
            {
                break;
            }
            c = mof_nextchar(mb);
        }
        if (mof_eof(mb))
        {
            return 0;
        }
    }
    else
    {
        MI_Char buf[3];
        buf[0] = (MI_Char)'/';
        buf[1] = (MI_Char)c;
        buf[2] = 0;
        yyerrorf(state->errhandler, ID_SYNTAX_ERROR, "", buf);
        return TOK_ERROR;
    }
    mof_nextchar(mb);
    return 0;
}

/*
**==============================================================================
**
** Skip all space and comments until end of the mof OR a valid token
** return value:
**      1       - skipped all space and comment & buffer is not at end
**      0       - buf is at end
**      ...     - invalid token
**
**==============================================================================
*/
int mofskipspace_comment(MOF_State * state)
{
    MOF_Buffer * mb = &(state->buf);
    while (1)
    {
        void * p = mb->cur;

        /* Skip whitespace, !check whitespace char! */
        while (mof_neof(mb) && mof_isspace(mb->e, mb->cur))
        {
            mof_nextchar(mb);
        }

        /* Return on end-of-file */
        if (mof_eof(mb))
        {
            return 0;
        }

        /* Recognize and skip comments */
        if (mof_getchar(mb->e, mb->cur) == '/')
        {
            int r = mof_skipcomment(state);
            if (r != 0) return r;
        }

        /* Return on end-of-file */
        if (mof_eof(mb))
        {
            return 0;
        }

        /* No space char & no comments */
        if (p == mb->cur)
            break;
    }
    return 1;
}

/*
**==============================================================================
**
** Lexical Parser generating TOKEN from buffer
**
**==============================================================================
*/
int moflex(MOF_State * state)
{
    MOF_Buffer * mb = &(state->buf);
    int r;
    int c;

    /* Skip all continuous spaces and comments */
    r = mofskipspace_comment(state);
    if (r == 0)
    {
        int cont = 0;
        while(!cont)
        {
            int rc;
            /* End of buffer, try to popup include file */
            int cif = closeIncludeFile(state);
            if (cif == 1)
            {
                /* Poped up valid include file */
                rc = mofskipspace_comment(state);
                if (rc == 0)
                {
                    /*Continue to pop up include file*/
                }
                else if (rc != 1)
                {
                    /*Failed*/
                    return rc;
                }
                else
                {
                    /*Skipped comment and buffer is not end*/
                    cont = 1;
                }
            }
            else
            {
                /* No included file */
                return cif;
            }
        }
    }
    else if (r != 1)
        return r;

    /* Parse identifier */
    if (mof_isalpha(mb->e, mb->cur) || mof_isunderscore(mb->e, mb->cur))
    {
        /* [A-Za-z_][A-Za-z_0-9]* */
        MOF_StringLen r;
        r.str.data = mb->cur;
        while (mof_isalnum(mb->e, mb->cur) || mof_isunderscore(mb->e, mb->cur))
        {
            mof_nextchar(mb);
        }
        r.len = mof_offset(mb->e.u, r.str.data, mb->cur);
        if (mof_converttoUTF16LE(state, &r) != 0)
        {
            return TOK_ERROR;
        }
        return mof_getidentifier(state, &r);
    }

    /* Parse literal string */
    if (mof_isdoublequotes(mb->e, mb->cur)) {
        return mof_parseliteralstring(state);
    }

    /* Parse single char as token */
    r = mof_getsinglechartoken(state);
    if (r != -1)
        return r;

    c = mof_getchar(mb->e, mb->cur);

    /* Parse #pragma token */
    if (c == '#')
    {
        MOF_StringLen r;
        r.str.data = mb->cur;
        // Skip the '#'
        mof_nextchar(mb);
        while (mof_isalnum(mb->e, mb->cur) || mof_isunderscore(mb->e, mb->cur))
            mof_nextchar(mb);

        r.len = mof_offset(mb->e.u, r.str.data, mb->cur);
        if (mof_converttoUTF16LE(state, &r) != 0)
        {
            return TOK_ERROR;
        }
        return mof_getpragma(state, &r);
    }

    /* Parse alias identifier */
    if (c == '$')
    {
        mof_nextchar(mb);

        /* Parse alias identifier: $[A-Za-z_][A-Za-z_0-9]* */
        if (mof_isalpha(mb->e, mb->cur) || mof_isunderscore(mb->e, mb->cur))
        {
            int ret;
            MOF_StringLen r;
            r.str.data = mb->cur;

            while (mof_isalnum(mb->e, mb->cur) || mof_isunderscore(mb->e, mb->cur))
                mof_nextchar(mb);

            r.len = mof_offset(mb->e.u, r.str.data, mb->cur);
            if (mof_converttoUTF16LE(state, &r) != 0)
            {
                return TOK_ERROR;
            }
            ret = mof_getidentifiervalue(state, &r);
            if (ret == 0) return TOK_ALIAS_IDENTIFIER;
            else return ret;
        }
        else
        {
            MI_Char buf[6];
            buf[0] = (MI_Char)'$';
            buf[1] = (MI_Char)mof_getchar(mb->e, mb->cur);
            buf[2] = buf[3] = buf[4] = (MI_Char)'.';
            buf[5] = 0;
            yyerrorf(state->errhandler, ID_SYNTAX_ERROR_INVALID_TOKEN, "", buf);
            return TOK_ERROR;
        }
    }

    /* Parse Char16 or Number */
    switch(c)
    {
    case '\'':
        {
            return mof_getChar16(state);
        }
        break;
    case '+':
        {
            mof_nextchar(mb);
            return mof_getnumber(state, MI_TRUE);
        }
        break;
    case '-':
        {
            mof_nextchar(mb);
            return mof_getnumber(state, MI_FALSE);
        }
        break;
    default:
        {
            return mof_getnumber(state, MI_TRUE);
        }
        break;
    }
}
