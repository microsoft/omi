/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include "Perf_Indication.h"
#include "ProviderUtil.h"

struct _Perf_Indication_Self
{
    MI_Context* indicationContext;
    MI_Uint64 keyCounter;
    MI_Boolean shutdownCalled;
};

void MI_CALL Perf_Indication_Load(
    _Outptr_result_maybenull_ Perf_Indication_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);
    *self = new Perf_Indication_Self;
    (*self)->keyCounter = 0;    
    (*self)->shutdownCalled = MI_FALSE;

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_Indication_Unload(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* context)
{
    if (self)
    {
        self->keyCounter = 0;
        delete self;
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_Indication_EnableIndications(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* indicationsContext,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className)
{
}

void MI_CALL Perf_Indication_DisableIndications(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* indicationsContext,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className)
{
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_PostResult(indicationsContext, MI_RESULT_OK);
}

void MI_CALL Perf_Indication_Subscribe(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_Filter* filter,
    _In_opt_z_ const MI_Char* bookmark,
    _In_ MI_Uint64  subscriptionID,
    _Outptr_result_maybenull_ void** subscriptionSelf)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(context);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(filter);
    MI_UNREFERENCED_PARAMETER(bookmark);
    MI_UNREFERENCED_PARAMETER(subscriptionID);
    *subscriptionSelf = NULL;

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_Indication_Unsubscribe(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ MI_Uint64  subscriptionID,
    _In_opt_ void* subscriptionSelf)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(subscriptionID);
    MI_UNREFERENCED_PARAMETER(subscriptionSelf);

    MI_PostResult(context, MI_RESULT_OK);
}

