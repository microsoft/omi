TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_wsman

SOURCES = test_wsman.c

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = xml

ARGUMENTS = cimns.xml

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) *.xml
