/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.     
*/
/**
    \TestClient.h 
    \brief       < Common function in TestClient. > 
    \date        12-28-10 11:23:02
*/
/*----------------------------------------------------------------------------*/
#ifndef _TestClient_h
#define _TestClient_h   

#include <base/strings.h>

#define T MI_T

mi::String MakeString(const char* str); 
bool StringToBoolean(const mi::String& isKey);
mi::Type StringToType(const mi::String& dataType);
mi::String Replace(const mi::String& source, mi::String sub, const mi::String rep);

#endif 
