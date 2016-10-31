TOP = ../..

include $(TOP)/config.mak

CXXSHLIBRARY = httpclientcxx

SOURCES = httpclientcxx.cpp

INCLUDES = $(TOP) $(TOP)/common

LIBRARIES = http protocol logging $(BASELIBS) $(PALLIBS)

DEFINES = BUILDING_HTTPCLIENT

include $(TOP)/mak/rules.mak

