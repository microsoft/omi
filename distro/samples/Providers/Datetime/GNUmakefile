TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = DatetimeProvider

SOURCES = \
    Datetime.c \
    module.c \
    schema.c

INCLUDES = $(TOP)/common

include $(TOP)/mak/rules.mak

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

gen:
	$(BINDIR)/omigen -f schema.mof OMI_Datetime=Datetime

reg:
	$(BINDIR)/omireg -n root/cimv2 $(TARGET)
