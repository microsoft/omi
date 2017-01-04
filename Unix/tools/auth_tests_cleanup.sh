#!/bin/sh
# 
# output directory and its softlink target are the two arguments

ntlm_file=$1/tmp/ntlm

if [ -f $ntlm_file ]; then
    echo "Removing NTLM file: $ntlm_file"
    rm -f $ntlm_file
fi

# Don't do cleanup for now since output is useful for debugging
#rm -rf $1 $2

