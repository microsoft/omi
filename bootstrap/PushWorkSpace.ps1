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

$ScriptName = "PushWorkSpace.ps1"
WriteToLog "Starting" 
$timeStarted = date

$BuildHost = $args[0]
$WorkSpaceName = $args[1]
$BuildDir = $args[2]
$RetryNum = $args[3]

$MaxRetries = 3
$TimeoutLength = 1800000  #Set Unix/Windows communication timeout to half an hour.
$ShellOutputTimeoutLength = 90000  #Set Unix timeout length for commands before they return a value, a minute and a half.

$TransferExec="..\build\Tools\Pscp\pscp.exe"

$BuildUser = "serviceb"
$BuildUserPW = "OpsMgr2007R2"

WriteToLog "     BuildHost: $BuildHost"
WriteToLog " WorkSpaceName: $WorkSpaceName"
WriteToLog "     BuildUser: $BuildUser"
WriteToLog "   BuildUserPW: <NOT>"

trap {

  # This is the trap for exceptions coming from the SSHCom calls:
  # Esceptions might be produced if connection can't be made among other things.  
  $ExceptionString = $_
  WriteToLog "ExceptionString: $ExceptionString"
  WriteToLog "SCRIPT ERROR : Breaking on trapped Exception"
  break
 
}

# create tarball
WriteToLog "Creating workspace archive"

$ArchiveName = "${WorkSpaceName}.tar.gz"
$WorkspaceArchive = "${BuildDir}\BuildType\${ArchiveName}"
if (Test-Path $WorkspaceArchive -pathtype leaf) {
    echo "Deleting old archive $WorkspaceArchive"
    del $WorkspaceArchive
}


$PackWorkspaceCmd = "${BuildDir}\Sources\build\Tools\7zip\7z.exe -r -ttar a ${WorkspaceArchive} ${BuildDir}\Sources\* -xr!Target\*"
WriteToLog $PackWorkspaceCmd
$ans = Invoke-Expression $PackWorkspaceCmd
WriteToLog "$ans"
$retval = $lastexitcode

# Push the tarball to the unix build host

# Push the workspace files.
WriteToLog "Pushing workspace archive"

$PushWorkspaceCmd = "$TransferExec -q -C -l $BuildUser -pw $BuildUserPW $WorkspaceArchive $BuildHost`:${ArchiveName}"
WriteToLog $PushWorkspaceCmd
$ans = Invoke-Expression "echo Y | $PushWorkspaceCmd"
WriteToLog "$ans"
$retval = $lastexitcode

# Push the unpack workspace file
WriteToLog "Pushing workspace unpack script"

$UnpackScriptName = "UnpackWorkspace.bsh"
$QualifiedUnpackScriptName = "${WorkSpaceName}.${UnpackScriptName}"
$PushUnpackCmd = "$TransferExec -q -C -l $BuildUser -pw $BuildUserPW ${BuildDir}\Sources\bootstrap\${UnpackScriptName} $BuildHost`:${QualifiedUnpackScriptName}"
WriteToLog $PushUnpackCmd
$ans = Invoke-Expression $PushUnpackCmd
WriteToLog "$ans"
$retval = $lastexitcode

# Run the unpack workspace command
# --------------------------

$scxssh = New-Object -ComObject sshcom.scxssh
$retval = $scxssh.ConnectWithPassword($BuildHost, 22, $BuildUser, $BuildUserPW)

$scxssh.OpenShell()
$scxssh.SetTimeout($TimeoutLength)  #Set a timeout for communications with the remote server in ms.
$scxssh.SetShellOutputTimeout($ShellOutputTimeoutLength)
$ans=$scxssh.GetResponse()
$ans

WriteToLog "Unpacking workspace files on unix host"

$retval = $scxssh.ShellCommand3("chmod +x ~/${QualifiedUnpackScriptName} && ~/${QualifiedUnpackScriptName} ${WorkSpaceName}")
$ans = $scxssh.GetResponse() # get output from last ShellCommand/ExecuteCommand
$ans

cp exception* -Force ..\Target\

$timeFinished = date
$elapsedTime = $timeFinished - $timeStarted 
WriteToLog "Elapsed Time "$elapsedTime.TotalMinutes" Minutes"

$stat = $scxssh.Shutdown()
if ( $retval -eq 0 ) {
   WriteToLog "Exiting 0"
   $host.SetShouldExit(0)
   exit
}

WriteToLog "SCRIPT ERROR : Exiting 2"
$host.SetShouldExit(2)
exit