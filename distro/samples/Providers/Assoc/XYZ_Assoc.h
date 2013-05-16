/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _XYZ_Assoc_h
#define _XYZ_Assoc_h

#include <MI.h>
#include "XYZ_Widget.h"
#include "XYZ_Gadget.h"

/*
**==============================================================================
**
** XYZ_Assoc [XYZ_Assoc]
**
** Keys:
**    Left
**    Right
**
**==============================================================================
*/

typedef struct _XYZ_Assoc
{
    MI_Instance __instance;
    /* XYZ_Assoc properties */
    /*KEY*/ XYZ_Widget_ConstRef Left;
    /*KEY*/ XYZ_Gadget_ConstRef Right;
}
XYZ_Assoc;

typedef struct _XYZ_Assoc_Ref
{
    XYZ_Assoc* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Assoc_Ref;

typedef struct _XYZ_Assoc_ConstRef
{
    MI_CONST XYZ_Assoc* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Assoc_ConstRef;

typedef struct _XYZ_Assoc_Array
{
    struct _XYZ_Assoc** data;
    MI_Uint32 size;
}
XYZ_Assoc_Array;

typedef struct _XYZ_Assoc_ConstArray
{
    struct _XYZ_Assoc MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
XYZ_Assoc_ConstArray;

typedef struct _XYZ_Assoc_ArrayRef
{
    XYZ_Assoc_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Assoc_ArrayRef;

typedef struct _XYZ_Assoc_ConstArrayRef
{
    XYZ_Assoc_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Assoc_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl XYZ_Assoc_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Assoc_Construct(
    XYZ_Assoc* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &XYZ_Assoc_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc_Clone(
    const XYZ_Assoc* self,
    XYZ_Assoc** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL XYZ_Assoc_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &XYZ_Assoc_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc_Destruct(XYZ_Assoc* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc_Delete(XYZ_Assoc* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc_Post(
    const XYZ_Assoc* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc_Set_Left(
    XYZ_Assoc* self,
    const XYZ_Widget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc_SetPtr_Left(
    XYZ_Assoc* self,
    const XYZ_Widget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc_Clear_Left(
    XYZ_Assoc* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc_Set_Right(
    XYZ_Assoc* self,
    const XYZ_Gadget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc_SetPtr_Right(
    XYZ_Assoc* self,
    const XYZ_Gadget* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc_Clear_Right(
    XYZ_Assoc* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** XYZ_Assoc provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _XYZ_Assoc_Self XYZ_Assoc_Self;

MI_EXTERN_C void MI_CALL XYZ_Assoc_Load(
    XYZ_Assoc_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Assoc_Unload(
    XYZ_Assoc_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Assoc_EnumerateInstances(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Assoc_GetInstance(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Assoc_CreateInstance(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc* newInstance);

MI_EXTERN_C void MI_CALL XYZ_Assoc_ModifyInstance(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Assoc_DeleteInstance(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc* instanceName);

MI_EXTERN_C void MI_CALL XYZ_Assoc_AssociatorInstancesLeft(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Assoc_AssociatorInstancesRight(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Assoc_ReferenceInstancesLeft(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Assoc_ReferenceInstancesRight(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


/*
**==============================================================================
**
** XYZ_Assoc_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class XYZ_Assoc_Class : public Instance
{
public:
    
    typedef XYZ_Assoc Self;
    
    XYZ_Assoc_Class() :
        Instance(&XYZ_Assoc_rtti)
    {
    }
    
    XYZ_Assoc_Class(
        const XYZ_Assoc* instanceName,
        bool keysOnly) :
        Instance(
            &XYZ_Assoc_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    XYZ_Assoc_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    XYZ_Assoc_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    XYZ_Assoc_Class& operator=(
        const XYZ_Assoc_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    XYZ_Assoc_Class(
        const XYZ_Assoc_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &XYZ_Assoc_rtti;
    }

    //
    // XYZ_Assoc_Class.Left
    //
    
    const Field<XYZ_Widget_Class>& Left() const
    {
        const size_t n = offsetof(Self, Left);
        return GetField<XYZ_Widget_Class>(n);
    }
    
    void Left(const Field<XYZ_Widget_Class>& x)
    {
        const size_t n = offsetof(Self, Left);
        GetField<XYZ_Widget_Class>(n) = x;
    }
    
    const XYZ_Widget_Class& Left_value() const
    {
        const size_t n = offsetof(Self, Left);
        return GetField<XYZ_Widget_Class>(n).value;
    }
    
    void Left_value(const XYZ_Widget_Class& x)
    {
        const size_t n = offsetof(Self, Left);
        GetField<XYZ_Widget_Class>(n).Set(x);
    }
    
    bool Left_exists() const
    {
        const size_t n = offsetof(Self, Left);
        return GetField<XYZ_Widget_Class>(n).exists ? true : false;
    }
    
    void Left_clear()
    {
        const size_t n = offsetof(Self, Left);
        GetField<XYZ_Widget_Class>(n).Clear();
    }

    //
    // XYZ_Assoc_Class.Right
    //
    
    const Field<XYZ_Gadget_Class>& Right() const
    {
        const size_t n = offsetof(Self, Right);
        return GetField<XYZ_Gadget_Class>(n);
    }
    
    void Right(const Field<XYZ_Gadget_Class>& x)
    {
        const size_t n = offsetof(Self, Right);
        GetField<XYZ_Gadget_Class>(n) = x;
    }
    
    const XYZ_Gadget_Class& Right_value() const
    {
        const size_t n = offsetof(Self, Right);
        return GetField<XYZ_Gadget_Class>(n).value;
    }
    
    void Right_value(const XYZ_Gadget_Class& x)
    {
        const size_t n = offsetof(Self, Right);
        GetField<XYZ_Gadget_Class>(n).Set(x);
    }
    
    bool Right_exists() const
    {
        const size_t n = offsetof(Self, Right);
        return GetField<XYZ_Gadget_Class>(n).exists ? true : false;
    }
    
    void Right_clear()
    {
        const size_t n = offsetof(Self, Right);
        GetField<XYZ_Gadget_Class>(n).Clear();
    }
};

typedef Array<XYZ_Assoc_Class> XYZ_Assoc_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _XYZ_Assoc_h */
