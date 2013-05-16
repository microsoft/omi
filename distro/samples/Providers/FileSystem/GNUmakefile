TOP = ../../..
include $(TOP)/config.mak

CSHLIBRARY = filesys

SOURCES = \
    module.c \
    MSFT_DataFile.c \
    MSFT_Directory.c \
    MSFT_DirectoryContainsFile.c \
    schema.c \
    dir.c

INCLUDES += $(TOP)/common $(TOP)

LIBRARIES += base

CLASSES = MSFT_DataFile MSFT_Directory MSFT_DirectoryContainsFile

include $(TOP)/mak/rules.mak

reg:
	$(BINDIR)/omireg -n root/omi $(TARGET)

gen:
	$(BINDIR)/omigen -m filesys schema.mof $(CLASSES)

tests:
	omicli a root/omi -rc MSFT_Directory { MSFT_Directory Name /opt }
