/* @migen@ */
#include <MI.h>
#include "MySimplePropertiesClass.h"

void MI_CALL MySimplePropertiesClass_Load(
    MySimplePropertiesClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MySimplePropertiesClass_Unload(
    MySimplePropertiesClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

