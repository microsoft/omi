TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = PresidentProvider

SOURCES = module.c President.c VicePresident.c PresidentLink.c schema.c

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = base

include $(TOP)/mak/rules.mak

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

CLASSES = MSFT_President=President MSFT_PresidentLink=PresidentLink MSFT_VicePresident=VicePresident

gen:
	$(BINDIR)/omigen --nogi MSFT_VicePresident -A schema.mof $(CLASSES)

reg:
	$(BINDIR)/omireg $(TARGET)

instreg:
	cp *.reg "$(TOP)/etc/omiregister/root-test"
