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
#include "Main_Class_Provider.h"
#include "EmbeddedInstance_Class_Provider.h"

using namespace mi;

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

MI_EXTERN_C void MI_CALL EmbeddedInstance_Load(
    EmbeddedInstance_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    EmbeddedInstance_Class_Provider* prov = new EmbeddedInstance_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (EmbeddedInstance_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL EmbeddedInstance_Unload(
    EmbeddedInstance_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    EmbeddedInstance_Class_Provider* prov = (EmbeddedInstance_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((EmbeddedInstance_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL EmbeddedInstance_EnumerateInstances(
    EmbeddedInstance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    EmbeddedInstance_Class_Provider* cxxSelf =((EmbeddedInstance_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL EmbeddedInstance_GetInstance(
    EmbeddedInstance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const EmbeddedInstance* instanceName,
    const MI_PropertySet* propertySet)
{
    EmbeddedInstance_Class_Provider* cxxSelf =((EmbeddedInstance_Class_Provider*)self);
    Context  cxxContext(context);
    EmbeddedInstance_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL EmbeddedInstance_CreateInstance(
    EmbeddedInstance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const EmbeddedInstance* newInstance)
{
    EmbeddedInstance_Class_Provider* cxxSelf =((EmbeddedInstance_Class_Provider*)self);
    Context  cxxContext(context);
    EmbeddedInstance_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL EmbeddedInstance_ModifyInstance(
    EmbeddedInstance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const EmbeddedInstance* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    EmbeddedInstance_Class_Provider* cxxSelf =((EmbeddedInstance_Class_Provider*)self);
    Context  cxxContext(context);
    EmbeddedInstance_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL EmbeddedInstance_DeleteInstance(
    EmbeddedInstance_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const EmbeddedInstance* instanceName)
{
    EmbeddedInstance_Class_Provider* cxxSelf =((EmbeddedInstance_Class_Provider*)self);
    Context  cxxContext(context);
    EmbeddedInstance_Class cxxInstanceName(instanceName, true);

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

