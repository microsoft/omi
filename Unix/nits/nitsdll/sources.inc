!include $(PROJECT_ROOT)\wmi\winomi\nits\makefile.cmn

TARGETNAME=nitsdll
TARGETTYPE=DYNLINK

LINKER_FLAGS=/MAP:$(OBJ_PATH)\$(O)\nitsdll.map

TARGETLIBS= $(TARGETLIBS) \
    $(PROJECT_OBJ_ROOT)\wmi\winomi\pal\nitspal\\$O\nitspal.lib \
    $(PROJECT_OBJ_ROOT)\wmi\winomi\nits\base\$(OGRP)\$(O)\nitsbase.lib \

SOURCES= \
    ..\main.cpp \
    ..\nitsdll.rc  \

RUN_WPP=$(SOURCES) -dll -gen:{um-w2k.tpl}*.tmh

DLLDEF=
DLLDEF_OBJECTS=\
    $(PROJECT_OBJ_ROOT)\wmi\winomi\nits\base\$(OGRP)\$(O)\nitsdll.obj \
    $(PROJECT_OBJ_ROOT)\wmi\winomi\nits\base\$(OGRP)\$(O)\nits_c.obj \
    $(PROJECT_OBJ_ROOT)\wmi\winomi\nits\base\$(OGRP)\$(O)\run.obj \
    $(PROJECT_OBJ_ROOT)\wmi\winomi\nits\base\$(OGRP)\$(O)\switch.obj \
    $(PROJECT_OBJ_ROOT)\wmi\winomi\nits\base\$(OGRP)\$(O)\globals.obj \