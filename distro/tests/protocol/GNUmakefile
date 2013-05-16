TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_protocol

SOURCES = \
    test_protocol.cpp \
    $(TOP)/tests/base/schema.c

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = micxx protocol sock base io ut

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
