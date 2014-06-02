/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _BaseAssoc_h
#define _BaseAssoc_h

#include <MI.h>
#include "Widget.h"
#include "Gadget.h"

/*
**==============================================================================
**
** BaseAssoc [XYZ_BaseAssoc]
**
** Keys:
**
**==============================================================================
*/

typedef struct _BaseAssoc
{
    MI_Instance __instance;
    /* BaseAssoc properties */
    Widget_ConstRef Left;
    Gadget_ConstRef Right;
}
BaseAssoc;

typedef struct _BaseAssoc_Ref
{
    BaseAssoc* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
BaseAssoc_Ref;

typedef struct _BaseAssoc_ConstRef
{
    MI_CONST BaseAssoc* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
BaseAssoc_ConstRef;

typedef struct _BaseAssoc_Array
{
    struct _BaseAssoc** data;
    MI_Uint32 size;
}
BaseAssoc_Array;

typedef struct _BaseAssoc_ConstArray
{
    struct _BaseAssoc MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
BaseAssoc_ConstArray;

typedef struct _BaseAssoc_ArrayRef
{
    BaseAssoc_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
BaseAssoc_ArrayRef;

typedef struct _BaseAssoc_ConstArrayRef
{
    BaseAssoc_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
BaseAssoc_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl BaseAssoc_rtti;

MI_INLINE MI_Result MI_CALL BaseAssoc_Construct(
    BaseAssoc* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &BaseAssoc_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL BaseAssoc_Clone(
    const BaseAssoc* self,
    BaseAssoc** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL BaseAssoc_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &BaseAssoc_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL BaseAssoc_Destruct(BaseAssoc* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL BaseAssoc_Delete(BaseAssoc* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL BaseAssoc_Post(
    const BaseAssoc* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL BaseAssoc_Set_Left(
    BaseAssoc* self,
    const Widget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL BaseAssoc_SetPtr_Left(
    BaseAssoc* self,
    const Widget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL BaseAssoc_Clear_Left(
    BaseAssoc* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL BaseAssoc_Set_Right(
    BaseAssoc* self,
    const Gadget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL BaseAssoc_SetPtr_Right(
    BaseAssoc* self,
    const Gadget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL BaseAssoc_Clear_Right(
    BaseAssoc* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** BaseAssoc provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _BaseAssoc_Self BaseAssoc_Self;

MI_EXTERN_C void MI_CALL BaseAssoc_Load(
    BaseAssoc_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL BaseAssoc_Unload(
    BaseAssoc_Self* self,
    MI_Context* context);


/*
**==============================================================================
**
** BaseAssoc_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class BaseAssoc_Class : public Instance
{
public:
    
    typedef BaseAssoc Self;
    
    BaseAssoc_Class() :
        Instance(&BaseAssoc_rtti)
    {
    }
    
    BaseAssoc_Class(
        const BaseAssoc* instanceName,
        bool keysOnly) :
        Instance(
            &BaseAssoc_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    BaseAssoc_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    BaseAssoc_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    BaseAssoc_Class& operator=(
        const BaseAssoc_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    BaseAssoc_Class(
        const BaseAssoc_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &BaseAssoc_rtti;
    }

    //
    // BaseAssoc_Class.Left
    //
    
    const Field<Widget_Class>& Left() const
    {
        const size_t n = offsetof(Self, Left);
        return GetField<Widget_Class>(n);
    }
    
    void Left(const Field<Widget_Class>& x)
    {
        const size_t n = offsetof(Self, Left);
        GetField<Widget_Class>(n) = x;
    }
    
    const Widget_Class& Left_value() const
    {
        const size_t n = offsetof(Self, Left);
        return GetField<Widget_Class>(n).value;
    }
    
    void Left_value(const Widget_Class& x)
    {
        const size_t n = offsetof(Self, Left);
        GetField<Widget_Class>(n).Set(x);
    }
    
    bool Left_exists() const
    {
        const size_t n = offsetof(Self, Left);
        return GetField<Widget_Class>(n).exists ? true : false;
    }
    
    void Left_clear()
    {
        const size_t n = offsetof(Self, Left);
        GetField<Widget_Class>(n).Clear();
    }

    //
    // BaseAssoc_Class.Right
    //
    
    const Field<Gadget_Class>& Right() const
    {
        const size_t n = offsetof(Self, Right);
        return GetField<Gadget_Class>(n);
    }
    
    void Right(const Field<Gadget_Class>& x)
    {
        const size_t n = offsetof(Self, Right);
        GetField<Gadget_Class>(n) = x;
    }
    
    const Gadget_Class& Right_value() const
    {
        const size_t n = offsetof(Self, Right);
        return GetField<Gadget_Class>(n).value;
    }
    
    void Right_value(const Gadget_Class& x)
    {
        const size_t n = offsetof(Self, Right);
        GetField<Gadget_Class>(n).Set(x);
    }
    
    bool Right_exists() const
    {
        const size_t n = offsetof(Self, Right);
        return GetField<Gadget_Class>(n).exists ? true : false;
    }
    
    void Right_clear()
    {
        const size_t n = offsetof(Self, Right);
        GetField<Gadget_Class>(n).Clear();
    }
};

typedef Array<BaseAssoc_Class> BaseAssoc_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _BaseAssoc_h */
