#ifndef INCLUDED_MI_FUNCTION_TABLE_HPP
#define INCLUDED_MI_FUNCTION_TABLE_HPP


#include "debug_tags.hpp"
#include "function_helper.hpp"
#include "internal_counted_ptr.hpp"
#include "mi_instance.hpp"
#include "mi_value.hpp"
#include "socket_wrapper.hpp"
#include "traits.hpp"


#ifndef EXPORT_PUBLIC
#define EXPORT_PUBLIC __attribute__ ((visibility ("default")))
#endif


namespace scx
{


class MI_Module;
class MI_Context;

class EXPORT_PUBLIC MI_FunctionTable : public util::ref_counted_obj
{
public:
    typedef util::internal_counted_ptr<MI_FunctionTable> Ptr;
    typedef util::internal_counted_ptr<MI_FunctionTable const> ConstPtr;

    typedef util::function_base<
        int,
        util::internal_counted_ptr<MI_Module> const&,
        util::internal_counted_ptr<MI_Context> const&> LoadFn;

    typedef util::function_base<
        int,
        util::internal_counted_ptr<MI_Context> const&> UnloadFn;

    typedef util::function_base<
        int,
        util::internal_counted_ptr<MI_Context> const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Instance::Ptr const&,
        MI_PropertySet::ConstPtr const&> GetInstanceFn;

    typedef util::function_base<
        int,
        util::internal_counted_ptr<MI_Context> const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_PropertySet::ConstPtr const&,
        MI_Value<MI_BOOLEAN>::Ptr const&> EnumerateInstancesFn;

    typedef util::function_base<
        int,
        util::internal_counted_ptr<MI_Context> const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Instance::Ptr const&> CreateInstanceFn;

    typedef util::function_base<
        int,
        util::internal_counted_ptr<MI_Context> const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Instance::Ptr const&,
        MI_PropertySet::ConstPtr const&> ModifyInstanceFn;

    typedef util::function_base<
        int,
        util::internal_counted_ptr<MI_Context> const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Instance::Ptr const&> DeleteInstanceFn;





//typedef void (MI_CALL *MI_ProviderFT_Invoke)(
//    _In_opt_ void* self,
//    _In_ MI_Context* context,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className,
//    _In_z_ const MI_Char* methodName,
//    _In_ const MI_Instance* instanceName,
//    _In_ const MI_Instance* inputParameters);


    typedef util::function_base<
        int,
        util::internal_counted_ptr<MI_Context> const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Value<MI_STRING>::Ptr const&,
        MI_Instance::Ptr const&,
        MI_Instance::Ptr const&> InvokeFn;
        

  
    EXPORT_PUBLIC int Load (
        util::internal_counted_ptr<MI_Module> const& pModule,
        util::internal_counted_ptr<MI_Context> const& pContext) const;

    EXPORT_PUBLIC int Unload (
        util::internal_counted_ptr<MI_Context> const& pContext) const;

    EXPORT_PUBLIC int GetInstance (
        util::internal_counted_ptr<MI_Context> const& pContext,
        MI_Value<MI_STRING>::Ptr const& pNameSpace,
        MI_Value<MI_STRING>::Ptr const& pClassName,
        MI_Instance::Ptr const& pInstanceName,
        MI_PropertySet::ConstPtr const& pPropertySet) const;

    EXPORT_PUBLIC int EnumerateInstances (
        util::internal_counted_ptr<MI_Context> const& pContext,
        MI_Value<MI_STRING>::Ptr const& pNameSpace,
        MI_Value<MI_STRING>::Ptr const& pClassName,
        MI_PropertySet::ConstPtr const& pPropertySet,
        MI_Value<MI_BOOLEAN>::Ptr const& pKeysOnly) const;

    EXPORT_PUBLIC int CreateInstance (
        util::internal_counted_ptr<MI_Context> const& pContext,
        MI_Value<MI_STRING>::Ptr const& pNameSpace,
        MI_Value<MI_STRING>::Ptr const& pClassName,
        MI_Instance::Ptr const& pNewInstance) const;

    EXPORT_PUBLIC int ModifyInstance (
        util::internal_counted_ptr<MI_Context> const& pContext,
        MI_Value<MI_STRING>::Ptr const& pNameSpace,
        MI_Value<MI_STRING>::Ptr const& pClassName,
        MI_Instance::Ptr const& pModifiedInstance,
        MI_PropertySet::ConstPtr const& pPropertySet) const;

    EXPORT_PUBLIC int DeleteInstance (
        util::internal_counted_ptr<MI_Context> const& pContext,
        MI_Value<MI_STRING>::Ptr const& pNameSpace,
        MI_Value<MI_STRING>::Ptr const& pClassName,
        MI_Instance::Ptr const& pInstanceName) const;

    EXPORT_PUBLIC int Invoke (
        util::internal_counted_ptr<MI_Context> const& pContext,
        MI_Value<MI_STRING>::Ptr const& pNameSpace,
        MI_Value<MI_STRING>::Ptr const& pClassName,
        MI_Value<MI_STRING>::Ptr const& pMethodName,
        MI_Instance::Ptr const& pInstanceName,
        MI_Instance::Ptr const& pInputParameters) const;


    EXPORT_PUBLIC /*ctor*/ MI_FunctionTable (
        LoadFn::Ptr const& pLoad,
        UnloadFn::Ptr const& pUnload,
        GetInstanceFn::Ptr const& pGetInstance,
        EnumerateInstancesFn::Ptr const& pEnumerateInstances,
        CreateInstanceFn::Ptr const& pCreateInstance,
        ModifyInstanceFn::Ptr const& pModifyInstance,
        DeleteInstanceFn::Ptr const& pDeleteInstance,
        InvokeFn::Ptr const& pInvoke);

    EXPORT_PUBLIC virtual /*dtor*/ ~MI_FunctionTable ();

    int send (socket_wrapper& sock) const;

private:
    LoadFn::Ptr const m_pLoad;
    UnloadFn::Ptr const m_pUnload;
    GetInstanceFn::Ptr const m_pGetInstance;
    EnumerateInstancesFn::Ptr const m_pEnumerateInstances;
    CreateInstanceFn::Ptr const m_pCreateInstance;
    ModifyInstanceFn::Ptr const m_pModifyInstance;
    DeleteInstanceFn::Ptr const m_pDeleteInstance;
    InvokeFn::Ptr const m_pInvoke;
};


} // namespace scx


#undef EXPORT_PUBLIC



//typedef void (MI_CALL *MI_ProviderFT_Load)(
//    _Outptr_ void** self,
//    _In_opt_ MI_Module_Self* selfModule,
//    _In_ MI_Context* context);

//typedef void (MI_CALL *MI_ProviderFT_Unload)(
//    _In_opt_ void* self,
//    _In_ MI_Context* context);

//typedef void (MI_CALL *MI_ProviderFT_GetInstance)(
//    _In_opt_ void* self,
//    _In_ MI_Context* context,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className,
//    _In_ const MI_Instance* instanceName,
//    _In_opt_ const MI_PropertySet* propertySet);

//typedef void (MI_CALL *MI_ProviderFT_EnumerateInstances)(
//    _In_opt_ void* self,
//    _In_ MI_Context* context,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className,
//    _In_opt_ const MI_PropertySet* propertySet,
//    MI_Boolean keysOnly,
//    _In_opt_ const MI_Filter* filter);

//typedef void (MI_CALL *MI_ProviderFT_CreateInstance)(
//    _In_opt_ void* self,
//    _In_ MI_Context* context,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className,
//    _In_ const MI_Instance* newInstance);

//typedef void (MI_CALL *MI_ProviderFT_ModifyInstance)(
//    void* self,
//    MI_Context* context,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className,
//    const MI_Instance* modifiedInstance,
//    const MI_PropertySet* propertySet);

//typedef void (MI_CALL *MI_ProviderFT_DeleteInstance)(
//    _In_opt_ void* self,
//    _In_ MI_Context* context,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className,
//    _In_ const MI_Instance* instanceName);

//typedef void (MI_CALL *MI_ProviderFT_AssociatorInstances)(
//    _In_opt_ void* self,
//    _In_ MI_Context* context,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className,
//    _In_ const MI_Instance* instanceName,
//    _In_opt_z_ const MI_Char* resultClass,
//    _In_opt_z_ const MI_Char* role,
//    _In_opt_z_ const MI_Char* resultRole,
//    _In_opt_ const MI_PropertySet* propertySet,
//    MI_Boolean keysOnly,
//    _In_opt_ const MI_Filter* filter);

//typedef void (MI_CALL *MI_ProviderFT_ReferenceInstances)(
//    _In_opt_ void* self,
//    _In_ MI_Context* context,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className,
//    _In_ const MI_Instance* instanceName,
//    _In_opt_z_ const MI_Char* role,
//    _In_opt_ const MI_PropertySet* propertySet,
//    MI_Boolean keysOnly,
//    _In_opt_ const MI_Filter* filter);

//typedef void (MI_CALL *MI_ProviderFT_EnableIndications)(
//    _In_opt_ void* self,
//    _In_ MI_Context* indicationsContext,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className);

//typedef void (MI_CALL *MI_ProviderFT_DisableIndications)(
//    _In_opt_ void* self,
//    _In_ MI_Context* indicationsContext,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className);

//typedef void (MI_CALL *MI_ProviderFT_Subscribe)(
//    _In_opt_ void* self,
//    _In_ MI_Context* context,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className,
//    _In_opt_ const MI_Filter* filter,
//    _In_opt_z_ const MI_Char* bookmark,
//    MI_Uint64  subscriptionID,
//    _Outptr_result_maybenull_ void** subscriptionSelf);

//typedef void (MI_CALL *MI_ProviderFT_Unsubscribe)(
//    _In_opt_ void* self,
//    _In_ MI_Context* context,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className,
//    MI_Uint64  subscriptionID,
//    _In_opt_ void* subscriptionSelf);

//typedef void (MI_CALL *MI_ProviderFT_Invoke)(
//    _In_opt_ void* self,
//    _In_ MI_Context* context,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className,
//    _In_z_ const MI_Char* methodName,
//    _In_ const MI_Instance* instanceName,
//    _In_ const MI_Instance* inputParameters);


#endif // INCLUDED_MI_FUNCTION_TABLE_HPP
