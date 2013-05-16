/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Main_h
#define _Main_h

#include <MI.h>

/*
**==============================================================================
**
** Main [Demo_Main]
**
** Keys:
**    SN
**
**==============================================================================
*/

typedef struct _Main
{
    MI_Instance __instance;
    /* Main properties */
    /*KEY*/ MI_ConstUint32Field SN;
    MI_ConstStringField Name;
}
Main;

typedef struct _Main_Ref
{
    Main* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Main_Ref;

typedef struct _Main_ConstRef
{
    MI_CONST Main* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Main_ConstRef;

typedef struct _Main_Array
{
    struct _Main** data;
    MI_Uint32 size;
}
Main_Array;

typedef struct _Main_ConstArray
{
    struct _Main MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Main_ConstArray;

typedef struct _Main_ArrayRef
{
    Main_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Main_ArrayRef;

typedef struct _Main_ConstArrayRef
{
    Main_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Main_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Main_rtti;

MI_INLINE MI_Result MI_CALL Main_Construct(
    Main* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Main_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_Clone(
    const Main* self,
    Main** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Main_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Main_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Main_Destruct(Main* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_Delete(Main* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_Post(
    const Main* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_Set_SN(
    Main* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->SN)->value = x;
    ((MI_Uint32Field*)&self->SN)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Main_Clear_SN(
    Main* self)
{
    memset((void*)&self->SN, 0, sizeof(self->SN));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Main_Set_Name(
    Main* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Main_SetPtr_Name(
    Main* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Main_Clear_Name(
    Main* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** Main.ChangeState()
**
**==============================================================================
*/

typedef struct _Main_ChangeState
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field NewState;
    /*OUT*/ MI_ConstUint32Field OldState;
}
Main_ChangeState;

MI_EXTERN_C MI_CONST MI_MethodDecl Main_ChangeState_rtti;

MI_INLINE MI_Result MI_CALL Main_ChangeState_Construct(
    Main_ChangeState* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &Main_ChangeState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_ChangeState_Clone(
    const Main_ChangeState* self,
    Main_ChangeState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Main_ChangeState_Destruct(
    Main_ChangeState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_ChangeState_Delete(
    Main_ChangeState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_ChangeState_Post(
    const Main_ChangeState* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_ChangeState_Set_MIReturn(
    Main_ChangeState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Main_ChangeState_Clear_MIReturn(
    Main_ChangeState* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Main_ChangeState_Set_NewState(
    Main_ChangeState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->NewState)->value = x;
    ((MI_Uint32Field*)&self->NewState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Main_ChangeState_Clear_NewState(
    Main_ChangeState* self)
{
    memset((void*)&self->NewState, 0, sizeof(self->NewState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Main_ChangeState_Set_OldState(
    Main_ChangeState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->OldState)->value = x;
    ((MI_Uint32Field*)&self->OldState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Main_ChangeState_Clear_OldState(
    Main_ChangeState* self)
{
    memset((void*)&self->OldState, 0, sizeof(self->OldState));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Main.HelloWorld()
**
**==============================================================================
*/

typedef struct _Main_HelloWorld
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field NewValue;
}
Main_HelloWorld;

MI_EXTERN_C MI_CONST MI_MethodDecl Main_HelloWorld_rtti;

MI_INLINE MI_Result MI_CALL Main_HelloWorld_Construct(
    Main_HelloWorld* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &Main_HelloWorld_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_HelloWorld_Clone(
    const Main_HelloWorld* self,
    Main_HelloWorld** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL Main_HelloWorld_Destruct(
    Main_HelloWorld* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_HelloWorld_Delete(
    Main_HelloWorld* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_HelloWorld_Post(
    const Main_HelloWorld* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Main_HelloWorld_Set_MIReturn(
    Main_HelloWorld* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Main_HelloWorld_Clear_MIReturn(
    Main_HelloWorld* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Main_HelloWorld_Set_NewValue(
    Main_HelloWorld* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->NewValue)->value = x;
    ((MI_Uint32Field*)&self->NewValue)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Main_HelloWorld_Clear_NewValue(
    Main_HelloWorld* self)
{
    memset((void*)&self->NewValue, 0, sizeof(self->NewValue));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Main provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Main_Self Main_Self;

MI_EXTERN_C void MI_CALL Main_Load(
    Main_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Main_Unload(
    Main_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Main_EnumerateInstances(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Main_GetInstance(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Main_CreateInstance(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* newInstance);

MI_EXTERN_C void MI_CALL Main_ModifyInstance(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Main_DeleteInstance(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Main* instanceName);

MI_EXTERN_C void MI_CALL Main_Invoke_ChangeState(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Main* instanceName,
    const Main_ChangeState* in);

MI_EXTERN_C void MI_CALL Main_Invoke_HelloWorld(
    Main_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Main* instanceName,
    const Main_HelloWorld* in);


/*
**==============================================================================
**
** Main_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Main_Class : public Instance
{
public:
    
    typedef Main Self;
    
    Main_Class() :
        Instance(&Main_rtti)
    {
    }
    
    Main_Class(
        const Main* instanceName,
        bool keysOnly) :
        Instance(
            &Main_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Main_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Main_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Main_Class& operator=(
        const Main_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Main_Class(
        const Main_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Main_rtti;
    }

    //
    // Main_Class.SN
    //
    
    const Field<Uint32>& SN() const
    {
        const size_t n = offsetof(Self, SN);
        return GetField<Uint32>(n);
    }
    
    void SN(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, SN);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& SN_value() const
    {
        const size_t n = offsetof(Self, SN);
        return GetField<Uint32>(n).value;
    }
    
    void SN_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, SN);
        GetField<Uint32>(n).Set(x);
    }
    
    bool SN_exists() const
    {
        const size_t n = offsetof(Self, SN);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void SN_clear()
    {
        const size_t n = offsetof(Self, SN);
        GetField<Uint32>(n).Clear();
    }

    //
    // Main_Class.Name
    //
    
    const Field<String>& Name() const
    {
        const size_t n = offsetof(Self, Name);
        return GetField<String>(n);
    }
    
    void Name(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Name);
        GetField<String>(n) = x;
    }
    
    const String& Name_value() const
    {
        const size_t n = offsetof(Self, Name);
        return GetField<String>(n).value;
    }
    
    void Name_value(const String& x)
    {
        const size_t n = offsetof(Self, Name);
        GetField<String>(n).Set(x);
    }
    
    bool Name_exists() const
    {
        const size_t n = offsetof(Self, Name);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Name_clear()
    {
        const size_t n = offsetof(Self, Name);
        GetField<String>(n).Clear();
    }
};

typedef Array<Main_Class> Main_ClassA;

class Main_ChangeState_Class : public Instance
{
public:
    
    typedef Main_ChangeState Self;
    
    Main_ChangeState_Class() :
        Instance(&Main_ChangeState_rtti)
    {
    }
    
    Main_ChangeState_Class(
        const Main_ChangeState* instanceName,
        bool keysOnly) :
        Instance(
            &Main_ChangeState_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Main_ChangeState_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Main_ChangeState_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Main_ChangeState_Class& operator=(
        const Main_ChangeState_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Main_ChangeState_Class(
        const Main_ChangeState_Class& x) :
        Instance(x)
    {
    }

    //
    // Main_ChangeState_Class.MIReturn
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
    // Main_ChangeState_Class.NewState
    //
    
    const Field<Uint32>& NewState() const
    {
        const size_t n = offsetof(Self, NewState);
        return GetField<Uint32>(n);
    }
    
    void NewState(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, NewState);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& NewState_value() const
    {
        const size_t n = offsetof(Self, NewState);
        return GetField<Uint32>(n).value;
    }
    
    void NewState_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, NewState);
        GetField<Uint32>(n).Set(x);
    }
    
    bool NewState_exists() const
    {
        const size_t n = offsetof(Self, NewState);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void NewState_clear()
    {
        const size_t n = offsetof(Self, NewState);
        GetField<Uint32>(n).Clear();
    }

    //
    // Main_ChangeState_Class.OldState
    //
    
    const Field<Uint32>& OldState() const
    {
        const size_t n = offsetof(Self, OldState);
        return GetField<Uint32>(n);
    }
    
    void OldState(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, OldState);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& OldState_value() const
    {
        const size_t n = offsetof(Self, OldState);
        return GetField<Uint32>(n).value;
    }
    
    void OldState_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, OldState);
        GetField<Uint32>(n).Set(x);
    }
    
    bool OldState_exists() const
    {
        const size_t n = offsetof(Self, OldState);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void OldState_clear()
    {
        const size_t n = offsetof(Self, OldState);
        GetField<Uint32>(n).Clear();
    }
};

typedef Array<Main_ChangeState_Class> Main_ChangeState_ClassA;

class Main_HelloWorld_Class : public Instance
{
public:
    
    typedef Main_HelloWorld Self;
    
    Main_HelloWorld_Class() :
        Instance(&Main_HelloWorld_rtti)
    {
    }
    
    Main_HelloWorld_Class(
        const Main_HelloWorld* instanceName,
        bool keysOnly) :
        Instance(
            &Main_HelloWorld_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Main_HelloWorld_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Main_HelloWorld_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Main_HelloWorld_Class& operator=(
        const Main_HelloWorld_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Main_HelloWorld_Class(
        const Main_HelloWorld_Class& x) :
        Instance(x)
    {
    }

    //
    // Main_HelloWorld_Class.MIReturn
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
    // Main_HelloWorld_Class.NewValue
    //
    
    const Field<Uint32>& NewValue() const
    {
        const size_t n = offsetof(Self, NewValue);
        return GetField<Uint32>(n);
    }
    
    void NewValue(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, NewValue);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& NewValue_value() const
    {
        const size_t n = offsetof(Self, NewValue);
        return GetField<Uint32>(n).value;
    }
    
    void NewValue_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, NewValue);
        GetField<Uint32>(n).Set(x);
    }
    
    bool NewValue_exists() const
    {
        const size_t n = offsetof(Self, NewValue);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void NewValue_clear()
    {
        const size_t n = offsetof(Self, NewValue);
        GetField<Uint32>(n).Clear();
    }
};

typedef Array<Main_HelloWorld_Class> Main_HelloWorld_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Main_h */
