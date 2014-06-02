/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _StressTestClass3_h
#define _StressTestClass3_h

#include <MI.h>
#include "StressTestClass2.h"
#include "StressTestClass0.h"
#include "StressTestClass1.h"

/*
**==============================================================================
**
** StressTestClass3 [StressTestClass3]
**
** Keys:
**    someKey0
**
**==============================================================================
*/

typedef struct _StressTestClass3 /* extends StressTestClass2 */
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
}
StressTestClass3;

typedef struct _StressTestClass3_Ref
{
    StressTestClass3* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass3_Ref;

typedef struct _StressTestClass3_ConstRef
{
    MI_CONST StressTestClass3* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass3_ConstRef;

typedef struct _StressTestClass3_Array
{
    struct _StressTestClass3** data;
    MI_Uint32 size;
}
StressTestClass3_Array;

typedef struct _StressTestClass3_ConstArray
{
    struct _StressTestClass3 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
StressTestClass3_ConstArray;

typedef struct _StressTestClass3_ArrayRef
{
    StressTestClass3_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass3_ArrayRef;

typedef struct _StressTestClass3_ConstArrayRef
{
    StressTestClass3_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass3_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl StressTestClass3_rtti;

MI_INLINE MI_Result MI_CALL StressTestClass3_Construct(
    _Out_ StressTestClass3* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &StressTestClass3_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass3_Clone(
    _In_ const StressTestClass3* self,
    _Outptr_ StressTestClass3** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL StressTestClass3_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &StressTestClass3_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL StressTestClass3_Destruct(_Inout_ StressTestClass3* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass3_Delete(_Inout_ StressTestClass3* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass3_Post(
    _In_ const StressTestClass3* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass3_Set_someKey0(
    _Inout_ StressTestClass3* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->someKey0)->value = x;
    ((MI_Uint32Field*)&self->someKey0)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass3_Clear_someKey0(
    _Inout_ StressTestClass3* self)
{
    memset((void*)&self->someKey0, 0, sizeof(self->someKey0));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass3_Set_embeddedInstance0(
    _Inout_ StressTestClass3* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass3_SetPtr_embeddedInstance0(
    _Inout_ StressTestClass3* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass3_Clear_embeddedInstance0(
    _Inout_ StressTestClass3* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL StressTestClass3_Set_embeddedInstance1(
    _Inout_ StressTestClass3* self,
    _In_ const StressTestClass1* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass3_SetPtr_embeddedInstance1(
    _Inout_ StressTestClass3* self,
    _In_ const StressTestClass1* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass3_Clear_embeddedInstance1(
    _Inout_ StressTestClass3* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL StressTestClass3_Set_embeddedInstance2(
    _Inout_ StressTestClass3* self,
    _In_ const StressTestClass2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass3_SetPtr_embeddedInstance2(
    _Inout_ StressTestClass3* self,
    _In_ const StressTestClass2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass3_Clear_embeddedInstance2(
    _Inout_ StressTestClass3* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** StressTestClass3 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _StressTestClass3_Self StressTestClass3_Self;

MI_EXTERN_C void MI_CALL StressTestClass3_Load(
    _Outptr_result_maybenull_ StressTestClass3_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass3_Unload(
    _In_opt_ StressTestClass3_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass3_EnumerateInstances(
    _In_opt_ StressTestClass3_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL StressTestClass3_GetInstance(
    _In_opt_ StressTestClass3_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass3* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass3_CreateInstance(
    _In_opt_ StressTestClass3_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass3* newInstance);

MI_EXTERN_C void MI_CALL StressTestClass3_ModifyInstance(
    _In_opt_ StressTestClass3_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass3* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass3_DeleteInstance(
    _In_opt_ StressTestClass3_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass3* instanceName);


#endif /* _StressTestClass3_h */
