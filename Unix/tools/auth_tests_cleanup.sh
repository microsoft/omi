#!/bin/sh
# 
# output directory is lone argument

ntlm_file=$1/tmp/ntlm

if [ -f $ntlm_file ]; then
    echo "Removing NTLM file: $ntlm_file"
    rm -f $ntlm_file
fi

