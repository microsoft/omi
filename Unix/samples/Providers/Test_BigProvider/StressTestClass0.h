/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _StressTestClass0_h
#define _StressTestClass0_h

#include <MI.h>

/*
**==============================================================================
**
** StressTestClass0 [StressTestClass0]
**
** Keys:
**    someKey0
**
**==============================================================================
*/

typedef struct _StressTestClass0
{
    MI_Instance __instance;
    /* StressTestClass0 properties */
    /*KEY*/ MI_ConstUint32Field someKey0;
}
StressTestClass0;

typedef struct _StressTestClass0_Ref
{
    StressTestClass0* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass0_Ref;

typedef struct _StressTestClass0_ConstRef
{
    MI_CONST StressTestClass0* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass0_ConstRef;

typedef struct _StressTestClass0_Array
{
    struct _StressTestClass0** data;
    MI_Uint32 size;
}
StressTestClass0_Array;

typedef struct _StressTestClass0_ConstArray
{
    struct _StressTestClass0 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
StressTestClass0_ConstArray;

typedef struct _StressTestClass0_ArrayRef
{
    StressTestClass0_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass0_ArrayRef;

typedef struct _StressTestClass0_ConstArrayRef
{
    StressTestClass0_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
StressTestClass0_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl StressTestClass0_rtti;

MI_INLINE MI_Result MI_CALL StressTestClass0_Construct(
    _Out_ StressTestClass0* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &StressTestClass0_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass0_Clone(
    _In_ const StressTestClass0* self,
    _Outptr_ StressTestClass0** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL StressTestClass0_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &StressTestClass0_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL StressTestClass0_Destruct(_Inout_ StressTestClass0* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass0_Delete(_Inout_ StressTestClass0* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass0_Post(
    _In_ const StressTestClass0* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL StressTestClass0_Set_someKey0(
    _Inout_ StressTestClass0* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->someKey0)->value = x;
    ((MI_Uint32Field*)&self->someKey0)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL StressTestClass0_Clear_someKey0(
    _Inout_ StressTestClass0* self)
{
    memset((void*)&self->someKey0, 0, sizeof(self->someKey0));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** StressTestClass0 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _StressTestClass0_Self StressTestClass0_Self;

MI_EXTERN_C void MI_CALL StressTestClass0_Load(
    _Outptr_result_maybenull_ StressTestClass0_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass0_Unload(
    _In_opt_ StressTestClass0_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL StressTestClass0_EnumerateInstances(
    _In_opt_ StressTestClass0_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL StressTestClass0_GetInstance(
    _In_opt_ StressTestClass0_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass0* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass0_CreateInstance(
    _In_opt_ StressTestClass0_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass0* newInstance);

MI_EXTERN_C void MI_CALL StressTestClass0_ModifyInstance(
    _In_opt_ StressTestClass0_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass0* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL StressTestClass0_DeleteInstance(
    _In_opt_ StressTestClass0_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass0* instanceName);


#endif /* _StressTestClass0_h */
