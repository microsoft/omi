/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#include <MI.h>
#include "module.h"
#include "X_SmallNumber_Class_Provider.h"
#include "X_HugeNumber_Class_Provider.h"
#include "X_NumberWorld_Class_Provider.h"
#include "X_HugeNumbers_Class_Provider.h"
#include "X_OddSmallNumbers_Class_Provider.h"
#include "X_EvenSmallNumbers_Class_Provider.h"
#include "X_Halves_Class_Provider.h"
#include "X_Profile_Class_Provider.h"
#include "X_HugeNumberConformsToProfile_Class_Provider.h"
#include "X_NumberWorldConformsToProfile_Class_Provider.h"
#include "X_Number1000001_Class_Provider.h"
#include "X_Cat_Class_Provider.h"
#include "X_Dog_Class_Provider.h"
#include "X_HTTPHeader_Class_Provider.h"

using namespace mi;

MI_EXTERN_C void MI_CALL X_SmallNumber_Load(
    X_SmallNumber_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_SmallNumber_Class_Provider* prov = new X_SmallNumber_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_SmallNumber_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_SmallNumber_Unload(
    X_SmallNumber_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_SmallNumber_Class_Provider* prov = (X_SmallNumber_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_SmallNumber_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_SmallNumber_EnumerateInstances(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_SmallNumber_Class_Provider* cxxSelf =((X_SmallNumber_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_SmallNumber_GetInstance(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SmallNumber* instanceName,
    const MI_PropertySet* propertySet)
{
    X_SmallNumber_Class_Provider* cxxSelf =((X_SmallNumber_Class_Provider*)self);
    Context  cxxContext(context);
    X_SmallNumber_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_SmallNumber_CreateInstance(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SmallNumber* newInstance)
{
    X_SmallNumber_Class_Provider* cxxSelf =((X_SmallNumber_Class_Provider*)self);
    Context  cxxContext(context);
    X_SmallNumber_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_SmallNumber_ModifyInstance(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SmallNumber* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_SmallNumber_Class_Provider* cxxSelf =((X_SmallNumber_Class_Provider*)self);
    Context  cxxContext(context);
    X_SmallNumber_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_SmallNumber_DeleteInstance(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SmallNumber* instanceName)
{
    X_SmallNumber_Class_Provider* cxxSelf =((X_SmallNumber_Class_Provider*)self);
    Context  cxxContext(context);
    X_SmallNumber_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_SmallNumber_Invoke_SpellNumber(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_SmallNumber* instanceName,
    const X_SmallNumber_SpellNumber* in)
{
    X_SmallNumber_Class_Provider* cxxSelf =((X_SmallNumber_Class_Provider*)self);
    X_SmallNumber_Class instance(instanceName, false);
    Context  cxxContext(context);
    X_SmallNumber_SpellNumber_Class param(in, false);

    cxxSelf->Invoke_SpellNumber(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL X_SmallNumber_Invoke_GetFactors(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_SmallNumber* instanceName,
    const X_SmallNumber_GetFactors* in)
{
    X_SmallNumber_Class_Provider* cxxSelf =((X_SmallNumber_Class_Provider*)self);
    X_SmallNumber_Class instance(instanceName, false);
    Context  cxxContext(context);
    X_SmallNumber_GetFactors_Class param(in, false);

    cxxSelf->Invoke_GetFactors(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL X_HugeNumber_Load(
    X_HugeNumber_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_HugeNumber_Class_Provider* prov = new X_HugeNumber_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_HugeNumber_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_HugeNumber_Unload(
    X_HugeNumber_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_HugeNumber_Class_Provider* prov = (X_HugeNumber_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_HugeNumber_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_HugeNumber_EnumerateInstances(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_HugeNumber_Class_Provider* cxxSelf =((X_HugeNumber_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_HugeNumber_GetInstance(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumber* instanceName,
    const MI_PropertySet* propertySet)
{
    X_HugeNumber_Class_Provider* cxxSelf =((X_HugeNumber_Class_Provider*)self);
    Context  cxxContext(context);
    X_HugeNumber_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_HugeNumber_CreateInstance(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumber* newInstance)
{
    X_HugeNumber_Class_Provider* cxxSelf =((X_HugeNumber_Class_Provider*)self);
    Context  cxxContext(context);
    X_HugeNumber_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_HugeNumber_ModifyInstance(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumber* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_HugeNumber_Class_Provider* cxxSelf =((X_HugeNumber_Class_Provider*)self);
    Context  cxxContext(context);
    X_HugeNumber_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_HugeNumber_DeleteInstance(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumber* instanceName)
{
    X_HugeNumber_Class_Provider* cxxSelf =((X_HugeNumber_Class_Provider*)self);
    Context  cxxContext(context);
    X_HugeNumber_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_HugeNumber_Invoke_SpellMagnitude(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_HugeNumber* instanceName,
    const X_HugeNumber_SpellMagnitude* in)
{
    X_HugeNumber_Class_Provider* cxxSelf =((X_HugeNumber_Class_Provider*)self);
    X_HugeNumber_Class instance(instanceName, false);
    Context  cxxContext(context);
    X_HugeNumber_SpellMagnitude_Class param(in, false);

    cxxSelf->Invoke_SpellMagnitude(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL X_HugeNumber_Invoke_TestEmbedded(
    X_HugeNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_HugeNumber* instanceName,
    const X_HugeNumber_TestEmbedded* in)
{
    X_HugeNumber_Class_Provider* cxxSelf =((X_HugeNumber_Class_Provider*)self);
    X_HugeNumber_Class instance(instanceName, false);
    Context  cxxContext(context);
    X_HugeNumber_TestEmbedded_Class param(in, false);

    cxxSelf->Invoke_TestEmbedded(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL X_NumberWorld_Load(
    X_NumberWorld_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_NumberWorld_Class_Provider* prov = new X_NumberWorld_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_NumberWorld_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_NumberWorld_Unload(
    X_NumberWorld_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_NumberWorld_Class_Provider* prov = (X_NumberWorld_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_NumberWorld_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_NumberWorld_EnumerateInstances(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_NumberWorld_Class_Provider* cxxSelf =((X_NumberWorld_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_NumberWorld_GetInstance(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorld* instanceName,
    const MI_PropertySet* propertySet)
{
    X_NumberWorld_Class_Provider* cxxSelf =((X_NumberWorld_Class_Provider*)self);
    Context  cxxContext(context);
    X_NumberWorld_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_NumberWorld_CreateInstance(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorld* newInstance)
{
    X_NumberWorld_Class_Provider* cxxSelf =((X_NumberWorld_Class_Provider*)self);
    Context  cxxContext(context);
    X_NumberWorld_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_NumberWorld_ModifyInstance(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorld* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_NumberWorld_Class_Provider* cxxSelf =((X_NumberWorld_Class_Provider*)self);
    Context  cxxContext(context);
    X_NumberWorld_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_NumberWorld_DeleteInstance(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorld* instanceName)
{
    X_NumberWorld_Class_Provider* cxxSelf =((X_NumberWorld_Class_Provider*)self);
    Context  cxxContext(context);
    X_NumberWorld_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_NumberWorld_Invoke_Terminate(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_NumberWorld* instanceName,
    const X_NumberWorld_Terminate* in)
{
    X_NumberWorld_Class_Provider* cxxSelf =((X_NumberWorld_Class_Provider*)self);
    X_NumberWorld_Class instance(instanceName, false);
    Context  cxxContext(context);
    X_NumberWorld_Terminate_Class param(in, false);

    cxxSelf->Invoke_Terminate(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL X_NumberWorld_Invoke_ReturnNamespace(
    X_NumberWorld_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_NumberWorld* instanceName,
    const X_NumberWorld_ReturnNamespace* in)
{
    X_NumberWorld_Class_Provider* cxxSelf =((X_NumberWorld_Class_Provider*)self);
    X_NumberWorld_Class instance(instanceName, false);
    Context  cxxContext(context);
    X_NumberWorld_ReturnNamespace_Class param(in, false);

    cxxSelf->Invoke_ReturnNamespace(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL X_HugeNumbers_Load(
    X_HugeNumbers_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_HugeNumbers_Class_Provider* prov = new X_HugeNumbers_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_HugeNumbers_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_HugeNumbers_Unload(
    X_HugeNumbers_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_HugeNumbers_Class_Provider* prov = (X_HugeNumbers_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_HugeNumbers_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_HugeNumbers_EnumerateInstances(
    X_HugeNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_HugeNumbers_Class_Provider* cxxSelf =((X_HugeNumbers_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_HugeNumbers_GetInstance(
    X_HugeNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumbers* instanceName,
    const MI_PropertySet* propertySet)
{
    X_HugeNumbers_Class_Provider* cxxSelf =((X_HugeNumbers_Class_Provider*)self);
    Context  cxxContext(context);
    X_HugeNumbers_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_HugeNumbers_CreateInstance(
    X_HugeNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumbers* newInstance)
{
    X_HugeNumbers_Class_Provider* cxxSelf =((X_HugeNumbers_Class_Provider*)self);
    Context  cxxContext(context);
    X_HugeNumbers_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_HugeNumbers_ModifyInstance(
    X_HugeNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumbers* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_HugeNumbers_Class_Provider* cxxSelf =((X_HugeNumbers_Class_Provider*)self);
    Context  cxxContext(context);
    X_HugeNumbers_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_HugeNumbers_DeleteInstance(
    X_HugeNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumbers* instanceName)
{
    X_HugeNumbers_Class_Provider* cxxSelf =((X_HugeNumbers_Class_Provider*)self);
    Context  cxxContext(context);
    X_HugeNumbers_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_HugeNumbers_AssociatorInstances(
    X_HugeNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_HugeNumbers_Class_Provider* cxxSelf =((X_HugeNumbers_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->AssociatorInstances(
        cxxContext,
        nameSpace,
        instanceName,
        resultClass,
        role,
        resultRole,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_HugeNumbers_ReferenceInstances(
    X_HugeNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_HugeNumbers_Class_Provider* cxxSelf =((X_HugeNumbers_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstances(
        cxxContext,
        nameSpace,
        instanceName,
        role,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_Load(
    X_OddSmallNumbers_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_OddSmallNumbers_Class_Provider* prov = new X_OddSmallNumbers_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_OddSmallNumbers_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_Unload(
    X_OddSmallNumbers_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_OddSmallNumbers_Class_Provider* prov = (X_OddSmallNumbers_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_OddSmallNumbers_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_EnumerateInstances(
    X_OddSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_OddSmallNumbers_Class_Provider* cxxSelf =((X_OddSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_GetInstance(
    X_OddSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_OddSmallNumbers* instanceName,
    const MI_PropertySet* propertySet)
{
    X_OddSmallNumbers_Class_Provider* cxxSelf =((X_OddSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);
    X_OddSmallNumbers_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_CreateInstance(
    X_OddSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_OddSmallNumbers* newInstance)
{
    X_OddSmallNumbers_Class_Provider* cxxSelf =((X_OddSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);
    X_OddSmallNumbers_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_ModifyInstance(
    X_OddSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_OddSmallNumbers* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_OddSmallNumbers_Class_Provider* cxxSelf =((X_OddSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);
    X_OddSmallNumbers_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_DeleteInstance(
    X_OddSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_OddSmallNumbers* instanceName)
{
    X_OddSmallNumbers_Class_Provider* cxxSelf =((X_OddSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);
    X_OddSmallNumbers_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_AssociatorInstances(
    X_OddSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_OddSmallNumbers_Class_Provider* cxxSelf =((X_OddSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->AssociatorInstances(
        cxxContext,
        nameSpace,
        instanceName,
        resultClass,
        role,
        resultRole,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_OddSmallNumbers_ReferenceInstances(
    X_OddSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_OddSmallNumbers_Class_Provider* cxxSelf =((X_OddSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstances(
        cxxContext,
        nameSpace,
        instanceName,
        role,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_Load(
    X_EvenSmallNumbers_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_EvenSmallNumbers_Class_Provider* prov = new X_EvenSmallNumbers_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_EvenSmallNumbers_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_Unload(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_EvenSmallNumbers_Class_Provider* prov = (X_EvenSmallNumbers_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_EvenSmallNumbers_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_EnumerateInstances(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_EvenSmallNumbers_Class_Provider* cxxSelf =((X_EvenSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_GetInstance(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_EvenSmallNumbers* instanceName,
    const MI_PropertySet* propertySet)
{
    X_EvenSmallNumbers_Class_Provider* cxxSelf =((X_EvenSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);
    X_EvenSmallNumbers_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_CreateInstance(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_EvenSmallNumbers* newInstance)
{
    X_EvenSmallNumbers_Class_Provider* cxxSelf =((X_EvenSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);
    X_EvenSmallNumbers_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_ModifyInstance(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_EvenSmallNumbers* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_EvenSmallNumbers_Class_Provider* cxxSelf =((X_EvenSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);
    X_EvenSmallNumbers_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_DeleteInstance(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_EvenSmallNumbers* instanceName)
{
    X_EvenSmallNumbers_Class_Provider* cxxSelf =((X_EvenSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);
    X_EvenSmallNumbers_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_AssociatorInstances(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_EvenSmallNumbers_Class_Provider* cxxSelf =((X_EvenSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->AssociatorInstances(
        cxxContext,
        nameSpace,
        instanceName,
        resultClass,
        role,
        resultRole,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_EvenSmallNumbers_ReferenceInstances(
    X_EvenSmallNumbers_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_EvenSmallNumbers_Class_Provider* cxxSelf =((X_EvenSmallNumbers_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstances(
        cxxContext,
        nameSpace,
        instanceName,
        role,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_Halves_Load(
    X_Halves_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_Halves_Class_Provider* prov = new X_Halves_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_Halves_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_Halves_Unload(
    X_Halves_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_Halves_Class_Provider* prov = (X_Halves_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_Halves_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_Halves_EnumerateInstances(
    X_Halves_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_Halves_Class_Provider* cxxSelf =((X_Halves_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_Halves_GetInstance(
    X_Halves_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Halves* instanceName,
    const MI_PropertySet* propertySet)
{
    X_Halves_Class_Provider* cxxSelf =((X_Halves_Class_Provider*)self);
    Context  cxxContext(context);
    X_Halves_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_Halves_CreateInstance(
    X_Halves_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Halves* newInstance)
{
    X_Halves_Class_Provider* cxxSelf =((X_Halves_Class_Provider*)self);
    Context  cxxContext(context);
    X_Halves_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_Halves_ModifyInstance(
    X_Halves_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Halves* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_Halves_Class_Provider* cxxSelf =((X_Halves_Class_Provider*)self);
    Context  cxxContext(context);
    X_Halves_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_Halves_DeleteInstance(
    X_Halves_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Halves* instanceName)
{
    X_Halves_Class_Provider* cxxSelf =((X_Halves_Class_Provider*)self);
    Context  cxxContext(context);
    X_Halves_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_Halves_AssociatorInstances(
    X_Halves_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_Halves_Class_Provider* cxxSelf =((X_Halves_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->AssociatorInstances(
        cxxContext,
        nameSpace,
        instanceName,
        resultClass,
        role,
        resultRole,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_Halves_ReferenceInstances(
    X_Halves_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_Halves_Class_Provider* cxxSelf =((X_Halves_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstances(
        cxxContext,
        nameSpace,
        instanceName,
        role,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_Profile_Load(
    X_Profile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_Profile_Class_Provider* prov = new X_Profile_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_Profile_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_Profile_Unload(
    X_Profile_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_Profile_Class_Provider* prov = (X_Profile_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_Profile_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_Profile_EnumerateInstances(
    X_Profile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_Profile_Class_Provider* cxxSelf =((X_Profile_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_Profile_GetInstance(
    X_Profile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Profile* instanceName,
    const MI_PropertySet* propertySet)
{
    X_Profile_Class_Provider* cxxSelf =((X_Profile_Class_Provider*)self);
    Context  cxxContext(context);
    X_Profile_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_Profile_CreateInstance(
    X_Profile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Profile* newInstance)
{
    X_Profile_Class_Provider* cxxSelf =((X_Profile_Class_Provider*)self);
    Context  cxxContext(context);
    X_Profile_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_Profile_ModifyInstance(
    X_Profile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Profile* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_Profile_Class_Provider* cxxSelf =((X_Profile_Class_Provider*)self);
    Context  cxxContext(context);
    X_Profile_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_Profile_DeleteInstance(
    X_Profile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Profile* instanceName)
{
    X_Profile_Class_Provider* cxxSelf =((X_Profile_Class_Provider*)self);
    Context  cxxContext(context);
    X_Profile_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_Load(
    X_HugeNumberConformsToProfile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_HugeNumberConformsToProfile_Class_Provider* prov = new X_HugeNumberConformsToProfile_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_HugeNumberConformsToProfile_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_Unload(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_HugeNumberConformsToProfile_Class_Provider* prov = (X_HugeNumberConformsToProfile_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_HugeNumberConformsToProfile_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_EnumerateInstances(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_HugeNumberConformsToProfile_Class_Provider* cxxSelf =((X_HugeNumberConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_GetInstance(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumberConformsToProfile* instanceName,
    const MI_PropertySet* propertySet)
{
    X_HugeNumberConformsToProfile_Class_Provider* cxxSelf =((X_HugeNumberConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);
    X_HugeNumberConformsToProfile_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_CreateInstance(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumberConformsToProfile* newInstance)
{
    X_HugeNumberConformsToProfile_Class_Provider* cxxSelf =((X_HugeNumberConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);
    X_HugeNumberConformsToProfile_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_ModifyInstance(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumberConformsToProfile* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_HugeNumberConformsToProfile_Class_Provider* cxxSelf =((X_HugeNumberConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);
    X_HugeNumberConformsToProfile_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_DeleteInstance(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HugeNumberConformsToProfile* instanceName)
{
    X_HugeNumberConformsToProfile_Class_Provider* cxxSelf =((X_HugeNumberConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);
    X_HugeNumberConformsToProfile_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_AssociatorInstances(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_HugeNumberConformsToProfile_Class_Provider* cxxSelf =((X_HugeNumberConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->AssociatorInstances(
        cxxContext,
        nameSpace,
        instanceName,
        resultClass,
        role,
        resultRole,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_HugeNumberConformsToProfile_ReferenceInstances(
    X_HugeNumberConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_HugeNumberConformsToProfile_Class_Provider* cxxSelf =((X_HugeNumberConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstances(
        cxxContext,
        nameSpace,
        instanceName,
        role,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_Load(
    X_NumberWorldConformsToProfile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_NumberWorldConformsToProfile_Class_Provider* prov = new X_NumberWorldConformsToProfile_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_NumberWorldConformsToProfile_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_Unload(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_NumberWorldConformsToProfile_Class_Provider* prov = (X_NumberWorldConformsToProfile_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_NumberWorldConformsToProfile_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_EnumerateInstances(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_NumberWorldConformsToProfile_Class_Provider* cxxSelf =((X_NumberWorldConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_GetInstance(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorldConformsToProfile* instanceName,
    const MI_PropertySet* propertySet)
{
    X_NumberWorldConformsToProfile_Class_Provider* cxxSelf =((X_NumberWorldConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);
    X_NumberWorldConformsToProfile_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_CreateInstance(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorldConformsToProfile* newInstance)
{
    X_NumberWorldConformsToProfile_Class_Provider* cxxSelf =((X_NumberWorldConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);
    X_NumberWorldConformsToProfile_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_ModifyInstance(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorldConformsToProfile* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_NumberWorldConformsToProfile_Class_Provider* cxxSelf =((X_NumberWorldConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);
    X_NumberWorldConformsToProfile_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_DeleteInstance(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_NumberWorldConformsToProfile* instanceName)
{
    X_NumberWorldConformsToProfile_Class_Provider* cxxSelf =((X_NumberWorldConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);
    X_NumberWorldConformsToProfile_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_AssociatorInstances(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_NumberWorldConformsToProfile_Class_Provider* cxxSelf =((X_NumberWorldConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->AssociatorInstances(
        cxxContext,
        nameSpace,
        instanceName,
        resultClass,
        role,
        resultRole,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_NumberWorldConformsToProfile_ReferenceInstances(
    X_NumberWorldConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_NumberWorldConformsToProfile_Class_Provider* cxxSelf =((X_NumberWorldConformsToProfile_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstances(
        cxxContext,
        nameSpace,
        instanceName,
        role,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_Number1000001_Load(
    X_Number1000001_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_Number1000001_Class_Provider* prov = new X_Number1000001_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_Number1000001_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_Number1000001_Unload(
    X_Number1000001_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_Number1000001_Class_Provider* prov = (X_Number1000001_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_Number1000001_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_Number1000001_EnumerateInstances(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_Number1000001_Class_Provider* cxxSelf =((X_Number1000001_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_Number1000001_GetInstance(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Number1000001* instanceName,
    const MI_PropertySet* propertySet)
{
    X_Number1000001_Class_Provider* cxxSelf =((X_Number1000001_Class_Provider*)self);
    Context  cxxContext(context);
    X_Number1000001_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_Number1000001_CreateInstance(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Number1000001* newInstance)
{
    X_Number1000001_Class_Provider* cxxSelf =((X_Number1000001_Class_Provider*)self);
    Context  cxxContext(context);
    X_Number1000001_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_Number1000001_ModifyInstance(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Number1000001* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_Number1000001_Class_Provider* cxxSelf =((X_Number1000001_Class_Provider*)self);
    Context  cxxContext(context);
    X_Number1000001_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_Number1000001_DeleteInstance(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Number1000001* instanceName)
{
    X_Number1000001_Class_Provider* cxxSelf =((X_Number1000001_Class_Provider*)self);
    Context  cxxContext(context);
    X_Number1000001_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_Number1000001_Invoke_SpellMagnitude(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_Number1000001* instanceName,
    const X_Number1000001_SpellMagnitude* in)
{
    X_Number1000001_Class_Provider* cxxSelf =((X_Number1000001_Class_Provider*)self);
    X_Number1000001_Class instance(instanceName, false);
    Context  cxxContext(context);
    X_Number1000001_SpellMagnitude_Class param(in, false);

    cxxSelf->Invoke_SpellMagnitude(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL X_Number1000001_Invoke_TestEmbedded(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_Number1000001* instanceName,
    const X_Number1000001_TestEmbedded* in)
{
    X_Number1000001_Class_Provider* cxxSelf =((X_Number1000001_Class_Provider*)self);
    X_Number1000001_Class instance(instanceName, false);
    Context  cxxContext(context);
    X_Number1000001_TestEmbedded_Class param(in, false);

    cxxSelf->Invoke_TestEmbedded(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL X_Number1000001_Invoke_Method1(
    X_Number1000001_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_Number1000001* instanceName,
    const X_Number1000001_Method1* in)
{
    X_Number1000001_Class_Provider* cxxSelf =((X_Number1000001_Class_Provider*)self);
    X_Number1000001_Class instance(instanceName, false);
    Context  cxxContext(context);
    X_Number1000001_Method1_Class param(in, false);

    cxxSelf->Invoke_Method1(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL X_Cat_Load(
    X_Cat_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_Cat_Class_Provider* prov = new X_Cat_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_Cat_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_Cat_Unload(
    X_Cat_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_Cat_Class_Provider* prov = (X_Cat_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_Cat_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_Cat_EnumerateInstances(
    X_Cat_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_Cat_Class_Provider* cxxSelf =((X_Cat_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_Cat_GetInstance(
    X_Cat_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Cat* instanceName,
    const MI_PropertySet* propertySet)
{
    X_Cat_Class_Provider* cxxSelf =((X_Cat_Class_Provider*)self);
    Context  cxxContext(context);
    X_Cat_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_Cat_CreateInstance(
    X_Cat_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Cat* newInstance)
{
    X_Cat_Class_Provider* cxxSelf =((X_Cat_Class_Provider*)self);
    Context  cxxContext(context);
    X_Cat_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_Cat_ModifyInstance(
    X_Cat_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Cat* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_Cat_Class_Provider* cxxSelf =((X_Cat_Class_Provider*)self);
    Context  cxxContext(context);
    X_Cat_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_Cat_DeleteInstance(
    X_Cat_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_Cat* instanceName)
{
    X_Cat_Class_Provider* cxxSelf =((X_Cat_Class_Provider*)self);
    Context  cxxContext(context);
    X_Cat_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_Dog_Load(
    X_Dog_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_Dog_Class_Provider* prov = new X_Dog_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_Dog_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_Dog_Unload(
    X_Dog_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_Dog_Class_Provider* prov = (X_Dog_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_Dog_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_Dog_Invoke_Fight(
    X_Dog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_Dog* instanceName,
    const X_Dog_Fight* in)
{
    X_Dog_Class_Provider* cxxSelf =((X_Dog_Class_Provider*)self);
    X_Dog_Class instance(instanceName, false);
    Context  cxxContext(context);
    X_Dog_Fight_Class param(in, false);

    cxxSelf->Invoke_Fight(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL X_HTTPHeader_Load(
    X_HTTPHeader_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_HTTPHeader_Class_Provider* prov = new X_HTTPHeader_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_HTTPHeader_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_HTTPHeader_Unload(
    X_HTTPHeader_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_HTTPHeader_Class_Provider* prov = (X_HTTPHeader_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_HTTPHeader_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_HTTPHeader_EnumerateInstances(
    X_HTTPHeader_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_HTTPHeader_Class_Provider* cxxSelf =((X_HTTPHeader_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_HTTPHeader_GetInstance(
    X_HTTPHeader_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HTTPHeader* instanceName,
    const MI_PropertySet* propertySet)
{
    X_HTTPHeader_Class_Provider* cxxSelf =((X_HTTPHeader_Class_Provider*)self);
    Context  cxxContext(context);
    X_HTTPHeader_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_HTTPHeader_CreateInstance(
    X_HTTPHeader_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HTTPHeader* newInstance)
{
    X_HTTPHeader_Class_Provider* cxxSelf =((X_HTTPHeader_Class_Provider*)self);
    Context  cxxContext(context);
    X_HTTPHeader_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_HTTPHeader_ModifyInstance(
    X_HTTPHeader_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HTTPHeader* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_HTTPHeader_Class_Provider* cxxSelf =((X_HTTPHeader_Class_Provider*)self);
    Context  cxxContext(context);
    X_HTTPHeader_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_HTTPHeader_DeleteInstance(
    X_HTTPHeader_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_HTTPHeader* instanceName)
{
    X_HTTPHeader_Class_Provider* cxxSelf =((X_HTTPHeader_Class_Provider*)self);
    Context  cxxContext(context);
    X_HTTPHeader_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C MI_SchemaDecl schemaDecl;

void MI_CALL Load(MI_Module_Self** self, struct _MI_Context* context)
{
    *self = (MI_Module_Self*)new Module;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Unload(MI_Module_Self* self, struct _MI_Context* context)
{
    Module* module = (Module*)self;
    delete module;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C MI_EXPORT MI_Module* MI_MAIN_CALL MI_Main(MI_Server* server)
{
    /* WARNING: THIS FUNCTION AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT. */
    extern MI_Server* __mi_server;
    static MI_Module module;
    __mi_server = server;
    module.flags |= MI_MODULE_FLAG_STANDARD_QUALIFIERS;
    module.flags |= MI_MODULE_FLAG_CPLUSPLUS;
    module.charSize = sizeof(MI_Char);
    module.version = MI_VERSION;
    module.generatorVersion = MI_MAKE_VERSION(1,0,0);
    module.schemaDecl = &schemaDecl;
    module.Load = Load;
    module.Unload = Unload;
    return &module;
}
