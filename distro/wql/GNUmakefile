TOP = ..
include $(TOP)/config.mak

LIBRARY = wql

SOURCES = wql.c wqlyacc.c output.c lexer.c identical.c

INCLUDES = $(TOP) $(TOP)/common

include $(TOP)/mak/rules.mak

# We must ignore 'suggest parentheses' warning in YACC generated code.
ifeq ($(COMPILER),GNU)
$(OBJDIRPATH)/wqlyacc.o : wqlyacc.c
	$(call compilec, wqlyacc.c, -Wno-parentheses -Wno-unused)
endif

# We must ignore 'Label ??? has no uses' error.
ifeq ($(COMPILER),HP)
$(OBJDIRPATH)/wqlyacc.o : wqlyacc.c
	$(call compilec, wqlyacc.c, +W612 +W2177)
endif

# Cancel the .y -> .c rule.
%.c : %.y

yacc:
	yacc -p wql -d wql.y
	mv y.tab.c wqlyaccinc.c
	mv y.tab.h wqlyacc.h

bison:
	bison -p wql -d wql.y
	mv wql.tab.c wqlyaccinc.c
	mv wql.tab.h wqlyacc.h

size:
	size $(TARGET)

tsize:
	size $(TARGET) | awk '{ x += $$4 } END { print x }'

