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
#include "OMI_Tester_Class_Provider.h"

using namespace mi;

MI_EXTERN_C void MI_CALL OMI_Tester_Load(
    OMI_Tester_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    OMI_Tester_Class_Provider* prov = new OMI_Tester_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (OMI_Tester_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL OMI_Tester_Unload(
    OMI_Tester_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    OMI_Tester_Class_Provider* prov = (OMI_Tester_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((OMI_Tester_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL OMI_Tester_EnumerateInstances(
    OMI_Tester_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    OMI_Tester_Class_Provider* cxxSelf =((OMI_Tester_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL OMI_Tester_GetInstance(
    OMI_Tester_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_Tester* instanceName,
    const MI_PropertySet* propertySet)
{
    OMI_Tester_Class_Provider* cxxSelf =((OMI_Tester_Class_Provider*)self);
    Context  cxxContext(context);
    OMI_Tester_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL OMI_Tester_CreateInstance(
    OMI_Tester_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_Tester* newInstance)
{
    OMI_Tester_Class_Provider* cxxSelf =((OMI_Tester_Class_Provider*)self);
    Context  cxxContext(context);
    OMI_Tester_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL OMI_Tester_ModifyInstance(
    OMI_Tester_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_Tester* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    OMI_Tester_Class_Provider* cxxSelf =((OMI_Tester_Class_Provider*)self);
    Context  cxxContext(context);
    OMI_Tester_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL OMI_Tester_DeleteInstance(
    OMI_Tester_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_Tester* instanceName)
{
    OMI_Tester_Class_Provider* cxxSelf =((OMI_Tester_Class_Provider*)self);
    Context  cxxContext(context);
    OMI_Tester_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL OMI_Tester_Invoke_Func1(
    OMI_Tester_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_Tester* instanceName,
    const OMI_Tester_Func1* in)
{
    OMI_Tester_Class_Provider* cxxSelf =((OMI_Tester_Class_Provider*)self);
    OMI_Tester_Class instance(instanceName, false);
    Context  cxxContext(context);
    OMI_Tester_Func1_Class param(in, false);

    cxxSelf->Invoke_Func1(cxxContext, nameSpace, instance, param);
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
    module.flags |= MI_MODULE_FLAG_CPLUSPLUS;
    module.charSize = sizeof(MI_Char);
    module.version = MI_VERSION;
    module.generatorVersion = MI_MAKE_VERSION(1,0,0);
    module.schemaDecl = &schemaDecl;
    module.Load = Load;
    module.Unload = Unload;
    return &module;
}
