/* @migen@ */
#include <MI.h>
#include "MyEmptySecondDerivedClass.h"

void MI_CALL MyEmptySecondDerivedClass_Load(
    MyEmptySecondDerivedClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyEmptySecondDerivedClass_Unload(
    MyEmptySecondDerivedClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

