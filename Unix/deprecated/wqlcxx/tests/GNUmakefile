TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = test_wqlcxx

SOURCES = test_wqlcxx.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = wqlcxx wql base ut

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)
