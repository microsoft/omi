/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Assoc1_h
#define _Assoc1_h

#include <MI.h>
#include "Assoc0.h"
#include "Widget.h"
#include "Gadget.h"

/*
**==============================================================================
**
** Assoc1 [Assoc1]
**
** Keys:
**    Left
**    Right
**
**==============================================================================
*/

typedef struct _Assoc1 /* extends Assoc0 */
{
    MI_Instance __instance;
    /* Assoc0 properties */
    /*KEY*/ Widget_ConstRef Left;
    /*KEY*/ Gadget_ConstRef Right;
    MI_ConstUint32Field Inherited;
    /* Assoc1 properties */
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
Assoc1;

typedef struct _Assoc1_Ref
{
    Assoc1* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Assoc1_Ref;

typedef struct _Assoc1_ConstRef
{
    MI_CONST Assoc1* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Assoc1_ConstRef;

typedef struct _Assoc1_Array
{
    struct _Assoc1** data;
    MI_Uint32 size;
}
Assoc1_Array;

typedef struct _Assoc1_ConstArray
{
    struct _Assoc1 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Assoc1_ConstArray;

typedef struct _Assoc1_ArrayRef
{
    Assoc1_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Assoc1_ArrayRef;

typedef struct _Assoc1_ConstArrayRef
{
    Assoc1_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Assoc1_ConstArrayRef;

/*
**==============================================================================
**
** Assoc1.Foo()
**
**==============================================================================
*/

typedef struct _Assoc1_Foo
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstReal32Field X;
    /*IN*/ MI_ConstReal32Field Y;
    /*OUT*/ MI_ConstReal32Field Z;
}
Assoc1_Foo;

/*
**==============================================================================
**
** Assoc1.Foo2()
**
**==============================================================================
*/

typedef struct _Assoc1_Foo2
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
    /*IN*/ Widget_ConstRef WidIn;
    /*IN*/ Gadget_ConstRef GadIn;
    /*IN*/ MI_ConstBooleanField BIn;
    /*IN*/ MI_ConstUint8Field U8In;
    /*IN*/ MI_ConstSint8Field S8In;
    /*IN*/ MI_ConstUint16Field U16In;
    /*IN*/ MI_ConstSint16Field S16In;
    /*IN*/ MI_ConstUint32Field U32In;
    /*IN*/ MI_ConstSint32Field S32In;
    /*IN*/ MI_ConstUint64Field U64In;
    /*IN*/ MI_ConstSint64Field S64In;
    /*IN*/ MI_ConstReal32Field R32In;
    /*IN*/ MI_ConstReal64Field R64In;
    /*IN*/ MI_ConstDatetimeField DT1In;
    /*IN*/ MI_ConstDatetimeField DT2In;
    /*IN*/ MI_ConstStringField SIn;
    /*IN*/ MI_ConstChar16Field C16In;
    /*IN*/ MI_ConstBooleanAField BAIn;
    /*IN*/ MI_ConstUint8AField U8AIn;
    /*IN*/ MI_ConstSint8AField S8AIn;
    /*IN*/ MI_ConstUint16AField U16AIn;
    /*IN*/ MI_ConstSint16AField S16AIn;
    /*IN*/ MI_ConstUint32AField U32AIn;
    /*IN*/ MI_ConstSint32AField S32AIn;
    /*IN*/ MI_ConstUint64AField U64AIn;
    /*IN*/ MI_ConstSint64AField S64AIn;
    /*IN*/ MI_ConstReal32AField R32AIn;
    /*IN*/ MI_ConstReal64AField R64AIn;
    /*IN*/ MI_ConstDatetimeAField DTAIn;
    /*IN*/ MI_ConstStringAField SAIn;
    /*IN*/ MI_ConstChar16AField C16AIn;
    /*OUT*/ Widget_ConstRef WidOut;
    /*OUT*/ Gadget_ConstRef GadOut;
    /*OUT*/ MI_ConstBooleanField BOut;
    /*OUT*/ MI_ConstUint8Field U8Out;
    /*OUT*/ MI_ConstSint8Field S8Out;
    /*OUT*/ MI_ConstUint16Field U16Out;
    /*OUT*/ MI_ConstSint16Field S16Out;
    /*OUT*/ MI_ConstUint32Field U32Out;
    /*OUT*/ MI_ConstSint32Field S32Out;
    /*OUT*/ MI_ConstUint64Field U64Out;
    /*OUT*/ MI_ConstSint64Field S64Out;
    /*OUT*/ MI_ConstReal32Field R32Out;
    /*OUT*/ MI_ConstReal64Field R64Out;
    /*OUT*/ MI_ConstDatetimeField DT1Out;
    /*OUT*/ MI_ConstDatetimeField DT2Out;
    /*OUT*/ MI_ConstStringField SOut;
    /*OUT*/ MI_ConstChar16Field C16Out;
    /*OUT*/ MI_ConstBooleanAField BAOut;
    /*OUT*/ MI_ConstUint8AField U8AOut;
    /*OUT*/ MI_ConstSint8AField S8AOut;
    /*OUT*/ MI_ConstUint16AField U16AOut;
    /*OUT*/ MI_ConstSint16AField S16AOut;
    /*OUT*/ MI_ConstUint32AField U32AOut;
    /*OUT*/ MI_ConstSint32AField S32AOut;
    /*OUT*/ MI_ConstUint64AField U64AOut;
    /*OUT*/ MI_ConstSint64AField S64AOut;
    /*OUT*/ MI_ConstReal32AField R32AOut;
    /*OUT*/ MI_ConstReal64AField R64AOut;
    /*OUT*/ MI_ConstDatetimeAField DTAOut;
    /*OUT*/ MI_ConstStringAField SAOut;
    /*OUT*/ MI_ConstChar16AField C16AOut;
    /*IN-OUT*/ Widget_ConstRef WidInOut;
    /*IN-OUT*/ Gadget_ConstRef GadInOut;
    /*IN-OUT*/ MI_ConstBooleanField BInOut;
    /*IN-OUT*/ MI_ConstUint8Field U8InOut;
    /*IN-OUT*/ MI_ConstSint8Field S8InOut;
    /*IN-OUT*/ MI_ConstUint16Field U16InOut;
    /*IN-OUT*/ MI_ConstSint16Field S16InOut;
    /*IN-OUT*/ MI_ConstUint32Field U32InOut;
    /*IN-OUT*/ MI_ConstSint32Field S32InOut;
    /*IN-OUT*/ MI_ConstUint64Field U64InOut;
    /*IN-OUT*/ MI_ConstSint64Field S64InOut;
    /*IN-OUT*/ MI_ConstReal32Field R32InOut;
    /*IN-OUT*/ MI_ConstReal64Field R64InOut;
    /*IN-OUT*/ MI_ConstDatetimeField DT1InOut;
    /*IN-OUT*/ MI_ConstDatetimeField DT2InOut;
    /*IN-OUT*/ MI_ConstStringField SInOut;
    /*IN-OUT*/ MI_ConstChar16Field C16InOut;
    /*IN-OUT*/ MI_ConstBooleanAField BAInOut;
    /*IN-OUT*/ MI_ConstUint8AField U8AInOut;
    /*IN-OUT*/ MI_ConstSint8AField S8AInOut;
    /*IN-OUT*/ MI_ConstUint16AField U16AInOut;
    /*IN-OUT*/ MI_ConstSint16AField S16AInOut;
    /*IN-OUT*/ MI_ConstUint32AField U32AInOut;
    /*IN-OUT*/ MI_ConstSint32AField S32AInOut;
    /*IN-OUT*/ MI_ConstUint64AField U64AInOut;
    /*IN-OUT*/ MI_ConstSint64AField S64AInOut;
    /*IN-OUT*/ MI_ConstReal32AField R32AInOut;
    /*IN-OUT*/ MI_ConstReal64AField R64AInOut;
    /*IN-OUT*/ MI_ConstDatetimeAField DTAInOut;
    /*IN-OUT*/ MI_ConstStringAField SAInOut;
    /*IN-OUT*/ MI_ConstChar16AField C16AInOut;
}
Assoc1_Foo2;


#endif /* _Assoc1_h */
