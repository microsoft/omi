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
#include "MSFT_Alert_Class_Provider.h"
#include "MSFT_Friends_Class_Provider.h"
#include "MSFT_Person_Class_Provider.h"
#include "TestSP_Method_Class_Provider.h"
#include "TestEmbeddedOperations_Class_Provider.h"
#include "X_SingletonWithAllTypes_Class_Provider.h"
#include "X_FailedAtLoad_Class_Provider.h"
#include "X_RefuseUnload_Class_Provider.h"

using namespace mi;

MI_EXTERN_C void MI_CALL MSFT_Alert_Load(
    MSFT_Alert_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MSFT_Alert_Class_Provider* prov = new MSFT_Alert_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (MSFT_Alert_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL MSFT_Alert_Unload(
    MSFT_Alert_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MSFT_Alert_Class_Provider* prov = (MSFT_Alert_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((MSFT_Alert_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL MSFT_Alert_EnableIndications(
    MSFT_Alert_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    MSFT_Alert_Class_Provider* cxxSelf =((MSFT_Alert_Class_Provider*)self);

    cxxSelf->SetIndicationContext(indicationsContext);
    cxxSelf->EnableIndications();
}

MI_EXTERN_C void MI_CALL MSFT_Alert_DisableIndications(
    MSFT_Alert_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    MSFT_Alert_Class_Provider* cxxSelf =((MSFT_Alert_Class_Provider*)self);

    cxxSelf->DisableIndications();
    cxxSelf->SetIndicationContext(0);

    MI_PostResult(indicationsContext, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL MSFT_Alert_Subscribe(
    MSFT_Alert_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf)
{
    MSFT_Alert_Class_Provider* cxxSelf =((MSFT_Alert_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->Subscribe(
        cxxContext,
        nameSpace,
        filter,
        bookmark,
        subscriptionID,
        subscriptionSelf);
}

MI_EXTERN_C void MI_CALL MSFT_Alert_Unsubscribe(
    MSFT_Alert_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf)
{
    MSFT_Alert_Class_Provider* cxxSelf =((MSFT_Alert_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->Unsubscribe(
        cxxContext,
        nameSpace,
        subscriptionID,
        subscriptionSelf);
}

MI_EXTERN_C void MI_CALL MSFT_Friends_Load(
    MSFT_Friends_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MSFT_Friends_Class_Provider* prov = new MSFT_Friends_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (MSFT_Friends_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL MSFT_Friends_Unload(
    MSFT_Friends_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MSFT_Friends_Class_Provider* prov = (MSFT_Friends_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((MSFT_Friends_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL MSFT_Friends_EnumerateInstances(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MSFT_Friends_Class_Provider* cxxSelf =((MSFT_Friends_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL MSFT_Friends_GetInstance(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Friends* instanceName,
    const MI_PropertySet* propertySet)
{
    MSFT_Friends_Class_Provider* cxxSelf =((MSFT_Friends_Class_Provider*)self);
    Context  cxxContext(context);
    MSFT_Friends_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL MSFT_Friends_CreateInstance(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Friends* newInstance)
{
    MSFT_Friends_Class_Provider* cxxSelf =((MSFT_Friends_Class_Provider*)self);
    Context  cxxContext(context);
    MSFT_Friends_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL MSFT_Friends_ModifyInstance(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Friends* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MSFT_Friends_Class_Provider* cxxSelf =((MSFT_Friends_Class_Provider*)self);
    Context  cxxContext(context);
    MSFT_Friends_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL MSFT_Friends_DeleteInstance(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Friends* instanceName)
{
    MSFT_Friends_Class_Provider* cxxSelf =((MSFT_Friends_Class_Provider*)self);
    Context  cxxContext(context);
    MSFT_Friends_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL MSFT_Friends_AssociatorInstances(
    MSFT_Friends_Self* self,
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
    MSFT_Friends_Class_Provider* cxxSelf =((MSFT_Friends_Class_Provider*)self);
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

MI_EXTERN_C void MI_CALL MSFT_Friends_ReferenceInstances(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MSFT_Friends_Class_Provider* cxxSelf =((MSFT_Friends_Class_Provider*)self);
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

MI_EXTERN_C void MI_CALL MSFT_Friends_Invoke_AddFriend(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Friends* instanceName,
    const MSFT_Friends_AddFriend* in)
{
    MSFT_Friends_Class_Provider* cxxSelf =((MSFT_Friends_Class_Provider*)self);
    MSFT_Friends_Class instance(instanceName, false);
    Context  cxxContext(context);
    MSFT_Friends_AddFriend_Class param(in, false);

    cxxSelf->Invoke_AddFriend(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL MSFT_Friends_Invoke_AddFriends(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Friends* instanceName,
    const MSFT_Friends_AddFriends* in)
{
    MSFT_Friends_Class_Provider* cxxSelf =((MSFT_Friends_Class_Provider*)self);
    MSFT_Friends_Class instance(instanceName, false);
    Context  cxxContext(context);
    MSFT_Friends_AddFriends_Class param(in, false);

    cxxSelf->Invoke_AddFriends(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL MSFT_Person_Load(
    MSFT_Person_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MSFT_Person_Class_Provider* prov = new MSFT_Person_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (MSFT_Person_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL MSFT_Person_Unload(
    MSFT_Person_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MSFT_Person_Class_Provider* prov = (MSFT_Person_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((MSFT_Person_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL MSFT_Person_EnumerateInstances(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MSFT_Person_Class_Provider* cxxSelf =((MSFT_Person_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL MSFT_Person_GetInstance(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Person* instanceName,
    const MI_PropertySet* propertySet)
{
    MSFT_Person_Class_Provider* cxxSelf =((MSFT_Person_Class_Provider*)self);
    Context  cxxContext(context);
    MSFT_Person_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL MSFT_Person_CreateInstance(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Person* newInstance)
{
    MSFT_Person_Class_Provider* cxxSelf =((MSFT_Person_Class_Provider*)self);
    Context  cxxContext(context);
    MSFT_Person_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL MSFT_Person_ModifyInstance(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Person* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MSFT_Person_Class_Provider* cxxSelf =((MSFT_Person_Class_Provider*)self);
    Context  cxxContext(context);
    MSFT_Person_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL MSFT_Person_DeleteInstance(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Person* instanceName)
{
    MSFT_Person_Class_Provider* cxxSelf =((MSFT_Person_Class_Provider*)self);
    Context  cxxContext(context);
    MSFT_Person_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL MSFT_Person_Invoke_Add(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Person* instanceName,
    const MSFT_Person_Add* in)
{
    MSFT_Person_Class_Provider* cxxSelf =((MSFT_Person_Class_Provider*)self);
    MSFT_Person_Class instance(instanceName, false);
    Context  cxxContext(context);
    MSFT_Person_Add_Class param(in, false);

    cxxSelf->Invoke_Add(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL MSFT_Person_Invoke_TestAllTypes(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Person* instanceName,
    const MSFT_Person_TestAllTypes* in)
{
    MSFT_Person_Class_Provider* cxxSelf =((MSFT_Person_Class_Provider*)self);
    MSFT_Person_Class instance(instanceName, false);
    Context  cxxContext(context);
    MSFT_Person_TestAllTypes_Class param(in, false);

    cxxSelf->Invoke_TestAllTypes(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL MSFT_Person_Invoke_StreamParams(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Person* instanceName,
    const MSFT_Person_StreamParams* in)
{
    MSFT_Person_Class_Provider* cxxSelf =((MSFT_Person_Class_Provider*)self);
    MSFT_Person_Class instance(instanceName, false);
    Context  cxxContext(context);
    MSFT_Person_StreamParams_Class param(in, false);

    cxxSelf->Invoke_StreamParams(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL TestSP_Method_Load(
    TestSP_Method_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    TestSP_Method_Class_Provider* prov = new TestSP_Method_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (TestSP_Method_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL TestSP_Method_Unload(
    TestSP_Method_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    TestSP_Method_Class_Provider* prov = (TestSP_Method_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((TestSP_Method_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL TestSP_Method_Invoke_MyFunc(
    TestSP_Method_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestSP_Method* instanceName,
    const TestSP_Method_MyFunc* in)
{
    TestSP_Method_Class_Provider* cxxSelf =((TestSP_Method_Class_Provider*)self);
    TestSP_Method_Class instance(instanceName, false);
    Context  cxxContext(context);
    TestSP_Method_MyFunc_Class param(in, false);

    cxxSelf->Invoke_MyFunc(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_Load(
    TestEmbeddedOperations_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    TestEmbeddedOperations_Class_Provider* prov = new TestEmbeddedOperations_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (TestEmbeddedOperations_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_Unload(
    TestEmbeddedOperations_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    TestEmbeddedOperations_Class_Provider* prov = (TestEmbeddedOperations_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((TestEmbeddedOperations_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_EnumerateInstances(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    TestEmbeddedOperations_Class_Provider* cxxSelf =((TestEmbeddedOperations_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_GetInstance(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestEmbeddedOperations* instanceName,
    const MI_PropertySet* propertySet)
{
    TestEmbeddedOperations_Class_Provider* cxxSelf =((TestEmbeddedOperations_Class_Provider*)self);
    Context  cxxContext(context);
    TestEmbeddedOperations_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_CreateInstance(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestEmbeddedOperations* newInstance)
{
    TestEmbeddedOperations_Class_Provider* cxxSelf =((TestEmbeddedOperations_Class_Provider*)self);
    Context  cxxContext(context);
    TestEmbeddedOperations_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_ModifyInstance(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestEmbeddedOperations* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    TestEmbeddedOperations_Class_Provider* cxxSelf =((TestEmbeddedOperations_Class_Provider*)self);
    Context  cxxContext(context);
    TestEmbeddedOperations_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_DeleteInstance(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestEmbeddedOperations* instanceName)
{
    TestEmbeddedOperations_Class_Provider* cxxSelf =((TestEmbeddedOperations_Class_Provider*)self);
    Context  cxxContext(context);
    TestEmbeddedOperations_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_Invoke_TestEmbedded(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestEmbeddedOperations* instanceName,
    const TestEmbeddedOperations_TestEmbedded* in)
{
    TestEmbeddedOperations_Class_Provider* cxxSelf =((TestEmbeddedOperations_Class_Provider*)self);
    TestEmbeddedOperations_Class instance(instanceName, false);
    Context  cxxContext(context);
    TestEmbeddedOperations_TestEmbedded_Class param(in, false);

    cxxSelf->Invoke_TestEmbedded(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_Invoke_TestEmbeddedInstanceReturnKey20100609(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestEmbeddedOperations* instanceName,
    const TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609* in)
{
    TestEmbeddedOperations_Class_Provider* cxxSelf =((TestEmbeddedOperations_Class_Provider*)self);
    TestEmbeddedOperations_Class instance(instanceName, false);
    Context  cxxContext(context);
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class param(in, false);

    cxxSelf->Invoke_TestEmbeddedInstanceReturnKey20100609(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL TestEmbeddedOperations_Invoke_TestEmbeddedObjectReturnKey20100609(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestEmbeddedOperations* instanceName,
    const TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609* in)
{
    TestEmbeddedOperations_Class_Provider* cxxSelf =((TestEmbeddedOperations_Class_Provider*)self);
    TestEmbeddedOperations_Class instance(instanceName, false);
    Context  cxxContext(context);
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class param(in, false);

    cxxSelf->Invoke_TestEmbeddedObjectReturnKey20100609(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_Load(
    X_SingletonWithAllTypes_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_SingletonWithAllTypes_Class_Provider* prov = new X_SingletonWithAllTypes_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_SingletonWithAllTypes_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_Unload(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_SingletonWithAllTypes_Class_Provider* prov = (X_SingletonWithAllTypes_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_SingletonWithAllTypes_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_EnumerateInstances(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_SingletonWithAllTypes_Class_Provider* cxxSelf =((X_SingletonWithAllTypes_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_GetInstance(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SingletonWithAllTypes* instanceName,
    const MI_PropertySet* propertySet)
{
    X_SingletonWithAllTypes_Class_Provider* cxxSelf =((X_SingletonWithAllTypes_Class_Provider*)self);
    Context  cxxContext(context);
    X_SingletonWithAllTypes_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_CreateInstance(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SingletonWithAllTypes* newInstance)
{
    X_SingletonWithAllTypes_Class_Provider* cxxSelf =((X_SingletonWithAllTypes_Class_Provider*)self);
    Context  cxxContext(context);
    X_SingletonWithAllTypes_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_ModifyInstance(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SingletonWithAllTypes* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_SingletonWithAllTypes_Class_Provider* cxxSelf =((X_SingletonWithAllTypes_Class_Provider*)self);
    Context  cxxContext(context);
    X_SingletonWithAllTypes_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_DeleteInstance(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SingletonWithAllTypes* instanceName)
{
    X_SingletonWithAllTypes_Class_Provider* cxxSelf =((X_SingletonWithAllTypes_Class_Provider*)self);
    Context  cxxContext(context);
    X_SingletonWithAllTypes_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_FailedAtLoad_Load(
    X_FailedAtLoad_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_FailedAtLoad_Class_Provider* prov = new X_FailedAtLoad_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_FailedAtLoad_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_FailedAtLoad_Unload(
    X_FailedAtLoad_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_FailedAtLoad_Class_Provider* prov = (X_FailedAtLoad_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_FailedAtLoad_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_FailedAtLoad_EnumerateInstances(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_FailedAtLoad_Class_Provider* cxxSelf =((X_FailedAtLoad_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_FailedAtLoad_GetInstance(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_FailedAtLoad* instanceName,
    const MI_PropertySet* propertySet)
{
    X_FailedAtLoad_Class_Provider* cxxSelf =((X_FailedAtLoad_Class_Provider*)self);
    Context  cxxContext(context);
    X_FailedAtLoad_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_FailedAtLoad_CreateInstance(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_FailedAtLoad* newInstance)
{
    X_FailedAtLoad_Class_Provider* cxxSelf =((X_FailedAtLoad_Class_Provider*)self);
    Context  cxxContext(context);
    X_FailedAtLoad_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_FailedAtLoad_ModifyInstance(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_FailedAtLoad* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_FailedAtLoad_Class_Provider* cxxSelf =((X_FailedAtLoad_Class_Provider*)self);
    Context  cxxContext(context);
    X_FailedAtLoad_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_FailedAtLoad_DeleteInstance(
    X_FailedAtLoad_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_FailedAtLoad* instanceName)
{
    X_FailedAtLoad_Class_Provider* cxxSelf =((X_FailedAtLoad_Class_Provider*)self);
    Context  cxxContext(context);
    X_FailedAtLoad_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_RefuseUnload_Load(
    X_RefuseUnload_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_RefuseUnload_Class_Provider* prov = new X_RefuseUnload_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (X_RefuseUnload_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL X_RefuseUnload_Unload(
    X_RefuseUnload_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    X_RefuseUnload_Class_Provider* prov = (X_RefuseUnload_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((X_RefuseUnload_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL X_RefuseUnload_EnumerateInstances(
    X_RefuseUnload_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    X_RefuseUnload_Class_Provider* cxxSelf =((X_RefuseUnload_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL X_RefuseUnload_GetInstance(
    X_RefuseUnload_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_RefuseUnload* instanceName,
    const MI_PropertySet* propertySet)
{
    X_RefuseUnload_Class_Provider* cxxSelf =((X_RefuseUnload_Class_Provider*)self);
    Context  cxxContext(context);
    X_RefuseUnload_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_RefuseUnload_CreateInstance(
    X_RefuseUnload_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_RefuseUnload* newInstance)
{
    X_RefuseUnload_Class_Provider* cxxSelf =((X_RefuseUnload_Class_Provider*)self);
    Context  cxxContext(context);
    X_RefuseUnload_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL X_RefuseUnload_ModifyInstance(
    X_RefuseUnload_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_RefuseUnload* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    X_RefuseUnload_Class_Provider* cxxSelf =((X_RefuseUnload_Class_Provider*)self);
    Context  cxxContext(context);
    X_RefuseUnload_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL X_RefuseUnload_DeleteInstance(
    X_RefuseUnload_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_RefuseUnload* instanceName)
{
    X_RefuseUnload_Class_Provider* cxxSelf =((X_RefuseUnload_Class_Provider*)self);
    Context  cxxContext(context);
    X_RefuseUnload_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL X_RefuseUnload_Invoke_RequestUnload(
    X_RefuseUnload_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_RefuseUnload* instanceName,
    const X_RefuseUnload_RequestUnload* in)
{
    X_RefuseUnload_Class_Provider* cxxSelf =((X_RefuseUnload_Class_Provider*)self);
    X_RefuseUnload_Class instance(instanceName, false);
    Context  cxxContext(context);
    X_RefuseUnload_RequestUnload_Class param(in, false);

    cxxSelf->Invoke_RequestUnload(cxxContext, nameSpace, instance, param);
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

