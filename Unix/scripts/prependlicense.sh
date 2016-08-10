#!/bin/bash
SOURCES1=`find . -name '*.c' -print`
SOURCES2=`find . -name '*.cpp' -print`
SOURCES3=`find . -name '*.h' -print`
SOURCES="$SOURCES1 $SOURCES2 $SOURCES3"
for i in $SOURCES
do
    echo $i
    cp $i $i.tmp
    cat license.h_ > $i
    cat $i.tmp >> $i
    rm -f $i.tmp
done
