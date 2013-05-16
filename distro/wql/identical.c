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
#include <base/strings.h>
#include <io/io.h>

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
            if (Zcmp(x->properties[i], y->properties[i]) != 0)
                return 0;
        }
    }

    /* Check classname */
    if (Zcmp(x->className, y->className) != 0)
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
                    if (Zcmp(sx->value.string, sy->value.string) != 0)
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
