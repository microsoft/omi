/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyClassForTestingAddedEmbeddedQualifier_h
#define _MyClassForTestingAddedEmbeddedQualifier_h

#include <MI.h>
#include "MySimplePropertiesClass.h"

/*
**==============================================================================
**
** MyClassForTestingAddedEmbeddedQualifier [MyClassForTestingAddedEmbeddedQualifier]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyClassForTestingAddedEmbeddedQualifier
{
    MI_Instance __instance;
    /* MyClassForTestingAddedEmbeddedQualifier properties */
    MI_ConstReferenceField v_embeddedObject;
    MySimplePropertiesClass_ConstRef v_embeddedInstance;
    MI_ConstReferenceAField a_embeddedObject;
    MySimplePropertiesClass_ConstArrayRef a_embeddedInstance;
}
MyClassForTestingAddedEmbeddedQualifier;

typedef struct _MyClassForTestingAddedEmbeddedQualifier_Ref
{
    MyClassForTestingAddedEmbeddedQualifier* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyClassForTestingAddedEmbeddedQualifier_Ref;

typedef struct _MyClassForTestingAddedEmbeddedQualifier_ConstRef
{
    MI_CONST MyClassForTestingAddedEmbeddedQualifier* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyClassForTestingAddedEmbeddedQualifier_ConstRef;

typedef struct _MyClassForTestingAddedEmbeddedQualifier_Array
{
    struct _MyClassForTestingAddedEmbeddedQualifier** data;
    MI_Uint32 size;
}
MyClassForTestingAddedEmbeddedQualifier_Array;

typedef struct _MyClassForTestingAddedEmbeddedQualifier_ConstArray
{
    struct _MyClassForTestingAddedEmbeddedQualifier MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyClassForTestingAddedEmbeddedQualifier_ConstArray;

typedef struct _MyClassForTestingAddedEmbeddedQualifier_ArrayRef
{
    MyClassForTestingAddedEmbeddedQualifier_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyClassForTestingAddedEmbeddedQualifier_ArrayRef;

typedef struct _MyClassForTestingAddedEmbeddedQualifier_ConstArrayRef
{
    MyClassForTestingAddedEmbeddedQualifier_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyClassForTestingAddedEmbeddedQualifier_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyClassForTestingAddedEmbeddedQualifier_rtti;

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Construct(
    MyClassForTestingAddedEmbeddedQualifier* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyClassForTestingAddedEmbeddedQualifier_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Clone(
    const MyClassForTestingAddedEmbeddedQualifier* self,
    MyClassForTestingAddedEmbeddedQualifier** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyClassForTestingAddedEmbeddedQualifier_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyClassForTestingAddedEmbeddedQualifier_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Destruct(MyClassForTestingAddedEmbeddedQualifier* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Delete(MyClassForTestingAddedEmbeddedQualifier* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Post(
    const MyClassForTestingAddedEmbeddedQualifier* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Set_v_embeddedObject(
    MyClassForTestingAddedEmbeddedQualifier* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_SetPtr_v_embeddedObject(
    MyClassForTestingAddedEmbeddedQualifier* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Clear_v_embeddedObject(
    MyClassForTestingAddedEmbeddedQualifier* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Set_v_embeddedInstance(
    MyClassForTestingAddedEmbeddedQualifier* self,
    const MySimplePropertiesClass* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_SetPtr_v_embeddedInstance(
    MyClassForTestingAddedEmbeddedQualifier* self,
    const MySimplePropertiesClass* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Clear_v_embeddedInstance(
    MyClassForTestingAddedEmbeddedQualifier* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Set_a_embeddedObject(
    MyClassForTestingAddedEmbeddedQualifier* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_SetPtr_a_embeddedObject(
    MyClassForTestingAddedEmbeddedQualifier* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Clear_a_embeddedObject(
    MyClassForTestingAddedEmbeddedQualifier* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Set_a_embeddedInstance(
    MyClassForTestingAddedEmbeddedQualifier* self,
    const MySimplePropertiesClass * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_SetPtr_a_embeddedInstance(
    MyClassForTestingAddedEmbeddedQualifier* self,
    const MySimplePropertiesClass * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyClassForTestingAddedEmbeddedQualifier_Clear_a_embeddedInstance(
    MyClassForTestingAddedEmbeddedQualifier* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MyClassForTestingAddedEmbeddedQualifier provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyClassForTestingAddedEmbeddedQualifier_Self MyClassForTestingAddedEmbeddedQualifier_Self;

MI_EXTERN_C void MI_CALL MyClassForTestingAddedEmbeddedQualifier_Load(
    MyClassForTestingAddedEmbeddedQualifier_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyClassForTestingAddedEmbeddedQualifier_Unload(
    MyClassForTestingAddedEmbeddedQualifier_Self* self,
    MI_Context* context);


#endif /* _MyClassForTestingAddedEmbeddedQualifier_h */
