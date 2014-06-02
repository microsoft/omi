#!/usr/bin/python

import mi
import ast
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-n","--NameSpace",action="store",type="string",dest="Namespace",help="Namespace of the instance")
parser.add_option("-c","--ClassName",action="store",type="string",dest="Classname",help="Classname of the instance")
parser.add_option("-k","--Keys",action="store",dest="Keys",help="Key properties of the instance should be a string in format:{'[property1]': foo,'[property2]': foo}")
parser.add_option("-d","--Domain",action="store",type="string",dest="Domain",help="Domain name used to connect to the server")
parser.add_option("-u","--Username",action="store",type="string",dest="Username",help="Username used to connect to the server")
parser.add_option("-p","--Password",action="store",type="string",dest="Password",help="Password used to connect to the server")

(options,args) = parser.parse_args()
if options.Namespace == None:
	parser.error("Namespace cannot be empty!")
if options.Classname == None:
	parser.error("Classname cannot be empty!")
if options.Domain == None:
	parser.error("Domain cannot be empty!")
if options.Username == None:
	parser.error("Username cannot be empty!")
if options.Password == None:
	parser.error("Password cannot be empty!")

session = mi.connect(options.Domain,options.Username,options.Password)
#separate the command with the result
print("\n")
print ("Result:")	

if options.Keys == None:
#if not specified key properties, do an enumerate-instances operation
	enum = session.enumerate_instances(options.Namespace,options.Classname)
	for inst in enum:
		mi.print_instance(inst)

#otherwise, do a get-instance operation
else:
	#evaluate the input string and convert the string into dictionary
	keyProperties = ast.literal_eval(options.Keys)
	inst = session.get_instance(options.Namespace,options.Classname,keyProperties)
	mi.print_instance(inst)

