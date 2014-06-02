/* @migen@ */
#include <stdlib.h>
#include <MI.h>
#include "Datetime.h"

void MI_CALL Datetime_Load(
    Datetime_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Datetime_Unload(
    Datetime_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Datetime_EnumerateInstances(
    Datetime_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Datetime inst;
    Datetime_Construct(&inst, context);
    MI_Datetime iv;
    MI_Datetime ts;

    memset(&ts, 0, sizeof(ts));
    ts.isTimestamp = MI_TRUE;
    ts.u.timestamp.year = 2001;
    ts.u.timestamp.month = 12;
    ts.u.timestamp.month = 25;

    memset(&iv, 0, sizeof(iv));
    iv.isTimestamp = MI_FALSE;
    iv.u.interval.days = 365;
    iv.u.interval.hours = 24;
    iv.u.interval.minutes = 60;

    // Datetime.timestamp:
    Datetime_Set_timestamp(&inst, ts);

    // Datetime.timestamp:
    Datetime_Set_interval(&inst, iv);

    // Datetime.timestamps:
    {
        MI_Datetime data[2];
        data[0] = ts;
        data[1] = ts;
        Datetime_Set_timestamps(&inst, data, MI_COUNT(data));
    }

    // Datetime.interval:
    {
        MI_Datetime data[2];
        data[0] = iv;
        data[1] = iv;
        Datetime_Set_intervals(&inst, data, MI_COUNT(data));
    }

    // Datetime.interval:
    {
        MI_Datetime data[2];
        data[0] = ts;
        data[1] = iv;
        Datetime_Set_mixed(&inst, data, MI_COUNT(data));
    }

    Datetime_Post(&inst, context);
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Datetime_GetInstance(
    Datetime_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Datetime* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Datetime_CreateInstance(
    Datetime_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Datetime* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Datetime_ModifyInstance(
    Datetime_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Datetime* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Datetime_DeleteInstance(
    Datetime_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Datetime* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

