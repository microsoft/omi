TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = fan

SOURCES = \
    ABC_EthernetPort.c \
    ABC_VLANEndpoint.c \
    module.c \
    schema.c

INCLUDES = ..

LIBRARIES = network

CLASSES = ABC_EthernetPort ABC_VLANEndpoint

include $(TOP)/mak/rules.mak

reg:
	$(BINDIR)/omireg -n root/omi $(TARGET)

gen:
	$(BINDIR)/omigen -C ./schema/CIM_Schema.mof -m fan schema.mof $(CLASSES)
