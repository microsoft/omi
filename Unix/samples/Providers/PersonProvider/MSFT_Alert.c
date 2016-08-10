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
#include "MSFT_Alert.h"

void MI_CALL MSFT_Alert_Load(
    MSFT_Alert_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_Alert_Unload(
    MSFT_Alert_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_Alert_EnableIndications(
    MSFT_Alert_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    /* TODO: store indicationsContext for later usage */
    /* NOTE: Do not call MI_PostResult on this context */
}

void MI_CALL MSFT_Alert_DisableIndications(
    MSFT_Alert_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    /* TODO: stop background thread that monitors subscriptions */

    MI_PostResult(indicationsContext, MI_RESULT_OK);
}

void MI_CALL MSFT_Alert_Subscribe(
    MSFT_Alert_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_Alert_Unsubscribe(
    MSFT_Alert_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

