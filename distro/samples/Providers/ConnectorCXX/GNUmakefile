TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = ConnectorProviderCXX

SOURCES = \
    BaseAssoc_Class_Provider.cpp \
    Base_Class_Provider.cpp \
    Connector_Class_Provider.cpp \
    DerivedAssoc_Class_Provider.cpp \
    Derived_Class_Provider.cpp \
    Gadget_Class_Provider.cpp \
    module.cpp \
    Order_Class_Provider.cpp \
    schema.c \
    stubs.cpp \
    Widget_Class_Provider.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = micxx base

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

CLASSES = \
    XYZ_Widget=Widget \
    XYZ_Gadget=Gadget \
    XYZ_Connector=Connector \
    XYZ_Order=Order \
    XYZ_Base=Base \
    XYZ_Derived=Derived \
    XYZ_BaseAssoc=BaseAssoc \
    XYZ_DerivedAssoc=DerivedAssoc

gen:
	$(BINDIR)/omigen --cpp -D -f schema.mof $(CLASSES)
