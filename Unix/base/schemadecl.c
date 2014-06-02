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

#include "schemadecl.h"
#include "naming.h"

static MI_Uint32 _Find(
    MI_FeatureDecl** data,
    MI_Uint32 size,
    const ZChar* name)
{
    MI_Uint32 code;
    MI_Uint32 i;

    /* Zero-length CIM names are illegal */
    if (*name == '\0')
        return (MI_Uint32)-1;

    /* Calculate hash code */
    code = Hash(name);

    /* Find the object */
    for (i = 0; i < size; i++)
    {
        const MI_FeatureDecl* p = data[i];
        if (p->code == code && Tcscasecmp(p->name, name) == 0)
            return i;
    }

    /* Not found */
    return (MI_Uint32)-1;
}

MI_ClassDecl* SchemaDecl_FindClassDecl(
    const MI_SchemaDecl* self,
    const ZChar* name)
{
    MI_Uint32 i;

    if (!self || !name)
        return NULL;
    
    i = _Find((MI_FeatureDecl**)self->classDecls, self->numClassDecls, name);
    return i == (MI_Uint32)-1 ? NULL : self->classDecls[i];
}

MI_MethodDecl* SchemaDecl_FindMethodDecl(
    const MI_ClassDecl* cd,
    const ZChar* name)
{
    MI_Uint32 i;

    if (!cd || !name)
        return NULL;
    
    i = _Find((MI_FeatureDecl**)cd->methods, cd->numMethods, name);
    return i == (MI_Uint32)-1 ? NULL : cd->methods[i];
}
