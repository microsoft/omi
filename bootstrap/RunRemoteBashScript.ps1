# // Copyright (c) Microsoft Corporation.  All rights reserved.
#
# Run a remote script that already is on the server, chmod -x first. 
# Should run any remote script, but the intention is to make
# all scx build scripts be bash.
#
######
# Set up the page width to be 3000 characters wide so output from things such 
# as make are not line wrapped by powershell output. 
$pshost=get-host
$pswindow=$pshost.ui.rawui
$newsize=$pswindow.buffersize
$newsize.width=3000
$pswindow.buffersize=$newsize

#####
# Stamp everything that gets writting from this script with the script name and date.
Function WriteToLog {
	$date = date
    write "$ScriptName ($date) : $args" 
}

$ScriptName = "RunRemoteBashScript.ps1"
$workingdir = get-location
WriteToLog "Starting" 
$timeStarted = date

$BuildHost = $args[0]
$ScriptToRun = $args[1]

$MaxRetries = 3
$TimeoutLength = 7200000	#Set Unix/Windows communication timeout to two hours.

$numargs = $args.length
If ( $numargs -lt 1 ) {
   WriteToLog "SCRIPT ERROR: Need at least buildhost and script to run"
   $host.SetShouldExit(1)
   exit

}

If ($args[2] -eq "-retry") {
	$RetryNum = $args[3]
	$currentarg = 4
}
else {
	$RetryNum = 0
	$currentarg=2
}

WriteToLog "Number of Args: $numargs"
For ($i = $currentarg; $i -lt $numargs; $i++) {
  $ArgsForScript = $ArgsForScript + " " + $args[$i]
}

$BuildUser = "serviceb"
$BuildUserPW = "OpsMgr2007R2"

WriteToLog "   ScriptToRun: $ScriptToRun"
WriteToLog " ArgsForScript: $ArgsForScript"
WriteToLog "     BuildHost: $BuildHost"
WriteToLog "     BuildUser: $BuildUser"
WriteToLog "   BuildUserPW: <not>"

trap {

  # This is the trap for exceptions coming from the $schssh. calls:
  # Esceptions might be produced if connection can't be made among other things.  
  $ExceptionString = $_
  WriteToLog "ExceptionString: $ExceptionString"
  WriteToLog "SCRIPT ERROR : Breaking on Trapped Exception"
  break
 
}

######
# Open ssh connection for the subsequent ExecuteCommand3 commands
$scxssh = New-Object -ComObject sshcom.scxssh
$retval = $scxssh.ConnectWithPassword($BuildHost, 22, $BuildUser, $BuildUserPW)

#Open a shell
#$scxssh.OpenShell()
#$ans = $scxssh.GetResponse() # get output from last ShellCommand/ExecuteCommand
#$ans

$scxssh.SetTimeout($TimeoutLength)  #Set a timeout for communications with the remote server in ms.
$ans = $scxssh.GetResponse() # get output from last ShellCommand/ExecuteCommand
$ans

################################
# First Chmod the script. 
$retval = $scxssh.ExecuteCommand3("chmod +x ~/$ScriptToRun") # stat will always be 0
$ans = $scxssh.GetResponse() # get output from last ShellCommand/ExecuteCommand
$ans
WriteToLog "Chmod Command Retval: $retval"

################################
# Then run the script. 
WriteToLog "Running $ScriptToRun $ArgsForScript" 
$retval = $scxssh.ExecuteCommand3( "$ScriptToRun $ArgsForScript") # stat will always be 0        
$ans = $scxssh.GetResponse() # get output from last ShellCommand/ExecuteCommand

# this is a workaround necessary for the upgrade to TFS 2010.
# we print "warning:" at the beginning of the printed string
# or the TFS logger will say the build failed when "warning:" appears later
$ans = "warning: This is not an actual warning but a workaround for the migration to TFS 2010`n" + $ans
$ans 

#try
#{
#	$stat = $scxssh.CloseShell()
#}
#catch [System.SystemException]
#{
#	WriteToLog "Connection Timed Out"
#	$RetryNum = $RetryNum + 1	
#
#	$_.ErrorDetails >> exception$RetryNum.txt
#	echo ----------------------- >> exception$RetryNum.txt
#	$_.InvocationInfo >> exception$RetryNum.txt		
#	echo ----------------------- >> exception$RetryNum.txt
#	$_.CategoryInfo >> exception$RetryNum.txt
#	echo ----------------------- >> exception$RetryNum.txt
#	$_.FullyQualifiedErrorId >> exception$RetryNum.txt
#
#	if ($RetryNum -le $MaxRetries)
#	{
#		WriteToLog "Attempting retry: $RetryNum"
#		WriteToLog "MaxRetries: $MaxRetries"
#		WriteToLog "$workingdir\$ScriptName $BuildHost $ScriptToRun -retry $RetryNum $ArgsForScript >> exception$RetryNum.txt"
#		$RetryCommand = "$workingdir\$ScriptName $BuildHost $ScriptToRun -retry $RetryNum $ArgsForScript >> exception$RetryNum.txt"
#		$retval = Invoke-Expression $RetryCommand
#		cp exception$RetryNum.txt -Force ..\Target\
#	}
#}

WriteToLog "$ScriptToRun Retval: $retval"

$timeFinished = date
$elapsedTime = $timeFinished - $timeStarted 
WriteToLog "Elapsed Time "$elapsedTime.TotalMinutes" Minutes"

########
# Shutdown and exit
$stat = $scxssh.Shutdown()
if ( $retval -eq 0 ) {
   WriteToLog "Exiting 0"
   $host.SetShouldExit(0)
   exit
}

WriteToLog "Exiting 2"
$host.SetShouldExit(2)
exit


