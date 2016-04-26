TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = Number

SOURCES = \
    module.c \
    Number.c \
    schema.c

INCLUDES = $(TOP) $(TOP)/common 

include $(TOP)/mak/rules.mak

CLASSES = XYZ_Number=Number

LIBRARIES = omi_error wsman http xmlserializer protocol sock base pal nits

gen:
	$(BINDIR)/omigen -f schema.mof $(CLASSES)

reg:
	$(BINDIR)/omireg $(TARGET)
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test#c/"

reg2:
	cp $(CSHLIBRARY).reg "$(TOP)/etc/omiregister/test#c/"
