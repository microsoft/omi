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
#include "Identifier_Class_Provider.h"
#include "Reference_Class_Provider.h"
#include "Test_Class_Provider.h"
#include "Main_Class_Provider.h"
#include "AllTypes_Class_Provider.h"
#include "Performance_Class_Provider.h"

using namespace mi;

MI_EXTERN_C void MI_CALL Identifier_Load(
    Identifier_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Identifier_Class_Provider* prov = new Identifier_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (Identifier_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Identifier_Unload(
    Identifier_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Identifier_Class_Provider* prov = (Identifier_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((Identifier_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL Identifier_EnumerateInstances(
    Identifier_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Identifier_Class_Provider* cxxSelf =((Identifier_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Identifier_GetInstance(
    Identifier_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identifier* instanceName,
    const MI_PropertySet* propertySet)
{
    Identifier_Class_Provider* cxxSelf =((Identifier_Class_Provider*)self);
    Context  cxxContext(context);
    Identifier_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Identifier_CreateInstance(
    Identifier_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identifier* newInstance)
{
    Identifier_Class_Provider* cxxSelf =((Identifier_Class_Provider*)self);
    Context  cxxContext(context);
    Identifier_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL Identifier_ModifyInstance(
    Identifier_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identifier* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    Identifier_Class_Provider* cxxSelf =((Identifier_Class_Provider*)self);
    Context  cxxContext(context);
    Identifier_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Identifier_DeleteInstance(
    Identifier_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identifier* instanceName)
{
    Identifier_Class_Provider* cxxSelf =((Identifier_Class_Provider*)self);
    Context  cxxContext(context);
    Identifier_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL Reference_Load(
    Reference_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Reference_Class_Provider* prov = new Reference_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (Reference_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Reference_Unload(
    Reference_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Reference_Class_Provider* prov = (Reference_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((Reference_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL Reference_EnumerateInstances(
    Reference_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Reference_Class_Provider* cxxSelf =((Reference_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Reference_GetInstance(
    Reference_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* instanceName,
    const MI_PropertySet* propertySet)
{
    Reference_Class_Provider* cxxSelf =((Reference_Class_Provider*)self);
    Context  cxxContext(context);
    Reference_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Reference_CreateInstance(
    Reference_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* newInstance)
{
    Reference_Class_Provider* cxxSelf =((Reference_Class_Provider*)self);
    Context  cxxContext(context);
    Reference_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL Reference_ModifyInstance(
    Reference_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    Reference_Class_Provider* cxxSelf =((Reference_Class_Provider*)self);
    Context  cxxContext(context);
    Reference_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Reference_DeleteInstance(
    Reference_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* instanceName)
{
    Reference_Class_Provider* cxxSelf =((Reference_Class_Provider*)self);
    Context  cxxContext(context);
    Reference_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL Test_Load(
    Test_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Test_Class_Provider* prov = new Test_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (Test_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Test_Unload(
    Test_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Test_Class_Provider* prov = (Test_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((Test_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL Test_EnumerateInstances(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Test_Class_Provider* cxxSelf =((Test_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Test_GetInstance(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test* instanceName,
    const MI_PropertySet* propertySet)
{
    Test_Class_Provider* cxxSelf =((Test_Class_Provider*)self);
    Context  cxxContext(context);
    Test_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Test_CreateInstance(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test* newInstance)
{
    Test_Class_Provider* cxxSelf =((Test_Class_Provider*)self);
    Context  cxxContext(context);
    Test_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL Test_ModifyInstance(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    Test_Class_Provider* cxxSelf =((Test_Class_Provider*)self);
    Context  cxxContext(context);
    Test_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Test_DeleteInstance(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test* instanceName)
{
    Test_Class_Provider* cxxSelf =((Test_Class_Provider*)self);
    Context  cxxContext(context);
    Test_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL Test_AssociatorInstancesId(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Identifier* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Test_Class_Provider* cxxSelf =((Test_Class_Provider*)self);
    Identifier_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->AssociatorInstancesId(
        cxxContext, 
        nameSpace,
        cxxInstanceName,
        resultClass,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Test_AssociatorInstancesRf(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Test_Class_Provider* cxxSelf =((Test_Class_Provider*)self);
    Reference_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->AssociatorInstancesRf(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        resultClass,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Test_ReferenceInstancesId(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const Identifier* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Test_Class_Provider* cxxSelf =((Test_Class_Provider*)self);
    Identifier_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstancesId(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Test_ReferenceInstancesRf(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const Reference* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Test_Class_Provider* cxxSelf =((Test_Class_Provider*)self);
    Reference_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstancesRf(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Test_Invoke_StaticFun(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Test* instanceName,
    const Test_StaticFun* in)
{
    Test_Class_Provider* cxxSelf =((Test_Class_Provider*)self);
    Test_Class instance(instanceName, false);
    Context  cxxContext(context);
    Test_StaticFun_Class param(in, false);

    cxxSelf->Invoke_StaticFun(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL Test_Invoke_InstanceFun(
    Test_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Test* instanceName,
    const Test_InstanceFun* in)
{
    Test_Class_Provider* cxxSelf =((Test_Class_Provider*)self);
    Test_Class instance(instanceName, false);
    Context  cxxContext(context);
    Test_InstanceFun_Class param(in, false);

    cxxSelf->Invoke_InstanceFun(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL Main_Load(
    Main_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Main_Class_Provider* prov = new Main_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (Main_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Main_Unload(
    Main_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Main_Class_Provider* prov = (Main_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((Main_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL Main_EnumerateInstances(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Main_Class_Provider* cxxSelf =((Main_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Main_GetInstance(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* instanceName,
    const MI_PropertySet* propertySet)
{
    Main_Class_Provider* cxxSelf =((Main_Class_Provider*)self);
    Context  cxxContext(context);
    Main_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Main_CreateInstance(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* newInstance)
{
    Main_Class_Provider* cxxSelf =((Main_Class_Provider*)self);
    Context  cxxContext(context);
    Main_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL Main_ModifyInstance(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    Main_Class_Provider* cxxSelf =((Main_Class_Provider*)self);
    Context  cxxContext(context);
    Main_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Main_DeleteInstance(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* instanceName)
{
    Main_Class_Provider* cxxSelf =((Main_Class_Provider*)self);
    Context  cxxContext(context);
    Main_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL Main_Invoke_ChangeState(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Main* instanceName,
    const Main_ChangeState* in)
{
    Main_Class_Provider* cxxSelf =((Main_Class_Provider*)self);
    Main_Class instance(instanceName, false);
    Context  cxxContext(context);
    Main_ChangeState_Class param(in, false);

    cxxSelf->Invoke_ChangeState(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL Main_Invoke_HelloWorld(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Main* instanceName,
    const Main_HelloWorld* in)
{
    Main_Class_Provider* cxxSelf =((Main_Class_Provider*)self);
    Main_Class instance(instanceName, false);
    Context  cxxContext(context);
    Main_HelloWorld_Class param(in, false);

    cxxSelf->Invoke_HelloWorld(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL AllTypes_Load(
    AllTypes_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    AllTypes_Class_Provider* prov = new AllTypes_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (AllTypes_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL AllTypes_Unload(
    AllTypes_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    AllTypes_Class_Provider* prov = (AllTypes_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((AllTypes_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL AllTypes_EnumerateInstances(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    AllTypes_Class_Provider* cxxSelf =((AllTypes_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL AllTypes_GetInstance(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const AllTypes* instanceName,
    const MI_PropertySet* propertySet)
{
    AllTypes_Class_Provider* cxxSelf =((AllTypes_Class_Provider*)self);
    Context  cxxContext(context);
    AllTypes_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL AllTypes_CreateInstance(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const AllTypes* newInstance)
{
    AllTypes_Class_Provider* cxxSelf =((AllTypes_Class_Provider*)self);
    Context  cxxContext(context);
    AllTypes_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL AllTypes_ModifyInstance(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const AllTypes* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    AllTypes_Class_Provider* cxxSelf =((AllTypes_Class_Provider*)self);
    Context  cxxContext(context);
    AllTypes_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL AllTypes_DeleteInstance(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const AllTypes* instanceName)
{
    AllTypes_Class_Provider* cxxSelf =((AllTypes_Class_Provider*)self);
    Context  cxxContext(context);
    AllTypes_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL AllTypes_AssociatorInstancesrefMain(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    AllTypes_Class_Provider* cxxSelf =((AllTypes_Class_Provider*)self);
    Main_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->AssociatorInstancesrefMain(
        cxxContext, 
        nameSpace,
        cxxInstanceName,
        resultClass,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL AllTypes_AssociatorInstancesrefRef(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Reference* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    AllTypes_Class_Provider* cxxSelf =((AllTypes_Class_Provider*)self);
    Reference_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->AssociatorInstancesrefRef(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        resultClass,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL AllTypes_ReferenceInstancesrefMain(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const Main* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    AllTypes_Class_Provider* cxxSelf =((AllTypes_Class_Provider*)self);
    Main_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstancesrefMain(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL AllTypes_ReferenceInstancesrefRef(
    AllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const Reference* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    AllTypes_Class_Provider* cxxSelf =((AllTypes_Class_Provider*)self);
    Reference_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstancesrefRef(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Performance_Load(
    Performance_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Performance_Class_Provider* prov = new Performance_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (Performance_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Performance_Unload(
    Performance_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Performance_Class_Provider* prov = (Performance_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((Performance_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL Performance_EnumerateInstances(
    Performance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Performance_Class_Provider* cxxSelf =((Performance_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Performance_GetInstance(
    Performance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Performance* instanceName,
    const MI_PropertySet* propertySet)
{
    Performance_Class_Provider* cxxSelf =((Performance_Class_Provider*)self);
    Context  cxxContext(context);
    Performance_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Performance_CreateInstance(
    Performance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Performance* newInstance)
{
    Performance_Class_Provider* cxxSelf =((Performance_Class_Provider*)self);
    Context  cxxContext(context);
    Performance_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL Performance_ModifyInstance(
    Performance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Performance* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    Performance_Class_Provider* cxxSelf =((Performance_Class_Provider*)self);
    Context  cxxContext(context);
    Performance_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Performance_DeleteInstance(
    Performance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Performance* instanceName)
{
    Performance_Class_Provider* cxxSelf =((Performance_Class_Provider*)self);
    Context  cxxContext(context);
    Performance_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}


MI_EXTERN_C MI_SchemaDecl schemaDecl;

void MI_CALL Load(MI_Module_Self** self, struct _MI_Context* context)
{
    *self = (MI_Module_Self*)new Module;
}

void MI_CALL Unload(MI_Module_Self* self, struct _MI_Context* context)
{
    Module* module = (Module*)self;
    delete module;
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

