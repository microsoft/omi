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

#ifndef _omi_instance_h
#define _omi_instance_h

#include "config.h"
#include <common.h>
#include "atomic.h"
#include "batch.h"
#include "buf.h"

BEGIN_EXTERNC

/*
**==============================================================================
**
** Instance structure and related functions.
**
**==============================================================================
*/

/* Immediately precedes heap-allocated Instance structures */
typedef struct _InstanceHeader
{
    MI_Uint32 magic;
    union
    {
        AtomicInt refs;
        MI_Uint64 alignment;
    }
    u;
}
InstanceHeader;

typedef struct _Instance /* extends MI_Instance */
{
    /* Function table (inherited field) */
    MI_InstanceFT* ft;

    /* The class declaration for this instance (inherited field) */
    MI_ClassDecl* classDecl;

    /* The optional server name (inherited field) */
    ZChar* serverName;

    /* The optional namespace (inherited field) */
    ZChar* nameSpace;

    /* Allocator for this instance */
    Batch* batch;

    /* Points to this structure if static, other structure if dynamic. */
    struct _Instance* self;

    /* If true, instances releases batch upon destruction */
    MI_Boolean releaseBatch;
}
Instance;

MI_Result MI_CALL Instance_Construct(
    MI_Instance* self,
    const MI_ClassDecl* classDecl,
    Batch* batch);

MI_Result Instance_New(
    _Out_ MI_Instance** selfOut,
    _In_ const MI_ClassDecl* classDecl,
    _In_opt_ Batch* batch);

MI_Result MI_CALL Instance_NewDynamic(
    MI_Instance** self,
    const ZChar* className,
    MI_Uint32 metaType, /* MI_FLAG_(CLASS|ASSOCIATION|INDICATION|METHOD) */
    Batch* batch);

/* TODO: Set MI_ClassDecl.schema during generation; eliminate schemaDecl arg */
MI_Result MI_CALL Instance_InitConvert(
    _In_ MI_Instance* self,
    _In_ const MI_ClassDecl* classDecl,
    _In_ const MI_Instance* instance,
    MI_Boolean keysOnly,
    MI_Boolean allowKeylessInst,
    MI_Boolean copy,
    _In_opt_ Batch* batch);

MI_Result MI_CALL Instance_Clone(
    const MI_Instance* self,
    MI_Instance** inst,
    Batch* batch);

MI_Result MI_CALL Instance_SetClassName(
    MI_Instance* self,
    const ZChar* className);

MI_Result MI_CALL Instance_Print(
    const MI_Instance* self,
    FILE* os,
    MI_Uint32 level,
    MI_Boolean showNulls);

/* Return true if instances have exactly the same keys */
MI_Boolean Instance_MatchKeys(
    const MI_Instance* self,
    const MI_Instance* instance);

/*
**==============================================================================
**
** MI_Instance function table and functions
**
**==============================================================================
*/

void __MI_Instance_Ref(MI_Instance* self);

void __MI_Instance_Unref(MI_Instance* self);

MI_Result MI_CALL __MI_Instance_Clone(
    const MI_Instance* self,
    MI_Instance** inst);

MI_Result MI_CALL __MI_Instance_Destruct(
    MI_Instance* self);

MI_Result MI_CALL __MI_Instance_Delete(
    MI_Instance* self);

MI_Result MI_CALL __MI_Instance_IsA(
    const MI_Instance* self_,
    const MI_ClassDecl* classDecl,
    MI_Boolean* result);

MI_Result MI_CALL __MI_Instance_GetClassName(
    const MI_Instance* self_,
    const ZChar** classname);

MI_Result MI_CALL __MI_Instance_SetNameSpace(
    MI_Instance* self,
    const ZChar* nameSpace);

MI_Result MI_CALL __MI_Instance_GetNameSpace(
    const MI_Instance* self,
    const ZChar** nameSpace);

MI_Result MI_CALL __MI_Instance_GetElementCount(
    const MI_Instance* self,
    MI_Uint32* count);

MI_Result MI_CALL __MI_Instance_AddElement(
    MI_Instance* self,
    const ZChar* name,
    const MI_Value* value,
    MI_Type type,
    MI_Uint32 flags);

MI_Result MI_CALL __MI_Instance_SetElement(
    MI_Instance* self,
    const ZChar* name,
    const MI_Value* value,
    MI_Type type,
    MI_Uint32 flags);

MI_Result MI_CALL __MI_Instance_SetElementAt(
    MI_Instance* self,
    MI_Uint32 index,
    const MI_Value* value,
    MI_Type type,
    MI_Uint32 flags);

MI_Result MI_CALL __MI_Instance_GetElement(
    const MI_Instance* self,
    const ZChar* name,
    MI_Value* valueOut,
    MI_Type* typeOut,
    MI_Uint32* flagsOut,
    MI_Uint32* indexOut);

MI_Result MI_CALL __MI_Instance_GetElementAt(
    const MI_Instance* self,
    MI_Uint32 index,
    const ZChar** name,
    MI_Value* value,
    MI_Type* type,
    MI_Uint32* flags);

MI_Result MI_CALL __MI_Instance_ClearElement(
    MI_Instance* self_,
    const ZChar* name);

MI_Result MI_CALL __MI_Instance_ClearElementAt(
    MI_Instance* self,
    MI_Uint32 index);

extern MI_InstanceFT __mi_instanceFT;

END_EXTERNC

#endif /* _omi_instance_h */
