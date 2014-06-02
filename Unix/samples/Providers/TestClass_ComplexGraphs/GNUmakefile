TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = TestClass_ComplexGraphs
SOURCES = $(wildcard *.c) $(wildcard *.cpp)

INCLUDES = $(TOP) $(TOP)/common 

LIBRARIES = base $(PALLIBS)

include $(TOP)/mak/rules.mak

$(LIBRARY): $(OBJECTS)
	$(CC) $(CXXSHLIBFLAGS) $(OBJECTS) -o $(LIBRARY)

%.o: %.c
	$(CC) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

reg:
	$(BINDIR)/omireg $(TARGET)

