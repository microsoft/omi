Unix builds are run from a single build project under: TeamBuildTypes\UnixBuildTemplate\TFSBuild.proj

To use this project it's necessary to pass in the correct "UnixBuildType" 
parameter for which build you want to run. To create a TFS build definition 
you must pass in this parameter through the "MSBuild Arguments" setting under 
the "Advanced" section on the "Process" tab of the build definition, like so:

Edit Build Definition... > Process > Advanced:

MSBuild Arguments: /p:UnixBuildType=SUSE_10.0_x64

Check the file TeamBuildTypes\UnixBuildTemplate\UnixBuildSettings.proj for 
the list of valid values for UnixBuildType.
