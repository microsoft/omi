/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_SmallNumber_h
#define _X_SmallNumber_h

#include <MI.h>
#include "X_Number.h"

/*
**==============================================================================
**
** X_SmallNumber [X_SmallNumber]
**
** Keys:
**    Number
**
**==============================================================================
*/

typedef struct _X_SmallNumber /* extends X_Number */
{
    MI_Instance __instance;
    /* X_ManagedElement properties */
    MI_ConstStringField Description;
    /* X_Number properties */
    /*KEY*/ MI_ConstUint64Field Number;
    /* X_SmallNumber properties */
    MI_ConstStringField SpelledNumber;
}
X_SmallNumber;

typedef struct _X_SmallNumber_Ref
{
    X_SmallNumber* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_SmallNumber_Ref;

typedef struct _X_SmallNumber_ConstRef
{
    MI_CONST X_SmallNumber* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_SmallNumber_ConstRef;

typedef struct _X_SmallNumber_Array
{
    struct _X_SmallNumber** data;
    MI_Uint32 size;
}
X_SmallNumber_Array;

typedef struct _X_SmallNumber_ConstArray
{
    struct _X_SmallNumber MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_SmallNumber_ConstArray;

typedef struct _X_SmallNumber_ArrayRef
{
    X_SmallNumber_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_SmallNumber_ArrayRef;

typedef struct _X_SmallNumber_ConstArrayRef
{
    X_SmallNumber_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_SmallNumber_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_SmallNumber_rtti;

MI_INLINE MI_Result MI_CALL X_SmallNumber_Construct(
    X_SmallNumber* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_SmallNumber_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_Clone(
    const X_SmallNumber* self,
    X_SmallNumber** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_SmallNumber_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_SmallNumber_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_Destruct(X_SmallNumber* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_Delete(X_SmallNumber* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_Post(
    const X_SmallNumber* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_Set_Description(
    X_SmallNumber* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_SetPtr_Description(
    X_SmallNumber* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_Clear_Description(
    X_SmallNumber* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_Set_Number(
    X_SmallNumber* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Number)->value = x;
    ((MI_Uint64Field*)&self->Number)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_Clear_Number(
    X_SmallNumber* self)
{
    memset((void*)&self->Number, 0, sizeof(self->Number));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_Set_SpelledNumber(
    X_SmallNumber* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_SetPtr_SpelledNumber(
    X_SmallNumber* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_Clear_SpelledNumber(
    X_SmallNumber* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** X_SmallNumber.SpellNumber()
**
**==============================================================================
*/

typedef struct _X_SmallNumber_SpellNumber
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
MI_ConstUint64Field num;
}
X_SmallNumber_SpellNumber;

MI_EXTERN_C MI_CONST MI_MethodDecl X_SmallNumber_SpellNumber_rtti;

MI_INLINE MI_Result MI_CALL X_SmallNumber_SpellNumber_Construct(
    X_SmallNumber_SpellNumber* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &X_SmallNumber_SpellNumber_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_SpellNumber_Clone(
    const X_SmallNumber_SpellNumber* self,
    X_SmallNumber_SpellNumber** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_SpellNumber_Destruct(
    X_SmallNumber_SpellNumber* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_SpellNumber_Delete(
    X_SmallNumber_SpellNumber* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_SpellNumber_Post(
    const X_SmallNumber_SpellNumber* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_SpellNumber_Set_MIReturn(
    X_SmallNumber_SpellNumber* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_SpellNumber_SetPtr_MIReturn(
    X_SmallNumber_SpellNumber* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_SpellNumber_Clear_MIReturn(
    X_SmallNumber_SpellNumber* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_SpellNumber_Set_num(
    X_SmallNumber_SpellNumber* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->num)->value = x;
    ((MI_Uint64Field*)&self->num)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_SpellNumber_Clear_num(
    X_SmallNumber_SpellNumber* self)
{
    memset((void*)&self->num, 0, sizeof(self->num));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** X_SmallNumber.GetFactors()
**
**==============================================================================
*/

typedef struct _X_SmallNumber_GetFactors
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ MI_ConstUint64AField numbers;
    /*OUT*/ MI_ConstStringAField spelled_numbers;
}
X_SmallNumber_GetFactors;

MI_EXTERN_C MI_CONST MI_MethodDecl X_SmallNumber_GetFactors_rtti;

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_Construct(
    X_SmallNumber_GetFactors* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &X_SmallNumber_GetFactors_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_Clone(
    const X_SmallNumber_GetFactors* self,
    X_SmallNumber_GetFactors** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_Destruct(
    X_SmallNumber_GetFactors* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_Delete(
    X_SmallNumber_GetFactors* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_Post(
    const X_SmallNumber_GetFactors* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_Set_MIReturn(
    X_SmallNumber_GetFactors* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_Clear_MIReturn(
    X_SmallNumber_GetFactors* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_Set_numbers(
    X_SmallNumber_GetFactors* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_SetPtr_numbers(
    X_SmallNumber_GetFactors* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_Clear_numbers(
    X_SmallNumber_GetFactors* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_Set_spelled_numbers(
    X_SmallNumber_GetFactors* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_SetPtr_spelled_numbers(
    X_SmallNumber_GetFactors* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SmallNumber_GetFactors_Clear_spelled_numbers(
    X_SmallNumber_GetFactors* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** X_SmallNumber provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_SmallNumber_Self X_SmallNumber_Self;

MI_EXTERN_C void MI_CALL X_SmallNumber_Load(
    X_SmallNumber_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_SmallNumber_Unload(
    X_SmallNumber_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_SmallNumber_EnumerateInstances(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_SmallNumber_GetInstance(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SmallNumber* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_SmallNumber_CreateInstance(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SmallNumber* newInstance);

MI_EXTERN_C void MI_CALL X_SmallNumber_ModifyInstance(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SmallNumber* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_SmallNumber_DeleteInstance(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SmallNumber* instanceName);

MI_EXTERN_C void MI_CALL X_SmallNumber_Invoke_SpellNumber(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_SmallNumber* instanceName,
    const X_SmallNumber_SpellNumber* in);

MI_EXTERN_C void MI_CALL X_SmallNumber_Invoke_GetFactors(
    X_SmallNumber_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const X_SmallNumber* instanceName,
    const X_SmallNumber_GetFactors* in);


/*
**==============================================================================
**
** X_SmallNumber_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_SmallNumber_Class : public X_Number_Class
{
public:
    
    typedef X_SmallNumber Self;
    
    X_SmallNumber_Class() :
        X_Number_Class(&X_SmallNumber_rtti)
    {
    }
    
    X_SmallNumber_Class(
        const X_SmallNumber* instanceName,
        bool keysOnly) :
        X_Number_Class(
            &X_SmallNumber_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_SmallNumber_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        X_Number_Class(clDecl, instance, keysOnly)
    {
    }
    
    X_SmallNumber_Class(
        const MI_ClassDecl* clDecl) :
        X_Number_Class(clDecl)
    {
    }
    
    X_SmallNumber_Class& operator=(
        const X_SmallNumber_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_SmallNumber_Class(
        const X_SmallNumber_Class& x) :
        X_Number_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_SmallNumber_rtti;
    }

    //
    // X_SmallNumber_Class.SpelledNumber
    //
    
    const Field<String>& SpelledNumber() const
    {
        const size_t n = offsetof(Self, SpelledNumber);
        return GetField<String>(n);
    }
    
    void SpelledNumber(const Field<String>& x)
    {
        const size_t n = offsetof(Self, SpelledNumber);
        GetField<String>(n) = x;
    }
    
    const String& SpelledNumber_value() const
    {
        const size_t n = offsetof(Self, SpelledNumber);
        return GetField<String>(n).value;
    }
    
    void SpelledNumber_value(const String& x)
    {
        const size_t n = offsetof(Self, SpelledNumber);
        GetField<String>(n).Set(x);
    }
    
    bool SpelledNumber_exists() const
    {
        const size_t n = offsetof(Self, SpelledNumber);
        return GetField<String>(n).exists ? true : false;
    }
    
    void SpelledNumber_clear()
    {
        const size_t n = offsetof(Self, SpelledNumber);
        GetField<String>(n).Clear();
    }
};

typedef Array<X_SmallNumber_Class> X_SmallNumber_ClassA;

class X_SmallNumber_SpellNumber_Class : public Instance
{
public:
    
    typedef X_SmallNumber_SpellNumber Self;
    
    X_SmallNumber_SpellNumber_Class() :
        Instance(&X_SmallNumber_SpellNumber_rtti)
    {
    }
    
    X_SmallNumber_SpellNumber_Class(
        const X_SmallNumber_SpellNumber* instanceName,
        bool keysOnly) :
        Instance(
            &X_SmallNumber_SpellNumber_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_SmallNumber_SpellNumber_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_SmallNumber_SpellNumber_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_SmallNumber_SpellNumber_Class& operator=(
        const X_SmallNumber_SpellNumber_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_SmallNumber_SpellNumber_Class(
        const X_SmallNumber_SpellNumber_Class& x) :
        Instance(x)
    {
    }

    //
    // X_SmallNumber_SpellNumber_Class.MIReturn
    //
    
    const Field<String>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n);
    }
    
    void MIReturn(const Field<String>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n) = x;
    }
    
    const String& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n).value;
    }
    
    void MIReturn_value(const String& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n).Clear();
    }

    //
    // X_SmallNumber_SpellNumber_Class.num
    //
    
    const Field<Uint64>& num() const
    {
        const size_t n = offsetof(Self, num);
        return GetField<Uint64>(n);
    }
    
    void num(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, num);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& num_value() const
    {
        const size_t n = offsetof(Self, num);
        return GetField<Uint64>(n).value;
    }
    
    void num_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, num);
        GetField<Uint64>(n).Set(x);
    }
    
    bool num_exists() const
    {
        const size_t n = offsetof(Self, num);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void num_clear()
    {
        const size_t n = offsetof(Self, num);
        GetField<Uint64>(n).Clear();
    }
};

typedef Array<X_SmallNumber_SpellNumber_Class> X_SmallNumber_SpellNumber_ClassA;

class X_SmallNumber_GetFactors_Class : public Instance
{
public:
    
    typedef X_SmallNumber_GetFactors Self;
    
    X_SmallNumber_GetFactors_Class() :
        Instance(&X_SmallNumber_GetFactors_rtti)
    {
    }
    
    X_SmallNumber_GetFactors_Class(
        const X_SmallNumber_GetFactors* instanceName,
        bool keysOnly) :
        Instance(
            &X_SmallNumber_GetFactors_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_SmallNumber_GetFactors_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_SmallNumber_GetFactors_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_SmallNumber_GetFactors_Class& operator=(
        const X_SmallNumber_GetFactors_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_SmallNumber_GetFactors_Class(
        const X_SmallNumber_GetFactors_Class& x) :
        Instance(x)
    {
    }

    //
    // X_SmallNumber_GetFactors_Class.MIReturn
    //
    
    const Field<Uint32>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n);
    }
    
    void MIReturn(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n).value;
    }
    
    void MIReturn_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n).Clear();
    }

    //
    // X_SmallNumber_GetFactors_Class.numbers
    //
    
    const Field<Uint64A>& numbers() const
    {
        const size_t n = offsetof(Self, numbers);
        return GetField<Uint64A>(n);
    }
    
    void numbers(const Field<Uint64A>& x)
    {
        const size_t n = offsetof(Self, numbers);
        GetField<Uint64A>(n) = x;
    }
    
    const Uint64A& numbers_value() const
    {
        const size_t n = offsetof(Self, numbers);
        return GetField<Uint64A>(n).value;
    }
    
    void numbers_value(const Uint64A& x)
    {
        const size_t n = offsetof(Self, numbers);
        GetField<Uint64A>(n).Set(x);
    }
    
    bool numbers_exists() const
    {
        const size_t n = offsetof(Self, numbers);
        return GetField<Uint64A>(n).exists ? true : false;
    }
    
    void numbers_clear()
    {
        const size_t n = offsetof(Self, numbers);
        GetField<Uint64A>(n).Clear();
    }

    //
    // X_SmallNumber_GetFactors_Class.spelled_numbers
    //
    
    const Field<StringA>& spelled_numbers() const
    {
        const size_t n = offsetof(Self, spelled_numbers);
        return GetField<StringA>(n);
    }
    
    void spelled_numbers(const Field<StringA>& x)
    {
        const size_t n = offsetof(Self, spelled_numbers);
        GetField<StringA>(n) = x;
    }
    
    const StringA& spelled_numbers_value() const
    {
        const size_t n = offsetof(Self, spelled_numbers);
        return GetField<StringA>(n).value;
    }
    
    void spelled_numbers_value(const StringA& x)
    {
        const size_t n = offsetof(Self, spelled_numbers);
        GetField<StringA>(n).Set(x);
    }
    
    bool spelled_numbers_exists() const
    {
        const size_t n = offsetof(Self, spelled_numbers);
        return GetField<StringA>(n).exists ? true : false;
    }
    
    void spelled_numbers_clear()
    {
        const size_t n = offsetof(Self, spelled_numbers);
        GetField<StringA>(n).Clear();
    }
};

typedef Array<X_SmallNumber_GetFactors_Class> X_SmallNumber_GetFactors_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_SmallNumber_h */
