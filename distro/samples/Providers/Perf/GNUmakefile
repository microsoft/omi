TOP = ../../..

include $(TOP)/config.mak

CSHLIBRARY = PerfProvider

SOURCES = $(wildcard *.c)

INCLUDES = $(TOP)/common $(TOP)

LIBRARIES = micxx base io

include $(TOP)/mak/rules.mak

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

CLASSES = OMI_Perf

gen:
	$(BINDIR)/omigen -f schema.mof $(CLASSES)

reg:
	$(BINDIR)/omireg -n root/omi $(TARGET)

ei:
	$(BINDIR)/omicli ei -q -S root/omi OMI_Perf

help:
	$(BINDIR)/omicli -h
