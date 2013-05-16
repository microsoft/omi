/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_Base_h
#define _MSFT_Base_h

#include <MI.h>

/*
**==============================================================================
**
** MSFT_Base [MSFT_Base]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _MSFT_Base
{
    MI_Instance __instance;
    /* MSFT_Base properties */
    /*KEY*/ MI_ConstUint32Field Key;
}
MSFT_Base;

typedef struct _MSFT_Base_Ref
{
    MSFT_Base* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Base_Ref;

typedef struct _MSFT_Base_ConstRef
{
    MI_CONST MSFT_Base* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Base_ConstRef;

typedef struct _MSFT_Base_Array
{
    struct _MSFT_Base** data;
    MI_Uint32 size;
}
MSFT_Base_Array;

typedef struct _MSFT_Base_ConstArray
{
    struct _MSFT_Base MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_Base_ConstArray;

typedef struct _MSFT_Base_ArrayRef
{
    MSFT_Base_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Base_ArrayRef;

typedef struct _MSFT_Base_ConstArrayRef
{
    MSFT_Base_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Base_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_Base_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Base_Construct(
    MSFT_Base* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MSFT_Base_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Base_Clone(
    const MSFT_Base* self,
    MSFT_Base** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_Base_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_Base_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_Base_Destruct(MSFT_Base* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Base_Delete(MSFT_Base* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Base_Post(
    const MSFT_Base* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Base_Set_Key(
    MSFT_Base* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Key)->value = x;
    ((MI_Uint32Field*)&self->Key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Base_Clear_Key(
    MSFT_Base* self)
{
    memset((void*)&self->Key, 0, sizeof(self->Key));
    return MI_RESULT_OK;
}


/*
**==============================================================================
**
** MSFT_Base_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class MSFT_Base_Class : public Instance
{
public:
    
    typedef MSFT_Base Self;
    
    MSFT_Base_Class() :
        Instance(&MSFT_Base_rtti)
    {
    }
    
    MSFT_Base_Class(
        const MSFT_Base* instanceName,
        bool keysOnly) :
        Instance(
            &MSFT_Base_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MSFT_Base_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MSFT_Base_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MSFT_Base_Class& operator=(
        const MSFT_Base_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MSFT_Base_Class(
        const MSFT_Base_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &MSFT_Base_rtti;
    }

    //
    // MSFT_Base_Class.Key
    //
    
    const Field<Uint32>& Key() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<Uint32>(n);
    }
    
    void Key(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Key);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Key_value() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<Uint32>(n).value;
    }
    
    void Key_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Key);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Key_exists() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Key_clear()
    {
        const size_t n = offsetof(Self, Key);
        GetField<Uint32>(n).Clear();
    }
};

typedef Array<MSFT_Base_Class> MSFT_Base_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MSFT_Base_h */
