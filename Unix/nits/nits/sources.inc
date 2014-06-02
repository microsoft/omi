!include $(PROJECT_ROOT)\wmi\winomi\nits\makefile.cmn

TARGETNAME=nits
TARGETTYPE=PROGRAM

UMTYPE=console
UMENTRY=main

TARGETLIBS= $(TARGETLIBS) \
    $(ADMIN_LIB_PATH)\nitsdll.lib \
    $(PROJECT_OBJ_ROOT)\wmi\winomi\pal\nitspal\\$O\nitspal.lib \

LINKER_FLAGS=/MAP:$(OBJ_PATH)\$(O)\nits.map

SOURCES= \
    ..\nits.cpp \
    ..\nits.rc