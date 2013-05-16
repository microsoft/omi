/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _XYZ_Assoc2_h
#define _XYZ_Assoc2_h

#include <MI.h>
#include "XYZ_Assoc.h"
#include "XYZ_Widget2.h"
#include "XYZ_Gadget2.h"

/*
**==============================================================================
**
** XYZ_Assoc2 [XYZ_Assoc2]
**
** Keys:
**    Left
**    Right
**
**==============================================================================
*/

typedef struct _XYZ_Assoc2 /* extends XYZ_Assoc */
{
    MI_Instance __instance;
    /* XYZ_Assoc properties */
    /*KEY*/ XYZ_Widget2_ConstRef Left;
    /*KEY*/ XYZ_Gadget2_ConstRef Right;
    /* XYZ_Assoc2 properties */
}
XYZ_Assoc2;

typedef struct _XYZ_Assoc2_Ref
{
    XYZ_Assoc2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Assoc2_Ref;

typedef struct _XYZ_Assoc2_ConstRef
{
    MI_CONST XYZ_Assoc2* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Assoc2_ConstRef;

typedef struct _XYZ_Assoc2_Array
{
    struct _XYZ_Assoc2** data;
    MI_Uint32 size;
}
XYZ_Assoc2_Array;

typedef struct _XYZ_Assoc2_ConstArray
{
    struct _XYZ_Assoc2 MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
XYZ_Assoc2_ConstArray;

typedef struct _XYZ_Assoc2_ArrayRef
{
    XYZ_Assoc2_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Assoc2_ArrayRef;

typedef struct _XYZ_Assoc2_ConstArrayRef
{
    XYZ_Assoc2_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Assoc2_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl XYZ_Assoc2_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Assoc2_Construct(
    XYZ_Assoc2* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &XYZ_Assoc2_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc2_Clone(
    const XYZ_Assoc2* self,
    XYZ_Assoc2** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL XYZ_Assoc2_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &XYZ_Assoc2_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc2_Destruct(XYZ_Assoc2* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc2_Delete(XYZ_Assoc2* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc2_Post(
    const XYZ_Assoc2* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc2_Set_Left(
    XYZ_Assoc2* self,
    const XYZ_Widget2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc2_SetPtr_Left(
    XYZ_Assoc2* self,
    const XYZ_Widget2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc2_Clear_Left(
    XYZ_Assoc2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc2_Set_Right(
    XYZ_Assoc2* self,
    const XYZ_Gadget2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc2_SetPtr_Right(
    XYZ_Assoc2* self,
    const XYZ_Gadget2* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Assoc2_Clear_Right(
    XYZ_Assoc2* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** XYZ_Assoc2 provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _XYZ_Assoc2_Self XYZ_Assoc2_Self;

MI_EXTERN_C void MI_CALL XYZ_Assoc2_Load(
    XYZ_Assoc2_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Assoc2_Unload(
    XYZ_Assoc2_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Assoc2_EnumerateInstances(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Assoc2_GetInstance(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc2* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Assoc2_CreateInstance(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc2* newInstance);

MI_EXTERN_C void MI_CALL XYZ_Assoc2_ModifyInstance(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc2* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Assoc2_DeleteInstance(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Assoc2* instanceName);

MI_EXTERN_C void MI_CALL XYZ_Assoc2_AssociatorInstancesLeft(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget2* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Assoc2_AssociatorInstancesRight(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget2* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Assoc2_ReferenceInstancesLeft(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Widget2* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Assoc2_ReferenceInstancesRight(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Gadget2* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);


/*
**==============================================================================
**
** XYZ_Assoc2_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class XYZ_Assoc2_Class : public XYZ_Assoc_Class
{
public:
    
    typedef XYZ_Assoc2 Self;
    
    XYZ_Assoc2_Class() :
        XYZ_Assoc_Class(&XYZ_Assoc2_rtti)
    {
    }
    
    XYZ_Assoc2_Class(
        const XYZ_Assoc2* instanceName,
        bool keysOnly) :
        XYZ_Assoc_Class(
            &XYZ_Assoc2_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    XYZ_Assoc2_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        XYZ_Assoc_Class(clDecl, instance, keysOnly)
    {
    }
    
    XYZ_Assoc2_Class(
        const MI_ClassDecl* clDecl) :
        XYZ_Assoc_Class(clDecl)
    {
    }
    
    XYZ_Assoc2_Class& operator=(
        const XYZ_Assoc2_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    XYZ_Assoc2_Class(
        const XYZ_Assoc2_Class& x) :
        XYZ_Assoc_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &XYZ_Assoc2_rtti;
    }

};

typedef Array<XYZ_Assoc2_Class> XYZ_Assoc2_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _XYZ_Assoc2_h */
