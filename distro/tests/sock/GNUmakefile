TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_sock

SOURCES = \
    test_selector.cpp \
    test_thread.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = sock base io ut

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
