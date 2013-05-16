/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_Animal_h
#define _MSFT_Animal_h

#include <MI.h>
#include "MSFT_Base.h"

/*
**==============================================================================
**
** MSFT_Animal [MSFT_Animal]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _MSFT_Animal /* extends MSFT_Base */
{
    MI_Instance __instance;
    /* MSFT_Base properties */
    /*KEY*/ MI_ConstUint32Field Key;
    /* MSFT_Animal properties */
    MI_ConstStringField Species;
}
MSFT_Animal;

typedef struct _MSFT_Animal_Ref
{
    MSFT_Animal* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Animal_Ref;

typedef struct _MSFT_Animal_ConstRef
{
    MI_CONST MSFT_Animal* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Animal_ConstRef;

typedef struct _MSFT_Animal_Array
{
    struct _MSFT_Animal** data;
    MI_Uint32 size;
}
MSFT_Animal_Array;

typedef struct _MSFT_Animal_ConstArray
{
    struct _MSFT_Animal MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_Animal_ConstArray;

typedef struct _MSFT_Animal_ArrayRef
{
    MSFT_Animal_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Animal_ArrayRef;

typedef struct _MSFT_Animal_ConstArrayRef
{
    MSFT_Animal_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Animal_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_Animal_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Animal_Construct(
    MSFT_Animal* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MSFT_Animal_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Animal_Clone(
    const MSFT_Animal* self,
    MSFT_Animal** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_Animal_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_Animal_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_Animal_Destruct(MSFT_Animal* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Animal_Delete(MSFT_Animal* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Animal_Post(
    const MSFT_Animal* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Animal_Set_Key(
    MSFT_Animal* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Key)->value = x;
    ((MI_Uint32Field*)&self->Key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Animal_Clear_Key(
    MSFT_Animal* self)
{
    memset((void*)&self->Key, 0, sizeof(self->Key));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Animal_Set_Species(
    MSFT_Animal* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Animal_SetPtr_Species(
    MSFT_Animal* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Animal_Clear_Species(
    MSFT_Animal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


/*
**==============================================================================
**
** MSFT_Animal_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class MSFT_Animal_Class : public MSFT_Base_Class
{
public:
    
    typedef MSFT_Animal Self;
    
    MSFT_Animal_Class() :
        MSFT_Base_Class(&MSFT_Animal_rtti)
    {
    }
    
    MSFT_Animal_Class(
        const MSFT_Animal* instanceName,
        bool keysOnly) :
        MSFT_Base_Class(
            &MSFT_Animal_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MSFT_Animal_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        MSFT_Base_Class(clDecl, instance, keysOnly)
    {
    }
    
    MSFT_Animal_Class(
        const MI_ClassDecl* clDecl) :
        MSFT_Base_Class(clDecl)
    {
    }
    
    MSFT_Animal_Class& operator=(
        const MSFT_Animal_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MSFT_Animal_Class(
        const MSFT_Animal_Class& x) :
        MSFT_Base_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &MSFT_Animal_rtti;
    }

    //
    // MSFT_Animal_Class.Species
    //
    
    const Field<String>& Species() const
    {
        const size_t n = offsetof(Self, Species);
        return GetField<String>(n);
    }
    
    void Species(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Species);
        GetField<String>(n) = x;
    }
    
    const String& Species_value() const
    {
        const size_t n = offsetof(Self, Species);
        return GetField<String>(n).value;
    }
    
    void Species_value(const String& x)
    {
        const size_t n = offsetof(Self, Species);
        GetField<String>(n).Set(x);
    }
    
    bool Species_exists() const
    {
        const size_t n = offsetof(Self, Species);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Species_clear()
    {
        const size_t n = offsetof(Self, Species);
        GetField<String>(n).Clear();
    }
};

typedef Array<MSFT_Animal_Class> MSFT_Animal_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MSFT_Animal_h */
