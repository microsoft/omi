#!/usr/bin/python

import mi
import sys
import ast
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-n","--Namespace",action="store",type="string",dest="Namespace",help="Namespace of the instance")
parser.add_option("-c","--Classname",action="store",type="string",dest="Classname",help="ClassName of the instance")
parser.add_option("-k","--Key",action="store",dest="Keys",help="Key properties of the instance should be a string in format:{'[property1]': foo,'[property2]': foo}")
parser.add_option("-m","--Methodname",action="store",type="string",dest="Method",help="Method name")
parser.add_option("-a","--Arguments",action="store",type="string",dest="Arguments",help="Arguments to the function")
parser.add_option("-d","--Domain",action="store",type="string",dest="Domain",help="Domain name used to connect to the server")
parser.add_option("-u","--Username",action="store",type="string",dest="Username",help="Username used to connect to the server")
parser.add_option("-p","--Password",action="store",type="string",dest="Password",help="Password used to connect to the server")

(options,args) = parser.parse_args()
if options.Namespace == None:
	parser.error("Namespace cannot be empty!")
if options.Classname == None:
	parser.error("Classname cannot be empty!")
if options.Method ==None:
	parser.error("Method name cannot be empty!")
if options.Domain == None:
	parser.error("Domain cannot be empty!")
if options.Username == None:
	parser.error("Username cannot be empty!")
if options.Password == None:
	parser.error("Password cannot be empty!")

session = mi.connect(options.Domain,options.Username,options.Password)
if options.Keys != None:
	#evaluate the input string and convert the string into dictionary
	try:	
		keyProperties = ast.literal_eval(options.Keys)
	except ValueError:
		print 'Key properties '+options.Keys+' should be in the format "{'+"'"+'propertyName'+"'"+':value}"'
		sys.exit(1)
	if keyProperties == {}:
		parser.error("Key instance cannot be empty!")
	inst = session.get_instance(options.Namespace,options.Classname,keyProperties)
	#separate the command with the result
	print("\n")
	print ("Result:")	
	res = session.invoke(options.Namespace,options.Method,argList = options.Arguments,instance = inst)
	mi.print_instance(res)

