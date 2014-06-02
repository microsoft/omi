TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = octetstrings

SOURCES = \
    module.c \
    OMI_OctetStrings.c \
    schema.c

INCLUDES = ..

LIBRARIES =

CLASSES = OMI_OctetStrings

include $(TOP)/mak/rules.mak

reg:
	$(BINDIR)/omireg -n root/omi $(TARGET)

gen:
	$(BINDIR)/omigen -B -m octetstrings schema.mof $(CLASSES)

tests:
	$(BINDIR)/omicli ei root/omi OMI_OctetStrings
