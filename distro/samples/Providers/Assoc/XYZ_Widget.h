/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _XYZ_Widget_h
#define _XYZ_Widget_h

#include <MI.h>

/*
**==============================================================================
**
** XYZ_Widget [XYZ_Widget]
**
** Keys:
**
**==============================================================================
*/

typedef struct _XYZ_Widget
{
    MI_Instance __instance;
    /* XYZ_Widget properties */
    MI_ConstStringField Key;
}
XYZ_Widget;

typedef struct _XYZ_Widget_Ref
{
    XYZ_Widget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Widget_Ref;

typedef struct _XYZ_Widget_ConstRef
{
    MI_CONST XYZ_Widget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Widget_ConstRef;

typedef struct _XYZ_Widget_Array
{
    struct _XYZ_Widget** data;
    MI_Uint32 size;
}
XYZ_Widget_Array;

typedef struct _XYZ_Widget_ConstArray
{
    struct _XYZ_Widget MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
XYZ_Widget_ConstArray;

typedef struct _XYZ_Widget_ArrayRef
{
    XYZ_Widget_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Widget_ArrayRef;

typedef struct _XYZ_Widget_ConstArrayRef
{
    XYZ_Widget_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Widget_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl XYZ_Widget_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Widget_Construct(
    XYZ_Widget* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &XYZ_Widget_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Widget_Clone(
    const XYZ_Widget* self,
    XYZ_Widget** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL XYZ_Widget_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &XYZ_Widget_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL XYZ_Widget_Destruct(XYZ_Widget* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Widget_Delete(XYZ_Widget* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Widget_Post(
    const XYZ_Widget* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Widget_Set_Key(
    XYZ_Widget* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Widget_SetPtr_Key(
    XYZ_Widget* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Widget_Clear_Key(
    XYZ_Widget* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** XYZ_Widget provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _XYZ_Widget_Self XYZ_Widget_Self;

MI_EXTERN_C void MI_CALL XYZ_Widget_Load(
    XYZ_Widget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Widget_Unload(
    XYZ_Widget_Self* self,
    MI_Context* context);


/*
**==============================================================================
**
** XYZ_Widget_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class XYZ_Widget_Class : public Instance
{
public:
    
    typedef XYZ_Widget Self;
    
    XYZ_Widget_Class() :
        Instance(&XYZ_Widget_rtti)
    {
    }
    
    XYZ_Widget_Class(
        const XYZ_Widget* instanceName,
        bool keysOnly) :
        Instance(
            &XYZ_Widget_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    XYZ_Widget_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    XYZ_Widget_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    XYZ_Widget_Class& operator=(
        const XYZ_Widget_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    XYZ_Widget_Class(
        const XYZ_Widget_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &XYZ_Widget_rtti;
    }

    //
    // XYZ_Widget_Class.Key
    //
    
    const Field<String>& Key() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<String>(n);
    }
    
    void Key(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Key);
        GetField<String>(n) = x;
    }
    
    const String& Key_value() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<String>(n).value;
    }
    
    void Key_value(const String& x)
    {
        const size_t n = offsetof(Self, Key);
        GetField<String>(n).Set(x);
    }
    
    bool Key_exists() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Key_clear()
    {
        const size_t n = offsetof(Self, Key);
        GetField<String>(n).Clear();
    }
};

typedef Array<XYZ_Widget_Class> XYZ_Widget_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _XYZ_Widget_h */
