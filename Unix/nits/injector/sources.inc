!include $(PROJECT_ROOT)\wmi\winomi\nits\makefile.cmn

TARGETNAME=nitsinj
TARGETTYPE=DYNLINK

LINKER_FLAGS=/MAP:$(OBJ_PATH)\$(O)\nitsinj.map

TARGETLIBS= $(TARGETLIBS) \
    $(ADMIN_LIB_PATH)\pal.lib \

SOURCES= \
    ..\injector.cpp \
    ..\nitsinj.rc  \

DLLDEF=
