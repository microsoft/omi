import imp
import os
#import socket
import sys


import omi
from omi import *


#import bookend
#from bookend import *

#import mi_protocol
#from mi_protocol import *

#import mi_schema
#import mi_context


#class Client:
#    fd = None
#    path = None
#    schema = None
#    provider = None
#    
#    def __init__ (self, _fd, _path):
#        be = VerboseBookEnd ('Client.__init__')
#        #self.fd = \
#        #    socket.fromfd (int (_fd), socket.AF_UNIX, socket.SOCK_STREAM)
#        self.path = _path
#        
#    def __del__ (self):
#        be = VerboseBookEnd ('Client.__del__')
#        #self.fd.close ()
#
#    def run (self):
#        be = BookEnd ('Client.run')
#        sys.path.append (self.path)
#        BookEndPrint ('path: "' + self.path + '"')
#        
#        #self.provider = __import__ ('mi_main')
#        #
#        #self.schema = self.provider.mi_main ()
#        #self.schema.send (self.fd)
#        #finished = False
#        #while True != finished:
#        #    opcode = read_opcode (self.fd)
#        #    op = {
#        #        OPCODE_MODULE_LOAD: self.handle_module_load,
#        #        OPCODE_MODULE_UNLOAD: self.handle_module_unload,
#        #        OPCODE_CLASS_LOAD: self.handle_class_load,
#        #        OPCODE_CLASS_UNLOAD: self.handle_class_unload,
#        #        OPCODE_ENUMERATE_INSTANCES: self.handle_enumerate_instances,
#        #        OPCODE_GET_INSTANCE: self.handle_get_instance,
#        #        OPCODE_CREATE_INSTANCE: self.handle_create_instance,
#        #        OPCODE_MODIFY_INSTANCE: self.handle_modify_instance,
#        #        OPCODE_DELETE_INSTANCE: self.handle_delete_instance,
#        #        }.get (opcode, None)
#        #    if op is not None:
#        #        finished = op ()
#        #    else:
#        #        finished = True
#
#
#    #def handle_module_load (self):
#    #    be = BookEnd ('Client.handle_module_load')
#    #    self.provider.Load (mi_context.Context (self))
#    #    return False
#
#
#    #def handle_module_unload (self):
#    #    be = BookEnd ('Client.handle_module_unload')
#    #    self.provider.Unload (mi_context.Context (self))
#    #    return True
#
#
#    #def handle_class_load (self):
#    #    be = BookEnd ('Client.handle_class_load')
#    #    className = read_string (self.fd)
#    #    BookEndPrint ('name: "' + className + '"')
#    #    fn = self.get_class_method (className, '_Load')
#    #    if fn is not None:
#    #        BookEndPrint ('method is not None')
#    #        fn (mi_context.Context (self))
#    #    else:
#    #        BookEndPrint ('method is None')
#    #        write_opcode (OPCODE_POST_RESULT, self.fd)
#    #        write_uint32 (MI_RESULT_INVALID_CLASS, self.fd)
#    #    return False
#
#
#    #def handle_class_unload (self):
#    #    be = BookEnd ('Client.handle_class_unload')
#    #    className = read_string (self.fd)
#    #    VerboseBookEndPrint ('name: "' + className + '"')
#    #    fn = self.get_class_method (className, '_Unload')
#    #    if fn is not None:
#    #        fn (mi_context.Context (self))
#    #    else:
#    #        write_opcode (OPCODE_POST_RESULT, self.fd)
#    #        write_uint32 (MI_RESULT_INVALID_CLASS, self.fd)
#    #    return False
#
#
#    #def handle_enumerate_instances (self):
#    #    be = BookEnd ('Client.handle_enumerate_instances')
#    #    className = read_string (self.fd)
#    #    keysOnly = read_boolean (self.fd)
#    #    VerboseBookEndPrint ('name: "' + className + '"')
#    #    fn = self.get_class_method (className, '_EnumerateInstances')
#    #    if fn is not None:
#    #        fn (mi_context.Context (self), keysOnly)
#    #    else:
#    #        write_opcode (OPCODE_POST_RESULT, self.fd)
#    #        write_uint32 (MI_RESULT_INVALID_CLASS, self.fd)
#    #    return False
#
#
#    #def handle_get_instance (self):
#    #    be = BookEnd ('Client.handle_get_instance')
#    #    className = read_string (self.fd)
#    #    VerboseBookEndPrint ('name: "' + className + '"')
#    #    instance = MI_Instance.read (0, self.fd)
#    #    if instance.className == className:
#    #        VerboseBookEndPrint ('class names match')
#    #        createFn = self.get_class_method (className, '_Create')
#    #        fn = self.get_class_method (className, '_GetInstance')
#    #        if createFn is not None and fn is not None:
#    #            cInstance = createFn (instance)
#    #            fn (mi_context.Context (self), cInstance)
#    #        else:
#    #            write_opcode (OPCODE_POST_RESULT, self.fd)
#    #            write_uint32 (MI_RESULT_INVALID_CLASS, self.fd)
#    #    else:
#    #        BookEndPrint ('class names do not match!')
#    #        write_opcode (OPCODE_POST_RESULT, self.fd)
#    #        write_uint32 (MI_RESULT_INVALID_CLASS, self.fd)
#    #    return False
#
#
#    #def handle_create_instance (self):
#    #    be = BookEnd ('Client.handle_create_instance')
#    #    className = read_string (self.fd)
#    #    VerboseBookEndPrint ('name: "' + className + '"')
#    #    instance = MI_Instance.read (0, self.fd)
#    #    if instance.className == className:
#    #        VerboseBookEndPrint ('class names match')
#    #        createFn = self.get_class_method (className, '_Create')
#    #        fn = self.get_class_method (className, '_CreateInstance')
#    #        if createFn is not None and fn is not None:
#    #            cInstance = createFn (instance)
#    #            fn (mi_context.Context (self), cInstance)
#    #        else:
#    #            write_opcode (OPCODE_POST_RESULT, self.fd)
#    #            write_uint32 (MI_RESULT_INVALID_CLASS, self.fd)
#    #    else:
#    #        BookEndPrint ('class names do not match!')
#    #        write_opcode (OPCODE_POST_RESULT, self.fd)
#    #        write_uint32 (MI_RESULT_INVALID_CLASS, self.fd)
#    #    return False
#
#
#    #def handle_modify_instance (self):
#    #    be = BookEnd ('Client.handle_modify_instance')
#    #    className = read_string (self.fd)
#    #    VerboseBookEndPrint ('name: "' + className + '"')
#    #    instance = MI_Instance.read (0, self.fd)
#    #    if instance.className == className:
#    #        VerboseBookEndPrint ('class names match')
#    #        createFn = self.get_class_method (className, '_Create')
#    #        fn = self.get_class_method (className, '_ModifyInstance')
#    #        if createFn is not None and fn is not None:
#    #            cInstance = createFn (instance)
#    #            fn (mi_context.Context (self), cInstance)
#    #        else:
#    #            write_opcode (OPCODE_POST_RESULT, self.fd)
#    #            write_uint32 (MI_RESULT_INVALID_CLASS, self.fd)
#    #    else:
#    #        BookEndPrint ('class names do not match!')
#    #        write_opcode (OPCODE_POST_RESULT, self.fd)
#    #        write_uint32 (MI_RESULT_INVALID_CLASS, self.fd)
#    #    return False
#
#
#    #def handle_delete_instance (self):
#    #    be = BookEnd ('Client.handle_delete_instance')
#    #    className = read_string (self.fd)
#    #    VerboseBookEndPrint ('name: "' + className + '"')
#    #    instance = MI_Instance.read (0, self.fd)
#    #    if instance.className == className:
#    #        VerboseBookEndPrint ('class names match')
#    #        createFn = self.get_class_method (className, '_Create')
#    #        fn = self.get_class_method (className, '_DeleteInstance')
#    #        if createFn is not None and fn is not None:
#    #            cInstance = createFn (instance)
#    #            fn (mi_context.Context (self), cInstance)
#    #        else:
#    #            write_opcode (OPCODE_POST_RESULT, self.fd)
#    #            write_uint32 (MI_RESULT_INVALID_CLASS, self.fd)
#    #    else:
#    #        BookEndPrint ('class names do not match!')
#    #        write_opcode (OPCODE_POST_RESULT, self.fd)
#    #        write_uint32 (MI_RESULT_INVALID_CLASS, self.fd)
#    #    return False
#    
#
#    #def recv_msg (self):
#    #    be = VerboseBookEnd ('Client.recv_msg')
#    #    opcode = read_sint8 (self.fd)
#
#    #def get_class_method (self, className, fnName):
#    #    be = BookEnd ('Client.get_class_method')
#    #    BookEndPrint (className + '.' + fnName)
#    #    fn = None
#    #    c = self.schema.get_class (className)
#    #    if c is not None:
#    #        BookEndPrint ('c is not None')
#    #        name = getattr (c._functionTable, fnName)
#    #        if name is not None:
#    #            BookEndPrint ('name is not None')
#    #            fn = getattr (self.provider, name)
#    #            if fn is None:
#    #                BookEndPrint ('fn is None')
#    #            else:
#    #                BookEndPrint ('fn is not None')
#    #        else:
#    #            BookEndPrint ('name is None')
#    #    else:
#    #        BookEndPrint ('c is None')
#    #    return fn
        

def main (argv = None):
    be = BookEnd ('main')

    for i in range (len (argv)):
        BookEndPrint ('args[' + str (i) + ']: "' + argv[i] + '"')

    #if DO_TRACE:
    #    for i in range (len (argv)):
    #        BookEndPrint ('args[' + str (i) + ']: "' + argv[i] + '"')

    if len (argv) == 3:
        try:
            fd = int (argv[1])
            
            #BookEndPrint ('fd: ' + argv[1])
            
            path = os.path.split (os.path.realpath (argv[0]))[0] + '/' + argv[2]
            #BookEndPrint ('path: "' + path + '"')


            #sys.path.append (path)
            #BookEndPrint ('path: ' + str (sys.path))


            client = Client (fd, path)
            client.run ()

            
        #except SocketClosed:
        #    BookEndPrint ('Disconnected from provider')
        except:
            e = sys.exc_info ()[0]
            sys.stderr.write ('Unhandled exception: ' + str(e) + '\n')
            raise
    else:
        sys.stderr.write ('Usage: client.py [SOCKET_ID] [PROVIDER]\n')


if __name__ == '__main__':
    sys.exit (main (sys.argv))
