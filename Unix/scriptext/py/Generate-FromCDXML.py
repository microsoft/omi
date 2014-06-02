#!/usr/bin/python

import xml.etree.ElementTree as ET
import sys
import string
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-i","--Input",action="store",type="string",dest="Input",help="Input CDXML file")
parser.add_option("-d","--Domain",action="store",type="string",dest="Domain",help="Domain name used to connect to the server")
parser.add_option("-u","--Username",action="store",type="string",dest="Username",help="Username used to connect to the server")
parser.add_option("-p","--Password",action="store",type="string",dest="Password",help="Password used to connect to the server")
#parser.add_option("-f","--file",action="store",type="string",dest="filename",help="Write result to FILE",metavar="FILE")

(options,args) = parser.parse_args()
if options.Input == None:
	parser.error("Input cdxml cannot be empty!")
if options.Domain == None:
	parser.error("Domain cannot be empty!")
if options.Username == None:
	parser.error("Username cannot be empty!")
if options.Password == None:
	parser.error("Password cannot be empty!")
try:
	tree = ET.parse(options.Input)
#missing file error
except IOError,e: 
	print "%s" % e
	sys.exit(1)
#bad cdxml format error
except Exception,e:
	print "Cannot parse the input CDXML,%s" % e
	sys.exit(1)
root = tree.getroot()

#Get namespace and classname
classElement = root.find('Class')
attrib = classElement.attrib['ClassName']
namespace,classname= attrib.rsplit('/',1)

#new file
scriptFile = None

#Get Default noun
defaultNoun = classElement.find('DefaultNoun').text

#InstanceCmdlets node
instCmd = classElement.find('InstanceCmdlets')

#read global set of parameters
#global boolean to indicate it's getting operation or others
getOperation = False

#Check cmdlet type by checking if child node GetCmdlet exists
getCmd = instCmd.find('GetCmdlet')
if getCmd != None:
	getOperation = True
	#create script get-noun.py
	filename = 'Get-'+defaultNoun+'.py'
	scriptFile = open(filename,'w+')

	#Get parameters if overrided: #add to propertyDict
	propertyDict = {}
	#list of mandatory parameters 
	propertyMand = [] 
	paras = getCmd.find('GetCmdletParameters')
	properties = paras.find('QueryableProperties')
	#for each property, get the name and type of the property
	for pro in properties.findall('Property'):
		pName = pro.attrib['PropertyName']
		typeTag = pro.find('Type')
		pType = typeTag.attrib['PSType']
		propertyDict[pName]=pType
	
		#check QueryType ########################################don't know the difference between query types???#
		queryType = pro.find('RegularQuery')
		if queryType != None:
			queryPara = queryType.find('CmdletParameterMetadata')
			isMandatory = queryPara.attrib['IsMandatory']
			if isMandatory == 'true':
				propertyMand.append(pName)
	
#write cmdlet content to the generated file:
#imports:
scriptFile.write('import mi \n')
scriptFile.write('import ast \n')
scriptFile.write('from optparse import OptionParser \n')
scriptFile.write('\n')

#optparse:
scriptFile.write('parser = OptionParser() \n')
if propertyDict !={}:
	for name in propertyDict:
		optType = propertyDict[name]
		if 'int' in optType:
			scriptFile.write('parser.add_option("--'+name+'", action="store",type="int",'+'dest="'+name+'",help="value of the property:'+name+'"'+')')
		else:
			scriptFile.write('parser.add_option("--'+name+'", action="store",type="'+optType+'",'+'dest="'+name+'",help="value of the property:'+name+'"'+')')

#end of property section
scriptFile.write('\n')
scriptFile.write('(options,args) = parser.parse_args() \n')
#warning of mandatory parameters:
for item in propertyMand:
	scriptFile.write('if options.'+item+' == None: \n')
	scriptFile.write('    parser.error("'+item+' cannot be empty!") \n')		

#connection, get session:
scriptFile.write('\n')
scriptFile.write('session = mi.connect("'+options.Domain+'","'+options.Username+'","'+options.Password+'") \n')
scriptFile.write('\n')

#Get-instance:
#make the key instance based on the key and input
if getOperation and propertyDict !={}:
		for name in propertyDict:
			scriptFile.write('keyProperties = {} \n')
			scriptFile.write('propertyValue = '+'options.'+name +'\n')
			scriptFile.write('keyProperties["'+name+'"] = propertyValue'+'\n')
scriptFile.write('\n')

#api call
scriptFile.write('inst = session.get_instance("'+namespace+'","'+classname+'",keyProperties) \n')
scriptFile.write('mi.print_instance(inst)')
