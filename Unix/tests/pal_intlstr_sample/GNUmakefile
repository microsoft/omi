TOP = ../..
include $(TOP)/config.mak

CPROGRAM = pal_intlstr_sample

SOURCES = $(TOP)/ut/omitestcommon.cpp $(TOP)/ut/omifaultsimtest.cpp \
	main.c \

DEFINES = HOOK_BUILD 

INCLUDES = . $(TOP) $(TOP)/common $(TOP)/nits/base

LIBRARIES = $(PALLIBS)

include $(TOP)/mak/rules.mak

