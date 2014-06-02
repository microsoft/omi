TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = mifastener

SOURCES = module.c Widget.c Gadget.c Fastener.c schema.c

INCLUDES = $(TOP)/common

include $(TOP)/mak/rules.mak

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

CLASSES=MSFT_Widget=Widget MSFT_Gadget=Gadget MSFT_Fastener=Fastener 

gen:
	$(BINDIR)/omigen schema.mof $(CLASSES)
