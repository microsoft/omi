/* @migen@ */
#include <MI.h>

MI_EXTERN_C MI_SchemaDecl schemaDecl;

void MI_CALL Load(_Outptr_result_maybenull_ MI_Module_Self** self, _In_ struct _MI_Context* context)
{
    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Unload(_In_opt_ MI_Module_Self* self, _In_ struct _MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(context);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C MI_EXPORT MI_Module* MI_MAIN_CALL MI_Main(_In_ MI_Server* server)
{
    /* WARNING: THIS FUNCTION AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT. */
    static MI_Module module;
    MI_EXTERN_C MI_Server* __mi_server;
    __mi_server = server;
    module.flags |= MI_MODULE_FLAG_DESCRIPTIONS;
    module.flags |= MI_MODULE_FLAG_VALUES;
    module.flags |= MI_MODULE_FLAG_BOOLEANS;
    module.charSize = sizeof(MI_Char);
    module.version = MI_VERSION;
    module.generatorVersion = MI_MAKE_VERSION(1,0,0);
    module.schemaDecl = &schemaDecl;
    module.Load = Load;
    module.Unload = Unload;
    return &module;
}
