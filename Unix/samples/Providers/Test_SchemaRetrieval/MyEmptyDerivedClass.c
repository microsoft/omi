/* @migen@ */
#include <MI.h>
#include "MyEmptyDerivedClass.h"

void MI_CALL MyEmptyDerivedClass_Load(
    MyEmptyDerivedClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyEmptyDerivedClass_Unload(
    MyEmptyDerivedClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

