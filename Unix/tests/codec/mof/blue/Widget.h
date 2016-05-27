/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Widget_h
#define _Widget_h

#include <MI.h>
#include "Embedded.h"

/*
**==============================================================================
**
** Widget [Widget]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Widget
{
    MI_Instance __instance;
    /* Widget properties */
    /*KEY*/ MI_ConstUint32Field Key;
    Embedded_ConstRef Emb;
}
Widget;

typedef struct _Widget_Ref
{
    Widget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Widget_Ref;

typedef struct _Widget_ConstRef
{
    MI_CONST Widget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Widget_ConstRef;

typedef struct _Widget_Array
{
    struct _Widget** data;
    MI_Uint32 size;
}
Widget_Array;

typedef struct _Widget_ConstArray
{
    struct _Widget MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Widget_ConstArray;

typedef struct _Widget_ArrayRef
{
    Widget_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Widget_ArrayRef;

typedef struct _Widget_ConstArrayRef
{
    Widget_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Widget_ConstArrayRef;


#endif /* _Widget_h */
