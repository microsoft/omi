/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include "OMI_OctetStrings.h"

void MI_CALL OMI_OctetStrings_Load(
    OMI_OctetStrings_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL OMI_OctetStrings_Unload(
    OMI_OctetStrings_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL OMI_OctetStrings_EnumerateInstances(
    OMI_OctetStrings_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    OMI_OctetStrings inst;
    OMI_OctetStrings_Construct(&inst, context);
    OMI_OctetStrings_Set_Key(&inst, "OMI_OctetStrings.1");

    {
        MI_Uint8 data[] = { 0, 0, 0, 9, 'h', 'e', 'l', 'l', 'o', };
        OMI_OctetStrings_Set_Data1(&inst, data, MI_COUNT(data));
    }

    OMI_OctetStrings_Set_Str(&inst, " &\'\"><");

    OMI_OctetStrings_Post(&inst, context);


    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL OMI_OctetStrings_GetInstance(
    OMI_OctetStrings_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_OctetStrings* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_OctetStrings_CreateInstance(
    OMI_OctetStrings_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_OctetStrings* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_OctetStrings_ModifyInstance(
    OMI_OctetStrings_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_OctetStrings* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL OMI_OctetStrings_DeleteInstance(
    OMI_OctetStrings_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_OctetStrings* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

