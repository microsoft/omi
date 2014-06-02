/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyFooClass_h
#define _MyFooClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyFooClass [MyFooClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyFooClass
{
    MI_Instance __instance;
    /* MyFooClass properties */
    MI_ConstSint64Field sint64Prop;
}
MyFooClass;

typedef struct _MyFooClass_Ref
{
    MyFooClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyFooClass_Ref;

typedef struct _MyFooClass_ConstRef
{
    MI_CONST MyFooClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyFooClass_ConstRef;

typedef struct _MyFooClass_Array
{
    struct _MyFooClass** data;
    MI_Uint32 size;
}
MyFooClass_Array;

typedef struct _MyFooClass_ConstArray
{
    struct _MyFooClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyFooClass_ConstArray;

typedef struct _MyFooClass_ArrayRef
{
    MyFooClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyFooClass_ArrayRef;

typedef struct _MyFooClass_ConstArrayRef
{
    MyFooClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyFooClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyFooClass_rtti;

MI_INLINE MI_Result MI_CALL MyFooClass_Construct(
    MyFooClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyFooClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyFooClass_Clone(
    const MyFooClass* self,
    MyFooClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyFooClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyFooClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyFooClass_Destruct(MyFooClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyFooClass_Delete(MyFooClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyFooClass_Post(
    const MyFooClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MyFooClass_Set_sint64Prop(
    MyFooClass* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->sint64Prop)->value = x;
    ((MI_Sint64Field*)&self->sint64Prop)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MyFooClass_Clear_sint64Prop(
    MyFooClass* self)
{
    memset((void*)&self->sint64Prop, 0, sizeof(self->sint64Prop));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MyFooClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyFooClass_Self MyFooClass_Self;

MI_EXTERN_C void MI_CALL MyFooClass_Load(
    MyFooClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyFooClass_Unload(
    MyFooClass_Self* self,
    MI_Context* context);


#endif /* _MyFooClass_h */
