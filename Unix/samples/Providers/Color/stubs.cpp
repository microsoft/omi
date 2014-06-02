/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not
** use this file except in compliance with the License. You may obtain a copy
** of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
** MERCHANTABLITY OR NON-INFRINGEMENT.
**
** See the Apache 2 License for the specific language governing permissions
** and limitations under the License.
**
**==============================================================================
*/

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
#include "ColorBase_Class_Provider.h"
#include "Color_Class_Provider.h"

using namespace mi;

MI_EXTERN_C void MI_CALL ColorBase_Load(
    ColorBase_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    ColorBase_Class_Provider* prov = new ColorBase_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (ColorBase_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL ColorBase_Unload(
    ColorBase_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    ColorBase_Class_Provider* prov = (ColorBase_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((ColorBase_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL ColorBase_EnumerateInstances(
    ColorBase_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    ColorBase_Class_Provider* cxxSelf =((ColorBase_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL ColorBase_GetInstance(
    ColorBase_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ColorBase* instanceName,
    const MI_PropertySet* propertySet)
{
    ColorBase_Class_Provider* cxxSelf =((ColorBase_Class_Provider*)self);
    Context  cxxContext(context);
    ColorBase_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL ColorBase_CreateInstance(
    ColorBase_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ColorBase* newInstance)
{
    ColorBase_Class_Provider* cxxSelf =((ColorBase_Class_Provider*)self);
    Context  cxxContext(context);
    ColorBase_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL ColorBase_ModifyInstance(
    ColorBase_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ColorBase* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    ColorBase_Class_Provider* cxxSelf =((ColorBase_Class_Provider*)self);
    Context  cxxContext(context);
    ColorBase_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL ColorBase_DeleteInstance(
    ColorBase_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ColorBase* instanceName)
{
    ColorBase_Class_Provider* cxxSelf =((ColorBase_Class_Provider*)self);
    Context  cxxContext(context);
    ColorBase_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL Color_Load(
    Color_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Color_Class_Provider* prov = new Color_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_PostResult(context, r);
        return;
    }
    *self = (Color_Self*)prov;
    MI_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL Color_Unload(
    Color_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    Color_Class_Provider* prov = (Color_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((Color_Class_Provider*)self);
    MI_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL Color_EnumerateInstances(
    Color_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Color_Class_Provider* cxxSelf =((Color_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL Color_GetInstance(
    Color_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Color* instanceName,
    const MI_PropertySet* propertySet)
{
    Color_Class_Provider* cxxSelf =((Color_Class_Provider*)self);
    Context  cxxContext(context);
    Color_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Color_CreateInstance(
    Color_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Color* newInstance)
{
    Color_Class_Provider* cxxSelf =((Color_Class_Provider*)self);
    Context  cxxContext(context);
    Color_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL Color_ModifyInstance(
    Color_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Color* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    Color_Class_Provider* cxxSelf =((Color_Class_Provider*)self);
    Context  cxxContext(context);
    Color_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL Color_DeleteInstance(
    Color_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Color* instanceName)
{
    Color_Class_Provider* cxxSelf =((Color_Class_Provider*)self);
    Context  cxxContext(context);
    Color_Class cxxInstanceName(instanceName, true);

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
    module.flags |= MI_MODULE_FLAG_FILTER_SUPPORT;
    module.charSize = sizeof(MI_Char);
    module.version = MI_VERSION;
    module.generatorVersion = MI_MAKE_VERSION(1,0,0);
    module.schemaDecl = &schemaDecl;
    module.Load = Load;
    module.Unload = Unload;
    return &module;
}

