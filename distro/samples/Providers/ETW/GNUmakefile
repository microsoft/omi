TOP = ../../..

include $(TOP)/config.mak

CSHLIBRARY = ETWProvider

SOURCES = $(wildcard *.c)

INCLUDES = $(TOP)/common $(TOP)

LIBRARIES = micxx base io

CACHEGRIND_ARGS = $(BINDIR)/omicli ei -q -S root/omi MILargeEvent

include $(TOP)/mak/rules.mak

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

CLASSES = MILargeEvent

gen:
	$(BINDIR)/omigen -f schema.mof $(CLASSES)

reg:
	$(BINDIR)/omireg -n root/omi $(TARGET)

ei:
	$(BINDIR)/omicli ei -q -S root/omi MILargeEvent
	( cd $(TOP); $(MAKE) stop )
