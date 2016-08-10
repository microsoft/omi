/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _impl_h
#define _impl_h

#include "fire.h"

MI_Result class_Load(
    void** classSelf,
    _In_ Config* config,
    _In_ SetupIndicationProperties setp);

MI_Result class_Unload(
    _In_ void* classSelf,
    _In_ Config* config);

MI_Result lifecycle_Load(
    _In_ Config* config, 
    _In_ MI_Instance* lifecycleInstance,
    _In_ MI_LifecycleIndicationCallback callback,
    _In_ MI_Context* context);

MI_Result lifecycle_Unload(
    _In_ Config* config);

MI_Result lifecycle_EnumerateInstances(
    _In_ Config* config);

MI_Result lifecycle_CreateInstance(
    _In_ Config* config,
    _In_ MI_Instance* instance);

MI_Result lifecycle_DeleteInstance(
    _In_ Config* config);

MI_Result lifecycle_ModifyInstance(
    _In_ MI_Instance* modifiedInstance,
    _In_ Config* config);

MI_Result lifecycle_ThreadControl(
    _Inout_ Config* config,
    _In_ MI_Uint32 operation);

MI_Result lifecycle_StartThread(
    _In_ Config* config);

MI_Result lifecycle_StopThread(
    _In_ Config* config);

MI_Result lifecycle_InvokeMethod(
    _In_ Config* config);

MI_Result lifecycle_AddEventToQueue(
    _In_ Config* config,
    _In_ MI_Uint32 eventType, 
    _In_ MI_Instance* sourceInstance,
    _In_ MI_Instance* previousInstance,
    _In_ MI_Instance* methodParam);

LifecycleEvent* lifecycle_RemoveEventFromQueue(
    _In_ Config* config);

MI_Result class_EnableIndications(
    _In_ void* classSelf,
    _In_ MI_Context* context,
    _In_ Config* config,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className);

MI_Result class_DisableIndications(
    _In_ void* classSelf,
    _In_ MI_Context* context,
    _In_ Config* config,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className);

MI_Result class_Subscribe(
    _In_ void* classSelf,
    _In_ MI_Context* context,
    _In_ Config* config,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className,
    _In_ const MI_Filter* filter,
    _In_opt_z_ const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf);

MI_Result class_Unsubscribe(
    _In_ void* classSelf,
    _In_ MI_Context* context,
    _In_ Config* config,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf);

MI_Result class_TestFilter(
    _In_ Config* config,
    _In_ MI_Instance* inst,
    _Out_ MI_Boolean* result);

MI_Datetime GetCurrentTimestamp();

#endif /* _impl_h_ */
