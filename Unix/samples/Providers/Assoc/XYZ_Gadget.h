/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _XYZ_Gadget_h
#define _XYZ_Gadget_h

#include <MI.h>

/*
**==============================================================================
**
** XYZ_Gadget [XYZ_Gadget]
**
** Keys:
**
**==============================================================================
*/

typedef struct _XYZ_Gadget
{
    MI_Instance __instance;
    /* XYZ_Gadget properties */
    MI_ConstStringField Key;
}
XYZ_Gadget;

typedef struct _XYZ_Gadget_Ref
{
    XYZ_Gadget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Gadget_Ref;

typedef struct _XYZ_Gadget_ConstRef
{
    MI_CONST XYZ_Gadget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Gadget_ConstRef;

typedef struct _XYZ_Gadget_Array
{
    struct _XYZ_Gadget** data;
    MI_Uint32 size;
}
XYZ_Gadget_Array;

typedef struct _XYZ_Gadget_ConstArray
{
    struct _XYZ_Gadget MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
XYZ_Gadget_ConstArray;

typedef struct _XYZ_Gadget_ArrayRef
{
    XYZ_Gadget_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Gadget_ArrayRef;

typedef struct _XYZ_Gadget_ConstArrayRef
{
    XYZ_Gadget_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Gadget_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl XYZ_Gadget_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Gadget_Construct(
    XYZ_Gadget* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &XYZ_Gadget_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget_Clone(
    const XYZ_Gadget* self,
    XYZ_Gadget** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL XYZ_Gadget_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &XYZ_Gadget_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget_Destruct(XYZ_Gadget* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget_Delete(XYZ_Gadget* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget_Post(
    const XYZ_Gadget* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget_Set_Key(
    XYZ_Gadget* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget_SetPtr_Key(
    XYZ_Gadget* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget_Clear_Key(
    XYZ_Gadget* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** XYZ_Gadget provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _XYZ_Gadget_Self XYZ_Gadget_Self;

MI_EXTERN_C void MI_CALL XYZ_Gadget_Load(
    XYZ_Gadget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Gadget_Unload(
    XYZ_Gadget_Self* self,
    MI_Context* context);


/*
**==============================================================================
**
** XYZ_Gadget_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class XYZ_Gadget_Class : public Instance
{
public:
    
    typedef XYZ_Gadget Self;
    
    XYZ_Gadget_Class() :
        Instance(&XYZ_Gadget_rtti)
    {
    }
    
    XYZ_Gadget_Class(
        const XYZ_Gadget* instanceName,
        bool keysOnly) :
        Instance(
            &XYZ_Gadget_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    XYZ_Gadget_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    XYZ_Gadget_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    XYZ_Gadget_Class& operator=(
        const XYZ_Gadget_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    XYZ_Gadget_Class(
        const XYZ_Gadget_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &XYZ_Gadget_rtti;
    }

    //
    // XYZ_Gadget_Class.Key
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

typedef Array<XYZ_Gadget_Class> XYZ_Gadget_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _XYZ_Gadget_h */
