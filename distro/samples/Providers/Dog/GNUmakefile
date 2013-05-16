TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = DogProvider

SOURCES = \
    Dog_Class_Provider.cpp \
    module.cpp \
    stubs.cpp \
    schema.c

INCLUDES = $(TOP)/common

LIBRARIES = micxx

include $(TOP)/mak/rules.mak

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

gen:
	$(BINDIR)/omigen --cpp -f schema.mof XYZ_Dog=Dog

reg:
	$(BINDIR)/omireg -n root/omi $(TARGET)

ei:
	$(BINDIR)/omicli ei root/omi XYZ_Dog
