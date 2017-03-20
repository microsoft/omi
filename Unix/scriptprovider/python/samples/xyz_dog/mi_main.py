import omi
from omi import *

import schema


def Load (module, context):
    context.PostResult (MI_RESULT_OK)


def Unload (module, context):
    context.PostResult (MI_RESULT_OK)


def XYZ_Dog_Load (
    module, context):
    context.PostResult (MI_RESULT_OK)


def XYZ_Dog_Unload (
    context):
    context.PostResult (MI_RESULT_OK)


def XYZ_Dog_EnumerateInstances (
    context, nameSpace, className, propertySet, keysOnly):
    be = BookEnd ('XYZ_Dog_EnumerateInstances')
    instance = context.NewInstance ('XYZ_Dog')
    instance.SetValue ('Key', MI_String ('1001'))
    arr2 = MI_Uint16A ()
    instance.SetValue ('Array2', arr2)
    arr3 = MI_Uint16A ()
    arr3.append (10)
    arr3.append (20)
    arr3.append (30)
    instance.SetValue ('Array3', arr3)
    context.PostInstance (instance)
    context.PostResult (MI_RESULT_OK)


def XYZ_Dog_GetInstance (
    context, nameSpace, className, instanceName, propertySet):
    context.PostResult (MI_RESULT_NOT_SUPPORTED)


def XYZ_Dog_CreateInstance (
    context, nameSpace, className, instance):
    context.PostResult (MI_RESULT_NOT_SUPPORTED)


def XYZ_Dog_ModifyInstance (
    context, nameSpace, className, instance, propertySet):
    context.PostResult (MI_RESULT_NOT_SUPPORTED)


def XYZ_Dog_DeleteInstance (
    context, nameSpace, className, instanceName):
    context.PostResult (MI_RESULT_NOT_SUPPORTED)


def mi_main ():
    r = MI_Module (schema.schema, Load, Unload)
    return r
