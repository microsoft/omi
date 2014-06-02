!include $(PROJECT_ROOT)\wmi\winomi\nits\makefile.cmn

TARGETNAME=nits_default_linkage_sample
TARGETTYPE=PROGRAM

UMTYPE=console
UMENTRY=main

INCLUDES= $(INCLUDES); \
    $(ADMIN_INC_PATH); \

SOURCES= \
    ..\linkageSample.c \
    ..\linkageSample.rc \

# TODO: Fix this; this should compile without HOOK_BUILD but on x86 it is not
C_DEFINES= $(C_DEFINES) /DUNICODE /D_UNICODE /DHOOK_BUILD

TARGETLIBS= $(TARGETLIBS) \
    $(ADMIN_LIB_PATH)\pal.lib \