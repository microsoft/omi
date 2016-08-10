/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <stdarg.h>
#include "result.h"

const ZChar* Result_ToString(MI_Result result)
{
    size_t i;
    struct Pair
    {
        MI_Result result;
        const ZChar* str;
    };
    static struct Pair _pairs[] =
    {
        {
            MI_RESULT_OK,
            MI_T("MI_RESULT_OK")
        },
        {
            MI_RESULT_FAILED,
            MI_T("MI_RESULT_FAILED")
        },
        {
            MI_RESULT_ACCESS_DENIED,
            MI_T("MI_RESULT_ACCESS_DENIED")
        },
        {
            MI_RESULT_INVALID_NAMESPACE,
            MI_T("MI_RESULT_INVALID_NAMESPACE")
        },
        {
            MI_RESULT_INVALID_PARAMETER,
            MI_T("MI_RESULT_INVALID_PARAMETER")
        },
        {
            MI_RESULT_INVALID_CLASS,
            MI_T("MI_RESULT_INVALID_CLASS")
        },
        {
            MI_RESULT_NOT_FOUND,
            MI_T("MI_RESULT_NOT_FOUND")
        },
        {
            MI_RESULT_NOT_SUPPORTED,
            MI_T("MI_RESULT_NOT_SUPPORTED")
        },
        {
            MI_RESULT_CLASS_HAS_CHILDREN,
            MI_T("MI_RESULT_CLASS_HAS_CHILDREN")
        },
        {
            MI_RESULT_CLASS_HAS_INSTANCES,
            MI_T("MI_RESULT_CLASS_HAS_INSTANCES")
        },
        {
            MI_RESULT_INVALID_SUPERCLASS,
            MI_T("MI_RESULT_INVALID_SUPERCLASS")
        },
        {
            MI_RESULT_ALREADY_EXISTS,
            MI_T("MI_RESULT_ALREADY_EXISTS")
        },
        {
            MI_RESULT_NO_SUCH_PROPERTY,
            MI_T("MI_RESULT_NO_SUCH_PROPERTY")
        },
        {
            MI_RESULT_TYPE_MISMATCH,
            MI_T("MI_RESULT_TYPE_MISMATCH")
        },
        {
            MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED,
            MI_T("MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED")
        },
        {
            MI_RESULT_INVALID_QUERY,
            MI_T("MI_RESULT_INVALID_QUERY")
        },
        {
            MI_RESULT_METHOD_NOT_AVAILABLE,
            MI_T("MI_RESULT_METHOD_NOT_AVAILABLE")
        },
        {
            MI_RESULT_METHOD_NOT_FOUND,
            MI_T("MI_RESULT_METHOD_NOT_FOUND")
        },
        {
            MI_RESULT_NAMESPACE_NOT_EMPTY,
            MI_T("MI_RESULT_NAMESPACE_NOT_EMPTY")
        },
        {
            MI_RESULT_INVALID_ENUMERATION_CONTEXT,
            MI_T("MI_RESULT_INVALID_ENUMERATION_CONTEXT")
        },
        {
            MI_RESULT_INVALID_OPERATION_TIMEOUT,
            MI_T("MI_RESULT_INVALID_OPERATION_TIMEOUT")
        },
        {
            MI_RESULT_PULL_HAS_BEEN_ABANDONED,
            MI_T("MI_RESULT_PULL_HAS_BEEN_ABANDONED")
        },
        {
            MI_RESULT_PULL_CANNOT_BE_ABANDONED,
            MI_T("MI_RESULT_PULL_CANNOT_BE_ABANDONED")
        },
        {
            MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED,
            MI_T("MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED")
        },
        {
            MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED,
            MI_T("MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED")
        },
        {
            MI_RESULT_SERVER_LIMITS_EXCEEDED,
            MI_T("MI_RESULT_SERVER_LIMITS_EXCEEDED")
        },
        {
            MI_RESULT_SERVER_IS_SHUTTING_DOWN,
            MI_T("MI_RESULT_SERVER_IS_SHUTTING_DOWN")
        },
        {
            MI_RESULT_CANCELED,
            MI_T("MI_RESULT_CANCELED")
        },
        {
            MI_RESULT_OPEN_FAILED,
            MI_T("MI_RESULT_OPEN_FAILED")
        },
        {
            MI_RESULT_INVALID_CLASS_HIERARCHY,
            MI_T("MI_RESULT_INVALID_CLASS_HIERARCHY")
        },
        {
            MI_RESULT_WOULD_BLOCK,
            MI_T("MI_RESULT_WOULD_BLOCK")
        },
        {
            MI_RESULT_TIME_OUT,
            MI_T("MI_RESULT_TIME_OUT")
        },
    };

    for (i = 0; i < MI_COUNT(_pairs); i++)
    {
        if (result == _pairs[i].result)
            return _pairs[i].str;
    }

    /* Not found! */
    return MI_T("");
}
