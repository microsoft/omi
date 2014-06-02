/* @migen@ */
#include <MI.h>
#include "MyArrayPropertiesArrayQualsClass.h"

void MI_CALL MyArrayPropertiesArrayQualsClass_Load(
    MyArrayPropertiesArrayQualsClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyArrayPropertiesArrayQualsClass_Unload(
    MyArrayPropertiesArrayQualsClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

