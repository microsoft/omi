/* @migen@ */
#include <MI.h>
#include "MSFT_BaseAddressFamily.h"

void MI_CALL MSFT_BaseAddressFamily_Load(
    _Outptr_result_maybenull_ MSFT_BaseAddressFamily_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_BaseAddressFamily_Unload(
    _In_opt_ MSFT_BaseAddressFamily_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

