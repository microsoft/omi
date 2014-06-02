#!/bin/bash

if [ "$#" != 1 ]; then
    echo "Usage: $0 OMIZIPFILE"
    exit 1
fi

$1/validateomi.sh $1/winomi.zip --dev

