TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = chkxml

SOURCES = chkxml.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = xml base io

ARGUMENTS = cimns.xml

include $(TOP)/mak/rules.mak

tests:
	$(BINDIR)/chkxml cim.xml
