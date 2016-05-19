/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _miapi_InteractionProtocolHandler_h_
#define _miapi_InteractionProtocolHandler_h_

MI_Result MI_MAIN_CALL InteractionProtocolHandler_Application_Initialize(MI_Uint32 flags, 
    _In_opt_z_ const MI_Char * applicationID,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_      MI_Application *miApplication);


#endif /* _miapi_InteractionProtocolHandler_h_ */

