/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_Gadget_h
#define _ABC_Gadget_h

#include <MI.h>

/*
**==============================================================================
**
** ABC_Gadget [ABC_Gadget]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _ABC_Gadget
{
    MI_Instance __instance;
    /* ABC_Gadget properties */
    /*KEY*/ MI_ConstStringField Key;
    MI_ConstStringField Color;
}
ABC_Gadget;

typedef struct _ABC_Gadget_Ref
{
    ABC_Gadget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Gadget_Ref;

typedef struct _ABC_Gadget_ConstRef
{
    MI_CONST ABC_Gadget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Gadget_ConstRef;

typedef struct _ABC_Gadget_Array
{
    struct _ABC_Gadget** data;
    MI_Uint32 size;
}
ABC_Gadget_Array;

typedef struct _ABC_Gadget_ConstArray
{
    struct _ABC_Gadget MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_Gadget_ConstArray;

typedef struct _ABC_Gadget_ArrayRef
{
    ABC_Gadget_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Gadget_ArrayRef;

typedef struct _ABC_Gadget_ConstArrayRef
{
    ABC_Gadget_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Gadget_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_Gadget_rtti;


/*
**==============================================================================
**
** ABC_Gadget_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class ABC_Gadget_Class : public Instance
{
public:
    
    typedef ABC_Gadget Self;
    
    ABC_Gadget_Class() :
        Instance(&ABC_Gadget_rtti)
    {
    }
    
    ABC_Gadget_Class(
        const ABC_Gadget* instanceName,
        bool keysOnly) :
        Instance(
            &ABC_Gadget_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    ABC_Gadget_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    ABC_Gadget_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    ABC_Gadget_Class& operator=(
        const ABC_Gadget_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    ABC_Gadget_Class(
        const ABC_Gadget_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &ABC_Gadget_rtti;
    }

    //
    // ABC_Gadget_Class.Key
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

    //
    // ABC_Gadget_Class.Color
    //
    
    const Field<String>& Color() const
    {
        const size_t n = offsetof(Self, Color);
        return GetField<String>(n);
    }
    
    void Color(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Color);
        GetField<String>(n) = x;
    }
    
    const String& Color_value() const
    {
        const size_t n = offsetof(Self, Color);
        return GetField<String>(n).value;
    }
    
    void Color_value(const String& x)
    {
        const size_t n = offsetof(Self, Color);
        GetField<String>(n).Set(x);
    }
    
    bool Color_exists() const
    {
        const size_t n = offsetof(Self, Color);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Color_clear()
    {
        const size_t n = offsetof(Self, Color);
        GetField<String>(n).Clear();
    }
};

typedef Array<ABC_Gadget_Class> ABC_Gadget_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _ABC_Gadget_h */
