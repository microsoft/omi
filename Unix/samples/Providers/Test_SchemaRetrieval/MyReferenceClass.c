/* @migen@ */
#include <MI.h>
#include "MyReferenceClass.h"

void MI_CALL MyReferenceClass_Load(
    MyReferenceClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyReferenceClass_Unload(
    MyReferenceClass_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyReferenceClass_Invoke_GetReferenceValue(
    MyReferenceClass_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyReferenceClass* instanceName,
    const MyReferenceClass_GetReferenceValue* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

