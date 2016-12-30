Install latest dotnet:
    https://github.com/dotnet/cli/blob/rel/1.0.0/scripts/obtain/dotnet-install.sh

Add ~/.dotnet to your path

Create directory structure under $(NUGET_PACKAGING_DIR)
.
├── libmi.nuspec
└── runtimes
    ├── linux
    │   └── native
    │       └── libmi.so
    └── osx
        └── native
            └── libmi.dylib

Update the version number in libmi.nuspec if needed
    <version>1.0.0-alpha02</version>

NOTE: powershell is locked into 1.0.0-* right now so if we create proper version number we will need to update powershell dependency as well.

Create package by running this from the same directory as libmi.nuspec:
    dotnet nuget pack libmi.nuspec

We may be able to specify the directory to output as well.


output from command:
    info : Attempting to build package from 'libmi.nuspec'.
    info : Successfully created package '.../libmi.1.0.0-alpha02.nupkg'.

The package file name is based in the <id> and <version> from the nuspec file, and is created in the $(NUGET_PACKAGING_DIR)/ directory
