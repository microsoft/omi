/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _XYZ_Widget2_h
#define _XYZ_Widget2_h

#include <MI.h>
#include "XYZ_Widget.h"

/*
**==============================================================================
**
** XYZ_Widget2 [XYZ_Widget2]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _XYZ_Widget2 /* extends XYZ_Widget */
{
    MI_Instance __instance;
    /* XYZ_Widget properties */
    /*KEY*/ MI_ConstStringField Key;
    /* XYZ_Widget2 properties */
}
XYZ_Widget2;

typedef struct _XYZ_Widget2_Ref
{
    XYZ_Widget2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Widget2_Ref;

typedef struct _XYZ_Widget2_ConstRef
{
    MI_CONST XYZ_Widget2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Widget2_ConstRef;

typedef struct _XYZ_Widget2_Array
{
    struct _XYZ_Widget2** data;
    MI_Uint32 size;
}
XYZ_Widget2_Array;

typedef struct _XYZ_Widget2_ConstArray
{
    struct _XYZ_Widget2 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
XYZ_Widget2_ConstArray;

typedef struct _XYZ_Widget2_ArrayRef
{
    XYZ_Widget2_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Widget2_ArrayRef;

typedef struct _XYZ_Widget2_ConstArrayRef
{
    XYZ_Widget2_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Widget2_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl XYZ_Widget2_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Widget2_Construct(
    XYZ_Widget2* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &XYZ_Widget2_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Widget2_Clone(
    const XYZ_Widget2* self,
    XYZ_Widget2** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL XYZ_Widget2_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &XYZ_Widget2_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL XYZ_Widget2_Destruct(XYZ_Widget2* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Widget2_Delete(XYZ_Widget2* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Widget2_Post(
    const XYZ_Widget2* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Widget2_Set_Key(
    XYZ_Widget2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Widget2_SetPtr_Key(
    XYZ_Widget2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Widget2_Clear_Key(
    XYZ_Widget2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** XYZ_Widget2 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _XYZ_Widget2_Self XYZ_Widget2_Self;

MI_EXTERN_C void MI_CALL XYZ_Widget2_Load(
    XYZ_Widget2_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Widget2_Unload(
    XYZ_Widget2_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Widget2_EnumerateInstances(
    XYZ_Widget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Widget2_GetInstance(
    XYZ_Widget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget2* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Widget2_CreateInstance(
    XYZ_Widget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget2* newInstance);

MI_EXTERN_C void MI_CALL XYZ_Widget2_ModifyInstance(
    XYZ_Widget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget2* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Widget2_DeleteInstance(
    XYZ_Widget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget2* instanceName);


/*
**==============================================================================
**
** XYZ_Widget2_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class XYZ_Widget2_Class : public XYZ_Widget_Class
{
public:
    
    typedef XYZ_Widget2 Self;
    
    XYZ_Widget2_Class() :
        XYZ_Widget_Class(&XYZ_Widget2_rtti)
    {
    }
    
    XYZ_Widget2_Class(
        const XYZ_Widget2* instanceName,
        bool keysOnly) :
        XYZ_Widget_Class(
            &XYZ_Widget2_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    XYZ_Widget2_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        XYZ_Widget_Class(clDecl, instance, keysOnly)
    {
    }
    
    XYZ_Widget2_Class(
        const MI_ClassDecl* clDecl) :
        XYZ_Widget_Class(clDecl)
    {
    }
    
    XYZ_Widget2_Class& operator=(
        const XYZ_Widget2_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    XYZ_Widget2_Class(
        const XYZ_Widget2_Class& x) :
        XYZ_Widget_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &XYZ_Widget2_rtti;
    }

};

typedef Array<XYZ_Widget2_Class> XYZ_Widget2_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _XYZ_Widget2_h */
