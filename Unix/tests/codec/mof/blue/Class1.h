/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Class1_h
#define _Class1_h

#include <MI.h>

/*
**==============================================================================
**
** Class1 [Class1]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Class1
{
    MI_Instance __instance;
    /* Class1 properties */
    /*KEY*/ MI_ConstUint32Field Key;
    MI_ConstStringField Msg;
    MI_ConstBooleanField Flag;
    MI_ConstUint8AField Numbers;
    MI_ConstStringField AlwaysNullProperty;
    MI_ConstStringAField Colors;
    MI_ConstStringField Unprintable;
    MI_ConstChar16Field Char;
}
Class1;

typedef struct _Class1_Ref
{
    Class1* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Class1_Ref;

typedef struct _Class1_ConstRef
{
    MI_CONST Class1* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Class1_ConstRef;

typedef struct _Class1_Array
{
    struct _Class1** data;
    MI_Uint32 size;
}
Class1_Array;

typedef struct _Class1_ConstArray
{
    struct _Class1 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Class1_ConstArray;

typedef struct _Class1_ArrayRef
{
    Class1_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Class1_ArrayRef;

typedef struct _Class1_ConstArrayRef
{
    Class1_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Class1_ConstArrayRef;


#endif /* _Class1_h */
