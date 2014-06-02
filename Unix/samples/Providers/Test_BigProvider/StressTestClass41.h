/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _StressTestClass41_h
#define _StressTestClass41_h

#include <MI.h>
#include "StressTestClass40.h"
#include "StressTestClass0.h"
#include "StressTestClass1.h"
#include "StressTestClass2.h"
#include "StressTestClass3.h"
#include "StressTestClass4.h"
#include "StressTestClass5.h"
#include "StressTestClass6.h"
#include "StressTestClass7.h"
#include "StressTestClass8.h"
#include "StressTestClass9.h"
#include "StressTestClass10.h"
#include "StressTestClass11.h"
#include "StressTestClass12.h"
#include "StressTestClass13.h"
#include "StressTestClass14.h"
#include "StressTestClass15.h"
#include "StressTestClass16.h"
#include "StressTestClass17.h"
#include "StressTestClass18.h"
#include "StressTestClass19.h"
#include "StressTestClass20.h"
#include "StressTestClass21.h"
#include "StressTestClass22.h"
#include "StressTestClass23.h"
#include "StressTestClass24.h"
#include "StressTestClass25.h"
#include "StressTestClass26.h"
#include "StressTestClass27.h"
#include "StressTestClass28.h"
#include "StressTestClass29.h"
#include "StressTestClass30.h"
#include "StressTestClass31.h"
#include "StressTestClass32.h"
#include "StressTestClass33.h"
#include "StressTestClass34.h"
#include "StressTestClass35.h"
#include "StressTestClass36.h"
#include "StressTestClass37.h"
#include "StressTestClass38.h"
#include "StressTestClass39.h"

/*
**==============================================================================
**
** StressTestClass41 [StressTestClass41]
**
** Keys:
**    someKey0
**
**==============================================================================
*/

typedef struct _StressTestClass41 /* extends StressTestClass40 */
{
    MI_Instance __instance;
    /* StressTestClass0 properties */
    /*KEY*/ MI_ConstUint32Field someKey0;
    /* StressTestClass1 properties */
    StressTestClass0_ConstRef embeddedInstance0;
    /* StressTestClass2 properties */
    StressTestClass1_ConstRef embeddedInstance1;
    /* StressTestClass3 properties */
    StressTestClass2_ConstRef embeddedInstance2;
    /* StressTestClass4 properties */
    StressTestClass3_ConstRef embeddedInstance3;
    /* StressTestClass5 properties */
    StressTestClass4_ConstRef embeddedInstance4;
    /* StressTestClass6 properties */
    StressTestClass5_ConstRef embeddedInstance5;
    /* StressTestClass7 properties */
    StressTestClass6_ConstRef embeddedInstance6;
    /* StressTestClass8 properties */
    StressTestClass7_ConstRef embeddedInstance7;
    /* StressTestClass9 properties */
    StressTestClass8_ConstRef embeddedInstance8;
    /* StressTestClass10 properties */
    StressTestClass9_ConstRef embeddedInstance9;
    /* StressTestClass11 properties */
    StressTestClass10_ConstRef embeddedInstance10;
    /* StressTestClass12 properties */
    StressTestClass11_ConstRef embeddedInstance11;
    /* StressTestClass13 properties */
    StressTestClass12_ConstRef embeddedInstance12;
    /* StressTestClass14 properties */
    StressTestClass13_ConstRef embeddedInstance13;
    /* StressTestClass15 properties */
    StressTestClass14_ConstRef embeddedInstance14;
    /* StressTestClass16 properties */
    StressTestClass15_ConstRef embeddedInstance15;
    /* StressTestClass17 properties */
    StressTestClass16_ConstRef embeddedInstance16;
    /* StressTestClass18 properties */
    StressTestClass17_ConstRef embeddedInstance17;
    /* StressTestClass19 properties */
    StressTestClass18_ConstRef embeddedInstance18;
    /* StressTestClass20 properties */
    StressTestClass19_ConstRef embeddedInstance19;
    /* StressTestClass21 properties */
    StressTestClass20_ConstRef embeddedInstance20;
    /* StressTestClass22 properties */
    StressTestClass21_ConstRef embeddedInstance21;
    /* StressTestClass23 properties */
    StressTestClass22_ConstRef embeddedInstance22;
    /* StressTestClass24 properties */
    StressTestClass23_ConstRef embeddedInstance23;
    /* StressTestClass25 properties */
    StressTestClass24_ConstRef embeddedInstance24;
    /* StressTestClass26 properties */
    StressTestClass25_ConstRef embeddedInstance25;
    /* StressTestClass27 properties */
    StressTestClass26_ConstRef embeddedInstance26;
    /* StressTestClass28 properties */
    StressTestClass27_ConstRef embeddedInstance27;
    /* StressTestClass29 properties */
    StressTestClass28_ConstRef embeddedInstance28;
    /* StressTestClass30 properties */
    StressTestClass29_ConstRef embeddedInstance29;
    /* StressTestClass31 properties */
    StressTestClass30_ConstRef embeddedInstance30;
    /* StressTestClass32 properties */
    StressTestClass31_ConstRef embeddedInstance31;
    /* StressTestClass33 properties */
    StressTestClass32_ConstRef embeddedInstance32;
    /* StressTestClass34 properties */
    StressTestClass33_ConstRef embeddedInstance33;
    /* StressTestClass35 properties */
    StressTestClass34_ConstRef embeddedInstance34;
    /* StressTestClass36 properties */
    StressTestClass35_ConstRef embeddedInstance35;
    /* StressTestClass37 properties */
    StressTestClass36_ConstRef embeddedInstance36;
    /* StressTestClass38 properties */
    StressTestClass37_ConstRef embeddedInstance37;
    /* StressTestClass39 properties */
    StressTestClass38_ConstRef embeddedInstance38;
    /* StressTestClass40 properties */
    StressTestClass39_ConstRef embeddedInstance39;
    /* StressTestClass41 properties */
    StressTestClass40_ConstRef embeddedInstance40;
}
StressTestClass41;

typedef struct _StressTestClass41_Ref
{
    StressTestClass41* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass41_Ref;

typedef struct _StressTestClass41_ConstRef
{
    MI_CONST StressTestClass41* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass41_ConstRef;

typedef struct _StressTestClass41_Array
{
    struct _StressTestClass41** data;
    MI_Uint32 size;
}
StressTestClass41_Array;

typedef struct _StressTestClass41_ConstArray
{
    struct _StressTestClass41 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
StressTestClass41_ConstArray;

typedef struct _StressTestClass41_ArrayRef
{
    StressTestClass41_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass41_ArrayRef;

typedef struct _StressTestClass41_ConstArrayRef
{
    StressTestClass41_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass41_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl StressTestClass41_rtti;

MI_INLINE MI_Result MI_CALL StressTestClass41_Construct(
    _Out_ StressTestClass41* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &StressTestClass41_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clone(
    _In_ const StressTestClass41* self,
    _Outptr_ StressTestClass41** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL StressTestClass41_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &StressTestClass41_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Destruct(_Inout_ StressTestClass41* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Delete(_Inout_ StressTestClass41* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Post(
    _In_ const StressTestClass41* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_someKey0(
    _Inout_ StressTestClass41* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->someKey0)->value = x;
    ((MI_Uint32Field*)&self->someKey0)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_someKey0(
    _Inout_ StressTestClass41* self)
{
    memset((void*)&self->someKey0, 0, sizeof(self->someKey0));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance0(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance0(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance0(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance1(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass1* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance1(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass1* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance1(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance2(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance2(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance2(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance3(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass3* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance3(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass3* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance3(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance4(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass4* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance4(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass4* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance4(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance5(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass5* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance5(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass5* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance5(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance6(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass6* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance6(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass6* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance6(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance7(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass7* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance7(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass7* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance7(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance8(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass8* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance8(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass8* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance8(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance9(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass9* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance9(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass9* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance9(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance10(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass10* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance10(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass10* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance10(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance11(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass11* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance11(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass11* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance11(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance12(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass12* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance12(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass12* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance12(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance13(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass13* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance13(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass13* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance13(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance14(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass14* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance14(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass14* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance14(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance15(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass15* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance15(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass15* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance15(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance16(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass16* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance16(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass16* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance16(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance17(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass17* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance17(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass17* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance17(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance18(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass18* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance18(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass18* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance18(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance19(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass19* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance19(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass19* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance19(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance20(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass20* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance20(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass20* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance20(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance21(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass21* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance21(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass21* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance21(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance22(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass22* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance22(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass22* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance22(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance23(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass23* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance23(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass23* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance23(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance24(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass24* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance24(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass24* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance24(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance25(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass25* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance25(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass25* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance25(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance26(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass26* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance26(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass26* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance26(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance27(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass27* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance27(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass27* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance27(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        28);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance28(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass28* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance28(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass28* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance28(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        29);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance29(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass29* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance29(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass29* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance29(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance30(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass30* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        31,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance30(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass30* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        31,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance30(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        31);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance31(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass31* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance31(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass31* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance31(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance32(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass32* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        33,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance32(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass32* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        33,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance32(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        33);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance33(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass33* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        34,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance33(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass33* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        34,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance33(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        34);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance34(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass34* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        35,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance34(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass34* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        35,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance34(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        35);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance35(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass35* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        36,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance35(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass35* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        36,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance35(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        36);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance36(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass36* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        37,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance36(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass36* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        37,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance36(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        37);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance37(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass37* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        38,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance37(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass37* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        38,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance37(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        38);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance38(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass38* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        39,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance38(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass38* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        39,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance38(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        39);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance39(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass39* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        40,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance39(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass39* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        40,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance39(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        40);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Set_embeddedInstance40(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass40* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        41,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_SetPtr_embeddedInstance40(
    _Inout_ StressTestClass41* self,
    _In_ const StressTestClass40* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        41,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass41_Clear_embeddedInstance40(
    _Inout_ StressTestClass41* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        41);
}

/*
**==============================================================================
**
** StressTestClass41 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _StressTestClass41_Self StressTestClass41_Self;

MI_EXTERN_C void MI_CALL StressTestClass41_Load(
    _Outptr_result_maybenull_ StressTestClass41_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass41_Unload(
    _In_opt_ StressTestClass41_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass41_EnumerateInstances(
    _In_opt_ StressTestClass41_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL StressTestClass41_GetInstance(
    _In_opt_ StressTestClass41_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass41* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass41_CreateInstance(
    _In_opt_ StressTestClass41_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass41* newInstance);

MI_EXTERN_C void MI_CALL StressTestClass41_ModifyInstance(
    _In_opt_ StressTestClass41_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass41* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass41_DeleteInstance(
    _In_opt_ StressTestClass41_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass41* instanceName);


#endif /* _StressTestClass41_h */
