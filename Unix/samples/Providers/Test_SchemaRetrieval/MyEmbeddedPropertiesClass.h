/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyEmbeddedPropertiesClass_h
#define _MyEmbeddedPropertiesClass_h

#include <MI.h>
#include "MySimplePropertiesClass.h"

/*
**==============================================================================
**
** MyEmbeddedPropertiesClass [MyEmbeddedPropertiesClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyEmbeddedPropertiesClass
{
    MI_Instance __instance;
    /* MyEmbeddedPropertiesClass properties */
    MI_ConstReferenceField v_embeddedObject;
    MySimplePropertiesClass_ConstRef v_embeddedInstance;
}
MyEmbeddedPropertiesClass;

typedef struct _MyEmbeddedPropertiesClass_Ref
{
    MyEmbeddedPropertiesClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmbeddedPropertiesClass_Ref;

typedef struct _MyEmbeddedPropertiesClass_ConstRef
{
    MI_CONST MyEmbeddedPropertiesClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmbeddedPropertiesClass_ConstRef;

typedef struct _MyEmbeddedPropertiesClass_Array
{
    struct _MyEmbeddedPropertiesClass** data;
    MI_Uint32 size;
}
MyEmbeddedPropertiesClass_Array;

typedef struct _MyEmbeddedPropertiesClass_ConstArray
{
    struct _MyEmbeddedPropertiesClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyEmbeddedPropertiesClass_ConstArray;

typedef struct _MyEmbeddedPropertiesClass_ArrayRef
{
    MyEmbeddedPropertiesClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmbeddedPropertiesClass_ArrayRef;

typedef struct _MyEmbeddedPropertiesClass_ConstArrayRef
{
    MyEmbeddedPropertiesClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmbeddedPropertiesClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyEmbeddedPropertiesClass_rtti;

MI_INLINE MI_Result MI_CALL MyEmbeddedPropertiesClass_Construct(
    MyEmbeddedPropertiesClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyEmbeddedPropertiesClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmbeddedPropertiesClass_Clone(
    const MyEmbeddedPropertiesClass* self,
    MyEmbeddedPropertiesClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyEmbeddedPropertiesClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyEmbeddedPropertiesClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyEmbeddedPropertiesClass_Destruct(MyEmbeddedPropertiesClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmbeddedPropertiesClass_Delete(MyEmbeddedPropertiesClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmbeddedPropertiesClass_Post(
    const MyEmbeddedPropertiesClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmbeddedPropertiesClass_Set_v_embeddedObject(
    MyEmbeddedPropertiesClass* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MyEmbeddedPropertiesClass_SetPtr_v_embeddedObject(
    MyEmbeddedPropertiesClass* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyEmbeddedPropertiesClass_Clear_v_embeddedObject(
    MyEmbeddedPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MyEmbeddedPropertiesClass_Set_v_embeddedInstance(
    MyEmbeddedPropertiesClass* self,
    const MySimplePropertiesClass* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MyEmbeddedPropertiesClass_SetPtr_v_embeddedInstance(
    MyEmbeddedPropertiesClass* self,
    const MySimplePropertiesClass* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MyEmbeddedPropertiesClass_Clear_v_embeddedInstance(
    MyEmbeddedPropertiesClass* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MyEmbeddedPropertiesClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyEmbeddedPropertiesClass_Self MyEmbeddedPropertiesClass_Self;

MI_EXTERN_C void MI_CALL MyEmbeddedPropertiesClass_Load(
    MyEmbeddedPropertiesClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyEmbeddedPropertiesClass_Unload(
    MyEmbeddedPropertiesClass_Self* self,
    MI_Context* context);


#endif /* _MyEmbeddedPropertiesClass_h */
