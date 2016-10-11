TOP = ../..
include $(TOP)/config.mak

CXXSHLIBRARY = nits

SOURCES = ../base/Frame.cpp \
    ../base/Globals.cpp \
    ../base/nits_c.cpp \
    ../base/nitsdll.cpp \
    ../base/Run.cpp \
    ../base/Switch.cpp \
    ../base/LocalInjection.cpp \
    ./main.cpp

DEFINES = UNICODE
EXPORTS = libnits.exp

INCLUDES = . $(TOP) $(TOP)/common

ifeq ($(OS),DARWIN)
LIBRARIES = nitspal
else
LIBRARIES = rt nitspal
endif

include $(TOP)/mak/rules.mak

