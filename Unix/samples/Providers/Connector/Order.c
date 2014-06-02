/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
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

