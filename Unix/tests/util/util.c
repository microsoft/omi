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
#include <base/pidfile.h>
#include <base/paths.h>
#include <base/log.h>
#include <pal/dir.h>
#include <pal/lock.h>
#include "util.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>
# include <pwd.h>
# include <unistd.h>

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
    struct passwd *pw = getpwuid(getuid());
    return pw->pw_dir;
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
    struct timeval tv;
    struct timezone tz;
    memset(&tv, 0, sizeof(tv));
    memset(&tz, 0, sizeof(tz));

    if (gettimeofday(&tv, &tz) != 0)
        return -1;

    *usec = (MI_Uint64)tv.tv_sec * (MI_Uint64)1000000 + (MI_Uint64)tv.tv_usec;
    return 0;
}

#define TIMESTAMP_SIZE 256
static int __GetTimeStamp(_Pre_writable_size_(TIMESTAMP_SIZE) char buf[TIMESTAMP_SIZE])
{
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

    return 0;
}

static void _PrintThreadID(FILE* f)
{
    ThreadID currentthread = Thread_ID();
    size_t i;
    size_t threadsize = sizeof(currentthread.__impl);
    unsigned char *ptc = (unsigned char*)(void*)(&currentthread.__impl);
    fprintf(f, "Thread: 0x");
    for(i=0; i < threadsize; i++) {
        fprintf(f, "%02x", (unsigned)(ptc[i]));
    }
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
** string hash function
**
**==============================================================================
*/

/* A number used to calculate hash value */
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
    MI_Result r = StartOmiserver();
    NitsAssert(r == MI_RESULT_OK, PAL_T("Failed to start Omiserver"));
    return r;
}

MI_Result StopServer_Assert()
{
    MI_Result r = StopOmiserver();
    NitsAssert(r == MI_RESULT_OK, PAL_T("Failed to stop Omiserver"));
    return r;
}

#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
