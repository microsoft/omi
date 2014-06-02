/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Order_h
#define _Order_h

#include <MI.h>

/*
**==============================================================================
**
** Order [XYZ_Order]
**
** Keys:
**
**==============================================================================
*/

typedef struct _Order
{
    MI_Instance __instance;
    /* Order properties */
    MI_ConstUint32Field SerialNumber;
    MI_ConstUint32Field Quantity;
}
Order;

typedef struct _Order_Ref
{
    Order* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Order_Ref;

typedef struct _Order_ConstRef
{
    MI_CONST Order* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Order_ConstRef;

typedef struct _Order_Array
{
    struct _Order** data;
    MI_Uint32 size;
}
Order_Array;

typedef struct _Order_ConstArray
{
    struct _Order MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Order_ConstArray;

typedef struct _Order_ArrayRef
{
    Order_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Order_ArrayRef;

typedef struct _Order_ConstArrayRef
{
    Order_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Order_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Order_rtti;

MI_INLINE MI_Result MI_CALL Order_Construct(
    Order* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Order_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Order_Clone(
    const Order* self,
    Order** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Order_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Order_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Order_Destruct(Order* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Order_Delete(Order* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Order_Post(
    const Order* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Order_Set_SerialNumber(
    Order* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->SerialNumber)->value = x;
    ((MI_Uint32Field*)&self->SerialNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Order_Clear_SerialNumber(
    Order* self)
{
    memset((void*)&self->SerialNumber, 0, sizeof(self->SerialNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Order_Set_Quantity(
    Order* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Quantity)->value = x;
    ((MI_Uint32Field*)&self->Quantity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Order_Clear_Quantity(
    Order* self)
{
    memset((void*)&self->Quantity, 0, sizeof(self->Quantity));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Order provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Order_Self Order_Self;

MI_EXTERN_C void MI_CALL Order_Load(
    Order_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Order_Unload(
    Order_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Order_EnableIndications(
    Order_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL Order_DisableIndications(
    Order_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className);

MI_EXTERN_C void MI_CALL Order_Subscribe(
    Order_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf);

MI_EXTERN_C void MI_CALL Order_Unsubscribe(
    Order_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf);


/*
**==============================================================================
**
** Order_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Order_Class : public Instance
{
public:
    
    typedef Order Self;
    
    Order_Class() :
        Instance(&Order_rtti)
    {
    }
    
    Order_Class(
        const Order* instanceName,
        bool keysOnly) :
        Instance(
            &Order_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Order_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Order_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Order_Class& operator=(
        const Order_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Order_Class(
        const Order_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Order_rtti;
    }

    //
    // Order_Class.SerialNumber
    //
    
    const Field<Uint32>& SerialNumber() const
    {
        const size_t n = offsetof(Self, SerialNumber);
        return GetField<Uint32>(n);
    }
    
    void SerialNumber(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, SerialNumber);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& SerialNumber_value() const
    {
        const size_t n = offsetof(Self, SerialNumber);
        return GetField<Uint32>(n).value;
    }
    
    void SerialNumber_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, SerialNumber);
        GetField<Uint32>(n).Set(x);
    }
    
    bool SerialNumber_exists() const
    {
        const size_t n = offsetof(Self, SerialNumber);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void SerialNumber_clear()
    {
        const size_t n = offsetof(Self, SerialNumber);
        GetField<Uint32>(n).Clear();
    }

    //
    // Order_Class.Quantity
    //
    
    const Field<Uint32>& Quantity() const
    {
        const size_t n = offsetof(Self, Quantity);
        return GetField<Uint32>(n);
    }
    
    void Quantity(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Quantity);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Quantity_value() const
    {
        const size_t n = offsetof(Self, Quantity);
        return GetField<Uint32>(n).value;
    }
    
    void Quantity_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Quantity);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Quantity_exists() const
    {
        const size_t n = offsetof(Self, Quantity);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Quantity_clear()
    {
        const size_t n = offsetof(Self, Quantity);
        GetField<Uint32>(n).Clear();
    }
};

typedef Array<Order_Class> Order_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Order_h */
