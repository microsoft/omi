/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _StressTestClass2_h
#define _StressTestClass2_h

#include <MI.h>
#include "StressTestClass1.h"
#include "StressTestClass0.h"

/*
**==============================================================================
**
** StressTestClass2 [StressTestClass2]
**
** Keys:
**    someKey0
**
**==============================================================================
*/

typedef struct _StressTestClass2 /* extends StressTestClass1 */
{
    MI_Instance __instance;
    /* StressTestClass0 properties */
    /*KEY*/ MI_ConstUint32Field someKey0;
    /* StressTestClass1 properties */
    StressTestClass0_ConstRef embeddedInstance0;
    /* StressTestClass2 properties */
    StressTestClass1_ConstRef embeddedInstance1;
}
StressTestClass2;

typedef struct _StressTestClass2_Ref
{
    StressTestClass2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass2_Ref;

typedef struct _StressTestClass2_ConstRef
{
    MI_CONST StressTestClass2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass2_ConstRef;

typedef struct _StressTestClass2_Array
{
    struct _StressTestClass2** data;
    MI_Uint32 size;
}
StressTestClass2_Array;

typedef struct _StressTestClass2_ConstArray
{
    struct _StressTestClass2 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
StressTestClass2_ConstArray;

typedef struct _StressTestClass2_ArrayRef
{
    StressTestClass2_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass2_ArrayRef;

typedef struct _StressTestClass2_ConstArrayRef
{
    StressTestClass2_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass2_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl StressTestClass2_rtti;

MI_INLINE MI_Result MI_CALL StressTestClass2_Construct(
    _Out_ StressTestClass2* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &StressTestClass2_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass2_Clone(
    _In_ const StressTestClass2* self,
    _Outptr_ StressTestClass2** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL StressTestClass2_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &StressTestClass2_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL StressTestClass2_Destruct(_Inout_ StressTestClass2* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass2_Delete(_Inout_ StressTestClass2* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass2_Post(
    _In_ const StressTestClass2* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass2_Set_someKey0(
    _Inout_ StressTestClass2* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->someKey0)->value = x;
    ((MI_Uint32Field*)&self->someKey0)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass2_Clear_someKey0(
    _Inout_ StressTestClass2* self)
{
    memset((void*)&self->someKey0, 0, sizeof(self->someKey0));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass2_Set_embeddedInstance0(
    _Inout_ StressTestClass2* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass2_SetPtr_embeddedInstance0(
    _Inout_ StressTestClass2* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass2_Clear_embeddedInstance0(
    _Inout_ StressTestClass2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL StressTestClass2_Set_embeddedInstance1(
    _Inout_ StressTestClass2* self,
    _In_ const StressTestClass1* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass2_SetPtr_embeddedInstance1(
    _Inout_ StressTestClass2* self,
    _In_ const StressTestClass1* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass2_Clear_embeddedInstance1(
    _Inout_ StressTestClass2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** StressTestClass2 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _StressTestClass2_Self StressTestClass2_Self;

MI_EXTERN_C void MI_CALL StressTestClass2_Load(
    _Outptr_result_maybenull_ StressTestClass2_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass2_Unload(
    _In_opt_ StressTestClass2_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass2_EnumerateInstances(
    _In_opt_ StressTestClass2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL StressTestClass2_GetInstance(
    _In_opt_ StressTestClass2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass2* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass2_CreateInstance(
    _In_opt_ StressTestClass2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass2* newInstance);

MI_EXTERN_C void MI_CALL StressTestClass2_ModifyInstance(
    _In_opt_ StressTestClass2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass2* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass2_DeleteInstance(
    _In_opt_ StressTestClass2_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass2* instanceName);


#endif /* _StressTestClass2_h */
