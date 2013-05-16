TOP = ../../../distro

include $(TOP)/config.mak

CXXSHLIBRARY = demo

SOURCES = $(wildcard *.c *.cpp)

INCLUDES = $(TOP) $(TOP)/common 

include $(TOP)/mak/rules.mak

LIBRARIES = micxx base

CLASSES = Demo_Identifier=Identifier /
	Demo_Reference=Reference /
	Demo_Test=Test /
	Demo_Main=Main /
	Demo_TestWithAllTypes=AllTypes /
	Demo_Performance=Performance

$(TARGET): $(__OBJECTS)
	mkdir -p $(LIBDIR)
	$(CXX) -o $(TARGET) $(__OBJECTS) -L$(LIBDIR) $(__LIBRARIES) $(CXXSHLIBFLAGS) $(LIBNAMEOPT)
	mkdir $(LIBDIR)/Source
	cp ./source/* $(LIBDIR)/Source
	@ echo

reg:
	$(BINDIR)/omireg $(TARGET)

gen:
	$(BINDIR)/omigen --cpp -m demo schema.mof $(Class)
