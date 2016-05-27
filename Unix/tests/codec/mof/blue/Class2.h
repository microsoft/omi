/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Class2_h
#define _Class2_h

#include <MI.h>

/*
**==============================================================================
**
** Class2 [Class2]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Class2
{
    MI_Instance __instance;
    /* Class2 properties */
    /*KEY*/ MI_ConstUint32Field Key;
    MI_ConstBooleanField B;
    MI_ConstUint8Field U8;
    MI_ConstSint8Field S8;
    MI_ConstUint16Field U16;
    MI_ConstSint16Field S16;
    MI_ConstUint32Field U32;
    MI_ConstSint32Field S32;
    MI_ConstUint64Field U64;
    MI_ConstSint64Field S64;
    MI_ConstReal32Field R32;
    MI_ConstReal64Field R64;
    MI_ConstDatetimeField DT1;
    MI_ConstDatetimeField DT2;
    MI_ConstStringField S;
    MI_ConstChar16Field C16;
    MI_ConstBooleanAField BA;
    MI_ConstUint8AField U8A;
    MI_ConstSint8AField S8A;
    MI_ConstUint16AField U16A;
    MI_ConstSint16AField S16A;
    MI_ConstUint32AField U32A;
    MI_ConstSint32AField S32A;
    MI_ConstUint64AField U64A;
    MI_ConstSint64AField S64A;
    MI_ConstReal32AField R32A;
    MI_ConstReal64AField R64A;
    MI_ConstDatetimeAField DTA;
    MI_ConstStringAField SA;
    MI_ConstChar16AField C16A;
}
Class2;

typedef struct _Class2_Ref
{
    Class2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Class2_Ref;

typedef struct _Class2_ConstRef
{
    MI_CONST Class2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Class2_ConstRef;

typedef struct _Class2_Array
{
    struct _Class2** data;
    MI_Uint32 size;
}
Class2_Array;

typedef struct _Class2_ConstArray
{
    struct _Class2 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Class2_ConstArray;

typedef struct _Class2_ArrayRef
{
    Class2_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Class2_ArrayRef;

typedef struct _Class2_ConstArrayRef
{
    Class2_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Class2_ConstArrayRef;


#endif /* _Class2_h */
