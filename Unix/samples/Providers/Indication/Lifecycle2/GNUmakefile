TOP = ../../../..
include $(TOP)/config.mak

CSHLIBRARY = lifecycle2

SOURCES = \
    module.c \
    ABC_Process.c \
    ABC_ProcessCreation.c \
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
CLASSES = ABC_Process ABC_ProcessCreation

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
