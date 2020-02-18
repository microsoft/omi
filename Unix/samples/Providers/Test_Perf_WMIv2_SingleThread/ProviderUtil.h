/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _ProviderUtil_h
#define _ProviderUtil_h

#include <stdlib.h>
#include "MI.h"
#include "Perf_Embedded.h"

#define IF_ERROR_POST_RETURN(_context, _result) \
    { if (_result != MI_RESULT_OK) \
        { MI_PostError(_context, _result, MI_RESULT_TYPE_MI, MI_T("")) ; return; } } 

#define IF_ERROR_POST_RETURN_WITH_RETURNVALUE(_context, _result, returnValue) \
    { if (_result != MI_RESULT_OK) \
        { MI_PostError(_context, _result, MI_RESULT_TYPE_MI, MI_T("")) ; return returnValue; } } 
        
#define IF_ERROR_DESTRUCT_POST_RETURN(_context, _result, _instance) \
    { if (_result != MI_RESULT_OK) \
        { \
        MI_Instance_Destruct(&_instance); \
        MI_PostError(_context, _result, MI_RESULT_TYPE_MI, MI_T("")); return; } } 

#define IF_ERROR_DESTRUCT_POST_RETURNVALUE(_context, _result, _instance, returnValue) \
    { if (_result != MI_RESULT_OK) \
        { \
        MI_Instance_Destruct(&_instance); \
        MI_PostError(_context, _result, MI_RESULT_TYPE_MI, MI_T("")); return returnValue; } } 

#define IF_ERROR_DELETE_ARRAY_POST_RETURN(_context, _result, _instance, _arrInstances, _arrCount) \
    { if (_result != MI_RESULT_OK) \
        { \
        for(MI_Uint32 j = 0; j < _arrCount; ++j) \
        { \
            MI_Instance_Destruct(_arrInstances[j]); \
        } \
        delete[] _arrInstances; \
        MI_Instance_Destruct(&_instance); \
        MI_PostError(_context, _result, MI_RESULT_TYPE_MI, MI_T("")); return; } } 

#define IF_ERROR_BREAK(_result) \
    { \
        if(_result != MI_RESULT_OK) \
            break; \
    } 

MI_Result FillInstance(MI_Context* context, MI_Instance* newInstance, MI_Uint64 keyValue);
MI_Result PostPsSemantics(MI_Context* context, MI_Uint32 PsSemanticsFlags, MI_Uint32 psSemanticsCount);


#endif
