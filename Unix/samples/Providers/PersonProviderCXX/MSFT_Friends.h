/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_Friends_h
#define _MSFT_Friends_h

#include <MI.h>
#include "MSFT_Person.h"

/*
**==============================================================================
**
** MSFT_Friends [MSFT_Friends]
**
** Keys:
**    Left
**    Right
**
**==============================================================================
*/

typedef struct _MSFT_Friends
{
    MI_Instance __instance;
    /* MSFT_Friends properties */
    /*KEY*/ MSFT_Person_ConstRef Left;
    /*KEY*/ MSFT_Person_ConstRef Right;
}
MSFT_Friends;

typedef struct _MSFT_Friends_Ref
{
    MSFT_Friends* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Friends_Ref;

typedef struct _MSFT_Friends_ConstRef
{
    MI_CONST MSFT_Friends* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Friends_ConstRef;

typedef struct _MSFT_Friends_Array
{
    struct _MSFT_Friends** data;
    MI_Uint32 size;
}
MSFT_Friends_Array;

typedef struct _MSFT_Friends_ConstArray
{
    struct _MSFT_Friends MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_Friends_ConstArray;

typedef struct _MSFT_Friends_ArrayRef
{
    MSFT_Friends_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Friends_ArrayRef;

typedef struct _MSFT_Friends_ConstArrayRef
{
    MSFT_Friends_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Friends_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_Friends_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Friends_Construct(
    MSFT_Friends* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MSFT_Friends_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_Clone(
    const MSFT_Friends* self,
    MSFT_Friends** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_Friends_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_Friends_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_Destruct(MSFT_Friends* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_Delete(MSFT_Friends* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_Post(
    const MSFT_Friends* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_Set_Left(
    MSFT_Friends* self,
    const MSFT_Person* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_SetPtr_Left(
    MSFT_Friends* self,
    const MSFT_Person* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_Clear_Left(
    MSFT_Friends* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_Set_Right(
    MSFT_Friends* self,
    const MSFT_Person* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_SetPtr_Right(
    MSFT_Friends* self,
    const MSFT_Person* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_Clear_Right(
    MSFT_Friends* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_Friends.AddFriend()
**
**==============================================================================
*/

typedef struct _MSFT_Friends_AddFriend
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_Person_ConstRef Friend;
}
MSFT_Friends_AddFriend;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_Friends_AddFriend_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriend_Construct(
    MSFT_Friends_AddFriend* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MSFT_Friends_AddFriend_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriend_Clone(
    const MSFT_Friends_AddFriend* self,
    MSFT_Friends_AddFriend** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriend_Destruct(
    MSFT_Friends_AddFriend* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriend_Delete(
    MSFT_Friends_AddFriend* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriend_Post(
    const MSFT_Friends_AddFriend* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriend_Set_MIReturn(
    MSFT_Friends_AddFriend* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriend_Clear_MIReturn(
    MSFT_Friends_AddFriend* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriend_Set_Friend(
    MSFT_Friends_AddFriend* self,
    const MSFT_Person* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriend_SetPtr_Friend(
    MSFT_Friends_AddFriend* self,
    const MSFT_Person* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriend_Clear_Friend(
    MSFT_Friends_AddFriend* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_Friends.AddFriends()
**
**==============================================================================
*/

typedef struct _MSFT_Friends_AddFriends
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MSFT_Person_ConstArrayRef Friends;
}
MSFT_Friends_AddFriends;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_Friends_AddFriends_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriends_Construct(
    MSFT_Friends_AddFriends* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MSFT_Friends_AddFriends_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriends_Clone(
    const MSFT_Friends_AddFriends* self,
    MSFT_Friends_AddFriends** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriends_Destruct(
    MSFT_Friends_AddFriends* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriends_Delete(
    MSFT_Friends_AddFriends* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriends_Post(
    const MSFT_Friends_AddFriends* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriends_Set_MIReturn(
    MSFT_Friends_AddFriends* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriends_Clear_MIReturn(
    MSFT_Friends_AddFriends* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriends_Set_Friends(
    MSFT_Friends_AddFriends* self,
    const MSFT_Person* const* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriends_SetPtr_Friends(
    MSFT_Friends_AddFriends* self,
    const MSFT_Person* const* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Friends_AddFriends_Clear_Friends(
    MSFT_Friends_AddFriends* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_Friends provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_Friends_Self MSFT_Friends_Self;

MI_EXTERN_C void MI_CALL MSFT_Friends_Load(
    MSFT_Friends_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_Friends_Unload(
    MSFT_Friends_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_Friends_EnumerateInstances(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_Friends_GetInstance(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Friends* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_Friends_CreateInstance(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Friends* newInstance);

MI_EXTERN_C void MI_CALL MSFT_Friends_ModifyInstance(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Friends* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_Friends_DeleteInstance(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Friends* instanceName);

MI_EXTERN_C void MI_CALL MSFT_Friends_AssociatorInstances(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_Friends_ReferenceInstances(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_Friends_Invoke_AddFriend(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Friends* instanceName,
    const MSFT_Friends_AddFriend* in);

MI_EXTERN_C void MI_CALL MSFT_Friends_Invoke_AddFriends(
    MSFT_Friends_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Friends* instanceName,
    const MSFT_Friends_AddFriends* in);


/*
**==============================================================================
**
** MSFT_Friends_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class MSFT_Friends_Class : public Instance
{
public:
    
    typedef MSFT_Friends Self;
    
    MSFT_Friends_Class() :
        Instance(&MSFT_Friends_rtti)
    {
    }
    
    MSFT_Friends_Class(
        const MSFT_Friends* instanceName,
        bool keysOnly) :
        Instance(
            &MSFT_Friends_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MSFT_Friends_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MSFT_Friends_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MSFT_Friends_Class& operator=(
        const MSFT_Friends_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MSFT_Friends_Class(
        const MSFT_Friends_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &MSFT_Friends_rtti;
    }

    //
    // MSFT_Friends_Class.Left
    //
    
    const Field<MSFT_Person_Class>& Left() const
    {
        const size_t n = offsetof(Self, Left);
        return GetField<MSFT_Person_Class>(n);
    }
    
    void Left(const Field<MSFT_Person_Class>& x)
    {
        const size_t n = offsetof(Self, Left);
        GetField<MSFT_Person_Class>(n) = x;
    }
    
    const MSFT_Person_Class& Left_value() const
    {
        const size_t n = offsetof(Self, Left);
        return GetField<MSFT_Person_Class>(n).value;
    }
    
    void Left_value(const MSFT_Person_Class& x)
    {
        const size_t n = offsetof(Self, Left);
        GetField<MSFT_Person_Class>(n).Set(x);
    }
    
    bool Left_exists() const
    {
        const size_t n = offsetof(Self, Left);
        return GetField<MSFT_Person_Class>(n).exists ? true : false;
    }
    
    void Left_clear()
    {
        const size_t n = offsetof(Self, Left);
        GetField<MSFT_Person_Class>(n).Clear();
    }

    //
    // MSFT_Friends_Class.Right
    //
    
    const Field<MSFT_Person_Class>& Right() const
    {
        const size_t n = offsetof(Self, Right);
        return GetField<MSFT_Person_Class>(n);
    }
    
    void Right(const Field<MSFT_Person_Class>& x)
    {
        const size_t n = offsetof(Self, Right);
        GetField<MSFT_Person_Class>(n) = x;
    }
    
    const MSFT_Person_Class& Right_value() const
    {
        const size_t n = offsetof(Self, Right);
        return GetField<MSFT_Person_Class>(n).value;
    }
    
    void Right_value(const MSFT_Person_Class& x)
    {
        const size_t n = offsetof(Self, Right);
        GetField<MSFT_Person_Class>(n).Set(x);
    }
    
    bool Right_exists() const
    {
        const size_t n = offsetof(Self, Right);
        return GetField<MSFT_Person_Class>(n).exists ? true : false;
    }
    
    void Right_clear()
    {
        const size_t n = offsetof(Self, Right);
        GetField<MSFT_Person_Class>(n).Clear();
    }
};

typedef Array<MSFT_Friends_Class> MSFT_Friends_ClassA;

class MSFT_Friends_AddFriend_Class : public Instance
{
public:
    
    typedef MSFT_Friends_AddFriend Self;
    
    MSFT_Friends_AddFriend_Class() :
        Instance(&MSFT_Friends_AddFriend_rtti)
    {
    }
    
    MSFT_Friends_AddFriend_Class(
        const MSFT_Friends_AddFriend* instanceName,
        bool keysOnly) :
        Instance(
            &MSFT_Friends_AddFriend_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MSFT_Friends_AddFriend_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MSFT_Friends_AddFriend_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MSFT_Friends_AddFriend_Class& operator=(
        const MSFT_Friends_AddFriend_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MSFT_Friends_AddFriend_Class(
        const MSFT_Friends_AddFriend_Class& x) :
        Instance(x)
    {
    }

    //
    // MSFT_Friends_AddFriend_Class.MIReturn
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
    // MSFT_Friends_AddFriend_Class.Friend
    //
    
    const Field<MSFT_Person_Class>& Friend() const
    {
        const size_t n = offsetof(Self, Friend);
        return GetField<MSFT_Person_Class>(n);
    }
    
    void Friend(const Field<MSFT_Person_Class>& x)
    {
        const size_t n = offsetof(Self, Friend);
        GetField<MSFT_Person_Class>(n) = x;
    }
    
    const MSFT_Person_Class& Friend_value() const
    {
        const size_t n = offsetof(Self, Friend);
        return GetField<MSFT_Person_Class>(n).value;
    }
    
    void Friend_value(const MSFT_Person_Class& x)
    {
        const size_t n = offsetof(Self, Friend);
        GetField<MSFT_Person_Class>(n).Set(x);
    }
    
    bool Friend_exists() const
    {
        const size_t n = offsetof(Self, Friend);
        return GetField<MSFT_Person_Class>(n).exists ? true : false;
    }
    
    void Friend_clear()
    {
        const size_t n = offsetof(Self, Friend);
        GetField<MSFT_Person_Class>(n).Clear();
    }
};

typedef Array<MSFT_Friends_AddFriend_Class> MSFT_Friends_AddFriend_ClassA;

class MSFT_Friends_AddFriends_Class : public Instance
{
public:
    
    typedef MSFT_Friends_AddFriends Self;
    
    MSFT_Friends_AddFriends_Class() :
        Instance(&MSFT_Friends_AddFriends_rtti)
    {
    }
    
    MSFT_Friends_AddFriends_Class(
        const MSFT_Friends_AddFriends* instanceName,
        bool keysOnly) :
        Instance(
            &MSFT_Friends_AddFriends_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MSFT_Friends_AddFriends_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MSFT_Friends_AddFriends_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MSFT_Friends_AddFriends_Class& operator=(
        const MSFT_Friends_AddFriends_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MSFT_Friends_AddFriends_Class(
        const MSFT_Friends_AddFriends_Class& x) :
        Instance(x)
    {
    }

    //
    // MSFT_Friends_AddFriends_Class.MIReturn
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
    // MSFT_Friends_AddFriends_Class.Friends
    //
    
    const Field<MSFT_Person_ClassA>& Friends() const
    {
        const size_t n = offsetof(Self, Friends);
        return GetField<MSFT_Person_ClassA>(n);
    }
    
    void Friends(const Field<MSFT_Person_ClassA>& x)
    {
        const size_t n = offsetof(Self, Friends);
        GetField<MSFT_Person_ClassA>(n) = x;
    }
    
    const MSFT_Person_ClassA& Friends_value() const
    {
        const size_t n = offsetof(Self, Friends);
        return GetField<MSFT_Person_ClassA>(n).value;
    }
    
    void Friends_value(const MSFT_Person_ClassA& x)
    {
        const size_t n = offsetof(Self, Friends);
        GetField<MSFT_Person_ClassA>(n).Set(x);
    }
    
    bool Friends_exists() const
    {
        const size_t n = offsetof(Self, Friends);
        return GetField<MSFT_Person_ClassA>(n).exists ? true : false;
    }
    
    void Friends_clear()
    {
        const size_t n = offsetof(Self, Friends);
        GetField<MSFT_Person_ClassA>(n).Clear();
    }
};

typedef Array<MSFT_Friends_AddFriends_Class> MSFT_Friends_AddFriends_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MSFT_Friends_h */
