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
## XYZ_Dog
##
##==============================================================================
XYZ_Dog_quals = [
    ]

XYZ_Dog_Key_quals = [
    ]

XYZ_Dog_Key_prop = MI_PropertyDecl (
    MI_FLAG_PROPERTY | MI_FLAG_KEY, # flags
    'Key', # name
    XYZ_Dog_Key_quals, # qualifiers
    MI_STRING, # type
    None, # className
    'XYZ_Dog', # origin
    'XYZ_Dog', # propagator
    None # value
    )

XYZ_Dog_Array1_quals = [
    ]

XYZ_Dog_Array1_prop = MI_PropertyDecl (
    MI_FLAG_PROPERTY, # flags
    'Array1', # name
    XYZ_Dog_Array1_quals, # qualifiers
    MI_UINT16A, # type
    None, # className
    'XYZ_Dog', # origin
    'XYZ_Dog', # propagator
    None # value
    )

XYZ_Dog_Array2_quals = [
    ]

XYZ_Dog_Array2_prop = MI_PropertyDecl (
    MI_FLAG_PROPERTY, # flags
    'Array2', # name
    XYZ_Dog_Array2_quals, # qualifiers
    MI_UINT16A, # type
    None, # className
    'XYZ_Dog', # origin
    'XYZ_Dog', # propagator
    None # value
    )

XYZ_Dog_Array3_quals = [
    ]

XYZ_Dog_Array3_prop = MI_PropertyDecl (
    MI_FLAG_PROPERTY, # flags
    'Array3', # name
    XYZ_Dog_Array3_quals, # qualifiers
    MI_UINT16A, # type
    None, # className
    'XYZ_Dog', # origin
    'XYZ_Dog', # propagator
    None # value
    )

XYZ_Dog_properties = [
    XYZ_Dog_Key_prop,
    XYZ_Dog_Array1_prop,
    XYZ_Dog_Array2_prop,
    XYZ_Dog_Array3_prop,
    ]

XYZ_Dog_methods = [
    ]

XYZ_Dog_functions = MI_FunctionTable (
    'XYZ_Dog_Load',
    'XYZ_Dog_Unload',
    'XYZ_Dog_GetInstance',
    'XYZ_Dog_EnumerateInstances',
    'XYZ_Dog_CreateInstance',
    'XYZ_Dog_ModifyInstance',
    'XYZ_Dog_DeleteInstance',
    None,
    None,
    None,
    None,
    None,
    None,
    None
    )

XYZ_Dog_class = MI_ClassDecl (
    MI_FLAG_CLASS, # flags
    'XYZ_Dog', # name
    XYZ_Dog_quals, # qualifiers
    XYZ_Dog_properties, # properties
    None, # superclass
    XYZ_Dog_methods, # method
    XYZ_Dog_functions, # FunctionTable
    None # owningclass
    )

classDecls = [
    XYZ_Dog_class,
    ]

schema = MI_SchemaDecl (
    qualifierDecls,
    classDecls
    )
