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

DEFINES = HOOK_BUILD MI_CONST= DETECT_FORBIDDEN_FUNCTIONS

LIBRARIES = provmgr $(MIAPILIB) omi_error wsman xmlserializer http protocol sock wql base $(PALLIBS) micodec mofparser

PKGCONFIGPACKAGES = 

include $(TOP)/mak/rules.mak
