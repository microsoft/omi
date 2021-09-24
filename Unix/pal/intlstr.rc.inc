
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
** MERCHANTABILITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#ifndef INTLSTR_RC_INC
#define INTLSTR_RC_INC
#endif

#include <pal/format.placeholders.h>

#define Intlstr_Define0(id, name, text) id, text "\0."
#define Intlstr_Define1(id, name, parameter1_type, parameter1_name, text) id, text "\0."
#define Intlstr_Define2(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, text) id, text "\0."
#define Intlstr_Define3(id, name, parameter1_type, parameter1_name, parameter2_type, parameter2_name, parameter3_type, parameter3_name, text) id, text "\0."

/* Notes:
 *
 * - LoadString (when returning a read-only pointer / in case a caller didn't provide a buffer) doesn't guarantee that the returned string is NUL-terminated.
 *   This knowledge is based on 1) lack of explicit guarantee in documentation, 2) reading source code of LoadString.
 *   To workaround - we are explicitly adding a NUL character above.
 */