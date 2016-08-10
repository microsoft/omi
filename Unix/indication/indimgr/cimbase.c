/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <pal/strings.h>
#include <indication/common/indilog.h>
#include "cimbase.h"

_Use_decl_annotations_
int CimBase_AddRef(CimBase *self)
{
    DEBUG_ASSERT(NULL != self);
    return (int)Atomic_Inc(&self->refcounter);
}

_Use_decl_annotations_
int CimBase_Release(CimBase *self)
{
    ptrdiff_t refc;
    DEBUG_ASSERT(NULL != self);
    DEBUG_ASSERT(NULL != self->_ft);
    DEBUG_ASSERT(NULL != self->_ft->finalize);
    refc = Atomic_Dec(&self->refcounter);
    if (refc == 0)
    {
        self->_ft->finalize(self);

        /* release memory of the object*/
        Batch_Delete(self->batch);
    }
    return (int)refc;
}

/* Release reference on the whole list starting from self */
_Use_decl_annotations_
int CimBase_ReleaseList(CimBase *self)
{
    DEBUG_ASSERT(self);
    while (self)
    {
        CimBase *p = self;
        self = self->next;
        CimBase_Release(p);
    }
    return 0;
}

/* Add to container callback */
int CimBase_OnAdd(_Inout_ CimBase *self, _In_ void* container)
{
    if (NULL != self->_container)
    {
        trace_ObjectContainerIsNotNull(self, self->_container);
        return -1;
    }

    /* set container */
    self->_container = container;

    /* Create a id for the object */
    self->identifier = self->_ft->createid(self);
    if (!self->identifier)
        return -1;
    return 0;
}

/* Remove from container callback */
int CimBase_OnRemove(_Inout_ CimBase *self, _In_ void* container)
{
    if (self->_container != container)
    {
        trace_ObjectUnexpectedContainer(self, self->_container, container);
        return -1;
    }

    self->_container = NULL;
    self->identifier = NULL;
    return 0;
}

void CimBase_Finalize(CimBase *self)
{
    return;
}

CimBaseFT g_cimbaseft = {
    CimBase_AddRef,
    CimBase_Release,
    CimBase_Finalize,
    CimBase_OnAdd,
    CimBase_OnRemove,
    NULL,
};

/* Create an object of child type of CimBase */
CimBase* CimBase_Create(size_t size)
{
    CimBase* cimbase;
    Batch *batch = Batch_New(BATCH_MAX_PAGES);
    if (NULL == batch)
    {
        LOGD_BATCH_CREATE_OOM;
        return NULL;
    }
    cimbase = (CimBase*)Batch_GetClear(batch, size);
    if (NULL == cimbase)
    {
        LOGD_BATCH_OOM;
        Batch_Delete(batch);
        return NULL;
    }
    cimbase->_ft = &g_cimbaseft;
    cimbase->batch = batch;
    return cimbase;
}

const MI_Char* CimBase_GetName(CimBase* self)
{
    DEBUG_ASSERT(self);
    return self->identifier;
}


#ifdef _PREFAST_
#pragma prefast(push)
#pragma prefast (disable: 22102)
#endif

/* Get id from an integer */
_Use_decl_annotations_
MI_Char* GetID(MI_Uint32 id, const MI_Char* base, Batch* batch)
{
    DEBUG_ASSERT(base);
    DEBUG_ASSERT(batch);
    {
        /* Maximum id is 4294967296, length of 10 */
        size_t baselen = Tcslen(base);
        size_t len = baselen + 10 + 1;
        MI_Uint32 tid = id;
        size_t idlen = 0;
        size_t i;
        MI_Char idbuf[10];
        MI_Char* buf = (MI_Char*)Batch_GetClear(batch, len * sizeof(MI_Char));
        if (NULL == buf)
        {
            LOGD_BATCH_OOM;
            return NULL;
        }
        /* NOTE: Szprintf has worse performance */
        Tcslcpy(buf, base, baselen + 1);
        while (tid > 0)
        {
            idbuf[idlen ++] = (tid % 10) + '0';
            tid = tid / 10;
        }
        if (idlen == 0)
        {
            idbuf[idlen ++] = '0';
        }
        for (i = idlen; i > 0; i--)
        {
            buf[baselen++] = idbuf[i - 1];
        }
        buf[baselen] = 0;
        return buf;
    }
}

/* Get reference count */
int CimBase_GetRefcount(_In_ CimBase *self)
{
    DEBUG_ASSERT(self);
    return (int)self->refcounter;
}

/* Set function table */
int CimBase_Set_FT(_Inout_ CimBase *self, _In_ CimBaseFT *ft)
{
    DEBUG_ASSERT(self);
    self->_ft = ft;
    return 0;
}

/* Set magic number */
int CimBase_Set_Magic(_Inout_ CimBase *self, _In_ MI_Uint32 magic)
{
    DEBUG_ASSERT(self);
    self->_magic = magic;
    return 0;
}

_Use_decl_annotations_
void ErrorHandler_SetLastError(
    ErrorHandler * handler,
    MI_Instance* error,
    MI_Result result)
{
    DEBUG_ASSERT(handler);
    DEBUG_ASSERT(handler->setlasterror);
    handler->setlasterror(handler->context, error, result);
}

#ifdef _PREFAST_
#pragma prefast(pop)
#endif

