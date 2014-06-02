TOP = ../../..
include $(TOP)/config.mak

CXXSHLIBRARY = numberProvider

SOURCES = \
    module.cpp \
    X_EvenSmallNumbers_Class_Provider.cpp \
    X_SmallNumber_Class_Provider.cpp \
    X_HugeNumber_Class_Provider.cpp \
    X_Halves_Class_Provider.cpp \
    X_HugeNumberConformsToProfile_Class_Provider.cpp \
    X_HugeNumbers_Class_Provider.cpp \
    X_NumberWorld_Class_Provider.cpp \
    X_NumberWorldConformsToProfile_Class_Provider.cpp \
    X_OddSmallNumbers_Class_Provider.cpp \
    X_Profile_Class_Provider.cpp \
    X_Number1000001_Class_Provider.cpp \
    X_Cat_Class_Provider.cpp \
    X_Dog_Class_Provider.cpp \
    X_HTTPHeader_Class_Provider.cpp \
    stubs.cpp \
    schema.c

INCLUDES = $(TOP) $(TOP)/common

ifeq ($(OS),LINUX)
CXXFLAGS = -fno-exceptions -fno-enforce-eh-specs -fno-rtti
endif

LIBRARIES = micxx base $(PALLIBS)

include $(TOP)/mak/rules.mak

##==============================================================================
##
## gen -- rule to regenerate provider sources.
##
##==============================================================================

CLASSES = \
    X_SmallNumber \
    X_HugeNumber \
    X_NumberWorld \
    X_HugeNumbers \
    X_OddSmallNumbers \
    X_EvenSmallNumbers \
    X_Halves \
    X_Profile \
    X_HugeNumberConformsToProfile \
    X_NumberWorldConformsToProfile \
    X_Number1000001 \
    X_Cat \
    X_Dog \
    X_HTTPHeader

gen:
	$(BINDIR)/omigen -A --cpp schema.mof $(CLASSES)

iv:
	$(BINDIR)/omicli iv test/cpp { X_Dog } Fight { CatsIn [ { X_Cat Key 1001 } ] }

reg:
	$(BINDIR)/omireg -n test/cpp $(TARGET)
