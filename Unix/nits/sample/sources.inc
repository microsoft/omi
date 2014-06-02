!include $(PROJECT_ROOT)\wmi\winomi\nits\makefile.cmn

TARGETNAME=NitsSample
TARGETTYPE=DYNLINK

LINKER_FLAGS=/MAP:$(OBJ_PATH)\$(O)\NitsSample.map

INCLUDES=$(INCLUDES); \
    $(ADMIN_INC_PATH); \

SOURCES= \
        ..\Product.c \
        ..\Shim.c \
        ..\Test.cpp \
        ..\NitsNewInterfaceTests.cpp \
        ..\NitsNewInterfaceTests1.cpp \
        ..\NitsSample.rc

TARGETLIBS= $(TARGETLIBS) \
    $(ADMIN_LIB_PATH)\pal.lib \
    $(ADMIN_LIB_PATH)\nitsdll.lib \

DLLDEF=
DLLDEF_OBJECTS= \
    $(ADMIN_LIB_PATH)\nitsstub.obj \

