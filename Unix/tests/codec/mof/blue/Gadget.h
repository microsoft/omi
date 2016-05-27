/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Gadget_h
#define _Gadget_h

#include <MI.h>
#include "Embedded.h"

/*
**==============================================================================
**
** Gadget [Gadget]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Gadget
{
    MI_Instance __instance;
    /* Gadget properties */
    /*KEY*/ MI_ConstUint32Field Key;
    Embedded_ConstArrayRef Emb;
}
Gadget;

typedef struct _Gadget_Ref
{
    Gadget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Gadget_Ref;

typedef struct _Gadget_ConstRef
{
    MI_CONST Gadget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Gadget_ConstRef;

typedef struct _Gadget_Array
{
    struct _Gadget** data;
    MI_Uint32 size;
}
Gadget_Array;

typedef struct _Gadget_ConstArray
{
    struct _Gadget MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Gadget_ConstArray;

typedef struct _Gadget_ArrayRef
{
    Gadget_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Gadget_ArrayRef;

typedef struct _Gadget_ConstArrayRef
{
    Gadget_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Gadget_ConstArrayRef;


#endif /* _Gadget_h */
