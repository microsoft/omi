/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
