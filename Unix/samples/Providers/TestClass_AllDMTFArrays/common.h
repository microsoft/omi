/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#define POST_ERROR(_context, _result, _type, _contextualMessage) \
{    \
    MI_PostError(_context, _result, _type, _contextualMessage);        \
    return;    \
}
