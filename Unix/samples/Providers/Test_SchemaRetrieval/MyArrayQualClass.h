/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyArrayQualClass_h
#define _MyArrayQualClass_h

#include <MI.h>

/*
**==============================================================================
**
** MyArrayQualClass [MyArrayQualClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyArrayQualClass
{
    MI_Instance __instance;
    /* MyArrayQualClass properties */
}
MyArrayQualClass;

typedef struct _MyArrayQualClass_Ref
{
    MyArrayQualClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayQualClass_Ref;

typedef struct _MyArrayQualClass_ConstRef
{
    MI_CONST MyArrayQualClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayQualClass_ConstRef;

typedef struct _MyArrayQualClass_Array
{
    struct _MyArrayQualClass** data;
    MI_Uint32 size;
}
MyArrayQualClass_Array;

typedef struct _MyArrayQualClass_ConstArray
{
    struct _MyArrayQualClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyArrayQualClass_ConstArray;

typedef struct _MyArrayQualClass_ArrayRef
{
    MyArrayQualClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayQualClass_ArrayRef;

typedef struct _MyArrayQualClass_ConstArrayRef
{
    MyArrayQualClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyArrayQualClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyArrayQualClass_rtti;

MI_INLINE MI_Result MI_CALL MyArrayQualClass_Construct(
    MyArrayQualClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyArrayQualClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayQualClass_Clone(
    const MyArrayQualClass* self,
    MyArrayQualClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyArrayQualClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyArrayQualClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyArrayQualClass_Destruct(MyArrayQualClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayQualClass_Delete(MyArrayQualClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyArrayQualClass_Post(
    const MyArrayQualClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MyArrayQualClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyArrayQualClass_Self MyArrayQualClass_Self;

MI_EXTERN_C void MI_CALL MyArrayQualClass_Load(
    MyArrayQualClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyArrayQualClass_Unload(
    MyArrayQualClass_Self* self,
    MI_Context* context);


#endif /* _MyArrayQualClass_h */
