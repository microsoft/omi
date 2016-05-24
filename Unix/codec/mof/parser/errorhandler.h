/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
