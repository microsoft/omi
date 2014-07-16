/* @migen@ */
#include <MI.h>
#include "Perf_Indication.h"
#ifdef _MSC_VER
#include "Windows.h"
#endif
#include "ProviderUtil.h"

struct _Perf_Indication_Self
{
    MI_Context* indicationContext;

#ifdef _MSC_VER
    PTP_TIMER indicationTimer;
#endif

    MI_Uint64 keyCounter;
    MI_Boolean shutdownCalled;
};

#ifdef _MSC_VER

static void CALLBACK TimerCallback(
    __inout     PTP_CALLBACK_INSTANCE instance,
    __inout_opt PVOID                 context,
    __inout     PTP_TIMER             timer
    )
{
    MI_Result result = MI_RESULT_FAILED;
    Perf_Indication_Self* self;
    Perf_Indication indicationInstance = {{0}};

    if(!context)
    {
        return;
    }

    self = (Perf_Indication_Self*)context;

    result = Perf_Indication_Construct(&indicationInstance, self->indicationContext);
    if(result != MI_RESULT_OK)
        return;

    result = FillInstance(self->indicationContext, &indicationInstance.__instance, self->keyCounter++);
    if(result != MI_RESULT_OK)
        return;

    Perf_Indication_Post(&indicationInstance, self->indicationContext, 0, 0);
    Perf_Indication_Destruct(&indicationInstance);

    if(self->shutdownCalled != MI_TRUE)
    {    
        // Clean up the previous timer. Do not do a WaitForThreadpoolTimerCallbacks as this will not respond.
        // Instead directly call CloseThreadPoolTimer. This asynchronously closes the timer when outstanding calls are done.
        // As the timer settings are for 1 event only, there will be no outstanding calls, but only the current call.
        SetThreadpoolTimer(self->indicationTimer, NULL, 0, 0);
        CloseThreadpoolTimer(self->indicationTimer);

        FILETIME now;
        ZeroMemory(&now, sizeof(FILETIME));

        self->indicationTimer = CreateThreadpoolTimer(TimerCallback, self, NULL);
        SetThreadpoolTimer(self->indicationTimer, &now, 0, 1);
    }
}

#endif

void MI_CALL Perf_Indication_Load(
    _Outptr_result_maybenull_ Perf_Indication_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);
    *self = new Perf_Indication_Self;
    (*self)->keyCounter = 0;    
    (*self)->shutdownCalled = MI_FALSE;

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_Indication_Unload(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* context)
{
    if (self)
    {
        self->keyCounter = 0;
        delete self;
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_Indication_EnableIndications(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* indicationsContext,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className)
{
#ifdef _MSC_VER

    /* NOTE: Do not call MI_PostResult on this context */
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);

    if (self)
    {
        FILETIME now;

        ZeroMemory(&now, sizeof(FILETIME));

        self->indicationContext = indicationsContext;
        self->indicationTimer = CreateThreadpoolTimer(TimerCallback, self, NULL);
        SetThreadpoolTimer(self->indicationTimer, &now, 0, 1);
    }

#endif
}

void MI_CALL Perf_Indication_DisableIndications(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* indicationsContext,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className)
{
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);

#ifdef _MSC_VER
    if (self)
    {
        self->indicationContext = 0;

        self->shutdownCalled = MI_TRUE;

        SetThreadpoolTimer(self->indicationTimer, NULL, 0, 0);
        WaitForThreadpoolTimerCallbacks(self->indicationTimer, TRUE);
        CloseThreadpoolTimer(self->indicationTimer);

        self->shutdownCalled = MI_FALSE;
    }

#endif

    MI_PostResult(indicationsContext, MI_RESULT_OK);
}

void MI_CALL Perf_Indication_Subscribe(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_Filter* filter,
    _In_opt_z_ const MI_Char* bookmark,
    _In_ MI_Uint64  subscriptionID,
    _Outptr_result_maybenull_ void** subscriptionSelf)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(context);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(filter);
    MI_UNREFERENCED_PARAMETER(bookmark);
    MI_UNREFERENCED_PARAMETER(subscriptionID);
    *subscriptionSelf = NULL;

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_Indication_Unsubscribe(
    _In_opt_ Perf_Indication_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ MI_Uint64  subscriptionID,
    _In_opt_ void* subscriptionSelf)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(subscriptionID);
    MI_UNREFERENCED_PARAMETER(subscriptionSelf);

    MI_PostResult(context, MI_RESULT_OK);
}

