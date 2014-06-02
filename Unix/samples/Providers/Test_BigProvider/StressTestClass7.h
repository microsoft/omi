/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _StressTestClass7_h
#define _StressTestClass7_h

#include <MI.h>
#include "StressTestClass6.h"
#include "StressTestClass0.h"
#include "StressTestClass1.h"
#include "StressTestClass2.h"
#include "StressTestClass3.h"
#include "StressTestClass4.h"
#include "StressTestClass5.h"

/*
**==============================================================================
**
** StressTestClass7 [StressTestClass7]
**
** Keys:
**    someKey0
**
**==============================================================================
*/

typedef struct _StressTestClass7 /* extends StressTestClass6 */
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
}
StressTestClass7;

typedef struct _StressTestClass7_Ref
{
    StressTestClass7* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass7_Ref;

typedef struct _StressTestClass7_ConstRef
{
    MI_CONST StressTestClass7* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass7_ConstRef;

typedef struct _StressTestClass7_Array
{
    struct _StressTestClass7** data;
    MI_Uint32 size;
}
StressTestClass7_Array;

typedef struct _StressTestClass7_ConstArray
{
    struct _StressTestClass7 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
StressTestClass7_ConstArray;

typedef struct _StressTestClass7_ArrayRef
{
    StressTestClass7_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass7_ArrayRef;

typedef struct _StressTestClass7_ConstArrayRef
{
    StressTestClass7_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass7_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl StressTestClass7_rtti;

MI_INLINE MI_Result MI_CALL StressTestClass7_Construct(
    _Out_ StressTestClass7* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &StressTestClass7_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Clone(
    _In_ const StressTestClass7* self,
    _Outptr_ StressTestClass7** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL StressTestClass7_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &StressTestClass7_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Destruct(_Inout_ StressTestClass7* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Delete(_Inout_ StressTestClass7* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Post(
    _In_ const StressTestClass7* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Set_someKey0(
    _Inout_ StressTestClass7* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->someKey0)->value = x;
    ((MI_Uint32Field*)&self->someKey0)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Clear_someKey0(
    _Inout_ StressTestClass7* self)
{
    memset((void*)&self->someKey0, 0, sizeof(self->someKey0));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Set_embeddedInstance0(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_SetPtr_embeddedInstance0(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Clear_embeddedInstance0(
    _Inout_ StressTestClass7* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Set_embeddedInstance1(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass1* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_SetPtr_embeddedInstance1(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass1* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Clear_embeddedInstance1(
    _Inout_ StressTestClass7* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Set_embeddedInstance2(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_SetPtr_embeddedInstance2(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Clear_embeddedInstance2(
    _Inout_ StressTestClass7* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Set_embeddedInstance3(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass3* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_SetPtr_embeddedInstance3(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass3* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Clear_embeddedInstance3(
    _Inout_ StressTestClass7* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Set_embeddedInstance4(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass4* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_SetPtr_embeddedInstance4(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass4* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Clear_embeddedInstance4(
    _Inout_ StressTestClass7* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Set_embeddedInstance5(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass5* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_SetPtr_embeddedInstance5(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass5* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Clear_embeddedInstance5(
    _Inout_ StressTestClass7* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Set_embeddedInstance6(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass6* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_SetPtr_embeddedInstance6(
    _Inout_ StressTestClass7* self,
    _In_ const StressTestClass6* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass7_Clear_embeddedInstance6(
    _Inout_ StressTestClass7* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

/*
**==============================================================================
**
** StressTestClass7 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _StressTestClass7_Self StressTestClass7_Self;

MI_EXTERN_C void MI_CALL StressTestClass7_Load(
    _Outptr_result_maybenull_ StressTestClass7_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass7_Unload(
    _In_opt_ StressTestClass7_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass7_EnumerateInstances(
    _In_opt_ StressTestClass7_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL StressTestClass7_GetInstance(
    _In_opt_ StressTestClass7_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass7* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass7_CreateInstance(
    _In_opt_ StressTestClass7_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass7* newInstance);

MI_EXTERN_C void MI_CALL StressTestClass7_ModifyInstance(
    _In_opt_ StressTestClass7_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass7* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass7_DeleteInstance(
    _In_opt_ StressTestClass7_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass7* instanceName);


#endif /* _StressTestClass7_h */
