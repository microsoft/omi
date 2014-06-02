/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_TestObject_h
#define _X_TestObject_h

#include <MI.h>

/*
**==============================================================================
**
** X_TestObject [X_TestObject]
**
** Keys:
**    id
**
**==============================================================================
*/

typedef struct _X_TestObject
{
    MI_Instance __instance;
    /* X_TestObject properties */
    /*KEY*/ MI_ConstUint64Field id;
    MI_ConstStringField str;
    MI_ConstChar16Field operation;
    MI_ConstUint32Field left_operand;
    MI_ConstUint32Field right_operand;
    MI_ConstUint32Field result;
}
X_TestObject;

typedef struct _X_TestObject_Ref
{
    X_TestObject* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestObject_Ref;

typedef struct _X_TestObject_ConstRef
{
    MI_CONST X_TestObject* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestObject_ConstRef;

typedef struct _X_TestObject_Array
{
    struct _X_TestObject** data;
    MI_Uint32 size;
}
X_TestObject_Array;

typedef struct _X_TestObject_ConstArray
{
    struct _X_TestObject MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_TestObject_ConstArray;

typedef struct _X_TestObject_ArrayRef
{
    X_TestObject_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestObject_ArrayRef;

typedef struct _X_TestObject_ConstArrayRef
{
    X_TestObject_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestObject_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_TestObject_rtti;

MI_INLINE MI_Result MI_CALL X_TestObject_Construct(
    X_TestObject* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_TestObject_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clone(
    const X_TestObject* self,
    X_TestObject** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_TestObject_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_TestObject_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Destruct(X_TestObject* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestObject_Delete(X_TestObject* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestObject_Post(
    const X_TestObject* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestObject_Set_id(
    X_TestObject* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->id)->value = x;
    ((MI_Uint64Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clear_id(
    X_TestObject* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Set_str(
    X_TestObject* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_TestObject_SetPtr_str(
    X_TestObject* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clear_str(
    X_TestObject* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL X_TestObject_Set_operation(
    X_TestObject* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->operation)->value = x;
    ((MI_Char16Field*)&self->operation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clear_operation(
    X_TestObject* self)
{
    memset((void*)&self->operation, 0, sizeof(self->operation));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Set_left_operand(
    X_TestObject* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->left_operand)->value = x;
    ((MI_Uint32Field*)&self->left_operand)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clear_left_operand(
    X_TestObject* self)
{
    memset((void*)&self->left_operand, 0, sizeof(self->left_operand));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Set_right_operand(
    X_TestObject* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->right_operand)->value = x;
    ((MI_Uint32Field*)&self->right_operand)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clear_right_operand(
    X_TestObject* self)
{
    memset((void*)&self->right_operand, 0, sizeof(self->right_operand));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Set_result(
    X_TestObject* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->result)->value = x;
    ((MI_Uint32Field*)&self->result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clear_result(
    X_TestObject* self)
{
    memset((void*)&self->result, 0, sizeof(self->result));
    return MI_RESULT_OK;
}


/*
**==============================================================================
**
** X_TestObject_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_TestObject_Class : public Instance
{
public:
    
    typedef X_TestObject Self;
    
    X_TestObject_Class() :
        Instance(&X_TestObject_rtti)
    {
    }
    
    X_TestObject_Class(
        const X_TestObject* instanceName,
        bool keysOnly) :
        Instance(
            &X_TestObject_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_TestObject_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_TestObject_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_TestObject_Class& operator=(
        const X_TestObject_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_TestObject_Class(
        const X_TestObject_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_TestObject_rtti;
    }

    //
    // X_TestObject_Class.id
    //
    
    const Field<Uint64>& id() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n);
    }
    
    void id(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& id_value() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n).value;
    }
    
    void id_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n).Set(x);
    }
    
    bool id_exists() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void id_clear()
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n).Clear();
    }

    //
    // X_TestObject_Class.str
    //
    
    const Field<String>& str() const
    {
        const size_t n = offsetof(Self, str);
        return GetField<String>(n);
    }
    
    void str(const Field<String>& x)
    {
        const size_t n = offsetof(Self, str);
        GetField<String>(n) = x;
    }
    
    const String& str_value() const
    {
        const size_t n = offsetof(Self, str);
        return GetField<String>(n).value;
    }
    
    void str_value(const String& x)
    {
        const size_t n = offsetof(Self, str);
        GetField<String>(n).Set(x);
    }
    
    bool str_exists() const
    {
        const size_t n = offsetof(Self, str);
        return GetField<String>(n).exists ? true : false;
    }
    
    void str_clear()
    {
        const size_t n = offsetof(Self, str);
        GetField<String>(n).Clear();
    }

    //
    // X_TestObject_Class.operation
    //
    
    const Field<Char16>& operation() const
    {
        const size_t n = offsetof(Self, operation);
        return GetField<Char16>(n);
    }
    
    void operation(const Field<Char16>& x)
    {
        const size_t n = offsetof(Self, operation);
        GetField<Char16>(n) = x;
    }
    
    const Char16& operation_value() const
    {
        const size_t n = offsetof(Self, operation);
        return GetField<Char16>(n).value;
    }
    
    void operation_value(const Char16& x)
    {
        const size_t n = offsetof(Self, operation);
        GetField<Char16>(n).Set(x);
    }
    
    bool operation_exists() const
    {
        const size_t n = offsetof(Self, operation);
        return GetField<Char16>(n).exists ? true : false;
    }
    
    void operation_clear()
    {
        const size_t n = offsetof(Self, operation);
        GetField<Char16>(n).Clear();
    }

    //
    // X_TestObject_Class.left_operand
    //
    
    const Field<Uint32>& left_operand() const
    {
        const size_t n = offsetof(Self, left_operand);
        return GetField<Uint32>(n);
    }
    
    void left_operand(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, left_operand);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& left_operand_value() const
    {
        const size_t n = offsetof(Self, left_operand);
        return GetField<Uint32>(n).value;
    }
    
    void left_operand_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, left_operand);
        GetField<Uint32>(n).Set(x);
    }
    
    bool left_operand_exists() const
    {
        const size_t n = offsetof(Self, left_operand);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void left_operand_clear()
    {
        const size_t n = offsetof(Self, left_operand);
        GetField<Uint32>(n).Clear();
    }

    //
    // X_TestObject_Class.right_operand
    //
    
    const Field<Uint32>& right_operand() const
    {
        const size_t n = offsetof(Self, right_operand);
        return GetField<Uint32>(n);
    }
    
    void right_operand(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, right_operand);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& right_operand_value() const
    {
        const size_t n = offsetof(Self, right_operand);
        return GetField<Uint32>(n).value;
    }
    
    void right_operand_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, right_operand);
        GetField<Uint32>(n).Set(x);
    }
    
    bool right_operand_exists() const
    {
        const size_t n = offsetof(Self, right_operand);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void right_operand_clear()
    {
        const size_t n = offsetof(Self, right_operand);
        GetField<Uint32>(n).Clear();
    }

    //
    // X_TestObject_Class.result
    //
    
    const Field<Uint32>& result() const
    {
        const size_t n = offsetof(Self, result);
        return GetField<Uint32>(n);
    }
    
    void result(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, result);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& result_value() const
    {
        const size_t n = offsetof(Self, result);
        return GetField<Uint32>(n).value;
    }
    
    void result_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, result);
        GetField<Uint32>(n).Set(x);
    }
    
    bool result_exists() const
    {
        const size_t n = offsetof(Self, result);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void result_clear()
    {
        const size_t n = offsetof(Self, result);
        GetField<Uint32>(n).Clear();
    }
};

typedef Array<X_TestObject_Class> X_TestObject_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_TestObject_h */
