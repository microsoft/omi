/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _indication_indimgr_listener_h
#define _indication_indimgr_listener_h

#include <common.h>
#include <base/Strand.h>
#include <base/messages.h>
#include "cimbase.h"

#define TEMP_LISTENER_ID_PREFIX MI_T("_templistener")

BEGIN_EXTERNC

/*
**==============================================================================
**
** Defines listener persistent types
**
**==============================================================================
*/
typedef enum _PersistenceType
{
    LISTENER_TEMP = 0,       /* Delivery result via incoming connection from */
                             /* subscription caller */
    LISTENER_OTHER,          /* Undefined */
    LISTENER_PERMANENT,      /* Listener is always expected to be available */
                             /* Inability to access this destination MUST be */
                             /* treated as an error condition. */
    LISTENER_TRANSIENT       /* Listener is short-lived, Inability to access */
                             /* the destination MAY be treated as a normal */
                             /* termination condition. */
}
PersistenceType;

/*
**==============================================================================
**
** Forward structure typedef declarations.
**
**==============================================================================
*/

typedef struct _Listener Listener;
typedef struct _ListenerFT ListenerFT;

/*
**==============================================================================
**
** Function that handling result indication instance from provider
**
**==============================================================================
*/
typedef void (MI_CALL* fnOnNewIndication)(
    _In_ Listener* listener,
    _In_ Interaction* interaction,
    _In_ PostInstanceMsg* instanceMsg);

/*
**==============================================================================
**
** Function that handling final result from indication manager
**
**==============================================================================
*/
typedef void (MI_CALL* fnOnFinalResult)(
    _In_ Listener* listener,
    _In_ Interaction* interaction,
    _In_ MI_Result result,
    _In_opt_ MI_Instance* errDetails);

/*
**==============================================================================
**
** Represents a CIM indication filter object
**
**==============================================================================
*/
struct _Listener
{
    CimBase base;

#if 0 /* To be enabled for indication profile */

    /* CIM_ManagedElement properties */
    MI_Char* InstanceID;
    MI_Char* Caption;
    MI_Char* Description;
    MI_Char* ElementName;

    /* CIM_ListenerDestination properties */
    MI_Char* SystemCreationClassName; /*key*/
    MI_Char* SystemName; /*key*/
    MI_Char* CreationClassName; /*key*/
    MI_Char* Name; /*key*/

    MI_Char* OtherPersistenceType;
    MI_Char* Destination;
    MI_Char* OtherProtocol;

    /*1: Other; 2:CIM-XML; 3:SM CLP; 4:WS-Management; 5:WSDM; ..:DMTF Reserved*/
    MI_Uint16 protocol; /* Default 2 */

#endif

    /*1: Other; 2:Permanent; 3:Transient*/
    MI_Uint16 PersistenceType;  /* Default 2 */
};

/* Creates a Listener object */
Listener* Listener_New(PersistenceType type);

/* Add a reference to a Listener object */
int Listener_AddRef(
    _Inout_ Listener* self);

/* Release a reference to a Listener object */
int Listener_Release(
    _Inout_ Listener* self);

/* Get reference count */
int Listener_GetRefcount(_In_ Listener *self);

END_EXTERNC

#endif /* _indication_indimgr_listener_h */
