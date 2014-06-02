!include $(PROJECT_ROOT)\wmi\winomi\nits\makefile.cmn

TARGETNAME=nitsbase
TARGETTYPE=LIBRARY

SOURCES= \
    ..\nitsdll.cpp \
    ..\Globals.cpp \
    ..\Run.cpp \
    ..\Switch.cpp \
    ..\nits_c.cpp \
    ..\Frame.cpp \
    ..\LocalInjection.cpp \

RUN_WPP=$(SOURCES) -dll -gen:{um-w2k.tpl}*.tmh