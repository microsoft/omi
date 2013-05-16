#!/bin/bash
#set -vx

##========================================================================
## usage 
##========================================================================
function usage()
{
	echo "PerformanceTest.sh <omiInstallLocation> <durationRunDays> <workingFolder> <platformName>"
}

##=======================================
## Check paramters
##=======================================

if [ "$#" -ne 4 ]; then
	echo "parameters error"
	usage;
	exit 5
fi

omiInstallLocation=$1
durationRunDays=$2
workingFolder=$3
platform=$4

if [ -d "$workingFolder" ]; then
	echo "Working folder exist, clearing it now"
	rm -f $workingFolder/*
else
	echo "Working folder not exist, creating it now"
	mkdir $workingFolder
fi

os=`uname -s`

##=======================================
## Check OMI status
##=======================================
if [ -d "$omiInstallLocation" ]; then
	echo "OMI is found"
else
	echo "OMI is not found"
	exit 10
fi

#restart OMI server for long-haul performance test
case $os in
        Linux)
            if [ -z `ps aux | grep omiserver | grep -v grep` ]; then 
                echo "OMI server is stopped, starting server now"
				$omiInstallLocation/bin/omiserver -d
				if [ "$?" -ne 0 ]; then
					echo "start server failed, exit"
					exit 17
				fi
            else
                echo "OMI is online, restarting server now"
				$omiInstallLocation/bin/omiserver -s
				$omiInstallLocation/bin/omiserver -d
				if [ "$?" -ne 0 ]; then
                 	echo "restart server failed, exit"
                    exit 17
                fi
            fi
            ;;
        *)
            if [ -z `ps -ef | grep omiserver | grep -v grep` ]; then 
                echo "OMI server is stopped, starting server now"
				$omiInstallLocation/bin/omiserver -d
				if [ "$?" -ne 0 ]; then
					echo "start server failed, exit"
					exit 17
				fi
            else
                echo "OMI is online, restarting server now"
				$omiInstallLocation/bin/omiserver -s
				$omiInstallLocation/bin/omiserver -d
				if [ "$?" -ne 0 ]; then
                 	echo "restart server failed, exit"
                    exit 17
                fi
            fi
            ;;
esac

##=======================================
## commands
##=======================================
callServerCommand="$omiInstallLocation/bin/omicli -R 50 ei root/cimv2 demo_performance &> /dev/null &"
monitorLog=$workingFolder/omiMonitor.log
monitorCommand=""
uninstJobsFile=$workingFolder/uninst
echo "$platform Performance test Report----------------------" > $monitorLog
$omiInstallLocation/bin/omiserver -v >> $monitorLog
case $os in
        Linux)
            monitorCommand="ps aux | grep omiserver | grep -v grep | awk '{print \$3\" \"\$4}'>$workingFolder/temp.log;date>$workingFolder/date.log;read cpuUsage memUsage<$workingFolder/temp.log;read recordDate<$workingFolder/date.log;rm -f $workingFolder/temp.log $workingFolder/date.log;echo omiserver.bin -- \$recordDate -- Monitor report:$'\n'CPU Rate: \$cpuUsage $'\n'MEM Rate: \$memUsage>> $monitorLog;ps aux | grep omiserver | grep -v grep | awk '{print \$2}' | xargs pmap | tail -n 3 | grep -i total>>$monitorLog"
            ;;
		HP-UX)
			monitorCommand="UNIX95= ps -efo pcpu,args | grep omiserver | grep -v grep | awk '{print \$1}'>$workingFolder/temp.log;date>$workingFolder/date.log;read cpuUsage<$workingFolder/temp.log;read recordDate<$workingFolder/date.log;rm -f $workingFolder/temp.log $workingFolder/date.log;echo omiserver.bin -- \$recordDate -- Monitor report:'\n'CPU Rate: \$cpuUsage '\n'MEM: >> $monitorLog;ps -ef | grep omiserver | grep -v grep | awk '{print \$2}' | xargs pmap | tail -n 2 | grep -v - | awk '{print \$1\" \"\$2}'>>$monitorLog"
          ;;
		SunOS)
			monitorCommand="ps -efo pcpu,pmem,comm | grep omiserver | awk '{print \$1\" \"\$2}'>$workingFolder/temp.log;date>$workingFolder/date.log;read cpuUsage memUsage<$workingFolder/temp.log;read recordDate<$workingFolder/date.log;rm -f $workingFolder/temp.log $workingFolder/date.log;echo omiserver.bin -- \$recordDate -- Monitor report:'\n'CPU Rate: \$cpuUsage '\n'MEM Rate: \$memUsage>> $monitorLog;ps -ef | grep omiserver | grep -v grep | awk '{print \$2}' | xargs pmap | grep -i total>>$monitorLog"
            ;;
		AIX)
			monitorCommand="ps -efo pcpu,pmem,comm | grep omiserver | awk '{print \$1\" \"\$2}'>$workingFolder/temp.log;date>$workingFolder/date.log;read cpuUsage memUsage<$workingFolder/temp.log;read recordDate<$workingFolder/date.log;rm -f $workingFolder/temp.log $workingFolder/date.log;echo omiserver.bin -- \$recordDate -- Monitor report: CPU Rate: \$cpuUsage MEM Rate: \$memUsage>> $monitorLog;ps -ef | grep omiserver | grep -v grep | awk '{print \$2}' | xargs procmap | grep -i total>> $monitorLog"
            ;;
        *)
            echo "unsupported platform, exit"
			exit 18
            ;;
esac

##========================================================================
## find crontab file according to paltform 
##========================================================================
crontabFile=""
case $os in
        	Linux)
			crontabFile="/etc/crontab"
            		;;
		*)
			crontabFile="/var/spool/cron/crontabs/root"
            		;;
esac


##=======================================================================================
## create a cron job to enumeration and invoke calls on the test provider(per 5 minutes) 
##=======================================================================================
cp $crontabFile $crontabFile.bak
case $os in
        	Linux)
			echo "*/5 * * * * root $callServerCommand">>$crontabFile
            		;;
		*)
			echo "1,6,11,16,21,26,31,36,41,46,51,56 * * * * $callServerCommand">>$crontabFile
            		;;
esac

if [ "$?" -ne 0 ]; then
	echo "install cron job[enumerate call] failed"
	echo "quit"
	exit 11
else
	echo "install cron job[enumerate call] successfully"
fi


##==============================================================================================
## create a cron job to takes memory and CPU usage statistics(per 6 minutes) and writes to a file 
##==============================================================================================

case $os in
        	Linux)
			echo "*/6 * * * * root $monitorCommand">>$crontabFile
            		;;
		*)
			echo "5,11,17,23,29,35,41,47,53,59 * * * * $monitorCommand">>$crontabFile
            		;;
esac

if [ "$?" -ne 0 ]; then
	echo "install cron job[monitor statistics] failed"
	echo "quit"
	exit 12
else
	echo "install cron job[monitor statistics] successfully"
fi

uninstTestShell=$workingFolder/uninstall
##========================================================================
## create uninstall test script
##========================================================================
function UninstallTest()
{
	echo "create uninstall test script"
	touch $uninstTestShell
	if [ -f "$uninstTestShell" ]; then
		echo "create successfully"
	else
		echo "create failed,exit"
		exit 22
	fi
	# restore crontab
	echo '#!/bin/bash'> $uninstTestShell
	echo "rm -f $crontabFile" >> $uninstTestShell
	echo "mv -f $crontabFile.bak $crontabFile" >> $uninstTestShell
	echo "ps -ef | grep cron | grep -v grep | awk '{print \$2}' | xargs kill" >> $uninstTestShell
	chmod a+x $uninstTestShell
}


##========================================================================
## create an at job to terminate above two cron jobs when time's up 
##========================================================================

case $os in
        	Linux)
			echo "sed -i -e '/.*omicli.*/d' -e '/.*omiserver.*/d' $crontabFile">>$uninstJobsFile
			at -f $uninstJobsFile `date | awk '{print $4}' | cut -d : -f 1-2` + ${durationRunDays} day
            		;;
			AIX)
			UninstallTest;
			at -f $uninstTestShell `date | awk '{print $4}' | cut -d : -f 1-2` + ${durationRunDays} day
            		;;
			*)
			echo "sed -e '/.*omicli.*/d' -e '/.*omiserver.*/d' $crontabFile>$workingFolder/tempCrontab;mv -f $workingFolder/tempCrontab $crontabFile">>$uninstJobsFile
			at -f $uninstJobsFile `date | awk '{print $4}' | cut -d : -f 1-2` + ${durationRunDays} day
            		;;
esac

if [ "$?" -ne 0 ]; then
	echo "install at job failed"
	echo "quit"
	exit 13
else
	echo "install at job for terminate performance test successfully"
fi

##========================================================================
## restart crond service 
##========================================================================
echo "make sure that installed cron jobs are effective, restart crond service"
case $os in
        	Linux)
			if [ -z ` ls /etc/init.d/ | grep crond` ]; then
				/etc/init.d/cron restart
			else
				/etc/init.d/crond restart
			fi
            		;;
		HP-UX)
			/sbin/init.d/cron stop
			/sbin/init.d/cron start
            		;;
		SunOS)
			ps -ef | grep cron | grep -v grep | awk '{print $2}' | xargs kill
            		;;
		AIX)
			ps -ef | grep cron | grep -v grep | awk '{print $2}' | xargs kill
            		;;
        	*)
			echo "unsupported platforms,exit"
			exit 18
            		;;
esac
exit 0
