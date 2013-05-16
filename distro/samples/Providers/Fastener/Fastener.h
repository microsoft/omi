/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Fastener_h
#define _Fastener_h

#include <MI.h>
#include "Widget.h"
#include "Gadget.h"

/*
**==============================================================================
**
** Fastener [MSFT_Fastener]
**
** Keys:
**    Left
**    Right
**
**==============================================================================
*/

typedef struct _Fastener
{
    MI_Instance __instance;
    /* Fastener properties */
    /*KEY*/ Widget_ConstRef Left;
    /*KEY*/ Gadget_ConstRef Right;
}
Fastener;

typedef struct _Fastener_Ref
{
    Fastener* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Fastener_Ref;

typedef struct _Fastener_ConstRef
{
    MI_CONST Fastener* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Fastener_ConstRef;

typedef struct _Fastener_Array
{
    struct _Fastener** data;
    MI_Uint32 size;
}
Fastener_Array;

typedef struct _Fastener_ConstArray
{
    struct _Fastener MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Fastener_ConstArray;

typedef struct _Fastener_ArrayRef
{
    Fastener_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Fastener_ArrayRef;

typedef struct _Fastener_ConstArrayRef
{
    Fastener_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Fastener_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Fastener_rtti;

MI_INLINE MI_Result MI_CALL Fastener_Construct(
    Fastener* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Fastener_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Fastener_Clone(
    const Fastener* self,
    Fastener** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Fastener_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Fastener_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Fastener_Destruct(Fastener* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Fastener_Delete(Fastener* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Fastener_Post(
    const Fastener* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Fastener_Set_Left(
    Fastener* self,
    const Widget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL Fastener_SetPtr_Left(
    Fastener* self,
    const Widget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Fastener_Clear_Left(
    Fastener* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Fastener_Set_Right(
    Fastener* self,
    const Gadget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL Fastener_SetPtr_Right(
    Fastener* self,
    const Gadget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Fastener_Clear_Right(
    Fastener* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** Fastener provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Fastener_Self Fastener_Self;

MI_EXTERN_C void MI_CALL Fastener_Load(
    Fastener_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Fastener_Unload(
    Fastener_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Fastener_EnumerateInstances(
    Fastener_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Fastener_GetInstance(
    Fastener_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Fastener* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Fastener_CreateInstance(
    Fastener_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Fastener* newInstance);

MI_EXTERN_C void MI_CALL Fastener_ModifyInstance(
    Fastener_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Fastener* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Fastener_DeleteInstance(
    Fastener_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Fastener* instanceName);

MI_EXTERN_C void MI_CALL Fastener_AssociatorInstancesLeft(
    Fastener_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Fastener_AssociatorInstancesRight(
    Fastener_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Fastener_ReferenceInstancesLeft(
    Fastener_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Fastener_ReferenceInstancesRight(
    Fastener_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _Fastener_h */
