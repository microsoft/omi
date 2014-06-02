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

#ifndef _indication_indimgr_cimbase_h
#define _indication_indimgr_cimbase_h

#include <common.h>
#include <pal/atomic.h>
#include <base/batch.h>

BEGIN_EXTERNC

typedef struct _CimBase CimBase;

/* Add reference */
typedef int (*AddRefFunc)(_Inout_ CimBase *self);
/* Release reference */
typedef int (*ReleaseFunc)(_Inout_ CimBase *self);
/* Finalize resources */
typedef void (*OnFinalizeFunc)(_Inout_ CimBase *self);
/* Called upon adding to a container */
typedef int (*OnAddFunc)(_Inout_ CimBase *self, _In_ void* container);
/* Called upon removing from a container */
typedef int (*OnRemoveFunc)(_Inout_ CimBase *self, _In_ void* container);
/* Create identifier of current object */
typedef MI_Char* (*CreateIdentifierFunc)(_In_ CimBase *self);

/*
**==============================================================================
**
** Defines function table that perform lifecycle management of all 3 types
** objects, filter, listener, and subscription.
**
**==============================================================================
*/
typedef struct _CimBaseFT
{
    AddRefFunc addref; /* Add reference count */
    ReleaseFunc release; /* Release reference count */
    OnFinalizeFunc finalize; /* Finalization of current object */
    OnAddFunc onadd; /* When is being added to IndicationManager */
    OnRemoveFunc onremove; /* When is being removed from IndicationManager */
    CreateIdentifierFunc createid; /* Create a new id for the object */
}CimBaseFT;

/*
**==============================================================================
**
** Represents a base strucutre for filter, hanlder, and subscription.
**
**==============================================================================
*/
struct _CimBase
{
    struct _CimBase* next;  /* Next item in the list, used by IndicationManager */
    struct _CimBase* prev;  /* Previous item in the list, used by IndicationManager */

    CimBaseFT * _ft;        /* Function table */
    MI_Uint32 _magic;       /* Validation purpose */

    void* _container;       /* Container object who cached this object */
    volatile ptrdiff_t refcounter;   /* Reference count */
    MI_Instance* inst;      /* CIM instance associated with the object */
    Batch *batch;           /* Batch allocator for current object */
    MI_Char *identifier;    /* Unique identifier of the object */
};

extern CimBaseFT g_cimbaseft;

/* Create an child object of CimBase */
CimBase* CimBase_Create(size_t size);

/* Add reference */
int CimBase_AddRef(_Inout_ CimBase *self);

/* Release reference */
int CimBase_Release(_Inout_ CimBase *self);

/* Release reference on the whole list starting from self */
int CimBase_ReleaseList(_Inout_ CimBase *self);

/* Add to container callback */
int CimBase_OnAdd(_Inout_ CimBase *self, _In_ void* container);

/* Remove from container callback */
int CimBase_OnRemove(_Inout_ CimBase *self, _In_ void* container);

/* Get id from an integer */
MI_Char* GetID(MI_Uint32 id, _In_z_ const MI_Char* base, _In_ Batch* batch);

/* Get reference count, for test purpose */
int CimBase_GetRefcount(_In_ CimBase *self);

/* Set function table */
int CimBase_Set_FT(_Inout_ CimBase *self, _In_ CimBaseFT *ft);

/* Set magic number */
int CimBase_Set_Magic(_Inout_ CimBase *self, _In_ MI_Uint32 magic);


/*
**==============================================================================
**
** Error handling structure and helpers
**
**==============================================================================
*/
/* Set last error  */
typedef void (*SetLastErrorFunc)(
    _In_opt_ void* context,
    _In_opt_ MI_Instance* error, MI_Result result);

typedef struct _ErrorHandler ErrorHandler;
struct _ErrorHandler
{
    SetLastErrorFunc setlasterror;
    void* context;
};

void ErrorHandler_SetLastError(_In_ ErrorHandler * handler,
    _In_opt_ MI_Instance* error, MI_Result result);

END_EXTERNC

#endif /* _indication_indimgr_cimbase_h */
