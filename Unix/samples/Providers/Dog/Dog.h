/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Dog_h
#define _Dog_h

#include <MI.h>

/*
**==============================================================================
**
** Dog [XYZ_Dog]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Dog
{
    MI_Instance __instance;
    /* Dog properties */
    /*KEY*/ MI_ConstStringField Key;
    MI_ConstUint16AField Array1;
    MI_ConstUint16AField Array2;
    MI_ConstUint16AField Array3;
}
Dog;

typedef struct _Dog_Ref
{
    Dog* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Dog_Ref;

typedef struct _Dog_ConstRef
{
    MI_CONST Dog* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Dog_ConstRef;

typedef struct _Dog_Array
{
    struct _Dog** data;
    MI_Uint32 size;
}
Dog_Array;

typedef struct _Dog_ConstArray
{
    struct _Dog MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Dog_ConstArray;

typedef struct _Dog_ArrayRef
{
    Dog_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Dog_ArrayRef;

typedef struct _Dog_ConstArrayRef
{
    Dog_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Dog_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Dog_rtti;

MI_INLINE MI_Result MI_CALL Dog_Construct(
    Dog* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Dog_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Dog_Clone(
    const Dog* self,
    Dog** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Dog_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Dog_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Dog_Destruct(Dog* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Dog_Delete(Dog* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Dog_Post(
    const Dog* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Dog_Set_Key(
    Dog* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Dog_SetPtr_Key(
    Dog* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Dog_Clear_Key(
    Dog* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL Dog_Set_Array1(
    Dog* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL Dog_SetPtr_Array1(
    Dog* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Dog_Clear_Array1(
    Dog* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Dog_Set_Array2(
    Dog* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL Dog_SetPtr_Array2(
    Dog* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Dog_Clear_Array2(
    Dog* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL Dog_Set_Array3(
    Dog* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL Dog_SetPtr_Array3(
    Dog* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Dog_Clear_Array3(
    Dog* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** Dog provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Dog_Self Dog_Self;

MI_EXTERN_C void MI_CALL Dog_Load(
    Dog_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Dog_Unload(
    Dog_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Dog_EnumerateInstances(
    Dog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Dog_GetInstance(
    Dog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Dog* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Dog_CreateInstance(
    Dog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Dog* newInstance);

MI_EXTERN_C void MI_CALL Dog_ModifyInstance(
    Dog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Dog* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Dog_DeleteInstance(
    Dog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Dog* instanceName);


/*
**==============================================================================
**
** Dog_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Dog_Class : public Instance
{
public:
    
    typedef Dog Self;
    
    Dog_Class() :
        Instance(&Dog_rtti)
    {
    }
    
    Dog_Class(
        const Dog* instanceName,
        bool keysOnly) :
        Instance(
            &Dog_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Dog_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Dog_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Dog_Class& operator=(
        const Dog_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Dog_Class(
        const Dog_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Dog_rtti;
    }

    //
    // Dog_Class.Key
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
    // Dog_Class.Array1
    //
    
    const Field<Uint16A>& Array1() const
    {
        const size_t n = offsetof(Self, Array1);
        return GetField<Uint16A>(n);
    }
    
    void Array1(const Field<Uint16A>& x)
    {
        const size_t n = offsetof(Self, Array1);
        GetField<Uint16A>(n) = x;
    }
    
    const Uint16A& Array1_value() const
    {
        const size_t n = offsetof(Self, Array1);
        return GetField<Uint16A>(n).value;
    }
    
    void Array1_value(const Uint16A& x)
    {
        const size_t n = offsetof(Self, Array1);
        GetField<Uint16A>(n).Set(x);
    }
    
    bool Array1_exists() const
    {
        const size_t n = offsetof(Self, Array1);
        return GetField<Uint16A>(n).exists ? true : false;
    }
    
    void Array1_clear()
    {
        const size_t n = offsetof(Self, Array1);
        GetField<Uint16A>(n).Clear();
    }

    //
    // Dog_Class.Array2
    //
    
    const Field<Uint16A>& Array2() const
    {
        const size_t n = offsetof(Self, Array2);
        return GetField<Uint16A>(n);
    }
    
    void Array2(const Field<Uint16A>& x)
    {
        const size_t n = offsetof(Self, Array2);
        GetField<Uint16A>(n) = x;
    }
    
    const Uint16A& Array2_value() const
    {
        const size_t n = offsetof(Self, Array2);
        return GetField<Uint16A>(n).value;
    }
    
    void Array2_value(const Uint16A& x)
    {
        const size_t n = offsetof(Self, Array2);
        GetField<Uint16A>(n).Set(x);
    }
    
    bool Array2_exists() const
    {
        const size_t n = offsetof(Self, Array2);
        return GetField<Uint16A>(n).exists ? true : false;
    }
    
    void Array2_clear()
    {
        const size_t n = offsetof(Self, Array2);
        GetField<Uint16A>(n).Clear();
    }

    //
    // Dog_Class.Array3
    //
    
    const Field<Uint16A>& Array3() const
    {
        const size_t n = offsetof(Self, Array3);
        return GetField<Uint16A>(n);
    }
    
    void Array3(const Field<Uint16A>& x)
    {
        const size_t n = offsetof(Self, Array3);
        GetField<Uint16A>(n) = x;
    }
    
    const Uint16A& Array3_value() const
    {
        const size_t n = offsetof(Self, Array3);
        return GetField<Uint16A>(n).value;
    }
    
    void Array3_value(const Uint16A& x)
    {
        const size_t n = offsetof(Self, Array3);
        GetField<Uint16A>(n).Set(x);
    }
    
    bool Array3_exists() const
    {
        const size_t n = offsetof(Self, Array3);
        return GetField<Uint16A>(n).exists ? true : false;
    }
    
    void Array3_clear()
    {
        const size_t n = offsetof(Self, Array3);
        GetField<Uint16A>(n).Clear();
    }
};

typedef Array<Dog_Class> Dog_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Dog_h */
