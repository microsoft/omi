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
#include "XYZ_Widget_Class_Provider.h"
#include "XYZ_Gadget_Class_Provider.h"
#include "XYZ_Assoc_Class_Provider.h"
#include "XYZ_Widget2_Class_Provider.h"
#include "XYZ_Gadget2_Class_Provider.h"
#include "XYZ_Assoc2_Class_Provider.h"

using namespace mi;

MI_EXTERN_C void MI_CALL XYZ_Widget_Load(
    XYZ_Widget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    XYZ_Widget_Class_Provider* prov = new XYZ_Widget_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (XYZ_Widget_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL XYZ_Widget_Unload(
    XYZ_Widget_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    XYZ_Widget_Class_Provider* prov = (XYZ_Widget_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((XYZ_Widget_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL XYZ_Gadget_Load(
    XYZ_Gadget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    XYZ_Gadget_Class_Provider* prov = new XYZ_Gadget_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (XYZ_Gadget_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL XYZ_Gadget_Unload(
    XYZ_Gadget_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    XYZ_Gadget_Class_Provider* prov = (XYZ_Gadget_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((XYZ_Gadget_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc_Load(
    XYZ_Assoc_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    XYZ_Assoc_Class_Provider* prov = new XYZ_Assoc_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (XYZ_Assoc_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc_Unload(
    XYZ_Assoc_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    XYZ_Assoc_Class_Provider* prov = (XYZ_Assoc_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((XYZ_Assoc_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc_EnumerateInstances(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    XYZ_Assoc_Class_Provider* cxxSelf =((XYZ_Assoc_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc_GetInstance(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc* instanceName,
    const MI_PropertySet* propertySet)
{
    XYZ_Assoc_Class_Provider* cxxSelf =((XYZ_Assoc_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Assoc_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL XYZ_Assoc_CreateInstance(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc* newInstance)
{
    XYZ_Assoc_Class_Provider* cxxSelf =((XYZ_Assoc_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Assoc_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc_ModifyInstance(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    XYZ_Assoc_Class_Provider* cxxSelf =((XYZ_Assoc_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Assoc_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL XYZ_Assoc_DeleteInstance(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc* instanceName)
{
    XYZ_Assoc_Class_Provider* cxxSelf =((XYZ_Assoc_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Assoc_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc_AssociatorInstancesLeft(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    XYZ_Assoc_Class_Provider* cxxSelf =((XYZ_Assoc_Class_Provider*)self);
    XYZ_Widget_Class cxxInstanceName(instanceName, true);
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

MI_EXTERN_C void MI_CALL XYZ_Assoc_AssociatorInstancesRight(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    XYZ_Assoc_Class_Provider* cxxSelf =((XYZ_Assoc_Class_Provider*)self);
    XYZ_Gadget_Class cxxInstanceName(instanceName, true);
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

MI_EXTERN_C void MI_CALL XYZ_Assoc_ReferenceInstancesLeft(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const XYZ_Widget* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    XYZ_Assoc_Class_Provider* cxxSelf =((XYZ_Assoc_Class_Provider*)self);
    XYZ_Widget_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstancesLeft(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc_ReferenceInstancesRight(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const XYZ_Gadget* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    XYZ_Assoc_Class_Provider* cxxSelf =((XYZ_Assoc_Class_Provider*)self);
    XYZ_Gadget_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstancesRight(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL XYZ_Widget2_Load(
    XYZ_Widget2_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    XYZ_Widget2_Class_Provider* prov = new XYZ_Widget2_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (XYZ_Widget2_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL XYZ_Widget2_Unload(
    XYZ_Widget2_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    XYZ_Widget2_Class_Provider* prov = (XYZ_Widget2_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((XYZ_Widget2_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL XYZ_Widget2_EnumerateInstances(
    XYZ_Widget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    XYZ_Widget2_Class_Provider* cxxSelf =((XYZ_Widget2_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL XYZ_Widget2_GetInstance(
    XYZ_Widget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget2* instanceName,
    const MI_PropertySet* propertySet)
{
    XYZ_Widget2_Class_Provider* cxxSelf =((XYZ_Widget2_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Widget2_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL XYZ_Widget2_CreateInstance(
    XYZ_Widget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget2* newInstance)
{
    XYZ_Widget2_Class_Provider* cxxSelf =((XYZ_Widget2_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Widget2_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL XYZ_Widget2_ModifyInstance(
    XYZ_Widget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget2* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    XYZ_Widget2_Class_Provider* cxxSelf =((XYZ_Widget2_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Widget2_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL XYZ_Widget2_DeleteInstance(
    XYZ_Widget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget2* instanceName)
{
    XYZ_Widget2_Class_Provider* cxxSelf =((XYZ_Widget2_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Widget2_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL XYZ_Gadget2_Load(
    XYZ_Gadget2_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    XYZ_Gadget2_Class_Provider* prov = new XYZ_Gadget2_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (XYZ_Gadget2_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL XYZ_Gadget2_Unload(
    XYZ_Gadget2_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    XYZ_Gadget2_Class_Provider* prov = (XYZ_Gadget2_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((XYZ_Gadget2_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL XYZ_Gadget2_EnumerateInstances(
    XYZ_Gadget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    XYZ_Gadget2_Class_Provider* cxxSelf =((XYZ_Gadget2_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL XYZ_Gadget2_GetInstance(
    XYZ_Gadget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget2* instanceName,
    const MI_PropertySet* propertySet)
{
    XYZ_Gadget2_Class_Provider* cxxSelf =((XYZ_Gadget2_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Gadget2_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL XYZ_Gadget2_CreateInstance(
    XYZ_Gadget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget2* newInstance)
{
    XYZ_Gadget2_Class_Provider* cxxSelf =((XYZ_Gadget2_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Gadget2_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL XYZ_Gadget2_ModifyInstance(
    XYZ_Gadget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget2* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    XYZ_Gadget2_Class_Provider* cxxSelf =((XYZ_Gadget2_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Gadget2_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL XYZ_Gadget2_DeleteInstance(
    XYZ_Gadget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget2* instanceName)
{
    XYZ_Gadget2_Class_Provider* cxxSelf =((XYZ_Gadget2_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Gadget2_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc2_Load(
    XYZ_Assoc2_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    XYZ_Assoc2_Class_Provider* prov = new XYZ_Assoc2_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (XYZ_Assoc2_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc2_Unload(
    XYZ_Assoc2_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    XYZ_Assoc2_Class_Provider* prov = (XYZ_Assoc2_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((XYZ_Assoc2_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc2_EnumerateInstances(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    XYZ_Assoc2_Class_Provider* cxxSelf =((XYZ_Assoc2_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc2_GetInstance(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc2* instanceName,
    const MI_PropertySet* propertySet)
{
    XYZ_Assoc2_Class_Provider* cxxSelf =((XYZ_Assoc2_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Assoc2_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL XYZ_Assoc2_CreateInstance(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc2* newInstance)
{
    XYZ_Assoc2_Class_Provider* cxxSelf =((XYZ_Assoc2_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Assoc2_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc2_ModifyInstance(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc2* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    XYZ_Assoc2_Class_Provider* cxxSelf =((XYZ_Assoc2_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Assoc2_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL XYZ_Assoc2_DeleteInstance(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc2* instanceName)
{
    XYZ_Assoc2_Class_Provider* cxxSelf =((XYZ_Assoc2_Class_Provider*)self);
    Context  cxxContext(context);
    XYZ_Assoc2_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc2_AssociatorInstancesLeft(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget2* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    XYZ_Assoc2_Class_Provider* cxxSelf =((XYZ_Assoc2_Class_Provider*)self);
    XYZ_Widget2_Class cxxInstanceName(instanceName, true);
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

MI_EXTERN_C void MI_CALL XYZ_Assoc2_AssociatorInstancesRight(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget2* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    XYZ_Assoc2_Class_Provider* cxxSelf =((XYZ_Assoc2_Class_Provider*)self);
    XYZ_Gadget2_Class cxxInstanceName(instanceName, true);
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

MI_EXTERN_C void MI_CALL XYZ_Assoc2_ReferenceInstancesLeft(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const XYZ_Widget2* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    XYZ_Assoc2_Class_Provider* cxxSelf =((XYZ_Assoc2_Class_Provider*)self);
    XYZ_Widget2_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstancesLeft(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL XYZ_Assoc2_ReferenceInstancesRight(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* resultClass,
    const XYZ_Gadget2* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    XYZ_Assoc2_Class_Provider* cxxSelf =((XYZ_Assoc2_Class_Provider*)self);
    XYZ_Gadget2_Class cxxInstanceName(instanceName, true);
    Context  cxxContext(context);

    cxxSelf->ReferenceInstancesRight(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
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
