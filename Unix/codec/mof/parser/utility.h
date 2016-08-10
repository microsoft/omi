/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _mof_utility_h
#define _mof_utility_h

/*
**==============================================================================
**
** Utilities needs to handle both ANSI and UNICODE buffer,
** including UTF16 Big Endian.
** Which require an input parameter (MOF_Encoding e),
** Caller need to make sure input data is encoded as UTF16 Big Endian
**
**==============================================================================
*/
int mof_getchar(MOF_Encoding e, void * data);

int mof_nextchar(_Inout_ MOF_Buffer * b);

MI_Boolean mof_isspace(MOF_Encoding e, void * data);

MI_Boolean mof_isalpha(MOF_Encoding e, void * data);

MI_Boolean mof_isalnum(MOF_Encoding e, void * data);

MI_Boolean mof_isunderscore(MOF_Encoding e, void * data);

MI_Boolean mof_isdoulbequotes(MOF_Encoding e, void * data);

MI_Boolean mof_isbackslash(MOF_Encoding e, void * data);

MI_Boolean mof_isminus(MOF_Encoding e, void * data);

MI_Boolean mof_isplus(MOF_Encoding e, void * data);

MI_Boolean mof_isdigit(MOF_Encoding e, void * data);

MI_Boolean mof_match(MOF_Encoding e, _In_ MOF_StringLen *data, _In_ MOF_StringLen *pattern);

/*
**==============================================================================
**
** Utilities handles only UTF16 Little Endian buffer
** or the function result does not depends on Endian;
**
** Caller need to make sure either the data is already converted to
** UTF16 Little Endian or the function result does not depends on Endian
** format.
**
** They take a parameter (MI_Boolean unicode) to indicate buffer is
** unicode or ansi.
**
**==============================================================================
*/

//
// result does not depends on endian
//
size_t mof_offset(MI_Boolean unicode, _In_ void * orgdata, _In_ void *curdata);

void mof_getcode(MI_Boolean unicode, _Inout_ MOF_StringLen *r);

int mof_ncasecmp(MI_Boolean unicode, _In_ void *s1, _In_ void * s2, size_t n);

void* mof_nextcharofbuf(MI_Boolean unicode, void * data);

void * mof_getprevcharpos(MI_Boolean unicode, void * data);

MI_Boolean mof_strtoul(MI_Boolean unicode, _In_ void * data, int radix, _In_opt_ void * endchar, _Out_ unsigned long *result);

MI_Real64 mof_strtod(MI_Boolean unicode, _In_ void * data);

MI_Sint64 mof_strtoll(MI_Boolean unicode, _In_ void * data, void ** endchar, int base);

MI_Sint64 mof_strtoull(MI_Boolean unicode, _In_ void * data, void ** endchar, int base);

void* mof_setchar(MI_Boolean unicode, _In_ void * data, int c);

MI_Boolean mof_isvalidhexstring(MI_Boolean unicode, void * data, size_t length);

/*
**==============================================================================
**
** Utilities handle MOF_Buffer
**
**==============================================================================
*/
int mof_nextcharn(_Inout_ MOF_Buffer* b, _Inout_ size_t *len);

MI_Boolean mof_eof(_In_ MOF_Buffer* b);

MI_Boolean mof_neof(_In_ MOF_Buffer* b);

void mof_fillbuf(_In_ MOF_Buffer* b,
                 _Out_writes_(size) MI_Char *buf,
                 _In_ MI_Uint32 size);

/*
**==============================================================================
**
** Error reporting functions
**
**==============================================================================
*/
extern void moferror(_In_ MOF_ErrorHandler *errhandler, _In_z_ const char* msg);

extern void yywarnf(_In_ MOF_ErrorHandler *errhandler, int id, _In_z_ const char *fmt, ...);

#define MOF_TRACE printf("MOF_TRACE: %s(%u)\n", __FILE__, __LINE__)

#define MOF_NOT_FOUND ((MI_Uint32)0xFFFFFFFF)

#define MOF_ASSERT(COND) assert(COND)

/*
**==============================================================================
**
** Utility report final error to error handler, it produces error code,
** error type, and error category based on error ID
**==============================================================================
*/
void ReportFinalError(
    _In_ MOF_ErrorHandler* errhandler,
    _In_ int id,
    _In_z_ MI_Char* formattedMSG);

/*
**==============================================================================
**
** Allocation utilities from batch
**
**==============================================================================
*/
void* MOF_Realloc(Batch* batch, void* ptr, size_t orgsize, size_t size);

/*
**==============================================================================
**
** Type-aware forms of memory allocation functions from batch
**
**==============================================================================
*/
#define CALLOC_T(ZT, N) ((ZT*)Batch_GetClear(state->batch, N * sizeof(ZT)))
#define MALLOC_T(ZT, N) ((ZT*)Batch_Get(state->batch, N * sizeof(ZT)))
#define REALLOC_T(ZT, PTR, O, N) ((ZT*)MOF_Realloc(state->batch,PTR,(O)*sizeof(ZT),(N)*sizeof(ZT)))

/*
**==============================================================================
**
** Other utilities
**
**==============================================================================
*/
MI_Result mof_setupbuffer(
    _In_reads_bytes_(nBytes) void * data,
    _In_ size_t nBytes,
    _In_opt_ Batch *batch,
    _Inout_ MOF_Buffer * b);

/* Convert UTF16 Big Endian to Little Endian string */
int mof_converttoUTF16LE(_Inout_ MOF_State * state, _Inout_ MOF_StringLen *r);

/*
**==============================================================================
**
** IO utilities
**
**==============================================================================
*/
#if defined(CONFIG_ENABLE_WCHAR)
# define Zfprintf fwprintf
#else
# define Zfprintf fprintf
#endif
#endif
