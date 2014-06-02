/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _StressTestClass5_h
#define _StressTestClass5_h

#include <MI.h>
#include "StressTestClass4.h"
#include "StressTestClass0.h"
#include "StressTestClass1.h"
#include "StressTestClass2.h"
#include "StressTestClass3.h"

/*
**==============================================================================
**
** StressTestClass5 [StressTestClass5]
**
** Keys:
**    someKey0
**
**==============================================================================
*/

typedef struct _StressTestClass5 /* extends StressTestClass4 */
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
}
StressTestClass5;

typedef struct _StressTestClass5_Ref
{
    StressTestClass5* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass5_Ref;

typedef struct _StressTestClass5_ConstRef
{
    MI_CONST StressTestClass5* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass5_ConstRef;

typedef struct _StressTestClass5_Array
{
    struct _StressTestClass5** data;
    MI_Uint32 size;
}
StressTestClass5_Array;

typedef struct _StressTestClass5_ConstArray
{
    struct _StressTestClass5 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
StressTestClass5_ConstArray;

typedef struct _StressTestClass5_ArrayRef
{
    StressTestClass5_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass5_ArrayRef;

typedef struct _StressTestClass5_ConstArrayRef
{
    StressTestClass5_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass5_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl StressTestClass5_rtti;

MI_INLINE MI_Result MI_CALL StressTestClass5_Construct(
    _Out_ StressTestClass5* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &StressTestClass5_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Clone(
    _In_ const StressTestClass5* self,
    _Outptr_ StressTestClass5** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL StressTestClass5_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &StressTestClass5_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Destruct(_Inout_ StressTestClass5* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Delete(_Inout_ StressTestClass5* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Post(
    _In_ const StressTestClass5* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Set_someKey0(
    _Inout_ StressTestClass5* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->someKey0)->value = x;
    ((MI_Uint32Field*)&self->someKey0)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Clear_someKey0(
    _Inout_ StressTestClass5* self)
{
    memset((void*)&self->someKey0, 0, sizeof(self->someKey0));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Set_embeddedInstance0(
    _Inout_ StressTestClass5* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_SetPtr_embeddedInstance0(
    _Inout_ StressTestClass5* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Clear_embeddedInstance0(
    _Inout_ StressTestClass5* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Set_embeddedInstance1(
    _Inout_ StressTestClass5* self,
    _In_ const StressTestClass1* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_SetPtr_embeddedInstance1(
    _Inout_ StressTestClass5* self,
    _In_ const StressTestClass1* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Clear_embeddedInstance1(
    _Inout_ StressTestClass5* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Set_embeddedInstance2(
    _Inout_ StressTestClass5* self,
    _In_ const StressTestClass2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_SetPtr_embeddedInstance2(
    _Inout_ StressTestClass5* self,
    _In_ const StressTestClass2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Clear_embeddedInstance2(
    _Inout_ StressTestClass5* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Set_embeddedInstance3(
    _Inout_ StressTestClass5* self,
    _In_ const StressTestClass3* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_SetPtr_embeddedInstance3(
    _Inout_ StressTestClass5* self,
    _In_ const StressTestClass3* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Clear_embeddedInstance3(
    _Inout_ StressTestClass5* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Set_embeddedInstance4(
    _Inout_ StressTestClass5* self,
    _In_ const StressTestClass4* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_SetPtr_embeddedInstance4(
    _Inout_ StressTestClass5* self,
    _In_ const StressTestClass4* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass5_Clear_embeddedInstance4(
    _Inout_ StressTestClass5* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

/*
**==============================================================================
**
** StressTestClass5 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _StressTestClass5_Self StressTestClass5_Self;

MI_EXTERN_C void MI_CALL StressTestClass5_Load(
    _Outptr_result_maybenull_ StressTestClass5_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass5_Unload(
    _In_opt_ StressTestClass5_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass5_EnumerateInstances(
    _In_opt_ StressTestClass5_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL StressTestClass5_GetInstance(
    _In_opt_ StressTestClass5_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass5* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass5_CreateInstance(
    _In_opt_ StressTestClass5_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass5* newInstance);

MI_EXTERN_C void MI_CALL StressTestClass5_ModifyInstance(
    _In_opt_ StressTestClass5_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass5* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass5_DeleteInstance(
    _In_opt_ StressTestClass5_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass5* instanceName);


#endif /* _StressTestClass5_h */
