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

//==============================================================================
//
// cmodule.h - source code template for generating 'module.c'.
//
//==============================================================================

#ifndef _migen_cmodule_t_h
#define _migen_cmodule_t_h

//==============================================================================
//
// MODULE_C_TEMPLATE
//
//==============================================================================

#define MODULE_C_TEMPLATE_1 "\
#include <MI.h>\n\
\n\
MI_EXTERN_C MI_SchemaDecl <SCHEMADECL>;\n\
\n\
void MI_CALL Load(MI_Module_Self** self, struct _MI_Context* context)\n\
{\n\
    *self = NULL;\n\
    MI_Context_PostResult(context, MI_RESULT_OK);\n\
}\n\
\n\
void MI_CALL Unload(MI_Module_Self* self, struct _MI_Context* context)\n\
{\n\
    MI_Context_PostResult(context, MI_RESULT_OK);\n\
}\n\
\n"

#define MODULE_C_TEMPLATE_2 "\
MI_EXTERN_C MI_EXPORT MI_Module* MI_MAIN_CALL <ENTRYPOINT>(MI_Server* server)\n\
{\n\
    /* WARNING: THIS FUNCTION AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT. */\n\
    extern MI_Server* __mi_server;\n\
    static MI_Module module;\n\
    __mi_server = server;\n";

#define MODULE_C_TEMPLATE_3 "\
    module.charSize = sizeof(MI_Char);\n\
    module.version = MI_VERSION;\n\
    module.generatorVersion = <VERSION>;\n\
    module.schemaDecl = &<SCHEMADECL>;\n\
    module.Load = Load;\n\
    module.Unload = Unload;\n\
    return &module;\n\
}"

#define STUBS_LOAD_UNLOAD_TEMPLATE "\
\n\
MI_EXTERN_C MI_SchemaDecl <SCHEMADECL>;\n\
\n\
void MI_CALL Load(MI_Module_Self** self, struct _MI_Context* context)\n\
{\n\
    *self = (MI_Module_Self*)new Module;\n\
    MI_Context_PostResult(context, MI_RESULT_OK);\n\
}\n\
\n\
void MI_CALL Unload(MI_Module_Self* self, struct _MI_Context* context)\n\
{\n\
    Module* module = (Module*)self;\n\
    delete module;\n\
    MI_Context_PostResult(context, MI_RESULT_OK);\n\
}\n\
\n"

#endif /* _migen_cmodule_t_h */
