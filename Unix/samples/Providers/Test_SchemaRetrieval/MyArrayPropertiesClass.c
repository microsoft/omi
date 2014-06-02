/* @migen@ */
#include <MI.h>
#include "MyArrayPropertiesClass.h"

void MI_CALL MyArrayPropertiesClass_Load(
    MyArrayPropertiesClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyArrayPropertiesClass_Unload(
    MyArrayPropertiesClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

