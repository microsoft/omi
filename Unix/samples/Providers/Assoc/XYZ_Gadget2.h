/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _XYZ_Gadget2_h
#define _XYZ_Gadget2_h

#include <MI.h>
#include "XYZ_Gadget.h"

/*
**==============================================================================
**
** XYZ_Gadget2 [XYZ_Gadget2]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _XYZ_Gadget2 /* extends XYZ_Gadget */
{
    MI_Instance __instance;
    /* XYZ_Gadget properties */
    /*KEY*/ MI_ConstStringField Key;
    /* XYZ_Gadget2 properties */
}
XYZ_Gadget2;

typedef struct _XYZ_Gadget2_Ref
{
    XYZ_Gadget2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Gadget2_Ref;

typedef struct _XYZ_Gadget2_ConstRef
{
    MI_CONST XYZ_Gadget2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Gadget2_ConstRef;

typedef struct _XYZ_Gadget2_Array
{
    struct _XYZ_Gadget2** data;
    MI_Uint32 size;
}
XYZ_Gadget2_Array;

typedef struct _XYZ_Gadget2_ConstArray
{
    struct _XYZ_Gadget2 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
XYZ_Gadget2_ConstArray;

typedef struct _XYZ_Gadget2_ArrayRef
{
    XYZ_Gadget2_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Gadget2_ArrayRef;

typedef struct _XYZ_Gadget2_ConstArrayRef
{
    XYZ_Gadget2_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Gadget2_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl XYZ_Gadget2_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Gadget2_Construct(
    XYZ_Gadget2* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &XYZ_Gadget2_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget2_Clone(
    const XYZ_Gadget2* self,
    XYZ_Gadget2** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL XYZ_Gadget2_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &XYZ_Gadget2_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget2_Destruct(XYZ_Gadget2* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget2_Delete(XYZ_Gadget2* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget2_Post(
    const XYZ_Gadget2* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget2_Set_Key(
    XYZ_Gadget2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget2_SetPtr_Key(
    XYZ_Gadget2* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Gadget2_Clear_Key(
    XYZ_Gadget2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

/*
**==============================================================================
**
** XYZ_Gadget2 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _XYZ_Gadget2_Self XYZ_Gadget2_Self;

MI_EXTERN_C void MI_CALL XYZ_Gadget2_Load(
    XYZ_Gadget2_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Gadget2_Unload(
    XYZ_Gadget2_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Gadget2_EnumerateInstances(
    XYZ_Gadget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Gadget2_GetInstance(
    XYZ_Gadget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget2* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Gadget2_CreateInstance(
    XYZ_Gadget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget2* newInstance);

MI_EXTERN_C void MI_CALL XYZ_Gadget2_ModifyInstance(
    XYZ_Gadget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget2* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Gadget2_DeleteInstance(
    XYZ_Gadget2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget2* instanceName);


/*
**==============================================================================
**
** XYZ_Gadget2_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class XYZ_Gadget2_Class : public XYZ_Gadget_Class
{
public:
    
    typedef XYZ_Gadget2 Self;
    
    XYZ_Gadget2_Class() :
        XYZ_Gadget_Class(&XYZ_Gadget2_rtti)
    {
    }
    
    XYZ_Gadget2_Class(
        const XYZ_Gadget2* instanceName,
        bool keysOnly) :
        XYZ_Gadget_Class(
            &XYZ_Gadget2_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    XYZ_Gadget2_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        XYZ_Gadget_Class(clDecl, instance, keysOnly)
    {
    }
    
    XYZ_Gadget2_Class(
        const MI_ClassDecl* clDecl) :
        XYZ_Gadget_Class(clDecl)
    {
    }
    
    XYZ_Gadget2_Class& operator=(
        const XYZ_Gadget2_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    XYZ_Gadget2_Class(
        const XYZ_Gadget2_Class& x) :
        XYZ_Gadget_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &XYZ_Gadget2_rtti;
    }

};

typedef Array<XYZ_Gadget2_Class> XYZ_Gadget2_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _XYZ_Gadget2_h */
