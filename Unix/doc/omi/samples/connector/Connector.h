/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Connector_h
#define _Connector_h

#include <MI.h>
#include "Widget.h"
#include "Gadget.h"

/*
**==============================================================================
**
** Connector [XYZ_Connector]
**
** Keys:
**    Left
**    Right
**
**==============================================================================
*/

typedef struct _Connector
{
    MI_Instance __instance;
    /* Connector properties */
    /*KEY*/ Widget_ConstRef Left;
    /*KEY*/ Gadget_ConstRef Right;
}
Connector;

typedef struct _Connector_Ref
{
    Connector* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Connector_Ref;

typedef struct _Connector_ConstRef
{
    MI_CONST Connector* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Connector_ConstRef;

typedef struct _Connector_Array
{
    struct _Connector** data;
    MI_Uint32 size;
}
Connector_Array;

typedef struct _Connector_ConstArray
{
    struct _Connector MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Connector_ConstArray;

typedef struct _Connector_ArrayRef
{
    Connector_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Connector_ArrayRef;

typedef struct _Connector_ConstArrayRef
{
    Connector_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Connector_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Connector_rtti;

MI_INLINE MI_Result MI_CALL Connector_Construct(
    Connector* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Connector_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Connector_Clone(
    const Connector* self,
    Connector** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Connector_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Connector_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Connector_Destruct(Connector* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Connector_Delete(Connector* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Connector_Post(
    const Connector* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Connector_Set_Left(
    Connector* self,
    const Widget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL Connector_SetPtr_Left(
    Connector* self,
    const Widget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Connector_Clear_Left(
    Connector* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Connector_Set_Right(
    Connector* self,
    const Gadget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL Connector_SetPtr_Right(
    Connector* self,
    const Gadget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Connector_Clear_Right(
    Connector* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** Connector provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Connector_Self Connector_Self;

MI_EXTERN_C void MI_CALL Connector_Load(
    Connector_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Connector_Unload(
    Connector_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Connector_EnumerateInstances(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Connector_GetInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Connector_CreateInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* newInstance);

MI_EXTERN_C void MI_CALL Connector_ModifyInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Connector_DeleteInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* instanceName);

MI_EXTERN_C void MI_CALL Connector_AssociatorInstancesLeft(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Connector_AssociatorInstancesRight(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Connector_ReferenceInstancesLeft(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Connector_ReferenceInstancesRight(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _Connector_h */
