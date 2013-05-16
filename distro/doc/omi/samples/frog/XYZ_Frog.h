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
#ifndef _XYZ_Frog_h
#define _XYZ_Frog_h

#include <MI.h>

/*
**==============================================================================
**
** XYZ_Frog [XYZ_Frog]
**
** Keys:
**    Name
**
**==============================================================================
*/

typedef struct _XYZ_Frog
{
    MI_Instance __instance;
    /* XYZ_Frog properties */
    /*KEY*/ MI_ConstStringField Name;
    MI_ConstUint32Field Weight;
    MI_ConstStringField Color;
}
XYZ_Frog;

typedef struct _XYZ_Frog_Ref
{
    XYZ_Frog* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Frog_Ref;

typedef struct _XYZ_Frog_ConstRef
{
    MI_CONST XYZ_Frog* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Frog_ConstRef;

typedef struct _XYZ_Frog_Array
{
    struct _XYZ_Frog** data;
    MI_Uint32 size;
}
XYZ_Frog_Array;

typedef struct _XYZ_Frog_ConstArray
{
    struct _XYZ_Frog MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
XYZ_Frog_ConstArray;

typedef struct _XYZ_Frog_ArrayRef
{
    XYZ_Frog_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Frog_ArrayRef;

typedef struct _XYZ_Frog_ConstArrayRef
{
    XYZ_Frog_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Frog_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl XYZ_Frog_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Frog_Construct(
    XYZ_Frog* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &XYZ_Frog_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Frog_Clone(
    const XYZ_Frog* self,
    XYZ_Frog** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL XYZ_Frog_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &XYZ_Frog_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL XYZ_Frog_Destruct(XYZ_Frog* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Frog_Delete(XYZ_Frog* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Frog_Post(
    const XYZ_Frog* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Frog_Set_Name(
    XYZ_Frog* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Frog_SetPtr_Name(
    XYZ_Frog* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Frog_Clear_Name(
    XYZ_Frog* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Frog_Set_Weight(
    XYZ_Frog* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Weight)->value = x;
    ((MI_Uint32Field*)&self->Weight)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Frog_Clear_Weight(
    XYZ_Frog* self)
{
    memset((void*)&self->Weight, 0, sizeof(self->Weight));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Frog_Set_Color(
    XYZ_Frog* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Frog_SetPtr_Color(
    XYZ_Frog* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Frog_Clear_Color(
    XYZ_Frog* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** XYZ_Frog provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _XYZ_Frog_Self XYZ_Frog_Self;

MI_EXTERN_C void MI_CALL XYZ_Frog_Load(
    XYZ_Frog_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Frog_Unload(
    XYZ_Frog_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Frog_EnumerateInstances(
    XYZ_Frog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Frog_GetInstance(
    XYZ_Frog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Frog* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Frog_CreateInstance(
    XYZ_Frog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Frog* newInstance);

MI_EXTERN_C void MI_CALL XYZ_Frog_ModifyInstance(
    XYZ_Frog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Frog* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Frog_DeleteInstance(
    XYZ_Frog_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Frog* instanceName);


/*
**==============================================================================
**
** XYZ_Frog_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class XYZ_Frog_Class : public Instance
{
public:
    
    typedef XYZ_Frog Self;
    
    XYZ_Frog_Class() :
        Instance(&XYZ_Frog_rtti)
    {
    }
    
    XYZ_Frog_Class(
        const XYZ_Frog* instanceName,
        bool keysOnly) :
        Instance(
            &XYZ_Frog_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    XYZ_Frog_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    XYZ_Frog_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    XYZ_Frog_Class& operator=(
        const XYZ_Frog_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    XYZ_Frog_Class(
        const XYZ_Frog_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &XYZ_Frog_rtti;
    }

    //
    // XYZ_Frog_Class.Name
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

    //
    // XYZ_Frog_Class.Weight
    //
    
    const Field<Uint32>& Weight() const
    {
        const size_t n = offsetof(Self, Weight);
        return GetField<Uint32>(n);
    }
    
    void Weight(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Weight);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Weight_value() const
    {
        const size_t n = offsetof(Self, Weight);
        return GetField<Uint32>(n).value;
    }
    
    void Weight_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Weight);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Weight_exists() const
    {
        const size_t n = offsetof(Self, Weight);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Weight_clear()
    {
        const size_t n = offsetof(Self, Weight);
        GetField<Uint32>(n).Clear();
    }

    //
    // XYZ_Frog_Class.Color
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

typedef Array<XYZ_Frog_Class> XYZ_Frog_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _XYZ_Frog_h */
