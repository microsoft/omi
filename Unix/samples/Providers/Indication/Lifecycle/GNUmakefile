TOP = ../../../..
include $(TOP)/config.mak

CSHLIBRARY = lifecycle

SOURCES = \
    module.c \
    XYZ_Process.c \
    XYZ_ComputerSystem.c \
    schema.c \

INCLUDES = ../util $(TOP) $(TOP)/common

include $(TOP)/mak/rules.mak

##==============================================================================
##
## Define macros; See MI.h for MI_API_VERSION details
##
##==============================================================================
DEFINES = HOOK_BUILD MI_API_VERSION=2

LIBRARIES = util

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================
CLASSES = XYZ_Process XYZ_ComputerSystem

gen:
	$(BINDIR)/omigen -f schema.mof $(CLASSES)

##==============================================================================
##
## Register
##
##==============================================================================
reg:
	$(BINDIR)/omireg -n root/sample $(TARGET)

regoop:
	$(BINDIR)/omireg -n oop/sample -o @requestor@ $(TARGET)

##==============================================================================
##
## dep -- rule to build dependent libraries.
##
##==============================================================================
dep:
	( cd ../util; $(MAKE); )
