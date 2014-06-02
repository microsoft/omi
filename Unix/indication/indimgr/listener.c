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

#include <indication/common/indilog.h>
#include "listener.h"

const MI_Uint32 g_ListenerMagic = 0xF11EE1FF;
MI_Uint32 g_ListenerTempID = 1;

void Listener_Finalize(CimBase *self)
{
    DEBUG_ASSERT(self);
    trace_FunctionEntered(__FILE__, __LINE__);
    return;
}

/* Create identifier of current object */
MI_Char* CreateListenerIdentifier(_In_ CimBase *self)
{
    DEBUG_ASSERT(self);
    if (self->_magic != g_ListenerMagic)
    {
        trace_ObjectIsnotValidListener(self);
        return NULL;
    }
    return GetID(g_ListenerTempID++, TEMP_LISTENER_ID_PREFIX, self->batch);;
}

CimBaseFT g_listenerft =
{
    CimBase_AddRef,
    CimBase_Release,
    Listener_Finalize,
    CimBase_OnAdd,
    CimBase_OnRemove,
    CreateListenerIdentifier,
};

Listener* Listener_New(PersistenceType type)
{
    Listener* listener = NULL;
    listener = (Listener*)CimBase_Create(sizeof(Listener));
    if (NULL == listener)
    {
        LOGD_BATCH_OOM;
        return NULL;
    }
    listener->PersistenceType = type;
    CimBase_Set_Magic(&listener->base, g_ListenerMagic);
    CimBase_Set_FT(&listener->base, &g_listenerft);

    Listener_AddRef(listener);
    return listener;
}

/* Add a reference to a Listener object */
_Use_decl_annotations_
int Listener_AddRef(Listener* self)
{
    DEBUG_ASSERT(self);
    return self->base._ft->addref((CimBase*)self);
}

/* Release a reference to a Listener object */
_Use_decl_annotations_
int Listener_Release(Listener* self)
{
    DEBUG_ASSERT(self);
    return self->base._ft->release((CimBase*)self);
}

/* Get reference count */
int Listener_GetRefcount(_In_ Listener *self)
{
    DEBUG_ASSERT(self);
    return CimBase_GetRefcount((CimBase*)self);
}

