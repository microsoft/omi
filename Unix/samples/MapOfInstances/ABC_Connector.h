/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_Connector_h
#define _ABC_Connector_h

#include <MI.h>
#include "ABC_Widget.h"
#include "ABC_Gadget.h"

/*
**==============================================================================
**
** ABC_Connector [ABC_Connector]
**
** Keys:
**    Left
**    Right
**
**==============================================================================
*/

typedef struct _ABC_Connector
{
    MI_Instance __instance;
    /* ABC_Connector properties */
    /*KEY*/ ABC_Widget_ConstRef Left;
    /*KEY*/ ABC_Gadget_ConstRef Right;
}
ABC_Connector;

typedef struct _ABC_Connector_Ref
{
    ABC_Connector* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Connector_Ref;

typedef struct _ABC_Connector_ConstRef
{
    MI_CONST ABC_Connector* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Connector_ConstRef;

typedef struct _ABC_Connector_Array
{
    struct _ABC_Connector** data;
    MI_Uint32 size;
}
ABC_Connector_Array;

typedef struct _ABC_Connector_ConstArray
{
    struct _ABC_Connector MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_Connector_ConstArray;

typedef struct _ABC_Connector_ArrayRef
{
    ABC_Connector_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Connector_ArrayRef;

typedef struct _ABC_Connector_ConstArrayRef
{
    ABC_Connector_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Connector_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_Connector_rtti;


/*
**==============================================================================
**
** ABC_Connector_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class ABC_Connector_Class : public Instance
{
public:
    
    typedef ABC_Connector Self;
    
    ABC_Connector_Class() :
        Instance(&ABC_Connector_rtti)
    {
    }
    
    ABC_Connector_Class(
        const ABC_Connector* instanceName,
        bool keysOnly) :
        Instance(
            &ABC_Connector_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    ABC_Connector_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    ABC_Connector_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    ABC_Connector_Class& operator=(
        const ABC_Connector_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    ABC_Connector_Class(
        const ABC_Connector_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &ABC_Connector_rtti;
    }

    //
    // ABC_Connector_Class.Left
    //
    
    const Field<ABC_Widget_Class>& Left() const
    {
        const size_t n = offsetof(Self, Left);
        return GetField<ABC_Widget_Class>(n);
    }
    
    void Left(const Field<ABC_Widget_Class>& x)
    {
        const size_t n = offsetof(Self, Left);
        GetField<ABC_Widget_Class>(n) = x;
    }
    
    const ABC_Widget_Class& Left_value() const
    {
        const size_t n = offsetof(Self, Left);
        return GetField<ABC_Widget_Class>(n).value;
    }
    
    void Left_value(const ABC_Widget_Class& x)
    {
        const size_t n = offsetof(Self, Left);
        GetField<ABC_Widget_Class>(n).Set(x);
    }
    
    bool Left_exists() const
    {
        const size_t n = offsetof(Self, Left);
        return GetField<ABC_Widget_Class>(n).exists ? true : false;
    }
    
    void Left_clear()
    {
        const size_t n = offsetof(Self, Left);
        GetField<ABC_Widget_Class>(n).Clear();
    }

    //
    // ABC_Connector_Class.Right
    //
    
    const Field<ABC_Gadget_Class>& Right() const
    {
        const size_t n = offsetof(Self, Right);
        return GetField<ABC_Gadget_Class>(n);
    }
    
    void Right(const Field<ABC_Gadget_Class>& x)
    {
        const size_t n = offsetof(Self, Right);
        GetField<ABC_Gadget_Class>(n) = x;
    }
    
    const ABC_Gadget_Class& Right_value() const
    {
        const size_t n = offsetof(Self, Right);
        return GetField<ABC_Gadget_Class>(n).value;
    }
    
    void Right_value(const ABC_Gadget_Class& x)
    {
        const size_t n = offsetof(Self, Right);
        GetField<ABC_Gadget_Class>(n).Set(x);
    }
    
    bool Right_exists() const
    {
        const size_t n = offsetof(Self, Right);
        return GetField<ABC_Gadget_Class>(n).exists ? true : false;
    }
    
    void Right_clear()
    {
        const size_t n = offsetof(Self, Right);
        GetField<ABC_Gadget_Class>(n).Clear();
    }
};

typedef Array<ABC_Connector_Class> ABC_Connector_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _ABC_Connector_h */
