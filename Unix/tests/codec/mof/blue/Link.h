/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Link_h
#define _Link_h

#include <MI.h>
#include "Widget.h"
#include "Gadget.h"

/*
**==============================================================================
**
** Link [Link]
**
** Keys:
**    Left
**    Right
**
**==============================================================================
*/

typedef struct _Link
{
    MI_Instance __instance;
    /* Link properties */
    /*KEY*/ Widget_ConstRef Left;
    /*KEY*/ Gadget_ConstRef Right;
}
Link;

typedef struct _Link_Ref
{
    Link* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Link_Ref;

typedef struct _Link_ConstRef
{
    MI_CONST Link* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Link_ConstRef;

typedef struct _Link_Array
{
    struct _Link** data;
    MI_Uint32 size;
}
Link_Array;

typedef struct _Link_ConstArray
{
    struct _Link MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Link_ConstArray;

typedef struct _Link_ArrayRef
{
    Link_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Link_ArrayRef;

typedef struct _Link_ConstArrayRef
{
    Link_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Link_ConstArrayRef;


#endif /* _Link_h */
