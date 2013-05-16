/* @migen@ */
#include <MI.h>
#include "OMI_NetworkVLAN.h"
#include <io/io.h>

void MI_CALL OMI_NetworkVLAN_Load(
    OMI_NetworkVLAN_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL OMI_NetworkVLAN_Unload(
    OMI_NetworkVLAN_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL OMI_NetworkVLAN_EnumerateInstances(
    OMI_NetworkVLAN_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    OMI_NetworkVLAN inst;
    size_t i;

    OMI_NetworkVLAN_Construct(&inst, context);

    for (i = 0; i < 10000; i++)
    {
        // OMI_NetworkVLAN.InstanceID:
        {
            MI_Char buf[32];
            Snprintf(buf, sizeof(buf), MI_T("DEVICEID:%u"), i);
            OMI_NetworkVLAN_Set_InstanceID(&inst, buf);
        }

        OMI_NetworkVLAN_Set_Caption(&inst, MI_T("My Caption"));
        OMI_NetworkVLAN_Set_Description(&inst, MI_T("My Description"));
        OMI_NetworkVLAN_Set_ElementName(&inst, MI_T("My Element Name"));
        OMI_NetworkVLAN_Set_ConnectivityStatus(&inst, 1);
        OMI_NetworkVLAN_Set_VLANId(&inst, 2);
        OMI_NetworkVLAN_Set_SAIdentifier(&inst, 3);
        OMI_NetworkVLAN_Set_TransmissionSize(&inst, 4);
        OMI_NetworkVLAN_Set_TypeOfMedia(&inst, 5);
        OMI_NetworkVLAN_Set_OtherTypeDescription(&inst, MI_T("My Other Type Description"));
        OMI_NetworkVLAN_Set_IsEnabled(&inst, MI_FALSE);
        OMI_NetworkVLAN_Post(&inst, context);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL OMI_NetworkVLAN_GetInstance(
    OMI_NetworkVLAN_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_NetworkVLAN* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_NetworkVLAN_CreateInstance(
    OMI_NetworkVLAN_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_NetworkVLAN* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_NetworkVLAN_ModifyInstance(
    OMI_NetworkVLAN_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_NetworkVLAN* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_NetworkVLAN_DeleteInstance(
    OMI_NetworkVLAN_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_NetworkVLAN* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

