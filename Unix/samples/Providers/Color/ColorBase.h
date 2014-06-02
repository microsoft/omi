/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ColorBase_h
#define _ColorBase_h

#include <MI.h>

/*
**==============================================================================
**
** ColorBase [XYZ_ColorBase]
**
** Keys:
**    Id
**
**==============================================================================
*/

typedef struct _ColorBase
{
    MI_Instance __instance;
    /* ColorBase properties */
    /*KEY*/ MI_ConstUint32Field Id;
}
ColorBase;

typedef struct _ColorBase_Ref
{
    ColorBase* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ColorBase_Ref;

typedef struct _ColorBase_ConstRef
{
    MI_CONST ColorBase* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ColorBase_ConstRef;

typedef struct _ColorBase_Array
{
    struct _ColorBase** data;
    MI_Uint32 size;
}
ColorBase_Array;

typedef struct _ColorBase_ConstArray
{
    struct _ColorBase MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ColorBase_ConstArray;

typedef struct _ColorBase_ArrayRef
{
    ColorBase_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ColorBase_ArrayRef;

typedef struct _ColorBase_ConstArrayRef
{
    ColorBase_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ColorBase_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ColorBase_rtti;

MI_INLINE MI_Result MI_CALL ColorBase_Construct(
    ColorBase* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ColorBase_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ColorBase_Clone(
    const ColorBase* self,
    ColorBase** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ColorBase_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ColorBase_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ColorBase_Destruct(ColorBase* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ColorBase_Delete(ColorBase* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ColorBase_Post(
    const ColorBase* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ColorBase_Set_Id(
    ColorBase* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Id)->value = x;
    ((MI_Uint32Field*)&self->Id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ColorBase_Clear_Id(
    ColorBase* self)
{
    memset((void*)&self->Id, 0, sizeof(self->Id));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ColorBase provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ColorBase_Self ColorBase_Self;

MI_EXTERN_C void MI_CALL ColorBase_Load(
    ColorBase_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ColorBase_Unload(
    ColorBase_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ColorBase_EnumerateInstances(
    ColorBase_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ColorBase_GetInstance(
    ColorBase_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ColorBase* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ColorBase_CreateInstance(
    ColorBase_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ColorBase* newInstance);

MI_EXTERN_C void MI_CALL ColorBase_ModifyInstance(
    ColorBase_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ColorBase* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ColorBase_DeleteInstance(
    ColorBase_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ColorBase* instanceName);


/*
**==============================================================================
**
** ColorBase_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class ColorBase_Class : public Instance
{
public:
    
    typedef ColorBase Self;
    
    ColorBase_Class() :
        Instance(&ColorBase_rtti)
    {
    }
    
    ColorBase_Class(
        const ColorBase* instanceName,
        bool keysOnly) :
        Instance(
            &ColorBase_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    ColorBase_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    ColorBase_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    ColorBase_Class& operator=(
        const ColorBase_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    ColorBase_Class(
        const ColorBase_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &ColorBase_rtti;
    }

    //
    // ColorBase_Class.Id
    //
    
    const Field<Uint32>& Id() const
    {
        const size_t n = offsetof(Self, Id);
        return GetField<Uint32>(n);
    }
    
    void Id(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, Id);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& Id_value() const
    {
        const size_t n = offsetof(Self, Id);
        return GetField<Uint32>(n).value;
    }
    
    void Id_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, Id);
        GetField<Uint32>(n).Set(x);
    }
    
    bool Id_exists() const
    {
        const size_t n = offsetof(Self, Id);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void Id_clear()
    {
        const size_t n = offsetof(Self, Id);
        GetField<Uint32>(n).Clear();
    }
};

typedef Array<ColorBase_Class> ColorBase_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _ColorBase_h */
