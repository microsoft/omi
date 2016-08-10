/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_ownedmemory_h
#define _pal_ownedmemory_h

#include <pal/palcommon.h>

PAL_BEGIN_EXTERNC

/*
* Usage of these APIs is specifically in those places where the allocation happens on ad-hoc calls
* And there is no single place where someone can deallocate all memory allocated so far possibly because 
* the memory allocation was done as part of shared library and there is no single exit point since atexit
* does not run upon its unload on unix systems
* the memory locations which were allocated will be kept till the end of program or till you call OwnedMemory_Free
* the memory will be in address space of PAL shared library on unix systems and non non-unix ones it will be part of anyone
* who links against PAL static library
*/
void *OwnedMemory_Alloc(size_t length);

int OwnedMemory_Free(void *ptr);

PAL_END_EXTERNC

#endif /* _pal_ownedmemory_h */
