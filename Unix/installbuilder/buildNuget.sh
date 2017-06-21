#! /bin/sh

# buildNuget.sh
#
# Build nuget packages for OMI (libmi)
#

# Abort on error

set -e

# Define necessary constants

build_location=/mnt/ostcdata/OSTCData/Builds/omi/develop

subdir_linux=Linux_ULINUX_1.0_x64_64_Release/openssl_1.0.0
subdir_osx=Darwin_10.12_x64_64_Release

# We should be built from omi/Unix directory, which means that
# the "installbuilder" directory should live here.

if [ ! -d installbuilder ]; then
    echo "$0: Must be run from omi/Unix directory" 1>& 2
    exit 1
fi

# ... and the omi.version file should be two levels up
# If we find it, source it for the nuget version number

if [ ! -f ../../omi.version ]; then
    echo "$0: Unable to locate OMI version file omi.version" 1>& 2
    exit 1
fi

. ../../omi.version

if [ "x$OMI_BUILDVERSION_NUGET" = "x" ]; then
    echo "$0: Variable OMI_BUILDVERSION_NUGET undefined in omi.version" 1>& 2
    exit 1
fi

# Pick up the patch version for OMI

build_version=`./configure --show-version-full`

# Verify that we can access the build shares to get the packages we need

if [ ! -d ${build_location}/${build_version} ]; then
    echo "$0: Unable to locate build share at ${build_location}" 1>& 2
    exit 1
fi

build_linux=${build_location}/${build_version}/${subdir_linux}
build_osx=${build_location}/${build_version}/${subdir_osx}

if [ ! -d ${build_linux} ]; then
    echo "$0: Unable to location OMI Linux build at: ${build_linux}"
    exit 1
fi

if [ ! -d ${build_osx} ]; then
    echo "$0: Unable to location OMI OS/X build at: ${build_osx}"
    exit 1
fi

#
# Write out the spec file
#

rm -rf installbuilder/nuget
mkdir -p installbuilder/nuget
cd installbuilder/nuget

echo "Writing libmi.nuspec file ..."

cat > libmi.nuspec <<EOF
<?xml version="1.0" encoding="utf-8"?>
<package xmlns="http://schemas.microsoft.com/packaging/2011/10/nuspec.xsd">
  <metadata>
    <id>libmi</id>
    <version>$OMI_BUILDVERSION_NUGET</version>
    <authors>Microsoft</authors>
    <owners>Microsoft</owners>
    <requireLicenseAcceptance>false</requireLicenseAcceptance>
    <description>OMI client-side wsman library for Linux and OSX</description>
    <copyright>Copyright 2016 Microsoft</copyright>
  </metadata>
</package>
EOF

#
# Build directory structure and populate it
#
# Note, up above, that we are now in the installbuilder/nuget directory
#

mkdir -p runtimes/linux-x64/native runtimes/osx/native 

# Copy the appropriate files in place

cp ${build_linux}/libmi.so runtimes/linux-x64/native
cp ${build_osx}/libmi.dylib runtimes/osx/native

# Finally, invoke dotnet to build the nuget package

dotnet nuget pack libmi.nuspec 

# All done

exit 0
