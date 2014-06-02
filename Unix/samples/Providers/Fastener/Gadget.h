/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Gadget_h
#define _Gadget_h

#include <MI.h>

/*
**==============================================================================
**
** Gadget [MSFT_Gadget]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Gadget
{
    MI_Instance __instance;
    /* Gadget properties */
    /*KEY*/ MI_ConstUint32Field Key;
}
Gadget;

typedef struct _Gadget_Ref
{
    Gadget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Gadget_Ref;

typedef struct _Gadget_ConstRef
{
    MI_CONST Gadget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Gadget_ConstRef;

typedef struct _Gadget_Array
{
    struct _Gadget** data;
    MI_Uint32 size;
}
Gadget_Array;

typedef struct _Gadget_ConstArray
{
    struct _Gadget MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Gadget_ConstArray;

typedef struct _Gadget_ArrayRef
{
    Gadget_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Gadget_ArrayRef;

typedef struct _Gadget_ConstArrayRef
{
    Gadget_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Gadget_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Gadget_rtti;

MI_INLINE MI_Result MI_CALL Gadget_Construct(
    Gadget* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Gadget_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_Clone(
    const Gadget* self,
    Gadget** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Gadget_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Gadget_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Gadget_Destruct(Gadget* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_Delete(Gadget* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_Post(
    const Gadget* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Gadget_Set_Key(
    Gadget* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Key)->value = x;
    ((MI_Uint32Field*)&self->Key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Gadget_Clear_Key(
    Gadget* self)
{
    memset((void*)&self->Key, 0, sizeof(self->Key));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Gadget provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Gadget_Self Gadget_Self;

MI_EXTERN_C void MI_CALL Gadget_Load(
    Gadget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Gadget_Unload(
    Gadget_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Gadget_EnumerateInstances(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Gadget_GetInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Gadget_CreateInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* newInstance);

MI_EXTERN_C void MI_CALL Gadget_ModifyInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Gadget_DeleteInstance(
    Gadget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName);


#endif /* _Gadget_h */
