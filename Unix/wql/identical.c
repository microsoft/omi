/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "wql.h"
#include <pal/strings.h>
#include <pal/format.h>

int WQL_Identical(const WQL* x, const WQL* y)
{
    size_t i;

    if (!x || !y)
        return 0;
    /* Check properties */
    {
        if (x->nproperties != y->nproperties)
            return 0;

        for (i = 0; i < x->nproperties; i++)
        {
            if (Tcscmp(x->properties[i], y->properties[i]) != 0)
                return 0;
        }
    }

    /* Check classname */
    if (Tcscmp(x->className, y->className) != 0)
        return 0;

    /* Check symbols */
    {
        if (x->nsymbols != y->nsymbols)
            return 0;

        for (i = 0; i < x->nsymbols; i++)
        {
            const WQL_Symbol* sx = &x->symbols[i];
            const WQL_Symbol* sy = &y->symbols[i];

            if (sx->type != sy->type)
                return 0;

            switch (sx->type)
            {
                case WQL_TYPE_IDENTIFIER:
                case WQL_TYPE_STRING:
                {
                    if (Tcscmp(sx->value.string, sy->value.string) != 0)
                        return 0;
                    break;
                }
                case WQL_TYPE_BOOLEAN:
                    if (sx->value.boolean != sy->value.boolean)
                        return 0;
                    break;
                case WQL_TYPE_INTEGER:
                    if (sx->value.integer != sy->value.integer)
                        return 0;
                    break;
                case WQL_TYPE_REAL:
                    if (sx->value.boolean != sy->value.boolean)
                        return 0;
                    break;
                default:
                    break;
            }
        }
    }

    /* Identical! */
    return 1;
}
