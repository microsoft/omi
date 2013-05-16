.PHONY: gen3
TOP = ..
include $(TOP)/config.mak

LIBRARY = xml

SOURCES = xml.c dump.c

INCLUDES = $(TOP) $(TOP)/common

include $(TOP)/mak/rules.mak

gen:
	gcc -Wall -o genischar genischar.c
	./genischar

gen2:
	gcc -Wall -o genisspace genisspace.c
	./genisspace

gen3:
	gcc -Wall -o gen3 gen3.c
	./gen3
