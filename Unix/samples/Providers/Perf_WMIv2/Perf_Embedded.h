/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Perf_Embedded_h
#define _Perf_Embedded_h

#include <MI.h>

/*
**==============================================================================
**
** Perf_Embedded [Perf_Embedded]
**
** Keys:
**    v_embeddedKey
**
**==============================================================================
*/

typedef struct _Perf_Embedded
{
    MI_Instance __instance;
    /* Perf_Embedded properties */
    /*KEY*/ MI_ConstUint16Field v_embeddedKey;
    MI_ConstStringField v_string;
}
Perf_Embedded;

typedef struct _Perf_Embedded_Ref
{
    Perf_Embedded* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_Embedded_Ref;

typedef struct _Perf_Embedded_ConstRef
{
    MI_CONST Perf_Embedded* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_Embedded_ConstRef;

typedef struct _Perf_Embedded_Array
{
    struct _Perf_Embedded** data;
    MI_Uint32 size;
}
Perf_Embedded_Array;

typedef struct _Perf_Embedded_ConstArray
{
    struct _Perf_Embedded MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Perf_Embedded_ConstArray;

typedef struct _Perf_Embedded_ArrayRef
{
    Perf_Embedded_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_Embedded_ArrayRef;

typedef struct _Perf_Embedded_ConstArrayRef
{
    Perf_Embedded_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Perf_Embedded_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Perf_Embedded_rtti;

MI_INLINE MI_Result MI_CALL Perf_Embedded_Construct(
    _Inout_ Perf_Embedded* self,
    _In_ MI_Context* context)
{
    return MI_ConstructInstance(context, &Perf_Embedded_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_Embedded_Clone(
    _In_ const Perf_Embedded* self,
    _Outptr_ Perf_Embedded** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Perf_Embedded_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Perf_Embedded_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Perf_Embedded_Destruct(_Inout_ Perf_Embedded* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_Embedded_Delete(_Inout_ Perf_Embedded* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_Embedded_Post(
    _In_ const Perf_Embedded* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Perf_Embedded_Set_v_embeddedKey(
    _Inout_ Perf_Embedded* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->v_embeddedKey)->value = x;
    ((MI_Uint16Field*)&self->v_embeddedKey)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Embedded_Clear_v_embeddedKey(
    _Inout_ Perf_Embedded* self)
{
    memset((void*)&self->v_embeddedKey, 0, sizeof(self->v_embeddedKey));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Perf_Embedded_Set_v_string(
    _Inout_ Perf_Embedded* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Perf_Embedded_SetPtr_v_string(
    _Inout_ Perf_Embedded* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Perf_Embedded_Clear_v_string(
    _Inout_ Perf_Embedded* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** Perf_Embedded provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Perf_Embedded_Self Perf_Embedded_Self;

MI_EXTERN_C void MI_CALL Perf_Embedded_Load(
    _Outptr_result_maybenull_ Perf_Embedded_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Perf_Embedded_Unload(
    _In_opt_ Perf_Embedded_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Perf_Embedded_EnumerateInstances(
    _In_opt_ Perf_Embedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Perf_Embedded_GetInstance(
    _In_opt_ Perf_Embedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_Embedded* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Perf_Embedded_CreateInstance(
    _In_opt_ Perf_Embedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_Embedded* newInstance);

MI_EXTERN_C void MI_CALL Perf_Embedded_ModifyInstance(
    _In_opt_ Perf_Embedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_Embedded* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Perf_Embedded_DeleteInstance(
    _In_opt_ Perf_Embedded_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_Embedded* instanceName);


#endif /* _Perf_Embedded_h */
