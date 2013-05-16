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
#include "helpers.h"
#include "naming.h"
#include "types.h"
#include "schemadecl.h"
#include "alloc.h"
#include "field.h"
#include <stdio.h>
#include <wchar.h>

/*
**==============================================================================
**
** Local definitions
**
**==============================================================================
*/

/* Magic number of InstanceHeader */
static MI_Uint32 _MAGIC = 0xB26AEA60;

/* Number of default pages for a self-owned batch object */
static MI_Uint32 _NUM_PAGES = 8;

/* The minimum number of reserved properties for a dynamic instance */
static MI_Uint32 _CAPACITY = 32;

/* Find capacity (lesser of _CAPACITY or x rounded to power of 2) */
static MI_Uint32 _FindCapacity(MI_Uint32 x)
{
    if (x <= _CAPACITY)
        return _CAPACITY;
    else
    {
        MI_Uint32 r = x - 1;

        r |= (r >> 1);
        r |= (r >> 2);
        r |= (r >> 4);
        r |= (r >> 8);
        r |= (r >> 16);

        return r + 1;
    }
}

/*
 * Obtains the self pointer for this instance. For static instances, this
 * it is the same as the instance parameter. For dynamic instances, the
 * self pointer is given by instance->self.
 */
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

/* Return the index of the given property or (MI_Uin32)-1 if not found */
static MI_Uint32 _FindPropertyDecl(
    const MI_ClassDecl* cd,
    const ZChar* name)
{
    MI_PropertyDecl** start = cd->properties;
    MI_PropertyDecl** end = start + cd->numProperties;
    MI_PropertyDecl** p = start;
    MI_Uint32 code;

    code = Hash(name);

    while (p != end)
    {
        if ((*p)->code == code && Zcasecmp((*p)->name, name) == 0)
            return (MI_Uint32)(p - start);
        p++;
    }

    return (MI_Uint32)-1;
}

static MI_PropertyDecl* _LookupPropertyDecl(
    const MI_ClassDecl* cd,
    const ZChar* name)
{
    MI_Uint32 index = _FindPropertyDecl(cd, name);

    if (index == (MI_Uint32)-1)
        return NULL;

    return cd->properties[index];
}

static MI_PropertyDecl* _ClonePropertyDecl(
    const MI_PropertyDecl* pd,
    Batch* batch)
{
    MI_PropertyDecl* p;

    p = (MI_PropertyDecl*)BCalloc(batch, sizeof(MI_PropertyDecl), CALLSITE);

    if (!p)
        return NULL;

    if (pd->name)
    {
        p->name = BStrdup(batch, pd->name, CALLSITE);

        if (!p->name)
            return NULL;
    }

    p->code = pd->code;
    p->flags = pd->flags;
    p->type = pd->type;
    p->offset = pd->offset;

    return p;
}

static MI_PropertyDecl** _ClonePropertyDecls(
    MI_PropertyDecl** properties,
    MI_Uint32 size,
    Batch* batch)
{
    MI_PropertyDecl** data;
    MI_Uint32 i;

    /* Allocate at least _CAPACITY properties */
    MI_Uint32 cap = (size < _CAPACITY) ? _CAPACITY : size;

    /* Allocate properties array */
    data = (MI_PropertyDecl**)BAlloc(batch, sizeof(MI_PropertyDecl*) * cap,
        CALLSITE);
    if (!data)
        return NULL;

    /* Copy each property */
    for (i = 0; i < size; i++)
    {
        MI_PropertyDecl* pd = _ClonePropertyDecl(properties[i], batch);
        if (!pd)
            return NULL;

        data[i] = pd;
    }

    return data;
}

static MI_ClassDecl* _CloneClassDecl(
    const MI_ClassDecl* cd,
    Batch* batch)
{
    MI_ClassDecl* p;

    /* Instance.classDecl */
    p = (MI_ClassDecl*)BCalloc(batch, sizeof(MI_ClassDecl), CALLSITE);
    if (!p)
        return NULL;

    /* Instance.name */
    if (cd->name)
    {
        p->name = BStrdup(batch, cd->name, CALLSITE);

        if (!p->name)
            return NULL;
    }

    /* Instance.code */
    p->code = cd->code;

    /* Instance.size */
    p->size = cd->size;

    /* Instance.properties */
    {
        p->properties = _ClonePropertyDecls(cd->properties, cd->numProperties,
            batch);

        if (!p->properties)
            return NULL;

        p->numProperties = cd->numProperties;
    }

    return p;
}

MI_INLINE InstanceHeader* _HeaderOf(Instance* self)
{
    return self ? ((InstanceHeader*)self - 1) : NULL;
}

MI_INLINE Instance* _InstanceOf(InstanceHeader* self)
{
    return self ? (Instance*)(self + 1) : NULL;
}

static Instance* _AllocInstance(Batch* batch, size_t size)
{
    InstanceHeader* h = (InstanceHeader*)BCalloc(
        batch,
        sizeof(InstanceHeader) + size,
        CALLSITE);

    if (!h)
        return NULL;

    h->magic = _MAGIC;
    h->u.refs = 1;
    return _InstanceOf(h);
}

static Instance* _ReallocInstance(
    Batch* batch,
    Instance* self,
    size_t oldSize,
    size_t newSize)
{
    InstanceHeader* h = (InstanceHeader*)BRealloc(
        batch,
        _HeaderOf(self),
        sizeof(InstanceHeader) + oldSize,
        sizeof(InstanceHeader) + newSize,
        CALLSITE);

    if (!h)
        return NULL;

    h->magic = _MAGIC;
    h->u.refs = 1;

    return _InstanceOf(h);
}

static void _FreeInstance(
    Batch* batch,
    Instance* self)
{
    InstanceHeader* h = _HeaderOf(self);

    if (h)
    {
        DEBUG_ASSERT(h->magic == _MAGIC);
#if defined(CONFIG_ENABLE_DEBUG)
        memset(h, 0xDD, sizeof(InstanceHeader) + sizeof(Instance));
#endif
        BFree(batch, h, CALLSITE);
    }
}

/*
 * Each dynamic instance is 'wrapped' inside another instance (referred to
 * by the self field). This requiredment is imposed by the
 * MI_Instance_AddElement() function, which does not allow the address of
 * the instance to change. Hence, indirection is required to allow the inner
 * instance to be relocated in memory as new properties are added. The
 * resulting layout is depicted below.
 *
 *        (Wrapper)
 *     +-------------+
 *     | MI_Instance |
 *     +---------+---+
 *     |         |   |         (Inner)
 *     +---------+---+     +-------------+
 *     | self    | ------> | MI_Instance |
 *     +---------+---+     +---------+---+
 *                         |         |   |
 *                         +---------+---+
 *                         |         |   |
 *                         +---------+---+
 *
 * All methods of the instance type, must resolve the self pointer using
 * _SelfOf(), which either returns the sole parameter itself (for static
 * instances) or the self field (for dynamic instances).
 *
 */
static Instance* _WrapInstance(
    Instance* self,
    Batch* batch)
{
    Instance* wrapper;

    if (!self)
        return NULL;

    /* Allocate space for outer wrapper instance */
    wrapper = (Instance*)_AllocInstance(batch, sizeof(MI_Instance));
    if (!wrapper)
        return NULL;

    /* Copy fields from inner instance to outer instance */
    *wrapper = *self;

    /* Set outer instance self to point to inner instance */
    wrapper->self = self;

    return wrapper;
}

MI_Uint32 _CountKeys(
    const Instance* self)
{
    MI_Uint32 n = 0;
    const MI_ClassDecl* cd = self->classDecl;
    MI_Uint32 i;

    for (i = 0; i < cd->numProperties; i++)
    {
        if (cd->properties[i]->flags & MI_FLAG_KEY)
            n++;
    }

    return n;
}

/*
**==============================================================================
**
** Public definitions
**
**==============================================================================
*/

MI_Result MI_CALL Instance_Construct(
    MI_Instance* self_,
    const MI_ClassDecl* classDecl,
    Batch* batch_)
{
    Instance* self = (Instance*)self_;
    MI_ClassDecl* cd = (MI_ClassDecl*)classDecl;
    Batch* batch = batch_;

    /* Check for null arguments */
    if (!self || !cd)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Create a new batch */
    if (!batch)
    {
        batch = Batch_New(_NUM_PAGES);
        if (!batch)
            return MI_RESULT_FAILED;
    }

    /* Zero-fill the object */
    memset(self, 0, cd->size);

    /* MI_Instance.ft */
    self->ft = &__mi_instanceFT;

    /* MI_Instance.self */
    self->self = self;

    /* MI_Instance.classDecl */
    self->classDecl = cd;

    /* MI_Instance.batch */
    self->batch = batch;

    /* Flags */
    self->releaseBatch = batch == batch_ ? MI_FALSE : MI_TRUE;

    MI_RETURN(MI_RESULT_OK);
}

_Use_decl_annotations_
MI_Result Instance_New(
    MI_Instance** selfOut,
    const MI_ClassDecl* classDecl,
    Batch* batch_)
{
    Instance* self;
    Batch* batch = batch_;
    MI_Result r;

    /* Check for null arguments */
    if (!selfOut || !classDecl)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Null out selfOut */
    *selfOut = NULL;

    /* Create a new batch */
    if (!batch)
    {
        batch = Batch_New(_NUM_PAGES);
        if (!batch)
            return MI_RESULT_FAILED;
    }

    /* Allocate structure */
    self = _AllocInstance(batch, classDecl->size);
    if (!self)
    {
        r = MI_RESULT_FAILED;
        goto failed;
    }

    /* Initialize the object */
    r = Instance_Construct((MI_Instance*)self, classDecl, batch);
    if (r != MI_RESULT_OK)
        goto failed;

    /* Arrange to release batch if we created it */
    self->releaseBatch = batch == batch_ ? MI_FALSE : MI_TRUE;

    *selfOut = (MI_Instance*)self;
    MI_RETURN(MI_RESULT_OK);

failed:
    if (batch != batch_)
        Batch_Delete(batch);
    return r;
}

_Use_decl_annotations_
MI_Result MI_CALL Instance_InitConvert(
    MI_Instance* self_,
    const MI_ClassDecl* cd1,
    const MI_Instance* inst_,
    MI_Boolean keysOnly,
    MI_Boolean allowKeylessInst,
    MI_Boolean copy,
    Batch* batch_)
{
    Instance* self;
    const Instance* inst = _SelfOf(inst_);
    MI_Uint32 i;
    MI_Result r;
    const MI_ClassDecl* cd2;
    const MI_SchemaDecl* sd1;
    Batch* batch = batch_;

    /* Check parameters */
    if (!self_ || !cd1 || !inst)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Create a new batch */
    if (!batch)
    {
        batch = Batch_New(_NUM_PAGES);
        if (!batch)
            return MI_RESULT_FAILED;
    }

    /* Resolve the schema declaration (based on type) */
    if (cd1->flags & MI_FLAG_METHOD)
        sd1 = ((MI_MethodDecl*)cd1)->schema;
    else if (cd1->flags & MI_FLAG_CLASS)
        sd1 = cd1->schema;
    else
    {
        return MI_RESULT_FAILED;
    }

    cd2 = inst->classDecl;

    /* Initialize the instance */
    r = Instance_Construct(self_, cd1, batch);
    if (r != MI_RESULT_OK)
    {
        goto failed;
    }

    /* Get the self pointer from the newly initialized instance */
    self = _SelfOf(self_);

    /* Arrange to release the batch */
    self->releaseBatch = batch == batch_ ? MI_FALSE : MI_TRUE;

    /* Copy the nameSpace */
    if (inst->nameSpace)
    {
        self->nameSpace = BStrdup(batch, inst->nameSpace, CALLSITE);
        if (!self->nameSpace)
        {
            r = MI_RESULT_FAILED;
            goto failed;
        }
    }

    /* Copy the serverName */
    if (inst->serverName)
    {
        self->serverName = BStrdup(batch, inst->serverName, CALLSITE);
        if (!self->serverName)
        {
            r = MI_RESULT_FAILED;
            goto failed;
        }
    }

    /* Validate that the two instances share the same key structure */
    if (!allowKeylessInst)
    {
        for (i = 0; i < cd1->numProperties; i++)
        {
            const MI_PropertyDecl* pd1 = cd1->properties[i];

            if (pd1->flags & MI_FLAG_KEY)
            {
                MI_Uint32 index;

                index = _FindPropertyDecl(cd2, pd1->name);
                if (index == (MI_Uint32)-1)
                {
                    r = MI_RESULT_TYPE_MISMATCH;
                    goto failed;
                }
            }
        }

        for (i = 0; i < cd2->numProperties; i++)
        {
            const MI_PropertyDecl* pd2 = cd2->properties[i];

            if (pd2->flags & MI_FLAG_KEY)
            {
                MI_Uint32 index;

                index = _FindPropertyDecl(cd1, pd2->name);
                if (index == (MI_Uint32)-1)
                {
                    r = MI_RESULT_TYPE_MISMATCH;
                    goto failed;
                }
            }
        }
    }

    /* ATTN: ignore unknown properties? */

    /* Set non-null properties */
    for (i = 0; i < cd2->numProperties; i++)
    {
        const MI_PropertyDecl* pd2 = cd2->properties[i];
        Field* field = (Field*)((char*)inst + pd2->offset);

        /* If requested, ignore non-keys */
        if (keysOnly && !(pd2->flags & MI_FLAG_KEY))
            continue;

        /* Set the non-null key values */
        if (Field_GetExists(field, pd2->type))
        {
            if (pd2->type == MI_STRING)
            {
                r = Instance_SetElementFromString(self_, pd2->name,
                    ((MI_Value*)field)->string);

                if (r != MI_RESULT_OK)
                {
                    r = MI_RESULT_TYPE_MISMATCH;
                    goto failed;
                }
            }
            else if (pd2->type == MI_STRINGA)
            {
                r = Instance_SetElementFromStringA(self_, pd2->name,
                    (const ZChar**)((MI_Value*)field)->stringa.data,
                    ((MI_Value*)field)->stringa.size);

                if (r != MI_RESULT_OK)
                {
                    r = MI_RESULT_TYPE_MISMATCH;
                    goto failed;
                }
            }
            else if (pd2->type == MI_INSTANCE || pd2->type == MI_REFERENCE)
            {
                MI_Instance* tmpInst;
                MI_ClassDecl* tmpCd;
                MI_Type type;

                /* Find the class declaration in the schema */
                tmpCd = SchemaDecl_FindClassDecl(sd1,
                    _SelfOf(((MI_Value*)field)->instance)->classDecl->name);

                if (!tmpCd)
                {
                    r = MI_RESULT_FAILED;
                    goto failed;
                }

                /* Allocate static instance of this class */
                if (Instance_New(&tmpInst, tmpCd, batch) != MI_RESULT_OK)
                {
                    r = MI_RESULT_FAILED;
                    goto failed;
                }

                /* Convert instance */
                r = Instance_InitConvert(tmpInst, tmpCd,
                    ((MI_Value*)field)->instance, keysOnly, MI_FALSE, copy,
                    ((Instance*)tmpInst)->batch);

                if (r != MI_RESULT_OK)
                {
                    __MI_Instance_Delete(tmpInst);
                    r = MI_RESULT_TYPE_MISMATCH;
                    goto failed;
                }

                /* Get the target property type */
                {
                    MI_PropertyDecl* pd = _LookupPropertyDecl(cd1, pd2->name);

                    if (!pd)
                    {
                        r = MI_RESULT_NO_SUCH_PROPERTY;
                        goto failed;
                    }

                    type = pd->type;
                }

                /* Reject if not instance or reference */

                switch (type)
                {
                    case MI_INSTANCE:
                    case MI_REFERENCE:
                    {
                        MI_Value v;
                        v.instance = tmpInst;

                        r = __MI_Instance_SetElement(
                            self_,
                            pd2->name,
                            &v,
                            type,
                            MI_FLAG_ADOPT);

                        break;
                    }
                    case MI_INSTANCEA:
                    case MI_REFERENCEA:
                    {
                        MI_Value v;
                        v.instancea.size = 1;
                        v.instancea.data =
                            BAlloc(batch, sizeof(void*), CALLSITE);

                        if (!v.instancea.data)
                        {
                            __MI_Instance_Delete(tmpInst);
                            r = MI_RESULT_FAILED;
                            goto failed;
                        }

                        v.instancea.data[0] = tmpInst;

                        r = __MI_Instance_SetElement(
                            self_,
                            pd2->name,
                            &v,
                            type,
                            MI_FLAG_ADOPT);

                        break;
                    }
                    default:
                    {
                        r = MI_RESULT_TYPE_MISMATCH;
                        break;
                    }
                }

                if (r != MI_RESULT_OK)
                {
                    __MI_Instance_Delete(tmpInst);
                    r = MI_RESULT_TYPE_MISMATCH;
                    goto failed;
                }
            }
            else if (pd2->type == MI_INSTANCEA || pd2->type == MI_REFERENCEA)
            {
                MI_Value v;
                MI_Uint32 j;

                v.instancea.size = ((MI_Value*)field)->instancea.size;
                v.instancea.data = BAlloc(batch,
                    v.instancea.size * sizeof(void*), CALLSITE);

                if (!v.instancea.data)
                {
                    r = MI_RESULT_FAILED;
                    goto failed;
                }

                for (j = 0; j < v.instancea.size; j++)
                {
                    MI_Instance* tmpInst;
                    MI_ClassDecl* tmpCd;

                    /* Find the schema declaration */
                    tmpCd = SchemaDecl_FindClassDecl(sd1, _SelfOf(((
                        MI_Value*)field)->instancea.data[j])->classDecl->name);

                    if (!tmpCd)
                    {
                        r = MI_RESULT_FAILED;
                        goto failed;
                    }

                    /* Allocate the instance for the provider */
                    if (Instance_New(&tmpInst,tmpCd,batch) != MI_RESULT_OK)
                    {
                        r = MI_RESULT_FAILED;
                        goto failed;
                    }

                    r = Instance_InitConvert(tmpInst, tmpCd,
                        ((MI_Value*)field)->instancea.data[j], keysOnly, MI_FALSE, copy,
                        ((Instance*)tmpInst)->batch);

                    if (r != MI_RESULT_OK)
                    {
                        MI_Uint32 k;

                        for (k = 0; k < j; k++)
                            __MI_Instance_Delete(v.instancea.data[k]);

                        r = MI_RESULT_TYPE_MISMATCH;
                        goto failed;
                    }

                    v.instancea.data[j] = tmpInst;
                }

                /* Set the value */
                r = __MI_Instance_SetElement(self_, pd2->name, &v, pd2->type,
                    MI_FLAG_ADOPT);

                /* Allow conversion from reference array to instance array */
                if (r == MI_RESULT_TYPE_MISMATCH && pd2->type == MI_INSTANCEA)
                {
                    r = __MI_Instance_SetElement(self_, pd2->name, &v,
                        MI_REFERENCEA, MI_FLAG_ADOPT);
                }

                if (r != MI_RESULT_OK)
                {
                    for (j = 0; j < v.instancea.size; j++)
                        __MI_Instance_Delete(v.instancea.data[j]);

                    r = MI_RESULT_TYPE_MISMATCH;
                    goto failed;
                }
            }
            else
            {
                MI_Uint32 tmpFlags = copy ? 0 : MI_FLAG_BORROW;

                /* Set the value */
                r = __MI_Instance_SetElement(self_, pd2->name, (MI_Value*)field,
                    pd2->type, tmpFlags);

                if (r != MI_RESULT_OK)
                {
                    r = MI_RESULT_TYPE_MISMATCH;
                    goto failed;
                }
            }
        }
    }

failed:
    if (batch != batch_)
        Batch_Delete(batch);
    return r;
}

MI_Result MI_CALL Instance_Clone(
    const MI_Instance* self_,
    MI_Instance** instOut,
    Batch* batch_)
{
    const Instance* self = _SelfOf(self_);
    Batch* batch = batch_;
    Instance* inst;
    MI_Uint32 i;
    MI_Result r;

    /* Check for a null parameter */
    if (!self || !instOut)
    {
        r = MI_RESULT_FAILED;
        goto failed;
    }

    /* Create new batch? */
    if (!batch)
    {
        batch = Batch_New(_NUM_PAGES);
        if (!batch)
            return MI_RESULT_FAILED;
    }

    /* Allocate the new instance */
    {
        MI_Uint32 cap = sizeof(MI_Instance) + _CAPACITY * sizeof(Field);

        if (self->classDecl->size > cap)
            cap = self->classDecl->size;

        inst = _AllocInstance(batch, cap);
        if (!inst)
        {
            r = MI_RESULT_FAILED;
            goto failed;
        }
    }

    /* Instance.self */
    inst->self = inst;

    /* Instance.flags */
    if (batch != batch_)
    {
        inst->releaseBatch = MI_TRUE;
    }

    /* Set Instance.batch */
    inst->batch = batch;

    /* Set MI_Instance.ft */
    inst->ft = &__mi_instanceFT;

    /* Instance.nameSpace */
    if (self->nameSpace)
    {
        inst->nameSpace = BStrdup(batch, self->nameSpace, CALLSITE);

        if (!inst->nameSpace)
        {
            r = MI_RESULT_FAILED;
            goto failed;
        }
    }

    /* Instance.serverName */
    if (self->serverName)
    {
        inst->serverName = BStrdup(batch, self->serverName, CALLSITE);

        if (!inst->serverName)
        {
            r = MI_RESULT_FAILED;
            goto failed;
        }
    }

    /* Set Instance.classDecl */
    if ((void*)self != (void*)self_)
    {
        inst->classDecl = _CloneClassDecl(self->classDecl, batch);

        if (!inst->classDecl)
        {
            r = MI_RESULT_FAILED;
            goto failed;
        }
    }
    else
        inst->classDecl = self->classDecl;

    /* Clone each of the fields */
    for (i = 0; i < self->classDecl->numProperties; i++)
    {
        const MI_PropertyDecl* pd = self->classDecl->properties[i];

        r = Field_Copy(
            (Field*)((char*)inst + pd->offset),
            pd->type,
            (Field*)((char*)self + pd->offset),
            batch);

        if (r != MI_RESULT_OK)
        {
            r = MI_RESULT_FAILED;
            goto failed;
        }
    }

    /* Wrapper dynamic instances */
    if ((void*)self != (void*)self_)
    {
        inst = _WrapInstance(inst, batch);
        if (!inst)
        {
            r = MI_RESULT_FAILED;
            goto failed;
        }
    }

    *instOut = (MI_Instance*)inst;
    return MI_RESULT_OK;

failed:
    if (batch != batch_)
        Batch_Delete(batch);
    return r;
}

MI_Result MI_CALL Instance_SetClassName(
    MI_Instance* self_,
    const ZChar* className)
{
    Instance* self = _SelfOf(self_);
    ZChar* oldClassName;

    /* Check parameters */
    if (!self || !className)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Save old className */
    oldClassName = self->classDecl->name;

    /* Set new className */
    {
        ZChar* tmp = BStrdup(self->batch, className, CALLSITE);

        if (!tmp)
            MI_RETURN(MI_RESULT_FAILED);

        self->classDecl->name = tmp;
        self->classDecl->code = Hash(tmp);
    }

    /* Free old className */
    if (oldClassName)
        BFree(self->batch, oldClassName, CALLSITE);

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL Instance_NewDynamic(
    MI_Instance** selfOut,
    const ZChar* className,
    MI_Uint32 metaType,
    Batch* batch_)
{
    Instance* self = NULL;
    Batch* batch = batch_;
    MI_Result r;

    /* Reject null arguments */
    if (!selfOut || !className)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Null output self pointer */
    *selfOut = NULL;

    /* Create batch if necessary */
    if (!batch)
    {
        batch = Batch_New(_NUM_PAGES);
        if (!batch)
            return MI_RESULT_FAILED;
    }

    /* Check that 'className' parameter is a legal CIM className */
    if (!LegalName(className))
    {
        r = MI_RESULT_INVALID_PARAMETER;
        goto failed;
    }

    /* Allocate instance and reserve room for properties */
    {
        self = _AllocInstance(batch,
            sizeof(MI_Instance) + _CAPACITY * sizeof(Field));

        if (!self)
        {
            r = MI_RESULT_FAILED;
            goto failed;
        }

        self->self = self;
    }

    /* Set Instance.classDecl */
    {
        MI_ClassDecl* cd;

        /* Allocate and set Instance.classDecl */
        {
            cd = (MI_ClassDecl*)BCalloc(batch, sizeof(MI_ClassDecl), CALLSITE);

            if (!cd)
            {
                r = MI_RESULT_FAILED;
                goto failed;
            }

            self->classDecl = cd;
        }

        /* MI_ClassDecl.flags: */
        if (metaType & MI_FLAG_ASSOCIATION)
            cd->flags |= MI_FLAG_ASSOCIATION;
        else if (metaType & MI_FLAG_INDICATION)
            cd->flags |= MI_FLAG_INDICATION;
        else if (metaType & MI_FLAG_METHOD)
            cd->flags |= MI_FLAG_METHOD;
        else if (metaType & MI_FLAG_CLASS)
            cd->flags |= MI_FLAG_CLASS;
        else
            cd->flags |= MI_FLAG_CLASS;

        /* MI_ClassDecl.name: */
        {
            cd->name = BStrdup(batch, className, CALLSITE);

            if (!cd->name)
            {
                r = MI_RESULT_FAILED;
                goto failed;
            }

        }

        /* MI_ClassDecl.code: */
        cd->code = Hash(cd->name);

        /* MI_ClassDecl.properties: */
        {
            MI_PropertyDecl** data;

            data = (MI_PropertyDecl**)BAlloc(batch,
                _CAPACITY * sizeof(MI_PropertyDecl), CALLSITE);

            if (!data)
            {
                r = MI_RESULT_FAILED;
                goto failed;
            }

            cd->properties = data;
            cd->numProperties = 0;
        }

        /* MI_ClassDecl.size: */
        cd->size = sizeof(MI_Instance);
    }

    /* Set batch: */
    self->batch = batch;

    /* Set flags */
    if (batch_)
        self->releaseBatch = MI_FALSE;
    else
        self->releaseBatch = MI_TRUE;

    /* Set MI_Instance.ft: */
    self->ft = &__mi_instanceFT;

    /* Set the self pointer */
    self->self = self;

    /* Set output instance (creating a wrapper for it) */
    self = _WrapInstance(self, batch);
    if (!self)
    {
        r = MI_RESULT_FAILED;
        goto failed;
    }

    *selfOut = (MI_Instance*)self;
    MI_RETURN(MI_RESULT_OK);

failed:
    if (batch != batch_)
        Batch_Delete(batch);
    return r;
}

MI_Boolean Instance_MatchKeys(
    const MI_Instance* self_,
    const MI_Instance* inst_)
{
    Instance* self;
    Instance* inst;

    /* Check parameters */
    if (!self_ || !inst_)
    {
        return MI_FALSE;
    }

    self = _SelfOf(self_);
    inst = _SelfOf(inst_);

    /* Check parameters */
    if (!self || !inst)
    {
        return MI_FALSE;
    }

    /* Verify they have the same number of keys (one or more) */
    {
        MI_Uint32 n = _CountKeys(self);

        if (n == 0 || n != _CountKeys(inst))
        {
            return MI_FALSE;
        }
    }

    /* Verify that key fields are identical */
    {
        const MI_ClassDecl* cd1 = self->classDecl;
        const MI_ClassDecl* cd2 = inst->classDecl;
        MI_Uint32 i;

        for (i = 0; i < cd1->numProperties; i++)
        {
            const MI_PropertyDecl* pd1 = cd1->properties[i];
            const MI_PropertyDecl* pd2;
            Field* f1;
            Field* f2;
            MI_Uint32 index;

            if (pd1->flags & MI_FLAG_KEY)
            {
                index = _FindPropertyDecl(cd2, pd1->name);

                if (index == (MI_Uint32)-1)
                {
                    return MI_FALSE;
                }

                pd2 = cd2->properties[index];

                if (!(pd2->flags & MI_FLAG_KEY))
                {
                    return MI_FALSE;
                }

                if (pd1->type != pd2->type)
                    return MI_FALSE;

                f1 = (Field*)((char*)self + pd1->offset);
                f2 = (Field*)((char*)inst + pd2->offset);

                if (!Field_MatchKey(f1, f2, pd1->type))
                {
                    return MI_FALSE;
                }
            }
        }
    }

    return MI_TRUE;
}

/*
**==============================================================================
**
** MI_Instance function table and functions
**
**==============================================================================
*/

void __MI_Instance_Ref(MI_Instance* self)
{
    InstanceHeader* h = _HeaderOf((Instance*)self);

    if (h)
        AtomicInc(&h->u.refs);
}

void __MI_Instance_Unref(MI_Instance* self)
{
    InstanceHeader* h = _HeaderOf((Instance*)self);

    if (h && AtomicDec(&h->u.refs))
        __MI_Instance_Delete((MI_Instance*)self);
}

MI_Result MI_CALL __MI_Instance_Clone(
    const MI_Instance* self,
    MI_Instance** inst)
{
    return Instance_Clone(self, inst, NULL);
}

MI_Result MI_CALL __MI_Instance_Destruct(
    MI_Instance* self_)
{
    Instance* self = _SelfOf(self_);
    Batch* batch;
    MI_Uint32 i;

    /* Check for null parameter */
    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Save pointer to batch */
    batch = self->batch;
    if (!batch)
        MI_RETURN(MI_RESULT_FAILED);

    /* Release serverName */
    if (self->serverName)
        BFree(batch, self->serverName, CALLSITE);

    /* Release nameSpace */
    if (self->nameSpace)
        BFree(batch, self->nameSpace, CALLSITE);

    /* Release all memory used by properties */
    for (i = 0; i < self->classDecl->numProperties; i++)
    {
        const MI_PropertyDecl* pd = self->classDecl->properties[i];
        Field* field = (Field*)((char*)self + pd->offset);
        Field_Destruct(field, pd->type, batch);
    }

    /* Free dynamic instance part (if any) */
    if ((void*)self != (void*)self_)
    {
        for (i = 0; i < self->classDecl->numProperties; i++)
        {
            MI_PropertyDecl* pd = self->classDecl->properties[i];
            BFree(batch, pd->name, CALLSITE);
            BFree(batch, pd, CALLSITE);
        }

        BFree(batch, self->classDecl->name, CALLSITE);
        BFree(batch, self->classDecl->properties, CALLSITE);
        BFree(batch, self->classDecl, CALLSITE);

        if ((void*)self != (void*)self_)
            _FreeInstance(batch, self);
    }

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL __MI_Instance_Delete(
    MI_Instance* self_)
{
    Instance* self = _SelfOf(self_);
    MI_Result r;
    Batch* batch;
    MI_Boolean releaseBatch;

    /* Check for null parameter */
    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Save pointer to batch */
    batch = self->batch;
    if (!batch)
        MI_RETURN(MI_RESULT_FAILED);

    /* Save */
    releaseBatch = self->releaseBatch;

    /* Destruct */
    r = __MI_Instance_Destruct(self_);
    if (r != MI_RESULT_OK)
        MI_RETURN(r);

    /* Release self pointer */
    _FreeInstance(batch, (Instance*)self_);

    /* Release the batch */
    if (releaseBatch)
        Batch_Delete(batch);

    return r;
}

MI_Result MI_CALL __MI_Instance_IsA(
    const MI_Instance* self_,
    const MI_ClassDecl* classDecl,
    MI_Boolean* resultOut)
{
    Instance* self = _SelfOf(self_);
    const MI_ClassDecl* p;

    if (!self || !classDecl)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    for (p = self->classDecl; p; p = p->superClassDecl)
    {
        if (p == classDecl)
        {
            if (resultOut)
                *resultOut = MI_TRUE;
            MI_RETURN(MI_RESULT_OK);
        }
    }

    if (resultOut)
        *resultOut = MI_FALSE;

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL __MI_Instance_GetClassName(
    const MI_Instance* self_,
    const ZChar** classNameOut)
{
    Instance* self = _SelfOf(self_);

    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    if (classNameOut)
        *classNameOut = self->classDecl->name;

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL __MI_Instance_SetNameSpace(
    MI_Instance* self_,
    const ZChar* nameSpace)
{
    Instance* self = _SelfOf(self_);
    ZChar* oldNameSpace;

    /* Check parameters */
    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Save old namespace */
    oldNameSpace = self->nameSpace;

    /* Set new namespace */
    if (nameSpace)
    {
        ZChar* tmp = BStrdup(self->batch, nameSpace, CALLSITE);

        if (!tmp)
            MI_RETURN(MI_RESULT_FAILED);

        self->nameSpace = tmp;
    }
    else
        self->nameSpace = NULL;

    /* Free old namespace */
    if (oldNameSpace)
        BFree(self->batch, oldNameSpace, CALLSITE);

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL __MI_Instance_GetNameSpace(
    const MI_Instance* self_,
    const ZChar** nameSpaceOut)
{
    Instance* self = _SelfOf(self_);

    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    if (nameSpaceOut)
        *nameSpaceOut = self->nameSpace;

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL __MI_Instance_GetElementCount(
    const MI_Instance* self_,
    MI_Uint32* countOut)
{
    Instance* self = _SelfOf(self_);

    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    if (countOut)
        *countOut = self->classDecl->numProperties;

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL __MI_Instance_AddElement(
    MI_Instance* self_,
    const ZChar* name,
    const MI_Value* value,
    MI_Type type,
    MI_Uint32 flags)
{
    Instance* self = _SelfOf(self_);
    MI_Uint32 index;
    MI_ClassDecl* cd;
    MI_Uint32 tflags = 0;

    if (flags & MI_FLAG_BORROW)
        tflags |= MI_FLAG_BORROW;

    if (flags & MI_FLAG_NULL)
        tflags |= MI_FLAG_NULL;

    /* Check for null arguments */
    if (!self || !name)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Reject attempts to extend a non-dynamic instances */
    if ((void*)self == (void*)self_)
        MI_RETURN(MI_RESULT_FAILED);

    /* Check that 'name' parameter is a legal CIM name */
    if (!LegalName(name))
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Find the property with this name */
    index = _FindPropertyDecl(self->classDecl, name);

    if (index != (MI_Uint32)-1)
        MI_RETURN(MI_RESULT_ALREADY_EXISTS);

    /* Get pointer to class declaration */
    cd = (MI_ClassDecl*)self->classDecl;

    /* Extend size of instance and properties array as needed */
    if (cd->numProperties == _FindCapacity(cd->numProperties))
    {
        MI_Uint32 cap;
        MI_PropertyDecl** data;

        /* Double old capacity */
        cap = 2 * cd->numProperties;

        /* Reallocate properties array */
        data = (MI_PropertyDecl**)BRealloc(
            self->batch,
            cd->properties,
            cd->numProperties * sizeof(MI_PropertyDecl),
            cap * sizeof(MI_PropertyDecl),
            CALLSITE);

        if (!data)
            MI_RETURN(MI_RESULT_FAILED);

        cd->properties = data;

        /* Reallocate instance */
        self = _ReallocInstance(
            self->batch,
            self,
            sizeof(MI_Instance) + cd->numProperties * sizeof(Field),
            sizeof(MI_Instance) + cap * sizeof(Field));
        if (!self)
            MI_RETURN(MI_RESULT_FAILED);

        /* Set new self */
        self->self = self;
    }

    /* Create and add new property */
    {
        MI_PropertyDecl* pd;

        /* Allocate new peroperty declaration */
        pd = (MI_PropertyDecl*)BCalloc(
            self->batch, sizeof(MI_PropertyDecl), CALLSITE);

        if (!pd)
            MI_RETURN(MI_RESULT_FAILED);

        /* MI_PropertyDecl.flags */
        pd->flags = flags;

        /* MI_PropertyDecl.name */
        pd->name = BStrdup(self->batch, name, CALLSITE);

        if (!pd->name)
            MI_RETURN(MI_RESULT_FAILED);

        /* MI_PropertyDecl.code */
        pd->code = Hash(pd->name);

        /* MI_PropertyDecl.type */
        pd->type = type;

        /* MI_PropertyDecl.offset */
        pd->offset = sizeof(MI_Instance) + cd->numProperties*sizeof(Field);

        /* Add property to array */
        cd->properties[cd->numProperties++] = pd;

        /* Clear the new field */
        memset((char*)self + pd->offset, 0, sizeof(Field));

        /* Adjust size */
        cd->size += sizeof(Field);
    }

    /* Reassign 'self' field (it may have changed) */
    ((Instance*)self_)->self = self;

    /* Copy self of self wrapper */
    memcpy(self_, self, sizeof(MI_Instance));

    /* Set the last property */
    MI_RETURN(__MI_Instance_SetElementAt(
        self_, cd->numProperties - 1, value, type, tflags));
}

MI_Result MI_CALL __MI_Instance_SetElement(
    MI_Instance* self_,
    const ZChar* name,
    const MI_Value* value,
    MI_Type type,
    MI_Uint32 flags)
{
    Instance* self = _SelfOf(self_);
    MI_Uint32 index;

    /* Check for null arguments */
    if (!self || !name)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Find the property with this name */
    index = _FindPropertyDecl(self->classDecl, name);

    if (index == (MI_Uint32)-1)
        MI_RETURN(MI_RESULT_NO_SUCH_PROPERTY);

    MI_RETURN(__MI_Instance_SetElementAt(self_, index, value, type, flags));
}

MI_Result MI_CALL __MI_Instance_SetElementAt(
    MI_Instance* self_,
    MI_Uint32 index,
    const MI_Value* value,
    MI_Type type,
    MI_Uint32 flags)
{
    Instance* self = _SelfOf(self_);
    const MI_PropertyDecl* pd;
    char* field;

    /* Check for null arguments */
    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Check whether index is in range */
    if (index > self->classDecl->numProperties)
        MI_RETURN(MI_RESULT_FAILED);

    /* Get pointer to properties declaration */
    pd = self->classDecl->properties[index];

    /* Check the type */
    if (type != (MI_Type)pd->type)
        MI_RETURN(MI_RESULT_TYPE_MISMATCH);

    /* Get pointer to field */
    field = (char*)self + pd->offset;

    /* Set the value */
    {
        MI_Result r = Field_Set(
            (Field*)field,
            pd->type,
            value,
            flags,
            self->batch);

        if (r != MI_RESULT_OK)
            return r;
    }

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL __MI_Instance_GetElement(
    const MI_Instance* self_,
    const ZChar* name,
    MI_Value* valueOut,
    MI_Type* typeOut,
    MI_Uint32* flagsOut,
    MI_Uint32* indexOut)
{
    Instance* self = _SelfOf(self_);
    MI_Uint32 index;
    MI_Result r;

    /* Check for null arguments */
    if (!self || !name)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Find the property with this name */
    index = _FindPropertyDecl(self->classDecl, name);

    if (index == (MI_Uint32)-1)
        MI_RETURN(MI_RESULT_NO_SUCH_PROPERTY);

    r = __MI_Instance_GetElementAt(
        self_, index, NULL, valueOut, typeOut, flagsOut);

    if (r != MI_RESULT_OK)
        MI_RETURN(r);

    if (indexOut)
        *indexOut = index;

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL __MI_Instance_GetElementAt(
    const MI_Instance* self_,
    MI_Uint32 index,
    const ZChar** nameOut,
    MI_Value* valueOut,
    MI_Type* typeOut,
    MI_Uint32* flagsOut)
{
    Instance* self = _SelfOf(self_);
    const MI_PropertyDecl* pd;
    const Field* field;

    /* Check for null arguments */
    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Check for bounds error */
    if (index >= self->classDecl->numProperties)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    pd = self->classDecl->properties[index];

    /* Get pointer to field */
    field = (Field*)((char*)self + pd->offset);

    /* set nameOut */
    if (nameOut)
        *nameOut = pd->name;

    /* set valueOut */
    if (valueOut)
        memcpy(valueOut, field, Type_SizeOf((MI_Type)pd->type));

    /* Set existsOut */
    if (flagsOut)
    {
        *flagsOut = pd->flags;

        if (!Field_GetExists(field, (MI_Type)pd->type))
            *flagsOut |= MI_FLAG_NULL;
    }

    /* Set typeOut */
    if (typeOut)
        *typeOut = (MI_Type)pd->type;

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL __MI_Instance_ClearElement(
    MI_Instance* self_,
    const ZChar* name)
{
    Instance* self = _SelfOf(self_);
    MI_Uint32 index;

    /* Check for null arguments */
    if (!self || !name)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Find the property with this name */
    index = _FindPropertyDecl(self->classDecl, name);

    if (index == (MI_Uint32)-1)
        MI_RETURN(MI_RESULT_NO_SUCH_PROPERTY);

    MI_RETURN(__MI_Instance_ClearElementAt(self_, index));
}

MI_Result MI_CALL __MI_Instance_ClearElementAt(
    MI_Instance* self_,
    MI_Uint32 index)
{
    Instance* self = _SelfOf(self_);
    const MI_PropertyDecl* pd;
    char* field;

    /* Check for null arguments */
    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Check whether index is in range */
    if (index > self->classDecl->numProperties)
        MI_RETURN(MI_RESULT_FAILED);

    /* Get pointer to properties declaration */
    pd = self->classDecl->properties[index];

    /* Get pointer to field */
    field = (char*)self + pd->offset;

    /* Clear the value */
    Field_Clear((Field*)field, pd->type,
        self->batch);

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL __MI_Instance_GetServerName(
    const MI_Instance* self,
    const ZChar** name)
{
    MI_RETURN(MI_RESULT_NOT_SUPPORTED);
}

MI_Result MI_CALL __MI_Instance_SetServerName(
    _Inout_ MI_Instance* self,
    _In_z_ const ZChar* name)
{
    MI_RETURN(MI_RESULT_NOT_SUPPORTED);
}

MI_Result MI_CALL __MI_Instance_GetClass(
    _In_ const MI_Instance* self,
    _Outptr_ MI_Class** instanceClass)
{
    MI_RETURN(MI_RESULT_NOT_SUPPORTED);
}

MI_InstanceFT __mi_instanceFT =
{
    __MI_Instance_Clone,
    __MI_Instance_Destruct,
    __MI_Instance_Delete,
    __MI_Instance_IsA,
    __MI_Instance_GetClassName,
    __MI_Instance_SetNameSpace,
    __MI_Instance_GetNameSpace,
    __MI_Instance_GetElementCount,
    __MI_Instance_AddElement,
    __MI_Instance_SetElement,
    __MI_Instance_SetElementAt,
    __MI_Instance_GetElement,
    __MI_Instance_GetElementAt,
    __MI_Instance_ClearElement,
    __MI_Instance_ClearElementAt,
    __MI_Instance_GetServerName,
    __MI_Instance_SetServerName,
    __MI_Instance_GetClass,
};
