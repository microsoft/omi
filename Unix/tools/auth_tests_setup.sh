#!/bin/bash
#
# Used by regress and 'make tests'.  Should be run at omi/Unix level.

if [ -z $outputdir ]; then
   outputdir=$1
fi

echo "OUTPUTDIR = " $outputdir

basedir=`basename ${PWD}`

if [ "$basedir" != "Unix" ]; then
    echo "Must be run from omi/Unix directory."
    exit 1
fi

username=$OMI_USER
userpasswd=$OMI_PASSWORD

#
# Clean up previous (if any) running omiserver
#
for d in output*
do
    pidFile=$d/var/run/omiserver.pid
    echo "Examining pid file:  $pidFile..."
    if [ -f $pidFile ]; then
        pid=`cat $pidFile`
    
        if [ "x${pid}" != "x" ]; then
            ps -p ${pid} | grep omiserver > /dev/null
            if [ $? -eq 0 ]; then
                sudo kill -15 $pid
            fi
        fi
        sudo rm -f $pidFile
    fi
done

#
# Setup the NTLM auth file for client and server. They must be different files because 
# if the differing permissions, as the server file must be owned by root and the client by
# the user.
#
# If there is already a cred file present we defer to it. In configure we possibly copied over
# a prebuilt cred file for the server from Unix/etc/creds. If such a file exists, it must contain the test
# credentials. The source of the cred file is contained in Unix/etc/creds. The destination is defined by 
# configure --dev. The credfile is not defined in non-dev build environments.
#
# If the server cred file isn't present we build one with the test credentials, derived from OMI_USER and 
# OMI_PASSWORD env variables.
#
# We create the cred file for the client and point to it with the NTLM_USER_FILE env variable.  This prevents us 
# from clobbering the credentials in ~/.omi/
#
# Once we have created the cred files, they are static unless removed, edited, or configured via
# configure. We always set the ownership and r/w permissions.


echo "scriptdir*1 = " ./tools

scriptdir="./tools"
#scriptdir=$(dirname ${scriptdir})
scriptdir=$(readlink -f ${scriptdir})

echo "scriptdir = " $scriptdir

if [ "x${username}" != "x" -a "x${userpasswd}" != "x" ]; then
    SUDO_PATH=`which sudo`
    export SUDO_PATH

## NTLM setup
    
    # client side creds
    echo "build cred files"

    client_ntlm_cred_dir=$outputdir/tmp/creds
    client_ntlm_file=$outputdir/tmp/creds/ntlm
    hostname=`uname -n`
    if [ ! -f $client_ntlm_file ]; then
       echo "build client auth file " $client_ntlm_file

       mkdir -p $outputdir/tmp
       mkdir -p $client_ntlm_cred_dir
       echo $hostname":"$username":"$userpasswd > $client_ntlm_file

    fi
    chmod 700 $client_ntlm_cred_dir
    chmod 600 $client_ntlm_file

    NTLM_USER_FILE=$client_ntlm_file
    export NTLM_USER_FILE

    # server side 
    # configure already created the dir

    server_creds_dir=$outputdir/etc/creds
    server_ntlm_file=$server_creds_dir/ntlm
    if sudo test ! -f $server_ntlm_file ; then
       echo "build server auth file " $server_ntlm_file
       cp $client_ntlm_file $server_ntlm_file
    else 
       echo "do not build server auth file " $server_ntlm_file
    fi
    sudo chmod 600 $server_ntlm_file

## Validate Kerberos is setup.

    if [ "$OMI_KRB_TESTS_ENABLED" = "FALSE" ] ; then
        echo "Kerberos Tests Disabled via OMI_KRB_TESTS_ENABLED"
        OMI_KRB_RUN_TESTS="false"
        export OMI_KRB_RUN_TESTS
    else
        unset OMI_KRB_RUN_TESTS
        OS=`uname -s`

       # We bring over the necessary keys from the system table 
       current_user=$(whoami)
       sudo $scriptdir/ktstrip /etc/krb5.keytab $server_creds_dir/omi.keytab $current_user
       if [ "$OS" = "Darwin" ] ; then 
          # kinit on the mac does not allow the passwd to be piped
          ${scriptdir}/kinit.exp ${username}  ${userpasswd}
       else
          #  Just do the kinit initally to prime the cred cache 
          echo ${userpasswd} | kinit -c FILE:/tmp/omi_cc ${username}
       fi
       if [ $? -eq 0 ] ; then
           echo "Kerberos Tests Enabled"
           OMI_KRB_RUN_TESTS="true"
           export OMI_KRB_RUN_TESTS
           # Tis is hard-coded here, but won't always be. In the meantime we can 
           # pretend its being checked in the tests themselves
           OMI_KRB_TESTS_REALM="SCX.COM"
           export OMI_KRB_TESTS_REALM
       else
           echo "Kerberos Tests Disabled Because cannot kinit ${username}"
       fi
    fi
fi

