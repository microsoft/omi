/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _StressTestClass1_h
#define _StressTestClass1_h

#include <MI.h>
#include "StressTestClass0.h"

/*
**==============================================================================
**
** StressTestClass1 [StressTestClass1]
**
** Keys:
**    someKey0
**
**==============================================================================
*/

typedef struct _StressTestClass1 /* extends StressTestClass0 */
{
    MI_Instance __instance;
    /* StressTestClass0 properties */
    /*KEY*/ MI_ConstUint32Field someKey0;
    /* StressTestClass1 properties */
    StressTestClass0_ConstRef embeddedInstance0;
}
StressTestClass1;

typedef struct _StressTestClass1_Ref
{
    StressTestClass1* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass1_Ref;

typedef struct _StressTestClass1_ConstRef
{
    MI_CONST StressTestClass1* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass1_ConstRef;

typedef struct _StressTestClass1_Array
{
    struct _StressTestClass1** data;
    MI_Uint32 size;
}
StressTestClass1_Array;

typedef struct _StressTestClass1_ConstArray
{
    struct _StressTestClass1 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
StressTestClass1_ConstArray;

typedef struct _StressTestClass1_ArrayRef
{
    StressTestClass1_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass1_ArrayRef;

typedef struct _StressTestClass1_ConstArrayRef
{
    StressTestClass1_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass1_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl StressTestClass1_rtti;

MI_INLINE MI_Result MI_CALL StressTestClass1_Construct(
    _Out_ StressTestClass1* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &StressTestClass1_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass1_Clone(
    _In_ const StressTestClass1* self,
    _Outptr_ StressTestClass1** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL StressTestClass1_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &StressTestClass1_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL StressTestClass1_Destruct(_Inout_ StressTestClass1* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass1_Delete(_Inout_ StressTestClass1* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass1_Post(
    _In_ const StressTestClass1* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass1_Set_someKey0(
    _Inout_ StressTestClass1* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->someKey0)->value = x;
    ((MI_Uint32Field*)&self->someKey0)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass1_Clear_someKey0(
    _Inout_ StressTestClass1* self)
{
    memset((void*)&self->someKey0, 0, sizeof(self->someKey0));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass1_Set_embeddedInstance0(
    _Inout_ StressTestClass1* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL StressTestClass1_SetPtr_embeddedInstance0(
    _Inout_ StressTestClass1* self,
    _In_ const StressTestClass0* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL StressTestClass1_Clear_embeddedInstance0(
    _Inout_ StressTestClass1* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** StressTestClass1 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _StressTestClass1_Self StressTestClass1_Self;

MI_EXTERN_C void MI_CALL StressTestClass1_Load(
    _Outptr_result_maybenull_ StressTestClass1_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass1_Unload(
    _In_opt_ StressTestClass1_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass1_EnumerateInstances(
    _In_opt_ StressTestClass1_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL StressTestClass1_GetInstance(
    _In_opt_ StressTestClass1_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass1* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass1_CreateInstance(
    _In_opt_ StressTestClass1_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass1* newInstance);

MI_EXTERN_C void MI_CALL StressTestClass1_ModifyInstance(
    _In_opt_ StressTestClass1_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass1* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass1_DeleteInstance(
    _In_opt_ StressTestClass1_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass1* instanceName);


#endif /* _StressTestClass1_h */
