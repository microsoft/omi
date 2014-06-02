
1. =====================BUILD========================

	(a) Enlist admin depot of fbl_srv_msp_dev branch
	(b) build %sdxroot%\admin\wmi\winomi\ folder


2. =====================SETUP========================

	(a) After build, COPY %_nttree%\winomi\ to WIN8 server (FULL SKU or CSS) local folder X
	(b) Copy \\scratch2\scratch\paulall\bins\WinOMI\amd64\lib\process.dll to X\lib (assume running on amd64 machine)
	    Copy \\scratch2\scratch\paulall\bins\WinOMI\amd64\etc\omiregister\root-standardcimv2\*.* to X\etc\omiregister\root-standardcimv2\


3. ================START WINOMI SERVER===============

	(a) Enable firewall 
	    You are going to need to open up the management port that winomi is currently using, which is port 5985.  Run this from cmd console,
	        netsh advfirewall firewall add rule name="Allow port 5985 for WINOMI" protocol=TCP localport=5985 dir=in action=allow
	(b) Start winomi server
            Goto X folder, and run following from cmd.exe
                start omiserver -l --loglevel 4
            It will start another cmd session for running winomi. Using ALT-TAB keys to switch cmd console sessions. 

4. ===============VERIFY WINOMI SERVER================

	(a) running following cmdline to verify server is working under folder X
	        omicli ei root/standardcimv2 msft_windowsprocess


5. ================BUILD & RUN UNIT TEST==============
	
    Please enable firewall for WINOMI server first!

    Default behavior for building and running unittests is with NITS framework; but due to some reason 
    if you want to run with UT framework, set UTBUILD=1 on the razzle window to build and 
    also set UTBUILD=1 on the test running cmd console; this will run the tests using UT framework

    If you are running Win8 OR winsrv2012 DEV box, then
	    (a) Follow BUILD steps to build winomi directory
             (b) following steps will help you run all or individual tests on dev box
		cd %_NTTREE%

		rem this is to be done only once unless you want to change nits binaries
		WinOMI\tests\unittest_install.cmd

		rem following runs the unittests
		WinOMI\tests\unittest.cmd

		rem Running individual test:-

		rem start omi server
		cd %_NTTREE%\WinOMI
		start omiserver.exe -l --loglevel 4

		rem run test
		cd %_NTTREE%\WinOMI\tests\bin
		nits test_cli.dll:TestOMICLI1

		rem stop omi server
		%SYSTEMROOT%\system32\taskkill /F /im omiserver.exe

		rem Running tests on dev machine seems much faster and easier than this; but just in case if you need to run unittests on test machine
		rem instructions to run unittests on windows test machines remain the same as described in previous section; only additional step is
		rem deploying the binaries to test machine which is covered below

    Else you will need to deploy binaries to test machine and run the unittests there; here are the steps:-

		rem deploying binaries to test machine

		rem Getting binaries from scratch:-

		rem On dev box run:-

		cd %_NTTREE%\WinOMI\tests
		putbins.cmd

		rem On test box on elevated cmd.exe console run:-
		rem following is to be done first time
		rem create directory to get binaries and set _NTTREE 

		cd \
		mkdir \bins
		set _NTTREE=\bins

		cd %_NTTREE%
		rem \\scratch2\scratch\<your alias>\bins\amd64\winomi\tests\getbins.cmd <your alias>
		\\scratch2\scratch\girishjo\bins\amd64\winomi\tests\getbins.cmd girishjo

		rem Getting binaries from \\tsclient

		rem On test box on elevated cmd.exe console run:-
		cd %_NTTREE%
		rem \\tsclient\<location of _NTTREE on dev box>\WinOMI\tests\getbinspvt.cmd \\tsclient\<location of _NTTREE on dev box>
		\\tsclient\d\win8\msp_dev.binaries.amd64chk\WinOMI\tests\getbinspvt.cmd \\tsclient\d\win8\msp_dev.binaries.amd64chk

		rem Run unittests with instructions below

		cd %_NTTREE%

		rem this is to be done only once unless you want to change nits binaries
		WinOMI\tests\unittest_install.cmd

		rem following runs the unittests
		WinOMI\tests\unittest.cmd

		rem Running individual test:-

		rem start omi server
		cd %_NTTREE%\WinOMI
		start omiserver.exe -l --loglevel 4

		rem run test
		cd %_NTTREE%\WinOMI\tests\bin
		nits test_cli.dll:TestOMICLI1

		rem stop omi server
		%SYSTEMROOT%\system32\taskkill /F /im omiserver.exe

6. ================PLEASE DO NOT BREAK OMI==============
OMI automatic validation tool

Why?
  OMI and WINOMI share the same source tree, any checkin to WINOMI source tree should NOT break OMI functionalities.

How?
  Long-termly, use automatic validation system. The system will not be ready until ~October. NO ETA yet. Short-termly, every WINOMI DEV should use validation tools as following,

Preparation (one time)
  (1)	Setup a LINUX VM.
	You can copy the VHD from \\hwqin-dev-01\vmshare\fedora.vhd, which is preconfigured with username: test  password: user@123
  (2)	Mount a share folder X to the VM
	It is used to exchange files, above VM already mounted \\scratch2\scratch to /mnt/ntscratch

Validation process
  (1)	Make your change to WINOMI under SD/razzle, and build
  (2)	Run following command line to pack WINOMI source tree to a zip file & put zip file to the mounted share folder X
	%_nttree%\winomi\tests\pack.cmd \\scratch2\scratch\bla
	Two files will be created under the target: winomi.zip & validateomi.sh
  (3)	. Logon to LINUX VM with username: test   password: user@123
	. Open a terminal console and run following command to run as root user, password: user@123
	    su -
	. Run following command line to validate your change
	    /mnt/ntscratch/bla/validateomi.sh /mnt/ntscratch/bla/winomi.zip
	. Any build/tests failures needs to be fixed before check in



7. ====================PS talk to WINOMI=============

        (a) Create a local account and add it into administrators group.
	    Say user name is "test" and password is "User@123", ip adddress is "157.59.86.50", then run following script in PS
		$pw = ConvertTo-SecureString "User@123" -asplaintext -force
		$creds=New-Object System.Management.Automation.PSCredential("157.59.86.50\test", $pw)
		$s = New-CimSession  -Port 5985  -ComputerName 157.59.86.50 -SkipTestConnection -Authentication Basic -Credential $creds
		Get-CimInstance -Namespace root/standardcimv2 -ClassName MSFT_WindowsComputerSystem -CimSession $s
