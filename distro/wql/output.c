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

#include "wql.h"
#include <base/buf.h>
#include <base/strings.h>
#include <io/io.h>

#define STRLIT(STR) STR, (sizeof(STR)-1)

static void _ZApp(Buf* out, const ZChar* s, size_t n)
{
    while (n--)
    {
        char c = (char)(*s++);
        Buf_App(out, &c, 1);
    }
}

static void _Indent(size_t nindent, Buf* out)
{
    size_t i;

    for (i = 0; i < nindent; i++)
        Buf_App(out, " ", 1);
}

int WQL_Define(const WQL* self, Buf* out, size_t nindent)
{
    char buf[128];
    int len;
    size_t i;

    if (!self)
        return -1;

    /* Print structure header */
    _Indent(nindent, out);
    Buf_App(out, STRLIT("static const WQL _wql =\n"));
    _Indent(nindent, out);
    Buf_App(out, STRLIT("{\n"));

    /* Print properties */
    {
        _Indent(nindent, out);
        Buf_App(out, STRLIT("    /* properties */\n"));
        _Indent(nindent, out);
        Buf_App(out, STRLIT("    {\n"));

        for (i = 0; i < self->nproperties; i++)
        {
            _Indent(nindent, out);
            Buf_App(out, STRLIT("        \""));

            _ZApp(out, self->properties[i], Zlen(self->properties[i]));
            Buf_App(out, STRLIT("\",\n"));
        }

        _Indent(nindent, out);
        Buf_App(out, STRLIT("    },\n"));

        _Indent(nindent, out);
        len = Snprintf(buf, sizeof(buf), "    %u,\n", (int)self->nproperties);
        Buf_App(out, buf, len);
    }

    /* Print class name */
    _Indent(nindent, out);
    Buf_App(out, STRLIT("    /* className */\n"));
    _Indent(nindent, out);
    Buf_App(out, STRLIT("    \""));
    _ZApp(out, self->className, Zlen(self->className));
    Buf_App(out, STRLIT("\",\n"));

    /* Print symbols */
    {
        _Indent(nindent, out);
        Buf_App(out, STRLIT("    /* symbols */\n"));
        _Indent(nindent, out);
        Buf_App(out, STRLIT("    {\n"));

        for (i = 0; i < self->nsymbols; i++)
        {
            const WQL_Symbol* sym = &self->symbols[i];

            _Indent(nindent, out);
            Buf_App(out, STRLIT("        { "));

            switch (sym->type)
            {
                case WQL_TYPE_OR:
                    Buf_App(out, STRLIT("WQL_TYPE_OR"));
                    break;
                case WQL_TYPE_AND:
                    Buf_App(out, STRLIT("WQL_TYPE_AND"));
                    break;
                case WQL_TYPE_NOT:
                    Buf_App(out, STRLIT("WQL_TYPE_NOT"));
                    break;
                case WQL_TYPE_EQ:
                    Buf_App(out, STRLIT("WQL_TYPE_EQ"));
                    break;
                case WQL_TYPE_NE:
                    Buf_App(out, STRLIT("WQL_TYPE_NE"));
                    break;
                case WQL_TYPE_LT:
                    Buf_App(out, STRLIT("WQL_TYPE_LT"));
                    break;
                case WQL_TYPE_LE:
                    Buf_App(out, STRLIT("WQL_TYPE_LE"));
                    break;
                case WQL_TYPE_GT:
                    Buf_App(out, STRLIT("WQL_TYPE_GT"));
                    break;
                case WQL_TYPE_GE:
                    Buf_App(out, STRLIT("WQL_TYPE_GE"));
                    break;
                case WQL_TYPE_IDENTIFIER:
                {
                    Buf_App(out, STRLIT("WQL_TYPE_IDENTIFIER, "));
                    Buf_App(out, STRLIT("WQL_VALUE_STRING(\""));
                    _ZApp(out, sym->value.string, Zlen(sym->value.string));
                    Buf_App(out, STRLIT("\")"));
                    break;
                }
                case WQL_TYPE_BOOLEAN:
                    Buf_App(out, STRLIT("WQL_TYPE_BOOLEAN, "));
                    Buf_App(out, STRLIT("WQL_VALUE_BOOLEAN("));
                    len = Snprintf(buf, sizeof(buf), "%u", sym->value.boolean);
                    Buf_App(out, buf, len);
                    Buf_App(out, STRLIT(")"));
                    break;
                case WQL_TYPE_INTEGER:
                    Buf_App(out, STRLIT("WQL_TYPE_INTEGER, "));
                    Buf_App(out, STRLIT("WQL_VALUE_INTEGER("));
                    len = Snprintf(buf, sizeof(buf), SINT64_FMT, 
                        sym->value.integer);
                    Buf_App(out, buf, len);
                    Buf_App(out, STRLIT(")"));
                    break;
                case WQL_TYPE_REAL:
                    Buf_App(out, STRLIT("WQL_TYPE_REAL, "));
                    Buf_App(out, STRLIT("WQL_VALUE_REAL("));
                    len = Snprintf(buf, sizeof(buf), "%lf", sym->value.real);
                    Buf_App(out, buf, len);
                    Buf_App(out, STRLIT(")"));
                    break;
                case WQL_TYPE_NULL:
                    Buf_App(out, STRLIT("WQL_TYPE_NULL"));
                    break;
                case WQL_TYPE_STRING:
                {
                    ZChar* p;
                    Buf_App(out, STRLIT("WQL_TYPE_STRING, "));
                    Buf_App(out, STRLIT("WQL_VALUE_STRING(\""));

                    for (p = sym->value.string; *p; p++)
                    {
                        char c = (char)*p;

                        switch (c)
                        {
                            case '"':
                            {
                                char c1 = '\\';
                                char c2 = '"';
                                Buf_App(out, &c1, 1);
                                Buf_App(out, &c2, 1);
                                break;
                            }
                            case '\n':
                            {
                                char c1 = '\\';
                                char c2 = 'n';
                                Buf_App(out, &c1, 1);
                                Buf_App(out, &c2, 1);
                                break;
                            }
                            case '\r':
                            {
                                char c1 = '\\';
                                char c2 = 'r';
                                Buf_App(out, &c1, 1);
                                Buf_App(out, &c2, 1);
                                break;
                            }
                            case '\f':
                            {
                                char c1 = '\\';
                                char c2 = 'f';
                                Buf_App(out, &c1, 1);
                                Buf_App(out, &c2, 1);
                                break;
                            }
                            case '\\':
                            {
                                char c1 = '\\';
                                char c2 = '\\';
                                Buf_App(out, &c1, 1);
                                Buf_App(out, &c2, 1);
                                break;
                            }
                            default:
                                Buf_App(out, &c, 1);
                        }
                    }
                    Buf_App(out, STRLIT("\")"));
                    break;
                }
                default:
                    return -1;
            }

            Buf_App(out, STRLIT(" },\n"));
        }

        _Indent(nindent, out);
        Buf_App(out, STRLIT("    },\n"));

        len = Snprintf(buf, sizeof(buf), "    %u,\n", (int)self->nsymbols);
        _Indent(nindent, out);
        Buf_App(out, buf, len);
    }

    /* Print structure trailer */
    _Indent(nindent, out);
    Buf_App(out, STRLIT("};\n"));

    /* Null terminate buffer */
    Buf_App(out, "\0", 1);

    return 0;
}

int WQL_Dump(const WQL* self, size_t nindent)
{
    Buf buf = BUF_INITIALIZER;

    if (WQL_Define(self, &buf, nindent) != 0)
        return -1;

    Zprintf(MI_T("%s"), scs((const char*)buf.data));
    Buf_Destroy(&buf);

    return 0;
}
