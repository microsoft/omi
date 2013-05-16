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
#include <io/io.h>

MI_INLINE Instance* _SelfOf(const MI_Instance* instance)
{
    Instance* self = (Instance*)instance;

    if (self)
    {
        if (self->self)
            self = self->self;

        return self;
    }

    DEBUG_ASSERT(0);
    return NULL;
}

MI_Result MI_CALL Instance_Print(
    const MI_Instance* self_,
    FILE* os,
    MI_Uint32 level,
    MI_Boolean showNulls)
{
    Instance* self = _SelfOf(self_);
    const MI_ClassDecl* cd = self->classDecl;
    MI_Uint32 i;

    /* Check for null arguments */
    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Print nameSpace and className */
    if (self->nameSpace)
    {
        Indent(os, level);
        Fzprintf(os, ZT("instance of %Z:%Z\n"), zcs(self->nameSpace), 
            zcs(cd->name));
    }
    else
    {
        Indent(os, level);
        Fzprintf(os, ZT("instance of %Z\n"), zcs(cd->name));
    }

    Indent(os, level);
    Fzprintf(os, ZT("{\n"));
    level++;

    /* Print the properties */
    for (i = 0; i < cd->numProperties; i++)
    {
        const MI_PropertyDecl* pd = cd->properties[i];
        const Field* field = (Field*)((char*)self + pd->offset);

        if (showNulls || Field_GetExists(field, pd->type))
        {
            Indent(os, level);

            if (pd->flags & MI_FLAG_KEY)
                Fzprintf(os, ZT("[Key] "));

            Fzprintf(os, ZT("%Z="), zcs(pd->name));

            Field_Print(field, os, pd->type, level);

            if (pd->type == MI_INSTANCE || pd->type == MI_REFERENCE)
            {
                if (!field->instance.value)
                    Fzprintf(os, ZT("\n"));
            }
            else
                Fzprintf(os, ZT("\n"));
        }
    }

    level--;
    Indent(os, level);

    Fzprintf(os, ZT("}\n"));

    MI_RETURN(MI_RESULT_OK);
}
