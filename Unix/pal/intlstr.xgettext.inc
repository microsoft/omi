
/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#include <pal/format.placeholders.h>

#define Intlstr_Define0(id, name, text) gettext(text)
#define Intlstr_Define1(id, name, parameter1_type, parameter1_name, text) gettext(text)
#define Intlstr_Define2(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, text) gettext(text)
#define Intlstr_Define3(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, text) gettext(text)
