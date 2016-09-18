/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Assoc0_h
#define _Assoc0_h

#include <MI.h>
#include "Widget.h"
#include "Gadget.h"

/*
**==============================================================================
**
** Assoc0 [Assoc0]
**
** Keys:
**    Left
**    Right
**
**==============================================================================
*/

typedef struct _Assoc0
{
    MI_Instance __instance;
    /* Assoc0 properties */
    /*KEY*/ Widget_ConstRef Left;
    /*KEY*/ Gadget_ConstRef Right;
    MI_ConstUint32Field Inherited;
}
Assoc0;

typedef struct _Assoc0_Ref
{
    Assoc0* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Assoc0_Ref;

typedef struct _Assoc0_ConstRef
{
    MI_CONST Assoc0* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Assoc0_ConstRef;

typedef struct _Assoc0_Array
{
    struct _Assoc0** data;
    MI_Uint32 size;
}
Assoc0_Array;

typedef struct _Assoc0_ConstArray
{
    struct _Assoc0 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Assoc0_ConstArray;

typedef struct _Assoc0_ArrayRef
{
    Assoc0_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Assoc0_ArrayRef;

typedef struct _Assoc0_ConstArrayRef
{
    Assoc0_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Assoc0_ConstArrayRef;


#endif /* _Assoc0_h */
