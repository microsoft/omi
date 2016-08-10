/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <ctype.h>
#include <time.h>
#include <pal/file.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <base/process.h>
#include <pal/sleep.h>
#include <base/paths.h>
#include <base/log.h>
#include <pal/dir.h>
#include <pal/lock.h>
#include "util.h"

#ifdef _MSC_VER
# include <windows.h>
# include <shlobj.h>
#else
# include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>
# include <pwd.h>
# include <unistd.h>
#endif

#ifdef _PREFAST_
    #pragma prefast(push)
    /* ANSI API ('SHGetFolderPathA') should not be called from Unicode modules. */
    /* Calling ANSI APIs leads to unexpected results when handling multi-lingual */
    /* text or Unicode-only languages. Use the Unicode version of this API instead.*/
    #pragma prefast(disable:38020)
#endif

/* get user home directory */
const char* gethomedir()
{
#ifdef _MSC_VER
    static char path[MAX_PATH];
    if (SHGetFolderPathA( NULL, CSIDL_PROFILE, NULL, 0, path ) != S_OK)
    {
        path[0] = '\0';
    }
    return (const char *)path;
#else
    struct passwd *pw = getpwuid(getuid());
    return pw->pw_dir;
#endif
}

MI_Char* ansiToMI(const char* src)
{
    MI_Char* mistr = NULL;
    if (g_batch && src)
    {
        MI_Uint32 size = strlen(src) + 1;
        mistr = (MI_Char*) Batch_Get(g_batch, size*sizeof(MI_Char));
        if (mistr)
        {
            MI_Uint32 i;
            for (i = 0; i < size; i++)
            {
                mistr[i] = (MI_Char)src[i];
            }
        }
    }
    return mistr;
}

char* MIToansi(const MI_Char* src)
{
#if (MI_CHAR_TYPE == 2)
    char* str = NULL;
    if (g_batch && src)
    {
        MI_Uint32 size = wcslen(src) + 1;
        str = (char*) Batch_Get(g_batch, size*sizeof(char));
        if (str)
        {
            MI_Uint32 i;
            for (i = 0; i < size; i++)
            {
                str[i] = (char)src[i];
            }
        }
    }
    return str;
#else
    return (char*)src;
#endif
}

int StringCompare(const MI_Char* s1, const MI_Char* s2)
{
    return Tcscasecmp(s1, s2);
}

int __GetCurrentTimeInUsec(MI_Uint64* usec)
{
#if defined(CONFIG_OS_WINDOWS)
    FILETIME ft;
    ULARGE_INTEGER tmp;

    GetSystemTimeAsFileTime(&ft);
    tmp.u.LowPart = ft.dwLowDateTime;
    tmp.u.HighPart = ft.dwHighDateTime;
    tmp.QuadPart -= 0X19DB1DED53E8000;
    *usec = tmp.QuadPart / (UINT64)10;

    return 0;
#else
    struct timeval tv;
    struct timezone tz;
    memset(&tv, 0, sizeof(tv));
    memset(&tz, 0, sizeof(tz));

    if (gettimeofday(&tv, &tz) != 0)
        return -1;

    *usec = (MI_Uint64)tv.tv_sec * (MI_Uint64)1000000 + (MI_Uint64)tv.tv_usec;
    return 0;
#endif
}

#define TIMESTAMP_SIZE 256
static int __GetTimeStamp(_Pre_writable_size_(TIMESTAMP_SIZE) char buf[TIMESTAMP_SIZE])
{
#if defined(CONFIG_OS_WINDOWS)
    {
        SYSTEMTIME systime;
        GetLocalTime(&systime);

        sprintf_s(
            buf,
            TIMESTAMP_SIZE,
            "%02u/%02u/%02u %02u:%02u:%02u",
            systime.wYear,
            systime.wMonth,
            systime.wDay,
            systime.wHour,
            systime.wMinute,
            systime.wSecond);
    }
#else
    MI_Uint64 usec;

    if (__GetCurrentTimeInUsec(&usec) != 0)
    {
        buf[0] = '\0';
        return -1;
    }

    {
        time_t t = usec / 1000000;
        struct tm tm;
        localtime_r(&t, &tm);
        sprintf(
            buf,
            "%02u/%02u/%02u %02u:%02u:%02u",
            tm.tm_year + 1900,		//aka.ms/sre-codescan/disable
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec);
    }
#endif

    return 0;
}

static void _PrintThreadID(FILE* f)
{
    ThreadID currentthread = Thread_ID();
#ifdef _MSC_VER
    fprintf(f, "Thread: 0x%x", (unsigned int)(currentthread.__impl));
#else
    size_t i;
    size_t threadsize = sizeof(currentthread.__impl);
    unsigned char *ptc = (unsigned char*)(void*)(&currentthread.__impl);
    fprintf(f, "Thread: 0x");
    for(i=0; i < threadsize; i++) {
        fprintf(f, "%02x", (unsigned)(ptc[i]));
    }
#endif
}

void _WriteHeader(
    const char* file,
    unsigned int line)
{
    char buf[256];
    __GetTimeStamp(buf);
    _PrintThreadID(g_logfile);
    fprintf(g_logfile, " : %s : ", buf);
    if (file)
        fprintf(g_logfile, "%s(%u): ", file, line);
}

void WriteLog(const char* fmt, ...)
{
    if (g_logfile)
    {
        va_list ap;
        memset(&ap, 0, sizeof(ap));
        va_start(ap, fmt);
        Vfprintf(g_logfile, fmt, ap);
        va_end(ap);

        fprintf(g_logfile, "\r\n");
        FlushLog(g_logfile);
    }
}

void FlushLog(FILE* file)
{
    if (file)
    {
        fflush(file);
        //File_Close(g_logfile);
        //g_logfile = File_Open(g_logfilepath, "a+");
    }
}


/*
**==============================================================================
**
** Consume instance
**
**==============================================================================
*/
static MI_Result _ConsumeInstanceResults(
    _In_ InstanceOperationStruct* ios,
    _In_ MI_Operation *miOperation)
{
    MI_Result miResult = MI_RESULT_FAILED;
    MI_Boolean moreResults = MI_FALSE;

    if (MI_TRUE == ios->sync)
    {
        do
        {
            const MI_Instance *miInstanceResult = NULL;
            MI_Result _miResult;
            const MI_Char *errorString = NULL;
            const MI_Instance *errorDetails = NULL;

            _miResult = MI_Operation_GetInstance(
                miOperation,
                &miInstanceResult,
                &moreResults,
                &miResult,
                &errorString,
                &errorDetails);
            if (_miResult != MI_RESULT_OK)
            {
                miResult = _miResult;
            }
            if (miInstanceResult)
                ios->count++;
        } while ((miResult == MI_RESULT_OK) && (moreResults == MI_TRUE));
    }
    else
    {
        ptrdiff_t finished;
        finished = ios->finished;
        while (!finished)
        {
            CondLock_Wait((ptrdiff_t)&ios->finished, &ios->finished, finished, CONDLOCK_DEFAULT_SPINCOUNT);
            finished = ios->finished;
            miResult = ios->finalResult;
        }
    }

    return miResult;
}

/*
**==============================================================================
**
** Async operation, the callback to receive instance results
**
**==============================================================================
*/
static MI_Result g_finalResult;
static MI_Boolean g_called;
static MI_Boolean g_moreResults;
void MI_CALL _InstanceResultCallback(
    _In_opt_     MI_Operation *operation,
    _In_     void *callbackContext,
    _In_opt_ const MI_Instance *instance,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char *errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    InstanceOperationStruct* ios = (InstanceOperationStruct*)callbackContext;
    if (instance)
        ios->count ++;
    if (moreResults == MI_FALSE)
    {
        ios->finalResult = resultCode;
        ios->finished = 1;
        CondLock_Broadcast((ptrdiff_t)&ios->finished);
    }
    g_finalResult = resultCode;
    g_called = MI_TRUE;
    g_moreResults = moreResults;
}

/*
**==============================================================================
**
** Read instance for given class
**
**==============================================================================
*/
_Use_decl_annotations_
MI_Result EnumerateInstance(
    InstanceOperationStruct* ios,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    MI_Result miResult;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;

    if (ios->sync == MI_FALSE)
    {
        _callbacks.callbackContext = ios;
        _callbacks.instanceResult = _InstanceResultCallback;
        callbacks = &_callbacks;
        ios->finished = 0;
        ios->finalResult = MI_RESULT_FAILED;
    }

    MI_Session_EnumerateInstances(&ios->session, 0, NULL, nameSpace, className, MI_FALSE, callbacks, &miOperation);
    miResult = _ConsumeInstanceResults(ios, &miOperation);
    MI_Operation_Close(&miOperation);
    return miResult;
}


static Process serverProcess;
MI_Char s_socketFile[PAL_MAX_PATH_SIZE];
char s_socketFile_a[PAL_MAX_PATH_SIZE];

/*
**==============================================================================
**
** Remember if the server is started or not
**
**==============================================================================
*/
int g_serverstarted = 0;

#if defined(_MSC_VER)
unsigned short _GetUnittestPortNumber()
{
    return 21718;
}
#else
unsigned short _GetUnittestPortNumber()
{
    return 10000 + ((geteuid() % 200) * 200);
}
#endif
unsigned short UnittestPortNumberWSMANHTTP()
{
    return _GetUnittestPortNumber() + 198;
}
unsigned short UnittestPortNumberWSMANHTTPS()
{
    return _GetUnittestPortNumber() + 197;
}

MI_Result StartOmiserver()
{
    const char* path = OMI_GetPath(ID_SERVERPROGRAM);
    const char* argv[17];
    char http[32];
    char https[32];
    int i;
    InstanceOperationStruct ios;
    MI_Result r;

    memset(&ios, 0, sizeof(InstanceOperationStruct));

    //
    // kill running omiserver if have any
    //
    {
        char buf[64];
        sprintf(buf, "pkill -9 %s", "omiserver");
        system(buf);
        Sleep_Milliseconds(10);
    }

    Snprintf(http, sizeof(http),"%d", UnittestPortNumberWSMANHTTP());
    Snprintf(https, sizeof(https),"%d", UnittestPortNumberWSMANHTTPS());

    Strlcpy(s_socketFile_a, OMI_GetPath(ID_SOCKETFILE), sizeof(s_socketFile_a)/sizeof(s_socketFile_a[0]));
    TcsStrlcpy(s_socketFile, s_socketFile_a, sizeof(s_socketFile)/sizeof(s_socketFile[0]));

    argv[0] = path;
    argv[1] = "--rundir";
#if defined(CONFIG_OS_WINDOWS)
    argv[2] = "..";
#else
    argv[2] = OMI_GetPath(ID_PREFIX);
#endif
    argv[3] = "--ignoreAuthentication";
    argv[4] = "--socketfile";
    argv[5] = s_socketFile_a;
    argv[6] = "--httpport";
    argv[7] = http;
    argv[8] = "--httpsport";
    argv[9] = https;
    argv[10] = "--livetime";
    argv[11] = "1800";

    argv[12] = "--loglevel";
    argv[13] = Log_GetLevelString(Log_GetLevel());
    argv[14] = NULL;

    if (Process_StartChild(&serverProcess, path, (char**)argv) != 0)
    {
        NitsAssert(0, PAL_T("Failed to create omiserver process"));
        return MI_RESULT_FAILED;
    }

    g_serverstarted = 1;

    /*  wait for server to start */
    r = MI_Application_Initialize(0, NULL, NULL, &ios.app);
    if (r != MI_RESULT_OK)
    {
        NitsAssert(0, PAL_T("Failed to Initialize MI_Application"));
        return r;
    }

    for (i = 0; i < 100; i++)
    {
        Sleep_Milliseconds(50);
        r = MI_Application_NewSession(&ios.app, NULL, NULL, NULL, NULL, NULL, &ios.session);
        if (r == MI_RESULT_OK)
        {
            break;
        }
    }

    if (r != MI_RESULT_OK)
    {
        NitsAssert(0, PAL_T("Failed to create session"));
        MI_Application_Close(&ios.app);
        return r;
    }

    /* TODO: Use MI_Session_TestConnection if it is implemented */
    for (i = 0; i < 1000; i++)
    {
        g_finalResult = MI_RESULT_OK;
        g_called = MI_FALSE;
        g_moreResults = MI_FALSE;
        r = EnumerateInstance(&ios, MI_T("root/omi"), MI_T("omi_identify"));
        if (r == MI_RESULT_OK)
        {
            break;
        }
        Sleep_Milliseconds(50);
    }
    if (r != MI_RESULT_OK)
    {
        NitsAssert(0, PAL_T("Failed to enumerate omi_identify instance"));
    }
    MI_Session_Close(&ios.session, NULL, NULL);
    MI_Application_Close(&ios.app);
    return r;
}

MI_Result StopOmiserver()
{
    MI_Result r = MI_RESULT_OK;
    if (g_serverstarted == 1)
    {
        /*
         * For e2e test, server might be busy, and e2e cancellation is not complete yet,
         * sleep two seconds to mitigate server hang issues during shutting down.
         */
        Sleep_Milliseconds(2000);
        if (Process_StopChild(&serverProcess) != 0)
        {
            memset((void*)&serverProcess, 0, sizeof(Process));
            r = MI_RESULT_FAILED;
        }
        g_serverstarted = 0;
    }
    return r;
}


/*
**==============================================================================
**
** string hash function
**
**==============================================================================
*/

/* A number used to caculate hash value */
#define HASH_SEED_PRIME_NUMBER 1313038763

/* String hash algorithm */
PAL_EXTERN_C size_t StringHash(_In_ const HashBucket* bucket)
{
    StringBucket* strbucket = (StringBucket*)bucket;
    size_t hash = HASH_SEED_PRIME_NUMBER;
    const MI_Char* p = strbucket->key;
    while(*p)
    {
        hash ^= ((hash << 5) + tolower(*p) + (hash >> 2));
        p++;
    }
    return hash;
}

PAL_EXTERN_C int StringBucketEqual(
    const HashBucket* bucket1_,
    const HashBucket* bucket2_)
{
    StringBucket* bucket1 = (StringBucket*)bucket1_;
    StringBucket* bucket2 = (StringBucket*)bucket2_;
    return Tcscasecmp(bucket1->key, bucket2->key) == 0;
}

PAL_EXTERN_C void StringBucketRelease(
    HashBucket* bucket_)
{
    StringBucket* bucket = (StringBucket*)bucket_;
    PAL_Free(bucket->key);
    PAL_Free(bucket);
}

_Use_decl_annotations_
int StringHashMap_Init(
    StringHashMap* self)
{
    return HashMap_Init(&self->map, 32, StringHash, StringBucketEqual, StringBucketRelease);
}

_Use_decl_annotations_
void StringHashMap_Destroy(
    StringHashMap* self)
{
    HashMap_Destroy(&self->map);
}

/* returns:
   -  non-null : found
   -  null     : key not present
*/ 
_Use_decl_annotations_
StringBucket* StringHashMap_Find(
    StringHashMap* self,
    const MI_Char* key)
{
    StringBucket b;
    b.key = (MI_Char*)key;
    return (StringBucket*)HashMap_Find(&self->map, (const HashBucket*)&b);
}

/* returns:
   -  0 : inserted the new item
   -  1 : the item is already present (and HashMap was not modified)
   - -1 : out of memory

   (there are no failure paths / no other return value is possible)
*/
_Use_decl_annotations_
int StringHashMap_Insert(
    StringHashMap* self,
    const MI_Char* key)
{
    StringBucket *b;
    b = (StringBucket*)PAL_Calloc( 1, sizeof(StringBucket) );
    if ( b )
    {
        b->key = PAL_Tcsdup( key );
        b->count = 0;
        return HashMap_Insert( &self->map, (HashBucket*)b );
    }
    return -1;
}

/* returns:
   -  0 : success
   - -1 : key not found - hashmap remains unchanged.
*/
_Use_decl_annotations_
int StringHashMap_Remove(
    StringHashMap* self,
    const MI_Char* key)
{
    StringBucket b;
    b.key = (MI_Char*)key;
    return HashMap_Remove(&self->map, (const HashBucket*)&b);
}


/* 
   Returns one element from the hash table. May be invoked
   multiple times (e.g. if you remove the element), returning
   null when empty.
 
   *iter should be zero initialized before first call
*/
_Use_decl_annotations_
const StringBucket* StringHashMap_Top(
    StringHashMap* self,
    size_t *iter)
{
    return (StringBucket*) HashMap_Top( &self->map, iter );
}

MI_Result StartServer_Assert()
{
# if !defined(_MSC_VER)
    MI_Result r = StartOmiserver();
    NitsAssert(r == MI_RESULT_OK, PAL_T("Failed to start Omiserver"));
    return r;
#else
    return MI_RESULT_OK;
#endif
}

MI_Result StopServer_Assert()
{
# if !defined(_MSC_VER)
    MI_Result r = StopOmiserver();
    NitsAssert(r == MI_RESULT_OK, PAL_T("Failed to stop Omiserver"));
    return r;
#else
    return MI_RESULT_OK;
#endif
}

#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
