/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Numbers_h
#define _Numbers_h

#include <MI.h>

/*
**==============================================================================
**
** Numbers [Numbers]
**
** Keys:
**
**==============================================================================
*/

typedef struct _Numbers
{
    MI_Instance __instance;
    /* Numbers properties */
    MI_ConstSint64AField numbers;
    MI_ConstUint32Field count;
}
Numbers;

typedef struct _Numbers_Ref
{
    Numbers* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Numbers_Ref;

typedef struct _Numbers_ConstRef
{
    MI_CONST Numbers* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Numbers_ConstRef;

typedef struct _Numbers_Array
{
    struct _Numbers** data;
    MI_Uint32 size;
}
Numbers_Array;

typedef struct _Numbers_ConstArray
{
    struct _Numbers MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Numbers_ConstArray;

typedef struct _Numbers_ArrayRef
{
    Numbers_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Numbers_ArrayRef;

typedef struct _Numbers_ConstArrayRef
{
    Numbers_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Numbers_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Numbers_rtti;

MI_INLINE MI_Result MI_CALL Numbers_Construct(
    _Inout_ Numbers* self,
    _In_ MI_Context* context)
{
    return MI_ConstructInstance(context, &Numbers_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Numbers_Clone(
    _In_ const Numbers* self,
    _Outptr_ Numbers** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Numbers_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Numbers_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Numbers_Destruct(_Inout_ Numbers* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Numbers_Delete(_Inout_ Numbers* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Numbers_Post(
    _In_ const Numbers* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Numbers_Set_numbers(
    _Inout_ Numbers* self,
    _In_reads_opt_(size) const MI_Sint64* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&arr,
        MI_SINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL Numbers_SetPtr_numbers(
    _Inout_ Numbers* self,
    _In_reads_opt_(size) const MI_Sint64* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&arr,
        MI_SINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Numbers_Clear_numbers(
    _Inout_ Numbers* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Numbers_Set_count(
    _Inout_ Numbers* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->count)->value = x;
    ((MI_Uint32Field*)&self->count)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Numbers_Clear_count(
    _Inout_ Numbers* self)
{
    memset((void*)&self->count, 0, sizeof(self->count));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Numbers provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Numbers_Self Numbers_Self;

MI_EXTERN_C void MI_CALL Numbers_Load(
    _Outptr_result_maybenull_ Numbers_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL Numbers_Unload(
    _In_opt_ Numbers_Self* self,
    _In_ MI_Context* context);


#endif /* _Numbers_h */
