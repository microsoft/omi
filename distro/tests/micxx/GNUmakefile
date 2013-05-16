TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = micxx

SOURCES = \
    $(TOP)/tests/base/schema.c \
    test_array.cpp \
    test_datetime.cpp  \
    test_micxx.cpp \
    test_string.cpp

INCLUDES = $(TOP) $(TOP)/common $(TOP)/tests/base

LIBRARIES = micxx base ut io

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
