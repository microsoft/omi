#!/bin/bash

echo Starting Traces Generator
echo gentraces.sh FILE or SYSLOG or NOOP

if [ $1="FILE" ]; then
        echo Generating traces for File Logging
        output/bin/oigenc $1 base/oi_traces.h base/oiomi.h
        exit 0
fi

if [ $1="SYSLOG" ]; then
        echo Generating traces for Syslog
        output/bin/oigenc $1 base/oi_traces.h OMI LOG_NDELAY LOG_LOCAL1 base/oiomi.h
        exit 0
fi

if [ $1="NOOP" ]; then
        echo Generating no traces at all
        output/bin/oigenc $1 base/oi_traces.h base/oiomi.h
        exit 0
fi

if [ -z $1 ]; then
        echo Defaulting to FILE mode
        output/bin/oigenc FILE base/oi_traces.h base/oiomi.h
        exit 0
fi
