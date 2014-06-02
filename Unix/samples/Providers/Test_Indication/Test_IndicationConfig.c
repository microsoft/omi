/* @migen@ */
#include <MI.h>
#include "Test_IndicationConfig.h"
#include "fire.h"

#define CLASSCOUNT 12

Config* g_configarray[CLASSCOUNT] = {
    &cfgTest_Indication,
    &cfgL_IndicationC1,
    &cfgL_IndicationC2,
    &cfgL_IndicationC3,
    &cfgR_IndicationC1,
    &cfgR_IndicationC2,
    &cfgR_IndicationC3,
    &cfgTest_Class,
    &cfgL_LifecycleC1,
    &cfgL_LifecycleC2,
    &cfgR_LifecycleC1,
    &cfgR_LifecycleC2};

void MI_CALL Test_IndicationConfig_Load(
    Test_IndicationConfig_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_IndicationConfig_Unload(
    Test_IndicationConfig_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

static MI_Result _ConfigToInstance(
    _Inout_ Test_IndicationConfig * inst,
    _In_ Config* config)
{
    MI_Result r;
    MI_Char* tmpChar; 
    r = Test_IndicationConfig_Set_className(inst, ansiToMI(config->className));
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_configFilepath(inst, ansiToMI(config->configFilepath));
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_dialect(inst, ansiToMI(config->dialect));
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_evalResult(inst, config->evalResult);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_expression(inst, ansiToMI(config->expression));
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_failAfterCount(inst, config->failAfterCount);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_failResult(inst, config->failResult);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_finalizeBehavior(inst, config->finalizeBehavior);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_finalizeResultCode(inst, config->finalizeResultCode);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_initBehavior(inst, config->initBehavior);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_initResultCode(inst, config->initResultCode);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_initTimeoutMS(inst, config->initTimeoutMS);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_intervalMS(inst, config->intervalMS);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_miscTestSubGroup(inst, config->miscTestSubGroup);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_postBehavior(inst, config->postBehavior);
    if (r != MI_RESULT_OK) return r;
    tmpChar = ansiToMI(config->providerBookmark);
    if (tmpChar)
    {
        r = Test_IndicationConfig_Set_providerBookmark(inst, tmpChar);
        if (r != MI_RESULT_OK) return r;
    }
    tmpChar = ansiToMI(config->subscribeBookmark);
    if (tmpChar)
    {
        r = Test_IndicationConfig_Set_subscribeBookmark(inst, tmpChar);
        if (r != MI_RESULT_OK) return r;
    }
    r = Test_IndicationConfig_Set_testGroup(inst, config->testGroup);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_logLoadUnloadCall(inst, config->logLoadUnloadCall);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_currentSubscriptionTypes(inst, config->currentSubscriptionTypes);
    if (r != MI_RESULT_OK) return r;
    r = Test_IndicationConfig_Set_supportedSubscriptionTypes(inst, config->supportedSubscriptionTypes);
    if (r != MI_RESULT_OK) return r;

    if (config->apicallseqcount > 0)
    {

        MI_Char** data = (MI_Char**)Batch_Get(g_batch, sizeof(MI_Char*) * config->apicallseqcount);
        if (data)
        {
            MI_Uint32 i;
            for (i = 0; i < config->apicallseqcount; i++)
                data[i] = ansiToMI(config->apicallseq[i]);
            r = Test_IndicationConfig_SetPtr_apicallseq(inst, (const MI_Char**)data, config->apicallseqcount);
        }
    }
    return r;
}

static MI_Result _InstanceToConfig(
    _In_ const Test_IndicationConfig * inst,
    _Inout_ Config* config)
{
    MI_Result r = MI_RESULT_OK;
    if (inst->dialect.exists)
        config->dialect = MIToansi(inst->dialect.value);
    if (inst->evalResult.exists)
        config->evalResult = inst->evalResult.value;
    if (inst->expression.exists)
        config->expression = MIToansi(inst->expression.value);
    if (inst->failAfterCount.exists)
        config->failAfterCount = inst->failAfterCount.value;
    if (inst->failResult.exists)
        config->failResult = (MI_Result)inst->failResult.value;
    if (inst->finalizeBehavior.exists)
        config->finalizeBehavior = inst->finalizeBehavior.value;
    if (inst->finalizeResultCode.exists)
        config->finalizeResultCode = (MI_Result)(inst->finalizeResultCode.value);
    if (inst->initBehavior.exists)
        config->initBehavior = inst->initBehavior.value;
    if (inst->initResultCode.exists)
        config->initResultCode = (MI_Result)(inst->initResultCode.value);
    if (inst->initTimeoutMS.exists)
        config->initTimeoutMS = inst->initTimeoutMS.value;
    if (inst->intervalMS.exists)
        config->intervalMS = inst->intervalMS.value;
    if (inst->miscTestSubGroup.exists)
        config->miscTestSubGroup = (inst->miscTestSubGroup.value);
    if (inst->postBehavior.exists)
        config->postBehavior = (inst->postBehavior.value);
    if (inst->providerBookmark.exists)
        config->providerBookmark = MIToansi(inst->providerBookmark.value);
    if (inst->subscribeBookmark.exists)
        config->subscribeBookmark = MIToansi(inst->subscribeBookmark.value);
    if (inst->testGroup.exists)
        config->testGroup = (inst->testGroup.value);
    if (inst->logLoadUnloadCall.exists)
        config->logLoadUnloadCall = (inst->logLoadUnloadCall.value);
    if (inst->currentSubscriptionTypes.exists)
        config->currentSubscriptionTypes = (inst->currentSubscriptionTypes.value);
    if (inst->supportedSubscriptionTypes.exists)
        config->supportedSubscriptionTypes = (inst->supportedSubscriptionTypes.value);
    return r;
}


void MI_CALL Test_IndicationConfig_EnumerateInstances(
    Test_IndicationConfig_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result r = MI_RESULT_OK;
    Test_IndicationConfig config;
    MI_Uint32 i;
    LOGMSG(("Test_IndicationConfig_EnumerateInstances: started"));
    ReloadConfig();
    for (i = 0; i < CLASSCOUNT; i++)
    {
        MI_Result r = Test_IndicationConfig_Construct(&config, context);
        if (r != MI_RESULT_OK) break;
        r = _ConfigToInstance(&config, g_configarray[i]);
        if (r != MI_RESULT_OK) break;
        r = Test_IndicationConfig_Post(&config, context);
        if (r != MI_RESULT_OK) break;
        Test_IndicationConfig_Destruct(&config);
    }
    LOGMSG(("Test_IndicationConfig_EnumerateInstances: result (%d)", r));
    MI_PostResult(context, r);
}

void MI_CALL Test_IndicationConfig_GetInstance(
    Test_IndicationConfig_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_IndicationConfig* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_Result r = MI_RESULT_NOT_FOUND;
    Test_IndicationConfig config;
    MI_Uint32 i;
    if (!instanceName->className.exists)
    {
        r = MI_RESULT_INVALID_PARAMETER;
    }
    else
    {
        ReloadConfig();
        LOGMSG(("Test_IndicationConfig_GetInstance: started, classname(%s)", MIToansi(instanceName->className.value)));
        for (i = 0; i < CLASSCOUNT; i++)
        {
            if (StringCompare(instanceName->className.value, ansiToMI(g_configarray[i]->className)) == 0)
            {
                r = Test_IndicationConfig_Construct(&config, context);
                if (r != MI_RESULT_OK) break;
                r = _ConfigToInstance(&config, g_configarray[i]);
                if (r != MI_RESULT_OK) break;
                r = Test_IndicationConfig_Post(&config, context);
                if (r != MI_RESULT_OK) break;
                Test_IndicationConfig_Destruct(&config);
                break;
            }
        }
    }
    LOGMSG(("Test_IndicationConfig_GetInstance: result (%d)", r));
    MI_PostResult(context, r);
}

void MI_CALL Test_IndicationConfig_CreateInstance(
    Test_IndicationConfig_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_IndicationConfig* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Test_IndicationConfig_ModifyInstance(
    Test_IndicationConfig_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_IndicationConfig* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_Result r = MI_RESULT_NOT_FOUND;
    MI_Uint32 i;
    /* TODO: OMI server require send an instance back, to be removed when the issue get fixed */
    Test_IndicationConfig config;
    if (!modifiedInstance->className.exists)
    {
        r = MI_RESULT_INVALID_PARAMETER;
    }
    else
    {
        LOGMSG(("Test_IndicationConfig_ModifyInstance: started, classname(%s)", MIToansi(modifiedInstance->className.value)));
        for (i = 0; i < CLASSCOUNT; i++)
        {
            if (StringCompare(modifiedInstance->className.value, ansiToMI(g_configarray[i]->className)) == 0)
            {
                r = _InstanceToConfig(modifiedInstance, g_configarray[i]);
                if (r == MI_RESULT_OK)
                {
                    writeconfig(g_configarray[i]);
                    r = Test_IndicationConfig_Construct(&config, context);
                    if (r != MI_RESULT_OK) break;
                    r = _ConfigToInstance(&config, g_configarray[i]);
                    if (r != MI_RESULT_OK)
                    {
                        Test_IndicationConfig_Destruct(&config);
                        break;
                    }
                    r = Test_IndicationConfig_Post(&config, context);
                    Test_IndicationConfig_Destruct(&config);
                    if (r == MI_RESULT_OK)
                    {
                        /* reset config properties */
                        readconfig(g_configarray[i]->className, g_configarray[i]);
                        g_configarray[i]->filter = NULL;
                    }
                    LOGMSG(("Test_IndicationConfig_ModifyInstance: write config file for class (%s)", g_configarray[i]->className));
                }
                break;
            }
        }
    }
    LOGMSG(("Test_IndicationConfig_ModifyInstance: result (%d)", r));
    MI_PostResult(context, r);
}

void MI_CALL Test_IndicationConfig_DeleteInstance(
    Test_IndicationConfig_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_IndicationConfig* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}
