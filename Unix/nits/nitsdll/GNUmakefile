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

INCLUDES = . $(TOP) $(TOP)/common

LIBRARIES = rt nitspal

include $(TOP)/mak/rules.mak
