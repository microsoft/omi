#!/bin/sh

username=$OMI_USER

if [ "x$username" != "x" ]; then
    userdel=`which userdel`
    if [ "x$userdel" = "x" ]; then
        echo "Failed to find 'userdel'"
        exit 1
    fi
    sudo $userdel --force $username

    if [ -f $ntlm_file ]; then
        rm -f $ntlm_file
    fi
fi
