/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyEmptyDerivedClass_h
#define _MyEmptyDerivedClass_h

#include <MI.h>
#include "MyEmptyClass.h"

/*
**==============================================================================
**
** MyEmptyDerivedClass [MyEmptyDerivedClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyEmptyDerivedClass /* extends MyEmptyClass */
{
    MI_Instance __instance;
    /* MyEmptyClass properties */
    /* MyEmptyDerivedClass properties */
}
MyEmptyDerivedClass;

typedef struct _MyEmptyDerivedClass_Ref
{
    MyEmptyDerivedClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmptyDerivedClass_Ref;

typedef struct _MyEmptyDerivedClass_ConstRef
{
    MI_CONST MyEmptyDerivedClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmptyDerivedClass_ConstRef;

typedef struct _MyEmptyDerivedClass_Array
{
    struct _MyEmptyDerivedClass** data;
    MI_Uint32 size;
}
MyEmptyDerivedClass_Array;

typedef struct _MyEmptyDerivedClass_ConstArray
{
    struct _MyEmptyDerivedClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyEmptyDerivedClass_ConstArray;

typedef struct _MyEmptyDerivedClass_ArrayRef
{
    MyEmptyDerivedClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmptyDerivedClass_ArrayRef;

typedef struct _MyEmptyDerivedClass_ConstArrayRef
{
    MyEmptyDerivedClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmptyDerivedClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyEmptyDerivedClass_rtti;

MI_INLINE MI_Result MI_CALL MyEmptyDerivedClass_Construct(
    MyEmptyDerivedClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyEmptyDerivedClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmptyDerivedClass_Clone(
    const MyEmptyDerivedClass* self,
    MyEmptyDerivedClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyEmptyDerivedClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyEmptyDerivedClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyEmptyDerivedClass_Destruct(MyEmptyDerivedClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmptyDerivedClass_Delete(MyEmptyDerivedClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmptyDerivedClass_Post(
    const MyEmptyDerivedClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MyEmptyDerivedClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyEmptyDerivedClass_Self MyEmptyDerivedClass_Self;

MI_EXTERN_C void MI_CALL MyEmptyDerivedClass_Load(
    MyEmptyDerivedClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyEmptyDerivedClass_Unload(
    MyEmptyDerivedClass_Self* self,
    MI_Context* context);


#endif /* _MyEmptyDerivedClass_h */
