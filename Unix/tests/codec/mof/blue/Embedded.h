/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Embedded_h
#define _Embedded_h

#include <MI.h>

/*
**==============================================================================
**
** Embedded [Embedded]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Embedded
{
    MI_Instance __instance;
    /* Embedded properties */
    /*KEY*/ MI_ConstUint32Field Key;
}
Embedded;

typedef struct _Embedded_Ref
{
    Embedded* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Embedded_Ref;

typedef struct _Embedded_ConstRef
{
    MI_CONST Embedded* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Embedded_ConstRef;

typedef struct _Embedded_Array
{
    struct _Embedded** data;
    MI_Uint32 size;
}
Embedded_Array;

typedef struct _Embedded_ConstArray
{
    struct _Embedded MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Embedded_ConstArray;

typedef struct _Embedded_ArrayRef
{
    Embedded_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Embedded_ArrayRef;

typedef struct _Embedded_ConstArrayRef
{
    Embedded_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Embedded_ConstArrayRef;


#endif /* _Embedded_h */
