TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = TestMapOfInstances

SOURCES = schema.c main.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = micxx ut io

include $(TOP)/mak/rules.mak

CLASSES = ABC_Widget ABC_Gadget ABC_Connector

gen:
	$(BINDIR)/omigen -n --cpp schema.mof $(CLASSES)
	rm -f module.cpp ABC_Connector_Class_Provider.* ABC_Gadget_Class_Provider.* ABC_Widget_Class_Provider.* stubs.cpp

tests:
	$(TARGET)
