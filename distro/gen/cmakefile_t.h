/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#define CMAKEFILE_TEMPLATE "\
include <OMIMAK>\n\
\n\
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
