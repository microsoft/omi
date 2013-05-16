# // Copyright (c) Microsoft Corporation.  All rights reserved.
#
# Set up the build workspace on a remote unix machine: Pushes a script
# named WorkspaceSetup.bsh to the unix machine, then makes the script
# executable over there and then runs the script. 
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

$BuildHostname=hostname

$ScriptName = "GetFiles.ps1"
WriteToLog "Starting" 
$timeStarted = date


$BuildHost = $args[0]
$FilesToGet= $args[1]
$DropDestination = $args[2]

$BuildUser = "serviceb"
$BuildUserPW = "OpsMgr2007R2"

$TransferExec="..\build\Tools\Pscp\pscp.exe"

WriteToLog "     BuildHost: $BuildHost"
WriteToLog " WorkSpaceName: $WorkSpaceName"
WriteToLog "     BuildUser: $BuildUser"
WriteToLog "   BuildUserPW: <NOT>"

trap {

  # This is the trap for exceptions coming from the SSHCom calls:
  # Esceptions might be produced if connection can't be made among other things.  
  $ExceptionString = $_scp 
  WriteToLog "ExceptionString: $ExceptionString"
  WriteToLog "SCRIPT ERROR : Breaking on trapped Exception"
  break
 
}


WriteToLog "Attempting to to clear log buffer for troubleshooting 01"
WriteToLog "Attempting to to clear log buffer for troubleshooting 02"
WriteToLog "Attempting to to clear log buffer for troubleshooting 03"
WriteToLog "Attempting to to clear log buffer for troubleshooting 04"
WriteToLog "Attempting to to clear log buffer for troubleshooting 05"
WriteToLog "Attempting to to clear log buffer for troubleshooting 06"

 if (!(test-path -path "$DropDestination"))
 {
	mkdir $DropDestination
 }

WriteToLog "$TransferExec -r -C -l $BuildUser $BuildHost`:$FilesToGet $DropDestination"
$ans = Invoke-Expression "$TransferExec -r -C -l $BuildUser -pw $BuildUserPW $BuildHost`:$FilesToGet $DropDestination\"
WriteToLog "$ans"
$retval = $lastexitcode

WriteToLog "$ans"

$timeFinished = date
$elapsedTime = $timeFinished - $timeStarted 
WriteToLog "Elapsed Time "$elapsedTime.TotalMinutes" Minutes"

########
# exit

if ( $retval -eq 0 ) {
   WriteToLog "Exiting 0"
   exit 0
}

WriteToLog "Exiting 2"
exit 2