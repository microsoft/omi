TOP = ..
include $(TOP)/config.mak

ifdef HPUX_PARISC_HP
  CXXPROGRAM = omiagent
  SOURCES = agent.c agentmaincxx.cpp
else
  CPROGRAM = omiagent
  SOURCES = agent.c agent_main.c
endif

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = provmgr wsman http protocol sock wql base io

PKGCONFIGPACKAGES = 

include $(TOP)/mak/rules.mak


# Support for purify of agent libraries

ifeq ($(ENABLE_PURIFY_AGENT),1)

PUREOPTIONS = -follow-child-processes=yes -locking=no \
    -always-use-cache-dir -cache-dir=$(PURIFY_TMP)/cache
PURIFY_WRAPPER = $(PURIFY_HOME)/purify $(PUREOPTIONS)
# May need library: $(PURIFY_HOME)/libpurify_stubs.a

CC:=$(PURIFY_WRAPPER) $(CC)

endif
