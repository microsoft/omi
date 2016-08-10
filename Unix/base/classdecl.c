/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <assert.h>
#include "classdecl.h"
#include "naming.h"
#include <pal/strings.h>

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

MI_MethodDecl* ClassDecl_FindMethodDecl(
    const MI_ClassDecl* self,
    const ZChar* name)
{
    MI_Uint32 i;

    if (!self || !name)
        return NULL;

    i = _Find((MI_FeatureDecl**)self->methods, self->numMethods, name);

    return i == (MI_Uint32)-1 ? NULL : self->methods[i];
}

MI_PropertyDecl* ClassDecl_FindPropertyDecl(
    const MI_ClassDecl* self,
    const ZChar* name)
{
    MI_Uint32 i;

    if (!self || !name)
        return NULL;

    i = _Find((MI_FeatureDecl**)self->properties, self->numProperties, name);

    return i == (MI_Uint32)-1 ? NULL : self->properties[i];
}
