#ifndef _omi_base64_h
#define _omi_base64_h

#include <common.h>

BEGIN_EXTERNC

typedef int (*Base64EncCallback)(
    const char* data, 
    size_t size, 
    void* callbackData);

int Base64Enc(
    const void* data,
    size_t size,
    Base64EncCallback callback,
    void* callbackData);

typedef int (*Base64DecCallback)(
    const void* data, 
    size_t size, 
    void* callbackData);

int Base64Dec(
    const void* data_,
    size_t size,
    Base64DecCallback callback,
    void* callbackData);

END_EXTERNC

#endif /* _omi_base64_h */
