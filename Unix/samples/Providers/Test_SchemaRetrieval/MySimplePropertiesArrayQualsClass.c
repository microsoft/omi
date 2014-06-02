/* @migen@ */
#include <MI.h>
#include "MySimplePropertiesArrayQualsClass.h"

void MI_CALL MySimplePropertiesArrayQualsClass_Load(
    MySimplePropertiesArrayQualsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MySimplePropertiesArrayQualsClass_Unload(
    MySimplePropertiesArrayQualsClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

