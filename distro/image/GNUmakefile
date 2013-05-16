TOP = ..
include $(TOP)/config.mak

$(shell mkdir -p $(OBJDIR)/server)
$(shell mkdir -p $(OBJDIR)/agent)

CPROGRAM = omiimage

SOURCES = \
    image.c \
    ../server/server.c \
    ../agent/agent.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = wsman http protocol sock disp provreg provmgr wql base xml io

PKGCONFIGPACKAGES = openssl

all: $(BINDIR)/omiimage omiserver omiagent

include $(TOP)/mak/rules.mak

omiserver:
	rm -f $(BINDIR)/omiserver
	ln -s $(TARGET) $(BINDIR)/omiserver

omiagent:
	rm -f $(BINDIR)/omiagent
	ln -s $(TARGET) $(BINDIR)/omiagent
