TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = TesterProvider

SOURCES = \
    module.cpp \
    OMI_Tester_Class_Provider.cpp \
    schema.c \
    stubs.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = micxx base io

include $(TOP)/mak/rules.mak

gen:
	$(BINDIR)/omigen --cpp schema.mof OMI_Tester

reg:
	$(BINDIR)/omireg $(TARGET)
