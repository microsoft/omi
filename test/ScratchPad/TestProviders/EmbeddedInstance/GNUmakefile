include /opt/omi/share/omi.mak

PROVIDER = instance
SOURCES = $(wildcard *.c *.cpp)
CLASSES = XXX_Main=MainXXX_EmbeddedInstance=EmbeddedInstance 

$(LIBRARY): $(OBJECTS)
	$(CXX) $(CXXSHLIBFLAGS) $(OBJECTS) -o $(LIBRARY) $(CXXLIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< $(CLIBS) -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

reg:
	$(BINDIR)/omireg $(CURDIR)/$(LIBRARY)

gen:
	$(BINDIR)/omigen --cpp -m instance schema.mof XXX_Main=Main XXX_EmbeddedInstance=EmbeddedInstance

clean:
	rm -f $(LIBRARY) $(OBJECTS) $(PROVIDER).reg


