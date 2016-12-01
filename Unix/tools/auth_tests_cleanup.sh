#!/bin/sh

ntlm_file=$HOME/.ntlm

if [ -f $ntlm_file ]; then
    rm -f $ntlm_file
fi
