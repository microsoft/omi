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

#ifndef _OI_ManifestGen_h_
#define _OI_ManifestGen_h_

#include "common.h"
#include "oicommon.h"
#include "OIParser.h"
#include "EtwGen.h"

BEGIN_EXTERNC

/*
    GenerateManifest

    generates Windows CBS manifest for OI tracing

    events - linked list of OI event description
    providerId - GUID
    binary - message, parameter and resource file name
    target - output file for the generated code
*/
MI_Boolean GenerateManifest(
    _In_   OIEvent * events,
    _In_   Buckets * etwInfo,
    _In_z_ char * providerName,
    _In_z_ char * providerId,
    _In_z_ char * binary,
    _In_z_ char * target);

END_EXTERNC

#endif /* _OI_ManifestGen_h_ */
