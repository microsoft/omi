/* @migen@ */
#include <MI.h>
#include "MyClassRestrictedQualsOnBaseElements.h"

void MI_CALL MyClassRestrictedQualsOnBaseElements_Load(
    MyClassRestrictedQualsOnBaseElements_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyClassRestrictedQualsOnBaseElements_Unload(
    MyClassRestrictedQualsOnBaseElements_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MyClassRestrictedQualsOnBaseElements_Invoke_myMethod(
    MyClassRestrictedQualsOnBaseElements_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MyClassRestrictedQualsOnBaseElements* instanceName,
    const MyClassRestrictedQualsOnBaseElements_myMethod* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

