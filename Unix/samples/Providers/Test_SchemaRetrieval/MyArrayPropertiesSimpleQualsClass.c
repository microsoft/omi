/* @migen@ */
#include <MI.h>
#include "MyArrayPropertiesSimpleQualsClass.h"

void MI_CALL MyArrayPropertiesSimpleQualsClass_Load(
    MyArrayPropertiesSimpleQualsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyArrayPropertiesSimpleQualsClass_Unload(
    MyArrayPropertiesSimpleQualsClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

