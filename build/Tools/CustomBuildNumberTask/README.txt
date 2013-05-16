CustomBuildNumberTask is a .net assembly which contains the MSBuild custom 
task "CustomBuildNumber".

The CustomBuildNumber task will update the build number for the currently in 
progress TFS build job (as well as the drop location) but if it detects that 
there will be a collision with an existing build number then it will increment 
the build revision number (or tack on a build revision number, starting at .1
if one did not previously exist) up to a maximum of 20 times until a free 
build number is found. The actual build number is returned as an output, if 
no free build number exists in the range attempted then the task will throw an
exception of type BuildNumberAlreadyExistsException.

To use the task in an MSBuild project it's necessary to first reference the 
assembly:

  <UsingTask TaskName="CustomBuildNumberTask.CustomBuildNumber" AssemblyFile="Path\to\Assembly\CustomBuildNumberTask.dll" />

Then use it within a target.

<Target>
    <CustomBuildNumber TFSServerURI="$(TeamFoundationServerUrl)" BuildURI="$(BuildUri)" RequestedBuildNumber="$(BuildNumber)" >
        <Output TaskParameter="BuildNumber" PropertyName="BuildNumber" />
    </CustomBuildNumber>
</Target>

--------

PARAMETERS:
    TFSServerURI
        The URI necessary to connect to the TFS instance where the build is 
        running. Within the context of a typical build job this will be the 
        value of the existing property TeamFoundationServerUrl (assuming you
        want to update the build number of the current build, which is the
        typical case).

        Ex: http://scxtfs4:8080/tfs/SCX

    BuildURI
        The URI specifying the build run to update, within the context of a 
        typical build job this will be the value of the BuildUri property.

        Ex: vstfs:///Build/Build/117587

    RequestedBuildNumber
        The build number requested to change to.

        Ex: REDHAT_4.0_x64_1.4.0-482_20120510.1

    [DropLocationRoot]
        Optional. The new root drop location to use for this build, useful 
        for changing the drop location of a build based on different 
        parameters.

        Ex: \\scxrelease\Build\ScxCore\MAIN\REDHAT4.0_x64

    [TrimFromDropDirectory]
        Optional. If there are parts of the BuildNumber you want to trim 
        before it is used as the name of the drop directory then you can set 
        that here. Requires the DropLocationRoot to have been set, otherwise
        this parameter has no effect.

        Ex: "REDHAT_4.0_x64_" with the build number: REDHAT_4.0_x64_1.4.0-482_20120510.1
        produces: "1.4.0-482_20120510.1" as the final drop directory.

    [ResetBuildRevision]
        Optional, default false. Whether to reset the build revision for the 
        requested build number back to 1 instead of the actual build revision. 
        For example if you have build number: 482_20120510.12 but you wish to 
        request build number 482_20120510.1, useful if you set the build 
        number to a different value depending on input parameters and the 
        automatically generated build number may have a very high revision.

        Ex: true

    [MaxRevisionIncrements]
        Optional, default 20. The maximum number of build revision values to 
        increment through to find one that hasn't been taken.

        Ex: 100

OUTPUT:
    BuildNumber
        The actual new build number for the current build.

        Ex: REDHAT_4.0_x64_1.4.0-482_20120510.5

    DropLocation
        The actual drop location for the build.

        Ex: \\scxrelease\Build\ScxCore\MAIN\REDHAT4.0_x64\1.4.0-482_20120510.1
    
--------

The sources for this task are currently checked into http://vstfpg05:8080/tfs 
under the CDM TPC at $/Sandbox/private/SCXTools/CustomBuildNumber