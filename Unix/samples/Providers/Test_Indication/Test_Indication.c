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
#include "Test_Indication.h"
#include "impl.h"

static MI_Result MI_CALL _SetIndicationProperties_Impl(
    _In_ void* cfg,
    _Outptr_ MI_Instance** indication)
{
    MI_Result r = MI_RESULT_OK;
    Config* config = (Config*)cfg;
    DEBUG_ASSERT (indication);
    *indication = NULL;
    {
        MI_Boolean match;
        Test_Indication* inst;
        MI_Uint32 arrayLength = (rand() % 30) + 1;
        MI_Boolean* boolArray = NULL;
        MI_Uint8* byteArray = NULL;
        MI_Datetime now = GetCurrentTimestamp();
        Test_Class embeddedInstance;
        Test_Class** embeddedInstanceArray = NULL;
        MI_Instance* embeddedObject = NULL;
        MI_Instance** embeddedObjectArray = NULL;
        MI_Uint32 i;
        MI_Value val;

        MI_Context* context = config->postctx;
        r = MI_Context_NewInstance(context, &Test_Indication_rtti, indication);
        CHKMIRESULTRETURN(r, "MI_Context_NewInstance failed");

        inst = (Test_Indication*) (*indication);

        r = Test_Indication_Set_message(inst, MI_T("test indication message"));
        CHKSETPROPERTY(r, "message");
        r = Test_Indication_Set_id(inst, config->count);
        CHKSETPROPERTY(r, "id");
        r = Test_Indication_Set_suint8(inst, 8);
        CHKSETPROPERTY(r, "suint8");
        
        boolArray = (MI_Boolean*)PAL_Malloc(arrayLength * sizeof(MI_Boolean));
        ONNULLGOTO(boolArray, "boolArray", SetIndicationCleanup);
        for (i = 0; i < arrayLength; i++)
        {
            boolArray[i] = rand() % 2;
        }
        r = Test_Indication_Set_a_bool(inst, boolArray, arrayLength);
        CHKSETPROPERTYGOTO(r, "a_bool", SetIndicationCleanup);

        byteArray = (MI_Uint8*)PAL_Malloc(arrayLength * sizeof(MI_Uint8));
        ONNULLGOTO(byteArray, "byteArray", SetIndicationCleanup);
        for (i = 0; i < arrayLength; i++)
        {
            byteArray[i] = rand() % UCHAR_MAX;
        }
        r = Test_Indication_Set_a_octetBytes(inst, byteArray, arrayLength);
        CHKSETPROPERTYGOTO(r, "a_octetBytes", SetIndicationCleanup);

        r = Test_Indication_Set_sbool(inst, rand() % 2);
        CHKSETPROPERTYGOTO(r, "sbool", SetIndicationCleanup);

        r = Test_Indication_Set_sDATETIME(inst, now);
        CHKSETPROPERTYGOTO(r, "sDatetime", SetIndicationCleanup);

        Test_Class_Construct(&embeddedInstance, config->postctx);
        Test_Class_Set_key(&embeddedInstance, MI_T("embeddedInstanceKey0"));
        r = Test_Indication_Set_embeddedinstance(inst, &embeddedInstance);
        CHKSETPROPERTYGOTO(r, "embeddedInstance", SetIndicationCleanup);

        embeddedInstanceArray = (Test_Class**)PAL_Malloc(sizeof(Test_Class*) * arrayLength);
        ONNULLGOTO(embeddedInstanceArray, "embeddedInstanceArray", SetIndicationCleanup);
        for (i = 0; i < arrayLength; i++)
        {
            embeddedInstanceArray[i] = NULL;
            Test_Class_Clone(&embeddedInstance, &embeddedInstanceArray[i]);
        }
        r = Test_Indication_Set_embeddedinstancearray(inst, (const Test_Class* const*)embeddedInstanceArray, arrayLength);
        CHKSETPROPERTYGOTO(r, "embeddedInstanceArray", SetIndicationCleanup);

        MI_Context_NewDynamicInstance(config->postctx, MI_T("IndicationEmbeddedObject"), 0, &embeddedObject);
        val.uint8a.data = byteArray;
        val.uint8a.size = arrayLength;
        r = MI_Instance_AddElement(embeddedObject, MI_T("a_uint8"), &val, MI_UINT8A, 0);
        CHKSETPROPERTYGOTO(r, "a_uint8", SetIndicationCleanup);
        r = Test_Indication_Set_embeddedobject(inst, embeddedObject);
        CHKSETPROPERTYGOTO(r, "embeddedObject", SetIndicationCleanup);

        embeddedObjectArray = (MI_Instance**)PAL_Malloc(sizeof(MI_Instance*) * arrayLength);
        ONNULLGOTO(embeddedObjectArray, "embeddedObjectArray", SetIndicationCleanup);
        for (i = 0; i < arrayLength; i++)
        {
            embeddedObjectArray[i] = NULL;
            MI_Instance_Clone(embeddedObject, &(embeddedObjectArray[i]));
        }
        r = Test_Indication_Set_embeddedobjectarray(inst, (const MI_Instance* const*)embeddedObjectArray, arrayLength);
        CHKSETPROPERTYGOTO(r, "embeddedObjectArray", SetIndicationCleanup);

        r = class_TestFilter(config, &inst->__instance, &match);
        if (r == MI_RESULT_OK)
        {
            if (match == MI_FALSE)
            {
                LOGMSG(("Indication does not match filter"));
            }
        }

SetIndicationCleanup:
        FREE(boolArray);
        FREE(byteArray);

        if (embeddedInstanceArray)
        {
            for (i = 0; i < arrayLength; i++)
            {
                if (embeddedInstanceArray[i])
                {
                    Test_Class_Delete(embeddedInstanceArray[i]);
                }
            }
            FREE(embeddedInstanceArray);
        }

        Test_Class_Destruct(&embeddedInstance);

        if (embeddedObjectArray)
        {
            for (i = 0; i < arrayLength; i++)
            {
                if (embeddedObjectArray[i])
                {
                    MI_Instance_Delete(embeddedObjectArray[i]);
                }
            }
            FREE(embeddedObjectArray);
        }
        MI_Instance_Delete(embeddedObject);
    }

    return r;
}

static MI_Result MI_CALL _SetIndicationProperties(
    _In_ void* cfg,
    _Outptr_ MI_Instance** indication)
{
    MI_Result r = _SetIndicationProperties_Impl(cfg, indication);
    if (r != MI_RESULT_OK)
    {
        if (*indication)
            MI_Instance_Delete(*indication);
    }
    return r;
}

void MI_CALL Test_Indication_Load(
    Test_Indication_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r;
    *self = NULL;
    r = class_Load((void**)self, &cfgTest_Indication, _SetIndicationProperties);
    MI_PostResult(context, r);
}

void MI_CALL Test_Indication_Unload(
    Test_Indication_Self* self,
    MI_Context* context)
{
    MI_Result r = class_Unload((void*)self, &cfgTest_Indication);
    MI_PostResult(context, r);
}

void MI_CALL Test_Indication_EnableIndications(
    Test_Indication_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    /* TODO: store indicationsContext for posting indication usage */
    /* NOTE:Call one of following functions if and ONLY if encount termination error,
            which will finalize the indicationsContext, 
            and terminate all active subscriptions to current class,
             MI_Context_PostResult
             MI_Context_PostError
             MI_Context_PostCimError
            */
    MI_Result r = class_EnableIndications((void*)self, indicationsContext, &cfgTest_Indication, nameSpace, className);
    if (r != MI_RESULT_OK)
        MI_PostResult(indicationsContext, r);
}

void MI_CALL Test_Indication_DisableIndications(
    Test_Indication_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    MI_Result r = class_DisableIndications((void*)self, indicationsContext, &cfgTest_Indication, nameSpace, className);
    MI_PostResult(indicationsContext, r);
}

void MI_CALL Test_Indication_Subscribe(
    Test_Indication_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf)
{
    /* TODO: store the context for posting indication usage */
    /* NOTE:Call one of following functions if and ONLY if encount termination error,
            which will finalize the context, 
            and Unsubscribe function will not be invoked then,
             MI_Context_PostResult
             MI_Context_PostError
             MI_Context_PostCimError
            */
    MI_Result r = class_Subscribe((void*)self, context, &cfgTest_Indication, nameSpace, className, filter, bookmark, subscriptionID, subscriptionSelf);
    if (r != MI_RESULT_OK)
        MI_PostResult(context, r);
}

void MI_CALL Test_Indication_Unsubscribe(
    Test_Indication_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf)
{
    MI_Result r = class_Unsubscribe((void*)self, context, &cfgTest_Indication, nameSpace, className, subscriptionID, subscriptionSelf);
    MI_PostResult(context, r);
}
