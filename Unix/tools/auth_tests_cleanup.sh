#!/bin/sh

ntlm_file=./output/tmp/ntlm

if [ -f $ntlm_file ]; then
    rm -f $ntlm_file
fi

