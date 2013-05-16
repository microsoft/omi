/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _DerivedAssoc_h
#define _DerivedAssoc_h

#include <MI.h>
#include "BaseAssoc.h"
#include "Widget.h"
#include "Gadget.h"

/*
**==============================================================================
**
** DerivedAssoc [XYZ_DerivedAssoc]
**
** Keys:
**
**==============================================================================
*/

typedef struct _DerivedAssoc /* extends XYZ_BaseAssoc */
{
    MI_Instance __instance;
    /* BaseAssoc properties */
    Widget_ConstRef Left;
    Gadget_ConstRef Right;
    /* DerivedAssoc properties */
}
DerivedAssoc;

typedef struct _DerivedAssoc_Ref
{
    DerivedAssoc* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
DerivedAssoc_Ref;

typedef struct _DerivedAssoc_ConstRef
{
    MI_CONST DerivedAssoc* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
DerivedAssoc_ConstRef;

typedef struct _DerivedAssoc_Array
{
    struct _DerivedAssoc** data;
    MI_Uint32 size;
}
DerivedAssoc_Array;

typedef struct _DerivedAssoc_ConstArray
{
    struct _DerivedAssoc MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
DerivedAssoc_ConstArray;

typedef struct _DerivedAssoc_ArrayRef
{
    DerivedAssoc_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
DerivedAssoc_ArrayRef;

typedef struct _DerivedAssoc_ConstArrayRef
{
    DerivedAssoc_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
DerivedAssoc_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl DerivedAssoc_rtti;

MI_INLINE MI_Result MI_CALL DerivedAssoc_Construct(
    DerivedAssoc* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &DerivedAssoc_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL DerivedAssoc_Clone(
    const DerivedAssoc* self,
    DerivedAssoc** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL DerivedAssoc_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &DerivedAssoc_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL DerivedAssoc_Destruct(DerivedAssoc* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL DerivedAssoc_Delete(DerivedAssoc* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL DerivedAssoc_Post(
    const DerivedAssoc* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL DerivedAssoc_Set_Left(
    DerivedAssoc* self,
    const Widget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL DerivedAssoc_SetPtr_Left(
    DerivedAssoc* self,
    const Widget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL DerivedAssoc_Clear_Left(
    DerivedAssoc* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL DerivedAssoc_Set_Right(
    DerivedAssoc* self,
    const Gadget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL DerivedAssoc_SetPtr_Right(
    DerivedAssoc* self,
    const Gadget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL DerivedAssoc_Clear_Right(
    DerivedAssoc* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** DerivedAssoc provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _DerivedAssoc_Self DerivedAssoc_Self;

MI_EXTERN_C void MI_CALL DerivedAssoc_Load(
    DerivedAssoc_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL DerivedAssoc_Unload(
    DerivedAssoc_Self* self,
    MI_Context* context);


/*
**==============================================================================
**
** DerivedAssoc_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class DerivedAssoc_Class : public BaseAssoc_Class
{
public:
    
    typedef DerivedAssoc Self;
    
    DerivedAssoc_Class() :
        BaseAssoc_Class(&DerivedAssoc_rtti)
    {
    }
    
    DerivedAssoc_Class(
        const DerivedAssoc* instanceName,
        bool keysOnly) :
        BaseAssoc_Class(
            &DerivedAssoc_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    DerivedAssoc_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        BaseAssoc_Class(clDecl, instance, keysOnly)
    {
    }
    
    DerivedAssoc_Class(
        const MI_ClassDecl* clDecl) :
        BaseAssoc_Class(clDecl)
    {
    }
    
    DerivedAssoc_Class& operator=(
        const DerivedAssoc_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    DerivedAssoc_Class(
        const DerivedAssoc_Class& x) :
        BaseAssoc_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &DerivedAssoc_rtti;
    }

};

typedef Array<DerivedAssoc_Class> DerivedAssoc_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _DerivedAssoc_h */
