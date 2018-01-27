#!/bin/sh
#
# usage: update_keytab.sh

SCRIPTNAME=$0
OMI_HOME=/opt/omi

syskeytab="/etc/krb5.keytab"
omikeytab="/etc/opt/omi/creds/omi.keytab"
ktstrip="$OMI_HOME/bin/support/ktstrip"
tmpfile=$(mktemp)

checkConfiguration()
{
    if ! crontab -l 2> /dev/null | grep -q "$ktstrip" ; then
        return 1
    fi

    return 0
}


configure()
{
    if checkConfiguration; then
       timestamp=$(date +%F\ %T)
       printf "$timestamp System already configured to run $SCRIPTNAME automatically\n"
       return 0
    fi

    # prime the omi keytab
    [ -f $syskeytab ] && [ \( ! -f $omikeytab \) -o \( $syskeytab -nt $omikeytab \) ] && $ktstrip $syskeytab $omikeytab || true

    crontab -l > $tmpfile 2> /dev/null || true

    # We don't worry about log rotate
    # execute the check every minute.

    echo "* * * * * [ -f $syskeytab ] && [ \( ! -f $omikeytab \) -o \( $syskeytab -nt $omikeytab \) ] && $ktstrip $syskeytab $omikeytab || true" >>$tmpfile

    crontab $tmpfile

    timestamp=$(date +%F\ %T)
    printf "$timestamp : Crontab configured to update omi keytab automatically\n"
}

unconfigure()
{
    if ! checkConfiguration; then
        timestamp=$(date +%F\ %T)
        printf "$timestamp : Crontab not configured to update omi keytab automatically. Skip unconfigure\n"
        return 0
    fi

    crontab -l > $tmpfile 2> /dev/null || true

    tmpfile2=$(mktemp)
    grep -v "$omikeytab" $tmpfile >$tmpfile2 
    crontab $tmpfile2

    timestamp=$(date +%F\ %T)
    printf "$timestamp : Crontab no longer configured to update omi keytab.\n"
}



while [ $# -ne 0 ]
do
    case "$1" in
	--configure)
        configure
	    shift 1
	    ;;

	--unconfigure)
        unconfigure
	    shift 1
	    ;;

    *)
        printf "$0 unknown option"
        numargs=0
        ;;
    esac
done

