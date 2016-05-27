/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Thing_h
#define _Thing_h

#include <MI.h>

/*
**==============================================================================
**
** Thing [Thing]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Thing
{
    MI_Instance __instance;
    /* Thing properties */
    /*KEY*/ MI_ConstUint32Field Key;
    MI_ConstReferenceField Obj;
}
Thing;

typedef struct _Thing_Ref
{
    Thing* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Thing_Ref;

typedef struct _Thing_ConstRef
{
    MI_CONST Thing* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Thing_ConstRef;

typedef struct _Thing_Array
{
    struct _Thing** data;
    MI_Uint32 size;
}
Thing_Array;

typedef struct _Thing_ConstArray
{
    struct _Thing MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Thing_ConstArray;

typedef struct _Thing_ArrayRef
{
    Thing_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Thing_ArrayRef;

typedef struct _Thing_ConstArrayRef
{
    Thing_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Thing_ConstArrayRef;


#endif /* _Thing_h */
