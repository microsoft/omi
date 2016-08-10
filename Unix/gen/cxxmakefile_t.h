#define CXXMAKEFILE_TEMPLATE "\
include <OMIMAK>\n\
\n\
DEFINES = MI_API_VERSION=<MIAPIVERSION>\n\
PROVIDER = <PROVIDER>\n\
SOURCES = <SOURCES>\n\
CLASSES = <CLASSES>\n\
\n\
$(LIBRARY): $(OBJECTS)\n\
	$(CXX) $(CXXSHLIBFLAGS) $(OBJECTS) -o $(LIBRARY) $(CXXLIBS)\n\
\n\
%.o: %.c\n\
	$(CC) -c $(CFLAGS) $(INCLUDES) $< $(CLIBS) -o $@\n\
\n\
%.o: %.cpp\n\
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@\n\
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
