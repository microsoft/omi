/* @migen@ */
#include <MI.h>
#include "MySimpleQualClass.h"

void MI_CALL MySimpleQualClass_Load(
    MySimpleQualClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MySimpleQualClass_Unload(
    MySimpleQualClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

