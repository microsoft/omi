/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_Widget_h
#define _ABC_Widget_h

#include <MI.h>

/*
**==============================================================================
**
** ABC_Widget [ABC_Widget]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _ABC_Widget
{
    MI_Instance __instance;
    /* ABC_Widget properties */
    /*KEY*/ MI_ConstStringField Key;
    MI_ConstStringField Color;
}
ABC_Widget;

typedef struct _ABC_Widget_Ref
{
    ABC_Widget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Widget_Ref;

typedef struct _ABC_Widget_ConstRef
{
    MI_CONST ABC_Widget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Widget_ConstRef;

typedef struct _ABC_Widget_Array
{
    struct _ABC_Widget** data;
    MI_Uint32 size;
}
ABC_Widget_Array;

typedef struct _ABC_Widget_ConstArray
{
    struct _ABC_Widget MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_Widget_ConstArray;

typedef struct _ABC_Widget_ArrayRef
{
    ABC_Widget_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Widget_ArrayRef;

typedef struct _ABC_Widget_ConstArrayRef
{
    ABC_Widget_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Widget_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_Widget_rtti;


/*
**==============================================================================
**
** ABC_Widget_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class ABC_Widget_Class : public Instance
{
public:
    
    typedef ABC_Widget Self;
    
    ABC_Widget_Class() :
        Instance(&ABC_Widget_rtti)
    {
    }
    
    ABC_Widget_Class(
        const ABC_Widget* instanceName,
        bool keysOnly) :
        Instance(
            &ABC_Widget_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    ABC_Widget_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    ABC_Widget_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    ABC_Widget_Class& operator=(
        const ABC_Widget_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    ABC_Widget_Class(
        const ABC_Widget_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &ABC_Widget_rtti;
    }

    //
    // ABC_Widget_Class.Key
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
    // ABC_Widget_Class.Color
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

typedef Array<ABC_Widget_Class> ABC_Widget_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _ABC_Widget_h */
