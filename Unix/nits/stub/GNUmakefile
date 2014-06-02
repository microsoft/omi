TOP = ../..
include $(TOP)/config.mak

LIBRARY = nitsstub

SOURCES = stub.c

DEFINES = UNICODE

ifeq ($(CONFIG_PREFIX),$(CONFIG_SRCDIR))
DEFINES += ENABLE_UNITTESTING
endif

INCLUDES = . $(TOP) $(TOP)/common

LIBRARIES = rt pal

include $(TOP)/mak/rules.mak
