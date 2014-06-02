TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = Color

SOURCES = \
    ColorBase_Class_Provider.cpp \
    Color_Class_Provider.cpp \
    module.cpp \
    schema.c \
    stubs.cpp

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
    XYZ_ColorBase=ColorBase \
    XYZ_Color=Color

gen:
	$(BINDIR)/omigen --cpp -f schema.mof $(CLASSES)
