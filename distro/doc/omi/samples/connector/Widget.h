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
#ifndef _Widget_h
#define _Widget_h

#include <MI.h>

/*
**==============================================================================
**
** Widget [XYZ_Widget]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _Widget
{
    MI_Instance __instance;
    /* Widget properties */
    /*KEY*/ MI_ConstUint32Field Key;
    MI_ConstUint32Field ModelNumber;
    MI_ConstStringField Color;
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

MI_INLINE MI_Result MI_CALL Widget_Set_Key(
    Widget* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Key)->value = x;
    ((MI_Uint32Field*)&self->Key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Widget_Clear_Key(
    Widget* self)
{
    memset((void*)&self->Key, 0, sizeof(self->Key));
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
    // Widget_Class.Key
    //
    
    const Field<Uint32>& Key() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<Uint32>(n);
    }
    
    void Key(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Key);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Key_value() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<Uint32>(n).value;
    }
    
    void Key_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Key);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Key_exists() const
    {
        const size_t n = offsetof(Self, Key);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Key_clear()
    {
        const size_t n = offsetof(Self, Key);
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
};

typedef Array<Widget_Class> Widget_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Widget_h */
