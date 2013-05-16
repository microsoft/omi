TOP = ../../../distro
include $(TOP)/config.mak

CXXPROGRAM = TestClient

SOURCES = TestClient.cpp TestClientMain.cpp CustomizedMethod.cpp ExpectedContext.cpp

HEADERS = TestClient.h CustomizedMethod.h ExpectedContext.h

INCLUDES = $(TOP) $(TOP)/common

DEFINES = MI_CONST=

LIBRARIES = omiclient micxx protocol wql xml base

GUID = F875CDC6-E283-4517-97E7-B1CD0545BF47

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)
