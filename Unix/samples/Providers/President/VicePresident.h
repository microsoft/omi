/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _VicePresident_h
#define _VicePresident_h

#include <MI.h>

/*
**==============================================================================
**
** VicePresident [MSFT_VicePresident]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _VicePresident
{
    MI_Instance __instance;
    /* VicePresident properties */
    /*KEY*/ MI_ConstUint32Field Key;
    MI_ConstStringField First;
    MI_ConstStringField Last;
}
VicePresident;

typedef struct _VicePresident_Ref
{
    VicePresident* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
VicePresident_Ref;

typedef struct _VicePresident_ConstRef
{
    MI_CONST VicePresident* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
VicePresident_ConstRef;

typedef struct _VicePresident_Array
{
    struct _VicePresident** data;
    MI_Uint32 size;
}
VicePresident_Array;

typedef struct _VicePresident_ConstArray
{
    struct _VicePresident MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
VicePresident_ConstArray;

typedef struct _VicePresident_ArrayRef
{
    VicePresident_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
VicePresident_ArrayRef;

typedef struct _VicePresident_ConstArrayRef
{
    VicePresident_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
VicePresident_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl VicePresident_rtti;

MI_INLINE MI_Result MI_CALL VicePresident_Construct(
    VicePresident* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &VicePresident_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL VicePresident_Clone(
    const VicePresident* self,
    VicePresident** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL VicePresident_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &VicePresident_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL VicePresident_Destruct(VicePresident* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL VicePresident_Delete(VicePresident* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL VicePresident_Post(
    const VicePresident* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL VicePresident_Set_Key(
    VicePresident* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Key)->value = x;
    ((MI_Uint32Field*)&self->Key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL VicePresident_Clear_Key(
    VicePresident* self)
{
    memset((void*)&self->Key, 0, sizeof(self->Key));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL VicePresident_Set_First(
    VicePresident* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL VicePresident_SetPtr_First(
    VicePresident* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL VicePresident_Clear_First(
    VicePresident* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL VicePresident_Set_Last(
    VicePresident* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL VicePresident_SetPtr_Last(
    VicePresident* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL VicePresident_Clear_Last(
    VicePresident* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** VicePresident provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _VicePresident_Self VicePresident_Self;

MI_EXTERN_C void MI_CALL VicePresident_Load(
    VicePresident_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL VicePresident_Unload(
    VicePresident_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL VicePresident_EnumerateInstances(
    VicePresident_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL VicePresident_GetInstance(
    VicePresident_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const VicePresident* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL VicePresident_CreateInstance(
    VicePresident_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const VicePresident* newInstance);

MI_EXTERN_C void MI_CALL VicePresident_ModifyInstance(
    VicePresident_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const VicePresident* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL VicePresident_DeleteInstance(
    VicePresident_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const VicePresident* instanceName);


#endif /* _VicePresident_h */
