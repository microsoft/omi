/*
Open Instrumentation for FILE OMI logging
*/

#ifndef _oi_file_h
#define _oi_file_h

#include "oi.h"
#include <base/log.h>

BEGIN_EXTERNC

#define OILOGSYSTEM_FILE

/* Not implemented */
unsigned long OIActivityId(OIActivityControlCode controlcode, OIGUID * activityId) { return 0; }
PAL_INLINE void trace_EventTransfer(OIGUID * activity, OIGUID * related) {}

/*
These are SYSLOG LEVEL remapped for non-Syslog environment.
They are converted to match Log_Level struct.
OMI Levels are as follows:
    OMI_FATAL = 0
    OMI_ERROR = 1
    OMI_WARNING = 2
    OMI_INFO = 3
    OMI_DEBUG = 4
    OMI_VERBOSE = 5
*/

/* logging levels */
#define	LOG_EMERG	OMI_FATAL
#define	LOG_ALERT	OMI_FATAL
#define	LOG_CRIT	OMI_FATAL
#define	LOG_ERR		OMI_ERROR
#define	LOG_WARNING	OMI_WARNING
#define	LOG_NOTICE	OMI_INFO
#define	LOG_INFO	OMI_INFO
#define	LOG_DEBUG	OMI_DEBUG
#define	LOG_VERBOSE	OMI_VERBOSE

#ifndef FILE_EVENT0 
#define FILE_EVENT0(eventId, eventName, priority, format)                                               \
PAL_INLINE void eventName(const char * file, int line)                                                  \
{                                                                                                       \
    FilePutLog(priority, eventId, file, line, format);                                                  \
}
#endif

#ifndef FILE_EVENT1 
#define FILE_EVENT1(eventId, eventName, priority, format, T0)                                           \
PAL_INLINE void eventName(const char * file, int line, T0 a0)                                                                            \
{                                                                                                       \
    FilePutLog(priority, eventId, file, line, format, a0);                                  \
}
#endif

#ifndef FILE_EVENT2
#define FILE_EVENT2(eventId, eventName, priority, format, T0, T1)                                       \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1)                                                                     \
{                                                                                                       \
    FilePutLog(priority, eventId, file, line, format, a0, a1);                              \
}
#endif

#ifndef FILE_EVENT3
#define FILE_EVENT3(eventId, eventName, priority, format, T0, T1, T2)                                   \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2)                                                              \
{                                                                                                       \
    FilePutLog(priority, eventId, file, line, format, a0, a1, a2);                          \
}
#endif

#ifndef FILE_EVENT4
#define FILE_EVENT4(eventId, eventName, priority, format, T0, T1, T2, T3)               \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3)                                       \
{                                                                                       \
    FilePutLog(priority, eventId, file, line, format, a0, a1, a2, a3);      \
}

#endif

#ifndef FILE_EVENT5
#define FILE_EVENT5(eventId, eventName, priority, format, T0, T1, T2, T3, T4)           \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4)                                \
{                                                                                       \
    FilePutLog(priority, eventId, file, line, format, a0, a1, a2, a3, a4);  \
}

#endif

#ifndef FILE_EVENT6
#define FILE_EVENT6(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5)           \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)                             \
{                                                                                           \
    FilePutLog(priority, eventId, file, line, format, a0, a1, a2, a3, a4, a5);  \
}

#endif

#ifndef FILE_EVENT7
#define FILE_EVENT7(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6)           \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)                          \
{                                                                                               \
    FilePutLog(priority, eventId, file, line, format, a0, a1, a2, a3, a4, a5, a6);  \
}

#endif

#ifndef FILE_EVENT8
#define FILE_EVENT8(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7)               \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)                           \
{                                                                                                       \
    FilePutLog(priority, eventId, file, line, format, a0, a1, a2, a3, a4, a5, a6, a7);      \
}

#endif

#ifndef FILE_EVENT9
#define FILE_EVENT9(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8)               \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)                        \
{                                                                                                           \
    FilePutLog(priority, eventId, file, line, format, a0, a1, a2, a3, a4, a5, a6, a7, a8);      \
}

#endif

#ifndef FILE_EVENT10
#define FILE_EVENT10(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)                  \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)                         \
{                                                                                                                   \
    FilePutLog(priority, eventId, file, line, format, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);          \
}
#endif
/* Debug versions that can be compiled out */

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define FILE_EVENTD0(eventId, eventName, priority, format)          \
FILE_EVENT0(eventId, eventName, priority, format)                
#else
#define FILE_EVENTD0(eventId, eventName, priority, format)          \
PAL_INLINE void eventName(const char * file, int line) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define FILE_EVENTD1(eventId, eventName, priority, format, T0)          \
FILE_EVENT1(eventId, eventName, priority, format, T0)                  
#else
#define FILE_EVENTD1(eventId, eventName, priority, format, T0)          \
PAL_INLINE void eventName(const char * file, int line, T0 a0) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define FILE_EVENTD2(eventId, eventName, priority, format, T0, T1)          \
FILE_EVENT2(eventId, eventName, priority, format, T0, T1)                  
#else
#define FILE_EVENTD2(eventId, eventName, priority, format, T0, T1)          \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define FILE_EVENTD3(eventId, eventName, priority, format, T0, T1, T2)          \
FILE_EVENT3(eventId, eventName, priority, format, T0, T1, T2)                  
#else
#define FILE_EVENTD3(eventId, eventName, priority, format, T0, T1, T2)          \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define FILE_EVENTD4(eventId, eventName, priority, format, T0, T1, T2, T3)          \
FILE_EVENT4(eventId, eventName, priority, format, T0, T1, T2, T3)                  
#else
#define FILE_EVENTD4(eventId, eventName, priority, format, T0, T1, T2, T3)          \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define FILE_EVENTD5(eventId, eventName, priority, format, T0, T1, T2, T3, T4)          \
FILE_EVENT5(eventId, eventName, priority, format, T0, T1, T2, T3, T4)                  
#else
#define FILE_EVENTD5(eventId, eventName, priority, format, T0, T1, T2, T3, T4)          \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define FILE_EVENTD6(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5)          \
FILE_EVENT6(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5)                  
#else
#define FILE_EVENTD6(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5)          \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define FILE_EVENTD7(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6)          \
FILE_EVENT7(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6)                  
#else
#define FILE_EVENTD7(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6)          \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define FILE_EVENTD8(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7)          \
FILE_EVENT8(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7)                  
#else
#define FILE_EVENTD8(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7)          \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define FILE_EVENTD9(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8)          \
FILE_EVENT9(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8)                  
#else
#define FILE_EVENTD9(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8)          \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define FILE_EVENTD10(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)          \
FILE_EVENT10(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)                  
#else
#define FILE_EVENTD10(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)          \
PAL_INLINE void eventName(const char * file, int line, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9) {}
#endif

END_EXTERNC

#endif /* _oi_file_h */
