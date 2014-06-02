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
#include "instance.h"
#include "indent.h"
#include "field.h"
#include <pal/format.h>


MI_Result MI_CALL Instance_Print(
    const MI_Instance* self_,
    FILE* os,
    MI_Uint32 level,
    MI_Boolean showNulls,
    MI_Boolean isClass)
{
    Instance* self = Instance_GetSelf( self_ );
    const MI_ClassDecl* cd;
    MI_Uint32 i;
    const MI_Char *objectType;

    /* Check for null arguments */
    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    cd = self->classDecl;

    if (isClass)
        objectType = PAL_T("class");
    else
         objectType = PAL_T("instance");

    /* Print nameSpace and className */
    if (self->nameSpace)
    {
        Indent(os, level);
        Ftprintf(os, PAL_T("%T of %T:%T\n"), objectType, tcs(self->nameSpace), 
            tcs(cd->name));
    }
    else
    {
        Indent(os, level);
        Ftprintf(os, PAL_T("%T of %T\n"), objectType, tcs(cd->name));
    }

    Indent(os, level);
    Ftprintf(os, PAL_T("{\n"));
    level++;

    /* Print the properties */
    for (i = 0; i < cd->numProperties; i++)
    {
        const MI_PropertyDecl* pd = cd->properties[i];
        const Field* field = (Field*)((char*)self + pd->offset);

        if (showNulls || Field_GetExists(field, pd->type))
        {
            Indent(os, level);

            if (isClass)
            {
                const MI_Char *typeName = Type_NameOf(pd->type);
                if (typeName == NULL)
                    typeName = PAL_T("unknown");
                Ftprintf(os, PAL_T("[MI_%T] "), typeName);
            }

            if (pd->flags & MI_FLAG_KEY)
                Ftprintf(os, PAL_T("[Key] "));

            Ftprintf(os, PAL_T("%T="), tcs(pd->name));

            Field_Print(field, os, pd->type, level, MI_TRUE, isClass);

            if (pd->type == MI_INSTANCE || pd->type == MI_REFERENCE)
            {
                if (!field->instance.value)
                    Ftprintf(os, PAL_T("\n"));
            }
            else
                Ftprintf(os, PAL_T("\n"));
        }
    }

    level--;
    Indent(os, level);

    Ftprintf(os, PAL_T("}\n"));

    MI_RETURN(MI_RESULT_OK);
}
