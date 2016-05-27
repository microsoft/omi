/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Container_h
#define _Container_h

#include <MI.h>
#include "Widget.h"
#include "Gadget.h"

/*
**==============================================================================
**
** Container [Container]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Container
{
    MI_Instance __instance;
    /* Container properties */
    /*KEY*/ MI_ConstUint32Field Key;
    Widget_ConstRef Wid;
    Gadget_ConstRef Gad;
}
Container;

typedef struct _Container_Ref
{
    Container* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Container_Ref;

typedef struct _Container_ConstRef
{
    MI_CONST Container* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Container_ConstRef;

typedef struct _Container_Array
{
    struct _Container** data;
    MI_Uint32 size;
}
Container_Array;

typedef struct _Container_ConstArray
{
    struct _Container MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Container_ConstArray;

typedef struct _Container_ArrayRef
{
    Container_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Container_ArrayRef;

typedef struct _Container_ConstArrayRef
{
    Container_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Container_ConstArrayRef;

/*
**==============================================================================
**
** Container.Foo1()
**
**==============================================================================
*/

typedef struct _Container_Foo1
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
Container_Foo1;

/*
**==============================================================================
**
** Container.Foo2()
**
**==============================================================================
*/

typedef struct _Container_Foo2
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ Widget_ConstRef Wid;
    /*OUT*/ Gadget_ConstRef Gad;
}
Container_Foo2;


#endif /* _Container_h */
