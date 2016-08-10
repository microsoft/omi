/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _tests_util_util_h
#define _tests_util_util_h


#ifdef _MSC_VER
#include <windows.h>
#endif
#include <MI.h>
#include <pal/thread.h>
#include <pal/sleep.h>
#include <pal/sem.h>
#include <pal/hashmap.h>
#include <base/batch.h>

PAL_BEGIN_EXTERNC

/* global batch object */
extern Batch* g_batch;

/* global log file, each module needs to define g_logfile */
extern FILE* g_logfile;

/* Write to global log file */
void WriteLog(const char* fmt, ...);
void FlushLog(FILE* file);


/* Compare MI_Char string */
int StringCompare(const MI_Char* s1, const MI_Char* s2);


void _WriteHeader(
    const char* file,
    unsigned int line);

INLINE int __MyLogFalse() { return 0; }

# define LOGMSG(ARGS) \
    do \
    { \
        _WriteHeader(__FILE__, __LINE__); \
        WriteLog ARGS; \
    } \
    while (__MyLogFalse())

/* Convert Ansi string to MI_Char string */
MI_Char* ansiToMI(const char* src);
/* Convert MI_Char string to ansi string (ascii only) */
char* MIToansi(const MI_Char* src);

#define CHKMIRESULTPOST(r,msg) \
    if (r != MI_RESULT_OK) \
    { \
        LOGMSG(("(%s) failed with error code (%d)",msg,r)); \
        MI_PostResult(context, r); \
        return; \
    }

#define CHKMIRESULTRETURN(r,msg) \
    if (r != MI_RESULT_OK) \
    { \
        LOGMSG(("(%s) failed with error code (%d)",msg,r)); \
        return r; \
    }

#define CHKSETPROPERTY(r, pname) \
    if (r != MI_RESULT_OK) \
    { \
        LOGMSG(("set property (%s) failed with error (%d)", pname, r )); \
        return r; \
    }

#define CHKSETPROPERTYGOTO(r, pname, label) \
    if (r != MI_RESULT_OK) \
    { \
        LOGMSG(("set property (%s) failed with error (%d)", pname, r )); \
        goto label; \
    }

#define ONNULLGOTO(value, pname, label) \
    if (value == NULL) \
    { \
        LOGMSG(("value of (%s) is NULL", pname)); \
        goto label; \
    }

#define FREE(ptr) \
    if (ptr) \
    { \
        PAL_Free(ptr); \
        ptr = NULL; \
    } \

const char* gethomedir();


MI_Result StartOmiserver();
MI_Result StopOmiserver();


/*
**==============================================================================
**
** Test structure for consume instance results
**
**==============================================================================
*/
typedef struct _InstanceOperationStruct
{
    MI_Boolean sync; /* async / sync */
    MI_Uint32 operationTimeout; /* timeout value for the operation */

    /* operation results */
    MI_Uint32 count;

    volatile ptrdiff_t finished; /* condication variable for terminating the operation */    

    MI_Result finalResult;

    /* MI objects */
    MI_Application app; /* application object */
    MI_Session session; /* test application */

}InstanceOperationStruct;

/*
**==============================================================================
**
** Read instance for given class
**
**==============================================================================
*/
MI_Result EnumerateInstance(
    _In_ InstanceOperationStruct* ios,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className);

/*
**==============================================================================
**
** String hash map implementation based on hashmap
**
**==============================================================================
*/
typedef struct _StringBucket /* derives from HashBucket */
{
    struct _StringBucket* next;
    MI_Char* key;
    MI_Uint32 count;
}
StringBucket;

typedef struct _StringHashMap
{
    HashMap map;
}StringHashMap;

/* returns:
   -  0 : success
   - <0 : out of memory
*/ 
int StringHashMap_Init(
    _Out_ StringHashMap* self);

void StringHashMap_Destroy(
    _In_ _Post_invalid_ StringHashMap* self);

/* returns:
   -  non-null : found
   -  null     : key not present
*/
_Ret_maybenull_ StringBucket* StringHashMap_Find(
    _In_ StringHashMap* self,
    _In_z_ const MI_Char* key);

/* returns:
   -  0 : inserted the new item
   -  1 : the item is already present (and HashMap was not modified)
   
   (there are no failure paths / no other return value is possible)
*/
int StringHashMap_Insert(
    _In_ StringHashMap* self,
    _In_z_ const MI_Char* key);

/* returns:
   -  0 : success
   - -1 : key not found - hashmap remains unchanged.
*/
int StringHashMap_Remove(
    _In_ StringHashMap* self,
    _In_ const MI_Char* key);

/* 
   Returns one element from the hash table. May be invoked
   multiple times (e.g. if you remove the element), returning
   null when empty.
 
   *iter should be zero initialized before first call
*/
_Ret_maybenull_ 
const StringBucket* StringHashMap_Top(
    _In_ StringHashMap* self,
    _Inout_ size_t *iter);

MI_Result StartServer_Assert();
MI_Result StopServer_Assert();

PAL_END_EXTERNC

#endif /* _tests_util_util_h */
