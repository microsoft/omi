/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _SubClass_h
#define _SubClass_h

#include <MI.h>
#include "SuperClass.h"

/*
**==============================================================================
**
** SubClass [SubClass]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _SubClass /* extends SuperClass */
{
    MI_Instance __instance;
    /* SuperClass properties */
    /*KEY*/ MI_ConstStringField Key;
    /* SubClass properties */
    MI_ConstUint32Field Count;
    MI_ConstStringField Color;
}
SubClass;

typedef struct _SubClass_Ref
{
    SubClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
SubClass_Ref;

typedef struct _SubClass_ConstRef
{
    MI_CONST SubClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
SubClass_ConstRef;

typedef struct _SubClass_Array
{
    struct _SubClass** data;
    MI_Uint32 size;
}
SubClass_Array;

typedef struct _SubClass_ConstArray
{
    struct _SubClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
SubClass_ConstArray;

typedef struct _SubClass_ArrayRef
{
    SubClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
SubClass_ArrayRef;

typedef struct _SubClass_ConstArrayRef
{
    SubClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
SubClass_ConstArrayRef;


#endif /* _SubClass_h */
