TOP = ../..
include $(TOP)/config.mak

CXXPROGRAM = nits

SOURCES = nits.cpp

DEFINES = UNICODE 

INCLUDES = . $(TOP) $(TOP)/common

ifeq ($(OS), DARWIN)
LIBRARIES = nits pal
else
LIBRARIES = nits pal rt
endif

include $(TOP)/mak/rules.mak
