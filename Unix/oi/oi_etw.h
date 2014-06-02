
#ifndef _oietw_h
#define _oietw_h

#ifdef _PREFAST_
/* Disable warnings that happen when Windows.h is included */ 
#pragma prefast(push)
#pragma prefast(disable : 28252)
#pragma prefast(disable : 28253)
#endif

#include <Windows.h>
#include <evntprov.h>
#include <stdio.h>
#include <oi/oi.h>
#include <MI.h>

#define OILOGSYSTEM_ETW

PAL_INLINE unsigned long OIActivityId(OIActivityControlCode controlcode, OIGUID * activityId)
{
    return EventActivityIdControl((ULONG) controlcode, (GUID *) activityId);
}

#ifndef ETWGUIDVALUE
#error Missing ETWGUIDVALUE, should be defined in generated code
/* #define ETWGUIDVALUE{ l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } } */
#endif

FORCEINLINE REGHANDLE EtwInitProvider()
{
    static REGHANDLE RegistrationHandle = 0;
    /* ETWGUIDVALUE should be a defined value */
    static const GUID ProviderGuid = ETWGUIDVALUE;

    if (RegistrationHandle)
        return RegistrationHandle;

    EventRegister(
        &ProviderGuid,      /* LPCGUID ProviderId */
        NULL,               /* PENABLECALLBACK EnableCallback */
        NULL,               /* PVOID CallbackContext */
        &RegistrationHandle /* PREGHANDLE RegHandle */
        );

    return RegistrationHandle;
}

/*
    level - ETW severity levels:
    1 "win:Critical",
    2 "win:Error",
    3 "win:Warning",
    4 "win:Informational",
    5 "win:Verbose"

    OMI levels:
    OMI_FATAL,  0
    OMI_ERROR,  1
    OMI_WARNING,2
    OMI_INFO,   3
    OMI_DEBUG,  4
    OMI_VERBOSE,5
*/
#if defined(OI_DONTCHECK_LOGLEVEL)
PAL_INLINE PAL_Boolean _ETWShouldLog(UCHAR level)
{
    return PAL_TRUE;
}
#else
#include "base/logbase.h"
static int _ETW2OMI[] = {0, 0, 1, 2, 3, 4};
PAL_INLINE PAL_Boolean _ETWShouldLog(UCHAR level)
{
    if (level >= (UCHAR)(sizeof(_ETW2OMI)/sizeof(int)))
        return PAL_FALSE;

    if (_ETW2OMI[level] > Log_GetLevel())
        return PAL_FALSE;
    else
        return PAL_TRUE;
}
#endif

// These functions use compiler's type knowledge 
// to do &value and sizeof(value)   for integers 
// vs     value and strlen(value)+1 for strings

#define ETW_CREATEDESC_TYPE(TYPE)                               \
    FORCEINLINE                                                 \
    VOID                                                        \
        etw_CreateDescriptor_ ## TYPE(                          \
        EVENT_DATA_DESCRIPTOR* pEventDataDescriptor,            \
        TYPE * value)                                           \
    {                                                           \
        pEventDataDescriptor->Ptr = (ULONGLONG)value;           \
        pEventDataDescriptor->Size = (ULONG)sizeof( TYPE );     \
        pEventDataDescriptor->Reserved = 0;                     \
    }

FORCEINLINE
VOID
etw_CreateDescriptor_LPCSTR(
    EVENT_DATA_DESCRIPTOR* pEventDataDescriptor,
    LPCSTR* value)
{
    pEventDataDescriptor->Ptr = (ULONGLONG)(*value);
    pEventDataDescriptor->Size =(ULONG) (*value ? strlen((*value)) + 1 : 0);
    pEventDataDescriptor->Reserved = 0;
    return;
}

FORCEINLINE
VOID
etw_CreateDescriptor_LPCWSTR(
    EVENT_DATA_DESCRIPTOR* pEventDataDescriptor,
    LPCWSTR* value)
{
    pEventDataDescriptor->Ptr = (ULONGLONG)(*value);
    pEventDataDescriptor->Size =(ULONG) (*value ? (wcslen((*value)) + 1)<<1 : 0);
    pEventDataDescriptor->Reserved = 0;
    return;
}

FORCEINLINE
VOID
etw_CreateDescriptor_PCWSTR(
    EVENT_DATA_DESCRIPTOR* pEventDataDescriptor,
    PCWSTR* value)
{
    pEventDataDescriptor->Ptr = (ULONGLONG)(*value);
    pEventDataDescriptor->Size =(ULONG) (*value ? (wcslen((*value)) + 1)<<1 : 0);
    pEventDataDescriptor->Reserved = 0;
    return;
}

#ifndef ETW_VERSION
#define ETW_VERSION  0
#endif

#define ETW_EVENT_DESCRIPTOR(id, channel, level, opcode, task, keyword) \
EVENT_DESCRIPTOR descriptor = {                 \
  id,	            /* USHORT    Id;       */   \
  ETW_VERSION,	    /* UCHAR     Version;  */   \
  channel,	        /* UCHAR     Channel;  */   \
  level,	        /* UCHAR     Level;    */   \
  opcode,	        /* UCHAR     Opcode;   */   \
  task,	            /* USHORT    Task;     */   \
  keyword,	        /* ULONGLONG Keyword;  */   \
};

_Use_decl_annotations_
PAL_INLINE void trace_EventTransfer(OIGUID * activity, OIGUID * related)
{
    REGHANDLE reg = EtwInitProvider();
    ETW_EVENT_DESCRIPTOR(500, 3, 4, 0, 0, 0);
    EventWriteEx(reg, &descriptor, 0, 0, (GUID *) activity, (GUID *) related, 0, NULL);
};

// Unique event signature templates for scalar types
// The actual types T0, T1... are not specified yet

#define ETW_EVENTSIG_IMPL0() \
FORCEINLINE static void Etw_Trace0(EVENT_DESCRIPTOR* eventDescriptor)  \
{                                                              \
    REGHANDLE reg = EtwInitProvider();                         \
    if (!_ETWShouldLog(eventDescriptor->Level)) return;        \
    EventWrite(reg, eventDescriptor, 0, NULL);                 \
}

#define ETW_EVENTSIG_IMPL1(T0) \
FORCEINLINE static void Etw_Trace1_ ## T0 (EVENT_DESCRIPTOR* eventDescriptor, T0 a0) \
{                                                              \
    REGHANDLE reg = EtwInitProvider();                         \
    EVENT_DATA_DESCRIPTOR Descriptors[1];                      \
    if (!_ETWShouldLog(eventDescriptor->Level)) return;        \
                                                               \
    etw_CreateDescriptor_ ## T0 ## (&Descriptors[0], &a0);     \
                                                               \
    EventWrite(reg, eventDescriptor, 1, Descriptors);          \
}

#define ETW_EVENTSIG_IMPL2(T0, T1) \
FORCEINLINE static void Etw_Trace2_ ## T0 ## _ ## T1(EVENT_DESCRIPTOR* eventDescriptor, T0 a0, T1 a1) \
{                                                              \
    REGHANDLE reg = EtwInitProvider();                         \
    EVENT_DATA_DESCRIPTOR Descriptors[2];                      \
    if (!_ETWShouldLog(eventDescriptor->Level)) return;        \
                                                               \
    etw_CreateDescriptor_ ## T0 ## (&Descriptors[0], &a0);     \
    etw_CreateDescriptor_ ## T1 ## (&Descriptors[1], &a1);     \
                                                               \
    EventWrite(reg, eventDescriptor, 2, Descriptors);          \
}

#define ETW_EVENTSIG_IMPL3(T0, T1, T2) \
FORCEINLINE static void Etw_Trace3_ ## T0 ## _ ## T1 ## _ ## T2 (EVENT_DESCRIPTOR* eventDescriptor, T0 a0, T1 a1, T2 a2) \
{                                                              \
    REGHANDLE reg = EtwInitProvider();                         \
    EVENT_DATA_DESCRIPTOR Descriptors[3];                      \
    if (!_ETWShouldLog(eventDescriptor->Level)) return;        \
                                                               \
    etw_CreateDescriptor_ ## T0 ## (&Descriptors[0], &a0);     \
    etw_CreateDescriptor_ ## T1 ## (&Descriptors[1], &a1);     \
    etw_CreateDescriptor_ ## T2 ## (&Descriptors[2], &a2);     \
                                                               \
    EventWrite(reg, eventDescriptor, 3, Descriptors);          \
}

#define ETW_EVENTSIG_IMPL4(T0, T1, T2, T3) \
FORCEINLINE static void Etw_Trace4_ ## T0 ## _ ## T1 ## _ ## T2 ## _ ## T3 (EVENT_DESCRIPTOR* eventDescriptor, T0 a0, T1 a1, T2 a2, T3 a3) \
{                                                              \
    REGHANDLE reg = EtwInitProvider();                         \
    EVENT_DATA_DESCRIPTOR Descriptors[4];                      \
    if (!_ETWShouldLog(eventDescriptor->Level)) return;        \
                                                               \
    etw_CreateDescriptor_ ## T0 ## (&Descriptors[0], &a0);     \
    etw_CreateDescriptor_ ## T1 ## (&Descriptors[1], &a1);     \
    etw_CreateDescriptor_ ## T2 ## (&Descriptors[2], &a2);     \
    etw_CreateDescriptor_ ## T3 ## (&Descriptors[3], &a3);     \
                                                               \
    EventWrite(reg, eventDescriptor, 4, Descriptors);          \
}

#define ETW_EVENTSIG_IMPL5(T0, T1, T2, T3, T4) \
FORCEINLINE static void Etw_Trace5_ ## T0 ## _ ## T1 ## _ ## T2 ## _ ## T3 ## _ ## T4 (EVENT_DESCRIPTOR* eventDescriptor, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) \
{                                                              \
    REGHANDLE reg = EtwInitProvider();                         \
    EVENT_DATA_DESCRIPTOR Descriptors[5];                      \
    if (!_ETWShouldLog(eventDescriptor->Level)) return;        \
                                                               \
    etw_CreateDescriptor_ ## T0 ## (&Descriptors[0], &a0);     \
    etw_CreateDescriptor_ ## T1 ## (&Descriptors[1], &a1);     \
    etw_CreateDescriptor_ ## T2 ## (&Descriptors[2], &a2);     \
    etw_CreateDescriptor_ ## T3 ## (&Descriptors[3], &a3);     \
    etw_CreateDescriptor_ ## T4 ## (&Descriptors[4], &a4);     \
                                                               \
    EventWrite(reg, eventDescriptor, 5, Descriptors);          \
}

#define ETW_EVENTSIG_IMPL6(T0, T1, T2, T3, T4, T5) \
FORCEINLINE static void Etw_Trace6_ ## T0 ## _ ## T1 ## _ ## T2 ## _ ## T3 ## _ ## T4 ## _ ## T5 (EVENT_DESCRIPTOR* eventDescriptor, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) \
{                                                              \
    REGHANDLE reg = EtwInitProvider();                         \
    EVENT_DATA_DESCRIPTOR Descriptors[6];                      \
    if (!_ETWShouldLog(eventDescriptor->Level)) return;        \
                                                               \
    etw_CreateDescriptor_ ## T0 ## (&Descriptors[0], &a0);     \
    etw_CreateDescriptor_ ## T1 ## (&Descriptors[1], &a1);     \
    etw_CreateDescriptor_ ## T2 ## (&Descriptors[2], &a2);     \
    etw_CreateDescriptor_ ## T3 ## (&Descriptors[3], &a3);     \
    etw_CreateDescriptor_ ## T4 ## (&Descriptors[4], &a4);     \
    etw_CreateDescriptor_ ## T5 ## (&Descriptors[5], &a5);     \
                                                               \
    EventWrite(reg, eventDescriptor, 6, Descriptors);          \
}

#define ETW_EVENTSIG_IMPL7(T0, T1, T2, T3, T4, T5, T6) \
FORCEINLINE static void Etw_Trace7_ ## T0 ## _ ## T1 ## _ ## T2 ## _ ## T3 ## _ ## T4 ## _ ## T5 ## _ ## T6 (EVENT_DESCRIPTOR* eventDescriptor, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) \
{                                                              \
    REGHANDLE reg = EtwInitProvider();                         \
    EVENT_DATA_DESCRIPTOR Descriptors[7];                      \
    if (!_ETWShouldLog(eventDescriptor->Level)) return;        \
                                                               \
    etw_CreateDescriptor_ ## T0 ## (&Descriptors[0], &a0);     \
    etw_CreateDescriptor_ ## T1 ## (&Descriptors[1], &a1);     \
    etw_CreateDescriptor_ ## T2 ## (&Descriptors[2], &a2);     \
    etw_CreateDescriptor_ ## T3 ## (&Descriptors[3], &a3);     \
    etw_CreateDescriptor_ ## T4 ## (&Descriptors[4], &a4);     \
    etw_CreateDescriptor_ ## T5 ## (&Descriptors[5], &a5);     \
    etw_CreateDescriptor_ ## T6 ## (&Descriptors[6], &a6);     \
                                                               \
    EventWrite(reg, eventDescriptor, 7, Descriptors);          \
}

#define ETW_EVENTSIG_IMPL8(T0, T1, T2, T3, T4, T5, T6, T7) \
FORCEINLINE static void Etw_Trace8_ ## T0 ## _ ## T1 ## _ ## T2 ## _ ## T3 ## _ ## T4 ## _ ## T5 ## _ ## T6 ## _ ## T7 (EVENT_DESCRIPTOR* eventDescriptor, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) \
{                                                              \
    REGHANDLE reg = EtwInitProvider();                         \
    EVENT_DATA_DESCRIPTOR Descriptors[8];                      \
    if (!_ETWShouldLog(eventDescriptor->Level)) return;        \
                                                               \
    etw_CreateDescriptor_ ## T0 ## (&Descriptors[0], &a0);     \
    etw_CreateDescriptor_ ## T1 ## (&Descriptors[1], &a1);     \
    etw_CreateDescriptor_ ## T2 ## (&Descriptors[2], &a2);     \
    etw_CreateDescriptor_ ## T3 ## (&Descriptors[3], &a3);     \
    etw_CreateDescriptor_ ## T4 ## (&Descriptors[4], &a4);     \
    etw_CreateDescriptor_ ## T5 ## (&Descriptors[5], &a5);     \
    etw_CreateDescriptor_ ## T6 ## (&Descriptors[6], &a6);     \
    etw_CreateDescriptor_ ## T7 ## (&Descriptors[7], &a7);     \
                                                               \
    EventWrite(reg, eventDescriptor, 8, Descriptors);          \
}

#define ETW_EVENTSIG_IMPL9(T0, T1, T2, T3, T4, T5, T6, T7, T8) \
FORCEINLINE static void Etw_Trace9_ ## T0 ## _ ## T1 ## _ ## T2 ## _ ## T3 ## _ ## T4 ## _ ## T5 ## _ ## T6 ## _ ## T7 ## _ ## T8 (EVENT_DESCRIPTOR* eventDescriptor, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8) \
{                                                              \
    REGHANDLE reg = EtwInitProvider();                         \
    EVENT_DATA_DESCRIPTOR Descriptors[9];                      \
    if (!_ETWShouldLog(eventDescriptor->Level)) return;        \
                                                               \
    etw_CreateDescriptor_ ## T0 ## (&Descriptors[0], &a0);     \
    etw_CreateDescriptor_ ## T1 ## (&Descriptors[1], &a1);     \
    etw_CreateDescriptor_ ## T2 ## (&Descriptors[2], &a2);     \
    etw_CreateDescriptor_ ## T3 ## (&Descriptors[3], &a3);     \
    etw_CreateDescriptor_ ## T4 ## (&Descriptors[4], &a4);     \
    etw_CreateDescriptor_ ## T5 ## (&Descriptors[5], &a5);     \
    etw_CreateDescriptor_ ## T6 ## (&Descriptors[6], &a6);     \
    etw_CreateDescriptor_ ## T7 ## (&Descriptors[7], &a7);     \
    etw_CreateDescriptor_ ## T8 ## (&Descriptors[8], &a8);     \
                                                               \
    EventWrite(reg, eventDescriptor, 9, Descriptors);          \
}

#define ETW_EVENTSIG_IMPL10(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9) \
FORCEINLINE static void Etw_Trace10_ ## T0 ## _ ## T1 ## _ ## T2 ## _ ## T3 ## _ ## T4 ## _ ## T5 ## _ ## T6 ## _ ## T7 ## _ ## T8 ## _ ## T9 (EVENT_DESCRIPTOR* eventDescriptor, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9) \
{                                                              \
    REGHANDLE reg = EtwInitProvider();                         \
    EVENT_DATA_DESCRIPTOR Descriptors[10];                     \
    if (!_ETWShouldLog(eventDescriptor->Level)) return;        \
                                                               \
    etw_CreateDescriptor_ ## T0 ## (&Descriptors[0], &a0);     \
    etw_CreateDescriptor_ ## T1 ## (&Descriptors[1], &a1);     \
    etw_CreateDescriptor_ ## T2 ## (&Descriptors[2], &a2);     \
    etw_CreateDescriptor_ ## T3 ## (&Descriptors[3], &a3);     \
    etw_CreateDescriptor_ ## T4 ## (&Descriptors[4], &a4);     \
    etw_CreateDescriptor_ ## T5 ## (&Descriptors[5], &a5);     \
    etw_CreateDescriptor_ ## T6 ## (&Descriptors[6], &a6);     \
    etw_CreateDescriptor_ ## T7 ## (&Descriptors[7], &a7);     \
    etw_CreateDescriptor_ ## T8 ## (&Descriptors[8], &a8);     \
    etw_CreateDescriptor_ ## T9 ## (&Descriptors[9], &a9);     \
                                                               \
    EventWrite(reg, eventDescriptor, 10, Descriptors);         \
}

#define ETW_EVENT0(eventId, eventName, channel, level, opcode, task, keyword)   \
static void eventName()                                                                \
{                                                                               \
    ETW_EVENT_DESCRIPTOR(eventId, channel, level, opcode, task, keyword);       \
    Etw_Trace0(&descriptor);                                                    \
}

#define ETW_EVENT1(eventId, eventName, channel, level, opcode, task, keyword, T0, N0)                   \
static void eventName(T0 a0)				                                                            \
{                                                                                                   \
    ETW_EVENT_DESCRIPTOR(eventId, channel, level, opcode, task, keyword);                           \
    Etw_Trace1_ ## N0 (&descriptor, a0);                                                            \
}

#define ETW_EVENT2(eventId, eventName, channel, level, opcode, task, keyword, T0, T1, N0, N1)               \
static void eventName(T0 a0, T1 a1)    	                                                            \
{                                                                                                   \
    ETW_EVENT_DESCRIPTOR(eventId, channel, level, opcode, task, keyword);                           \
    Etw_Trace2_ ## N0 ## _ ## N1(&descriptor, a0, a1);                                              \
}

#define ETW_EVENT3(eventId, eventName, channel, level, opcode, task, keyword, T0, T1, T2, N0, N1, N2)           \
static void eventName(T0 a0, T1 a1, T2 a2)    	                                                        \
{                                                                                                   \
    ETW_EVENT_DESCRIPTOR(eventId, channel, level, opcode, task, keyword);                           \
    Etw_Trace3_ ## N0 ## _ ## N1 ## _ ## N2 (&descriptor, a0, a1, a2);                              \
}

#define ETW_EVENT4(eventId, eventName, channel, level, opcode, task, keyword, T0, T1, T2, T3, N0, N1, N2, N3)       \
static void eventName(T0 a0, T1 a1, T2 a2, T3 a3)    	                                                \
{                                                                                                   \
    ETW_EVENT_DESCRIPTOR(eventId, channel, level, opcode, task, keyword);                           \
    Etw_Trace4_ ## N0 ## _ ## N1 ## _ ## N2 ## _ ## N3 (&descriptor, a0, a1, a2, a3);               \
}

#define ETW_EVENT5(eventId, eventName, channel, level, opcode, task, keyword, T0, T1, T2, T3, T4, N0, N1, N2, N3, N4)       \
static void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4)    	                                            \
{                                                                                                       \
    ETW_EVENT_DESCRIPTOR(eventId, channel, level, opcode, task, keyword);                               \
    Etw_Trace5_ ## N0 ## _ ## N1 ## _ ## N2 ## _ ## N3 ## _ ## N4 (&descriptor, a0, a1, a2, a3, a4);    \
}

#define ETW_EVENT6(eventId, eventName, channel, level, opcode, task, keyword, T0, T1, T2, T3, T4, T5, N0, N1, N2, N3, N4, N5)               \
static void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)    	                                                \
{                                                                                                                   \
    ETW_EVENT_DESCRIPTOR(eventId, channel, level, opcode, task, keyword);                                           \
    Etw_Trace6_ ## N0 ## _ ## N1 ## _ ## N2 ## _ ## N3 ## _ ## N4 ## _ ## N5 (&descriptor, a0, a1, a2, a3, a4, a5); \
}

#define ETW_EVENT7(eventId, eventName, channel, level, opcode, task, keyword, T0, T1, T2, T3, T4, T5, T6, N0, N1, N2, N3, N4, N5, N6)   \
static void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)    	                                    \
{                                                                                                           \
    ETW_EVENT_DESCRIPTOR(eventId, channel, level, opcode, task, keyword);                                   \
    Etw_Trace7_ ## N0 ## _ ## N1 ## _ ## N2 ## _ ## N3 ## _ ## N4 ## _ ## N5 ## _ ## N6 (                   \
        &descriptor, a0, a1, a2, a3, a4, a5, a6);                                                           \
}

#define ETW_EVENT8(eventId, eventName, channel, level, opcode, task, keyword, T0, T1, T2, T3, T4, T5, T6, T7, N0, N1, N2, N3, N4, N5, N6, N7)   \
static void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)    	                                \
{                                                                                                               \
    ETW_EVENT_DESCRIPTOR(eventId, channel, level, opcode, task, keyword);                                       \
    Etw_Trace8_ ## N0 ## _ ## N1 ## _ ## N2 ## _ ## N3 ## _ ## N4 ## _ ## N5 ## _ ## N6 ## _ ## N7 (            \
        &descriptor, a0, a1, a2, a3, a4, a5, a6, a7);                                                           \
}

#define ETW_EVENT9(eventId, eventName, channel, level, opcode, task, keyword, T0, T1, T2, T3, T4, T5, T6, T7, T8, N0, N1, N2, N3, N4, N5, N6, N7, N8)   \
static void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)    	                            \
{                                                                                                                   \
    ETW_EVENT_DESCRIPTOR(eventId, channel, level, opcode, task, keyword);                                           \
    Etw_Trace9_ ## N0 ## _ ## N1 ## _ ## N2 ## _ ## N3 ## _ ## N4 ## _ ## N5 ## _ ## N6 ## _ ## N7 ## _ ## N8 (     \
        &descriptor, a0, a1, a2, a3, a4, a5, a6, a7, a8);                                                           \
}

#define ETW_EVENT10(eventId, eventName, channel, level, opcode, task, keyword, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, N0, N1, N2, N3, N4, N5, N6, N7, N8, N9)      \
static void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)    	                            \
{                                                                                                                           \
    ETW_EVENT_DESCRIPTOR(eventId, channel, level, opcode, task, keyword);                                                   \
    Etw_Trace10_ ## N0 ## _ ## N1 ## _ ## N2 ## _ ## N3 ## _ ## N4 ## _ ## N5 ## _ ## N6 ## _ ## N7 ## _ ## N8 ## _ ## N9 ( \
        &descriptor, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);                                                               \
}

#ifdef _PREFAST_
#pragma prefast(pop)
#endif

#endif /* _oietw_h */
