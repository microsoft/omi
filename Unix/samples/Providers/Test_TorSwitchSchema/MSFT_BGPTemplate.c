/* @migen@ */
#include <MI.h>
#include "MSFT_BGPTemplate.h"

void MI_CALL MSFT_BGPTemplate_Load(
    _Outptr_result_maybenull_ MSFT_BGPTemplate_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_BGPTemplate_Unload(
    _In_opt_ MSFT_BGPTemplate_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

