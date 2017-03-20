import omi
from omi import *

import schema

import sys
import os


HOST_FILE_NAME = '/etc/hosts'
TEMP_HOST_FILE_NAME = '/etc/~hosts'


def Load (module, context):
    be = BookEnd ('Load (Hosts module)')
    context.PostResult (MI_RESULT_OK)


def Unload (module, context):
    be = BookEnd ('Unload (Hosts module)')
    context.PostResult (MI_RESULT_OK)


def Hosts_Load (
    module, context):
    be = BookEnd ('Hosts_Load')
    context.PostResult (MI_RESULT_OK)


def Hosts_Unload (
    context):
    be = BookEnd ('Hosts_Unload')
    context.PostResult (MI_RESULT_OK)


def Hosts_EnumerateInstances (
    context, nameSpace, className, propertySet, keysOnly):
    be = BookEnd ('Hosts_EnumerateInstances')
    BookEndPrint ('Sanity Check')
    f = open (HOST_FILE_NAME, 'r')
    for line in f:
        line = line.strip ()
        if len (line) > 0 and not line.startswith ('#'):
            IPAddress, FQDN = parse_line (line)
            IPAddress = MI_String (IPAddress)
            FQDN = MI_String (FQDN)
            instance = context.NewInstance ('Hosts')
            instance.SetValue ('FQDN', FQDN)
            if not keysOnly.value:
                instance.SetValue ('IPAddress', IPAddress)
            context.PostInstance (instance)
    f.close ()
    context.PostResult (MI_RESULT_OK)


def Hosts_GetInstance (
    context, nameSpace, className, instanceName, propertySet):
    be = BookEnd ('Hosts_GetInstance')
    name = instanceName.GetValue ('FQDN')
    BookEndPrint ('FQDN: "' + str (name) + '"')
    f = open (HOST_FILE_NAME, 'r')
    found = False
    for line in f:
        line = line.strip ()
        if len (line) > 0 and not line.startswith ('#'):
            IPAddress, FQDN = parse_line (line)
            if FQDN == name.value:
                instance = context.NewInstance ('Hosts')
                instance.SetValue ('FQDN', MI_String (FQDN))
                instance.SetValue ('IPAddress', MI_String (IPAddress))
                context.PostInstance (instance)
                context.PostResult (MI_RESULT_OK)
                found = True
                break
    f.close ()
    if not found:
        context.PostResult (MI_RESULT_NOT_FOUND)


def Hosts_CreateInstance (
    context, nameSpace, className, instance):
    fqdn = instance.GetValue ('FQDN')
    BookEndPrint ('FQDN: "' + str (fqdn) + '"')
    ipAddress = instance.GetValue ('IPAddress')
    BookEndPrint ('IPAddress: "' + str (ipAddress) + '"')
    fin = open (HOST_FILE_NAME, 'r')
    fout = open (TEMP_HOST_FILE_NAME, 'w')
    exists = False
    for line in fin:
        line = line.strip ()
        if len (line) > 0 and not line.startswith ('#'):
            IPAddress, FQDN = parse_line (line)
            if FQDN == fqdn.value:
                exists = True
                break
            fout.write (IPAddress.ljust(15, ' ')  + ' ' + FQDN + '\n')
        else:
            fout.write (line + '\n')
    fin.close ()
    if not exists:
        fout.write ('# this entry created with the Python script provider\n')
        fout.write (ipAddress.value.ljust(15, ' ')  + ' ' + \
                    fqdn.value + '\n')
        fout.close ()
        os.rename (TEMP_HOST_FILE_NAME, HOST_FILE_NAME)
        context.PostResult (MI_RESULT_OK)
    else:
        fout.close ()
        context.PostResult (MI_RESULT_ALREADY_EXISTS)


def Hosts_ModifyInstance (
    context, nameSpace, className, instance, propertySet):
    be = BookEnd ('Hosts_ModifyInstance')
    fqdn = instance.GetValue ('FQDN')
    BookEndPrint ('FQDN: "' + str (fqdn) + '"')
    ipAddress = instance.GetValue ('IPAddress')
    BookEndPrint ('IPAddress: "' + str (ipAddress) + '"')
    fin = open (HOST_FILE_NAME, 'r')
    fout = open (TEMP_HOST_FILE_NAME, 'w')
    exists = False
    for line in fin:
        line = line.strip ()
        if len (line) > 0 and not line.startswith ('#'):
            IPAddress, FQDN = parse_line (line)
            if FQDN == fqdn.value:
                BookEndPrint ('--found it--')
                IPAddress = ipAddress.value
                exists = True
            fout.write (IPAddress.ljust(15, ' ')  + ' ' + FQDN + '\n')
        else:
            fout.write (line + '\n')
    fin.close ()
    fout.close ()
    if exists:
        context.PostResult (MI_RESULT_OK)
        os.rename (TEMP_HOST_FILE_NAME, HOST_FILE_NAME)
    else:
        context.PostResult (MI_RESULT_NOT_FOUND)


def Hosts_DeleteInstance (
    context, nameSpace, className, instanceName):
    be = BookEnd ('Hosts_DeleteInstance')
    fqdn = instanceName.GetValue ('FQDN')
    BookEndPrint ('FQDN: "' + str (fqdn) + '"')
    fin = open (HOST_FILE_NAME, 'r')
    fout = open (TEMP_HOST_FILE_NAME, 'w')
    exists = False
    for line in fin:
        line = line.strip ()
        BookEndPrint ('--line--')
        if len (line) > 0 and not line.startswith ('#'):
            IPAddress, FQDN = parse_line (line)
            if FQDN == fqdn.value:
                BookEndPrint ('found it')
                exists = True
            else:
                BookEndPrint ('not it')
                fout.write (IPAddress.ljust(15, ' ')  + ' ' + FQDN + '\n')
        else:
            fout.write (line + '\n')
    fin.close ()
    fout.close ()
    if exists:
        os.rename (TEMP_HOST_FILE_NAME, HOST_FILE_NAME)
        context.PostResult (MI_RESULT_OK)
    else:
        context.PostResult (MI_RESULT_NOT_FOUND)


def Hosts_Ping (
    context, nameSpace, className, methodName, instanceName, parameters):
    be = BookEnd ('Hosts_Ping')
    outParams = context.NewParameters ('Hosts', 'Ping')
    outParams.SetValue ('MIReturn', MI_Uint64 (123))
    context.PostInstance (outParams)
    context.PostResult (MI_RESULT_OK)


def mi_main ():
    be = BookEnd ('mi_main')
    r = MI_Module (schema.schema, Load, Unload)
    return r

    
def parse_line (line):
    return line.split (None, 1)
