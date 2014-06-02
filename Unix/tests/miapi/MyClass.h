/* @statikgen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyClass_h
#define _MyClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyClass [MyClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyClass
{
    MI_Instance __instance;
    /* MyClass properties */
    MI_ConstUint32Field Property;
}
MyClass;

typedef struct _MyClass_Ref
{
    MyClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyClass_Ref;

typedef struct _MyClass_ConstRef
{
    MI_CONST MyClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyClass_ConstRef;

typedef struct _MyClass_Array
{
    struct _MyClass** data;
    MI_Uint32 size;
}
MyClass_Array;

typedef struct _MyClass_ConstArray
{
    struct _MyClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyClass_ConstArray;

typedef struct _MyClass_ArrayRef
{
    MyClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyClass_ArrayRef;

typedef struct _MyClass_ConstArrayRef
{
    MyClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyClass_ConstArrayRef;


#endif /* _MyClass_h */
