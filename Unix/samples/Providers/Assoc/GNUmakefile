TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = AssocCXX

SOURCES =  \
    module.cpp \
    schema.c \
    stubs.cpp \
    XYZ_Assoc2_Class_Provider.cpp \
    XYZ_Assoc_Class_Provider.cpp \
    XYZ_Gadget2_Class_Provider.cpp \
    XYZ_Gadget_Class_Provider.cpp \
    XYZ_Widget2_Class_Provider.cpp \
    XYZ_Widget_Class_Provider.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = micxx base

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

CLASSES = XYZ_Widget XYZ_Gadget XYZ_Assoc XYZ_Widget2 XYZ_Gadget2 XYZ_Assoc2

gen:
	$(BINDIR)/omigen --cpp -D -f schema.mof $(CLASSES)

reg:
	$(BINDIR)/omireg $(TARGET)

