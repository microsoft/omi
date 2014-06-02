/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MySimpleQualClass_h
#define _MySimpleQualClass_h

#include <MI.h>

/*
**==============================================================================
**
** MySimpleQualClass [MySimpleQualClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MySimpleQualClass
{
    MI_Instance __instance;
    /* MySimpleQualClass properties */
}
MySimpleQualClass;

typedef struct _MySimpleQualClass_Ref
{
    MySimpleQualClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleQualClass_Ref;

typedef struct _MySimpleQualClass_ConstRef
{
    MI_CONST MySimpleQualClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleQualClass_ConstRef;

typedef struct _MySimpleQualClass_Array
{
    struct _MySimpleQualClass** data;
    MI_Uint32 size;
}
MySimpleQualClass_Array;

typedef struct _MySimpleQualClass_ConstArray
{
    struct _MySimpleQualClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MySimpleQualClass_ConstArray;

typedef struct _MySimpleQualClass_ArrayRef
{
    MySimpleQualClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleQualClass_ArrayRef;

typedef struct _MySimpleQualClass_ConstArrayRef
{
    MySimpleQualClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySimpleQualClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MySimpleQualClass_rtti;

MI_INLINE MI_Result MI_CALL MySimpleQualClass_Construct(
    MySimpleQualClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MySimpleQualClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleQualClass_Clone(
    const MySimpleQualClass* self,
    MySimpleQualClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MySimpleQualClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MySimpleQualClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MySimpleQualClass_Destruct(MySimpleQualClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleQualClass_Delete(MySimpleQualClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySimpleQualClass_Post(
    const MySimpleQualClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MySimpleQualClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MySimpleQualClass_Self MySimpleQualClass_Self;

MI_EXTERN_C void MI_CALL MySimpleQualClass_Load(
    MySimpleQualClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySimpleQualClass_Unload(
    MySimpleQualClass_Self* self,
    MI_Context* context);


#endif /* _MySimpleQualClass_h */
