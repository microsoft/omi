/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _Module_t_h
#define _Module_t_h

#include <MI.h>
#include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

/*  instance of this class is automatically created when library is loaded;
    it's a convenient place to store global data associated with the module */
class Module
{
public:
    Module();
    ~Module();

};

MI_END_NAMESPACE
#endif /* _Module_t_h */

