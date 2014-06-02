/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyEmptyClass_h
#define _MyEmptyClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyEmptyClass [MyEmptyClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyEmptyClass
{
    MI_Instance __instance;
    /* MyEmptyClass properties */
}
MyEmptyClass;

typedef struct _MyEmptyClass_Ref
{
    MyEmptyClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmptyClass_Ref;

typedef struct _MyEmptyClass_ConstRef
{
    MI_CONST MyEmptyClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmptyClass_ConstRef;

typedef struct _MyEmptyClass_Array
{
    struct _MyEmptyClass** data;
    MI_Uint32 size;
}
MyEmptyClass_Array;

typedef struct _MyEmptyClass_ConstArray
{
    struct _MyEmptyClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyEmptyClass_ConstArray;

typedef struct _MyEmptyClass_ArrayRef
{
    MyEmptyClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmptyClass_ArrayRef;

typedef struct _MyEmptyClass_ConstArrayRef
{
    MyEmptyClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmptyClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyEmptyClass_rtti;

MI_INLINE MI_Result MI_CALL MyEmptyClass_Construct(
    MyEmptyClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyEmptyClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmptyClass_Clone(
    const MyEmptyClass* self,
    MyEmptyClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyEmptyClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyEmptyClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyEmptyClass_Destruct(MyEmptyClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmptyClass_Delete(MyEmptyClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmptyClass_Post(
    const MyEmptyClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MyEmptyClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyEmptyClass_Self MyEmptyClass_Self;

MI_EXTERN_C void MI_CALL MyEmptyClass_Load(
    MyEmptyClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyEmptyClass_Unload(
    MyEmptyClass_Self* self,
    MI_Context* context);


#endif /* _MyEmptyClass_h */
