TOP = ../../../..
include $(TOP)/config.mak

CSHLIBRARY = fanprofile

SOURCES = \
    ABC_ElementConformsToProfile.c \
    ABC_Fan.c \
    ABC_RegisteredProfile.c \
    module.c \
    schema.c \
    utils.c

INCLUDES += ..

LIBRARIES = fancommon

CLASSES = ABC_Fan ABC_ElementConformsToProfile ABC_RegisteredProfile 

include $(TOP)/mak/rules.mak

reg:
	$(BINDIR)/omireg -n interop $(TARGET)

gen:
	$(BINDIR)/omigen -m fan schema.mof $(CLASSES)
