/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.     
*/
/**
    \CustomizedMethod.h 
    \brief       < Define cusomized method to get expected value exactly. > 
    \date        01-06-11 11:23:02
*/
/*----------------------------------------------------------------------------*/
#ifndef _CustomizedMethod_h
#define _CustomizedMethod_h

#include <micxx/dinstance.h>
#include <string>
#include <base/strings.h>
#include <vector>
#include <map>

void RunCommand(const char* command, mi::String &value);

// Type define function
typedef void (*MODULE_TEST_CALLBACK) (mi::String &value);


// Call registeration function first time.
void _RegisterFunction();
void _registerCallback(mi::String methodName, MODULE_TEST_CALLBACK pfn);


// Macro define function registration.
#define REG_TEST() _RegisterFunction() 

// Macro define:call _registerCallback to append customized function. 
#define APPEND_TEST(METHODNAME, FUNC) _registerCallback(METHODNAME, FUNC)  

#endif
