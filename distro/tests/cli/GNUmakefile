TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_cli

SOURCES = test_cli.cpp \
    ../../cli/cli.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = omiclient micxx wql base ut io

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(TESTOPTS)
