TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = Test_SchemaRetrieval
SOURCES = $(wildcard *.c)

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = omi_error wsman xmlserializer $(BASELIBS) $(PALLIBS)

include $(TOP)/mak/rules.mak

CLASSES = MyEmptyClass MyEmptyDerivedClass MyEmptySecondDerivedClass \
	MySimpleQualClass MyArrayQualClass MySimplePropertiesClass MyEmbeddedPropertiesClass MySimplePropertiesDerivedClass \
	MyFooClass MySimplePropertiesSimpleQualsClass MySimplePropertiesArrayQualsClass MyArrayPropertiesClass \
	MyArrayPropertiesSimpleQualsClass MyArrayPropertiesArrayQualsClass MyNoParamMethodsClass MyNoParamSimpleQualsMethodsClass \
	MyNoParamArrayQualsMethodsClass MySimpleParamMethodsClass MyArrayParamMethodsClass \
	MyArrayParamSimpleQualsMethodsClass MyArrayParamArrayQualsMethodsClass MySimpleParamSimpleQualsMethodsClass \
	MySimpleParamArrayQualsMethodsClass MyReferenceClass MyVariousArrayLengthClass \
	MyOptionTestClass MyOptionTestDerivedClass MyClassForTestingAddedEmbeddedQualifier MyClassRestrictedQualsOnBaseElements MyDerivedClassOfRestrictedQualsOnBaseElements
	

$(LIBRARY): $(OBJECTS)
	$(CC) $(CSHLIBFLAGS) $(OBJECTS) -o $(LIBRARY)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

gen:
	$(BINDIR)/omigen -D -V -M -S -B -m Test_SchemaRetrieval schema.mof $(CLASSES)

reg:
	$(BINDIR)/omireg -n root/cimv2 $(TARGET)

oreg:
	$(BINDIR)/omireg -o localadmin -n root/cimv2 $(TARGET)

start:
	omiserver -l --loglevel 4
