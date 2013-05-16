/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_Tester_h
#define _OMI_Tester_h

#include <MI.h>

/*
**==============================================================================
**
** OMI_Tester [OMI_Tester]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _OMI_Tester
{
    MI_Instance __instance;
    /* OMI_Tester properties */
    /*KEY*/ MI_ConstStringField Key;
}
OMI_Tester;

typedef struct _OMI_Tester_Ref
{
    OMI_Tester* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_Tester_Ref;

typedef struct _OMI_Tester_ConstRef
{
    MI_CONST OMI_Tester* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_Tester_ConstRef;

typedef struct _OMI_Tester_Array
{
    struct _OMI_Tester** data;
    MI_Uint32 size;
}
OMI_Tester_Array;

typedef struct _OMI_Tester_ConstArray
{
    struct _OMI_Tester MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_Tester_ConstArray;

typedef struct _OMI_Tester_ArrayRef
{
    OMI_Tester_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_Tester_ArrayRef;

typedef struct _OMI_Tester_ConstArrayRef
{
    OMI_Tester_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_Tester_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_Tester_rtti;

MI_INLINE MI_Result MI_CALL OMI_Tester_Construct(
    OMI_Tester* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &OMI_Tester_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Clone(
    const OMI_Tester* self,
    OMI_Tester** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_Tester_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_Tester_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Destruct(OMI_Tester* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Delete(OMI_Tester* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Post(
    const OMI_Tester* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Set_Key(
    OMI_Tester* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_SetPtr_Key(
    OMI_Tester* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Clear_Key(
    OMI_Tester* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** OMI_Tester.Func1()
**
**==============================================================================
*/

typedef struct _OMI_Tester_Func1
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringField In1;
    /*IN*/ MI_ConstUint32Field In2;
    /*IN*/ MI_ConstBooleanField In3;
    /*OUT*/ MI_ConstStringField Out1;
    /*OUT*/ MI_ConstUint32Field Out2;
    /*OUT*/ MI_ConstBooleanField Out3;
}
OMI_Tester_Func1;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_Tester_Func1_rtti;

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Construct(
    OMI_Tester_Func1* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &OMI_Tester_Func1_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Clone(
    const OMI_Tester_Func1* self,
    OMI_Tester_Func1** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Destruct(
    OMI_Tester_Func1* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Delete(
    OMI_Tester_Func1* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Post(
    const OMI_Tester_Func1* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Set_MIReturn(
    OMI_Tester_Func1* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Clear_MIReturn(
    OMI_Tester_Func1* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Set_In1(
    OMI_Tester_Func1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_SetPtr_In1(
    OMI_Tester_Func1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Clear_In1(
    OMI_Tester_Func1* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Set_In2(
    OMI_Tester_Func1* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->In2)->value = x;
    ((MI_Uint32Field*)&self->In2)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Clear_In2(
    OMI_Tester_Func1* self)
{
    memset((void*)&self->In2, 0, sizeof(self->In2));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Set_In3(
    OMI_Tester_Func1* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->In3)->value = x;
    ((MI_BooleanField*)&self->In3)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Clear_In3(
    OMI_Tester_Func1* self)
{
    memset((void*)&self->In3, 0, sizeof(self->In3));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Set_Out1(
    OMI_Tester_Func1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_SetPtr_Out1(
    OMI_Tester_Func1* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Clear_Out1(
    OMI_Tester_Func1* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Set_Out2(
    OMI_Tester_Func1* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Out2)->value = x;
    ((MI_Uint32Field*)&self->Out2)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Clear_Out2(
    OMI_Tester_Func1* self)
{
    memset((void*)&self->Out2, 0, sizeof(self->Out2));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Set_Out3(
    OMI_Tester_Func1* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Out3)->value = x;
    ((MI_BooleanField*)&self->Out3)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_Tester_Func1_Clear_Out3(
    OMI_Tester_Func1* self)
{
    memset((void*)&self->Out3, 0, sizeof(self->Out3));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_Tester provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _OMI_Tester_Self OMI_Tester_Self;

MI_EXTERN_C void MI_CALL OMI_Tester_Load(
    OMI_Tester_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_Tester_Unload(
    OMI_Tester_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_Tester_EnumerateInstances(
    OMI_Tester_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL OMI_Tester_GetInstance(
    OMI_Tester_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_Tester* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_Tester_CreateInstance(
    OMI_Tester_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_Tester* newInstance);

MI_EXTERN_C void MI_CALL OMI_Tester_ModifyInstance(
    OMI_Tester_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_Tester* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_Tester_DeleteInstance(
    OMI_Tester_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_Tester* instanceName);

MI_EXTERN_C void MI_CALL OMI_Tester_Invoke_Func1(
    OMI_Tester_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_Tester* instanceName,
    const OMI_Tester_Func1* in);


/*
**==============================================================================
**
** OMI_Tester_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class OMI_Tester_Class : public Instance
{
public:
    
    typedef OMI_Tester Self;
    
    OMI_Tester_Class() :
        Instance(&OMI_Tester_rtti)
    {
    }
    
    OMI_Tester_Class(
        const OMI_Tester* instanceName,
        bool keysOnly) :
        Instance(
            &OMI_Tester_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    OMI_Tester_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    OMI_Tester_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    OMI_Tester_Class& operator=(
        const OMI_Tester_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    OMI_Tester_Class(
        const OMI_Tester_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &OMI_Tester_rtti;
    }

    //
    // OMI_Tester_Class.Key
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

typedef Array<OMI_Tester_Class> OMI_Tester_ClassA;

class OMI_Tester_Func1_Class : public Instance
{
public:
    
    typedef OMI_Tester_Func1 Self;
    
    OMI_Tester_Func1_Class() :
        Instance(&OMI_Tester_Func1_rtti)
    {
    }
    
    OMI_Tester_Func1_Class(
        const OMI_Tester_Func1* instanceName,
        bool keysOnly) :
        Instance(
            &OMI_Tester_Func1_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    OMI_Tester_Func1_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    OMI_Tester_Func1_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    OMI_Tester_Func1_Class& operator=(
        const OMI_Tester_Func1_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    OMI_Tester_Func1_Class(
        const OMI_Tester_Func1_Class& x) :
        Instance(x)
    {
    }

    //
    // OMI_Tester_Func1_Class.MIReturn
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
    // OMI_Tester_Func1_Class.In1
    //
    
    const Field<String>& In1() const
    {
        const size_t n = offsetof(Self, In1);
        return GetField<String>(n);
    }
    
    void In1(const Field<String>& x)
    {
        const size_t n = offsetof(Self, In1);
        GetField<String>(n) = x;
    }
    
    const String& In1_value() const
    {
        const size_t n = offsetof(Self, In1);
        return GetField<String>(n).value;
    }
    
    void In1_value(const String& x)
    {
        const size_t n = offsetof(Self, In1);
        GetField<String>(n).Set(x);
    }
    
    bool In1_exists() const
    {
        const size_t n = offsetof(Self, In1);
        return GetField<String>(n).exists ? true : false;
    }
    
    void In1_clear()
    {
        const size_t n = offsetof(Self, In1);
        GetField<String>(n).Clear();
    }

    //
    // OMI_Tester_Func1_Class.In2
    //
    
    const Field<Uint32>& In2() const
    {
        const size_t n = offsetof(Self, In2);
        return GetField<Uint32>(n);
    }
    
    void In2(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, In2);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& In2_value() const
    {
        const size_t n = offsetof(Self, In2);
        return GetField<Uint32>(n).value;
    }
    
    void In2_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, In2);
        GetField<Uint32>(n).Set(x);
    }
    
    bool In2_exists() const
    {
        const size_t n = offsetof(Self, In2);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void In2_clear()
    {
        const size_t n = offsetof(Self, In2);
        GetField<Uint32>(n).Clear();
    }

    //
    // OMI_Tester_Func1_Class.In3
    //
    
    const Field<Boolean>& In3() const
    {
        const size_t n = offsetof(Self, In3);
        return GetField<Boolean>(n);
    }
    
    void In3(const Field<Boolean>& x)
    {
        const size_t n = offsetof(Self, In3);
        GetField<Boolean>(n) = x;
    }
    
    const Boolean& In3_value() const
    {
        const size_t n = offsetof(Self, In3);
        return GetField<Boolean>(n).value;
    }
    
    void In3_value(const Boolean& x)
    {
        const size_t n = offsetof(Self, In3);
        GetField<Boolean>(n).Set(x);
    }
    
    bool In3_exists() const
    {
        const size_t n = offsetof(Self, In3);
        return GetField<Boolean>(n).exists ? true : false;
    }
    
    void In3_clear()
    {
        const size_t n = offsetof(Self, In3);
        GetField<Boolean>(n).Clear();
    }

    //
    // OMI_Tester_Func1_Class.Out1
    //
    
    const Field<String>& Out1() const
    {
        const size_t n = offsetof(Self, Out1);
        return GetField<String>(n);
    }
    
    void Out1(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Out1);
        GetField<String>(n) = x;
    }
    
    const String& Out1_value() const
    {
        const size_t n = offsetof(Self, Out1);
        return GetField<String>(n).value;
    }
    
    void Out1_value(const String& x)
    {
        const size_t n = offsetof(Self, Out1);
        GetField<String>(n).Set(x);
    }
    
    bool Out1_exists() const
    {
        const size_t n = offsetof(Self, Out1);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Out1_clear()
    {
        const size_t n = offsetof(Self, Out1);
        GetField<String>(n).Clear();
    }

    //
    // OMI_Tester_Func1_Class.Out2
    //
    
    const Field<Uint32>& Out2() const
    {
        const size_t n = offsetof(Self, Out2);
        return GetField<Uint32>(n);
    }
    
    void Out2(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Out2);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Out2_value() const
    {
        const size_t n = offsetof(Self, Out2);
        return GetField<Uint32>(n).value;
    }
    
    void Out2_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Out2);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Out2_exists() const
    {
        const size_t n = offsetof(Self, Out2);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Out2_clear()
    {
        const size_t n = offsetof(Self, Out2);
        GetField<Uint32>(n).Clear();
    }

    //
    // OMI_Tester_Func1_Class.Out3
    //
    
    const Field<Boolean>& Out3() const
    {
        const size_t n = offsetof(Self, Out3);
        return GetField<Boolean>(n);
    }
    
    void Out3(const Field<Boolean>& x)
    {
        const size_t n = offsetof(Self, Out3);
        GetField<Boolean>(n) = x;
    }
    
    const Boolean& Out3_value() const
    {
        const size_t n = offsetof(Self, Out3);
        return GetField<Boolean>(n).value;
    }
    
    void Out3_value(const Boolean& x)
    {
        const size_t n = offsetof(Self, Out3);
        GetField<Boolean>(n).Set(x);
    }
    
    bool Out3_exists() const
    {
        const size_t n = offsetof(Self, Out3);
        return GetField<Boolean>(n).exists ? true : false;
    }
    
    void Out3_clear()
    {
        const size_t n = offsetof(Self, Out3);
        GetField<Boolean>(n).Clear();
    }
};

typedef Array<OMI_Tester_Func1_Class> OMI_Tester_Func1_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _OMI_Tester_h */
