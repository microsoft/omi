/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_OctetStrings_h
#define _OMI_OctetStrings_h

#include <MI.h>

/*
**==============================================================================
**
** OMI_OctetStrings [OMI_OctetStrings]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _OMI_OctetStrings
{
    MI_Instance __instance;
    /* OMI_OctetStrings properties */
    /*KEY*/ MI_ConstStringField Key;
    MI_ConstUint8AField Data1;
    MI_ConstStringAField Data2;
    MI_ConstStringField Str;
}
OMI_OctetStrings;

typedef struct _OMI_OctetStrings_Ref
{
    OMI_OctetStrings* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_OctetStrings_Ref;

typedef struct _OMI_OctetStrings_ConstRef
{
    MI_CONST OMI_OctetStrings* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_OctetStrings_ConstRef;

typedef struct _OMI_OctetStrings_Array
{
    struct _OMI_OctetStrings** data;
    MI_Uint32 size;
}
OMI_OctetStrings_Array;

typedef struct _OMI_OctetStrings_ConstArray
{
    struct _OMI_OctetStrings MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_OctetStrings_ConstArray;

typedef struct _OMI_OctetStrings_ArrayRef
{
    OMI_OctetStrings_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_OctetStrings_ArrayRef;

typedef struct _OMI_OctetStrings_ConstArrayRef
{
    OMI_OctetStrings_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_OctetStrings_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_OctetStrings_rtti;

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Construct(
    OMI_OctetStrings* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &OMI_OctetStrings_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Clone(
    const OMI_OctetStrings* self,
    OMI_OctetStrings** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_OctetStrings_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_OctetStrings_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Destruct(OMI_OctetStrings* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Delete(OMI_OctetStrings* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Post(
    const OMI_OctetStrings* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Set_Key(
    OMI_OctetStrings* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_SetPtr_Key(
    OMI_OctetStrings* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Clear_Key(
    OMI_OctetStrings* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Set_Data1(
    OMI_OctetStrings* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_SetPtr_Data1(
    OMI_OctetStrings* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Clear_Data1(
    OMI_OctetStrings* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Set_Data2(
    OMI_OctetStrings* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_SetPtr_Data2(
    OMI_OctetStrings* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Clear_Data2(
    OMI_OctetStrings* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Set_Str(
    OMI_OctetStrings* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_SetPtr_Str(
    OMI_OctetStrings* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_OctetStrings_Clear_Str(
    OMI_OctetStrings* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** OMI_OctetStrings provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _OMI_OctetStrings_Self OMI_OctetStrings_Self;

MI_EXTERN_C void MI_CALL OMI_OctetStrings_Load(
    OMI_OctetStrings_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_OctetStrings_Unload(
    OMI_OctetStrings_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_OctetStrings_EnumerateInstances(
    OMI_OctetStrings_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL OMI_OctetStrings_GetInstance(
    OMI_OctetStrings_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_OctetStrings* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_OctetStrings_CreateInstance(
    OMI_OctetStrings_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_OctetStrings* newInstance);

MI_EXTERN_C void MI_CALL OMI_OctetStrings_ModifyInstance(
    OMI_OctetStrings_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_OctetStrings* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_OctetStrings_DeleteInstance(
    OMI_OctetStrings_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_OctetStrings* instanceName);


#endif /* _OMI_OctetStrings_h */
