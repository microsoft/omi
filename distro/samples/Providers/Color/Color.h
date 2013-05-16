/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _Color_h
#define _Color_h

#include <MI.h>
#include "ColorBase.h"

/*
**==============================================================================
**
** Color [XYZ_Color]
**
** Keys:
**    Id
**
**==============================================================================
*/

typedef struct _Color /* extends XYZ_ColorBase */
{
    MI_Instance __instance;
    /* ColorBase properties */
    /*KEY*/ MI_ConstUint32Field Id;
    /* Color properties */
    MI_ConstStringField Caption;
    MI_ConstStringField Name;
}
Color;

typedef struct _Color_Ref
{
    Color* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Color_Ref;

typedef struct _Color_ConstRef
{
    MI_CONST Color* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Color_ConstRef;

typedef struct _Color_Array
{
    struct _Color** data;
    MI_Uint32 size;
}
Color_Array;

typedef struct _Color_ConstArray
{
    struct _Color MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
Color_ConstArray;

typedef struct _Color_ArrayRef
{
    Color_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Color_ArrayRef;

typedef struct _Color_ConstArrayRef
{
    Color_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
Color_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl Color_rtti;

MI_INLINE MI_Result MI_CALL Color_Construct(
    Color* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &Color_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL Color_Clone(
    const Color* self,
    Color** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL Color_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &Color_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL Color_Destruct(Color* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Color_Delete(Color* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL Color_Post(
    const Color* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL Color_Set_Id(
    Color* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Id)->value = x;
    ((MI_Uint32Field*)&self->Id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Color_Clear_Id(
    Color* self)
{
    memset((void*)&self->Id, 0, sizeof(self->Id));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL Color_Set_Caption(
    Color* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Color_SetPtr_Caption(
    Color* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Color_Clear_Caption(
    Color* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL Color_Set_Name(
    Color* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL Color_SetPtr_Name(
    Color* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL Color_Clear_Name(
    Color* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** Color provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _Color_Self Color_Self;

MI_EXTERN_C void MI_CALL Color_Load(
    Color_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Color_Unload(
    Color_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL Color_EnumerateInstances(
    Color_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL Color_GetInstance(
    Color_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Color* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Color_CreateInstance(
    Color_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Color* newInstance);

MI_EXTERN_C void MI_CALL Color_ModifyInstance(
    Color_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Color* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL Color_DeleteInstance(
    Color_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Color* instanceName);


/*
**==============================================================================
**
** Color_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class Color_Class : public ColorBase_Class
{
public:
    
    typedef Color Self;
    
    Color_Class() :
        ColorBase_Class(&Color_rtti)
    {
    }
    
    Color_Class(
        const Color* instanceName,
        bool keysOnly) :
        ColorBase_Class(
            &Color_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    Color_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        ColorBase_Class(clDecl, instance, keysOnly)
    {
    }
    
    Color_Class(
        const MI_ClassDecl* clDecl) :
        ColorBase_Class(clDecl)
    {
    }
    
    Color_Class& operator=(
        const Color_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    Color_Class(
        const Color_Class& x) :
        ColorBase_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &Color_rtti;
    }

    //
    // Color_Class.Caption
    //
    
    const Field<String>& Caption() const
    {
        const size_t n = offsetof(Self, Caption);
        return GetField<String>(n);
    }
    
    void Caption(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Caption);
        GetField<String>(n) = x;
    }
    
    const String& Caption_value() const
    {
        const size_t n = offsetof(Self, Caption);
        return GetField<String>(n).value;
    }
    
    void Caption_value(const String& x)
    {
        const size_t n = offsetof(Self, Caption);
        GetField<String>(n).Set(x);
    }
    
    bool Caption_exists() const
    {
        const size_t n = offsetof(Self, Caption);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Caption_clear()
    {
        const size_t n = offsetof(Self, Caption);
        GetField<String>(n).Clear();
    }

    //
    // Color_Class.Name
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

typedef Array<Color_Class> Color_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _Color_h */
