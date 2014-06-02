/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MyEmptySecondDerivedClass_h
#define _MyEmptySecondDerivedClass_h

#include <MI.h>
#include "MyEmptyDerivedClass.h"

/*
**==============================================================================
**
** MyEmptySecondDerivedClass [MyEmptySecondDerivedClass]
**
** Keys:
**
**==============================================================================
*/

typedef struct _MyEmptySecondDerivedClass /* extends MyEmptyDerivedClass */
{
    MI_Instance __instance;
    /* MyEmptyClass properties */
    /* MyEmptyDerivedClass properties */
    /* MyEmptySecondDerivedClass properties */
}
MyEmptySecondDerivedClass;

typedef struct _MyEmptySecondDerivedClass_Ref
{
    MyEmptySecondDerivedClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmptySecondDerivedClass_Ref;

typedef struct _MyEmptySecondDerivedClass_ConstRef
{
    MI_CONST MyEmptySecondDerivedClass* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmptySecondDerivedClass_ConstRef;

typedef struct _MyEmptySecondDerivedClass_Array
{
    struct _MyEmptySecondDerivedClass** data;
    MI_Uint32 size;
}
MyEmptySecondDerivedClass_Array;

typedef struct _MyEmptySecondDerivedClass_ConstArray
{
    struct _MyEmptySecondDerivedClass MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MyEmptySecondDerivedClass_ConstArray;

typedef struct _MyEmptySecondDerivedClass_ArrayRef
{
    MyEmptySecondDerivedClass_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmptySecondDerivedClass_ArrayRef;

typedef struct _MyEmptySecondDerivedClass_ConstArrayRef
{
    MyEmptySecondDerivedClass_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MyEmptySecondDerivedClass_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MyEmptySecondDerivedClass_rtti;

MI_INLINE MI_Result MI_CALL MyEmptySecondDerivedClass_Construct(
    MyEmptySecondDerivedClass* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MyEmptySecondDerivedClass_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmptySecondDerivedClass_Clone(
    const MyEmptySecondDerivedClass* self,
    MyEmptySecondDerivedClass** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MyEmptySecondDerivedClass_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MyEmptySecondDerivedClass_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MyEmptySecondDerivedClass_Destruct(MyEmptySecondDerivedClass* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmptySecondDerivedClass_Delete(MyEmptySecondDerivedClass* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MyEmptySecondDerivedClass_Post(
    const MyEmptySecondDerivedClass* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** MyEmptySecondDerivedClass provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MyEmptySecondDerivedClass_Self MyEmptySecondDerivedClass_Self;

MI_EXTERN_C void MI_CALL MyEmptySecondDerivedClass_Load(
    MyEmptySecondDerivedClass_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MyEmptySecondDerivedClass_Unload(
    MyEmptySecondDerivedClass_Self* self,
    MI_Context* context);


#endif /* _MyEmptySecondDerivedClass_h */
