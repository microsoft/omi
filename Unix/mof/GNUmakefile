TOP = ..
include $(TOP)/config.mak

LIBRARY = mof

SOURCES = state.c heap.c buffer.c mofyacc.c moflex.c types.c ptrarray.c

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CHAR_TYPE=1 MI_CONST= HOOK_BUILD

LIBRARIES = base

include $(TOP)/mak/rules.mak

# We must ignore 'suggest parentheses' warning in YACC generated code.
ifeq ($(COMPILER),GNU)
$(OBJDIRPATH)/mofyacc.o : mofyacc.c
	$(call compilec, mofyacc.c, -Wno-parentheses -Wno-unused)
	
endif

# We must ignore 'Label ??? has no uses' error.
ifeq ($(COMPILER),HP)
$(OBJDIRPATH)/mofyacc.o : mofyacc.c
	$(call compilec, mofyacc.c, +W612 +W2177)
endif

##==============================================================================
##
## Lex and YACC rules
##
##==============================================================================

grammar: lex yacc

yacc:
	yacc -d mof.y
	mv y.tab.c mofyaccinc.c
	mv y.tab.h mofyacc.h

lex:
	flex mof.l
	mv lex.yy.c moflexinc.c
