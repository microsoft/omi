TOP = ../..
include $(TOP)/config.mak

LIBRARY = nitsstub

SOURCES = stub.c

DEFINES = UNICODE

ifeq ($(CONFIG_PREFIX),$(CONFIG_SRCDIR))
DEFINES += ENABLE_UNITTESTING
endif

INCLUDES = . $(TOP) $(TOP)/common

ifeq ($(OS), DARWIN)
LIBRARIES = pal
else
LIBRARIES = rt pal
endif

include $(TOP)/mak/rules.mak
