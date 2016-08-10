#define CMAKEFILE_TEMPLATE "\
include <OMIMAK>\n\
\n\
DEFINES = MI_API_VERSION=<MIAPIVERSION>\n\
PROVIDER = <PROVIDER>\n\
SOURCES = <SOURCES>\n\
CLASSES = <CLASSES>\n\
\n\
$(LIBRARY): $(OBJECTS)\n\
	$(CC) $(CSHLIBFLAGS) $(OBJECTS) -o $(LIBRARY)\n\
\n\
%.o: %.c\n\
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@\n\
\n\
reg:\n\
	$(BINDIR)/omireg $(CURDIR)/$(LIBRARY)\n\
\n\
gen:\n\
	$(BINDIR)/omigen <CMDLINE>\n\
\n\
clean:\n\
	rm -f $(LIBRARY) $(OBJECTS) $(PROVIDER).reg\n\
\n\n"
