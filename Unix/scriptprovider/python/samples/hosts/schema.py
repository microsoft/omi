# @migen@
##==============================================================================
##
## WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
##
##==============================================================================
import omi
from omi import *

##==============================================================================
##
## Qualifier declarations
##
##==============================================================================
qualifierDecls = [
    ]

##==============================================================================
##
## Hosts
##
##==============================================================================
Hosts_quals = [
    ]

Hosts_FQDN_quals = [
    ]

Hosts_FQDN_prop = MI_PropertyDecl (
    MI_FLAG_PROPERTY | MI_FLAG_KEY, # flags
    'FQDN', # name
    Hosts_FQDN_quals, # qualifiers
    MI_STRING, # type
    None, # className
    'Hosts', # origin
    'Hosts', # propagator
    None # value
    )

Hosts_IPAddress_quals = [
    ]

Hosts_IPAddress_prop = MI_PropertyDecl (
    MI_FLAG_PROPERTY, # flags
    'IPAddress', # name
    Hosts_IPAddress_quals, # qualifiers
    MI_STRING, # type
    None, # className
    'Hosts', # origin
    'Hosts', # propagator
    None # value
    )

Hosts_properties = [
    Hosts_FQDN_prop,
    Hosts_IPAddress_prop,
    ]

Hosts_Ping_quals = [
    ]

Hosts_Ping_MIReturn_quals = [
    ]

Hosts_Ping_MIReturn_param = MI_ParameterDecl (
    MI_FLAG_PARAMETER | MI_FLAG_OUT, # flags
    'MIReturn', # name
    Hosts_Ping_MIReturn_quals, # qualifiers
    MI_UINT64, # type
    None # className
    )

Hosts_Ping_params = [
    Hosts_Ping_MIReturn_param,
    ]

Hosts_Ping_method = MI_MethodDecl (
    MI_FLAG_METHOD | MI_FLAG_STATIC, # flags
    'Ping', # name
    Hosts_Ping_quals, # qualifiers
    Hosts_Ping_params, # parameters
    MI_UINT64, # returnType
    'Hosts', # origin
    'Hosts', # propagator
    'Hosts_Ping' # method
    )

Hosts_methods = [
    Hosts_Ping_method,
    ]

Hosts_functions = MI_FunctionTable (
    'Hosts_Load',
    'Hosts_Unload',
    'Hosts_GetInstance',
    'Hosts_EnumerateInstances',
    'Hosts_CreateInstance',
    'Hosts_ModifyInstance',
    'Hosts_DeleteInstance',
    None,
    None,
    None,
    None,
    None,
    None,
    None
    )

Hosts_class = MI_ClassDecl (
    MI_FLAG_CLASS, # flags
    'Hosts', # name
    Hosts_quals, # qualifiers
    Hosts_properties, # properties
    None, # superclass
    Hosts_methods, # method
    Hosts_functions, # FunctionTable
    None # owningclass
    )

classDecls = [
    Hosts_class,
    ]

schema = MI_SchemaDecl (
    qualifierDecls,
    classDecls
    )
