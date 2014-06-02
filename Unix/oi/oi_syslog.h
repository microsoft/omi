
#ifndef _oi_syslog_h
#define _oi_syslog_h

#include <oi/oi.h>
#include <syslog.h>
#include <pal/format.h>
#include <pal/strings.h>
#include <base/log.h>

BEGIN_EXTERNC
    
#define OILOGSYSTEM_SYSLOG

unsigned long OIActivityId(OIActivityControlCode controlcode, OIGUID * activityId) { return 0; }
PAL_INLINE void trace_EventTransfer(_Inout_opt_ OIGUID * activity, _Inout_ OIGUID * related) {}

/*
OMI Levels are as follows:
    OMI_FATAL = 0
    OMI_ERROR = 1
    OMI_WARNING = 2
    OMI_INFO = 3
    OMI_DEBUG = 4
    OMI_VERBOSE = 5

Syslog levels to OMI
    LOG_EMERG	0 0	
    LOG_ALERT	1 0	
    LOG_CRIT	2 0	
    LOG_ERR		3 1	
    LOG_WARNING	4 2	
    LOG_NOTICE	5 3	
    LOG_INFO	6 5	
    LOG_DEBUG	7 4	
*/
static int _Syslog2OMI[] = {0, 0, 0, 1, 2, 3, 5, 4};

/*
SYSLOG does not have LOG_VERBOSE, so we handle it separately
*/
#define LOG_VERBOSE LOG_DEBUG

/*
APPNAME, LOGOPT, LOGFACILITY are defines from the generated code.
*/
PAL_INLINE void OpenSysLogOnce()
{
    static int LogOpened = 0;
    if (LogOpened == 1)
        return;
    openlog(APPNAME, LOGOPT, LOGFACILITY);
    LogOpened = 1; 
}

/*
Pulls OMI run-time log level, ex:
    omiserver --loglevel 4
*/
PAL_INLINE PAL_Boolean _ShouldSyslog(unsigned int level)
{
    if (_Syslog2OMI[level] > Log_GetLevel())
        return PAL_FALSE;
    else
        return PAL_TRUE;
}

#define FORMATLENGTH 1024
#define FORMAT_SYSLOG PAL_T("EventId=%d: Priority=%s: ")

/* Combine prefix and convert input format from PAL_T to SYSLOG/printf */
#if defined(CONFIG_ENABLE_WCHAR)
PAL_INLINE PAL_Boolean _Convert(const TChar * in, char * out)
{
    wchar_t wbuf[FORMATLENGTH];
    wchar_t * fmt = 0;
    memset(&wbuf, 0, sizeof(wbuf));
    if (StrWcslcpy(out, FORMAT_SYSLOG, FORMATLENGTH) >= FORMATLENGTH)
        return PAL_FALSE;
    fmt = WFixupFormat(wbuf, PAL_COUNT(wbuf), in);
    if (!fmt)
        return PAL_FALSE;
    if (StrWcslcat(out, wbuf, FORMATLENGTH) >= FORMATLENGTH)
        return PAL_FALSE;

    return PAL_TRUE;
}
#else
PAL_INLINE PAL_Boolean _Convert(const TChar * in, char * out)
{
    char buf[FORMATLENGTH];
    char * fmt = 0;

    memset(&buf, 0, sizeof(buf));
    Strlcpy(out, FORMAT_SYSLOG, FORMATLENGTH);
    fmt = FixupFormat(buf, PAL_COUNT(buf), in);
    if (!fmt)
        return PAL_FALSE;
    if (Strlcat(out, buf, FORMATLENGTH) >= FORMATLENGTH)
        return PAL_FALSE;

    return PAL_TRUE;
}
#endif

PAL_INLINE void _SyslogPut(
    int priority,
    const MI_Char* format,
    ...)
{
    char printfFormat[FORMATLENGTH];

    if (_ShouldSyslog(priority) && _Convert(format, printfFormat) == PAL_TRUE) 
    {
        OpenSysLogOnce();

        va_list ap;
        va_start(ap, format);
        vsyslog(priority, printfFormat, ap);
        va_end(ap);
    }
}


#define SYSLOG_EVENT0(eventId, eventName, priority, format)     \
PAL_INLINE void eventName()                                         \
{                                                               \
    _SyslogPut(priority, format, eventId, #priority);           \
}

#define SYSLOG_EVENT0(eventId, eventName, priority, format)                                             \
PAL_INLINE void eventName()                                                                                 \
{                                                                                                       \
    _SyslogPut(priority, format, eventId, #priority);                                                   \
}

#define SYSLOG_EVENT1(eventId, eventName, priority, format, T0)                                         \
PAL_INLINE void eventName(T0 a0)                                                                            \
{                                                                                                       \
    _SyslogPut(priority, format, eventId, #priority, a0);                                               \
}

#define SYSLOG_EVENT2(eventId, eventName, priority, format, T0, T1)                                     \
PAL_INLINE void eventName(T0 a0, T1 a1)                                                                     \
{                                                                                                       \
    _SyslogPut(priority, format, eventId, #priority, a0, a1);                                           \
}

#define SYSLOG_EVENT3(eventId, eventName, priority, format, T0, T1, T2)                                 \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2)                                                              \
{                                                                                                       \
    _SyslogPut(priority, format, eventId, #priority, a0, a1, a2);                                       \
}

#define SYSLOG_EVENT4(eventId, eventName, priority, format, T0, T1, T2, T3)             \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3)                                       \
{                                                                                       \
    _SyslogPut(priority, format, eventId, #priority, a0, a1, a2, a3);                   \
}

#define SYSLOG_EVENT5(eventId, eventName, priority, format, T0, T1, T2, T3, T4)         \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4)                                \
{                                                                                       \
    _SyslogPut(priority, format, eventId, #priority, a0, a1, a2, a3, a4);               \
}

#define SYSLOG_EVENT6(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5)         \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)                             \
{                                                                                           \
    _SyslogPut(priority, format, eventId, #priority, a0, a1, a2, a3, a4, a5);               \
}

#define SYSLOG_EVENT7(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6)         \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)                          \
{                                                                                               \
    _SyslogPut(priority, format, eventId, #priority, a0, a1, a2, a3, a4, a5, a6);               \
}

#define SYSLOG_EVENT8(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7)             \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)                           \
{                                                                                                       \
    _SyslogPut(priority, format, eventId, #priority, a0, a1, a2, a3, a4, a5, a6, a7);                   \
}

#define SYSLOG_EVENT9(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8)             \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)                        \
{                                                                                                           \
    _SyslogPut(priority, format, eventId, #priority, a0, a1, a2, a3, a4, a5, a6, a7, a8);                   \
}

#define SYSLOG_EVENT10(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)                \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9)                         \
{                                                                                                                   \
    _SyslogPut(priority, format, eventId, #priority, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);                       \
}

/* Debug versions that can be compiled out */

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define SYSLOG_EVENTD0(eventId, eventName, priority, format)          \
SYSLOG_EVENT0(eventId, eventName, priority, format)                
#else
#define SYSLOG_EVENTD0(eventId, eventName, priority, format)          \
PAL_INLINE void eventName() {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define SYSLOG_EVENTD1(eventId, eventName, priority, format, T0)          \
SYSLOG_EVENT1(eventId, eventName, priority, format, T0)                  
#else
#define SYSLOG_EVENTD1(eventId, eventName, priority, format, T0)          \
PAL_INLINE void eventName(T0 a0) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define SYSLOG_EVENTD2(eventId, eventName, priority, format, T0, T1)          \
SYSLOG_EVENT2(eventId, eventName, priority, format, T0, T1)                  
#else
#define SYSLOG_EVENTD2(eventId, eventName, priority, format, T0, T1)          \
PAL_INLINE void eventName(T0 a0, T1 a1) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define SYSLOG_EVENTD3(eventId, eventName, priority, format, T0, T1, T2)          \
SYSLOG_EVENT3(eventId, eventName, priority, format, T0, T1, T2)                  
#else
#define SYSLOG_EVENTD3(eventId, eventName, priority, format, T0, T1, T2)          \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define SYSLOG_EVENTD4(eventId, eventName, priority, format, T0, T1, T2, T3)          \
SYSLOG_EVENT4(eventId, eventName, priority, format, T0, T1, T2, T3)                  
#else
#define SYSLOG_EVENTD4(eventId, eventName, priority, format, T0, T1, T2, T3)          \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define SYSLOG_EVENTD5(eventId, eventName, priority, format, T0, T1, T2, T3, T4)          \
SYSLOG_EVENT5(eventId, eventName, priority, format, T0, T1, T2, T3, T4)                  
#else
#define SYSLOG_EVENTD5(eventId, eventName, priority, format, T0, T1, T2, T3, T4)          \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define SYSLOG_EVENTD6(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5)          \
SYSLOG_EVENT6(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5)                  
#else
#define SYSLOG_EVENTD6(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5)          \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define SYSLOG_EVENTD7(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6)          \
SYSLOG_EVENT7(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6)                  
#else
#define SYSLOG_EVENTD7(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6)          \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define SYSLOG_EVENTD8(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7)          \
SYSLOG_EVENT8(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7)                  
#else
#define SYSLOG_EVENTD8(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7)          \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define SYSLOG_EVENTD9(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8)          \
SYSLOG_EVENT9(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8)                  
#else
#define SYSLOG_EVENTD9(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8)          \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8) {}
#endif

#if defined(CONFIG_ENABLE_DEBUG)                                    
#define SYSLOG_EVENTD10(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)          \
SYSLOG_EVENT10(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)                  
#else
#define SYSLOG_EVENTD10(eventId, eventName, priority, format, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)          \
PAL_INLINE void eventName(T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, T9 a9) {}
#endif

END_EXTERNC

#endif /* _oi_syslog_h */
