/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _StressTestClass20_h
#define _StressTestClass20_h

#include <MI.h>
#include "StressTestClass19.h"
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

/*
**==============================================================================
**
** StressTestClass20 [StressTestClass20]
**
** Keys:
**    someKey0
**
**==============================================================================
*/

typedef struct _StressTestClass20 /* extends StressTestClass19 */
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
}
StressTestClass20;

typedef struct _StressTestClass20_Ref
{
    StressTestClass20* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass20_Ref;

typedef struct _StressTestClass20_ConstRef
{
    MI_CONST StressTestClass20* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass20_ConstRef;

typedef struct _StressTestClass20_Array
{
    struct _StressTestClass20** data;
    MI_Uint32 size;
}
StressTestClass20_Array;

typedef struct _StressTestClass20_ConstArray
{
    struct _StressTestClass20 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
StressTestClass20_ConstArray;

typedef struct _StressTestClass20_ArrayRef
{
    StressTestClass20_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass20_ArrayRef;

typedef struct _StressTestClass20_ConstArrayRef
{
    StressTestClass20_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass20_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl StressTestClass20_rtti;

MI_INLINE MI_Result MI_CALL StressTestClass20_Construct(
    _Out_ StressTestClass20* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &StressTestClass20_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clone(
    _In_ const StressTestClass20* self,
    _Outptr_ StressTestClass20** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL StressTestClass20_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &StressTestClass20_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Destruct(_Inout_ StressTestClass20* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Delete(_Inout_ StressTestClass20* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Post(
    _In_ const StressTestClass20* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_someKey0(
    _Inout_ StressTestClass20* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->someKey0)->value = x;
    ((MI_Uint32Field*)&self->someKey0)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_someKey0(
    _Inout_ StressTestClass20* self)
{
    memset((void*)&self->someKey0, 0, sizeof(self->someKey0));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance0(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance0(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance0(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance1(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass1* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance1(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass1* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance1(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance2(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance2(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance2(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance3(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass3* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance3(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass3* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance3(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance4(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass4* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance4(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass4* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance4(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance5(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass5* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance5(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass5* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance5(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance6(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass6* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance6(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass6* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance6(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance7(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass7* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance7(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass7* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance7(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance8(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass8* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance8(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass8* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance8(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance9(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass9* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance9(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass9* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance9(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance10(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass10* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance10(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass10* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance10(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance11(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass11* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance11(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass11* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance11(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance12(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass12* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance12(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass12* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance12(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance13(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass13* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance13(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass13* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance13(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance14(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass14* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance14(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass14* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance14(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance15(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass15* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance15(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass15* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance15(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance16(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass16* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance16(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass16* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance16(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance17(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass17* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance17(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass17* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance17(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance18(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass18* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance18(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass18* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance18(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Set_embeddedInstance19(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass19* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_SetPtr_embeddedInstance19(
    _Inout_ StressTestClass20* self,
    _In_ const StressTestClass19* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass20_Clear_embeddedInstance19(
    _Inout_ StressTestClass20* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

/*
**==============================================================================
**
** StressTestClass20 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _StressTestClass20_Self StressTestClass20_Self;

MI_EXTERN_C void MI_CALL StressTestClass20_Load(
    _Outptr_result_maybenull_ StressTestClass20_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass20_Unload(
    _In_opt_ StressTestClass20_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass20_EnumerateInstances(
    _In_opt_ StressTestClass20_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL StressTestClass20_GetInstance(
    _In_opt_ StressTestClass20_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass20* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass20_CreateInstance(
    _In_opt_ StressTestClass20_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass20* newInstance);

MI_EXTERN_C void MI_CALL StressTestClass20_ModifyInstance(
    _In_opt_ StressTestClass20_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass20* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass20_DeleteInstance(
    _In_opt_ StressTestClass20_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass20* instanceName);


#endif /* _StressTestClass20_h */
