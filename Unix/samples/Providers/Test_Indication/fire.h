/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _fire_h
#define _fire_h


#ifdef _MSC_VER
#include <windows.h>
#endif
#include <MI.h>
#include <pal/file.h>
#include <pal/thread.h>
#include <pal/sleep.h>
#include <pal/sem.h>
#include <base/batch.h>
#include <tests/util/indiprvdconfig.h>
#include "impl.h"

/* thread proc to fire indications based on the config */
PAL_Uint32 THREAD_API fireindication(void* param);
PAL_Uint32 THREAD_API fireLifecycleEvents(void* param);


/* global config objects */
extern Config cfgTest_Indication;
extern Config cfgL_IndicationC1;
extern Config cfgL_IndicationC2;
extern Config cfgL_IndicationC3;
extern Config cfgR_IndicationC1;
extern Config cfgR_IndicationC2;
extern Config cfgR_IndicationC3;
extern Config cfgTest_Class;
extern Config cfgL_LifecycleC1; 
extern Config cfgL_LifecycleC2; 
extern Config cfgR_LifecycleC1; 
extern Config cfgR_LifecycleC2; 

/* Initialize config for all classes */
void ReloadConfig();
MI_Result Initialize();
MI_Result Finalize();

#endif /* _fire_h */
