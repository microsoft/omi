/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "indicommon.h"
#include <pal/atomic.h>
#include <pal/strings.h>

typedef struct _LifecycleIndicationClass
{
    MI_ConstString name;
    SubscriptionTargetType targetType;
}LifecycleIndicationClass;

/* list of lifecycle classes */
LifecycleIndicationClass g_cLifecycleClasses[] = {
    { MI_T("CIM_InstIndication"), SUBSCRIP_TARGET_LIFECYCLE_ALL },
    { MI_T("CIM_InstCreation"), SUBSCRIP_TARGET_LIFECYCLE_CREATE },
    { MI_T("CIM_InstModification"), SUBSCRIP_TARGET_LIFECYCLE_MODIFY },
    { MI_T("CIM_InstDeletion"), SUBSCRIP_TARGET_LIFECYCLE_DELETE },
    { MI_T("CIM_InstRead"), SUBSCRIP_TARGET_LIFECYCLE_READ },
    { MI_T("CIM_InstMethodCall"), SUBSCRIP_TARGET_LIFECYCLE_METHODCALL },
    { NULL, SUBSCRIP_TARGET_UNSUPPORTED},
};

/* 
* Get SubscriptionTargetType if given class is lifecycle class,
* otherwise return SUBSCRIP_TARGET_DEFAULT;
*/
_Use_decl_annotations_
SubscriptionTargetType GetSubscriptionTargetType(MI_ConstString name)
{
    LifecycleIndicationClass *cls;
    DEBUG_ASSERT(name);
    cls = &g_cLifecycleClasses[0];
    while (cls->name)
    {
        if (Tcscasecmp(cls->name, name) == 0)
            return cls->targetType;
        cls++;
    }
    return SUBSCRIP_TARGET_DEFAULT;
}

/* global subscription ID variable */
ptrdiff_t g_SubscriptionID = 1;

/* Generate an unique subscription ID */
MI_Uint64 GenerateSubscriptionID()
{
    return (MI_Uint64)Atomic_Inc(&g_SubscriptionID);
}

