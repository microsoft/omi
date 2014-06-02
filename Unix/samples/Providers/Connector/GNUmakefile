TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = Connector

SOURCES = \
    Connector.c \
    Gadget.c \
    module.c \
    Order.c \
    schema.c \
    Widget.c \
    Base.c \
    Derived.c \
    BaseAssoc.c \
    DerivedAssoc.c

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = pal

include $(TOP)/mak/rules.mak

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
	$(BINDIR)/omigen -D -f schema.mof $(CLASSES)

reg:
	$(BINDIR)/omireg -n root/omi $(TARGET)
