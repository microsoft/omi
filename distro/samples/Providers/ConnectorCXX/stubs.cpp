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
#include "Widget_Class_Provider.h"
#include "Gadget_Class_Provider.h"
#include "Connector_Class_Provider.h"
#include "Order_Class_Provider.h"
#include "Base_Class_Provider.h"
#include "Derived_Class_Provider.h"
#include "BaseAssoc_Class_Provider.h"
#include "DerivedAssoc_Class_Provider.h"

using namespace mi;

MI_EXTERN_C void MI_CALL Widget_Load(
    Widget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Widget_Class_Provider* prov = new Widget_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (Widget_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Widget_Unload(
    Widget_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Widget_Class_Provider* prov = (Widget_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((Widget_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL Widget_EnumerateInstances(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Widget_Class_Provider* cxxSelf =((Widget_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Widget_GetInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName,
    const MI_PropertySet* propertySet)
{
    Widget_Class_Provider* cxxSelf =((Widget_Class_Provider*)self);
    Context  cxxContext(context);
    Widget_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Widget_CreateInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* newInstance)
{
    Widget_Class_Provider* cxxSelf =((Widget_Class_Provider*)self);
    Context  cxxContext(context);
    Widget_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL Widget_ModifyInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    Widget_Class_Provider* cxxSelf =((Widget_Class_Provider*)self);
    Context  cxxContext(context);
    Widget_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Widget_DeleteInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName)
{
    Widget_Class_Provider* cxxSelf =((Widget_Class_Provider*)self);
    Context  cxxContext(context);
    Widget_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL Gadget_Load(
    Gadget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Gadget_Class_Provider* prov = new Gadget_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (Gadget_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Gadget_Unload(
    Gadget_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Gadget_Class_Provider* prov = (Gadget_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((Gadget_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL Gadget_EnumerateInstances(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Gadget_Class_Provider* cxxSelf =((Gadget_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Gadget_GetInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName,
    const MI_PropertySet* propertySet)
{
    Gadget_Class_Provider* cxxSelf =((Gadget_Class_Provider*)self);
    Context  cxxContext(context);
    Gadget_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Gadget_CreateInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* newInstance)
{
    Gadget_Class_Provider* cxxSelf =((Gadget_Class_Provider*)self);
    Context  cxxContext(context);
    Gadget_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL Gadget_ModifyInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    Gadget_Class_Provider* cxxSelf =((Gadget_Class_Provider*)self);
    Context  cxxContext(context);
    Gadget_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Gadget_DeleteInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName)
{
    Gadget_Class_Provider* cxxSelf =((Gadget_Class_Provider*)self);
    Context  cxxContext(context);
    Gadget_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL Gadget_Invoke_ChangeState(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Gadget* instanceName,
    const Gadget_ChangeState* in)
{
    Gadget_Class_Provider* cxxSelf =((Gadget_Class_Provider*)self);
    Gadget_Class instance(instanceName, false);
    Context  cxxContext(context);
    Gadget_ChangeState_Class param(in, false);

    cxxSelf->Invoke_ChangeState(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL Gadget_Invoke_Foo(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Gadget* instanceName,
    const Gadget_Foo* in)
{
    Gadget_Class_Provider* cxxSelf =((Gadget_Class_Provider*)self);
    Gadget_Class instance(instanceName, false);
    Context  cxxContext(context);
    Gadget_Foo_Class param(in, false);

    cxxSelf->Invoke_Foo(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL Connector_Load(
    Connector_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Connector_Class_Provider* prov = new Connector_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (Connector_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Connector_Unload(
    Connector_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Connector_Class_Provider* prov = (Connector_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((Connector_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL Connector_EnumerateInstances(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Connector_Class_Provider* cxxSelf =((Connector_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Connector_GetInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* instanceName,
    const MI_PropertySet* propertySet)
{
    Connector_Class_Provider* cxxSelf =((Connector_Class_Provider*)self);
    Context  cxxContext(context);
    Connector_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Connector_CreateInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* newInstance)
{
    Connector_Class_Provider* cxxSelf =((Connector_Class_Provider*)self);
    Context  cxxContext(context);
    Connector_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL Connector_ModifyInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    Connector_Class_Provider* cxxSelf =((Connector_Class_Provider*)self);
    Context  cxxContext(context);
    Connector_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Connector_DeleteInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* instanceName)
{
    Connector_Class_Provider* cxxSelf =((Connector_Class_Provider*)self);
    Context  cxxContext(context);
    Connector_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL Connector_AssociatorInstancesLeft(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Connector_Class_Provider* cxxSelf =((Connector_Class_Provider*)self);
    Widget_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->AssociatorInstancesLeft(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        resultClass,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Connector_AssociatorInstancesRight(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Connector_Class_Provider* cxxSelf =((Connector_Class_Provider*)self);
    Gadget_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->AssociatorInstancesRight(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        resultClass,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Connector_ReferenceInstancesLeft(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const Widget* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Connector_Class_Provider* cxxSelf =((Connector_Class_Provider*)self);
    Widget_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstancesLeft(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Connector_ReferenceInstancesRight(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const Gadget* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Connector_Class_Provider* cxxSelf =((Connector_Class_Provider*)self);
    Gadget_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstancesRight(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Order_Load(
    Order_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Order_Class_Provider* prov = new Order_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (Order_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Order_Unload(
    Order_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Order_Class_Provider* prov = (Order_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((Order_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL Order_EnableIndications(
    Order_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    Order_Class_Provider* cxxSelf =((Order_Class_Provider*)self);

    cxxSelf->SetIndicationContext(indicationsContext);
    cxxSelf->EnableIndications();
}

MI_EXTERN_C void MI_CALL Order_DisableIndications(
    Order_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    Order_Class_Provider* cxxSelf =((Order_Class_Provider*)self);

    cxxSelf->DisableIndications();
    cxxSelf->SetIndicationContext(0);

    MI_PostResult(indicationsContext, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Order_Subscribe(
    Order_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf)
{
    Order_Class_Provider* cxxSelf =((Order_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->Subscribe(
        cxxContext,
        nameSpace,
        filter,
        bookmark,
        subscriptionID,
        subscriptionSelf);
}

MI_EXTERN_C void MI_CALL Order_Unsubscribe(
    Order_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf)
{
    Order_Class_Provider* cxxSelf =((Order_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->Unsubscribe(
        cxxContext,
        nameSpace,
        subscriptionID,
        subscriptionSelf);
}

MI_EXTERN_C void MI_CALL Base_Load(
    Base_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Base_Class_Provider* prov = new Base_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (Base_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Base_Unload(
    Base_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Base_Class_Provider* prov = (Base_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((Base_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL Base_Invoke_Foo(
    Base_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Base* instanceName,
    const Base_Foo* in)
{
    Base_Class_Provider* cxxSelf =((Base_Class_Provider*)self);
    Base_Class instance(instanceName, false);
    Context  cxxContext(context);
    Base_Foo_Class param(in, false);

    cxxSelf->Invoke_Foo(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL Derived_Load(
    Derived_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Derived_Class_Provider* prov = new Derived_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (Derived_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Derived_Unload(
    Derived_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Derived_Class_Provider* prov = (Derived_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((Derived_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL Derived_Invoke_Foo(
    Derived_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Derived* instanceName,
    const Derived_Foo* in)
{
    Derived_Class_Provider* cxxSelf =((Derived_Class_Provider*)self);
    Derived_Class instance(instanceName, false);
    Context  cxxContext(context);
    Derived_Foo_Class param(in, false);

    cxxSelf->Invoke_Foo(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL BaseAssoc_Load(
    BaseAssoc_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    BaseAssoc_Class_Provider* prov = new BaseAssoc_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (BaseAssoc_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL BaseAssoc_Unload(
    BaseAssoc_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    BaseAssoc_Class_Provider* prov = (BaseAssoc_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((BaseAssoc_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL DerivedAssoc_Load(
    DerivedAssoc_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    DerivedAssoc_Class_Provider* prov = new DerivedAssoc_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (DerivedAssoc_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL DerivedAssoc_Unload(
    DerivedAssoc_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    DerivedAssoc_Class_Provider* prov = (DerivedAssoc_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((DerivedAssoc_Class_Provider*)self);
    MI_PostResult(context, r);
}


MI_EXTERN_C MI_SchemaDecl schemaDecl;

void MI_CALL Load(MI_Module_Self** self, struct _MI_Context* context)
{
    *self = (MI_Module_Self*)new Module;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Unload(MI_Module_Self* self, struct _MI_Context* context)
{
    Module* module = (Module*)self;
    delete module;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C MI_EXPORT MI_Module* MI_MAIN_CALL MI_Main(MI_Server* server)
{
    /* WARNING: THIS FUNCTION AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT. */
    extern MI_Server* __mi_server;
    static MI_Module module;
    __mi_server = server;
    module.flags |= MI_MODULE_FLAG_STANDARD_QUALIFIERS;
    module.flags |= MI_MODULE_FLAG_DESCRIPTIONS;
    module.flags |= MI_MODULE_FLAG_CPLUSPLUS;
    module.flags |= MI_MODULE_FLAG_FILTER_SUPPORT;
    module.charSize = sizeof(MI_Char);
    module.version = MI_VERSION;
    module.generatorVersion = MI_MAKE_VERSION(1,0,0);
    module.schemaDecl = &schemaDecl;
    module.Load = Load;
    module.Unload = Unload;
    return &module;
}
