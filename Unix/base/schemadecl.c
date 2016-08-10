/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
