#ifndef _oi_noop_h
#define _oi_noop_h

#include "oi.h"
#include <base/log.h>

#define OILOGSYSTEM_NOOP

unsigned long OIActivityId(OIActivityControlCode controlcode, OIGUID * activityId) { return 0; }
PAL_INLINE void trace_EventTransfer(_Inout_opt_ OIGUID * activity, _Inout_ OIGUID * related) {}

#endif /* _oi_noop_h */
