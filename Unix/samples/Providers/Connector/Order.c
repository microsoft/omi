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
#include "Order.h"
#include "Threads.h"

static LockType lock;
static int done;

/* Post an indication every 100 milliseconds until done */
void IndicationThread(void* arg)
{
    MI_Context* context = (MI_Context*)arg;

    /* Loop until done flag is set */
    for (;;)
    {
        /* Check whether global done flag was set */
        {
            int flag;

            Lock(&lock);
            flag = done;
            Unlock(&lock);

            if (flag)
            {
                MI_PostResult(context, MI_RESULT_OK);
                return;
            }
        }

        /* Post one indication */
        {
            Order order;
            Order_Construct(&order, context);
            Order_Set_SerialNumber(&order, 1001);
            Order_Set_Quantity(&order, 988);
            Order_Post(&order, context);
            Order_Destruct(&order);
        }

        /* Wait 100 milliseconds */
        Sleep(100);
    }
}

void MI_CALL Order_Load(
    Order_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Order_Unload(
    Order_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Order_EnableIndications(
    Order_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    /* Create thread to generate indications */
    if (CreateThread(IndicationThread, indicationsContext) != 0)
    {
        MI_PostResult(indicationsContext, MI_RESULT_FAILED);
    }
}

void MI_CALL Order_DisableIndications(
    Order_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    /* Signal indication thread to exit */
    Lock(&lock);
    done = 1;
    Unlock(&lock);

    MI_PostResult(indicationsContext, MI_RESULT_OK);
}

void MI_CALL Order_Subscribe(
    Order_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Order_Unsubscribe(
    Order_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

