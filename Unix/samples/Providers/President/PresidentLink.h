/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _PresidentLink_h
#define _PresidentLink_h

#include <MI.h>
#include "President.h"

/*
**==============================================================================
**
** PresidentLink [MSFT_PresidentLink]
**
** Keys:
**    Prev
**    Next
**
**==============================================================================
*/

typedef struct _PresidentLink
{
    MI_Instance __instance;
    /* PresidentLink properties */
    /*KEY*/ President_ConstRef Prev;
    /*KEY*/ President_ConstRef Next;
}
PresidentLink;

typedef struct _PresidentLink_Ref
{
    PresidentLink* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PresidentLink_Ref;

typedef struct _PresidentLink_ConstRef
{
    MI_CONST PresidentLink* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PresidentLink_ConstRef;

typedef struct _PresidentLink_Array
{
    struct _PresidentLink** data;
    MI_Uint32 size;
}
PresidentLink_Array;

typedef struct _PresidentLink_ConstArray
{
    struct _PresidentLink MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
PresidentLink_ConstArray;

typedef struct _PresidentLink_ArrayRef
{
    PresidentLink_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PresidentLink_ArrayRef;

typedef struct _PresidentLink_ConstArrayRef
{
    PresidentLink_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
PresidentLink_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl PresidentLink_rtti;

MI_INLINE MI_Result MI_CALL PresidentLink_Construct(
    PresidentLink* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &PresidentLink_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL PresidentLink_Clone(
    const PresidentLink* self,
    PresidentLink** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL PresidentLink_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &PresidentLink_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL PresidentLink_Destruct(PresidentLink* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL PresidentLink_Delete(PresidentLink* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL PresidentLink_Post(
    const PresidentLink* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL PresidentLink_Set_Prev(
    PresidentLink* self,
    const President* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL PresidentLink_SetPtr_Prev(
    PresidentLink* self,
    const President* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PresidentLink_Clear_Prev(
    PresidentLink* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL PresidentLink_Set_Next(
    PresidentLink* self,
    const President* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL PresidentLink_SetPtr_Next(
    PresidentLink* self,
    const President* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL PresidentLink_Clear_Next(
    PresidentLink* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** PresidentLink provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _PresidentLink_Self PresidentLink_Self;

MI_EXTERN_C void MI_CALL PresidentLink_Load(
    PresidentLink_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL PresidentLink_Unload(
    PresidentLink_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL PresidentLink_EnumerateInstances(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL PresidentLink_GetInstance(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PresidentLink* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL PresidentLink_CreateInstance(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PresidentLink* newInstance);

MI_EXTERN_C void MI_CALL PresidentLink_ModifyInstance(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PresidentLink* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL PresidentLink_DeleteInstance(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const PresidentLink* instanceName);

MI_EXTERN_C void MI_CALL PresidentLink_AssociatorInstances(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL PresidentLink_ReferenceInstances(
    PresidentLink_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


#endif /* _PresidentLink_h */
