#ifndef _buf_h
#define _buf_h

#include <MI.h>

typedef struct Buf
{
    /* Pointer to data buffer */
    MI_Char* data;

    /* Current size of buffer */
    size_t size;

    /* Current capacity of buffer */
    size_t capacity;

    /* Non-zero if Buf instance owns the 'data' buffer */
    int owner;
}
Buf;

MI_Result Buf_Construct(
    _Out_ Buf* self,
    _Inout_ MI_Char* data,
    size_t capacity);

void Buf_Destruct(
    _Inout_ Buf* self);

MI_Result Buf_Put(
    _Inout_ Buf* self,
    _In_reads_(size) const MI_Char* data,
    size_t size);

MI_INLINE MI_Result Buf_PutC(
    _Inout_ Buf* self,
    const MI_Char c)
{
    return Buf_Put(self, &c, 1);
}

MI_Result Buf_PutStr(
    _Inout_ Buf* self,
    _In_z_ const MI_Char* str);

#endif /* _buf_h */
