/* @migen@ */
#include <MI.h>
#include "MyEmbeddedPropertiesClass.h"

void MI_CALL MyEmbeddedPropertiesClass_Load(
    MyEmbeddedPropertiesClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyEmbeddedPropertiesClass_Unload(
    MyEmbeddedPropertiesClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

