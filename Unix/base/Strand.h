/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _Strand_h
#define _Strand_h

#include <pal/thread.h>
#include <pal/atomic.h>
#include <pal/slist.h>
#include <pal/hashmap.h>
#include <base/interaction.h>
#include <sock/selector.h>
#include <pal/palcommon.h>

BEGIN_EXTERNC

//------------------------------------------------------------------------------------------------------------
// General Utility functions
//------------------------------------------------------------------------------------------------------------

MI_INLINE
ptrdiff_t
ReadWithFence (
    _In_ volatile ptrdiff_t* source
    )
{
    return Atomic_CompareAndSwap( source, 0, 0 );
}

MI_INLINE
unsigned long
GetFirstSetLSB( ptrdiff_t x )
{
    if( x != 0 )
    {
#if defined(CONFIG_HAVE_BUILTIN_CTZ)
        return __builtin_ctz( (unsigned long) x ) + 1;
#else
        unsigned long count = 0;
        unsigned long ulX = (unsigned long)x;
        while(ulX)
        {
            if((ulX & 1) != 0)
                break;
            count++;
            ulX = ulX >> 1;
        }

        return count + 1;
#endif
    }
    else
        return 0;
}

#define FromOffset( type, memberName, memberPtr )   ( (type*) ( ((char*)(memberPtr)) - offsetof(type,memberName) ) )
#define FromOffsetConst( type, memberName, memberPtr )   ( (const type*) ( ((const char*)(memberPtr)) - offsetof(type,memberName) ) )

//------------------------------------------------------------------------------------------------------------

#if defined(CONFIG_ENABLE_DEBUG)
#define STRAND_ENABLE_DEBUG 1
#endif

//------------------------------------------------------------------------------------------------------------
// Strand Types
#define STRAND_TYPE_NOINTERACTION       0
#define STRAND_TYPE_LEFTMOST            1
#define STRAND_TYPE_RIGHTMOST           2
#define STRAND_TYPE_MIDDLE              3
#define STRAND_TYPE_PARENTLEFT          4
#define STRAND_TYPE_PARENTRIGHT         5
#define STRAND_TYPE_PARENTNOINTERACTION 6
#define STRAND_TYPE_ENTRY               7

#define STRAND_ISTYPE_EDGE( strand )    ( (strand)->strandType == STRAND_TYPE_LEFTMOST || (strand)->strandType == STRAND_TYPE_RIGHTMOST )
#define STRAND_ISTYPE_MIDDLE( strand )  ( (strand)->strandType == STRAND_TYPE_MIDDLE )
#define STRAND_ISTYPE_PARENT( strand )  ( (strand)->strandType == STRAND_TYPE_PARENTLEFT || (strand)->strandType == STRAND_TYPE_PARENTRIGHT || (strand)->strandType == STRAND_TYPE_PARENTNOINTERACTION )
#define STRAND_ISTYPE_ENTRY( strand )   ( (strand)->strandType == STRAND_TYPE_ENTRY )
#define STRAND_ISTYPE_MANY( strand )    ( STRAND_ISTYPE_ENTRY(strand) || STRAND_ISTYPE_PARENT(strand) )

typedef enum _TimerReason
{
    TimerReason_Expired         = 0,
    TimerReason_ManuallyFired   = 1,
    TimerReason_Canceled        = 2
}
TimerReason;

//------------------------------------------------------------------------------------------------------------
typedef MI_Boolean (*StrandMethod)( _In_ Strand* );

// Similar to the interaction one, but this called from the strand
typedef struct _StrandFT
{
    // - On a StrandBoth this can be NULL
    //      and if the other side is opened message will always pass thru to the other side
    // - On a StrandMany(parent) this can be NULL
    //      and the message will be passed either a found entry or all entries (if findEntryProc is NULL)
    // - On a StrandEntry this can be NULL
    //      and the message will be passed thru to the to the parent (once possible)
    void (*Post)( _In_ Strand* self, _In_ Message* msg);

    // - On a StrandBoth this can be NULL
    //      and if the other side is opened message will always pass thru to the other side
    // - On a StrandMany(parent) this can be NULL
    //      and the message will be passed either a found entry or all entries (if findEntryProc is NULL)
    // - On a StrandEntry this can be NULL
    //      and the message will be passed to the to the parent (once possible)
    void (*PostControl)( _In_ Strand* self, _In_ Message* msg);

    // If this one is set to NULL (It should be NULL in a StrandMany(parent)):
    // - On normal Strand it will no do anything
    // - On StrandBoth it will pass thru to the other side if that side is Pending Ack (even if ackPassThru parameter is not set on Open/Post)
    // - On a StrandMany(parent) it will take care of keep sending messages from entries
    // - On a StrandEntry it will no do anything (NOTE that user is responsible to manage flow control if there are secondary messages)
    void (*Ack)( _In_ Strand* self);

    // If this one is set to NULL the strand will take care itself
    // - On a Strand it will not do anything (only sending back to the left it is on the right)
    // - On a StrandBoth (even if it is not NULL) it always take care of passing thru cancel to the other side (if interaction is opened and not closed yet)
    // - On a StrandMany(parent) it cancels all entries
    // - On a StrandEntry it cancels the parent
    void (*Cancel)( _In_ Strand* self);

    // If this one is set to NULL the strand will take care itself,
    // including passing thru close to the other side (only in that case)
    // - On a StrandMany(parent) it closes all entries
    // - On a StrandEntry it does nothing (user should call StrandEntry_CloseParent if wants to close the parent)
    void (*Close)( _In_ Strand* self);

    // Called when everything is finished (there are no ack pendings and everything is closed)
    // if NULL the strand will just delete itself
    void (*Finish)( _In_ Strand* self);

    // Called when either the timer expires or Strand_FireTimer is called
    // Should not be NULL if the timer is used
    void (*Timer)( _In_ Strand* self, TimerReason reason);

    // Auxiliary (optional) strand methods
    void (*Aux0)( _In_ Strand* self);
    void (*Aux1)( _In_ Strand* self);
    void (*Aux2)( _In_ Strand* self);
    void (*Aux3)( _In_ Strand* self);
    void (*Aux4)( _In_ Strand* self);
}
StrandFT;

typedef struct _StoredMsg
{
    Message *           msg;                // scheduled msg
    Message *           controlMsg;         // control msg (Note if we have more than one control message type we will need to add more of this)
} StoredMsg;

// information about one side interaction
typedef struct _InteractionInfo
{
    Interaction         interaction;        // interaction used
    StrandFT *          userFT;             // user methods
    MI_Boolean          opened;             // if the interaction have been opened (initial Ack is pending otherwise)
    MI_Boolean          thisClosedOther;    // if we closed the interaction with other component
    MI_Boolean          thisAckPending;     // if we posted to the other component and have an ack pending from it
    MI_Boolean          otherClosedThis;    // if the other component closed this interaction
    MI_Boolean          otherAckPending;    // if the other component posted to this component and have an ack pending from us
    MI_Boolean          ackPassthru;        // if the ack to last post/open should be relayed automatically to the other side (in a pass-thru fashion)
    StoredMsg           stored;             // stored scheduled msg(s)
    Message *           otherMsg;           // scheduled msg for other
} InteractionInfo;

typedef struct _Timer Timer;

#if defined(STRAND_ENABLE_DEBUG)
typedef const char ** StrandDebugInfo;
#define STRAND_DEBUG( debugInfoName )   _Strand_DebugInfo_##debugInfoName,
#define STRAND_PASSDEBUG( debugInfo )   debugInfo,
#else
#define STRAND_DEBUG( debugInfoName )
#define STRAND_PASSDEBUG( debugInfo )
#endif

//---------------------------------------------------------------------------------------------------------------------
// Used during creation (*_New/*_Init) to indicate that we are entering the strand
// that we just created (It SHOULD call Strand_Leave to leave it)
#define STRAND_FLAG_ENTERSTRAND         0x1

// Only used on Strand/StrandMany/StrandEntry (it doesnt make sense on StrandBoth)
#define STRAND_FLAG_NOINTERACTION       0x2

// Can be issued by Strand_New/StrandBoth_New/StrandMany_New/StrandEntry_New
// (does NOT zeroes all allocated fields)
// Note that Strand_Init/StrandBoth_Init only initialize strand fields
// so since it doesnt have additional fields, that flag SHOULD NOT be used there
// (it is used internally to indicate that fields have NOT been zeroed already)
#define STRAND_FLAG_NOZEROALLOCATED     0x4

// When a Strand object is going to be deleted (just before calling Finish),
// if it has a running timer then it is going to automatically fire/close it first
// and only then (after timer callback) call Finish.
// If the implementer wants instead to wait until the timer expires before calling Finish
// it can specify the following flag
// IMPORTANT: Please note that the Strand will not be deleted in that case until
// no timer is set (what can delay general shutdown).
#define STRAND_FLAG_FINISHWAITSFORTIMER 0x8

// Delays accepting the open/acking open until Strand_AcceptOpen() is called
#define STRAND_FLAG_DELAYACCEPTOPEN     0x10

typedef unsigned short StrandFlags;

//---------------------------------------------------------------------------------------------------------------------
// Strand with interactions in one side
struct _Strand
{
#if defined(STRAND_ENABLE_DEBUG)
    StrandDebugInfo     debug;
    ThreadID            threadId;               // threadId of the thread executing strand (if any)
    ThreadID            testThreadId;
#endif
    volatile ptrdiff_t  stateScheduled;         // methods marked for execution (by order bit)
    StrandMethod *      strandMethods;
    MI_Boolean          canceled;               // if we have been canceled (either way)
    MI_Boolean          delayFinish;            // if the object wants to delay its finalization (false by default)
    ptrdiff_t           currentMethodBit;
    MI_Boolean *        strandStealedFlag;      // used to notify bailing out when an opening is completed while running a strand method
    unsigned char       strandType;             // see STRAND_TYPE_* above
    StrandFlags         flags;
    Timer*              timer;
    InteractionInfo     info;                   // Interaction info (for the left on StrandBoth)
};

// Strand with interactions in both directions
typedef struct _StrandBoth
{
    Strand              base;
    InteractionInfo     infoRight;          // Interaction info used for the right interaction
    MI_Boolean          leftCanceled;       // If we have passed the cancelation to the left side
    //Flag to track an async open on right interaction initiated but not yet completed.
    //This is introduced to have a simple solution to prevent WSManCD leaks on
    //different failure paths that did not have the right interaction opened yet
    //Note that only WSManCD currently does an async open on the right interaction.
    //TODO: This needs to be integrated into base strand or we need a better alternative
    MI_Boolean          asyncOpenInProgress;      // False initially, True upon an async open, False upon open completion
} StrandBoth;

typedef struct _StrandMany StrandMany;
typedef struct _StrandEntry StrandEntry;

typedef StrandEntry* (*FindEntryProc)(_In_ const StrandMany* parent, _In_ const Message* msg);

// Used on StrandMany between parent and entries
typedef struct _StrandManyInternalFT
{
    // Called on the parent when StrandEntry_ScheduleNew is called
    // Can be NULL if StrandEntry_ScheduleNew is never used
    // note that if it is used and it is NULL failure on creation
    // may go unnoticed.
    // *failed can be MI_TRUE if the entry failed to be added,
    // or the user function can also set it to MI_TRUE if it has
    // a problem (like starting the interaction);
    // The entry will be automatically deleted in either case.
    void (*NewEntry)( _In_ StrandMany* self, _In_ StrandEntry* newEntry, _In_opt_ Message* msg, _Inout_ MI_Boolean* failed );

    // Called when (after) a entry is deleted (by the Entry itself, not by the parent)
    // If NULL does nothing
    void (*EntryDeleted)( _In_ StrandMany* self );

    // If NULL message is just posted thru the interaction (when possible)
    // If NOT NULL, it is only called once ACK is not pending
    void (*EntryPost)( _In_ StrandMany* self, _In_ Message* msg);

    // If NULL message is just posted thru the interaction
    void (*EntryPostControl)( _In_ StrandMany* self, _In_ Message* msg);

    // If NULL interaction is closed (if not already)
    // If NOT NULL, it is only called if the interaction is not closed already
    void (*EntryClose)( _In_ StrandMany* self);

    // Called once the parent has added us
    // If NULL nothing is done
    void (*AddedToParent)( _In_ StrandEntry* self, _In_opt_ Message* msg);

    // If NULL message is just posted thru the interaction
    void (*ParentPost)( _In_ StrandEntry* self, _In_ Message* msg);

    // If NULL message is just posted thru the interaction
    void (*ParentPostControl)( _In_ StrandEntry* self, _In_ Message* msg);

    // If NULL ack is just passed thru (if passthru version was used)
    void (*ParentAck)( _In_ StrandEntry* self);

    // If NULL interaction is closed
    void (*ParentClose)( _In_ StrandEntry* self);
}
StrandManyInternalFT;

// Strand with interactions on to many
struct _StrandMany
{
    SListHead               pending;        // pending operations on main strand
    HashMap                 many;           // collection with interactions on the MANY direction (a StrandEntry)
    HashMapIterator         iter;           // to interato thru "many"
    size_t                  numEntries;     // number of entries on "many"
    FindEntryProc           findEntryProc;
    Strand                  strand;         // includes interaction for the Parent
    StrandManyInternalFT*   userInternalFT;
    StrandEntry*            currentEntry;   // current entry whose operation is being executed
    MI_Boolean              pendingRetry;   // if there are items in the pending list for retry
};

typedef unsigned short EntryOperationMaskType;

// A Strand with interaction belonging to the MANY part of StrandMany
struct _StrandEntry
{
    SListEntry              entry;              // to be used on parent "pending" list
    HashBucket              bucket;             // to be used on parent "many" list
    Strand                  strand;             // Includes Interaction info for the entry
    StrandMany *            parent;
    EntryOperationMaskType  operationScheduled; // entry operation scheduled on parent
    EntryOperationMaskType  operationsPending;  // entry operations pending to be scheduled on parent
    MI_Boolean              ackPassthru;        // if the ack for the post parent operation should go pass thru to interaction
    StoredMsg               toParent;           // stored scheduled msg(s) to/for parent
    StoredMsg               fromParent;         // stored scheduled msg(s) from parent
};

// If interaction is NULL then is assumed that is going to open an interaction to the right
// (and thisAckPending is going to be set to true)
Strand* Strand_New(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _In_        StrandFT *              userFT,
                size_t                  structSize,
                StrandFlags             flags,
    _In_opt_    InteractionOpenParams*  interactionOpenParams );

// If interaction is NULL then is assumed that is going to open an interaction to the right
// (and thisAckPending is going to be set to true)
void Strand_Init(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _Out_       Strand*                 self,
    _In_        StrandFT*               userFT,
                StrandFlags             flags,
    _In_opt_    InteractionOpenParams*  interactionOpenParams );
// interaction indicates the interaction opening from the left
// It is always assumed that is going to open an interaction to the right
StrandBoth* StrandBoth_New(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _In_        StrandFT*               userLeftFT,
    _In_        StrandFT*               userRightFT,
                size_t                  structSize,
                StrandFlags             flags,
    _In_opt_    InteractionOpenParams*  interactionOpenParams );

// interaction indicates the interaction opening from the left
// It is always assumed that is going to open an interaction to the right
void StrandBoth_Init(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _Out_       StrandBoth*             self,
    _In_        StrandFT*               userLeftFT,
    _In_        StrandFT*               userRightFT,
                StrandFlags             flags,
    _In_opt_    InteractionOpenParams*  interactionOpenParams );

// interaction indicates the interaction opening from the left
// otherwise if parentHasInteraction is MI_TRUE it is then assumed that is going to open an interaction to the right
// (and infoRight.thisAckPending is going to be set to true)
StrandMany* StrandMany_New(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _In_        StrandFT*               userParentFT,
    _In_opt_    StrandManyInternalFT*   userInternalFT,
                size_t                  structSize,
                StrandFlags             flags,
    _In_opt_    InteractionOpenParams*  interactionOpenParams,  // if STRAND_FLAG_NOINTERACTION is not used and interactionOpenParams is NULL it is assumed it will open an interaction on the right
                size_t                  numLists,               // numlist for the underlying Hash table, use 1 if it is not going to be searched
    _In_opt_    HashMapHashProc         hash,                   // hashing func for the underlying Hash table, if NULL will use the StrandEntry pointer
    _In_opt_    HashMapEqualProc        equal,                  // equal func for the underlying Hash table, can be NULL if it is not going to be searched or entry ptr comparison is ok
    _In_opt_    FindEntryProc           findEntryProc );        // finds a entry based on a message, can be NULL if msg should not be automatically redirected to entries

// This can be called from outside (StrandMany) parent strand
// IMPORTANT: The entry is not completely created/added until StrandEntry_ScheduleAdd/StrandMany_AddEntry is called
StrandEntry* StrandEntry_New(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _In_        StrandMany*             parent,
    _In_        StrandFT*               userEntryFT,
                size_t                  structSize,
                StrandFlags             flags,
    _In_opt_    InteractionOpenParams*  interactionOpenParams );

// Completes adding a entry created by StrandEntry_New
// if the entry cannot be added it will be automatically deleted
void StrandEntry_ScheduleAdd(
    _In_        StrandEntry*            self,
    _In_opt_    Message *               msg );          // optional initial message

// Completes adding a entry created by StrandEntry_New, but
// this should ONLY be called from parent (StrandMany) strand
// if the entry cannot be added it will be automatically deleted
MI_Result StrandMany_AddEntry(
    _In_        StrandEntry*            self );

// Can be used with any type of strand (this should be called in the object strand)
void Strand_Delete( _In_ Strand* self );

// It should delete all entries first (this should be called in the Parent object strand)
void StrandMany_Delete( _In_ StrandMany* self );

// Deletes a StrandEntry FROM the parent (StrandMany) strand
void StrandMany_DeleteEntry( _In_ StrandEntry* entry );

// Deletes a StrandEntry (this should be called in the Entry object strand)
void StrandEntry_Delete( _In_ StrandEntry* self );

// Deletes a StrandEntry that was NOT ADDED yet to the StrandMany
// (not StrandEntry_ScheduleAdd or StrandMany_AddEntry called)
MI_INLINE void StrandEntry_DeleteNoAdded( _In_ StrandEntry* self )
{
    SList_Free( self );
}

// Called inside a strand method (or when creating strand with STRAND_FLAG_ENTERSTRAND)
// to explictly leave the strand (prematurely on the case of the strand method)
// Note that additional strand methods can be called if they are already
// scheduled when Strand_Leave is called
void Strand_Leave( _In_ Strand* self );

//------------------------------------------------------------------------------------------------------------

// For testing purposes only
#if defined(STRAND_ENABLE_DEBUG)

#define STRAND_SETTESTSTRANDTHREAD( strand )    ((strand)->testThreadId = Thread_ID())

// internal use
MI_INLINE void _Strand_SetCurrentStrandThread( _In_ Strand* strand )
{
    strand->threadId = Thread_ID();
}

// internal use
MI_INLINE void _Strand_ExitCurrentStrandThread( _In_ Strand* strand )
{
    strand->threadId = Thread_ID_Null();
}

#else

#define STRAND_SETTESTSTRANDTHREAD( strand )
#define _Strand_SetCurrentStrandThread( strand )
#define _Strand_ExitCurrentStrandThread( strand )

#endif

// internal use
MI_INLINE void _Strand_Finish(
    _In_ Strand* self)
{
    if( NULL != self->info.userFT->Finish )
    {
        (*self->info.userFT->Finish)(self);
    }
    else
    {
        Strand_Delete( self );
    }
}

// internal use
MI_INLINE
void _Strand_Post_CommonImp(
    _In_ InteractionInfo*   info,
    _In_ Message *          msg)
{
    DEBUG_ASSERT( !info->thisClosedOther );
    DEBUG_ASSERT( !info->thisAckPending );

    info->thisAckPending = MI_TRUE;
}

// internal use
MI_INLINE
void _Strand_Post_Imp(
    _In_ InteractionInfo*   info,
    _In_ Message *          msg)
{
    DEBUG_ASSERT( !info->ackPassthru );

    _Strand_Post_CommonImp( info, msg );
    info->interaction.other->ft->Post( info->interaction.other, msg );
}

// internal use
MI_INLINE
void _Strand_PostPassthru_Imp(
    _In_ InteractionInfo*   info,
    _In_ Message *          msg)
{
    DEBUG_ASSERT( !info->ackPassthru );
    info->ackPassthru = MI_TRUE;

    _Strand_Post_CommonImp( info, msg );
    info->interaction.other->ft->Post( info->interaction.other, msg );
}

// internal use
MI_INLINE
void _Strand_PostAndLeaveStrand_Imp(
    _In_ Strand*            strand,
    _In_ InteractionInfo*   info,
    _In_ Message *          msg)
{
    Interaction* other = info->interaction.other;
    DEBUG_ASSERT( !info->ackPassthru );

    _Strand_Post_CommonImp( info, msg );
    Strand_Leave(strand);
    other->ft->Post( other, msg );
}

// internal use
MI_INLINE
void _Strand_PostControl_Imp(
    _In_ InteractionInfo*   info,
    _In_ Message *          msg)
{
    DEBUG_ASSERT( !info->thisClosedOther );

    info->interaction.other->ft->PostControl( info->interaction.other, msg );
}

// internal use
MI_INLINE
void _Strand_Ack_Imp(
    _In_ InteractionInfo*   info)
{
    DEBUG_ASSERT( info->otherAckPending );

    info->otherAckPending = MI_FALSE;
    info->opened = MI_TRUE; // as soon as it send an Ack it means the interaction has been opened
    info->interaction.other->ft->Ack( info->interaction.other );
}

// internal use
MI_INLINE
void _Strand_Close_Imp(
    _In_ InteractionInfo*   info)
{
    DEBUG_ASSERT( !info->thisClosedOther );

    info->thisClosedOther = MI_TRUE;
    if( NULL != info->interaction.other )
    {
        info->interaction.other->ft->Close( info->interaction.other );
    }
    // otherwise implies a strand without interaction
}

//------------------------------------------------------------------------------------------------------------
#define BitExecuting            0x1

#define FirstMethodBit          1
#define FirstRealMethodBit      1

// For all Strands
#define BitCompleteOpenAsync    0x2
#define BitTimer                0x4

// For Strands with just one interaction
#define BitCancel               0x8
#define BitCancelSelf           0x10
#define BitPostControl          0x20    // Note if we have more than one control message type we will need to add more of this
#define BitPost                 0x40
#define BitPostOther            0x80
#define BitAck                  0x100
#define BitAckOther             0x200
#define BitClose                0x400
#define BitCloseOther           0x800
#define BitAux0                 0x1000
#define BitAux1                 0x2000
#define BitAux2                 0x4000
#define BitAux3                 0x8000
#define BitAux4                 0x10000

#define Strand_NumBaseMethods   11
#define Strand_NumAuxMethods    5
#define Strand_NumMethods       (Strand_NumBaseMethods+Strand_NumAuxMethods)

// For Strands with both interactions
#define BitCancel_Left          0x8
#define BitCancel_Right         0x10
#define BitCancelSelf_Both      0x20
#define BitPostControl_Left     0x40    // Note if we have more than one control message type we will need to add more of this
#define BitPostControl_Right    0x80    // (and same here)
#define BitPost_Left            0x100
#define BitPost_Right           0x200
#define BitPostOther_Left       0x400
#define BitPostOther_Right      0x800
#define BitAck_Left             0x1000
#define BitAck_Right            0x2000
#define BitAckOther_Left        0x4000
#define BitAckOther_Right       0x8000
#define BitClose_Left           0x10000
#define BitClose_Right          0x20000
#define BitCloseOther_Left      0x40000
#define BitCloseOther_Right     0x80000
#define BitAux0_Left            0x100000
#define BitAux1_Left            0x200000
#define BitAux2_Left            0x400000
#define BitAux3_Left            0x800000
#define BitAux4_Left            0x1000000
#define BitAux0_Right           0x2000000
#define BitAux1_Right           0x4000000
#define BitAux2_Right           0x8000000
#define BitAux3_Right           0x10000000
#define BitAux4_Right           0x20000000

#define StrandBoth_NumBaseMethods   19
#define StrandBoth_NumAuxMethods    10
#define StrandBoth_NumMethods       (StrandBoth_NumBaseMethods+StrandBoth_NumAuxMethods)

// for StrandMany/StrandEntry
#define BitCancel_Many          0x8
#define BitCancelSelf_Many      0x10
#define BitCancelInternal       0x20
#define BitPostControl_Many     0x40    // Note if we have more than one control message type we will need to add more of this
#define BitPostControlInternal  0x80    // Note if we have more than one control message type we will need to add more of this
#define BitPost_Many            0x100
#define BitPostOther_Many       0x200
#define BitPostInternal         0x400
#define BitAck_Many             0x800
#define BitAckOther_Many        0x1000
#define BitAckInternal          0x2000
#define BitEntryOperation       0x4000   // Entry operation (for scheduling operations on parent from entries)
#define BitClose_Many           0x8000
#define BitCloseOther_Many      0x10000
#define BitCloseInternal        0x20000
#define BitAux0_Many            0x40000
#define BitAux1_Many            0x80000
#define BitAux2_Many            0x100000
#define BitAux3_Many            0x200000
#define BitAux4_Many            0x400000

#define StrandMany_NumBaseMethods   17
#define StrandMany_NumAuxMethods    5
#define StrandMany_NumMethods       (StrandMany_NumBaseMethods+StrandMany_NumAuxMethods)

// for StrandMany/StrandEntry, bits of EntryOperations scheduled on one particular entry
#define BitEntryAdd             0x1
#define BitEntryCancel          0x2
#define BitEntryPostControl     0x4
#define BitEntryPost            0x8
#define BitEntryClose           0x10
#define BitEntryAux0            0x20
#define BitEntryAux1            0x40
#define BitEntryAux2            0x80
#define BitEntryAux3            0x100
#define BitEntryAux4            0x200
#define BitEntryDeleted         0x400

#define StrandMany_FirstBitEntryOperationAux    6
#define StrandMany_LastBitEntryOperationAux     10
#define StrandMany_NumEntryOperations           11

// internal use
#if defined(STRAND_ENABLE_DEBUG)
extern void _Strand_ScheduleImp(
    _In_        Strand*                 self,
                unsigned int            methodBit,
                MI_Boolean              allowMultiSchedule,
    _In_opt_    Strand*                 fromStrand,
                EntryOperationMaskType  entryOperationBit );

#define _Strand_Schedule( self, methodBit ) \
    ( _Strand_ScheduleImp( (self), (methodBit), MI_FALSE, NULL, 0 ) )

#define _Strand_ScheduleEntryOperation( self, allowMultiSchedule, fromStrand, entryOperationBit ) \
    ( _Strand_ScheduleImp( (self), BitEntryOperation, (allowMultiSchedule), (fromStrand), (entryOperationBit) ) )

#define _Strand_ScheduleTimer( self ) \
    ( _Strand_ScheduleImp( (self), BitTimer, MI_TRUE, NULL, 0 ) )

#else

extern void _Strand_ScheduleImp(
    _In_        Strand*                 self,
                unsigned int            methodBit );

#define _Strand_Schedule( self, methodBit ) \
    ( _Strand_ScheduleImp( (self), (methodBit) ) )

#define _Strand_ScheduleEntryOperation( self, allowMultiSchedule, fromStrand, entryOperationBit ) \
    ( _Strand_ScheduleImp( (self), BitEntryOperation ) )

#define _Strand_ScheduleTimer( self ) \
    ( _Strand_ScheduleImp( (self), BitTimer ) )

#endif

//------------------------------------------------------------------------------------------------------------
// Debugging aid
//------------------------------------------------------------------------------------------------------------

#if defined(STRAND_ENABLE_DEBUG)
typedef struct _StrandBaseDebugInfo
{
    const char *    name;
    char            letter;
} StrandBaseDebugInfo;

extern StrandBaseDebugInfo _Strand_BaseNameDebugInfo[Strand_NumMethods+5];
extern StrandBaseDebugInfo _StrandBoth_BaseNameDebugInfo[StrandBoth_NumMethods+5];
extern StrandBaseDebugInfo _StrandMany_BaseNameDebugInfo[StrandMany_NumMethods+5];
extern char * _StrandMany_BaseEntryOperationDebugInfo[StrandMany_NumEntryOperations+3];
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUGNAME( strandName )   const char * _Strand_DebugInfo_##strandName [1] = { #strandName };
#else
#define STRAND_DEBUGNAME( strandName )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUGNAME1( strandName, auxName0 )   const char * _Strand_DebugInfo_##strandName [Strand_NumAuxMethods+1] = { #strandName, #auxName0 };
#else
#define STRAND_DEBUGNAME1( strandName, auxName0 )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUGNAME2( strandName, auxName0, auxName1 )   const char * _Strand_DebugInfo_##strandName [Strand_NumAuxMethods+1] = { #strandName, #auxName0, #auxName1 };
#else
#define STRAND_DEBUGNAME2( strandName, auxName0, auxName1 )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUGNAME3( strandName, auxName0, auxName1, auxName2 )   const char * _Strand_DebugInfo_##strandName [Strand_NumAuxMethods+1] = { #strandName, #auxName0, #auxName1, #auxName2 };
#else
#define STRAND_DEBUGNAME3( strandName, auxName0, auxName1, auxName2 )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUGNAME4( strandName, auxName0, auxName1, auxName2, auxName3 )   const char * _Strand_DebugInfo_##strandName [Strand_NumAuxMethods+1] = { #strandName, #auxName0, #auxName1, #auxName2, #auxName3 };
#else
#define STRAND_DEBUGNAME4( strandName, auxName0, auxName1, auxName2, auxName3 )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUGNAME5( strandName, auxName0, auxName1, auxName2, auxName3, auxName4 )   const char * _Strand_DebugInfo_##strandName [Strand_NumAuxMethods+1] = { #strandName, #auxName0, #auxName1, #auxName2, #auxName3, #auxName4 };
#else
#define STRAND_DEBUGNAME5( strandName, auxName0, auxName1, auxName2, auxName3, auxName4 )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUGNAME6( strandName, auxName0, auxName1, auxName2, auxName3, auxName4, auxName5 )   const char * _Strand_DebugInfo_##strandName [StrandBoth_NumAuxMethods+1] = { #strandName, #auxName0, #auxName1, #auxName2, #auxName3, #auxName4, #auxName5 };
#else
#define STRAND_DEBUGNAME6( strandName, auxName0, auxName1, auxName2, auxName3, auxName4, auxName5 )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUGNAME7( strandName, auxName0, auxName1, auxName2, auxName3, auxName4, auxName5, auxName6 )   const char * _Strand_DebugInfo_##strandName [StrandBoth_NumAuxMethods+1] = { #strandName, #auxName0, #auxName1, #auxName2, #auxName3, #auxName4, #auxName5, #auxName6 };
#else
#define STRAND_DEBUGNAME7( strandName, auxName0, auxName1, auxName2, auxName3, auxName4, auxName5, auxName6 )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUGNAME8( strandName, auxName0, auxName1, auxName2, auxName3, auxName4, auxName5, auxName6, auxName7 )   const char * _Strand_DebugInfo_##strandName [StrandBoth_NumAuxMethods+1] = { #strandName, #auxName0, #auxName1, #auxName2, #auxName3, #auxName4, #auxName5, #auxName6, #auxName7 };
#else
#define STRAND_DEBUGNAME8( strandName, auxName0, auxName1, auxName2, auxName3, auxName4, auxName5, auxName6, auxName7 )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUGNAME9( strandName, auxName0, auxName1, auxName2, auxName3, auxName4, auxName5, auxName6, auxName7, auxName8 )   const char * _Strand_DebugInfo_##strandName [StrandBoth_NumAuxMethods+1] = { #strandName, #auxName0, #auxName1, #auxName2, #auxName3, #auxName4, #auxName5, #auxName6, #auxName7, #auxName8 };
#else
#define STRAND_DEBUGNAME9( strandName, auxName0, auxName1, auxName2, auxName3, auxName4, auxName5, auxName6, auxName7, auxName8 )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUGNAME10( strandName, auxName0, auxName1, auxName2, auxName3, auxName4, auxName5, auxName6, auxName7, auxName8, auxName9 )   const char * _Strand_DebugInfo_##strandName [StrandBoth_NumAuxMethods+1] = { #strandName, #auxName0, #auxName1, #auxName2, #auxName3, #auxName4, #auxName5, #auxName6, #auxName7, #auxName8, #auxName9 };
#else
#define STRAND_DEBUGNAME10( strandName, auxName0, auxName1, auxName2, auxName3, auxName4, auxName5, auxName6, auxName7, auxName8, auxName9 )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUG_GETBASEINFO( strand )  ( STRAND_TYPE_MIDDLE == (strand)->strandType ?  _StrandBoth_BaseNameDebugInfo : ( STRAND_ISTYPE_EDGE(strand) ? _Strand_BaseNameDebugInfo : _StrandMany_BaseNameDebugInfo ) )
#define STRAND_DEBUG_GETINFOSIZE( strand )  ( STRAND_TYPE_MIDDLE == (strand)->strandType ?  StrandBoth_NumMethods : ( STRAND_ISTYPE_EDGE(strand) ? Strand_NumMethods : StrandMany_NumMethods ) )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUG_GETNAME( strand )   ( NULL != (strand)->debug ? (strand)->debug[0] : STRAND_DEBUG_GETBASEINFO(strand)[0].name )
#else
#define STRAND_DEBUG_GETNAME( strand )   ""
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define _STRAND_DEBUG_GETMETHOD( strand, bitIndex0 ) \
    ( (bitIndex0) >= Strand_NumBaseMethods && NULL != (strand)->debug && NULL != (strand)->debug[(bitIndex0)-Strand_NumBaseMethods+1] ? \
        (strand)->debug[(bitIndex0)-Strand_NumBaseMethods+1] : \
        _Strand_BaseNameDebugInfo[(bitIndex0)+2].name )
#define _STRANDBOTH_DEBUG_GETMETHOD( strand, bitIndex0 ) \
    ( (bitIndex0) >= StrandBoth_NumBaseMethods && NULL != (strand)->debug && NULL != (strand)->debug[(bitIndex0)-StrandBoth_NumBaseMethods+1] ? \
        (strand)->debug[(bitIndex0)-StrandBoth_NumBaseMethods+1] : \
        _StrandBoth_BaseNameDebugInfo[(bitIndex0)+2].name )
#define _STRANDMANY_DEBUG_GETMETHOD( strand, bitIndex0 )  \
    ( (bitIndex0) >= StrandMany_NumBaseMethods && NULL != (strand)->debug && NULL != (strand)->debug[(bitIndex0)-StrandMany_NumBaseMethods+1] ? \
        (strand)->debug[(bitIndex0)-StrandMany_NumBaseMethods+1] : \
        _StrandMany_BaseNameDebugInfo[(bitIndex0)+2].name )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUG_GETMETHODINDEX( strand, bitIndex ) \
    ( STRAND_TYPE_MIDDLE == (strand)->strandType ?  \
        _STRANDBOTH_DEBUG_GETMETHOD( strand, (bitIndex)-FirstMethodBit-1 ) : \
            ( STRAND_ISTYPE_EDGE(strand) ? \
                _STRAND_DEBUG_GETMETHOD( strand, (bitIndex)-FirstMethodBit-1 ) : \
                _STRANDMANY_DEBUG_GETMETHOD( strand, (bitIndex)-FirstMethodBit-1 ) ) )
#else
#define STRAND_DEBUG_GETMETHODINDEX( strand, bitIndex ) ""
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUG_GETMETHOD( strand, methodBit ) ( (methodBit == 0) ? "EnterStrand" : STRAND_DEBUG_GETMETHODINDEX( strand, GetFirstSetLSB(methodBit) ) )
#else
#define STRAND_DEBUG_GETMETHOD( strand, methodBit ) ""
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUG_GETOPERATIONINDEX( strand, bitIndex ) \
    ( (bitIndex) >= StrandMany_FirstBitEntryOperationAux && (bitIndex) <= StrandMany_LastBitEntryOperationAux \
    && NULL != (strand)->debug && NULL != (strand)->debug[(bitIndex)-StrandMany_FirstBitEntryOperationAux+1] ? \
        (strand)->debug[(bitIndex)-StrandMany_FirstBitEntryOperationAux+1] : _StrandMany_BaseEntryOperationDebugInfo[(bitIndex)-1] )
#else
#define STRAND_DEBUG_GETOPERATIONINDEX( strand, bitIndex ) ""
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUG_GETOPERATION( strand, operationMethodBit ) STRAND_DEBUG_GETOPERATIONINDEX( strand, GetFirstSetLSB(operationMethodBit) )
#else
#define STRAND_DEBUG_GETOPERATION( strand, operationMethodBit ) ""
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_ASSERTEXECUTING( strand )    DEBUG_ASSERT( ( ReadWithFence(&(strand)->stateScheduled) & BitExecuting ) != 0 )
#else
#define STRAND_ASSERTEXECUTING( strand )    ((void)0)
#endif

#if defined(STRAND_ENABLE_DEBUG)
void _Strand_AssertOnStrand( _In_ Strand* strand );
#define STRAND_ASSERTONSTRAND( strand )     _Strand_AssertOnStrand( strand )
#else
#define STRAND_ASSERTONSTRAND( strand )    ((void)0)
#endif

#if defined(STRAND_ENABLE_DEBUG)
extern void _StrandLogWithName( _In_ Strand* self, _In_ const char * operation );
#define STRAND_LOGWITHNAME( strand, operation ) \
    _StrandLogWithName( strand, operation )
#else
#define STRAND_LOGWITHNAME( strand, operation )    ((void)0)
#endif

/*
#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_VERIFYPROPERLYOPENED( strand ) \
DEBUG_ASSERT( (strand)->info.opened || \
    ( STRAND_ISTYPE_EDGE( strand ) && (strand)->currentMethodBit == BitAck ) || \
    ( STRAND_ISTYPE_MANY( strand ) && (strand)->currentMethodBit == BitAck_Many ) )
#else
#define STRAND_VERIFYPROPERLYOPENED( strand )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRANDBOTH_VERIFYPROPERLYOPENED_LEFT( strand ) \
DEBUG_ASSERT( (strand)->base.info.opened || (strand)->base.currentMethodBit == BitAck_Left )
#else
#define STRANDBOTH_VERIFYPROPERLYOPENED_LEFT( strand )
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRANDBOTH_VERIFYPROPERLYOPENED_RIGHT( strand ) \
DEBUG_ASSERT( (strand)->infoRight.opened || (strand)->base.currentMethodBit == BitAck_Right )
#else
#define STRANDBOTH_VERIFYPROPERLYOPENED_RIGHT( strand )
#endif
*/

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_VERIFYPROPERLYOPENED( strand ) DEBUG_ASSERT( (strand)->info.opened )
#else
#define STRAND_VERIFYPROPERLYOPENED( strand ) ((void)0)
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRANDBOTH_VERIFYPROPERLYOPENED_LEFT( strand ) DEBUG_ASSERT( (strand)->base.info.opened )
#else
#define STRANDBOTH_VERIFYPROPERLYOPENED_LEFT( strand ) ((void)0)
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRANDBOTH_VERIFYPROPERLYOPENED_RIGHT( strand ) DEBUG_ASSERT( (strand)->infoRight.opened )
#else
#define STRANDBOTH_VERIFYPROPERLYOPENED_RIGHT( strand ) ((void)0)
#endif

//------------------------------------------------------------------------------------------------------------

// initiates a Post in the other interaction (should be running on the strand)
// Can also be used on StrandMany and StrandEntry (but not with StrandBoth)
MI_INLINE
void Strand_Post(
    _In_ Strand *   strand,
    _In_ Message *  msg)
{
    DEBUG_ASSERT( STRAND_ISTYPE_EDGE( strand ) || STRAND_ISTYPE_MANY( strand ) );
    STRAND_ASSERTONSTRAND( strand );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRAND_VERIFYPROPERLYOPENED( strand );

    STRAND_LOGWITHNAME( strand, "Post" );
    _Strand_Post_Imp( &strand->info, msg );
    STRAND_LOGWITHNAME( strand, "Returning from Post" );
}

// initiates a Post in the other left interaction (should be running on the strand)
MI_INLINE
void StrandBoth_PostLeft(
    _In_ StrandBoth *   strand,
    _In_ Message *      msg)
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &strand->base ) );
    STRAND_ASSERTONSTRAND( &strand->base );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRANDBOTH_VERIFYPROPERLYOPENED_LEFT( strand );

    STRAND_LOGWITHNAME( &strand->base, "PostLeft" );
    _Strand_Post_Imp( &strand->base.info, msg );
    STRAND_LOGWITHNAME( &strand->base, "Returning from PostLeft" );
}

// initiates a Post in the other right interaction (should be running on the strand)
MI_INLINE
void StrandBoth_PostRight(
    _In_ StrandBoth *   strand,
    _In_ Message *      msg)
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &strand->base ) );
    STRAND_ASSERTONSTRAND( &strand->base );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRANDBOTH_VERIFYPROPERLYOPENED_RIGHT( strand );

    STRAND_LOGWITHNAME( &strand->base, "PostRight" );
    _Strand_Post_Imp( &strand->infoRight, msg );
    STRAND_LOGWITHNAME( &strand->base, "Returning from PostRight" );
}

// initiates a Post in the other interaction (should be running on the strand)
// In this version the ack is relayed automatically to the other side (in a pass-thru fashion)
// ( no user Ack will be called )
MI_INLINE
void Strand_PostPassthru(
    _In_ Strand *   strand,
    _In_ Message *  msg)
{
    DEBUG_ASSERT( STRAND_ISTYPE_EDGE( strand ) || STRAND_ISTYPE_MANY( strand ) );
    STRAND_ASSERTONSTRAND( strand );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRAND_VERIFYPROPERLYOPENED( strand );

    STRAND_LOGWITHNAME( strand, "PostPassthru" );
    _Strand_PostPassthru_Imp( &strand->info, msg );
    STRAND_LOGWITHNAME( strand, "Returning from PostPassthru" );
}

// initiates a Post in the other left interaction (should be running on the strand)
// In this version the ack is relayed automatically to the other side (in a pass-thru fashion)
// ( no user Ack will be called )
MI_INLINE
void StrandBoth_PostPassthruLeft(
    _In_ StrandBoth *   strand,
    _In_ Message *      msg)
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &strand->base ) );
    STRAND_ASSERTONSTRAND( &strand->base );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRANDBOTH_VERIFYPROPERLYOPENED_LEFT( strand );

    STRAND_LOGWITHNAME( &strand->base, "PostPassthruLeft" );
    _Strand_PostPassthru_Imp( &strand->base.info, msg );
    STRAND_LOGWITHNAME( &strand->base, "Returning from PostPassthruLeft" );
}

// initiates a Post in the other right interaction (should be running on the strand)
// In this version the ack is relayed automatically to the other side (in a pass-thru fashion)
// ( no user Ack will be called )
MI_INLINE
void StrandBoth_PostPassthruRight(
    _In_ StrandBoth *   strand,
    _In_ Message *      msg)
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &strand->base ) );
    STRAND_ASSERTONSTRAND( &strand->base );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRANDBOTH_VERIFYPROPERLYOPENED_RIGHT( strand );

    STRAND_LOGWITHNAME( &strand->base, "PostPassthruRight" );
    _Strand_PostPassthru_Imp( &strand->infoRight, msg );
    STRAND_LOGWITHNAME( &strand->base, "Returning from PostPassthruRight" );
}

// initiates a Post in the other interaction (should be running on the strand)
// and leaves the strand before returning
// Can also be used on StrandMany and StrandEntry (but not with StrandBoth)
MI_INLINE
void Strand_PostAndLeaveStrand(
    _In_ Strand *   strand,
    _In_ Message *  msg)
{
    DEBUG_ASSERT( STRAND_ISTYPE_EDGE( strand ) || STRAND_ISTYPE_MANY( strand ) );
    STRAND_ASSERTONSTRAND( strand );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRAND_VERIFYPROPERLYOPENED( strand );

    STRAND_LOGWITHNAME( strand, "PostAndLeaveStrand" );
    _Strand_PostAndLeaveStrand_Imp( strand, &strand->info, msg );
}

// initiates a Post in the other left interaction (should be running on the strand)
// and leaves the strand before returning
MI_INLINE
void StrandBoth_PostLeftAndLeaveStrand(
    _In_ StrandBoth *   strand,
    _In_ Message *      msg)
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &strand->base ) );
    STRAND_ASSERTONSTRAND( &strand->base );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRANDBOTH_VERIFYPROPERLYOPENED_LEFT( strand );

    STRAND_LOGWITHNAME( &strand->base, "PostLeftAndLeaveStrand" );
    _Strand_PostAndLeaveStrand_Imp( &strand->base, &strand->base.info, msg );
}

// initiates a Post in the other right interaction (should be running on the strand)
// and leaves the strand before returning
MI_INLINE
void StrandBoth_PostRightAndLeaveStrand(
    _In_ StrandBoth *   strand,
    _In_ Message *      msg)
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &strand->base ) );
    STRAND_ASSERTONSTRAND( &strand->base );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRANDBOTH_VERIFYPROPERLYOPENED_RIGHT( strand );

    STRAND_LOGWITHNAME( &strand->base, "PostRightAndLeaveStrand" );
    _Strand_PostAndLeaveStrand_Imp( &strand->base, &strand->infoRight, msg );
}

// initiates a PostControl in the other interaction (should be running on the strand)
// Can also be used on StrandMany and StrandEntry (but not with StrandBoth)
MI_INLINE
void Strand_PostControl(
    _In_ Strand *   strand,
    _In_ Message *  msg)
{
    DEBUG_ASSERT( STRAND_ISTYPE_EDGE( strand ) || STRAND_ISTYPE_MANY( strand ) );
    STRAND_ASSERTONSTRAND( strand );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRAND_VERIFYPROPERLYOPENED( strand );

    STRAND_LOGWITHNAME( strand, "PostControl" );
    _Strand_PostControl_Imp( &strand->info, msg );
    STRAND_LOGWITHNAME( strand, "Returning from PostControl" );
}

// initiates a PostControl in the other left interaction (should be running on the strand)
MI_INLINE
void StrandBoth_PostControlLeft(
    _In_ StrandBoth *   strand,
    _In_ Message *      msg)
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &strand->base ) );
    STRAND_ASSERTONSTRAND( &strand->base );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRANDBOTH_VERIFYPROPERLYOPENED_LEFT( strand );

    STRAND_LOGWITHNAME( &strand->base, "PostControlLeft" );
    _Strand_PostControl_Imp( &strand->base.info, msg );
    STRAND_LOGWITHNAME( &strand->base, "Returning from PostControlLeft" );
}

// initiates a PostControl in the other right interaction (should be running on the strand)
MI_INLINE
void StrandBoth_PostControlRight(
    _In_ StrandBoth *   strand,
    _In_ Message *      msg)
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &strand->base ) );
    STRAND_ASSERTONSTRAND( &strand->base );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRANDBOTH_VERIFYPROPERLYOPENED_RIGHT( strand );

    STRAND_LOGWITHNAME( &strand->base, "PostControlRight" );
    _Strand_PostControl_Imp( &strand->infoRight, msg );
    STRAND_LOGWITHNAME( &strand->base, "Returning from PostControlRight" );
}

// initiates an Ack in the other interaction (should be running on the strand)
// Can also be used on StrandMany and StrandEntry (but not with StrandBoth)
MI_INLINE
void Strand_Ack(
    _In_ Strand *   strand)
{
    DEBUG_ASSERT( STRAND_ISTYPE_EDGE( strand ) || STRAND_ISTYPE_MANY( strand ) );
    STRAND_ASSERTONSTRAND( strand );

    STRAND_LOGWITHNAME( strand, "Ack" );
    _Strand_Ack_Imp( &strand->info );
    STRAND_LOGWITHNAME( strand, "Returning from Ack" );
}

// initiates an Ack in the other left interaction (should be running on the strand)
MI_INLINE
void StrandBoth_AckLeft(
    _In_ StrandBoth *   strand)
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &strand->base ) );
    STRAND_ASSERTONSTRAND( &strand->base );

    STRAND_LOGWITHNAME( &strand->base, "AckLeft" );
    _Strand_Ack_Imp( &strand->base.info );
    STRAND_LOGWITHNAME( &strand->base, "Returning from AckLeft" );
}

// initiates an Ack in the other right interaction (should be running on the strand)
MI_INLINE
void StrandBoth_AckRight(
    _In_ StrandBoth *   strand)
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &strand->base ) );
    STRAND_ASSERTONSTRAND( &strand->base );

    STRAND_LOGWITHNAME( &strand->base, "AckRight" );
    _Strand_Ack_Imp( &strand->infoRight );
    STRAND_LOGWITHNAME( &strand->base, "Returning from AckRight" );
}

// initiates a cancel wherever necessary
// ( can be used with any type of strand)
void Strand_Cancel(
    _In_ Strand *   self);

// initiates a Close in the other interaction (should be running on the strand)
// Can also be used on StrandMany and StrandEntry (but not with StrandBoth)
MI_INLINE
void Strand_Close(
    _In_ Strand *   strand)
{
    DEBUG_ASSERT( STRAND_ISTYPE_EDGE( strand ) || STRAND_ISTYPE_MANY( strand ) );
    STRAND_ASSERTONSTRAND( strand );
    // During ack the opened state is not set until it returns back from user method, so the user can Post while opened is not set yet
    STRAND_VERIFYPROPERLYOPENED( strand );

    STRAND_LOGWITHNAME( strand, "Close" );
    _Strand_Close_Imp( &strand->info );
    STRAND_LOGWITHNAME( strand, "Returning from Close" );
}

// initiates a Close in the other left interaction (should be running on the strand)
MI_INLINE
void StrandBoth_CloseLeft(
    _In_ StrandBoth *   strand)
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &strand->base ) );
    STRAND_ASSERTONSTRAND( &strand->base );
    // During ack the opened state is not set until it returns back from user method, so the user can Close while opened is not set yet
    STRANDBOTH_VERIFYPROPERLYOPENED_LEFT( strand );

    STRAND_LOGWITHNAME( &strand->base, "CloseLeft" );
    _Strand_Close_Imp( &strand->base.info );
    STRAND_LOGWITHNAME( &strand->base, "Returning from CloseLeft" );
}

// initiates a Close in the other right interaction (should be running on the strand)
MI_INLINE
void StrandBoth_CloseRight(
    _In_ StrandBoth *   strand)
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &strand->base ) );
    STRAND_ASSERTONSTRAND( &strand->base );
    // During ack the opened state is not set until it returns back from user method, so the user can Close while opened is not set yet
    STRANDBOTH_VERIFYPROPERLYOPENED_RIGHT( strand );

    STRAND_LOGWITHNAME( &strand->base, "CloseRight" );
    _Strand_Close_Imp( &strand->infoRight );
    STRAND_LOGWITHNAME( &strand->base, "Returning from CloseRight" );
}

MI_INLINE
void Strand_SetDelayFinish(
    _In_ Strand* self )
{
    STRAND_ASSERTONSTRAND( self );
    self->delayFinish = MI_TRUE;
}

MI_INLINE
void Strand_ResetDelayFinish(
    _In_ Strand* self )
{
    STRAND_ASSERTONSTRAND( self );
    self->delayFinish = MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
// Internal use
MI_INLINE
void _Strand_StartOpenImp(
    _In_        InteractionInfo*    info,
                MI_Boolean          initialAckPending )
{
    DEBUG_ASSERT( !info->otherAckPending );
    DEBUG_ASSERT( !info->thisAckPending );

    info->thisClosedOther = MI_FALSE;
    info->otherClosedThis = MI_FALSE;
    info->thisAckPending = initialAckPending;
    info->otherAckPending = MI_FALSE;
    info->opened = MI_TRUE;
}

// Internal use
MI_INLINE
void _Strand_StartOpenCancelImp(
    _In_        InteractionInfo*    info )
{
    DEBUG_ASSERT( info->opened );

    info->thisAckPending = MI_FALSE;
    info->opened = MI_FALSE;
}

// Internal use
MI_INLINE
void _Strand_OpenPrepareImp(
    _In_        Strand *                self,
    _In_        InteractionInfo*        info,
    _Out_       InteractionOpenParams*  interactionParams,
    _In_opt_    void*                   callbackData,   // Optional callbackData (usually the object being called back)
    _In_opt_    Message*                msg,            // Optional initial message, if not NULL receiver should call Message_Release once interaction is opened/done with the message
                MI_Boolean              leaveStrand )   // If true it will leave the strand once opened
{
    STRAND_ASSERTONSTRAND(self);

    _Strand_StartOpenImp( info, NULL != msg );

    interactionParams->callbackData = callbackData;
    interactionParams->interaction = &info->interaction;
    interactionParams->msg = msg;
    interactionParams->origin = leaveStrand ? self : NULL;
}

// Internal use
MI_INLINE
void _Strand_OpenImp(
    _In_        Strand *            self,
    _In_        InteractionInfo*    info,
    _In_        OpenCallback        callback,
    _In_opt_    void*               callbackData,   // Optional callbackData (usually the object being called back)
    _In_opt_    Message*            msg,            // Optional initial message, if not NULL receiver should call Message_Release once interaction is opened/done with the message
                MI_Boolean          leaveStrand )   // If true it will leave the strand once opened
{
    InteractionOpenParams params;

    _Strand_OpenPrepareImp(self, info, &params, callbackData, msg, leaveStrand );

    (*callback)( &params );
}

// Used on Strand/StrandMany/StrandEntry (but not StrandBoth, see below)
MI_INLINE
void Strand_Open(
    _In_        Strand *        self,
    _In_        OpenCallback    callback,
    _In_opt_    void*           callbackData,   // Optional callbackData (usually the object being called back)
    _In_opt_    Message*        msg,            // Optional initial message, if not NULL receiver should call Message_Release once interaction is opened/done with the message
                MI_Boolean      leaveStrand )   // If true it will leave the strand once opened
{
    DEBUG_ASSERT( !self->info.ackPassthru );
    DEBUG_ASSERT( !STRAND_ISTYPE_MIDDLE( self ) );
    _Strand_OpenImp( self, &self->info, callback, callbackData, msg, leaveStrand );
}

// Make sure of call Strand_OpenCancel if the open doesnt actually occurs
// Used on Strand/StrandMany/StrandEntry (but not StrandBoth, see below)
MI_INLINE
void Strand_OpenPrepare(
    _In_        Strand *                self,
    _Out_       InteractionOpenParams*  interactionParams,
    _In_opt_    void*                   callbackData,   // Optional callbackData (usually the object being called back)
    _In_opt_    Message*                msg,            // Optional initial message, if not NULL receiver should call Message_Release once interaction is opened/done with the message
                MI_Boolean              leaveStrand )   // If true it will leave the strand once opened
{
    DEBUG_ASSERT( !self->info.ackPassthru );
    DEBUG_ASSERT( !STRAND_ISTYPE_MIDDLE( self ) );
    _Strand_OpenPrepareImp( self, &self->info, interactionParams, callbackData, msg, leaveStrand );
}

// If after call Strand_OpenPrepare the opend didnt happen
// Used on Strand/StrandMany/StrandEntry (but not StrandBoth, see below)
MI_INLINE
void Strand_OpenCancel(
    _In_        Strand *                self )
{
    STRAND_ASSERTONSTRAND(self);
    _Strand_StartOpenCancelImp( &self->info );
}

// Always open to the right
// ackPassthru indicates if the initial Ack from open is just going to be passed thru
// or delivered to the Ack user method instead (it will always be passthru if the ack
// user method is NULL)
MI_INLINE
void StrandBoth_Open(
    _In_        StrandBoth *    self,
    _In_        OpenCallback    callback,
    _In_opt_    void*           callbackData,   // Optional callbackData (usually the object being called back)
    _In_opt_    Message*        msg,            // Optional initial message, if not NULL receiver should call Message_Release once interaction is opened/done with the message
                MI_Boolean      leaveStrand,    // If true it will leave the strand once opened
                MI_Boolean      ackPassthru )
{
    DEBUG_ASSERT( !self->infoRight.ackPassthru );
    DEBUG_ASSERT( !ackPassthru || NULL != msg );    // No sense on indicating passthru if there is no message
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &self->base ) );
    self->infoRight.ackPassthru = ackPassthru;
    _Strand_OpenImp( &self->base, &self->infoRight, callback, callbackData, msg, leaveStrand );
}

// Make sure of call Strand_OpenCancel if the open doesnt actually occurs
// Always open to the right
// ackPassthru indicates if the initial Ack from open is just going to be passed thru
// or delivered to the Ack user method instead (it will always be passthru if the ack
// user method is NULL)
MI_INLINE
void StrandBoth_OpenPrepare(
    _In_        StrandBoth *            self,
    _Out_       InteractionOpenParams*  interactionParams,
    _In_opt_    void*                   callbackData,   // Optional callbackData (usually the object being called back)
    _In_opt_    Message*                msg,            // Optional initial message, if not NULL receiver should call Message_Release once interaction is opened/done with the message
                MI_Boolean              leaveStrand,    // If true it will leave the strand once opened
                MI_Boolean              ackPassthru )
{
    DEBUG_ASSERT( !self->infoRight.ackPassthru );
    DEBUG_ASSERT( !ackPassthru || NULL != msg );    // No sense on indicating passthru if there is no message
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &self->base ) );
    self->infoRight.ackPassthru = ackPassthru;
    _Strand_OpenPrepareImp( &self->base, &self->infoRight, interactionParams, callbackData, msg, leaveStrand );
}

// If after call Strand_OpenPrepare the opend didnt happen
// Used on Strand/StrandMany/StrandEntry (but not StrandBoth, see below)
MI_INLINE
void StrandBoth_OpenCancel(
    _In_        StrandBoth *            self )
{
    STRAND_ASSERTONSTRAND(&self->base);
    _Strand_StartOpenCancelImp( &self->infoRight );
}

// Used on Strand/StrandMany/StrandEntry (but not StrandBoth, see below)
MI_INLINE
void Strand_StartOpenAsync(
    _In_        Strand *        self )
{
    STRAND_ASSERTONSTRAND(self);
    DEBUG_ASSERT( !self->info.ackPassthru );
    DEBUG_ASSERT( !STRAND_ISTYPE_MIDDLE( self ) );

    _Strand_StartOpenImp( &self->info, MI_FALSE );
    // this is different in this case
    // not opened until Strand_CompleteOpenAsync
    self->info.opened = MI_FALSE;
}

// Always open to the right
MI_INLINE
void StrandBoth_StartOpenAsync(
    _In_        StrandBoth *    self )
{
    STRAND_ASSERTONSTRAND(&self->base);
    DEBUG_ASSERT( !self->infoRight.ackPassthru );
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &self->base ) );

    _Strand_StartOpenImp( &self->infoRight, MI_FALSE );
    // this is different in this case
    // not opened until StrandBoth_CompleteOpenAsync
    self->infoRight.opened = MI_FALSE;
}

// Used on Strand/StrandMany/StrandEntry AND StrandBoth (which always accepts on the left)
void Strand_AcceptOpen(
    _In_        Strand*                 self,
    _In_        InteractionOpenParams*  params );

// Used on Strand/StrandMany/StrandEntry AND StrandBoth (which always accepts on the left)
// However this should only be used if the 'otherStrand' is a Strand/StrandMany/StrandEntry
// (use Strand_AcceptOpenAsyncFromStrandBoth if it is StrandBoth)
void Strand_AcceptOpenAsync(
    _In_        Strand*                 self,
    _In_        Strand*                 otherStrand );

// Used on Strand/StrandMany/StrandEntry AND StrandBoth (which always accepts on the left)
// However this should only be used if the 'otherStrand' is a StrandBoth
void Strand_AcceptOpenAsyncFromStrandBoth(
    _In_        Strand*                 self,
    _In_        StrandBoth*             otherStrand );

// Also used on all kind of strands
void Strand_FailOpenWithMsg(
    _In_        InteractionOpenParams*  params,
    _In_opt_    Message*                msg );  // Optional failed response message (it will be canceled otherwise). Note that it is NOT released inside

// Also used on all kind of strands
MI_INLINE
void Strand_FailOpen(
    _In_        InteractionOpenParams*  params )
{
    Strand_FailOpenWithMsg( params, NULL );
}

typedef PostResultMsg* (*MakeResultMessageCallback)(
    _In_ Message* req,
    _In_opt_ const MI_Instance* err,
    _In_opt_z_ const MI_Char* errmsg,
    _In_z_ const MI_Char *errorType,
    _In_ MI_Uint32 r);

// Also used on all kind of strands
void Strand_FailOpenWithResult(
    _In_ InteractionOpenParams*  params,
    MI_Result result,
    _In_ MakeResultMessageCallback callback);

//------------------------------------------------------------------------------------------------------------
// Needed in a StrandBoth if we are opening one side but the other side is in error
// and therefore we need to force it closed
MI_INLINE
void Strand_ForceClose(
    _In_ InteractionInfo *  info )
{
    DEBUG_ASSERT( !info->otherAckPending );

    info->thisClosedOther = MI_TRUE;
    info->otherClosedThis = MI_TRUE;
    info->thisAckPending = MI_FALSE;
}

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26001) // bogus "we know the interaction points to the middle of the Strand struct"
#endif /* _PREFAST_ */

MI_INLINE
Strand*
Strand_FromInteraction(
    _In_ Interaction* interaction )
{
    return FromOffset(Strand,info,interaction);
}

MI_INLINE
StrandBoth*
Strand_FromInteractionRight(
    _In_ Interaction* interaction )
{
    return FromOffset(StrandBoth,infoRight,interaction);
}

// For use on StrandMany user methods
MI_INLINE
StrandMany* StrandMany_FromStrand( _In_ Strand * strand )
{
    return FromOffset(StrandMany,strand,strand);
}

// For use on StrandMany user methods
MI_INLINE
StrandEntry* StrandEntry_FromStrand( _In_ Strand * strand )
{
    return FromOffset(StrandEntry,strand,strand);
}

// For use on HashMapHashProc and HashMapEqualProc
MI_INLINE
StrandEntry* StrandEntry_FromBucket( _In_ HashBucket * bucket )
{
    return FromOffset(StrandEntry,bucket,bucket);
}
MI_INLINE
const StrandEntry* StrandEntry_FromBucketConst( _In_ const HashBucket * bucket )
{
    return FromOffsetConst(StrandEntry,bucket,bucket);
}

//------------------------------------------------------------------------------------------------------------
// note that an internal "iter" variable is used, so this can only be used inside the strand
MI_INLINE
void StrandMany_BeginIteration( _In_ StrandMany* self )
{
    STRAND_ASSERTONSTRAND( &self->strand );
    HashMap_BeginIteration( &self->many, &self->iter);
}

MI_INLINE
StrandEntry * StrandMany_Iterate( _In_ StrandMany* self )
{
    HashBucket* bucket;

    STRAND_ASSERTONSTRAND( &self->strand );

    bucket = (HashBucket*)HashMap_Iterate(&self->many, &self->iter);

    if( NULL == bucket )
        return NULL;
    else
        return StrandEntry_FromBucket( bucket );
}

#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

//------------------------------------------------------------------------------------------------------------

MI_INLINE
void _Strand_SchedulePostCommon( _In_ InteractionInfo* info, _In_ Message * msg )
{
    DEBUG_ASSERT( NULL == info->otherMsg );
    Message_AddRef( msg );  // since the actual message use can be delayed
    info->otherMsg = msg;
}

// Dont use with a StrandBoth (use StrandBoth_SchedulePostLeft or StrandBoth_SchedulePostRight instead)
// (neither with a StrandMany/StrandEntry, see below instead)
MI_INLINE
void Strand_SchedulePost( _In_ Strand* self, _In_ Message * msg )
{
    DEBUG_ASSERT( STRAND_ISTYPE_EDGE( self ) );
    _Strand_SchedulePostCommon( &self->info,  msg );
    _Strand_Schedule( self, BitPostOther );
}

MI_INLINE
void StrandBoth_SchedulePostLeft( _In_ StrandBoth* self, _In_ Message * msg )
{
    DEBUG_ASSERT( STRAND_TYPE_MIDDLE == self->base.strandType );
    _Strand_SchedulePostCommon( &self->base.info,  msg );
    _Strand_Schedule( &self->base, BitPostOther_Left );
}

MI_INLINE
void StrandBoth_SchedulePostRight( _In_ StrandBoth* self, _In_ Message * msg )
{
    DEBUG_ASSERT( STRAND_TYPE_MIDDLE == self->base.strandType );
    _Strand_SchedulePostCommon( &self->infoRight,  msg );
    _Strand_Schedule( &self->base, BitPostOther_Right );
}

MI_INLINE
void StrandMany_SchedulePost( _In_ StrandMany* self, _In_ Message * msg  )
{
    DEBUG_ASSERT( STRAND_ISTYPE_PARENT(&self->strand) );
    _Strand_SchedulePostCommon( &self->strand.info,  msg );
    _Strand_Schedule( &self->strand, BitPostOther_Many );
}

MI_INLINE
void StrandEntry_SchedulePost( _In_ StrandEntry* self, _In_ Message * msg  )
{
    DEBUG_ASSERT( STRAND_ISTYPE_ENTRY(&self->strand) );
    _Strand_SchedulePostCommon( &self->strand.info,  msg );
    _Strand_Schedule( &self->strand, BitPostOther_Many );
}

// Dont use with a StrandBoth (use StrandBoth_ScheduleAckLeft or StrandBoth_ScheduleAckRight instead)
// (neither with a StrandMany/StrandEntry, see below instead)
MI_INLINE
void Strand_ScheduleAck( _In_ Strand* self )
{
    DEBUG_ASSERT( STRAND_ISTYPE_EDGE( self ) );
    _Strand_Schedule( self, BitAckOther );
}

MI_INLINE
void StrandBoth_ScheduleAckLeft( _In_ StrandBoth* self )
{
    DEBUG_ASSERT( STRAND_TYPE_MIDDLE == self->base.strandType );
    _Strand_Schedule( &self->base, BitAckOther_Left );
}

MI_INLINE
void StrandBoth_ScheduleAckRight( _In_ StrandBoth* self )
{
    DEBUG_ASSERT( STRAND_TYPE_MIDDLE == self->base.strandType );
    _Strand_Schedule( &self->base, BitAckOther_Right );
}

MI_INLINE
void StrandMany_ScheduleAck( _In_ StrandMany* self )
{
    DEBUG_ASSERT( STRAND_ISTYPE_PARENT(&self->strand) );
    _Strand_Schedule( &self->strand, BitAckOther_Many );
}

MI_INLINE
void StrandEntry_ScheduleAck( _In_ StrandEntry* self )
{
    DEBUG_ASSERT( STRAND_ISTYPE_ENTRY(&self->strand) );
    _Strand_Schedule( &self->strand, BitAckOther_Many );
}

// Dont use with a StrandBoth (use StrandBoth_ScheduleCloseLeft or StrandBoth_ScheduleCloseRight instead)
// (neither with a StrandMany/StrandEntry, see below instead)
MI_INLINE
void Strand_ScheduleClose( _In_ Strand* self )
{
    DEBUG_ASSERT( STRAND_ISTYPE_EDGE( self ) );
    _Strand_Schedule( self, BitCloseOther );
}

MI_INLINE
void StrandBoth_ScheduleCloseLeft( _In_ StrandBoth* self )
{
    DEBUG_ASSERT( STRAND_TYPE_MIDDLE == self->base.strandType );
    _Strand_Schedule( &self->base, BitCloseOther_Left );
}

MI_INLINE
void StrandBoth_ScheduleCloseRight( _In_ StrandBoth* self )
{
    DEBUG_ASSERT( STRAND_TYPE_MIDDLE == self->base.strandType );
    _Strand_Schedule( &self->base, BitCloseOther_Right );
}

MI_INLINE
void StrandMany_ScheduleClose( _In_ StrandMany* self )
{
    DEBUG_ASSERT( STRAND_ISTYPE_PARENT(&self->strand) );
    _Strand_Schedule( &self->strand, BitCloseOther_Many );
}

MI_INLINE
void StrandEntry_ScheduleClose( _In_ StrandEntry* self )
{
    DEBUG_ASSERT( STRAND_ISTYPE_ENTRY(&self->strand) );
    _Strand_Schedule( &self->strand, BitCloseOther_Many );
}

// Dont use with a StrandBoth (use StrandBoth_ScheduleCancel instead)
// (neither with a StrandMany/StrandEntry, see below instead)
MI_INLINE
void Strand_ScheduleCancel( _In_ Strand* self )
{
    DEBUG_ASSERT( STRAND_ISTYPE_EDGE( self ) );
    _Strand_Schedule( self, BitCancelSelf );
}

MI_INLINE
void StrandBoth_ScheduleCancel( _In_ StrandBoth* self )
{
    DEBUG_ASSERT( STRAND_TYPE_MIDDLE == self->base.strandType );
    _Strand_Schedule( &self->base, BitCancelSelf_Both );
}

MI_INLINE
void StrandMany_ScheduleCancel( _In_ StrandMany* self )
{
    DEBUG_ASSERT( STRAND_ISTYPE_PARENT(&self->strand) );
    _Strand_Schedule( &self->strand, BitCancelSelf_Many );
}

MI_INLINE
void StrandEntry_ScheduleCancel( _In_ StrandEntry* self )
{
    DEBUG_ASSERT( STRAND_ISTYPE_ENTRY(&self->strand) );
    _Strand_Schedule( &self->strand, BitCancelSelf_Many );
}

//------------------------------------------------------------------------------------------------------------

// Dont use with a StrandBoth/StrandMany/StrandEntry (use StrandBoth_ScheduleAuxLeft, StrandBoth_ScheduleAuxRight, StrandMany_ScheduleAux or StrandEntry_ScheduleAux instead)
MI_INLINE
void Strand_ScheduleAux( _In_ Strand* self, unsigned int auxMethodNumber )
{
    DEBUG_ASSERT( STRAND_ISTYPE_EDGE( self ) );
    _Strand_Schedule( self, BitAux0 << auxMethodNumber );
}

MI_INLINE
void StrandBoth_ScheduleAuxLeft( _In_ StrandBoth* self, unsigned int auxMethodNumber )
{
    DEBUG_ASSERT( STRAND_TYPE_MIDDLE == self->base.strandType );
    _Strand_Schedule( &self->base, BitAux0_Left << auxMethodNumber );
}

MI_INLINE
void StrandBoth_ScheduleAuxRight( _In_ StrandBoth* self, unsigned int auxMethodNumber )
{
    DEBUG_ASSERT( STRAND_TYPE_MIDDLE == self->base.strandType );
    _Strand_Schedule( &self->base, BitAux0_Right << auxMethodNumber );
}

MI_INLINE
void StrandMany_ScheduleAux( _In_ StrandMany* self, unsigned int auxMethodNumber )
{
    DEBUG_ASSERT( STRAND_ISTYPE_PARENT( &self->strand ) );
    _Strand_Schedule( &self->strand, BitAux0_Many << auxMethodNumber );
}

MI_INLINE
void StrandEntry_ScheduleAux( _In_ StrandEntry* self, unsigned int auxMethodNumber )
{
    DEBUG_ASSERT( STRAND_TYPE_ENTRY == self->strand.strandType );
    _Strand_Schedule( &self->strand, BitAux0_Many << auxMethodNumber );
}

//------------------------------------------------------------------------------------------------------------

// Call these ONLY from Parent strand
MI_INLINE
void StrandMany_CancelEntry( _In_ StrandEntry* entry )
{
    STRAND_ASSERTONSTRAND( &entry->parent->strand );
    _Strand_Schedule( &entry->strand, BitCancelInternal );
}
MI_INLINE
void StrandMany_CloseEntry( _In_ StrandEntry* entry )
{
    STRAND_ASSERTONSTRAND( &entry->parent->strand );
    _Strand_Schedule( &entry->strand, BitCloseInternal );
}
MI_INLINE
void StrandMany_AckEntry( _In_ StrandEntry* entry )
{
    STRAND_ASSERTONSTRAND( &entry->parent->strand );
    _Strand_Schedule( &entry->strand, BitAckInternal );
}
void StrandMany_CancelAllEntries( _In_ StrandMany* self );
void StrandMany_CloseAllEntries( _In_ StrandMany* self );
void StrandMany_PostEntry( _In_ StrandEntry* entry, _In_ Message* msg );
void StrandMany_PostAll( _In_ StrandMany* self, _In_ Message* msg );
MI_Boolean StrandMany_PostFindEntry( _In_ StrandMany* self, _In_ Message* msg );
void StrandMany_PostControlEntry( _In_ StrandEntry* entry, _In_ Message* msg );
void StrandMany_PostControlAll( _In_ StrandMany* self, _In_ Message* msg );
MI_Boolean StrandMany_PostControlFindEntry( _In_ StrandMany* self, _In_ Message* msg );

// internal use only
void _StrandEntry_ScheduleParent( _In_ StrandEntry* self, EntryOperationMaskType entryOperationBit );

// Call these ONLY from a Entry strand
MI_INLINE
void StrandEntry_CancelParent( _In_ StrandEntry* self )
{
    STRAND_ASSERTONSTRAND( &self->strand );
    _StrandEntry_ScheduleParent( self, BitEntryCancel );
}
MI_INLINE
void StrandEntry_CloseParent( _In_ StrandEntry* self )
{
    STRAND_ASSERTONSTRAND( &self->strand );
    _StrandEntry_ScheduleParent( self, BitEntryClose );
}

void StrandEntry_PostParent( _In_ StrandEntry* self, _In_ Message* msg );

// Use this if the msg comes from the interaction
// Takes care of delivering Ack on the interaction once Parent has actually
// being able to Post (manages flow control internally)
void StrandEntry_PostParentPassthru( _In_ StrandEntry* self, _In_ Message* msg );

void StrandEntry_PostControlParent( _In_ StrandEntry* self, _In_ Message* msg );

MI_INLINE
void StrandEntry_ScheduleAuxParent( _In_ StrandEntry* self, unsigned int auxMethodNumber  )
{
    STRAND_ASSERTONSTRAND( &self->strand );
    DEBUG_ASSERT( (BitEntryAux0 << auxMethodNumber) < BitEntryDeleted );
    _StrandEntry_ScheduleParent( self, BitEntryAux0 << auxMethodNumber );
}


//------------------------------------------------------------------------------------------------------------
// Timer methods and types
//
// Note: These were moved from a separate header file to resolve the circular
//       dependency caused by Strand using Timer and Timer functions taking a
//       Strand as an argument.

typedef enum _TimerResult
{
    TimerResult_Success         = 0,
    TimerResult_Failed          = 1,
    TimerResult_InvalidArgument = 2
}
TimerResult;

/*
 * Specifies a single use timer that will timeout after a specified amount
 * of time.  The timer may be triggered early through manual intervention.
 */
struct _Timer
{
    /* The timeout value to use, specified in microseconds. */
    MI_Uint64 timeoutInUsec;

    /* Specifies the reason of calling the timeout callback: expired, manually fired, etc. */
    TimerReason reason;

    /* Internal OS-Specific data */
#if defined(CONFIG_POSIX)
    Handler handler;
    Selector* selector;
#endif
    /* End OS-Specific data */
};

/*
 * Doesn't start the actual timer or extend an already scheduled Timer.
 * It just sets the Timer's specified timeout period.  This should be set
 * prior to the first call to Timer_Start.
 *
 * Updates to its value will take effect the next time Timer_Start is called.
 */
MI_INLINE
void Timer_SetTime(
    _In_ Timer* timer,
    _In_ MI_Uint64 timeUsec )
{
    DEBUG_ASSERT( timer );
    timer->timeoutInUsec = timeUsec;
}

/*
 * Starts an initialized Timer with a previously specified timeout value.
 * Also used to restart a timer after completion.
 */
TimerResult Timer_Start(
    _In_ Timer* timer,
    _In_ Strand* strand );

/*
 * Manually force early execution of a Timer.
 */
void Timer_Fire(
    _In_ Timer* timer,
    _In_ Strand* strand,
         TimerReason reason );

/*
 * Cleans up a Timer from a previous run, but leaves it ready for re-use via
 * Timer_Start().
 *
 * Note: This is designed to be used by a Strand and not to be used via
 *       independent calls.
 */
void Timer_Close(
    _In_ Timer* timer );

/*
 * Sets a global internal selector to avoid requiring it to be passed in via
 * Timer_Init().
 */
void Timer_SetSelector(
    _In_ Selector* selector );

/*
 * Timer manipulation functions for Strands
 */
void Strand_StartTimer( _In_ Strand* self, _In_ Timer* timer, _In_ MI_Uint64 timeusecs );
void Strand_FireTimer( _In_ Strand* self );
MI_Boolean Strand_HaveTimer( _In_ Strand* self );

// Internal Use
MI_INLINE
MI_Boolean _Strand_ShouldFinish(
    _In_ Strand* self )
{
    MI_Boolean shouldFinish = (*self->strandMethods[0])(self);

    if( shouldFinish && NULL != self->timer )
    {
        if( (self->flags & STRAND_FLAG_FINISHWAITSFORTIMER ) == 0 )
        {
            // Canceled reason overwrites any other reason
            Timer_Fire( self->timer, self, TimerReason_Canceled );
        }
        shouldFinish = MI_FALSE;   // In any case we cannot finish until timer is not set anymore
    }

    return shouldFinish;
}

// Internal Use
// This is not needed if everything is called inside the strand (for UT use)
// If close/ack are called outside the strand then call this afterwards
// ( can be used with any type of strand )
MI_INLINE
void _Strand_CheckDelete(
    _In_ Strand* self )
{
    STRAND_ASSERTONSTRAND( self );
    if( (*self->strandMethods[0])(self) )
    {
        _Strand_Finish( self );
    }
}

/*
**==============================================================================
*/

END_EXTERNC

#endif /* _Strand_h */


