!include $(PROJECT_ROOT)\wmi\winomi\nits\makefile.cmn

TARGETNAME=nits_debug_build_sample
TARGETTYPE=PROGRAM

UMTYPE=console
UMENTRY=main

INCLUDES= $(INCLUDES); \
    $(ADMIN_INC_PATH); \

SOURCES= \
    ..\linkageSample.c \
    ..\linkageSample.rc \

C_DEFINES= $(C_DEFINES) /DUNICODE /D_UNICODE /DDEBUG_BUILD

TARGETLIBS= $(TARGETLIBS) \
    $(ADMIN_LIB_PATH)\pal.lib \

DLLDEF_OBJECTS= \
    $(ADMIN_LIB_PATH)\nitsstub.obj \
