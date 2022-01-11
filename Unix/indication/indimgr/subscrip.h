/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _indication_indimgr_subscrip_h
#define _indication_indimgr_subscrip_h

#include <common.h>
#include "filter.h"
#include "listener.h"
#include "classlist.h"

#define TEMP_SUBSCRIPTION_ID_PREFIX MI_T("_tempsubscription")

BEGIN_EXTERNC

/*
**==============================================================================
**
** Defines subscription persistent type
**
**==============================================================================
*/
typedef enum _SubscriptionPersistType
{
    SUBSCRIP_PER_TEMPORARY,      /* Subscription does not survive reboot */
                    /* It created by Subscribe* API call */

    SUBSCRIP_PER_PERMANENT,      /* Subscription can survive cross server reboot */
                    /* It requires both filter and handler are persist x-reboot */

    SUBSCRIP_PER_TRANSIENT       /* Subscription does not survive reboot */
                    /* It created by CreateInstance of CIM_*Subscription class */
}
SubscriptionPersistType;

/*
**==============================================================================
**
** Represents a CIM_IndicationSubscription OR CIM_FilterCollectionSubscription
** instance; Both are association classes that associate Filter and Listener
** objects.
**
**==============================================================================
*/
typedef struct _Subscription
{
    CimBase base;

    /* CIM_AbstractIndicationSubscription properties */
    FilterBase* filter; /* Either a filter or filter collection */
    Listener* listener;

#if 0 /* To be enabled for indication profile */

    MI_Uint16 OnFatalErrorPolicy; /* 1:Other, 2:Ignore, 3:Disable, 4:Remove */
    MI_Char* OtherOnFatalErrorPolicy;
    MI_Uint64 FailureTriggerTimeInterval; /* seconds */
    MI_Uint16 SubscriptionState; /* 0:Unknown, 1:Other, 2:Enabled, 3:Enabled Degraded, 4:Disabled */
    MI_Uint16 OtherSubscriptionState;
    MI_Datetime TimeOfLastStateChange;
    MI_Uint64 SubscriptionDuration; /* seconds */
    MI_Datetime SubscriptionStartTime;
    MI_Uint64 SubscriptionTimeRemaining; /* seconds */
    MI_Uint16 RepeatNotificationPolicy; /* 0:Unknown, 1:Other, 2:None, 3:Suppress, 4:Delay */
    MI_Char * OtherRepeatNotificationPolicy;
    MI_Uint64 RepeatNotificationInterval; /* seconds */
    MI_Uint64 RepeatNotificationGap; /* seconds */
    MI_Uint16 RepeatNotificationCount;

#endif

    SubscriptionPersistType persistType; /* subscription type */
    MI_Uint64 subscriptionID; /* Internal subscription ID, Unique cross process */

    IndicationClassList* classlist; /* List of indication target class */

    MI_Instance* lastError; /* last error details */
    MI_Result lastErrorCode;
}
Subscription;

extern CimBaseFT g_subscriptionft;

/* Creates a subscription object */
/* Subscription object holds reference to both filter and listener upon succeed */
Subscription* Subscription_New(_In_ FilterBase *filter, _In_ Listener* listener);

/* Add a reference to a subscription object */
int Subscription_AddRef(_Inout_ Subscription* self);

/* Release a reference to a subscription object */
int Subscription_Release(_Inout_ Subscription* self);

/* Get reference count */
int Subscription_GetRefcount(_In_ Subscription* self);

/* Check if given object is a Subscription */
MI_Boolean CimBase_IsSubscription(_In_ CimBase* self);

END_EXTERNC

#endif /* _indication_indimgr_subscrip_h */
