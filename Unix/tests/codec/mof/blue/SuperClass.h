/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _SuperClass_h
#define _SuperClass_h

#include <MI.h>

/*
**==============================================================================
**
** SuperClass [SuperClass]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _SuperClass
{
    MI_Instance __instance;
    /* SuperClass properties */
    /*KEY*/ MI_ConstStringField Key;
}
SuperClass;

typedef struct _SuperClass_Ref
{
    SuperClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
SuperClass_Ref;

typedef struct _SuperClass_ConstRef
{
    MI_CONST SuperClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
SuperClass_ConstRef;

typedef struct _SuperClass_Array
{
    struct _SuperClass** data;
    MI_Uint32 size;
}
SuperClass_Array;

typedef struct _SuperClass_ConstArray
{
    struct _SuperClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
SuperClass_ConstArray;

typedef struct _SuperClass_ArrayRef
{
    SuperClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
SuperClass_ArrayRef;

typedef struct _SuperClass_ConstArrayRef
{
    SuperClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
SuperClass_ConstArrayRef;


#endif /* _SuperClass_h */
