/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
#include "class.h"
#include <pal/intsafe.h>
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
static MI_Uint32 _NUM_PAGES = INFINITE;

/* The minimum number of reserved properties for a dynamic instance */
static size_t _CAPACITY = 32;

/* Find capacity (lesser of _CAPACITY or x rounded to power of 2) */
static size_t _FindCapacity(size_t x)
{
    if (x <= _CAPACITY)
        return _CAPACITY;
    else
    {
        size_t r = x - 1;

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

/* Return the index of the given property */
MI_Uint32 _FindFeatureDecl(
    MI_FeatureDecl** features,
    MI_Uint32 numFeatures,
    const MI_Char* name)
{
    MI_Uint32 code;
    MI_FeatureDecl** start = features;
    MI_FeatureDecl** p = start;
    MI_FeatureDecl** end = start + numFeatures;

    /* Zero-length CIM names are illegal */
    if (*name == '\0')
        return (MI_Uint32)-1;

    code = Hash(name);

    /* Find the property */
    while (p != end)
    {
        if (p[0]->code == code && Tcscasecmp(p[0]->name, name) == 0)
            return (MI_Uint32)(p - start);
        p++;
    }

    /* Not found */
    return (MI_Uint32)-1;
}

/* Return the index of the given property */
MI_INLINE MI_Uint32 _FindPropertyDeclIndex(
    const MI_ClassDecl* cd,
    const MI_Char* name)
{
    return _FindFeatureDecl(
        (MI_FeatureDecl**)cd->properties,
        cd->numProperties,
        name);
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
        if ((*p)->code == code && Tcscasecmp((*p)->name, name) == 0)
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
static MI_Qualifier * _CloneQualifierDecl(
    MI_Qualifier * qualifier,
    _Inout_ Batch *batch)
{
    MI_Qualifier *newQualifier = Batch_Get(batch, sizeof(MI_Qualifier));
    if (newQualifier == NULL)
    {
        return NULL;
    }
    memset(newQualifier, 0, sizeof(*newQualifier));
    newQualifier->name = Batch_Tcsdup(batch, qualifier->name);
    if (newQualifier->name == NULL)
    {
        return NULL;
    }
    newQualifier->type = qualifier->type;
    newQualifier->flavor = qualifier->flavor;
    /* Clone only boolean values. */
    if (qualifier->value && qualifier->type == MI_BOOLEAN)
    {
        newQualifier->value = Batch_Get(batch, sizeof(MI_Boolean));
        if (newQualifier->value == NULL)
        {
            return NULL;
        }
        *(MI_Boolean*)newQualifier->value = *(MI_Boolean*)qualifier->value;
    }
    else
    {
        newQualifier->value = NULL;
    }

    return newQualifier;
}

static MI_Qualifier  **_CloneQualifierDecls(
    MI_Qualifier **qualifiers,
    MI_Uint32 numQualifiers,
    _Inout_ Batch *batch)
{
    MI_Qualifier **newQualifiers = Batch_Get(batch, sizeof(MI_Qualifier*)*numQualifiers);
    MI_Uint32 qualifierIndex = 0;
    if (newQualifiers == NULL)
    {
        return NULL;
    }
    for (;qualifierIndex != numQualifiers; qualifierIndex++)
    {
        newQualifiers[qualifierIndex] = _CloneQualifierDecl(qualifiers[qualifierIndex], batch);
        if (newQualifiers[qualifierIndex] == NULL)
        {
            return NULL;
        }
    }

    return newQualifiers;
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

    if (pd->qualifiers && pd->numQualifiers)
    {
        p->qualifiers = _CloneQualifierDecls(pd->qualifiers, pd->numQualifiers, batch);
        if (p->qualifiers == NULL)
        {
            return NULL;  /* Returning NULL causes whole batch to destruct */
        }
        p->numQualifiers = pd->numQualifiers;
    }

    return p;
}

static MI_PropertyDecl** _ClonePropertyDecls(
    MI_PropertyDecl** properties,
    size_t size,
    Batch* batch)
{
    MI_PropertyDecl** data;
    MI_Uint32 i;

    /* Allocate at least _CAPACITY properties */
    size_t cap = (size < _CAPACITY) ? _CAPACITY : size;

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

MI_ClassDecl* _CloneClassDecl(
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
    p->owningClass = (MI_Class*)-1; //We are using this clone because it is a dynamic classDecl, so mark this classDecl as dynamic
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
    if ((cd->flags & (MI_FLAG_CLASS|MI_FLAG_ASSOCIATION|MI_FLAG_INDICATION)) && (cd->owningClass == NULL))
    {
        //Should be static
        self->classDecl = cd;
    }
    else if ((cd->flags & (MI_FLAG_CLASS|MI_FLAG_ASSOCIATION|MI_FLAG_INDICATION)) && (cd->owningClass != (MI_Class*)-1))
    {
        //Bump up the ref-count on the owning classDecl if it is a class AND it is not a static classDecl
        MI_Class *newClass;
        MI_Result result = MI_Class_Clone(cd->owningClass, &newClass);
        if (result != MI_RESULT_OK)
            return result;

        self->classDecl = newClass->classDecl;
    }
    else if (cd->flags & (MI_FLAG_CLASS|MI_FLAG_ASSOCIATION|MI_FLAG_INDICATION))
    {
        if (!batch)
        {
            assert(0);
            MI_RETURN(MI_RESULT_INVALID_PARAMETER);
        }

        //This is a class, so do a full clone
        self->classDecl = Class_Clone_ClassDecl(batch, cd);
        if (self->classDecl == NULL)
            return MI_RESULT_FAILED;
    }
    else
    {
        if (!batch)
        {
            assert(0);
            MI_RETURN(MI_RESULT_INVALID_PARAMETER);
        }

        //This may be a parameter, so need to do a reduced clone
        self->classDecl = _CloneClassDecl(cd, batch);
        if (self->classDecl == NULL)
            return MI_RESULT_FAILED;
    }

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
    Batch* batch_,
    MI_Uint32 flags)
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
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
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
            r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto failed;
        }
    }

    /* Copy the serverName */
    if (inst->serverName)
    {
        self->serverName = BStrdup(batch, inst->serverName, CALLSITE);
        if (!self->serverName)
        {
            r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
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
                    if (pd1->value)
                    {
                        //add default key value
                        MI_Value* value = (MI_Value*)pd1->value;
                        r = MI_Instance_SetElementAt(self_, i, value, pd1->type, MI_FLAG_BORROW);
                        if (r != MI_RESULT_OK)
                        {
                            goto failed;
                        }

                    }
                    else
                    {
                        r = MI_RESULT_NO_SUCH_PROPERTY;
                        goto failed;
                    }
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
                    r = MI_RESULT_NO_SUCH_PROPERTY;
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
                    ((MI_Value*)field)->string, flags);

                if (r != MI_RESULT_OK)
                {
                    goto failed;
                }
            }
            else if (pd2->type == MI_STRINGA)
            {
                r = Instance_SetElementFromStringA(self_, pd2->name,
                    (const ZChar**)((MI_Value*)field)->stringa.data,
                    ((MI_Value*)field)->stringa.size,
                    flags);

                if (r != MI_RESULT_OK)
                {
                    goto failed;
                }
            }
            else if (pd2->type == MI_INSTANCE || pd2->type == MI_REFERENCE)
            {
                MI_Instance* tmpInst;
                MI_ClassDecl* tmpCd;
                MI_Type type;
                MI_Boolean allowKeylessEmbedInst = (pd2->type == MI_INSTANCE) ? MI_TRUE : MI_FALSE;

                /* Find the class declaration in the schema */
                tmpCd = SchemaDecl_FindClassDecl(sd1,
                    _SelfOf(((MI_Value*)field)->instance)->classDecl->name);

                if (!tmpCd)
                {
                    r = MI_RESULT_NO_SUCH_PROPERTY;
                    goto failed;
                }

                /* Allocate static instance of this class */
                r = Instance_New(&tmpInst, tmpCd, batch);
                if (r != MI_RESULT_OK)
                {
                    goto failed;
                }

                /* Convert instance */
                r = Instance_InitConvert(tmpInst, tmpCd,
                    ((MI_Value*)field)->instance, keysOnly, allowKeylessEmbedInst, copy,
                    ((Instance*)tmpInst)->batch, flags);

                if (r != MI_RESULT_OK)
                {
                    __MI_Instance_Delete(tmpInst);
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
                MI_Boolean allowKeylessEmbedInst = (pd2->type == MI_INSTANCEA) ? MI_TRUE : MI_FALSE;

                v.instancea.size = ((MI_Value*)field)->instancea.size;
                v.instancea.data = BAlloc(batch,
                    v.instancea.size * sizeof(void*), CALLSITE);

                if (!v.instancea.data)
                {
                    r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
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
                        r = MI_RESULT_NO_SUCH_PROPERTY;
                        goto failed;
                    }

                    /* Allocate the instance for the provider */
                    r = Instance_New(&tmpInst,tmpCd,batch);
                    if (r != MI_RESULT_OK)
                    {
                        goto failed;
                    }

                    r = Instance_InitConvert(tmpInst, tmpCd,
                        ((MI_Value*)field)->instancea.data[j], keysOnly, allowKeylessEmbedInst, copy,
                        ((Instance*)tmpInst)->batch, flags);

                    if (r != MI_RESULT_OK)
                    {
                        MI_Uint32 k;

                        for (k = 0; k < j; k++)
                            __MI_Instance_Delete(v.instancea.data[k]);

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
    const Instance* self;
    Batch* batch = batch_;
    Instance* inst;
    MI_Uint32 i;
    MI_Result r;

    /* Check for externally defined instance */
    if (self_ && self_->ft != &__mi_instanceFT && self_->ft != NULL)
        return MI_Instance_Clone(self_, instOut);

    self = _SelfOf(self_);

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
    if ((self->classDecl->flags & (MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_ASSOCIATION)) &&  (self->classDecl->owningClass == NULL)) //static
    {
        inst->classDecl = self->classDecl;
    }
    else if ((self->classDecl->owningClass == (MI_Class*)-1) || !(self->classDecl->flags & (MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_ASSOCIATION)))
    {
        //classDecl is from a dynamic instance without a proper classDecl
        inst->classDecl = _CloneClassDecl(self->classDecl, batch);

        if (!inst->classDecl)
            MI_RETURN(MI_RESULT_FAILED);
    }
    else if (self->classDecl->owningClass)  //has a proper MI_Class owner so can clone it to bump refcount
    {
        MI_Class *clonedClass;
        MI_Result result = MI_Class_Clone(self->classDecl->owningClass, &clonedClass);
        if (result != MI_RESULT_OK)
            MI_RETURN(result);
        inst->classDecl = clonedClass->classDecl;
    }
    else//We had better do a hard clone
    {
        inst->classDecl = Class_Clone_ClassDecl(batch, self->classDecl);
        if (inst->classDecl == NULL)
            MI_RETURN(MI_RESULT_FAILED);
    }

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

_Use_decl_annotations_
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

            cd->owningClass = (MI_Class*) -1; /* Mark as a dynamic instance */
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

/* Get underline instance */
Instance* Instance_GetSelf(
    const MI_Instance* self)
{
    return _SelfOf( self );
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
        Atomic_Inc(&h->u.refs);
}

void __MI_Instance_Unref(MI_Instance* self)
{
    InstanceHeader* h = _HeaderOf((Instance*)self);

    if (h && Atomic_Dec(&h->u.refs) == 0)
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
    MI_Boolean releaseBatch;

    /* Check for null parameter */
    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Save release flag */
    releaseBatch = self->releaseBatch;

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
    else
    {
        if ((self->classDecl->flags & (MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_ASSOCIATION)) && self->classDecl->owningClass)
        {
            //Bump down the ref-count on the owning MI_Class if there is one, deleting it if necessary
            MI_Class_Delete(self->classDecl->owningClass);
        }
    }

    /* release batch */
    if (releaseBatch)
        Batch_Delete(batch);

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
    if (MI_FALSE == releaseBatch)
        _FreeInstance(batch, (Instance*)self_);

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
            cd->numProperties * sizeof(MI_PropertyDecl*),
            cap * sizeof(MI_PropertyDecl*),
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

        /* Allocate new property declaration */
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

    /* Set flagsOut */
    if (flagsOut)
    {
        MI_Uint8 fieldFlags = 0;
        *flagsOut = pd->flags & ~(MI_FLAG_NULL | MI_FLAG_NOT_MODIFIED);

        if (!Field_GetExists(field, (MI_Type)pd->type))
            *flagsOut |= MI_FLAG_NULL;

        /* get the field flags */
        switch ((MI_Type)pd->type)
        {
            case MI_UINT8:
            case MI_SINT8:
            case MI_BOOLEAN:
            {
                MI_Uint8Field* f = (MI_Uint8Field*)field;
                fieldFlags = f->flags;
                break;
            }
            case MI_UINT16:
            case MI_SINT16:
            case MI_CHAR16:
            {
                MI_Uint16Field* f = (MI_Uint16Field*)field;
                fieldFlags = f->flags;
                break;
            }
            case MI_UINT32:
            case MI_SINT32:
            case MI_REAL32:
            {
                MI_Uint32Field* f = (MI_Uint32Field*)field;
                fieldFlags = f->flags;
                break;
            }
            case MI_UINT64:
            case MI_SINT64:
            case MI_REAL64:
            {
                MI_Uint64Field* f = (MI_Uint64Field*)field;
                fieldFlags = f->flags;
                break;
            }
            case MI_DATETIME:
            {
                MI_DatetimeField* f = (MI_DatetimeField*)field;
                fieldFlags = f->flags;
                break;
            }
            case MI_STRING:
            {
                MI_StringField* f = (MI_StringField*)field;
                fieldFlags = f->flags;
                break;
            }
            case MI_INSTANCE:
            case MI_REFERENCE:
            {
                MI_InstanceField* f = (MI_InstanceField*)field;
                fieldFlags = f->flags;
                break;
            }
            case MI_BOOLEANA:
            case MI_UINT8A:
            case MI_SINT8A:
            case MI_UINT16A:
            case MI_SINT16A:
            case MI_UINT32A:
            case MI_SINT32A:
            case MI_UINT64A:
            case MI_SINT64A:
            case MI_REAL32A:
            case MI_REAL64A:
            case MI_CHAR16A:
            case MI_DATETIMEA:
            case MI_INSTANCEA:
            case MI_REFERENCEA:
            case MI_STRINGA:
            {
                MI_StringAField* f = (MI_StringAField*)field;
                fieldFlags = f->flags;
                break;
            }
        }
        if ((fieldFlags & _MODIFIED) == 0)
        {
            *flagsOut |= MI_FLAG_NOT_MODIFIED;
        }
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
    const MI_Instance* self_,
    const ZChar** servername)
{
    Instance* self = _SelfOf(self_);

    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    if (servername)
        *servername = self->serverName;

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL __MI_Instance_SetServerName(
    _Inout_ MI_Instance* self_,
    _In_z_ const ZChar* serverName)
{
    Instance* self = _SelfOf(self_);
    Instance* selfOrg = (Instance*)self_;
    MI_Char* oldServerName;

    /* Check parameters */
    if (!self)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Save old namespace */
    oldServerName = self->serverName;

    /* Set new namespace */
    if (serverName)
    {
        MI_Char* tmp;

        tmp = BStrdup(self->batch, serverName, CALLSITE);

        if (!tmp)
            MI_RETURN(MI_RESULT_SERVER_LIMITS_EXCEEDED);

        self->serverName = tmp;
    }
    else
        self->serverName = NULL;

    if (selfOrg != self)
        selfOrg->serverName = self->serverName;

    /* Free old namespace */
    if (oldServerName)
        BFree(self->batch, oldServerName, CALLSITE);

    MI_RETURN(MI_RESULT_OK);
}

MI_Result MI_CALL __MI_Instance_GetClass(
    _In_ const MI_Instance* self_,
    _Outptr_ MI_Class** instanceClass)
{
    Instance* self = _SelfOf(self_);

    return Class_New(self->classDecl, self->nameSpace, self->serverName, instanceClass);
}

MI_Result MI_CALL MI_Instance_GetClassExt(
    _In_ const MI_Instance *self,
    _Inout_ MI_Class* classToGet)
{
    if ((self == NULL) || (classToGet == NULL))
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    return Class_Construct(classToGet, self->classDecl);
}

MI_Result Instance_SetElementArray(
    _Out_ MI_Instance* self_,
    _In_z_ const MI_Char* name,
    MI_Type type,
    MI_Uint32 flags,
    MI_Uint32 numberArrayItems,
    _Out_ MI_Uint32 *elementId
    )
{
    MI_Result result;
    Instance* self = _SelfOf(self_);
    MI_Uint32 index;
    MI_ArrayField *fieldValue;
    MI_Value nullValue;

    //Find the ID of the entry
    /* Check for null arguments */
    if (!self || !name)
        MI_RETURN(MI_RESULT_INVALID_PARAMETER);

    /* Find the property with this name */
    index = _FindPropertyDeclIndex(self->classDecl, name);

    if (index == (MI_Uint32)-1)
        MI_RETURN(MI_RESULT_NO_SUCH_PROPERTY);

    //SetElementAt with NULL value
    nullValue.array.data = NULL;
    nullValue.array.size = 0;
    result = __MI_Instance_SetElementAt(self_, index, &nullValue, type|MI_ARRAY, flags);
    if (result != MI_RESULT_OK)
    {
        return result;
    }

    //Get the array field
    fieldValue = (MI_ArrayField*)((char*)self + self->classDecl->properties[index]->offset);

    //Allocate the element array
    fieldValue->value.size = 0;  //We set the size as 0, but as items are added the number is increased
    if (numberArrayItems)
    {
        fieldValue->value.data = Batch_Get(self->batch, numberArrayItems*Type_SizeOf(type));
        if (fieldValue->value.data == NULL)
        {
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
    }
    else
    {
        fieldValue->value.data = NULL;
    }
    *elementId = index;
    return MI_RESULT_OK;
}

MI_Result Instance_SetElementArrayItem(
    _Out_ MI_Instance* self_,
    MI_Uint32 elementId,
    MI_Value value)
{
    Instance* self = _SelfOf(self_);
    MI_ArrayField *fieldValue;
    MI_Type type;
    MI_Result result;

    type = (MI_Type)(self->classDecl->properties[elementId]->type & ~16); //Remove array part of type;

    fieldValue = (MI_ArrayField*)((char*)self + self->classDecl->properties[elementId]->offset);

    result = Class_Clone_ArrayValue(self->batch, type, fieldValue->value.data, fieldValue->value.size, &value);
    if (result != MI_RESULT_OK)
        return result;

    //Bump how many array items we have in value
    fieldValue->value.size++;
    fieldValue->exists = MI_TRUE;

    return MI_RESULT_OK;
}

MI_Boolean Instance_IsDynamic(
    _In_ MI_Instance *self_)
{
    Instance* self = _SelfOf(self_);
    if (self != (void*)self_)
        return MI_TRUE;
    else
        return MI_FALSE;
}

/*
 * Verifies that all key properties of the instance have non-NULL values.  A
 * NULL key property means that it is a malformed instance.
 *
 * Note: __MI_Instance_* functions are used in case the provided instance
 *       does not have a function table.
 */
MI_Boolean Instance_ValidateNonNullKeys(
    const MI_Instance* self )
{
    MI_Uint32 i = 0;

    if (Instance_IsDynamic((MI_Instance*)self))
    {
        /* Dynamic instance
         * Since it doesn't have a MI_ClassDecl, the best we can do is to
         * validate whether all of its key properties are non-NULL. */
        MI_Uint32 count = 0;
        MI_Result result = __MI_Instance_GetElementCount( self, &count );
        if (MI_RESULT_OK != result)
            return MI_FALSE;
        for (i = 0; i < count; i++)
        {
            MI_Uint32 flags = 0;
            MI_Result result = __MI_Instance_GetElementAt( self, i, NULL, NULL, NULL, &flags );
            if (MI_RESULT_OK != result)
                return MI_FALSE;
            if ((MI_FLAG_KEY & flags) &&
                (MI_FLAG_NULL & flags))
                return MI_FALSE;
        }
        return MI_TRUE;
    }
    else
    {
        /* Static instance
         * Validate that each key property is non-NULL */
        const MI_ClassDecl* cd = self->classDecl;
        for (i = 0; i < cd->numProperties; i++)
        {
            if (cd->properties[i]->flags & MI_FLAG_KEY)
            {
                MI_Uint32 flags = 0;
                MI_Result result = __MI_Instance_GetElementAt( self, i, NULL, NULL, NULL, &flags );
                if (MI_RESULT_OK != result)
                    return MI_FALSE;
                if (MI_FLAG_NULL & flags)
                    return MI_FALSE;
            }
        }
        return MI_TRUE;
    }
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
