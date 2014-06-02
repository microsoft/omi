/* @migen@ */
#include <MI.h>
#include "MyArrayQualClass.h"

void MI_CALL MyArrayQualClass_Load(
    MyArrayQualClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyArrayQualClass_Unload(
    MyArrayQualClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

