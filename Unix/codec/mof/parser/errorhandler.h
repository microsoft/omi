/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _mof_errorhandler_h
#define _mof_errorhandler_h

//#ifndef MI_CHAR_TYPE
//# define MI_CHAR_TYPE 1
//#endif

#include <MI.h>

/*
**==============================================================================
**
** MOF_ErrorHandler
**  Contains callbacks handle errors, including callback of lookup localized
**  string, callbcak of reporting error data.
**
**==============================================================================
*/
#define MSG_SIZE 256
typedef struct _MOF_ErrorHandler
{
    /* error infomation */
    _Field_size_(MSG_SIZE) MI_Char errormsg[MSG_SIZE];

    /* User callback to invoke to look up string */
    _Post_z_ MI_Char * (*stringLookup)(
        MI_Uint32 id,
        _Out_writes_z_(len) MI_Char *buffer,
        size_t len);

    /* Callback to report final error */
    void* onErrorContext;
    void (*onError)(
        _In_ void * onErrorContext,
        MI_Uint32 errorCode,
        MI_Uint16 errorCategory,
        _In_opt_z_ const MI_Char * errorType,
        _In_opt_z_ const MI_Char * errorMessage);

    /* state object, it could be null if no state object setup yet */
    void *state;
}MOF_ErrorHandler;


#endif /* _mof_errorhandler_h */
