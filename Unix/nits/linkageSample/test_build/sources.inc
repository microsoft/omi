!include $(PROJECT_ROOT)\wmi\winomi\nits\makefile.cmn

TARGETNAME=nits_test_build_sample
TARGETTYPE=DYNLINK

INCLUDES=$(INCLUDES); \
         $(ADMIN_INC_PATH); \

SOURCES= \
        ..\linkageSample.cpp \
        ..\linkageSample.rc

TARGETLIBS=  $(TARGETLIBS) \
    $(ADMIN_LIB_PATH)\pal.lib \
    $(ADMIN_LIB_PATH)\nitsdll.lib \

DLLDEF_OBJECTS= \
    $(ADMIN_LIB_PATH)\nitsstub.obj \

C_DEFINES=$(C_DEFINES) /D_UNICODE /DUNICODE /DTEST_BUILD

DLLDEF=