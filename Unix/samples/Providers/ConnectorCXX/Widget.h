/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Widget_h
#define _Widget_h

#include <MI.h>

/*
**==============================================================================
**
** Widget [XYZ_Widget]
**
** Keys:
**    SerialNumber
**
**==============================================================================
*/

typedef struct _Widget
{
    MI_Instance __instance;
    /* Widget properties */
    /*KEY*/ MI_ConstUint32Field SerialNumber;
    MI_ConstUint32Field ModelNumber;
    MI_ConstStringField Color;
    MI_ConstStringAField Colors;
    MI_ConstUint32AField Numbers;
    MI_ConstDatetimeField Timestamp;
    MI_ConstDatetimeField Interval;
    MI_ConstDatetimeAField TimestampA;
    MI_ConstDatetimeAField IntervalA;
}
Widget;

typedef struct _Widget_Ref
{
    Widget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Widget_Ref;

typedef struct _Widget_ConstRef
{
    MI_CONST Widget* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Widget_ConstRef;

typedef struct _Widget_Array
{
    struct _Widget** data;
    MI_Uint32 size;
}
Widget_Array;

typedef struct _Widget_ConstArray
{
    struct _Widget MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Widget_ConstArray;

typedef struct _Widget_ArrayRef
{
    Widget_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Widget_ArrayRef;

typedef struct _Widget_ConstArrayRef
{
    Widget_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Widget_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Widget_rtti;

MI_INLINE MI_Result MI_CALL Widget_Construct(
    Widget* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Widget_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Widget_Clone(
    const Widget* self,
    Widget** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Widget_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Widget_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Widget_Destruct(Widget* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Widget_Delete(Widget* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Widget_Post(
    const Widget* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Widget_Set_SerialNumber(
    Widget* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->SerialNumber)->value = x;
    ((MI_Uint32Field*)&self->SerialNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_SerialNumber(
    Widget* self)
{
    memset((void*)&self->SerialNumber, 0, sizeof(self->SerialNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_ModelNumber(
    Widget* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ModelNumber)->value = x;
    ((MI_Uint32Field*)&self->ModelNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_ModelNumber(
    Widget* self)
{
    memset((void*)&self->ModelNumber, 0, sizeof(self->ModelNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_Color(
    Widget* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Widget_SetPtr_Color(
    Widget* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Widget_Clear_Color(
    Widget* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL Widget_Set_Colors(
    Widget* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL Widget_SetPtr_Colors(
    Widget* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Widget_Clear_Colors(
    Widget* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL Widget_Set_Numbers(
    Widget* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL Widget_SetPtr_Numbers(
    Widget* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Widget_Clear_Numbers(
    Widget* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL Widget_Set_Timestamp(
    Widget* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->Timestamp)->value = x;
    ((MI_DatetimeField*)&self->Timestamp)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_Timestamp(
    Widget* self)
{
    memset((void*)&self->Timestamp, 0, sizeof(self->Timestamp));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_Interval(
    Widget* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->Interval)->value = x;
    ((MI_DatetimeField*)&self->Interval)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_Interval(
    Widget* self)
{
    memset((void*)&self->Interval, 0, sizeof(self->Interval));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Set_TimestampA(
    Widget* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL Widget_SetPtr_TimestampA(
    Widget* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Widget_Clear_TimestampA(
    Widget* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL Widget_Set_IntervalA(
    Widget* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL Widget_SetPtr_IntervalA(
    Widget* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Widget_Clear_IntervalA(
    Widget* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

/*
**==============================================================================
**
** Widget provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Widget_Self Widget_Self;

MI_EXTERN_C void MI_CALL Widget_Load(
    Widget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Widget_Unload(
    Widget_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Widget_EnumerateInstances(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Widget_GetInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Widget_CreateInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* newInstance);

MI_EXTERN_C void MI_CALL Widget_ModifyInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Widget_DeleteInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName);


/*
**==============================================================================
**
** Widget_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Widget_Class : public Instance
{
public:
    
    typedef Widget Self;
    
    Widget_Class() :
        Instance(&Widget_rtti)
    {
    }
    
    Widget_Class(
        const Widget* instanceName,
        bool keysOnly) :
        Instance(
            &Widget_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Widget_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    Widget_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    Widget_Class& operator=(
        const Widget_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Widget_Class(
        const Widget_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Widget_rtti;
    }

    //
    // Widget_Class.SerialNumber
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
    // Widget_Class.ModelNumber
    //
    
    const Field<Uint32>& ModelNumber() const
    {
        const size_t n = offsetof(Self, ModelNumber);
        return GetField<Uint32>(n);
    }
    
    void ModelNumber(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, ModelNumber);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& ModelNumber_value() const
    {
        const size_t n = offsetof(Self, ModelNumber);
        return GetField<Uint32>(n).value;
    }
    
    void ModelNumber_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, ModelNumber);
        GetField<Uint32>(n).Set(x);
    }
    
    bool ModelNumber_exists() const
    {
        const size_t n = offsetof(Self, ModelNumber);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void ModelNumber_clear()
    {
        const size_t n = offsetof(Self, ModelNumber);
        GetField<Uint32>(n).Clear();
    }

    //
    // Widget_Class.Color
    //
    
    const Field<String>& Color() const
    {
        const size_t n = offsetof(Self, Color);
        return GetField<String>(n);
    }
    
    void Color(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Color);
        GetField<String>(n) = x;
    }
    
    const String& Color_value() const
    {
        const size_t n = offsetof(Self, Color);
        return GetField<String>(n).value;
    }
    
    void Color_value(const String& x)
    {
        const size_t n = offsetof(Self, Color);
        GetField<String>(n).Set(x);
    }
    
    bool Color_exists() const
    {
        const size_t n = offsetof(Self, Color);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Color_clear()
    {
        const size_t n = offsetof(Self, Color);
        GetField<String>(n).Clear();
    }

    //
    // Widget_Class.Colors
    //
    
    const Field<StringA>& Colors() const
    {
        const size_t n = offsetof(Self, Colors);
        return GetField<StringA>(n);
    }
    
    void Colors(const Field<StringA>& x)
    {
        const size_t n = offsetof(Self, Colors);
        GetField<StringA>(n) = x;
    }
    
    const StringA& Colors_value() const
    {
        const size_t n = offsetof(Self, Colors);
        return GetField<StringA>(n).value;
    }
    
    void Colors_value(const StringA& x)
    {
        const size_t n = offsetof(Self, Colors);
        GetField<StringA>(n).Set(x);
    }
    
    bool Colors_exists() const
    {
        const size_t n = offsetof(Self, Colors);
        return GetField<StringA>(n).exists ? true : false;
    }
    
    void Colors_clear()
    {
        const size_t n = offsetof(Self, Colors);
        GetField<StringA>(n).Clear();
    }

    //
    // Widget_Class.Numbers
    //
    
    const Field<Uint32A>& Numbers() const
    {
        const size_t n = offsetof(Self, Numbers);
        return GetField<Uint32A>(n);
    }
    
    void Numbers(const Field<Uint32A>& x)
    {
        const size_t n = offsetof(Self, Numbers);
        GetField<Uint32A>(n) = x;
    }
    
    const Uint32A& Numbers_value() const
    {
        const size_t n = offsetof(Self, Numbers);
        return GetField<Uint32A>(n).value;
    }
    
    void Numbers_value(const Uint32A& x)
    {
        const size_t n = offsetof(Self, Numbers);
        GetField<Uint32A>(n).Set(x);
    }
    
    bool Numbers_exists() const
    {
        const size_t n = offsetof(Self, Numbers);
        return GetField<Uint32A>(n).exists ? true : false;
    }
    
    void Numbers_clear()
    {
        const size_t n = offsetof(Self, Numbers);
        GetField<Uint32A>(n).Clear();
    }

    //
    // Widget_Class.Timestamp
    //
    
    const Field<Datetime>& Timestamp() const
    {
        const size_t n = offsetof(Self, Timestamp);
        return GetField<Datetime>(n);
    }
    
    void Timestamp(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, Timestamp);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& Timestamp_value() const
    {
        const size_t n = offsetof(Self, Timestamp);
        return GetField<Datetime>(n).value;
    }
    
    void Timestamp_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, Timestamp);
        GetField<Datetime>(n).Set(x);
    }
    
    bool Timestamp_exists() const
    {
        const size_t n = offsetof(Self, Timestamp);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void Timestamp_clear()
    {
        const size_t n = offsetof(Self, Timestamp);
        GetField<Datetime>(n).Clear();
    }

    //
    // Widget_Class.Interval
    //
    
    const Field<Datetime>& Interval() const
    {
        const size_t n = offsetof(Self, Interval);
        return GetField<Datetime>(n);
    }
    
    void Interval(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, Interval);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& Interval_value() const
    {
        const size_t n = offsetof(Self, Interval);
        return GetField<Datetime>(n).value;
    }
    
    void Interval_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, Interval);
        GetField<Datetime>(n).Set(x);
    }
    
    bool Interval_exists() const
    {
        const size_t n = offsetof(Self, Interval);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void Interval_clear()
    {
        const size_t n = offsetof(Self, Interval);
        GetField<Datetime>(n).Clear();
    }

    //
    // Widget_Class.TimestampA
    //
    
    const Field<DatetimeA>& TimestampA() const
    {
        const size_t n = offsetof(Self, TimestampA);
        return GetField<DatetimeA>(n);
    }
    
    void TimestampA(const Field<DatetimeA>& x)
    {
        const size_t n = offsetof(Self, TimestampA);
        GetField<DatetimeA>(n) = x;
    }
    
    const DatetimeA& TimestampA_value() const
    {
        const size_t n = offsetof(Self, TimestampA);
        return GetField<DatetimeA>(n).value;
    }
    
    void TimestampA_value(const DatetimeA& x)
    {
        const size_t n = offsetof(Self, TimestampA);
        GetField<DatetimeA>(n).Set(x);
    }
    
    bool TimestampA_exists() const
    {
        const size_t n = offsetof(Self, TimestampA);
        return GetField<DatetimeA>(n).exists ? true : false;
    }
    
    void TimestampA_clear()
    {
        const size_t n = offsetof(Self, TimestampA);
        GetField<DatetimeA>(n).Clear();
    }

    //
    // Widget_Class.IntervalA
    //
    
    const Field<DatetimeA>& IntervalA() const
    {
        const size_t n = offsetof(Self, IntervalA);
        return GetField<DatetimeA>(n);
    }
    
    void IntervalA(const Field<DatetimeA>& x)
    {
        const size_t n = offsetof(Self, IntervalA);
        GetField<DatetimeA>(n) = x;
    }
    
    const DatetimeA& IntervalA_value() const
    {
        const size_t n = offsetof(Self, IntervalA);
        return GetField<DatetimeA>(n).value;
    }
    
    void IntervalA_value(const DatetimeA& x)
    {
        const size_t n = offsetof(Self, IntervalA);
        GetField<DatetimeA>(n).Set(x);
    }
    
    bool IntervalA_exists() const
    {
        const size_t n = offsetof(Self, IntervalA);
        return GetField<DatetimeA>(n).exists ? true : false;
    }
    
    void IntervalA_clear()
    {
        const size_t n = offsetof(Self, IntervalA);
        GetField<DatetimeA>(n).Clear();
    }
};

typedef Array<Widget_Class> Widget_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Widget_h */
