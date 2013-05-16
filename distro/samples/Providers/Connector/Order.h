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


#endif /* _Order_h */
