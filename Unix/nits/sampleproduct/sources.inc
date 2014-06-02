!include $(PROJECT_ROOT)\wmi\winomi\nits\makefile.cmn

TARGETNAME=NitsSampleProduct
TARGETTYPE=DYNLINK

INCLUDES=$(INCLUDES); \
    $(ADMIN_INC_PATH); \

SOURCES= \
        ..\sampleproduct.cpp \
        ..\NitsSampleProduct.rc

TARGETLIBS= $(TARGETLIBS) \
    $(ADMIN_LIB_PATH)\pal.lib \

C_DEFINES=$(C_DEFINES) /D_UNICODE /DUNICODE /DHOOK_BUILD

DLLDEF=
DLLDEF_OBJECTS= \
    $(ADMIN_LIB_PATH)\nitsstub.obj \

