/* @migen@ */
#include <MI.h>
#include "MySimplePropertiesSimpleQualsClass.h"

void MI_CALL MySimplePropertiesSimpleQualsClass_Load(
    MySimplePropertiesSimpleQualsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MySimplePropertiesSimpleQualsClass_Unload(
    MySimplePropertiesSimpleQualsClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

