/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _base_packing_h
#define _base_packing_h

#include "instance.h"

BEGIN_EXTERNC

/*
**==============================================================================
**
** Instance_Pack()
**
**     Serializes an instance into a buffer.
**
** Parameters:
**     self - the instance to be serialized.
**     keysOnly - pack only KEY properties.
**     buf - the buffer to put instance into.
**
** Returns:
**     MI_RESULT_OK on success.
**
**==============================================================================
*/
MI_Result Instance_Pack(
    const MI_Instance* self,
    MI_Boolean keysOnly,
    MI_Boolean (*filterProperty)(const ZChar* name, void* data),
    void* filterPropertyData,
    Buf* buf);

/*
**==============================================================================
**
** Instance_Unpack()
**
**     Unpacks an instance from a buffer.
**
** Parameters:
**     self - shall point to a newly allocated instance.
**     buf - buffer form which instance will be unpacked.
**     batch - if non-null, use this batch to allocate all elements.
**     copy - if false, use pointers into batch (otherwise make copy).
**
** Returns:
**     MI_RESULT_OK on success.
**
**==============================================================================
*/
MI_Result Instance_Unpack(
    MI_Instance** self,
    Buf* buf,
    Batch* batch,
    MI_Boolean copy);

/*
**==============================================================================
**
** InstanceToBatch()
**
**     Serializes an instance into a batch.
**
** Parameters:
**     instance - the instance to be serialized.
**     batch - the batch to put instance into.
**     ptrOut - pointer to the packed instance in the batch
**     sizeOut - size of the packed instance
**
** Returns:
**     MI_RESULT_OK on success.
**
**==============================================================================
*/
MI_Result InstanceToBatch(
    const MI_Instance* instance,
    MI_Boolean (*filterProperty)(const ZChar* name, void* data),
    void* filterPropertyData,
    Batch* batch,
    void** ptrOut,
    MI_Uint32* sizeOut);

END_EXTERNC

#endif /* _base_packing_h */
