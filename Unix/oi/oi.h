/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/


#ifndef _oi_h
#define _oi_h

// The code being instrumented should only include oi.h

#include <pal/strings.h>
#include <pal/format.h>

PAL_BEGIN_EXTERNC

#define OI_EVENT(format) PAL_INLINE
#define OI_SETDEFAULT(setting)

typedef struct _OIGUID
{
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
}
OIGUID;

/* Documentation from http://msdn.microsoft.com/en-us/library/windows/desktop/aa363720(v=vs.85).aspx */
typedef enum _OIActivityControlCode
{
    /* Sets the ActivityId parameter to the current identifier value from thread local storage. */
    OI_CTRL_GET_ID = 1,         
    
    /* Uses the identifier in the ActivityId parameter to set the value of the current identifier in the thread local storage. */
    OI_CTRL_SET_ID,         
    
    /* Creates a new identifier and sets the ActivityId parameter to the value of the new identifier. */
    OI_CTRL_CREATE_ID,      
    
    /* 
        Performs the following:
        Copies the current identifier from thread local storage.
        Sets the current identifier in thread local storage to the identifier specified in the ActivityId parameter.
        Sets the ActivityId parameter to the copy of the previous current identifier.
    */
    OI_CTRL_GET_SET_ID,     
    
    /* 
        Performs the following:
        Copies the current identifier from thread local storage.
        Creates a new identifier and sets the current identifier in thread local storage to the identifier specified in the ActivityId parameter.
        Sets the ActivityId parameter to the copy of the previous current identifier. 
    */
    OI_CTRL_CREATE_SET_ID
} OIActivityControlCode;

PAL_INLINE unsigned long OIActivityId(OIActivityControlCode controlcode, OIGUID * activityId);

/*
trace_EventTransfer

activity - optional activity id, may be NULL - current TLS value will be used
related - mandatory - related activity id
*/
PAL_INLINE void trace_EventTransfer(OIGUID * activity, OIGUID * related);

PAL_END_EXTERNC

#endif // _oi_h
